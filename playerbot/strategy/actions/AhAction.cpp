#include "botpch.h"
#include "../../playerbot.h"
#include "AhAction.h"
#include "../../../ahbot/AhBot.h"
#include "../values/ItemCountValue.h"
#include "../../RandomItemMgr.h"
#include "../values/BudgetValues.h"
#include <AuctionHouseBot/AuctionHouseBot.h>

using namespace std;
using namespace ai;

bool AhAction::Execute(Event& event)
{
    string text = event.getParam();

    list<ObjectGuid> npcs = AI_VALUE(list<ObjectGuid>, "nearest npcs");
    for (list<ObjectGuid>::iterator i = npcs.begin(); i != npcs.end(); i++)
    {
        Unit* npc = bot->GetNPCIfCanInteractWith(*i, UNIT_NPC_FLAG_AUCTIONEER);
        if (!npc)
            continue;
    
        if (!sRandomPlayerbotMgr.m_ahActionMutex.try_lock()) //Another bot is using the Auction right now. Try again later.
            return false;

        bool doneAuction = ExecuteCommand(text, npc);

        sRandomPlayerbotMgr.m_ahActionMutex.unlock();
        
        return doneAuction;
    }

    ai->TellError("Cannot find auctioneer nearby");
    return false;
}

bool AhAction::ExecuteCommand(string text, Unit* auctioneer)
{
    uint32 time;
#ifdef MANGOSBOT_ZERO
    time = 8 * HOUR / MINUTE;
#else
    time = 12 * HOUR / MINUTE;
#endif

    if (text == "vendor")
    {
        AuctionHouseEntry const* auctionHouseEntry = bot->GetSession()->GetCheckedAuctionHouseForAuctioneer(auctioneer->GetObjectGuid());
        if (!auctionHouseEntry)
            return false;

        list<Item*> items = AI_VALUE2(list<Item*>, "inventory items", "usage " + to_string(ITEM_USAGE_AH));
        
        bool postedItem = false;

        for (auto item : items)
        {
            RESET_AI_VALUE2(ItemUsage, "item usage", ItemQualifier(item).GetQualifier());
            if(AI_VALUE2(ItemUsage, "item usage", ItemQualifier(item).GetQualifier()) != ITEM_USAGE_AH)
                continue;

            uint32 deposit = AuctionHouseMgr::GetAuctionDeposit(auctionHouseEntry, time, item);

            RESET_AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::ah);
            uint32 freeMoney = AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::ah);

            if (deposit > freeMoney)
                return false;

            uint32 price = GetSellPrice(item->GetProto());

            price *= item->GetCount();

            postedItem |= PostItem(item, price, auctioneer, time);

            if (!urand(0, 5))
                break;
        }

        return postedItem;
    }

    int pos = text.find(" ");
    if (pos == string::npos) return false;

    string priceStr = text.substr(0, pos);
    uint32 price = ChatHelper::parseMoney(priceStr);

    list<Item*> found = ai->InventoryParseItems(text, ITERATE_ITEMS_IN_BAGS);
    if (found.empty())
        return false;

    Item* item = *found.begin();

    return PostItem(item, price, auctioneer, time);
}

bool AhAction::PostItem(Item* item, uint32 price, Unit* auctioneer, uint32 time)
{
    ObjectGuid itemGuid = item->GetObjectGuid();
    ItemPrototype const* proto = item->GetProto();
    uint32 cnt = item->GetCount();

    WorldPacket packet;
    packet << auctioneer->GetObjectGuid();
#ifdef MANGOSBOT_TWO
    packet << (uint32)1;
#endif
    packet << itemGuid;
#ifdef MANGOSBOT_TWO
    packet << cnt;
#endif
    packet << price * 95 / 100;
    packet << price;
    packet << time;

    bot->GetSession()->HandleAuctionSellItem(packet);

    if (bot->GetItemByGuid(itemGuid))
        return false;

    ostringstream out;
    out << "Posting " << ChatHelper::formatItem(item, cnt) << " for " << ChatHelper::formatMoney(price) << " to the AH";
    ai->TellMasterNoFacing(out.str(), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
    return true;
}

uint32 AhAction::GetSellPrice(ItemPrototype const* proto)
{
    uint32 price = sAuctionHouseBot.GetItemData(proto->ItemId).Value;

    if (!price)
        price = auctionbot.GetSellPrice(proto);

    if (!price)
        price = proto->SellPrice * 1.5;

    return price;
}


bool AhBidAction::ExecuteCommand(string text, Unit* auctioneer)
{
    AuctionHouseEntry const* auctionHouseEntry = bot->GetSession()->GetCheckedAuctionHouseForAuctioneer(auctioneer->GetObjectGuid());
    if (!auctionHouseEntry)
        return false;

    // always return pointer
    AuctionHouseObject* auctionHouse = sAuctionMgr.GetAuctionsMap(auctionHouseEntry);

    if (!auctionHouse)
        return false;

    AuctionHouseObject::AuctionEntryMap const& map = auctionHouse->GetAuctions();

    if (map.empty())
        return false;

    AuctionEntry* auction = nullptr;

    vector<pair<AuctionEntry*, uint32>> auctionPowers;

    if (text == "vendor")
    {
        auto data = WorldPacket();
        uint32 count, totalcount = 0;
        auctionHouse->BuildListBidderItems(data, bot, 9999, count, totalcount);

        if (totalcount > 10) //Already have 10 bids, stop.
            return false;

        unordered_map <ItemUsage, int32> freeMoney;

        freeMoney[ITEM_USAGE_EQUIP] = freeMoney[ITEM_USAGE_REPLACE] = freeMoney[ITEM_USAGE_BAD_EQUIP] = (uint32)NeedMoneyFor::gear;
        freeMoney[ITEM_USAGE_USE] = (uint32)NeedMoneyFor::consumables;
        freeMoney[ITEM_USAGE_SKILL] = freeMoney[ITEM_USAGE_DISENCHANT] =(uint32)NeedMoneyFor::tradeskill;
        freeMoney[ITEM_USAGE_AMMO] = (uint32)NeedMoneyFor::ammo;
        freeMoney[ITEM_USAGE_QUEST] = freeMoney[ITEM_USAGE_AH] = freeMoney[ITEM_USAGE_VENDOR] = freeMoney[ITEM_USAGE_FORCE] = (uint32)NeedMoneyFor::anything;

        uint32 checkNumAuctions = urand(50, 250);

        for (uint32 i = 0; i < checkNumAuctions; i++)
        {
            auto curAuction = std::next(std::begin(map), urand(0, map.size()-1));

            auction = curAuction->second;

            if (!auction)
                continue;

            if (auction->owner == bot->GetGUIDLow())
                continue;

            uint32 cost = std::min(auction->buyout, uint32(std::max(auction->bid, auction->startbid) * frand(1.05f, 1.25f)));

            ItemUsage usage = AI_VALUE2(ItemUsage, "item usage", ItemQualifier(auction).GetQualifier());

            if (freeMoney.find(usage) == freeMoney.end() || cost > AI_VALUE2(uint32, "free money for", freeMoney[usage]))
                continue;

            uint32 power = 1;
                
            switch (usage)
            {
            case ITEM_USAGE_EQUIP:
            case ITEM_USAGE_REPLACE:
            case ITEM_USAGE_BAD_EQUIP:
                power = sRandomItemMgr.GetLiveStatWeight(bot, auction->itemTemplate);
                break;
            case ITEM_USAGE_AH:
                if (cost >= (int32)GetSellPrice(sObjectMgr.GetItemPrototype(auction->itemTemplate)))
                    continue;
                power = 1000;
                break;
            case ITEM_USAGE_VENDOR:
                if (cost >= (int32)sObjectMgr.GetItemPrototype(auction->itemTemplate)->SellPrice)
                    continue;
                power = 1000;
                break;
            case ITEM_USAGE_FORCE:
                power = 1000;
                break;
            }

            power *= 1000;
            power /= (cost+1);

            auctionPowers.push_back(make_pair(auction, power));
        }

        std::sort(auctionPowers.begin(), auctionPowers.end(), [](std::pair<AuctionEntry*, uint32> i, std::pair<AuctionEntry*, uint32> j) {return i > j; });

        bool bidItems = false;

        for (auto auctionPower : auctionPowers)
        {
            auction = auctionPower.first;

            if (!auction)
                continue;

            ItemUsage usage = AI_VALUE2(ItemUsage, "item usage", ItemQualifier(auction).GetQualifier());

            uint32 price = std::min(auction->buyout, uint32(std::max(auction->bid, auction->startbid) * frand(1.05f, 1.25f)));

            if (freeMoney.find(usage) == freeMoney.end() || price > AI_VALUE2(uint32, "free money for", freeMoney[usage]))
                if (!urand(0, 5))
                    break;
                else
                continue;

            bidItems = BidItem(auction, price, auctioneer);
                
            if (bidItems)
                totalcount++;

            if (!urand(0, 5) || totalcount > 10)
                break;

            RESET_AI_VALUE2(uint32, "free money for", freeMoney[usage]);
        }

        return bidItems;
    }

    int pos = text.find(" ");
    if (pos == string::npos) return false;

    string priceStr = text.substr(0, pos);
    uint32 price = ChatHelper::parseMoney(priceStr);

    for (auto curAuction : map)
    {
        auction = curAuction.second;

        if (auction->owner == bot->GetGUIDLow())
            continue;

        ItemPrototype const* proto = sObjectMgr.GetItemPrototype(auction->itemTemplate);

        if (!proto)
            continue;

        if(!proto->Name1)
            continue;
        
        if (!strstri(proto->Name1, text.c_str()))
            continue;

        if (price && auction->bid + 5 > price)
            continue;

        uint32 cost = std::min(auction->buyout, uint32(std::max(auction->bid, auction->startbid) * frand(1.05f, 1.25f)));

        uint32 power = auction->itemCount;
        power *= 1000;
        power /= cost;

        auctionPowers.push_back(make_pair(auction, power));
    }

    if (auctionPowers.empty())
        return false;

    std::sort(auctionPowers.begin(), auctionPowers.end(), [](std::pair<AuctionEntry*, uint32> i, std::pair<AuctionEntry*, uint32> j) {return i > j; });

    auction = auctionPowers.begin()->first;

    uint32 cost = std::min(auction->buyout, uint32(std::max(auction->bid, auction->startbid) * frand(1.05f, 1.25f)));

    return BidItem(auction, cost, auctioneer);
}

bool AhBidAction::BidItem(AuctionEntry* auction, uint32 price, Unit* auctioneer)
{
    WorldPacket packet;
    packet << auctioneer->GetObjectGuid();
    packet << auction->Id;
    packet << price;

    uint32 oldMoney = bot->GetMoney();

    bot->GetSession()->HandleAuctionPlaceBid(packet);

    if (bot->GetMoney() < oldMoney)
    {
        ItemPrototype const* proto = sObjectMgr.GetItemPrototype(auction->itemTemplate);
        ostringstream out;
        ItemQualifier itemQualifier(auction);
        out << "Bidding " << ChatHelper::formatMoney(price) << " on " << ChatHelper::formatItem(itemQualifier, auction->itemCount) << " on the AH";
        ai->TellMasterNoFacing(out.str(), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        return true;
    }
    return false;
}
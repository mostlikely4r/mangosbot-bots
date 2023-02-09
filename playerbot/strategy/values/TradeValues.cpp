#include "botpch.h"
#include "../../playerbot.h"
#include "TradeValues.h"
#include "ItemUsageValue.h"
#include "../../TravelMgr.h"

using namespace ai;

bool ItemsUsefulToGiveValue::IsTradingItem(uint32 entry)
{
    TradeData* trade = bot->GetTradeData();

    if (!trade)
        return false;

    for (uint8 i = 0; i < TRADE_SLOT_TRADED_COUNT; i++)
    {
        Item* tradeItem = trade->GetItem(TradeSlots(i));

        if (tradeItem && tradeItem->GetEntry() == entry)
            return true;;
    }

    return false;
}

list<Item*> ItemsUsefulToGiveValue::Calculate()
{
    GuidPosition guidP = AI_VALUE(GuidPosition, "rpg target");
    
    Player* player = guidP.GetPlayer();

    list<Item*> giveItems;

    if (ai->HasActivePlayerMaster() || !player->GetPlayerbotAI())
        return giveItems;

    list<ItemUsage> myUsages = { ITEM_USAGE_NONE , ITEM_USAGE_VENDOR, ITEM_USAGE_AH, ITEM_USAGE_DISENCHANT };

    for (auto& myUsage : myUsages)
    {
        list<Item*> myItems = AI_VALUE2(list<Item*>, "inventory items", "usage " + to_string(myUsage));
        myItems.reverse();

        for (auto& item : myItems)
        {
            if (!item->CanBeTraded())
                continue;

            TradeData* trade = bot->GetTradeData();

            if (trade)
            {

                if (trade->HasItem(item->GetObjectGuid())) //This specific item isn't being traded.
                    continue;

                if (IsTradingItem(item->GetEntry())) //A simular item isn't being traded.
                    continue;

                if (std::any_of(giveItems.begin(), giveItems.end(), [item](Item* i) {return i->GetEntry() == item->GetEntry(); })) //We didn't already add a simular item to this list.
                    continue;
            }

            ItemUsage otherUsage = PAI_VALUE2(ItemUsage, "item usage", ItemQualifier(item).GetQualifier());

            if (std::find(myUsages.begin(), myUsages.end(), otherUsage) == myUsages.end())
                giveItems.push_back(item);
        }
    }

    return giveItems;
}

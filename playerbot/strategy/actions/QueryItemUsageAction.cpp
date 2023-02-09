#include "botpch.h"
#include "../../playerbot.h"
#include "QueryItemUsageAction.h"
#include "../../../ahbot/AhBot.h"
#include "../values/ItemUsageValue.h"
#include "../../RandomPlayerbotMgr.h"
#include "../../RandomItemMgr.h"

using namespace ai;

bool QueryItemUsageAction::Execute(Event& event)
{
    if (!GetMaster() && !sPlayerbotAIConfig.randomBotSayWithoutMaster)
        return false;

    WorldPacket& data = event.getPacket();
    if (!data.empty())
    {
        data.rpos(0);

        ObjectGuid guid;
        data >> guid;
        if (guid != bot->GetObjectGuid())
            return false;

        uint32 received, created, isShowChatMessage, slotId, itemId,suffixFactor, count;
        uint32 itemRandomPropertyId;
        //uint32 invCount;
        uint8 bagSlot;

        data >> received;                               // 0=looted, 1=from npc
        data >> created;                                // 0=received, 1=created
        data >> isShowChatMessage;                                      // IsShowChatMessage
        data >> bagSlot;
                                                                // item slot, but when added to stack: 0xFFFFFFFF
        data >> slotId;
        data >> itemId;
        data >> suffixFactor;
        data >> itemRandomPropertyId;
        data >> count;
        // data >> invCount; // [-ZERO] count of items in inventory

        ItemQualifier itemQualifier(itemId, (int32)itemRandomPropertyId);

        if (!itemQualifier.GetProto())
            return false;

        ai->TellMaster(QueryItem(itemQualifier, count, GetCount(itemQualifier)), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);

        if (sPlayerbotAIConfig.hasLog("bot_events.csv"))
        {
            if (event.getSource() == "item push result")
            {

                QuestStatusMap& questMap = bot->getQuestStatusMap();
                for (QuestStatusMap::const_iterator i = questMap.begin(); i != questMap.end(); i++)
                {
                    const Quest* questTemplate = sObjectMgr.GetQuestTemplate(i->first);
                    if (!questTemplate)
                        continue;

                    uint32 questId = questTemplate->GetQuestId();
                    QuestStatus status = bot->GetQuestStatus(questId);
                    if (status == QUEST_STATUS_INCOMPLETE || (status == QUEST_STATUS_COMPLETE && !bot->GetQuestRewardStatus(questId)))
                    {
                        QuestStatusData const& questStatus = i->second;
                        for (int i = 0; i < QUEST_OBJECTIVES_COUNT; i++)
                        {
                            if (questTemplate->ReqItemId[i] != itemId)
                                continue;

                            int required = questTemplate->ReqItemCount[i];
                            int available = questStatus.m_itemcount[i];

                            if (!required)
                                continue;

                            sPlayerbotAIConfig.logEvent(ai, "QueryItemUsageAction", questTemplate->GetTitle(), to_string((float)available / (float)required));
                        }
                    }
                }
            }
        }

        return true;
    }

    string text = event.getParam();
    set<string> qualifiers = chat->parseItemQualifiers(text);
    for (auto qualifier : qualifiers)
    {
        ItemQualifier itemQualifier(qualifier);
        if (!itemQualifier.GetProto()) continue;

        ai->TellMaster(QueryItem(itemQualifier, 0, GetCount(itemQualifier)), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
    }
    return true;
}

uint32 QueryItemUsageAction::GetCount(ItemQualifier& qualifier)
{
    uint32 total = 0;
    list<Item*> items = ai->InventoryParseItems(qualifier.GetProto()->Name1);
    if (!items.empty())
    {
        for (list<Item*>::iterator i = items.begin(); i != items.end(); ++i)
        {
            total += (*i)->GetCount();
        }
    }
    return total;
}

string QueryItemUsageAction::QueryItem(ItemQualifier& qualifier, uint32 count, uint32 total)
{
    ostringstream out;
#ifdef CMANGOS
    string usage = QueryItemUsage(qualifier);
#endif
#ifdef MANGOS
    bool usage = QueryItemUsage(item);
#endif
    string quest = QueryQuestItem(qualifier.GetId());
    string price = QueryItemPrice(qualifier);
    string power = QueryItemPower(qualifier);
#ifdef CMANGOS
    if (usage.empty())
#endif
#ifdef MANGOS
    if (!usage)
#endif
        usage = (quest.empty() ? "Useless" : "Quest");

    out << chat->formatItem(qualifier, count, total) << ": " << usage;
    if (!quest.empty())
        out << ", " << quest;
    if (!price.empty())
        out << ", " << price;
    if (!power.empty())
        out << ", " << power;
    return out.str();
}

string QueryItemUsageAction::QueryItemUsage(ItemQualifier& qualifier)
{
    ItemUsage usage = AI_VALUE2(ItemUsage, "item usage", qualifier.GetQualifier());
    switch (usage)
    {
    case ITEM_USAGE_EQUIP:
        return "Equip";
    case ITEM_USAGE_REPLACE:
        return "Equip (replace)";
    case ITEM_USAGE_BAD_EQUIP:
        return "Equip (temporary)";
    case ITEM_USAGE_BROKEN_EQUIP:
        return "Broken Equip";
    case ITEM_USAGE_QUEST:
        return "Quest (other)";
    case ITEM_USAGE_SKILL:
        return "Tradeskill";
    case ITEM_USAGE_USE:
        return "Use";
	case ITEM_USAGE_GUILD_TASK:
		return "Guild task";
	case ITEM_USAGE_DISENCHANT:
		return "Disenchant";
    case ITEM_USAGE_VENDOR:
        return "Vendor";
    case ITEM_USAGE_AH:
        return "Auctionhouse";
    case ITEM_USAGE_AMMO:
        return "Ammunition";
	}

    return "";
}

string QueryItemUsageAction::QueryItemPrice(ItemQualifier& qualifier)
{
    if (!sRandomPlayerbotMgr.IsRandomBot(bot))
        return "";

    if (qualifier.GetProto()->Bonding == BIND_WHEN_PICKED_UP)
        return "";

    ostringstream msg;
    list<Item*> items = ai->InventoryParseItems(qualifier.GetProto()->Name1);
    int32 sellPrice = 0;
    if (!items.empty())
    {
        for (list<Item*>::iterator i = items.begin(); i != items.end(); ++i)
        {
            Item* sell = *i;
            sellPrice += sell->GetCount() * auctionbot.GetSellPrice(sell->GetProto()) * sRandomPlayerbotMgr.GetSellMultiplier(bot);
        }

        if(sellPrice)
            msg << "Sell: " << chat->formatMoney(sellPrice);
    }

    ItemUsage usage = AI_VALUE2(ItemUsage, "item usage", qualifier.GetQualifier());
    if (usage == ITEM_USAGE_NONE)
        return msg.str();

    int32 buyPrice = auctionbot.GetBuyPrice(qualifier.GetProto()) * sRandomPlayerbotMgr.GetBuyMultiplier(bot);
    if (buyPrice)
    {
        if (sellPrice) msg << " ";
        msg << "Buy: " << chat->formatMoney(buyPrice);
    }

    return msg.str();
}

string QueryItemUsageAction::QueryQuestItem(uint32 itemId)
{
    Player *bot = ai->GetBot();
    QuestStatusMap& questMap = bot->getQuestStatusMap();
    for (QuestStatusMap::const_iterator i = questMap.begin(); i != questMap.end(); i++)
    {
        const Quest *questTemplate = sObjectMgr.GetQuestTemplate( i->first );
        if( !questTemplate )
            continue;

        uint32 questId = questTemplate->GetQuestId();
        QuestStatus status = bot->GetQuestStatus(questId);
        if (status == QUEST_STATUS_INCOMPLETE || (status == QUEST_STATUS_COMPLETE && !bot->GetQuestRewardStatus(questId)))
        {
            QuestStatusData const& questStatus = i->second;
            string usage = QueryQuestItem(itemId, questTemplate, &questStatus);
            if (!usage.empty()) return usage;
        }
    }

    return "";
}


string QueryItemUsageAction::QueryQuestItem(uint32 itemId, const Quest *questTemplate, const QuestStatusData *questStatus)
{
    for (int i = 0; i < QUEST_OBJECTIVES_COUNT; i++)
    {
        if (questTemplate->ReqItemId[i] != itemId)
            continue;

        int required = questTemplate->ReqItemCount[i];
        int available = questStatus->m_itemcount[i];

        if (!required)
            continue;

        return chat->formatQuestObjective(chat->formatQuest(questTemplate), available, required);
    }

    return "";
}

string QueryItemUsageAction::QueryItemPower(ItemQualifier& qualifier)
{
    uint32 power = sRandomItemMgr.ItemStatWeight(bot, qualifier);

    ItemPrototype const* proto = ObjectMgr::GetItemPrototype(qualifier.GetId());

    if (power)
    {
        ostringstream out;
        char color[32];
        sprintf(color, "%x", ItemQualityColors[qualifier.GetProto()->Quality]);
        out << "power: |h|c" << color << "|h" << to_string(power) << "|h|cffffffff";
        return out.str().c_str();
    }

    return "";
}
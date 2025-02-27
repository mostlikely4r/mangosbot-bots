#include "botpch.h"
#include "../../playerbot.h"
#include "DestroyItemAction.h"
#include "../values/ItemCountValue.h"

using namespace ai;

bool DestroyItemAction::Execute(Event& event)
{
    string text = event.getParam();
    ItemIds ids = chat->parseItems(text);

    for (ItemIds::iterator i =ids.begin(); i != ids.end(); i++)
    {
        FindItemByIdVisitor visitor(*i);
        DestroyItem(&visitor);
    }

    return true;
}

void DestroyItemAction::DestroyItem(FindItemVisitor* visitor)
{
    ai->InventoryIterateItems(visitor);
    list<Item*> items = visitor->GetResult();
	for (list<Item*>::iterator i = items.begin(); i != items.end(); ++i)
    {
		Item* item = *i;
        ostringstream out; out << chat->formatItem(item) << " destroyed";
        bot->DestroyItem(item->GetBagSlot(),item->GetSlot(), true);
        ai->TellMaster(out, PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
    }
}

bool SmartDestroyItemAction::Execute(Event& event)
{
    uint8 bagSpace = AI_VALUE(uint8, "bag space");

    if (bagSpace < 90)
        return false;

    // only destroy grey items if with real player/guild
    if (ai->HasRealPlayerMaster() || ai->IsInRealGuild())
    {
        set<Item*> items;
        FindItemsToTradeByQualityVisitor visitor(ITEM_QUALITY_POOR, 5);
        ai->InventoryIterateItems(&visitor, ITERATE_ITEMS_IN_BAGS);
        items.insert(visitor.GetResult().begin(), visitor.GetResult().end());

        for (auto& item : items)
        {
            if (AI_VALUE2(ForceItemUsage, "force item usage", item->GetProto()->ItemId) != ForceItemUsage::FORCE_USAGE_NONE)
                continue;

            FindItemByIdVisitor visitor(item->GetProto()->ItemId);
            DestroyItem(&visitor);

            bagSpace = AI_VALUE(uint8, "bag space");

            if (bagSpace < 90)
                return true;
        }
        return true;
    }

    vector<uint32> bestToDestroy = { ITEM_USAGE_NONE }; //First destroy anything useless.

    if (!AI_VALUE(bool, "can sell") && AI_VALUE(bool, "should get money")) //We need money so quest items are less important since they can't directly be sold.
        bestToDestroy.push_back(ITEM_USAGE_QUEST);
    else //We don't need money so destroy the cheapest stuff.
    {
        bestToDestroy.push_back(ITEM_USAGE_VENDOR);
        bestToDestroy.push_back(ITEM_USAGE_AH);
    }

    //If we still need room 
    bestToDestroy.push_back(ITEM_USAGE_SKILL); //Items that might help tradeskill are more important than above but still expenable.
    bestToDestroy.push_back(ITEM_USAGE_USE); //These are more likely to be usefull 'soon' but still expenable.

    for (auto& usage : bestToDestroy)
    {

        list<uint32> items = AI_VALUE2(list<uint32>, "inventory item ids", "usage " + to_string(usage));

        items.reverse();

        for (auto& item : items)
        {
            if (AI_VALUE2(ForceItemUsage, "force item usage", item) != ForceItemUsage::FORCE_USAGE_NONE)
                continue;

            FindItemByIdVisitor visitor(item);
            DestroyItem(&visitor);

            bagSpace = AI_VALUE(uint8, "bag space");

            if(bagSpace < 90)
                return true;
        }
    }

    return false;
}
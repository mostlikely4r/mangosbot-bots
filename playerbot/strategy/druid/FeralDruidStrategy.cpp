#include "botpch.h"
#include "../../playerbot.h"
#include "FeralDruidStrategy.h"

using namespace ai;

class FeralDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    FeralDruidStrategyActionNodeFactory()
    {
        creators["survival instincts"] = &survival_instincts;
        creators["thorns"] = &thorns;
        creators["omen of clarity"] = &omen_of_clarity;
        creators["cure poison"] = &cure_poison;
        creators["cure poison on party"] = &cure_poison_on_party;
        creators["abolish poison"] = &abolish_poison;
        creators["abolish poison on party"] = &abolish_poison_on_party;
    }
private:
    static ActionNode* survival_instincts(PlayerbotAI* ai)
    {
        return new ActionNode ("survival instincts",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("barskin"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* thorns(PlayerbotAI* ai)
    {
        return new ActionNode ("thorns",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* omen_of_clarity(PlayerbotAI* ai)
    {
        return new ActionNode ("omen of clarity",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* cure_poison(PlayerbotAI* ai)
    {
        return new ActionNode ("cure poison",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* cure_poison_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("cure poison on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* abolish_poison(PlayerbotAI* ai)
    {
        return new ActionNode ("abolish poison",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* abolish_poison_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("abolish poison on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
};

FeralDruidStrategy::FeralDruidStrategy(PlayerbotAI* ai) : GenericDruidStrategy(ai)
{
    actionNodeFactories.Add(new FeralDruidStrategyActionNodeFactory());
    actionNodeFactories.Add(new ShapeshiftDruidStrategyActionNodeFactory());
}

NextAction** FeralDruidStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0,
        new NextAction("faerie fire", ACTION_NORMAL + 1),
        new NextAction("melee", ACTION_NORMAL),
        NULL);
}

void FeralDruidStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDruidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy too close for melee",
        NextAction::array(0, new NextAction("move out of enemy contact", ACTION_NORMAL + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("survival instincts", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "omen of clarity",
        NextAction::array(0, new NextAction("omen of clarity", 66.0f), NULL))); //High priority to avoid going back to cat form.
}
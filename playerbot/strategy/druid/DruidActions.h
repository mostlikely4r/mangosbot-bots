#pragma once

#include "../actions/GenericActions.h"
#include "DruidShapeshiftActions.h"
#include "DruidBearActions.h"
#include "DruidCatActions.h"

namespace ai
{
	class CastFaerieFireAction : public CastRangedDebuffSpellAction
	{
	public:
		CastFaerieFireAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "faerie fire") {}
	};

    class CastFaerieFireFeralAction : public CastRangedDebuffSpellAction
    {
    public:
        CastFaerieFireFeralAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "faerie fire (feral)") {}
    };

	class CastRejuvenationAction : public CastHealingSpellAction 
	{
	public:
		CastRejuvenationAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "rejuvenation") {}
	};

	class CastRegrowthAction : public CastHealingSpellAction 
	{
	public:
		CastRegrowthAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "regrowth") {}
	};

    class CastHealingTouchAction : public CastHealingSpellAction 
	{
    public:
        CastHealingTouchAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "healing touch") {}
    };

    class CastRejuvenationOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRejuvenationOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "rejuvenation") {}
    };

    class CastRegrowthOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRegrowthOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "regrowth") {}
    };

    class CastHealingTouchOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealingTouchOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "healing touch") {}
    };

	class CastReviveAction : public ResurrectPartyMemberAction
	{
	public:
		CastReviveAction(PlayerbotAI* ai) : ResurrectPartyMemberAction(ai, "revive") {}

		virtual NextAction** getPrerequisites() 
		{
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), ResurrectPartyMemberAction::getPrerequisites());
		}
	};

	class CastRebirthAction : public ResurrectPartyMemberAction
	{
	public:
		CastRebirthAction(PlayerbotAI* ai) : ResurrectPartyMemberAction(ai, "rebirth") {}

		virtual NextAction** getPrerequisites() 
		{
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), ResurrectPartyMemberAction::getPrerequisites());
		}
	};

	BUFF_ACTION(CastMarkOfTheWildAction, "mark of the wild");
	BUFF_PARTY_ACTION(CastMarkOfTheWildOnPartyAction, "mark of the wild");
	BUFF_PARTY_ACTION(CastGiftOfTheWildOnPartyAction, "gift of the wild");

	class CastSurvivalInstinctsAction : public CastBuffSpellAction 
	{
	public:
		CastSurvivalInstinctsAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "survival instincts") {}
	};

	class CastThornsAction : public CastBuffSpellAction 
	{
	public:
		CastThornsAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "thorns") {}
	};

    class CastThornsOnPartyAction : public BuffOnPartyAction 
	{
    public:
        CastThornsOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "thorns") {}
    };

	class CastOmenOfClarityAction : public CastBuffSpellAction 
	{
	public:
	    CastOmenOfClarityAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "omen of clarity") {}
		virtual bool isUseful() override { return CastBuffSpellAction::isUseful() && ai->HasSpell("omen of clarity"); }
	};

	class CastWrathAction : public CastSpellAction
	{
	public:
		CastWrathAction(PlayerbotAI* ai) : CastSpellAction(ai, "wrath") {}
	};

	class CastStarfallAction : public CastSpellAction
	{
	public:
		CastStarfallAction(PlayerbotAI* ai) : CastSpellAction(ai, "starfall") {}
	};

	class CastHurricaneAction : public CastSpellAction
	{
	public:
	    CastHurricaneAction(PlayerbotAI* ai) : CastSpellAction(ai, "hurricane") {}
	};

	class CastMoonfireAction : public CastRangedDebuffSpellAction
	{
	public:
		CastMoonfireAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "moonfire") {}
	};

	class CastInsectSwarmAction : public CastRangedDebuffSpellAction
	{
	public:
		CastInsectSwarmAction(PlayerbotAI* ai) : CastRangedDebuffSpellAction(ai, "insect swarm") {}
	};

	class CastStarfireAction : public CastSpellAction
	{
	public:
		CastStarfireAction(PlayerbotAI* ai) : CastSpellAction(ai, "starfire") {}
	};

	class CastEntanglingRootsAction : public CastSpellAction
	{
	public:
		CastEntanglingRootsAction(PlayerbotAI* ai) : CastSpellAction(ai, "entangling roots") {}
	};

    class CastEntanglingRootsCcAction : public CastCrowdControlSpellAction
    {
    public:
        CastEntanglingRootsCcAction(PlayerbotAI* ai) : CastCrowdControlSpellAction(ai, "entangling roots") {}
    };

	SNARE_ACTION(CastEntanglingRootsSnareAction, "entangling roots");

    class CastHibernateAction : public CastSpellAction
	{
	public:
        CastHibernateAction(PlayerbotAI* ai) : CastSpellAction(ai, "hibernate") {}
	};

    class CastHibernateCcAction : public CastSpellAction
    {
    public:
        CastHibernateCcAction(PlayerbotAI* ai) : CastSpellAction(ai, "hibernate on cc") {}
        virtual Value<Unit*>* GetTargetValue();
        virtual bool Execute(Event& event);
    };

    class CastNaturesGraspAction : public CastBuffSpellAction
	{
	public:
        CastNaturesGraspAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "nature's grasp") {}
	};

	class CastCurePoisonAction : public CastCureSpellAction
	{
	public:
		CastCurePoisonAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "cure poison") {}
	};

    class CastCurePoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCurePoisonOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cure poison", DISPEL_POISON) {}
    };

	class CastAbolishPoisonAction : public CastCureSpellAction
	{
	public:
		CastAbolishPoisonAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "abolish poison") {}
	};

    class CastAbolishPoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastAbolishPoisonOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "abolish poison", DISPEL_POISON) {}
    };

	CURE_ACTION(CastRemoveCurseAction, "remove curse");
	CURE_PARTY_ACTION(CastRemoveCurseOnPartyAction, "remove curse", DISPEL_CURSE);

    class CastBarskinAction : public CastBuffSpellAction
    {
    public:
        CastBarskinAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "barskin") {}
    };

    class CastInnervateAction : public CastSpellAction
    {
    public:
        CastInnervateAction(PlayerbotAI* ai) : CastSpellAction(ai, "innervate") {}
        virtual string GetTargetName() { return "self target"; }
    };

    class CastTranquilityAction : public CastAoeHealSpellAction
    {
    public:
        CastTranquilityAction(PlayerbotAI* ai) : CastAoeHealSpellAction(ai, "tranquility") {}
    };

    class CastNaturesSwiftnessAction : public CastBuffSpellAction
    {
    public:
        CastNaturesSwiftnessAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "nature's swiftness") {}
    };
}

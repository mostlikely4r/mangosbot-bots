#pragma once
#include "../Value.h"

namespace ai
{    
    class FreeMoveCenterValue : public CalculatedValue<GuidPosition>
	{
	public:
        FreeMoveCenterValue(PlayerbotAI* ai) : CalculatedValue(ai, "free move center", 5) {};
        virtual GuidPosition Calculate() override;
    };   

    class FreeMoveRangeValue : public FloatCalculatedValue
    {
    public:
        FreeMoveRangeValue(PlayerbotAI* ai) : FloatCalculatedValue(ai, "free move range", 2) {};
        virtual float Calculate() override;
    };

    class CanFreeMoveToValue : public BoolCalculatedValue, public Qualified
    {
    public:
        CanFreeMoveToValue(PlayerbotAI* ai, string name = "can free move to") : BoolCalculatedValue(ai, name, 2) {};
        virtual bool Calculate() override;
    protected:
        virtual float GetRange() { return ai->HasStrategy("stay", BotState::BOT_STATE_NON_COMBAT) ? INTERACTION_DISTANCE : AI_VALUE(float, "free move range"); }
    };

    class CanFreeTargetValue : public CanFreeMoveToValue
    {
    public:
        CanFreeTargetValue(PlayerbotAI* ai) : CanFreeMoveToValue(ai, "can free target") {};
        virtual float GetRange() { return ai->HasStrategy("stay", BotState::BOT_STATE_NON_COMBAT) ? std::min(ai->GetRange("spell"), AI_VALUE(float, "free move range")) : AI_VALUE(float, "free move range"); }
    };
};


#pragma once
#include "PassTroughStrategy.h"

namespace ai
{
    class NonCombatStrategy : public Strategy
    {
    public:
        NonCombatStrategy(PlayerbotAI* ai) : Strategy(ai) {}
		virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }

    protected:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };

    class CollisionStrategy : public Strategy
    {
    public:
        CollisionStrategy(PlayerbotAI* ai) : Strategy(ai) {}
		int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        string getName() override { return "collision"; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };

    class MountStrategy : public Strategy
    {
    public:
        MountStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        string getName() override { return "mount"; }

    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class AttackTaggedStrategy : public Strategy
    {
    public:
        AttackTaggedStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        string getName() override { return "attack tagged"; }
    };
}

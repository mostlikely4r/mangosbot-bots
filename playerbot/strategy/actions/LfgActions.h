#pragma once
#include "MovementActions.h"
#include "AiFactory.h"
#include "PlayerbotAIConfig.h"
#include "../ItemVisitors.h"
#include "RandomPlayerbotMgr.h"
#ifdef MANGOSBOT_ZERO
#include "LFG/LFGMgr.h"
#endif
#ifdef MANGOSBOT_TWO
#include "LFG/LFGMgr.h"
#include "LFG/LFG.h"
#endif
#include "BattleGround.h"
#include "BattleGroundMgr.h"
#include "BattleGroundWS.h"
#include "ChooseTargetActions.h"
#include "CheckMountStateAction.h"
#include "G3D/Vector3.h"

namespace ai
{
    class LfgJoinAction : public Action
    {
    public:
        LfgJoinAction(PlayerbotAI* ai, string name = "lfg join") : Action(ai, name) {}
        virtual bool Execute(Event& event) override;
        virtual bool isUseful();

    protected:
        bool JoinLFG();
        bool SetRoles();
#ifdef MANGOSBOT_TWO
        LfgRoles GetRoles();
#endif
    };

    class LfgAcceptAction : public LfgJoinAction
    {
    public:
        LfgAcceptAction(PlayerbotAI* ai) : LfgJoinAction(ai, "lfg accept") {}
        virtual bool Execute(Event& event) override;
        virtual bool isUseful() { return true; }
    };

    class LfgRoleCheckAction : public LfgJoinAction
    {
    public:
        LfgRoleCheckAction(PlayerbotAI* ai) : LfgJoinAction(ai, "lfg role check") {}
        virtual bool Execute(Event& event) override;
        virtual bool isUseful() { return true; }
    };

    class LfgLeaveAction : public Action
    {
    public:
        LfgLeaveAction(PlayerbotAI* ai) : Action(ai, "lfg leave") {}
        virtual bool Execute(Event& event);
        virtual bool isUseful();
    };

    class LfgTeleportAction : public Action
    {
    public:
        LfgTeleportAction(PlayerbotAI* ai) : Action(ai, "lfg teleport") {}
        virtual bool Execute(Event& event);
    };
}

#pragma once
#include "GenericActions.h"

namespace ai
{
    class WhoAction : public ChatCommandAction 
    {
    public:
        WhoAction(PlayerbotAI* ai) : ChatCommandAction(ai, "who") {}
        virtual bool Execute(Event& event) override;

    private:
        string QueryTrade(string text);
        string QuerySkill(string text);
        string QuerySpec(string text);
    };
}

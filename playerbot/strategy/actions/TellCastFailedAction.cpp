#include "botpch.h"
#include "../../playerbot.h"
#include "TellCastFailedAction.h"
#include "../../ServerFacade.h"

using namespace ai;

bool TellCastFailedAction::Execute(Event& event)
{
    WorldPacket p(event.getPacket());
    p.rpos(0);
    uint8 castCount, result;
    uint32 spellId;
    p >> castCount >> spellId >> result;
    ai->SpellInterrupted(spellId);

    if (result == SPELL_CAST_OK)
        return false;

    const SpellEntry *const pSpellInfo =  sServerFacade.LookupSpellInfo(spellId);
    ostringstream out; out << chat->formatSpell(pSpellInfo) << ": ";
    switch (result)
    {
    case SPELL_FAILED_NOT_READY:
        out << "not ready";
        break;
    case SPELL_FAILED_REQUIRES_SPELL_FOCUS:
        out << "requires spell focus";
        break;
    case SPELL_FAILED_REQUIRES_AREA:
        out << "cannot cast here";
        break;
    case SPELL_FAILED_EQUIPPED_ITEM_CLASS:
        out << "requires item";
        break;
    case SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND:
    case SPELL_FAILED_EQUIPPED_ITEM_CLASS_OFFHAND:
        out << "requires weapon";
        break;
    case SPELL_FAILED_PREVENTED_BY_MECHANIC:
        out << "interrupted";
        break;
    default:
        out << "cannot cast";
    }
    int32 castTime = GetSpellCastTime(pSpellInfo
#ifdef CMANGOS
            , bot
#endif
    );
    if (castTime >= 2000)
        ai->TellError(out.str());
    return true;
}

bool TellSpellAction::Execute(Event& event)
{
    string spell = event.getParam();
    uint32 spellId = AI_VALUE2(uint32, "spell id", spell);
    if (!spellId)
        return false;

    SpellEntry const *spellInfo = sServerFacade.LookupSpellInfo(spellId );
    if (!spellInfo)
        return false;

    ostringstream out; out << chat->formatSpell(spellInfo);
    ai->TellError(out.str());
    return true;
}

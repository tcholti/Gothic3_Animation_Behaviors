#include "BadBlockProtectionResearch.h"

namespace BadBlockResearch
{
namespace
{
struct DiagnosticEpisodeState
{
    bool active = false;
    unsigned long ordinal = 0;
};

DiagnosticEpisodeState g_DiagnosticEpisode;

struct MatchFacts
{
    gEAction action;
    gEPhase phase;
    eCEntity *actorInstance;
    eCEntity *playerInstance;
};

bool TryMatchProtectedPlayerHit(
    GEU32 rawDuration,
    PSCharacterControl const *receiver,
    MatchFacts &facts)
{
    constexpr GEU32 timeoutMSecs = 2500;
    if (rawDuration <= timeoutMSecs || receiver == nullptr)
        return false;

    // The wrapper stores a property set, not an eCEntity pointer.
    eCEntityPropertySet *propertySet = receiver->m_pEngineEntityPropertySet;
    if (propertySet == nullptr)
        return false;

    eCEntity *actorInstance = propertySet->GetEntity();
    if (actorInstance == nullptr)
        return false;

    Entity const player = Entity::GetPlayer();
    eCEntity *playerInstance = player.GetInstance();
    if (actorInstance != playerInstance || !player.Routine.IsValid())
        return false;

    gEAction const action = player.Routine.Action;
    switch (action)
    {
        case gEAction_QuickAttackR:
        case gEAction_QuickAttackL:
        case gEAction_WhirlAttack:
            break;
        default:
            return false;
    }

    gEPhase const phase = player.GetCurrentAniPhase();
    if (phase != gEPhase_Hit)
        return false;

    facts.action = action;
    facts.phase = phase;
    facts.actorInstance = actorInstance;
    facts.playerInstance = playerInstance;
    return true;
}
}

GEU32 EvaluatePlayerHitTimeout(
    GEU32 rawDuration,
    PSCharacterControl const *receiver,
    FILE *log,
    bool protectionEnabled)
{
    constexpr GEU32 timeoutMSecs = 2500;
    MatchFacts facts = {};
    bool const qualifies =
        TryMatchProtectedPlayerHit(rawDuration, receiver, facts);

    // Diagnostic-only episode suppression. It does not decide protection,
    // extend protection, or alter the native timer. Any non-matching call
    // rearms the logger for the next qualifying window.
    if (!qualifies)
    {
        g_DiagnosticEpisode.active = false;
        return rawDuration;
    }

    GEU32 const effectiveDuration =
        protectionEnabled ? timeoutMSecs : rawDuration;

    if (!g_DiagnosticEpisode.active)
    {
        g_DiagnosticEpisode.active = true;
        ++g_DiagnosticEpisode.ordinal;

        if (log != nullptr)
        {
            std::fprintf(
                log,
                "Episode start id=%lu mode=%s raw=%lu effective=%lu action=%d phase=%d actor=%p player=%p\n",
                g_DiagnosticEpisode.ordinal,
                protectionEnabled ? "PROTECTION" : "CONTROL",
                static_cast<unsigned long>(rawDuration),
                static_cast<unsigned long>(effectiveDuration),
                static_cast<int>(facts.action),
                static_cast<int>(facts.phase),
                static_cast<void *>(facts.actorInstance),
                static_cast<void *>(facts.playerInstance));
            std::fflush(log);
        }
    }

    // Protection changes only this call's result. Native held-input time keeps
    // advancing. Control mode returns the native value unchanged.
    return effectiveDuration;
}
}

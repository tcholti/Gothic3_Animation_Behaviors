#include "BadBlockProtectionResearch.h"

namespace BadBlockResearch
{
GEU32 DeferPlayerHitTimeout(
    GEU32 rawDuration,
    PSCharacterControl const *receiver,
    FILE *log)
{
    constexpr GEU32 timeoutMSecs = 2500;
    if (rawDuration <= timeoutMSecs || receiver == nullptr)
        return rawDuration;

    // The wrapper stores a property set, not an eCEntity pointer.
    eCEntityPropertySet *propertySet = receiver->m_pEngineEntityPropertySet;
    if (propertySet == nullptr)
        return rawDuration;

    eCEntity *actorInstance = propertySet->GetEntity();
    if (actorInstance == nullptr)
        return rawDuration;

    Entity const player = Entity::GetPlayer();
    eCEntity *playerInstance = player.GetInstance();
    if (actorInstance != playerInstance || !player.Routine.IsValid())
        return rawDuration;

    gEAction const action = player.Routine.Action;
    switch (action)
    {
        case gEAction_QuickAttackR:
        case gEAction_QuickAttackL:
        case gEAction_WhirlAttack:
            break;
        default:
            return rawDuration;
    }

    gEPhase const phase = player.GetCurrentAniPhase();
    if (phase != gEPhase_Hit)
        return rawDuration;

    if (log != nullptr)
    {
        std::fprintf(
            log,
            "Clamp raw=%lu action=%d phase=%d actor=%p player=%p\n",
            static_cast<unsigned long>(rawDuration),
            static_cast<int>(action),
            static_cast<int>(phase),
            static_cast<void *>(actorInstance),
            static_cast<void *>(playerInstance));
        std::fflush(log);
    }

    // Only this call's result changes; native held-input time keeps advancing.
    return timeoutMSecs;
}
}

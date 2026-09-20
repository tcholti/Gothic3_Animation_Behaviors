#pragma once

#include "FrameCollisionShared.h"

namespace FrameCollision::Raw8FistWindowProbe
{
struct InvocationScope
{
    InvocationScope *previous;
    gCScriptProcessingUnit *spu;
    eCEntity *actorInstance;
    eCEntity *fistSourceInstance;
    std::uint64_t c1Generation;
    std::string animationName;
    GEInt action;
    bool c1GenerationValid;
    bool originSourceIsRaw8;
    bool syntheticAttemptObserved;
    bool exactNativeDamageObserved;
    GEU32 exactNativeDamageOrdinal;
};

void BeginInvocation(
    gCScriptProcessingUnit *spu, InvocationScope &scope);
void ObserveTimingResult(
    gCScriptProcessingUnit *spu, GEDouble realPlayTime,
    GEDouble returnedPlayTime);
void ObserveOnDamage(
    GEU32 ordinal, void *callerAddress,
    eCEntity *entityArgument1, eCEntity *entityArgument2);
void CompleteInvocation(
    InvocationScope &scope, GEBool combatMoveResult);
}

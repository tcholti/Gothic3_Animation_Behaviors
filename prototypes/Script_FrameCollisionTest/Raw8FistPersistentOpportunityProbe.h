#pragma once

#include "CollisionLifecycleGuard.h"
#include "FrameCollisionShared.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>

#include <cstdint>

namespace FrameCollision::Raw8FistPersistentOpportunityProbe
{
struct InvocationScope
{
    InvocationScope *previous;
    eCEntity *actorInstance;
    eCEntity *fistSourceInstance;
    gCScriptProcessingUnit *spu;
    std::uint64_t c1Generation;
    std::uint64_t tokenOrdinal;
    bool fullStop;
    bool contactConsumed;
    bool active;
};

void ObserveAcceptedMarker(
    Entity &actor, MarkerProcessResult const &result);

GEDouble ApplyTimingPersistence(
    gCScriptProcessingUnit *spu,
    eCWrapper_emfx2Actor *animationActor,
    eCWrapper_emfx2Actor::eEMotionType motionType,
    GEDouble realPlayTime, GEDouble permanentPlayTime);

void BeginCombatMoveInvocation(
    gCScriptProcessingUnit *spu, GEBool fullStop,
    InvocationScope &scope);
void CompleteCombatMoveInvocation(InvocationScope &scope);

void ObserveContactResolutionDispatch(
    void *callerAddress, eCEntity *entityArgument1,
    eCEntity *entityArgument2);

void CloseForFinalization(
    CollisionLifecycleGuard::GenerationToken const &generation);
}

#pragma once

#include "CollisionLifecycleGuard.h"
#include "FrameCollisionShared.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>

#include <cstdint>

namespace FrameCollision::FrameCollisionMarkers
{
struct AttackCallbackOwnershipResult;
}

namespace FrameCollision::Raw8FistCollision
{
struct InvocationScope
{
    InvocationScope *previous;
    eCEntity *actorInstance;
    eCEntity *fistSourceInstance;
    gCScriptProcessingUnit *spu;
    std::uint64_t c1Generation;
    std::uint64_t opportunityOrdinal;
    bool fullStop;
    bool contactConsumed;
    bool active;
};

bool IsSupportedFamily(AttackFamily family);

void UpdateMarkerOwnership(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership,
    gCScriptProcessingUnit *spu);
void ApplyAcceptedMarkerLatch(
    Entity &actor, MarkerProcessResult &result);
void UpdateTimingPermissionFromMarker(
    Entity &actor, MarkerProcessResult const &result);
GEDouble ApplyTimingPermission(
    gCScriptProcessingUnit *spu,
    eCWrapper_emfx2Actor *animationActor,
    eCWrapper_emfx2Actor::eEMotionType motionType,
    GEDouble realPlayTime);

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

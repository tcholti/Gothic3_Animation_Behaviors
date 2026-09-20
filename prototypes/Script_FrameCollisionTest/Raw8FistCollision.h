#pragma once

#include "FrameCollisionShared.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>

namespace FrameCollision::FrameCollisionMarkers
{
struct AttackCallbackOwnershipResult;
}

namespace FrameCollision::Raw8FistCollision
{
bool IsSupportedFamily(AttackFamily family);

#ifdef FRAME_COLLISION_DIAGNOSTICS
struct PostAttemptObservationScope
{
    PostAttemptObservationScope *previous;
    gCScriptProcessingUnit *spu;
    eCEntity *actorInstance;
    eCEntity *fistSourceInstance;
    std::uint64_t c1Generation;
    GEInt action;
    std::string animationName;
    bool permissionConsumed;
    bool syntheticApplied;
    GEU32 firstOnDamageOrdinal;
    GEU32 lastOnDamageOrdinal;
    GEU32 onDamageCount;
};

void BeginPostAttemptObservation(
    gCScriptProcessingUnit *spu, PostAttemptObservationScope &scope);
void ObservePostAttemptOnDamageEntry(GEU32 ordinal);
void CompletePostAttemptObservation(
    PostAttemptObservationScope &scope, GEBool combatMoveResult);
#endif

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
}

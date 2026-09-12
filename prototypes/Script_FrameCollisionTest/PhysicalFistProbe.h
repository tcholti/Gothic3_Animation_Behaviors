#pragma once

#include "FrameCollisionMarkers.h"

#include <cstdint>
#include <string>

namespace FrameCollision::PhysicalFistProbe
{
struct QuickCallbackObservation
{
    bool active;
    eCEntity *actorInstance;
    eCEntity *rightSourceInstance;
    std::uint64_t c1Generation;
    GEInt actionBefore;
    GEInt phaseBefore;
    GEFloat stateTimeBefore;
    GEInt statePositionBefore;
    GEInt rightGroupBefore;
    std::string motionBefore;
};

bool ShouldSuppressNativeCallback(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership,
    gCScriptProcessingUnit *spu);

QuickCallbackObservation BeginQuickCallbackObservation(
    Entity &actor, gCScriptProcessingUnit *spu);

void EndQuickCallbackObservation(
    Entity &actor, QuickCallbackObservation const &observation,
    GEBool nativeResult);
}

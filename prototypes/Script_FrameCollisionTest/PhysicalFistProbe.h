#pragma once

#include "FrameCollisionMarkers.h"

#include <cstdint>
#include <string>

namespace FrameCollision::PhysicalFistProbe
{
struct QuickCallbackObservation
{
    bool active;
    QuickCallbackObservation *previousScope;
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

void BeginQuickCallbackObservation(
    Entity &actor, gCScriptProcessingUnit *spu,
    QuickCallbackObservation &observation);

bool ShouldSuppressCollisionGroupRequest(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup);

void EndQuickCallbackObservation(
    Entity &actor, QuickCallbackObservation &observation,
    GEBool nativeResult);
}

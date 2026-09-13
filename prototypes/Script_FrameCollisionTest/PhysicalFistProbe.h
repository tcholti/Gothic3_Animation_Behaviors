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

struct NormalCallbackObservation
{
    bool active;
    NormalCallbackObservation *previousScope;
    eCEntity *actorInstance;
    eCEntity *rightSourceInstance;
    std::uint64_t c1Generation;
    GEInt actionBefore;
    GEInt phaseBefore;
    GEFloat stateTimeBefore;
    GEInt statePositionBefore;
    GEInt rightUseTypeBefore;
    GEInt rightGroupBefore;
    std::string motionBefore;
    std::string rightNameBefore;
};

struct PowerCallbackObservation
{
    bool active;
    PowerCallbackObservation *previousScope;
    eCEntity *actorInstance;
    eCEntity *rightSourceInstance;
    std::uint64_t c1Generation;
    GEInt actionBefore;
    GEInt phaseBefore;
    GEFloat stateTimeBefore;
    GEInt statePositionBefore;
    GEInt rightUseTypeBefore;
    GEInt rightGroupBefore;
    std::string motionBefore;
    std::string rightNameBefore;
};

bool ShouldSuppressNativeCallback(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership,
    gCScriptProcessingUnit *spu);

void BeginQuickCallbackObservation(
    Entity &actor, gCScriptProcessingUnit *spu,
    QuickCallbackObservation &observation);

void BeginNormalCallbackObservation(
    Entity &actor, gCScriptProcessingUnit *spu,
    NormalCallbackObservation &observation);

void BeginPowerCallbackObservation(
    Entity &actor, gCScriptProcessingUnit *spu,
    PowerCallbackObservation &observation);

bool ShouldSuppressCollisionGroupRequest(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup);

void OnMarkerProcessed(
    Entity &actor, MarkerOpcode markerOpcode,
    MarkerProcessResult const &result);

void EndQuickCallbackObservation(
    Entity &actor, QuickCallbackObservation &observation,
    GEBool nativeResult);

void EndNormalCallbackObservation(
    Entity &actor, NormalCallbackObservation &observation,
    GEBool nativeResult);

void EndPowerCallbackObservation(
    Entity &actor, PowerCallbackObservation &observation,
    GEBool nativeResult);
}

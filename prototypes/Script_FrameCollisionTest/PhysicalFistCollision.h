#pragma once

#include "FrameCollisionMarkers.h"

#include <cstdint>

namespace FrameCollision::PhysicalFistCollision
{
struct NativeCallbackScope
{
    bool active;
    NativeCallbackScope *previousScope;
    eCEntity *actorInstance;
    eCEntity *rightSourceInstance;
    std::uint64_t c1Generation;
    AttackFamily family;
};

void BeginNativeCallbackScope(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &ownership,
    gCScriptProcessingUnit *spu, NativeCallbackScope &scope);
void EndNativeCallbackScope(NativeCallbackScope &scope);

bool ShouldSuppressCollisionGroupRequest(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup);
bool ShouldSuppressNormalNativeTriggerClear(
    eCTrigger_PS *trigger, void *callerAddress);

bool TryProcessMarker(
    Entity &actor, MarkerOpcode markerOpcode, char const *effectName,
    double elapsedMs, MarkerProcessResult &result);
}

#pragma once

#include "FrameCollisionShared.h"

namespace FrameCollision::FrameCollisionMarkers
{
struct AttackCallbackOwnershipResult
{
    bool attackHitEligible;
    bool suppressNativeCallback;
    bool controlledObservationAvailable;
    CurrentMotionMarkerResult decision;
    EquippedCollisionSources sources;
    ControlledCallbackObservation controlledObservation;
};

MarkerOpcode GetMarkerOpcode(char const *effectName);
char const *GetMarkerOpcodeName(MarkerOpcode opcode);
GEInt GetFirstAuthoredMarkerFrame(
    CurrentMotionMarkerResult const &decision, MarkerOpcode opcode);

bool IsAttackHit(Entity &actor, AttackFamily family);
CurrentMotionMarkerResult GetCurrentMarkerDecision(Entity &actor);
AttackCallbackOwnershipResult EvaluateAttackCallbackOwnership(
    Entity &actor, AttackFamily family);

MarkerProcessResult ProcessMarker(
    Entity &actor, MarkerOpcode markerOpcode, char const *effectName,
    double elapsedMs);

GEInt RetireMarkerOwnedSource(eCEntity *sourceInstance);
bool HasMarkerOwnedWindows();
bool TryGetMarkerOwnedWindow(
    eCEntity *actorInstance, MarkerOwnedWindowView &view);
}

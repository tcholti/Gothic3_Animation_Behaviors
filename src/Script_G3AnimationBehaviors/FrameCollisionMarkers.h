#pragma once

#include "FrameCollisionShared.h"

namespace FrameCollision::FrameCollisionMarkers
{
struct AttackCallbackOwnershipResult
{
    bool attackHitEligible;
    bool suppressNativeCallback;
    CurrentMotionMarkerResult decision;
    EquippedCollisionSources sources;
    eCEntity *fistSourceInstance;
};

MarkerOpcode GetMarkerOpcode(char const *effectName);
char const *GetMarkerOpcodeName(MarkerOpcode opcode);
GEInt GetFirstAuthoredMarkerFrame(
    CurrentMotionMarkerResult const &decision, MarkerOpcode opcode);

bool IsAttackHit(Entity &actor, AttackFamily family);
bool TryGetCurrentAttackHitFamily(
    Entity &actor, AttackFamily &family);
CurrentMotionMarkerResult GetCurrentMarkerDecision(Entity &actor);
AttackCallbackOwnershipResult EvaluateAttackCallbackOwnership(
    Entity &actor, AttackFamily family);

MarkerProcessResult ProcessMarker(
    Entity &actor, MarkerOpcode markerOpcode, char const *effectName,
    double elapsedMs, bool equippedSprintAuthorized);
MarkerProcessResult CreateMarkerResult(
    EquippedCollisionSources const &sources, MarkerOpcode opcode,
    char const *effectName, double elapsedMs);

void RetireFinalizedGeneration(
    eCEntity *actorInstance, std::uint64_t c1Generation);
GEInt RetireMarkerOwnedSource(eCEntity *sourceInstance);
bool HasMarkerOwnedWindows();
bool TryGetMarkerOwnedWindow(
    eCEntity *actorInstance, MarkerOwnedWindowView &view);
}

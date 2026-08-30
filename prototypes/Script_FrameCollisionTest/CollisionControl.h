#pragma once

#include "CollisionSources.h"
#include "FrameCollisionShared.h"

namespace FrameCollision::CollisionControl
{
// Transitional diagnostic aliases only. CollisionDiagnostics.cpp remains
// textually unchanged until its dedicated per-CPP/logger review; the helper
// implementations live exclusively in CollisionSources.
using CollisionSources::GetCollisionSourceUseType;
using CollisionSources::GetEquippedCollisionSources;
using CollisionSources::HasRequiredCollisionSources;

MarkerOpcode GetMarkerOpcode(char const *effectName);
char const *GetMarkerOpcodeName(MarkerOpcode opcode);
GEInt GetFirstAuthoredMarkerFrame(CurrentMotionMarkerResult const &decision, MarkerOpcode opcode);

bool IsAttackHit(Entity &actor, AttackFamily family);
CurrentMotionMarkerResult GetCurrentMarkerDecision(Entity &actor);

ControlledCallbackObservation ObserveControlledAttackCallback(
    Entity &actor, EquippedCollisionSources const &sources);

MarkerProcessResult ProcessMarker(Entity &actor, EquippedCollisionSources const &sources,
                                  MarkerOpcode markerOpcode, char const *effectName,
                                  double elapsedMs);

GEInt RetireMarkerOwnedSource(eCEntity *sourceInstance);
bool HasMarkerOwnedWindows();
bool TryGetMarkerOwnedWindow(eCEntity *actorInstance, MarkerOwnedWindowView &view);
}

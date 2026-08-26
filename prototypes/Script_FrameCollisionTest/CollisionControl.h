#pragma once

#include "FrameCollisionShared.h"

namespace FrameCollision::CollisionControl
{
MarkerOpcode GetMarkerOpcode(char const *effectName);
char const *GetMarkerOpcodeName(MarkerOpcode opcode);
GEInt GetFirstAuthoredMarkerFrame(CurrentMotionMarkerResult const &decision, MarkerOpcode opcode);

bool IsAttackHit(Entity &actor, AttackFamily family);
EquippedCollisionSources GetEquippedCollisionSources(Entity &actor);
gEUseType GetCollisionSourceUseType(Entity &source);
bool HasRequiredCollisionSources(EquippedCollisionSources const &sources, unsigned int requiredMask);
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

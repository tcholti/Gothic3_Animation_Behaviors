#pragma once

#include "FrameCollisionShared.h"

#include <cstdio>

class eCVisualAnimation_PS;

namespace FrameCollision::CollisionDiagnostics
{
struct PrimaryMotionEventSnapshot
{
    GEDouble elapsedMilliseconds;
    PrimaryMotionLifetimeSnapshot primary;
};

void OpenLog();
void CloseLog();
bool IsLogOpen();
FILE *GetLog();

bool ShouldLogOwnership(Entity &actor);
void LogOwnershipDecision(Entity &actor, CurrentMotionMarkerResult const &decision,
                          EquippedCollisionSources const &sources, bool willSuppress);
void LogControlledCallbackBoundary(Entity &actor,
                                   ControlledCallbackObservation const &observation);
void LogNullMarker(char const *markerName);
void LogMarkerContext(char const *markerName, MarkerOpcode opcode, Entity &actor,
                      EquippedCollisionSources const &sources);
void LogMarkerResult(MarkerProcessResult const &result);
void LogSetCollisionGroup(eCEntity *changedEntity, eECollisionGroup requestedGroup,
                          eECollisionGroup beforeGroup, eECollisionGroup afterGroup,
                          GEInt retiredMarkerExecutionCount);
PrimaryMotionEventSnapshot CapturePrimaryMotionEventSnapshot(
    eCVisualAnimation_PS *animationPS);
PrimaryMotionEventSnapshot CapturePrimaryMotionEventSnapshot(Entity &actor);
void LogOriginalAttackCallbackBoundary(Entity &actor,
                                       char const *callbackFamily,
                                       char const *boundary);
void LogPrimaryMotionEvent(eCVisualAnimation_PS *animationPS,
                           char const *operation,
                           PrimaryMotionEventSnapshot const &before,
                           PrimaryMotionEventSnapshot const &after);
void ObserveMarkerOwnedLifetimeOnTick(Entity &actor, MarkerOwnedWindowView const &window);
void ResetMarkerOwnedLifetime(eCEntity *actorInstance);
void ForgetMarkerOwnedLifetime(eCEntity *actorInstance);
}

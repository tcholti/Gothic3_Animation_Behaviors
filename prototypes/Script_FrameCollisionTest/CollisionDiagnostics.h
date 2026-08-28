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

enum { NativeCleanupStackCapacity = 16 };

struct NativeCleanupStackSnapshot
{
    void *frames[NativeCleanupStackCapacity];
    unsigned short frameCount;
};

struct HitReplacementSourceSnapshot
{
    bool resolved;
    std::string name;
    void *address;
    GEInt collisionGroup;
};

struct HitReplacementStackSnapshot
{
    GEDouble elapsedMilliseconds;
    std::string outgoingMotionName;
    std::string movementName;
    GEInt action;
    GEInt phase;
    GEFloat stateTime;
    void *incomingRequestAddress;
    HitReplacementSourceSnapshot leftSource;
    HitReplacementSourceSnapshot rightSource;
    void *frames[NativeCleanupStackCapacity];
    unsigned short frameCount;
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
                          GEInt retiredMarkerExecutionCount,
                          void *callerAddress,
                          NativeCleanupStackSnapshot const &cleanupStack);
PrimaryMotionEventSnapshot CapturePrimaryMotionEventSnapshot(
    eCVisualAnimation_PS *animationPS);
PrimaryMotionEventSnapshot CapturePrimaryMotionEventSnapshot(Entity &actor);
bool IsAttackHitPrimaryMotion(PrimaryMotionEventSnapshot const &snapshot);
void CaptureHitReplacementContext(Entity &actor, void *incomingRequestAddress,
                                  HitReplacementStackSnapshot &snapshot);
void LogHitReplacementStack(Entity &actor,
                            HitReplacementStackSnapshot const &replacement,
                            PrimaryMotionEventSnapshot const &incoming);
void LogHitStopStack(Entity &actor,
                     HitReplacementStackSnapshot const &stop,
                     GEFloat blendTime);
void LogHitStartRecoverBeginStack(
    Entity &actor, HitReplacementStackSnapshot const &startRecover);
void LogCombatMoveStartRecoverBoundary(Entity &actor,
                                         char const *boundary);
void LogPrimaryMotionEvent(eCVisualAnimation_PS *animationPS,
                           char const *operation,
                           PrimaryMotionEventSnapshot const &before,
                           PrimaryMotionEventSnapshot const &after);
void ObserveMarkerOwnedLifetimeOnTick(Entity &actor, MarkerOwnedWindowView const &window);
void ResetMarkerOwnedLifetime(eCEntity *actorInstance);
void ForgetMarkerOwnedLifetime(eCEntity *actorInstance);
}

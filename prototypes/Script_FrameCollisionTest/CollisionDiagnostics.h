#pragma once

#include "CollisionLifecycleGuard.h"
#include "FrameCollisionMarkers.h"

#include <cstdio>

namespace FrameCollision::CollisionDiagnostics
{
void OpenLog();
void CloseLog();
bool IsLogOpen();
FILE *GetLog();

void LogAttackCallbackOwnership(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &result);
void LogNullMarker(char const *markerName);
void LogMarkerContext(Entity &actor, MarkerOpcode opcode);
void LogMarkerResult(Entity &actor, MarkerProcessResult const &result);
void LogSetCollisionGroup(
    eCEntity *changedEntity, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup, eECollisionGroup afterGroup,
    GEInt retiredMarkerExecutionCount);

void LogBeginCombatMoveResult(
    CollisionLifecycleGuard::BeginCombatMoveResult const &result);
void LogCompleteCombatMoveResult(
    CollisionLifecycleGuard::CompleteCombatMoveResult const &result);
void LogCollisionObservationResult(
    CollisionLifecycleGuard::CollisionObservationResult const &result);
void LogBridgeRetirementResult(
    CollisionLifecycleGuard::BridgeRetirementResult const &result);
void LogFinalizationResult(
    CollisionLifecycleGuard::FinalizationResult const &result);
void LogRunScriptFunctionScopeReturn(
    void *scopeAddress, bool parentScopeExists, GEBool nativeResult);
}

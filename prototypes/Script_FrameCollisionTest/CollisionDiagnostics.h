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
void LogFistTriggerStateSnapshot(char const *boundary, Entity &actor);
void LogFistCanBeActivatedNow(
    char const *boundary, Entity &actor, eCEntity *fistSourceInstance,
    gCTouchDamage_PS *touchDamagePS, eCEntity *entityArgument,
    void *contactIteratorAddress, bool nativeResultAvailable,
    GEBool nativeResult);
void LogFistTriggerTarget(
    char const *boundary, Entity &actor, eCEntity *fistSourceInstance,
    gCTouchDamage_PS *touchDamagePS, eCEntity *entityArgument1,
    eCEntity *entityArgument2, void *contactIteratorAddress);
void LogFistHookEntry(
    char const *hookKind, GEU32 ordinal, gCTouchDamage_PS *touchDamagePS,
    Entity &player, eCEntity *resolverSourceInstance,
    bool exactTouchDamageIdentityMatch);
void LogFistHookEntryCap(char const *hookKind, GEU32 cap);
void LogNullMarker(char const *markerName);
void LogMarkerContext(Entity &actor, MarkerOpcode opcode);
void LogMarkerResult(Entity &actor, MarkerProcessResult const &result);
void LogSetCollisionGroup(
    eCEntity *changedEntity, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup, eECollisionGroup afterGroup,
    GEInt retiredMarkerSourceBitCount);

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

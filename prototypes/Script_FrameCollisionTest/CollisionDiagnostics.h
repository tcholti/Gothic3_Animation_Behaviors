#pragma once

#include "CollisionLifecycleGuard.h"
#include "FrameCollisionMarkers.h"

#include <cstdint>
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
#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
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
#endif
void LogEntityOnDamageEntry(
    GEU32 ordinal, void *callerAddress, gCEntity *thisEntity,
    eCEntity *entityArgument1, eCEntity *entityArgument2,
    GEInt integerArgument1, GEInt integerArgument2,
    void *contactIteratorAddress);
void LogEntityOnDamageEntryCap(GEU32 cap);
void LogRaw8FistMarkerOwnership(
    Entity &actor, AttackFamily family, std::uint64_t c1Generation,
    eCEntity *fistSourceInstance, gCScriptProcessingUnit *spu,
    void *animationActorAddress,
    GEInt latchBefore, GEInt latchAfter, bool writeConfirmed);
void LogRaw8FistMarkerOpportunity(
    Entity &actor, MarkerProcessResult const &result,
    void *animationActorAddress, bool timingAvailable,
    GEDouble realPlayTime, GEDouble maxTime,
    GEDouble nativeThresholdConstant, GEDouble computedThreshold,
    bool realBelowThreshold, bool ownershipMatched,
    bool timingPermissionArmed);
void LogRaw8FistTimingPermissionConsumed(
    eCEntity *actorInstance, std::uint64_t c1Generation,
    gCScriptProcessingUnit *hookSPU, void *hookAnimationActorAddress,
    GEInt motionType, GEDouble realPlayTime, GEDouble maxTime,
    GEDouble nativeThresholdConstant, GEDouble computedThreshold,
    GEDouble returnedPlayTime, bool syntheticApplied);
void LogRaw8FistTimingPermissionRetired(
    eCEntity *actorInstance, std::uint64_t c1Generation,
    gCScriptProcessingUnit *spu, void *animationActorAddress,
    char const *reason);
void LogNullMarker(char const *markerName);
void LogMarkerResult(Entity &actor, MarkerProcessResult const &result);
void LogSetCollisionGroup(
    eCEntity *changedEntity, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup, eECollisionGroup afterGroup,
    GEInt retiredMarkerSourceBitCount,
    CollisionLifecycleGuard::CollisionObservationResult const &observation);

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
#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
void LogRunScriptFunctionScopeReturn(
    void *scopeAddress, bool parentScopeExists, GEBool nativeResult);
#endif
}

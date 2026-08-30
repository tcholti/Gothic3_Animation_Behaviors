#pragma once

#include "FrameCollisionShared.h"

#include <cstdint>
#include <string>

namespace FrameCollision::CollisionLifecycleGuard
{
enum GenerationStatus
{
    GenerationStatus_Candidate,
    GenerationStatus_Persisted,
    GenerationStatus_OuterBound
};

struct GenerationToken
{
    eCEntity *actorInstance;
    std::uint64_t generation;
    bool valid;
    bool combatMoveCandidate;
};

struct PreCombatDispatchView
{
    gCScriptProcessingUnit *spu;
    bTObjStack<gScriptRunTimeSingleState> *runtimeStack;
    bCString const *scriptName;
};

struct PreCombatBridgeToken
{
    eCEntity *actorInstance;
    std::uint64_t generation;
    bool active;
    bool consumed;
};

enum LifecycleIssueCode
{
    LifecycleIssue_None,
    LifecycleIssue_OverlapOutstanding,
    LifecycleIssue_CandidateGenerationChanged,
    LifecycleIssue_NullArgumentsCombatMove,
    LifecycleIssue_PreCombatBridgeCombatMoveMismatch,
    LifecycleIssue_NullArgumentsPreCombatOffense,
    LifecycleIssue_NonFunctionPreCombatOffense,
    LifecycleIssue_LiveFrameMismatchPreCombatOffense,
    LifecycleIssue_PreCombatActorSourceOrBridgeOverlap,
    LifecycleIssue_PreCombatGenerationOverlap,
    LifecycleIssue_PreCombatGenerationFrameOverlap,
    LifecycleIssue_SourceAlreadyOwnedByOtherGeneration,
    LifecycleIssue_EquippedSourceRegistrationFailed,
    LifecycleIssue_UnownedPlayerOffenseRequest,
    LifecycleIssue_PreCombatBridgeUnconsumedAtDispatchReturn,
    LifecycleIssue_PreCombatBridgeRetirementMismatch,
    LifecycleIssue_FinalizationGenerationChanged
};

enum BindingEventCode
{
    BindingEvent_None,
    BindingEvent_CombatMoveCandidateBound,
    BindingEvent_PreCombatBridgeConsumed,
    BindingEvent_CombatMoveReused,
    BindingEvent_PreCombatAcquired,
    BindingEvent_PreCombatReused
};

enum CandidateStatusCode
{
    CandidateStatus_None,
    CandidateStatus_Persisted,
    CandidateStatus_CancelledImmediateResult
};

struct GenerationFacts
{
    eCEntity *actorInstance;
    std::uint64_t generation;
    GenerationStatus status;
    unsigned int trackedSourceCount;
    bool outstanding;
};

struct LifecycleIssue
{
    LifecycleIssueCode code;
    eCEntity *actorInstance;
    std::uint64_t generation;
    eCEntity *sourceInstance;
};

struct BindingObservation
{
    BindingEventCode code;
    GenerationFacts generation;
    gCScriptProcessingUnit *spu;
    gScrArgument *arguments;
    std::string scriptName;
    eCEntity *sourceInstance;
};

struct StartSourceFacts
{
    eCEntity *sourceInstance;
    unsigned int sideMask;
    eECollisionGroup actualGroup;
};

struct LifecycleStartFacts
{
    bool available;
    GenerationFacts generation;
    std::uint64_t replacedGeneration;
    bool replacedOutstanding;
    StartSourceFacts sources[2];
};

struct SourceEventFacts
{
    bool available;
    eCEntity *actorInstance;
    std::uint64_t generation;
    GenerationStatus status;
    eCEntity *sourceInstance;
    unsigned int sideMask;
    unsigned int offensiveRequestCount;
    bool outstandingCleanup;
    bool cleanupObserved;
    eECollisionGroup actualGroup;
};

struct BeginCombatMoveResult
{
    GenerationToken token;
    LifecycleStartFacts start;
    BindingObservation binding;
    LifecycleIssue issue;
};

struct CompleteCombatMoveResult
{
    CandidateStatusCode statusEvent;
    GenerationFacts generation;
    LifecycleIssue issue;
};

struct CollisionObservationResult
{
    LifecycleStartFacts start;
    BindingObservation binding;
    LifecycleIssue issue;
    bool offenseRequestObserved;
    bool cleanupFulfilledObserved;
    SourceEventFacts sourceEvent;
};

struct BridgeRetirementResult
{
    bool bridgeWasActive;
    bool bindingRetired;
    GenerationFacts generation;
    LifecycleIssue issue;
};

enum FinalizationOutcome
{
    FinalizationOutcome_None,
    FinalizationOutcome_NoOpNoOutstanding,
    FinalizationOutcome_UnresolvedNotEquipped,
    FinalizationOutcome_NoOpPhysicallyCleanReconciled,
    FinalizationOutcome_RepairedToItemEquipped,
    FinalizationOutcome_RepairDivergedFromItemEquipped
};

struct FinalizationSourceResult
{
    FinalizationOutcome outcome;
    eCEntity *sourceInstance;
    unsigned int originalSideMask;
    unsigned int currentSideMask;
    unsigned int offensiveRequestCount;
    eECollisionGroup actualGroupBeforeRepair;
    eECollisionGroup repairRequestedGroup;
    eECollisionGroup actualGroupAfterRepair;
    bool outstandingBeforeFinalization;
    bool cleanupObservedBeforeFinalization;
    bool livenessEstablished;
    bool repairAttempted;
    bool physicalCollisionChanged;
};

struct FinalizationResult
{
    bool available;
    eCEntity *actorInstance;
    std::uint64_t generation;
    GenerationStatus status;
    unsigned int sourceCount;
    FinalizationSourceResult sources[2];
    bool physicalCollisionChanged;
    LifecycleIssue issue;
};

BeginCombatMoveResult BeginCombatMove(
    Entity &actor, EquippedCollisionSources const &sources,
    gCScriptProcessingUnit *spu,
    PreCombatBridgeToken *preCombatBridge);
CompleteCombatMoveResult CompleteCombatMoveCandidate(
    GenerationToken const &token, GEBool originalResult);
CollisionObservationResult ObserveCollisionGroupResult(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup resultingGroup,
    PreCombatDispatchView const *preCombatDispatch,
    PreCombatBridgeToken *preCombatBridge);
BridgeRetirementResult RetirePreCombatBridgeAfterDispatch(
    PreCombatBridgeToken &preCombatBridge);
GenerationToken CaptureFinalizationToken(eCEntity *actorInstance);
FinalizationResult FinalizeAfterAISetState(GenerationToken const &token);
}

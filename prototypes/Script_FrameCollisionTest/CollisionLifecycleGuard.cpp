#include "CollisionLifecycleGuard.h"

#include "CollisionSources.h"

#include <string>
#include <unordered_map>

namespace FrameCollision::CollisionLifecycleGuard
{
struct OuterFrameBinding
{
    gCScriptProcessingUnit *spu;
    gScrArgument *arguments;
    std::string scriptName;
    bool active;
    bool preCombatTemporary;
};

struct SourceLifecycleRecord
{
    eCEntity *sourceInstance;
    unsigned int sideMask;
    unsigned int offensiveRequestCount;
    bool outstandingCleanup;
    bool cleanupObserved;
};

struct ActorLifecycleRecord
{
    eCEntity *actorInstance;
    std::uint64_t generation;
    GenerationStatus status;
    SourceLifecycleRecord sources[2];
    unsigned int sourceCount;
    OuterFrameBinding outerFrame;
};

struct SourceOwner
{
    eCEntity *actorInstance;
    std::uint64_t generation;
    unsigned int sourceIndex;
};

struct ScriptFunctionDispatchContext
{
    gCScriptProcessingUnit *spu;
    eCEntity *actorInstance;
    gScrArgument *arguments;
    std::string scriptName;
    bool topIsScriptFunction;
};

static std::uint64_t g_NextGeneration = 0;
static std::unordered_map<eCEntity *, ActorLifecycleRecord> g_ActorRecords;
static std::unordered_map<eCEntity *, SourceOwner> g_SourceOwners;

static bool HasOutstandingObligation(ActorLifecycleRecord const &record)
{
    for (unsigned int i = 0; i < record.sourceCount; ++i)
    {
        if (record.sources[i].outstandingCleanup)
            return true;
    }
    return false;
}

static GenerationFacts MakeGenerationFacts(
    ActorLifecycleRecord const &record)
{
    GenerationFacts facts = {};
    facts.actorInstance = record.actorInstance;
    facts.generation = record.generation;
    facts.status = record.status;
    facts.trackedSourceCount = record.sourceCount;
    facts.outstanding = HasOutstandingObligation(record);
    return facts;
}

static LifecycleIssue MakeIssue(
    LifecycleIssueCode code, eCEntity *actorInstance,
    std::uint64_t generation, eCEntity *sourceInstance = nullptr)
{
    LifecycleIssue issue = {};
    issue.code = code;
    issue.actorInstance = actorInstance;
    issue.generation = generation;
    issue.sourceInstance = sourceInstance;
    return issue;
}

static BindingObservation MakeBindingObservation(
    BindingEventCode code, ActorLifecycleRecord const &record,
    ScriptFunctionDispatchContext const &frame,
    eCEntity *sourceInstance = nullptr)
{
    BindingObservation observation = {};
    observation.code = code;
    observation.generation = MakeGenerationFacts(record);
    observation.spu = frame.spu;
    observation.arguments = frame.arguments;
    observation.scriptName = frame.scriptName;
    observation.sourceInstance = sourceInstance;
    return observation;
}

static LifecycleStartFacts MakeLifecycleStartFacts(
    ActorLifecycleRecord const &record,
    std::uint64_t replacedGeneration, bool replacedOutstanding)
{
    LifecycleStartFacts result = {};
    result.available = true;
    result.generation = MakeGenerationFacts(record);
    result.replacedGeneration = replacedGeneration;
    result.replacedOutstanding = replacedOutstanding;
    for (unsigned int i = 0; i < record.sourceCount; ++i)
    {
        result.sources[i].sourceInstance = record.sources[i].sourceInstance;
        result.sources[i].sideMask = record.sources[i].sideMask;
        result.sources[i].actualGroup =
            record.sources[i].sourceInstance != nullptr
                ? record.sources[i].sourceInstance->GetCollisionGroup()
                : static_cast<eECollisionGroup>(-1);
    }
    return result;
}

static SourceEventFacts MakeSourceEventFacts(
    ActorLifecycleRecord const &record,
    SourceLifecycleRecord const &source,
    eECollisionGroup actualGroup)
{
    SourceEventFacts result = {};
    result.available = true;
    result.actorInstance = record.actorInstance;
    result.generation = record.generation;
    result.status = record.status;
    result.sourceInstance = source.sourceInstance;
    result.sideMask = source.sideMask;
    result.offensiveRequestCount = source.offensiveRequestCount;
    result.outstandingCleanup = source.outstandingCleanup;
    result.cleanupObserved = source.cleanupObserved;
    result.actualGroup = actualGroup;
    return result;
}

static void RemoveRecord(
    std::unordered_map<eCEntity *, ActorLifecycleRecord>::iterator recordIt)
{
    ActorLifecycleRecord const &record = recordIt->second;
    for (unsigned int i = 0; i < record.sourceCount; ++i)
    {
        eCEntity *sourceInstance = record.sources[i].sourceInstance;
        auto ownerIt = g_SourceOwners.find(sourceInstance);
        if (ownerIt != g_SourceOwners.end()
            && ownerIt->second.actorInstance == record.actorInstance
            && ownerIt->second.generation == record.generation)
        {
            g_SourceOwners.erase(ownerIt);
        }
    }
    g_ActorRecords.erase(recordIt);
}

static void AddSource(
    ActorLifecycleRecord &record, eCEntity *sourceInstance,
    unsigned int sideMask)
{
    if (sourceInstance == nullptr)
        return;

    for (unsigned int i = 0; i < record.sourceCount; ++i)
    {
        if (record.sources[i].sourceInstance == sourceInstance)
        {
            record.sources[i].sideMask |= sideMask;
            return;
        }
    }

    if (record.sourceCount >= 2)
        return;
    SourceLifecycleRecord &source = record.sources[record.sourceCount++];
    source.sourceInstance = sourceInstance;
    source.sideMask = sideMask;
    source.offensiveRequestCount = 0;
    source.outstandingCleanup = false;
    source.cleanupObserved = false;
}

static void RegisterSourceOwners(ActorLifecycleRecord const &record)
{
    for (unsigned int i = 0; i < record.sourceCount; ++i)
    {
        SourceOwner owner = {};
        owner.actorInstance = record.actorInstance;
        owner.generation = record.generation;
        owner.sourceIndex = i;
        g_SourceOwners[record.sources[i].sourceInstance] = owner;
    }
}

static ScriptFunctionDispatchContext CaptureTopScriptFunction(
    gCScriptProcessingUnit *spu,
    bTObjStack<gScriptRunTimeSingleState> &stateStack)
{
    ScriptFunctionDispatchContext result = {};
    result.spu = spu;
    result.actorInstance = spu != nullptr ? spu->GetSelfEntity() : nullptr;
    GEInt const count = stateStack.GetCount();
    if (spu == nullptr || count <= 0)
        return result;

    gScriptRunTimeSingleState const &top = stateStack.GetAt(count - 1);
    result.arguments = top.m_pArguments;
    GELPCChar name = top.m_strScriptName.GetText();
    result.scriptName = name != nullptr ? name : "";
    result.topIsScriptFunction = top.m_bIsScriptState == GEFalse;
    return result;
}

static ScriptFunctionDispatchContext CaptureCurrentTopScriptFunction(
    gCScriptProcessingUnit *spu)
{
    if (spu == nullptr)
        return ScriptFunctionDispatchContext();
    return CaptureTopScriptFunction(spu, spu->m_StateStack);
}

static bool HasLiveCorrelator(
    ScriptFunctionDispatchContext const &frame)
{
    return frame.spu != nullptr
        && frame.actorInstance != nullptr
        && frame.topIsScriptFunction
        && frame.arguments != nullptr;
}

static bool MatchesBinding(
    OuterFrameBinding const &binding,
    ScriptFunctionDispatchContext const &frame)
{
    return binding.active
        && HasLiveCorrelator(frame)
        && binding.spu == frame.spu
        && binding.arguments == frame.arguments
        && binding.scriptName == frame.scriptName;
}

static bool MatchesRecordBinding(
    ActorLifecycleRecord const &record,
    ScriptFunctionDispatchContext const &frame)
{
    return record.actorInstance == frame.actorInstance
        && MatchesBinding(record.outerFrame, frame);
}

static void BindOuterFrame(
    ActorLifecycleRecord &record,
    ScriptFunctionDispatchContext const &frame,
    bool preCombatTemporary = false)
{
    record.outerFrame.spu = frame.spu;
    record.outerFrame.arguments = frame.arguments;
    record.outerFrame.scriptName = frame.scriptName;
    record.outerFrame.active = true;
    record.outerFrame.preCombatTemporary = preCombatTemporary;
}

static void RetireOuterFrameBinding(ActorLifecycleRecord &record)
{
    record.outerFrame.spu = nullptr;
    record.outerFrame.arguments = nullptr;
    record.outerFrame.scriptName.clear();
    record.outerFrame.active = false;
    record.outerFrame.preCombatTemporary = false;
}

BeginCombatMoveResult BeginCombatMove(
    Entity &actor, EquippedCollisionSources const &sources,
    gCScriptProcessingUnit *spu,
    PreCombatBridgeToken *preCombatBridge)
{
    BeginCombatMoveResult result = {};
    if (actor == None || actor.GetInstance() == nullptr)
        return result;

    eCEntity *actorInstance = actor.GetInstance();
    ScriptFunctionDispatchContext const currentFrame =
        CaptureCurrentTopScriptFunction(spu);
    std::uint64_t replacedGeneration = 0;
    bool replacedOutstanding = false;
    auto oldIt = g_ActorRecords.find(actorInstance);
    if (oldIt != g_ActorRecords.end())
    {
        if (oldIt->second.status == GenerationStatus_OuterBound
            || oldIt->second.outerFrame.preCombatTemporary)
        {
            bool const matchingBridge =
                preCombatBridge != nullptr
                && preCombatBridge->active
                && !preCombatBridge->consumed
                && preCombatBridge->actorInstance == actorInstance
                && preCombatBridge->generation == oldIt->second.generation;
            if (matchingBridge
                && oldIt->second.outerFrame.preCombatTemporary
                && MatchesRecordBinding(oldIt->second, currentFrame))
            {
                oldIt->second.status = GenerationStatus_Persisted;
                RetireOuterFrameBinding(oldIt->second);
                preCombatBridge->active = false;
                preCombatBridge->consumed = true;
                result.binding = MakeBindingObservation(
                    BindingEvent_PreCombatBridgeConsumed,
                    oldIt->second, currentFrame);
                result.token.actorInstance = actorInstance;
                result.token.generation = oldIt->second.generation;
                result.token.valid = true;
                result.token.combatMoveCandidate = false;
                return result;
            }

            result.issue = MakeIssue(
                LifecycleIssue_PreCombatBridgeCombatMoveMismatch,
                actorInstance, oldIt->second.generation);
            return result;
        }

        if (MatchesRecordBinding(oldIt->second, currentFrame))
        {
            result.binding = MakeBindingObservation(
                BindingEvent_CombatMoveReused,
                oldIt->second, currentFrame);
            result.token.actorInstance = actorInstance;
            result.token.generation = oldIt->second.generation;
            result.token.valid = true;
            result.token.combatMoveCandidate = false;
            return result;
        }

        replacedGeneration = oldIt->second.generation;
        replacedOutstanding = HasOutstandingObligation(oldIt->second);
        if (replacedOutstanding)
        {
            result.issue = MakeIssue(
                LifecycleIssue_OverlapOutstanding,
                actorInstance, oldIt->second.generation);
        }
        RemoveRecord(oldIt);
    }

    ActorLifecycleRecord record = {};
    record.actorInstance = actorInstance;
    record.generation = ++g_NextGeneration;
    record.status = GenerationStatus_Candidate;
    AddSource(record, sources.rightInstance, SourceMask_Right);
    AddSource(record, sources.leftInstance, SourceMask_Left);
    if (HasLiveCorrelator(currentFrame)
        && currentFrame.actorInstance == actorInstance)
    {
        BindOuterFrame(record, currentFrame);
    }
    g_ActorRecords[actorInstance] = record;
    RegisterSourceOwners(g_ActorRecords[actorInstance]);
    ActorLifecycleRecord &stored = g_ActorRecords[actorInstance];
    result.start = MakeLifecycleStartFacts(
        stored, replacedGeneration, replacedOutstanding);

    if (MatchesRecordBinding(stored, currentFrame))
    {
        result.binding = MakeBindingObservation(
            BindingEvent_CombatMoveCandidateBound,
            stored, currentFrame);
    }
    else if (currentFrame.actorInstance == actorInstance
             && currentFrame.topIsScriptFunction
             && currentFrame.arguments == nullptr
             && result.issue.code == LifecycleIssue_None)
    {
        result.issue = MakeIssue(
            LifecycleIssue_NullArgumentsCombatMove,
            actorInstance, stored.generation);
    }

    result.token.actorInstance = actorInstance;
    result.token.generation = stored.generation;
    result.token.valid = true;
    result.token.combatMoveCandidate = true;
    return result;
}

CompleteCombatMoveResult CompleteCombatMoveCandidate(
    GenerationToken const &token, GEBool originalResult)
{
    CompleteCombatMoveResult result = {};
    if (!token.valid || !token.combatMoveCandidate)
        return result;
    auto recordIt = g_ActorRecords.find(token.actorInstance);
    if (recordIt == g_ActorRecords.end()
        || recordIt->second.generation != token.generation)
    {
        result.issue = MakeIssue(
            LifecycleIssue_CandidateGenerationChanged,
            token.actorInstance, token.generation);
        return result;
    }

    if (originalResult == GEFalse)
    {
        recordIt->second.status = GenerationStatus_Persisted;
        result.statusEvent = CandidateStatus_Persisted;
        result.generation = MakeGenerationFacts(recordIt->second);
        return result;
    }

    result.statusEvent = CandidateStatus_CancelledImmediateResult;
    result.generation = MakeGenerationFacts(recordIt->second);
    RemoveRecord(recordIt);
    return result;
}

static bool TryGetOwnedSource(
    eCEntity *sourceInstance, ActorLifecycleRecord *&actorRecord,
    SourceLifecycleRecord *&sourceRecord)
{
    auto ownerIt = g_SourceOwners.find(sourceInstance);
    if (ownerIt == g_SourceOwners.end())
        return false;
    SourceOwner const &owner = ownerIt->second;
    auto actorIt = g_ActorRecords.find(owner.actorInstance);
    if (actorIt == g_ActorRecords.end()
        || actorIt->second.generation != owner.generation
        || owner.sourceIndex >= actorIt->second.sourceCount
        || actorIt->second.sources[owner.sourceIndex].sourceInstance
               != sourceInstance)
    {
        return false;
    }
    actorRecord = &actorIt->second;
    sourceRecord = &actorIt->second.sources[owner.sourceIndex];
    return true;
}

static unsigned int GetEquippedSideMask(
    EquippedCollisionSources const &sources, eCEntity *sourceInstance)
{
    unsigned int sideMask = SourceMask_None;
    if (sourceInstance != nullptr && sourceInstance == sources.rightInstance)
        sideMask |= SourceMask_Right;
    if (sourceInstance != nullptr && sourceInstance == sources.leftInstance)
        sideMask |= SourceMask_Left;
    return sideMask;
}

enum PreCombatAcquisitionResult
{
    PreCombatAcquisition_NotApplicable,
    PreCombatAcquisition_Ready,
    PreCombatAcquisition_Rejected
};

static PreCombatAcquisitionResult ResolvePreCombatOffenseOwner(
    eCEntity *sourceInstance, ActorLifecycleRecord *&actorRecord,
    SourceLifecycleRecord *&sourceRecord,
    PreCombatDispatchView const *preCombatDispatch,
    PreCombatBridgeToken *preCombatBridge,
    CollisionObservationResult &result)
{
    if (preCombatDispatch == nullptr || preCombatBridge == nullptr)
        return PreCombatAcquisition_NotApplicable;

    if (preCombatDispatch->spu == nullptr
        || preCombatDispatch->runtimeStack == nullptr
        || preCombatDispatch->scriptName == nullptr
        || preCombatDispatch->runtimeStack
            != &preCombatDispatch->spu->m_StateStack)
    {
        result.issue = MakeIssue(
            LifecycleIssue_LiveFrameMismatchPreCombatOffense,
            nullptr, 0, sourceInstance);
        return PreCombatAcquisition_Rejected;
    }

    ScriptFunctionDispatchContext const liveFrame =
        CaptureTopScriptFunction(
            preCombatDispatch->spu,
            *preCombatDispatch->runtimeStack);
    if (!liveFrame.topIsScriptFunction || liveFrame.arguments == nullptr)
    {
        result.issue = MakeIssue(
            liveFrame.topIsScriptFunction
                ? LifecycleIssue_NullArgumentsPreCombatOffense
                : LifecycleIssue_NonFunctionPreCombatOffense,
            liveFrame.actorInstance, 0, sourceInstance);
        return PreCombatAcquisition_Rejected;
    }

    GELPCChar const wrapperName = preCombatDispatch->scriptName->GetText();
    if (wrapperName == nullptr || liveFrame.scriptName != wrapperName)
    {
        result.issue = MakeIssue(
            LifecycleIssue_LiveFrameMismatchPreCombatOffense,
            liveFrame.actorInstance, 0, sourceInstance);
        return PreCombatAcquisition_Rejected;
    }

    Entity actor(liveFrame.actorInstance);
    if (actor == None)
        return PreCombatAcquisition_Rejected;
    EquippedCollisionSources const equipped =
        CollisionSources::GetEquippedCollisionSources(actor);
    unsigned int const sourceSideMask =
        GetEquippedSideMask(equipped, sourceInstance);
    if (sourceSideMask == SourceMask_None)
        return PreCombatAcquisition_NotApplicable;

    auto recordIt = g_ActorRecords.find(liveFrame.actorInstance);
    if (recordIt == g_ActorRecords.end())
    {
        ActorLifecycleRecord *rightOwner = nullptr;
        SourceLifecycleRecord *rightSource = nullptr;
        ActorLifecycleRecord *leftOwner = nullptr;
        SourceLifecycleRecord *leftSource = nullptr;
        bool const equippedSourceAlreadyOwned =
            TryGetOwnedSource(
                equipped.rightInstance, rightOwner, rightSource)
            || TryGetOwnedSource(
                equipped.leftInstance, leftOwner, leftSource);
        if (actorRecord != nullptr || sourceRecord != nullptr
            || equippedSourceAlreadyOwned
            || preCombatBridge->active
            || preCombatBridge->consumed)
        {
            result.issue = MakeIssue(
                LifecycleIssue_PreCombatActorSourceOrBridgeOverlap,
                liveFrame.actorInstance, 0, sourceInstance);
            return PreCombatAcquisition_Rejected;
        }

        ActorLifecycleRecord record = {};
        record.actorInstance = liveFrame.actorInstance;
        record.generation = ++g_NextGeneration;
        record.status = GenerationStatus_OuterBound;
        AddSource(record, equipped.rightInstance, SourceMask_Right);
        AddSource(record, equipped.leftInstance, SourceMask_Left);
        BindOuterFrame(record, liveFrame, true);
        g_ActorRecords[record.actorInstance] = record;
        RegisterSourceOwners(g_ActorRecords[record.actorInstance]);
        recordIt = g_ActorRecords.find(record.actorInstance);
        result.start = MakeLifecycleStartFacts(
            recordIt->second, 0, false);
        result.binding = MakeBindingObservation(
            BindingEvent_PreCombatAcquired,
            recordIt->second, liveFrame, sourceInstance);
    }
    else if (!recordIt->second.outerFrame.preCombatTemporary)
    {
        if (!preCombatBridge->active
            && actorRecord == &recordIt->second)
        {
            return PreCombatAcquisition_NotApplicable;
        }
        result.issue = MakeIssue(
            LifecycleIssue_PreCombatGenerationOverlap,
            liveFrame.actorInstance, recordIt->second.generation,
            sourceInstance);
        return PreCombatAcquisition_Rejected;
    }
    else if (!MatchesRecordBinding(recordIt->second, liveFrame)
             || !preCombatBridge->active
             || preCombatBridge->consumed
             || preCombatBridge->actorInstance != liveFrame.actorInstance
             || preCombatBridge->generation != recordIt->second.generation)
    {
        result.issue = MakeIssue(
            LifecycleIssue_PreCombatGenerationFrameOverlap,
            liveFrame.actorInstance, recordIt->second.generation,
            sourceInstance);
        return PreCombatAcquisition_Rejected;
    }
    else
    {
        result.binding = MakeBindingObservation(
            BindingEvent_PreCombatReused,
            recordIt->second, liveFrame, sourceInstance);
    }

    if (actorRecord != nullptr && actorRecord != &recordIt->second)
    {
        result.issue = MakeIssue(
            LifecycleIssue_SourceAlreadyOwnedByOtherGeneration,
            liveFrame.actorInstance, recordIt->second.generation,
            sourceInstance);
        return PreCombatAcquisition_Rejected;
    }

    ActorLifecycleRecord *ownedActor = nullptr;
    SourceLifecycleRecord *ownedSource = nullptr;
    if (!TryGetOwnedSource(sourceInstance, ownedActor, ownedSource)
        || ownedActor != &recordIt->second)
    {
        AddSource(recordIt->second, sourceInstance, sourceSideMask);
        RegisterSourceOwners(recordIt->second);
        ownedActor = nullptr;
        ownedSource = nullptr;
        if (!TryGetOwnedSource(sourceInstance, ownedActor, ownedSource)
            || ownedActor != &recordIt->second)
        {
            result.issue = MakeIssue(
                LifecycleIssue_EquippedSourceRegistrationFailed,
                liveFrame.actorInstance, recordIt->second.generation,
                sourceInstance);
            return PreCombatAcquisition_Rejected;
        }
    }

    actorRecord = ownedActor;
    sourceRecord = ownedSource;
    preCombatBridge->actorInstance = recordIt->second.actorInstance;
    preCombatBridge->generation = recordIt->second.generation;
    preCombatBridge->active = true;
    preCombatBridge->consumed = false;
    return PreCombatAcquisition_Ready;
}

static bool IsCurrentlyEquippedByPlayer(eCEntity *sourceInstance)
{
    Entity player = Entity::GetPlayer();
    if (player == None)
        return false;
    EquippedCollisionSources sources =
        CollisionSources::GetEquippedCollisionSources(player);
    return sourceInstance == sources.rightInstance
        || sourceInstance == sources.leftInstance;
}

CollisionObservationResult ObserveCollisionGroupResult(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup resultingGroup,
    PreCombatDispatchView const *preCombatDispatch,
    PreCombatBridgeToken *preCombatBridge)
{
    CollisionObservationResult result = {};
    if (sourceInstance == nullptr)
        return result;

    ActorLifecycleRecord *actorRecord = nullptr;
    SourceLifecycleRecord *sourceRecord = nullptr;
    bool const owned = TryGetOwnedSource(
        sourceInstance, actorRecord, sourceRecord);

    bool const successfulOffenseRequest =
        requestedGroup == eECollisionGroup_Item_Attack
        && resultingGroup == eECollisionGroup_Item_Attack;
    if (successfulOffenseRequest)
    {
        PreCombatAcquisitionResult const preCombat =
            ResolvePreCombatOffenseOwner(
                sourceInstance, actorRecord, sourceRecord,
                preCombatDispatch, preCombatBridge, result);
        if (preCombat == PreCombatAcquisition_Rejected)
            return result;
        bool const resolvedOwned =
            preCombat == PreCombatAcquisition_Ready || owned;
        if (!resolvedOwned)
        {
            if (IsCurrentlyEquippedByPlayer(sourceInstance))
            {
                Entity player = Entity::GetPlayer();
                result.issue = MakeIssue(
                    LifecycleIssue_UnownedPlayerOffenseRequest,
                    player != None ? player.GetInstance() : nullptr,
                    0, sourceInstance);
            }
            return result;
        }

        ++sourceRecord->offensiveRequestCount;
        sourceRecord->outstandingCleanup = true;
        sourceRecord->cleanupObserved = false;
        result.offenseRequestObserved = true;
        result.sourceEvent = MakeSourceEventFacts(
            *actorRecord, *sourceRecord, resultingGroup);
        return result;
    }

    if (owned
        && sourceRecord->outstandingCleanup
        && resultingGroup != eECollisionGroup_Item_Attack)
    {
        sourceRecord->outstandingCleanup = false;
        sourceRecord->cleanupObserved = true;
        result.cleanupFulfilledObserved = true;
        result.sourceEvent = MakeSourceEventFacts(
            *actorRecord, *sourceRecord, resultingGroup);
    }
    return result;
}

BridgeRetirementResult RetirePreCombatBridgeAfterDispatch(
    PreCombatBridgeToken &preCombatBridge)
{
    BridgeRetirementResult result = {};
    if (!preCombatBridge.active)
        return result;

    result.bridgeWasActive = true;
    auto recordIt = g_ActorRecords.find(preCombatBridge.actorInstance);
    if (recordIt != g_ActorRecords.end()
        && recordIt->second.generation == preCombatBridge.generation
        && recordIt->second.status == GenerationStatus_OuterBound
        && recordIt->second.outerFrame.preCombatTemporary)
    {
        result.generation = MakeGenerationFacts(recordIt->second);
        result.issue = MakeIssue(
            LifecycleIssue_PreCombatBridgeUnconsumedAtDispatchReturn,
            preCombatBridge.actorInstance, preCombatBridge.generation);
        RetireOuterFrameBinding(recordIt->second);
        result.bindingRetired = true;
    }
    else
    {
        result.issue = MakeIssue(
            LifecycleIssue_PreCombatBridgeRetirementMismatch,
            preCombatBridge.actorInstance, preCombatBridge.generation);
    }

    preCombatBridge.active = false;
    return result;
}

GenerationToken CaptureCurrentGenerationToken(eCEntity *actorInstance)
{
    GenerationToken token = {};
    auto recordIt = g_ActorRecords.find(actorInstance);
    if (recordIt == g_ActorRecords.end())
        return token;
    token.actorInstance = actorInstance;
    token.generation = recordIt->second.generation;
    token.valid = true;
    return token;
}

GenerationToken CaptureFinalizationToken(eCEntity *actorInstance)
{
    return CaptureCurrentGenerationToken(actorInstance);
}

static unsigned int GetCurrentSideMask(
    EquippedCollisionSources const &sources, eCEntity *sourceInstance)
{
    unsigned int result = SourceMask_None;
    if (sourceInstance != nullptr && sourceInstance == sources.rightInstance)
        result |= SourceMask_Right;
    if (sourceInstance != nullptr && sourceInstance == sources.leftInstance)
        result |= SourceMask_Left;
    return result;
}

FinalizationResult FinalizeAfterAISetState(
    GenerationToken const &token)
{
    FinalizationResult result = {};
    if (!token.valid)
        return result;
    auto recordIt = g_ActorRecords.find(token.actorInstance);
    if (recordIt == g_ActorRecords.end()
        || recordIt->second.generation != token.generation)
    {
        result.issue = MakeIssue(
            LifecycleIssue_FinalizationGenerationChanged,
            token.actorInstance, token.generation);
        return result;
    }

    ActorLifecycleRecord &record = recordIt->second;
    result.available = true;
    result.actorInstance = record.actorInstance;
    result.generation = record.generation;
    result.status = record.status;
    result.sourceCount = record.sourceCount;

    Entity actor(record.actorInstance);
    EquippedCollisionSources currentSources = {};
    if (actor != None)
        currentSources = CollisionSources::GetEquippedCollisionSources(actor);

    for (unsigned int i = 0; i < record.sourceCount; ++i)
    {
        SourceLifecycleRecord &source = record.sources[i];
        FinalizationSourceResult &sourceResult = result.sources[i];
        sourceResult.sourceInstance = source.sourceInstance;
        sourceResult.originalSideMask = source.sideMask;
        sourceResult.offensiveRequestCount = source.offensiveRequestCount;
        sourceResult.outstandingBeforeFinalization =
            source.outstandingCleanup;
        sourceResult.cleanupObservedBeforeFinalization =
            source.cleanupObserved;
        sourceResult.currentSideMask =
            GetCurrentSideMask(currentSources, source.sourceInstance);
        sourceResult.livenessEstablished =
            sourceResult.currentSideMask != SourceMask_None;
        sourceResult.actualGroupBeforeRepair =
            static_cast<eECollisionGroup>(-1);
        sourceResult.repairRequestedGroup =
            static_cast<eECollisionGroup>(-1);
        sourceResult.actualGroupAfterRepair =
            static_cast<eECollisionGroup>(-1);
        if (sourceResult.livenessEstablished)
        {
            sourceResult.actualGroupBeforeRepair =
                source.sourceInstance->GetCollisionGroup();
        }

        if (!sourceResult.outstandingBeforeFinalization)
        {
            sourceResult.outcome =
                FinalizationOutcome_NoOpNoOutstanding;
        }
        else if (!sourceResult.livenessEstablished)
        {
            sourceResult.outcome =
                FinalizationOutcome_UnresolvedNotEquipped;
        }
        else if (sourceResult.actualGroupBeforeRepair
                 != eECollisionGroup_Item_Attack)
        {
            sourceResult.outcome =
                FinalizationOutcome_NoOpPhysicallyCleanReconciled;
        }
        else
        {
            sourceResult.repairAttempted = true;
            sourceResult.repairRequestedGroup =
                eECollisionGroup_Item_Equipped;
            Entity repairSource(source.sourceInstance);
            repairSource.SetCollisionGroup(
                eECollisionGroup_Item_Equipped);
            sourceResult.actualGroupAfterRepair =
                source.sourceInstance->GetCollisionGroup();
            sourceResult.physicalCollisionChanged =
                sourceResult.actualGroupAfterRepair
                != sourceResult.actualGroupBeforeRepair;
            result.physicalCollisionChanged =
                result.physicalCollisionChanged
                || sourceResult.physicalCollisionChanged;
            sourceResult.outcome =
                sourceResult.actualGroupAfterRepair
                    == eECollisionGroup_Item_Equipped
                ? FinalizationOutcome_RepairedToItemEquipped
                : FinalizationOutcome_RepairDivergedFromItemEquipped;
        }
    }

    RemoveRecord(recordIt);
    return result;
}
}

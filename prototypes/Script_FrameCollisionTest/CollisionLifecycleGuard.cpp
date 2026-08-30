#include "CollisionLifecycleGuard.h"

#include "CollisionControl.h"
#include "CollisionDiagnostics.h"
#include "HookBridgeRuntime.h"

#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>

namespace FrameCollision::CollisionLifecycleGuard
{
enum GenerationStatus
{
    GenerationStatus_Candidate,
    GenerationStatus_Persisted,
    GenerationStatus_OuterBound
};

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
static thread_local std::vector<ScriptFunctionDispatchContext>
    g_ScriptFunctionDispatchStack;

static char const *GetStatusName(GenerationStatus status)
{
    if (status == GenerationStatus_Persisted)
        return "PERSISTED";
    if (status == GenerationStatus_OuterBound)
        return "OUTER_BOUND";
    return "CANDIDATE";
}

static char const *GetSideName(unsigned int sideMask)
{
    if (sideMask == SourceMask_Both)
        return "RIGHT|LEFT";
    if (sideMask == SourceMask_Right)
        return "RIGHT";
    if (sideMask == SourceMask_Left)
        return "LEFT";
    return "NONE";
}

static std::string GetEntityName(eCEntity *instance)
{
    if (instance == nullptr)
        return "<null>";
    Entity entity(instance);
    if (entity == None)
        return "<unavailable>";
    GELPCChar name = entity.GetName().GetText();
    return name != nullptr ? name : "<unnamed>";
}

static bool IsPlayerActor(eCEntity *actorInstance)
{
    Entity player = Entity::GetPlayer();
    return player != None && actorInstance == player.GetInstance();
}

static bool HasOutstandingObligation(ActorLifecycleRecord const &record)
{
    for (unsigned int i = 0; i < record.sourceCount; ++i)
    {
        if (record.sources[i].outstandingCleanup)
            return true;
    }
    return false;
}

static void LogInvariantWarning(
    char const *code, eCEntity *actorInstance, std::uint64_t generation,
    eCEntity *sourceInstance = nullptr)
{
    if (!IsPlayerActor(actorInstance))
        return;
    FILE *log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    std::fprintf(log, "===== C1 INVARIANT WARNING =====\n");
    std::fprintf(log, "ElapsedMs: %.3f\n",
                 HookBridgeRuntime::GetElapsedMilliseconds());
    std::fprintf(log, "Code: %s\n", code);
    std::fprintf(log, "ActorAddress: %p\n",
                 static_cast<void *>(actorInstance));
    std::fprintf(log, "Actor: %s\n", GetEntityName(actorInstance).c_str());
    std::fprintf(log, "Generation: %llu\n",
                 static_cast<unsigned long long>(generation));
    if (sourceInstance != nullptr)
    {
        std::fprintf(log, "SourceAddress: %p\n",
                     static_cast<void *>(sourceInstance));
        std::fprintf(log, "Source: %s\n",
                     GetEntityName(sourceInstance).c_str());
        std::fprintf(log, "ActualGroup: %d\n",
                     static_cast<GEInt>(sourceInstance->GetCollisionGroup()));
    }
    std::fprintf(log, "PhysicalCollisionChanged: 0\n");
    std::fprintf(log, "================================\n\n");
    std::fflush(log);
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

static void LogLifecycleStart(
    ActorLifecycleRecord const &record, std::uint64_t replacedGeneration,
    bool replacedOutstanding)
{
    if (!IsPlayerActor(record.actorInstance))
        return;
    FILE *log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    std::fprintf(log, "===== C1 LIFECYCLE START =====\n");
    std::fprintf(log, "ElapsedMs: %.3f\n",
                 HookBridgeRuntime::GetElapsedMilliseconds());
    std::fprintf(log, "ActorAddress: %p\n",
                 static_cast<void *>(record.actorInstance));
    std::fprintf(log, "Actor: %s\n",
                 GetEntityName(record.actorInstance).c_str());
    std::fprintf(log, "Generation: %llu\n",
                 static_cast<unsigned long long>(record.generation));
    std::fprintf(log, "Status: %s\n", GetStatusName(record.status));
    std::fprintf(log, "ReplacedGeneration: %llu\n",
                 static_cast<unsigned long long>(replacedGeneration));
    std::fprintf(log, "ReplacedOutstanding: %d\n",
                 replacedOutstanding ? 1 : 0);
    std::fprintf(log, "TrackedSourceCount: %u\n", record.sourceCount);
    for (unsigned int i = 0; i < record.sourceCount; ++i)
    {
        SourceLifecycleRecord const &source = record.sources[i];
        std::fprintf(log, "Source[%u].Address: %p\n", i,
                     static_cast<void *>(source.sourceInstance));
        std::fprintf(log, "Source[%u].Name: %s\n", i,
                     GetEntityName(source.sourceInstance).c_str());
        std::fprintf(log, "Source[%u].SideMask: %u\n", i,
                     source.sideMask);
        std::fprintf(log, "Source[%u].Side: %s\n", i,
                     GetSideName(source.sideMask));
        std::fprintf(log, "Source[%u].ActualGroup: %d\n", i,
                     static_cast<GEInt>(
                         source.sourceInstance->GetCollisionGroup()));
    }
    std::fprintf(log, "PhysicalCollisionChanged: 0\n");
    std::fprintf(log, "==============================\n\n");
    std::fflush(log);
}

static void LogCandidateStatus(
    ActorLifecycleRecord const &record, char const *event)
{
    if (!IsPlayerActor(record.actorInstance))
        return;
    FILE *log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    std::fprintf(log, "===== C1 LIFECYCLE STATUS =====\n");
    std::fprintf(log, "ElapsedMs: %.3f\n",
                 HookBridgeRuntime::GetElapsedMilliseconds());
    std::fprintf(log, "Event: %s\n", event);
    std::fprintf(log, "ActorAddress: %p\n",
                 static_cast<void *>(record.actorInstance));
    std::fprintf(log, "Actor: %s\n",
                 GetEntityName(record.actorInstance).c_str());
    std::fprintf(log, "Generation: %llu\n",
                 static_cast<unsigned long long>(record.generation));
    std::fprintf(log, "Status: %s\n", GetStatusName(record.status));
    std::fprintf(log, "Outstanding: %d\n",
                 HasOutstandingObligation(record) ? 1 : 0);
    std::fprintf(log, "PhysicalCollisionChanged: 0\n");
    std::fprintf(log, "===============================\n\n");
    std::fflush(log);
}

static void LogSourceEvent(
    char const *heading, ActorLifecycleRecord const &record,
    SourceLifecycleRecord const &source, eECollisionGroup actualGroup)
{
    if (!IsPlayerActor(record.actorInstance))
        return;
    FILE *log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    std::fprintf(log, "===== %s =====\n", heading);
    std::fprintf(log, "ElapsedMs: %.3f\n",
                 HookBridgeRuntime::GetElapsedMilliseconds());
    std::fprintf(log, "ActorAddress: %p\n",
                 static_cast<void *>(record.actorInstance));
    std::fprintf(log, "Actor: %s\n",
                 GetEntityName(record.actorInstance).c_str());
    std::fprintf(log, "Generation: %llu\n",
                 static_cast<unsigned long long>(record.generation));
    std::fprintf(log, "Status: %s\n", GetStatusName(record.status));
    std::fprintf(log, "SourceAddress: %p\n",
                 static_cast<void *>(source.sourceInstance));
    std::fprintf(log, "Source: %s\n",
                 GetEntityName(source.sourceInstance).c_str());
    std::fprintf(log, "OriginalSideMask: %u\n", source.sideMask);
    std::fprintf(log, "OriginalSide: %s\n",
                 GetSideName(source.sideMask));
    std::fprintf(log, "OffensiveRequestCount: %u\n",
                 source.offensiveRequestCount);
    std::fprintf(log, "Outstanding: %d\n",
                 source.outstandingCleanup ? 1 : 0);
    std::fprintf(log, "CleanupObserved: %d\n",
                 source.cleanupObserved ? 1 : 0);
    std::fprintf(log, "ActualGroup: %d\n",
                 static_cast<GEInt>(actualGroup));
    std::fprintf(log, "PhysicalCollisionChanged: 0\n");
    std::fprintf(log, "==============================\n\n");
    std::fflush(log);
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

static void LogOuterBindingEvent(
    char const *event, ActorLifecycleRecord const &record,
    ScriptFunctionDispatchContext const &frame,
    eCEntity *sourceInstance = nullptr)
{
    if (!IsPlayerActor(record.actorInstance))
        return;
    FILE *log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    std::fprintf(log, "===== C1-O2 OUTER BINDING =====\n");
    std::fprintf(log, "ElapsedMs: %.3f\n",
                 HookBridgeRuntime::GetElapsedMilliseconds());
    std::fprintf(log, "Event: %s\n", event);
    std::fprintf(log, "ActorAddress: %p\n",
                 static_cast<void *>(record.actorInstance));
    std::fprintf(log, "Actor: %s\n",
                 GetEntityName(record.actorInstance).c_str());
    std::fprintf(log, "Generation: %llu\n",
                 static_cast<unsigned long long>(record.generation));
    std::fprintf(log, "Status: %s\n", GetStatusName(record.status));
    std::fprintf(log, "SPUAddress: %p\n", static_cast<void *>(frame.spu));
    std::fprintf(log, "ArgumentsAddress: %p\n",
                 static_cast<void *>(frame.arguments));
    std::fprintf(log, "ScriptFunction: %s\n", frame.scriptName.c_str());
    std::fprintf(log, "Outstanding: %d\n",
                 HasOutstandingObligation(record) ? 1 : 0);
    if (sourceInstance != nullptr)
    {
        std::fprintf(log, "SourceAddress: %p\n",
                     static_cast<void *>(sourceInstance));
        std::fprintf(log, "Source: %s\n",
                     GetEntityName(sourceInstance).c_str());
    }
    for (unsigned int i = 0; i < record.sourceCount; ++i)
    {
        SourceLifecycleRecord const &source = record.sources[i];
        if (!source.outstandingCleanup)
            continue;
        std::fprintf(log, "OutstandingSource[%u].Address: %p\n", i,
                     static_cast<void *>(source.sourceInstance));
        std::fprintf(log, "OutstandingSource[%u].Name: %s\n", i,
                     GetEntityName(source.sourceInstance).c_str());
        std::fprintf(log, "OutstandingSource[%u].ActualGroup: %d\n", i,
                     static_cast<GEInt>(
                         source.sourceInstance->GetCollisionGroup()));
    }
    std::fprintf(log, "PhysicalCollisionChanged: 0\n");
    std::fprintf(log, "================================\n\n");
    std::fflush(log);
}

static void LogOuterBindingFailure(
    char const *code, eCEntity *actorInstance, std::uint64_t generation,
    ScriptFunctionDispatchContext const &frame,
    eCEntity *sourceInstance = nullptr)
{
    if (!IsPlayerActor(actorInstance))
        return;
    FILE *log = CollisionDiagnostics::GetLog();
    if (log == nullptr)
        return;

    std::fprintf(log, "===== C1-O2 BINDING INVARIANT =====\n");
    std::fprintf(log, "ElapsedMs: %.3f\n",
                 HookBridgeRuntime::GetElapsedMilliseconds());
    std::fprintf(log, "Code: %s\n", code);
    std::fprintf(log, "ActorAddress: %p\n",
                 static_cast<void *>(actorInstance));
    std::fprintf(log, "Actor: %s\n",
                 GetEntityName(actorInstance).c_str());
    std::fprintf(log, "Generation: %llu\n",
                 static_cast<unsigned long long>(generation));
    std::fprintf(log, "SPUAddress: %p\n", static_cast<void *>(frame.spu));
    std::fprintf(log, "TopIsScriptFunction: %d\n",
                 frame.topIsScriptFunction ? 1 : 0);
    std::fprintf(log, "ArgumentsAddress: %p\n",
                 static_cast<void *>(frame.arguments));
    std::fprintf(log, "ScriptFunction: %s\n", frame.scriptName.c_str());
    if (sourceInstance != nullptr)
    {
        std::fprintf(log, "SourceAddress: %p\n",
                     static_cast<void *>(sourceInstance));
        std::fprintf(log, "Source: %s\n",
                     GetEntityName(sourceInstance).c_str());
    }
    std::fprintf(log, "PhysicalCollisionChanged: 0\n");
    std::fprintf(log, "===================================\n\n");
    std::fflush(log);
}

ScriptFunctionDispatchToken BeginScriptFunctionDispatch(
    bCString const &scriptName,
    bTObjStack<gScriptRunTimeSingleState> &stateStack,
    gCScriptProcessingUnit *spu)
{
    (void) scriptName;
    ScriptFunctionDispatchContext context =
        CaptureTopScriptFunction(spu, stateStack);
    ScriptFunctionDispatchToken token = {};
    token.spu = context.spu;
    token.actorInstance = context.actorInstance;
    token.arguments = context.arguments;
    token.scriptName = context.scriptName;
    token.dispatchDepth = g_ScriptFunctionDispatchStack.size();
    token.hasLiveCorrelator = HasLiveCorrelator(context);
    g_ScriptFunctionDispatchStack.push_back(context);
    return token;
}

void EndScriptFunctionDispatch(
    ScriptFunctionDispatchToken const &token, GEBool originalResult)
{
    bool const dispatchStillLive =
        token.dispatchDepth < g_ScriptFunctionDispatchStack.size()
        && token.hasLiveCorrelator
        && g_ScriptFunctionDispatchStack[token.dispatchDepth].spu
               == token.spu
        && g_ScriptFunctionDispatchStack[token.dispatchDepth].actorInstance
               == token.actorInstance
        && g_ScriptFunctionDispatchStack[token.dispatchDepth].arguments
               == token.arguments
        && g_ScriptFunctionDispatchStack[token.dispatchDepth].scriptName
               == token.scriptName
        && g_ScriptFunctionDispatchStack[token.dispatchDepth]
               .topIsScriptFunction;
    if (originalResult == GETrue && dispatchStillLive)
    {
        auto recordIt = g_ActorRecords.find(token.actorInstance);
        if (recordIt != g_ActorRecords.end())
        {
            ScriptFunctionDispatchContext completed = {};
            completed.spu = token.spu;
            completed.actorInstance = token.actorInstance;
            completed.arguments = token.arguments;
            completed.scriptName = token.scriptName;
            completed.topIsScriptFunction = true;
            if (MatchesRecordBinding(recordIt->second, completed))
            {
                bool const outstanding =
                    HasOutstandingObligation(recordIt->second);
                LogOuterBindingEvent(
                    outstanding ? "OUTER_RETURN_OUTSTANDING"
                                : "OUTER_RETURN_RETIRED",
                    recordIt->second, completed);
                RetireOuterFrameBinding(recordIt->second);
                if (!outstanding)
                    RemoveRecord(recordIt);
            }
        }
    }

    if (token.dispatchDepth <= g_ScriptFunctionDispatchStack.size())
        g_ScriptFunctionDispatchStack.resize(token.dispatchDepth);
    else
        g_ScriptFunctionDispatchStack.clear();
}

void InvalidateScriptFunctionDispatchAfterAISetState(
    eCEntity *actorInstance)
{
    for (ScriptFunctionDispatchContext &context
         : g_ScriptFunctionDispatchStack)
    {
        if (context.actorInstance != actorInstance)
            continue;
        context.spu = nullptr;
        context.actorInstance = nullptr;
        context.arguments = nullptr;
        context.scriptName.clear();
        context.topIsScriptFunction = false;
    }
}

GenerationToken BeginCombatMove(
    Entity &actor, EquippedCollisionSources const &sources,
    gCScriptProcessingUnit *spu,
    PreCombatBridgeToken *preCombatBridge)
{
    GenerationToken token = {};
    if (actor == None || actor.GetInstance() == nullptr)
        return token;

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
                LogOuterBindingEvent(
                    "PRECOMBAT_BRIDGE_CONSUMED",
                    oldIt->second, currentFrame);
                token.actorInstance = actorInstance;
                token.generation = oldIt->second.generation;
                token.valid = true;
                token.combatMoveCandidate = false;
                return token;
            }

            LogOuterBindingFailure(
                "PRECOMBAT_BRIDGE_COMBAT_MOVE_MISMATCH",
                actorInstance, oldIt->second.generation,
                currentFrame);
            return token;
        }

        if (MatchesRecordBinding(oldIt->second, currentFrame))
        {
            LogOuterBindingEvent(
                "COMBAT_MOVE_REUSED", oldIt->second, currentFrame);
            token.actorInstance = actorInstance;
            token.generation = oldIt->second.generation;
            token.valid = true;
            token.combatMoveCandidate = false;
            return token;
        }

        replacedGeneration = oldIt->second.generation;
        replacedOutstanding = HasOutstandingObligation(oldIt->second);
        if (replacedOutstanding)
        {
            LogInvariantWarning(
                "OVERLAP_OUTSTANDING", actorInstance,
                oldIt->second.generation);
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
        BindOuterFrame(record, currentFrame);
    g_ActorRecords[actorInstance] = record;
    RegisterSourceOwners(g_ActorRecords[actorInstance]);
    LogLifecycleStart(
        g_ActorRecords[actorInstance], replacedGeneration,
        replacedOutstanding);
    if (MatchesRecordBinding(
            g_ActorRecords[actorInstance], currentFrame))
    {
        LogOuterBindingEvent(
            "COMBAT_MOVE_CANDIDATE_BOUND",
            g_ActorRecords[actorInstance], currentFrame);
    }
    else if (currentFrame.actorInstance == actorInstance
             && currentFrame.topIsScriptFunction
             && currentFrame.arguments == nullptr)
    {
        LogOuterBindingFailure(
            "NULL_ARGUMENTS_COMBAT_MOVE", actorInstance,
            record.generation, currentFrame);
    }

    token.actorInstance = actorInstance;
    token.generation = record.generation;
    token.valid = true;
    token.combatMoveCandidate = true;
    return token;
}

void CompleteCombatMoveCandidate(
    GenerationToken const &token, GEBool originalResult)
{
    if (!token.valid || !token.combatMoveCandidate)
        return;
    auto recordIt = g_ActorRecords.find(token.actorInstance);
    if (recordIt == g_ActorRecords.end()
        || recordIt->second.generation != token.generation)
    {
        LogInvariantWarning(
            "CANDIDATE_GENERATION_CHANGED", token.actorInstance,
            token.generation);
        return;
    }

    if (originalResult == GEFalse)
    {
        recordIt->second.status = GenerationStatus_Persisted;
        LogCandidateStatus(recordIt->second, "PERSISTED");
        return;
    }

    LogCandidateStatus(recordIt->second, "CANCELLED_IMMEDIATE_RESULT");
    RemoveRecord(recordIt);
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
    PreCombatBridgeToken *preCombatBridge)
{
    if (preCombatDispatch == nullptr || preCombatBridge == nullptr)
        return PreCombatAcquisition_NotApplicable;

    if (preCombatDispatch->spu == nullptr
        || preCombatDispatch->runtimeStack == nullptr
        || preCombatDispatch->scriptName == nullptr
        || preCombatDispatch->runtimeStack
            != &preCombatDispatch->spu->m_StateStack)
    {
        return PreCombatAcquisition_Rejected;
    }

    ScriptFunctionDispatchContext const liveFrame =
        CaptureTopScriptFunction(
            preCombatDispatch->spu,
            *preCombatDispatch->runtimeStack);
    if (!liveFrame.topIsScriptFunction || liveFrame.arguments == nullptr)
    {
        LogOuterBindingFailure(
            liveFrame.topIsScriptFunction
                ? "NULL_ARGUMENTS_PRECOMBAT_OFFENSE"
                : "NON_FUNCTION_PRECOMBAT_OFFENSE",
            liveFrame.actorInstance, 0, liveFrame, sourceInstance);
        return PreCombatAcquisition_Rejected;
    }

    GELPCChar const wrapperName = preCombatDispatch->scriptName->GetText();
    if (wrapperName == nullptr || liveFrame.scriptName != wrapperName)
    {
        LogOuterBindingFailure(
            "LIVE_FRAME_MISMATCH_PRECOMBAT_OFFENSE",
            liveFrame.actorInstance, 0, liveFrame, sourceInstance);
        return PreCombatAcquisition_Rejected;
    }

    Entity actor(liveFrame.actorInstance);
    if (actor == None)
        return PreCombatAcquisition_Rejected;
    EquippedCollisionSources const equipped =
        CollisionControl::GetEquippedCollisionSources(actor);
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
            LogOuterBindingFailure(
                "PRECOMBAT_ACTOR_SOURCE_OR_BRIDGE_OVERLAP",
                liveFrame.actorInstance, 0, liveFrame, sourceInstance);
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
        LogLifecycleStart(recordIt->second, 0, false);
        LogOuterBindingEvent(
            "PRECOMBAT_ACQUIRED", recordIt->second, liveFrame,
            sourceInstance);
    }
    else if (!recordIt->second.outerFrame.preCombatTemporary)
    {
        if (!preCombatBridge->active
            && actorRecord == &recordIt->second)
            return PreCombatAcquisition_NotApplicable;
        LogOuterBindingFailure(
            "PRECOMBAT_GENERATION_OVERLAP",
            liveFrame.actorInstance, recordIt->second.generation,
            liveFrame, sourceInstance);
        return PreCombatAcquisition_Rejected;
    }
    else if (!MatchesRecordBinding(recordIt->second, liveFrame)
             || !preCombatBridge->active
             || preCombatBridge->consumed
             || preCombatBridge->actorInstance != liveFrame.actorInstance
             || preCombatBridge->generation != recordIt->second.generation)
    {
        LogOuterBindingFailure(
            "PRECOMBAT_GENERATION_FRAME_OVERLAP",
            liveFrame.actorInstance, recordIt->second.generation,
            liveFrame, sourceInstance);
        return PreCombatAcquisition_Rejected;
    }
    else
    {
        LogOuterBindingEvent(
            "PRECOMBAT_REUSED", recordIt->second, liveFrame,
            sourceInstance);
    }

    if (actorRecord != nullptr && actorRecord != &recordIt->second)
    {
        LogOuterBindingFailure(
            "SOURCE_ALREADY_OWNED_BY_OTHER_GENERATION",
            liveFrame.actorInstance, recordIt->second.generation,
            liveFrame, sourceInstance);
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
            LogOuterBindingFailure(
                "EQUIPPED_SOURCE_REGISTRATION_FAILED",
                liveFrame.actorInstance, recordIt->second.generation,
                liveFrame, sourceInstance);
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
        CollisionControl::GetEquippedCollisionSources(player);
    return sourceInstance == sources.rightInstance
        || sourceInstance == sources.leftInstance;
}

void ObserveCollisionGroupResult(
    eCEntity *sourceInstance, eECollisionGroup requestedGroup,
    eECollisionGroup resultingGroup,
    PreCombatDispatchView const *preCombatDispatch,
    PreCombatBridgeToken *preCombatBridge)
{
    if (sourceInstance == nullptr)
        return;

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
                preCombatDispatch, preCombatBridge);
        if (preCombat == PreCombatAcquisition_Rejected)
            return;
        bool const resolvedOwned =
            preCombat == PreCombatAcquisition_Ready || owned;
        if (!resolvedOwned)
        {
            if (IsCurrentlyEquippedByPlayer(sourceInstance))
            {
                Entity player = Entity::GetPlayer();
                LogInvariantWarning(
                    "UNOWNED_PLAYER_OFFENSE_REQUEST",
                    player != None ? player.GetInstance() : nullptr,
                    0, sourceInstance);
            }
            return;
        }

        ++sourceRecord->offensiveRequestCount;
        sourceRecord->outstandingCleanup = true;
        sourceRecord->cleanupObserved = false;
        LogSourceEvent(
            "C1 OFFENSE REQUEST", *actorRecord, *sourceRecord,
            resultingGroup);
        return;
    }

    if (owned
        && sourceRecord->outstandingCleanup
        && resultingGroup != eECollisionGroup_Item_Attack)
    {
        sourceRecord->outstandingCleanup = false;
        sourceRecord->cleanupObserved = true;
        LogSourceEvent(
            "C1 CLEANUP FULFILLED", *actorRecord, *sourceRecord,
            resultingGroup);
    }
}

void RetirePreCombatBridgeAfterDispatch(
    PreCombatBridgeToken &preCombatBridge)
{
    if (!preCombatBridge.active)
        return;

    auto recordIt = g_ActorRecords.find(preCombatBridge.actorInstance);
    if (recordIt != g_ActorRecords.end()
        && recordIt->second.generation == preCombatBridge.generation
        && recordIt->second.status == GenerationStatus_OuterBound
        && recordIt->second.outerFrame.preCombatTemporary)
    {
        LogInvariantWarning(
            "PRECOMBAT_BRIDGE_UNCONSUMED_AT_DISPATCH_RETURN",
            preCombatBridge.actorInstance,
            preCombatBridge.generation);
        RetireOuterFrameBinding(recordIt->second);
    }
    else
    {
        LogInvariantWarning(
            "PRECOMBAT_BRIDGE_RETIREMENT_MISMATCH",
            preCombatBridge.actorInstance,
            preCombatBridge.generation);
    }

    preCombatBridge.active = false;
}

GenerationToken CaptureFinalizationToken(eCEntity *actorInstance)
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

void FinalizeAfterAISetState(GenerationToken const &token)
{
    if (!token.valid)
        return;
    auto recordIt = g_ActorRecords.find(token.actorInstance);
    if (recordIt == g_ActorRecords.end()
        || recordIt->second.generation != token.generation)
    {
        LogInvariantWarning(
            "FINALIZATION_GENERATION_CHANGED", token.actorInstance,
            token.generation);
        return;
    }

    ActorLifecycleRecord &record = recordIt->second;
    Entity actor(record.actorInstance);
    EquippedCollisionSources currentSources = {};
    if (actor != None)
        currentSources = CollisionControl::GetEquippedCollisionSources(actor);

    FILE *log = IsPlayerActor(record.actorInstance)
        ? CollisionDiagnostics::GetLog() : nullptr;
    if (log != nullptr)
    {
        std::fprintf(log, "===== C1 FINALIZATION =====\n");
        std::fprintf(log, "ElapsedMs: %.3f\n",
                     HookBridgeRuntime::GetElapsedMilliseconds());
        std::fprintf(log, "Reason: AISETSTATE_AFTER_ORIGINAL\n");
        std::fprintf(log, "ActorAddress: %p\n",
                     static_cast<void *>(record.actorInstance));
        std::fprintf(log, "Actor: %s\n",
                     GetEntityName(record.actorInstance).c_str());
        std::fprintf(log, "Generation: %llu\n",
                     static_cast<unsigned long long>(record.generation));
        std::fprintf(log, "Status: %s\n", GetStatusName(record.status));
        std::fprintf(log, "TrackedSourceCount: %u\n", record.sourceCount);
    }

    for (unsigned int i = 0; i < record.sourceCount; ++i)
    {
        SourceLifecycleRecord &source = record.sources[i];
        bool const outstandingBeforeFinalization =
            source.outstandingCleanup;
        unsigned int const currentSideMask =
            GetCurrentSideMask(currentSources, source.sourceInstance);
        bool const stillEquipped = currentSideMask != SourceMask_None;
        eECollisionGroup actualGroup = static_cast<eECollisionGroup>(-1);
        if (stillEquipped)
            actualGroup = source.sourceInstance->GetCollisionGroup();

        char const *outcome = nullptr;
        if (!source.outstandingCleanup)
        {
            outcome = "NO_OP_NO_OUTSTANDING";
        }
        else if (!stillEquipped)
        {
            outcome = "UNRESOLVED_NOT_EQUIPPED";
        }
        else if (actualGroup != eECollisionGroup_Item_Attack)
        {
            outcome = "NO_OP_PHYSICALLY_CLEAN_RECONCILED";
        }
        else
        {
            outcome = "WOULD_REPAIR";
        }

        if (log != nullptr)
        {
            std::fprintf(log, "Source[%u].Outcome: %s\n", i, outcome);
            std::fprintf(log, "Source[%u].Address: %p\n", i,
                         static_cast<void *>(source.sourceInstance));
            if (stillEquipped)
            {
                std::fprintf(log, "Source[%u].Name: %s\n", i,
                             GetEntityName(source.sourceInstance).c_str());
            }
            else
            {
                std::fprintf(log,
                             "Source[%u].Name: <not-dereferenced>\n", i);
            }
            std::fprintf(log, "Source[%u].LivenessEstablished: %d\n", i,
                         stillEquipped ? 1 : 0);
            std::fprintf(log, "Source[%u].OriginalSideMask: %u\n", i,
                         source.sideMask);
            std::fprintf(log, "Source[%u].OriginalSide: %s\n", i,
                         GetSideName(source.sideMask));
            std::fprintf(log, "Source[%u].OffensiveRequestCount: %u\n", i,
                         source.offensiveRequestCount);
            std::fprintf(
                log, "Source[%u].OutstandingBeforeFinalization: %d\n", i,
                outstandingBeforeFinalization ? 1 : 0);
            std::fprintf(log, "Source[%u].ActualGroup: %d\n", i,
                         static_cast<GEInt>(actualGroup));
            std::fprintf(log, "Source[%u].CleanupObserved: %d\n", i,
                         source.cleanupObserved ? 1 : 0);
            std::fprintf(log, "Source[%u].StillEquipped: %d\n", i,
                         stillEquipped ? 1 : 0);
            std::fprintf(log, "Source[%u].CurrentSideMask: %u\n", i,
                         currentSideMask);
        }
    }

    if (log != nullptr)
    {
        if (record.sourceCount == 0)
            std::fprintf(log, "GenerationOutcome: NO_OP_NO_TRACKED_SOURCE\n");
        std::fprintf(log, "PhysicalCollisionChanged: 0\n");
        std::fprintf(log, "===========================\n\n");
        std::fflush(log);
    }

    RemoveRecord(recordIt);
}
}

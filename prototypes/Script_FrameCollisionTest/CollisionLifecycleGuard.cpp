#include "CollisionLifecycleGuard.h"

#include "CollisionControl.h"
#include "CollisionDiagnostics.h"
#include "HookBridgeRuntime.h"

#include <cstdio>
#include <string>
#include <unordered_map>

namespace FrameCollision::CollisionLifecycleGuard
{
enum GenerationStatus
{
    GenerationStatus_Candidate,
    GenerationStatus_Persisted
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
};

struct SourceOwner
{
    eCEntity *actorInstance;
    std::uint64_t generation;
    unsigned int sourceIndex;
};

static std::uint64_t g_NextGeneration = 0;
static std::unordered_map<eCEntity *, ActorLifecycleRecord> g_ActorRecords;
static std::unordered_map<eCEntity *, SourceOwner> g_SourceOwners;

static char const *GetStatusName(GenerationStatus status)
{
    return status == GenerationStatus_Persisted ? "PERSISTED" : "CANDIDATE";
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

GenerationToken BeginCombatMove(
    Entity &actor, EquippedCollisionSources const &sources)
{
    GenerationToken token = {};
    if (actor == None || actor.GetInstance() == nullptr)
        return token;

    eCEntity *actorInstance = actor.GetInstance();
    std::uint64_t replacedGeneration = 0;
    bool replacedOutstanding = false;
    auto oldIt = g_ActorRecords.find(actorInstance);
    if (oldIt != g_ActorRecords.end())
    {
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
    g_ActorRecords[actorInstance] = record;
    RegisterSourceOwners(g_ActorRecords[actorInstance]);
    LogLifecycleStart(
        g_ActorRecords[actorInstance], replacedGeneration,
        replacedOutstanding);

    token.actorInstance = actorInstance;
    token.generation = record.generation;
    token.valid = true;
    return token;
}

void CompleteCombatMoveCandidate(
    GenerationToken const &token, GEBool originalResult)
{
    if (!token.valid)
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
    eECollisionGroup resultingGroup)
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
        if (!owned)
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
        eECollisionGroup const actualGroup =
            source.sourceInstance->GetCollisionGroup();
        bool const outstandingBeforeFinalization =
            source.outstandingCleanup;
        unsigned int const currentSideMask =
            GetCurrentSideMask(currentSources, source.sourceInstance);
        bool const stillEquipped = currentSideMask != SourceMask_None;
        char const *outcome = nullptr;
        if (!source.outstandingCleanup)
        {
            outcome = "NO_OP_NO_OUTSTANDING";
        }
        else if (actualGroup != eECollisionGroup_Item_Attack)
        {
            outcome = "NO_OP_PHYSICALLY_CLEAN_RECONCILED";
        }
        else if (stillEquipped)
        {
            outcome = "WOULD_REPAIR";
        }
        else
        {
            outcome = "UNRESOLVED_NOT_EQUIPPED";
        }

        if (log != nullptr)
        {
            std::fprintf(log, "Source[%u].Outcome: %s\n", i, outcome);
            std::fprintf(log, "Source[%u].Address: %p\n", i,
                         static_cast<void *>(source.sourceInstance));
            std::fprintf(log, "Source[%u].Name: %s\n", i,
                         GetEntityName(source.sourceInstance).c_str());
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

#include "CollisionDiagnostics.h"

#include "CollisionSources.h"
#include "RuntimeClock.h"

#include <cstring>
#include <string>
#include <unordered_map>

#include <windows.h>

namespace FrameCollision::CollisionDiagnostics
{
static FILE *g_pLog = nullptr;
static std::unordered_map<eCEntity *, std::string> g_LastLoggedAni;

static std::string GetGameDirectory()
{
    char path[MAX_PATH] = {};
    ::GetModuleFileNameA(NULL, path, MAX_PATH);
    std::string result(path);
    std::string::size_type separator = result.find_last_of("\\/");
    if (separator != std::string::npos)
        result.resize(separator);
    return result;
}

static bool IsPlayerActor(eCEntity *actorInstance)
{
    Entity player = Entity::GetPlayer();
    return player != None && actorInstance == player.GetInstance();
}

static char const *EntityName(eCEntity *instance)
{
    if (instance == nullptr)
        return "<null>";
    Entity entity(instance);
    return entity != None ? entity.GetName().GetText() : "<unavailable>";
}

static char const *AttackFamilyName(AttackFamily family)
{
    switch (family)
    {
        case AttackFamily_Normal: return "NORMAL";
        case AttackFamily_Quick: return "QUICK";
        case AttackFamily_Whirl: return "WHIRL";
        default: return "UNKNOWN";
    }
}

static char const *GenerationStatusName(
    CollisionLifecycleGuard::GenerationStatus status)
{
    switch (status)
    {
        case CollisionLifecycleGuard::GenerationStatus_Persisted:
            return "PERSISTED";
        case CollisionLifecycleGuard::GenerationStatus_OuterBound:
            return "OUTER_BOUND";
        default:
            return "CANDIDATE";
    }
}

static char const *SideName(unsigned int sideMask)
{
    if (sideMask == SourceMask_Both)
        return "RIGHT|LEFT";
    if (sideMask == SourceMask_Right)
        return "RIGHT";
    if (sideMask == SourceMask_Left)
        return "LEFT";
    return "NONE";
}

static char const *IssueName(
    CollisionLifecycleGuard::LifecycleIssueCode code)
{
    using namespace CollisionLifecycleGuard;
    switch (code)
    {
        case LifecycleIssue_OverlapOutstanding:
            return "OVERLAP_OUTSTANDING";
        case LifecycleIssue_CandidateGenerationChanged:
            return "CANDIDATE_GENERATION_CHANGED";
        case LifecycleIssue_NullArgumentsCombatMove:
            return "NULL_ARGUMENTS_COMBAT_MOVE";
        case LifecycleIssue_PreCombatBridgeCombatMoveMismatch:
            return "PRECOMBAT_BRIDGE_COMBAT_MOVE_MISMATCH";
        case LifecycleIssue_NullArgumentsPreCombatOffense:
            return "NULL_ARGUMENTS_PRECOMBAT_OFFENSE";
        case LifecycleIssue_NonFunctionPreCombatOffense:
            return "NON_FUNCTION_PRECOMBAT_OFFENSE";
        case LifecycleIssue_LiveFrameMismatchPreCombatOffense:
            return "LIVE_FRAME_MISMATCH_PRECOMBAT_OFFENSE";
        case LifecycleIssue_PreCombatActorSourceOrBridgeOverlap:
            return "PRECOMBAT_ACTOR_SOURCE_OR_BRIDGE_OVERLAP";
        case LifecycleIssue_PreCombatGenerationOverlap:
            return "PRECOMBAT_GENERATION_OVERLAP";
        case LifecycleIssue_PreCombatGenerationFrameOverlap:
            return "PRECOMBAT_GENERATION_FRAME_OVERLAP";
        case LifecycleIssue_SourceAlreadyOwnedByOtherGeneration:
            return "SOURCE_ALREADY_OWNED_BY_OTHER_GENERATION";
        case LifecycleIssue_EquippedSourceRegistrationFailed:
            return "EQUIPPED_SOURCE_REGISTRATION_FAILED";
        case LifecycleIssue_UnownedPlayerOffenseRequest:
            return "UNOWNED_PLAYER_OFFENSE_REQUEST";
        case LifecycleIssue_PreCombatBridgeUnconsumedAtDispatchReturn:
            return "PRECOMBAT_BRIDGE_UNCONSUMED_AT_DISPATCH_RETURN";
        case LifecycleIssue_PreCombatBridgeRetirementMismatch:
            return "PRECOMBAT_BRIDGE_RETIREMENT_MISMATCH";
        case LifecycleIssue_FinalizationGenerationChanged:
            return "FINALIZATION_GENERATION_CHANGED";
        default:
            return "NONE";
    }
}

static char const *BindingEventName(
    CollisionLifecycleGuard::BindingEventCode code)
{
    using namespace CollisionLifecycleGuard;
    switch (code)
    {
        case BindingEvent_CombatMoveCandidateBound:
            return "COMBAT_MOVE_CANDIDATE_BOUND";
        case BindingEvent_PreCombatBridgeConsumed:
            return "PRECOMBAT_BRIDGE_CONSUMED";
        case BindingEvent_CombatMoveReused:
            return "COMBAT_MOVE_REUSED";
        case BindingEvent_PreCombatAcquired:
            return "PRECOMBAT_ACQUIRED";
        case BindingEvent_PreCombatReused:
            return "PRECOMBAT_REUSED";
        default:
            return "NONE";
    }
}

static char const *FinalizationOutcomeName(
    CollisionLifecycleGuard::FinalizationOutcome outcome)
{
    using namespace CollisionLifecycleGuard;
    switch (outcome)
    {
        case FinalizationOutcome_NoOpNoOutstanding:
            return "NO_OP_NO_OUTSTANDING";
        case FinalizationOutcome_UnresolvedNotEquipped:
            return "UNRESOLVED_NOT_EQUIPPED";
        case FinalizationOutcome_NoOpPhysicallyCleanReconciled:
            return "NO_OP_PHYSICALLY_CLEAN_RECONCILED";
        case FinalizationOutcome_RepairedToItemEquipped:
            return "REPAIRED_TO_ITEM_EQUIPPED";
        case FinalizationOutcome_RepairDivergedFromItemEquipped:
            return "REPAIR_DIVERGED_FROM_ITEM_EQUIPPED";
        default:
            return "NONE";
    }
}

void OpenLog()
{
    std::string const logPath =
        GetGameDirectory() + "\\Script_FrameCollisionTest.log";
    g_pLog = std::fopen(logPath.c_str(), "w");
    if (g_pLog == nullptr)
        return;

    std::fprintf(g_pLog, "Script_FrameCollisionTest diagnostic build loaded.\n");
    std::fprintf(g_pLog, "DiagnosticProfile: CORE\n");
#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
    std::fprintf(g_pLog, "DeepDiagnostics: ENABLED\n");
#else
    std::fprintf(g_pLog, "DeepDiagnostics: DISABLED\n");
#endif
    std::fprintf(g_pLog, "BehaviorCore: EngineBridge + FrameCollisionMarkers + CollisionSources + CollisionSourceOperations + CollisionLifecycleGuard + RuntimeClock\n");
    std::fprintf(g_pLog, "C1Repair: exact outstanding live equipped Item_Attack source -> Item_Equipped after native AISetState opportunity; no ClearTriggeredList.\n");
    std::fprintf(g_pLog, "MarkerFamilies: Normal Quick Whirl\n");
    std::fprintf(g_pLog, "MarkerOpcodes: RIGHT LEFT BOTH OFF\n");
    std::fflush(g_pLog);
}

void CloseLog()
{
    if (g_pLog == nullptr)
        return;
    std::fprintf(g_pLog, "Script_FrameCollisionTest unloading cleanly.\n");
    std::fflush(g_pLog);
    std::fclose(g_pLog);
    g_pLog = nullptr;
}

bool IsLogOpen() { return g_pLog != nullptr; }
FILE *GetLog() { return g_pLog; }

static void LogResolvedSource(char const *label, eCEntity *sourceInstance)
{
    std::fprintf(g_pLog, "%sResolved: %d\n", label,
                 sourceInstance != nullptr ? 1 : 0);
    if (sourceInstance == nullptr)
        return;
    Entity source(sourceInstance);
    std::fprintf(g_pLog, "%sName: %s\n", label, source.GetName().GetText());
    std::fprintf(g_pLog, "%sAddress: %p\n", label,
                 static_cast<void *>(sourceInstance));
    std::fprintf(g_pLog, "%sUseType: %d\n", label,
                 static_cast<GEInt>(
                     CollisionSources::GetCollisionSourceUseType(source)));
    std::fprintf(g_pLog, "%sCollisionGroup: %d\n", label,
                 static_cast<GEInt>(source.GetCollisionGroup()));
}

void LogAttackCallbackOwnership(
    Entity &actor, AttackFamily family,
    FrameCollisionMarkers::AttackCallbackOwnershipResult const &result)
{
    if (g_pLog == nullptr || !result.attackHitEligible)
        return;

    eCEntity *actorInstance = actor.GetInstance();
    bCString currentAni = actor.NPC.GetCurrentMovementAni();
    std::string currentName = currentAni.GetText() != nullptr
        ? currentAni.GetText() : "";
    auto found = g_LastLoggedAni.find(actorInstance);
    bool const motionAlreadyLogged =
        found != g_LastLoggedAni.end() && found->second == currentName;
    if (!motionAlreadyLogged)
    {
        g_LastLoggedAni[actorInstance] = currentName;
        std::fprintf(g_pLog, "===== MARKER OWNERSHIP DECISION =====\n");
        std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                     RuntimeClock::GetElapsedMilliseconds());
        std::fprintf(g_pLog, "Actor: %s\n", actor.GetName().GetText());
        std::fprintf(g_pLog, "Family: %s\n", AttackFamilyName(family));
        std::fprintf(g_pLog, "CurrentMovementAni: %s\n", currentName.c_str());
        std::fprintf(g_pLog, "Action: %d\n",
                     static_cast<GEInt>(
                         actor.Routine.GetProperty<PSRoutine::PropertyAction>()));
        std::fprintf(g_pLog, "AniPhase: %d\n",
                     static_cast<GEInt>(actor.GetCurrentAniPhase()));
        std::fprintf(g_pLog, "MatchingMotionFound: %d\n",
                     result.decision.foundMatchingMotion ? 1 : 0);
        std::fprintf(g_pLog, "MarkerScanValid: %d\n",
                     result.decision.scanValid ? 1 : 0);
        std::fprintf(g_pLog, "ContainsReservedSourceMarker: %d\n",
                     result.decision.markerPresent ? 1 : 0);
        std::fprintf(g_pLog, "RequiredSourceMask: %u\n",
                     result.decision.requiredSourceMask);
        for (GEInt opcode = 0; opcode < MarkerOpcode_Count; ++opcode)
        {
            MarkerOpcode const markerOpcode =
                static_cast<MarkerOpcode>(opcode);
            std::fprintf(g_pLog, "Authored%sCount: %d\n",
                         FrameCollisionMarkers::GetMarkerOpcodeName(markerOpcode),
                         result.decision.markerCounts[opcode]);
            std::fprintf(g_pLog, "First%sFrame: %d\n",
                         FrameCollisionMarkers::GetMarkerOpcodeName(markerOpcode),
                         result.decision.firstMarkerFrames[opcode]);
        }
        LogResolvedSource("RightSource", result.sources.rightInstance);
        LogResolvedSource("LeftSource", result.sources.leftInstance);
        std::fprintf(g_pLog, "SuppressNativeCallback: %d\n",
                     result.suppressNativeCallback ? 1 : 0);
        std::fprintf(g_pLog, "=====================================\n\n");
    }

    std::fflush(g_pLog);
}

void LogNullMarker(char const *markerName)
{
    if (g_pLog == nullptr)
        return;
    std::fprintf(g_pLog, "===== RESERVED MARKER =====\n");
    std::fprintf(g_pLog, "Marker: %s\n",
                 markerName != nullptr ? markerName : "<null>");
    std::fprintf(g_pLog, "Result: REJECTED_NULL_ACTOR\n");
    std::fprintf(g_pLog, "===========================\n\n");
    std::fflush(g_pLog);
}

void LogMarkerContext(Entity &actor, MarkerOpcode opcode)
{
    if (g_pLog == nullptr)
        return;
    bCString ani = actor.NPC.GetCurrentMovementAni();
    std::fprintf(g_pLog, "===== %s RECEIVED =====\n",
                 FrameCollisionMarkers::GetMarkerOpcodeName(opcode));
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                 RuntimeClock::GetElapsedMilliseconds());
    std::fprintf(g_pLog, "Actor: %s\n", actor.GetName().GetText());
    std::fprintf(g_pLog, "Action: %d\n",
                 static_cast<GEInt>(
                     actor.Routine.GetProperty<PSRoutine::PropertyAction>()));
    std::fprintf(g_pLog, "AniPhase: %d\n",
                 static_cast<GEInt>(actor.GetCurrentAniPhase()));
    std::fprintf(g_pLog, "StateTime: %.6f\n", actor.Routine.GetStateTime());
    std::fprintf(g_pLog, "CurrentMovementAni: %s\n", ani.GetText());
}

void LogMarkerResult(Entity &, MarkerProcessResult const &r)
{
    if (g_pLog == nullptr)
        return;
    std::fprintf(g_pLog, "MarkerName: %s\n", r.markerName.c_str());
    std::fprintf(g_pLog, "MarkerOpcode: %s\n",
                 FrameCollisionMarkers::GetMarkerOpcodeName(r.opcode));
    std::fprintf(g_pLog, "C1GenerationValid: %d\n",
                 r.c1GenerationValid ? 1 : 0);
    std::fprintf(g_pLog, "C1Generation: %llu\n",
                 static_cast<unsigned long long>(r.c1Generation));
    switch (r.code)
    {
        case MarkerResult_RejectedUnsupportedHit:
            std::fprintf(g_pLog, "MarkerAction: REJECTED_UNSUPPORTED_HIT\n");
            break;
        case MarkerResult_RejectedMotionOwnership:
            std::fprintf(g_pLog, "MarkerAction: REJECTED_MOTION_OWNERSHIP\n");
            break;
        case MarkerResult_UnsupportedMissingSource:
            std::fprintf(g_pLog, "MarkerAction: UNSUPPORTED_MISSING_SOURCE\n");
            std::fprintf(g_pLog, "RequiredSourceMask: %u\n",
                         r.decision.requiredSourceMask);
            break;
        case MarkerResult_RejectedNoGeneration:
            std::fprintf(g_pLog, "MarkerAction: REJECTED_NO_C1_GENERATION\n");
            break;
        case MarkerResult_DuplicateIgnored:
            std::fprintf(g_pLog, "MarkerAction: DUPLICATE_SAME_UPDATE_IGNORED\n");
            std::fprintf(g_pLog, "DuplicateStateTimeDelta: %.9f\n",
                         r.duplicateStateTimeDelta);
            std::fprintf(g_pLog, "DuplicateElapsedMsDelta: %.6f\n",
                         r.duplicateElapsedMsDelta);
            break;
        case MarkerResult_RejectedGenerationInconsistency:
            std::fprintf(
                g_pLog,
                "MarkerAction: REJECTED_C1_GENERATION_INCONSISTENCY\n");
            break;
        case MarkerResult_BudgetIgnored:
            std::fprintf(g_pLog, "MarkerAction: AUTHORED_OCCURRENCE_BUDGET_IGNORED\n");
            break;
        case MarkerResult_OffAccepted:
            std::fprintf(g_pLog, "MarkerAction: OFF_ACCEPTED\n");
            break;
        case MarkerResult_OffNoWindow:
            std::fprintf(g_pLog, "MarkerAction: OFF_NO_MARKER_OWNED_WINDOW\n");
            break;
        case MarkerResult_RejectedEmptySourceSet:
            std::fprintf(g_pLog, "MarkerAction: REJECTED_EMPTY_SOURCE_SET\n");
            break;
        case MarkerResult_RejectedIncompleteActivation:
            std::fprintf(g_pLog, "MarkerAction: REJECTED_INCOMPLETE_ACTIVATION\n");
            std::fprintf(g_pLog, "MissingSourceMask: %u\n", r.missingSourceMask);
            break;
        case MarkerResult_Accepted:
            std::fprintf(g_pLog, "MarkerAction: ACCEPTED\n");
            break;
    }
    std::fprintf(g_pLog, "AuthoredMarkerOccurrences: %d\n",
                 r.authoredMarkerCount);
    std::fprintf(g_pLog, "AcceptedMarkerOccurrencesBefore: %d\n",
                 r.acceptedMarkerCountBefore);
    std::fprintf(g_pLog, "AcceptedMarkerOccurrencesAfter: %d\n",
                 r.acceptedMarkerCountAfter);
    std::fprintf(g_pLog, "ExecutionBudgetReset: %d\n",
                 r.executionBudgetReset ? 1 : 0);
    std::fprintf(g_pLog, "PreviousSourceMask: %u\n", r.previousSourceMask);
    std::fprintf(g_pLog, "DesiredSourceMask: %u\n", r.desiredSourceMask);
    std::fprintf(g_pLog, "RetiredSourceMask: %u\n", r.retiredSourceMask);
    std::fprintf(g_pLog, "OwnedMaskAtOff: %u\n", r.ownedMask);
    std::fprintf(g_pLog, "MarkerOwnedWeaponMask: %u\n",
                 r.markerOwnedWeaponMask);
    std::fprintf(g_pLog, "ActivatedSourceCount: %d\n",
                 r.activatedSourceCount);
    std::fprintf(g_pLog, "RetiredSourceCount: %d\n",
                 r.retiredSourceCount);
    std::fprintf(g_pLog, "DeactivatedSourceCount: %d\n",
                 r.deactivatedSourceCount);
    std::fprintf(g_pLog, "TriggeredListClearCount: %d\n",
                 r.triggeredListClearCount);
    for (GEInt i = 0; i < 2; ++i)
    {
        unsigned int const mask = i == 0 ? SourceMask_Right : SourceMask_Left;
        if ((r.desiredSourceMask & mask) == 0)
            continue;
        char const *label = i == 0 ? "Right" : "Left";
        std::fprintf(g_pLog, "%sGroupBefore: %d\n", label,
                     r.sourceGroupBefore[i]);
        std::fprintf(g_pLog, "%sGroupAfter: %d\n", label,
                     r.sourceGroupAfter[i]);
        std::fprintf(g_pLog, "%sUseType: %d\n", label,
                     r.sourceUseTypes[i]);
        std::fprintf(g_pLog, "%sGroupRequested: %d\n", label,
                     r.sourceGroupRequested[i] ? 1 : 0);
        std::fprintf(g_pLog, "%sFistGroupSkip: %d\n", label,
                     r.sourceSkippedGroupForFist[i] ? 1 : 0);
        std::fprintf(g_pLog, "%sTriggeredListCleared: %d\n", label,
                     r.sourceListCleared[i] ? 1 : 0);
    }
    if (r.quickStatePositionBeforeMarker >= 0)
    {
        std::fprintf(g_pLog, "QuickStatePositionBefore: %d\n",
                     r.quickStatePositionBeforeMarker);
        std::fprintf(g_pLog, "QuickStatePositionAfter: %d\n",
                     r.quickStatePositionAfterMarker);
    }
    if (r.whirlStatePositionBeforeMarker >= 0)
    {
        std::fprintf(g_pLog, "WhirlStatePositionBefore: %d\n",
                     r.whirlStatePositionBeforeMarker);
        std::fprintf(g_pLog, "WhirlStatePositionAfter: %d\n",
                     r.whirlStatePositionAfterMarker);
    }
    std::fprintf(g_pLog, "===========================\n\n");
    std::fflush(g_pLog);
}

static char const *PlayerSlotMatch(eCEntity *changedEntity)
{
    Entity player = Entity::GetPlayer();
    if (player == None)
        return "NO_PLAYER";
    EquippedCollisionSources const sources =
        CollisionSources::GetEquippedCollisionSources(player);
    bool const right = changedEntity != nullptr
        && changedEntity == sources.rightInstance;
    bool const left = changedEntity != nullptr
        && changedEntity == sources.leftInstance;
    if (right && left)
        return "BOTH";
    if (right)
        return "RIGHT";
    if (left)
        return "LEFT";
    return "NONE";
}

void LogSetCollisionGroup(
    eCEntity *changedEntity, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup, eECollisionGroup afterGroup,
    GEInt retiredMarkerSourceBitCount)
{
    if (g_pLog == nullptr || changedEntity == nullptr)
        return;
    bool const involvesAttack =
        requestedGroup == eECollisionGroup_Item_Attack
        || beforeGroup == eECollisionGroup_Item_Attack
        || afterGroup == eECollisionGroup_Item_Attack;
    if (!involvesAttack)
        return;

    std::fprintf(g_pLog, "===== ENGINE SetCollisionGroup =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                 RuntimeClock::GetElapsedMilliseconds());
    std::fprintf(g_pLog, "Source: %s\n", EntityName(changedEntity));
    std::fprintf(g_pLog, "SourceAddress: %p\n",
                 static_cast<void *>(changedEntity));
    std::fprintf(g_pLog, "SlotAssociation: %s\n",
                 PlayerSlotMatch(changedEntity));
    Entity player = Entity::GetPlayer();
    if (player != None)
    {
        bCString currentAni = player.NPC.GetCurrentMovementAni();
        std::fprintf(
            g_pLog, "PlayerAction: %d\n",
            static_cast<GEInt>(
                player.Routine.GetProperty<PSRoutine::PropertyAction>()));
        std::fprintf(g_pLog, "PlayerAniPhase: %d\n",
                     static_cast<GEInt>(player.GetCurrentAniPhase()));
        std::fprintf(g_pLog, "PlayerStateTime: %.6f\n",
                     player.Routine.GetStateTime());
        std::fprintf(g_pLog, "PlayerCurrentMovementAni: %s\n",
                     currentAni.GetText());
    }
    std::fprintf(g_pLog, "RequestedGroup: %d\n",
                 static_cast<GEInt>(requestedGroup));
    std::fprintf(g_pLog, "BeforeGroup: %d\n",
                 static_cast<GEInt>(beforeGroup));
    std::fprintf(g_pLog, "AfterGroup: %d\n",
                 static_cast<GEInt>(afterGroup));
    std::fprintf(g_pLog, "RetiredMarkerSourceBitCount: %d\n",
                 retiredMarkerSourceBitCount);
    std::fprintf(g_pLog, "====================================\n\n");
    std::fflush(g_pLog);
}

static void LogIssue(
    CollisionLifecycleGuard::LifecycleIssue const &issue)
{
    if (g_pLog == nullptr
        || issue.code == CollisionLifecycleGuard::LifecycleIssue_None)
        return;
    std::fprintf(g_pLog, "===== C1 INVARIANT WARNING =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                 RuntimeClock::GetElapsedMilliseconds());
    std::fprintf(g_pLog, "Code: %s\n", IssueName(issue.code));
    std::fprintf(g_pLog, "ActorAddress: %p\n",
                 static_cast<void *>(issue.actorInstance));
    std::fprintf(g_pLog, "Generation: %llu\n",
                 static_cast<unsigned long long>(issue.generation));
    std::fprintf(g_pLog, "SourceAddress: %p\n",
                 static_cast<void *>(issue.sourceInstance));
    std::fprintf(g_pLog, "================================\n\n");
}

static void LogBinding(
    CollisionLifecycleGuard::BindingObservation const &binding)
{
    using namespace CollisionLifecycleGuard;
    if (g_pLog == nullptr || binding.code == BindingEvent_None)
        return;
    if (!IsPlayerActor(binding.generation.actorInstance))
        return;
    std::fprintf(g_pLog, "===== C1 SCRIPT BINDING =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                 RuntimeClock::GetElapsedMilliseconds());
    std::fprintf(g_pLog, "Event: %s\n", BindingEventName(binding.code));
    std::fprintf(g_pLog, "Actor: %s\n",
                 EntityName(binding.generation.actorInstance));
    std::fprintf(g_pLog, "Generation: %llu\n",
                 static_cast<unsigned long long>(
                     binding.generation.generation));
    std::fprintf(g_pLog, "Status: %s\n",
                 GenerationStatusName(binding.generation.status));
    std::fprintf(g_pLog, "Outstanding: %d\n",
                 binding.generation.outstanding ? 1 : 0);
    std::fprintf(g_pLog, "ScriptFunction: %s\n",
                 binding.scriptName.c_str());
    std::fprintf(g_pLog, "SourceAddress: %p\n",
                 static_cast<void *>(binding.sourceInstance));
    std::fprintf(g_pLog, "=============================\n\n");
}

static void LogLifecycleStart(
    CollisionLifecycleGuard::LifecycleStartFacts const &start)
{
    if (g_pLog == nullptr || !start.available
        || !IsPlayerActor(start.generation.actorInstance))
        return;
    std::fprintf(g_pLog, "===== C1 LIFECYCLE START =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                 RuntimeClock::GetElapsedMilliseconds());
    std::fprintf(g_pLog, "Actor: %s\n",
                 EntityName(start.generation.actorInstance));
    std::fprintf(g_pLog, "Generation: %llu\n",
                 static_cast<unsigned long long>(
                     start.generation.generation));
    std::fprintf(g_pLog, "Status: %s\n",
                 GenerationStatusName(start.generation.status));
    std::fprintf(g_pLog, "ReplacedGeneration: %llu\n",
                 static_cast<unsigned long long>(start.replacedGeneration));
    std::fprintf(g_pLog, "ReplacedOutstanding: %d\n",
                 start.replacedOutstanding ? 1 : 0);
    std::fprintf(g_pLog, "TrackedSourceCount: %u\n",
                 start.generation.trackedSourceCount);
    for (unsigned int i = 0; i < start.generation.trackedSourceCount; ++i)
    {
        std::fprintf(g_pLog, "Source[%u].Address: %p\n", i,
                     static_cast<void *>(start.sources[i].sourceInstance));
        std::fprintf(g_pLog, "Source[%u].Side: %s\n", i,
                     SideName(start.sources[i].sideMask));
        std::fprintf(g_pLog, "Source[%u].ActualGroup: %d\n", i,
                     static_cast<GEInt>(start.sources[i].actualGroup));
    }
    std::fprintf(g_pLog, "==============================\n\n");
}

static void LogSourceEvent(
    char const *heading,
    CollisionLifecycleGuard::SourceEventFacts const &event)
{
    if (g_pLog == nullptr || !event.available
        || !IsPlayerActor(event.actorInstance))
        return;
    std::fprintf(g_pLog, "===== %s =====\n", heading);
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                 RuntimeClock::GetElapsedMilliseconds());
    std::fprintf(g_pLog, "Actor: %s\n", EntityName(event.actorInstance));
    std::fprintf(g_pLog, "Generation: %llu\n",
                 static_cast<unsigned long long>(event.generation));
    std::fprintf(g_pLog, "Status: %s\n",
                 GenerationStatusName(event.status));
    std::fprintf(g_pLog, "Source: %s\n", EntityName(event.sourceInstance));
    std::fprintf(g_pLog, "SourceAddress: %p\n",
                 static_cast<void *>(event.sourceInstance));
    std::fprintf(g_pLog, "Side: %s\n", SideName(event.sideMask));
    std::fprintf(g_pLog, "OffensiveRequestCount: %u\n",
                 event.offensiveRequestCount);
    std::fprintf(g_pLog, "Outstanding: %d\n",
                 event.outstandingCleanup ? 1 : 0);
    std::fprintf(g_pLog, "CleanupObserved: %d\n",
                 event.cleanupObserved ? 1 : 0);
    std::fprintf(g_pLog, "ActualGroup: %d\n",
                 static_cast<GEInt>(event.actualGroup));
    std::fprintf(g_pLog, "==============================\n\n");
}

void LogBeginCombatMoveResult(
    CollisionLifecycleGuard::BeginCombatMoveResult const &result)
{
    LogLifecycleStart(result.start);
    LogBinding(result.binding);
    LogIssue(result.issue);
    if (g_pLog != nullptr)
        std::fflush(g_pLog);
}

void LogCompleteCombatMoveResult(
    CollisionLifecycleGuard::CompleteCombatMoveResult const &result)
{
    using namespace CollisionLifecycleGuard;
    if (g_pLog != nullptr && result.statusEvent != CandidateStatus_None
        && IsPlayerActor(result.generation.actorInstance))
    {
        std::fprintf(g_pLog, "===== C1 LIFECYCLE STATUS =====\n");
        std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                     RuntimeClock::GetElapsedMilliseconds());
        std::fprintf(g_pLog, "Event: %s\n",
                     result.statusEvent == CandidateStatus_Persisted
                         ? "PERSISTED" : "CANCELLED_IMMEDIATE_RESULT");
        std::fprintf(g_pLog, "Actor: %s\n",
                     EntityName(result.generation.actorInstance));
        std::fprintf(g_pLog, "Generation: %llu\n",
                     static_cast<unsigned long long>(
                         result.generation.generation));
        std::fprintf(g_pLog, "Status: %s\n",
                     GenerationStatusName(result.generation.status));
        std::fprintf(g_pLog, "Outstanding: %d\n",
                     result.generation.outstanding ? 1 : 0);
        std::fprintf(g_pLog, "===============================\n\n");
    }
    LogIssue(result.issue);
    if (g_pLog != nullptr)
        std::fflush(g_pLog);
}

void LogCollisionObservationResult(
    CollisionLifecycleGuard::CollisionObservationResult const &result)
{
    LogLifecycleStart(result.start);
    LogBinding(result.binding);
    if (result.offenseRequestObserved)
        LogSourceEvent("C1 OFFENSE REQUEST", result.sourceEvent);
    if (result.cleanupFulfilledObserved)
        LogSourceEvent("C1 CLEANUP FULFILLED", result.sourceEvent);
    LogIssue(result.issue);
    if (g_pLog != nullptr)
        std::fflush(g_pLog);
}

void LogBridgeRetirementResult(
    CollisionLifecycleGuard::BridgeRetirementResult const &result)
{
    LogIssue(result.issue);
    if (g_pLog != nullptr)
        std::fflush(g_pLog);
}

void LogFinalizationResult(
    CollisionLifecycleGuard::FinalizationResult const &result)
{
    LogIssue(result.issue);
    if (g_pLog == nullptr || !result.available
        || !IsPlayerActor(result.actorInstance))
        return;

    std::fprintf(g_pLog, "===== C1 FINALIZATION =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                 RuntimeClock::GetElapsedMilliseconds());
    std::fprintf(g_pLog, "Reason: AISETSTATE_AFTER_ORIGINAL\n");
    std::fprintf(g_pLog, "Actor: %s\n", EntityName(result.actorInstance));
    std::fprintf(g_pLog, "Generation: %llu\n",
                 static_cast<unsigned long long>(result.generation));
    std::fprintf(g_pLog, "Status: %s\n",
                 GenerationStatusName(result.status));
    std::fprintf(g_pLog, "TrackedSourceCount: %u\n", result.sourceCount);
    for (unsigned int i = 0; i < result.sourceCount; ++i)
    {
        auto const &source = result.sources[i];
        std::fprintf(g_pLog, "Source[%u].Outcome: %s\n", i,
                     FinalizationOutcomeName(source.outcome));
        std::fprintf(g_pLog, "Source[%u].Address: %p\n", i,
                     static_cast<void *>(source.sourceInstance));
        std::fprintf(g_pLog, "Source[%u].LivenessEstablished: %d\n", i,
                     source.livenessEstablished ? 1 : 0);
        if (source.livenessEstablished)
        {
            std::fprintf(g_pLog, "Source[%u].Name: %s\n", i,
                         EntityName(source.sourceInstance));
        }
        else
        {
            std::fprintf(g_pLog,
                         "Source[%u].Name: <not-dereferenced>\n", i);
        }
        std::fprintf(g_pLog, "Source[%u].OriginalSide: %s\n", i,
                     SideName(source.originalSideMask));
        std::fprintf(g_pLog, "Source[%u].CurrentSideMask: %u\n", i,
                     source.currentSideMask);
        std::fprintf(g_pLog, "Source[%u].OffensiveRequestCount: %u\n", i,
                     source.offensiveRequestCount);
        std::fprintf(g_pLog,
                     "Source[%u].OutstandingBeforeFinalization: %d\n", i,
                     source.outstandingBeforeFinalization ? 1 : 0);
        std::fprintf(g_pLog,
                     "Source[%u].CleanupObservedBeforeFinalization: %d\n", i,
                     source.cleanupObservedBeforeFinalization ? 1 : 0);
        std::fprintf(g_pLog, "Source[%u].ActualGroupBeforeRepair: %d\n", i,
                     static_cast<GEInt>(source.actualGroupBeforeRepair));
        std::fprintf(g_pLog, "Source[%u].RepairAttempted: %d\n", i,
                     source.repairAttempted ? 1 : 0);
        if (source.repairAttempted)
        {
            std::fprintf(g_pLog, "Source[%u].RepairRequestedGroup: %d\n", i,
                         static_cast<GEInt>(source.repairRequestedGroup));
            std::fprintf(g_pLog, "Source[%u].ActualGroupAfterRepair: %d\n", i,
                         static_cast<GEInt>(source.actualGroupAfterRepair));
        }
        std::fprintf(g_pLog, "Source[%u].PhysicalCollisionChanged: %d\n", i,
                     source.physicalCollisionChanged ? 1 : 0);
    }
    std::fprintf(g_pLog, "PhysicalCollisionChanged: %d\n",
                 result.physicalCollisionChanged ? 1 : 0);
    std::fprintf(g_pLog, "===========================\n\n");
    std::fflush(g_pLog);
}

void LogRunScriptFunctionScopeReturn(
    void *scopeAddress, bool parentScopeExists, GEBool nativeResult)
{
    if (g_pLog == nullptr)
        return;
    std::fprintf(g_pLog, "===== C1 DISPATCH RETURN =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                 RuntimeClock::GetElapsedMilliseconds());
    std::fprintf(g_pLog, "ScopeAddress: %p\n", scopeAddress);
    std::fprintf(g_pLog, "ParentScopeExists: %d\n",
                 parentScopeExists ? 1 : 0);
    std::fprintf(g_pLog, "NativeResult: %d\n",
                 nativeResult == GETrue ? 1 : 0);
    std::fprintf(g_pLog, "==============================\n\n");
    std::fflush(g_pLog);
}
}

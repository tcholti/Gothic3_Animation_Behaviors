#include "CollisionDiagnostics.h"

#include "CollisionControl.h"
#include "HookBridgeRuntime.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <unordered_map>

#include <windows.h>

namespace FrameCollision::CollisionDiagnostics
{
struct LifetimeState
{
    bool initialized;
    bool lastHasPrimaryMotionInstance;
    bool lastPrimaryMotionRunning;
    GEDouble lastPrimaryPlayTime;
    GEDouble lastPrimaryMaxTime;
    GEInt lastObservedAction;
    GEInt lastObservedPhase;
    std::string lastObservedMovementAni;
    std::string lastPrimaryMotionName;
};

static FILE *g_pLog = nullptr;
static std::unordered_map<eCEntity *, std::string> g_LastLoggedAni;
static std::unordered_map<eCEntity *, LifetimeState> g_LifetimeStateByActor;

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

void OpenLog()
{
    std::string logPath = GetGameDirectory() + "\\Script_FrameCollisionTest.log";
    g_pLog = std::fopen(logPath.c_str(), "w");
    if (g_pLog == nullptr)
        return;

    std::fprintf(g_pLog, "Script_FrameCollisionTest v0.20 loaded.\n");
    std::fprintf(g_pLog, "GENERALIZED ACTOR / WEAPON-SLOT PROTOTYPE.\n");
    std::fprintf(g_pLog, "NO IsPlayer restriction.\n");
    std::fprintf(g_pLog, "NO 2H / Staff / 1H use-type restriction.\n");
    std::fprintf(g_pLog, "NO P0/P1/P2 restriction.\n");
    std::fprintf(g_pLog, "Normal eligibility: exact Attack action + Hit phase + current _Attack_Hit_ motion + RIGHT/LEFT/BOTH source marker.\n");
    std::fprintf(g_pLog, "Quick eligibility: OnAI_QuickAttack + exact Quick/QuickR/QuickL action + Hit phase + a RIGHT/LEFT/BOTH source marker.\n");
    std::fprintf(g_pLog, "Accepted Quick marker completes one-shot callback bookkeeping: StatePosition -> 1.\n");
    std::fprintf(g_pLog, "Full Whirl eligibility: OnAI_WhirlAttack + exact WhirlAttack action + Hit phase + a RIGHT/LEFT/BOTH source marker.\n");
    std::fprintf(g_pLog, "Accepted full-Whirl marker completes one-shot callback bookkeeping: StatePosition -> 1.\n");
    std::fprintf(g_pLog, "Full Whirl uses explicit marker windows; ResetOnUntouch is NOT enabled.\n");
    std::fprintf(g_pLog, "v0.20 PRIMARY-MOTION LIFETIME PROBE: read-only; cleanup behavior is unchanged.\n");
    std::fprintf(g_pLog, "STEP B1 PRIMARYFIRST EVENT PROBE: PlayMotion/StopMotion request/result snapshots; diagnostic-only.\n");
    std::fprintf(g_pLog, "STEP B3 COMBATMOVE STARTRECOVER BOUNDARY PROBE: player-only BEGIN/END snapshots; diagnostic-only.\n");
    std::fprintf(g_pLog, "STEP B4 NATIVE CLEANUP CALL-SITE PROBE: exact player weapon 7 -> 5 caller module/RVA; diagnostic-only.\n");
    std::fprintf(g_pLog, "STEP B5 CLEANUP PARENT-STACK PROBE: short Win32-captured raw stack for exact player weapon 7 -> 5 cleanup; diagnostic-only.\n");
    std::fprintf(g_pLog, "STEP B6 HIT STARTRECOVER / STOP / REPLACEMENT / UNGATED EMPTY-PRIMARY SUCCESSOR STACK PROBE: player PrimaryFirst outgoing attack-Hit or factual empty-Primary successor stack; diagnostic-only.\n");
    std::fprintf(g_pLog, "STEP B7 COMBATMOVE FULLSTOP STACK PROBE: player sAICombatMoveInstr fullStop=true caller/context stack; diagnostic-only.\n");
    std::fprintf(g_pLog, "v0.20 probe runs only while a marker-owned collision window exists.\n");
    std::fprintf(g_pLog, "Dual SimpleWhirl remains on the original OnAI_SimpleWhirl callback in v0.19.\n");
    std::fprintf(g_pLog, "FIST CAUSAL TEST: raw Fist/PhysicalFist skips SetCollisionGroup(Item_Attack).\n");
    std::fprintf(g_pLog, "FIST CAUSAL TEST: ClearTriggeredList remains active.\n");
    std::fprintf(g_pLog, "G3AB_COL_RIGHT is the final RIGHT equipped-slot marker.\n");
    std::fprintf(g_pLog, "G3AB_COL_LEFT is the final LEFT equipped-slot marker.\n");
    std::fprintf(g_pLog, "G3AB_COL_BOTH is the final BOTH equipped-slot marker.\n");
    std::fprintf(g_pLog, "RIGHT, LEFT, and BOTH use exact-set semantics: the selected source set replaces the previous marker-owned set.\n");
    std::fprintf(g_pLog, "BOTH activates/rearms the right and left equipped slot entities independently at one authored marker.\n");
    std::fprintf(g_pLog, "If any source required by the exact motion is missing, its original attack callback is NOT suppressed.\n");
    std::fprintf(g_pLog, "This protects unarmed/monster attacks until body-source resolution is implemented.\n");
    std::fprintf(g_pLog, "Marker action: non-Fist -> Item_Attack + ClearTriggeredList; Fist -> ClearTriggeredList only.\n");
    std::fprintf(g_pLog, "G3AB_COL_OFF closes only a weapon window opened by this prototype.\n");
    std::fprintf(g_pLog, "OFF requests Item_Equipped and never clears the triggered list.\n");
    std::fprintf(g_pLog, "OFF before ON or after natural reset is consumed as a logged no-op.\n");
    std::fprintf(g_pLog, "Fist/body OFF remains unsupported; Gothic 3 still owns Hit->Recover reset.\n");
    std::fprintf(g_pLog, "Known collision groups: Item_Equipped=5, Item_Attack=7.\n");
    std::fprintf(g_pLog, "PASSIVE DUAL DISCOVERY: Item_Attack transitions are labelled by exact player LEFT/RIGHT slot entity identity.\n");
    std::fprintf(g_pLog, "A Dual both-weapon activation normally appears as separate LEFT and RIGHT transition records.\n");
    std::fprintf(g_pLog, "Preserved RIGHT and LEFT Normal paths passed v0.14 source validation.\n\n");
    std::fprintf(g_pLog, "v0.19 adds only the full 2H/Staff OnAI_WhirlAttack adapter.\n");
    std::fprintf(g_pLog, "v0.19 preserves the validated v0.18 Normal/Quick RIGHT/LEFT/BOTH/OFF core unchanged.\n");
    std::fprintf(g_pLog, "No Dual SimpleWhirl, Power, collision-source, timing, or cleanup behavior is added in v0.19.\n");
    std::fprintf(g_pLog, "Dedup key: actor + RIGHT/LEFT slot snapshot + motion + marker + action + phase + state time; wall window <= 5 ms.\n\n");
    std::fprintf(g_pLog, "Authored-occurrence budgets are cached separately for RIGHT, LEFT, BOTH, and OFF.\n");
    std::fprintf(g_pLog, "Budget key: actor + RIGHT/LEFT slot snapshot + motion + action + phase.\n");
    std::fprintf(g_pLog, "Marker-time or controlled-callback state-time rollback starts a new execution.\n");
    std::fprintf(g_pLog, "Natural collision reset outside the owning Hit execution retires the actor budget.\n");
    std::fprintf(g_pLog, "No per-frame actor scan; budget work occurs only when a reserved marker is received.\n\n");
    std::fflush(g_pLog);
}

void CloseLog()
{
    if (g_pLog == nullptr)
        return;
    std::fprintf(g_pLog, "Script_FrameCollisionTest unloading.\n");
    std::fflush(g_pLog);
    std::fclose(g_pLog);
    g_pLog = nullptr;
}

bool IsLogOpen() { return g_pLog != nullptr; }
FILE *GetLog() { return g_pLog; }

static char const *BaseName(char const *path)
{
    if (path == nullptr)
        return "";
    char const *slash1 = std::strrchr(path, '\\');
    char const *slash2 = std::strrchr(path, '/');
    char const *last = slash1;
    if (slash2 != nullptr && (last == nullptr || slash2 > last))
        last = slash2;
    return last != nullptr ? last + 1 : path;
}

static bool SameFileName(char const *a, char const *b)
{
    return a != nullptr && b != nullptr && _stricmp(BaseName(a), BaseName(b)) == 0;
}

static bool Contains(char const *text, char const *token)
{
    return text != nullptr && token != nullptr && std::strstr(text, token) != nullptr;
}

static bool IsAttackHitMotionName(char const *motionName)
{
    static char const *const AttackHitTokens[] =
    {
        "_Attack_Hit_",
        "_PowerAttack_Hit_",
        "_QuickAttack_Hit_",
        "_SimpleWhirl_Hit_",
        "_SprintAttack_Hit_",
        "_WhirlAttack_Hit_",
        "_PierceAttack_Hit_",
        "_JumpAttack_Hit_",
        "_RamAttack_Hit_",
        "_HackAttack_Hit_",
        "_FinishingAttack_Hit_",
        "_GetUpAttack_Hit_"
    };
    for (char const *token : AttackHitTokens)
    {
        if (Contains(motionName, token))
            return true;
    }
    return false;
}

static void LogResolvedSource(char const *label, eCEntity *sourceInstance)
{
    if (g_pLog == nullptr)
        return;
    std::fprintf(g_pLog, "%sSourceResolved: %d\n", label, sourceInstance != nullptr ? 1 : 0);
    if (sourceInstance == nullptr)
        return;
    Entity source(sourceInstance);
    std::fprintf(g_pLog, "%sSource: %s\n", label, source.GetName().GetText());
    std::fprintf(g_pLog, "%sSourceAddress: %p\n", label, static_cast<void *>(sourceInstance));
    std::fprintf(g_pLog, "%sSourceUseType: %d\n", label,
                 static_cast<GEInt>(CollisionControl::GetCollisionSourceUseType(source)));
    std::fprintf(g_pLog, "%sSourceCollisionGroup: %d\n", label,
                 static_cast<GEInt>(source.GetCollisionGroup()));
}

bool ShouldLogOwnership(Entity &actor)
{
    eCEntity *instance = actor.GetInstance();
    if (instance == nullptr)
        return true;
    bCString ani = actor.NPC.GetCurrentMovementAni();
    std::string currentName = ani.GetText() != nullptr ? ani.GetText() : "";
    auto found = g_LastLoggedAni.find(instance);
    if (found != g_LastLoggedAni.end() && found->second == currentName)
        return false;
    g_LastLoggedAni[instance] = currentName;
    return true;
}

void LogOwnershipDecision(Entity &actor, CurrentMotionMarkerResult const &decision,
                          EquippedCollisionSources const &sources, bool willSuppress)
{
    if (g_pLog == nullptr)
        return;
    bCString ani = actor.NPC.GetCurrentMovementAni();
    std::fprintf(g_pLog, "===== MARKER OWNERSHIP DECISION =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n", HookBridgeRuntime::GetElapsedMilliseconds());
    std::fprintf(g_pLog, "Actor: %s\n", actor.GetName().GetText());
    std::fprintf(g_pLog, "CurrentMovementAni: %s\n", ani.GetText());
    std::fprintf(g_pLog, "MatchingMotionFound: %d\n", decision.foundMatchingMotion ? 1 : 0);
    std::fprintf(g_pLog, "FrameEffectCount: %d\n", decision.frameEffectCount);
    std::fprintf(g_pLog, "ContainsReservedSourceMarker: %d\n", decision.markerPresent ? 1 : 0);
    std::fprintf(g_pLog, "RequiredSourceMask: %u\n", decision.requiredSourceMask);
    for (GEInt opcode = 0; opcode < MarkerOpcode_Count; ++opcode)
    {
        std::fprintf(g_pLog, "Authored%sMarkerCount: %d\n",
                     CollisionControl::GetMarkerOpcodeName(static_cast<MarkerOpcode>(opcode)),
                     decision.markerCounts[opcode]);
        std::fprintf(g_pLog, "First%sMarkerFrame: %d\n",
                     CollisionControl::GetMarkerOpcodeName(static_cast<MarkerOpcode>(opcode)),
                     decision.firstMarkerFrames[opcode]);
    }
    LogResolvedSource("RightHand", sources.rightInstance);
    LogResolvedSource("LeftHand", sources.leftInstance);
    std::fprintf(g_pLog, "Decision: %s\n",
                 willSuppress ? "FRAME-CONTROLLED - suppress original timer callback"
                              : "LEGACY/NATIVE - call original timer callback");
    if (decision.markerPresent
        && !CollisionControl::HasRequiredCollisionSources(sources, decision.requiredSourceMask))
        std::fprintf(g_pLog, "Reason: at least one source required by the exact motion is missing.\n");
    std::fprintf(g_pLog, "=====================================\n\n");
    std::fflush(g_pLog);
}

void LogControlledCallbackBoundary(Entity &actor,
                                   ControlledCallbackObservation const &observation)
{
    if (g_pLog == nullptr || !observation.executionRetired)
        return;
    std::fprintf(g_pLog, "===== CONTROLLED CALLBACK EXECUTION BOUNDARY =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n", HookBridgeRuntime::GetElapsedMilliseconds());
    std::fprintf(g_pLog, "Actor: %s\n", actor.GetName().GetText());
    std::fprintf(g_pLog, "CurrentMovementAni: %s\n", observation.currentAnimation.GetText());
    std::fprintf(g_pLog, "Action: %d\n", observation.currentAction);
    std::fprintf(g_pLog, "AniPhase: %d\n", observation.currentPhase);
    std::fprintf(g_pLog, "PreviousControlledCallbackStateTime: %.6f\n", observation.previousStateTime);
    std::fprintf(g_pLog, "CurrentControlledCallbackStateTime: %.6f\n", observation.currentStateTime);
    std::fprintf(g_pLog, "ExecutionBoundaryKeyChanged: %d\n", observation.keyChanged ? 1 : 0);
    std::fprintf(g_pLog, "ExecutionBoundaryStateTimeRollback: %d\n",
                 observation.stateTimeRolledBack ? 1 : 0);
    std::fprintf(g_pLog, "MarkerExecutionBudget: RETIRED_BEFORE_MARKER\n");
    std::fprintf(g_pLog, "=====================================\n\n");
    std::fflush(g_pLog);
}

void LogNullMarker(char const *markerName)
{
    if (g_pLog == nullptr)
        return;
    std::fprintf(g_pLog, "===== %s RECEIVED =====\n", markerName != nullptr ? markerName : "<null>");
    std::fprintf(g_pLog, "MarkerAction: REJECTED - Entity1 == NULL\n");
    std::fprintf(g_pLog, "=================================\n\n");
    std::fflush(g_pLog);
}

void LogMarkerContext(char const *markerName, MarkerOpcode opcode, Entity &actor,
                      EquippedCollisionSources const &sources)
{
    if (g_pLog == nullptr)
        return;
    bCString ani = actor.NPC.GetCurrentMovementAni();
    std::fprintf(g_pLog, "===== %s RECEIVED =====\n", markerName != nullptr ? markerName : "<null>");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n", HookBridgeRuntime::GetElapsedMilliseconds());
    std::fprintf(g_pLog, "Actor: %s\n", actor.GetName().GetText());
    std::fprintf(g_pLog, "Action: %d\n",
                 static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyAction>()));
    std::fprintf(g_pLog, "AniPhase: %d\n", static_cast<GEInt>(actor.GetCurrentAniPhase()));
    std::fprintf(g_pLog, "StateTime: %.6f\n", actor.Routine.GetStateTime());
    std::fprintf(g_pLog, "StatePosition: %d\n",
                 static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>()));
    std::fprintf(g_pLog, "CurrentMovementAni: %s\n", ani.GetText());
    std::fprintf(g_pLog, "MarkerOpcode: %s\n", CollisionControl::GetMarkerOpcodeName(opcode));
    LogResolvedSource("RightHand", sources.rightInstance);
    LogResolvedSource("LeftHand", sources.leftInstance);
}

void LogMarkerResult(MarkerProcessResult const &r)
{
    if (g_pLog == nullptr)
        return;
    switch (r.code)
    {
        case MarkerResult_RejectedUnsupportedHit:
            std::fprintf(g_pLog, "MarkerAction: REJECTED - unsupported Normal/Quick/full-Whirl action or Hit phase\n");
            break;
        case MarkerResult_RejectedMotionOwnership:
            std::fprintf(g_pLog, "MarkerAction: REJECTED - current matching motion does not own marker\n");
            break;
        case MarkerResult_UnsupportedMissingSource:
            std::fprintf(g_pLog, "MarkerAction: UNSUPPORTED SOURCE - exact motion requires a missing equipped slot; original attack-family callback was left active\n");
            std::fprintf(g_pLog, "RequiredSourceMask: %u\n", r.decision.requiredSourceMask);
            break;
        case MarkerResult_DuplicateIgnored:
            std::fprintf(g_pLog, "MarkerAction: DUPLICATE_SAME_UPDATE_IGNORED\n");
            std::fprintf(g_pLog, "AuthoredMarkerFrame: %d\n",
                         CollisionControl::GetFirstAuthoredMarkerFrame(r.decision, r.opcode));
            std::fprintf(g_pLog, "DuplicateStateTimeDelta: %.9f\n", r.duplicateStateTimeDelta);
            std::fprintf(g_pLog, "DuplicateElapsedMsDelta: %.6f\n", r.duplicateElapsedMsDelta);
            std::fprintf(g_pLog, "SetCollisionGroupAction: NOT_REQUESTED_DUPLICATE\n");
            std::fprintf(g_pLog, "TriggeredDamageList: NOT_CLEARED_DUPLICATE\n");
            std::fprintf(g_pLog, "Original StartEffect for marker: NOT CALLED\n");
            break;
        case MarkerResult_BudgetIgnored:
            std::fprintf(g_pLog, "MarkerAction: AUTHORED_OCCURRENCE_BUDGET_IGNORED\n");
            std::fprintf(g_pLog, "MarkerName: %s\n", r.markerName.c_str());
            std::fprintf(g_pLog, "AuthoredMarkerOccurrences: %d\n", r.authoredMarkerCount);
            std::fprintf(g_pLog, "AcceptedMarkerOccurrencesBefore: %d\n", r.acceptedMarkerCountBefore);
            std::fprintf(g_pLog, "AcceptedMarkerOccurrencesAfter: %d\n", r.acceptedMarkerCountAfter);
            std::fprintf(g_pLog, "ExecutionBudgetReset: %d\n", r.executionBudgetReset ? 1 : 0);
            std::fprintf(g_pLog, "SetCollisionGroupAction: NOT_REQUESTED_BUDGET_EXHAUSTED\n");
            std::fprintf(g_pLog, "TriggeredDamageList: NOT_CLEARED_BUDGET_EXHAUSTED\n");
            std::fprintf(g_pLog, "Original StartEffect for marker: NOT CALLED\n");
            break;
        case MarkerResult_OffAccepted:
        case MarkerResult_OffNoWindow:
            std::fprintf(g_pLog, "MarkerAction: %s\n",
                         r.code == MarkerResult_OffAccepted ? "OFF_ACCEPTED"
                                                           : "OFF_NO_MARKER_OWNED_WINDOW");
            std::fprintf(g_pLog, "MarkerName: %s\n", r.markerName.c_str());
            std::fprintf(g_pLog, "MarkerOpcode: %s\n", CollisionControl::GetMarkerOpcodeName(r.opcode));
            std::fprintf(g_pLog, "AuthoredMarkerOccurrences: %d\n", r.authoredMarkerCount);
            std::fprintf(g_pLog, "AcceptedMarkerOccurrencesBefore: %d\n", r.acceptedMarkerCountBefore);
            std::fprintf(g_pLog, "AcceptedMarkerOccurrencesAfter: %d\n", r.acceptedMarkerCountAfter);
            std::fprintf(g_pLog, "ExecutionBudgetReset: %d\n", r.executionBudgetReset ? 1 : 0);
            std::fprintf(g_pLog, "AuthoredMarkerFrame: %d\n",
                         CollisionControl::GetFirstAuthoredMarkerFrame(r.decision, r.opcode));
            std::fprintf(g_pLog, "MarkerOwnedSourceMaskBeforeOff: %u\n", r.ownedMask);
            std::fprintf(g_pLog, "DeactivatedSourceCount: %d\n", r.deactivatedSourceCount);
            std::fprintf(g_pLog, "SetCollisionGroupAction: %s\n",
                         r.deactivatedSourceCount > 0
                             ? "REQUESTED_ITEM_EQUIPPED_FOR_OWNED_SOURCES"
                             : "NO_ACTIVE_WEAPON_SOURCE_TO_DEACTIVATE");
            std::fprintf(g_pLog, "TriggeredDamageList: NOT_CLEARED_OFF\n");
            std::fprintf(g_pLog, "Original StartEffect for marker: NOT CALLED\n");
            break;
        case MarkerResult_RejectedEmptySourceSet:
            std::fprintf(g_pLog, "MarkerAction: REJECTED - source marker selected an empty source set\n");
            break;
        case MarkerResult_RejectedIncompleteActivation:
            std::fprintf(g_pLog, "MarkerAction: REJECTED - selected source set is incomplete at activation\n");
            std::fprintf(g_pLog, "MissingSourceMask: %u\n", r.missingSourceMask);
            break;
        case MarkerResult_Accepted:
        {
            unsigned int sourceMasks[2] = { SourceMask_Right, SourceMask_Left };
            char const *sourceLabels[2] = { "Right", "Left" };
            GEInt diagnosticIndex = (r.desiredSourceMask & SourceMask_Right) != 0 ? 0 : 1;
            std::fprintf(g_pLog, "MarkerAction: ACCEPTED\n");
            std::fprintf(g_pLog, "MarkerName: %s\n", r.markerName.c_str());
            std::fprintf(g_pLog, "MarkerOpcode: %s\n", CollisionControl::GetMarkerOpcodeName(r.opcode));
            std::fprintf(g_pLog, "AuthoredMarkerOccurrences: %d\n", r.authoredMarkerCount);
            std::fprintf(g_pLog, "AcceptedMarkerOccurrencesBefore: %d\n", r.acceptedMarkerCountBefore);
            std::fprintf(g_pLog, "AcceptedMarkerOccurrencesAfter: %d\n", r.acceptedMarkerCountAfter);
            std::fprintf(g_pLog, "ExecutionBudgetReset: %d\n", r.executionBudgetReset ? 1 : 0);
            std::fprintf(g_pLog, "AuthoredMarkerFrame: %d\n",
                         CollisionControl::GetFirstAuthoredMarkerFrame(r.decision, r.opcode));
            std::fprintf(g_pLog, "PreviousMarkerOwnedSourceMask: %u\n", r.previousSourceMask);
            std::fprintf(g_pLog, "DesiredMarkerOwnedSourceMask: %u\n", r.desiredSourceMask);
            std::fprintf(g_pLog, "RetiredMarkerOwnedSourceMask: %u\n", r.retiredSourceMask);
            std::fprintf(g_pLog, "RetiredSourceCount: %d\n", r.retiredSourceCount);
            std::fprintf(g_pLog, "MarkerOwnedWeaponSourceMaskAfterActivation: %u\n",
                         r.markerOwnedWeaponMask);
            std::fprintf(g_pLog, "CollisionGroupBeforeMarker: %d\n", r.sourceGroupBefore[diagnosticIndex]);
            std::fprintf(g_pLog, "CollisionGroupAfterMarker: %d\n", r.sourceGroupAfter[diagnosticIndex]);
            std::fprintf(g_pLog, "ResolvedSourceUseTypeAtMarker: %d\n", r.sourceUseTypes[diagnosticIndex]);
            std::fprintf(g_pLog, "ActivatedSourceCount: %d\n", r.activatedSourceCount);
            std::fprintf(g_pLog, "CollisionGroupRequestCount: %d\n", r.collisionGroupRequestCount);
            std::fprintf(g_pLog, "FistSourceCount: %d\n", r.fistSourceCount);
            std::fprintf(g_pLog, "TriggeredDamageListClearCount: %d\n", r.triggeredListClearCount);
            for (GEInt i = 0; i < 2; ++i)
            {
                if ((r.desiredSourceMask & sourceMasks[i]) == 0)
                    continue;
                std::fprintf(g_pLog, "%sCollisionGroupBeforeMarker: %d\n", sourceLabels[i], r.sourceGroupBefore[i]);
                std::fprintf(g_pLog, "%sCollisionGroupAfterMarker: %d\n", sourceLabels[i], r.sourceGroupAfter[i]);
                std::fprintf(g_pLog, "%sResolvedSourceUseTypeAtMarker: %d\n", sourceLabels[i], r.sourceUseTypes[i]);
                std::fprintf(g_pLog, "%sSetCollisionGroupRequested: %d\n", sourceLabels[i], r.sourceGroupRequested[i] ? 1 : 0);
                std::fprintf(g_pLog, "%sSkippedCollisionGroupForFist: %d\n", sourceLabels[i], r.sourceSkippedGroupForFist[i] ? 1 : 0);
                std::fprintf(g_pLog, "%sTriggeredDamageListCleared: %d\n", sourceLabels[i], r.sourceListCleared[i] ? 1 : 0);
            }
            std::fprintf(g_pLog, "SetCollisionGroupAction: %s\n",
                         r.collisionGroupRequestCount == 0 ? "SKIPPED_FOR_FIST_CAUSAL_TEST"
                       : r.activatedSourceCount > 1 ? "REQUESTED_ITEM_ATTACK_FOR_SOURCE_SET"
                                                     : "REQUESTED_ITEM_ATTACK");
            std::fprintf(g_pLog, "TriggeredDamageList: %s\n",
                         r.triggeredListClearCount > 1 ? "CLEARED_FOR_SOURCE_SET" : "CLEARED");
            if (r.quickStatePositionBeforeMarker >= 0)
            {
                std::fprintf(g_pLog, "QuickStatePositionBeforeMarker: %d\n", r.quickStatePositionBeforeMarker);
                std::fprintf(g_pLog, "QuickStatePositionAfterMarker: %d\n", r.quickStatePositionAfterMarker);
            }
            if (r.whirlStatePositionBeforeMarker >= 0)
            {
                std::fprintf(g_pLog, "WhirlStatePositionBeforeMarker: %d\n", r.whirlStatePositionBeforeMarker);
                std::fprintf(g_pLog, "WhirlStatePositionAfterMarker: %d\n", r.whirlStatePositionAfterMarker);
            }
            std::fprintf(g_pLog, "Original StartEffect for marker: NOT CALLED\n");
            break;
        }
    }
    std::fprintf(g_pLog, "=================================\n\n");
    std::fflush(g_pLog);
}

struct PlayerSlotIdentityResult
{
    char const *slotMatch;
    bool matchesEquippedSource;
};

static PlayerSlotIdentityResult LogPlayerSlotIdentity(eCEntity *changedEntity)
{
    Entity player = Entity::GetPlayer();
    if (player == None)
    {
        std::fprintf(g_pLog, "PlayerSlotMatch: NO_PLAYER\n");
        return { "NO_PLAYER", false };
    }
    Entity leftItem = player.Inventory.GetItemFromSlot(gESlot_LeftHand);
    Entity rightItem = player.Inventory.GetItemFromSlot(gESlot_RightHand);
    eCEntity *leftInstance = leftItem != None ? leftItem.GetInstance() : nullptr;
    eCEntity *rightInstance = rightItem != None ? rightItem.GetInstance() : nullptr;
    bool matchesLeft = changedEntity != nullptr && changedEntity == leftInstance;
    bool matchesRight = changedEntity != nullptr && changedEntity == rightInstance;
    char const *slotMatch = matchesLeft && matchesRight ? "BOTH"
                          : matchesLeft ? "LEFT" : matchesRight ? "RIGHT" : "NONE";
    bCString currentAni = player.NPC.GetCurrentMovementAni();
    std::fprintf(g_pLog, "ChangedEntityAddress: %p\n", static_cast<void *>(changedEntity));
    std::fprintf(g_pLog, "PlayerSlotMatch: %s\n", slotMatch);
    std::fprintf(g_pLog, "PlayerAction: %d\n", static_cast<GEInt>(player.Routine.GetProperty<PSRoutine::PropertyAction>()));
    std::fprintf(g_pLog, "PlayerAniPhase: %d\n", static_cast<GEInt>(player.GetCurrentAniPhase()));
    std::fprintf(g_pLog, "PlayerPrimaryPose: %d\n", static_cast<GEInt>(player.NPC.GetPrimaryPose()));
    std::fprintf(g_pLog, "PlayerStateTime: %.6f\n", player.Routine.GetStateTime());
    std::fprintf(g_pLog, "PlayerStatePosition: %d\n", static_cast<GEInt>(player.Routine.GetProperty<PSRoutine::PropertyStatePosition>()));
    std::fprintf(g_pLog, "PlayerCurrentMovementAni: %s\n", currentAni.GetText());
    std::fprintf(g_pLog, "PlayerLeftItem: %s\n", leftItem != None ? leftItem.GetName().GetText() : "<none>");
    std::fprintf(g_pLog, "PlayerLeftItemAddress: %p\n", static_cast<void *>(leftInstance));
    std::fprintf(g_pLog, "PlayerLeftUseType: %d\n", leftItem != None ? static_cast<GEInt>(CollisionControl::GetCollisionSourceUseType(leftItem)) : -1);
    std::fprintf(g_pLog, "PlayerLeftCollisionGroup: %d\n", leftItem != None ? static_cast<GEInt>(leftItem.GetCollisionGroup()) : -1);
    std::fprintf(g_pLog, "PlayerRightItem: %s\n", rightItem != None ? rightItem.GetName().GetText() : "<none>");
    std::fprintf(g_pLog, "PlayerRightItemAddress: %p\n", static_cast<void *>(rightInstance));
    std::fprintf(g_pLog, "PlayerRightUseType: %d\n", rightItem != None ? static_cast<GEInt>(CollisionControl::GetCollisionSourceUseType(rightItem)) : -1);
    std::fprintf(g_pLog, "PlayerRightCollisionGroup: %d\n", rightItem != None ? static_cast<GEInt>(rightItem.GetCollisionGroup()) : -1);
    return { slotMatch, matchesLeft || matchesRight };
}

static void LogNativeCleanupCallSite(
    eCEntity *changedEntity, char const *slotMatch, void *callerAddress,
    NativeCleanupStackSnapshot const &cleanupStack)
{
    HMODULE callerModule = nullptr;
    char modulePath[MAX_PATH] = {};
    bool const moduleResolved =
        callerAddress != nullptr
        && ::GetModuleHandleExA(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
                | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPCSTR>(callerAddress), &callerModule) != FALSE;
    DWORD const modulePathLength = moduleResolved
        ? ::GetModuleFileNameA(callerModule, modulePath, MAX_PATH) : 0;

    std::uintptr_t const callerValue =
        reinterpret_cast<std::uintptr_t>(callerAddress);
    std::uintptr_t const moduleBase =
        reinterpret_cast<std::uintptr_t>(callerModule);
    unsigned long const callerRva = moduleResolved
        ? static_cast<unsigned long>(callerValue - moduleBase) : 0;

    Entity changed(changedEntity);
    std::fprintf(g_pLog, "===== NATIVE CLEANUP CALL SITE =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                 HookBridgeRuntime::GetElapsedMilliseconds());
    std::fprintf(g_pLog, "Source: %s\n", changed.GetName().GetText());
    std::fprintf(g_pLog, "SourceAddress: %p\n",
                 static_cast<void *>(changedEntity));
    std::fprintf(g_pLog, "PlayerSlotMatch: %s\n", slotMatch);
    std::fprintf(g_pLog, "CallerAddress: %p\n", callerAddress);
    std::fprintf(g_pLog, "CallerModuleResolved: %d\n",
                 moduleResolved ? 1 : 0);
    std::fprintf(g_pLog, "CallerModule: %s\n",
                 modulePathLength > 0 ? BaseName(modulePath)
                                      : moduleResolved ? "<path-unavailable>"
                                                       : "<unresolved>");
    std::fprintf(g_pLog, "CallerModuleBase: %p\n",
                 static_cast<void *>(callerModule));
    if (moduleResolved)
        std::fprintf(g_pLog, "CallerRVA: 0x%08lX\n", callerRva);
    else
        std::fprintf(g_pLog, "CallerRVA: <unresolved>\n");

    std::fprintf(g_pLog, "CapturedStackFrameCount: %u\n",
                 static_cast<unsigned int>(cleanupStack.frameCount));
    for (unsigned short i = 0; i < cleanupStack.frameCount; ++i)
    {
        void *frameAddress = cleanupStack.frames[i];
        HMODULE frameModule = nullptr;
        char frameModulePath[MAX_PATH] = {};
        bool const frameModuleResolved =
            frameAddress != nullptr
            && ::GetModuleHandleExA(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
                    | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                reinterpret_cast<LPCSTR>(frameAddress),
                &frameModule) != FALSE;
        DWORD const frameModulePathLength = frameModuleResolved
            ? ::GetModuleFileNameA(
                frameModule, frameModulePath, MAX_PATH) : 0;
        std::uintptr_t const frameValue =
            reinterpret_cast<std::uintptr_t>(frameAddress);
        std::uintptr_t const frameModuleBase =
            reinterpret_cast<std::uintptr_t>(frameModule);
        unsigned long const frameRva = frameModuleResolved
            ? static_cast<unsigned long>(
                frameValue - frameModuleBase) : 0;

        if (frameModuleResolved)
        {
            std::fprintf(
                g_pLog,
                "StackFrame[%u]: Address=%p Module=%s Base=%p RVA=0x%08lX\n",
                static_cast<unsigned int>(i), frameAddress,
                frameModulePathLength > 0
                    ? BaseName(frameModulePath) : "<path-unavailable>",
                static_cast<void *>(frameModule), frameRva);
        }
        else
        {
            std::fprintf(
                g_pLog,
                "StackFrame[%u]: Address=%p Module=<unresolved> Base=%p RVA=<unresolved>\n",
                static_cast<unsigned int>(i), frameAddress,
                static_cast<void *>(frameModule));
        }
    }

    std::fprintf(g_pLog, "RequestedGroup: %d\n",
                 static_cast<GEInt>(eECollisionGroup_Item_Equipped));
    std::fprintf(g_pLog, "BeforeGroup: %d\n",
                 static_cast<GEInt>(eECollisionGroup_Item_Attack));
    std::fprintf(g_pLog, "AfterGroup: %d\n",
                 static_cast<GEInt>(eECollisionGroup_Item_Equipped));
    std::fprintf(g_pLog, "CleanupBehaviorChanged: 0\n");
    std::fprintf(g_pLog, "====================================\n\n");
}

void LogSetCollisionGroup(eCEntity *changedEntity, eECollisionGroup requestedGroup,
                          eECollisionGroup beforeGroup, eECollisionGroup afterGroup,
                          GEInt retiredMarkerExecutionCount,
                          void *callerAddress,
                          NativeCleanupStackSnapshot const &cleanupStack)
{
    if (changedEntity == nullptr || g_pLog == nullptr)
        return;
    bool involvesAttack = requestedGroup == eECollisionGroup_Item_Attack
                       || beforeGroup == eECollisionGroup_Item_Attack
                       || afterGroup == eECollisionGroup_Item_Attack;
    if (!involvesAttack)
        return;
    Entity changed(changedEntity);
    std::fprintf(g_pLog, "===== ENGINE SetCollisionGroup =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n", HookBridgeRuntime::GetElapsedMilliseconds());
    std::fprintf(g_pLog, "Entity: %s\n", changed.GetName().GetText());
    PlayerSlotIdentityResult slotIdentity =
        LogPlayerSlotIdentity(changedEntity);
    std::fprintf(g_pLog, "RequestedGroup: %d\n", static_cast<GEInt>(requestedGroup));
    std::fprintf(g_pLog, "BeforeGroup: %d\n", static_cast<GEInt>(beforeGroup));
    std::fprintf(g_pLog, "AfterGroup: %d\n", static_cast<GEInt>(afterGroup));
    std::fprintf(g_pLog, "Item_EquippedValue: %d\n", static_cast<GEInt>(eECollisionGroup_Item_Equipped));
    std::fprintf(g_pLog, "Item_AttackValue: %d\n", static_cast<GEInt>(eECollisionGroup_Item_Attack));
    std::fprintf(g_pLog, "RetiredMarkerExecutionCount: %d\n", retiredMarkerExecutionCount);
    std::fprintf(g_pLog, "====================================\n\n");

    bool const isExactNativeCleanup =
        requestedGroup == eECollisionGroup_Item_Equipped
        && beforeGroup == eECollisionGroup_Item_Attack
        && afterGroup == eECollisionGroup_Item_Equipped;
    if (slotIdentity.matchesEquippedSource && isExactNativeCleanup)
        LogNativeCleanupCallSite(
            changedEntity, slotIdentity.slotMatch, callerAddress,
            cleanupStack);
    std::fflush(g_pLog);
}

static bool TryGetPrimaryMotionLifetimeSnapshot(
    eCVisualAnimation_PS *animationPS, PrimaryMotionLifetimeSnapshot &snapshot)
{
    snapshot = {};
    if (animationPS == nullptr || !animationPS->HasActor())
        return false;
    eCWrapper_emfx2Actor *animationActor = animationPS->GetActor();
    if (animationActor == nullptr)
        return false;
    auto const primaryFirst = static_cast<eCWrapper_emfx2Actor::eEMotionType>(0);
    snapshot.available = true;
    snapshot.hasMotionInstance = animationActor->HasMotionInstance(primaryFirst);
    if (!snapshot.hasMotionInstance)
        return true;
    snapshot.motionRunning = animationActor->IsMotionRunning(primaryFirst);
    snapshot.playTime = animationActor->GetPlayTime(primaryFirst);
    snapshot.maxTime = animationActor->GetMaxTime(primaryFirst);
    snapshot.playSpeed = animationActor->GetPlaySpeed(primaryFirst);
    snapshot.motionName = animationPS->GetMotionDesc(primaryFirst).GetMotionFilename().GetText();
    return true;
}

static bool TryGetPrimaryMotionLifetimeSnapshot(
    Entity &actor, PrimaryMotionLifetimeSnapshot &snapshot)
{
    snapshot = {};
    if (actor == None || !actor.Animation.IsValid())
        return false;
    auto *animationPS =
        static_cast<eCVisualAnimation_PS *>(actor.Animation.m_pEngineEntityPropertySet);
    return TryGetPrimaryMotionLifetimeSnapshot(animationPS, snapshot);
}

PrimaryMotionEventSnapshot CapturePrimaryMotionEventSnapshot(
    eCVisualAnimation_PS *animationPS)
{
    PrimaryMotionEventSnapshot result = {};
    result.elapsedMilliseconds = HookBridgeRuntime::GetElapsedMilliseconds();
    TryGetPrimaryMotionLifetimeSnapshot(animationPS, result.primary);
    return result;
}

PrimaryMotionEventSnapshot CapturePrimaryMotionEventSnapshot(Entity &actor)
{
    PrimaryMotionEventSnapshot result = {};
    result.elapsedMilliseconds = HookBridgeRuntime::GetElapsedMilliseconds();
    TryGetPrimaryMotionLifetimeSnapshot(actor, result.primary);
    return result;
}

bool IsAttackHitPrimaryMotion(PrimaryMotionEventSnapshot const &snapshot)
{
    return snapshot.primary.available
        && snapshot.primary.hasMotionInstance
        && IsAttackHitMotionName(snapshot.primary.motionName.c_str());
}

static void CaptureHitReplacementSource(
    eCEntity *sourceInstance, HitReplacementSourceSnapshot &snapshot)
{
    snapshot = {};
    snapshot.address = sourceInstance;
    snapshot.collisionGroup = -1;
    if (sourceInstance == nullptr)
        return;

    Entity source(sourceInstance);
    snapshot.resolved = true;
    snapshot.name = source.GetName().GetText();
    snapshot.collisionGroup =
        static_cast<GEInt>(source.GetCollisionGroup());
}

void CaptureHitReplacementContext(
    Entity &actor, void *incomingRequestAddress,
    HitReplacementStackSnapshot &snapshot)
{
    snapshot.elapsedMilliseconds = HookBridgeRuntime::GetElapsedMilliseconds();
    snapshot.incomingRequestAddress = incomingRequestAddress;
    if (actor == None)
        return;

    bCString movement = actor.NPC.GetCurrentMovementAni();
    snapshot.movementName = movement.GetText() != nullptr
        ? movement.GetText() : "";
    snapshot.action = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    snapshot.phase = static_cast<GEInt>(actor.GetCurrentAniPhase());
    snapshot.stateTime = actor.Routine.GetStateTime();
    snapshot.statePosition = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());

    EquippedCollisionSources sources =
        CollisionControl::GetEquippedCollisionSources(actor);
    CaptureHitReplacementSource(sources.leftInstance, snapshot.leftSource);
    CaptureHitReplacementSource(sources.rightInstance, snapshot.rightSource);
}

static void LogHitReplacementSource(
    char const *label, HitReplacementSourceSnapshot const &source)
{
    std::fprintf(g_pLog, "%sSourceResolved: %d\n",
                 label, source.resolved ? 1 : 0);
    std::fprintf(g_pLog, "%sSource: %s\n",
                 label, source.resolved ? source.name.c_str() : "<none>");
    std::fprintf(g_pLog, "%sSourceAddress: %p\n",
                 label, source.address);
    std::fprintf(g_pLog, "%sSourceCollisionGroup: %d\n",
                 label, source.collisionGroup);
}

void LogHitReplacementStack(
    Entity &actor, HitReplacementStackSnapshot const &replacement,
    PrimaryMotionEventSnapshot const &incoming)
{
    if (g_pLog == nullptr)
        return;

    std::fprintf(g_pLog, "===== HIT REPLACEMENT STACK =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                 replacement.elapsedMilliseconds);
    std::fprintf(g_pLog, "Actor: %s\n",
                 actor != None ? actor.GetName().GetText() : "<unavailable>");
    std::fprintf(g_pLog, "OutgoingPrimaryMotionName: %s\n",
                 replacement.outgoingMotionName.c_str());
    std::fprintf(g_pLog, "IncomingMotionRequestAddress: %p\n",
                 replacement.incomingRequestAddress);
    std::fprintf(g_pLog, "IncomingPrimaryMotionNameAfterOriginal: %s\n",
                 incoming.primary.motionName.c_str());
    std::fprintf(g_pLog, "IncomingPrimarySnapshotAvailable: %d\n",
                 incoming.primary.available ? 1 : 0);
    std::fprintf(g_pLog, "IncomingPrimaryHasMotionInstance: %d\n",
                 incoming.primary.hasMotionInstance ? 1 : 0);
    std::fprintf(g_pLog, "CurrentAction: %d\n", replacement.action);
    std::fprintf(g_pLog, "CurrentAniPhase: %d\n", replacement.phase);
    std::fprintf(g_pLog, "CurrentStateTime: %.6f\n",
                 replacement.stateTime);
    std::fprintf(g_pLog, "CurrentMovementAni: %s\n",
                 replacement.movementName.c_str());
    LogHitReplacementSource("LeftHand", replacement.leftSource);
    LogHitReplacementSource("RightHand", replacement.rightSource);
    std::fprintf(g_pLog, "CapturedStackFrameCount: %u\n",
                 static_cast<unsigned int>(replacement.frameCount));
    for (unsigned short i = 0; i < replacement.frameCount; ++i)
    {
        void *frameAddress = replacement.frames[i];
        HMODULE frameModule = nullptr;
        char frameModulePath[MAX_PATH] = {};
        bool const frameModuleResolved =
            frameAddress != nullptr
            && ::GetModuleHandleExA(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
                    | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                reinterpret_cast<LPCSTR>(frameAddress),
                &frameModule) != FALSE;
        DWORD const frameModulePathLength = frameModuleResolved
            ? ::GetModuleFileNameA(
                frameModule, frameModulePath, MAX_PATH) : 0;
        std::uintptr_t const frameValue =
            reinterpret_cast<std::uintptr_t>(frameAddress);
        std::uintptr_t const frameModuleBase =
            reinterpret_cast<std::uintptr_t>(frameModule);
        unsigned long const frameRva = frameModuleResolved
            ? static_cast<unsigned long>(
                frameValue - frameModuleBase) : 0;
        if (frameModuleResolved)
        {
            std::fprintf(
                g_pLog,
                "StackFrame[%u]: Address=%p Module=%s Base=%p RVA=0x%08lX\n",
                static_cast<unsigned int>(i), frameAddress,
                frameModulePathLength > 0
                    ? BaseName(frameModulePath) : "<path-unavailable>",
                static_cast<void *>(frameModule), frameRva);
        }
        else
        {
            std::fprintf(
                g_pLog,
                "StackFrame[%u]: Address=%p Module=<unresolved> Base=%p RVA=<unresolved>\n",
                static_cast<unsigned int>(i), frameAddress,
                static_cast<void *>(frameModule));
        }
    }
    std::fprintf(g_pLog, "CleanupBehaviorChanged: 0\n");
    std::fprintf(g_pLog, "=================================\n\n");
    std::fflush(g_pLog);
}

void LogEmptyPrimarySuccessorStack(
    Entity &actor, HitReplacementStackSnapshot const &request,
    PrimaryMotionEventSnapshot const &successor)
{
    if (g_pLog == nullptr)
        return;

    std::fprintf(g_pLog, "===== EMPTY-PRIMARY SUCCESSOR STACK =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n", request.elapsedMilliseconds);
    std::fprintf(g_pLog, "Actor: %s\n",
                 actor != None ? actor.GetName().GetText() : "<unavailable>");
    std::fprintf(g_pLog, "PrimaryWasEmptyBefore: 1\n");
    std::fprintf(g_pLog, "IncomingMotionRequestAddress: %p\n",
                 request.incomingRequestAddress);
    std::fprintf(g_pLog, "SuccessorPrimaryMotionNameAfterOriginal: %s\n",
                 successor.primary.motionName.c_str());
    std::fprintf(g_pLog, "SuccessorPrimarySnapshotAvailable: %d\n",
                 successor.primary.available ? 1 : 0);
    std::fprintf(g_pLog, "SuccessorPrimaryHasMotionInstance: %d\n",
                 successor.primary.hasMotionInstance ? 1 : 0);
    std::fprintf(g_pLog, "CurrentActionBeforeOriginal: %d\n", request.action);
    std::fprintf(g_pLog, "CurrentAniPhaseBeforeOriginal: %d\n", request.phase);
    std::fprintf(g_pLog, "CurrentStateTimeBeforeOriginal: %.6f\n",
                 request.stateTime);
    std::fprintf(g_pLog, "CurrentStatePositionBeforeOriginal: %d\n",
                 request.statePosition);
    std::fprintf(g_pLog, "CurrentMovementAniBeforeOriginal: %s\n",
                 request.movementName.c_str());
    LogHitReplacementSource("LeftHand", request.leftSource);
    LogHitReplacementSource("RightHand", request.rightSource);
    std::fprintf(g_pLog, "CapturedStackFrameCount: %u\n",
                 static_cast<unsigned int>(request.frameCount));
    for (unsigned short i = 0; i < request.frameCount; ++i)
    {
        void *frameAddress = request.frames[i];
        HMODULE frameModule = nullptr;
        char frameModulePath[MAX_PATH] = {};
        bool const frameModuleResolved =
            frameAddress != nullptr
            && ::GetModuleHandleExA(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
                    | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                reinterpret_cast<LPCSTR>(frameAddress),
                &frameModule) != FALSE;
        DWORD const frameModulePathLength = frameModuleResolved
            ? ::GetModuleFileNameA(
                frameModule, frameModulePath, MAX_PATH) : 0;
        std::uintptr_t const frameValue =
            reinterpret_cast<std::uintptr_t>(frameAddress);
        std::uintptr_t const frameModuleBase =
            reinterpret_cast<std::uintptr_t>(frameModule);
        unsigned long const frameRva = frameModuleResolved
            ? static_cast<unsigned long>(frameValue - frameModuleBase) : 0;
        if (frameModuleResolved)
        {
            std::fprintf(
                g_pLog,
                "StackFrame[%u]: Address=%p Module=%s Base=%p RVA=0x%08lX\n",
                static_cast<unsigned int>(i), frameAddress,
                frameModulePathLength > 0
                    ? BaseName(frameModulePath) : "<path-unavailable>",
                static_cast<void *>(frameModule), frameRva);
        }
        else
        {
            std::fprintf(
                g_pLog,
                "StackFrame[%u]: Address=%p Module=<unresolved> Base=%p RVA=<unresolved>\n",
                static_cast<unsigned int>(i), frameAddress,
                static_cast<void *>(frameModule));
        }
    }
    std::fprintf(g_pLog, "CleanupBehaviorChanged: 0\n");
    std::fprintf(g_pLog, "=============================================\n\n");
    std::fflush(g_pLog);
}

void LogHitStopStack(Entity &actor,
                     HitReplacementStackSnapshot const &stop,
                     GEFloat blendTime)
{
    if (g_pLog == nullptr)
        return;

    std::fprintf(g_pLog, "===== HIT STOP STACK =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n", stop.elapsedMilliseconds);
    std::fprintf(g_pLog, "Actor: %s\n",
                 actor != None ? actor.GetName().GetText() : "<unavailable>");
    std::fprintf(g_pLog, "OutgoingPrimaryMotionName: %s\n",
                 stop.outgoingMotionName.c_str());
    std::fprintf(g_pLog, "StopMotionType: 0\n");
    std::fprintf(g_pLog, "StopMotionBlendTime: %.6f\n", blendTime);
    std::fprintf(g_pLog, "StopIsConfirmedReplacement: 0\n");
    std::fprintf(g_pLog, "CurrentAction: %d\n", stop.action);
    std::fprintf(g_pLog, "CurrentAniPhase: %d\n", stop.phase);
    std::fprintf(g_pLog, "CurrentStateTime: %.6f\n", stop.stateTime);
    std::fprintf(g_pLog, "CurrentMovementAni: %s\n",
                 stop.movementName.c_str());
    LogHitReplacementSource("LeftHand", stop.leftSource);
    LogHitReplacementSource("RightHand", stop.rightSource);
    std::fprintf(g_pLog, "CapturedStackFrameCount: %u\n",
                 static_cast<unsigned int>(stop.frameCount));
    for (unsigned short i = 0; i < stop.frameCount; ++i)
    {
        void *frameAddress = stop.frames[i];
        HMODULE frameModule = nullptr;
        char frameModulePath[MAX_PATH] = {};
        bool const frameModuleResolved =
            frameAddress != nullptr
            && ::GetModuleHandleExA(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
                    | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                reinterpret_cast<LPCSTR>(frameAddress),
                &frameModule) != FALSE;
        DWORD const frameModulePathLength = frameModuleResolved
            ? ::GetModuleFileNameA(
                frameModule, frameModulePath, MAX_PATH) : 0;
        std::uintptr_t const frameValue =
            reinterpret_cast<std::uintptr_t>(frameAddress);
        std::uintptr_t const frameModuleBase =
            reinterpret_cast<std::uintptr_t>(frameModule);
        unsigned long const frameRva = frameModuleResolved
            ? static_cast<unsigned long>(frameValue - frameModuleBase) : 0;
        if (frameModuleResolved)
        {
            std::fprintf(
                g_pLog,
                "StackFrame[%u]: Address=%p Module=%s Base=%p RVA=0x%08lX\n",
                static_cast<unsigned int>(i), frameAddress,
                frameModulePathLength > 0
                    ? BaseName(frameModulePath) : "<path-unavailable>",
                static_cast<void *>(frameModule), frameRva);
        }
        else
        {
            std::fprintf(
                g_pLog,
                "StackFrame[%u]: Address=%p Module=<unresolved> Base=%p RVA=<unresolved>\n",
                static_cast<unsigned int>(i), frameAddress,
                static_cast<void *>(frameModule));
        }
    }
    std::fprintf(g_pLog, "CleanupBehaviorChanged: 0\n");
    std::fprintf(g_pLog, "==========================\n\n");
    std::fflush(g_pLog);
}

void LogHitStartRecoverBeginStack(
    Entity &actor, HitReplacementStackSnapshot const &startRecover)
{
    if (g_pLog == nullptr)
        return;

    std::fprintf(g_pLog, "===== HIT STARTRECOVER BEGIN STACK =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                 startRecover.elapsedMilliseconds);
    std::fprintf(g_pLog, "Actor: %s\n",
                 actor != None ? actor.GetName().GetText() : "<unavailable>");
    std::fprintf(g_pLog, "OutgoingPrimaryMotionName: %s\n",
                 startRecover.outgoingMotionName.c_str());
    std::fprintf(g_pLog, "CurrentAction: %d\n", startRecover.action);
    std::fprintf(g_pLog, "CurrentAniPhase: %d\n", startRecover.phase);
    std::fprintf(g_pLog, "CurrentStateTime: %.6f\n",
                 startRecover.stateTime);
    std::fprintf(g_pLog, "CurrentMovementAni: %s\n",
                 startRecover.movementName.c_str());
    LogHitReplacementSource("LeftHand", startRecover.leftSource);
    LogHitReplacementSource("RightHand", startRecover.rightSource);
    std::fprintf(g_pLog, "CapturedStackFrameCount: %u\n",
                 static_cast<unsigned int>(startRecover.frameCount));
    for (unsigned short i = 0; i < startRecover.frameCount; ++i)
    {
        void *frameAddress = startRecover.frames[i];
        HMODULE frameModule = nullptr;
        char frameModulePath[MAX_PATH] = {};
        bool const frameModuleResolved =
            frameAddress != nullptr
            && ::GetModuleHandleExA(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
                    | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                reinterpret_cast<LPCSTR>(frameAddress),
                &frameModule) != FALSE;
        DWORD const frameModulePathLength = frameModuleResolved
            ? ::GetModuleFileNameA(
                frameModule, frameModulePath, MAX_PATH) : 0;
        std::uintptr_t const frameValue =
            reinterpret_cast<std::uintptr_t>(frameAddress);
        std::uintptr_t const frameModuleBase =
            reinterpret_cast<std::uintptr_t>(frameModule);
        unsigned long const frameRva = frameModuleResolved
            ? static_cast<unsigned long>(frameValue - frameModuleBase) : 0;
        if (frameModuleResolved)
        {
            std::fprintf(
                g_pLog,
                "StackFrame[%u]: Address=%p Module=%s Base=%p RVA=0x%08lX\n",
                static_cast<unsigned int>(i), frameAddress,
                frameModulePathLength > 0
                    ? BaseName(frameModulePath) : "<path-unavailable>",
                static_cast<void *>(frameModule), frameRva);
        }
        else
        {
            std::fprintf(
                g_pLog,
                "StackFrame[%u]: Address=%p Module=<unresolved> Base=%p RVA=<unresolved>\n",
                static_cast<unsigned int>(i), frameAddress,
                static_cast<void *>(frameModule));
        }
    }
    std::fprintf(g_pLog, "CleanupBehaviorChanged: 0\n");
    std::fprintf(g_pLog, "========================================\n\n");
    std::fflush(g_pLog);
}

static void LogPrimaryMotionEventSnapshot(
    char const *stage, PrimaryMotionEventSnapshot const &eventSnapshot)
{
    PrimaryMotionLifetimeSnapshot const &snapshot = eventSnapshot.primary;
    std::fprintf(g_pLog, "Stage: %s\n", stage);
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n",
                 eventSnapshot.elapsedMilliseconds);
    std::fprintf(g_pLog, "PrimarySnapshotAvailable: %d\n",
                 snapshot.available ? 1 : 0);
    std::fprintf(g_pLog, "PrimaryMotionName: %s\n",
                 snapshot.motionName.c_str());
    std::fprintf(g_pLog, "PrimaryHasMotionInstance: %d\n",
                 snapshot.hasMotionInstance ? 1 : 0);
    std::fprintf(g_pLog, "PrimaryMotionRunning: %d\n",
                 snapshot.motionRunning ? 1 : 0);
    std::fprintf(g_pLog, "PrimaryPlayTime: %.6f\n", snapshot.playTime);
    std::fprintf(g_pLog, "PrimaryMaxTime: %.6f\n", snapshot.maxTime);
    std::fprintf(g_pLog, "PrimaryPlaySpeed: %.6f\n", snapshot.playSpeed);
}

void LogCombatMoveFullStopStack(
    Entity &actor, HitReplacementStackSnapshot const &fullStop,
    PrimaryMotionEventSnapshot const &primary)
{
    if (g_pLog == nullptr)
        return;

    std::fprintf(g_pLog, "===== COMBATMOVE FULLSTOP STACK =====\n");
    std::fprintf(g_pLog, "ElapsedMs: %.3f\n", fullStop.elapsedMilliseconds);
    std::fprintf(g_pLog, "ActorAddress: %p\n",
                 static_cast<void *>(actor.GetInstance()));
    std::fprintf(g_pLog, "Actor: %s\n",
                 actor != None ? actor.GetName().GetText() : "<unavailable>");
    std::fprintf(g_pLog, "FullStop: 1\n");
    std::fprintf(g_pLog, "InstructionArgsAddress: %p\n",
                 fullStop.incomingRequestAddress);
    std::fprintf(g_pLog, "CurrentAction: %d\n", fullStop.action);
    std::fprintf(g_pLog, "CurrentAniPhase: %d\n", fullStop.phase);
    std::fprintf(g_pLog, "CurrentStateTime: %.6f\n", fullStop.stateTime);
    std::fprintf(g_pLog, "CurrentStatePosition: %d\n",
                 fullStop.statePosition);
    std::fprintf(g_pLog, "CurrentMovementAni: %s\n",
                 fullStop.movementName.c_str());
    LogPrimaryMotionEventSnapshot("BEFORE_ORIGINAL", primary);
    LogHitReplacementSource("LeftHand", fullStop.leftSource);
    LogHitReplacementSource("RightHand", fullStop.rightSource);
    std::fprintf(g_pLog, "CapturedStackFrameCount: %u\n",
                 static_cast<unsigned int>(fullStop.frameCount));
    for (unsigned short i = 0; i < fullStop.frameCount; ++i)
    {
        void *frameAddress = fullStop.frames[i];
        HMODULE frameModule = nullptr;
        char frameModulePath[MAX_PATH] = {};
        bool const frameModuleResolved =
            frameAddress != nullptr
            && ::GetModuleHandleExA(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
                    | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                reinterpret_cast<LPCSTR>(frameAddress),
                &frameModule) != FALSE;
        DWORD const frameModulePathLength = frameModuleResolved
            ? ::GetModuleFileNameA(
                frameModule, frameModulePath, MAX_PATH) : 0;
        std::uintptr_t const frameValue =
            reinterpret_cast<std::uintptr_t>(frameAddress);
        std::uintptr_t const frameModuleBase =
            reinterpret_cast<std::uintptr_t>(frameModule);
        unsigned long const frameRva = frameModuleResolved
            ? static_cast<unsigned long>(frameValue - frameModuleBase) : 0;
        if (frameModuleResolved)
        {
            std::fprintf(
                g_pLog,
                "StackFrame[%u]: Address=%p Module=%s Base=%p RVA=0x%08lX\n",
                static_cast<unsigned int>(i), frameAddress,
                frameModulePathLength > 0
                    ? BaseName(frameModulePath) : "<path-unavailable>",
                static_cast<void *>(frameModule), frameRva);
        }
        else
        {
            std::fprintf(
                g_pLog,
                "StackFrame[%u]: Address=%p Module=<unresolved> Base=%p RVA=<unresolved>\n",
                static_cast<unsigned int>(i), frameAddress,
                static_cast<void *>(frameModule));
        }
    }
    std::fprintf(g_pLog, "CleanupBehaviorChanged: 0\n");
    std::fprintf(g_pLog, "=====================================\n\n");
    std::fflush(g_pLog);
}

static void LogCombatMoveEquippedSource(
    char const *label, eCEntity *sourceInstance)
{
    std::fprintf(g_pLog, "%sSourceResolved: %d\n",
                 label, sourceInstance != nullptr ? 1 : 0);
    if (sourceInstance == nullptr)
        return;
    Entity source(sourceInstance);
    std::fprintf(g_pLog, "%sSource: %s\n",
                 label, source.GetName().GetText());
    std::fprintf(g_pLog, "%sSourceAddress: %p\n",
                 label, static_cast<void *>(sourceInstance));
    std::fprintf(g_pLog, "%sSourceCollisionGroup: %d\n",
                 label, static_cast<GEInt>(source.GetCollisionGroup()));
}

void LogCombatMoveStartRecoverBoundary(Entity &actor,
                                       char const *boundary)
{
    if (g_pLog == nullptr)
        return;

    PrimaryMotionEventSnapshot snapshot =
        CapturePrimaryMotionEventSnapshot(actor);
    EquippedCollisionSources sources =
        CollisionControl::GetEquippedCollisionSources(actor);
    bCString currentMovementAni = actor.NPC.GetCurrentMovementAni();
    std::fprintf(g_pLog, "===== COMBATMOVE STARTRECOVER %s =====\n",
                 boundary);
    std::fprintf(g_pLog, "ActorAddress: %p\n",
                 static_cast<void *>(actor.GetInstance()));
    std::fprintf(g_pLog, "Actor: %s\n", actor.GetName().GetText());
    std::fprintf(g_pLog, "CurrentAction: %d\n",
                 static_cast<GEInt>(
                     actor.Routine.GetProperty<PSRoutine::PropertyAction>()));
    std::fprintf(g_pLog, "CurrentAniPhase: %d\n",
                 static_cast<GEInt>(actor.GetCurrentAniPhase()));
    std::fprintf(g_pLog, "CurrentMovementAni: %s\n",
                 currentMovementAni.GetText());
    LogPrimaryMotionEventSnapshot(boundary, snapshot);
    LogCombatMoveEquippedSource("LeftHand", sources.leftInstance);
    LogCombatMoveEquippedSource("RightHand", sources.rightInstance);
    std::fprintf(g_pLog, "CleanupBehaviorChanged: 0\n");
    std::fprintf(g_pLog, "=========================================\n\n");
    std::fflush(g_pLog);
}

void LogPrimaryMotionEvent(eCVisualAnimation_PS *animationPS,
                           char const *operation,
                           PrimaryMotionEventSnapshot const &before,
                           PrimaryMotionEventSnapshot const &after)
{
    if (g_pLog == nullptr)
        return;

    eCEntity *ownerEntity = animationPS != nullptr ? animationPS->GetEntity() : nullptr;
    std::fprintf(g_pLog, "===== PRIMARYFIRST %s =====\n", operation);
    std::fprintf(g_pLog, "OwnerEntityAddress: %p\n",
                 static_cast<void *>(ownerEntity));
    if (ownerEntity != nullptr)
    {
        Entity owner(ownerEntity);
        std::fprintf(g_pLog, "OwnerEntity: %s\n", owner.GetName().GetText());
    }
    else
    {
        std::fprintf(g_pLog, "OwnerEntity: <unavailable>\n");
    }
    std::fprintf(g_pLog, "MotionType: 0\n");
    LogPrimaryMotionEventSnapshot("REQUEST_BEFORE_ORIGINAL", before);
    LogPrimaryMotionEventSnapshot("RESULT_AFTER_ORIGINAL", after);
    std::fprintf(g_pLog, "CleanupBehaviorChanged: 0\n");
    std::fprintf(g_pLog, "=====================================\n\n");
    std::fflush(g_pLog);
}

void ResetMarkerOwnedLifetime(eCEntity *actorInstance)
{
    if (actorInstance != nullptr)
        g_LifetimeStateByActor[actorInstance] = {};
}

void ForgetMarkerOwnedLifetime(eCEntity *actorInstance)
{
    if (actorInstance != nullptr)
        g_LifetimeStateByActor.erase(actorInstance);
}

void ObserveMarkerOwnedLifetimeOnTick(Entity &actor, MarkerOwnedWindowView const &window)
{
    if (actor == None)
        return;
    eCEntity *actorInstance = actor.GetInstance();
    LifetimeState &state = g_LifetimeStateByActor[actorInstance];
    bCString currentMovementAni = actor.NPC.GetCurrentMovementAni();
    GEInt currentAction = static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    GEInt currentPhase = static_cast<GEInt>(actor.GetCurrentAniPhase());
    PrimaryMotionLifetimeSnapshot snapshot = {};
    bool snapshotAvailable = TryGetPrimaryMotionLifetimeSnapshot(actor, snapshot);
    bool firstSnapshot = !state.initialized;
    bool movementChanged = !firstSnapshot && !SameFileName(state.lastObservedMovementAni.c_str(), currentMovementAni.GetText());
    bool actionChanged = !firstSnapshot && state.lastObservedAction != currentAction;
    bool phaseChanged = !firstSnapshot && state.lastObservedPhase != currentPhase;
    bool instanceChanged = !firstSnapshot && state.lastHasPrimaryMotionInstance != snapshot.hasMotionInstance;
    bool runningChanged = !firstSnapshot && state.lastPrimaryMotionRunning != snapshot.motionRunning;
    bool primaryNameChanged = !firstSnapshot && !SameFileName(state.lastPrimaryMotionName.c_str(), snapshot.motionName.c_str());
    bool playTimeRolledBack = !firstSnapshot && snapshot.hasMotionInstance
                           && state.lastHasPrimaryMotionInstance
                           && snapshot.playTime + 0.000001 < state.lastPrimaryPlayTime;
    bool atMotionEnd = snapshot.hasMotionInstance && snapshot.maxTime > 0.0
                    && snapshot.playTime + 0.001 >= snapshot.maxTime;
    bool previouslyAtMotionEnd = !firstSnapshot && state.lastHasPrimaryMotionInstance
                              && state.lastPrimaryMaxTime > 0.0
                              && state.lastPrimaryPlayTime + 0.001 >= state.lastPrimaryMaxTime;
    bool crossedMotionEnd = atMotionEnd && !previouslyAtMotionEnd;
    bool logTransition = firstSnapshot || movementChanged || actionChanged || phaseChanged
                      || instanceChanged || runningChanged || primaryNameChanged
                      || playTimeRolledBack || crossedMotionEnd;
    if (logTransition && g_pLog != nullptr)
    {
        std::fprintf(g_pLog, "===== MARKER-OWNED PRIMARY MOTION LIFETIME =====\n");
        std::fprintf(g_pLog, "ElapsedMs: %.3f\n", HookBridgeRuntime::GetElapsedMilliseconds());
        std::fprintf(g_pLog, "Actor: %s\n", actor.GetName().GetText());
        std::fprintf(g_pLog, "OwnedAnimation: %s\n", window.animationName.c_str());
        std::fprintf(g_pLog, "OwnedAction: %d\n", window.action);
        std::fprintf(g_pLog, "OwnedPhase: %d\n", window.phase);
        std::fprintf(g_pLog, "ActiveSourceMask: %u\n", window.activeSourceMask);
        std::fprintf(g_pLog, "CurrentMovementAni: %s\n", currentMovementAni.GetText());
        std::fprintf(g_pLog, "CurrentAction: %d\n", currentAction);
        std::fprintf(g_pLog, "CurrentAniPhase: %d\n", currentPhase);
        std::fprintf(g_pLog, "PrimarySnapshotAvailable: %d\n", snapshotAvailable ? 1 : 0);
        std::fprintf(g_pLog, "PrimaryHasMotionInstance: %d\n", snapshot.hasMotionInstance ? 1 : 0);
        std::fprintf(g_pLog, "PrimaryMotionRunning: %d\n", snapshot.motionRunning ? 1 : 0);
        std::fprintf(g_pLog, "PrimaryMotionName: %s\n", snapshot.motionName.c_str());
        std::fprintf(g_pLog, "PrimaryPlayTime: %.6f\n", snapshot.playTime);
        std::fprintf(g_pLog, "PrimaryMaxTime: %.6f\n", snapshot.maxTime);
        std::fprintf(g_pLog, "PrimaryPlaySpeed: %.6f\n", snapshot.playSpeed);
        std::fprintf(g_pLog, "CurrentMovementMatchesOwned: %d\n", SameFileName(window.animationName.c_str(), currentMovementAni.GetText()) ? 1 : 0);
        std::fprintf(g_pLog, "PrimaryMotionMatchesOwned: %d\n", SameFileName(window.animationName.c_str(), snapshot.motionName.c_str()) ? 1 : 0);
        std::fprintf(g_pLog, "CurrentActionPhaseMatchesOwned: %d\n", window.action == currentAction && window.phase == currentPhase ? 1 : 0);
        std::fprintf(g_pLog, "FirstLifetimeSnapshot: %d\n", firstSnapshot ? 1 : 0);
        std::fprintf(g_pLog, "MovementChanged: %d\n", movementChanged ? 1 : 0);
        std::fprintf(g_pLog, "ActionChanged: %d\n", actionChanged ? 1 : 0);
        std::fprintf(g_pLog, "PhaseChanged: %d\n", phaseChanged ? 1 : 0);
        std::fprintf(g_pLog, "PrimaryInstanceChanged: %d\n", instanceChanged ? 1 : 0);
        std::fprintf(g_pLog, "PrimaryRunningChanged: %d\n", runningChanged ? 1 : 0);
        std::fprintf(g_pLog, "PrimaryNameChanged: %d\n", primaryNameChanged ? 1 : 0);
        std::fprintf(g_pLog, "PrimaryPlayTimeRolledBack: %d\n", playTimeRolledBack ? 1 : 0);
        std::fprintf(g_pLog, "PrimaryCrossedMotionEnd: %d\n", crossedMotionEnd ? 1 : 0);
        std::fprintf(g_pLog, "CleanupBehaviorChanged: 0\n");
        std::fprintf(g_pLog, "=====================================\n\n");
        std::fflush(g_pLog);
    }
    state.initialized = true;
    state.lastHasPrimaryMotionInstance = snapshot.hasMotionInstance;
    state.lastPrimaryMotionRunning = snapshot.motionRunning;
    state.lastPrimaryPlayTime = snapshot.playTime;
    state.lastPrimaryMaxTime = snapshot.maxTime;
    state.lastObservedAction = currentAction;
    state.lastObservedPhase = currentPhase;
    state.lastObservedMovementAni = currentMovementAni.GetText();
    state.lastPrimaryMotionName = snapshot.motionName;
}
}

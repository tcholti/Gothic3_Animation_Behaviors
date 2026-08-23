#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>
#include <g3sdk/Engine/ge_resourceanimationmotion_ps.h>
#include <g3sdk/Game/ge_effectsystem.h>
#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Memory.h>
#include <g3sdk/util/ScriptUtil.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>

#include <windows.h>

static mCFunctionHook Hook_StartEffect;
static mCFunctionHook Hook_OnAI_Attack;
static mCFunctionHook Hook_OnAI_QuickAttack;
static mCFunctionHook Hook_SetCollisionGroup;

static FILE *g_pLog = nullptr;
static LARGE_INTEGER g_StartCounter = {};
static LARGE_INTEGER g_Frequency = {};

static char const *const g_CollisionOnMarker = "G3AB_COL_TEST";
static char const *const g_CollisionLeftMarker = "G3AB_COL_LEFT_TEST";
static char const *const g_CollisionOffMarker = "G3AB_COL_OFF_TEST";

enum MarkerOpcode
{
    MarkerOpcode_Right = 0,
    MarkerOpcode_Left = 1,
    MarkerOpcode_Off = 2,
    MarkerOpcode_Count = 3,
    MarkerOpcode_Invalid = -1
};

static unsigned int const SourceMask_None = 0;
static unsigned int const SourceMask_Right = 1u << 0;
static unsigned int const SourceMask_Left = 1u << 1;

struct EquippedCollisionSources
{
    eCEntity *rightInstance;
    eCEntity *leftInstance;
};

// Last animation name logged per actor.
// Diagnostic only; it prevents the v0.5 per-frame suppression spam.
static std::unordered_map<eCEntity *, std::string> g_LastLoggedAni;

// Marker-presence cache by exact animation filename.
// Marker ownership belongs to the animation resource, so it does not need to
// be rescanned every callback once resolved.
struct CachedMarkerInfo
{
    bool foundMatchingMotion;
    bool markerPresent;
    GEInt frameEffectCount;
    GEInt firstMarkerFrames[MarkerOpcode_Count];
    GEInt markerCounts[MarkerOpcode_Count];
    unsigned int requiredSourceMask;
};

static std::unordered_map<std::string, CachedMarkerInfo> g_MarkerCache;

// Gothic 3 can dispatch the same authored frame effect more than once during
// one animation update. Preserve genuine later markers, but suppress an
// identical actor/source/motion marker repeated at the same state time within
// a very small wall-clock window.
struct LastAcceptedMarkerDispatch
{
    eCEntity *rightSourceInstance;
    eCEntity *leftSourceInstance;
    std::string animationName;
    std::string markerName;
    GEInt action;
    GEInt phase;
    GEFloat stateTime;
    double elapsedMs;
};

static std::unordered_map<eCEntity *, LastAcceptedMarkerDispatch> g_LastAcceptedMarkerDispatchByActor;

// The occurrence guard rejects interleaved marker replay. The exact motion
// scan supplies the authored RIGHT/LEFT/OFF counts once, then each actor keeps
// only a small execution record. No actor/world scan or per-frame work is
// needed.
struct MarkerExecutionBudget
{
    eCEntity *rightSourceInstance;
    eCEntity *leftSourceInstance;
    std::string animationName;
    GEInt action;
    GEInt phase;
    GEInt authoredCounts[MarkerOpcode_Count];
    GEInt acceptedCounts[MarkerOpcode_Count];
    GEFloat lastMarkerStateTime;
};

static std::unordered_map<eCEntity *, MarkerExecutionBudget> g_MarkerExecutionBudgetByActor;

// OFF may only close a source set opened by this prototype for the same
// actor/slot-snapshot/motion/action/phase. Natural engine reset retires each
// active source bit through the SetCollisionGroup hook.
struct MarkerOwnedCollisionWindow
{
    eCEntity *rightSourceInstance;
    eCEntity *leftSourceInstance;
    unsigned int activeSourceMask;
    std::string animationName;
    GEInt action;
    GEInt phase;
};

static std::unordered_map<eCEntity *, MarkerOwnedCollisionWindow> g_MarkerOwnedWindowByActor;

// -----------------------------------------------------------------------------
// Results
// -----------------------------------------------------------------------------

struct FrameEffectScanResult
{
    bool layoutLookedValid;
    bool foundMarker;
    GEInt count;
    GEInt firstMarkerFrames[MarkerOpcode_Count];
    GEInt markerCounts[MarkerOpcode_Count];
    unsigned int requiredSourceMask;
};

struct CurrentMotionMarkerResult
{
    bool foundMatchingMotion;
    bool markerPresent;
    GEInt frameEffectCount;
    GEInt firstMarkerFrames[MarkerOpcode_Count];
    GEInt markerCounts[MarkerOpcode_Count];
    unsigned int requiredSourceMask;
};

// -----------------------------------------------------------------------------
// General helpers
// -----------------------------------------------------------------------------

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

static double GetElapsedMilliseconds()
{
    LARGE_INTEGER now = {};
    ::QueryPerformanceCounter(&now);

    if (g_Frequency.QuadPart == 0)
        return 0.0;

    return (static_cast<double>(now.QuadPart - g_StartCounter.QuadPart) * 1000.0)
         / static_cast<double>(g_Frequency.QuadPart);
}

static void OpenLog()
{
    ::QueryPerformanceFrequency(&g_Frequency);
    ::QueryPerformanceCounter(&g_StartCounter);

    std::string logPath = GetGameDirectory() + "\\Script_FrameCollisionTest.log";

    g_pLog = std::fopen(logPath.c_str(), "w");

    if (g_pLog != nullptr)
    {
        std::fprintf(g_pLog, "Script_FrameCollisionTest v0.14 loaded.\n");

        std::fprintf(g_pLog, "GENERALIZED ACTOR / WEAPON-SLOT PROTOTYPE.\n");

        std::fprintf(g_pLog, "NO IsPlayer restriction.\n");

        std::fprintf(g_pLog, "NO 2H / Staff / 1H use-type restriction.\n");

        std::fprintf(g_pLog, "NO P0/P1/P2 restriction.\n");

        std::fprintf(g_pLog, "Normal eligibility: current animation contains _Attack_Hit_ and a RIGHT/LEFT source marker.\n");

        std::fprintf(g_pLog, "Quick eligibility: OnAI_QuickAttack + exact Quick/QuickR/QuickL action + Hit phase + a RIGHT/LEFT source marker.\n");

        std::fprintf(g_pLog, "Accepted Quick marker completes one-shot callback bookkeeping: StatePosition -> 1.\n");

        std::fprintf(g_pLog, "FIST CAUSAL TEST: raw Fist/PhysicalFist skips SetCollisionGroup(Item_Attack).\n");

        std::fprintf(g_pLog, "FIST CAUSAL TEST: ClearTriggeredList remains active.\n");

        std::fprintf(g_pLog, "G3AB_COL_TEST is the preserved RIGHT-hand marker alias.\n");

        std::fprintf(g_pLog, "G3AB_COL_LEFT_TEST is the provisional LEFT-hand marker.\n");

        std::fprintf(g_pLog, "RIGHT and LEFT use exact-set semantics: the selected source replaces the previous marker-owned set.\n");

        std::fprintf(g_pLog, "BOTH is intentionally disabled until LEFT and preserved RIGHT pass runtime validation.\n");

        std::fprintf(g_pLog, "If any source required by the exact motion is missing, its original attack callback is NOT suppressed.\n");

        std::fprintf(g_pLog, "This protects unarmed/monster attacks until body-source resolution is implemented.\n");

        std::fprintf(g_pLog, "Marker action: non-Fist -> Item_Attack + ClearTriggeredList; Fist -> ClearTriggeredList only.\n");

        std::fprintf(g_pLog, "G3AB_COL_OFF_TEST closes only a weapon window opened by this prototype.\n");

        std::fprintf(g_pLog, "OFF requests Item_Equipped and never clears the triggered list.\n");

        std::fprintf(g_pLog, "OFF before ON or after natural reset is consumed as a logged no-op.\n");

        std::fprintf(g_pLog, "Fist/body OFF remains unsupported; Gothic 3 still owns Hit->Recover reset.\n");

        std::fprintf(g_pLog, "Known collision groups: Item_Equipped=5, Item_Attack=7.\n");

        std::fprintf(g_pLog, "PASSIVE DUAL DISCOVERY: Item_Attack transitions are labelled by exact player LEFT/RIGHT slot entity identity.\n");

        std::fprintf(g_pLog, "A Dual both-weapon activation normally appears as separate LEFT and RIGHT transition records.\n");

        std::fprintf(g_pLog, "Preserved RIGHT Normal/Quick behavior remains the validated v0.9 path; LEFT is new and provisional.\n\n");

        std::fprintf(g_pLog, "v0.14 preserves same-update marker deduplication for RIGHT, LEFT, and OFF.\n");

        std::fprintf(g_pLog, "Dedup key: actor + RIGHT/LEFT slot snapshot + motion + marker + action + phase + state time; wall window <= 5 ms.\n\n");

        std::fprintf(g_pLog, "Authored-occurrence budgets are cached separately for RIGHT, LEFT, and OFF.\n");

        std::fprintf(g_pLog, "Budget key: actor + RIGHT/LEFT slot snapshot + motion + action + phase; state-time rollback starts a new execution.\n");

        std::fprintf(g_pLog, "Natural collision reset outside the owning Hit execution retires the actor budget.\n");

        std::fprintf(g_pLog, "No per-frame actor scan; budget work occurs only when a reserved marker is received.\n\n");

        std::fflush(g_pLog);
    }
}

static bool Contains(char const *text, char const *token)
{
    return text != nullptr && token != nullptr && std::strstr(text, token) != nullptr;
}

static MarkerOpcode GetMarkerOpcode(char const *effectName)
{
    if (effectName == nullptr)
        return MarkerOpcode_Invalid;

    if (std::strcmp(effectName, g_CollisionOnMarker) == 0)
        return MarkerOpcode_Right;

    if (std::strcmp(effectName, g_CollisionLeftMarker) == 0)
        return MarkerOpcode_Left;

    if (std::strcmp(effectName, g_CollisionOffMarker) == 0)
        return MarkerOpcode_Off;

    return MarkerOpcode_Invalid;
}

static char const *GetMarkerOpcodeName(MarkerOpcode opcode)
{
    switch (opcode)
    {
        case MarkerOpcode_Right: return "RIGHT";
        case MarkerOpcode_Left:  return "LEFT";
        case MarkerOpcode_Off:   return "OFF";
        default:                 return "INVALID";
    }
}

static unsigned int GetMarkerDesiredSourceMask(MarkerOpcode opcode)
{
    switch (opcode)
    {
        case MarkerOpcode_Right: return SourceMask_Right;
        case MarkerOpcode_Left:  return SourceMask_Left;
        default:                 return SourceMask_None;
    }
}

static bool IsSourceMarker(MarkerOpcode opcode)
{
    return opcode == MarkerOpcode_Right || opcode == MarkerOpcode_Left;
}

static GEInt GetAuthoredMarkerCount(CurrentMotionMarkerResult const &decision, MarkerOpcode opcode)
{
    return opcode >= 0 && opcode < MarkerOpcode_Count ? decision.markerCounts[opcode] : 0;
}

static GEInt GetFirstAuthoredMarkerFrame(CurrentMotionMarkerResult const &decision, MarkerOpcode opcode)
{
    return opcode >= 0 && opcode < MarkerOpcode_Count ? decision.firstMarkerFrames[opcode] : -1;
}

static char const *BaseName(char const *path)
{
    if (path == nullptr)
        return "";

    char const *slash1 = std::strrchr(path, '\\');

    char const *slash2 = std::strrchr(path, '/');

    char const *last = slash1;

    if (slash2 != nullptr && (last == nullptr || slash2 > last))
    {
        last = slash2;
    }

    return last != nullptr ? last + 1 : path;
}

static bool SameFileName(char const *a, char const *b)
{
    if (a == nullptr || b == nullptr)
        return false;

    return _stricmp(BaseName(a), BaseName(b)) == 0;
}

static GEFloat AbsoluteFloat(GEFloat value)
{
    return value < 0.0f ? -value : value;
}

static bool IsDuplicateSameUpdateMarker(eCEntity *actorInstance, EquippedCollisionSources const &sources,
                                        char const *animationName, char const *markerName,
                                        GEInt action, GEInt phase, GEFloat stateTime,
                                        double elapsedMs, GEFloat &stateTimeDelta,
                                        double &elapsedMsDelta)
{
    stateTimeDelta = 0.0f;
    elapsedMsDelta = 0.0;

    auto found = g_LastAcceptedMarkerDispatchByActor.find(actorInstance);

    if (found == g_LastAcceptedMarkerDispatchByActor.end())
        return false;

    LastAcceptedMarkerDispatch const &previous = found->second;

    stateTimeDelta = AbsoluteFloat(stateTime - previous.stateTime);
    elapsedMsDelta = elapsedMs - previous.elapsedMs;

    return previous.rightSourceInstance == sources.rightInstance
        && previous.leftSourceInstance == sources.leftInstance
        && SameFileName(previous.animationName.c_str(), animationName)
        && previous.markerName == (markerName != nullptr ? markerName : "")
        && previous.action == action
        && previous.phase == phase
        && stateTimeDelta <= 0.000001f
        && elapsedMsDelta >= 0.0
        && elapsedMsDelta <= 5.0;
}

static void RememberAcceptedMarker(eCEntity *actorInstance, EquippedCollisionSources const &sources,
                                   char const *animationName, char const *markerName,
                                   GEInt action, GEInt phase, GEFloat stateTime,
                                   double elapsedMs)
{
    LastAcceptedMarkerDispatch record = {};

    record.rightSourceInstance = sources.rightInstance;
    record.leftSourceInstance = sources.leftInstance;
    record.animationName = animationName != nullptr ? animationName : "";
    record.markerName = markerName != nullptr ? markerName : "";
    record.action = action;
    record.phase = phase;
    record.stateTime = stateTime;
    record.elapsedMs = elapsedMs;

    g_LastAcceptedMarkerDispatchByActor[actorInstance] = record;
}

static void ForgetMarkerExecutionForActor(eCEntity *actorInstance)
{
    if (actorInstance == nullptr)
        return;

    g_MarkerExecutionBudgetByActor.erase(actorInstance);
    g_LastAcceptedMarkerDispatchByActor.erase(actorInstance);
}

static bool TryConsumeAuthoredMarkerOccurrence(eCEntity *actorInstance, EquippedCollisionSources const &sources,
                                               char const *animationName, GEInt action, GEInt phase,
                                               GEFloat stateTime, MarkerOpcode opcode,
                                               CurrentMotionMarkerResult const &decision,
                                               GEInt &authoredCount, GEInt &acceptedBefore,
                                               GEInt &acceptedAfter, bool &executionReset)
{
    authoredCount = GetAuthoredMarkerCount(decision, opcode);
    acceptedBefore = 0;
    acceptedAfter = 0;
    executionReset = false;

    auto found = g_MarkerExecutionBudgetByActor.find(actorInstance);

    bool startsNewExecution = found == g_MarkerExecutionBudgetByActor.end();

    if (!startsNewExecution)
    {
        MarkerExecutionBudget const &previous = found->second;

        startsNewExecution = previous.rightSourceInstance != sources.rightInstance
                          || previous.leftSourceInstance != sources.leftInstance
                          || !SameFileName(previous.animationName.c_str(), animationName)
                          || previous.action != action
                          || previous.phase != phase
                          || stateTime + 0.000001f < previous.lastMarkerStateTime;

        for (GEInt i = 0; !startsNewExecution && i < MarkerOpcode_Count; ++i)
        {
            startsNewExecution = previous.authoredCounts[i] != decision.markerCounts[i];
        }
    }

    if (startsNewExecution)
    {
        MarkerExecutionBudget record = {};

        record.rightSourceInstance = sources.rightInstance;
        record.leftSourceInstance = sources.leftInstance;
        record.animationName = animationName != nullptr ? animationName : "";
        record.action = action;
        record.phase = phase;

        for (GEInt i = 0; i < MarkerOpcode_Count; ++i)
        {
            record.authoredCounts[i] = decision.markerCounts[i];
            record.acceptedCounts[i] = 0;
        }

        record.lastMarkerStateTime = stateTime;

        g_MarkerExecutionBudgetByActor[actorInstance] = record;
        found = g_MarkerExecutionBudgetByActor.find(actorInstance);
        executionReset = true;
    }

    MarkerExecutionBudget &record = found->second;

    if (opcode < 0 || opcode >= MarkerOpcode_Count)
        return false;

    GEInt &acceptedCount = record.acceptedCounts[opcode];

    acceptedBefore = acceptedCount;
    acceptedAfter = acceptedCount;

    if (authoredCount <= 0 || acceptedCount >= authoredCount)
        return false;

    ++acceptedCount;
    record.lastMarkerStateTime = stateTime;
    acceptedAfter = acceptedCount;

    return true;
}

static void RememberMarkerOwnedWindow(eCEntity *actorInstance, EquippedCollisionSources const &sources,
                                      unsigned int activeSourceMask, char const *animationName,
                                      GEInt action, GEInt phase)
{
    MarkerOwnedCollisionWindow record = {};

    record.rightSourceInstance = sources.rightInstance;
    record.leftSourceInstance = sources.leftInstance;
    record.activeSourceMask = activeSourceMask;
    record.animationName = animationName != nullptr ? animationName : "";
    record.action = action;
    record.phase = phase;

    g_MarkerOwnedWindowByActor[actorInstance] = record;
}

static MarkerOwnedCollisionWindow *FindMatchingMarkerOwnedWindow(eCEntity *actorInstance,
                                                                 EquippedCollisionSources const &sources,
                                                                 char const *animationName,
                                                                 GEInt action, GEInt phase)
{
    auto found = g_MarkerOwnedWindowByActor.find(actorInstance);

    if (found == g_MarkerOwnedWindowByActor.end())
        return nullptr;

    MarkerOwnedCollisionWindow &record = found->second;

    bool matches = record.rightSourceInstance == sources.rightInstance
                && record.leftSourceInstance == sources.leftInstance
                && SameFileName(record.animationName.c_str(), animationName)
                && record.action == action
                && record.phase == phase;

    return matches ? &record : nullptr;
}

static void ForgetMarkerOwnedWindowForActor(eCEntity *actorInstance)
{
    if (actorInstance != nullptr)
    {
        g_MarkerOwnedWindowByActor.erase(actorInstance);
    }
}

static bool MarkerWindowStillMatchesActorExecution(eCEntity *actorInstance,
                                                    MarkerOwnedCollisionWindow const &record)
{
    if (actorInstance == nullptr)
        return false;

    Entity actor(actorInstance);
    bCString currentAnimation = actor.NPC.GetCurrentMovementAni();
    GEInt currentAction = static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    GEInt currentPhase = static_cast<GEInt>(actor.GetCurrentAniPhase());

    return SameFileName(record.animationName.c_str(), currentAnimation.GetText())
        && record.action == currentAction
        && record.phase == currentPhase;
}

static void RetireMarkerOwnedSource(eCEntity *sourceInstance)
{
    if (sourceInstance == nullptr)
        return;

    for (auto entry = g_MarkerOwnedWindowByActor.begin(); entry != g_MarkerOwnedWindowByActor.end();)
    {
        MarkerOwnedCollisionWindow &record = entry->second;

        bool retiredSource = false;

        if ((record.activeSourceMask & SourceMask_Right) != 0
            && record.rightSourceInstance == sourceInstance)
        {
            record.activeSourceMask &= ~SourceMask_Right;
            retiredSource = true;
        }

        if ((record.activeSourceMask & SourceMask_Left) != 0
            && record.leftSourceInstance == sourceInstance)
        {
            record.activeSourceMask &= ~SourceMask_Left;
            retiredSource = true;
        }

        if (retiredSource)
        {
            if (!MarkerWindowStillMatchesActorExecution(entry->first, record))
            {
                ForgetMarkerExecutionForActor(entry->first);
            }

            if (record.activeSourceMask == SourceMask_None)
            {
                entry = g_MarkerOwnedWindowByActor.erase(entry);
            }
            else
            {
                ++entry;
            }
        }
        else
        {
            ++entry;
        }
    }
}

static bool IsAttackHit(Entity &actor)
{
    bCString ani = actor.NPC.GetCurrentMovementAni();

    return Contains(ani.GetText(), "_Attack_Hit_");
}

static bool IsQuickAttackAction(gEAction action)
{
    return action == gEAction_QuickAttack || action == gEAction_QuickAttackR || action == gEAction_QuickAttackL;
}

static bool IsQuickAttackHit(Entity &actor)
{
    gEAction action = actor.Routine.GetProperty<PSRoutine::PropertyAction>();

    return IsQuickAttackAction(action) && actor.GetCurrentAniPhase() == gEPhase_Hit;
}

static EquippedCollisionSources GetEquippedCollisionSources(Entity &actor)
{
    EquippedCollisionSources result = {};

    Entity right = actor.Inventory.GetItemFromSlot(gESlot_RightHand);
    Entity left = actor.Inventory.GetItemFromSlot(gESlot_LeftHand);

    result.rightInstance = right != None ? right.GetInstance() : nullptr;
    result.leftInstance = left != None ? left.GetInstance() : nullptr;

    return result;
}

static bool HasRequiredCollisionSources(EquippedCollisionSources const &sources, unsigned int requiredMask)
{
    if ((requiredMask & SourceMask_Right) != 0 && sources.rightInstance == nullptr)
        return false;

    if ((requiredMask & SourceMask_Left) != 0 && sources.leftInstance == nullptr)
        return false;

    return true;
}

static eCEntity *GetSourceInstance(EquippedCollisionSources const &sources, unsigned int sourceMask)
{
    if (sourceMask == SourceMask_Right)
        return sources.rightInstance;

    if (sourceMask == SourceMask_Left)
        return sources.leftInstance;

    return nullptr;
}

static gEUseType GetCollisionSourceUseType(Entity &source)
{
    eCEntity *instance = source.GetInstance();

    return instance != nullptr ? gCEntity::GetUseType(instance) : gEUseType_None;
}

static bool IsFistCollisionSource(Entity &source)
{
    if (source == None)
        return false;

    gEUseType useType = GetCollisionSourceUseType(source);

    return useType == gEUseType_Fist || useType == gEUseType_PhysicalFist;
}

static void LogPlayerSlotIdentity(eCEntity *changedEntity)
{
    if (g_pLog == nullptr)
        return;

    Entity player = Entity::GetPlayer();

    if (player == None)
    {
        std::fprintf(g_pLog, "PlayerSlotMatch: NO_PLAYER\n");

        return;
    }

    Entity leftItem = player.Inventory.GetItemFromSlot(gESlot_LeftHand);

    Entity rightItem = player.Inventory.GetItemFromSlot(gESlot_RightHand);

    eCEntity *leftInstance = leftItem != None ? leftItem.GetInstance() : nullptr;

    eCEntity *rightInstance = rightItem != None ? rightItem.GetInstance() : nullptr;

    bool matchesLeft = changedEntity != nullptr && changedEntity == leftInstance;

    bool matchesRight = changedEntity != nullptr && changedEntity == rightInstance;

    char const *slotMatch = matchesLeft && matchesRight ? "BOTH"
                          : matchesLeft                 ? "LEFT"
                          : matchesRight                ? "RIGHT"
                                                        : "NONE";

    bCString currentAni = player.NPC.GetCurrentMovementAni();

    std::fprintf(g_pLog, "ChangedEntityAddress: %p\n", static_cast<void *>(changedEntity));

    std::fprintf(g_pLog, "PlayerSlotMatch: %s\n", slotMatch);

    std::fprintf(g_pLog, "PlayerAction: %d\n",
                 static_cast<GEInt>(player.Routine.GetProperty<PSRoutine::PropertyAction>()));

    std::fprintf(g_pLog, "PlayerAniPhase: %d\n", static_cast<GEInt>(player.GetCurrentAniPhase()));

    std::fprintf(g_pLog, "PlayerPrimaryPose: %d\n", static_cast<GEInt>(player.NPC.GetPrimaryPose()));

    std::fprintf(g_pLog, "PlayerStateTime: %.6f\n", player.Routine.GetStateTime());

    std::fprintf(g_pLog, "PlayerStatePosition: %d\n",
                 static_cast<GEInt>(player.Routine.GetProperty<PSRoutine::PropertyStatePosition>()));

    std::fprintf(g_pLog, "PlayerCurrentMovementAni: %s\n", currentAni.GetText());

    std::fprintf(g_pLog, "PlayerLeftItem: %s\n", leftItem != None ? leftItem.GetName().GetText() : "<none>");

    std::fprintf(g_pLog, "PlayerLeftItemAddress: %p\n", static_cast<void *>(leftInstance));

    std::fprintf(g_pLog, "PlayerLeftUseType: %d\n",
                 leftItem != None ? static_cast<GEInt>(GetCollisionSourceUseType(leftItem)) : -1);

    std::fprintf(g_pLog, "PlayerLeftCollisionGroup: %d\n",
                 leftItem != None ? static_cast<GEInt>(leftItem.GetCollisionGroup()) : -1);

    std::fprintf(g_pLog, "PlayerRightItem: %s\n", rightItem != None ? rightItem.GetName().GetText() : "<none>");

    std::fprintf(g_pLog, "PlayerRightItemAddress: %p\n", static_cast<void *>(rightInstance));

    std::fprintf(g_pLog, "PlayerRightUseType: %d\n",
                 rightItem != None ? static_cast<GEInt>(GetCollisionSourceUseType(rightItem)) : -1);

    std::fprintf(g_pLog, "PlayerRightCollisionGroup: %d\n",
                 rightItem != None ? static_cast<GEInt>(rightItem.GetCollisionGroup()) : -1);
}

// -----------------------------------------------------------------------------
// Frame-effect scan
//
// CONFIRMED runtime layout:
//
// eCResourceAnimationMotion_PS
//     +0x4C = frame-effect array data pointer
//     +0x50 = frame-effect count
//
// eSFrameEffect
//     +0x00 = GEU16 authored frame
//     +0x04 = bCString effect name
//     stride = 8 bytes
// -----------------------------------------------------------------------------

static FrameEffectScanResult ScanFrameEffects(eCResourceAnimationMotion_PS const *motion)
{
    FrameEffectScanResult result = {};

    result.layoutLookedValid = false;
    result.foundMarker = false;
    result.count = 0;
    result.requiredSourceMask = SourceMask_None;

    for (GEInt i = 0; i < MarkerOpcode_Count; ++i)
    {
        result.firstMarkerFrames[i] = -1;
        result.markerCounts[i] = 0;
    }

    if (motion == nullptr)
        return result;

    unsigned char const *base = reinterpret_cast<unsigned char const *>(motion);

    unsigned char const *data = *reinterpret_cast<unsigned char const *const *>(base + 0x4C);

    GEInt count = *reinterpret_cast<GEInt const *>(base + 0x50);

    result.count = count;

    if (count < 0 || count > 256)
        return result;

    if (count > 0 && data == nullptr)
        return result;

    result.layoutLookedValid = true;

    for (GEInt i = 0; i < count; ++i)
    {
        unsigned char const *entry = data + (i * 8);

        GEU16 authoredFrame = *reinterpret_cast<GEU16 const *>(entry + 0x00);

        bCString const *effectString = reinterpret_cast<bCString const *>(entry + 0x04);

        char const *effectName = effectString->GetText();

        MarkerOpcode opcode = GetMarkerOpcode(effectName);

        if (opcode == MarkerOpcode_Invalid)
            continue;

        ++result.markerCounts[opcode];

        if (result.firstMarkerFrames[opcode] < 0)
        {
            result.firstMarkerFrames[opcode] = static_cast<GEInt>(authoredFrame);
        }

        if (IsSourceMarker(opcode))
        {
            result.foundMarker = true;
            result.requiredSourceMask |= GetMarkerDesiredSourceMask(opcode);
        }
    }

    return result;
}

static CurrentMotionMarkerResult ScanCurrentMotionForMarker(Entity &actor)
{
    CurrentMotionMarkerResult result = {};

    result.foundMatchingMotion = false;
    result.markerPresent = false;
    result.frameEffectCount = 0;
    result.requiredSourceMask = SourceMask_None;

    for (GEInt i = 0; i < MarkerOpcode_Count; ++i)
    {
        result.firstMarkerFrames[i] = -1;
        result.markerCounts[i] = 0;
    }

    eCEntity *instance = actor.GetInstance();

    if (instance == nullptr)
        return result;

    eCEntityPropertySet *propertySet = instance->GetPropertySet(eEPropertySetType_Animation);

    if (propertySet == nullptr)
        return result;

    eCVisualAnimation_PS *visualAnimation = static_cast<eCVisualAnimation_PS *>(propertySet);

    bCString currentAni = actor.NPC.GetCurrentMovementAni();

    char const *currentAniName = currentAni.GetText();

    for (GEInt i = 0; i < 4; ++i)
    {
        eCWrapper_emfx2Actor::eEMotionType type = static_cast<eCWrapper_emfx2Actor::eEMotionType>(i);

        eCVisualAnimation_PS::eSMotionDesc const &desc = visualAnimation->GetMotionDesc(type);

        if (desc.IsValid() == GEFalse)
            continue;

        bCString const &motionFilename = desc.GetMotionFilename();

        if (!SameFileName(motionFilename.GetText(), currentAniName))
        {
            continue;
        }

        result.foundMatchingMotion = true;

        eCResourceAnimationMotion_PS const *motion = desc.GetMotion();

        FrameEffectScanResult scan = ScanFrameEffects(motion);

        result.frameEffectCount = scan.count;

        result.markerPresent = scan.layoutLookedValid && scan.foundMarker;

        result.requiredSourceMask = scan.requiredSourceMask;

        for (GEInt opcode = 0; opcode < MarkerOpcode_Count; ++opcode)
        {
            result.firstMarkerFrames[opcode] = scan.firstMarkerFrames[opcode];
            result.markerCounts[opcode] = scan.markerCounts[opcode];
        }

        return result;
    }

    return result;
}

static CurrentMotionMarkerResult GetCurrentMarkerDecision(Entity &actor)
{
    bCString currentAni = actor.NPC.GetCurrentMovementAni();

    std::string currentName = currentAni.GetText() != nullptr ? currentAni.GetText() : "";

    auto found = g_MarkerCache.find(currentName);

    if (found != g_MarkerCache.end())
    {
        CurrentMotionMarkerResult result = {};

        result.foundMatchingMotion = found->second.foundMatchingMotion;

        result.markerPresent = found->second.markerPresent;

        result.frameEffectCount = found->second.frameEffectCount;

        result.requiredSourceMask = found->second.requiredSourceMask;

        for (GEInt opcode = 0; opcode < MarkerOpcode_Count; ++opcode)
        {
            result.firstMarkerFrames[opcode] = found->second.firstMarkerFrames[opcode];
            result.markerCounts[opcode] = found->second.markerCounts[opcode];
        }

        return result;
    }

    CurrentMotionMarkerResult scanned = ScanCurrentMotionForMarker(actor);

    CachedMarkerInfo cached = {};

    cached.foundMatchingMotion = scanned.foundMatchingMotion;

    cached.markerPresent = scanned.markerPresent;

    cached.frameEffectCount = scanned.frameEffectCount;

    cached.requiredSourceMask = scanned.requiredSourceMask;

    for (GEInt opcode = 0; opcode < MarkerOpcode_Count; ++opcode)
    {
        cached.firstMarkerFrames[opcode] = scanned.firstMarkerFrames[opcode];
        cached.markerCounts[opcode] = scanned.markerCounts[opcode];
    }

    g_MarkerCache[currentName] = cached;

    return scanned;
}

// -----------------------------------------------------------------------------
// Diagnostic helpers
// -----------------------------------------------------------------------------

static bool ShouldLogOwnership(Entity &actor)
{
    eCEntity *instance = actor.GetInstance();

    if (instance == nullptr)
        return true;

    bCString ani = actor.NPC.GetCurrentMovementAni();

    std::string currentName = ani.GetText() != nullptr ? ani.GetText() : "";

    auto found = g_LastLoggedAni.find(instance);

    if (found != g_LastLoggedAni.end() && found->second == currentName)
    {
        return false;
    }

    g_LastLoggedAni[instance] = currentName;

    return true;
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
                 static_cast<GEInt>(GetCollisionSourceUseType(source)));
    std::fprintf(g_pLog, "%sSourceCollisionGroup: %d\n", label,
                 static_cast<GEInt>(source.GetCollisionGroup()));
}

static void LogOwnershipDecision(Entity &actor, CurrentMotionMarkerResult const &decision,
                                 EquippedCollisionSources const &sources,
                                 bool willSuppress)
{
    if (g_pLog == nullptr)
        return;

    bCString ani = actor.NPC.GetCurrentMovementAni();

    std::fprintf(g_pLog, "===== MARKER OWNERSHIP DECISION =====\n");

    std::fprintf(g_pLog, "ElapsedMs: %.3f\n", GetElapsedMilliseconds());

    std::fprintf(g_pLog, "Actor: %s\n", actor.GetName().GetText());

    std::fprintf(g_pLog, "CurrentMovementAni: %s\n", ani.GetText());

    std::fprintf(g_pLog, "MatchingMotionFound: %d\n", decision.foundMatchingMotion ? 1 : 0);

    std::fprintf(g_pLog, "FrameEffectCount: %d\n", decision.frameEffectCount);

    std::fprintf(g_pLog, "ContainsReservedSourceMarker: %d\n", decision.markerPresent ? 1 : 0);
    std::fprintf(g_pLog, "RequiredSourceMask: %u\n", decision.requiredSourceMask);

    for (GEInt opcode = 0; opcode < MarkerOpcode_Count; ++opcode)
    {
        std::fprintf(g_pLog, "Authored%sMarkerCount: %d\n",
                     GetMarkerOpcodeName(static_cast<MarkerOpcode>(opcode)), decision.markerCounts[opcode]);
        std::fprintf(g_pLog, "First%sMarkerFrame: %d\n",
                     GetMarkerOpcodeName(static_cast<MarkerOpcode>(opcode)), decision.firstMarkerFrames[opcode]);
    }

    LogResolvedSource("RightHand", sources.rightInstance);
    LogResolvedSource("LeftHand", sources.leftInstance);

    std::fprintf(g_pLog, "Decision: %s\n",
                 willSuppress ? "FRAME-CONTROLLED - suppress original timer callback"
                              : "LEGACY/NATIVE - call original timer callback");

    if (decision.markerPresent && !HasRequiredCollisionSources(sources, decision.requiredSourceMask))
    {
        std::fprintf(g_pLog, "Reason: at least one source required by the exact motion is missing.\n");
    }

    std::fprintf(g_pLog, "=====================================\n\n");

    std::fflush(g_pLog);
}

static void LogMarkerContext(char const *markerName, MarkerOpcode opcode, Entity &actor,
                             EquippedCollisionSources const &sources)
{
    if (g_pLog == nullptr)
        return;

    bCString ani = actor.NPC.GetCurrentMovementAni();

    std::fprintf(g_pLog, "===== %s RECEIVED =====\n", markerName != nullptr ? markerName : "<null>");

    std::fprintf(g_pLog, "ElapsedMs: %.3f\n", GetElapsedMilliseconds());

    std::fprintf(g_pLog, "Actor: %s\n", actor.GetName().GetText());

    std::fprintf(g_pLog, "Action: %d\n", static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyAction>()));

    std::fprintf(g_pLog, "AniPhase: %d\n", static_cast<GEInt>(actor.GetCurrentAniPhase()));

    std::fprintf(g_pLog, "StateTime: %.6f\n", actor.Routine.GetStateTime());

    std::fprintf(g_pLog, "StatePosition: %d\n",
                 static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>()));

    std::fprintf(g_pLog, "CurrentMovementAni: %s\n", ani.GetText());
    std::fprintf(g_pLog, "MarkerOpcode: %s\n", GetMarkerOpcodeName(opcode));

    LogResolvedSource("RightHand", sources.rightInstance);
    LogResolvedSource("LeftHand", sources.leftInstance);
}

// -----------------------------------------------------------------------------
// Engine eCEntity::SetCollisionGroup logger
//
// v0.6 no longer filters to the player's weapon.
// It logs ANY entity transition involving Item_Attack so NPC/staff activation
// and natural reset are directly visible.
// -----------------------------------------------------------------------------

static void GE_STDCALL SetCollisionGroup_FrameCollisionTest(eECollisionGroup a_Group)
{
    eCEntity *pThis = Hook_SetCollisionGroup.GetSelf<eCEntity *>();

    eECollisionGroup beforeGroup = pThis != nullptr ? pThis->GetCollisionGroup() : static_cast<eECollisionGroup>(-1);

    Hook_SetCollisionGroup.GetOriginalFunction (&SetCollisionGroup_FrameCollisionTest)(a_Group);

    if (pThis != nullptr && pThis->GetCollisionGroup() != eECollisionGroup_Item_Attack)
    {
        RetireMarkerOwnedSource(pThis);
    }

    if (pThis == nullptr || g_pLog == nullptr)
    {
        return;
    }

    eECollisionGroup afterGroup = pThis->GetCollisionGroup();

    bool involvesAttack = a_Group == eECollisionGroup_Item_Attack || beforeGroup == eECollisionGroup_Item_Attack
                       || afterGroup == eECollisionGroup_Item_Attack;

    if (!involvesAttack)
        return;

    Entity changedEntity(pThis);

    std::fprintf(g_pLog, "===== ENGINE SetCollisionGroup =====\n");

    std::fprintf(g_pLog, "ElapsedMs: %.3f\n", GetElapsedMilliseconds());

    std::fprintf(g_pLog, "Entity: %s\n", changedEntity.GetName().GetText());

    LogPlayerSlotIdentity(pThis);

    std::fprintf(g_pLog, "RequestedGroup: %d\n", static_cast<GEInt>(a_Group));

    std::fprintf(g_pLog, "BeforeGroup: %d\n", static_cast<GEInt>(beforeGroup));

    std::fprintf(g_pLog, "AfterGroup: %d\n", static_cast<GEInt>(afterGroup));

    std::fprintf(g_pLog, "Item_EquippedValue: %d\n", static_cast<GEInt>(eECollisionGroup_Item_Equipped));

    std::fprintf(g_pLog, "Item_AttackValue: %d\n", static_cast<GEInt>(eECollisionGroup_Item_Attack));

    std::fprintf(g_pLog, "====================================\n\n");

    std::fflush(g_pLog);
}

// -----------------------------------------------------------------------------
// OnAI_Attack
//
// v0.6:
//     ANY actor.
//     ANY weapon/use type.
//     ANY P-position.
//
// A marked Attack_Hit is controlled only when every equipped source required
// by the exact motion can be resolved.
//
// If source cannot be resolved, original callback remains untouched.
// -----------------------------------------------------------------------------

DECLARE_SCRIPT_CALLBACK(OnAI_Attack_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()

    if (!IsAttackHit(SelfEntity))
    {
        return Hook_OnAI_Attack.GetOriginalFunction(&OnAI_Attack_FrameCollisionTest)(a_pSPU);
    }

    CurrentMotionMarkerResult decision = GetCurrentMarkerDecision(SelfEntity);

    EquippedCollisionSources sources = GetEquippedCollisionSources(SelfEntity);

    bool willSuppress = decision.foundMatchingMotion && decision.markerPresent
                     && HasRequiredCollisionSources(sources, decision.requiredSourceMask);

    if (ShouldLogOwnership(SelfEntity))
    {
        LogOwnershipDecision(SelfEntity, decision, sources, willSuppress);
    }

    if (willSuppress)
    {
        return GETrue;
    }

    return Hook_OnAI_Attack.GetOriginalFunction(&OnAI_Attack_FrameCollisionTest)(a_pSPU);
}

// -----------------------------------------------------------------------------
// OnAI_QuickAttack
//
// v0.7 adds only the native Quick callback family.
//
// Exact Quick/QuickR/QuickL action and Hit phase replace filename-family
// parsing for this path. Marker ownership and equipped-slot preflight remain
// identical to the Normal path.
// -----------------------------------------------------------------------------

DECLARE_SCRIPT_CALLBACK(OnAI_QuickAttack_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()

    if (!IsQuickAttackHit(SelfEntity))
    {
        return Hook_OnAI_QuickAttack.GetOriginalFunction(&OnAI_QuickAttack_FrameCollisionTest)(a_pSPU);
    }

    CurrentMotionMarkerResult decision = GetCurrentMarkerDecision(SelfEntity);

    EquippedCollisionSources sources = GetEquippedCollisionSources(SelfEntity);

    bool willSuppress = decision.foundMatchingMotion && decision.markerPresent
                     && HasRequiredCollisionSources(sources, decision.requiredSourceMask);

    if (ShouldLogOwnership(SelfEntity))
    {
        LogOwnershipDecision(SelfEntity, decision, sources, willSuppress);
    }

    if (willSuppress)
    {
        return GETrue;
    }

    return Hook_OnAI_QuickAttack.GetOriginalFunction(&OnAI_QuickAttack_FrameCollisionTest)(a_pSPU);
}

// -----------------------------------------------------------------------------
// StartEffect
//
// These remain PROTOTYPE markers. Their current meanings are:
//
//     G3AB_COL_TEST      -> exact active set { RIGHT }.
//     G3AB_COL_LEFT_TEST -> exact active set { LEFT }.
//     G3AB_COL_OFF_TEST  -> exact active set { } for the matching window.
//
// BOTH remains deliberately unrecognized until LEFT and preserved RIGHT are
// validated independently.
// -----------------------------------------------------------------------------

static GELPVoid StartEffect_FrameCollisionTest(bCString const &a_EffectName, eCEntity *a_pEntity1, eCEntity *a_pEntity2,
                                               bCMatrix const *a_pMatrix, GEBool a_bUnknown)
{
    GELPCChar effectName = a_EffectName.GetText();
    MarkerOpcode markerOpcode = GetMarkerOpcode(effectName);

    if (markerOpcode == MarkerOpcode_Invalid)
    {
        return Hook_StartEffect.GetOriginalFunction(&StartEffect_FrameCollisionTest)(a_EffectName, a_pEntity1,
                                                                                     a_pEntity2, a_pMatrix, a_bUnknown);
    }

    // Reserved test marker is consumed even if the actor/source cannot be
    // resolved, so the engine never tries to find a real effect resource
    // named G3AB_COL_TEST / G3AB_COL_LEFT_TEST / G3AB_COL_OFF_TEST.
    if (a_pEntity1 == nullptr)
    {
        if (g_pLog != nullptr)
        {
            std::fprintf(g_pLog, "===== %s RECEIVED =====\n", effectName);

            std::fprintf(g_pLog, "MarkerAction: REJECTED - Entity1 == NULL\n");

            std::fprintf(g_pLog, "=================================\n\n");

            std::fflush(g_pLog);
        }

        return nullptr;
    }

    Entity actor(a_pEntity1);
    EquippedCollisionSources sources = GetEquippedCollisionSources(actor);

    LogMarkerContext(effectName, markerOpcode, actor, sources);

    bool isNormalAttackHit = IsAttackHit(actor);

    bool isQuickAttackHit = IsQuickAttackHit(actor);

    if (!isNormalAttackHit && !isQuickAttackHit)
    {
        if (g_pLog != nullptr)
        {
            std::fprintf(g_pLog, "MarkerAction: REJECTED - unsupported Normal/Quick Hit context\n");

            std::fprintf(g_pLog, "=================================\n\n");

            std::fflush(g_pLog);
        }

        return nullptr;
    }

    CurrentMotionMarkerResult decision = GetCurrentMarkerDecision(actor);

    if (!decision.foundMatchingMotion || !decision.markerPresent
        || GetAuthoredMarkerCount(decision, markerOpcode) <= 0)
    {
        if (g_pLog != nullptr)
        {
            std::fprintf(g_pLog, "MarkerAction: REJECTED - current matching motion does not own marker\n");

            std::fprintf(g_pLog, "=================================\n\n");

            std::fflush(g_pLog);
        }

        return nullptr;
    }

    if (!HasRequiredCollisionSources(sources, decision.requiredSourceMask))
    {
        if (g_pLog != nullptr)
        {
            std::fprintf(
                g_pLog,
                "MarkerAction: UNSUPPORTED SOURCE - exact motion requires a missing equipped slot; original attack-family callback was left active\n");

            std::fprintf(g_pLog, "RequiredSourceMask: %u\n", decision.requiredSourceMask);

            std::fprintf(g_pLog, "=================================\n\n");

            std::fflush(g_pLog);
        }

        return nullptr;
    }

    bCString currentAnimation = actor.NPC.GetCurrentMovementAni();

    GEInt markerAction = static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyAction>());

    GEInt markerPhase = static_cast<GEInt>(actor.GetCurrentAniPhase());

    GEFloat markerStateTime = actor.Routine.GetStateTime();

    double markerElapsedMs = GetElapsedMilliseconds();

    GEFloat duplicateStateTimeDelta = 0.0f;

    double duplicateElapsedMsDelta = 0.0;

    if (IsDuplicateSameUpdateMarker(a_pEntity1, sources, currentAnimation.GetText(), effectName,
                                    markerAction, markerPhase, markerStateTime, markerElapsedMs,
                                    duplicateStateTimeDelta, duplicateElapsedMsDelta))
    {
        if (g_pLog != nullptr)
        {
            std::fprintf(g_pLog, "MarkerAction: DUPLICATE_SAME_UPDATE_IGNORED\n");

            std::fprintf(g_pLog, "AuthoredMarkerFrame: %d\n",
                         GetFirstAuthoredMarkerFrame(decision, markerOpcode));

            std::fprintf(g_pLog, "DuplicateStateTimeDelta: %.9f\n", duplicateStateTimeDelta);

            std::fprintf(g_pLog, "DuplicateElapsedMsDelta: %.6f\n", duplicateElapsedMsDelta);

            std::fprintf(g_pLog, "SetCollisionGroupAction: NOT_REQUESTED_DUPLICATE\n");

            std::fprintf(g_pLog, "TriggeredDamageList: NOT_CLEARED_DUPLICATE\n");

            std::fprintf(g_pLog, "Original StartEffect for marker: NOT CALLED\n");

            std::fprintf(g_pLog, "=================================\n\n");

            std::fflush(g_pLog);
        }

        return nullptr;
    }

    GEInt authoredMarkerCount = 0;

    GEInt acceptedMarkerCountBefore = 0;

    GEInt acceptedMarkerCountAfter = 0;

    bool executionBudgetReset = false;

    bool occurrenceAccepted = TryConsumeAuthoredMarkerOccurrence(
        a_pEntity1, sources, currentAnimation.GetText(), markerAction, markerPhase,
        markerStateTime, markerOpcode, decision,
        authoredMarkerCount, acceptedMarkerCountBefore, acceptedMarkerCountAfter, executionBudgetReset);

    if (!occurrenceAccepted)
    {
        if (g_pLog != nullptr)
        {
            std::fprintf(g_pLog, "MarkerAction: AUTHORED_OCCURRENCE_BUDGET_IGNORED\n");

            std::fprintf(g_pLog, "MarkerName: %s\n", effectName);

            std::fprintf(g_pLog, "AuthoredMarkerOccurrences: %d\n", authoredMarkerCount);

            std::fprintf(g_pLog, "AcceptedMarkerOccurrencesBefore: %d\n", acceptedMarkerCountBefore);

            std::fprintf(g_pLog, "AcceptedMarkerOccurrencesAfter: %d\n", acceptedMarkerCountAfter);

            std::fprintf(g_pLog, "ExecutionBudgetReset: %d\n", executionBudgetReset ? 1 : 0);

            std::fprintf(g_pLog, "SetCollisionGroupAction: NOT_REQUESTED_BUDGET_EXHAUSTED\n");

            std::fprintf(g_pLog, "TriggeredDamageList: NOT_CLEARED_BUDGET_EXHAUSTED\n");

            std::fprintf(g_pLog, "Original StartEffect for marker: NOT CALLED\n");

            std::fprintf(g_pLog, "=================================\n\n");

            std::fflush(g_pLog);
        }

        return nullptr;
    }

    if (markerOpcode == MarkerOpcode_Off)
    {
        MarkerOwnedCollisionWindow *window = FindMatchingMarkerOwnedWindow(
            a_pEntity1, sources, currentAnimation.GetText(), markerAction, markerPhase);

        unsigned int ownedMask = window != nullptr ? window->activeSourceMask : SourceMask_None;
        GEInt deactivatedSourceCount = 0;

        // Remove marker ownership before requesting Item_Equipped so the
        // SetCollisionGroup hook observes an intentional OFF transition and
        // does not retire this execution's remaining occurrence budget.
        if (window != nullptr)
            window->activeSourceMask = SourceMask_None;

        unsigned int sourceMasks[2] = { SourceMask_Right, SourceMask_Left };

        for (GEInt i = 0; i < 2; ++i)
        {
            unsigned int sourceMask = sourceMasks[i];

            if ((ownedMask & sourceMask) == 0)
                continue;

            eCEntity *sourceInstance = GetSourceInstance(sources, sourceMask);

            if (sourceInstance == nullptr)
                continue;

            Entity source(sourceInstance);

            if (!IsFistCollisionSource(source)
                && source.GetCollisionGroup() == eECollisionGroup_Item_Attack)
            {
                source.SetCollisionGroup(eECollisionGroup_Item_Equipped);
                ++deactivatedSourceCount;
            }
        }

        if (window != nullptr)
            ForgetMarkerOwnedWindowForActor(a_pEntity1);

        RememberAcceptedMarker(a_pEntity1, sources, currentAnimation.GetText(), effectName,
                               markerAction, markerPhase, markerStateTime, markerElapsedMs);

        if (g_pLog != nullptr)
        {
            std::fprintf(g_pLog, "MarkerAction: %s\n",
                         ownedMask != SourceMask_None ? "OFF_ACCEPTED" : "OFF_NO_MARKER_OWNED_WINDOW");

            std::fprintf(g_pLog, "MarkerName: %s\n", effectName);
            std::fprintf(g_pLog, "MarkerOpcode: %s\n", GetMarkerOpcodeName(markerOpcode));

            std::fprintf(g_pLog, "AuthoredMarkerOccurrences: %d\n", authoredMarkerCount);

            std::fprintf(g_pLog, "AcceptedMarkerOccurrencesBefore: %d\n", acceptedMarkerCountBefore);

            std::fprintf(g_pLog, "AcceptedMarkerOccurrencesAfter: %d\n", acceptedMarkerCountAfter);

            std::fprintf(g_pLog, "ExecutionBudgetReset: %d\n", executionBudgetReset ? 1 : 0);

            std::fprintf(g_pLog, "AuthoredMarkerFrame: %d\n",
                         GetFirstAuthoredMarkerFrame(decision, markerOpcode));
            std::fprintf(g_pLog, "MarkerOwnedSourceMaskBeforeOff: %u\n", ownedMask);
            std::fprintf(g_pLog, "DeactivatedSourceCount: %d\n", deactivatedSourceCount);
            std::fprintf(g_pLog, "SetCollisionGroupAction: %s\n",
                         deactivatedSourceCount > 0 ? "REQUESTED_ITEM_EQUIPPED_FOR_OWNED_SOURCES"
                                                    : "NO_ACTIVE_WEAPON_SOURCE_TO_DEACTIVATE");

            std::fprintf(g_pLog, "TriggeredDamageList: NOT_CLEARED_OFF\n");

            std::fprintf(g_pLog, "Original StartEffect for marker: NOT CALLED\n");

            std::fprintf(g_pLog, "=================================\n\n");

            std::fflush(g_pLog);
        }

        return nullptr;
    }

    unsigned int desiredSourceMask = GetMarkerDesiredSourceMask(markerOpcode);
    eCEntity *selectedSourceInstance = GetSourceInstance(sources, desiredSourceMask);

    // Required-source preflight above guarantees this for a valid source
    // marker. Keep the guard explicit so malformed future opcode changes fail
    // closed without dereferencing a null entity.
    if (selectedSourceInstance == nullptr)
    {
        if (g_pLog != nullptr)
        {
            std::fprintf(g_pLog, "MarkerAction: REJECTED - selected source is missing\n");
            std::fprintf(g_pLog, "=================================\n\n");
            std::fflush(g_pLog);
        }

        return nullptr;
    }

    MarkerOwnedCollisionWindow *previousWindow = FindMatchingMarkerOwnedWindow(
        a_pEntity1, sources, currentAnimation.GetText(), markerAction, markerPhase);
    unsigned int previousSourceMask = previousWindow != nullptr
                                    ? previousWindow->activeSourceMask
                                    : SourceMask_None;
    unsigned int retiredSourceMask = previousSourceMask & ~desiredSourceMask;

    // Publish the exact desired set before retiring an old source. The
    // SetCollisionGroup hook then sees that retirement as intentional and
    // leaves the current execution budget intact.
    RememberMarkerOwnedWindow(a_pEntity1, sources, desiredSourceMask,
                              currentAnimation.GetText(), markerAction, markerPhase);

    unsigned int sourceMasks[2] = { SourceMask_Right, SourceMask_Left };
    GEInt retiredSourceCount = 0;

    for (GEInt i = 0; i < 2; ++i)
    {
        unsigned int sourceMask = sourceMasks[i];

        if ((retiredSourceMask & sourceMask) == 0)
            continue;

        eCEntity *sourceInstance = GetSourceInstance(sources, sourceMask);

        if (sourceInstance == nullptr)
            continue;

        Entity retiredSource(sourceInstance);

        if (!IsFistCollisionSource(retiredSource)
            && retiredSource.GetCollisionGroup() == eECollisionGroup_Item_Attack)
        {
            retiredSource.SetCollisionGroup(eECollisionGroup_Item_Equipped);
            ++retiredSourceCount;
        }
    }

    Entity selectedSource(selectedSourceInstance);
    GEInt beforeGroup = static_cast<GEInt>(selectedSource.GetCollisionGroup());
    GEInt sourceUseType = static_cast<GEInt>(GetCollisionSourceUseType(selectedSource));
    bool skipCollisionGroupForFist = IsFistCollisionSource(selectedSource);

    GEInt quickStatePositionBeforeMarker = -1;

    GEInt quickStatePositionAfterMarker = -1;

    if (isQuickAttackHit)
    {
        quickStatePositionBeforeMarker =
            static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    }

    // v0.9 causal isolation:
    // keep ownership, native suppression, marker timing, source resolution,
    // and triggered-list rearming unchanged. Skip only the weapon-style group
    // request when the resolved raw source is Fist/PhysicalFist.
    if (!skipCollisionGroupForFist)
    {
        selectedSource.SetCollisionGroup(eECollisionGroup_Item_Attack);

        if (selectedSource.GetCollisionGroup() != eECollisionGroup_Item_Attack)
            ForgetMarkerOwnedWindowForActor(a_pEntity1);
    }
    else
    {
        // Fist/body OFF is still deliberately unsupported, so do not publish
        // a marker-owned weapon window for this source.
        ForgetMarkerOwnedWindowForActor(a_pEntity1);
    }

    selectedSource.TouchDamage.ClearTriggeredList();

    // Reference Quick callback implementations use StatePosition as their
    // one-shot collision activation gate and set it to 1 after activating.
    // v0.7 runtime left this gate at 0, after which the original callback
    // reactivated collision following Gothic 3's natural reset. Complete that
    // bookkeeping here when the accepted Quick marker owns activation.
    //
    // Keep the proven Normal path unchanged.
    if (isQuickAttackHit)
    {
        actor.Routine.AccessProperty<PSRoutine::PropertyStatePosition>() = 1;

        quickStatePositionAfterMarker =
            static_cast<GEInt>(actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
    }

    RememberAcceptedMarker(a_pEntity1, sources, currentAnimation.GetText(), effectName,
                           markerAction, markerPhase, markerStateTime, markerElapsedMs);

    GEInt afterGroup = static_cast<GEInt>(selectedSource.GetCollisionGroup());

    if (g_pLog != nullptr)
    {
        std::fprintf(g_pLog, "MarkerAction: ACCEPTED\n");

        std::fprintf(g_pLog, "MarkerName: %s\n", effectName);
        std::fprintf(g_pLog, "MarkerOpcode: %s\n", GetMarkerOpcodeName(markerOpcode));

        std::fprintf(g_pLog, "AuthoredMarkerOccurrences: %d\n", authoredMarkerCount);

        std::fprintf(g_pLog, "AcceptedMarkerOccurrencesBefore: %d\n", acceptedMarkerCountBefore);

        std::fprintf(g_pLog, "AcceptedMarkerOccurrencesAfter: %d\n", acceptedMarkerCountAfter);

        std::fprintf(g_pLog, "ExecutionBudgetReset: %d\n", executionBudgetReset ? 1 : 0);

        std::fprintf(g_pLog, "AuthoredMarkerFrame: %d\n",
                     GetFirstAuthoredMarkerFrame(decision, markerOpcode));

        std::fprintf(g_pLog, "PreviousMarkerOwnedSourceMask: %u\n", previousSourceMask);
        std::fprintf(g_pLog, "DesiredMarkerOwnedSourceMask: %u\n", desiredSourceMask);
        std::fprintf(g_pLog, "RetiredMarkerOwnedSourceMask: %u\n", retiredSourceMask);
        std::fprintf(g_pLog, "RetiredSourceCount: %d\n", retiredSourceCount);

        std::fprintf(g_pLog, "CollisionGroupBeforeMarker: %d\n", beforeGroup);

        std::fprintf(g_pLog, "CollisionGroupAfterMarker: %d\n", afterGroup);

        std::fprintf(g_pLog, "ResolvedSourceUseTypeAtMarker: %d\n", sourceUseType);

        std::fprintf(g_pLog, "SetCollisionGroupAction: %s\n",
                     skipCollisionGroupForFist ? "SKIPPED_FOR_FIST_CAUSAL_TEST"
                                               : "REQUESTED_ITEM_ATTACK");

        std::fprintf(g_pLog, "TriggeredDamageList: CLEARED\n");

        if (isQuickAttackHit)
        {
            std::fprintf(g_pLog, "QuickStatePositionBeforeMarker: %d\n", quickStatePositionBeforeMarker);

            std::fprintf(g_pLog, "QuickStatePositionAfterMarker: %d\n", quickStatePositionAfterMarker);
        }

        std::fprintf(g_pLog, "Original StartEffect for marker: NOT CALLED\n");

        std::fprintf(g_pLog, "=================================\n\n");

        std::fflush(g_pLog);
    }

    return nullptr;
}

// -----------------------------------------------------------------------------
// Install
// -----------------------------------------------------------------------------

static void InstallHooks()
{
    GetScriptAdmin().LoadScriptDLL("Script_Game.dll");

    Hook_OnAI_Attack.Hook(GetScriptAdminExt().GetScriptAICallback("OnAI_Attack")->m_funcScriptAICallback,
                          &OnAI_Attack_FrameCollisionTest);

    Hook_OnAI_QuickAttack.Hook(
        GetScriptAdminExt().GetScriptAICallback("OnAI_QuickAttack")->m_funcScriptAICallback,
        &OnAI_QuickAttack_FrameCollisionTest);

    Hook_StartEffect.Prepare(RVA_Game(0x60850), &StartEffect_FrameCollisionTest, mCBaseHook::mEHookType_ThisCall)
        .Hook();

    Hook_SetCollisionGroup
        .Prepare(RVA_Engine(0x225660), &SetCollisionGroup_FrameCollisionTest, mCBaseHook::mEHookType_ThisCall)
        .Hook();
}

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    OpenLog();

    if (g_pLog != nullptr)
    {
        std::fprintf(g_pLog, "Installing hooks...\n");

        std::fflush(g_pLog);
    }

    InstallHooks();

    if (g_pLog != nullptr)
    {
        std::fprintf(g_pLog, "Hooks installed.\n\n");

        std::fflush(g_pLog);
    }

    return &GetScriptInit();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH: ::DisableThreadLibraryCalls(hModule); break;

        case DLL_PROCESS_DETACH:
            if (g_pLog != nullptr)
            {
                std::fprintf(g_pLog, "Script_FrameCollisionTest unloading.\n");

                std::fflush(g_pLog);
                std::fclose(g_pLog);
                g_pLog = nullptr;
            }
            break;
    }

    return TRUE;
}

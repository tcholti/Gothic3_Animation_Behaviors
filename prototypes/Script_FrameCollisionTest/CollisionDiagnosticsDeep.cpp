#include "CollisionDiagnosticsDeep.h"

#include "CollisionDiagnostics.h"
#include "CollisionSources.h"
#include "RuntimeClock.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>

#include <cstdint>
#include <cstring>
#include <unordered_map>

#include <windows.h>

namespace FrameCollision::CollisionDiagnosticsDeep
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

static std::unordered_map<eCEntity *, LifetimeState> g_LifetimeStateByActor;

static FILE *Log()
{
    return CollisionDiagnostics::GetLog();
}

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
    return a != nullptr && b != nullptr
        && _stricmp(BaseName(a), BaseName(b)) == 0;
}

static bool Contains(char const *text, char const *token)
{
    return text != nullptr && token != nullptr
        && std::strstr(text, token) != nullptr;
}

static bool IsAttackHitMotionName(char const *motionName)
{
    static char const *const tokens[] =
    {
        "_Attack_Hit_", "_PowerAttack_Hit_", "_QuickAttack_Hit_",
        "_SimpleWhirl_Hit_", "_SprintAttack_Hit_", "_WhirlAttack_Hit_",
        "_PierceAttack_Hit_", "_JumpAttack_Hit_", "_RamAttack_Hit_",
        "_HackAttack_Hit_", "_FinishingAttack_Hit_", "_GetUpAttack_Hit_"
    };
    for (char const *token : tokens)
    {
        if (Contains(motionName, token))
            return true;
    }
    return false;
}

static bool TryGetPrimaryMotionLifetimeSnapshot(
    eCVisualAnimation_PS *animationPS,
    PrimaryMotionLifetimeSnapshot &snapshot)
{
    snapshot = {};
    if (animationPS == nullptr || !animationPS->HasActor())
        return false;
    eCWrapper_emfx2Actor *animationActor = animationPS->GetActor();
    if (animationActor == nullptr)
        return false;
    auto const primaryFirst =
        static_cast<eCWrapper_emfx2Actor::eEMotionType>(0);
    snapshot.available = true;
    snapshot.hasMotionInstance =
        animationActor->HasMotionInstance(primaryFirst);
    if (!snapshot.hasMotionInstance)
        return true;
    snapshot.motionRunning = animationActor->IsMotionRunning(primaryFirst);
    snapshot.playTime = animationActor->GetPlayTime(primaryFirst);
    snapshot.maxTime = animationActor->GetMaxTime(primaryFirst);
    snapshot.playSpeed = animationActor->GetPlaySpeed(primaryFirst);
    snapshot.motionName =
        animationPS->GetMotionDesc(primaryFirst).GetMotionFilename().GetText();
    return true;
}

static bool TryGetPrimaryMotionLifetimeSnapshot(
    Entity &actor, PrimaryMotionLifetimeSnapshot &snapshot)
{
    snapshot = {};
    if (actor == None || !actor.Animation.IsValid())
        return false;
    auto *animationPS = static_cast<eCVisualAnimation_PS *>(
        actor.Animation.m_pEngineEntityPropertySet);
    return TryGetPrimaryMotionLifetimeSnapshot(animationPS, snapshot);
}

PrimaryMotionEventSnapshot CapturePrimaryMotionEventSnapshot(
    eCVisualAnimation_PS *animationPS)
{
    PrimaryMotionEventSnapshot result = {};
    result.elapsedMilliseconds = RuntimeClock::GetElapsedMilliseconds();
    TryGetPrimaryMotionLifetimeSnapshot(animationPS, result.primary);
    return result;
}

PrimaryMotionEventSnapshot CapturePrimaryMotionEventSnapshot(Entity &actor)
{
    PrimaryMotionEventSnapshot result = {};
    result.elapsedMilliseconds = RuntimeClock::GetElapsedMilliseconds();
    TryGetPrimaryMotionLifetimeSnapshot(actor, result.primary);
    return result;
}

bool IsAttackHitPrimaryMotion(
    PrimaryMotionEventSnapshot const &snapshot)
{
    return snapshot.primary.available
        && snapshot.primary.hasMotionInstance
        && IsAttackHitMotionName(snapshot.primary.motionName.c_str());
}

static void CaptureSource(
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
    snapshot.elapsedMilliseconds = RuntimeClock::GetElapsedMilliseconds();
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
    EquippedCollisionSources const sources =
        CollisionSources::GetEquippedCollisionSources(actor);
    CaptureSource(sources.leftInstance, snapshot.leftSource);
    CaptureSource(sources.rightInstance, snapshot.rightSource);
}

static void LogSource(
    char const *label, HitReplacementSourceSnapshot const &source)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    std::fprintf(log, "%sSourceResolved: %d\n", label,
                 source.resolved ? 1 : 0);
    std::fprintf(log, "%sSource: %s\n", label,
                 source.resolved ? source.name.c_str() : "<none>");
    std::fprintf(log, "%sSourceAddress: %p\n", label, source.address);
    std::fprintf(log, "%sSourceCollisionGroup: %d\n", label,
                 source.collisionGroup);
}

static void LogStackFrames(
    void *const *frames, unsigned short frameCount)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    std::fprintf(log, "CapturedStackFrameCount: %u\n",
                 static_cast<unsigned int>(frameCount));
    for (unsigned short i = 0; i < frameCount; ++i)
    {
        void *frameAddress = frames[i];
        HMODULE frameModule = nullptr;
        char modulePath[MAX_PATH] = {};
        bool const resolved = frameAddress != nullptr
            && ::GetModuleHandleExA(
                GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
                    | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                reinterpret_cast<LPCSTR>(frameAddress),
                &frameModule) != FALSE;
        DWORD const pathLength = resolved
            ? ::GetModuleFileNameA(frameModule, modulePath, MAX_PATH) : 0;
        std::uintptr_t const frameValue =
            reinterpret_cast<std::uintptr_t>(frameAddress);
        std::uintptr_t const baseValue =
            reinterpret_cast<std::uintptr_t>(frameModule);
        unsigned long const rva = resolved
            ? static_cast<unsigned long>(frameValue - baseValue) : 0;
        if (resolved)
        {
            std::fprintf(log,
                "StackFrame[%u]: Address=%p Module=%s Base=%p RVA=0x%08lX\n",
                static_cast<unsigned int>(i), frameAddress,
                pathLength > 0 ? BaseName(modulePath) : "<path-unavailable>",
                static_cast<void *>(frameModule), rva);
        }
        else
        {
            std::fprintf(log,
                "StackFrame[%u]: Address=%p Module=<unresolved> Base=%p RVA=<unresolved>\n",
                static_cast<unsigned int>(i), frameAddress,
                static_cast<void *>(frameModule));
        }
    }
}

static void LogPrimary(
    char const *stage, PrimaryMotionEventSnapshot const &event)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    PrimaryMotionLifetimeSnapshot const &snapshot = event.primary;
    std::fprintf(log, "Stage: %s\n", stage);
    std::fprintf(log, "ElapsedMs: %.3f\n", event.elapsedMilliseconds);
    std::fprintf(log, "PrimarySnapshotAvailable: %d\n",
                 snapshot.available ? 1 : 0);
    std::fprintf(log, "PrimaryMotionName: %s\n",
                 snapshot.motionName.c_str());
    std::fprintf(log, "PrimaryHasMotionInstance: %d\n",
                 snapshot.hasMotionInstance ? 1 : 0);
    std::fprintf(log, "PrimaryMotionRunning: %d\n",
                 snapshot.motionRunning ? 1 : 0);
    std::fprintf(log, "PrimaryPlayTime: %.6f\n", snapshot.playTime);
    std::fprintf(log, "PrimaryMaxTime: %.6f\n", snapshot.maxTime);
    std::fprintf(log, "PrimaryPlaySpeed: %.6f\n", snapshot.playSpeed);
}

static void LogReplacementContext(
    HitReplacementStackSnapshot const &context)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    std::fprintf(log, "CurrentAction: %d\n", context.action);
    std::fprintf(log, "CurrentAniPhase: %d\n", context.phase);
    std::fprintf(log, "CurrentStateTime: %.6f\n", context.stateTime);
    std::fprintf(log, "CurrentStatePosition: %d\n", context.statePosition);
    std::fprintf(log, "CurrentMovementAni: %s\n",
                 context.movementName.c_str());
    LogSource("LeftHand", context.leftSource);
    LogSource("RightHand", context.rightSource);
    LogStackFrames(context.frames, context.frameCount);
}

void LogHitReplacementStack(
    Entity &actor, HitReplacementStackSnapshot const &replacement,
    PrimaryMotionEventSnapshot const &incoming)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    std::fprintf(log, "===== DEEP HIT REPLACEMENT STACK =====\n");
    std::fprintf(log, "ElapsedMs: %.3f\n", replacement.elapsedMilliseconds);
    std::fprintf(log, "Actor: %s\n",
                 actor != None ? actor.GetName().GetText() : "<unavailable>");
    std::fprintf(log, "OutgoingPrimaryMotionName: %s\n",
                 replacement.outgoingMotionName.c_str());
    std::fprintf(log, "IncomingMotionRequestAddress: %p\n",
                 replacement.incomingRequestAddress);
    std::fprintf(log, "IncomingPrimaryMotionName: %s\n",
                 incoming.primary.motionName.c_str());
    LogReplacementContext(replacement);
    std::fprintf(log, "======================================\n\n");
    std::fflush(log);
}

void LogEmptyPrimarySuccessorStack(
    Entity &actor, HitReplacementStackSnapshot const &request,
    PrimaryMotionEventSnapshot const &successor)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    std::fprintf(log, "===== DEEP EMPTY-PRIMARY SUCCESSOR STACK =====\n");
    std::fprintf(log, "ElapsedMs: %.3f\n", request.elapsedMilliseconds);
    std::fprintf(log, "Actor: %s\n",
                 actor != None ? actor.GetName().GetText() : "<unavailable>");
    std::fprintf(log, "IncomingMotionRequestAddress: %p\n",
                 request.incomingRequestAddress);
    std::fprintf(log, "SuccessorPrimaryMotionName: %s\n",
                 successor.primary.motionName.c_str());
    LogReplacementContext(request);
    std::fprintf(log, "==============================================\n\n");
    std::fflush(log);
}

void LogHitStopStack(
    Entity &actor, HitReplacementStackSnapshot const &stop,
    GEFloat blendTime)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    std::fprintf(log, "===== DEEP HIT STOP STACK =====\n");
    std::fprintf(log, "ElapsedMs: %.3f\n", stop.elapsedMilliseconds);
    std::fprintf(log, "Actor: %s\n",
                 actor != None ? actor.GetName().GetText() : "<unavailable>");
    std::fprintf(log, "OutgoingPrimaryMotionName: %s\n",
                 stop.outgoingMotionName.c_str());
    std::fprintf(log, "StopMotionBlendTime: %.6f\n", blendTime);
    LogReplacementContext(stop);
    std::fprintf(log, "===============================\n\n");
    std::fflush(log);
}

void LogHitStartRecoverBeginStack(
    Entity &actor, HitReplacementStackSnapshot const &startRecover)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    std::fprintf(log, "===== DEEP HIT STARTRECOVER BEGIN STACK =====\n");
    std::fprintf(log, "ElapsedMs: %.3f\n",
                 startRecover.elapsedMilliseconds);
    std::fprintf(log, "Actor: %s\n",
                 actor != None ? actor.GetName().GetText() : "<unavailable>");
    std::fprintf(log, "OutgoingPrimaryMotionName: %s\n",
                 startRecover.outgoingMotionName.c_str());
    LogReplacementContext(startRecover);
    std::fprintf(log, "=============================================\n\n");
    std::fflush(log);
}

void LogCombatMoveFullStopStack(
    Entity &actor, HitReplacementStackSnapshot const &fullStop,
    PrimaryMotionEventSnapshot const &primary)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    std::fprintf(log, "===== DEEP COMBATMOVE FULLSTOP STACK =====\n");
    std::fprintf(log, "ElapsedMs: %.3f\n", fullStop.elapsedMilliseconds);
    std::fprintf(log, "Actor: %s\n",
                 actor != None ? actor.GetName().GetText() : "<unavailable>");
    std::fprintf(log, "InstructionArgsAddress: %p\n",
                 fullStop.incomingRequestAddress);
    LogPrimary("BEFORE_ORIGINAL", primary);
    LogReplacementContext(fullStop);
    std::fprintf(log, "==========================================\n\n");
    std::fflush(log);
}

static void LogCaller(void *callerAddress)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    HMODULE callerModule = nullptr;
    char modulePath[MAX_PATH] = {};
    bool const resolved = callerAddress != nullptr
        && ::GetModuleHandleExA(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
                | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPCSTR>(callerAddress),
            &callerModule) != FALSE;
    DWORD const pathLength = resolved
        ? ::GetModuleFileNameA(callerModule, modulePath, MAX_PATH) : 0;
    std::uintptr_t const callerValue =
        reinterpret_cast<std::uintptr_t>(callerAddress);
    std::uintptr_t const baseValue =
        reinterpret_cast<std::uintptr_t>(callerModule);
    unsigned long const rva = resolved
        ? static_cast<unsigned long>(callerValue - baseValue) : 0;
    std::fprintf(log, "CallerAddress: %p\n", callerAddress);
    std::fprintf(log, "CallerModuleResolved: %d\n", resolved ? 1 : 0);
    std::fprintf(log, "CallerModule: %s\n",
                 pathLength > 0 ? BaseName(modulePath)
                                : resolved ? "<path-unavailable>"
                                           : "<unresolved>");
    if (resolved)
        std::fprintf(log, "CallerRVA: 0x%08lX\n", rva);
    else
        std::fprintf(log, "CallerRVA: <unresolved>\n");
}

void LogAIFullStopCallSite(
    Entity &actor, AIFullStopStackSnapshot const &fullStop)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    std::fprintf(log, "===== DEEP AIFULLSTOP CALLSITE =====\n");
    std::fprintf(log, "ElapsedMs: %.3f\n",
                 fullStop.context.elapsedMilliseconds);
    std::fprintf(log, "Actor: %s\n", actor.GetName().GetText());
    LogCaller(fullStop.callerAddress);
    std::fprintf(log, "CurrentState: %s\n", fullStop.currentState.c_str());
    std::fprintf(log, "PressedKey: %d\n", fullStop.pressedKey);
    std::fprintf(log, "IsPressed: %d\n",
                 fullStop.isPressed == GETrue ? 1 : 0);
    std::fprintf(log, "IsPressedBefore: %d\n",
                 fullStop.isPressedBefore == GETrue ? 1 : 0);
    std::fprintf(log, "DurationPressedMSecs: %u\n",
                 static_cast<unsigned int>(fullStop.durationPressedMSecs));
    LogPrimary("BEFORE_ORIGINAL", fullStop.primary);
    LogReplacementContext(fullStop.context);
    std::fprintf(log, "====================================\n\n");
    std::fflush(log);
}

void LogAISetStateCallSite(
    Entity &actor, AISetStateStackSnapshot const &setState)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    std::fprintf(log, "===== DEEP AISETSTATE CALLSITE =====\n");
    std::fprintf(log, "ElapsedMs: %.3f\n",
                 setState.context.elapsedMilliseconds);
    std::fprintf(log, "Actor: %s\n", actor.GetName().GetText());
    std::fprintf(log, "RequestedState: %s\n",
                 setState.requestedState.c_str());
    std::fprintf(log, "CurrentStateBeforeOriginal: %s\n",
                 setState.currentState.c_str());
    LogCaller(setState.callerAddress);
    LogPrimary("BEFORE_ORIGINAL", setState.primary);
    LogReplacementContext(setState.context);
    std::fprintf(log, "===================================\n\n");
    std::fflush(log);
}

void LogNativeCleanupCallSite(
    eCEntity *changedEntity, eECollisionGroup requestedGroup,
    eECollisionGroup beforeGroup, eECollisionGroup afterGroup,
    void *callerAddress, NativeCleanupStackSnapshot const &stack)
{
    FILE *log = Log();
    if (log == nullptr || changedEntity == nullptr)
        return;
    if (requestedGroup != eECollisionGroup_Item_Equipped
        || beforeGroup != eECollisionGroup_Item_Attack
        || afterGroup != eECollisionGroup_Item_Equipped)
        return;
    std::fprintf(log, "===== DEEP NATIVE CLEANUP CALL SITE =====\n");
    Entity changed(changedEntity);
    std::fprintf(log, "ElapsedMs: %.3f\n",
                 RuntimeClock::GetElapsedMilliseconds());
    std::fprintf(log, "Source: %s\n", changed.GetName().GetText());
    std::fprintf(log, "SourceAddress: %p\n",
                 static_cast<void *>(changedEntity));
    LogCaller(callerAddress);
    LogStackFrames(stack.frames, stack.frameCount);
    std::fprintf(log, "RequestedGroup: %d\n",
                 static_cast<GEInt>(requestedGroup));
    std::fprintf(log, "BeforeGroup: %d\n",
                 static_cast<GEInt>(beforeGroup));
    std::fprintf(log, "AfterGroup: %d\n",
                 static_cast<GEInt>(afterGroup));
    std::fprintf(log, "=========================================\n\n");
    std::fflush(log);
}

OuterFrameSnapshot CaptureOuterFrameSnapshot(
    Entity &actor, gCScriptProcessingUnit *spu)
{
    OuterFrameSnapshot snapshot = {};
    snapshot.elapsedMilliseconds = RuntimeClock::GetElapsedMilliseconds();
    snapshot.spuAddress = spu;
    snapshot.topIndex = -1;
    snapshot.action = -1;
    snapshot.statePosition = -1;
    snapshot.stateTime = -1.0f;
    if (actor != None)
    {
        bCString currentState = actor.Routine.GetCurrentState();
        snapshot.currentState = currentState.GetText() != nullptr
            ? currentState.GetText() : "";
        snapshot.action = static_cast<GEInt>(
            actor.Routine.GetProperty<PSRoutine::PropertyAction>());
        snapshot.statePosition = static_cast<GEInt>(
            actor.Routine.GetProperty<PSRoutine::PropertyStatePosition>());
        snapshot.stateTime = actor.Routine.GetStateTime();
    }
    if (spu == nullptr)
        return snapshot;
    snapshot.stateStackCount =
        static_cast<GEInt>(spu->m_StateStack.GetCount());
    if (snapshot.stateStackCount <= 0)
        return snapshot;
    snapshot.hasTopFrame = true;
    snapshot.topIndex = snapshot.stateStackCount - 1;
    gScriptRunTimeSingleState &top =
        spu->m_StateStack.AccessAt(snapshot.topIndex);
    snapshot.topEntryAddress = static_cast<void *>(&top);
    snapshot.topScriptName = top.m_strScriptName.GetText() != nullptr
        ? top.m_strScriptName.GetText() : "";
    snapshot.topIsScriptState = top.m_bIsScriptState;
    snapshot.topBreakBlock = top.m_iBreakBlock;
    snapshot.topArgumentsAddress = static_cast<void *>(top.m_pArguments);
    snapshot.topLocalCallback = top.m_strLocalCallback.GetText() != nullptr
        ? top.m_strLocalCallback.GetText() : "";
    snapshot.topExtraFloat = top.__FIXME_0014;
    return snapshot;
}

void LogOuterFrameSnapshot(
    char const *eventName, Entity &actor, eCEntity *sourceInstance,
    eECollisionGroup requestedGroup, eECollisionGroup beforeGroup,
    eECollisionGroup afterGroup, OuterFrameSnapshot const &snapshot)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    std::fprintf(log, "===== DEEP %s =====\n", eventName);
    std::fprintf(log, "ElapsedMs: %.3f\n", snapshot.elapsedMilliseconds);
    std::fprintf(log, "ActorAddress: %p\n",
                 actor != None ? static_cast<void *>(actor.GetInstance()) : nullptr);
    std::fprintf(log, "Actor: %s\n",
                 actor != None ? actor.GetName().GetText() : "<unavailable>");
    if (sourceInstance != nullptr)
    {
        std::fprintf(log, "SourceAddress: %p\n",
                     static_cast<void *>(sourceInstance));
        std::fprintf(log, "RequestedGroup: %d\n",
                     static_cast<GEInt>(requestedGroup));
        std::fprintf(log, "BeforeGroup: %d\n",
                     static_cast<GEInt>(beforeGroup));
        std::fprintf(log, "AfterGroup: %d\n",
                     static_cast<GEInt>(afterGroup));
    }
    std::fprintf(log, "SPUAddress: %p\n",
                 static_cast<void *>(snapshot.spuAddress));
    std::fprintf(log, "StateStackCount: %d\n", snapshot.stateStackCount);
    std::fprintf(log, "HasTopFrame: %d\n", snapshot.hasTopFrame ? 1 : 0);
    if (snapshot.hasTopFrame)
    {
        std::fprintf(log, "TopIndex: %d\n", snapshot.topIndex);
        std::fprintf(log, "TopEntryAddress: %p\n", snapshot.topEntryAddress);
        std::fprintf(log, "TopScriptName: %s\n",
                     snapshot.topScriptName.c_str());
        std::fprintf(log, "TopIsScriptState: %d\n",
                     snapshot.topIsScriptState == GETrue ? 1 : 0);
        std::fprintf(log, "TopBreakBlock: %u\n",
                     static_cast<unsigned int>(snapshot.topBreakBlock));
        std::fprintf(log, "TopArgumentsAddress: %p\n",
                     snapshot.topArgumentsAddress);
        std::fprintf(log, "TopLocalCallback: %s\n",
                     snapshot.topLocalCallback.c_str());
        std::fprintf(log, "TopExtraFloat: %.6f\n", snapshot.topExtraFloat);
    }
    std::fprintf(log, "CurrentState: %s\n", snapshot.currentState.c_str());
    std::fprintf(log, "CurrentAction: %d\n", snapshot.action);
    std::fprintf(log, "CurrentStatePosition: %d\n", snapshot.statePosition);
    std::fprintf(log, "CurrentStateTime: %.6f\n", snapshot.stateTime);
    std::fprintf(log, "===========================\n\n");
    std::fflush(log);
}

void LogRunScriptFunctionOffenseScope(
    Entity &actor, eCEntity *sourceInstance,
    RunScriptFunctionScopeIdentity const &scope,
    gCScriptProcessingUnit *playerSPU, void *playerStateStackAddress,
    bool spuMatchesPlayer, bool runtimeStackMatchesPlayer,
    bool offenseObservedSet)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    GELPCChar scriptName = scope.scriptName != nullptr
        ? scope.scriptName->GetText() : nullptr;
    std::fprintf(log, "===== DEEP C1 OFFENSE SCOPE =====\n");
    std::fprintf(log, "ElapsedMs: %.3f\n",
                 RuntimeClock::GetElapsedMilliseconds());
    std::fprintf(log, "ActorAddress: %p\n",
                 actor != None ? static_cast<void *>(actor.GetInstance()) : nullptr);
    std::fprintf(log, "SourceAddress: %p\n",
                 static_cast<void *>(sourceInstance));
    std::fprintf(log, "ScopeAddress: %p\n", scope.scopeAddress);
    std::fprintf(log, "ScopeSPUAddress: %p\n",
                 static_cast<void *>(scope.spu));
    std::fprintf(log, "PlayerSPUAddress: %p\n",
                 static_cast<void *>(playerSPU));
    std::fprintf(log, "SPUMatchesPlayer: %d\n", spuMatchesPlayer ? 1 : 0);
    std::fprintf(log, "ScopeRuntimeStackAddress: %p\n",
                 scope.runtimeStackAddress);
    std::fprintf(log, "PlayerStateStackAddress: %p\n",
                 playerStateStackAddress);
    std::fprintf(log, "RuntimeStackMatchesPlayerStateStack: %d\n",
                 runtimeStackMatchesPlayer ? 1 : 0);
    std::fprintf(log, "ScriptFunctionName: %s\n",
                 scriptName != nullptr ? scriptName : "<no-current-scope>");
    std::fprintf(log, "ParentScopeExists: %d\n",
                 scope.parentScopeExists ? 1 : 0);
    std::fprintf(log, "OffenseObservedSet: %d\n",
                 offenseObservedSet ? 1 : 0);
    std::fprintf(log, "=================================\n\n");
    std::fflush(log);
}

static void LogCombatMoveSource(char const *label, eCEntity *sourceInstance)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    std::fprintf(log, "%sSourceResolved: %d\n", label,
                 sourceInstance != nullptr ? 1 : 0);
    if (sourceInstance == nullptr)
        return;
    Entity source(sourceInstance);
    std::fprintf(log, "%sSource: %s\n", label, source.GetName().GetText());
    std::fprintf(log, "%sSourceAddress: %p\n", label,
                 static_cast<void *>(sourceInstance));
    std::fprintf(log, "%sSourceCollisionGroup: %d\n", label,
                 static_cast<GEInt>(source.GetCollisionGroup()));
}

void LogCombatMoveStartRecoverBoundary(
    Entity &actor, char const *boundary)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    PrimaryMotionEventSnapshot snapshot =
        CapturePrimaryMotionEventSnapshot(actor);
    EquippedCollisionSources const sources =
        CollisionSources::GetEquippedCollisionSources(actor);
    bCString currentMovementAni = actor.NPC.GetCurrentMovementAni();
    std::fprintf(log, "===== DEEP COMBATMOVE STARTRECOVER %s =====\n", boundary);
    std::fprintf(log, "Actor: %s\n", actor.GetName().GetText());
    std::fprintf(log, "CurrentAction: %d\n",
                 static_cast<GEInt>(
                     actor.Routine.GetProperty<PSRoutine::PropertyAction>()));
    std::fprintf(log, "CurrentAniPhase: %d\n",
                 static_cast<GEInt>(actor.GetCurrentAniPhase()));
    std::fprintf(log, "CurrentMovementAni: %s\n",
                 currentMovementAni.GetText());
    LogPrimary(boundary, snapshot);
    LogCombatMoveSource("LeftHand", sources.leftInstance);
    LogCombatMoveSource("RightHand", sources.rightInstance);
    std::fprintf(log, "============================================\n\n");
    std::fflush(log);
}

void LogPrimaryMotionEvent(
    eCVisualAnimation_PS *animationPS, char const *operation,
    PrimaryMotionEventSnapshot const &before,
    PrimaryMotionEventSnapshot const &after)
{
    FILE *log = Log();
    if (log == nullptr)
        return;
    eCEntity *owner = animationPS != nullptr ? animationPS->GetEntity() : nullptr;
    std::fprintf(log, "===== DEEP PRIMARYFIRST %s =====\n", operation);
    std::fprintf(log, "OwnerEntityAddress: %p\n", static_cast<void *>(owner));
    LogPrimary("REQUEST_BEFORE_ORIGINAL", before);
    LogPrimary("RESULT_AFTER_ORIGINAL", after);
    std::fprintf(log, "==================================\n\n");
    std::fflush(log);
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

void ObserveMarkerOwnedLifetimeOnTick(
    Entity &actor, MarkerOwnedWindowView const &window)
{
    if (actor == None)
        return;
    eCEntity *actorInstance = actor.GetInstance();
    LifetimeState &state = g_LifetimeStateByActor[actorInstance];
    bCString currentMovementAni = actor.NPC.GetCurrentMovementAni();
    GEInt currentAction = static_cast<GEInt>(
        actor.Routine.GetProperty<PSRoutine::PropertyAction>());
    GEInt currentPhase = static_cast<GEInt>(actor.GetCurrentAniPhase());
    PrimaryMotionLifetimeSnapshot snapshot = {};
    bool const snapshotAvailable =
        TryGetPrimaryMotionLifetimeSnapshot(actor, snapshot);
    bool const firstSnapshot = !state.initialized;
    bool const movementChanged = !firstSnapshot
        && !SameFileName(state.lastObservedMovementAni.c_str(),
                         currentMovementAni.GetText());
    bool const actionChanged = !firstSnapshot
        && state.lastObservedAction != currentAction;
    bool const phaseChanged = !firstSnapshot
        && state.lastObservedPhase != currentPhase;
    bool const instanceChanged = !firstSnapshot
        && state.lastHasPrimaryMotionInstance != snapshot.hasMotionInstance;
    bool const runningChanged = !firstSnapshot
        && state.lastPrimaryMotionRunning != snapshot.motionRunning;
    bool const primaryNameChanged = !firstSnapshot
        && !SameFileName(state.lastPrimaryMotionName.c_str(),
                         snapshot.motionName.c_str());
    bool const playTimeRolledBack = !firstSnapshot
        && snapshot.hasMotionInstance
        && state.lastHasPrimaryMotionInstance
        && snapshot.playTime + 0.000001 < state.lastPrimaryPlayTime;
    bool const atMotionEnd = snapshot.hasMotionInstance
        && snapshot.maxTime > 0.0
        && snapshot.playTime + 0.001 >= snapshot.maxTime;
    bool const previouslyAtMotionEnd = !firstSnapshot
        && state.lastHasPrimaryMotionInstance
        && state.lastPrimaryMaxTime > 0.0
        && state.lastPrimaryPlayTime + 0.001 >= state.lastPrimaryMaxTime;
    bool const crossedMotionEnd = atMotionEnd && !previouslyAtMotionEnd;
    bool const logTransition = firstSnapshot || movementChanged || actionChanged
        || phaseChanged || instanceChanged || runningChanged
        || primaryNameChanged || playTimeRolledBack || crossedMotionEnd;

    FILE *log = Log();
    if (logTransition && log != nullptr)
    {
        std::fprintf(log, "===== DEEP MARKER-OWNED PRIMARY MOTION LIFETIME =====\n");
        std::fprintf(log, "ElapsedMs: %.3f\n",
                     RuntimeClock::GetElapsedMilliseconds());
        std::fprintf(log, "Actor: %s\n", actor.GetName().GetText());
        std::fprintf(log, "OwnedAnimation: %s\n", window.animationName.c_str());
        std::fprintf(log, "OwnedAction: %d\n", window.action);
        std::fprintf(log, "OwnedPhase: %d\n", window.phase);
        std::fprintf(log, "ActiveSourceMask: %u\n", window.activeSourceMask);
        std::fprintf(log, "CurrentMovementAni: %s\n",
                     currentMovementAni.GetText());
        std::fprintf(log, "CurrentAction: %d\n", currentAction);
        std::fprintf(log, "CurrentAniPhase: %d\n", currentPhase);
        std::fprintf(log, "PrimarySnapshotAvailable: %d\n",
                     snapshotAvailable ? 1 : 0);
        std::fprintf(log, "PrimaryHasMotionInstance: %d\n",
                     snapshot.hasMotionInstance ? 1 : 0);
        std::fprintf(log, "PrimaryMotionRunning: %d\n",
                     snapshot.motionRunning ? 1 : 0);
        std::fprintf(log, "PrimaryMotionName: %s\n",
                     snapshot.motionName.c_str());
        std::fprintf(log, "PrimaryPlayTime: %.6f\n", snapshot.playTime);
        std::fprintf(log, "PrimaryMaxTime: %.6f\n", snapshot.maxTime);
        std::fprintf(log, "PrimaryPlaySpeed: %.6f\n", snapshot.playSpeed);
        std::fprintf(log, "MovementChanged: %d\n", movementChanged ? 1 : 0);
        std::fprintf(log, "ActionChanged: %d\n", actionChanged ? 1 : 0);
        std::fprintf(log, "PhaseChanged: %d\n", phaseChanged ? 1 : 0);
        std::fprintf(log, "PrimaryInstanceChanged: %d\n", instanceChanged ? 1 : 0);
        std::fprintf(log, "PrimaryRunningChanged: %d\n", runningChanged ? 1 : 0);
        std::fprintf(log, "PrimaryNameChanged: %d\n", primaryNameChanged ? 1 : 0);
        std::fprintf(log, "PrimaryPlayTimeRolledBack: %d\n",
                     playTimeRolledBack ? 1 : 0);
        std::fprintf(log, "PrimaryCrossedMotionEnd: %d\n",
                     crossedMotionEnd ? 1 : 0);
        std::fprintf(log, "===================================================\n\n");
        std::fflush(log);
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

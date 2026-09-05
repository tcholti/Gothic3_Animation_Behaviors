#include "EngineBridge.h"

#include "CollisionLifecycleGuard.h"
#include "CollisionSources.h"
#include "FrameCollisionMarkers.h"
#include "RuntimeClock.h"

#ifdef FRAME_COLLISION_DIAGNOSTICS
#include "CollisionDiagnostics.h"
#endif
#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
#include "CollisionDiagnosticsDeep.h"
#endif

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>
#endif
#include <g3sdk/Engine/animation/ge_animationadmin.h>
#include <g3sdk/Game/ge_effectsystem.h>
#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Memory.h>
#include <g3sdk/util/ScriptUtil.h>

#include <string>

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
#include <cstdio>
#include <intrin.h>
#include <windows.h>
#pragma intrinsic(_ReturnAddress)
#endif

using namespace FrameCollision;

// Sole owner of every Gothic 3 hook used by this DLL. Diagnostic-only hooks
// do not exist in the behavior-only translation unit after preprocessing.
static mCFunctionHook Hook_StartEffect;
static mCFunctionHook Hook_OnAI_Attack;
static mCFunctionHook Hook_OnAI_PowerAttack;
static mCFunctionHook Hook_OnAI_QuickAttack;
static mCFunctionHook Hook_OnAI_SimpleWhirl;
static mCFunctionHook Hook_OnAI_WhirlAttack;
static mCFunctionHook Hook_OnAI_PierceAttack;
static mCFunctionHook Hook_OnAI_HackAttack;
static mCCallHook Hook_CombatMoveMotionResourceQuery;
static mCFunctionHook Hook_SetCollisionGroup;
static mCFunctionHook Hook_AICombatMoveInstr;
static mCFunctionHook Hook_AISetState;
static mCFunctionHook Hook_RunScriptFunction;

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
static mCFunctionHook Hook_OnTick;
static mCFunctionHook Hook_PlayMotion;
static mCFunctionHook Hook_StopMotion;
static mCFunctionHook Hook_AICombatMoveStartRecover;
static mCFunctionHook Hook_AIFullStop;
#endif

struct RunScriptFunctionScope
{
    RunScriptFunctionScope *previous;
    gCScriptProcessingUnit *spu;
    bTObjStack<gScriptRunTimeSingleState> *runtimeStack;
    bCString const *scriptName;
    CollisionLifecycleGuard::PreCombatBridgeToken preCombatBridge;
#ifdef FRAME_COLLISION_DIAGNOSTICS
    bool offenseObserved;
#endif
};

static thread_local RunScriptFunctionScope *g_pCurrentRunScriptFunctionScope = nullptr;

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
static CollisionDiagnosticsDeep::RunScriptFunctionScopeIdentity
GetRunScriptFunctionScopeIdentity(RunScriptFunctionScope *scope)
{
    CollisionDiagnosticsDeep::RunScriptFunctionScopeIdentity identity = {};
    if (scope == nullptr)
        return identity;
    identity.scopeAddress = static_cast<void *>(scope);
    identity.spu = scope->spu;
    identity.runtimeStackAddress = static_cast<void *>(scope->runtimeStack);
    identity.scriptName = scope->scriptName;
    identity.parentScopeExists = scope->previous != nullptr;
    return identity;
}
#endif

static bool IsPlayerEntity(eCEntity *instance)
{
    Entity player = Entity::GetPlayer();
    return player != None && instance == player.GetInstance();
}

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
static gCScriptProcessingUnit *GetActorSPU(Entity &actor)
{
    if (actor == None)
        return nullptr;
    gCScriptRoutine_PS *routinePS = static_cast<gCScriptRoutine_PS *>(
        actor.Routine.m_pEngineEntityPropertySet);
    return routinePS != nullptr ? &routinePS->GetSPU() : nullptr;
}
#endif

static bool EvaluateAttackCallback(Entity &actor, AttackFamily family)
{
    FrameCollisionMarkers::AttackCallbackOwnershipResult const ownership =
        FrameCollisionMarkers::EvaluateAttackCallbackOwnership(actor, family);
#ifdef FRAME_COLLISION_DIAGNOSTICS
    CollisionDiagnostics::LogAttackCallbackOwnership(actor, family, ownership);
#endif
    return ownership.suppressNativeCallback;
}

DECLARE_SCRIPT_CALLBACK(OnAI_Attack_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()
    if (EvaluateAttackCallback(SelfEntity, AttackFamily_Normal))
        return GETrue;
#ifdef FRAME_COLLISION_DIAGNOSTICS
    CollisionDiagnostics::LogFistTriggerStateSnapshot(
        "NATIVE_ATTACK_BEFORE_ORIGINAL", SelfEntity);
    GEBool const result = Hook_OnAI_Attack.GetOriginalFunction(
        &OnAI_Attack_FrameCollisionTest)(a_pSPU);
    CollisionDiagnostics::LogFistTriggerStateSnapshot(
        "NATIVE_ATTACK_AFTER_ORIGINAL", SelfEntity);
    return result;
#else
    return Hook_OnAI_Attack.GetOriginalFunction(&OnAI_Attack_FrameCollisionTest)(a_pSPU);
#endif
}

DECLARE_SCRIPT_CALLBACK(OnAI_PowerAttack_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()
    if (EvaluateAttackCallback(SelfEntity, AttackFamily_Power))
        return GETrue;
    return Hook_OnAI_PowerAttack.GetOriginalFunction(
        &OnAI_PowerAttack_FrameCollisionTest)(a_pSPU);
}

DECLARE_SCRIPT_CALLBACK(OnAI_QuickAttack_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()
    if (EvaluateAttackCallback(SelfEntity, AttackFamily_Quick))
        return GETrue;
    return Hook_OnAI_QuickAttack.GetOriginalFunction(&OnAI_QuickAttack_FrameCollisionTest)(a_pSPU);
}

DECLARE_SCRIPT_CALLBACK(OnAI_SimpleWhirl_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()
    if (EvaluateAttackCallback(SelfEntity, AttackFamily_SimpleWhirl))
        return GETrue;
    return Hook_OnAI_SimpleWhirl.GetOriginalFunction(
        &OnAI_SimpleWhirl_FrameCollisionTest)(a_pSPU);
}

DECLARE_SCRIPT_CALLBACK(OnAI_WhirlAttack_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()
    if (EvaluateAttackCallback(SelfEntity, AttackFamily_Whirl))
        return GETrue;
    return Hook_OnAI_WhirlAttack.GetOriginalFunction(&OnAI_WhirlAttack_FrameCollisionTest)(a_pSPU);
}

DECLARE_SCRIPT_CALLBACK(OnAI_PierceAttack_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()
    if (EvaluateAttackCallback(SelfEntity, AttackFamily_Pierce))
        return GETrue;
    return Hook_OnAI_PierceAttack.GetOriginalFunction(
        &OnAI_PierceAttack_FrameCollisionTest)(a_pSPU);
}

DECLARE_SCRIPT_CALLBACK(OnAI_HackAttack_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()
    if (EvaluateAttackCallback(SelfEntity, AttackFamily_Hack))
        return GETrue;
    return Hook_OnAI_HackAttack.GetOriginalFunction(
        &OnAI_HackAttack_FrameCollisionTest)(a_pSPU);
}

static gEAction GetCombatMoveFactualAction(
    gCScriptProcessingUnit const *a_pSPU)
{
    if (a_pSPU == nullptr)
        return gEAction_None;
    // Tested sAICombatMoveInstr layout: the factual action used by this path
    // is stored directly at SPU + 0x154.
    GEU8 const *const bytes = reinterpret_cast<GEU8 const *>(a_pSPU);
    return *reinterpret_cast<gEAction const *>(bytes + 0x154);
}

static eCResourceDataEntity *GE_STDCALL
QueryCombatMoveMotionResource_FrameCollisionTest(
    gCScriptProcessingUnit *a_pSPU, eCAnimationAdmin *a_pAnimationAdmin,
    bCString const &a_ResourceName,
    eEResourceCacheBehavior a_CacheBehavior)
{
    char const *const resourceName = a_ResourceName.GetText();
    if (GetCombatMoveFactualAction(a_pSPU) == gEAction_HackAttack
        && resourceName != nullptr)
    {
        static char const FinishingToken[] = "_FinishingAttack_";
        static char const HackToken[] = "_HackAttack_";
        std::string candidate(resourceName);
        std::string::size_type const actionToken =
            candidate.find(FinishingToken);
        if (actionToken != std::string::npos)
        {
            candidate.replace(actionToken, sizeof(FinishingToken) - 1,
                              HackToken);
            bCString const candidateName(candidate.c_str());
            eCResourceDataEntity *const candidateResource =
                a_pAnimationAdmin->QueryMotionDataEntity(
                    candidateName, a_CacheBehavior);
            if (candidateResource != nullptr)
                return candidateResource;
        }
    }

    return a_pAnimationAdmin->QueryMotionDataEntity(
        a_ResourceName, a_CacheBehavior);
}

static GELPVoid StartEffect_FrameCollisionTest(
    bCString const &a_EffectName, eCEntity *a_pEntity1, eCEntity *a_pEntity2,
    bCMatrix const *a_pMatrix, GEBool a_bUnknown)
{
    GELPCChar const effectName = a_EffectName.GetText();
    MarkerOpcode const markerOpcode =
        FrameCollisionMarkers::GetMarkerOpcode(effectName);
    if (markerOpcode == MarkerOpcode_Invalid)
    {
        return Hook_StartEffect.GetOriginalFunction(&StartEffect_FrameCollisionTest)(
            a_EffectName, a_pEntity1, a_pEntity2, a_pMatrix, a_bUnknown);
    }

    // Reserved markers are consumed even when malformed so Gothic never tries
    // to resolve them as real effect resources.
    if (a_pEntity1 == nullptr)
    {
#ifdef FRAME_COLLISION_DIAGNOSTICS
        CollisionDiagnostics::LogNullMarker(effectName);
#endif
        return nullptr;
    }

    Entity actor(a_pEntity1);
#ifdef FRAME_COLLISION_DIAGNOSTICS
    CollisionDiagnostics::LogMarkerContext(actor, markerOpcode);
#endif

    MarkerProcessResult const result = FrameCollisionMarkers::ProcessMarker(
        actor, markerOpcode, effectName,
        RuntimeClock::GetElapsedMilliseconds());

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
    if (result.code == MarkerResult_Accepted)
    {
        if (result.markerOwnedWeaponMask != SourceMask_None)
            CollisionDiagnosticsDeep::ResetMarkerOwnedLifetime(a_pEntity1);
        else
            CollisionDiagnosticsDeep::ForgetMarkerOwnedLifetime(a_pEntity1);
    }
    else if ((result.code == MarkerResult_OffAccepted
              || result.code == MarkerResult_OffNoWindow)
             && result.markerOwnedWindowRemoved)
    {
        CollisionDiagnosticsDeep::ForgetMarkerOwnedLifetime(a_pEntity1);
    }
#endif
#ifdef FRAME_COLLISION_DIAGNOSTICS
    CollisionDiagnostics::LogMarkerResult(actor, result);
#endif
    return nullptr;
}

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
static bool DidPrimaryFirstReplace(
    CollisionDiagnosticsDeep::PrimaryMotionEventSnapshot const &before,
    CollisionDiagnosticsDeep::PrimaryMotionEventSnapshot const &after)
{
    if (!before.primary.hasMotionInstance
        || !after.primary.available
        || !after.primary.hasMotionInstance)
        return false;
    if (before.primary.motionName != after.primary.motionName)
        return true;
    return after.primary.playTime + 0.0001 < before.primary.playTime;
}

static void GE_STDCALL PlayMotion_FrameCollisionTest(
    eCWrapper_emfx2Actor::eEMotionType a_MotionType,
    eCWrapper_emfx2Motion::eSMotionDesc *a_pMotionDesc)
{
    if (static_cast<GEInt>(a_MotionType) != 0)
    {
        Hook_PlayMotion.GetOriginalFunction(&PlayMotion_FrameCollisionTest)(
            a_MotionType, a_pMotionDesc);
        return;
    }

    eCVisualAnimation_PS *pThis =
        Hook_PlayMotion.GetSelf<eCVisualAnimation_PS *>();
    eCEntity *ownerEntity = pThis != nullptr ? pThis->GetEntity() : nullptr;
    if (!IsPlayerEntity(ownerEntity))
    {
        Hook_PlayMotion.GetOriginalFunction(&PlayMotion_FrameCollisionTest)(
            a_MotionType, a_pMotionDesc);
        return;
    }

    CollisionDiagnosticsDeep::PrimaryMotionEventSnapshot const before =
        CollisionDiagnosticsDeep::CapturePrimaryMotionEventSnapshot(pThis);
    Entity actor(ownerEntity);
    bool const outgoingAttackHit =
        CollisionDiagnosticsDeep::IsAttackHitPrimaryMotion(before);
    CollisionDiagnosticsDeep::HitReplacementStackSnapshot replacement = {};
    if (outgoingAttackHit)
    {
        replacement.outgoingMotionName = before.primary.motionName;
        replacement.frameCount = ::CaptureStackBackTrace(
            0, CollisionDiagnosticsDeep::NativeCleanupStackCapacity,
            replacement.frames, nullptr);
        CollisionDiagnosticsDeep::CaptureHitReplacementContext(
            actor, static_cast<void *>(a_pMotionDesc), replacement);
    }

    bool const emptyPrimaryContext =
        before.primary.available && !before.primary.hasMotionInstance;
    CollisionDiagnosticsDeep::HitReplacementStackSnapshot emptyPrimary = {};
    if (emptyPrimaryContext)
    {
        emptyPrimary.frameCount = ::CaptureStackBackTrace(
            0, CollisionDiagnosticsDeep::NativeCleanupStackCapacity,
            emptyPrimary.frames, nullptr);
        CollisionDiagnosticsDeep::CaptureHitReplacementContext(
            actor, static_cast<void *>(a_pMotionDesc), emptyPrimary);
    }

    Hook_PlayMotion.GetOriginalFunction(&PlayMotion_FrameCollisionTest)(
        a_MotionType, a_pMotionDesc);

    CollisionDiagnosticsDeep::PrimaryMotionEventSnapshot const after =
        CollisionDiagnosticsDeep::CapturePrimaryMotionEventSnapshot(pThis);
    if (outgoingAttackHit && DidPrimaryFirstReplace(before, after))
        CollisionDiagnosticsDeep::LogHitReplacementStack(
            actor, replacement, after);
    if (emptyPrimaryContext && after.primary.available
        && after.primary.hasMotionInstance)
    {
        CollisionDiagnosticsDeep::LogEmptyPrimarySuccessorStack(
            actor, emptyPrimary, after);
    }
    CollisionDiagnosticsDeep::LogPrimaryMotionEvent(
        pThis, "PlayMotion", before, after);
}

static void GE_STDCALL StopMotion_FrameCollisionTest(
    eCWrapper_emfx2Actor::eEMotionType a_MotionType, GEFloat a_fBlendTime)
{
    if (static_cast<GEInt>(a_MotionType) != 0)
    {
        Hook_StopMotion.GetOriginalFunction(&StopMotion_FrameCollisionTest)(
            a_MotionType, a_fBlendTime);
        return;
    }

    eCVisualAnimation_PS *pThis =
        Hook_StopMotion.GetSelf<eCVisualAnimation_PS *>();
    eCEntity *ownerEntity = pThis != nullptr ? pThis->GetEntity() : nullptr;
    if (!IsPlayerEntity(ownerEntity))
    {
        Hook_StopMotion.GetOriginalFunction(&StopMotion_FrameCollisionTest)(
            a_MotionType, a_fBlendTime);
        return;
    }

    CollisionDiagnosticsDeep::PrimaryMotionEventSnapshot const before =
        CollisionDiagnosticsDeep::CapturePrimaryMotionEventSnapshot(pThis);
    Entity actor(ownerEntity);
    if (CollisionDiagnosticsDeep::IsAttackHitPrimaryMotion(before))
    {
        CollisionDiagnosticsDeep::HitReplacementStackSnapshot stop = {};
        stop.outgoingMotionName = before.primary.motionName;
        stop.frameCount = ::CaptureStackBackTrace(
            0, CollisionDiagnosticsDeep::NativeCleanupStackCapacity,
            stop.frames, nullptr);
        CollisionDiagnosticsDeep::CaptureHitReplacementContext(
            actor, nullptr, stop);
        CollisionDiagnosticsDeep::LogHitStopStack(actor, stop, a_fBlendTime);
    }

    Hook_StopMotion.GetOriginalFunction(&StopMotion_FrameCollisionTest)(
        a_MotionType, a_fBlendTime);
    CollisionDiagnosticsDeep::PrimaryMotionEventSnapshot const after =
        CollisionDiagnosticsDeep::CapturePrimaryMotionEventSnapshot(pThis);
    CollisionDiagnosticsDeep::LogPrimaryMotionEvent(
        pThis, "StopMotion", before, after);
}

static void GE_STDCALL AICombatMoveStartRecover_FrameCollisionTest(
    gCScriptProcessingUnit *a_pSPU)
{
    Entity actor;
    if (a_pSPU != nullptr)
        actor.AttachTo(a_pSPU->GetSelfEntity());
    bool const shouldLog = actor != None && IsPlayerEntity(actor.GetInstance());

    if (shouldLog)
    {
        CollisionDiagnosticsDeep::LogCombatMoveStartRecoverBoundary(
            actor, "BEGIN");
        CollisionDiagnosticsDeep::PrimaryMotionEventSnapshot const begin =
            CollisionDiagnosticsDeep::CapturePrimaryMotionEventSnapshot(actor);
        if (CollisionDiagnosticsDeep::IsAttackHitPrimaryMotion(begin))
        {
            CollisionDiagnosticsDeep::HitReplacementStackSnapshot stack = {};
            stack.outgoingMotionName = begin.primary.motionName;
            stack.frameCount = ::CaptureStackBackTrace(
                0, CollisionDiagnosticsDeep::NativeCleanupStackCapacity,
                stack.frames, nullptr);
            CollisionDiagnosticsDeep::CaptureHitReplacementContext(
                actor, nullptr, stack);
            CollisionDiagnosticsDeep::LogHitStartRecoverBeginStack(
                actor, stack);
        }
    }

    Hook_AICombatMoveStartRecover.GetOriginalFunction(
        &AICombatMoveStartRecover_FrameCollisionTest)(a_pSPU);

    if (shouldLog)
        CollisionDiagnosticsDeep::LogCombatMoveStartRecoverBoundary(
            actor, "END");
}
#endif

static GEBool GE_STDCALL RunScriptFunction_FrameCollisionTest(
    gCScriptAdmin *a_pThis, bCString const &a_ScriptName,
    bTObjStack<gScriptRunTimeSingleState> &a_rRunTimeStack,
    gCScriptProcessingUnit *a_pSPU)
{
    RunScriptFunctionScope scope = {};
    scope.previous = g_pCurrentRunScriptFunctionScope;
    scope.spu = a_pSPU;
    scope.runtimeStack = &a_rRunTimeStack;
    scope.scriptName = &a_ScriptName;
    g_pCurrentRunScriptFunctionScope = &scope;

    GEBool const result = Hook_RunScriptFunction.GetOriginalFunction(
        &RunScriptFunction_FrameCollisionTest)(
            a_pThis, a_ScriptName, a_rRunTimeStack, a_pSPU);

    g_pCurrentRunScriptFunctionScope = scope.previous;

    if (scope.preCombatBridge.active)
    {
        CollisionLifecycleGuard::BridgeRetirementResult const retirement =
            CollisionLifecycleGuard::RetirePreCombatBridgeAfterDispatch(
                scope.preCombatBridge);
#ifdef FRAME_COLLISION_DIAGNOSTICS
        CollisionDiagnostics::LogBridgeRetirementResult(retirement);
#endif
    }

#ifdef FRAME_COLLISION_DIAGNOSTICS
    if (scope.offenseObserved)
    {
        CollisionDiagnostics::LogRunScriptFunctionScopeReturn(
            static_cast<void *>(&scope), scope.previous != nullptr, result);
    }
#endif
    return result;
}

static GEBool GE_STDCALL AICombatMoveInstr_FrameCollisionTest(
    GELPVoid a_pArgs, gCScriptProcessingUnit *a_pSPU, GEBool a_bFullStop)
{
    CollisionLifecycleGuard::GenerationToken generation = {};
    if (a_bFullStop != GETrue && a_pArgs != nullptr && a_pSPU != nullptr)
    {
        Entity actor;
        actor.AttachTo(a_pSPU->GetSelfEntity());
        if (actor != None)
        {
            EquippedCollisionSources const sources =
                CollisionSources::GetEquippedCollisionSources(actor);
            CollisionLifecycleGuard::BeginCombatMoveResult const begin =
                CollisionLifecycleGuard::BeginCombatMove(
                    actor, sources, a_pSPU,
                    g_pCurrentRunScriptFunctionScope != nullptr
                        ? &g_pCurrentRunScriptFunctionScope->preCombatBridge
                        : nullptr);
            generation = begin.token;
#ifdef FRAME_COLLISION_DIAGNOSTICS
            CollisionDiagnostics::LogBeginCombatMoveResult(begin);
#endif
#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
            CollisionDiagnosticsDeep::OuterFrameSnapshot const outerFrame =
                CollisionDiagnosticsDeep::CaptureOuterFrameSnapshot(
                    actor, a_pSPU);
            CollisionDiagnosticsDeep::LogOuterFrameSnapshot(
                "DEEP OUTER_FRAME COMBAT_MOVE_INITIAL", actor, nullptr,
                static_cast<eECollisionGroup>(-1),
                static_cast<eECollisionGroup>(-1),
                static_cast<eECollisionGroup>(-1), outerFrame);
#endif
        }
    }

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
    if (a_bFullStop == GETrue && a_pSPU != nullptr)
    {
        Entity actor;
        actor.AttachTo(a_pSPU->GetSelfEntity());
        if (actor != None && IsPlayerEntity(actor.GetInstance()))
        {
            CollisionDiagnosticsDeep::HitReplacementStackSnapshot fullStop = {};
            fullStop.frameCount = ::CaptureStackBackTrace(
                0, CollisionDiagnosticsDeep::NativeCleanupStackCapacity,
                fullStop.frames, nullptr);
            CollisionDiagnosticsDeep::CaptureHitReplacementContext(
                actor, a_pArgs, fullStop);
            CollisionDiagnosticsDeep::PrimaryMotionEventSnapshot const primary =
                CollisionDiagnosticsDeep::CapturePrimaryMotionEventSnapshot(actor);
            CollisionDiagnosticsDeep::LogCombatMoveFullStopStack(
                actor, fullStop, primary);
        }
    }
#endif

    GEBool const result = Hook_AICombatMoveInstr.GetOriginalFunction(
        &AICombatMoveInstr_FrameCollisionTest)(a_pArgs, a_pSPU, a_bFullStop);
    CollisionLifecycleGuard::CompleteCombatMoveResult const complete =
        CollisionLifecycleGuard::CompleteCombatMoveCandidate(generation, result);
#ifdef FRAME_COLLISION_DIAGNOSTICS
    CollisionDiagnostics::LogCompleteCombatMoveResult(complete);
#endif
    return result;
}

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
static void GE_STDCALL AIFullStop_FrameCollisionTest(
    gCScriptRoutine_PS *a_pThis)
{
    void *callerAddress = _ReturnAddress();
    eCEntity *ownerEntity =
        a_pThis != nullptr ? a_pThis->GetEntity() : nullptr;
    if (IsPlayerEntity(ownerEntity))
    {
        Entity actor(ownerEntity);
        CollisionDiagnosticsDeep::AIFullStopStackSnapshot fullStop = {};
        fullStop.callerAddress = callerAddress;
        fullStop.context.frameCount = ::CaptureStackBackTrace(
            0, CollisionDiagnosticsDeep::NativeCleanupStackCapacity,
            fullStop.context.frames, nullptr);
        CollisionDiagnosticsDeep::CaptureHitReplacementContext(
            actor, nullptr, fullStop.context);
        fullStop.primary =
            CollisionDiagnosticsDeep::CapturePrimaryMotionEventSnapshot(actor);

        bCString currentState = actor.Routine.GetCurrentState();
        fullStop.currentState = currentState.GetText() != nullptr
            ? currentState.GetText() : "";
        fullStop.pressedKey = static_cast<GEInt>(
            actor.CharacterControl.GetProperty<
                PSCharacterControl::PropertyPressedKey>());
        fullStop.isPressed = actor.CharacterControl.GetProperty<
            PSCharacterControl::PropertyIsPressed>();
        fullStop.isPressedBefore = actor.CharacterControl.GetProperty<
            PSCharacterControl::PropertyIsPressedBefore>();
        fullStop.durationPressedMSecs = actor.CharacterControl.GetProperty<
            PSCharacterControl::PropertyDurationPressedMSecs>();

        CollisionDiagnosticsDeep::LogAIFullStopCallSite(actor, fullStop);
    }

    Hook_AIFullStop.GetOriginalFunction(&AIFullStop_FrameCollisionTest)(a_pThis);
}
#endif

static void GE_STDCALL AISetState_FrameCollisionTest(
    gCScriptRoutine_PS *a_pThis, bCString const &a_State)
{
    eCEntity *ownerEntity =
        a_pThis != nullptr ? a_pThis->GetEntity() : nullptr;
    CollisionLifecycleGuard::GenerationToken const finalization =
        CollisionLifecycleGuard::CaptureFinalizationToken(ownerEntity);

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
    void *callerAddress = _ReturnAddress();
    if (IsPlayerEntity(ownerEntity))
    {
        Entity actor(ownerEntity);
        CollisionDiagnosticsDeep::AISetStateStackSnapshot setState = {};
        setState.callerAddress = callerAddress;
        setState.context.frameCount = ::CaptureStackBackTrace(
            0, CollisionDiagnosticsDeep::NativeCleanupStackCapacity,
            setState.context.frames, nullptr);
        CollisionDiagnosticsDeep::CaptureHitReplacementContext(
            actor, nullptr, setState.context);
        setState.primary =
            CollisionDiagnosticsDeep::CapturePrimaryMotionEventSnapshot(actor);
        bCString currentState = actor.Routine.GetCurrentState();
        setState.currentState = currentState.GetText() != nullptr
            ? currentState.GetText() : "";
        setState.requestedState = a_State.GetText() != nullptr
            ? a_State.GetText() : "";
        CollisionDiagnosticsDeep::LogAISetStateCallSite(actor, setState);

        gCScriptProcessingUnit *spu = &a_pThis->GetSPU();
        CollisionDiagnosticsDeep::OuterFrameSnapshot const outerFrame =
            CollisionDiagnosticsDeep::CaptureOuterFrameSnapshot(actor, spu);
        CollisionDiagnosticsDeep::LogOuterFrameSnapshot(
            "DEEP OUTER_FRAME AI_SET_STATE_BEFORE", actor, nullptr,
            static_cast<eECollisionGroup>(-1),
            static_cast<eECollisionGroup>(-1),
            static_cast<eECollisionGroup>(-1), outerFrame);
    }
#endif

#ifdef FRAME_COLLISION_DIAGNOSTICS
    if (IsPlayerEntity(ownerEntity))
    {
        Entity actor(ownerEntity);
        CollisionDiagnostics::LogFistTriggerStateSnapshot(
            "AISETSTATE_BEFORE_ORIGINAL", actor);
    }
#endif

    Hook_AISetState.GetOriginalFunction(&AISetState_FrameCollisionTest)(
        a_pThis, a_State);

#ifdef FRAME_COLLISION_DIAGNOSTICS
    if (IsPlayerEntity(ownerEntity))
    {
        Entity actor(ownerEntity);
        CollisionDiagnostics::LogFistTriggerStateSnapshot(
            "AISETSTATE_AFTER_ORIGINAL", actor);
    }
#endif

    CollisionLifecycleGuard::FinalizationResult const result =
        CollisionLifecycleGuard::FinalizeAfterAISetState(finalization);
#ifdef FRAME_COLLISION_DIAGNOSTICS
    CollisionDiagnostics::LogFinalizationResult(result);
#endif

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
    if (IsPlayerEntity(ownerEntity))
    {
        Entity actor(ownerEntity);
        gCScriptProcessingUnit *spu = &a_pThis->GetSPU();
        CollisionDiagnosticsDeep::OuterFrameSnapshot const outerFrame =
            CollisionDiagnosticsDeep::CaptureOuterFrameSnapshot(actor, spu);
        CollisionDiagnosticsDeep::LogOuterFrameSnapshot(
            "DEEP OUTER_FRAME AI_SET_STATE_AFTER", actor, nullptr,
            static_cast<eECollisionGroup>(-1),
            static_cast<eECollisionGroup>(-1),
            static_cast<eECollisionGroup>(-1), outerFrame);
    }
#endif
}

static void GE_STDCALL SetCollisionGroup_FrameCollisionTest(
    eCEntity *a_pThis, eECollisionGroup a_Group)
{
    eECollisionGroup const beforeGroup = a_pThis != nullptr
        ? a_pThis->GetCollisionGroup()
        : static_cast<eECollisionGroup>(-1);

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
    void *callerAddress = _ReturnAddress();
    CollisionDiagnosticsDeep::NativeCleanupStackSnapshot cleanupStack = {};
    if (a_Group == eECollisionGroup_Item_Equipped
        && beforeGroup == eECollisionGroup_Item_Attack)
    {
        cleanupStack.frameCount = ::CaptureStackBackTrace(
            0, CollisionDiagnosticsDeep::NativeCleanupStackCapacity,
            cleanupStack.frames, nullptr);
    }
#endif

    Hook_SetCollisionGroup.GetOriginalFunction(
        &SetCollisionGroup_FrameCollisionTest)(a_pThis, a_Group);

    GEInt retiredMarkerSourceBitCount = 0;
    if (a_pThis != nullptr
        && a_pThis->GetCollisionGroup() != eECollisionGroup_Item_Attack)
    {
        retiredMarkerSourceBitCount =
            FrameCollisionMarkers::RetireMarkerOwnedSource(a_pThis);
    }

    eECollisionGroup const afterGroup = a_pThis != nullptr
        ? a_pThis->GetCollisionGroup()
        : static_cast<eECollisionGroup>(-1);

    CollisionLifecycleGuard::PreCombatDispatchView preCombatDispatch = {};
    CollisionLifecycleGuard::PreCombatDispatchView const *preCombatDispatchPtr =
        nullptr;
    CollisionLifecycleGuard::PreCombatBridgeToken *preCombatBridge = nullptr;
    if (a_Group == eECollisionGroup_Item_Attack
        && afterGroup == eECollisionGroup_Item_Attack
        && g_pCurrentRunScriptFunctionScope != nullptr)
    {
        RunScriptFunctionScope *scope = g_pCurrentRunScriptFunctionScope;
        preCombatDispatch.spu = scope->spu;
        preCombatDispatch.runtimeStack = scope->runtimeStack;
        preCombatDispatch.scriptName = scope->scriptName;
        preCombatDispatchPtr = &preCombatDispatch;
        preCombatBridge = &scope->preCombatBridge;
    }

    CollisionLifecycleGuard::CollisionObservationResult const observation =
        CollisionLifecycleGuard::ObserveCollisionGroupResult(
            a_pThis, a_Group, afterGroup, preCombatDispatchPtr,
            preCombatBridge);

#ifdef FRAME_COLLISION_DIAGNOSTICS
    CollisionDiagnostics::LogSetCollisionGroup(
        a_pThis, a_Group, beforeGroup, afterGroup,
        retiredMarkerSourceBitCount);
    CollisionDiagnostics::LogCollisionObservationResult(observation);
    if (observation.offenseRequestObserved
        && g_pCurrentRunScriptFunctionScope != nullptr)
    {
        g_pCurrentRunScriptFunctionScope->offenseObserved = true;
    }
#endif

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
    CollisionDiagnosticsDeep::LogNativeCleanupCallSite(
        a_pThis, a_Group, beforeGroup, afterGroup,
        callerAddress, cleanupStack);

    if (a_pThis != nullptr)
    {
        Entity player = Entity::GetPlayer();
        if (player != None)
        {
            EquippedCollisionSources const sources =
                CollisionSources::GetEquippedCollisionSources(player);
            bool const isEquippedPlayerSource =
                a_pThis == sources.rightInstance
                || a_pThis == sources.leftInstance;
            bool const successfulOffense =
                isEquippedPlayerSource
                && a_Group == eECollisionGroup_Item_Attack
                && afterGroup == eECollisionGroup_Item_Attack;
            bool const observedCleanup =
                isEquippedPlayerSource
                && beforeGroup == eECollisionGroup_Item_Attack
                && afterGroup != eECollisionGroup_Item_Attack;
            if (successfulOffense || observedCleanup)
            {
                gCScriptProcessingUnit *spu = GetActorSPU(player);
                if (successfulOffense)
                {
                    RunScriptFunctionScope *scope =
                        g_pCurrentRunScriptFunctionScope;
                    void *playerStateStackAddress = spu != nullptr
                        ? static_cast<void *>(&spu->m_StateStack) : nullptr;
                    bool const spuMatchesPlayer =
                        scope != nullptr && spu != nullptr
                        && scope->spu == spu;
                    bool const runtimeStackMatchesPlayer =
                        scope != nullptr && spu != nullptr
                        && scope->runtimeStack == &spu->m_StateStack;
                    CollisionDiagnosticsDeep::LogRunScriptFunctionOffenseScope(
                        player, a_pThis,
                        GetRunScriptFunctionScopeIdentity(scope),
                        spu, playerStateStackAddress, spuMatchesPlayer,
                        runtimeStackMatchesPlayer, spuMatchesPlayer);
                }
                CollisionDiagnosticsDeep::OuterFrameSnapshot const outerFrame =
                    CollisionDiagnosticsDeep::CaptureOuterFrameSnapshot(
                        player, spu);
                CollisionDiagnosticsDeep::LogOuterFrameSnapshot(
                    successfulOffense
                        ? "DEEP OUTER_FRAME OFFENSE"
                        : "DEEP OUTER_FRAME CLEANUP",
                    player, a_pThis, a_Group, beforeGroup, afterGroup,
                    outerFrame);
            }
        }
    }
#endif
}

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
static GEInt GE_STDCALL OnTick_FrameCollisionTest(
    gCScriptProcessingUnit *a_pSPU, GELPVoid a_pSelfEntity,
    GELPVoid a_pOtherEntity, GEInt a_iArgs)
{
    GEInt const result = Hook_OnTick.GetOriginalFunction(
        &OnTick_FrameCollisionTest)(
            a_pSPU, a_pSelfEntity, a_pOtherEntity, a_iArgs);
    if (!FrameCollisionMarkers::HasMarkerOwnedWindows())
        return result;

    Entity actor;
    if (a_pSelfEntity != nullptr)
        actor = *static_cast<Entity *>(a_pSelfEntity);
    else if (a_pSPU != nullptr)
        actor.AttachTo(a_pSPU->GetSelfEntity());

    if (actor != None)
    {
        MarkerOwnedWindowView window = {};
        if (FrameCollisionMarkers::TryGetMarkerOwnedWindow(
                actor.GetInstance(), window))
        {
            CollisionDiagnosticsDeep::ObserveMarkerOwnedLifetimeOnTick(
                actor, window);
        }
        else
        {
            CollisionDiagnosticsDeep::ForgetMarkerOwnedLifetime(
                actor.GetInstance());
        }
    }
    return result;
}
#endif

void FrameCollision::EngineBridge::InstallHooks()
{
    GetScriptAdmin().LoadScriptDLL("Script_Game.dll");

    Hook_OnAI_Attack.Hook(
        GetScriptAdminExt().GetScriptAICallback("OnAI_Attack")
            ->m_funcScriptAICallback,
        &OnAI_Attack_FrameCollisionTest);
    Hook_OnAI_PowerAttack.Hook(
        GetScriptAdminExt().GetScriptAICallback("OnAI_PowerAttack")
            ->m_funcScriptAICallback,
        &OnAI_PowerAttack_FrameCollisionTest);
    Hook_OnAI_QuickAttack.Hook(
        GetScriptAdminExt().GetScriptAICallback("OnAI_QuickAttack")
            ->m_funcScriptAICallback,
        &OnAI_QuickAttack_FrameCollisionTest);
    Hook_OnAI_SimpleWhirl.Hook(
        GetScriptAdminExt().GetScriptAICallback("OnAI_SimpleWhirl")
            ->m_funcScriptAICallback,
        &OnAI_SimpleWhirl_FrameCollisionTest);
    Hook_OnAI_WhirlAttack.Hook(
        GetScriptAdminExt().GetScriptAICallback("OnAI_WhirlAttack")
            ->m_funcScriptAICallback,
        &OnAI_WhirlAttack_FrameCollisionTest);
    Hook_OnAI_PierceAttack.Hook(
        GetScriptAdminExt().GetScriptAICallback("OnAI_PierceAttack")
            ->m_funcScriptAICallback,
        &OnAI_PierceAttack_FrameCollisionTest);
    Hook_OnAI_HackAttack.Hook(
        GetScriptAdminExt().GetScriptAICallback("OnAI_HackAttack")
            ->m_funcScriptAICallback,
        &OnAI_HackAttack_FrameCollisionTest);

    Hook_CombatMoveMotionResourceQuery
        .Prepare(RVA_Game(0x16B10C),
                 &QueryCombatMoveMotionResource_FrameCollisionTest)
        // sAICombatMoveInstr's EBP + 0x0C argument is its existing SPU.
        .AddPtrStackArgEbp(0xC)
        .AddThisArg()
        .Hook();

    Hook_StartEffect
        .Prepare(RVA_Game(0x60850), &StartEffect_FrameCollisionTest,
                 mCBaseHook::mEHookType_ThisCall)
        .Hook();
    Hook_SetCollisionGroup
        .Prepare(RVA_Engine(0x225660), &SetCollisionGroup_FrameCollisionTest)
        .ThisCall()
        .Hook();
    Hook_AICombatMoveInstr
        .Prepare(RVA_Game(0x1696E0), &AICombatMoveInstr_FrameCollisionTest)
        .Hook();
    Hook_AISetState
        .Prepare(RVA_Game(0x164320), &AISetState_FrameCollisionTest)
        .ThisCall()
        .Hook();
    Hook_RunScriptFunction
        .Prepare(RVA_Game(0x1604E0), &RunScriptFunction_FrameCollisionTest)
        .ThisCall()
        .Hook();

#ifdef FRAME_COLLISION_DIAGNOSTICS_DEEP
    gSScript const *onTickScript = GetScriptAdminExt().GetScript("OnTick");
    if (onTickScript != nullptr)
    {
        Hook_OnTick.Hook(onTickScript->m_funcScript, &OnTick_FrameCollisionTest);
    }
    else if (CollisionDiagnostics::IsLogOpen())
    {
        std::fprintf(
            CollisionDiagnostics::GetLog(),
            "DEEP WARNING: OnTick script not found; marker lifetime probe disabled.\n");
        std::fflush(CollisionDiagnostics::GetLog());
    }

    Hook_PlayMotion
        .Prepare(RVA_Engine(0x30860), &PlayMotion_FrameCollisionTest,
                 mCBaseHook::mEHookType_ThisCall)
        .Hook();
    Hook_StopMotion
        .Prepare(RVA_Engine(0x30980), &StopMotion_FrameCollisionTest,
                 mCBaseHook::mEHookType_ThisCall)
        .Hook();
    Hook_AICombatMoveStartRecover
        .Prepare(RVA_Game(0x16E360),
                 &AICombatMoveStartRecover_FrameCollisionTest)
        .Hook();
    Hook_AIFullStop
        .Prepare(RVA_Game(0x164430), &AIFullStop_FrameCollisionTest)
        .ThisCall()
        .Hook();
#endif
}

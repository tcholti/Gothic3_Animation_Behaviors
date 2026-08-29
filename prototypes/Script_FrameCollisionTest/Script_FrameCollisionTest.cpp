#include "CollisionControl.h"
#include "CollisionDiagnostics.h"
#include "CollisionLifecycleGuard.h"
#include "HookBridgeRuntime.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>
#include <g3sdk/Game/ge_effectsystem.h>
#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Memory.h>
#include <g3sdk/util/ScriptUtil.h>

#include <intrin.h>
#include <windows.h>

#pragma intrinsic(_ReturnAddress)

using namespace FrameCollision;

// Sole owner of every Gothic 3 hook used by this research DLL.
static mCFunctionHook Hook_StartEffect;
static mCFunctionHook Hook_OnAI_Attack;
static mCFunctionHook Hook_OnAI_QuickAttack;
static mCFunctionHook Hook_OnAI_WhirlAttack;
static mCFunctionHook Hook_OnTick;
static mCFunctionHook Hook_SetCollisionGroup;
static mCFunctionHook Hook_PlayMotion;
static mCFunctionHook Hook_StopMotion;
static mCFunctionHook Hook_AICombatMoveInstr;
static mCFunctionHook Hook_AICombatMoveStartRecover;
static mCFunctionHook Hook_AIFullStop;
static mCFunctionHook Hook_AISetState;
static mCFunctionHook Hook_RunScriptFunction;

static bool ShouldSuppressAttackCallback(Entity &actor)
{
    CurrentMotionMarkerResult decision = CollisionControl::GetCurrentMarkerDecision(actor);
    EquippedCollisionSources sources = CollisionControl::GetEquippedCollisionSources(actor);
    bool willSuppress = decision.foundMatchingMotion && decision.markerPresent
                     && CollisionControl::HasRequiredCollisionSources(
                            sources, decision.requiredSourceMask);

    if (willSuppress)
    {
        ControlledCallbackObservation observation =
            CollisionControl::ObserveControlledAttackCallback(actor, sources);
        CollisionDiagnostics::LogControlledCallbackBoundary(actor, observation);
    }

    if (CollisionDiagnostics::ShouldLogOwnership(actor))
        CollisionDiagnostics::LogOwnershipDecision(actor, decision, sources, willSuppress);

    return willSuppress;
}

DECLARE_SCRIPT_CALLBACK(OnAI_Attack_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()
    if (CollisionControl::IsAttackHit(SelfEntity, AttackFamily_Normal)
        && ShouldSuppressAttackCallback(SelfEntity))
        return GETrue;
    return Hook_OnAI_Attack.GetOriginalFunction(&OnAI_Attack_FrameCollisionTest)(a_pSPU);
}

DECLARE_SCRIPT_CALLBACK(OnAI_QuickAttack_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()
    if (CollisionControl::IsAttackHit(SelfEntity, AttackFamily_Quick)
        && ShouldSuppressAttackCallback(SelfEntity))
        return GETrue;
    return Hook_OnAI_QuickAttack.GetOriginalFunction(&OnAI_QuickAttack_FrameCollisionTest)(a_pSPU);
}

DECLARE_SCRIPT_CALLBACK(OnAI_WhirlAttack_FrameCollisionTest)
{
    INIT_SCRIPT_CALLBACK()
    if (CollisionControl::IsAttackHit(SelfEntity, AttackFamily_Whirl)
        && ShouldSuppressAttackCallback(SelfEntity))
        return GETrue;
    return Hook_OnAI_WhirlAttack.GetOriginalFunction(&OnAI_WhirlAttack_FrameCollisionTest)(a_pSPU);
}

static bool IsPlayerEntity(eCEntity *instance)
{
    Entity player = Entity::GetPlayer();
    return player != None && instance == player.GetInstance();
}

static gCScriptProcessingUnit *GetActorSPU(Entity &actor)
{
    if (actor == None)
        return nullptr;
    gCScriptRoutine_PS *routinePS = static_cast<gCScriptRoutine_PS *>(
        actor.Routine.m_pEngineEntityPropertySet);
    return routinePS != nullptr ? &routinePS->GetSPU() : nullptr;
}

static GELPVoid StartEffect_FrameCollisionTest(
    bCString const &a_EffectName, eCEntity *a_pEntity1, eCEntity *a_pEntity2,
    bCMatrix const *a_pMatrix, GEBool a_bUnknown)
{
    GELPCChar effectName = a_EffectName.GetText();
    MarkerOpcode markerOpcode = CollisionControl::GetMarkerOpcode(effectName);
    if (markerOpcode == MarkerOpcode_Invalid)
    {
        return Hook_StartEffect.GetOriginalFunction(&StartEffect_FrameCollisionTest)(
            a_EffectName, a_pEntity1, a_pEntity2, a_pMatrix, a_bUnknown);
    }

    // Reserved markers are always consumed so Gothic 3 never resolves them as
    // real effect resources.
    if (a_pEntity1 == nullptr)
    {
        CollisionDiagnostics::LogNullMarker(effectName);
        return nullptr;
    }

    Entity actor(a_pEntity1);
    EquippedCollisionSources sources = CollisionControl::GetEquippedCollisionSources(actor);
    CollisionDiagnostics::LogMarkerContext(effectName, markerOpcode, actor, sources);

    MarkerProcessResult result = CollisionControl::ProcessMarker(
        actor, sources, markerOpcode, effectName,
        HookBridgeRuntime::GetElapsedMilliseconds());

    if (result.code == MarkerResult_Accepted)
    {
        if (result.markerOwnedWeaponMask != SourceMask_None)
            CollisionDiagnostics::ResetMarkerOwnedLifetime(a_pEntity1);
        else
            CollisionDiagnostics::ForgetMarkerOwnedLifetime(a_pEntity1);
    }
    else if ((result.code == MarkerResult_OffAccepted
           || result.code == MarkerResult_OffNoWindow)
          && result.markerOwnedWindowRemoved)
    {
        CollisionDiagnostics::ForgetMarkerOwnedLifetime(a_pEntity1);
    }

    CollisionDiagnostics::LogMarkerResult(result);
    return nullptr;
}

static bool DidPrimaryFirstReplace(
    CollisionDiagnostics::PrimaryMotionEventSnapshot const &before,
    CollisionDiagnostics::PrimaryMotionEventSnapshot const &after)
{
    if (!before.primary.hasMotionInstance
        || !after.primary.available
        || !after.primary.hasMotionInstance)
        return false;

    if (before.primary.motionName != after.primary.motionName)
        return true;

    // A same-name execution can still be replaced/restarted. B1 already
    // records play time, so a clear rollback is the narrow evidence available
    // here without guessing at opaque motion-instance internals.
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

    eCVisualAnimation_PS *pThis = Hook_PlayMotion.GetSelf<eCVisualAnimation_PS *>();
    eCEntity *ownerEntity = pThis != nullptr ? pThis->GetEntity() : nullptr;
    if (!IsPlayerEntity(ownerEntity))
    {
        Hook_PlayMotion.GetOriginalFunction(&PlayMotion_FrameCollisionTest)(
            a_MotionType, a_pMotionDesc);
        return;
    }

    CollisionDiagnostics::PrimaryMotionEventSnapshot before =
        CollisionDiagnostics::CapturePrimaryMotionEventSnapshot(pThis);
    Entity actor(ownerEntity);
    bool const outgoingAttackHit =
        CollisionDiagnostics::IsAttackHitPrimaryMotion(before);
    CollisionDiagnostics::HitReplacementStackSnapshot replacement = {};
    if (outgoingAttackHit)
    {
        replacement.outgoingMotionName = before.primary.motionName;
        replacement.frameCount = ::CaptureStackBackTrace(
            0, CollisionDiagnostics::NativeCleanupStackCapacity,
            replacement.frames, nullptr);
        CollisionDiagnostics::CaptureHitReplacementContext(
            actor, static_cast<void *>(a_pMotionDesc), replacement);
    }

    bool const emptyPrimaryContext =
        before.primary.available
        && !before.primary.hasMotionInstance;
    CollisionDiagnostics::HitReplacementStackSnapshot emptyPrimarySuccessor = {};
    if (emptyPrimaryContext)
    {
        emptyPrimarySuccessor.frameCount = ::CaptureStackBackTrace(
            0, CollisionDiagnostics::NativeCleanupStackCapacity,
            emptyPrimarySuccessor.frames, nullptr);
        CollisionDiagnostics::CaptureHitReplacementContext(
            actor, static_cast<void *>(a_pMotionDesc), emptyPrimarySuccessor);
    }

    Hook_PlayMotion.GetOriginalFunction(&PlayMotion_FrameCollisionTest)(
        a_MotionType, a_pMotionDesc);
    CollisionDiagnostics::PrimaryMotionEventSnapshot after =
        CollisionDiagnostics::CapturePrimaryMotionEventSnapshot(pThis);
    if (outgoingAttackHit && DidPrimaryFirstReplace(before, after))
        CollisionDiagnostics::LogHitReplacementStack(actor, replacement, after);
    if (emptyPrimaryContext
        && after.primary.available
        && after.primary.hasMotionInstance)
    {
        CollisionDiagnostics::LogEmptyPrimarySuccessorStack(
            actor, emptyPrimarySuccessor, after);
    }
    CollisionDiagnostics::LogPrimaryMotionEvent(
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

    eCVisualAnimation_PS *pThis = Hook_StopMotion.GetSelf<eCVisualAnimation_PS *>();
    eCEntity *ownerEntity = pThis != nullptr ? pThis->GetEntity() : nullptr;
    if (!IsPlayerEntity(ownerEntity))
    {
        Hook_StopMotion.GetOriginalFunction(&StopMotion_FrameCollisionTest)(
            a_MotionType, a_fBlendTime);
        return;
    }

    CollisionDiagnostics::PrimaryMotionEventSnapshot before =
        CollisionDiagnostics::CapturePrimaryMotionEventSnapshot(pThis);
    Entity actor(ownerEntity);
    if (CollisionDiagnostics::IsAttackHitPrimaryMotion(before))
    {
        CollisionDiagnostics::HitReplacementStackSnapshot stop = {};
        stop.outgoingMotionName = before.primary.motionName;
        stop.frameCount = ::CaptureStackBackTrace(
            0, CollisionDiagnostics::NativeCleanupStackCapacity,
            stop.frames, nullptr);
        CollisionDiagnostics::CaptureHitReplacementContext(
            actor, nullptr, stop);
        CollisionDiagnostics::LogHitStopStack(actor, stop, a_fBlendTime);
    }
    Hook_StopMotion.GetOriginalFunction(&StopMotion_FrameCollisionTest)(
        a_MotionType, a_fBlendTime);
    CollisionDiagnostics::PrimaryMotionEventSnapshot after =
        CollisionDiagnostics::CapturePrimaryMotionEventSnapshot(pThis);
    CollisionDiagnostics::LogPrimaryMotionEvent(
        pThis, "StopMotion", before, after);
}

static void GE_STDCALL AICombatMoveStartRecover_FrameCollisionTest(
    gCScriptProcessingUnit *a_pSPU)
{
    Entity actor;
    if (a_pSPU != nullptr)
        actor.AttachTo(a_pSPU->GetSelfEntity());
    bool const shouldLog =
        actor != None && IsPlayerEntity(actor.GetInstance());

    if (shouldLog)
    {
        CollisionDiagnostics::LogCombatMoveStartRecoverBoundary(actor, "BEGIN");
        CollisionDiagnostics::PrimaryMotionEventSnapshot begin =
            CollisionDiagnostics::CapturePrimaryMotionEventSnapshot(actor);
        if (CollisionDiagnostics::IsAttackHitPrimaryMotion(begin))
        {
            CollisionDiagnostics::HitReplacementStackSnapshot startRecover = {};
            startRecover.outgoingMotionName = begin.primary.motionName;
            startRecover.frameCount = ::CaptureStackBackTrace(
                0, CollisionDiagnostics::NativeCleanupStackCapacity,
                startRecover.frames, nullptr);
            CollisionDiagnostics::CaptureHitReplacementContext(
                actor, nullptr, startRecover);
            CollisionDiagnostics::LogHitStartRecoverBeginStack(
                actor, startRecover);
        }
    }
    Hook_AICombatMoveStartRecover.GetOriginalFunction(
        &AICombatMoveStartRecover_FrameCollisionTest)(a_pSPU);
    if (shouldLog)
        CollisionDiagnostics::LogCombatMoveStartRecoverBoundary(actor, "END");
}

static GEBool GE_STDCALL RunScriptFunction_FrameCollisionTest(
    gCScriptAdmin *a_pThis, bCString const &a_ScriptName,
    bTObjStack<gScriptRunTimeSingleState> &a_rRunTimeStack,
    gCScriptProcessingUnit *a_pSPU)
{
    return Hook_RunScriptFunction.GetOriginalFunction(
        &RunScriptFunction_FrameCollisionTest)(
            a_pThis, a_ScriptName, a_rRunTimeStack, a_pSPU);
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
            EquippedCollisionSources sources =
                CollisionControl::GetEquippedCollisionSources(actor);
            generation = CollisionLifecycleGuard::BeginCombatMove(
                actor, sources, a_pSPU);
        }
        CollisionDiagnostics::OuterFrameSnapshot outerFrame =
            CollisionDiagnostics::CaptureOuterFrameSnapshot(actor, a_pSPU);
        CollisionDiagnostics::LogOuterFrameSnapshot(
            "OUTER_FRAME COMBAT_MOVE_INITIAL", actor, nullptr,
            static_cast<eECollisionGroup>(-1),
            static_cast<eECollisionGroup>(-1),
            static_cast<eECollisionGroup>(-1), outerFrame);
    }

    if (a_bFullStop == GETrue && a_pSPU != nullptr)
    {
        Entity actor;
        actor.AttachTo(a_pSPU->GetSelfEntity());
        if (actor != None && IsPlayerEntity(actor.GetInstance()))
        {
            CollisionDiagnostics::HitReplacementStackSnapshot fullStop = {};
            fullStop.frameCount = ::CaptureStackBackTrace(
                0, CollisionDiagnostics::NativeCleanupStackCapacity,
                fullStop.frames, nullptr);
            CollisionDiagnostics::CaptureHitReplacementContext(
                actor, a_pArgs, fullStop);
            CollisionDiagnostics::PrimaryMotionEventSnapshot primary =
                CollisionDiagnostics::CapturePrimaryMotionEventSnapshot(actor);
            CollisionDiagnostics::LogCombatMoveFullStopStack(
                actor, fullStop, primary);
        }
    }

    GEBool result = Hook_AICombatMoveInstr.GetOriginalFunction(
        &AICombatMoveInstr_FrameCollisionTest)(a_pArgs, a_pSPU, a_bFullStop);
    CollisionLifecycleGuard::CompleteCombatMoveCandidate(generation, result);
    return result;
}

static void GE_STDCALL AIFullStop_FrameCollisionTest(
    gCScriptRoutine_PS *a_pThis)
{
    void *callerAddress = _ReturnAddress();
    eCEntity *ownerEntity =
        a_pThis != nullptr ? a_pThis->GetEntity() : nullptr;
    if (IsPlayerEntity(ownerEntity))
    {
        Entity actor(ownerEntity);
        CollisionDiagnostics::AIFullStopStackSnapshot fullStop = {};
        fullStop.callerAddress = callerAddress;
        fullStop.context.frameCount = ::CaptureStackBackTrace(
            0, CollisionDiagnostics::NativeCleanupStackCapacity,
            fullStop.context.frames, nullptr);
        CollisionDiagnostics::CaptureHitReplacementContext(
            actor, nullptr, fullStop.context);
        fullStop.primary =
            CollisionDiagnostics::CapturePrimaryMotionEventSnapshot(actor);

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

        CollisionDiagnostics::LogAIFullStopCallSite(actor, fullStop);
    }

    Hook_AIFullStop.GetOriginalFunction(&AIFullStop_FrameCollisionTest)(
        a_pThis);
}

static void GE_STDCALL AISetState_FrameCollisionTest(
    gCScriptRoutine_PS *a_pThis, bCString const &a_State)
{
    void *callerAddress = _ReturnAddress();
    eCEntity *ownerEntity =
        a_pThis != nullptr ? a_pThis->GetEntity() : nullptr;
    CollisionLifecycleGuard::GenerationToken finalization =
        CollisionLifecycleGuard::CaptureFinalizationToken(ownerEntity);
    if (IsPlayerEntity(ownerEntity))
    {
        Entity actor(ownerEntity);
        CollisionDiagnostics::AISetStateStackSnapshot setState = {};
        setState.callerAddress = callerAddress;
        setState.context.frameCount = ::CaptureStackBackTrace(
            0, CollisionDiagnostics::NativeCleanupStackCapacity,
            setState.context.frames, nullptr);
        CollisionDiagnostics::CaptureHitReplacementContext(
            actor, nullptr, setState.context);
        setState.primary =
            CollisionDiagnostics::CapturePrimaryMotionEventSnapshot(actor);

        bCString currentState = actor.Routine.GetCurrentState();
        setState.currentState = currentState.GetText() != nullptr
            ? currentState.GetText() : "";
        setState.requestedState = a_State.GetText() != nullptr
            ? a_State.GetText() : "";

        CollisionDiagnostics::LogAISetStateCallSite(actor, setState);

        gCScriptProcessingUnit *spu =
            a_pThis != nullptr ? &a_pThis->GetSPU() : nullptr;
        CollisionDiagnostics::OuterFrameSnapshot outerFrame =
            CollisionDiagnostics::CaptureOuterFrameSnapshot(actor, spu);
        CollisionDiagnostics::LogOuterFrameSnapshot(
            "OUTER_FRAME AI_SET_STATE_BEFORE", actor, nullptr,
            static_cast<eECollisionGroup>(-1),
            static_cast<eECollisionGroup>(-1),
            static_cast<eECollisionGroup>(-1), outerFrame);
    }

    Hook_AISetState.GetOriginalFunction(&AISetState_FrameCollisionTest)(
        a_pThis, a_State);
    CollisionLifecycleGuard::InvalidateScriptFunctionDispatchAfterAISetState(
        ownerEntity);
    CollisionLifecycleGuard::FinalizeAfterAISetState(finalization);
    if (IsPlayerEntity(ownerEntity))
    {
        Entity actor(ownerEntity);
        gCScriptProcessingUnit *spu =
            a_pThis != nullptr ? &a_pThis->GetSPU() : nullptr;
        CollisionDiagnostics::OuterFrameSnapshot outerFrame =
            CollisionDiagnostics::CaptureOuterFrameSnapshot(actor, spu);
        CollisionDiagnostics::LogOuterFrameSnapshot(
            "OUTER_FRAME AI_SET_STATE_AFTER", actor, nullptr,
            static_cast<eECollisionGroup>(-1),
            static_cast<eECollisionGroup>(-1),
            static_cast<eECollisionGroup>(-1), outerFrame);
    }
}

static void GE_STDCALL SetCollisionGroup_FrameCollisionTest(eECollisionGroup a_Group)
{
    void *callerAddress = _ReturnAddress();
    eCEntity *pThis = Hook_SetCollisionGroup.GetSelf<eCEntity *>();
    eECollisionGroup beforeGroup = pThis != nullptr
        ? pThis->GetCollisionGroup() : static_cast<eECollisionGroup>(-1);

    CollisionDiagnostics::NativeCleanupStackSnapshot cleanupStack = {};
    if (a_Group == eECollisionGroup_Item_Equipped
        && beforeGroup == eECollisionGroup_Item_Attack)
    {
        cleanupStack.frameCount = ::CaptureStackBackTrace(
            0, CollisionDiagnostics::NativeCleanupStackCapacity,
            cleanupStack.frames, nullptr);
    }

    Hook_SetCollisionGroup.GetOriginalFunction(&SetCollisionGroup_FrameCollisionTest)(a_Group);

    GEInt retiredMarkerExecutionCount = 0;
    if (pThis != nullptr && pThis->GetCollisionGroup() != eECollisionGroup_Item_Attack)
        retiredMarkerExecutionCount = CollisionControl::RetireMarkerOwnedSource(pThis);

    eECollisionGroup afterGroup = pThis != nullptr
        ? pThis->GetCollisionGroup() : static_cast<eECollisionGroup>(-1);
    CollisionLifecycleGuard::ObserveCollisionGroupResult(
        pThis, a_Group, afterGroup);
    CollisionDiagnostics::LogSetCollisionGroup(
        pThis, a_Group, beforeGroup, afterGroup,
        retiredMarkerExecutionCount, callerAddress, cleanupStack);
    if (pThis != nullptr)
    {
        Entity player = Entity::GetPlayer();
        if (player != None)
        {
            EquippedCollisionSources sources =
                CollisionControl::GetEquippedCollisionSources(player);
            bool const isEquippedPlayerSource =
                pThis == sources.rightInstance
                || pThis == sources.leftInstance;
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
                CollisionDiagnostics::OuterFrameSnapshot outerFrame =
                    CollisionDiagnostics::CaptureOuterFrameSnapshot(
                        player, spu);
                CollisionDiagnostics::LogOuterFrameSnapshot(
                    successfulOffense
                        ? "OUTER_FRAME OFFENSE"
                        : "OUTER_FRAME CLEANUP",
                    player, pThis, a_Group, beforeGroup, afterGroup,
                    outerFrame);
            }
        }
    }
}

static GEInt GE_STDCALL OnTick_FrameCollisionTest(gCScriptProcessingUnit *a_pSPU,
                                                  GELPVoid a_pSelfEntity,
                                                  GELPVoid a_pOtherEntity,
                                                  GEInt a_iArgs)
{
    GEInt result = Hook_OnTick.GetOriginalFunction(&OnTick_FrameCollisionTest)(
        a_pSPU, a_pSelfEntity, a_pOtherEntity, a_iArgs);
    if (!CollisionControl::HasMarkerOwnedWindows())
        return result;

    Entity actor;
    if (a_pSelfEntity != nullptr)
        actor = *static_cast<Entity *>(a_pSelfEntity);
    else if (a_pSPU != nullptr)
        actor.AttachTo(a_pSPU->GetSelfEntity());

    if (actor != None)
    {
        MarkerOwnedWindowView window = {};
        if (CollisionControl::TryGetMarkerOwnedWindow(actor.GetInstance(), window))
            CollisionDiagnostics::ObserveMarkerOwnedLifetimeOnTick(actor, window);
        else
            CollisionDiagnostics::ForgetMarkerOwnedLifetime(actor.GetInstance());
    }
    return result;
}

static void InstallHooks()
{
    GetScriptAdmin().LoadScriptDLL("Script_Game.dll");
    Hook_OnAI_Attack.Hook(
        GetScriptAdminExt().GetScriptAICallback("OnAI_Attack")->m_funcScriptAICallback,
        &OnAI_Attack_FrameCollisionTest);
    Hook_OnAI_QuickAttack.Hook(
        GetScriptAdminExt().GetScriptAICallback("OnAI_QuickAttack")->m_funcScriptAICallback,
        &OnAI_QuickAttack_FrameCollisionTest);
    Hook_OnAI_WhirlAttack.Hook(
        GetScriptAdminExt().GetScriptAICallback("OnAI_WhirlAttack")->m_funcScriptAICallback,
        &OnAI_WhirlAttack_FrameCollisionTest);

    gSScript const *onTickScript = GetScriptAdminExt().GetScript("OnTick");
    if (onTickScript != nullptr)
    {
        Hook_OnTick.Hook(onTickScript->m_funcScript, &OnTick_FrameCollisionTest);
    }
    else if (CollisionDiagnostics::IsLogOpen())
    {
        std::fprintf(CollisionDiagnostics::GetLog(),
                     "WARNING: OnTick script not found; primary-motion lifetime probe disabled.\n");
        std::fflush(CollisionDiagnostics::GetLog());
    }

    Hook_StartEffect
        .Prepare(RVA_Game(0x60850), &StartEffect_FrameCollisionTest,
                 mCBaseHook::mEHookType_ThisCall)
        .Hook();
    Hook_SetCollisionGroup
        .Prepare(RVA_Engine(0x225660), &SetCollisionGroup_FrameCollisionTest,
                 mCBaseHook::mEHookType_ThisCall)
        .Hook();
    Hook_PlayMotion
        .Prepare(RVA_Engine(0x30860), &PlayMotion_FrameCollisionTest,
                 mCBaseHook::mEHookType_ThisCall)
        .Hook();
    Hook_StopMotion
        .Prepare(RVA_Engine(0x30980), &StopMotion_FrameCollisionTest,
                 mCBaseHook::mEHookType_ThisCall)
        .Hook();
    Hook_AICombatMoveInstr
        .Prepare(RVA_Game(0x1696E0), &AICombatMoveInstr_FrameCollisionTest)
        .Hook();
    Hook_AICombatMoveStartRecover
        .Prepare(RVA_Game(0x16E360),
                 &AICombatMoveStartRecover_FrameCollisionTest)
        .Hook();
    Hook_AIFullStop
        .Prepare(RVA_Game(0x164430), &AIFullStop_FrameCollisionTest)
        .ThisCall()
        .Hook();
    Hook_AISetState
        .Prepare(RVA_Game(0x164320), &AISetState_FrameCollisionTest)
        .ThisCall()
        .Hook();
    Hook_RunScriptFunction
        .Prepare(RVA_Game(0x1604E0), &RunScriptFunction_FrameCollisionTest)
        .ThisCall()
        .Hook();
}

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    HookBridgeRuntime::InitializeClock();
    CollisionDiagnostics::OpenLog();
    if (CollisionDiagnostics::IsLogOpen())
    {
        std::fprintf(CollisionDiagnostics::GetLog(), "Installing hooks...\n");
        std::fflush(CollisionDiagnostics::GetLog());
    }
    InstallHooks();
    if (CollisionDiagnostics::IsLogOpen())
    {
        std::fprintf(CollisionDiagnostics::GetLog(), "Hooks installed.\n\n");
        std::fflush(CollisionDiagnostics::GetLog());
    }
    return &GetScriptInit();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH: ::DisableThreadLibraryCalls(hModule); break;
        case DLL_PROCESS_DETACH: CollisionDiagnostics::CloseLog(); break;
    }
    return TRUE;
}

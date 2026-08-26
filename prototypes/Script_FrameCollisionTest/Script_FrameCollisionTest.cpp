#include "CollisionControl.h"
#include "CollisionDiagnostics.h"
#include "HookBridgeRuntime.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>
#include <g3sdk/Game/ge_effectsystem.h>
#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Memory.h>
#include <g3sdk/util/ScriptUtil.h>

#include <windows.h>

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
    PrimaryMotionEventSnapshot before =
        CollisionDiagnostics::CapturePrimaryMotionEventSnapshot(pThis);
    Hook_PlayMotion.GetOriginalFunction(&PlayMotion_FrameCollisionTest)(
        a_MotionType, a_pMotionDesc);
    PrimaryMotionEventSnapshot after =
        CollisionDiagnostics::CapturePrimaryMotionEventSnapshot(pThis);
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
    PrimaryMotionEventSnapshot before =
        CollisionDiagnostics::CapturePrimaryMotionEventSnapshot(pThis);
    Hook_StopMotion.GetOriginalFunction(&StopMotion_FrameCollisionTest)(
        a_MotionType, a_fBlendTime);
    PrimaryMotionEventSnapshot after =
        CollisionDiagnostics::CapturePrimaryMotionEventSnapshot(pThis);
    CollisionDiagnostics::LogPrimaryMotionEvent(
        pThis, "StopMotion", before, after);
}

static void GE_STDCALL SetCollisionGroup_FrameCollisionTest(eECollisionGroup a_Group)
{
    eCEntity *pThis = Hook_SetCollisionGroup.GetSelf<eCEntity *>();
    eECollisionGroup beforeGroup = pThis != nullptr
        ? pThis->GetCollisionGroup() : static_cast<eECollisionGroup>(-1);
    Hook_SetCollisionGroup.GetOriginalFunction(&SetCollisionGroup_FrameCollisionTest)(a_Group);

    GEInt retiredMarkerExecutionCount = 0;
    if (pThis != nullptr && pThis->GetCollisionGroup() != eECollisionGroup_Item_Attack)
        retiredMarkerExecutionCount = CollisionControl::RetireMarkerOwnedSource(pThis);

    eECollisionGroup afterGroup = pThis != nullptr
        ? pThis->GetCollisionGroup() : static_cast<eECollisionGroup>(-1);
    CollisionDiagnostics::LogSetCollisionGroup(
        pThis, a_Group, beforeGroup, afterGroup, retiredMarkerExecutionCount);
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

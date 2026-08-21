#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>
#include <g3sdk/Engine/animation/ge_wrapper_emfx2actor.h>
#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Memory.h>

#include <stdio.h>

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

static mCCallHook Hook_CombatMoveLogger;
static mCFunctionHook Hook_GetAnimationSpeedModifier;

static FILE *g_pLogFile = nullptr;

const char *GetPhaseName(gEPhase a_Phase)
{
    switch (a_Phase)
    {
        case gEPhase_Raise: return "Raise";

        case gEPhase_Hit: return "Hit";

        case gEPhase_Aim: return "Aim";

        case gEPhase_Recover: return "Recover";

        case gEPhase_Begin: return "Begin";

        case gEPhase_Loop: return "Loop";

        case gEPhase_End: return "End";

        default: return "Other";
    }
}

GEBool TryGetPrimaryPlaySpeed(Entity a_Entity, GEFloat &a_rPlaySpeed)
{
    a_rPlaySpeed = 0.0f;

    if (a_Entity == None)
        return GEFalse;

    if (!a_Entity.Animation.IsValid())
        return GEFalse;

    eCVisualAnimation_PS *animationPS =
        static_cast<eCVisualAnimation_PS *>(a_Entity.Animation.m_pEngineEntityPropertySet);

    if (animationPS == nullptr)
        return GEFalse;

    if (!animationPS->HasActor())
        return GEFalse;

    eCWrapper_emfx2Actor *actor = animationPS->GetActor();

    if (actor == nullptr)
        return GEFalse;

    // The base SDK does not yet name its eEMotionType values.
    // Jackydima's adjusted SDK confirms that PrimaryFirst is the first value,
    // therefore its numeric value is 0.
    const eCWrapper_emfx2Actor::eEMotionType motionType = static_cast<eCWrapper_emfx2Actor::eEMotionType>(0);

    if (!actor->HasMotionInstance(motionType))
        return GEFalse;

    a_rPlaySpeed = actor->GetPlaySpeed(motionType);

    return GETrue;
}

void LogPrimaryPlaySpeed(Entity a_Entity)
{
    if (g_pLogFile == nullptr)
        return;

    GEFloat playSpeed = 0.0f;

    if (TryGetPrimaryPlaySpeed(a_Entity, playSpeed))
    {
        fprintf(g_pLogFile, "PrimaryPlaySpeed: %.3f\n", playSpeed);
    }
    else
    {
        fprintf(g_pLogFile, "PrimaryPlaySpeed: Unavailable\n");
    }
}

void GE_STDCALL CombatMoveLogger(gCScriptProcessingUnit::sAICombatMoveInstr_Args *a_pArgs,
                                 gCScriptProcessingUnit *a_pSPU)
{
    if (a_pArgs == nullptr || a_pSPU == nullptr)
        return;

    Entity self = Entity(a_pArgs->SelfEntity);

    if (self == None)
        return;

    // Diagnostic logger remains player-only.
    if (self != Entity::GetPlayer())
        return;

    if (g_pLogFile == nullptr)
        return;

    Entity target = Entity(a_pArgs->TargetEntity);

    bCString currentMovementAni = self.NPC.GetCurrentMovementAni();

    gEPhase currentAniPhase = self.GetCurrentAniPhase();

    gEDirection currentAniDirection = self.GetCurrentAniDirection();

    fprintf(g_pLogFile, "========== CombatMove ==========\n");

    fprintf(g_pLogFile, "Self: %s\n", self.GetName().GetText());

    fprintf(g_pLogFile, "Action: %d\n", static_cast<GEInt>(a_pArgs->Action));

    fprintf(g_pLogFile, "RequestedPhaseName: %s\n", a_pArgs->PhaseName.GetText());

    fprintf(g_pLogFile, "AniSpeedScale: %.3f\n", a_pArgs->AniSpeedScale);

    fprintf(g_pLogFile, "CurrentMovementAni: %s\n", currentMovementAni.GetText());

    fprintf(g_pLogFile, "CurrentAniPhase: %d\n", static_cast<GEInt>(currentAniPhase));

    fprintf(g_pLogFile, "CurrentAniDirection: %d\n", static_cast<GEInt>(currentAniDirection));

    LogPrimaryPlaySpeed(self);

    if (target != None)
    {
        fprintf(g_pLogFile, "Target: %s\n", target.GetName().GetText());
    }
    else
    {
        fprintf(g_pLogFile, "Target: None\n");
    }

    fprintf(g_pLogFile, "===============================\n\n");

    fflush(g_pLogFile);
}

GEFloat GE_STDCALL AnimationSpeedModifierLogger(Entity a_Entity, gEPhase a_Phase)
{
    // Gothic 3 supplies the current Action through EAX.
    gEAction action = Hook_GetAnimationSpeedModifier.GetImmEax<gEAction>();

    // Call Gothic 3's original speed function unchanged.
    GEFloat returnedSpeed =
        Hook_GetAnimationSpeedModifier.GetOriginalFunction(&AnimationSpeedModifierLogger)(a_Entity, a_Phase);

    if (a_Entity == None)
        return returnedSpeed;

    // Diagnostic remains player-only.
    if (a_Entity != Entity::GetPlayer())
        return returnedSpeed;

    if (g_pLogFile == nullptr)
        return returnedSpeed;

    bCString currentMovementAni = a_Entity.NPC.GetCurrentMovementAni();

    gEPhase currentAniPhase = a_Entity.GetCurrentAniPhase();

    gEDirection currentAniDirection = a_Entity.GetCurrentAniDirection();

    fprintf(g_pLogFile, "===== AnimationSpeedModifier =====\n");

    fprintf(g_pLogFile, "Self: %s\n", a_Entity.GetName().GetText());

    fprintf(g_pLogFile, "Action: %d\n", static_cast<GEInt>(action));

    fprintf(g_pLogFile, "RequestedPhase: %s (%d)\n", GetPhaseName(a_Phase), static_cast<GEInt>(a_Phase));

    fprintf(g_pLogFile, "ReturnedSpeedModifier: %.3f\n", returnedSpeed);

    fprintf(g_pLogFile, "CurrentMovementAni: %s\n", currentMovementAni.GetText());

    fprintf(g_pLogFile, "CurrentAniPhase: %s (%d)\n", GetPhaseName(currentAniPhase),
            static_cast<GEInt>(currentAniPhase));

    fprintf(g_pLogFile, "CurrentAniDirection: %d\n", static_cast<GEInt>(currentAniDirection));

    LogPrimaryPlaySpeed(a_Entity);

    fprintf(g_pLogFile, "==================================\n\n");

    fflush(g_pLogFile);

    return returnedSpeed;
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    g_pLogFile = fopen("CombatMoveLogger.log", "w");

    if (g_pLogFile != nullptr)
    {
        fprintf(g_pLogFile, "Script_CombatMoveLogger v0.4 loaded.\n");

        fprintf(g_pLogFile, "ScriptInit reached successfully.\n");

        fprintf(g_pLogFile, "Installing CombatMove hook...\n");

        fprintf(g_pLogFile, "Installing AnimationSpeedModifier hook...\n\n");

        fflush(g_pLogFile);
    }

    GetScriptAdmin().LoadScriptDLL("Script_Game.dll");

    // Existing known-good CombatMove hook.
    Hook_CombatMoveLogger.Prepare(RVA_Game(0x16B065), &CombatMoveLogger)
        .InsertCall()
        .AddPtrStackArgEbp(0x8)
        .AddPtrStackArgEbp(0xC)
        .RestoreRegister()
        .Hook();

    // Existing known-good read-only speed-modifier hook.
    Hook_GetAnimationSpeedModifier
        .Prepare(RVA_ScriptGame(0x42A0), &AnimationSpeedModifierLogger, mCBaseHook::mEHookType_Mixed,
                 mERegisterType_Eax)
        .Hook();

    if (g_pLogFile != nullptr)
    {
        fprintf(g_pLogFile, "CombatMove hook installed.\n");

        fprintf(g_pLogFile, "AnimationSpeedModifier hook installed.\n\n");

        fflush(g_pLogFile);
    }

    return &GetScriptInit();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH: ::DisableThreadLibraryCalls(hModule); break;

        case DLL_PROCESS_DETACH:
            if (g_pLogFile != nullptr)
            {
                fprintf(g_pLogFile, "Script_CombatMoveLogger unloading.\n");

                fflush(g_pLogFile);
                fclose(g_pLogFile);
                g_pLogFile = nullptr;
            }
            break;
    }

    return TRUE;
}

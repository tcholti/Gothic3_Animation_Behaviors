#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Memory.h>

#include <cstdio>

namespace
{
static mCCallHook Hook_SpeedModifierCall_47F6C;
static mCCaller Call_GetAnimationSpeedModifier;
static FILE *g_pLogFile = nullptr;
static GEU32 g_EventOrdinal = 0;
static GEU32 const EventLogCap = 1024;

using mFGetAnimationSpeedModifier = GEFloat (GE_STDCALL *)(Entity, gEPhase);

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

char const *GetPhaseName(gEPhase phase)
{
    switch (phase)
    {
        case gEPhase_Raise:   return "Raise";
        case gEPhase_Hit:     return "Hit";
        case gEPhase_Aim:     return "Aim";
        case gEPhase_Recover: return "Recover";
        case gEPhase_Begin:   return "Begin";
        case gEPhase_Loop:    return "Loop";
        case gEPhase_End:     return "End";
        default:              return "Other";
    }
}

GEFloat GE_STDCALL SpeedSprintProbe(
    gEAction passedAction,
    Entity entity,
    gEPhase phase)
{
    gEAction currentActionBefore = gEAction_None;
    gEAction currentActionAfter = gEAction_None;

    if (entity != None)
    {
        currentActionBefore =
            entity.Routine.GetProperty<PSRoutine::PropertyAction>();
    }

    Call_GetAnimationSpeedModifier.SetImmEax(passedAction);
    GEFloat const compatibleSpeed =
        Call_GetAnimationSpeedModifier
            .GetFunction<mFGetAnimationSpeedModifier>()(
                entity, phase);

    if (entity != None)
    {
        currentActionAfter =
            entity.Routine.GetProperty<PSRoutine::PropertyAction>();
    }

    // The first runtime probe filtered non-player calls by observing Action9 at
    // this exact point. That was circular: the question is whether Gothic may
    // enter this shared routine as Sprint and change PropertyAction before the
    // Hit-speed call. Therefore log every +0x47F6C call, bounded by a cap.
    if (g_pLogFile != nullptr
        && entity != None
        && g_EventOrdinal < EventLogCap)
    {
        ++g_EventOrdinal;

        bool const isPlayer = entity == Entity::GetPlayer();
        bool const sprintBefore =
            currentActionBefore == gEAction_SprintAttack;
        bool const sprintAfter =
            currentActionAfter == gEAction_SprintAttack;
        bCString const currentMovementAni = entity.NPC.GetCurrentMovementAni();
        bCString const entityName = entity.GetName();

        std::fprintf(g_pLogFile, "===== SprintSharedPowerHit =====\n");
        std::fprintf(
            g_pLogFile,
            "Ordinal=%u\n",
            static_cast<unsigned>(g_EventOrdinal));
        std::fprintf(
            g_pLogFile,
            "Entity=%s\n",
            entityName.GetText());
        std::fprintf(
            g_pLogFile,
            "IsPlayer=%s\n",
            isPlayer ? "true" : "false");
        std::fprintf(
            g_pLogFile,
            "PassedAction=%d\n",
            static_cast<GEInt>(passedAction));
        std::fprintf(
            g_pLogFile,
            "CurrentActionBefore=%d\n",
            static_cast<GEInt>(currentActionBefore));
        std::fprintf(
            g_pLogFile,
            "SprintBefore=%s\n",
            sprintBefore ? "true" : "false");
        std::fprintf(
            g_pLogFile,
            "RequestedPhase=%s (%d)\n",
            GetPhaseName(phase),
            static_cast<GEInt>(phase));
        std::fprintf(
            g_pLogFile,
            "CompatibleSpeed=%.6f\n",
            compatibleSpeed);
        std::fprintf(
            g_pLogFile,
            "CurrentActionAfter=%d\n",
            static_cast<GEInt>(currentActionAfter));
        std::fprintf(
            g_pLogFile,
            "SprintAfter=%s\n",
            sprintAfter ? "true" : "false");
        std::fprintf(
            g_pLogFile,
            "CurrentMovementAni=%s\n",
            currentMovementAni.GetText());
        std::fprintf(g_pLogFile, "===============================\n\n");
        std::fflush(g_pLogFile);
    }

    return compatibleSpeed;
}
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    g_pLogFile = std::fopen("SpeedSprintProbe.log", "w");
    if (g_pLogFile != nullptr)
    {
        std::fprintf(
            g_pLogFile,
            "Script_SpeedSprintProbe loaded. Diagnostics only; no speed composition.\n");
        std::fprintf(
            g_pLogFile,
            "Logging every Script_Game+0x47F6C call, capped at %u events.\n\n",
            static_cast<unsigned>(EventLogCap));
        std::fflush(g_pLogFile);
    }

    GetScriptAdmin().LoadScriptDLL("Script_Game.dll");

    Call_GetAnimationSpeedModifier.Init(
        mCCaller::GetCallerParams(
            RVA_ScriptGame(0x42A0), mERegisterType_Eax));

    Hook_SpeedModifierCall_47F6C
        .Prepare(RVA_ScriptGame(0x47F6C), &SpeedSprintProbe)
        .AddRegArg(mERegisterType_Eax)
        .Hook();

    if (g_pLogFile != nullptr)
    {
        std::fprintf(
            g_pLogFile,
            "Hook installed at Script_Game+0x47F6C.\n\n");
        std::fflush(g_pLogFile);
    }

    return &GetScriptInit();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            ::DisableThreadLibraryCalls(hModule);
            break;

        case DLL_PROCESS_DETACH:
            if (g_pLogFile != nullptr)
            {
                std::fprintf(
                    g_pLogFile,
                    "Script_SpeedSprintProbe unloading after %u logged events.\n",
                    static_cast<unsigned>(g_EventOrdinal));
                std::fflush(g_pLogFile);
                std::fclose(g_pLogFile);
                g_pLogFile = nullptr;
            }
            break;
    }

    return TRUE;
}

#include "BehaviorProfiles.h"

#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>
#include <g3sdk/util/Memory.h>

#include <cstdio>

namespace
{
static mCCallHook Hook_CombatMoveIdentityProbe;
static FILE *g_pLogFile = nullptr;

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

bool TryMapActionProfile(
    gEAction action,
    G3AB::BehaviorProfiles::ActionProfile &profile)
{
    switch (action)
    {
        case gEAction_Attack:
            profile = G3AB::BehaviorProfiles::ActionProfile::Normal;
            return true;

        case gEAction_QuickAttack:
        case gEAction_QuickAttackR:
        case gEAction_QuickAttackL:
            profile = G3AB::BehaviorProfiles::ActionProfile::Quick;
            return true;

        default:
            return false;
    }
}

char const *GetActionProfileName(
    G3AB::BehaviorProfiles::ActionProfile profile)
{
    switch (profile)
    {
        case G3AB::BehaviorProfiles::ActionProfile::Normal:
            return "Normal";
        case G3AB::BehaviorProfiles::ActionProfile::Quick:
            return "Quick";
        default:
            return "Unknown";
    }
}

void GE_STDCALL CombatMoveIdentityProbe(
    gCScriptProcessingUnit::sAICombatMoveInstr_Args *a_pArgs,
    gCScriptProcessingUnit *a_pSPU)
{
    if (a_pArgs == nullptr || a_pSPU == nullptr || g_pLogFile == nullptr)
        return;

    Entity actor(a_pArgs->SelfEntity);
    if (actor == None || actor != Entity::GetPlayer())
        return;

    G3AB::BehaviorProfiles::ActionProfile actionProfile;
    if (!TryMapActionProfile(a_pArgs->Action, actionProfile))
        return;

    G3AB::BehaviorProfiles::ProfileKey key;
    gEUseType rawLeftUseType = gEUseType_None;
    gEUseType rawRightUseType = gEUseType_None;

    bool const keyBuilt = G3AB::BehaviorProfiles::TryBuildRuntimeKey(
        actor,
        actionProfile,
        key,
        rawLeftUseType,
        rawRightUseType);

    bCString const animationResourceName = actor.Animation.GetResourceName();

    std::fprintf(g_pLogFile, "===== SpeedIdentity =====\n");
    std::fprintf(
        g_pLogFile,
        "Action=%d\n",
        static_cast<GEInt>(a_pArgs->Action));
    std::fprintf(
        g_pLogFile,
        "ActionProfile=%s\n",
        GetActionProfileName(actionProfile));
    std::fprintf(
        g_pLogFile,
        "RequestedPhaseName=%s\n",
        a_pArgs->PhaseName.GetText());
    std::fprintf(
        g_pLogFile,
        "AnimationResourceName=%s\n",
        animationResourceName.GetText());
    std::fprintf(
        g_pLogFile,
        "RawLeftUseType=%d\n",
        static_cast<GEInt>(rawLeftUseType));
    std::fprintf(
        g_pLogFile,
        "RawRightUseType=%d\n",
        static_cast<GEInt>(rawRightUseType));
    std::fprintf(g_pLogFile, "RuntimeKeyBuilt=%s\n", keyBuilt ? "true" : "false");

    if (keyBuilt)
    {
        std::fprintf(
            g_pLogFile,
            "Key.AnimationFamily=%s\n",
            key.animationFamily.c_str());
        std::fprintf(
            g_pLogFile,
            "Key.LeftAnimationUseType=%s\n",
            key.leftAnimationUseType.c_str());
        std::fprintf(
            g_pLogFile,
            "Key.RightAnimationUseType=%s\n",
            key.rightAnimationUseType.c_str());

        G3AB::BehaviorProfiles::Profile const *profile =
            G3AB::BehaviorProfiles::Find(key);

        std::fprintf(
            g_pLogFile,
            "ProfileMatch=%s\n",
            profile != nullptr ? "true" : "false");

        if (profile != nullptr)
        {
            std::fprintf(
                g_pLogFile,
                "ProfileHasBaseSpeed=%s\n",
                profile->hasBaseSpeed ? "true" : "false");
            if (profile->hasBaseSpeed)
            {
                std::fprintf(
                    g_pLogFile,
                    "ProfileBaseSpeed=%.6f\n",
                    profile->baseSpeed);
            }
        }
    }

    std::fprintf(g_pLogFile, "=========================\n\n");
    std::fflush(g_pLogFile);
}
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    g_pLogFile = std::fopen("SpeedIdentityProbe.log", "w");
    if (g_pLogFile != nullptr)
    {
        std::fprintf(g_pLogFile, "Script_SpeedIdentityProbe loaded.\n");
        std::fprintf(g_pLogFile, "Loading production BehaviorProfiles implementation.\n\n");
        std::fflush(g_pLogFile);
    }

    G3AB::BehaviorProfiles::Load();

    Hook_CombatMoveIdentityProbe
        .Prepare(RVA_Game(0x16B065), &CombatMoveIdentityProbe)
        .InsertCall()
        .AddPtrStackArgEbp(0x8)
        .AddPtrStackArgEbp(0xC)
        .RestoreRegister()
        .Hook();

    if (g_pLogFile != nullptr)
    {
        std::fprintf(g_pLogFile, "CombatMove identity hook installed.\n\n");
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
                std::fprintf(g_pLogFile, "Script_SpeedIdentityProbe unloading.\n");
                std::fflush(g_pLogFile);
                std::fclose(g_pLogFile);
                g_pLogFile = nullptr;
            }
            break;
    }

    return TRUE;
}

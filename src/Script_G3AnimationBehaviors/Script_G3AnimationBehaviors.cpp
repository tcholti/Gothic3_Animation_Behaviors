#include "AttackRaise.h"
#include "AttackSpeed.h"
#include "SharedConfig.h"

#include <g3sdk/Script.h>

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

void LoadSettings()
{
    eCConfigFile config = eCConfigFile();

    if (config.ReadFile(bCString("G3AnimationBehaviors.ini")))
    {
        G3ABConfig::EnableTwoHandedNormalRaise =
            config.GetBool(
                bCString("Raise"),
                bCString("EnableTwoHandedNormal"),
                G3ABConfig::EnableTwoHandedNormalRaise);

        G3ABConfig::TwoHandedNormalAttackSpeed =
            config.GetFloat(
                bCString("AttackSpeed"),
                bCString("TwoHandedNormal"),
                G3ABConfig::TwoHandedNormalAttackSpeed);
    }
}

extern "C" __declspec(dllexport)
gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    // Ensure Script_Game.dll is available before installing hooks.
    GetScriptAdmin().LoadScriptDLL("Script_Game.dll");

    LoadSettings();

    InstallAttackRaiseHook();
    InstallAttackSpeedHook();

    return &GetScriptInit();
}

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD dwReason,
    LPVOID)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            ::DisableThreadLibraryCalls(hModule);
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

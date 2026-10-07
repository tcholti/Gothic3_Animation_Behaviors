#include "BadBlockProtectionResearch.h"

#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>

#include <cstdio>
#include <cstring>

#include <windows.h>

#ifndef G3AB_BADBLOCK_PROTECTION_MODE
#define G3AB_BADBLOCK_PROTECTION_MODE 1
#endif

#ifndef G3AB_BADBLOCK_EXCLUSION_PROBE
#define G3AB_BADBLOCK_EXCLUSION_PROBE 0
#endif

namespace
{
FILE *g_pLog = nullptr;

constexpr GEU32 DurationCallRva = 0x633BF;
constexpr GEU32 DurationGetterSlotRva = 0xE4990;
constexpr bool ProtectionEnabled = G3AB_BADBLOCK_PROTECTION_MODE != 0;
constexpr bool ExclusionProbeEnabled = G3AB_BADBLOCK_EXCLUSION_PROBE != 0;

// Win32 getter: original CharacterControl/property wrapper in ECX, result in EAX.
using DurationGetter = GEU32 (__thiscall *)(PSCharacterControl const *);
static_assert(sizeof(DurationGetter) == 4, "This seam requires the Win32 ABI.");

mCCallHook g_PlayerDurationCallHook;
// Installation transport only: no actor or timer state, and no IAT writes.
DurationGetter const volatile *g_pDurationGetterSlot = nullptr;

GEU32 GE_STDCALL PlayerDurationAdapter(PSCharacterControl const *receiver)
{
    // Preserve the original indirect call's current target and receiver once.
    DurationGetter const nativeGetter = *g_pDurationGetterSlot;
    GEU32 const rawDuration = nativeGetter(receiver);
    if (ExclusionProbeEnabled)
    {
        return BadBlockResearch::ObservePierceHackHitTimeout(
            rawDuration, receiver, g_pLog);
    }

    return BadBlockResearch::EvaluatePlayerHitTimeout(
        rawDuration, receiver, g_pLog, ProtectionEnabled);
}

void InstallPlayerDurationHook()
{
    if (g_PlayerDurationCallHook.IsActive())
        return;

    GetScriptAdmin().LoadScriptDLL("Script_Game.dll");
    HMODULE const scriptGame = ::GetModuleHandleA("Script_Game.dll");
    if (scriptGame == nullptr)
    {
        if (g_pLog != nullptr)
            std::fprintf(g_pLog, "Player timeout seam inactive: Script_Game unavailable.\n");
        return;
    }

    GEU32 const moduleBase = reinterpret_cast<GEU32>(scriptGame);
    GEU32 const slotAddress = moduleBase + DurationGetterSlotRva;
    unsigned char const *callSite =
        reinterpret_cast<unsigned char const *>(moduleBase + DurationCallRva);

    // Tested six-byte call [IAT], cmp eax,2500 and jbe +0x63586.
    // The absolute IAT operand is relocated with Script_Game's loaded base.
    unsigned char expected[] = {
        0xFF, 0x15, 0, 0, 0, 0,
        0x3D, 0xC4, 0x09, 0x00, 0x00,
        0x0F, 0x86, 0xB6, 0x01, 0x00, 0x00};
    std::memcpy(expected + 2, &slotAddress, sizeof(slotAddress));
    DurationGetter const volatile *slot =
        reinterpret_cast<DurationGetter const volatile *>(slotAddress);
    if (std::memcmp(callSite, expected, sizeof(expected)) != 0 || *slot == nullptr)
    {
        if (g_pLog != nullptr)
            std::fprintf(g_pLog, "Player timeout seam inactive: unsupported/conflicting timeout seam.\n");
        return;
    }

    g_pDurationGetterSlot = slot;
    // OnlyStack + AddThisArg passes ECX as a stdcall stack argument without
    // shared receiver storage. The decoder replaces the whole six-byte call;
    // the native comparison and conditional branch remain untouched.
    GEBool const installed = g_PlayerDurationCallHook
        .Prepare(moduleBase + DurationCallRva, &PlayerDurationAdapter)
        .AddThisArg()
        .Hook();
    if (g_pLog != nullptr)
        std::fprintf(
            g_pLog,
            "Player timeout seam +0x633BF: %s.\n",
            installed ? "installed" : "inactive");
}

void OpenLog()
{
    g_pLog = std::fopen("G3AB_BadBlockResearch.log", "w");
    if (g_pLog == nullptr)
        return;

    if (ExclusionProbeEnabled)
    {
        std::fprintf(
            g_pLog,
            "Script_G3AB_BadBlockResearch loaded.\n"
            "Mode: EXCLUSION PROBE (Pierce/Hack observe-only; native raw preserved).\n"
            "Research only: overdue player Action11/Action14 factual Hit seam.\n"
            "Production Script_G3AnimationBehaviors.dll may coexist in this frozen fixture.\n");
    }
    else
    {
        std::fprintf(
            g_pLog,
            "Script_G3AB_BadBlockResearch loaded.\n"
            "Mode: %s.\n"
            "Research only: overdue player Quick R/L and full Whirl Hit seam.\n"
            "Production Script_G3AnimationBehaviors.dll is intentionally independent.\n",
            ProtectionEnabled
                ? "PROTECTION (qualifying raw >2500 returns 2500)"
                : "CONTROL (observe only; native raw preserved)");
    }
    std::fflush(g_pLog);
}
void CloseLog()
{
    if (g_pLog == nullptr)
        return;

    std::fprintf(g_pLog, "Script_G3AB_BadBlockResearch unloading.\n");
    std::fflush(g_pLog);
    std::fclose(g_pLog);
    g_pLog = nullptr;
}
}

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    OpenLog();
    InstallPlayerDurationHook();
    if (g_pLog != nullptr)
        std::fflush(g_pLog);
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
            CloseLog();
            break;
    }
    return TRUE;
}

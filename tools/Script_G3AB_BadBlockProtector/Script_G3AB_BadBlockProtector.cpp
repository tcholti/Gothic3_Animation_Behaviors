#include <g3sdk/Script.h>
#include <g3sdk/util/Hook.h>

#include <cstring>

#include <windows.h>

namespace
{
constexpr GEU32 DurationCallRva = 0x633BF;
constexpr GEU32 DurationGetterSlotRva = 0xE4990;
constexpr GEU32 TimeoutMSecs = 2500;

using DurationGetter = GEU32 (__thiscall *)(PSCharacterControl const *);
static_assert(sizeof(DurationGetter) == 4, "This seam requires the Win32 ABI.");

mCCallHook g_PlayerDurationCallHook;
DurationGetter const volatile *g_pDurationGetterSlot = nullptr;

GEU32 EvaluatePlayerHitTimeout(
    GEU32 rawDuration,
    PSCharacterControl const *receiver)
{
    if (rawDuration <= TimeoutMSecs || receiver == nullptr)
        return rawDuration;

    eCEntityPropertySet *propertySet =
        receiver->m_pEngineEntityPropertySet;
    if (propertySet == nullptr)
        return rawDuration;

    eCEntity *actorInstance = propertySet->GetEntity();
    if (actorInstance == nullptr)
        return rawDuration;

    Entity const player = Entity::GetPlayer();
    if (actorInstance != player.GetInstance() || !player.Routine.IsValid())
        return rawDuration;

    switch (player.Routine.Action)
    {
        case gEAction_QuickAttackR:
        case gEAction_QuickAttackL:
        case gEAction_WhirlAttack:
            break;
        default:
            return rawDuration;
    }

    if (player.GetCurrentAniPhase() != gEPhase_Hit)
        return rawDuration;

    return TimeoutMSecs;
}

GEU32 GE_STDCALL PlayerDurationAdapter(PSCharacterControl const *receiver)
{
    DurationGetter const nativeGetter = *g_pDurationGetterSlot;
    GEU32 const rawDuration = nativeGetter(receiver);
    return EvaluatePlayerHitTimeout(rawDuration, receiver);
}

void InstallPlayerDurationHook()
{
    if (g_PlayerDurationCallHook.IsActive())
        return;

    GetScriptAdmin().LoadScriptDLL("Script_Game.dll");
    HMODULE const scriptGame = ::GetModuleHandleA("Script_Game.dll");
    if (scriptGame == nullptr)
        return;

    GEU32 const moduleBase = reinterpret_cast<GEU32>(scriptGame);
    GEU32 const slotAddress = moduleBase + DurationGetterSlotRva;
    unsigned char const *callSite =
        reinterpret_cast<unsigned char const *>(moduleBase + DurationCallRva);

    unsigned char expected[] = {
        0xFF, 0x15, 0, 0, 0, 0,
        0x3D, 0xC4, 0x09, 0x00, 0x00,
        0x0F, 0x86, 0xB6, 0x01, 0x00, 0x00};
    std::memcpy(expected + 2, &slotAddress, sizeof(slotAddress));

    DurationGetter const volatile *slot =
        reinterpret_cast<DurationGetter const volatile *>(slotAddress);
    if (std::memcmp(callSite, expected, sizeof(expected)) != 0 || *slot == nullptr)
        return;

    g_pDurationGetterSlot = slot;
    g_PlayerDurationCallHook
        .Prepare(moduleBase + DurationCallRva, &PlayerDurationAdapter)
        .AddThisArg()
        .Hook();
}
}

gSScriptInit &GetScriptInit()
{
    static gSScriptInit s_ScriptInit;
    return s_ScriptInit;
}

extern "C" __declspec(dllexport) gSScriptInit const *GE_STDCALL ScriptInit(void)
{
    InstallPlayerDurationHook();
    return &GetScriptInit();
}

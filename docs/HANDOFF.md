# Gothic 3 Animation Behaviors — Continuation Handoff

**Status:** Canonical continuation handoff  
**Date:** 2026-08-22

## 1. Authority Order

For a new implementation session/chat, use:

1. `docs/DESIGN.md` — current intended architecture.
2. `docs/RESEARCH_MAP.md` — current state and next work.
3. `docs/EVIDENCE_LEDGER.md` — fact/hypothesis status.
4. `docs/ANIMATION_RULES.md` — engine-facing animation semantics.
5. `docs/SOURCE_HOOK_GUIDE.md` — search/hook/build method.
6. current actual source files in `src/` and `prototypes/` once migrated.

If an old historical document conflicts with these, use the canonical files above.

## 2. Repository

Remote project:

`tcholti/Gothic3_Animation_Behaviors`

Local project root:

`E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\Gothic3_Animation_Behaviors`

### Official SDK dependency

`thirdparty/gothic3sdk`

Pinned:

`90bfd344de4510dda7ac9da7461cc7f1eac911f7`

### Jackydima reference

`references/jackydima-gothic3sdk`

Pinned:

`da61a791a97704ecebf166768c30564b6332d82d`

The Jackydima pin includes the 2026-08-20 WhirlAttack change that sets `PropertyResetOnUntouch = GETrue`.

## 3. Project Goal

Build a general Gothic 3 animation-behavior system that supports configurable Raise behavior, configurable attack playback speed, animation-authored frame collision, player and NPC use, and future expansion to additional actor families where source resolution is understood.

Preserve native behavior for unconfigured/unmarked cases.

## 4. Core Architecture in One Paragraph

Use the named native callback family + `gEPhase` + exact current motion marker for frame-collision ownership. Marker presence declares that exact execution frame-controlled, allowing the native timed activation in that callback to be suppressed before the marker fires. Read and log exact `gEAction` values, but do not add an action whitelist when callback + phase + marker already provide sufficient scope. When the marker is dispatched, invoke the appropriate source activation/rearm helper. Keep physical damage-source resolution separate from callback/phase identity.

## 5. Proven Raise State

2H normal Raise insertion is proven.

Mechanism:

`PREPEND_BREAK_BLOCK`

Result:

- correct P0/P1 Raise auto-resolved;
- original Hit preserved;
- original target preserved;
- pose cycle preserved;
- collision/Recover preserved.

Do not re-prove basic Raise feasibility.

## 6. Proven Speed State

Observed/proven:

- 1H normal Hit `0.600`
- 2H normal Hit `0.700`
- Quick Hit `1.000`
- Power Raise `1.500`
- Power Hit `1.000`

A `Script_Game + 0x42A0` modifier hook can override values, but conflicts with NewBalance when both own that path.

Production hook point remains to be finalized.

Project policy:

no user-facing RecoverSpeed; controlled Recover should follow effective Hit speed.

## 7. Proven Frame-Collision State

Confirmed:

- custom frame markers survive Blender -> xmot;
- exact live motion frame-effect list can be inspected;
- marker presence can declare ownership before marker time;
- Normal native timer can be suppressed for marked execution;
- marker can activate/rearm collision;
- normal weapon reset happens naturally at Hit -> Recover;
- ownership follows marker rather than pose;
- marker remains authored-frame synchronized under speed changes;
- Staff normal works for player;
- Staff normal works for human NPC.

Current prototype reference:

`Script_FrameCollisionTest v0.6`

## 8. Current QuickAttack Problem

Staff Quick markers fire.

Actions include QuickAttackR/L.

`v0.6` does not take ownership because the eligibility path still assumes literal Normal `_Attack_Hit_` naming.

Native collision therefore activates before the marker.

This is the immediate coding problem.

## 9. Exact Next Coding Step — FrameCollision v0.7

Preserve proven Normal code unchanged.

Add Quick support through:

- `OnAI_QuickAttack`;
- Hit phase;
- exact current-motion marker presence;
- the existing right-hand prototype source resolver.

Log Quick/QuickR/QuickL action values, but do not use them as an ownership whitelist.

Required behavior:

marked Quick execution with a valid right-hand source suppresses native timed activation and waits for the authored marker. Unmarked or unresolved executions call the original callback.

Staff is the first controlled animation/test case, not a Staff restriction in code. Do not mark Dual or Torch+1H Quick animations while `G3AB_COL_TEST` still means right-hand source.

## 10. Current Hand-Source Evidence

Preserve these distinctions for later source-explicit markers/general resolution:

- Dual P0 Normal: left.
- Dual P1 Quick: left.
- Dual P3 Quick file: should be left; runtime use unconfirmed.
- Dual P1 Pierce: left.
- Dual Power in Jackydima's current implementation: both.
- Torch+1H P1/P3 Quick: left torch.
- Some native Torch+1H P0 Normal left-torch activations are considered erroneous; Jackydima corrects regular Normal collision to the right weapon.
- Native Dual P0 Power left-source and one Dual finishing source remain unconfirmed.

Preferred future marker direction is generic source-explicit RIGHT/LEFT/BOTH/OFF across callback families. Names are not frozen.

## 11. v0.7 Validation

Player Staff Quick:

- no native `5 -> 7` before marker;
- marker triggers activation/rearm;
- both R/L variants work;
- natural reset after Hit.

NPC Staff Quick:

- same behavior on NPC's own equipped item.

Do not expand further until these pass.

## 12. Next Dedicated Fist Test

After Quick support:

remove only Fist `SetCollisionGroup`, keep `ClearTriggeredList`, and repeat controlled limb-contact tests.

Goal:

isolate whether Fist damage requires the weapon-style collision group at all.

## 13. Then

1. general source resolver;
2. production collision helper API;
3. freeze marker vocabulary;
4. migrate frame collision into `Script_G3AnimationBehaviors`;
5. generalize Raise;
6. implement safe profile-aware speed authority.

## 14. Code Files to Request From User Before Migration

The user will supply the actual latest code.

At minimum request/upload the latest real copies of:

- `Script_G3AnimationBehaviors.cpp`
- its `CMakeLists.txt`
- current config/INI parsing source if separate
- `Script_FrameCollisionTest.cpp` v0.6/latest
- FrameCollision prototype `CMakeLists.txt`
- any helper/header files those targets currently depend on
- latest CombatMove/collision logger source only if still needed for verification

Do not reconstruct these files from conversation memory if the user can provide the actual files.

## 15. Intended Repository Placement After Review

Likely structure:

```text
src/
    Script_G3AnimationBehaviors/
        CMakeLists.txt
        Script_G3AnimationBehaviors.cpp
        ...

prototypes/
    Script_FrameCollisionTest/
        CMakeLists.txt
        Script_FrameCollisionTest.cpp
        ...

config/
    G3AnimationBehaviors.ini

docs/
    DESIGN.md
    RESEARCH_MAP.md
    SOURCE_HOOK_GUIDE.md
    ANIMATION_RULES.md
    EVIDENCE_LEDGER.md
    HANDOFF.md
```

Do not force this structure if the actual source dependencies show a better minimal layout.

## 16. Runtime Test Environment

Gothic 3:

`E:\SteamLibrary\steamapps\common\Gothic 3`

DLL install:

`E:\SteamLibrary\steamapps\common\Gothic 3\scripts`

INI:

`E:\SteamLibrary\steamapps\common\Gothic 3\Ini`

For isolated collision tests, avoid loading old collision/logger DLLs unless that test explicitly requires them.

## 17. Collaboration Rules

- preserve proven work;
- one manageable change at a time;
- give exact paths/complete replacement files when implementation starts;
- distinguish confirmed from inferred;
- use animation-mod evidence as real engineering evidence;
- challenge unsupported assumptions;
- do not over-redesign working components;
- do not ask the user to repeat information already preserved in the project/docs/code.

## 18. Historical Documents

Older source documents remain useful for provenance but are not current authority:

- `Gothic_3_Scripting_Research_Implementation_Map_v0.2`
- `Gothic_3_Scripting_Source_Hook_Research_Guide_v0.1`
- old New-Chat Continuation Handoff
- old INI example
- old Design and INI Reference
- original Animation rules notes

Their durable knowledge has been migrated into the canonical documentation set.

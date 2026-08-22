# Gothic 3 Animation Behaviors — Source & Hook Guide

**Status:** Canonical practical research guide  
**Date:** 2026-08-20

## 1. Purpose

Use this guide to decide where to search, which source is authoritative for a particular question, which hook pattern has already worked, which addresses/symbols are useful, and when to build a logger instead of modifying behavior.

The Research Map records what is known. This guide records how to find the next missing fact safely.

## 2. Repository Roles

### Project repository

`Gothic3_Animation_Behaviors`

Local path:

`E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\Gothic3_Animation_Behaviors`

### Official SDK dependency

Project path:

`thirdparty/gothic3sdk`

Upstream:

`Georgeto/gothic3sdk`

Pinned project revision at documentation time:

`90bfd344de4510dda7ac9da7461cc7f1eac911f7`

Role:

- SDK declarations;
- enums;
- engine/script wrappers;
- hook utilities;
- official low-level definitions.

This is the build dependency unless a deliberate documented SDK fork becomes necessary.

### Jackydima reference source

Project path:

`references/jackydima-gothic3sdk`

Upstream:

`Jackydima/gothic3sdk`

Pinned project revision at documentation time:

`da61a791a97704ecebf166768c30564b6332d82d`

Role:

- current NewBalance/AttackCollision/Animation reference source;
- production-scale examples;
- compatibility target;
- recent collision behavior changes.

Do not silently replace the official SDK dependency with this fork.

### Historical local examples environment

Existing separate repository:

`E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\gothic3sdk-examples`

Role:

- older known-good prototype build environment;
- CombatMove logger;
- Raise prototype;
- FrameCollision prototypes.

Preserve it as historical/testing infrastructure until the latest code is migrated into this project.

## 3. Research Order

Before writing code:

1. define the exact runtime question;
2. search official SDK declarations;
3. search official/small examples for syntax;
4. search Jackydima current sources for real usage;
5. compare against controlled runtime logs;
6. compare against animation-file evidence;
7. build the smallest diagnostic if causality is still unclear;
8. modify behavior only after the owning layer is understood.

## 4. Source Evidence Hierarchy

### SDK declaration

Best for signatures, enums, fields, and exposed interfaces.

Limitation: does not prove internal engine behavior.

### Small SDK/example code

Best for known-good hook syntax, includes, CMake structure, and minimal patterns.

### Current Jackydima source

Best for working callbacks, practical source selection, collision rearm patterns, and current compatibility expectations.

### Commented/reconstructed reverse-engineering source

Best for architecture clues.

Never treat it as exact original engine source without runtime verification.

### Runtime diagnostic

Best for what the tested build actually does.

### Animation empirical evidence

Best for naming, pose transitions, fallback/lookup behavior, and asset-level rules.

Repeated animation-modding observations are engineering evidence.

## 5. Core Search Targets

### Native semantic enums

Search `GameEnum.h` for:

- `gEAction`
- `gEPhase`
- `gEAniState`
- `gEPose`
- `gEUseType`
- `gEDirection`

### Script Processing / CombatMove

Search `ge_scriptprocessingunit.h` for:

- `sAICombatMoveInstr_Args`
- `sAICombatMoveStart`
- `sAICombatMoveItlLoop`
- `sAICombatMoveStartRecover`
- state timing fields/context

### Script control flow

Search `gs_scriptmacros.h` for:

- `BREAK_BLOCK`
- `PREPEND_BREAK_BLOCK_BEGIN`
- `PREPEND_BREAK_BLOCK_END`

### Animation queries

Search SDK wrappers and Jackydima `Script_Animation` for:

- `GetAni`
- `GetAniEx`
- `GetAniName`
- `GetCurrentMovementAni`
- `GetCurrentAniPhase`
- `GetCurrentAniDirection`
- `GetPrimaryPoseExt`
- `FixAniDirection`

### Collision

Search Jackydima `Script_AttackCollision` for:

- `OnAI_Attack`
- `OnAI_QuickAttack`
- `OnAI_PowerAttack`
- `OnAI_PierceAttack`
- `OnAI_SimpleWhirl`
- `OnAI_WhirlAttack`
- `SetCollisionGroup`
- `ClearTriggeredList`
- `PropertyResetOnUntouch`
- left/right inventory slots

### Frame effects

Search for:

- `UpdateFrameEffects`
- `GetFrameEffectList`
- `eSFrameEffect`
- `StartEffect`
- motion descriptor/resource accessors

### Speed

Search for:

- `GetAnimationSpeedModifier`
- `AniSpeedScale`
- `m_fAniSpeedScale`
- `sAICombatMoveInstr`
- `PlayMotion`
- `GetMaxTime`

## 6. Known Hook / RVA Reference

Treat addresses as build-specific and reverify when the executable/SDK target changes.

| Area | Symbol / purpose | Known RVA / address |
|---|---|---|
| Action/phase speed | `GetAnimationSpeedModifier` | `Script_Game + 0x42A0` |
| Global attack speed example | `Script_AttackSpeed` | `Script_Game + 0x4D5B` |
| CombatMove animation-string point | known call hook | `Game + 0x16B065` |
| CombatMove reach/vector | known call hook | `Game + 0x16B8A3` |
| CombatMove movement | known call hook | `Game + 0x16B8A9` |
| Animation name | `GetAniName` | `Game + 0x16F840` |
| `GetAniEx` | animation query | `Script + 0x15C10` |
| Motion resource string | `GetMotionDataEntityAniString` | `Game + 0xD97D5` |
| Cached animation actor | `GetCachedMotionDataActor` | `Game + 0xDA344` |
| Action buffer | `AddAction` | `Script_Game + 0x7940` |
| Player action helper | `PopCurrentActionIfPlayer` | `Script_Game + 0x79A0` |
| Player action helper | `ClearNextActionsIfPlayer` | `Script_Game + 0x7A00` |
| Frame-effect update | `eCVisualAnimation_PS::UpdateFrameEffects` | `Game RVA 0x2EFF0` |
| Frame-effect list | `GetFrameEffectList` | `Game RVA 0x12E460` |
| Motion access | `eSMotionDesc::GetMotion` | `Game RVAs 0x2A0C0 / 0x2A0B0` |
| Effect dispatch | `gCEffectSystem::StartEffect` | `Game RVA 0x60850` |
| Entity collision group | `eCEntity::SetCollisionGroup` | `Game RVA 0x225660` |

## 7. Frame-Effect Structure

Confirmed runtime structure used by the prototype:

`eSFrameEffect`

- stride: 8 bytes
- offset `+0x00`: authored frame (`uint16`)
- offset `+0x04`: effect name (`bCString`)

Use this only with the exact tested engine build/layout.

## 8. Proven Hook Patterns

### Inserted call hook

The CombatMove logger used a call hook at the known CombatMove point.

Use when observation at a call site is enough and original behavior need not be replaced.

### Function hook with original fallback

Common pattern:

- inspect/filter;
- perform custom behavior when eligible;
- otherwise call original;
- or call original after a safe pre/post intervention.

### PREPEND_BREAK_BLOCK state hook

Proven for asynchronous Raise before the original melee state.

Use when the desired operation must complete before the untouched original state starts.

### Named AI callback hook

Preferred when Gothic 3 already provides a high-level attack callback containing the correct family semantics.

Current collision generalization should prefer callback family + exact action + phase + marker rather than dropping immediately to a lower-level generic hook.

## 9. Same-Function Hook Caution

Do not assume two independently loaded `mCFunctionHook` hooks on the same target function will chain safely.

This remains unresolved for the project.

Before shipping compatibility with NewBalance / Script_AttackCollision:

- inspect `Hook.h` / hook implementation;
- determine chaining semantics;
- avoid relying on load order;
- prefer one owner or a downstream intervention if necessary.

## 10. Current Collision Callback Knowledge

### `OnAI_Attack`

Proven Normal path in FrameCollision prototype.

### `OnAI_QuickAttack`

Relevant to:

- `gEAction_QuickAttack`
- `gEAction_QuickAttackR`
- `gEAction_QuickAttackL`

This is the immediate next callback family to integrate.

### `OnAI_PowerAttack`

Third-party source demonstrates both-hand behavior for Dual and repeated triggered-list clearing.

Pinned NewBalance also implements the Dual rearm independently:

- `scripts/Script_NewBalance/CallHook.cpp` defines `FixDualOneHanded`;
- it requires 1H in both hands and clears both weapon `TouchDamage` lists;
- it is inserted at `RVA_ScriptGame(0x482e7)`;
- the code comment identifies it as a Dual 1H PowerAttack hit-detection fix.

This proves the fix is present in NewBalance itself. The address is
build-specific, and source alone does not provide the authored-frame timing.

SDK `eCTrigger_PS` exposes `EntitiesVisited`, `EntitiesVisitedCount`,
`ClearTriggeredList()`, and `ClearTriggeredList(eCEntity *)`. Treat this as
structural evidence that visit suppression is tracked per target. Marked v0.10
2H testing already confirms that one cleared window can damage multiple distinct
opponents. Prioritize passive source/list-clear logging; add damaged-target
identity only if a later same-target rearm result cannot be interpreted
reliably from the clear sequence and observed damage.

### `OnAI_WhirlAttack`

Recent Jackydima source added `PropertyResetOnUntouch = GETrue` to the right-weapon Whirl activation path.

This is relevant evidence for repeated-contact/rearm behavior.

Current v0.10 marker limitation: motion scanning stops at the first matching
`G3AB_COL_TEST`, so `AuthoredMarkerFrame` reports that first frame even when the
same motion contains and dispatches a later marker with the same name. The
global `StartEffect` hook still receives and processes each dispatch, and each
accepted dispatch calls `ClearTriggeredList`. Count received/accepted marker
blocks and compare their `StateTime`; do not treat the repeated first-frame
label as evidence that the later marker failed to fire.

Observed complication: in the controlled frame-4/frame-15 fixture, frame 15
dispatched twice at identical `StateTime` on every one of four attacks. The
motion scan reported four total frame effects, matching two whooshes plus two
authored markers, so the repeated runtime call is not explained by a third
authored marker. Production should debounce an identical same-update dispatch
keyed by actor, current motion/execution, marker opcode, and source. Do not
collapse different simultaneous source opcodes; use BOTH when both hands are
intentionally authored together.

Validated v0.11 implements this as an actor-local last-accepted record. It
also includes action, phase, exact state time, and a maximum 5 ms wall-clock
window in the key. The check occurs before collision activation or list
clearing. This is deliberately a duplicate-dispatch guard, not a general marker
cooldown: a second authored contact at a later state time must still pass. In
six exact-fixture executions, the guard retained 12 genuine markers and ignored
six same-update late duplicates; every ignored callback performed no collision
or list mutation.

v0.12 adds a separate actor-local marker-owned weapon-window record for
provisional `G3AB_COL_OFF_TEST`. Accepted non-Fist ON stores actor + source +
motion + action + phase. OFF may request `Item_Equipped` only when that record
still matches and the source remains `Item_Attack`; it performs no list clear.
The global collision-group observer retires the record whenever the source is
no longer `Item_Attack`, covering both explicit OFF and natural reset. OFF-only
motions do not claim callback ownership because ON remains the declaration that
suppresses the native timer.

## 11. Current Marker-Control Research Pattern

At callback entry / Hit start:

1. derive current actor/action/phase;
2. access exact current motion;
3. scan that motion's frame-effect list;
4. if reserved marker absent: do not take ownership;
5. if present: suppress native timed activation for this execution;
6. when marker is dispatched through `StartEffect`, call the appropriate attack-family activation/rearm helper.

## 12. Diagnostic Design Rules

- change one variable per comparison;
- use one weapon/action family at a time;
- repeat enough times to distinguish pattern from input error;
- save logs before the next test overwrites them;
- test without target for pure sequencing, then with a stable target for collision/damage;
- use player + NPC tests for actor-general behavior;
- do not rely on visual hit impression when a collision-group/logger diagnostic is available.

## 13. Current Fist Causality Diagnostic

Preferred next isolated test after Quick support:

- remove only Fist `SetCollisionGroup`;
- keep `ClearTriggeredList`;
- suppress native timed activation as before;
- test multiple limbs.

Then invert if needed.

This isolates the logical rearm operation from a weapon-style collision-group operation.

## 14. Standalone Build/Test Workflow

The project repository is now the authoritative build workspace. The separate
`gothic3sdk-examples` checkout remains historical/reference infrastructure and
is no longer required for routine project builds.

From the `Gothic3_Animation_Behaviors` repository root:

```powershell
git submodule update --init --recursive
cmake -S . -B build -G "Visual Studio 17 2022" -A Win32
cmake --build build --config Release --target <TargetName>
```

Current build targets:

- `Script_G3AnimationBehaviors`
- `Script_FrameCollisionTest`
- `Script_FrameEffectLogger`
- `Script_CombatMoveLogger`

Build output and generated Visual Studio files remain under the ignored
repository-local `build/` directory. Build the source directly from this
repository; do not copy current source into the examples checkout.

## 15. Runtime Test Installation

Game scripts directory:

`E:\SteamLibrary\steamapps\common\Gothic 3\scripts`

Game INI directory:

`E:\SteamLibrary\steamapps\common\Gothic 3\Ini`

For isolated frame-collision tests, keep conflicting older collision DLLs removed unless the current test explicitly targets compatibility.

## 16. Code Migration Rule

When the latest actual `.cpp` files are supplied:

1. treat those files, not conversation reconstruction, as the authoritative code baseline;
2. preserve versioned proven prototypes;
3. move reusable behavior into the production module only after its test path is understood;
4. retain separate prototype history where it documents a proven experiment;
5. update this guide only when the search/hook method changes.

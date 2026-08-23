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

Runtime qualification: v0.12 physically proves OFF and later ON restoration,
but its actor-local last-accepted dedupe record is too narrow for interleaved
replay. The authored ON-f4/OFF-f10/ON-f15 motion dispatches `ON, OFF, ON` at the
late state time. All three pass because each differs from the immediately
previous marker.

Validated v0.13 uses two ordered guards:

1. retain v0.11 exact same-update identical-marker suppression;
2. consume one cached authored occurrence for that marker name.

The order matters. Layer one prevents an immediate duplicate ON from consuming
an occurrence intended for a later genuine ON. Layer two rejects interleaved
replay after the exact motion's authored count is exhausted. The execution key
is actor + source + motion + action + phase. State-time rollback starts a new
execution; natural collision cleanup after leaving the owning Hit retires the
record. This accepts the tested motion's two ON and one OFF operations without
requiring numbered marker names.

Performance contract: the exact frame-effect array is scanned once per
animation name and the result is cached. Each actor that fires a reserved
marker has at most one current execution record. Checks occur only in reserved
`StartEffect` callbacks; there is no per-frame actor/world scan. Release code
must disable or remove the prototype's verbose `fprintf` diagnostics.

Seven exact-fixture executions confirm the ordering. Each attack accepted the
early ON, intended OFF, and late ON; rejected the replayed OFF through the
occurrence budget; then rejected the final extra ON through the unchanged
same-update duplicate guard. Every rejected callback logged no collision-group
request and no triggered-list clear. Each new attack reset its actor execution
budget, and every late genuine ON received Gothic 3's natural cleanup.

A separate four-execution 2H Quick regression confirms the same ordering in the
Quick callback family: three QuickAttackR/action 4 and one QuickAttackL/action 5
each accepted two ON and one OFF, rejected the same two replay callbacks, and
naturally cleaned up. The first genuine ON performed the required Quick
StatePosition 0 -> 1 bookkeeping; the second genuine ON preserved 1 -> 1.
This validates reuse of the occurrence core across Normal and Quick while
keeping callback-family adapters explicit. It does not make Whirl eligible.

### v0.14 LEFT-first candidate

Source inspection now confirms that the left-hand operation is not a different
collision primitive. Jackydima's current `Script_AttackCollision` resolves
`gESlot_LeftHand`, requests `Item_Attack`, and clears that entity's triggered
list. Its Dual Power paths perform the corresponding operations on both slot
entities, and NewBalance `FixDualOneHanded` clears the two lists separately.
Therefore BOTH should be represented as a coordinated source set rather than
as a singular synthetic source.

The v0.14 candidate refactors the validated singular record into two fixed slot
snapshots and a two-bit active mask. It recognizes the preserved RIGHT alias
`G3AB_COL_TEST`, provisional LEFT `G3AB_COL_LEFT_TEST`, and existing OFF.
RIGHT/LEFT replace the exact marker-owned active set; OFF closes it. Authored
occurrence counts are independent per opcode. The callback preflight requires
every source named anywhere in the exact motion, preventing partial ownership
when a required slot is absent. BOTH remains disabled pending isolated LEFT and
RIGHT regression logs.

The LEFT runtime gate passed. A mixed session retained native behavior for an
unmarked P1 motion while two marked P0 motions used only LEFT. A second session
marked both P0 and P1 replacement motions LEFT: six P0 plus five P1 accepts
mapped one-for-one to 11 left 5 -> 7/list clears and 11 natural left 7 -> 5
resets, with no player right activation, duplicate rejection, occurrence-budget
rejection, or delayed reactivation. Since tested native P1 normally uses RIGHT,
this is direct evidence that callback ownership replaces the native source.
Do not enable BOTH until the preserved RIGHT marker path is regressed under the
same v0.14 refactor. That regression passed in four exact
RIGHT-f4/OFF-f10/RIGHT-f15 executions: two RIGHT accepts/clears, one OFF accept,
the expected occurrence/dedupe rejections, and right
`5 -> 7 -> 5 -> 7 -> 5` with no LEFT activation.

The subsequent Dual Normal exact-set test passed all complete executions:
29 attacks accepted RIGHT -> LEFT -> RIGHT or LEFT -> RIGHT -> LEFT and visibly
rearmed the same target for the third contact. It also found a marker-time
interruption hazard. Normal currently treats any current `_Attack_Hit_` filename
as Normal Hit. During one interruption, action had already changed to 59 while
the stale attack filename persisted, so a later RIGHT marker was accepted.
Before BOTH, change Normal marker eligibility to require all three conditions:

- the exact current motion is a marked Normal `_Attack_Hit_` motion;
- `Routine.PropertyAction == gEAction_Attack`;
- current animation phase is `gEPhase_Hit`.

Then force an interruption before a later marker and confirm that the marker is
consumed as unsupported without collision-group or triggered-list mutation.

v0.15 implements this as one shared `IsNormalAttackHit` predicate used by both
`OnAI_Attack` and `StartEffect`. The predicate requires
`gEAction_Attack`, `gEPhase_Hit`, and the current `_Attack_Hit_` motion. This
keeps the callback and marker gates identical and avoids maintaining a second
interruption mechanism. Build/install and valid-path regression passed. Damage
interruptions stopped later marker delivery, so the invalid-action rejection
branch was not directly observed at runtime.

The same test found a separate cache-lifetime edge: natural 7 -> 5 retirement
after only the first authored source marker can occur while action, phase, and
the stale Hit filename still match. If the next attack's first marker state
time is slightly greater, rollback-at-marker does not reset the occurrence
record. The next implementation should recognize this natural-retirement
boundary (or add an equivalent execution generation) while preserving the
existing rule that explicit OFF and exact-set switching do not retire the
current budget.

The v0.16 candidate uses both available event boundaries. While a marked
Normal/Quick callback is controlled, the cached record observes callback state
time and is retired on rollback before a later marker. For weapon sources, the
existing `SetCollisionGroup` hook independently treats rollback during natural
retirement of a still marker-owned source as an execution end. OFF and exact-
set switching publish an empty/replacement owned mask before requesting
`Item_Equipped`, so those intentional transitions do not trigger retirement.
The callback path is also relevant to logical/Fist sources, which deliberately
skip weapon `Item_Attack` group changes. Both checks are event-driven and add no
per-frame actor/world scan.

v0.16 runtime validation passed for the tested weapon path. Across 38 marked
executions, every natural marker-owned retirement removed exactly one cached
execution. The matrix contained 25 complete 2H Normal doubles, seven
first-RIGHT interruptions, four complete Quick doubles, and two complete Dual
alternating-source attacks. Every complete attack began with a fresh budget and
retained its later genuine contact. The controlled-callback rollback diagnostic
did not trigger in this session because natural weapon-source retirement
supplied the boundary; retain that callback path for Fist/logical sources.
Unmarked GetUpAttack/GetUpParade actions produced native collision diagnostics
but no reserved-marker dispatch.

The v0.17 candidate adds BOTH as one new opcode, not a new callback adapter.
`G3AB_COL_BOTH_TEST` contributes RIGHT|LEFT to exact-motion source preflight
and has its own authored-occurrence budget. At marker time the existing exact-
set transition publishes both bits, retires only sources outside that desired
set, then independently requests `Item_Attack` and clears the triggered list
for each equipped slot entity. Per-slot group/use-type/clear fields supplement
the preserved singular diagnostics. Missing either required slot keeps the
original Normal/Quick callback active. Fist/logical sources still skip the
weapon-group request; only successfully activated weapon bits remain in the
marker-owned window.

The first v0.17 runtime gate passed. Sixteen P0 Dual Normal executions each
accepted one authored BOTH occurrence and produced exactly two independent
group requests, two triggered-list clears, and marker-owned RIGHT|LEFT mask 3.
The right -> left -> right fixture visibly produced only the first two contacts,
as expected when the first weapon is not rearmed. Fifteen P1 alternating-marker
positive controls retained three accepted source occurrences and could produce
all three contacts. Repeated BOTH rearm then passed. Seventeen complete P0 executions accepted
BOTH -> BOTH -> BOTH and performed six source requests plus six list clears per
attack; all three intended same-target contacts were observed. Four P0 attacks
interrupted after the second BOTH reset both sources during Hit without
contaminating the next execution. Eleven complete P1 alternating-source
controls and one interrupted P1 retained expected behavior. Unmarked
GetUpAttack and side-Normal activity remained native; the suspected accidental
SimpleWhirl was not present in the log.

The missing-slot fallback passed separately. Ten P0 2H Normal BOTH callbacks
resolved RIGHT but not LEFT, retained the original callback, and consumed the
reserved marker as unsupported with zero custom group request or list clear.
Native timing independently produced ten right-source activations near state
time 0.25 and ten Recover resets. The all-or-nothing preflight therefore
prevents partial BOTH ownership in the tested path.

Mixed exact-set transitions also passed. In 28 complete controlled player
executions, P0 used BOTH -> LEFT -> OFF -> BOTH and P1 used
BOTH -> RIGHT -> OFF -> BOTH. LEFT/RIGHT replaced mask 3 with mask 2/1,
retired the opposite source, and rearmed the desired source. OFF deactivated
that single owned source without clearing. Final BOTH reactivated/cleared both.
Four interrupted executions remained valid prefixes. A multi-target follow-up
preserved the same ordering and observed damage across multiple opponents.

The overlapping NPC battle reproduced 19 complete and 20 interrupted valid
prefixes across PC_Hero, AssWarrior_07, and Silvio. Each actor resolved distinct
slot-entity addresses; no malformed or cross-actor sequence appeared. Actual
Power motions generated 66 reserved callbacks, all rejected at the
Normal/Quick context gate without acceptance. These logs are strong functional
stress evidence but not a performance benchmark: verbose prototype logging
dominates the session, and no frame-time comparison was recorded.

Do not infer Power support from globally received frame effects. v0.14 consumes
reserved marker names in real `PowerAttack_Hit` motions but rejects them at the
Normal/Quick context gate. The two probe logs contain 45 and 55 such rejected
Power callbacks; native Power independently activates both equipped weapons.
Test the same motion data under a Normal filename for source-set work, then add
a Power callback adapter as its own change.

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

The final planned pre-vocabulary Quick regression passed the same shared core.
Forty-seven fresh Dual Quick executions covered P0/P1 QuickAttackR and
QuickAttackL: 45 complete schedules and two valid prefixes ending after OFF.
P0 used BOTH -> LEFT -> OFF -> BOTH; P1 used
BOTH -> RIGHT -> OFF -> BOTH. Every first BOTH reset the occurrence budget and
performed the required Quick StatePosition 0 -> 1 update. Later side/BOTH
markers preserved 1 -> 1, exact-set transitions and OFF used the expected
masks, and no delayed native reactivation appeared after cleanup. This closes
the tested Normal/Quick shared-core gate before production marker spelling is
frozen. It does not authorize Whirl or Power callbacks.

The equipped-slot spelling is now frozen for v0.18:
`G3AB_COL_RIGHT`, `G3AB_COL_LEFT`, `G3AB_COL_BOTH`, and
`G3AB_COL_OFF`. The parser recognizes only these final names; historical
`*_TEST` spellings are not aliases. RIGHT/LEFT identify equipped slot sources,
and each source command remains an exact-set rearm operation. Use at most one
G3AB collision command per authored frame, use BOTH rather than simultaneous
RIGHT+LEFT, and keep OFF plus the next activation on separate frames. Final
body/unarmed/monster marker terminology remains outside this frozen subset.

v0.18 runtime validates the clean rename with no aliases. The log contains 24
complete final-name executions: 12 Normal and 12 Quick covering both poses and
all four tested QuickAttackR/L variants. Each accepted exactly
BOTH -> side -> OFF -> BOTH, began with a fresh budget, rejected the expected
two occurrence replays plus one same-update duplicate, and retired both sources
naturally. All Quick first markers performed StatePosition 0 -> 1; later source
markers preserved 1 -> 1. No `*_TEST` marker, unsupported final marker,
malformed sequence, or extra native player activation appeared.

For the next callback family, do not add generic filename permission. Map the
native `OnAI_WhirlAttack` entry plus exact action and Hit phase first. Confirm
whether 2H/Staff full Whirl and Dual SimpleWhirl share that callback before
deciding whether one adapter can own both. Preserve the validated marker parser,
source-set transition helper, occurrence guard, duplicate guard, and execution
cleanup unchanged.


For gameplay diagnosis, visible stumble is not a sufficient hit signal. Rapid
repeated contacts may reduce or remove the target's stumble response while
health still decreases, and close-overlap geometry can also produce genuine
misses. Keep those cases separate. If future callback-family tests require
per-contact certainty, extend the consolidated logger with a narrowly scoped
damage/health observer rather than inferring damage from animation response.

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

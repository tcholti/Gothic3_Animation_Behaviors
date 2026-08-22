# Gothic 3 Animation Behaviors — Continuation Handoff

**Status:** Canonical continuation handoff  
**Date:** 2026-08-22

## 1. Authority Order

For a new implementation session/chat, use:

1. `docs/DESIGN.md` — current intended architecture.
2. `docs/RESEARCH_MAP.md` — current state and next work.
3. `docs/EVIDENCE_LEDGER.md` — fact/hypothesis status.
4. `docs/ANIMATION_RULES.md` — engine-facing animation semantics.
5. `docs/ANIMATION_CATALOG.md` — exact animation families, examples, and author observations.
6. `data/animation_names/` — verbatim and generated searchable animation-name inventories.
7. `docs/SOURCE_HOOK_GUIDE.md` — search/hook/build method.
8. current actual source files in `src/` and `prototypes/` once migrated.

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

Use the named native callback family + exact `gEAction` + `gEPhase` + exact current-motion marker for frame-collision ownership. The named callback scopes native-timer suppression; when the marker later reaches global `StartEffect`, exact action and phase correlate it with the supported family without new per-execution state. Marker presence declares that exact execution frame-controlled. When dispatched, invoke the appropriate source activation/rearm helper. Keep physical damage-source resolution separate from callback/action/phase identity.

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

Validated baseline:

`Script_FrameCollisionTest v0.8` at commit `f4d2946`

v0.8 successfully configured and compiled as a standalone Win32 Release target on 2026-08-22. The installed DLL matched the built DLL at SHA-256 `18DDE8B770400C76709063FA0888EFEF888F41C2FE03B3449508BC43DA120858`. Controlled player Staff QuickAttackR/action 4, QuickAttackL/action 5, and marked Normal/action 1 all passed runtime validation. A controlled human-NPC session then confirmed two QuickAttackR/action 4 and five QuickAttackL/action 5 executions on `OutNovice_01` using its own `It_Halberd_01`; all seven passed the same marker/bookkeeping/reset checks.

Active causal-test source:

`Script_FrameCollisionTest v0.9` at commit `11f2a1b`

v0.9 retains the validated v0.8 behavior and skips only the weapon-style collision-group request when the resolved source raw UseType is Fist or PhysicalFist. Triggered-list clearing remains active.

Diagnostic-only v0.10 source at commit `6914039` preserves v0.9 behavior and adds exact player left/right equipped-entity labels to the passive global collision-group log. Its Win32 Release build passed on 2026-08-22 with only the pre-existing Windows SDK C5105 warning. The installed DLL matches the build at SHA-256 `647B8C36C0FEA9D16C898F069894028DE0769FF7C4D7A30A84DDE2F0422B0C6D`; the validated v0.9 rollback DLL is preserved at SHA-256 `16B2F35DBA817F344F24BADED3ABEA7ED5A237ACDCED631008CEAF675A9F3140`. Controlled unmarked player Dual runtime passed and produced the complete tested Normal/Quick/Pierce/Power slot map with paired activation/reset records.

Validated v0.11 at commit `0bbc377` preserves v0.10 behavior and adds only same-update duplicate-marker suppression. The guard runs after marker ownership and source resolution but before `SetCollisionGroup` or `ClearTriggeredList`. Its identity key is actor + resolved source + current motion + marker name + action + phase + state time, with a wall-clock window of at most 5 ms. Different state times remain independent authored contacts. Win32 Release build and installation passed at SHA-256 `F47EAD5B403DA701F32CCD23B2A2A429BDB16491DDE0864E0CF10CF76C78D154`; the validated v0.10 rollback is `647B8C36C0FEA9D16C898F069894028DE0769FF7C4D7A30A84DDE2F0422B0C6D`.

Build `89f36d8` failed because the script-layer `Entity` wrapper does not expose `GetUseType()`. Build `9b4a73c` failed because base `eCEntity` also has no member `GetUseType()`. Commit `11f2a1b` passes the `eCEntity*` from `Entity.GetInstance()` to the SDK-declared static `gCEntity::GetUseType(eCEntity*)` and compiled successfully. The installed v0.9 DLL matches the build at SHA-256 `16B2F35DBA817F344F24BADED3ABEA7ED5A237ACDCED631008CEAF675A9F3140`; the validated v0.8 rollback DLL is preserved. The completed player Fist matrix passed native left hand plus custom right hand, left leg, right leg, and head contacts.

## 8. QuickAttack Finding and Validated Fix

Staff Quick markers were previously confirmed to fire, with native QuickAttackR/L action values observed. v0.6 could not own them because its eligibility path assumed literal Normal `_Attack_Hit_` naming.

v0.7 proved pre-marker QuickR/L ownership but failed after reset because it left the callback one-shot gate at 0. v0.8 preserves the Normal callback body and adds only the missing accepted-Quick-marker bookkeeping. In the controlled player test, both Quick actions changed `StatePosition` 0 -> 1 at marker frame 6, naturally reset collision 7 -> 5, and produced no delayed unmarked 5 -> 7 reactivation. The controlled NPC test reproduced the corrected sequence on the NPC's own equipped Halberd, confirming that the fix is not player-specific.

## 9. v0.8 Implementation Contract

- `OnAI_QuickAttack` is hooked separately;
- exact Quick, QuickR, and QuickL actions plus Hit phase identify the Quick family at callback and marker time;
- exact current-motion marker presence declares ownership;
- the existing right-hand prototype source resolver is unchanged;
- unmarked, wrong-action/phase, or unresolved-source executions call the original Quick callback;
- there is no Staff, raw-UseType, or pose restriction;
- only an accepted Quick marker sets `Routine.PropertyStatePosition` to 1 and logs the before/after values;
- accepted Normal markers do not read or mutate this Quick bookkeeping.

The exact action check does not control animation resolution. It lets global `StartEffect` confirm that the later marker belongs to the Quick callback family whose native timer was suppressed.

Observed v0.7 behavior:

marked QuickR/L execution with a valid right-hand source suppresses pre-marker native activation and waits for authored marker frame 6. However, after the natural 7 -> 5 reset, the original Quick callback later reactivates 5 -> 7 because marker ownership did not complete the callback's one-shot state bookkeeping. v0.7 is therefore not a valid Quick implementation.

Staff is the first controlled animation/test case, not a Staff restriction in code. Do not mark Dual or Torch+1H Quick animations while `G3AB_COL_TEST` still means right-hand source.

## 10. Current Hand-Source Evidence

Controlled v0.10 player Dual runtime established:

- P0 Normal: left; P1 Normal: right.
- P0 QuickAttackR/L: right; P1 QuickAttackR/L: left.
- P0 Pierce: right; P1 Pierce: left.
- P0 and P1 Power: both initially; P0 visually contacts right -> left -> right and P1 left -> right -> left, so the first weapon needs later rearm for the third contact.
- native Dual Power is reported to damage only twice; both pinned NewBalance (`FixDualOneHanded`) and `Script_AttackCollision` contain later both-list clearing, plausibly enabling the third contact.
- every one of the 17 group-activation records had a matching 7 -> 5 reset in phase 3.
- Quick R/L action/filename direction did not select collision hand.
- SDK trigger state is per entity (`EntitiesVisited` / `EntitiesVisitedCount`); a NewBalance-enabled Normal/Quick swing has been observed hitting several distinct opponents, while the native baseline remains untested.
- current project behavior is stronger than that historical observation: with NewBalance and `Script_AttackCollision` absent, four marked 2H Normal attacks each logged one frame-7 activation/list clear and one natural reset; one observed swing hit three wolves and at least two hit two wolves. A marker clear therefore does not limit one active window to one target.

Preserve these remaining distinctions:

- Dual P3 Quick file should be left visually; runtime use remains unconfirmed.
- Dual has SimpleWhirl only, despite `WhirlAttack` in its filenames; source/contact intent and Power third-contact rearm remain untested.
- the separate full Whirl belongs to human 2H/Staff; ordinary 1H has none and hand-to-hand coverage is unknown.
- Torch+1H P1/P3 Quick: left torch.
- Some native Torch+1H P0 Normal left-torch activations are considered erroneous; Jackydima corrects regular Normal collision to the right weapon.
- One Dual finishing source remains unconfirmed.

Preferred future marker direction is generic source-explicit RIGHT/LEFT/BOTH/OFF across callback families. There is no separate ON marker: RIGHT/LEFT/BOTH each activate and rearm their named source set, while OFF creates a deterministic inactive gap by disabling marker-owned sources. Thus a same-weapon double attack can use RIGHT -> OFF -> RIGHT. This is especially needed for authored 2H/Staff double attacks whose second motion can touch a nearby target too early. Names and exact restoration rules are not frozen.

The same-target Normal isolation is complete. With one identical 2H double-
contact motion, native/no-marker and frame-4-only marker variants hit once;
frame-4 plus frame-15 markers hit the same opponent at both intended contacts.
The second source marker therefore rearms the weapon; OFF remains a timing-gap
feature. The later marker dispatched twice at the same `StateTime` in every
v0.10 attack. v0.11 retained two genuine contacts and ignored exactly one
same-update duplicate in each of six regression executions: 12 accepts, six
ignored duplicates, 12 clears, and six natural resets. Two-contact damage was
observed against two targets.

## 11. v0.8 Validation — PLAYER AND NPC PASSED

v0.7 baseline retained for comparison:

- player Staff marked Normal P0/P1 regression passed;
- player Staff QuickAttackR/action 4 and QuickAttackL/action 5 first activated at marker frame 6;
- no native 5 -> 7 occurred before those markers;
- v0.7 then failed because every natural 7 -> 5 reset was followed by an unmarked 5 -> 7.

v0.8 controlled player result:

- built and installed successfully; build/install SHA-256 matched;
- marked Staff QuickAttackR/action 4 activated only at marker frame 6;
- marked Staff QuickAttackL/action 5 activated only at marker frame 6;
- both Quick markers changed `StatePosition` 0 -> 1;
- each Quick activation naturally reset 7 -> 5;
- neither reset was followed by the v0.7 unmarked reactivation;
- one marked Staff Normal/action 1 retained marker-frame-5 activation and natural reset.

v0.8 controlled NPC result:

- actor `OutNovice_01` resolved its own `It_Halberd_01`;
- two QuickAttackR/action 4 and five QuickAttackL/action 5 executions were recorded;
- all seven changed `StatePosition` 0 -> 1 at marker frame 6;
- all seven activated 5 -> 7 and naturally reset 7 -> 5;
- no immediate post-reset reactivation occurred;
- other later unmarked collision cycles were separate native NPC attacks.

Staff QuickR/L validation is complete for the player and a human NPC. Generic Quick/action 3 remains untested because neither controlled session selected it.

## 12. FrameCollision v0.9 Fist Causal Matrix — PASSED

v0.9 compiled, was installed with a matching hash, and preserves the validated
v0.8 rollback DLL. It isolates raw `gEUseType_Fist` and
`gEUseType_PhysicalFist`: those sources skip the weapon-style
`SetCollisionGroup(Item_Attack)` request while retaining
`ClearTriggeredList`. Every non-Fist path is unchanged.

Exact player fixture:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R
Hero_Stand_None_Fist_P1_Attack_Recover_N_Fwd_00_%_00_P1_0_R
```

Completed focused-target contacts:

- native left hand — passed at marker frame 3;
- custom right hand — passed at marker frame 3;
- custom left leg — passed at marker frame 3;
- custom right leg — passed at marker frame 2; Blender inspection confirmed collision and whoosh were accidentally swapped (collision 2, whoosh 3);
- custom head — passed at marker frame 3.

All five visibly damaged the target. Every accepted path resolved Fist UseType
8, kept collision group 0 -> 0, skipped the group request, and cleared the
triggered list. The tested result is therefore conclusive: requesting the weapon
`Item_Attack` group is unnecessary for these hand/leg/head Fist contacts.
Production Fist handling should treat the logical Fist entity as a body-contact
rearm source rather than a right-hand weapon collision group.

Scope and limitations:

- this proves five player Fist/UseType-8 motions, not literally every body part;
- PhysicalFist/UseType 55 and monster bodies remain runtime-unproven;
- the right-leg marker was frame 2 rather than the planned frame 3, so the
  matrix is a source/contact proof rather than an identical timing comparison;
- the four focused-neutral custom-motion logs unload immediately after marker
  acceptance, so Recover completion and Hit -> Recover cleanup were not
  observed; no repeat is needed for the group-call causal result;
- a target that cannot be focused is invalid for Fist contact testing, even
  though a 2H weapon can hit the same unfocused allied setup;
- repeated unfocused attacks produced more accepted markers than fresh ownership
  decisions (5 versus 4 and 7 versus 5); that continuous-action relationship is
  separately unresolved and must not be assumed 1:1 in production.

The Fist causal matrix is complete. Do not build the inverse isolation unless a
future regression contradicts these positive results.

## 13. Then

1. implement a provisional OFF test marker under the proven Normal path and validate RIGHT/test marker -> OFF -> RIGHT/test marker using the same double-contact motion;
2. perform one Quick repeated-marker regression if useful. Do not test the actual Whirl callback with v0.11: its marker handler intentionally accepts only Normal/Quick Hit contexts;
3. add Whirl ownership separately, then validate 2H/Staff full-Whirl `ResetOnUntouch`, repeated contact, and explicit-OFF gaps using the same motion;
4. validate remaining human melee source families, beginning with Torch+1H and other left-source exceptions where needed;
5. add collision callback adapters one family at a time;
6. freeze marker vocabulary and migrate the validated collision core into `Script_G3AnimationBehaviors`;
7. generalize Raise and speed initially for Normal and Quick, using frame 0–12 inclusive for Hit (13 sampled frames) and frame 0–4 inclusive for Raise (5 sampled frames) as authoring conventions, with logger-measured native durations for speed calibration.

## 14. Repository and Build State

The source migration and standalone build migration are complete.

The project root owns the build through its top-level `CMakeLists.txt` and the
pinned official SDK submodule. Routine builds must use this repository directly,
not copied source in `gothic3sdk-examples`.

Validated configuration/build commands:

```powershell
git submodule update --init --recursive
cmake -S . -B build -G "Visual Studio 17 2022" -A Win32
cmake --build build --config Release --target Script_FrameCollisionTest
```

Validated v0.8 DLL output:

`build/prototypes/Script_FrameCollisionTest/Release/Script_FrameCollisionTest.dll`

Validated v0.8 build/install SHA-256:

`18DDE8B770400C76709063FA0888EFEF888F41C2FE03B3449508BC43DA120858`

## 15. Current Source Layout

- production: `src/Script_G3AnimationBehaviors/`
- active collision prototype: `prototypes/Script_FrameCollisionTest/`
- historical frame-effect proof: `prototypes/Script_FrameEffectLogger/`
- consolidated diagnostic logger: `tools/Script_CombatMoveLogger/`
- project configuration: `config/`
- canonical documentation: `docs/`
- animation-name inventories: `data/animation_names/`

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
- do not ask the user to repeat information already preserved in the project/docs/code;
- when new information materially affects future reasoning, record it in the appropriate canonical document or evidence ledger during the next logical documentation checkpoint.

## 18. Historical Documents

Older source documents remain useful for provenance but are not current authority:

- `Gothic_3_Scripting_Research_Implementation_Map_v0.2`
- `Gothic_3_Scripting_Source_Hook_Research_Guide_v0.1`
- old New-Chat Continuation Handoff
- old INI example
- old Design and INI Reference
- original Animation rules notes

Their durable knowledge has been migrated into the canonical documentation set.

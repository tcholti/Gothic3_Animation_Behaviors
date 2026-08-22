# Gothic 3 Animation Behaviors — Research Map

**Status:** Canonical engineering-state map  
**Date:** 2026-08-22  
**Supersedes:** the "current/next" state in the older v0.2 Research & Implementation Map and v0.1 handoff.

## 1. Purpose

This document records the current engineering state of the Gothic 3 Animation Behaviors project.

It separates confirmed facts, strongly supported findings, working hypotheses, unresolved questions, design decisions, completed milestones, and the immediate implementation sequence.

Historical documents remain useful source material, but this file is the current continuation map.

## 2. Evidence Vocabulary

- **CONFIRMED** — SDK/source verification, controlled runtime logging, or controlled behavior-changing test.
- **STRONGLY SUPPORTED** — repeated empirical animation-modding evidence and/or multiple converging observations.
- **WORKING HYPOTHESIS** — plausible explanation still requiring isolation.
- **UNKNOWN** — not sufficiently investigated.
- **DESIGN DECISION** — intended project behavior, not a claim about native engine behavior.

## 3. Current Project Priorities

### Priority A — Frame-controlled melee collision

Complete the generalized authored-frame collision mechanism while preserving correct source selection and native reset behavior.

### Priority B — Raise control

Move the proven Raise mechanism into the unified production system and generalize it carefully across intended human melee families.

### Priority C — Playback-speed control

Implement profile-aware speed authority that is compatible with existing mods and supports a consistent animation-timing standard.

### Later

- intended-target/crosshair enforcement;
- Recover interruptibility consistency if still needed;
- climbing and broader Gothic 3 scripting research.

## 4. Completed Milestones

### 4.1 Development and diagnostic foundation — COMPLETE

- Visual Studio 2022 / CMake / Win32 toolchain established.
- SDK/examples build path proven.
- CombatMove logger created and used successfully.
- multiple dedicated prototype DLLs created and tested.

### 4.2 CombatMove phase/speed baseline — COMPLETE

Confirmed tested values include:

- 1H Attack Hit `0.600`
- 2H Attack Hit `0.700`
- QuickAttack Hit `1.000`
- PowerAttack Raise `1.500`
- PowerAttack Hit `1.000`

Ordinary Recover visibly plays without appearing as a normal separate external CombatMove request in the original logger.

### 4.3 Raise proof of concept — COMPLETE

A previously unused 2H normal-Attack Raise was successfully prepended with `PREPEND_BREAK_BLOCK`.

The engine resolved the correct P0/P1 Raise automatically.

Original Hit, target propagation, collision, pose alternation, and Recover remained intact.

### 4.4 Initial speed override — COMPLETE AS PROOF

`Script_G3AnimationBehaviors v0.1` proved a Raise toggle for normal 2H, configurable normal 2H Hit speed, and that the stock 2H Hit modifier could be observed at `0.700` and overridden to `1.000`.

Compatibility with another mod using the same upstream speed hook is not solved.

### 4.5 Frame-effect reverse engineering — COMPLETE

Confirmed pipeline:

`custom authored frame effect in Blender -> exported .xmot -> eCVisualAnimation_PS::UpdateFrameEffects -> gCEffectSystem::StartEffect -> DLL marker recognition -> custom code at the authored frame`

### 4.6 Marker-driven collision proof — COMPLETE

Confirmed:

- exact current Hit motion can be inspected before marker fires;
- marker presence can declare custom ownership;
- native timed `OnAI_Attack` activation can be suppressed for that execution;
- marker can activate collision and clear the triggered list;
- marker ownership follows the marked exact animation rather than a hard-coded P0/P1 rule.

### 4.7 Natural weapon collision reset — COMPLETE

A hook on `eCEntity::SetCollisionGroup` confirmed the ordinary weapon path resets:

`5 -> 7` at activation, then `7 -> 5` at Hit -> Recover.

A mandatory end marker is not needed for ordinary single-hit attacks.

### 4.8 Playback-speed synchronization of marker — COMPLETE

For a tested 12-frame 2H normal Hit:

- marker frame stayed tied to the authored animation frame when playback speed changed;
- marker timing shifted in real time as expected with speed;
- marker-to-collision call delay was approximately `0.02–0.03 ms`.

### 4.9 Staff player test — COMPLETE

`Script_FrameCollisionTest v0.6` successfully controlled a Staff normal attack using the actor's actual right-hand Staff/Halberd item.

Natural reset also worked.

### 4.10 NPC Staff test — COMPLETE

A non-player human NPC using Hero-family Staff animations successfully used marker-controlled collision on its own equipped halberd.

This confirms the system is not inherently player-specific.

### 4.11 QuickAttack diagnostic — COMPLETE

Staff QuickAttack markers fire correctly.

Native action values observed include QuickAttackR and QuickAttackL.

`v0.6` still rejects those executions because its eligibility path is tied to the literal `_Attack_Hit_` Normal-attack naming assumption, so native collision occurs before the marker.

This is an implementation limitation, not a frame-marker limitation.

### 4.12 Fist/body-contact observation — COMPLETE

With marked Fist tests and native timed activation suppressed:

- left leg damage worked;
- right leg damage worked;
- right hand damage worked;
- left hand damage worked.

The same logical right-slot `Fist` entity was used, remained collision group `0`, and `SetCollisionGroup(Item_Attack)` did not visibly change that stored group.

## 5. Current Prototype State

### Script_G3AnimationBehaviors

Current known integrated proof version: `v0.1`.

Proven concepts:

- Raise configuration;
- speed configuration;
- game loads correctly alongside the separate frame-collision prototype.

### Script_FrameCollisionTest

Current validated prototype: `v0.8` at commit `f4d2946`.

Retained proven behavior:

- exact-motion marker ownership;
- marked Normal attack path;
- generalized player/NPC eligibility;
- Staff Normal;
- natural weapon collision reset;
- separate Quick/QuickR/QuickL callback/action/Hit eligibility;
- right-hand prototype source meaning;
- no Staff/UseType/Pose gate.

v0.7 runtime result:

- QuickR/action 4 and QuickL/action 5 first activated at marker frame 6;
- no pre-marker native activation occurred;
- after every natural 7 -> 5 reset, an unmarked 5 -> 7 reactivation occurred;
- v0.7 failed runtime validation.

v0.8 player runtime result:

- standalone Win32 Release build succeeded;
- installed DLL matched the build at SHA-256 `18DDE8B770400C76709063FA0888EFEF888F41C2FE03B3449508BC43DA120858`;
- QuickAttackR/action 4 and QuickAttackL/action 5 each activated only at marker frame 6;
- each accepted Quick marker changed `Routine.PropertyStatePosition` 0 -> 1;
- both executions naturally reset collision 7 -> 5 without the v0.7 post-reset reactivation;
- one marked Normal/action 1 regression retained marker-frame-5 activation and natural reset;
- no per-actor ownership state was introduced.

Player and human-NPC Staff QuickR/L validation are complete. In the NPC test, `OutNovice_01` produced two QuickAttackR/action 4 and five QuickAttackL/action 5 executions using its own `It_Halberd_01`; all seven passed marker, bookkeeping, and reset checks.

Current causal source candidate: `v0.9` at commit `11f2a1b`.

- identifies only raw `gEUseType_Fist` and `gEUseType_PhysicalFist`;
- skips `SetCollisionGroup(Item_Attack)` only for those resolved sources;
- keeps `ClearTriggeredList` unconditional;
- preserves Normal/Quick ownership and Quick StatePosition bookkeeping;
- logs the raw source UseType and whether the group request was skipped;
- leaves every non-Fist activation path unchanged.

Build `89f36d8` failed because the script-layer `Entity` wrapper has no `GetUseType()` member. Build `9b4a73c` then failed because the base `eCEntity` returned by `GetInstance()` also has no member `GetUseType()`. Commit `11f2a1b` uses the SDK-declared game-layer static resolver `gCEntity::GetUseType(eCEntity*)` and compiled successfully. The installed v0.9 DLL matches the successful build at SHA-256 `16B2F35DBA817F344F24BADED3ABEA7ED5A237ACDCED631008CEAF675A9F3140`; the validated v0.8 rollback copy remains preserved. Runtime contact validation is in progress: the native-motion left-hand baseline passed.

### Prototype marker

`G3AB_COL_TEST`

Status: proven research marker, not finalized production vocabulary.

## 6. v0.8 Implementation — PLAYER AND NPC RUNTIME PASSED

v0.8 keeps the v0.7 callback/action/phase/marker ownership model and completes
the Quick callback's one-shot bookkeeping only at accepted marker time.

The implementation remains intentionally narrow:

1. resolve Normal versus Quick marker context;
2. retain all ownership and source checks;
3. activate the right-hand prototype source and clear its triggered list;
4. for Quick only, set `PropertyStatePosition = 1`;
5. log Quick state position before and after;
6. leave Normal behavior unchanged.

The controlled player test confirms the predicted correction: both Quick markers
observed state position 0 and changed it to 1; neither natural 7 -> 5 reset was
followed by the v0.7 delayed 5 -> 7 reactivation. A controlled human-NPC test
then reproduced the corrected sequence seven times on the NPC's own equipped
Halberd. This promotes the fix's tested player/NPC behavior to **CONFIRMED**,
while the exact unobserved native callback internals behind the original defect
remain **STRONGLY SUPPORTED**.

The current `G3AB_COL_TEST` marker still means the actor's right-hand equipped
item. Do not mark Dual or Torch+1H Quick animations until explicit source
handling exists.

## 7. v0.8 Test Matrix

### Player Staff Quick — PASSED

Confirmed for QuickAttackR/action 4 and QuickAttackL/action 5:

- marker frame 6 performed the only 5 -> 7 activation;
- Quick StatePosition changed 0 -> 1;
- natural 7 -> 5 reset remained;
- no immediate post-reset 5 -> 7 occurred;
- the following attack began from collision group 5.

### Player Staff Normal regression — PASSED

One marked Normal/action 1 activated at marker frame 5 and naturally reset
7 -> 5. The separate Normal adapter remained compatible with the shared
activation/reset core.

### NPC Staff Quick — PASSED

For `OutNovice_01` using its own `It_Halberd_01`:

- QuickAttackR/action 4 occurred twice;
- QuickAttackL/action 5 occurred five times;
- all seven marker events changed StatePosition 0 -> 1;
- all seven activated 5 -> 7 and naturally reset 7 -> 5;
- no immediate post-reset reactivation occurred.

Other later unmarked collision cycles were separated native NPC attacks, not the
v0.7 same-execution reactivation.

Generic Quick/action 3 remains untested. Neither controlled player nor NPC
session selected it.

## 8. Fist Causal Test — LEFT- AND RIGHT-HAND PASSED; MATRIX IN PROGRESS

Current causal question:

Does `SetCollisionGroup(Item_Attack)` contribute to marked Fist damage, or is
triggered-list rearming the effective operation?

v0.9 obtains the base pointer with `source.GetInstance()` and passes it to the
SDK-declared game-layer resolver `gCEntity::GetUseType(eCEntity*)`. It changes
exactly one operation for a source whose raw UseType is `Fist` or
`PhysicalFist`:

- skip `SetCollisionGroup(Item_Attack)`;
- keep `ClearTriggeredList`.

Unchanged controls:

- exact-motion marker ownership;
- Normal callback suppression;
- right-slot source resolution;
- marker timing;
- all non-Fist group activation;
- Quick callback/bookkeeping code.

Build history:

- initial commit `89f36d8`: failed with MSVC C2039 because the script `Entity` wrapper has no `GetUseType()`;
- first correction `9b4a73c`: failed because base `eCEntity` also has no member `GetUseType()`;
- current correction `11f2a1b`: calls static `gCEntity::GetUseType(eCEntity*)`; Win32 Release build and hash-matched installation passed.

Required separate-launch runtime matrix:

All variants replace the same 8-frame Hit file:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R
```

All use the same Recover:

```text
Hero_Stand_None_Fist_P1_Attack_Recover_N_Fwd_00_%_00_P1_0_R
```

Controlled timing for every Hit variant:

- whoosh effect at frame 2;
- `G3AB_COL_TEST` at frame 3;
- all other Hit timing, filename, pose transition, target setup, and DLL unchanged;
- each variant may use a custom Recover beginning at its own final Hit pose and returning to idle;
- Recover motion/length may vary, but it must have no collision marker or intended test contact.

Run and preserve a separate log for:

1. native P0 motion/left-hand contact with the marker added;
2. custom right-hand contact;
3. custom left-leg contact;
4. custom right-leg contact;
5. custom head contact.

Completed contacts:

- native P0 left-hand motion visibly damaged the target;
- custom right-hand motion visibly damaged a focused neutral target;
- both successful marked paths resolved Fist UseType 8, skipped the group
  request, remained group 0 -> 0, and cleared the triggered list;
- therefore the group request is unnecessary for the tested left- and right-hand
  contacts.

Target/focus control:

- `invisibility` stopped preventing retaliation once the target was struck;
- two unfocused allied-human sessions produced no observed Fist damage despite
  12 accepted marked-P0 events and eight unmarked P1 legacy/native callbacks;
- a marked 2H control visibly damaged the unfocused allied setup after normal
  weapon activation 5 -> 7;
- this confirms that an unfocused allied target is unsuitable for the Fist
  matrix and strongly supports Fist-specific target/focus gating;
- use a focusable neutral target for left-leg, right-leg, and head tests.

The unfocused sessions also showed accepted marker counts greater than fresh
frame-controlled ownership decisions (5 versus 4 and 7 versus 5). Exact cause is
open; production design must not assume a strict 1:1 callback/marker count until
that continuous-action pattern is understood.

For every remaining launch, record whether contact damages and verify that the
log reports raw UseType 8 or 55, `SKIPPED_FOR_FIST_CAUSAL_TEST`, and
`TriggeredDamageList: CLEARED`.

If all controlled contacts still damage, the weapon-style group call is
unnecessary for the tested hand/leg/head contacts. If damage fails, the call
contributes despite the logical Fist entity remaining collision group 0.

Only if the result remains ambiguous should the inverse isolation be built:
restore the group call and remove only triggered-list clearing.

## 9. Source-Resolver Work After Quick + Fist

The production collision API must separate callback/action family, authored source choice, and physical body-contact mechanism.

Current animation/source evidence to preserve:

- Dual P0 Normal: left weapon.
- Dual P1 Quick: left weapon.
- Dual P3 Quick file: should be left visually; whether the game currently uses it is unconfirmed.
- Dual P1 Pierce: left weapon.
- Dual P0 Power may be left natively: working hypothesis.
- Dual Power in Jackydima's current implementation: both weapons activated and rearmed.
- Torch+1H P1 and P3 Quick: left torch.
- Some Torch+1H P0 Normal attacks natively use the left torch incorrectly; Jackydima's correction sends regular Torch+1H Normal collision to the right weapon.
- One Dual finishing animation may visually use both weapons; exact native source remains unconfirmed and one damaging source is acceptable for that animation.

Needed future validation still includes:

- 1H;
- Torch + 1H;
- Shield + 1H;
- Dual;
- 2H;
- Staff;
- Fist;
- multi-hit Power/Whirl;
- later monster-specific cases.

## 10. Production Marker Vocabulary — NOT FROZEN

Current preferred candidates are generic source-explicit markers such as RIGHT/LEFT/BOTH/OFF, shared across attack callback families.

They are not frozen. Do not mass-author them until source activation, OFF-state tracking, Fist/body behavior, and repeated-hit semantics are proven.

## 11. Raise Generalization — After Collision Core Stabilizes

Known starting point: 2H Normal works.

Likely controlled expansion:

1. 2H normal integrated into unified module;
2. Staff normal;
3. 2H/Staff Quick where Raise assets exist;
4. 1H family;
5. Torch + 1H;
6. Shield + 1H;
7. Dual;
8. selected Whirl/SimpleWhirl only where desired.

At each step verify resolved Raise, source/destination pose, Hit, Recover, speed, collision, and player/NPC behavior where relevant.

## 12. Speed-System Continuation

Current design goal:

- configure by animation family + normalized left/right animation UseTypes + action profile;
- preserve native behavior for missing profiles;
- apply custom speed only to matching profiles;
- avoid unsafe conflict with NewBalance's upstream speed hook.

Open implementation question:

What is the safest final point for production speed authority?

A downstream CombatMove `AniSpeedScale` intervention remains a leading option.

## 13. Recover Policy

Confirmed engine behavior:

ordinary Recover can start internally without appearing as a separate external CombatMove request.

Project design decision:

controlled Recover should follow the effective Hit speed and should not expose a separate user tuning key.

Separate issue:

Recover interruptibility has shown inconsistencies among attack variants and may later need a dedicated diagnostic.

## 14. Important Current Unknowns

1. Final production collision marker names.
2. General primary/secondary/all source resolver.
3. Exact Fist activation/rearm causality.
4. Safe compatibility strategy when multiple DLLs hook the same callback/function.
5. Final production speed-hook location.
6. Exact final INI syntax after current code is migrated.
7. Which Whirl/SimpleWhirl attacks should opt into Raise.
8. Multi-hit source/rearm semantics across all supported weapon families.
9. Monster-specific physical damage-source resolution.
10. Exact relationship among action R/L, final filename R/L, `Routine.HitDirection`, and victim reaction selection; no current implementation depends on it.

## 15. Superseded Earlier Continuation Points

The following old "next tasks" are historical, not current:

- first Recover-speed search;
- first collision ON/OFF comparison;
- first player-only 2H collision proof;
- Staff marker feasibility;
- NPC marker feasibility;
- whether marker timing remains synchronized when speed changes.

Those questions produced later results and should not be restarted unless a new regression specifically requires them.

## 16. Later Research

### Optional logical hit-direction diagnostic

CombatMoveLogger v0.4 does not currently log `Routine.HitDirection`. No current collision, Raise, or speed plan requires it.

If a later feature depends on reaction-side selection, extend the consolidated logger rather than creating a separate temporary DLL. The useful record should pair attacker action/pose/current motion and `HitDirection` with the victim's selected reaction action/current motion at the damage event. A controlled follow-up may force only HitDirection Left versus Right while preserving attack frames and collision.

### Intended target

Still relevant but outside the current immediate animation-behavior core.

Distinct concepts remain FocusEntity, CurrentTarget, AlternativeTarget, AlignmentTarget, action target, CombatMove TargetEntity, and SPU context entities.

### Climbing

Long-term separate Gothic 3 scripting investigation. Not part of the current combat implementation.

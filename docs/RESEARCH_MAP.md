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

For a tested 2H normal Hit authored from frame 0 through frame 12 inclusive (13 sampled frames):

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

Build `89f36d8` failed because the script-layer `Entity` wrapper has no `GetUseType()` member. Build `9b4a73c` then failed because the base `eCEntity` returned by `GetInstance()` also has no member `GetUseType()`. Commit `11f2a1b` uses the SDK-declared game-layer static resolver `gCEntity::GetUseType(eCEntity*)` and compiled successfully. The installed v0.9 DLL matches the successful build at SHA-256 `16B2F35DBA817F344F24BADED3ABEA7ED5A237ACDCED631008CEAF675A9F3140`; the validated v0.8 rollback copy remains preserved. Runtime contact validation is complete: the native left hand and custom right hand, left leg, right leg, and head all passed. The right-leg fixture's collision effect was accidentally authored on frame 2 and its whoosh on frame 3; this does not change the Fist source conclusion.

Current diagnostic candidate: `v0.10` at commit `6914039`.

- marked Normal/Quick ownership and activation behavior remain v0.9;
- the global `SetCollisionGroup` observer now compares the changed entity pointer with the player's exact left- and right-slot entity pointers;
- every transition involving `Item_Attack` is labelled `LEFT`, `RIGHT`, `BOTH`, `NONE`, or `NO_PLAYER` and includes current player action, phase, primary pose, state time/position, animation, and both slot snapshots;
- no Pierce, Power, SimpleWhirl, or Whirl callback is newly intercepted for behavior;
- Win32 Release compilation passed on 2026-08-22 with only the pre-existing Windows SDK C5105 warning;
- installed/build SHA-256 matches at `647B8C36C0FEA9D16C898F069894028DE0769FF7C4D7A30A84DDE2F0422B0C6D`;
- validated v0.9 rollback SHA-256 is `16B2F35DBA817F344F24BADED3ABEA7ED5A237ACDCED631008CEAF675A9F3140`;
- controlled unmarked player Dual runtime passed: exact slot labels produced the complete Normal/Quick/Pierce/Power source map and paired activation/reset records.

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

## 8. Fist Causal Test — COMPLETE AND PASSED

Question answered: `SetCollisionGroup(Item_Attack)` is unnecessary for the
five tested player Fist body contacts when the logical Fist source is rearmed by
clearing its triggered-damage list.

Validated v0.9 branch:

- raw Fist/PhysicalFist detection uses static
  `gCEntity::GetUseType(eCEntity*)`;
- Fist/PhysicalFist skips the weapon-style group request;
- `ClearTriggeredList` remains active;
- all non-Fist marker paths remain unchanged.

Passed contact motions:

1. native left hand — marker frame 3;
2. custom right hand — marker frame 3;
3. custom left leg — marker frame 3;
4. custom right leg — marker frame 2;
5. custom head — marker frame 3.

All five visibly damaged a focused target while the accepted marker resolved
UseType 8, kept group 0 -> 0, skipped the group request, and cleared the list.
The right-leg frame-2 marker is a controlled-fixture deviation, but a positive
result still proves that the omitted group request was not required for that
contact.

Production consequence:

- distinguish weapon activation from Fist/body rearming in the collision helper;
- a Fist marker should rearm the logical Fist source without requesting
  `Item_Attack`;
- keep claims limited to the tested player Fist contacts;
- separately validate PhysicalFist 55 and monster-specific body sources when
  those families are implemented.

Limitations retained:

- the four focused-neutral custom-motion sessions may have ended before Recover
  completed, so they are not Recover/reset tests;
- unfocused allied humans are invalid Fist targets;
- accepted-marker counts exceeded fresh ownership decisions in repeated
  unfocused input, whose callback/action-state cause remains open.

No inverse isolation is required unless later evidence contradicts the positive
matrix.

## 9. Source-Resolver Work After Quick + Fist

The production collision API must separate callback/action family, authored source choice, and physical body-contact mechanism.

Controlled v0.10 player Dual runtime source map:

- P0 Normal: left weapon.
- P1 Normal: right weapon.
- P0 QuickAttackR and QuickAttackL: right weapon.
- P1 QuickAttackR and QuickAttackL: left weapon.
- P0 Pierce: right weapon.
- P1 Pierce: left weapon.
- P0 and P1 Power: both weapons.
- all 17 activation records had paired 7 -> 5 resets in phase 3.

The Power group result contradicts the earlier P0-left-only recollection and
converges with Jackydima's initial BOTH activation. It does not prove all three
visual contacts can damage: P0 is right -> left -> right and P1 is left -> right
-> left, while native behavior is reported to damage only twice. The first
weapon must be rearmed for its second contact. Jackydima later clears both lists
again; v0.10 did not observe that operation.

Other source evidence to preserve:

- Dual P3 Quick file: should be left visually; whether the game currently uses it is unconfirmed.
- Dual has SimpleWhirl only; its files use the `WhirlAttack` name token and its exact source/contact intent remains to be tested.
- Jackydima's SimpleWhirl code uses left in Dual P1 and right otherwise.
- Human 2H/Staff have the separate full Whirl; Jackydima activates right and enables `PropertyResetOnUntouch`.
- ordinary human 1H families have no Whirl; hand-to-hand coverage remains unknown.
- Torch+1H P1 and P3 Quick: left torch.
- Some Torch+1H P0 Normal attacks natively use the left torch incorrectly; Jackydima's correction sends regular Torch+1H Normal collision to the right weapon.
- One Dual finishing animation may visually use both weapons; exact native source remains unconfirmed and one damaging source is acceptable for that animation.

Needed future validation still includes:

- 1H;
- Torch + 1H;
- Shield + 1H;
- 2H;
- Staff;
- Fist beyond the completed player UseType-8 matrix;
- Dual SimpleWhirl source/contact intent and Dual Power third-contact rearm;
- separate 2H/Staff full-Whirl recontact/`ResetOnUntouch` behavior;
- later monster-specific cases.

## 10. Dual Normal/Quick/Pierce/Power Source Discovery — COMPLETE

The controlled targetless player session used unmarked Dual animations, two
distinct equipped 1H entity instances, seven Normal attacks for stance changes,
both Quick variants in P0 and P1, two Block prerequisites, both Pierce poses,
and both Power poses.

| Tested execution | Logged source |
|---|---|
| P0 Normal | LEFT |
| P1 Normal | RIGHT |
| P0 QuickAttackR | RIGHT |
| P0 QuickAttackL | RIGHT |
| P1 QuickAttackR | LEFT |
| P1 QuickAttackL | LEFT |
| P0 Pierce | RIGHT |
| P1 Pierce | LEFT |
| P0 Power | RIGHT + LEFT |
| P1 Power | RIGHT + LEFT |

Every activation had a paired 7 -> 5 reset in phase 3. Pierce collision and
cleanup passed; Pierce Recover is known-good and is not a project issue or
follow-up target.

Next Dual work is SimpleWhirl plus Power multi-contact rearming. Dual does not
have the separate full Whirl used by 2H/Staff. The diagnostic must observe
`ClearTriggeredList`, because first group activation alone cannot distinguish
native two-hit Power from the intended three-contact sequence. It should also
record damaged-target identity: SDK structure exposes per-entity visited state,
and the tester's NewBalance-enabled setup allows one Normal/Quick swing to hit
several different opponents, but the native baseline is unknown. Pinned
NewBalance independently clears both Dual weapon lists through
`FixDualOneHanded`, so the rearm fix is not exclusive to
`Script_AttackCollision`. Separate later 2H/Staff Whirl work should observe
`ResetOnUntouch` and OFF-gap needs.

## 11. Production Marker Vocabulary — NOT FROZEN

Current preferred candidates are generic source-explicit markers such as RIGHT/LEFT/BOTH/OFF, shared across attack callback families.

Current proposed responsibilities:

- RIGHT/LEFT/BOTH activate and rearm the named source set for that authored
  contact;
- OFF deactivates the source set owned by the current marked execution;
- OFF does not clear lists by itself; the next source marker performs the
  rearm.

This separation is important for custom 2H/Staff double attacks: explicit OFF
can prevent a nearby target from being struck by the second weapon motion before
its intended acceleration, while the next ON marker opens a clean second
contact window.

They are not frozen. Do not mass-author them until source activation, OFF-state tracking, Fist/body behavior, and repeated-hit semantics are proven.

## 12. Raise Generalization — After Collision Core Stabilizes

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

## 13. Speed-System Continuation

Current design goal:

- configure by animation family + normalized left/right animation UseTypes + action profile;
- preserve native behavior for missing profiles;
- apply custom speed only to matching profiles;
- avoid unsafe conflict with NewBalance's upstream speed hook.

Open implementation question:

What is the safest final point for production speed authority?

A downstream CombatMove `AniSpeedScale` intervention remains a leading option.

## 14. Recover Policy

Confirmed engine behavior:

ordinary Recover can start internally without appearing as a separate external CombatMove request.

Project design decision:

controlled Recover should follow the effective Hit speed and should not expose a separate user tuning key.

Separate issue:

Recover interruptibility has shown inconsistencies among attack variants and may later need a dedicated diagnostic.

## 15. Important Current Unknowns

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

## 16. Superseded Earlier Continuation Points

The following old "next tasks" are historical, not current:

- first Recover-speed search;
- first collision ON/OFF comparison;
- first player-only 2H collision proof;
- Staff marker feasibility;
- NPC marker feasibility;
- whether marker timing remains synchronized when speed changes.

Those questions produced later results and should not be restarted unless a new regression specifically requires them.

## 17. Later Research

### Optional logical hit-direction diagnostic

CombatMoveLogger v0.4 does not currently log `Routine.HitDirection`. No current collision, Raise, or speed plan requires it.

If a later feature depends on reaction-side selection, extend the consolidated logger rather than creating a separate temporary DLL. The useful record should pair attacker action/pose/current motion and `HitDirection` with the victim's selected reaction action/current motion at the damage event. A controlled follow-up may force only HitDirection Left versus Right while preserving attack frames and collision.

### Intended target

Still relevant but outside the current immediate animation-behavior core.

Distinct concepts remain FocusEntity, CurrentTarget, AlternativeTarget, AlignmentTarget, action target, CombatMove TargetEntity, and SPU context entities.

### Climbing

Long-term separate Gothic 3 scripting investigation. Not part of the current combat implementation.

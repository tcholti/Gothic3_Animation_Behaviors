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

Current known prototype: `v0.6`.

Proven:

- exact-motion marker ownership;
- normal attack path;
- generalized player/NPC eligibility;
- Staff normal;
- natural weapon collision reset.

Current limitation:

- Normal-specific eligibility still blocks QuickAttack ownership.

### Prototype marker

`G3AB_COL_TEST`

Status: proven research marker, not finalized production vocabulary.

## 6. Immediate Next Implementation — v0.7

Preserve the proven Normal path unchanged.

Add QuickAttack frame-collision ownership by:

1. using `OnAI_QuickAttack`;
2. accepting exact actions:
   - `gEAction_QuickAttack`
   - `gEAction_QuickAttackR`
   - `gEAction_QuickAttackL`
3. requiring `gEPhase_Hit`;
4. inspecting the exact current Hit motion for the marker;
5. suppressing native QuickAttack timed activation only when that exact motion is marked and the prototype source resolves;
6. letting the authored marker trigger the collision operation.

The action check is not used for animation resolution. It lets the later global `StartEffect` handler correlate the marker with the Quick callback family without adding per-actor/per-execution ownership state.

The current `G3AB_COL_TEST` prototype marker continues to mean the actor's right-hand equipped item. Staff is the first controlled asset/test case, but there is no Staff restriction in the callback code. Dual and Torch+1H Quick animations remain unmarked/native until explicit left/right source markers or equivalent source handling are implemented.

QuickAttackR/QuickAttackL and final filename R/L are logical direction evidence, not physical hand-source selectors. They must not replace explicit RIGHT/LEFT/BOTH collision-source handling.

## 7. v0.7 Test Matrix

### Player Staff Quick

Required observations:

- no native `5 -> 7` before marker;
- marker causes activation/rearm at authored frame;
- QuickAttackR and QuickAttackL both work;
- natural reset occurs after Hit.

### NPC Staff Quick

Repeat with a controlled human NPC.

Required result:

same authored-frame behavior on the NPC's own equipped Staff/Halberd.

## 8. Fist Causal Test — Next Dedicated Diagnostic

Current question:

Does `SetCollisionGroup(Item_Attack)` contribute to marked Fist damage, or is triggered-list rearming the effective operation?

Preferred controlled test:

1. keep frame ownership and native suppression unchanged;
2. remove only the Fist `SetCollisionGroup` call;
3. keep `ClearTriggeredList`;
4. repeat controlled contact tests with left leg, right leg, right hand, and left hand.

If damage remains, `SetCollisionGroup` is likely irrelevant for the Fist path.

Then, if useful, perform the inverse test: keep the group call while removing the triggered-list clear.

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

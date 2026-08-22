# Gothic 3 Animation Behaviors — Design

**Status:** Canonical working design  
**Date:** 2026-08-22  
**Project:** `Gothic3_Animation_Behaviors`

## 1. Purpose

`Script_G3AnimationBehaviors` is intended to provide a general animation-behavior layer for Gothic 3 that can support rebuilt combat animations without forcing them to conform to legacy timing assumptions.

The current system has three primary behavior domains:

1. Raise-phase control.
2. Attack playback-speed control.
3. Authored-frame collision control.

The design must preserve Gothic 3's native animation/action resolution wherever possible and intervene only when a configured profile or authored animation explicitly opts in.

## 2. Scope

The system is actor-general by design.

`Hero` is an animation-family identifier used by compatible human actors; it is not a player-only selector. The frame-collision mechanism must also remain technically usable by other animation families, including monsters, when their animations and physical damage sources are understood.

Current practical development emphasis is human melee because that is the animation set being rebuilt and tested first.

Unconfigured profiles and unmarked animations must retain native behavior.

## 3. Design Principles

### DP-01 — Native semantics first

Use Gothic 3's native `gEAction`, `gEPhase`, `gEAniState`, `gEPose`, raw `gEUseType` plus its animation UseType mapping, and current resolved motion/animation context.

Do not make filename substring parsing the sole authority when the engine already exposes the semantic state directly.

### DP-02 — Preserve engine animation resolution

Do not manually construct exact P0/P1/P2/P10/etc. animation filenames when Gothic 3 can resolve the correct animation from the current actor, pose, action, phase, direction, and use types.

### DP-03 — Opt-in behavior

Speed/Raise behavior is controlled by configuration.

Frame collision is controlled by a reserved frame marker embedded in the exact animation motion.

Missing configuration or missing marker means the corresponding custom behavior does not take ownership.

### DP-04 — Separate attack family from physical damage source

The current action/callback determines the broad attack mechanism.

The physical source that can damage a target is a separate concern.

Examples include the right-hand weapon, left-hand weapon, both equipped weapons, a logical unarmed/Fist source whose contact comes from body collision geometry, and future monster-specific body/limb/head sources.

A generic `Hit` label does not identify the physical damage source.

### DP-05 — Preserve proven paths while expanding

Add one action family/callback at a time. Do not rewrite a proven Normal-attack path while adding QuickAttack support.

### DP-06 — Controlled fallback

If a custom rule does not intentionally apply, preserve original behavior.

### DP-07 — Configuration is loaded once

Parse configuration at initialization into normalized in-memory rules. Do not repeatedly parse the INI during attacks.

### DP-08 — Evidence before generalization

Player tests alone are insufficient for an actor-general feature. Important behavior must be checked with both controlled player and NPC cases where applicable.

## 4. Configuration Identity

The configuration concept is indexed by:

`AnimationFamily + LeftAnimationUseType + RightAnimationUseType + ActionProfile`

The exact textual INI syntax is not frozen until the current code is migrated into this repository.

### 4.1 Animation UseType normalization

Raw `gEUseType` is not always the same as the animation token.

Examples:

- `gEUseType_Axe` -> `2H`
- `gEUseType_Pickaxe` -> `2H`
- `gEUseType_Halberd` -> `Staff`
- `gEUseType_Rake` -> `Staff`
- `gEUseType_Shovel` -> `Staff`
- `gEUseType_Broom` -> `Staff`
- `gEUseType_Fan` -> `Staff`
- `gEUseType_PhysicalFist` -> `Fist`

The full known mapping is maintained in `ANIMATION_RULES.md`.

### 4.2 Action profiles

Configuration may group closely related native actions for user-facing simplicity, but runtime implementation must still identify the exact `gEAction` where the global marker dispatcher needs to correlate an authored marker with a supported callback family.

For v0.7 Quick collision, `OnAI_QuickAttack` scopes native-timer suppression at callback time. The marker fires later through global `StartEffect`, which does not receive the earlier callback identity. Exact Quick/QuickR/QuickL action values are therefore the smallest stateless correlation mechanism. A future per-execution ownership record could replace this check, but would add state and cleanup complexity.

Minimum intended groups:

- **Normal**: `gEAction_Attack`
- **Quick**: `gEAction_QuickAttack`, `gEAction_QuickAttackR`, `gEAction_QuickAttackL`

Likely future groups include PowerAttack, SimpleWhirl, WhirlAttack, PierceAttack, and other actions only when their behavior is deliberately supported.

## 5. Raise Architecture

A normal 2H Attack Raise has already been successfully inserted by hooking the original melee state and using `PREPEND_BREAK_BLOCK`.

This preserves the original state after the inserted asynchronous Raise completes.

The proven sequence is conceptually:

`custom Raise -> original state -> original Hit -> native continuation`

The engine resolves the correct P0/P1 Raise animation automatically.

Raise should be enabled only for matching configured profiles/actions. The production system should reuse the proven prepend mechanism where it is the highest-level sufficient intervention.

Actions that already have valid native Raise behavior, such as existing PowerAttack cases, should not be needlessly reconstructed.

## 6. Playback-Speed Architecture

### 6.1 Proven facts

`AniSpeedScale` participates in actual animation duration.

The tested stock/configured values include:

- 1H normal Hit: `0.600`
- 2H normal Hit: `0.700`
- QuickAttack Hit: `1.000`
- PowerAttack Raise: `1.500`
- PowerAttack Hit: `1.000`

An upstream action/phase-aware modifier hook at `Script_Game + 0x42A0` has also been proven.

### 6.2 Production goal

Speed authority should be limited to matching configured profiles and phases.

The current design preference is to avoid globally replacing values for unrelated actors/attacks.

### 6.3 Compatibility

The current upstream speed hook conflicts with NewBalance/other code that hooks the same speed-modifier path.

A production implementation should prefer the safest point that allows matching-profile authority without depending on DLL load order or unsafe same-function hook chaining.

A downstream final `CombatMove` / `AniSpeedScale` intervention remains a strong candidate, but the final code location must be verified against the migrated implementation.

### 6.4 Recover policy

There is intentionally no planned user-facing `RecoverSpeed` tuning key.

**Design decision:** Recover should follow the effective Hit speed for a controlled attack profile.

This is a project behavior requirement, not a claim that vanilla Gothic 3 always does this automatically.

## 7. Frame-Controlled Collision Architecture

### 7.1 Ownership declaration

At Hit execution/start, inspect the exact current motion resource and its frame-effect list.

If no reserved G3AB collision marker is present, frame collision does not take ownership and existing/native/legacy collision behavior remains active.

If a reserved marker is present, that exact animation execution opts into frame-controlled collision and legacy timed activation for that execution must be suppressed before it can activate earlier than the authored marker.

### 7.2 Marker execution

When the authored marker reaches `gCEffectSystem::StartEffect`, immediately execute the collision activation/rearm operation associated with the current attack family/source resolver.

Measured prototype behavior shows marker-to-collision code execution is effectively immediate at the authored frame.

### 7.3 Natural end reset

For ordinary weapon single-hit attacks, Gothic 3 has been observed resetting:

`Item_Attack (7) -> Item_Equipped (5)`

at the Hit -> Recover transition.

Therefore an explicit OFF marker is not required at normal Hit end.

An explicit OFF capability may still be useful for deliberate inactive gaps inside multi-hit animations, but this is not yet a finalized production requirement.

### 7.4 Repeated authored hits

For a later hit in the same attack to damage the same target again, the relevant triggered-damage list must be rearmed/cleared at the later authored strike.

The final generalized rearm/source API is not yet frozen.

### 7.5 Marker vocabulary

The prototype marker `G3AB_COL_TEST` is proven.

Current preferred production candidates are source-explicit, action-family-independent markers such as:

- `G3AB_COL_RIGHT`
- `G3AB_COL_LEFT`
- `G3AB_COL_BOTH`
- `G3AB_COL_OFF`

They remain **proposals only**. Generic source markers are preferred over separate Normal/Quick/Power marker vocabularies because the native callback already supplies the attack-family context.

Do not mass-author these names into animation libraries until source activation, OFF-state tracking, Fist/body behavior, and multi-hit rearming are validated.

## 8. Callback + Action + Phase + Marker Model

The preferred collision-control model is:

1. the named native callback identifies the collision path that must be intercepted;
2. exact `gEAction` identifies a supported member of that callback family when the marker later reaches the global dispatcher;
3. `gEPhase_Hit` confirms the currently supported phase;
4. exact current-motion marker presence declares frame-controlled ownership;
5. a source resolver or source-explicit marker chooses the logical/physical damage source;
6. marker execution performs the activation/rearm operation.

The action check does not help Gothic 3 select or play an animation. It correlates the later global `StartEffect` marker with the attack family whose native callback was suppressed. Without it, the current stateless prototype would need either a filename-family heuristic or stored per-execution ownership state.

This avoids a generic filename substring such as `_Attack_Hit_` as sole authority while keeping v0.7 simpler than a new state-lifecycle system.

## 9. Current Callback Families of Interest

Known attack callbacks include:

- `OnAI_Attack`
- `OnAI_GetUpAttack`
- `OnAI_PierceAttack`
- `OnAI_QuickAttack`
- `OnAI_PowerAttack`
- `OnAI_SimpleWhirl`
- `OnAI_WhirlAttack`

`OnAI_QuickAttack` covers native actions including QuickAttackR and QuickAttackL. At callback time it scopes the native timer path. The global marker handler later uses exact Quick/QuickR/QuickL `Routine.Action` values plus Hit phase and exact-motion marker to confirm that the marker belongs to this supported family.

## 10. Current Source-Selection Knowledge

### Normal

Source may depend on weapon configuration and pose/action logic. A simple right-hand assumption is not sufficient for all final cases.

Current animation-author evidence:

- Dual P0 Normal uses the left weapon.
- Some Torch+1H P0 Normal attacks natively activate the left torch; this is considered erroneous for those animations.
- Jackydima's `Script_AttackCollision` deliberately sends regular Torch+1H Normal attacks to the right weapon.

### QuickAttack

Current animation-author evidence:

- Dual P1 Quick uses the left weapon.
- A Dual P3 Quick animation file exists and should visually use the left weapon, but whether Gothic 3 currently resolves/uses that file is unconfirmed.
- Torch+1H P1 and P3 Quick attacks use the left torch.
- Other currently understood Quick cases commonly use the right-hand item.

These pose/UseType rules are useful evidence for the prototype resolver, not the preferred final authoring interface. Source-explicit animation markers would remove the need to infer the intended hand from pose and equipment.

### PierceAttack

Dual P1 Pierce uses the left weapon according to animation-author evidence and is also represented as a left-source special case in current third-party code.

### PowerAttack

Jackydima's current source activates both right and left weapons for Dual Power attacks and later re-clears their triggered lists. This is the preferred known behavior for those attacks.

A recollection that the native Dual P0 Power path may be left-source is not yet isolated and remains a working hypothesis.

### FinishingAttack

One Dual finishing animation may visually contact with both weapons while only one source actually damages. The exact native source is not yet confirmed; for that particular animation, a single damaging source is considered acceptable.

### WhirlAttack

Known third-party code historically used right-hand activation and has needed reset/rearm fixes. Current upstream Jackydima work added `PropertyResetOnUntouch = GETrue` to WhirlAttack handling.

### Fist

The logical Fist source does not behave like a normal equipped weapon collision group.

The completed v0.9 player matrix produced damage from the native left hand and custom right hand, left leg, right leg, and head while the logical Fist entity remained collision group `0`, the weapon-style `SetCollisionGroup(Item_Attack)` request was skipped, and the triggered-damage list was cleared.

**Production direction:** treat Fist as a logical body-contact rearm source. The marker helper should clear/rearm the logical Fist source without requesting the weapon `Item_Attack` group.

This conclusion is limited to the tested player `gEUseType_Fist = 8` contacts. It does not prove every body part, `gEUseType_PhysicalFist = 55`, or monster-specific bodies. The matrix retained triggered-list clearing, so its independent necessity was not isolated.

## 11. Compatibility Rules

Do not rely on DLL load order to solve multiple independent hooks on the same function.

Before integrating with NewBalance or `Script_AttackCollision`, inspect the hook implementation and choose one of:

- one shared downstream intervention;
- integration into one owner;
- a proven chain-safe mechanism.

Unmarked/unconfigured attacks must remain compatible with existing behavior.

## 12. Implementation Strategy

1. Preserve the validated Normal and QuickR/L marker-controlled paths.
2. Generalize the source helper into explicit weapon activation versus Fist/body rearming; Fist skips the weapon group request and clears its logical source list.
3. Resolve right/left/both equipped-weapon selection deliberately before marking Dual or Torch+1H attacks.
4. Freeze a production marker vocabulary only after source selection, OFF-state tracking, and repeated-hit semantics are understood.
5. Integrate the validated behavior into `Script_G3AnimationBehaviors`.
6. Expand Raise and speed control incrementally using the same evidence discipline.

## 13. Non-Goals for the Current Iteration

The following are not immediate implementation targets:

- global creature reanimation;
- intended-target/crosshair correction;
- climbing;
- rewriting Gothic 3 input arbitration;
- manually constructing all combat animation filenames;
- replacing every third-party collision behavior before equivalent source selection is implemented.

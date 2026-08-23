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

### 6.5 Initial authoring and calibration scope

Raise and playback-speed work should initially target Normal and Quick attacks.
The animation-authoring baseline is currently a Hit authored from frame 0 through
frame 12 inclusive (13 sampled frames) plus a Raise authored from frame 0 through
frame 4 inclusive (5 sampled frames). These are asset conventions, not engine
hardcodes. Provisional family speeds
(Quick above 1.0, 1H near 1.0, 2H near 0.95, Staff near 0.9 or 0.8) must not be
frozen until native Normal/Quick durations are recorded and compared through the
logger.

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

A source marker may therefore repeat within one Hit. Dual Power is the current
reference case:

- P0 visual contacts: RIGHT, LEFT, RIGHT;
- P1 visual contacts: LEFT, RIGHT, LEFT.

The repeated first-hand marker must rearm that source for its second contact.
`BOTH` means both sources activate/rearm at that authored moment; it must not
be treated as shorthand for solving every later contact in the attack. An OFF
marker is needed only if an inactive gap must prevent unintended contact, not
merely because the same source will be rearmed later.

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

Controlled v0.10 player runtime evidence:

- Dual P0 Normal uses the left weapon.
- Dual P1 Normal uses the right weapon.
- every tested activation naturally reset 7 -> 5 in phase 3.

Other current evidence:

- Some Torch+1H P0 Normal attacks natively activate the left torch; this is considered erroneous for those animations.
- Jackydima's `Script_AttackCollision` deliberately sends regular Torch+1H Normal attacks to the right weapon.

### QuickAttack

Controlled v0.10 player runtime evidence:

- Dual P0 QuickAttackR and QuickAttackL both use the right weapon.
- Dual P1 QuickAttackR and QuickAttackL both use the left weapon.
- all four tested activations naturally reset 7 -> 5 in phase 3.
- Quick R/L direction metadata does not select the physical weapon hand.

Other current evidence:

- A Dual P3 Quick animation file exists and should visually use the left weapon, but whether Gothic 3 currently resolves/uses that file is unconfirmed.
- Torch+1H P1 and P3 Quick attacks use the left torch.

These pose/UseType rules are useful evidence for the prototype resolver, not the preferred final authoring interface. Source-explicit animation markers would remove the need to infer the intended hand from pose and equipment.

### PierceAttack

Controlled v0.10 player runtime shows Dual P0 Pierce using the right weapon and
Dual P1 Pierce using the left weapon. Both naturally reset 7 -> 5 in phase 3.
This matches the current third-party source rule.

### PowerAttack

Controlled v0.10 player runtime shows both P0 and P1 Dual Power activating the
right and left weapons at the same logged state time, then naturally resetting
both to 5 in phase 3. This contradicts the earlier recollection that P0 might be
left-only.

Dual Power is a three-contact animation: P0 visually strikes right -> left ->
right, while P1 strikes left -> right -> left. Initial BOTH activation only
allows each weapon entity to damage the same target once until its triggered
list is rearmed. Native behavior is reported to produce only two effective hits.

Jackydima's current source matches the observed BOTH group activation and later
re-clears both triggered lists at a Dual-specific threshold. That rearm plausibly
enables the first weapon's third visual contact, but v0.10 observed only
collision-group transitions. Production must not treat BOTH activation alone as
complete Dual Power behavior.

Pinned NewBalance contains an independent `FixDualOneHanded` call hook that
clears both Dual weapon lists at `RVA_ScriptGame(0x482e7)`. This confirms the
rearm fix is present in NewBalance itself, not only in `Script_AttackCollision`.
The hook location is build-specific and does not yet establish the exact
animation time of the clear.

The engine trigger structure keeps `EntitiesVisited` and
`EntitiesVisitedCount`. Controlled marked-2H testing confirms the first part of
the resulting model for the current project path:

- a weapon may hit several different entities during one active window;
- an entity already visited by that weapon cannot normally be damaged again
  until its visit entry is cleared or reset;
- clearing at a new source marker starts a fresh authored contact for that
  source.

The marked v0.10 2H Normal path damaged two or three distinct wolves during one
window after a single list clear, while each of four attacks logged only one
player activation and one natural reset. Multi-target behavior is therefore
confirmed for the current marker-controlled weapon path. Completely unmodified
native behavior and same-target rearming remain separate questions.

### FinishingAttack

One Dual finishing animation may visually contact with both weapons while only one source actually damages. The exact native source is not yet confirmed; for that particular animation, a single damaging source is considered acceptable.

For human 2H/Staff, Block + held attack selects Finishing rather than Whirl. In
front of a downed enemy, death is timer-driven rather than collision-driven.
Animation-length tests strongly support that the execution timer begins with Hit
and is insensitive to Raise-length changes. Preserve the established Finishing
Hit timing when replacing these assets. Standing-target selection may become
HackAttack, but that branch remains a working hypothesis.

### WhirlAttack

Human attack-family coverage is equipment-specific:

- Dual has SimpleWhirl only, although its animation filenames serialize
  `WhirlAttack`; it is selected by holding attack slightly less than Power.
- 2H and Staff have full Whirl, selected by Block + quick attack.
- ordinary 1H families have no Whirl.
- hand-to-hand coverage remains unknown.

The Dual SimpleWhirl visually turns the actor with one sword extended forward
and the other backward; whether one or both should damage is unconfirmed.
Filename spelling must not substitute for logging the native action/callback.

Known third-party full-Whirl code historically used right-hand activation and
has needed reset/rearm fixes. Current upstream Jackydima work added
`PropertyResetOnUntouch = GETrue` to WhirlAttack handling.

For authored 2H/Staff double attacks, automatic reset-on-untouch is not a full
replacement for an explicit inactive window. A nearby opponent can intersect
the second swing before its intended acceleration. The preferred marker model
is source-explicit; there is no separate marker literally named ON:

1. RIGHT/LEFT/BOTH marker: activate and clear the named source set's triggered
   list;
2. generic OFF marker: return every source owned by this marked execution to
   its inactive/equipped collision state;
3. later RIGHT/LEFT/BOTH marker: reactivate and rearm only the authored next
   contact.

OFF controls physical timing; it does not itself rearm or produce damage.
Exact restoration and cleanup rules must be proven before marker names freeze.
A same-source double attack simply repeats that source marker after OFF; for
example, RIGHT -> OFF -> RIGHT.

The first OFF proof must use distinct targets because an already visited target
cannot reveal whether collision remained active. Use an identical horizontal
2H sweep as ON-only control and ON -> OFF variant; later wolves crossed by the
continuing blade must remain unharmed after OFF. Then reuse the validated double
attack for ON -> OFF -> ON to prove that the next source marker restores the
weapon window and rearms the list. The current v0.12 prototype limits OFF to a
matching marker-owned weapon window; Fist/body OFF remains separate work.

v0.12 validates the physical rule. In the tested horizontal sweep, ON-only
could hit all three wolves; OFF at frame 9 usually limited damage to one, and
OFF at frame 8 never allowed more than one. The double attack retained two
intended damage contacts after ON -> OFF -> ON, including multi-target contacts
on both swings.

The double log also proves that last-marker-only dedupe is not the final
architecture. At the late contact Gothic 3 dispatches `ON, OFF, ON` at one
state time, replaying already-consumed marker names around the genuine late ON.
Because the names interleave, comparing only with the immediately previous
marker accepts all three. The v0.13 source candidate therefore keeps the v0.11
same-update identical-marker guard as layer one and adds an authored-occurrence
budget as layer two. The first layer prevents an immediate duplicate from
consuming a later genuine occurrence; the second rejects interleaved replay.
Two authored ON entries permit two accepts and one authored OFF entry permits
one. Calls beyond those counts do not mutate collision or lists. This retains
the generic marker vocabulary without per-contact numbering.

The guard is event-driven. Exact-motion ON/OFF counts are scanned once and
cached by animation name; runtime work occurs only when a reserved marker is
dispatched. Each participating actor has at most one current execution record.
There is no per-frame actor/world scan. Verbose prototype logging is not part
of the intended production cost and must be disabled or removed in the release
DLL.

v0.13 validates the combined guard in seven executions of the exact double
fixture. Each execution accepted two ON and one OFF, rejected the replayed OFF
by occurrence budget, rejected the final extra ON as an exact same-update
duplicate, and naturally cleaned up once. Rejected calls performed no
collision/list mutation. Both genuine contacts remained visually effective
against two independently tested targets. This validates function and
execution reset for the tested Normal path; it does not replace future
large-battle profiling or entity-lifecycle review for production.

Before OFF existed, v0.10 isolated same-target list rearming under the proven
Normal path by reusing one identical double-contact 2H motion in three variants:

1. no marker: native-timer baseline;
2. first-contact marker only: one authored activation/list clear across both
   visual contacts;
3. first- and second-contact markers: the second marker clears the same weapon
   list again while collision is already active.

Only marker placement changed. Variants 1 and 2 damaged the target once;
variant 3 damaged it at both intended contacts. The second marker's list clear
is therefore the isolated rearm cause. OFF is added and tested separately for
the inactive gap.
The source-level clear semantics do not need exhaustive repetition across every
action family; callback-specific tests instead validate ownership and native
timer suppression.

The two-marker log also exposed deterministic duplicate dispatch: the later
authored marker fired twice at identical `StateTime` in every tested attack.
Production marker handling must ignore an identical actor + motion + marker +
source dispatch repeated within the same animation update, while preserving
genuinely different simultaneous source markers.

v0.11 validates that rule for the tested right-source Normal path. Across six
executions it preserved both authored contacts, ignored one duplicate late
callback per attack, and reduced list clearing from three calls to the intended
two without losing two-contact damage.

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

1. Preserve the validated Normal and QuickR/L marker-controlled paths and the v0.9 Fist/body rearm result.
2. Preserve the completed Dual Normal/Quick/Pierce/Power source map; extend passive diagnostics to `ClearTriggeredList`, Dual SimpleWhirl, and the separate 2H/Staff full-Whirl path without changing native behavior. Add damaged-target identity only if later same-target results are ambiguous.
3. Generalize the source helper into explicit weapon activation versus Fist/body rearming; Fist skips the weapon group request and clears its logical source list.
4. Add collision ownership adapters one callback family at a time. Collision scope should cover the main human melee families before production integration, but Raise and speed remain initially scoped to Normal and Quick.
5. Treat BOTH group activation as proven but incomplete: validate Dual Power's third-contact rearm, multi-target versus same-target list behavior, SimpleWhirl source/contact intent, full-Whirl `ResetOnUntouch`, and explicit OFF for authored inactive gaps.
6. Freeze a production marker vocabulary only after source-set tracking and repeated-hit/OFF semantics are understood.
7. Integrate the validated collision core into `Script_G3AnimationBehaviors`.
8. Generalize Raise and speed control incrementally, calibrating provisional speeds against logged native Normal/Quick durations.

## 13. Non-Goals for the Current Iteration

The following are not immediate implementation targets:

- global creature reanimation;
- intended-target/crosshair correction;
- climbing;
- rewriting Gothic 3 input arbitration;
- manually constructing all combat animation filenames;
- replacing every third-party collision behavior before equivalent source selection is implemented.

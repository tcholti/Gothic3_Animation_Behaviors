# Attack Forward Displacement — Research / Architecture

**Status:** ACTIVE  
**Branch:** `development`  
**Stable baseline:** `main` contains the accepted Collision + Speed + Raise checkpoint through EV-433.

## Purpose

Research how Gothic 3 decides **how far an attack moves the acting character forward**, and determine the smallest compatible architecture for making that distance configurable.

This is research/design only. Do not implement production behavior until native ownership, New Balance intervention, timing interaction and compatibility composition are causally understood.

## Protected accepted systems

```text
Collision = CLOSED/PASS
Speed = CLOSED/PASS
Raise = CLOSED/PASS
New Balance compatibility = protected
AttackCollision compatibility = protected
```

Do not redesign or weaken those systems to obtain displacement control.

## Established project seed

`SOURCE_HOOK_GUIDE.md §3B` already preserves two factual starting surfaces:

```text
Game+0x16B8A3  CombatMove reach/vector call
Game+0x16B8A9  CombatMove movement call
```

These are starting surfaces only, not ownership proof.

Research must separate:

```text
animation/root translation contribution
CombatMove-requested displacement
motion/pose descriptor values
action-specific Script_Game policy
New Balance intervention
speed / animation-duration interaction
```

Do not call the feature root-motion control unless root motion is actually proven to own the observed attack displacement.

## Static research status — EV-434

Principal static causality is now established:

```text
native:
selected resource filename word 13 = D_filename
T = primary max time / AniSpeedScale
m_DirectionVec = normalized direction * D_filename/T
Game+0x16B8A3 = native vector scale
Game+0x16B8A9 = CharacterMovement receiver load / New Balance insertion
Game+0x16B8B7 = actual EnableCombatMovementFromSPU call

New Balance project pin:
references/jackydima-gothic3sdk
@ 316d32406a133f8884e7e302752c35f66b4f54fc

NB Hit behavior:
action/skill GetCombatMoveLength policy
-> normalize existing vector
-> replace magnitude by L/T * ATTACK_REACH_MULTIPLIER
```

Native `GetCombatMoveLength` is not the native movement-distance owner on the tested path; its native Hit caller discards the return. The selected resource filename supplies native distance.

Speed algebra is closed: changing `AniSpeedScale` changes the commanded velocity needed to cover the chosen nominal distance over the nominal animation duration; it does not inherently change that nominal distance.

The strongest compatible future seam is after native/New Balance vector policy at the CombatMove-specific `Game+0x16B8B7` call, with candidate scalar composition `v_configured = k * v_compatible`. This is not yet production-frozen.

## Selected architecture candidate — EV-438

Option 2 is selected for research closure:

```text
<Attack>_Movement=Off
= preserve the complete live compatible stack unchanged

<Attack>_Movement=<non-negative number>
= absolute authored-style CombatMove distance for that Hit

100
= behave as a CombatMove distance of 100 regardless of the selected
  animation's filename value or New Balance's action-wide reach value
```

This removes the movement-specific need for future animation-name injection/repacking and allows one profile value to normalize multiple attacks in the same profile even when their current asset names carry different movement numbers.

### Smallest compatible seam

Use one G3AB insertion immediately before the existing native CharacterMovement call at `Game+0x16B8B7`.

At that point:
- Gothic has resolved/started the actual motion;
- Speed's final request `AniSpeedScale` is already present;
- native filename movement policy has run;
- pinned New Balance at `+0x16B8A9` has already run if installed;
- the final direction is present in `SPU.m_DirectionVec`;
- the untouched native CharacterMovement call has not yet consumed it.

Configured movement therefore computes:

```text
T = primary motion max time / request.AniSpeedScale
velocityMagnitude = configuredMovement / T
```

and replaces only the vector magnitude while preserving its final direction.

No movement setting -> no mutation.

### Architecture ownership

```text
BehaviorProfiles
= configuration storage / profile identity

AttackMovement
= action eligibility + movement-distance policy + vector magnitude composition

EngineBridge
= one physical +0x16B8B7 transport hook only
```

Do not put movement policy in EngineBridge.

No state/cache/generation tracking is required.

### Supported initial action scope

Use the existing profile attack surface:

```text
Normal
Quick
Power
Pierce
Hack
SimpleWhirl
Whirl
```

Sprint inherits Power where the factual Sprint route reaches this movement boundary. Do not add a new Sprint profile key.

Finishing/JumpAttack/RamAttack are outside initial scope.

### Fail-closed boundaries

- null args/SPU/entity -> untouched;
- physical phase other than Hit -> untouched;
- unsupported action -> untouched;
- missing/invalid/movement Off -> untouched;
- invalid/non-positive duration -> untouched;
- configured positive distance with degenerate final direction -> untouched;
- configured zero distance -> zero movement vector is valid.

Do not add a second hook merely to manufacture direction for zero-authored/zero-compatible attacks in v1.

## Evidence order

Use:

```text
current project source/reference
-> pinned official SDK
-> pinned Jackydima/New Balance reference
-> tested Gothic binary reference/static inspection
-> smallest controlled runtime probe only if static ownership remains unresolved
```

Do not create a probe merely because one could provide more data. First exhaust the existing source/binary surfaces.

## Non-goals

- no production implementation;
- no INI key creation yet;
- no new hook yet;
- no Collision/Speed/Raise redesign;
- no broad movement/traversal system;
- no climbing/vaulting implementation;
- no assumption that every attack should move or should share one distance rule.

## Closure target

Static ownership, New Balance intervention and speed algebra are closed by EV-434, and the practical author/runtime movement-phase and archive/distribution constraints are reconciled by EV-435. EV-438 now freezes the intended absolute authoring semantics, initial profile scope and smallest candidate seam. Research closes after one bounded independent static architecture/hook review confirms the +0x16B8B7 transport and fail-closed design. Then freeze a separate production implementation task.

Then freeze a separate production task if implementation is justified.

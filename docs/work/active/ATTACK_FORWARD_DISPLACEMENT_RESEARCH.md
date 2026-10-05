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

## Current architecture question

EV-434 + EV-435 are sufficient to stop re-proving the basic movement mechanism.

The remaining question is semantic, not causal:

> When New Balance has already replaced the animation-authored Hit movement magnitude, what should a configured G3AB value mean?

The design must distinguish at least these states conceptually before implementation is frozen:

```text
Off
= preserve the complete live compatible stack unchanged
  (native or New Balance/other compatible movement)

authored-animation baseline
= the movement Gothic would derive from the selected animation resource's
  filename distance field at the already-composed request speed

configured control
= a deliberate author/user adjustment whose neutral meaning must be chosen
  explicitly rather than inferred from New Balance's final vector
```

Important product constraint:
- changing the animation filename itself is not an acceptable configuration mechanism because it requires resource replacement/repacking under Gothic archive precedence;
- the runtime feature exists to provide this control without renaming/repacking animations.

Potential implementation families may include:
- scalar over the final compatible vector (`1.0` = preserve New Balance/native compatible behavior);
- restoration/scaling of the animation-authored baseline after New Balance (`1.0` = selected animation's authored movement);
- an explicit distinction between those semantics.

Do not freeze one merely because its hook is easiest. Resolve the intended authoring contract first.

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

Static ownership, New Balance intervention and speed algebra are closed by EV-434, and the practical author/runtime movement-phase and archive/distribution constraints are reconciled by EV-435. Research now closes when Normal Chat + User freeze the intended authoring/configuration semantics (especially the meaning of `1.0` and Off behavior), supported initial attack scope, and the smallest compatible seam that implements those semantics without animation renaming/repacking.

Then freeze a separate production task if implementation is justified.

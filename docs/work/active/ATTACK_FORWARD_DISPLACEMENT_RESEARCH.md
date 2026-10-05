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

User-selected authoring contract:

```text
inactive / Off
= preserve the complete live compatible stack unchanged
  (native, New Balance, AttackCollision-compatible downstream behavior)

configured numeric multiplier K
= take the selected animation resource's authored filename movement
  as the baseline and apply K to that authored movement

K = 1.0
= exactly the selected animation's authored movement value

K = 0.5
= half the selected animation's authored movement

K = 1.5
= 150% of the selected animation's authored movement
```

This is intentionally **not** `K * New Balance final magnitude`. When configured, G3AB is expected to own the movement magnitude for that attack while still preserving downstream direction and native obstacle/ledge/target stopping behavior. When inactive, G3AB must not alter New Balance/native movement at all.

The same profile identity and attack-grouping model used by Speed is the desired configuration surface: Normal, Quick, Power, Pierce, Hack, SimpleWhirl and Whirl settings may each carry an optional movement multiplier. Sprint-origin behavior should be resolved from factual routing/evidence rather than given a new symmetric profile key by assumption.

Important default-config consequence:
- because `1.0` is an active authored-baseline override rather than "leave compatible movement unchanged", the shipping INI must not silently enable numeric `1.0` for every profile;
- missing/inactive movement configuration must preserve the live compatible stack;
- if movement keys are shown for discoverability, they need an explicit inactive representation rather than a live numeric default.

Future archive-injection work may normalize authored filename distances across attacks/families. This runtime multiplier is deliberately relative to whatever value is authored in the selected animation resource, so normalized future assets will automatically make one profile multiplier produce correspondingly normalized results without changing the runtime architecture.

The remaining architecture work is to determine the smallest transport/state needed to retain the native authored magnitude across New Balance's downstream replacement and reapply `authoredMagnitude * K` at the final CombatMove movement seam.

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

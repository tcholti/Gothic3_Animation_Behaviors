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

## Active runtime probe implementation

`docs/work/active/ATTACK_FORWARD_DISPLACEMENT_RUNTIME_PROBE.md`

The probe is observation-only and exists solely to close the remaining runtime question below.

## Remaining runtime question

Only one causal gate remains before production architecture can freeze:

> For representative unobstructed attacks, does actual entity travel correspond to the commanded CombatMove velocity integrated over the interval for which combat movement is enabled?

The first runtime pass should measure only what is necessary to answer that:

```text
factual action + phase
selected animation resource
request AniSpeedScale
incoming final compatible movement vector at/just before Game+0x16B8B7
entity world position when combat movement becomes enabled
time movement becomes enabled
entity world position when that CombatMove movement becomes disabled
time movement becomes disabled
reason/context for disable if readily available
```

Derived comparison:

```text
predicted commanded travel
= |v_compatible| * actual enabled duration

observed entity travel
= horizontal entity-position delta over the same interval
```

Use:
- one representative human Normal attack;
- one representative nonhuman Normal attack;
- flat/unobstructed conditions;
- target/no-target setup chosen to avoid early target-stop where practical;
- at least two playback-speed settings on one fixture;
- New Balance active for the compatibility fixture.

Do **not** add direct root/bone instrumentation initially. If commanded-vs-observed travel agrees within ordinary runtime tolerance, an independent material root contribution to entity translation is not indicated for those fixtures. Add root-relative instrumentation only if a meaningful discrepancy appears.

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

Static ownership, New Balance intervention and speed algebra are already closed by EV-434. Research now closes when bounded runtime evidence establishes whether compatible commanded velocity accounts for representative realized entity travel closely enough to support scalar composition at the final CombatMove movement seam. If it does, return to Normal Chat to freeze initial public scope/config semantics and the smallest production implementation. If it does not, investigate only the measured discrepancy.

Then freeze a separate production task if implementation is justified.

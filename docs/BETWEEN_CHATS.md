# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — EV-434 displacement static closure

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `development`

## Stable baseline

`main` remains the promoted Collision + Speed + Raise baseline through EV-433.

## Displacement static result — EV-434

```text
native selected-resource filename word 13 = movement distance
T = maxTime / AniSpeedScale
native m_DirectionVec magnitude = D_filename / T

Game+0x16B8A3 = native vector Scale
Game+0x16B8A9 = New Balance insertion after native scale
Game+0x16B8B7 = final CombatMove EnableCombatMovementFromSPU call
```

Project-pinned New Balance:
`references/jackydima-gothic3sdk @ 316d32406a133f8884e7e302752c35f66b4f54fc`

For eligible Hit actions New Balance normalizes the existing direction and replaces magnitude with its action/skill distance divided by nominal duration, multiplied by `ATTACK_REACH_MULTIPLIER`.

Native `GetCombatMoveLength` is not the native movement-distance owner in the tested path.

Speed changes commanded velocity but nominal uninterrupted travel cancels back to the selected distance.

Strongest compatibility candidate, **not yet frozen**:

`Game+0x16B8B7 -> v_configured = k * v_compatible`

## Active responsibility

Parent research:
`docs/work/active/ATTACK_FORWARD_DISPLACEMENT_RESEARCH.md`

Bounded implementation:
`docs/work/active/ATTACK_FORWARD_DISPLACEMENT_RUNTIME_PROBE.md`

One runtime gate remains:

compare
```text
|final compatible velocity| * actual combat-movement-enabled duration
```
against
```text
observed horizontal entity-position travel
```

on:
- one human Normal;
- one nonhuman Normal;
- unobstructed/flat conditions;
- at least two speeds on one fixture;
- New Balance active for compatibility coverage.

Do not instrument root/bones unless the first comparison shows a meaningful discrepancy.

No production displacement implementation yet. The current code task is diagnostics-only: implement the removable `Script_AttackDisplacementProbe.dll`, then stop for Normal Chat source review.

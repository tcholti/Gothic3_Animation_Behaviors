# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — EV-438 absolute attack movement architecture

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `development`

## Stable baseline

`main` remains Collision + Speed + Raise stable through EV-433.

## Movement research

EV-434:
- native filename movement mechanism and New Balance replacement path proven.

EV-435:
- practical Hit-phase movement / archive constraints reconciled.

EV-437:
- New Balance owns Hit movement across the complete ordinary melee attack surface relevant to current G3AB profiles.

EV-438:
- **option 2 selected and statically feasible.**

```text
Movement=Off
-> no G3AB mutation; native/New Balance untouched

Movement=<number>
-> absolute CombatMove Hit distance in Gothic authored movement units
```

Candidate seam:

```text
New Balance +0x16B8A9 (if present)
-> final SPU.m_DirectionVec
-> G3AB insert immediately before Game+0x16B8B7
-> configured magnitude = Movement / (maxTime / AniSpeedScale)
-> original EnableCombatMovementFromSPU unchanged
```

Architecture:
```text
BehaviorProfiles = config/profile identity
AttackMovement = movement policy
EngineBridge = one hook transport
```

Initial action surface:
`Normal / Quick / Power / Pierce / Hack / SimpleWhirl / Whirl`
with Sprint inheriting Power where factually routed.

No state, no filename parsing, no New Balance detection, no per-frame work.

Zero-direction positive override fails closed in v1 rather than inventing direction; current shipping profile inventory is not blocked by the known Troll_None_Fist zero-distance edge.

## Active responsibility

Parent research:
`docs/work/active/ATTACK_FORWARD_DISPLACEMENT_RESEARCH.md`

Independent review:
`docs/work/active/ATTACK_MOVEMENT_ARCHITECTURE_REVIEW.md`

EV-439 additionally removes the unused `Troll_None_Fist` zero-distance route as a practical v1 blocker. Keep the simple fail-closed zero-direction rule; do not add a second movement hook/state machine for that unused route.

If the independent review passes, close research and freeze the bounded production implementation.

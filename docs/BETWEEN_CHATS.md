# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — EV-440 attack movement production freeze

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `development`

## Stable baseline

`main` remains Collision + Speed + Raise stable through EV-433.

## Movement closure

EV-434–EV-439 established native/New Balance ownership, practical phase/archive constraints, complete ordinary melee New Balance ownership, absolute-distance option 2 feasibility, and removal of the unused Troll_None_Fist zero-route as a v1 blocker.

EV-440 independent Sol review:

```text
BLOCKER 0
MAJOR   0
MINOR   0
NOTE    3
PASS WITH NON-BLOCKING NOTES
```

The notes are mandatory implementation details:
- exact +0x16B8B7 hook transport;
- finite replacement validation before mutation;
- reuse existing bounded profile lookup.

## Frozen production semantics

```text
<Attack>_Movement=Off
= no G3AB movement mutation

<Attack>_Movement=<finite non-negative number>
= absolute authored-style CombatMove distance for factual Hit

Movement=0
= valid active zero movement
```

Compatibility:

```text
Native + Off -> native untouched
NB + Off     -> New Balance untouched
Native + numeric -> G3AB owns final Hit magnitude
NB + numeric     -> NB runs first, G3AB then overrides magnitude
```

## Active responsibility

`docs/work/active/ATTACK_MOVEMENT_PRODUCTION_IMPLEMENTATION.md`

Allowed production ownership:
```text
BehaviorProfiles = configuration
AttackMovement    = stateless policy
EngineBridge      = one +0x16B8B7 hook transport
INI               = Off-by-default user surface
```

No Collision/Speed/Raise redesign.
No build/deploy/runtime in implementation task.

After implementation: independent Normal Chat source review, then User-local build/deploy/runtime.

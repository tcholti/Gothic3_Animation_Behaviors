# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-04

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`  
`main` remains frozen.

## Current state

```text
Collision = CLOSED/PASS through EV-390
Speed v2 = CLOSED/PASS through EV-410
neutral Speed INI = LOCKED

Raise AddRaise = ACTIVE NEXT FEATURE
public first scope:
  Normal_AddRaise
  Quick_AddRaise
  Whirl_AddRaise
shipping default = Off

Quick static precheck = CLOSED
Action3 = generic Quick selector/request identity
Gothic selects and writes factual Action4/QuickAttackR or Action5/QuickAttackL downstream
```

## Continue here

Read:

1. root `README.md` -> Start Here
2. `docs/SESSION_ENTRYPOINT.md`
3. `docs/work/active/RAISE_ADDRAISE_PRODUCTION_IMPLEMENTATION.md`
4. `docs/DESIGN.md` Raise section
5. `docs/SOURCE_HOOK_GUIDE.md` Quick caller/source facts
6. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
7. `docs/FEATURE_DEVELOPMENT_METHOD.md`

## Frozen implementation direction

```text
Normal -> PS_Melee_Attack + PREPEND_BREAK_BLOCK
Whirl  -> PS_Melee_WhirlAttack + PREPEND_BREAK_BLOCK
Quick  -> existing sAICombatMoveInstr transport only after Gothic selected Action4/5
```

Do not use `PS_Melee_QuickAttack` entry to choose R/L. Do not invent Quick direction-selection logic.

The implementation is generic/profile-driven from the start. Hero None+2H is only the first runtime fixture because matching Normal, Quick and full Whirl Raise assets already exist.

Work build execution is prohibited unless a later explicit task authorizes it. After implementation publication, Normal Chat performs independent source review before the User builds/deploys/tests locally.

## Protected

Do not reopen Speed/collision, touch Finishing, broaden AddRaise scope, add weapon-specific policy, construct Raise filenames manually, add a RaiseSpeed key, or promote `main` absent a new explicit decision.

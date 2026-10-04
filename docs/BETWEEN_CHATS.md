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
27 tested profiles / 97 tested Speed settings
BaseSpeed = ReferenceHitBaseSpeed by default

Raise AddRaise = ACTIVE NEXT FEATURE
design = LOCKED
public first scope:
  Normal_AddRaise
  Quick_AddRaise
  Whirl_AddRaise
shipping default = Off
```

## Continue here

Read:

1. root `README.md` -> Start Here
2. `docs/SESSION_ENTRYPOINT.md`
3. `docs/work/active/RAISE_ADDRAISE_IMPLEMENTATION_PRECHECK.md`
4. `docs/DESIGN.md` Raise section

Before implementation also apply `WORK_IMPLEMENTATION_PROTOCOL.md` and `FEATURE_DEVELOPMENT_METHOD.md`.

## Locked Raise rules

```text
AddRaise is additive only.
Off/missing -> G3AB adds nothing; native behavior untouched.
On -> request matching Gothic Raise, wait, then continue original attack.

First scope = Normal / Quick / Whirl only.
No public native-Raise disable/replace controls.
No RaiseSpeed key.
No weapon-specific C++ branches.
No manual Raise filename construction.
Gothic resolves the concrete Raise animation itself.
```

Preferred transport:

```text
Normal -> PS_Melee_Attack + PREPEND_BREAK_BLOCK
Quick  -> PS_Melee_QuickAttack candidate
Whirl  -> PS_Melee_WhirlAttack + PREPEND_BREAK_BLOCK
```

Historical 2H Normal Raise + New Balance coexistence = observed PASS. Lower-level `sAICombatMoveInstr` interception is fallback only.

## Only remaining pre-implementation question

At `PS_Melee_QuickAttack` entry, determine whether the factual action is already QuickAttackR/Action4 or QuickAttackL/Action5.

```text
YES -> freeze generic Normal/Quick/Whirl implementation.
NO  -> find the smallest factual R/L selection boundary;
       do not invent R/L selection in G3AB.
```

Do not repeat broad Raise architecture research.

## First runtime fixture after implementation

User already has Hero None+2H Raise assets for Normal, Quick and full Whirl.

Test order:

```text
1. AddRaise Off control.
2. Native stack: 2H Normal / Quick R+L / Whirl with AddRaise On.
3. New Balance stack: repeat all three.
4. Change BaseSpeed and test whether added Raise follows relative timing.
5. Then create/test 1H Raise assets; expect no new C++ branch.
```

Release README later explains Gothic Raise naming rules with matched Normal, QuickR/L and Whirl examples; never tell authors to blindly replace only `Hit` with `Raise`.

## Protected

Do not reopen Speed/collision, touch Finishing, broaden AddRaise scope, or promote `main` absent a new explicit decision.

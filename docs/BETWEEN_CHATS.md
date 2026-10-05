# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — EV-424 direction causal closure

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`  
Collision, Speed core and Hack compatibility remain CLOSED/PASS. `main` frozen.

## EV-423 runtime contradiction

```text
Normal Left  -> correct Left Raise  -> following Hit becomes Fwd
Normal Right -> correct Right Raise -> following Hit becomes Fwd
```

Generated dual Fwd Normal and ordinary P0/P1 Quick Raises are runtime-valid.

## EV-424 static causal closure

`sAICombatMoveInstr_Args` has no direction field.

`sAICombatMoveStart`:
```text
Game+0x16ABB0
-> recomputes current direction
-> Fwd literal init +0x16AEDD
-> Action1 direction path +0x16AF3C
-> Right +0x16AF61 / Left +0x16AF76
-> write Navigation current gEDirection +0x16B00E
-> pass direction bCString to GetAniName at +0x16B056
-> GetAniName serializes that direction
```

Cause:
```text
Raise = first classification, correct Left/Right
Hit   = second classification after Raise, may now resolve Fwd
```

The previous animation filename is not the direction authority on this path. Gothic's naming structure remains a real state/resource contract, but the Normal direction token is freshly supplied to `GetAniName`.

## Active responsibility

`docs/work/active/RAISE_NORMAL_DIRECTION_CONTINUATION_IMPLEMENTATION.md`

Frozen correction:
```text
during pending Normal continuation:
capture Gothic-native direction at Raise GetAniName
-> on stored Hit GetAniName, reuse exactly that direction
-> restore matching Navigation current direction
-> let Gothic build the name normally
```

Allowed production files only:
```text
AttackRaise.cpp
AttackRaise.h
EngineBridge.cpp
```

No filename parsing, copied geometry policy, target/facing mutation, Speed change, Quick/Whirl redesign, Hack change or Collision change.

Independent source review + focused runtime validation are required after implementation.

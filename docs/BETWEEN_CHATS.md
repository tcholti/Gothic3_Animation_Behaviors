# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-04

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`  
Collision CLOSED/PASS and protected. `main` frozen.

## Current state

```text
production source = 41ed80c6420e5236d13fc037cb5923b946cb8ccc
source review = PASS EV-419
built/live SHA256 =
3E7BCDBE1EBFC92B6E5FCFD7507A1E6A36C9DB8849847C29AD15288C01C2928D
native focused runtime = PASS EV-420
New Balance + AttackCollision focused runtime = PASS EV-421
EV-417 AttackCollision Hack bypass = runtime CLOSED on tested 2H fixture
```

The User ran the same 0.1-versus-1.0 matrix both native and with New Balance + AttackCollision:

```text
2H Normal Raise+Hit = PASS
2H Quick Raise+Hit = PASS
2H Power Raise follows authored speed = PASS
2H Whirl Raise+Hit = PASS
2H Hack configured speed = PASS
1H Power Raise follows authored speed = PASS
1H Pierce whole-attack control = PASS
```

Power note: visual testing proves authored-speed coupling; exact preserved Raise-vs-Hit numerical ratio was not independently measured.

## Immediate continuation

Use:
`docs/work/active/RAISE_ADDRAISE_RUNTIME_ACCEPTANCE.md`

Only small final sanity controls remain:
```text
1. one understood New Balance contextual slowdown/modifier on configured Hack
2. factual Finishing control to confirm Hack profile does not alter Action15
3. one interrupted Hack -> later attack / AddRaise-to-Hack transition
```

Stop on lost relative modifier, Finishing timing change, continuation leak, crash or Collision contradiction.

No new Work task is needed unless runtime produces contradictory evidence.

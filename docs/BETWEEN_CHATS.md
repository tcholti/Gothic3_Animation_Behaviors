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
current Release built/live SHA256 =
3E7BCDBE1EBFC92B6E5FCFD7507A1E6A36C9DB8849847C29AD15288C01C2928D
native focused runtime = PASS EV-420
intended New Balance + AttackCollision Hack route = PENDING
```

EV-420 native-only fixture had New Balance/AttackCollision absent. Tested authored speeds 0.1 and 1.0:

```text
2H Normal Raise+Hit = PASS
2H Quick Raise+Hit = PASS
2H Power Raise follows authored speed = PASS
2H Whirl Raise+Hit = PASS
2H Hack Raise/Hit coupling = PASS
1H Power Raise follows authored speed = PASS
1H Pierce whole-attack control = PASS
```

Power note: this batch proves authored-speed coupling, not an independent numerical measurement of the preserved live Raise-vs-Hit phase ratio.

## Immediate continuation

Use:
`docs/work/active/RAISE_ADDRAISE_RUNTIME_ACCEPTANCE.md`

Next fixture:
```text
restore intended Script_NewBalance.dll + Script_AttackCollision.dll
-> keep current G3AB production DLL/hash
-> 2H Hack strong contrast (0.1 vs 1.0 is already convenient)
-> verify AttackCollision Hack now follows configured BaseSpeed
-> verify no obvious double scaling
-> one New Balance modifier/slowdown control
-> factual Finishing control
-> one interrupted Hack / AddRaise-to-Hack transition if convenient
```

Stop on ignored Hack authoring, extreme double-slowdown, Finishing timing change, lost New Balance relative modifier, continuation leak, crash or Collision contradiction.

No new Work task is needed unless runtime produces contradictory evidence.

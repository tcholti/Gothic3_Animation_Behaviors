# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — Raise/Speed runtime closure

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`  
Collision CLOSED/PASS and protected. `main` frozen.

## Current state

```text
accepted production source = 41ed80c6420e5236d13fc037cb5923b946cb8ccc
source review = PASS EV-419
built/live production SHA256 at EV-420 =
3E7BCDBE1EBFC92B6E5FCFD7507A1E6A36C9DB8849847C29AD15288C01C2928D
native focused runtime = PASS EV-420
New Balance + AttackCollision focused runtime = PASS EV-421
final stamina/Finishing/interruption sanity = PASS EV-422
Raise/Speed/Hack compatibility = CLOSED/PASS
```

Final EV-422 facts:
```text
ordinary zero-stamina Hack has little/no slowdown even without G3AB
-> absence is native/compatible behavior, not modifier loss

New Balance alternative zero-stamina attack restriction
-> configured Hack obeys it with G3AB installed

Hack_BaseSpeed=0.1 vs Finishing:
unique Hack asset  -> Hack slow / Finishing native-fast
shared Finishing asset -> Hack slow / Finishing native-fast

repeated Hack/other-attack interruptions
-> no stuck attack, stale Raise, speed carry-over or continuation leak
```

The completed runtime-acceptance record is archived at:
`docs/archive/investigations/RAISE_ADDRAISE_RUNTIME_ACCEPTANCE.md`

## Immediate continuation

No Raise/Speed Work task or runtime gate remains.

Next session:
```text
start from README -> SESSION_ENTRYPOINT
-> confirm development HEAD / knowledge-state PASS
-> choose the next project responsibility from the current roadmap/priority
```

Do not reopen Raise, Speed, Hack compatibility, Finishing isolation, or Collision absent contradictory evidence.

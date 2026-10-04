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
Raise AddRaise source = IMPLEMENTED
implementation commit = bc46dcf7d22305c4d9d4f99fc5f5a1075ef726bd
independent Normal Chat source review = PASS
public scope = Normal / Quick / Whirl
shipping AddRaise keys = 55 / all Off
build/deploy identity = PASS
Gate A AddRaise-Off = PASS EV-411
runtime acceptance = Gate B pending
```

## Continue here

Read:

1. root `README.md` -> Start Here
2. `docs/SESSION_ENTRYPOINT.md`
3. `docs/work/active/RAISE_ADDRAISE_RUNTIME_ACCEPTANCE.md`

Immediate next step is Gate B: native-stack Hero None+2H. Physically remove `Script_NewBalance.dll` and `Script_AttackCollision.dll` from Gothic 3 `scripts`, set only the Hero None+2H `Normal_AddRaise`, `Quick_AddRaise`, and `Whirl_AddRaise` values to `On` in the live INI, then test Normal, both factual Quick sides, and full Whirl.

The first behavior fixture is Hero None+2H because matching Normal, Quick R/L and full Whirl Raise assets are already ready.

Do not reopen Collision/Speed, broaden AddRaise scope, add RaiseSpeed, or begin 1H generalization before the focused 2H native + New Balance acceptance gates close.

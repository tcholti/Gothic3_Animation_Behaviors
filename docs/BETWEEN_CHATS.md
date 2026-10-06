# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-06 — EV-445 attack movement runtime closure

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `development`

## Stable baseline

`main` remains Collision + Speed + Raise stable through EV-433.

## Attack movement — CLOSED / PASS

Research/architecture:
- EV-434–EV-440

Source implementation/review:
- production source lineage from `7393f390f30d1981a5065b6342a684cd590fbac9`
- EV-441 source review PASS
- EV-444 pre-release public key rename to `MovementOverride`

Runtime:
- EV-443 core 2H mechanism PASS
- EV-445 broad acceptance PASS

Public semantics:
```text
<Attack>_MovementOverride=Off
-> preserve native/New Balance movement

<Attack>_MovementOverride=0
-> no forward movement

<Attack>_MovementOverride=<positive number>
-> absolute configured attack movement distance
```

Broad EV-445 coverage:
- 1H, Torch+1H, Shield+1H, 1H+1H, 2H, Staff, Fist;
- Axe and Rapier custom/separated sets;
- Troll, Sabertooth and Demon representatives;
- all available Normal/Quick/Power/Whirl/SimpleWhirl/Hack/Pierce routes;
- representative Sprint routes;
- native + New Balance;
- Off and multiple strong numeric values.

Known boundary:
- an attack authored with movement value `0` in its animation name has no usable direction at the late movement seam, so MovementOverride cannot create forward movement;
- Rapier Quick is the confirmed example;
- changing its authored movement field to `100` made MovementOverride work with and without New Balance;
- this is documented in the shipping INI;
- no second hook/state/cache is justified.

No active attack-movement task remains.
No source change is pending.

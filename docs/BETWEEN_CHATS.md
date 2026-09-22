# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-22

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

## Frozen state

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`  
Source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`

Diagnostic SHA256:
`5AD5B33A8826DB5E78F4AECADC3FF48546E1C54ADA3BE9ED2BE9A54E6190E313`

Behavior SHA256:
`A806EC6523116286335A659735067B1AA6C581837B3E0D604E6271AC98079340`

## Current campaign

```text
Stage A body-contact                 PASS EV-365–EV-366
bad-skip C1-R1 stress               PASS EV-367
Stage B equipped/cumulative         PASS EV-368
Stage C modded/custom               ACTIVE
  zombie separation                PASS EV-370
  Axe separation                   PASS EV-371
  Rapier separation                PASS EV-372
  custom/multi-contact             NEXT
```

## EV-371 Axe separation

- Hero Axe: `Hero_..._Axe_...`, factual `It_Axe_Bardiche / UseType52`; clean no-target + combat coverage; marked Normal/Quick/Power/Whirl/Hack.
- Ogre/Orc/Stalker controls from EV-368 used `*_2H_*`; separation runs use `*_Axe_*` with the same factual raw52 sources.
- Ogre had 2 genuinely unmarked Quick executions; they stayed native and source state still balanced.
- all four Axe logs: zero anomaly/repair/divergence/error; clean unload.

## EV-372 Rapier separation

- Hero Rapier: `Hero_..._Rapier_...`, factual `It_1H_Epee_01 / UseType2`.
- clean no-target + Golem combat run.
- 48/48 player ownership observations marked: Normal/Quick/Power/Pierce.
- Epee: 53 openings = 53 cleanups; zero anomaly/repair/divergence/error; clean unload.
- Golem remained unmarked/native control.

Third-party constraint remains: Zombie Separation and Axe Separation conflict even without our DLL, so never use them as a combined acceptance environment.

## Next

Continue Stage C with the User's **fast/multi-contact authored animations and any remaining custom collision-authoring fixtures**. Then Stage D mixed stress.

No source change is authorized from EV-371/EV-372.

After closure, `research/raw/` contains only `Keep.txt`.

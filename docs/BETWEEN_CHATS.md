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

No source change absent new contradictory evidence.

## Current campaign

```text
Stage A body-contact                 PASS EV-365–EV-366
bad-skip C1-R1 stress               PASS EV-367
Stage B equipped/cumulative         PASS EV-368
Stage C modded/custom               ACTIVE
  native zombie baseline            PASS EV-369
  zombie separation                 PASS EV-370
  Axe separation                    NEXT
```

## EV-369 -> EV-370 comparison

Native zombie baseline:
- Mummy = Fist/raw8
- BenSala Zombie = `It_Pickaxe` / Axe raw52 on native shared 2H animation set
- UndeadPriest = Staff/raw12
- Gotha 1H+shield control added with EV-370 batch
- native motion identities = `Hero_...`

Zombie separation:
- motion identities become `Zombie_...`
- factual sources remain the same
- Mummy: 39 raw8 opportunities -> 23 contacts + 16 closes
- Zombie Pickaxe/raw52: 47 openings = 47 cleanups
- UndeadPriest Staff/raw12: 49 openings = 49 cleanups
- 1H+shield: same RIGHT sword + LEFT shield topology; sword 41 openings = 41 cleanups; RIGHT markers never spuriously activate shield
- unmarked separated assets remain native
- zero anomaly/repair/divergence/error; clean unloads

Disposition: **zombie separation PASS, no source change.**

## Separation-mod environment constraint

User reports zombie separation and Axe separation conflict when stacked: Axe separation prevents zombie-separation 2H animations from working.

This is outside our collision-mod acceptance responsibility. Validate independently:

```text
G3 Animation Behaviors + zombie separation
G3 Animation Behaviors + Axe separation
G3 Animation Behaviors + Rapier separation
```

Do not stack zombie separation with Axe separation for acceptance.

## Next

Disable zombie separation and test **Axe separation alone**. Compare factual Axe/raw52 behavior against the established native shared-2H baseline, then continue Rapier separation and custom/multi-contact fixtures.

`research/raw/` contains only `Keep.txt`.

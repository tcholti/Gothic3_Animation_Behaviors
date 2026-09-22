# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-22

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

## Frozen collision source

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Source:
`f1f5d2aad3edc3564a9a8b40541840b94f8fa903`

Diagnostic SHA256:
`5AD5B33A8826DB5E78F4AECADC3FF48546E1C54ADA3BE9ED2BE9A54E6190E313`

Behavior SHA256:
`A806EC6523116286335A659735067B1AA6C581837B3E0D604E6271AC98079340`

No source change is authorized absent newly demonstrated contradictory evidence.

## Comprehensive final-source status

```text
Stage A — non-weapon/body-contact       CLOSED/PASS EV-365–EV-366
supplemental bad-skip C1-R1 stress      PASS EV-367
Stage B — equipped/cumulative matrix    CLOSED/PASS EV-368
Stage C — modded/custom compatibility   ACTIVE
  native zombie baseline/control        PASS EV-369
  zombie animation separation           PASS EV-370
  Axe animation separation              NEXT
```

## EV-370 zombie-separation result

Direct native/modded evidence now exists.

Native baseline:
- EV-369 Mummy, Zombie Axe/raw52 and UndeadPriest Staff/raw12 use ordinary `Hero_...` animation identities.
- EV-370 adds the missing Gotha_SlaveZombie_02 1H+shield native control: RIGHT `It_1H_Sword_Rust_01` / UseType2 + LEFT skeleton shield, with `Hero_..._Shield_1H_...` motions.

With zombie separation enabled:
- Mummy keeps factual Fist/raw8 but motions become `Zombie_..._Fist_...`; 39 opportunities -> 23 exact contacts + 16 finalization closes.
- BenSala_Zombie_02 keeps factual `It_Pickaxe` / UseType52 but motions become `Zombie_..._2H_...`; 47 openings = 47 cleanups.
- UndeadPriest keeps factual Quarterstaff / UseType12 but motions become `Zombie_..._Staff_...`; 49 openings = 49 cleanups.
- Gotha_SlaveZombie_02 keeps the same sword+shield source topology but motions become `Zombie_..._Shield_1H_...`; sword physical state remains balanced at 41 openings = 41 cleanups and RIGHT-only marker traffic never spuriously activates the shield.
- genuinely unmarked separated assets correctly stay native instead of inheriting ownership from their old human-animation counterparts.
- player 2H coexistence remains healthy.
- zero marker anomaly/discovery, C1 repair/divergence, invariant/generation contradiction, explicit error/failure or unload problem.

Disposition: **PASS.** No collision source change.

## Third-party separation-mod composition constraint

The User reports:
- zombie animation separation and Axe animation separation cannot be used together cleanly;
- when Axe separation is enabled, the zombie-separation 2H animations do not work.

This is outside the current collision-mod responsibility. The acceptance goal is:

```text
Gothic3_Animation_Behaviors + zombie separation   -> validate
Gothic3_Animation_Behaviors + Axe separation      -> validate
Gothic3_Animation_Behaviors + Rapier separation   -> validate
```

It is **not** required that independent third-party separation mods work when stacked with each other. Do not combine zombie separation with Axe separation for the Axe acceptance run.

## Current responsibility — Axe separation

NEXT:
- disable zombie separation;
- enable the Axe-separation mod in its intended standalone environment;
- compare factual Axe/raw52 behavior against the established native shared-2H baseline;
- verify the separated Axe animation identities/markers drive the same factual equipped source correctly;
- continue player-weapon coexistence as useful.

After Axe separation, continue Rapier separation and fast/multi-contact/custom authoring fixtures.

A Stage-C failure must first be reduced to the smallest factual route before any source change.

After EV-370 closure, `research/raw/` contains only `Keep.txt`.

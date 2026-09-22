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
  native zombie baseline/control        CLOSED/PASS EV-369
  zombie separation mod                 NEXT / NOT YET RUN
```

## EV-369 correction and baseline

EV-369 was initially misclassified by Normal Chat as a zombie-separation-mod run. The User clarified that **no zombie separation mod was enabled**. The three logs are the native control baseline for the upcoming separation test.

Native runtime facts:
- Mummy: factual raw8 Fist / UseType8; marked Normal + Power healthy.
- BenSala_Zombie_02: exact `It_Pickaxe` / UseType52 (Axe/raw52); Quick/Power/Whirl/Normal/Hack healthy; 62 exact openings = 62 exact cleanups; one unmarked FinishingAttack/Hack stayed native.
- UndeadPriest: exact `It_Staff_Quarterstaff_01` / UseType12; Power/Whirl/Quick/Normal/Hack healthy; 64 exact openings = 64 exact cleanups.
- player 2H coexistence remained clean.
- zero marker anomaly/discovery, C1 repair/divergence, invariant/generation contradiction, explicit error/failure or unload problem.

Native animation-set rule supplied by the User and consistent with established evidence:
- native non-Staff two-handed weapons use the ordinary 2H animation set;
- factual Axe/UseType52 therefore appearing with `Hero_..._2H_...` motion identity is expected, not a mismatch;
- Staff uses its own animation set;
- a later Axe-separation mod will deliberately give Axe a unique animation set.

The native zombie actors likewise use ordinary human animation assets. EV-369 therefore establishes the exact baseline against which the forthcoming zombie-separation mod should be compared.

## Current responsibility — Stage C zombie separation

NEXT:
- enable the zombie animation-separation mod;
- repeat representative Mummy/Fist, Zombie Axe/raw52 and UndeadPriest Staff/raw12 combat routes where the mod provides separated assets;
- continue rotating a useful player weapon in the same runs;
- compare factual actor/action/source/UseType, marker acceptance, physical opening/cleanup, raw8 opportunity accounting and fallback behavior against EV-369.

After the zombie-separation comparison, continue the prepared Axe-separation, Rapier-separation and fast/multi-contact custom-animation fixtures.

A Stage-C failure must first be reduced to the smallest factual route before any source change.

`research/raw/` contains only `Keep.txt`.

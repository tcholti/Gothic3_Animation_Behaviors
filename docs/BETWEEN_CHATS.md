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
  zombie separation fixture             CLOSED/PASS EV-369
```

## EV-369 zombie-separation result

User reports the zombie-separation mod was active and supplied distinct zombie/mummy animation behavior.

Runtime facts:
- Mummy: factual raw8 Fist / UseType8, marked Normal + Power; 33 FIST opportunities across 28 attacks, including five later-FIST reopens; current opportunities fully resolved by 15 exact contacts + 13 lifecycle closes after those five earlier opportunities were superseded.
- BenSala_Zombie_02: exact `It_Pickaxe` / UseType52 (Axe/raw52), not raw3. Quick/Power/Whirl/Normal/Hack marker traffic balanced; 62 exact 5->7 openings = 62 exact 7->5 cleanups. One unmarked FinishingAttack-classified Hack stayed native.
- UndeadPriest: exact `It_Staff_Quarterstaff_01` / UseType12. Power/Whirl/Quick/Normal/Hack marker traffic balanced; 64 exact openings = 64 exact cleanups.
- player 2H coexistence remained clean in all three fixtures.
- zero marker anomaly/discovery, C1 repair/divergence, invariant/generation contradiction, explicit error/failure or unload problem.

Important observability qualification:
- despite the modded zombie behavior being active, diagnostic `CurrentMovementAni` still reports `Hero_...` motion identifiers for Mummy, Zombie and UndeadPriest;
- therefore EV-369 proves compatibility under the modded runtime but does not prove that Gothic exposes a separate zombie runtime motion-name/file namespace to this diagnostic layer.

No source change is justified.

## Current responsibility — remaining Stage C

Continue the User's planned mod/separation compatibility sequence. Prepared routes still include:
- Axe-separation;
- Rapier-separation;
- fast/multi-contact authored animations / other custom collision-authoring fixtures.

Use the same compositional test method:
- run the modded actor/source attacks;
- rotate useful player weapon attacks in the same combat;
- let diagnostics classify factual Action/family/source/UseType;
- do not infer semantics from the mod name or animation filename.

A Stage-C failure must first be reduced to the smallest factual route before any source change.

After EV-369 closure, `research/raw/` contains only `Keep.txt`.

# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-24

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
Stage C separation compatibility    PASS EV-369–EV-372
Stage D mixed stress                CLOSED/PASS EV-373–EV-374

standalone final-source regression  CLOSED/PASS
New Balance exact bundle regression CURRENT
```

## EV-374 second broad stress run

POP-07 package:
- raw SHA256 `BC7F1447C6F3B6BFE5C765C8A057EDFA81C3EDD205B9DAE7FC9F5DF60A4B06D6`
- 4,650,022 bytes / 20,907 lines
- exactly 1 anomaly-class timeline event

That single event is a bounded C1-R1 recovery:

```text
Actor = SlaveZombie
Source = It_Pickaxe / UseType52
Side = RIGHT
OutstandingBeforeFinalization = 1
ActualGroupBeforeRepair = 7
LivenessEstablished = 1
Outcome = REPAIRED_TO_ITEM_EQUIPPED
ActualGroupAfterRepair = 5
PhysicalCollisionChanged = 1
```

No marker anomaly/discovery, warning, error, mismatch/divergence, or C1 invariant warning was found.

Representative run windows include:
- player 2H vs ScorpionKing;
- dual-1H BOTH/LEFT/OFF traffic interleaved with Snapper raw8;
- Schakal raw8 while player 1H collision cleans normally;
- Axe/raw52 zombie traffic mixed with player 1H+torch;
- Sandcrawler raw8 mixed with player 2H/GetUpAttack collision;
- terminal dual-1H/native-fallback traffic plus TRex raw8 Sprint-origin opportunity -> exact native contact consumption.

The final shown equipped obligations are zero, the final TRex raw8 C1 is zero-outstanding, and `Script_FrameCollisionTest` unloads cleanly.

EV-374 itself contains no raw55/Troll route. Stage-D closure is compositional: exact frozen-source raw55+equipped coexistence is already established at EV-366 and raw8/raw55/equipped coexistence at EV-359–EV-364; EV-373/374 provide the missing long unscripted mixed churn.

Result: **PASS EV-374. Stage D and the standalone final-source regression are CLOSED. No source change.**

## Next — New Balance exact bundle compatibility

Test the exact New Balance 0.7 environment the User actually intends to run:

```text
New Balance installed as distributed
+ all normally used/distributed New Balance DLLs
+ relevant Jackydima collision DLLs, including Script_AttackCollision where applicable
+ exactly one Gothic3_Animation_Behaviors collision twin
- Zombie/Axe/Rapier separation mods for this gate
```

Separation mods are deliberately removed from the load order for the current compatibility campaign. Do not add a separation fixture to the New Balance matrix unless the User later opens that combined environment as a separate goal.

Across the compatibility gate cover several representative cases rather than one smoke:

```text
1. equipped marker combat
2. raw8 body-contact, including knockdown/get-up control
3. raw55 PhysicalFist/Troll
4. mixed gameplay stress
```

### Separation clarification

Earlier combined Zombie Separation + Axe Separation testing showed missing animation behavior specifically on zombie 2H/Axe use even when Gothic3_Animation_Behaviors was absent. The User now reports that the two mods otherwise worked together and considers the likely cause to be missing `Axe`-named animation assets for special zombies: those actors use axes but their separated zombie set supplies corresponding `2H` animations, leaving no asset after Axe-family separation. Copying the relevant zombie `2H` animations and renaming the family token to `Axe` is a plausible fix, but this explanation/fix has not been independently verified by project evidence. Do not describe the mods as fundamentally incompatible.

Do not omit a normally installed New Balance DLL pre-emptively. If a failure appears, reduce the exact DLL composition and factual route before considering any source change.

The detailed pre-New-Balance standalone test plan is archived; `COLLISION_TEST_PLAN.md` now owns the compatibility gate directly.

After EV-374 closure, `research/raw/` contains only `Keep.txt`.

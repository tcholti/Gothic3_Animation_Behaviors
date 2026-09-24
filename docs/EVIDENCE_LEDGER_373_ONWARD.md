# Gothic 3 Animation Behaviors — Evidence Ledger EV-373 Onward

**Status:** Active evidence/provenance ledger  
**Opened:** 2026-09-23

## Purpose

Record evidence after the EV-365–EV-372 final-source Stage-A/B/separation-compatibility volume.

This ledger is proof history, not the normal knowledge interface. Current established collision facts belong in `COLLISION_REFERENCE.md` and owning architecture/reference documents.

## Entry format

```text
### EV-xxx — short factual title

Observed:
- direct factual result(s)

Scope / limits:
- exact actor/action/source/build/test limits
- explicit non-claims when important

Provenance:
- source/log/commit/hash/path as applicable

Disposition:
- PASS / FAIL / NEGATIVE CONTROL / INCONCLUSIVE / SUPERSEDED
```

## Entries

### EV-373 — Broad mixed-gameplay stress run PASS with bounded lifecycle recoveries

Observed:
- The User performed one long natural mixed-gameplay stress session involving ordinary travel/combat churn, multiple fights and weapon/source changes. The User reported that everything looked and worked normally in-game throughout the run.
- The CORE diagnostic log contains 16,693 lines / 3,424,951 bytes and was processed through the POP-07 large-log evidence package. The package exposed exactly six high-level anomaly-class events: four `CORE C1 FINALIZATION ANOMALY / REPAIR` records and two `CORE MARKER ANOMALY / DISCOVERY` records.
- All four C1-R1 events were bounded exact-source recoveries that converged the live outstanding physical source from group7 back to Item_Equipped/group5. The observed repaired routes included player Staff/Halberd, Stalker Axe/raw52, ordinary 1H sword, and a small-axe source whose factual runtime UseType was 2. No repair divergence or unresolved equipped-source state was observed.
- Both marker anomaly/discovery records were fail-closed unsupported/late traffic rather than stale collision activation: one arrived at Action0 with no valid C1, and one arrived under unknown Action68 with no live equipped source. Neither established ownership or left collision active.
- Representative early/middle/late source windows were inspected around all six exceptional events. The run ended with ordinary 1H+shield traffic cleaning RIGHT from group7 to group5, all shown final obligations at zero, followed by `Script_FrameCollisionTest unloading cleanly`.
- No contradictory runtime evidence requiring a collision-source change was found.

Scope / limits:
- This is the first broad Stage-D mixed-stress run on the frozen source. It is a meaningful PASS for this run, but it does not by itself close all of Stage D; whether another broad stress run is useful is intentionally left for the next session.
- The four repairs corroborate the existing C1-R1 safety-net architecture under unscripted real gameplay. They do not imply that ordinary native cleanup never misses, and they do not reopen the separate paused `AttackContinuationProtection` responsibility.
- The User's positive gameplay observation is supporting evidence alongside the diagnostics; the PASS disposition rests on the diagnostic convergence/fail-closed behavior as well.

Provenance:
- frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- uploaded raw/derived evidence commit: `028c929005a9b1c35cb48e74070d1995c457ba06`;
- canonical raw source: `research/archive/2026.09.23_stress_collision_test.log`;
- raw Git blob: `95d57f8ee7ea1aa993b1b9773f31fca3be0afd40`;
- raw SHA256: `0B5596584ED39571CA89CE7CBD90BA7065DF134CF4274BB3C4ADFA7CA5782652`;
- raw size: 3,424,951 bytes / 16,693 lines;
- derived retrieval package: `research/derived/2026.09.23_stress_collision_test_large_log/` (60 complete-source parts, 17 signal parts).

Disposition:
- **PASS — Stage-D broad mixed-stress batch 1.**
- Stage D remains ACTIVE pending a deliberate next-session decision on whether another broad stress run is warranted.
- No source change is justified.

### EV-374 — Second broad mixed-gameplay stress PASS; Stage D and standalone regression CLOSED

Observed:
- The User published a second long broad stress session on the unchanged frozen collision source. The POP-07 package contains 20,907 complete source lines / 4,650,022 bytes.
- The package reports exactly **one** anomaly-class timeline event: one `CORE C1 FINALIZATION ANOMALY / REPAIR`. There are no `CORE MARKER ANOMALY / DISCOVERY` records in the event package.
- The single repair occurs for `SlaveZombie` with exact RIGHT `It_Pickaxe / UseType52`: `OutstandingBeforeFinalization=1`, `ActualGroupBeforeRepair=7`, `LivenessEstablished=1`, `Outcome=REPAIRED_TO_ITEM_EQUIPPED`, `ActualGroupAfterRepair=5`, `PhysicalCollisionChanged=1`. The repair converges safely and no repair divergence follows.
- Targeted whole-package checks found no `WARNING`, `ERROR`, `MISMATCH`, `DIVERGENCE`, or `C1 INVARIANT WARNING` records.
- Representative windows demonstrate substantial mixed churn rather than an isolated smoke: player 2H combat against ScorpionKing; dual-1H BOTH/LEFT/OFF marker traffic interleaved with Snapper raw8 opportunities; Schakal raw8 while player 1H collision activates/cleans; Axe/raw52 zombie traffic mixed with player 1H+torch; Sandcrawler raw8 while player 2H/GetUpAttack collision is active; and terminal dual-1H/native-fallback traffic alongside TRex raw8 Sprint-origin transport.
- The terminal TRex sequence opens a marked raw8 Sprint opportunity at factual Action9, survives into factual Action2/Power, consumes on exact native contact, retires permission, and finalizes `Outstanding=0`. The final shown equipped player sources also clean back to group5 / `Outstanding=0`, and the DLL ends with `Script_FrameCollisionTest unloading cleanly`.
- No contradictory runtime evidence requiring a collision-source change was found.

Scope / limits:
- EV-374 itself does **not** exercise a factual raw55/Troll route. Stage-D closure therefore does not claim that every collision mechanism appeared in this one log.
- Stage-D closure is compositional under the standing campaign rule: exact frozen-source raw55+equipped coexistence is already established by EV-366; raw8/raw55/equipped coexistence is established by the focused frozen-source acceptance EV-359–EV-364; EV-373 and EV-374 add two long unscripted mixed-gameplay sessions with substantial C1/actor/weapon churn and natural cleanup/repair opportunities.
- The successful C1-R1 repair is safety-net corroboration, not evidence that native cleanup should be replaced or that the separate paused `AttackContinuationProtection` responsibility should reopen.
- This is standalone collision evidence only. It does not certify New Balance / AttackCollision compatibility.

Provenance:
- frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- uploaded raw/derived evidence commit: `b6661547bf509ffeebec8f055ada7f857fd835fb`;
- canonical raw source after POP-06 closure: `research/archive/2026.09.24_stresstest_collision_2.log`;
- raw Git blob: `f319500a0ebbf0f7d82be5e6e057fd89e478698c`;
- raw SHA256: `BC7F1447C6F3B6BFE5C765C8A057EDFA81C3EDD205B9DAE7FC9F5DF60A4B06D6`;
- raw size: 4,650,022 bytes / 20,907 lines;
- derived retrieval package: `research/derived/2026.09.24_stresstest_collision_2_large_log/` (82 complete-source parts, 18 signal parts).

Disposition:
- **PASS — Stage-D broad mixed-stress batch 2.**
- **Stage D mixed stress CLOSED/PASS EV-373–EV-374.**
- **Standalone final-source collision regression CLOSED/PASS through EV-374.**
- New Balance exact distributed-bundle compatibility becomes the current gate.
- No source change is justified.

### EV-375 — Zombie + Axe separation asset-gap remedy PASS

Observed:
- The User tested the proposed remedy for the earlier combined Zombie Separation + Axe Separation zombie 2H/Axe animation gap: corresponding zombie `2H` animation assets were copied and the animation-family token was changed to `Axe` so Axe Separation could resolve an Axe-named zombie animation.
- Runtime directly shows `BenSala_Zombie_02` using the new `Zombie_..._Axe_...` motion family while the factual equipped source remains `It_Pickaxe / UseType52`.
- Marked copied/renamed Normal, Power and Whirl animations are detected and accepted. Representative examples include `Zombie_Stand_None_Axe_P0/P1_Attack...`, `Zombie_Stand_None_Axe_P0/P1_PowerAttack...`, and `Zombie_Parade_None_Axe_P0_WhirlAttack...`.
- Whirl exercises repeated authored collision timing on the copied/renamed asset: `RIGHT -> OFF -> RIGHT` is accepted, the exact Pickaxe/raw52 source opens/closes accordingly, and finalization returns `Outstanding=0`.
- The unmarked copied/renamed FinishingAttack/Hack asset remains native (`MarkerPresent=0 / RequiredMask=0 / SuppressNative=0`) and its factual Pickaxe/raw52 source still cleans normally.
- Whole-log checks found no `ANOMALY`, `DIVERGENCE`, `WARNING`, or `ERROR` records. The final shown source state is zero-outstanding and the diagnostic DLL unloads cleanly.

Scope / limits:
- This verifies the proposed asset-gap remedy for the tested Ben Sala zombie Axe/raw52 route and proves that Zombie Separation + Axe Separation can coexist on that route when matching `Zombie_..._Axe_...` assets are supplied.
- It does not claim every special-zombie animation asset or every third-party separation combination is automatically complete; missing assets would still need corresponding coverage.
- This is not a collision-source change. The result further confirms that the earlier observed failure was an animation asset-availability/naming problem, not a Gothic3_Animation_Behaviors collision incompatibility.

Provenance:
- frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- raw upload commit: `212de868ae1310e2b29d4ce9a947e0a629bfc3a2`;
- canonical archived runtime: `research/archive/2026.09.24_zombie_axe_asset_gap_fix.log`;
- raw Git blob: `f5a7e5d9c1d606cd32551606c2896c8a7fe1498a`;
- raw size: 88,785 bytes / 472 lines.

Disposition:
- **PASS — proposed Zombie+Axe separation asset-gap remedy verified for the tested route.**
- Combined Zombie + Axe separation is no longer treated as fundamentally incompatible.
- All separation mods may remain installed for the upcoming New Balance compatibility environment because that now matches the User's intended load order.
- No collision source change is justified.

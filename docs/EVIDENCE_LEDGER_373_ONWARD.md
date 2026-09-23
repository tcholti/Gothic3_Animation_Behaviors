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

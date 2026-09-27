# Gothic 3 Animation Behaviors — Evidence Ledger EV-384 Onward

**Status:** Active evidence/provenance ledger  
**Opened:** 2026-09-27

## Purpose

Record evidence after the closed EV-380–EV-383 volume.

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

### EV-384 — Broad intended-stack New Balance mixed-gameplay compatibility stress PASS

Observed:
- The User performed the planned broad mixed-gameplay New Balance compatibility run with varied combat, actor/source/weapon churn, weapon changes, movement into/out of settlements and ordinary gameplay transitions. The User reports that collision behavior looked correct throughout the run.
- The canonical runtime artifact is 4,189,040 bytes / 20,550 lines and was processed with the established `Prepare-Log.cmd` workflow. The derived manifest binds the package to source SHA256 `864DF10D88267616E3B4BA39BA7897E28318E773DEC6C2BEBDD5ADC1D8BC7A2D`.
- Whole-run processed counts contain 27 `CORE C1 FINALIZATION ANOMALY / REPAIR` events and 5 `CORE MARKER ANOMALY / DISCOVERY` events.
- All five indexed marker anomalies are Whirl-family callbacks rejected fail-closed as `REJECTED_C1_GENERATION_INCONSISTENCY`. Reviewed events include stale RIGHT and OFF callbacks; the rejection does not authorize a new physical opening and matches the established generation-safety behavior rather than exposing a new collision-policy contradiction.
- Bounded C1-R1 samples cover single-source and dual-source obligations. When an exact owned source remains outstanding at finalization, the repair outcome is `REPAIRED_TO_ITEM_EQUIPPED`, the requested group is 5, and the observed group after repair is 5. The dual-source sample restores both RIGHT and LEFT sources independently. A late-run sample around source line 20231 shows the same convergent repair behavior, with no sampled `REPAIR_DIVERGED_FROM_ITEM_EQUIPPED` outcome.
- The final run tail remains healthy: the last observed player collision opportunity opens group5 -> group7, native cleanup returns group7 -> group5 with `Outstanding=0`, C1 finalization is `NO_OP_NO_OUTSTANDING`, and `Script_FrameCollisionTest` unloads cleanly.
- No production source file changed between the EV-382 Normal raw55 correction and this runtime-evidence tail; EV-383 and EV-384 therefore exercise the same accepted collision behavior lineage rather than a silently altered implementation.

Scope / limits:
- This is broad representative compatibility evidence for the User's current intended New Balance 0.7 distributed stack plus the project separation/compatibility environment described by `COLLISION_TEST_PLAN.md`; it is not a claim about every possible third-party DLL/mod combination.
- The five Whirl generation-mismatch anomaly records are expected fail-closed stale-callback handling. They do not justify widening the marker contract or weakening generation checks.
- The 27 finalization/repair records are not treated as failures merely because the diagnostic calls them anomalies/repairs; correctness is determined by exact-source bounded repair convergence and absence of divergence/stale ownership.
- The large raw log is canonical provenance only after processing. Routine analysis must use the committed derived package and open only specifically identified `full_source_part_*` context when required by a flagged event.
- This evidence closes the broader New Balance full-stack compatibility gate. It does not replace the still-required standalone/no-New-Balance post-compat raw55 sentinel.

Provenance:
- final behavior source change before this evidence tail: `a31c66b97e45c27d0739b7df51252d33f490e7e1`;
- latest deployed diagnostic SHA256 inherited from EV-382: `81CF4C99BDA65EA6FBBC02839680E83B719B6E535407EB604E6AD015B038F2D3`;
- broad stress upload commit: `00594cd80e4d22c099f290bcdfcf2d0ba4e698d0`;
- canonical archived raw: `research/archive/2026.09.27_newbalance_stresstest.log`, Git blob `dd220273e14aac38c794b2e5472925f934b63099`;
- canonical raw SHA256: `864DF10D88267616E3B4BA39BA7897E28318E773DEC6C2BEBDD5ADC1D8BC7A2D`;
- derived retrieval package: `research/derived/2026.09.27_newbalance_stresstest_large_log/`;
- compact whole-run surfaces: `manifest.txt`, `event_counts.tsv`, `event_timeline_part_001.tsv`, `full_source_index.tsv`;
- specifically reviewed processed context: marker anomalies around source lines 9625, 9846, 14359, 16180 and 19483; repair samples around 4389, 5464, 16156 and 20231; final tail through line 20550.

Disposition:
- **PASS — BROAD REPRESENTATIVE / FULL INTENDED-STACK NEW BALANCE COMPATIBILITY CLOSED FOR THE TESTED ENVIRONMENT.**
- No source correction is indicated by this stress run.
- **NEXT GATE:** standalone/no-New-Balance post-compat raw55 sentinel, beginning with the planned Troll/raw55 control without New Balance.
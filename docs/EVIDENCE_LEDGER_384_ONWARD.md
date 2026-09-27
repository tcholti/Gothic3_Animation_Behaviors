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

### EV-385 — Standalone raw55 sentinel exposes Sprint-origin second-FIST current-SPRINT/SP1 compatibility hole

Observed:
- The User published four BlackTroll/raw55 runs in the standalone/no-New-Balance sentinel environment: double-FIST authoring at frames `1+3`, `1+8`, and `1+15`, plus a single-FIST control set with each marker placed appropriately for its animation.
- The `1+3` run repeatedly exposes one exact failure class. Four distinct Sprint-origin executions (C1=19, 30, 48, 68) accept marker1 while factual `Action9 / SPRINT / SP1`, suppress the premature native opening, and perform the one authored exact RIGHT `TrollFist` raw55 `5 -> 7` opening. Marker2 then arrives in the same C1 while still factual `Action9 / SPRINT / SP1`, with RIGHT already group7, and is rejected as `REJECTED_UNSUPPORTED_HIT`; `AcceptedFistCount` remains 1, `GroupRequested=0`, and `ClearTriggeredList=0`.
- Representative C1=19 places marker1 at `StateTime=2.848456` and marker2 at `StateTime=2.933686`. The rejected marker2 does not corrupt lifecycle state: native damage can still occur from the first opportunity, Gothic later cleans exact RIGHT `7 -> 5`, the outstanding obligation reaches zero, and C1 finalizes `NO_OP_NO_OUTSTANDING`.
- The `1+8` and `1+15` runs contain zero `CORE MARKER ANOMALY / DISCOVERY` and zero `REJECTED_UNSUPPORTED_HIT` records. In reviewed Sprint-origin executions, marker1 is factual `SPRINT/SP1` and opens once; before marker2 the same C1 has transitioned to factual `POWER/SP1`, where marker2 is accepted as clear-only rearm (`AcceptedFistCount=2`, `GroupRequested=0`, `ClearTriggeredList=1`) and ordinary native cleanup returns group7 -> group5.
- The single-marker run also contains zero marker anomalies. Repeated standalone Sprint-origin single-FIST executions accept factual `SPRINT/SP1`, perform the authored opening, may produce native damage, and clean normally to group5.
- Across all four logs there are no `C1 INVARIANT WARNING` records and no `CORE C1 FINALIZATION ANOMALY / REPAIR` records. The observed failure is therefore a narrow repeated-marker eligibility rejection, not a lifecycle/cleanup/generation failure.
- Normal and Quick marked traffic in the same batch remains healthy. No factual `OriginFamily=POWER` execution was found in these four logs, and no unmarked raw55 fixture was included, so the true-Power and native-fallback portions of the standalone sentinel remain unclosed.
- Source review identifies the exact current gate responsible for the rejection: `PhysicalFistCollision::IsSecondFistAllowed()` permits Sprint-origin marker2 under current POWER at explicit SP1/SP2, but under current SPRINT permits SP2 only. EV-385 now directly proves current-SPRINT/SP1 can be legitimate standalone same-C1 second-FIST traffic.

Scope / limits:
- This finding applies to the tested BlackTroll/raw55 standalone/no-New-Balance route on the same post-compatibility source lineage used for EV-384.
- It does not justify a generic StatePosition range, family-independent widening, more than two FIST markers, new hooks, queues/timers, hit flags, custom damage, or any change to first-FIST ownership.
- The existing fail-closed rejection and native cleanup remain safe. The defect is functional compatibility for an evidence-backed authored second-contact opportunity, not unsafe stale ownership.
- This batch does not complete the standalone sentinel because true-Power-origin single/double controls and unmarked raw55 native fallback still require final-candidate validation.

Provenance:
- behavior source under test: `a31c66b97e45c27d0739b7df51252d33f490e7e1` plus documentation/evidence-only lineage through the pre-upload checkpoint;
- runtime upload commit: `f686f7ed0cbd069010b35e1c6004b49b33676fb0`;
- `1+3`: `research/archive/2026.09.27_blacktroll_all_double_markers_1_3.log`, Git blob `60d732641081f0aaa63f00e3b21e06f43ab68019`;
- `1+8`: `research/archive/2026.09.27_blacktroll_all_double_markers_1_8.log`, Git blob `4b6133f96029bf2ed751070f7ec5af9c60823d00`;
- `1+15`: `research/archive/2026.09.27_blacktroll_all_double_markers_1_15.log`, Git blob `1cf09dba3811bbdebd090a7510ca647e6a15d876`;
- single-FIST control: `research/archive/2026.09.27_blacktroll_all_single_marker.log`, Git blob `4c002d5a80740a608f0a262761ec5f41187bff64`.

Disposition:
- **PARTIAL FAIL / CORRECTION REQUIRED — standalone Sprint-origin marker2 at factual current `SPRINT/SP1` is legitimate supported traffic but the current compatibility rule rejects it.**
- **IMPLEMENTATION BASIS READY:** preserve current-Power explicit `{SP1,SP2}` and extend the same Sprint-origin second-FIST branch to current-Sprint explicit `{SP1,SP2}`. Do not use a generic `>=1` rule.
- Production collision migration remains blocked. After the bounded correction is implemented and independently reviewed, runtime validation must directly retest standalone `1+3`, preserve the `1+8`/`1+15` continuation behavior, recheck New Balance representative Sprint SP2/transition behavior because source changed after EV-384, and finish the still-missing true-Power/unmarked standalone sentinel controls.
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
- No production source file changed between the EV-382 correction and this runtime-evidence tail; EV-383 and EV-384 therefore exercise the same accepted collision behavior lineage rather than a silently altered implementation.

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
- The `1+3` run repeatedly exposes one exact failure class. Four distinct Sprint-origin executions accept marker1 while factual `Action9 / SPRINT / SP1`, suppress the premature native opening, and perform the one authored exact RIGHT `TrollFist` raw55 `5 -> 7` opening. Marker2 then arrives in the same C1 while still factual `Action9 / SPRINT / SP1`, with RIGHT already group7, and is rejected as `REJECTED_UNSUPPORTED_HIT`; `AcceptedFistCount` remains 1, `GroupRequested=0`, and `ClearTriggeredList=0`.
- Representative C1=19 places marker1 at `StateTime=2.848456` and marker2 at `StateTime=2.933686`. The rejected marker2 does not corrupt lifecycle state: native damage can still occur from the first opportunity, Gothic later cleans exact RIGHT `7 -> 5`, the outstanding obligation reaches zero, and C1 finalizes `NO_OP_NO_OUTSTANDING`.
- The `1+8` and `1+15` runs contain zero marker anomalies and zero `REJECTED_UNSUPPORTED_HIT` records. In reviewed Sprint-origin executions, marker1 is factual `SPRINT/SP1` and opens once; before marker2 the same C1 has transitioned to factual `POWER/SP1`, where marker2 is accepted as clear-only rearm (`AcceptedFistCount=2`, `GroupRequested=0`, `ClearTriggeredList=1`) and ordinary native cleanup returns group7 -> group5.
- The single-marker run also contains zero marker anomalies. Repeated standalone Sprint-origin single-FIST executions accept factual `SPRINT/SP1`, perform the authored opening, may produce native damage, and clean normally to group5.
- Across all four logs there are no `C1 INVARIANT WARNING` records and no `CORE C1 FINALIZATION ANOMALY / REPAIR` records. The observed failure is therefore a narrow repeated-marker eligibility rejection, not a lifecycle/cleanup/generation failure.
- Normal and Quick marked traffic in the same batch remains healthy. No factual `OriginFamily=POWER` execution was found in these four logs, and no unmarked raw55 fixture was included, so the true-Power and native-fallback portions of the standalone sentinel remain unclosed.
- Source review identifies the exact current gate responsible for the rejection: `PhysicalFistCollision::IsSecondFistAllowed()` permits Sprint-origin marker2 under current POWER at explicit SP1/SP2, but under current SPRINT permits SP2 only. EV-385 directly proves current-SPRINT/SP1 can be legitimate standalone same-C1 second-FIST traffic.

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

### EV-386 — Corrected standalone marked raw55 final-candidate matrix PASS

Observed:
- The User published four BlackTroll/raw55 runs in the standalone/no-New-Balance environment on the corrected final candidate: double-FIST authoring at `1+3`, `1+8`, and `1+15`, plus a single-FIST control set.
- The `1+3` run repeatedly proves the exact EV-385 correction. Sprint-origin marker1 is factual `SPRINT/Action9/SP1`, suppresses the premature native opening, and performs the one RIGHT raw55 `5 -> 7` opening. Marker2 remains factual `SPRINT/Action9/SP1` in the same C1 and is now accepted clear-only: `AcceptedFistCount=2`, `GroupRequested=0`, `ClearTriggeredList=1`, source remains group7, then native cleanup returns group7 -> group5 with `Outstanding=0` and `NO_OP_NO_OUTSTANDING` finalization.
- The `1+8` and `1+15` runs preserve the established continuation route. Marker1 is `SPRINT/SP1`; marker2 arrives after the same-C1 Action9 -> Action2 transition as current `POWER/SP1`, is accepted clear-only (`GroupRequested=0`, `ClearTriggeredList=1`), and cleanup converges normally.
- The `1+15` run contains factual true-Power-origin double-FIST traffic. Representative C1=15 accepts first `POWER/SP1` FIST with `earlyOpeningSuppressed=1` and the one group5 -> group7 opening, then accepts second `POWER/SP1` FIST clear-only with no second physical opening.
- The single-marker run contains repeated factual Sprint-origin `SPRINT/SP1` controls and factual true-Power `POWER/SP1` controls. Each accepted single FIST opens the exact RIGHT raw55 source and cleans normally.
- Across all four artifacts, bounded searches find zero `REJECTED_*` records and zero `ANOMALY` records. Reviewed tails return TrollFist group7 -> group5, clear exact outstanding obligations to zero, finalize `NO_OP_NO_OUTSTANDING`, and unload `Script_FrameCollisionTest` cleanly.
- No `MarkerPresent=0` BlackTroll/raw55 route exists in any of these four marked artifacts. Therefore this batch does not prove the separate unmarked raw55 native-fallback sentinel.

Scope / limits:
- This is a PASS for the corrected **marked** standalone raw55 final-candidate matrix.
- It closes the EV-385 current-SPRINT/SP1 second-FIST defect and closes the previously missing factual true-Power single/double marked controls.
- The standalone diagnostic sentinel remains open only for one representative unmarked raw55 native-fallback control.
- This evidence makes no New Balance claim. The User reports having already run the same matrix under New Balance; those logs remain unpublished/unreviewed at EV-386.

Provenance:
- reviewed behavior source: `1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0`;
- final-candidate behavior SHA256: `D5BECB2C32A9766B1B444CB5864C0C30C9AC251A1679F605127F4D7318900B78`;
- final-candidate diagnostic/live SHA256: `AEF0E18205BAA9258D50B2E934173C48B845E0F1B9A9F425D622F4E4598EE773`;
- runtime upload commit: `769b7f6ae74e156f8eec22aee51c60b6b636c6db`;
- archive transaction commit: `526d0e685dfa6ea033fd175d91668888eb6341a8`;
- `1+3`: `research/archive/2026.09.27_blacktroll_all_double_markers_1_3_test2.log`, Git blob `69b9c8c65f3afa59911f5075a9a28369f9663d27`;
- `1+8`: `research/archive/2026.09.27_blacktroll_all_double_markers_1_8_test2.log`, Git blob `da6c405dbc6f37788cacebaa0fea753c4a6867f0`;
- `1+15`: `research/archive/2026.09.27_blacktroll_all_double_markers_1_15_test2.log`, Git blob `64d361fa6f72c4f5b48b4fe52d6515514df14d69`;
- single-FIST: `research/archive/2026.09.27_blacktroll_all_single_marker_test2.log`, Git blob `30cd1bdd44b65e122ce6a98c2624129af2ffd018`.

Disposition:
- **PASS — CORRECTED MARKED STANDALONE RAW55 FINAL-CANDIDATE MATRIX.**
- **EV-385 ELIGIBILITY DEFECT CLOSED.**
- **NEXT STANDALONE ITEM:** one representative unmarked raw55 native-fallback control. After that passes, process the already-run New Balance final-candidate regression before behavior-only release-purity validation.

### EV-387 — Final-candidate standalone unmarked raw55 native fallback PASS

Observed:
- The User published one standalone/no-New-Balance BlackTroll/raw55 final-candidate run with authored FIST markers removed.
- Repeated BlackTroll Quick, Normal, factual true Power (`Action2`), and Sprint (`Action9`) attacks are observed with `MarkerPresent=0`, `FistMarkers=0`, and `SuppressNative=0`.
- Bounded searches find zero `RAW55_PHYSICAL_FIST_MARKER` records and zero `RAW55_PHYSICAL_FIST_NATIVE_OPEN_SUPPRESSED` records. G3AB therefore does not claim, physically open, or rearm these unmarked raw55 executions.
- Gothic native behavior performs the exact RIGHT raw55 group5 -> group7 opening; native contact/damage may occur; ordinary native cleanup returns group7 -> group5 with `Outstanding=0` and `NO_OP_NO_OUTSTANDING` finalization.
- Whole-artifact bounded searches find zero `REJECTED_*`, zero `ANOMALY`, and zero `C1 INVARIANT` matches. The diagnostic twin unloads cleanly.

Scope / limits:
- This is the final-candidate standalone/no-New-Balance BlackTroll/raw55 native-fallback control.
- Combined with EV-386, it closes the corrected final-candidate standalone diagnostic raw55 sentinel.
- It does not close the still-required final-candidate New Balance regression or the later diagnostics-free behavior-twin release-purity gate.

Provenance:
- reviewed behavior source: `1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0`;
- final-candidate diagnostic/live SHA256: `AEF0E18205BAA9258D50B2E934173C48B845E0F1B9A9F425D622F4E4598EE773`;
- runtime upload commit: `3b1b9498682284f6612c93e3d878745e1dc8791d`;
- archive transaction commit: `8cb7ef92e3d0af1e33a6ac9223d748bf463d939f`;
- canonical archived raw: `research/archive/2026.09.27_blacktroll_all_single_no_markers_test2.log`;
- Git blob: `71337df2faec9766b065196f70828d6ce0c22d44`.

Disposition:
- **PASS — FINAL-CANDIDATE STANDALONE/NO-NEW-BALANCE DIAGNOSTIC RAW55 SENTINEL CLOSED THROUGH EV-386–EV-387.**
- **NEXT:** review the User's already-recorded final-candidate New Balance/raw55 logs through POP-06 bounded retrieval; do not rerun them. The focused regression must preserve the compatibility-sensitive Sprint SP2 / Action9 -> Action2 semantics before behavior-only release-purity validation.
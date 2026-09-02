# Power + Pierce Marker Validation Checkpoint

**Date:** 2026-09-03  
**Branch:** `docs/collision-source-evidence`  
**Purpose:** Compact retrieval checkpoint for the already-committed raw runtime evidence validating the newly implemented PowerAttack and PierceAttack marker adapters. Raw logs remain canonical evidence.

## Implementation baseline

- Remaining melee marker adapters + optional Hack routing implementation: `f0d929c90fbe086f44f66f91a2523904d06c3903`
- Generic diagnostic StatePosition before/after marker logging: `7c31784c5ef86bc79b54d573144b8e40f33e5e6b`

Implemented bookkeeping relevant here:

```text
Power ordinary/non-Dual -> StatePosition 1
Power Dual              -> StatePosition 2
Pierce                   -> StatePosition 1
```

Markers retain the shared RIGHT / LEFT / BOTH / OFF exact-set architecture, generation-scoped occurrence/dedupe bookkeeping, repeated-contact rearm, native cleanup-first lifecycle behavior, and C1-R1 terminal safety.

---

## PowerAttack validation — CLOSED/PASS for current marker-expansion stage

### Ordinary isolated validation

Raw:

`research/raw/2026-09-02_power_marker_adapter_isolated_validation.log`

Commit:

`369f3ad6626417e319518c915f63b601b07fc60b`

Validated:

- marked Power ownership and native-callback suppression;
- ordinary 1H / 2H / Staff StatePosition `0 -> 1`;
- Dual Power StatePosition `0 -> 2`;
- Dual exact-set programs `BOTH -> LEFT/RIGHT -> OFF -> BOTH`;
- both sources can be activated/rearmed independently;
- marker-free controls remain native;
- final-update replay callbacks are safely rejected by authored-occurrence/same-update duplicate guards;
- natural phase completion cleans exact live sources `7 -> 5`;
- no C1 repair, invariant warning, or finalization physical change was required;
- User visually confirmed target contacts worked.

### Legitimate-interruption cleanup validation

Raw:

`research/raw/2026-09-02_power_legitimate_interruption_cleanup_validation.log`

Raw commit:

`2f602453ae38fea120bbf5ff78c2d9fc953c4d99`

Derived package commit:

`a80162099f4248a446199b7f46ea981cc24a8de8`

Validated strong post-marker legitimate interruption cleanup for Dual, 2H and Staff, with an additional non-P0 1H Power case showing the same pattern. Native reaction cleanup returned live marker-owned source(s) `7 -> 5` before the subsequent reaction generation; C1 recorded cleanup fulfillment and remained a no-op fail-safe.

Exact marked 1H P0 post-marker interruption was not captured because its later marker was often preceded by the interruption. This does not contradict the shared behavior proven by the other cases.

---

## PierceAttack validation — CLOSED/PASS for current marker-expansion stage

### Test 1 — native Pierce motions / native source correspondence

Raw:

`research/raw/2026-09-02_pierce_native_marker_adapter_isolated_validation.log`

Commit:

`7accaaf9b254a9121ec111e02f65f9e8fca2d3a9`

Validated:

```text
Dual P0 Pierce -> RIGHT
Dual P1 Pierce -> LEFT
Pierce accepted marker -> StatePosition 1
```

Marked Pierce suppressed the native callback, activated the exact expected source `5 -> 7`, and natural cleanup returned it `7 -> 5`. Normal attacks used between Dual stances remained separate executions. User visually confirmed collision with the opponent.

A repeated-execution diagnostic nuance was observed: some later Pierce executions processed markers correctly without another fresh `MARKER OWNERSHIP DECISION` block.

### Test 2 — Power motion / multi-marker program executed under Pierce action

Raw:

`research/raw/2026-09-02_pierce_power_motion_multi_marker_validation.log`

Commit:

`c4026282b9277738468a6caf99f49b8f484f72dd`

The Dual Pierce resources used the previously tested Power motion content and marker programs while runtime action remained Pierce (`11`):

```text
P0: BOTH -> LEFT  -> OFF -> BOTH
P1: BOTH -> RIGHT -> OFF -> BOTH
```

Validated:

- native action/family remained Pierce;
- authored markers, not stock Pierce source assumptions, controlled RIGHT / LEFT / BOTH / OFF collision behavior;
- BOTH activated both exact Dual weapon sources;
- BOTH-to-single retired only the opposite source;
- OFF closed the marker-owned window;
- final BOTH reactivated/rearmed both sources;
- StatePosition remained `1`, proving bookkeeping follows Pierce action rather than copied Power motion content;
- duplicate/replay protection remained correct;
- all live sources cleaned naturally without C1 repair;
- ordinary 1H Pierce was also tested with and without target;
- User repeatedly confirmed all authored Dual contacts could connect against the selected target, including runs where RMB release timing was varied after Hit began.

### Test 3 — legitimate interruption cleanup under custom multi-marker Pierce

Raw:

`research/raw/2026-09-02_pierce_power_motion_interruption_cleanup_validation.log`

Commit:

`327fb20247eedb443e57f4b7fe1d4c644a1e6655`

Strong qualifying cases were captured.

Generation 106:

```text
Pierce Hit
-> BOTH accepted
-> RIGHT 5 -> 7
-> LEFT  5 -> 7
-> legitimate interruption
-> RIGHT 7 -> 5
-> LEFT  7 -> 5
-> both C1 obligations fulfilled
-> Stumble generation
```

Generation 188 additionally proved interruption after `BOTH -> LEFT`, where only the remaining LEFT source was live and Gothic cleaned that exact source before Stumble.

No C1 repair or physical finalization change was required.

### Pierce target/reaction semantics observation

During multi-target combat the User observed that Pierce contacts affected the selected/focused target while another nearby target was not hit by the same Pierce swings. This resembles the earlier Fist target-gating observation but is not yet claimed to have the same internal cause.

The User separately confirmed that humanoid targets which normally perform the distinctive long Pierce stumble still performed that same reaction when hit by the custom Power-motion Pierce animations, and every successful authored swing against the selected target produced the expected reaction sound.

Current bounded interpretation:

```text
G3AB markers control WHEN and WHICH physical weapon source is live.
Pierce action 11 retains native target/reaction semantics.
```

This makes alternate authored stabs using RIGHT, LEFT or both weapons a valid design space, while broad sweeping Pierce animations may not behave like generic multi-target attacks. The hypothesis that focused-target restriction exists specifically for balance protection remains unproven design intent and should not be stated as fact.

### Test 4 — New Balance bad-skip control + Jackydima Script_AttackCollision compatibility

Raw:

`research/raw/2026-09-03_pierce_native_marker_newbalance_badskip_control.log`

Commit:

`fd91f90a255559923f2ada7e83355333177931f0`

Runtime configuration included New Balance with its bad-skip prevention and Jackydima `Script_AttackCollision`. No target was used. The User performed four accepted Pierce executions in each configuration:

```text
1H                 x4
Torch + 1H         x4
Shield + 1H        x4
Dual P0 / RIGHT    x4
Dual P1 / LEFT     x4
```

Total: 20 accepted Pierce marker executions.

All accepted markers had valid C1 generation bookkeeping and `StatePositionAfterMarker: 1`; the expected exact source activated `5 -> 7` and later cleaned `7 -> 5`. Torch and Shield were factually resolved as LEFT equipped sources but were not accidentally activated by RIGHT-only Pierce markers. Dual P0/P1 preserved the expected RIGHT/LEFT distinction. No `C1GenerationValid: 0`, `RepairAttempted: 1`, or `PhysicalCollisionChanged: 1` signal occurred, and the diagnostic unloaded cleanly.

Therefore Pierce marker handling is runtime-compatible with the **tested** New Balance + Jackydima Script_AttackCollision configuration across these Pierce equipment cases. This is Pierce-specific compatibility evidence, not blanket certification of every callback/family in Script_AttackCollision.

The diagnostic cadence observation persisted: the 20 healthy accepted executions produced one fresh `MARKER OWNERSHIP DECISION` per distinct Pierce motion rather than one per execution. Because New Balance bad-skip prevention was active, bad skip is not required for the observation and should no longer be treated as its likely explanation. A relationship to native Pierce target/effect semantics is possible but unproven.

Because all execution bookkeeping, source behavior and cleanup remained correct, no further investigation of this diagnostic cadence is currently justified unless future behavior contradicts the accepted results.

---

## Current closure and next step

```text
PowerAttack  -> current marker-expansion validation CLOSED/PASS
PierceAttack -> current marker-expansion validation CLOSED/PASS

NEXT:
SimpleWhirl isolated validation
-> Hack isolated validation
-> combined marker/lifecycle regression
```

Do not reopen Power or Pierce merely to investigate benign diagnostic cadence or broaden already-covered incidental combat variation. Reopen only on concrete contradicting behavior/evidence.

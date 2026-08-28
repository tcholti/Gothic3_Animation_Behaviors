# Collision Lifecycle Test Plan

**Status:** Current staged validation plan  
**Updated:** 2026-08-28

## Purpose

Validate one general execution-level collision-cleanup model with the smallest tests that can falsify it. Broaden only when the current lifecycle question is resolved.

Earlier test chronology and superseded gate wording are preserved in:

`docs/archive/technical_2026-08-27/COLLISION_TEST_PLAN_pre_ia.md`

Exact established findings should be retrieved through `EVIDENCE_INDEX.md` rather than rerunning closed matrices.

---

## 1. Rules for the Current Test Phase

- diagnostics remain observational;
- do not implement production cleanup while the general finalization boundary is unresolved;
- do not add Staff/Quick/Whirl/block-timeout-specific cleanup branches;
- preserve native behavior for unmarked controls;
- compare one conceptual variable at a time where practical;
- visual observation may identify a reproduction, but lifecycle conclusions come from logs/source evidence;
- do not repeat already-closed marker/source tests unless a later implementation could have regressed them;
- prefer reusing the current diagnostic before adding another hook;
- preserve raw runtime logs exactly as produced; do not treat `git diff --check` warnings in raw logs as a reason to edit them.

Authoritative live diagnostic DLL:

```text
E:\SteamLibrary\steamapps\common\Gothic 3\scripts\Script_FrameCollisionTest.dll
```

Before treating a rebuilt diagnostic run as evidence, verify the built and live DLLs are identical or confirm the intended startup banner. Do not keep backup/renamed matching DLLs in the live `scripts` directory.

---

## 2. Closed Gate Summary — B6 / B7 / B7b

### B6 — deferred ProcessScript candidate rejected

B6 established that clean completion exposes useful `sAICombatMoveInstr -> ProcessScript()` context, while an armed bad Whirl can disappear to Ambient without exposing the same useful replacement-time ScriptAdmin/SPU context. Therefore the replacement-triggered deferred-`ProcessScript()` strategy was rejected in its present form.

Evidence: EV-174–EV-181.

### B7 — explicit CombatMove FullStop proven

B7 proved:

```text
bad full Whirl
→ active sAICombatMoveInstr receives fullStop=true
→ no normal Whirl cleanup follows

legitimate Normal/Quick reaction
→ active sAICombatMoveInstr also receives fullStop=true
→ separate reaction cleanup later runs when offense had armed
```

Therefore FullStop is instruction termination, not collision cleanup.

Evidence: EV-182–EV-186.

### B7b — exact callers and tested Whirl abandonment mechanism resolved

B7b distinguishes the exact paths.

Tested bad player full Whirl:

```text
Use2 held beyond 2500 ms
→ Script_Game +0x633F1  PSRoutine::FullStop()
→ return +0x633F7
→ Script_Game +0x63409  PSRoutine::SetState(...)
→ SPU state stack / state-position / break-block bookkeeping reset
→ suspended Whirl ScriptFunction continuation discarded
→ ordinary +0x4E03C cleanup cannot be reached
→ armed source may remain Item_Attack(7)
```

Tested legitimate Normal/Quick reaction:

```text
Script_Game +0x2D0F2  PSRoutine::FullStop()
→ return +0x2D0F8 into reaction control
→ established +0x24AFF reaction cleanup when offense had armed
→ reaction continuation owns successor
```

This resolves the causal mechanism for the tested player full-Whirl held-Use2 stale-collision failure.

Evidence: EV-187–EV-189.

---

## 3. Gate B8 — CURRENT — Cross-Family State-Stack Abandonment

### Question

Earlier native evidence already proves stale collision in player Dual Quick (EV-162). The exact Whirl `+0x633F1 -> SetState` path must not be assumed universal.

> **When the known player Dual Quick bad skip occurs, does Gothic discard the suspended attack continuation through the same AIFullStop/SetState mechanism, through a different AIFullStop caller followed by another state/task replacement, or without AIFullStop at all?**

### Diagnostic

Use the currently deployed B7b diagnostic unchanged.

Relevant records already available:

```text
===== AIFULLSTOP CALLSITE =====
===== COMBATMOVE FULLSTOP STACK =====
```

Existing motion, StartRecover and collision-group records provide the supporting timeline.

Do **not** add another hook before this test.

### Controlled fixture

Use the same player Dual / 1H+1H Quick bad-skip reproduction previously established by B3b / EV-162.

Run one session:

```text
1. clean Dual Quick controls — 3 complete attacks
2. bad Dual Quick skip attempts — enough attempts to obtain several clear failures
3. prefer at least 3 armed stale failures where offensive collision had already been requested
4. pre-activation failures are useful negative controls but do not replace armed cases
5. after one armed stale case, brief idle/movement is optional supporting evidence
6. exit normally
```

Do not introduce a target/reaction comparison unless the known Dual Quick reproduction itself requires the established block/target condition. The variable under test is the bad Dual Quick teardown mechanism, not another reaction matrix.

Frozen raw filename:

```text
research/raw/2026-08-28_b8_player_dual_quick_state_stack_abandonment.log
```

### Interpretation

#### Outcome A — same exact Whirl caller

```text
armed bad Dual Quick
→ AIFullStop caller +0x633F7
```

Then the same held-Use2 branch is shared by at least full Whirl and Dual Quick. Correlate the subsequent state transition before claiming the complete `FullStop -> SetState` sequence generalizes.

#### Outcome B — different AIFullStop caller

```text
armed bad Dual Quick
→ AIFullStop occurs
→ caller differs from +0x633F7
```

Static-audit that exact caller next. Ask whether it also leads to `SetState`, `SetTask`, or another supported state-stack replacement that discards the suspended attack continuation.

Do not add runtime instrumentation until the static branch is understood.

#### Outcome C — no AIFullStop on armed bad Dual Quick

The Whirl-specific FullStop path does not generalize to Dual Quick. Return to the existing motion/state evidence and identify the alternative native state/task reset or instruction-abandonment route before adding a new diagnostic.

### Acceptance

B8 is successful when the known Dual Quick stale failure is classified into a concrete native continuation-loss mechanism strongly enough to answer whether **state-stack abandonment** is a general defect class rather than only a full-Whirl implementation detail.

---

## 4. Gate C1 — Prove a General Post-Native-Opportunity Finalization Checkpoint

Run only after B8 or later evidence identifies a sufficiently general terminal-execution mechanism.

First add a **diagnostic-only**, tightly gated one-shot checkpoint for an already-owned exact attack execution.

It must demonstrate:

1. it runs after clean ordinary native cleanup;
2. it runs after legitimate interruption cleanup;
3. it runs after bad teardown even when cleanup was absent;
4. unrelated processing is a no-op because no owned execution is finalizing;
5. the same execution is checked once, not repeatedly.

Do not perform fallback cleanup in C1. Establish ordering first.

---

## 5. Gate C2 — Minimal Cleanup Repair Prototype

Only after C1 proves the timing point.

```text
owned exact execution requested offensive collision
→ proven post-native-opportunity checkpoint
→ cleanup observed?
    yes -> retire/no-op
    no  -> perform native-equivalent repair for owned offensive source(s)
```

Initial cases:

1. clean native completion — no-op;
2. clean marked completion — no-op;
3. legitimate damage/reaction interruption — no-op;
4. known stale native bad teardown — repair;
5. known stale marked bad teardown — repair.

Repair must not create a second activation, duplicate list clear or unrelated state mutation.

---

## 6. Gate C3 — Can Offensive Collision Legitimately Survive Across Independent Hits?

Once a repair exists, challenge the invariant with representative native/unmarked chains:

- 1H Normal/Quick;
- Shield+1H Normal/Quick;
- Dual Normal/Quick;
- 2H Normal/full Whirl;
- Staff Normal/full Whirl.

Search for:

```text
Hit A requested offense
Hit A physically ended
Hit B is an independent execution
NO legitimate cleanup occurred between them
and persistence is intentionally native-correct
```

Interpretation:

- never observed legitimately → strengthens universal end guard;
- clearly intentional transfer → represent it before release;
- only seen in stale paths → supports guard, not an exception.

EV-181 is already a negative example of accidental carry.

---

## 7. Gate C4 — Source-Aware Fallback Decision

Prefer one execution-level obligation unless evidence proves independent partial-source cleanup.

Use Dual/multi-source cases to ask:

- can RIGHT clean while LEFT legitimately remains offensive after the same Hit ends?
- can one source fail independently while another cleans?
- must native-equivalent repair operate per source?

Adopt source-aware lifecycle state only if evidence requires it.

---

## 8. Gate C5 — Negative / No-Op Regression

Required if the final design uses a generic terminal checkpoint.

At minimum test:

- Fist;
- bow;
- crossbow;
- magic.

Expected result: complete no-op because no exact owned weapon-style offensive execution is finalizing.

Fist is especially important because it can share melee action enums without using the tested weapon-style `Item_Attack(7)` source model.

---

## 9. Gate C6 — Defensive Collision Semantics

Before release, if the chosen cleanup operation could affect defensive item state, test:

- weapon into weapon block;
- weapon into shield block;
- 2H/Staff block with obvious bounce;
- ParadeStumble/block-stumble.

Observe attacker/defender source/group requests around contact. Do not add defensive special cases unless evidence requires them.

---

## 10. Marker-Core Regression — Reuse Existing Fixtures

Re-run compact marker fixtures only after lifecycle changes that could plausibly affect them:

```text
RIGHT -> LEFT
BOTH -> RIGHT
RIGHT -> OFF -> RIGHT
BOTH -> LEFT -> OFF -> BOTH
```

Verify desired-set transition, source rearm, occurrence/replay guards, execution retirement and absence of unexpected native timer activation.

Do not rebuild the historical v0.10–v0.18 matrix unless a regression demands it.

---

## 11. Broad Regression — After the Lifecycle Model Is Chosen

Challenge the **one chosen rule** across:

- 1H;
- Shield+1H;
- Dual;
- 2H;
- Staff;
- Normal;
- Quick;
- Power;
- SimpleWhirl/full Whirl where applicable;
- player + controlled human NPC;
- marked + unmarked attacks;
- normal completion, chaining, damage interruption, blocking and known bad-skip conditions.

The matrix is evidence coverage, not a production branch matrix.

---

## 12. Success Criteria

Collision-lifecycle research is ready for production integration when evidence answers:

1. what constitutes an owned real attack-Hit execution;
2. what native transition proves that execution can no longer resume;
3. what creates the offensive collision obligation, including `7 -> 7` requests;
4. what timing point occurs after Gothic's legitimate cleanup opportunity even on bad teardown;
5. how native cleanup success is observed;
6. whether repair must be attack-wide or source-specific;
7. whether any legitimate native sequence carries offense across independent physical Hits;
8. whether defensive collision introduces a conflicting state;
9. whether unrelated Fist/ranged/magic processing remains a no-op;
10. whether marked and native activation converge on one end-of-Hit safety rule.

Only then should the stable lifecycle be integrated into `Script_G3AnimationBehaviors`.

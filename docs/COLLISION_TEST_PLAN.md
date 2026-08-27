# Collision Lifecycle Test Plan

**Status:** Current staged validation plan  
**Updated:** 2026-08-27

## Purpose

Validate the preferred execution-level collision-cleanup model with the smallest tests that can falsify it, then broaden only after the lifecycle boundary is proven.

Earlier test chronology and superseded gate wording are preserved in:

`docs/archive/technical_2026-08-27/COLLISION_TEST_PLAN_pre_ia.md`

Exact established findings should be retrieved through `EVIDENCE_INDEX.md` rather than re-running old matrices without a reason.

---

## 1. Rules for the Current Test Phase

- diagnostics remain observational;
- do not implement production cleanup while B6 is still answering the post-native-opportunity question;
- do not add Staff/Quick/Whirl/block-timeout-specific cleanup branches;
- preserve native behavior for unmarked controls;
- compare one conceptual variable at a time where practical;
- visual observation may identify a reproduction, but lifecycle conclusions come from logs/source evidence;
- stop and revise the diagnostic if the required event ordering cannot be reconstructed clearly;
- do not repeat already-closed marker/source tests unless a later implementation could have regressed them.

---

## 2. Gate B6 — Hit Teardown / Replacement Stack and Script-Context Validation

This is the **current gate**.

Question:

> **Do the relevant actual Hit teardown/replacement paths occur inside one useful SPU / `gCScriptProcessingUnit::ProcessScript()` execution context, allowing a later tightly gated one-shot checkpoint to run after Gothic's native cleanup opportunity?**

### B6-A — Build/load sanity

Passed for the current diagnostic baseline after isolating the live script directory. EV-173 records why backup Script DLLs must not remain in the live `scripts` directory.

Required for the revised probe:

1. current `Script_FrameCollisionTest` builds;
2. DLL loads/unloads normally with only the intended active prototype DLL present;
3. Win32 stack/module resolution produces readable frames;
4. existing B4/B5 cleanup diagnostics remain intact;
5. no marker/collision behavior changes are introduced by the diagnostic.

### B6-B — Clean completion teardown/replacement

EV-174 established that ordinary clean 2H Normal completion uses this tested sequence:

```text
attack Hit Primary exists
→ StartRecover BEGIN
→ StopMotion(type 0) removes outgoing Hit Primary
→ successor Recover PlayMotion(type 0)
→ StartRecover END while source can still be group 7
→ native cleanup 7 -> 5
```

Therefore the revised B6-B correlation is:

```text
owned/current attack Hit
→ outgoing-Hit StopMotion stack captured before the original stop
→ existing StopMotion before/after record proves Hit removal
→ immediately following existing PlayMotion record proves successor Recover
→ native cleanup event in the same transition sequence
```

Record the relevant Game/Script_Game/Engine frames and their ordering.

Do **not** treat StopMotion alone as production Hit-end authority. In B6 it is a factual teardown event that must be correlated with the actual successor sequence.

### B6-C — Legitimate damage/reaction teardown/replacement

Interrupt a real attack Hit through a controlled damage/reaction path known to receive legitimate native cleanup.

Required correlation allows either observed sequencing form:

```text
attack Hit
→ legitimate native interruption cleanup
→ outgoing-Hit StopMotion stack + reaction successor PlayMotion
```

or, if Gothic directly replaces the still-visible Hit:

```text
attack Hit
→ legitimate native interruption cleanup
→ confirmed direct PlayMotion replacement stack
```

Compare the surrounding script-processing frames with the clean case. The known cleanup route itself may differ; the question is whether there is a useful common post-dispatch timing context.

### B6-D — Bad block-skip direct teardown/replacement

Reproduce a native or marked bad block-skip case where offensive collision remains stale.

Required correlation:

```text
attack Hit requested offensive collision
→ no corresponding legitimate cleanup
→ actual PrimaryFirst Hit eventually ends/replaces/restarts
→ either:
     outgoing-Hit StopMotion stack + successor PlayMotion
   or
     confirmed direct PlayMotion replacement stack
→ source remains offensive
```

This is the decisive negative-path comparison.

### B6 interpretation

**If all relevant teardown/replacement paths share a useful current `ProcessScript()` invocation/context:**

- strengthen the deferred one-shot candidate;
- next design step is a narrowly gated post-script diagnostic/guard prototype, not unconditional ProcessScript cleanup.

**If a relevant teardown/replacement occurs outside that context:**

- reject `ProcessScript()` as a universal timing checkpoint;
- return to architecture/search for another event boundary;
- do not compensate with family-specific repair branches.

**If stacks are ambiguous:**

- improve only the diagnostic fact needed to distinguish the execution context.

Current immediate engineering task before rerunning B6-B:

> Add diagnostic-only Win32 stack capture to the already-hooked player/type-0 `StopMotion` path when its before-snapshot is an attack-Hit Primary. Keep the existing direct PlayMotion replacement probe unchanged. Add no new Gothic hook, production cleanup, polling, or lifecycle ownership state.

---

## 3. Gate C1 — Prove the Deferred Checkpoint Before Repairing Anything

Run only if B6 supports a common post-script timing point.

First add a **diagnostic-only** tightly gated one-shot checkpoint for an already-tracked/pending exact attack execution.

It must demonstrate:

1. the checkpoint runs after clean ordinary native cleanup;
2. it runs after legitimate interruption cleanup;
3. it runs after bad direct replacement even when cleanup was absent;
4. unrelated script processing does nothing because no owned execution is pending;
5. the same execution is checked once, not repeatedly.

Do not perform fallback cleanup in this gate. Establish ordering first.

---

## 4. Gate C2 — Minimal Cleanup Repair Prototype

Only after C1 proves the timing point.

Implement the smallest execution-owned repair:

```text
pending exact execution requested offensive collision
→ post-native-opportunity checkpoint
→ cleanup observed?
    yes -> retire/no-op
    no  -> perform native-equivalent repair for the owned offensive source(s)
```

Initial cases:

1. clean native completion — must no-op;
2. clean marked completion — must no-op;
3. legitimate damage/reaction interruption — must no-op;
4. known stale native block-skip — must repair;
5. known stale marked block-skip — must repair.

A successful repair must not create a second collision activation, duplicate list clear, or unrelated state mutation.

---

## 5. Gate C3 — Does Offensive Collision Ever Legitimately Survive Across Independent Hit Executions?

Once a repair exists, challenge the universal invariant with representative native/unmarked attack chaining.

Initial families:

- 1H Normal/Quick;
- Shield+1H Normal/Quick;
- Dual Normal/Quick;
- 2H Normal/full Whirl;
- Staff Normal/full Whirl.

Critical pattern to search for:

```text
Hit A requested offensive collision
Hit A physically ended
Hit B is an independent execution
NO legitimate cleanup occurred between them
and this persistence is intentional/native-correct
```

Interpretation:

- never observed legitimately → strengthens the universal end guard;
- clearly intentional transfer → architecture must represent that transfer before release;
- only observed in stale/bugged paths → supports the guard, not an exception.

Do not infer intentional carry merely from a later `7 -> 7` request; determine whether the previous source was already stale.

---

## 6. Gate C4 — Source-Aware Fallback Decision

Prefer one execution-level obligation unless evidence proves independent partial-source cleanup.

Use Dual/multi-source cases to ask:

- can RIGHT clean while LEFT legitimately remains offensive after the same Hit ends?
- can one source fail independently while another cleans?
- does the native cleanup semantic operation operate per source in a way the repair must mirror?

Adopt source-aware lifecycle state only if these tests show it is necessary.

Do not choose it merely because marker desired-set state already contains a source mask.

---

## 7. Gate C5 — Negative / No-Op Regression for Generic Script Timing

Required if the final design uses a generic SPU/script timing checkpoint.

At minimum test:

- Fist;
- bow;
- crossbow;
- magic.

Expected result:

> The generic checkpoint is a complete no-op because no exact owned weapon-style offensive execution is pending finalization.

Fist is especially important: it can share ordinary melee action enums but the tested logical Fist source does not request weapon-style `Item_Attack(7)`. This protects the rule that **actual collision ownership/request**, not action enum alone, creates the cleanup obligation.

---

## 8. Gate C6 — Block / Parade Defensive Collision Semantics

Run only before release if the chosen cleanup operation might affect defensive item state.

Controlled pairs:

- weapon into weapon block;
- weapon into shield block;
- 2H/Staff block with obvious bounce;
- ParadeStumble/block-stumble case.

Observe attacker and defender source/group requests around contact.

Questions:

1. Does a defender weapon/shield enter `Item_Attack` or another special collision state?
2. Is visual bounce physical collision or combat-state response logic?
3. Could the repair operation disturb a legitimate defensive state?

Do not add defensive special cases unless evidence requires them.

---

## 9. Marker-Core Regression — Reuse Existing Fixtures

The marker source-set core is already strongly validated. Re-run compact fixtures only after lifecycle changes that could plausibly affect it.

Representative semantics:

```text
RIGHT -> LEFT
BOTH -> RIGHT
RIGHT -> OFF -> RIGHT
BOTH -> LEFT -> OFF -> BOTH
```

Verify:

- desired-set transition;
- later source rearm through `ClearTriggeredList()`;
- occurrence/replay guards;
- natural/fallback execution retirement;
- no unexpected native timer activation.

Do not rebuild the historical v0.10–v0.18 matrix from scratch unless a regression demands it.

---

## 10. Broad Regression Phase — After the Lifecycle Model Is Chosen

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
- normal completion, chaining, damage interruption, blocking, and known skip conditions.

The matrix is evidence coverage, not a production branch matrix.

---

## 11. Success Criteria

The collision-lifecycle research is ready for production integration when evidence answers:

1. what constitutes an owned real attack-Hit execution;
2. what event establishes its actual physical end/replacement;
3. what creates the offensive collision obligation, including `7 -> 7` requests;
4. what timing point occurs after Gothic's legitimate cleanup opportunity;
5. how native cleanup success is observed;
6. whether repair must be attack-wide or source-specific;
7. whether any legitimate native sequence carries offensive collision across independent physical Hit executions;
8. whether defensive collision introduces a conflicting state;
9. whether unrelated Fist/ranged/magic script processing remains a no-op;
10. whether marked and native activation converge on one end-of-Hit safety rule.

Only then should the stable collision lifecycle be integrated into the production `Script_G3AnimationBehaviors` implementation.

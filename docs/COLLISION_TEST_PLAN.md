# Collision Lifecycle Test Plan

**Status:** Current staged validation plan  
**Updated:** 2026-08-28

## Purpose

Validate the preferred execution-level collision-cleanup model with the smallest tests that can falsify it, then broaden only after the lifecycle boundary is proven.

Earlier test chronology and superseded gate wording are preserved in:

`docs/archive/technical_2026-08-27/COLLISION_TEST_PLAN_pre_ia.md`

Exact established findings should be retrieved through `EVIDENCE_INDEX.md` rather than re-running old matrices without a reason.

---

## 1. Rules for the Current Test Phase

- diagnostics remain observational;
- do not implement production cleanup while the lifecycle/finalization boundary is unresolved;
- do not add Staff/Quick/Whirl/block-timeout-specific cleanup branches;
- preserve native behavior for unmarked controls;
- compare one conceptual variable at a time where practical;
- visual observation may identify a reproduction, but lifecycle conclusions come from logs/source evidence;
- stop and revise the diagnostic if the required event ordering cannot be reconstructed clearly;
- do not repeat already-closed marker/source tests unless a later implementation could have regressed them.

Authoritative local deployment for controlled runtime tests:

```text
E:\SteamLibrary\steamapps\common\Gothic 3\scripts\Script_FrameCollisionTest.dll
```

Before treating a rebuilt diagnostic run as evidence, verify that the built DLL and this exact live DLL are identical or otherwise verify the intended revised startup banner. Do not infer deployment from backup/tool directories under `E:\Mods`.

---

## 2. Gate B6 — Cross-Path Script-Context Validation — RESOLVED NEGATIVE FOR THE DEFERRED-PROCESSSCRIPT CANDIDATE

Question tested:

> **Do the relevant actual Hit disappearance/replacement paths occur inside one useful SPU / `gCScriptProcessingUnit::ProcessScript()` execution context, allowing a later tightly gated one-shot checkpoint to run after Gothic's native cleanup opportunity?**

### B6-B — Clean completion

EV-176 established a useful clean-path context:

```text
attack Hit Primary exists / weapon 7
→ StartRecover BEGIN
→ diagnostic
   → sAICombatMoveInstr
   → ProcessScript()
→ empty Primary
→ Recover
→ later action-specific native cleanup 7 -> 5
```

Clean full Whirl in the later combined run reproduced the same `sAICombatMoveInstr -> ProcessScript()` StartRecover shape and then cleaned at its ordinary `Script_Game +0x4E03C` site.

### B6-C — Legitimate reaction

EV-177/EV-178 established the cleanup/replacement ordering and why earlier semantic gates missed the reaction successor.

B6-C3 then captured the actual empty-Primary reaction successors factually. EV-179 records representative cases:

```text
Quick interruption:
+0x24AFF cleanup
→ reaction Script_Game frame +0x227AD
→ RunScriptState return +0x1604D3
→ Stumble successor stack:
   Game +0x16B485
   → Game +0x169724
   → Script_Game +0x4ACDA
   → RunScriptFunction return +0x1605EB
   → RunScriptState return +0x1604D3
```

and:

```text
Normal interruption:
+0x24AFF cleanup
→ reaction Script_Game frame +0x235C7
→ RunScriptState return +0x1604D3
→ KnockDown successor stack:
   Game +0x16B485
   → Game +0x169724
   → Script_Game +0x2378B
   → RunScriptState return +0x1604D3
```

Interpretation:

- legitimate reaction successor installation remains inside the reaction Script_Game/ScriptAdmin chain;
- static EV-170 places `RunScriptState` under `ProcessScript()`;
- the runtime unwind does not directly identify the exact outer ProcessScript invocation, so do not overstate that identity.

### B6-D — Bad block-skip

EV-180/EV-181 provide the decisive comparison.

Representative armed bad Whirl:

```text
Whirl Hit starts through normal attack-start script stack
→ timer/callback arms weapon 5 -> 7 at StateTime ~0.256
→ NO StartRecover
→ NO +0x4E03C cleanup
→ Hit disappears
→ Ambient installed from empty Primary
   action 0 / phase 5
   weapon still 7
   observed successor stack only:
      diagnostic
      → Game +0xD9CB3
```

A separate skip occurred before the activation threshold and returned to Ambient with the weapon still 5. That control shows a bad skip does not create a cleanup obligation unless offensive collision was actually requested.

The strongest armed case then remained group 7 through ordinary Ambient/idle for roughly nineteen seconds and into a later Normal attack. That later Normal first requested `7 -> 7`; only its own clean completion finally reset the weapon at the ordinary Normal cleanup site.

### B6 conclusion

B6 **did not establish one useful observable current ProcessScript/ScriptAdmin context across all relevant replacement paths**.

The bad visible Hit-to-Ambient replacement exposed only `probe -> Game +0xD9CB3`; because stack unwinding can stop early, this is not proof that ProcessScript can never exist farther above. It is, however, sufficient to reject the specific production candidate that required every relevant replacement to expose a useful current ProcessScript invocation for same-dispatch deferred finalization.

Therefore:

- do **not** proceed to C1 with a pending-finalization / post-ProcessScript prototype;
- do **not** add a ProcessScript behavior hook to rescue the candidate;
- preserve the execution-level cleanup invariant;
- move the architecture search earlier into attack-lifecycle/bookkeeping/control flow.

Canonical evidence: EV-176, EV-179–EV-181.

---

## 3. Gate B7 — Attack-Lifecycle / Bookkeeping Reconstruction — CURRENT GATE

Question:

> **What native CombatMove/routine/instruction bookkeeping established at attack-Hit start keeps the normal-completion and legitimate-reaction paths connected to cleanup, and what is abandoned, reset, or bypassed differently on the bad block-skip path?**

Do not assume a literal allocated attack "package". Treat the current model as a control-flow/lifecycle bundle whose pieces may include:

- animation playback;
- movement/reach execution;
- CombatMove instruction state;
- Routine StateTime;
- Routine StatePosition;
- callback scheduling/progression;
- ScriptFunction/ScriptState continuation.

### B7-A — Static reconstruction first

Inspect the smallest existing source/binary areas around:

1. `sAICombatMoveStart`;
2. `sAICombatMoveItlLoop`;
3. `sAICombatMoveInstr` and its active instruction/callback state, including exposed `m_pfInstrCallback` structure where authoritative declarations support it;
4. transitions that establish/reset Routine StateTime and StatePosition;
5. the action-specific continuation after CombatMove returns;
6. reaction state/reset flow leading to the tested `Script_Game +0x24AFF` cleanup;
7. any directly supported caller/branch associated with the observed bad-skip return to ordinary animation handling.

Do not infer ownership from nearby addresses alone. Prefer caller/callee relations, exported symbols, authoritative SDK structure, and runtime stacks.

### B7-B — Offensive activation stack, only if static evidence still leaves the timer/callback path ambiguous

Reuse the already-owned `SetCollisionGroup` hook. No new Gothic hook is needed merely to observe this question.

Add diagnostic stack capture only for actual player equipped-source offensive requests relevant to the controlled fixture:

```text
5 -> 7
7 -> 7
```

`7 -> 7` must be retained because EV-181 proves a new execution can inherit stale offense and make a real offensive request without a numeric transition.

The diagnostic should preserve factual context already logged:

- action/phase;
- StateTime;
- StatePosition;
- current movement;
- exact equipped source;
- caller module/RVA;
- short stack.

Do not use these facts as production lifetime authority.

### B7-C — Controlled comparison fixture

If a runtime comparison is required, use the compact order that minimizes noisy target combat:

```text
1. clean Normal attacks — no target
2. clean Quick attacks — no target
3. clean full Whirl — no target
4. bad skipped full Whirl attempts — no target
5. spawn one durable target
6. several legitimate Normal interruptions
7. several legitimate Quick interruptions
8. exit
```

The current B6-C3/B6-D raw already contains a strong version of this fixture; do not rerun it unless B7 instrumentation asks a new factual question.

Compare **mechanism**, not just attack-family names:

- what is established at Hit start;
- when StateTime/StatePosition change;
- what invokes offensive activation;
- what clean completion retains until action-specific cleanup;
- what reaction resets/changes before `+0x24AFF`;
- what the bad skip loses before Ambient/idle takes over.

### B7 acceptance

B7 is successful when evidence identifies either:

1. a general lifecycle/bookkeeping signal that survives every armed execution until one of its legitimate terminal paths, or
2. a narrower supported event that reliably distinguishes "native cleanup still has an opportunity" from "the execution has been abandoned and no opportunity remains."

If neither exists, continue architectural search rather than falling back to polling/timers/family matrices.

Current immediate Normal Chat responsibility:

> Interpret the current B6 result as a rejected timing candidate, then source-audit the CombatMove/routine bookkeeping path before freezing any new Work diagnostic. A likely first runtime refinement, if still needed, is offensive activation stack capture in the existing `SetCollisionGroup` hook; do not implement it until the static question has been narrowed.

---

## 4. Gate C1 — Prove a New Finalization Checkpoint Before Repairing Anything

Run only after B7 or later evidence identifies a general finalization timing point.

First add a **diagnostic-only** tightly gated one-shot checkpoint for an already-owned exact attack execution.

It must demonstrate:

1. the checkpoint runs after clean ordinary native cleanup;
2. it runs after legitimate interruption cleanup;
3. it runs after bad teardown even when cleanup was absent;
4. unrelated processing does nothing because no owned execution is pending/finalizing;
5. the same execution is checked once, not repeatedly.

Do not perform fallback cleanup in this gate. Establish ordering first.

---

## 5. Gate C2 — Minimal Cleanup Repair Prototype

Only after C1 proves the timing point.

Implement the smallest execution-owned repair:

```text
owned exact execution requested offensive collision
→ proven post-native-opportunity checkpoint
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

## 6. Gate C3 — Does Offensive Collision Ever Legitimately Survive Across Independent Hit Executions?

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

EV-181 is already a negative example of accidental carry: a broken Whirl left group 7, then a later Normal requested `7 -> 7` and finally cleaned it. Do not mistake that pattern for intentional transfer.

---

## 7. Gate C4 — Source-Aware Fallback Decision

Prefer one execution-level obligation unless evidence proves independent partial-source cleanup.

Use Dual/multi-source cases to ask:

- can RIGHT clean while LEFT legitimately remains offensive after the same Hit ends?
- can one source fail independently while another cleans?
- does the native cleanup semantic operation operate per source in a way the repair must mirror?

Adopt source-aware lifecycle state only if these tests show it is necessary.

Do not choose it merely because marker desired-set state already contains a source mask.

---

## 8. Gate C5 — Negative / No-Op Regression for Generic Timing

Required if the final design uses a generic timing checkpoint.

At minimum test:

- Fist;
- bow;
- crossbow;
- magic.

Expected result:

> The generic checkpoint is a complete no-op because no exact owned weapon-style offensive execution is pending/finalizing.

Fist is especially important: it can share ordinary melee action enums but the tested logical Fist source does not request weapon-style `Item_Attack(7)`. This protects the rule that **actual collision ownership/request**, not action enum alone, creates the cleanup obligation.

---

## 9. Gate C6 — Block / Parade Defensive Collision Semantics

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

## 10. Marker-Core Regression — Reuse Existing Fixtures

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

## 11. Broad Regression Phase — After the Lifecycle Model Is Chosen

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

## 12. Success Criteria

The collision-lifecycle research is ready for production integration when evidence answers:

1. what constitutes an owned real attack-Hit execution;
2. what event establishes its actual physical end/replacement;
3. what creates the offensive collision obligation, including `7 -> 7` requests;
4. what timing point occurs after Gothic's legitimate cleanup opportunity even on the bad teardown path;
5. how native cleanup success is observed;
6. whether repair must be attack-wide or source-specific;
7. whether any legitimate native sequence carries offensive collision across independent physical Hit executions;
8. whether defensive collision introduces a conflicting state;
9. whether unrelated Fist/ranged/magic processing remains a no-op;
10. whether marked and native activation converge on one end-of-Hit safety rule.

Only then should the stable collision lifecycle be integrated into the production `Script_G3AnimationBehaviors` implementation.

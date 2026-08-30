# Collision Lifecycle Test Plan

**Status:** Current staged validation plan  
**Updated:** 2026-08-30

## Purpose

Validate one general execution-level collision-cleanup model with the smallest tests that can falsify it. Historical gate detail is preserved through `EVIDENCE_INDEX.md`, the canonical evidence ledgers and raw/archive artifacts; this file owns the **current and forward validation sequence**.

Current state and exact next responsibility: `SESSION_ENTRYPOINT.md`.  
Current lifecycle architecture: `COLLISION_LIFECYCLE_PLAN.md`.

---

## 1. Rules for the Current Test Phase

- C1 remains **shadow-only** until a physical-repair gate is explicitly frozen and implemented.
- Compare one conceptual variable at a time where practical.
- Do not add family/action/input/state-name-specific ownership or repair branches.
- Do not treat `RunScriptFunction`, FullStop or AISetState as unconditional cleanup authority.
- Preserve native behavior for unmarked controls and all proven marker bookkeeping.
- A successful offensive request creates an exact source obligation; observed native cleanup fulfills that obligation.
- Visual observation may identify a reproduction, but lifecycle conclusions come from logs/source evidence.
- Preserve raw runtime logs exactly as produced.
- Follow `PROJECT_PIPELINE.md` for gate identity, build identity and artifact naming, and `PROJECT_OPERATING_PROCEDURES.md` for local build/deploy/test/log operations.
- Preserve external/native combat-rule choices and compatibility requirements.

Authoritative research DLL remains:

```text
Script_FrameCollisionTest
```

---

## 2. Closed Lifecycle / Substrate Gates — Retrieve, Do Not Rerun by Default

```text
B6 replacement/deferred ProcessScript candidate      EV-174–EV-181
B7/B7b termination / continuation loss               EV-182–EV-189
B8 cross-family abandonment generality               EV-190
B9 cleanup/finalization ordering                      EV-191
C1 shadow execution/source obligation core           EV-192–EV-193
C1 pre-Combat acquisition gap                        EV-194
C1-O1 outer ScriptFunction lifetime/correlation      EV-195–EV-196
hook/finalizer substrate stabilization               EV-199–EV-203
C1-O2-P1 lightweight dispatch bridge                 EV-204
C1-O2-P2 lazy pre-Combat acquisition/consumption     EV-205
```

Do not reconstruct these gates from old chat history when the ledger/index already answers the question.

---

## 3. C1-O2-P2 — CLOSED FOR TESTED OUTER-ACQUISITION / BINDING MODEL

P2 answered:

> **Can C1 use the proven P1 live `RunScriptFunction` scope only at a successful exact equipped-source pre-CombatMove offense to acquire its existing monotonic generation, let matching CombatMove in that same live ScriptFunction invocation reuse that generation, then consume/retire the native-frame bridge before `RunScriptFunction` returns — without reconnecting the rejected eager dispatch machinery or changing cleanup/finalization/physical collision behavior?**

Answer for the tested model: **yes**.

Canonical evidence: EV-205.

Validated P2 DLL SHA256:

```text
1081B287912DB9A368164DDE13542A7EC2D6E5DBB0AA29B04C19BD7932D92C7C
```

Validation:

```text
P2-A independent source audit = PASS
P2-B isolated load/unload = PASS
P2-C targeted GetUp meaning = PASS
P2-D broad gameplay ownership/stability = PASS
P2-D shutdown/unload = not captured in that raw file
```

The accepted identity model is:

```text
live ScriptFunction frame
= temporary native correlator only where early acquisition needs it

C1 monotonic generation
= durable plugin execution identity

actual successful Item_Attack request
= exact source obligation

native transition away from Item_Attack
= obligation fulfilled

destructive AISetState with obligation still outstanding
= existing shadow WOULD_REPAIR classification
```

P2-D produced 13 tested pre-Combat bridge generations and no C1/P2 binding failure signal. The broad run also retained expected native-clean, reaction, stale/inherited and destructive-shadow behavior across multiple melee configurations.

Do **not** reintroduce:

```text
g_ScriptFunctionDispatchStack
BeginScriptFunctionDispatch()
EndScriptFunctionDispatch()
per-dispatch vector/string capture
eager actor/state-stack inspection
cross-suspension native-frame persistence
family/action/input/GetUp classifiers
null-arguments fallback
```

---

## 4. Current Responsibility — Design the Physical-Repair Gate

**No implementation gate ID is frozen yet.**

This responsibility belongs to Normal Chat first.

Retrieve only the current lifecycle/finalizer source and architecture needed to answer:

> **What is the smallest controlled native-equivalent physical repair that can replace the already-proven shadow `WOULD_REPAIR` outcome while preserving exact-source ownership, source liveness, native-cleanup precedence, legitimate reaction behavior, inherited `7 -> 7` attribution and all current no-op cases?**

### Required design properties

Any proposed repair gate must preserve:

1. **Exact source ownership** — repair only the exact source whose tracked obligation is still outstanding.
2. **Established liveness** — do not dereference or mutate a remembered source until current equipped identity establishes it as live.
3. **Native-cleanup precedence** — if native cleanup already fulfilled the source obligation, repair is forbidden.
4. **Consequence-based ownership** — do not classify repair from attack family, action name, filename token, held key, timeout, FullStop or interruption cause.
5. **No arbitrary group-7 adoption** — unrelated pre-existing offensive state is not automatically owned by the current generation.
6. **Source-specific Dual behavior** — one outstanding side must not force mutation of the other side.
7. **Inherited `7 -> 7` correctness** — a later legitimate request while already offensive still belongs to that later execution and may later be fulfilled by native cleanup.
8. **No global machinery** — no polling, timer, world scan or broad actor sweep.
9. **Marker-core isolation** — physical end-of-execution repair must not refactor the proven marker-window core.
10. **Rejected C1-O2 machinery remains rejected.**

### Questions to resolve before freezing Work

Normal Chat must inspect the exact current finalizer/source path and determine:

```text
which existing finalization branch owns the mutation
what exact native-equivalent SetCollisionGroup transition is appropriate
whether Item_Equipped is the complete native-equivalent target for the proven weapon-source cases
exact ordering of liveness check → current group observation → repair call → diagnostic → record retirement
how to preserve source-specific behavior when a record tracks two sources
what diagnostic proves a real physical repair occurred
what conditions remain diagnostic/no-op only
```

Do not infer these details from the shadow label alone; verify them against current source and the already-tested native cleanup semantics.

---

## 5. Candidate Runtime Falsification Matrix — NOT YET FROZEN

Once the design is source-reviewed and one bounded implementation responsibility is frozen, the smallest useful runtime matrix should distinguish at least:

### Positive repair case

Known armed destructive abandonment with an exact live/equipped outstanding source.

Expected only after repair is deliberately enabled:

```text
real offense obligation
→ destructive finalization with no native cleanup
→ exact source still live/equipped and offensive
→ native-equivalent repair on that source only
→ source no longer offensive
```

### Clean native path

```text
normal offense
→ native cleanup
→ obligation fulfilled
→ finalization no-op
→ zero repair mutation
```

### Legitimate reaction interruption

Expected: native/reaction-side cleanup wins; no repair mutation.

### Pre-activation interruption

Expected: no successful offense → no obligation → no repair mutation.

### Inherited stale `7 -> 7`

Expected: later legitimate execution owns its actual request; later native cleanup may fulfill it; do not repair merely because the request began at 7.

### Dual source-specific control

Expected: only the exact outstanding side may be repaired; fulfilled/non-outstanding side remains untouched.

### GetUpAttack acquisition control

Expected: P2 pre-Combat generation ownership remains intact; clean GetUp native cleanup remains no-op at finalization.

### GetUpParade / defensive control

Expected: `Hit` resource naming alone does not create an offensive C1 obligation or repair.

### Marker-window regression

Run only the compact marker fixtures needed if the physical-repair implementation can plausibly interact with marker-owned source state. Do not rerun the full historical marker matrix by default.

---

## 6. Acceptance Principle for a Future Physical-Repair Gate

The first repair gate must prove **less**, not more:

> Given an already-proven C1 `WOULD_REPAIR` source outcome, can the research DLL perform the same narrow source reset Gothic 3 normally performs during legitimate cleanup, without changing any execution that already cleaned itself or never requested offense?

A first repair gate should fail closed if source liveness, exact ownership or native-equivalent mutation cannot be established from existing evidence/source APIs.

Do not solve uncertainty by adding family matrices, timeout logic, fallback ownership, broad collision scans or interruption-cause classification.

---

## 7. After Controlled Physical Repair

Only after a bounded physical-repair gate passes should the project expand toward:

```text
controlled repair proof
→ preserve known destructive abandonment as positive stress case
→ preserve ordinary / legitimate reaction / pre-activation no-op controls
→ preserve inherited 7 -> 7 attribution
→ broad marked/unmarked/player/NPC/negative regression
→ stable production integration
→ only later reconsider marker-bookkeeping simplification
```

Root-cause repair of the held-Use2 / Alternative-AI interruption is not a prerequisite unless evidence later shows the general collision guard cannot preserve integrity independently.

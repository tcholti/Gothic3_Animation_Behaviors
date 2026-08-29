# Collision Lifecycle Test Plan

**Status:** Current staged validation plan  
**Updated:** 2026-08-30

## Purpose

Validate one general execution-level collision-cleanup model with the smallest tests that can falsify it. Historical gate detail is preserved through `EVIDENCE_INDEX.md`, the canonical evidence ledgers and raw/archive artifacts; this file owns the **current and forward validation sequence**.

Current state and exact next responsibility: `SESSION_ENTRYPOINT.md`.  
Current lifecycle architecture: `COLLISION_LIFECYCLE_PLAN.md`.

---

## 1. Rules for the Current Test Phase

- C1 remains **shadow-only**; production physical repair is disabled.
- Compare one conceptual variable at a time where practical.
- Do not add family/action/input/state-name-specific ownership or repair branches.
- Do not treat `RunScriptFunction`, FullStop or AISetState as unconditional cleanup authority.
- Preserve native behavior for unmarked controls and all proven marker bookkeeping.
- Visual observation may identify a reproduction, but lifecycle conclusions come from logs/source evidence.
- Reuse the current diagnostic/hook owner when it already exposes the needed fact; add another hook only for a specific unresolved question.
- Preserve raw runtime logs exactly as produced.
- Follow `PROJECT_PIPELINE.md` for gate identity, build identity and artifact naming, and `PROJECT_OPERATING_PROCEDURES.md` for local build/deploy/test/log operations.
- Preserve external/native combat-rule choices and compatibility requirements.

Authoritative research DLL remains:

```text
Script_FrameCollisionTest
```

Before any controlled runtime result becomes evidence, verify exact intended build/deployment identity and startup banner using the project procedures.

---

## 2. Closed Lifecycle / Substrate Gates — Retrieve, Do Not Rerun by Default

### B6 — replacement-triggered deferred `ProcessScript()` candidate rejected

Evidence: EV-174–EV-181.

### B7 / B7b — CombatMove termination and continuation loss resolved

Evidence: EV-182–EV-189.

### B8 — cross-family abandonment generality resolved

Evidence: EV-190.

### B9 — cleanup/finalization ordering resolved

Evidence: EV-191.

### C1 — shadow execution/source obligation core passed

Evidence: EV-192–EV-193.

### C1 acquisition boundary gap

GetUpAttack can legitimately request `Item_Attack(7)` before CombatMove starts, so CombatMove is not a universal outer execution-acquisition boundary.

Evidence: EV-194.

### C1-O1 — outer ScriptFunction lifetime/identity probe resolved

The same live GetUp ScriptFunction frame spans pre-CombatMove offense → later CombatMove → cleanup. Raw frame/arguments addresses can be reused after retirement, so they are lifetime-bound correlators only; C1's monotonic generation remains durable identity.

Evidence: EV-195–EV-196.

### C1 directly relevant hook/finalizer substrate — passed for tested stability

The prerequisite isolation sequence is now closed enough to reassess C1-O2:

- EV-199 — direct `RunScriptFunction` capture crash isolated; pure-pass-through baseline retained; AISetState transport then stabilized;
- EV-200 — AIFullStop explicit-this transport passed extended stability;
- EV-201–EV-202 — first SetCollisionGroup extended run crashed for an independently localized post-AISetState finalizer-lifetime defect, not demonstrated SetCollisionGroup transport failure;
- EV-203 — finalizer liveness correction passed isolated + extended stability and SetCollisionGroup explicit-this transport passed the corrected extended gate.

Current tested substrate:

```text
RunScriptFunction = recursion-safe pure pass-through; capture still suspended
AISetState        = explicit-this PASS for tested extended stability
AIFullStop        = explicit-this PASS for tested extended stability
SetCollisionGroup = explicit-this PASS for tested extended stability
C1 finalizer      = source-liveness-gated PASS for tested stability
physical repair   = OFF
```

Do not rerun these transport gates by default unless a new contradiction appears.

---

## 3. Current Gate — C1-O2 Reassessment Before Any New Integration

C1-O2 remains the higher-level target, but the original direct `RunScriptFunction` dispatch-capture implementation is **not automatically re-authorized**.

The current Normal Chat question is:

> **Given the now-stable surrounding hook/finalizer substrate, what is the smallest source-supported and falsifiable way to bind C1's existing monotonic generation to the proven live outer ScriptFunction lifetime early enough to own legitimate pre-CombatMove offense, without making generic `RunScriptFunction` combat authority or repeating the original capture crash?**

The reassessment must first distinguish:

1. what was proven about the outer ScriptFunction lifetime by EV-195–EV-196;
2. what remains unexplained about the direct capture crash in EV-199;
3. what later substrate stabilization in EV-200–EV-203 actually removes from consideration;
4. what it does **not** prove about the old failed capture path.

No Work task is frozen until Normal Chat selects one bounded candidate with explicit stop conditions.

### Reassessment acceptance

A candidate may proceed to a frozen diagnostic/implementation task only if source review can state:

- exact hook/call boundary used;
- exact transient data captured and its nesting/thread assumptions;
- why the candidate does not create unconditional combat ownership;
- how pre-CombatMove offense is tied to the supplied/current actor context;
- how binding lifetime is retired before raw address reuse;
- how the candidate preserves current C1 generation/source/cleanup semantics;
- how a failure will be diagnosed rather than guessed around;
- that physical repair remains disabled.

If these cannot be stated without family/action/input classification, guessed null-argument fallback, polling/world scan, or broader hook conversion, do not freeze implementation.

---

## 4. C1-O2 Source Contract — If Integration Resumes

Any resumed C1-O2 implementation must preserve:

1. one minimal nesting-safe transient dispatch/context mechanism;
2. original hooked/native call exactly once with unchanged real arguments;
3. live-frame correlation only by the frozen rule:
   - exact SPU;
   - top frame is ScriptFunction;
   - non-null bound `m_pArguments`;
   - same ScriptFunction name;
4. pre-CombatMove acquisition only for a successful `Item_Attack` request on the supplied/current actor's exact equipped RIGHT/LEFT source entity;
5. later matching CombatMove reuses rather than replaces the pre-acquired generation;
6. ordinary CombatMove-created generation behavior remains when no matching pre-acquired binding exists;
7. successful cleanup remains source/consequence based and does not require the old frame to remain current;
8. true outer return retires the native binding before pointer reuse;
9. outstanding obligation at true return is diagnostic-only, not a newly invented repair/finalization rule;
10. existing AISetState shadow finalization semantics remain unchanged;
11. no null-arguments fallback, family/action/input classifier, arbitrary group-7 adoption, polling/timer/world scan or marker-core refactor.

No runtime acceptance can compensate for a source-level violation of these rules.

---

## 5. C1-O2 Runtime Matrix — Only After Reassessment + Independent Source Review + Build/Load Verification

Normal Chat will freeze the exact controlled fixture and raw filename only after a resumed C1-O2 candidate passes source review and exact built/live identity verification.

### A. Pre-CombatMove GetUp acquisition

Expected:

```text
legitimate equipped-source Item_Attack before CombatMove
→ one C1 generation acquired from live outer context
→ later CombatMove for same live frame reuses same generation
→ ordinary native cleanup fulfills exact source obligation
→ no repair candidate / no binding invariant
```

This remains the primary positive test.

### B. Ordinary CombatMove-created control

Representative clean Normal/full-Whirl executions should preserve the existing CombatMove-created route when no earlier binding is needed.

Expected: native cleanup observed; finalization no-op.

### C. Known armed destructive abandonment

Expected: outstanding exact source at destructive finalization → existing `WOULD_REPAIR` shadow outcome only.

The known held-Use2 path remains a stress case, not production classification authority.

### D. Pre-activation abandonment

Expected: no offensive request → no cleanup obligation → no repair candidate.

### E. Legitimate reaction interruption

Expected: reaction-side native cleanup fulfills the exact source obligation; no repair candidate.

### F. Inherited stale `7 -> 7`

Expected: later legitimate request while already group 7 belongs to the later execution's generation; later native cleanup fulfills that generation.

### G. Frame-lifetime failure signals

Specifically inspect for:

- frame mismatch / overlap invariants;
- null-arguments failure;
- `OUTER_RETURN_OUTSTANDING`;
- generation replacement where reuse was expected;
- a retired binding matching a later reused raw address.

Any occurrence is a gate result to interpret, not something to hide with fallback behavior.

---

## 6. C1-O2 Runtime Acceptance

C1-O2 passes only if the tested controls support one model:

```text
outer live ScriptFunction frame
= temporary native lifetime correlator

C1 monotonic generation
= durable plugin execution identity

actual successful Item_Attack request
= exact source obligation

native transition away from Item_Attack
= obligation fulfilled

destructive AISetState with obligation still outstanding
= existing shadow WOULD_REPAIR classification
```

And specifically:

- GetUp pre-CombatMove offense is no longer unowned;
- later CombatMove reuses the same generation;
- clean ordinary paths remain clean/no-op;
- legitimate reactions remain native-clean/no-op;
- pre-activation failures remain no-op;
- known armed stale paths retain shadow `WOULD_REPAIR`;
- inherited `7 -> 7` attribution remains correct;
- no lifetime-correlator reuse/leak invariant occurs;
- physical collision behavior remains unchanged by C1-O2.

If the route requires family/action/input classification or guessed null-arguments fallback, C1-O2 fails.

---

## 7. After C1-O2 — Universal Guard First

Only after the outer binding model passes should Normal Chat freeze a physical-repair gate.

```text
stable shadow execution/source ownership
→ controlled native-equivalent physical repair
→ retain known destructive abandonment as positive stress case
→ preserve ordinary / legitimate reaction / pre-activation no-op controls
→ preserve inherited 7 -> 7 attribution
→ broad marked/unmarked/player/NPC/negative regression
→ stable production integration
```

Root-cause repair of the held-Use2 / Alternative-AI interruption is not a planned prerequisite. Reopen it only if evidence shows the general collision guard cannot preserve integrity without changing that external lifecycle path.

Likely later responsibilities remain evidence-dependent and are not pre-authorized:

- choose the exact gate for promoting shadow `WOULD_REPAIR` to native-equivalent physical repair;
- test broad marked/unmarked/player/NPC regression;
- challenge whether any legitimate independent Hit sequence intentionally carries offensive collision across executions;
- verify negative/no-op behavior for Fist, bow, crossbow and magic;
- verify defensive block/parade semantics if later physical repair could disturb them;
- reconsider marker-core simplification only after native lifetime and physical guard preserve historical marker guarantees.

---

## 8. Marker-Core Regression — Reuse Existing Fixtures When Relevant

If a lifecycle change can plausibly affect marker behavior, reuse compact proven fixtures such as:

```text
RIGHT -> LEFT
BOTH -> RIGHT
RIGHT -> OFF -> RIGHT
BOTH -> LEFT -> OFF -> BOTH
```

Verify desired-set transition, source rearm, occurrence/replay guards, execution retirement and absence of unexpected native timer activation.

Do not rebuild the full historical v0.10–v0.18 matrix unless a regression demands it.

Marker simplification is a later optimization question, not a prerequisite for the universal guard. Preserve duplicate/replay handling, occurrence protection, exact source-set semantics, repeated-contact rearm, Quick bookkeeping and any other mechanism whose original regression still requires it.

---

## 9. Success Criteria for Stable Collision Integration

Before stable lifecycle behavior can move into `Script_G3AnimationBehaviors`, evidence must support:

1. exact ownership of a real attack execution before and during CombatMove where needed;
2. exact creation of offensive source obligations, including `7 -> 7` requests;
3. reliable observation of native cleanup fulfillment;
4. safe lifetime retirement without raw-pointer reuse confusion;
5. a terminal/finalization rule that preserves Gothic's legitimate cleanup opportunity;
6. correct handling of clean, reaction, pre-activation, bad-abandonment and inherited-stale cases;
7. safe native-equivalent physical repair only for exact abandoned outstanding sources;
8. no-op behavior for unrelated mechanics/source models and compatible external combat-rule choices;
9. preservation of marked and native collision semantics behind one end-of-execution safety invariant.

Only after those conditions pass should stable production integration be considered.

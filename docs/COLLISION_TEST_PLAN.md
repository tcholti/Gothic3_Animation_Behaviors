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

The prerequisite isolation sequence is closed enough to resume C1-O2 through a narrower probe:

- EV-199 — direct `RunScriptFunction` capture crash isolated; pure-pass-through baseline retained; AISetState transport then stabilized;
- EV-200 — AIFullStop explicit-this transport passed extended stability;
- EV-201–EV-202 — first SetCollisionGroup extended run crashed for an independently localized post-AISetState finalizer-lifetime defect, not demonstrated SetCollisionGroup transport failure;
- EV-203 — finalizer liveness correction passed isolated + extended stability and SetCollisionGroup explicit-this transport passed the corrected extended gate.

Current tested substrate:

```text
RunScriptFunction = recursion-safe explicit-this pure pass-through; stable transport baseline
AISetState        = explicit-this PASS for tested extended stability
AIFullStop        = explicit-this PASS for tested extended stability
SetCollisionGroup = explicit-this PASS for tested extended stability
C1 finalizer      = source-liveness-gated PASS for tested stability
physical repair   = OFF
```

Do not rerun these transport gates by default unless a new contradiction appears.

---

## 3. Current Gate — C1-O2-P1 Lightweight Dispatch Bridge

The C1-O2 reassessment selected one bounded diagnostic candidate. The old eager dispatch-capture implementation remains rejected as a template.

P1 asks:

> **Can the already-stable explicit-this RunScriptFunction hook carry a zero-allocation, nesting-safe, stack-local current-dispatch scope across the native call, with no engine/API work before native execution, and expose that scope only when an already-relevant player offensive SetCollisionGroup event occurs?**

Exact frozen implementation contract: `BETWEEN_CHATS.md`.

### P1 source requirements

The generic unrelated RunScriptFunction path must contain only:

```text
construct tiny stack-local scope from existing hook arguments
→ link previous thread-local scope pointer
→ publish current thread-local scope pointer
→ call original RunScriptFunction exactly once with unchanged arguments
→ restore previous thread-local pointer
→ if this scope observed a relevant offense, emit return diagnostic
→ return native result unchanged
```

Before the original/native call P1 must perform no state-stack inspection, actor/entity lookup, C1 record lookup, string copy/ownership, vector/container mutation, heap allocation, logging or collision work.

At an already-established successful player equipped-source offensive SetCollisionGroup event only, P1 may:

- inspect the current scope pointer;
- compare its SPU and runtime-stack identities with the already-resolved player SPU/state stack;
- log the live ScriptFunction name/reference identity;
- log whether a parent scope exists without assigning parent/outer ownership semantics;
- mark the current matching scope as having observed relevant offense.

When that wrapper later returns, the native boolean result is sufficient to observe suspended/unfinished (`false`) versus completed (`true`) dispatch for this probe. P1 must not recapture the state-stack merely to rediscover that fact.

### P1 explicitly does not implement

- C1 generation acquisition/binding;
- persistent native-frame ownership across suspension;
- matching-parent/outer selection;
- later continuation retirement;
- altered CombatMove generation semantics;
- cleanup/finalization changes;
- physical repair.

`CollisionLifecycleGuard.*` remains unchanged and its older dormant Begin/End dispatch machinery remains disconnected.

---

## 4. C1-O2-P1 Validation Sequence

Do not combine P1 implementation with higher-level C1-O2 ownership validation.

### P1-A — independent source audit

Before build, confirm:

1. no engine/API call occurs before the original RunScriptFunction;
2. no dynamic allocation/container/string ownership exists on the generic wrapper path;
3. nesting uses only a stack-local scope and previous TLS pointer;
4. the native function is called exactly once with unchanged arguments;
5. TLS is restored before relevant-return diagnostics;
6. scope/name references do not survive wrapper return;
7. offense observation is behind the existing exact player-equipped successful-offense gate;
8. C1 lifecycle behavior and physical collision behavior are unchanged.

Any violation is a source-level P1 failure regardless of runtime behavior.

### P1-B — isolated load/unload

This is the first runtime gate because both old capture builds crashed during ordinary registered-ScriptFunction activity before useful C1-O2 acquisition evidence appeared.

Expected:

```text
normal DLL load
→ main-menu script activity
→ no P1 offense event required
→ normal unload
→ no old registered-ScriptFunction crash signature
```

Normal Chat freezes the exact raw filename only after source review and exact build/live identity verification.

### P1-C — targeted relevant-offense correlation

After isolated stability passes, use a small controlled combat run containing representative ordinary offense and the pre-CombatMove GetUp case when practical.

For relevant offense, compare P1 against the already-existing `OUTER_FRAME OFFENSE` observation.

Expected:

- current scope exists for the relevant synchronous offense;
- scope SPU matches the player SPU where C1-O2 correlation is expected;
- runtime-stack identity is consistent with the supplied actor SPU state stack;
- ScriptFunction name is available while synchronously live;
- native return is observed without post-call state-stack recapture;
- parent presence, if any, is reported as evidence rather than silently classified.

If the pre-CombatMove GetUp offense does not occur inside a usable P1 scope, P1 answers the gate negatively; do not invent fallback ownership in the same task.

### P1-D — extended stability only after targeted meaning is confirmed

If P1-B and P1-C are clean, perform broader combat/interruption coverage to determine whether the lightweight bridge remains stable under repeated/nested script activity.

This extended run is still diagnostic-only. It does not authorize C1 generation binding or physical repair.

---

## 5. P1 Acceptance / Failure Meaning

P1 passes only if both source and runtime evidence support:

```text
RunScriptFunction transport
+ stack-local/TLS current-dispatch scope
= stable low-cost synchronous bridge
```

without changing collision behavior.

A P1 pass would authorize Normal Chat to design the next smallest step: lazy acquisition of C1's existing monotonic generation at a proven relevant offense event, using the already-proven live-frame correlator rules.

A P1 pass does **not** prove continuation retirement, parent/outer ownership selection, full C1-O2 correctness or physical repair.

A P1 failure must be interpreted at the narrow bridge boundary. Do not restore the old vector/string capture or broaden to another hook in the same implementation task.

---

## 6. C1-O2 Source Contract — For Later Integration Only

Any later resumed C1-O2 integration must preserve:

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

Do not implement this section during P1.

---

## 7. Full C1-O2 Runtime Matrix — Only After P1 and Later Binding Integration Pass Source Review

### A. Pre-CombatMove GetUp acquisition

Expected:

```text
legitimate equipped-source Item_Attack before CombatMove
→ one C1 generation acquired from live outer context
→ later CombatMove for same live frame reuses same generation
→ ordinary native cleanup fulfills exact source obligation
→ no repair candidate / no binding invariant
```

This remains the primary positive integration test.

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

## 8. Full C1-O2 Runtime Acceptance

Full C1-O2 passes only if the tested controls support one model:

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

## 9. After C1-O2 — Universal Guard First

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

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

The same GetUp ScriptFunction execution correlates pre-CombatMove offense → later CombatMove → cleanup. Raw frame/arguments addresses can be reused after retirement, so they are lifetime-bound correlators only; C1's monotonic generation remains durable identity.

Evidence: EV-195–EV-196.

### Directly relevant hook/finalizer substrate — passed for tested stability

- EV-199 — old eager `RunScriptFunction` capture crash isolated; pure-pass transport baseline retained; AISetState transport stabilized;
- EV-200 — AIFullStop explicit-this transport passed extended stability;
- EV-201–EV-202 — first SetCollisionGroup extended run exposed an independent post-AISetState finalizer-lifetime defect, not demonstrated SetCollisionGroup transport failure;
- EV-203 — finalizer liveness correction passed isolated + extended stability and SetCollisionGroup explicit-this transport passed the corrected extended gate.

### C1-O2-P1 — lightweight dispatch bridge passed its bounded meaning gate

Evidence: EV-204.

P1 source audit passed. Corrected validated DLL SHA256:

```text
44C15C068D34F82BDCB03EEBEC76C3C0A93094D64662B032954BFF637D51E05D
```

P1-B isolated main-menu load/unload passed without the old registered-ScriptFunction crash.

P1-C targeted gameplay produced 27 `C1-O2-P1 OFFENSE SCOPE` records and four deliberate GetUp pre-Combat acquisition-gap reproductions. In all four initial GetUp `5 -> 7` events:

- a current P1 scope existed;
- scope SPU matched player SPU;
- runtime-stack identity matched player SPU state stack;
- ScriptFunction was `_AI_GetUpAttack`;
- independent `OUTER_FRAME OFFENSE` agreed on `_AI_GetUpAttack` / `OnAI_GetUpAttack` with non-null arguments;
- matching player CombatMove began in the same live ScriptFunction invocation;
- only afterward `RunScriptFunction` returned `GEFalse` / suspended.

Later GetUp timer `7 -> 7` offense and representative ordinary Normal/Quick timer offense occurred with **no live P1 wrapper scope** while the relevant ScriptFunction could remain suspended on the SPU. Therefore a live wrapper scope is a transient acquisition bridge, not a universal collision-owner requirement.

P1-D was not run as a separate long-duration extended-stability gate. P1 is closed as PASS for source + isolated + targeted meaning; do not describe it as separately extended-stability proven.

---

## 3. Current Gate — C1-O2-P2 Lazy Pre-Combat Generation Acquisition + Bridge Consumption

Exact frozen implementation contract: `BETWEEN_CHATS.md`.

P2 asks:

> **Can C1 use the proven P1 live `RunScriptFunction` scope only at a successful exact equipped-source pre-CombatMove offense to acquire its existing monotonic generation, let matching CombatMove in that same live ScriptFunction invocation reuse that generation, then consume/retire the native-frame bridge before `RunScriptFunction` returns — without reconnecting the rejected eager dispatch machinery or changing cleanup/finalization/physical collision behavior?**

P2 deliberately tests the smaller lifetime model first:

```text
native ScriptFunction identity
= temporary pre-Combat offense -> matching CombatMove correlator

C1 monotonic generation
= durable plugin execution identity
```

The four P1 GetUp cases show that matching CombatMove begins **before** the live wrapper returns/suspends. Therefore cross-suspension native-frame persistence is not currently required for the proven positive path. It is not claimed universally unnecessary until P2 and later integration evidence support that conclusion.

### P2 allowed acquisition work

Generic `RunScriptFunction` entry must remain the P1 lightweight path: stack-local/TLS bookkeeping only before the unchanged native call.

Only at a real successful `Item_Attack` event with a current P1 scope may C1 lazily perform the additional work needed to validate:

1. valid current SPU;
2. runtime-stack identity equals that SPU state stack;
3. current top frame is a ScriptFunction;
4. top `m_pArguments` is non-null;
5. top ScriptFunction name matches the live wrapper ScriptFunction name;
6. the offensive source is the exact currently equipped RIGHT and/or LEFT source of that SPU actor;
7. no incompatible existing generation/binding owns the actor/source.

No family/action/input/GetUp/state-name classifier or null-arguments fallback is allowed.

When valid, P2 may create one C1 monotonic generation, bind it temporarily by the proven SPU + arguments + ScriptFunction-name correlator, attribute the actual source obligation to that generation, and return only a tiny generation/bridge token to the same stack-local P1 scope.

### Matching CombatMove

When `BeginCombatMove()` sees the exact same actor/SPU/non-null arguments/ScriptFunction name:

```text
reuse SAME pre-acquired generation
→ mark the already-real generation as persisted/CombatMove-owned
→ consume/retire temporary native binding immediately
→ keep durable generation + source obligation alive
```

The pre-acquired generation is already real because an actual offensive request occurred. P2 must not discard it merely because the later CombatMove result is immediate.

When no matching pre-acquired binding exists, ordinary CombatMove-created candidate/result behavior remains unchanged.

### Wrapper-return safety

If a pre-Combat bridge reaches `RunScriptFunction` return without matching CombatMove having consumed it:

- log a dedicated P2 binding invariant;
- retire the native binding before wrapper return/pointer reuse;
- retain any already-real C1 source obligation/generation needed for normal cleanup/finalization observation;
- do not silently persist native-frame identity across suspension;
- do not invent fallback continuation ownership or physical repair.

This condition is a P2 gate result, not an alternate architecture hidden inside the same implementation.

### Rejected machinery remains rejected

Do not reconnect or depend on:

```text
g_ScriptFunctionDispatchStack
BeginScriptFunctionDispatch()
EndScriptFunctionDispatch()
```

Do not restore per-dispatch vector/string capture, eager state-stack inspection, actor lookup or logging around every `RunScriptFunction` call.

---

## 4. C1-O2-P2 Validation Sequence

Do not combine P2 implementation with physical repair or broader continuation architecture.

### P2-A — independent source audit

Confirm:

1. generic `RunScriptFunction` still performs only stack-local/TLS work before native execution;
2. no old dispatch vector/Begin/End lifecycle is reconnected;
3. lazy actor/state-stack/C1 work occurs only at a real successful offense with a live current scope;
4. exact equipped-source and live-frame rules are enforced;
5. matching CombatMove reuses rather than replaces the pre-acquired generation;
6. the temporary native binding is consumed at matching CombatMove;
7. an unconsumed bridge cannot survive wrapper return;
8. ordinary CombatMove-created semantics remain unchanged;
9. source cleanup and AISetState finalization semantics remain unchanged;
10. physical repair remains disabled.

### P2-B — isolated load/unload

Expected:

```text
normal DLL load
→ main-menu script activity
→ no P2 acquisition required
→ normal unload
→ no registered-ScriptFunction crash
```

### P2-C — targeted 2H GetUp positive correlation

Primary positive integration test.

Expected first GetUp `5 -> 7`:

```text
real equipped-source offense
→ no UNOWNED_PLAYER_OFFENSE_REQUEST for that event
→ PRECOMBAT generation acquired
→ C1 OFFENSE REQUEST attributed to that generation
→ matching CombatMove reuses SAME generation
→ temporary native binding consumed before dispatch return
→ no unconsumed-bridge invariant
```

Then:

```text
later native timer 7 -> 7
→ same durable generation/source ownership
→ no live RunScriptFunction scope required
→ native cleanup fulfills same generation's obligation
→ physical collision behavior unchanged
```

Representative ordinary Normal attacks remain the control:

```text
ordinary CombatMove-created generation path unchanged
→ timer offense need not have a live P1 scope
→ normal native cleanup
```

Do not authorize a broad P2 extended run until P2-C proves the intended meaning.

### P2-D — broader stability only after P2-C

If P2-C passes, then perform broader combat/interruption coverage before claiming extended stability or full C1-O2 completion.

---

## 5. P2 Acceptance / Failure Meaning

P2 passes its bounded meaning gate only if the tested positive path supports:

```text
live P1 scope at pre-Combat offense
→ lazy C1 generation acquisition
→ matching CombatMove generation reuse
→ temporary native binding consumed before wrapper return
→ later durable ownership independent of live wrapper scope
```

without changing physical collision behavior.

P2 fails at this boundary if the tested GetUp path requires native binding to survive `RunScriptFunction` return, parent-scope selection, null-argument fallback, another hook or production action/state classification. Do not broaden the implementation in the same task.

---

## 6. C1-O2 Source Contract — Preserved Integration Rules

Any C1-O2 integration must preserve:

1. one minimal nesting-safe transient dispatch/context mechanism;
2. original hooked/native call exactly once with unchanged real arguments;
3. live-frame correlation only by exact SPU + real ScriptFunction + non-null `m_pArguments` + ScriptFunction name;
4. pre-Combat acquisition only for a successful `Item_Attack` request on the current actor's exact equipped RIGHT/LEFT source entity;
5. later matching CombatMove reuses rather than replaces the pre-acquired generation;
6. ordinary CombatMove-created generation behavior remains when no matching pre-acquired binding exists;
7. successful cleanup remains source/consequence based and does not require the old frame to remain current;
8. temporary native binding must retire before raw correlator reuse; P2 first tests consumption at matching CombatMove rather than persistence across suspension;
9. an unconsumed binding at wrapper return is diagnostic, not a reason to invent continuation ownership or repair;
10. existing AISetState shadow finalization semantics remain unchanged;
11. no null-arguments fallback, family/action/input classifier, arbitrary group-7 adoption, polling/timer/world scan or marker-core refactor.

---

## 7. Full C1-O2 Runtime Matrix — After P2 Meaning Pass

### A. Pre-CombatMove GetUp acquisition

Expected:

```text
legitimate equipped-source Item_Attack before CombatMove
→ one C1 generation acquired from live current scope/frame
→ later CombatMove for same live frame reuses same generation
→ temporary native binding consumed
→ later timer offense remains on same durable generation
→ ordinary native cleanup fulfills exact source obligation
→ no repair candidate / no binding invariant
```

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

### G. Binding/lifetime failure signals

Specifically inspect for:

- live-frame mismatch / overlap invariants;
- null-arguments failure;
- unconsumed pre-Combat bridge at wrapper return;
- generation replacement where reuse was expected;
- retired binding matching later reused raw correlators.

Any occurrence is a gate result to interpret, not something to hide with fallback behavior.

---

## 8. Full C1-O2 Runtime Acceptance

Full C1-O2 passes only if the tested controls support one model:

```text
live ScriptFunction frame
= temporary native correlator where early acquisition needs it

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
- temporary native binding does not leak into later raw-pointer reuse;
- clean ordinary paths remain clean/no-op;
- legitimate reactions remain native-clean/no-op;
- pre-activation failures remain no-op;
- known armed stale paths retain shadow `WOULD_REPAIR`;
- inherited `7 -> 7` attribution remains correct;
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

Root-cause repair of the held-Use2 / Alternative-AI interruption is not a planned prerequisite. Reopen it only if evidence shows the general collision guard cannot preserve integrity without changing that external lifecycle path.

Likely later responsibilities remain evidence-dependent and are not pre-authorized:

- choose the exact gate for promoting shadow `WOULD_REPAIR` to native-equivalent physical repair;
- test broad marked/unmarked/player/NPC regression;
- challenge whether any legitimate independent Hit sequence intentionally carries offensive collision across executions;
- verify negative/no-op behavior for Fist, bow, crossbow and magic;
- verify defensive block/parade semantics if later physical repair could disturb them;
- reconsider marker-core simplification only after native lifetime and physical guard preserve historical marker guarantees.

---

## 10. Marker-Core Regression — Reuse Existing Fixtures When Relevant

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

## 11. Success Criteria for Stable Collision Integration

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

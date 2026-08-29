# Collision Lifecycle Diagnostic Architecture

**Status:** Current research-diagnostic authority  
**Updated:** 2026-08-29

## Purpose

Define the smallest observational instrumentation needed to answer collision-lifecycle questions without turning diagnostics into a second behavior/lifecycle system.

The logger measures the architecture. It does not define it.

Current gate: `SESSION_ENTRYPOINT.md`.  
Exact evidence: `EVIDENCE_INDEX.md` → canonical evidence ledger.  
Historical probe detail: evidence/raw/archive + `docs/archive/technical_2026-08-27/COLLISION_LOGGER_PLAN_pre_ia.md`.

---

## 1. Three Roles

### Production/release behavior

- no research-log dependency;
- no diagnostic state required for correctness;
- no polling retained merely because it helped investigation;
- only the minimum event/state machinery required by the proven design.

### Retained diagnostic build/tool

- preserves useful lifecycle/collision probes for controlled reproduction and future bug reports;
- may be more verbose than release behavior;
- must remain removable without changing collision behavior.

### General combat diagnostics

`tools/Script_CombatMoveLogger` remains a separate proven combat-move/speed tool. Only observations with continuing general value should later be copied there.

Do not merge every temporary collision probe into the general logger.

---

## 2. One Hook Owner

While collision behavior and diagnostics need overlapping Gothic hooks, keep one research DLL with one owner per engine hook.

Current responsibility boundary:

```text
Script_FrameCollisionTest.dll
│
├─ Main / Hook Bridge
│    installs/owns Gothic hooks once
│    captures factual engine events / transient native context
│
├─ CollisionLifecycleGuard
│    C1 shadow execution/source obligations
│    no physical repair
│
├─ CollisionControl
│    proven marker/source behavior
│
└─ CollisionDiagnostics
     observation/logging only
```

The current C1-O2 frozen task may add one `RunScriptFunction` hook/context owner at the tested native boundary. That context is infrastructure for exact actor/SPU/live-frame correlation; it must not become a second attack classifier or generic cleanup system.

Avoid diagnostic state feeding marker behavior decisions.

---

## 3. Current Evidence Model

The collision diagnostic should answer factual questions around one exact execution/source obligation:

1. Did a real equipped source successfully request `Item_Attack`, including `7 -> 7`?
2. Which C1 generation owns that request?
3. Was the request acquired before or at CombatMove?
4. What live outer ScriptFunction correlator was bound to that generation while the frame existed?
5. Did a later CombatMove reuse that same generation or create the ordinary candidate path?
6. Did Gothic perform legitimate cleanup for the exact source?
7. Did the native frame retire normally, or did destructive state replacement remove it?
8. Did the generation finalize cleanly or remain a shadow `WOULD_REPAIR` candidate?
9. Did any binding/frame invariant fail?

Do not add fields merely because they are available.

---

## 4. Established Diagnostic Events to Preserve

The current research prototype has accumulated useful factual observations. Preserve them while C1-O2 is being validated unless a bounded task explicitly removes superseded diagnostics after evidence is safely canonical.

### Collision request / cleanup observation

Existing `eCEntity::SetCollisionGroup` observation remains authoritative for:

- exact changed source entity;
- equipped RIGHT/LEFT slot association;
- requested/before/after group;
- successful offensive `Item_Attack` request, including `7 -> 7`;
- successful transition away from `Item_Attack` used as native cleanup fulfillment;
- tested native cleanup call-site/stack evidence.

A numeric group already being 7 does **not** mean no new request occurred.

### CombatMove observation

Existing `sAICombatMoveInstr` observation remains useful for:

- new initial invocation;
- ordinary C1 candidate creation path;
- persisted asynchronous instruction behavior;
- fullStop termination evidence;
- later C1-O2 generation reuse when the outer frame already owns the execution.

CombatMove remains an inner milestone, not universal outer acquisition.

### AISetState observation

Existing `gCScriptRoutine_PS::AISetState` observation remains the tested destructive-finalization checkpoint for C1 shadow classification when an exact generation/source obligation is already owned.

It is generic infrastructure and must stay a no-op for unrelated processing.

### Primary motion / StartRecover / FullStop historical probes

Retain B1–B9 motion/StartRecover/AIFullStop probes as historical/reproduction diagnostics while useful. They no longer define the current gate and should not be extended simply because they already exist.

Their durable conclusions route through EV-158–EV-191.

### C1 shadow events

Preserve the high-signal C1 records needed to verify:

```text
lifecycle/generation start
source offense request
source cleanup fulfilled
shadow finalization outcome
invariant warning
```

The C1 core result is EV-192–EV-193.

### C1-O1 outer-frame snapshots

The broad C1-O1 stack/frame snapshot probe established the outer lifetime and pointer-reuse qualification. It remains useful evidence/reproduction support, but C1-O2 should **not** turn generic ScriptFunction dispatch into broad per-call logging.

Evidence: EV-195–EV-196.

---

## 5. Current Diagnostic Question — C1-O2 Outer Binding

C1-O2 needs only enough new signal to prove the native binding lifecycle:

```text
pre-CombatMove offense
→ outer binding acquisition + generation

later CombatMove
→ same live binding reuses same generation

ordinary CombatMove-first path
→ candidate generation obtains live outer binding when available

native true ScriptFunction return
→ binding retirement before raw address reuse

failure
→ concise invariant, no guessed fallback
```

### Required high-signal C1-O2 events

The frozen implementation contract should expose, at minimum:

- **pre-CombatMove outer acquisition** with actor, generation, exact source and live-frame correlator summary;
- **CombatMove reuse** showing the same generation was reused from a still-live outer binding;
- **ordinary CombatMove binding** for the existing candidate-created path;
- **outer binding retirement** on true `RunScriptFunction` return;
- **frame mismatch / overlap invariant** if a request or later CombatMove cannot safely match the live binding;
- **null-arguments invariant** if a relevant ScriptFunction cannot satisfy the frozen correlator;
- **`OUTER_RETURN_OUTSTANDING`-style invariant** if a true return retires the live frame while the bound generation still has an outstanding source obligation.

The exact event spelling may follow the frozen C1-O2 implementation contract. Do not create a parallel diagnostic vocabulary merely for documentation.

---

## 6. C1-O2 Transient `RunScriptFunction` Context

The new context is allowed only for the exact synchronous `gCScriptAdmin::RunScriptFunction(..., stateStack, spu)` dispatch.

Diagnostic/context rules:

1. capture the relevant live frame correlator before the original registered ScriptFunction execution can remove it;
2. supplied `gCScriptProcessingUnit *` is the actor-context authority;
3. actor comes from `spu->GetSelfEntity()`;
4. matching live frame requires:
   - exact SPU;
   - top frame is ScriptFunction, not ScriptState;
   - non-null `m_pArguments` equal to the bound value;
   - same ScriptFunction name;
5. break block is context only and may advance during one execution;
6. top-entry address is diagnostic only;
7. action/phase/state/input/family are context only, not ownership identity;
8. wrapper calls original exactly once with unchanged arguments;
9. transient dispatch context must be nesting-safe and leave no context after wrapper exit;
10. true return retires the native binding before any raw-address reuse can match it later.

Do not dereference/classify arguments merely to invent a stronger identity.

Evidence basis: EV-195–EV-196.

---

## 7. Logging Restraint

The generic `RunScriptFunction` path executes far more than attacks. Therefore:

- no broad per-call ScriptFunction dump;
- no continuous state-stack logging;
- no full stack dump for every dispatch;
- no action/family table to decide which ScriptFunctions matter;
- no logging merely because a frame exists.

Emit C1-O2 records only when a fact is relevant to binding/acquisition/reuse/retirement or when a frozen invariant fails.

The diagnostic should remain bounded enough that the controlled runtime matrix can be inspected causally.

---

## 8. Cleanup Observation Semantics

Do not define cleanup as “the group is currently not 7.”

The current C1 model observes the actual successful consequence of a source request:

```text
successful Item_Attack request
→ exact source obligation becomes outstanding

successful later transition away from Item_Attack
→ that exact source obligation is fulfilled
```

Cleanup can execute under a different ScriptState/reaction context from the old attack ScriptFunction. Therefore C1-O2 frame matching must **not** be required for cleanup fulfillment.

Do not add cleanup because `RunScriptFunction` returned, CombatMove fullStopped, Recover appeared, or AISetState was requested.

---

## 9. Execution Identity

Current authority after C1-O1:

```text
C1 monotonic generation
= durable plugin execution identity

exact SPU + live ScriptFunction + non-null m_pArguments + same ScriptFunction name
= temporary native lifetime correlator only
```

Raw stack-entry or arguments addresses are not globally unique; they may be reused after retirement.

If a future relevant ScriptFunction has null `m_pArguments`, log the failure and leave the new route unacquired. Do not guess another identity rule inside diagnostics.

---

## 10. Marker Diagnostics Remain Separate

Marker occurrence/replay/source-set bookkeeping is proven behavior with its own regression history. C1/C1-O2 must not silently reinterpret marker diagnostics as execution cleanup state.

Preserve the distinction:

```text
marker occurrence/exact-set bookkeeping
≠
physical source cleanup obligation
```

Before any future marker-core simplification, retrieve the marker-lifetime route in `EVIDENCE_INDEX.md` and `COLLISION_LIFECYCLE_PLAN.md`.

---

## 11. What Not to Add Without a New Question

Do not add:

- production physical repair;
- GetUp/Quick/Whirl/action/input/state-name ownership classifiers;
- unconditional cleanup/finalization on `RunScriptFunction` return, FullStop or AISetState;
- adoption of arbitrary already-group-7 equipment;
- null-arguments identity fallback;
- broad per-frame actor/world scans;
- wall-clock cleanup timers;
- duplicate hook owners for the same target;
- another lifecycle model inside diagnostics;
- marker-core simplification during C1-O2;
- guessed binary layouts when SDK-supported fields or opaque factual logging are sufficient.

---

## 12. C1-O2 Diagnostic Acceptance

The diagnostic architecture is sufficient for C1-O2 when a controlled run can establish, without broad dumps:

1. the pre-CombatMove GetUp offense acquired generation N from a live outer frame;
2. its later CombatMove reused generation N;
3. ordinary CombatMove-first controls still create/bind the expected candidate generation;
4. legitimate native cleanup fulfills exact source obligations independently of old frame context;
5. true-return binding retirement occurs before a later reused address could match;
6. known bad armed abandonment keeps the existing shadow `WOULD_REPAIR` classification;
7. clean/reaction/pre-activation controls remain no-op;
8. any mismatch/null/outstanding-return condition appears as an explicit invariant rather than hidden fallback behavior;
9. all records state/guarantee that physical collision behavior was not changed by the shadow diagnostic.

---

## 13. Release Extraction Rule

When collision behavior is stable:

1. keep production behavior modules and required hook ownership;
2. omit verbose research diagnostics from the release build;
3. retain a diagnostic build/tool for future controlled reproduction;
4. selectively migrate only generally useful observations to the combat logger;
5. preserve raw logs/evidence IDs so removed instrumentation does not erase what it taught us.

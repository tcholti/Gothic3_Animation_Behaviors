# Collision Lifecycle Diagnostic Architecture

**Status:** Current research-diagnostic authority  
**Updated:** 2026-08-30

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
- must remain removable without changing the intended production rule.

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
│    C1 monotonic execution/source obligations
│    C1-O2 temporary pre-Combat ScriptFunction bridge
│    C1-R1 exact controlled physical repair
│
├─ CollisionControl
│    proven marker/source behavior
│
└─ CollisionDiagnostics
     observation/logging only
```

The `RunScriptFunction` context remains infrastructure for exact actor/SPU/live-frame correlation. It must not become a second attack classifier or generic cleanup system.

Avoid diagnostic state feeding marker behavior decisions.

---

## 3. Current Evidence Model

The collision diagnostic should answer factual questions around one exact execution/source obligation:

1. Did a real equipped source successfully request `Item_Attack`, including `7 -> 7`?
2. Which C1 monotonic generation owns that request?
3. Was the generation acquired through the ordinary CombatMove path or the proven pre-Combat ScriptFunction bridge?
4. If early acquisition occurred, was the temporary native binding consumed by matching CombatMove before wrapper return?
5. Did Gothic perform legitimate cleanup for the exact source?
6. Did destructive AISetState finalize the generation with an obligation still outstanding?
7. Was the remembered source still exact current equipped RIGHT/LEFT and therefore safe to observe/mutate?
8. If the source was still physically `Item_Attack(7)`, did C1-R1 issue exactly one `Item_Equipped(5)` request and obtain exact group 5?
9. Did any acquisition, binding, liveness, repair or generation invariant fail?

Do not add fields merely because they are available.

---

## 4. Established Diagnostic Events to Preserve

### Collision request / cleanup observation

Existing `eCEntity::SetCollisionGroup` observation remains authoritative for:

- exact changed source entity;
- equipped RIGHT/LEFT slot association;
- requested/before/after group;
- successful offensive `Item_Attack` request, including `7 -> 7`;
- successful transition away from `Item_Attack` used as source-obligation fulfillment;
- tested native cleanup call-site/stack evidence;
- C1-R1 repair requests passing through the same normal hook path.

A numeric group already being 7 does **not** mean no new request occurred.

### CombatMove observation

Existing `sAICombatMoveInstr` observation remains useful for:

- new initial invocation;
- ordinary C1 candidate creation path;
- persisted asynchronous instruction behavior;
- FullStop termination evidence;
- matching consumption of the temporary pre-Combat bridge.

CombatMove remains an inner milestone, not universal outer acquisition.

### AISetState observation

Existing `gCScriptRoutine_PS::AISetState` observation remains the tested destructive-finalization checkpoint for an already-owned exact generation/source obligation.

Native AISetState executes first. C1 finalization runs afterward so native/reaction cleanup has precedence.

AISetState is generic infrastructure and must remain a no-op for unrelated processing.

### Primary motion / StartRecover / FullStop historical probes

Retain B1–B9 motion/StartRecover/AIFullStop probes as historical/reproduction diagnostics while useful. They no longer define the active gate and should not be extended simply because they already exist.

Their durable conclusions route through EV-158–EV-191.

### C1 lifecycle events

Preserve the high-signal C1 records needed to verify:

```text
lifecycle/generation start
source offense request
source cleanup fulfilled
finalization outcome
repair attempted/result
invariant warning
```

Core ownership evidence: EV-192–EV-193.  
Outer acquisition/binding closure: EV-204–EV-205.  
Controlled physical repair: EV-206.

### C1-O2 bridge events

The lightweight P1/P2 bridge is now established, not an open diagnostic hypothesis. Preserve only enough signal to prove/regress:

```text
PRECOMBAT_ACQUIRED
PRECOMBAT_BRIDGE_CONSUMED
relevant DISPATCH RETURN
binding/generation/null-argument invariant failures
```

Do not restore broad eager dispatch capture or broad per-call ScriptFunction logging.

### C1-R1 repair events

Preserve enough signal to distinguish:

```text
NO_OP_NO_OUTSTANDING
UNRESOLVED_NOT_EQUIPPED
NO_OP_PHYSICALLY_CLEAN_RECONCILED
REPAIRED_TO_ITEM_EQUIPPED
REPAIR_DIVERGED_FROM_ITEM_EQUIPPED
```

A repair result is meaningful only together with exact source ownership, liveness establishment, pre-repair group, requested group and post-repair group.

---

## 5. Current Diagnostic Question

C1-O2 is closed for the tested bridge model. C1-R1 implementation and its main positive/no-op/source-specific/marker/broad exercised coverage are also established.

The current runtime question is narrow:

> Do genuine unarmed/Fist and crossbow gameplay remain outside inappropriate weapon-style C1 repair ownership/mutation while the validated C1-R1 DLL remains stable?

The exact current test responsibility is owned by `SESSION_ENTRYPOINT.md` and `BETWEEN_CHATS.md`.

No new diagnostic architecture is required for that closure. Use the existing events and inspect only the signals needed to establish absence of inappropriate obligation/repair/failure behavior.

---

## 6. Established `RunScriptFunction` Context Rules

The proven synchronous `gCScriptAdmin::RunScriptFunction(..., stateStack, spu)` context remains bounded by these rules:

1. supplied `gCScriptProcessingUnit *` is the actor-context authority;
2. actor comes from `spu->GetSelfEntity()`;
3. relevant live-frame matching uses exact SPU, ScriptFunction frame, non-null `m_pArguments` and same ScriptFunction name;
4. break block is context only and may advance during one execution;
5. raw top-entry/argument addresses are lifetime-bound diagnostic correlators, not durable IDs;
6. action/phase/state/input/family are context only, not ownership identity;
7. wrapper calls original exactly once with unchanged arguments;
8. transient scope is nesting-safe and does not persist after wrapper exit;
9. the temporary native binding is consumed before wrapper return in the proven early-offense path;
10. C1's monotonic generation remains the durable identity afterward.

Do not dereference/classify arguments merely to invent a stronger identity.

Evidence: EV-195–EV-196, EV-204–EV-205.

---

## 7. Logging Restraint

The generic script and collision paths execute far more than the active test needs. Therefore:

- no broad per-call ScriptFunction dump;
- no continuous state-stack logging;
- no full stack dump for every dispatch;
- no family/action table to decide ownership;
- no polling/world scans;
- no logging merely because a frame exists;
- no new verbose probe when existing C1/SetCollisionGroup/marker diagnostics already answer the question.

For large runtime logs, preserve the raw artifact and use the deterministic large-log evidence tooling described by POP-07 / `tools/log_evidence/README.md` rather than weakening runtime logging to fit connector limits.

---

## 8. Cleanup and Repair Observation Semantics

Do not define cleanup as “the group is currently not 7.”

The current C1 model observes consequences:

```text
successful Item_Attack request
→ exact source obligation becomes outstanding

successful later transition away from Item_Attack
→ exact source obligation is fulfilled
```

Cleanup can execute under a different ScriptState/reaction context from the old attack ScriptFunction. Therefore old frame matching is not required for cleanup fulfillment.

C1-R1 acts only after native AISetState has executed and only when:

```text
obligation still outstanding
+ exact current equipped identity establishes source liveness
+ actual group still Item_Attack(7)
```

Then and only then:

```text
SetCollisionGroup(Item_Equipped)
→ verify exact Item_Equipped(5)
```

Do not add cleanup because `RunScriptFunction` returned, CombatMove FullStopped, Recover appeared, or AISetState was merely requested.

---

## 9. Execution Identity

Current authority:

```text
C1 monotonic generation
= durable plugin execution identity

exact SPU + live ScriptFunction + non-null m_pArguments + same ScriptFunction name
= temporary native lifetime correlator only where early acquisition needs it
```

Raw stack-entry or argument addresses are not globally unique and can be reused after retirement.

If a future relevant ScriptFunction has null `m_pArguments`, log the failure and leave that route unacquired. Do not guess another identity rule inside diagnostics.

---

## 10. Marker Diagnostics Remain Separate

Marker occurrence/replay/source-set bookkeeping is proven behavior with its own regression history. C1 must not reinterpret marker diagnostics as execution cleanup state.

Preserve the distinction:

```text
marker occurrence/exact-set bookkeeping
≠
physical source cleanup obligation
```

C1-R1 repair intentionally passes through the existing SetCollisionGroup hook so established source-obligation transition and marker-owned source retirement remain on the normal path.

Before any future marker-core simplification, retrieve the marker-lifetime route in `EVIDENCE_INDEX.md` and `COLLISION_LIFECYCLE_PLAN.md`.

---

## 11. What Not to Add Without a New Question

Do not add:

- GetUp/Quick/Whirl/action/input/state-name ownership classifiers;
- unconditional cleanup/finalization on `RunScriptFunction` return, FullStop or AISetState;
- adoption of arbitrary already-group-7 equipment;
- null-arguments identity fallback;
- broad per-frame actor/world scans;
- wall-clock cleanup timers;
- duplicate hook owners for the same target;
- another lifecycle model inside diagnostics;
- marker-core simplification during C1-R1 closure;
- `ClearTriggeredList()` as terminal repair behavior;
- guessed binary layouts when SDK-supported fields or opaque factual logging are sufficient.

---

## 12. Current Diagnostic Acceptance

The retained diagnostic architecture is sufficient when a controlled run can establish, without broad dumps:

1. exact source offense/cleanup obligation transitions;
2. pre-Combat acquisition/bridge consumption when that path occurs;
3. clean/reaction/no-offense finalizations as non-mutating;
4. destructive outstanding live/equipped group-7 finalization as one exact `7 -> 5` repair;
5. source-specific Dual behavior;
6. marker-owned repair/retirement interaction without reopening stale collision;
7. unsupported/negative source classes do not acquire inappropriate weapon-style repair obligations;
8. any binding/liveness/repair divergence appears as an explicit invariant/failure rather than hidden fallback behavior.

---

## 13. Release Extraction Rule

When collision behavior is stable:

1. keep production behavior modules and required hook ownership;
2. omit verbose research diagnostics from the release build;
3. retain a diagnostic build/tool for future controlled reproduction;
4. selectively migrate only generally useful observations to the combat logger;
5. preserve raw logs/evidence IDs so removed instrumentation does not erase what it taught us.

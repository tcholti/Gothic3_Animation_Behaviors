# Collision Lifecycle Diagnostic Architecture

**Status:** Current research-diagnostic authority  
**Updated:** 2026-08-30

## Purpose

Define the smallest observational instrumentation needed to answer collision-lifecycle questions without turning diagnostics into a second behavior/lifecycle system or making routine combat logs unnecessarily large.

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
- may expose opt-in deep probes when a specific investigation requires them;
- should keep ordinary collision-development logs compact enough to inspect efficiently;
- must remain removable/reducible without changing intended behavior.

### General combat diagnostics

`tools/Script_CombatMoveLogger` remains a separate proven combat-move/speed tool. Only observations with continuing general value should later be copied there.

Do not merge every temporary collision probe into the general logger.

---

## 2. One Hook Owner

While collision behavior and diagnostics need overlapping Gothic hooks, keep one research DLL with one owner per engine hook.

Target responsibility boundary:

```text
Script_FrameCollisionTest.dll
│
├─ EngineBridge
│    installs/owns Gothic hooks once
│    preserves calling conventions / recursion safety / ordering
│    captures factual engine events / transient native context
│
├─ CollisionLifecycleGuard
│    C1 monotonic execution/source obligations
│    C1-O2 temporary pre-Combat ScriptFunction bridge
│    C1-R1 exact controlled physical repair
│
├─ FrameCollisionMarkers / CollisionControl
│    marker ownership and authored collision behavior
│
├─ CollisionSources
│    generic source identity / source-specific operations
│
└─ CollisionDiagnostics
     observation/logging only
```

The `RunScriptFunction` context remains infrastructure for exact actor/SPU/live-frame correlation. It must not become a second attack classifier or generic cleanup system.

Avoid diagnostic state feeding marker or lifecycle behavior decisions.

---

## 3. Current Evidence Model

The collision diagnostic must be able to answer factual questions around one exact execution/source obligation:

1. Did an exact source successfully request offense, including `7 -> 7` for equipped weapons?
2. Which C1 monotonic generation owns that request?
3. Was the generation acquired through ordinary CombatMove or the proven pre-Combat ScriptFunction bridge?
4. If early acquisition occurred, was the temporary native binding consumed by matching CombatMove before wrapper return?
5. Did Gothic perform legitimate cleanup for the exact source?
6. Did destructive AISetState finalize the generation with an obligation still outstanding?
7. Was the remembered source still exact current equipped RIGHT/LEFT and therefore safe to observe/mutate?
8. If the source was still physically `Item_Attack(7)`, did C1-R1 issue exactly one `Item_Equipped(5)` request and obtain exact group 5?
9. Did marker ownership, occurrence, exact-set switching, source rearm or native suppression behave as authored?
10. Did any acquisition, binding, liveness, repair, marker or generation invariant fail?

Do not add fields merely because they are available.

---

## 4. Core Collision Evidence — Preserve by Default

Ordinary collision-development/regression runs should retain enough exact information to verify the active system without broad historical dumps.

Preserve startup/build identity and clean unload.

Preserve marker evidence sufficient to establish exact actor/current motion, action/phase, marker opcode, required/resolved source set, native callback suppression, accepted/rejected/duplicate/budget/OFF result, exact source-set switching, source activation/deactivation/rearm, and StatePosition mutation where it is part of native suppression.

Existing `eCEntity::SetCollisionGroup` observation remains authoritative for exact changed source, relevant equipped RIGHT/LEFT association, requested/before/after group, successful offensive `Item_Attack` request including `7 -> 7`, successful transition away from `Item_Attack`, and C1-R1 repair passing through the same normal hook path.

Preserve high-signal C1 records for:

```text
lifecycle/generation start
source offense request
source cleanup fulfilled
finalization outcome
repair attempted/result
explicit invariant/failure warning
```

Preserve only enough routine C1-O2 signal to regress:

```text
PRECOMBAT_ACQUIRED
PRECOMBAT_BRIDGE_CONSUMED
relevant DISPATCH RETURN when early offense occurred
binding/generation/null-argument invariant failures
```

Preserve C1-R1 outcome distinctions:

```text
NO_OP_NO_OUTSTANDING
UNRESOLVED_NOT_EQUIPPED
NO_OP_PHYSICALLY_CLEAN_RECONCILED
REPAIRED_TO_ITEM_EQUIPPED
REPAIR_DIVERGED_FROM_ITEM_EQUIPPED
```

A repair result is meaningful only together with exact source ownership, liveness establishment, pre-repair group, requested group and post-repair group.

---

## 5. Opt-In Deep Probes — Retain Only for Concrete Investigations

The B1–B9 research phase required broad observation to discover native ownership/cleanup paths. Those questions are now largely closed and their durable conclusions live in canonical evidence.

The following current probes are candidates for **opt-in diagnostic mode rather than ordinary always-on logging**:

```text
PrimaryFirst PlayMotion / StopMotion snapshots
OnTick marker-owned primary-motion lifetime tracking
AICombatMoveStartRecover begin/end snapshots and stacks
AIFullStop callsite / input-duration / stack capture
broad AISetState caller/context stack snapshots
broad outer ScriptFunction frame snapshots
full native-cleanup stack capture for every 7 -> 5 transition
empty-primary successor / replacement stack probes
```

These are candidates, not an instruction to delete them immediately.

Use them only when a concrete future question needs them, such as `AttackContinuationProtection`, a new cleanup contradiction, a hook-order/calling-convention contradiction, a source-lifetime problem or a new animation-replacement question.

---

## 6. Obsolete Historical Noise — Removal Rule

A diagnostic path may be removed entirely only when all of the following are true:

```text
1. the question it answered is closed;
2. its durable conclusion/provenance already exists in canonical evidence;
3. no current collision/marker/lifecycle/continuation responsibility depends on the runtime signal;
4. an opt-in deep mode would not provide realistic future value;
5. removing it cannot alter behavior, hook ordering or feature state.
```

Do not delete a probe merely because its output is large. Prefer a compact core event or an opt-in deep mode before deleting useful investigative capability.

---

## 7. Mandatory Post-EngineBridge Diagnostics Review

After the central EngineBridge extraction, every `.cpp` in `prototypes/Script_FrameCollisionTest` is reviewed one by one before marker simplification begins. `CollisionDiagnostics.cpp` receives a dedicated evidence-volume audit during that gate.

For every diagnostic function/event, classify it as exactly one of:

```text
CORE COLLISION EVIDENCE
OPT-IN DEEP PROBE
OBSOLETE HISTORICAL NOISE
```

The review must answer:

```text
- Which current/future collision question does this event answer?
- Is the same fact already available from a smaller authoritative event?
- Does it execute on a high-frequency path?
- Does it duplicate large state/stack blocks repeatedly?
- Would moving it behind a diagnostic mode preserve investigative precision?
- Could removing/guarding it accidentally change hook behavior or ordering?
```

Do not perform logger slimming before the EngineBridge refactor has passed its own compact runtime baseline with the existing logger. Structural behavior and observation changes must remain causally separable.

Preferred sequence:

```text
EngineBridge extraction
→ build/source audit
→ one-by-one .cpp review including diagnostics classification
→ compact collision baseline with unchanged logger
→ freeze/implement approved logger reduction separately
→ prove reduced/default logger still exposes all required collision signals
→ only then begin marker-bookkeeping simplification
```

---

## 8. Established `RunScriptFunction` Context Rules

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

## 9. Logging Restraint

Generic script/collision paths execute far more than most active tests need. Therefore:

- no broad per-call ScriptFunction dump;
- no continuous state-stack logging;
- no full stack dump for every ordinary dispatch/cleanup;
- no family/action table to decide lifecycle ownership;
- no polling/world scans for diagnostic convenience;
- no logging merely because a frame exists;
- no repeated large context block when a compact generation/source event already answers the question;
- no new verbose probe when existing C1/SetCollisionGroup/marker diagnostics already answer the question.

Large logs may still legitimately occur during broad compatibility or actor-general tests. Preserve raw evidence and use POP-07 when necessary, but **large-log tooling is not a reason to keep avoidable routine verbosity**.

---

## 10. Cleanup and Repair Observation Semantics

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

## 11. Execution Identity

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

## 12. Marker Diagnostics Remain Separate

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

## 13. Diagnostic Sufficiency Contract

The default retained diagnostic profile is sufficient only if controlled runs can still establish, without deep probes:

1. exact marker ownership/suppression and accepted/rejected marker result;
2. exact source offense/cleanup transition;
3. C1 generation identity for the relevant source obligation;
4. pre-Combat acquisition/bridge consumption when that path occurs;
5. clean/reaction/no-offense finalization as non-mutating;
6. destructive outstanding live/equipped group-7 finalization as one exact `7 -> 5` repair;
7. source-specific Dual independence;
8. marker-owned repair/retirement interaction without reopening stale collision;
9. unsupported/negative source classes do not acquire inappropriate weapon-style repair obligations;
10. any binding/liveness/repair/marker divergence appears as an explicit invariant/failure rather than hidden fallback behavior;
11. build identity and clean unload.

If slimming the logger makes any of these facts ambiguous, the reduction is too aggressive and must be revised.

For a dedicated future investigation, an opt-in deep profile may add call stacks, motion snapshots or broader native context without changing behavior.

---

## 14. What Not to Add Without a New Question

Do not add:

- GetUp/Quick/Whirl/action/input/state-name lifecycle ownership classifiers;
- unconditional cleanup/finalization on `RunScriptFunction` return, FullStop or AISetState;
- adoption of arbitrary already-group-7 equipment;
- null-arguments identity fallback;
- broad per-frame actor/world scans;
- wall-clock cleanup timers;
- duplicate hook owners for the same target;
- another lifecycle model inside diagnostics;
- marker-core simplification merely to reduce log size;
- `ClearTriggeredList()` as terminal repair behavior;
- guessed binary layouts when SDK-supported fields or opaque factual logging are sufficient.

---

## 15. Release Extraction Rule

When collision behavior is stable:

1. keep production behavior modules and required hook ownership;
2. omit default research verbosity from the release build;
3. retain a diagnostic build/profile for future controlled reproduction;
4. keep compact exact failure/invariant observability where it is useful and cheap;
5. selectively migrate only generally useful observations to the general combat logger;
6. preserve raw logs/evidence IDs so removed instrumentation does not erase what it taught us.

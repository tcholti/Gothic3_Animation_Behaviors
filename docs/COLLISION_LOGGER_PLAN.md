# Collision Lifecycle Diagnostic Architecture

**Status:** Current research-diagnostic authority  
**Updated:** 2026-09-01

## Purpose

Define the smallest observational instrumentation needed to validate collision behavior without turning diagnostics into a second behavior system or contaminating the public release binary.

> **The logger measures the architecture. It does not define it.**

Release/build separation is governed by `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

Completed structural rewrite reference: `SECOND_PASS_REWRITE_CONTRACT.md`.  
Current marker-bookkeeping authority: `MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md`.  
Exact evidence: `EVIDENCE_INDEX.md` → canonical evidence ledgers.  
Historical probe detail: evidence/raw/archive + archived pre-IA logger documents.

---

## 1. Product Roles

### Public release behavior

The public `Script_G3AnimationBehaviors.dll` contains **no research diagnostics at all**.

```text
NO CollisionDiagnostics implementation
NO research log strings/banners
NO diagnostic state
NO diagnostic-only hooks
NO stack/RVA capture
NO motion-lifetime research probes
NO hidden runtime diagnostic mode
NO behavior dependency on diagnostics
```

This is stronger than “logging disabled.” Diagnostic source is not compiled into the public release target.

### Instrumented diagnostic twin

The diagnostic/research build uses the same behavior core plus instrumentation for controlled validation and future investigation.

It contains:

```text
compact default/core evidence
+ optional deep probes
```

It is used **in place of** the release DLL during testing. Do not load release and diagnostic twins together unless a future architecture explicitly proves safe coexistence.

### General combat diagnostics

`tools/Script_CombatMoveLogger` remains a separate general Gothic combat/speed research tool for facts that can be independently observed.

Do not force internal Animation Behaviors state into that generic logger merely to avoid an instrumented twin.

---

## 2. Dependency Rule

Correct direction:

```text
EngineBridge / behavior modules / source adapters
        ↓
compact factual behavior result/state
        ↓
CollisionDiagnostics [diagnostic build only]
```

Forbidden:

```text
behavior correctness
→ requires logger open
→ requires CollisionDiagnostics state
→ requires diagnostic-only hook
→ requires diagnostic polling
```

The behavior-only prototype target created by the completed second-pass rewrite mechanically enforces this separation and passed functional/release-purity verification through EV-215.

---

## 3. One Hook Owner

Each built DLL has one physical owner per Gothic hook: `EngineBridge`.

Behavior-required current collision hooks:

```text
OnAI_Attack
OnAI_QuickAttack
OnAI_WhirlAttack
StartEffect
SetCollisionGroup
AICombatMoveInstr
AISetState
RunScriptFunction
```

Current diagnostic-only/deep hook candidates:

```text
PlayMotion
StopMotion
AICombatMoveStartRecover
OnTick
AIFullStop
```

`AIFullStop` is diagnostic-only for the current collision responsibility but remains a proven explicit-this transport point that may later become behavior-required for `AttackContinuationProtection`.

Diagnostic-only hooks must never become production prerequisites merely because the historical research DLL always installed them.

---

## 4. Core Diagnostic Evidence — Default in Diagnostic Twin

Ordinary diagnostic/regression runs keep compact evidence sufficient to prove the active behavior system.

Preserve:

### Build / lifetime

```text
build identity
diagnostic profile identity
clean startup / clean unload
```

### Marker ownership

```text
actor / exact current motion
action / phase
marker opcode
required/resolved source set
native callback suppression decision
C1 generation used as marker execution identity
accepted/rejected/duplicate/budget/OFF outcome
exact source-set switch
activation/deactivation/rearm
StatePosition mutation where behaviorally used
```

### Physical source transitions

```text
exact changed source
RIGHT/LEFT slot association where relevant
requested group
before group
after group
successful offense including 7 -> 7
successful transition away from Item_Attack
exact marker-owned physical source-bit retirement
```

### C1 lifecycle

```text
generation start
exact source offense request / obligation
cleanup fulfilled
finalization outcome
repair attempted/result
explicit invariant/failure signal
```

### P2 bridge

Preserve only enough routine signal to regress:

```text
PRECOMBAT_ACQUIRED
PRECOMBAT_BRIDGE_CONSUMED
relevant dispatch return when early offense occurred
binding/generation/null-argument invariant failures
```

### C1-R1 outcomes

```text
NO_OP_NO_OUTSTANDING
UNRESOLVED_NOT_EQUIPPED
NO_OP_PHYSICALLY_CLEAN_RECONCILED
REPAIRED_TO_ITEM_EQUIPPED
REPAIR_DIVERGED_FROM_ITEM_EQUIPPED
```

A repair result is meaningful only together with exact source ownership, liveness establishment, pre-repair group, requested group and post-repair group.

**None of this diagnostic evidence belongs in the public release binary.**

---

## 5. Opt-In Deep Probes — Diagnostic Twin Only

Retain for concrete investigations, disabled by default in ordinary diagnostic runs:

```text
PrimaryFirst PlayMotion / StopMotion snapshots
hit replacement stacks
empty-primary successor stacks
StopMotion hit stacks
AICombatMoveStartRecover begin/end + stacks
CombatMove FullStop stack/context
AIFullStop callsite / input-duration / primary-motion / stack
broad AISetState caller/state/primary-motion/stack context
broad outer ScriptFunction/state-stack snapshots
P1 detailed scope/SPU/runtime-stack pointer evidence
full native cleanup caller module/RVA + stack
OnTick marker-owned PrimaryFirst lifetime tracking
```

Use only when a concrete question requires them, such as:

```text
AttackContinuationProtection
new cleanup contradiction
new source-lifetime contradiction
hook-order/calling-convention investigation
animation replacement/lifetime question
```

Deep capture should happen only after a profile/build check. Do not pay stack/module/motion-sampling cost merely because deep code exists in the diagnostic product.

---

## 6. Obsolete Historical Noise

Remove from normal diagnostic output when its question is already closed and canonical evidence preserves the conclusion.

Examples:

```text
B1–B9 / O1 / P1 experiment chronology in startup banner
stale statement that C1 is shadow-only / WOULD_REPAIR-only
repeated CleanupBehaviorChanged: 0
repeated LifecycleBehaviorChanged: 0
repeated CollisionBehaviorChanged: 0
TopEntryAddressIsExecutionIdentity: 0
ArgumentsDereferencedOrClassified: 0
TLSRestoredBeforeLog: 1
ScopePersistedAfterReturn: 0
constant collision-group value labels on every event
large repeated player state/source blocks when compact exact-source facts suffice
```

Do not delete a useful future deep probe merely because it is verbose. Move it behind deep diagnostics instead.

A probe may be removed entirely only when:

```text
1. its question is closed;
2. durable conclusion/provenance exists in canonical evidence;
3. no current/future plausible diagnostic question needs the signal;
4. removing it cannot alter behavior, hook ordering or feature state.
```

---

## 7. RuntimeClock Is Not Diagnostics

Second-pass review corrected the earlier classification of `HookBridgeRuntime`.

The elapsed-millisecond clock participates in actual marker duplicate acceptance:

```text
same actor/source/motion/marker/action/phase/state time
+ elapsed delta <= 5 ms
→ same-update duplicate rejection
```

The completed rewrite renamed:

```text
HookBridgeRuntime
→ RuntimeClock
```

`RuntimeClock` remains in the behavior core.

Do not remove or diagnostic-gate this clock until a separate behavior change proves a replacement duplicate predicate.

---

## 8. CollisionLifecycleGuard Diagnostic Boundary

The completed second-pass rewrite removed direct diagnostic formatting/output responsibility from `CollisionLifecycleGuard`.

Current boundary:

```text
CollisionLifecycleGuard
→ decides/updates C1 behavior
→ returns compact factual synchronous result structures

CollisionDiagnostics [diagnostic build]
→ formats/logs those facts
```

Do not introduce a generic event bus, asynchronous queue, callback registry or second lifecycle model.

The C1 finalizer remains two-phase and reentrancy-safe:

```text
1. classify/repair fixed max-two sources into stack-local results
2. diagnostic formatting only after mutation/classification completes
```

No diagnostic block may remain half-written across reentrant `SetCollisionGroup` repair.

---

## 9. Marker Diagnostics Remain Separate From Lifecycle

Marker occurrence/replay/source-set bookkeeping is behavior with its own regression history.

Preserve the distinction:

```text
marker occurrence/exact-set bookkeeping
≠
physical source cleanup obligation
```

Gate 4 established:

```text
C1 monotonic generation
= durable marker occurrence/dedupe execution identity
```

The older marker-local source/motion/action/phase/state-time and controlled-callback rollback guesses are no longer execution-boundary authority. Natural marker-source retirement is factual retirement of the exact physical source bit/window only.

This does **not** collapse marker behavior into lifecycle repair. Preserve occurrence budgets, duplicate/replay protection, exact-set RIGHT/LEFT/BOTH/OFF semantics, OFF intra-Hit gaps, repeated-contact rearm, StatePosition handling, supported-family ownership, physical source/window state and dead/late rejection.

C1-R1 repair intentionally passes through the normal SetCollisionGroup bridge so marker-owned physical source retirement and C1 source-obligation observation remain on the established path.

Before any future marker-core change:

```text
EVIDENCE_INDEX.md
→ marker execution lifetime/bookkeeping
→ EV-131–EV-133 / EV-167 / EV-213–EV-214
→ MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md
→ COLLISION_LIFECYCLE_PLAN.md §9
```

Do not use logger reduction as a reason to weaken marker behavior.

---

## 10. Diagnostic Sufficiency Contract

The default diagnostic twin is sufficient only if controlled runs can establish without deep probes:

```text
1. exact marker ownership/suppression/result
2. exact source offense/cleanup transition
3. C1 generation for marker execution identity and source obligation
4. pre-Combat acquisition/bridge consumption when present
5. clean/reaction/no-offense finalization as non-mutating
6. destructive outstanding live/equipped group-7 finalization as one exact 7 -> 5 repair
7. Dual source independence
8. marker-owned repair/physical-bit retirement without stale reopen
9. unsupported/negative sources do not acquire inappropriate weapon-style repair
10. invariant/failure divergence appears explicitly
11. build identity + clean unload
```

If compacting the diagnostic product makes any required fact ambiguous, the reduction is too aggressive.

---

## 11. Logging Restraint

Generic script/collision paths execute far more often than active tests need.

Therefore default diagnostics should avoid:

```text
broad per-call ScriptFunction dumps
continuous state-stack logging
full stack capture for ordinary cleanup
generic per-frame actor/world polling
repeated large context blocks when compact generation/source facts answer the question
```

Large logs may still legitimately occur during broad diagnostic compatibility tests. Preserve raw artifacts and use deterministic reduction tools rather than keeping avoidable default verbosity.

---

## 12. Cleanup / Repair Observation Semantics

Do not define cleanup as “group currently is not 7.”

Current C1 model observes consequences:

```text
successful Item_Attack request
→ exact source obligation outstanding

successful later transition away from Item_Attack
→ exact source obligation fulfilled
```

C1-R1 acts only after native AISetState and only when:

```text
obligation outstanding
+ exact current equipped identity establishes liveness
+ actual source still Item_Attack(7)
```

Then exactly:

```text
SetCollisionGroup(Item_Equipped)
→ verify Item_Equipped(5)
```

Do not add cleanup because `RunScriptFunction` returned, CombatMove FullStopped, Recover appeared or AISetState was merely requested.

---

## 13. Execution Identity

```text
C1 monotonic generation
= durable plugin execution identity
= durable marker occurrence/dedupe execution identity

exact SPU + live ScriptFunction + non-null m_pArguments + same ScriptFunction name
= temporary native correlator only where early acquisition needs it
```

Raw frame/argument addresses are not globally unique.

Diagnostics may observe failures but must not invent identity fallbacks.

---

## 14. Build / Release Extraction Rule

Current prototype architecture mechanically produces:

```text
Script_FrameCollisionTest
= diagnostic research target

Script_FrameCollisionBehaviorTest
= behavior-only target with no diagnostics compiled
```

Never deploy both together.

This separation passed source/build verification and behavior-only runtime verification through EV-208–EV-215.

Later production:

```text
Script_G3AnimationBehaviors release
= mature behavior modules only
= zero research diagnostics

instrumented diagnostic twin
= same behavior core + compact/deep diagnostics
= used in place of release for controlled reproduction
```

Before public release verify explicitly:

```text
release target does not compile diagnostic sources
release target does not install diagnostic-only hooks
release binary contains no research log paths/banners/diagnostic state
behavior passes runtime/compatibility tests without diagnostics
separate diagnostic twin remains available for reproduction
```

Canonical release rule: `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

---

## 15. Current Sequence

Architecture verification is complete through EV-215. There is no pending diagnostic regression merely to reconfirm the second-pass/Gate-4 architecture.

Current repository sequence:

```text
documentation/knowledge cleanup
→ separate justified raw→archive provenance migration
→ temporary-branch inspection
→ protected-main stable promotion/verification
→ new collision feature expansion
```

When future engineering creates a new diagnostic question:

```text
freeze the smallest falsifiable question
→ use CORE diagnostics if sufficient
→ enable deep probes only when CORE cannot establish the required fact
→ test the diagnostic twin in place of behavior-only release product
→ return to behavior-only verification when the changed behavior is ready
```

Structural behavior and observation changes remain causally separated.

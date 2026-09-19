# Collision Diagnostic Architecture

**Status:** Current research-diagnostic authority  
**Updated:** 2026-09-16

## Purpose

Define the smallest observational instrumentation needed to validate collision behavior without turning diagnostics into behavior, contaminating the release DLL, or producing unnecessarily huge logs during large regression/compatibility tests.

> The logger measures the architecture. It does not define it.

> **Known successful behavior logs compactly. Unknown, unsupported, contradictory, repair, or invariant behavior logs richly.**

Release/build separation: `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.  
Behavior architecture: `DESIGN.md`.  
Established collision facts: `COLLISION_REFERENCE.md`.  
Lifecycle authority: `COLLISION_LIFECYCLE.md`.  
Validation authority: `COLLISION_TEST_PLAN.md`.  
Evidence: `EVIDENCE_INDEX.md`.

---

## 1. Product Roles

### Public release

`Script_G3AnimationBehaviors.dll` contains behavior only:

```text
NO CollisionDiagnostics implementation
NO research log strings/banners
NO diagnostic state
NO diagnostic-only hooks
NO stack/RVA capture
NO deep motion probes
NO behavior dependency on diagnostics
```

This is a mechanical source/preprocess/compile/link separation, not a runtime setting.

### CORE diagnostic twin

The ordinary diagnostic product uses the same behavior core plus **compact CORE diagnostics**. It replaces the release twin during controlled testing; never normally load both.

CORE is the default for broad regression/compatibility testing.

### DEEP / bounded causal diagnostics

DEEP retains opt-in reverse-engineering probes for a specific unresolved causal question. Dedicated temporary probe modules may also own a narrowly frozen causal intervention when observation alone cannot answer the question. Neither may be required for ordinary regression proof and neither may become a production prerequisite by accident.

`tools/Script_CombatMoveLogger` remains a separate general combat/speed research tool and must not become an owner of Animation Behaviors internal state.

---

## 2. Dependency / Hook Ownership

Correct direction:

```text
EngineBridge / behavior modules / source adapters / bounded probes
-> compact factual synchronous results
-> CollisionDiagnostics [diagnostic build only]
```

Each built DLL has one physical owner per Gothic hook: `EngineBridge`.

Established behavior hook surface includes the proven attack/collision/state/dispatch hooks already used by the collision core, including `StartEffect`, `SetCollisionGroup`, CombatMove/state/RunScriptFunction transport and the family callbacks required by supported marker adapters.

Production raw-8 Fist uses one important behavior-required transport:

```text
exact Game +0x16E180 GetPlayTime(motion 0) call-site hook
```

This is an exact call-site permission transport, **not** a global `GetPlayTime` hook and not a diagnostic-only probe. Behavior may substitute threshold+epsilon only for one matching armed comparison. Diagnostics may observe the decision but cannot own it.

`AIFullStop` remains diagnostic/deep for current behavior and is a proven explicit-this transport point that may later become behavior-required only if the evidence-backed `AttackContinuationProtection` design actually needs it.

Stage A moved raw8 feature state/policy into `Raw8FistCollision`; `EngineBridge` remains sole owner of the physical timing hook and delegates to that feature module.

Permanent PhysicalFist/raw55 behavior follows the same ownership rule: `EngineBridge` owns shared low-level hook transport, while `PhysicalFistCollision` owns raw55 eligibility/state/behavior policy. Historical `PhysicalFistProbe` work is archived provenance and does not define current hook policy.

---

## 3. CORE Diagnostic Contract

CORE should be sufficient for large tests while keeping healthy known paths compact.

### Build / lifetime

```text
build identity
diagnostic profile
clean startup / clean unload
```

### Attack identity

For any attack relevant to marker processing, preserve enough to establish:

```text
actor
factual numeric action
resolved supported family when known
phase / StatePosition where behaviorally relevant
exact current motion
C1 generation when available
```

Native action identity outranks filename heuristics.

### Marker/source result

CORE must establish:

```text
marker opcode
accepted/rejected/duplicate/budget/OFF outcome
rejection reason when rejected
factual resolved source identity / UseType
equipped side association where relevant
meaningful source-set change
activation/deactivation/rearm when physically performed
```

A healthy known execution should not require a repeated full ownership-decision dump unless needed to disambiguate the result.

### Physical transitions

Preserve meaningful transitions:

```text
exact source
RIGHT/LEFT association where meaningful
requested group
before / after group
offense including 7 -> 7 when behaviorally relevant
transition away from Item_Attack
exact marker-owned source-bit retirement where applicable
```

Routine `SetCollisionGroup` calls that produce no meaningful physical change should be compacted or suppressed when they carry no attack-source information. Do not suppress meaningful `7 -> 7` offense/rearm facts when they are part of the active causal question.

### C1 lifecycle

For healthy known paths CORE should prefer compact lifecycle outcome records rather than always logging the full transition chronology.

Must remain unambiguous:

```text
generation identity
exact outstanding obligation when one exists
cleanup fulfilled vs unresolved
finalization outcome
repair attempted/result
explicit invariant/failure signal
```

Detailed START -> BINDING -> STATUS -> FINALIZATION chronology moves to DEEP or appears only when needed for an anomaly/repair.

### Raw-8 FIST

Supported/proven raw8 FIST families currently include Normal + Power + Quick + Sprint for the tested scope.

For a healthy known FIST execution, CORE preserves the behavioral facts without repeating all research-era arithmetic/addresses every time:

```text
actor / action-family / generation
factual Fist/raw8 identity
initial marked-execution close succeeded when applicable
accepted FIST rearm succeeded
timing path classification, e.g. NATIVE_TIMING vs EARLY_PERMISSION
identity/ownership match
native damage correlation when required by the test
```

Full SPU addresses, animation-actor addresses, threshold arithmetic, exact real/max/returned play times, and repeated before/after snapshots are DEEP unless an anomaly or a new mechanism question requires them.

### PhysicalFist/raw55

Raw55 is no longer an unknown-source discovery problem. For the tested Troll/BlackTroll domain CORE/targeted diagnostics must be able to establish:

```text
actor / factual family / C1 generation
exact current RIGHT/LEFT TrollFist source
PhysicalFist/raw55 identity
before/requested/after collision group
marker occurrence and StatePosition
whether a marker-owned triggered-list clear was performed
native damage correlation when required
native exact 7 -> 5 cleanup
```

Repeated-contact research may additionally require current trigger bookkeeping (`EntitiesVisited`, `EntitiesVisitedCount`, player presence/count) and exact clear-call caller identity. Those are question-specific deep/probe facts, not permanent CORE noise.

### Damage correlation

When the test requires damage proof, CORE may correlate:

```text
target
source
attacker
caller module/RVA
action/family context
generation when available
```

For already-proven healthy routes, repeated full entity/contact-iterator address blocks are DEEP.

### C1-R1 outcomes

```text
NO_OP_NO_OUTSTANDING
UNRESOLVED_NOT_EQUIPPED
NO_OP_PHYSICALLY_CLEAN_RECONCILED
REPAIRED_TO_ITEM_EQUIPPED
REPAIR_DIVERGED_FROM_ITEM_EQUIPPED
```

A repair result is meaningful only with exact source ownership/liveness and before/requested/after groups.

---

## 4. Conditional CORE Verbosity

CORE automatically becomes richer when the event is not a routine healthy known path.

```text
KNOWN + SUCCESSFUL
-> compact

KNOWN + unexpected failure/rejection
-> detailed

UNSUPPORTED / UNKNOWN ACTION OR FAMILY
-> detailed

NEW / unexpected source UseType or source identity
-> detailed

C1 overlap / invariant issue
-> detailed

C1 repair / repair divergence
-> detailed

raw8 identity mismatch / stale timing permission / unexpected native route
-> detailed

raw55 unexpected source/family/contact/reset behavior
-> detailed

DEEP explicitly enabled
-> full requested research detail
```

This conditional rule is central to making larger tests manageable without losing discovery capability.

---

## 5. Unknown-Family / Source Discovery Contract

Sprint is no longer an unsupported-family example; raw8 Sprint production support is closed. The generic discovery contract remains necessary for any future unknown action/family/source.

For unsupported/unknown attack traffic retain at minimum:

```text
actor
C1 generation if available
numeric action
resolved action name when known
phase
StatePosition
current animation
marker opcode/name
source identity/name
source UseType
source collision group
equipped-side association if any
marker rejection reason
```

If native damage follows, correlate enough to establish:

```text
target
source
attacker
caller module/RVA
action context
generation when available
```

Do not hard-code the discovery contract around one previously unknown family.

---

## 6. Stage B Compaction Boundary

The completed Stage B diagnostic refactor established the current CORE-versus-DEEP boundary. Its original bounded contract is archived historical provenance; this document owns the current diagnostic rule.

The durable boundary is:

```text
routine healthy behavior -> compact CORE
unknown/unsupported/anomalous behavior -> richer CORE
historical exploratory snapshots/stacks -> DEEP
bounded causal interventions -> dedicated probe ownership
production correctness -> never depends on diagnostics
```

Do not reopen Stage B merely because a later research question temporarily needs richer data.

---

## 7. Deep Probes — Opt-In Only

Retain deep instrumentation for a concrete question, disabled by default:

```text
full raw8 latch/SPU/animation-actor identity
real/max/threshold/synthetic timing arithmetic
PlayMotion / StopMotion lifetime snapshots
replacement stacks
StartRecover begin/end + stacks
CombatMove FullStop stack/context
AIFullStop callsite/input-duration/context
broad AISetState callers/stacks
outer ScriptFunction/state-stack detail
full native cleanup caller/RVA/stack
OnTick marker lifetime tracking
full OnDamage caller/contact trace
raw55 trigger visited-list/readback/caller probes
full routine C1 dispatch chronology
```

Likely future uses:

```text
future unexpected source/family discovery
remaining PhysicalFist/raw55 repeated-contact causality
AttackContinuationProtection native timeout/consumer trace
new cleanup/source-lifetime contradiction
calling-convention/hook-order investigation
```

Deep capture must not become a production prerequisite.

---

## 8. Closed Sprint Diagnostic Questions

The earlier Sprint discovery questions are closed for the current proven raw8 scope. Evidence established factual Action9/Sprint semantic identity, transport through the existing Power callback path, raw8 source/mechanism support and production validation.

Retained limit:

```text
equipped Sprint RIGHT/LEFT/BOTH/OFF remains unsupported without factual evidence
```

If a future equipped Sprint source appears, reopen only that new source/mechanism question rather than the closed raw8 Sprint route.

---

## 9. PhysicalFist/raw55 Repeated-Contact Diagnostics

Raw55 factual source discovery and first-contact family classification are closed through EV-282. Current unresolved work is narrower: family-specific repeated-contact ownership.

Normal evidence through EV-290 establishes:

```text
frame-1/SP0 authored raw55 opening
marker-owned ClearTriggeredList enables early first contact
native exact 7 -> 7 setter is not second-contact owner
PC_Hero becomes visited after hit1
visited bookkeeping is reset during native SP0 -> 1 callback
exact reset operation = eCTrigger_PS::ClearTriggeredList() ALL
Engine RVA = +0x7DDA0
caller = Script_Game.dll +0x386C6
```

The current diagnostic-only causal probe suppresses only that exact post-hit1 native ALL clear when all factual Normal actor/C1/current-RIGHT/raw55/contact/caller gates match. Required observations include:

```text
suppression decision/fired state
PRE/POST player presence and visited/count alignment
SP0 -> 1 progression
marker2 remains observational
first damage survives or not
second damage survives or not
native exact 7 -> 5 cleanup
clean C1 finalization / any contradiction
```

Do not directly mutate visited arrays, add a replacement clear, write StatePosition, dispatch damage or alter native cleanup in the same test.

If the native clear is proven necessary, a later one-variable marker2 replacement-clear probe may be justified. If hit2 survives suppression, continue causal isolation instead of giving marker2 ownership.

---

## 10. AttackContinuationProtection Diagnostics

The future protection must be conditioned on the **factual native bad-skip timeout/consumer**, not on a continuously running plugin timer.

Diagnostics should be able to distinguish:

```text
native destructive condition never became due
native condition became due outside a genuine attack
native condition became due during a genuine attack and would destroy it
New Balance prevented the route before our intervention point
legitimate reaction/interrupt FullStop path
```

If New Balance prevents the relevant native condition, no protection intervention should be logged or performed.

---

## 11. Diagnostic Restraint

Remove/avoid routine historical noise once a question is canonically closed.

Default diagnostics should avoid broad per-call ScriptFunction dumps, continuous state-stack logging, full stacks for ordinary cleanup, per-frame/world polling, repeated large actor/source blocks, and repeated complete FIST timing dumps for already-proven healthy paths.

If CORE compaction makes a required behavior fact ambiguous, enable the smallest deep signal or bounded probe rather than inferring.

Unknown/unsupported events are an exception to aggressive compaction: enough detail must remain to classify them later.

For oversized logs, use POP-07 derived packages for retrieval instead of making routine orientation depend on reading multi-megabyte source logs.

---

## 12. RuntimeClock Is Behavior

The monotonic clock used by marker duplicate acceptance belongs in the behavior core, not diagnostics. Do not diagnostic-gate it unless a separate behavior change proves a replacement predicate.

---

## 13. Lifecycle / Marker Separation

Diagnostics must preserve the conceptual split:

```text
marker occurrence/exact-set bookkeeping
!=
physical source cleanup obligation
!=
contact/trigger visited-list bookkeeping
```

C1 generation is the shared factual execution identity; it does not collapse marker semantics, lifecycle repair and trigger-contact semantics into one state machine.

C1-R1 mutation remains two-phase/reentrancy-safe: classify/repair fixed sources first, then format diagnostics after mutation completes.

---

## 14. Current Diagnostic Sequence

```text
architecture + diagnostic-volume audit             DONE
Stage A behavior architecture refactor              DONE/PASS
Stage B diagnostic refactor + compact sentinel      DONE/PASS
raw8 Sprint discovery/production validation         DONE/PASS
native equipped-NPC / raw8 compatibility controls  DONE/PASS through later evidence
raw55 factual source + first-contact family routes  DONE/PASS through EV-282
raw55 cross-family two-FIST checkpoint              DONE — EV-283
Normal repeated-contact reset-source isolation      DONE through EV-290
-> local build/runtime of exact native ALL-clear suppression causal probe
-> close Normal native-clear necessity
-> if required, one-variable marker2 replacement-clear proof
-> Power repeated-FIST closure
-> Sprint repeated-FIST closure
-> permanent raw55 architecture
-> standalone collision regression
-> mature New Balance/Jackydima compatibility gate
-> AttackContinuationProtection later, separately
```

For each new causal question, use CORE if sufficient and enable only the smallest DEEP/probe surface needed for facts CORE cannot establish.

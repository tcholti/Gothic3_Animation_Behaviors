# Collision Lifecycle Diagnostic Architecture

**Status:** Current research-diagnostic authority  
**Updated:** 2026-09-08

## Purpose

Define the smallest observational instrumentation needed to validate collision behavior without turning diagnostics into behavior or contaminating the release DLL.

> The logger measures the architecture. It does not define it.

Release/build separation: `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.  
Behavior architecture: `DESIGN.md`.  
Lifecycle authority: `COLLISION_LIFECYCLE_PLAN.md`.  
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

### Diagnostic twin

The diagnostic product uses the same behavior core plus compact CORE diagnostics and opt-in deep probes. It replaces the release twin during controlled testing; never normally load both.

`tools/Script_CombatMoveLogger` remains a separate general combat/speed research tool and must not become an owner of Animation Behaviors internal state.

---

## 2. Dependency / Hook Ownership

Correct direction:

```text
EngineBridge / behavior modules / source adapters
-> compact factual synchronous results
-> CollisionDiagnostics [diagnostic build only]
```

Each built DLL has one physical owner per Gothic hook: `EngineBridge`.

Established behavior hook surface includes the proven attack/collision/state/dispatch hooks already used by the collision core, including `StartEffect`, `SetCollisionGroup`, CombatMove/state/RunScriptFunction transport and the family callbacks required by supported marker adapters.

Production human raw-8 Fist adds one important behavior-required transport:

```text
exact Game +0x16E180 GetPlayTime(motion 0) call-site hook
```

This is an exact call-site permission transport, **not** a global `GetPlayTime` hook and not a diagnostic-only probe. Behavior may substitute threshold+epsilon only for one matching armed comparison. Diagnostics may observe the decision but cannot own it.

`AIFullStop` remains diagnostic/deep for current behavior and is a proven explicit-this transport point that may later become behavior-required only if the evidence-backed `AttackContinuationProtection` design actually needs it.

---

## 3. CORE Diagnostic Contract

Ordinary controlled runs should be able to establish:

### Build / lifetime

```text
build identity
diagnostic profile
clean startup / clean unload
```

### Equipped marker ownership

```text
actor / exact current motion
action / phase
marker opcode
required/resolved equipped source set
native callback suppression decision where applicable
C1 generation
accepted/rejected/duplicate/budget/OFF result
source-set switch
activation/deactivation/rearm
StatePosition mutation where behaviorally used
```

### Equipped physical transitions

```text
exact source
RIGHT/LEFT slot association
requested group
before / after group
offense including 7 -> 7
transition away from Item_Attack
exact marker-owned source-bit retirement
```

### C1 lifecycle

```text
generation start
exact source obligation
cleanup fulfilled
finalization outcome
repair attempted/result
explicit invariant/failure signal
```

### Human Fist ownership/opportunity

CORE must preserve enough information to prove production Fist behavior without experiment-only noise:

```text
HUMAN_FIST_MARKER_OWNERSHIP
actor/SPU/C1 generation/animation identity
LatchOffset 0x164
LatchBefore / LatchAfter
WriteAttempted / WriteConfirmed

HUMAN_FIST_MARKER_OPPORTUNITY
LatchBefore / LatchAfter / LatchWriteConfirmed
TimingAvailable
RealPlayTime
NativeThreshold
RealBelowThreshold
TimingPermissionArmed
identity/ownership match
```

When causal verification requires damage entry, the diagnostic twin may correlate `gCEntity::OnDamage` caller module/RVA; current production evidence uses Game `+0x16E348` for the tested human path.

Do not restore N4/N5/N6 experiment chronology to normal logs.

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

## 4. Deep Probes — Opt-In Only

Retain deep instrumentation for a concrete question, disabled by default:

```text
PlayMotion / StopMotion lifetime snapshots
replacement stacks
StartRecover begin/end + stacks
CombatMove FullStop stack/context
AIFullStop callsite/input-duration/context
broad AISetState callers/stacks
outer ScriptFunction/state-stack detail
full native cleanup caller/RVA/stack
OnTick marker lifetime tracking
OnDamage caller trace when CORE cannot answer a new mechanism question
```

Likely future uses:

```text
PhysicalFist/raw55 mechanism discovery
AttackContinuationProtection native timeout/consumer trace
new cleanup/source-lifetime contradiction
calling-convention/hook-order investigation
```

Deep capture must not become a production prerequisite.

---

## 5. PhysicalFist/raw55 Discovery Diagnostics

The first raw55 stage is discovery, not implementation. Prefer existing CORE facts and add only the smallest missing deep signals required to classify:

```text
exact UseType/action/phase/current motion
TouchDamage/collision-group state where relevant
SPU+0x164 participation
whether Game+0x16E180 timing comparison participates
whether Game+0x16E1A3 native close participates
OnDamage caller/target context
```

Do not copy the human-Fist diagnostic state machine onto raw55 merely to make logs look symmetrical.

---

## 6. AttackContinuationProtection Diagnostics

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

## 7. Diagnostic Restraint

Remove/avoid routine historical noise once a question is canonically closed. Preserve reusable deep probes only when plausible future questions still need them.

Default diagnostics should avoid broad per-call ScriptFunction dumps, continuous state-stack logging, full stacks for ordinary cleanup, per-frame/world polling, and repeated large actor/source blocks.

If CORE compaction makes a required behavior fact ambiguous, the diagnostic contract is too weak; enable the smallest deep probe rather than inferring.

---

## 8. RuntimeClock Is Behavior

The monotonic clock used by marker duplicate acceptance belongs in the behavior core, not diagnostics. Do not diagnostic-gate it unless a separate behavior change proves a replacement predicate.

---

## 9. Lifecycle / Marker Separation

Diagnostics must preserve the conceptual split:

```text
marker occurrence/exact-set bookkeeping
!=
physical equipped-source cleanup obligation
```

C1 generation is the shared factual execution identity; it does not collapse marker semantics into lifecycle repair.

C1-R1 mutation remains two-phase/reentrancy-safe: classify/repair fixed sources first, then format diagnostics after mutation completes.

---

## 10. Current Diagnostic Sequence

There is no pending diagnostic regression merely to reconfirm EV-208–EV-215 or production human raw-8 Fist.

Future diagnostic work is driven by the technical roadmap:

```text
bounded PhysicalFist/raw55 discovery
-> any tractable extension validation
-> final native mixed regression
-> AttackContinuationProtection source/runtime investigation and validation
-> combined regression
-> mature compatibility gate
```

For each stage, use CORE if sufficient and enable deep diagnostics only for facts CORE cannot establish.

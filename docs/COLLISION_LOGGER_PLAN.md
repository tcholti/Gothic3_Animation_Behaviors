# Collision Lifecycle Diagnostic Architecture

**Status:** Current research-diagnostic authority  
**Updated:** 2026-09-09

## Purpose

Define the smallest observational instrumentation needed to validate collision behavior without turning diagnostics into behavior, contaminating the release DLL, or producing unnecessarily huge logs during large regression/compatibility tests.

> The logger measures the architecture. It does not define it.

> **Known successful behavior logs compactly. Unknown, unsupported, contradictory, repair, or invariant behavior logs richly.**

Release/build separation: `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.  
Behavior architecture: `DESIGN.md`.  
Current redesign authority: `COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`.  
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

This is a mechanical source/preprocess/compile/link separation, not a runtime setting.

### CORE diagnostic twin

The ordinary diagnostic product uses the same behavior core plus **compact CORE diagnostics**. It replaces the release twin during controlled testing; never normally load both.

CORE is the default for broad regression/compatibility testing.

### DEEP diagnostic profile

DEEP retains opt-in reverse-engineering probes for a specific unresolved causal question. It must not be required for ordinary regression proof and must never become a production prerequisite.

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

Production raw-8 Fist uses one important behavior-required transport:

```text
exact Game +0x16E180 GetPlayTime(motion 0) call-site hook
```

This is an exact call-site permission transport, **not** a global `GetPlayTime` hook and not a diagnostic-only probe. Behavior may substitute threshold+epsilon only for one matching armed comparison. Diagnostics may observe the decision but cannot own it.

`AIFullStop` remains diagnostic/deep for current behavior and is a proven explicit-this transport point that may later become behavior-required only if the evidence-backed `AttackContinuationProtection` design actually needs it.

The architecture audit may move raw8 feature state/policy out of `EngineBridge`, but `EngineBridge` remains sole owner of the physical timing hook and delegates to the owning feature module.

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

### Equipped physical transitions

Preserve meaningful transitions:

```text
exact source
RIGHT/LEFT slot association
requested group
before / after group
offense including 7 -> 7 when behaviorally relevant
transition away from Item_Attack
exact marker-owned source-bit retirement
```

Routine `SetCollisionGroup` calls that produce no meaningful physical change should be reviewed for compaction or DEEP-only detail unless they are needed to explain an anomaly.

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

Detailed START -> BINDING -> STATUS -> FINALIZATION chronology may move to DEEP except where an anomaly/repair requires it in CORE.

### Raw-8 FIST

Supported/proven raw8 FIST families currently include Normal + Power + Quick for the tested scope.

For a healthy known FIST execution, CORE should preserve the behavioral facts without repeating all research-era arithmetic/addresses every time:

```text
actor / action-family / generation
factual Fist/raw8 identity
initial marked-execution close succeeded when applicable
accepted FIST rearm succeeded
timing path classification, e.g. NATIVE_TIMING vs EARLY_PERMISSION
identity/ownership match
native damage correlation when required by the test
```

Full SPU addresses, animation-actor addresses, threshold arithmetic, exact real/max/returned play times, and repeated before/after snapshots are DEEP candidates unless an anomaly or a new mechanism question requires them.

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

For already-proven healthy routes, repeated full entity/contact-iterator address blocks should be compacted unless needed for ambiguity/anomaly resolution.

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

CORE should automatically become richer when the event is not a routine healthy known path.

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

DEEP explicitly enabled
-> full requested research detail
```

This conditional rule is central to making larger tests manageable without losing discovery capability.

---

## 5. Unknown-Family / Sprint Discovery Contract

The post-EV-249 Sabretooth test revealed factual `gEAction_SprintAttack = 9` traffic that the current framework does not support. Current observed Sprint source is `Fist/raw8`; other source types remain unknown.

Until Sprint is implemented, CORE must ensure unsupported Sprint cannot disappear into a generic rejection line.

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

This contract applies to future unknown families/source UseTypes as well, not only Sprint.

---

## 6. High-Value CORE Compaction Candidates

During the architecture/diagnostic audit, explicitly evaluate whether these current routine records can move to DEEP or become anomaly/condition-driven:

```text
FIST trigger-state snapshot before/after every native attack callback
FIST trigger-state snapshot before/after ordinary AISetState
SetCollisionGroup records where no meaningful physical state changed
full healthy C1 START -> BINDING -> STATUS -> FINALIZATION chronology
full entity addresses/contact iterator data for every known successful damage
complete ownership-decision dump for every known successful attack
complete raw8 timing arithmetic for every already-proven early FIST
```

Do **not** simply delete reusable capability. Prefer:

```text
CORE compact summary
+ anomaly-triggered detail
+ DEEP retained research probe
```

The exact literal compact log syntax is not frozen yet; the information contract is.

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
hook-entry identity probes
```

Likely future uses:

```text
SprintAttack callback/native mechanism classification
future unexpected source/family discovery
PhysicalFist/raw55 mechanism discovery if factual raw55 appears
AttackContinuationProtection native timeout/consumer trace
new cleanup/source-lifetime contradiction
calling-convention/hook-order investigation
```

Deep capture must not become a production prerequisite.

---

## 8. SprintAttack Diagnostic Questions

After the architecture refactor and compact equivalence sentinel, use CORE first and add only the smallest missing DEEP signal needed to establish:

```text
which actors execute gEAction_SprintAttack
which factual source UseTypes occur
what callback/hook transport owns Sprint
what StatePosition Sprint uses
whether equipped Sprint exists
whether raw8 Sprint traverses the same SPU+0x164 / +0x16E180 / +0x16E1A3 / +0x16E348 mechanism
whether any equipped Sprint uses the established equipped physical source path
```

Do not copy the raw8 FIST diagnostic state machine onto another source type merely for symmetry.

---

## 9. PhysicalFist/raw55 Discovery Diagnostics

Raw55 remains unobserved/deferred. No new raw55 instrumentation is justified unless factual `UseType == 55` appears.

If reopened, prefer existing CORE facts and add only the smallest missing deep signals required to classify:

```text
exact UseType/action/phase/current motion
TouchDamage/collision-group state where relevant
SPU+0x164 participation
whether Game+0x16E180 timing comparison participates
whether Game+0x16E1A3 native close participates
OnDamage caller/target context
```

Do not copy raw8 FIST behavior/diagnostics onto raw55 merely to make logs look symmetrical.

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

If CORE compaction makes a required behavior fact ambiguous, the diagnostic contract is too weak; enable the smallest deep probe rather than inferring.

Unknown/unsupported events are an exception to aggressive compaction: enough detail must remain to classify them later.

---

## 12. RuntimeClock Is Behavior

The monotonic clock used by marker duplicate acceptance belongs in the behavior core, not diagnostics. Do not diagnostic-gate it unless a separate behavior change proves a replacement predicate.

---

## 13. Lifecycle / Marker Separation

Diagnostics must preserve the conceptual split:

```text
marker occurrence/exact-set bookkeeping
!=
physical equipped-source cleanup obligation
```

C1 generation is the shared factual execution identity; it does not collapse marker semantics into lifecycle repair.

C1-R1 mutation remains two-phase/reentrancy-safe: classify/repair fixed sources first, then format diagnostics after mutation completes.

---

## 14. Current Diagnostic Sequence

There is no pending diagnostic regression merely to reconfirm EV-208–EV-215 or raw8 Normal/Power/Quick behavior.

Next:

```text
complete architecture + diagnostic-volume audit
-> freeze compact CORE / retained DEEP refactor
-> bounded Work implementation
-> compact post-refactor equivalence sentinel
-> SprintAttack mechanism investigation
-> focused Sprint validation if implemented
-> broad native/modded compatibility matrix using compact CORE
-> final native mixed/stress regression
-> AttackContinuationProtection source/runtime investigation
-> combined regression
-> mature compatibility gate
```

For each new causal question, use CORE if sufficient and enable DEEP only for facts CORE cannot establish.

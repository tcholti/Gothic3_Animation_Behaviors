# Second-Pass Collision Architecture Rewrite Contract

**Status:** IMPLEMENTED + VALIDATED REFERENCE CONTRACT — rewrite closed through EV-208–EV-212; later Gate-4 verification closed through EV-213–EV-215  
**Updated:** 2026-09-01  
**Scope:** `prototypes/Script_FrameCollisionTest/` only, plus its CMake/build-product separation  
**Release rule:** `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`

## 1. Purpose

Preserve the exact semantic-preserving rewrite contract that followed the completed first per-CPP review and second-pass architecture synthesis.

This rewrite removed rejected historical baggage, separated responsibilities cleanly, reduced permanent research-hook/diagnostic coupling, and mechanically proved that the behavior core can compile without diagnostics.

It did **not** add a new attack family, change collision semantics, redesign C1, implement bad-skip prevention, migrate production Raise/speed, or begin final `Script_G3AnimationBehaviors` integration.

The rewrite was implemented at:

```text
4eeb701725e8b77d8850116d408155653ff4ad36
```

Its source/build and product-validation gates are closed through EV-208–EV-212. The separate later marker-bookkeeping simplification was then completed by Gate 4 / EV-213, directly regressed against the historical EV-131 fixture in EV-214, and the final behavior-only architecture smoke passed in EV-215.

Historical preconditions and validation steps remain below as provenance. They are **not current executable next steps**. Current validation posture is owned by `COLLISION_TEST_PLAN.md`; current project responsibility is owned by `SESSION_ENTRYPOINT.md` / `BETWEEN_CHATS.md`.

---

## 2. Non-Negotiable Behavior Invariants

Preserve all currently proven behavior exactly.

### C1 lifecycle / repair

```text
real attack execution
→ monotonic C1 generation
→ successful exact-source Item_Attack request creates/refreshes obligation
→ successful later transition away from Item_Attack fulfills obligation
→ destructive post-native-AISetState finalization checks only remaining obligations
```

Terminal repair remains exactly:

```text
exact outstanding source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList()
→ verify exact resulting group Item_Equipped(5)
```

Native cleanup always gets first opportunity.

Preserve the proven P2 temporary pre-Combat ScriptFunction correlator:

```text
exact SPU
+ exact runtime/state stack
+ live ScriptFunction frame
+ non-null m_pArguments
+ same ScriptFunction name
```

The monotonic C1 generation remains durable execution identity.

### Marker behavior

Preserve:

```text
exact current-motion ownership
Normal / Quick / full-Whirl currently supported family predicates
RIGHT / LEFT / BOTH / OFF exact-set semantics
authored occurrence budgets
same-update duplicate/replay suppression
repeated-contact ClearTriggeredList rearm
Quick/full-Whirl StatePosition suppression
marker-owned source/window state
natural SetCollisionGroup retirement of marker-owned sources
explicit OFF as intra-Hit authored inactive gap
late/dead-execution rejection
current research Fist behavior without generalizing it
unmarked/unsupported native fallback
```

Historical rewrite-scope constraint: this second-pass rewrite itself did **not** replace marker execution bookkeeping with C1. EV-131–EV-133 and EV-167 were the regression authority that required a later dedicated audit rather than an opportunistic deletion during structural rewrite.

That later audit is now complete. Gate 4 / EV-213 established the monotonic C1 generation as durable marker occurrence/dedupe execution identity and removed the older marker-local source/motion/action/phase/state-time and controlled-callback rollback guesses about a new execution. Independent marker invariants listed above remain preserved. Current authority: `MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md`.

### Hook transport / ordering

Preserve proven hook targets, calling conventions, recursion safety and original-call order.

Explicit `.ThisCall()` remains on the behavior-critical paths already proven with it:

```text
RunScriptFunction
AISetState
SetCollisionGroup
```

`AIFullStop` remains explicit-this if present in the diagnostic/deep build; it is not behavior-required for the current collision system.

Preserve ordering:

```text
RunScriptFunction:
  publish stack-local scope across original
  → original exactly once
  → restore parent scope
  → retire P2 temporary bridge / emit diagnostic result if compiled

AICombatMoveInstr:
  BeginCombatMove
  → original exactly once
  → CompleteCombatMoveCandidate

AISetState:
  CaptureFinalizationToken
  → original native AISetState exactly once
  → FinalizeAfterAISetState
  → diagnostics only after/around factual behavior without changing ordering

SetCollisionGroup:
  capture factual before/context
  → original setter exactly once
  → retire marker-owned source if resulting group is not Item_Attack
  → C1 observes resulting transition
  → diagnostics observe result if compiled
```

C1-R1 repair must continue to re-enter the same ordinary SetCollisionGroup bridge path.

---

## 3. Target Behavior-Core Modules

After the rewrite, the behavior architecture is:

```text
Script_FrameCollisionTest / later Script_G3AnimationBehaviors
│
├─ EngineBridge
│    sole physical owner of behavior-required Gothic hooks
│    calling-convention-safe transport
│    no marker/source/lifecycle feature policy
│
├─ FrameCollisionMarkers
│    exact current-motion marker ownership
│    attack-family eligibility / custom callback ownership decision
│    RIGHT / LEFT / BOTH / OFF authored semantics
│    occurrence/replay/duplicate bookkeeping
│    StatePosition native-activation suppression
│    marker-owned source/window bookkeeping
│
├─ CollisionSources
│    factual current RIGHT/LEFT equipped source resolution
│    source UseType facts
│    required-source availability queries
│
├─ CollisionSourceOperations
│    source-specific physical operations requested by marker behavior
│    current equipped-weapon Item_Attack / Item_Equipped operations
│    repeated-contact ClearTriggeredList rearm
│    preserve current research Fist group-skip/rearm behavior
│    no attack-family or marker-ownership policy
│
├─ CollisionLifecycleGuard
│    C1 monotonic generation
│    P2 temporary pre-Combat correlator
│    exact per-source offense/cleanup obligations
│    post-native-AISetState exact terminal repair
│    no diagnostic formatting/output dependency
│
└─ RuntimeClock
     behavior-required monotonic elapsed-time service
     currently required by same-update duplicate-marker suppression
```

Diagnostics are not part of this behavior-core dependency chain.

---

## 4. File-Level Rewrite Contract

### 4.1 `HookBridgeRuntime.h/.cpp` → `RuntimeClock.h/.cpp`

Rename the module because the second pass established that elapsed time is part of actual marker duplicate acceptance behavior, not merely research diagnostics.

Keep logic unchanged unless a compile contradiction requires a mechanical adjustment:

```text
InitializeClock()
GetElapsedMilliseconds()
```

Initialize before hook installation in both behavior-only and diagnostic builds.

Do not redesign the 5 ms duplicate predicate in this rewrite.

### 4.2 `CollisionControl.h/.cpp` → `FrameCollisionMarkers.h/.cpp`

Rename only after the generic physical operations are extracted.

This module owns marker policy and bookkeeping, not generic source facts or diagnostic formatting.

Move the current EngineBridge marker callback suppression policy into this module behind one clear factual API. The exact function name may be chosen during implementation, but its contract is frozen:

```text
input:
  actor
  attack family / callback family

marker module:
  verifies current family/action/Hit eligibility
  obtains exact current-motion marker decision
  resolves required current equipped sources through CollisionSources
  performs existing controlled-callback bookkeeping

output:
  whether custom marker ownership suppresses the native callback
  compact factual observation/result needed by diagnostics
```

EngineBridge must not independently combine marker presence + required source masks into feature policy after this move.

Preserve all existing authored-marker semantics.

### 4.3 Marker-cache correction

Fix the current permanent negative-cache hazard.

Current unsafe behavior:

```text
animation name X
→ transient scan cannot resolve exact current motion
→ foundMatchingMotion=false cached permanently for X
→ later valid motion never rescanned
```

Required rule:

```text
cache a marker decision only after:
  exact current motion descriptor was resolved
  AND frame-effect layout/scan was valid enough to establish a factual marker/no-marker result
```

A transient unresolved motion or invalid/unreadable scan must not create a permanent negative cache entry.

Do not alter marker vocabulary, marker counts, frames, required-source semantics or positive cache meaning.

### 4.4 New `CollisionSourceOperations.h/.cpp`

Extract source-specific physical marker operations from `FrameCollisionMarkers`.

The operation layer receives an already-decided physical source and requested marker behavior. It does not decide attack family, marker ownership or desired source set.

Preserve current operations exactly:

For ordinary equipped weapon sources:

```text
activate/rearm:
  SetCollisionGroup(Item_Attack)
  ClearTriggeredList()

deactivate:
  SetCollisionGroup(Item_Equipped)
  no ClearTriggeredList()
```

For current research Fist/PhysicalFist handling:

```text
activate/rearm:
  do not force weapon Item_Attack group mutation
  preserve existing ClearTriggeredList behavior
```

Do not declare generalized Fist support or invent monster/body adapters.

All SetCollisionGroup calls continue through the normal engine function so EngineBridge/C1/marker retirement observe the resulting transition.

### 4.5 `CollisionSources.h/.cpp`

Keep as factual source-query module.

No new marker/lifecycle policy.

Remove the temporary re-export aliases from the marker header:

```text
GetEquippedCollisionSources
GetCollisionSourceUseType
HasRequiredCollisionSources
```

Consumers that genuinely need these facts call `CollisionSources` directly.

### 4.6 `CollisionLifecycleGuard.h/.cpp`

Remove the rejected dormant eager dispatch machinery completely:

```text
ScriptFunctionDispatchToken
BeginScriptFunctionDispatch
EndScriptFunctionDispatch
g_ScriptFunctionDispatchStack
InvalidateScriptFunctionDispatchAfterAISetState
EngineBridge's now-no-op InvalidateScriptFunctionDispatchAfterAISetState call
unused <vector> dependency once no longer required
```

Do **not** remove or conflate the live P2 correlator machinery:

```text
ScriptFunctionDispatchContext
CaptureTopScriptFunction
CaptureCurrentTopScriptFunction
HasLiveCorrelator
OuterFrameBinding
MatchesBinding / BindOuterFrame
PreCombatDispatchView
PreCombatBridgeToken
ResolvePreCombatOffenseOwner
matching CombatMove consumption
RetirePreCombatBridgeAfterDispatch
```

Remove all direct `CollisionDiagnostics`, `FILE*`, `fprintf`, player-only log gating and logger-formatting responsibility from the lifecycle guard.

The guard must remain completely correct when diagnostics are not compiled.

Replace embedded log emission with compact factual return/result structures or explicit observation records returned synchronously from the existing operations. Keep this simple and local; do not introduce a generic event bus, observer registry, callback framework or asynchronous queue.

The fixed two-source finalizer remains two-phase and reentrancy-safe:

```text
1. classify / repair all max-two sources into stack-local factual results
2. only after mutation/classification is complete may the diagnostic build format those results
```

No half-written diagnostic block may be open across a repair setter call.

### 4.7 `FrameCollisionShared.h`

Keep only behavior-shared types that are legitimate without diagnostics.

Move diagnostic-only types such as PrimaryFirst motion-lifetime snapshots out of the shared behavior header.

Marker/lifecycle factual result structures may remain shared only when they describe actual behavior outcomes rather than logger presentation.

Do not turn `FrameCollisionShared.h` into a generic dumping ground.

### 4.8 `EngineBridge.h/.cpp`

Remain sole physical hook owner inside each built DLL.

Behavior-required hook set for the current collision system:

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

These remain in the behavior-only build.

Current diagnostic-only hook candidates:

```text
PlayMotion
StopMotion
AICombatMoveStartRecover
OnTick
AIFullStop
```

They must not be installed or compiled into the behavior-only build merely because the old research DLL always installed them.

`AIFullStop` remains a preserved proven transport point for possible future `AttackContinuationProtection`, but it is not behavior-required by current collision responsibilities.

EngineBridge may contain small compile-time-guarded calls that hand already-produced factual results to diagnostic code in the diagnostic target. It must not require diagnostic code for behavior correctness.

Do not introduce duplicate hook owners or a generic event bus.

### 4.9 `CollisionDiagnostics.h/.cpp`

Retain only compact default diagnostic evidence for the diagnostic product.

Core diagnostic evidence must remain sufficient to prove:

```text
build/profile identity + clean unload
exact marker ownership/current motion/action/phase/opcode
required/resolved source set
native callback suppression decision
marker result: accepted/rejected/duplicate/budget/OFF
exact source-set activation/deactivation/rearm
StatePosition mutation where behaviorally used
exact SetCollisionGroup source/slot/requested/before/after
successful offense including 7 -> 7
successful transition away from Item_Attack
marker-source retirement
C1 generation/start
C1 exact-source offense obligation
C1 cleanup fulfillment
C1 finalization/repair result
PRECOMBAT_ACQUIRED
PRECOMBAT_BRIDGE_CONSUMED
relevant dispatch return when early offense occurred
explicit binding/generation/liveness/repair/marker invariant failure
C1-R1 outcome distinctions
```

Remove stale experiment chronology and repetitive historical proof fields from the normal diagnostic output.

### 4.10 New `CollisionDiagnosticsDeep.h/.cpp`

Move retained historical/deep investigation capability here, including as applicable:

```text
PrimaryFirst PlayMotion / StopMotion snapshots
hit replacement stacks
empty-primary successor stacks
StopMotion hit stacks
AICombatMoveStartRecover begin/end stacks
CombatMove FullStop stack/context
AIFullStop caller/input-duration/primary-motion/stack
AISetState caller/state/primary-motion/stack
outer ScriptFunction/state-stack snapshots
P1 detailed pointer/SPU/runtime-stack snapshots
full native cleanup caller module/RVA + stack
OnTick marker-owned PrimaryFirst lifetime tracking
```

Deep diagnostics remain disabled by default in ordinary diagnostic runs.

They may be enabled by a diagnostic-only compile/profile mechanism. Do not add a user-facing production INI responsibility in this rewrite.

Diagnostic-only hooks are installed only when the selected diagnostic build/profile actually requires them.

### 4.11 `Script_FrameCollisionTest.cpp`

Remain a composition root.

Behavior-only composition:

```text
RuntimeClock::InitializeClock()
EngineBridge::InstallHooks()
```

Diagnostic composition additionally opens/closes diagnostics and identifies the diagnostic profile.

No collision/marker/lifecycle decision logic belongs here.

### 4.12 `CMakeLists.txt`

Create a mechanical diagnostics-free build check now.

Required product classes:

```text
BEHAVIOR-ONLY prototype target
  behavior-core sources only
  no CollisionDiagnostics source files
  no deep diagnostic source files
  no diagnostic-only hooks compiled/installed

DIAGNOSTIC prototype target
  same behavior core
  + compact CollisionDiagnostics
  + retained deep diagnostics capability
```

Keep existing `Script_FrameCollisionTest` as the diagnostic research target unless a build-system contradiction requires otherwise.

Add a clearly named behavior-only prototype target, provisionally:

```text
Script_FrameCollisionBehaviorTest
```

The two products are mutually exclusive at runtime. Never deploy both into Gothic 3's live `scripts` directory together.

A compile-time diagnostic definition is allowed to remove diagnostic call sites from the behavior-only binary. A runtime switch that leaves research diagnostics compiled into a future public release is forbidden by `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

The final public `Script_G3AnimationBehaviors` target is **not** created or migrated in this rewrite.

---

## 5. Explicit Non-Goals

Do not combine this rewrite with:

```text
C1-driven marker bookkeeping simplification
Power / Pierce / SimpleWhirl marker expansion
new marker vocabulary
new Fist semantics or generalized Fist support
monster/body collision adapters
AttackContinuationProtection
Raise changes
speed changes
configuration redesign
New Balance / Jackydima compatibility fixes
final production DLL migration
target acquisition
climbing
unrelated hook transport rewrites
new cleanup/finalization predicates
new timers/polling/world scans
```

These are the historical scope boundaries of the second-pass rewrite. Gate 4 later completed the first item as a separate responsibility; the remaining items are still separate unless another current authority explicitly changes them.

Do not change current marker frames, occurrence budgets, replay rules, source masks, action eligibility or collision timings merely because this completed structural contract is being referenced.

---

## 6. Historical Stop Conditions During Implementation

During the original rewrite, implementation was required to stop and return to Normal Chat rather than improvise if it discovered a concrete contradiction in:

```text
calling convention / hook macro linkage
required original-call ordering
C1 P2 correlator lifetime
SetCollisionGroup re-entry/finalizer semantics
source liveness requirements
marker-cache factual-validity test
current Fist source operation semantics
CMake/toolchain ability to produce a diagnostics-free behavior target from the shared behavior core
```

A source/API contradiction could narrow or change the frozen architecture. It did not authorize opportunistic redesign.

This section is retained as implementation provenance, not as a current gate.

---

## 7. Validation Sequence — Historical and Closed

### Gate 0 — unchanged post-EngineBridge baseline

Historical precondition before source rewrite:

```text
current source unchanged
current existing logger unchanged
build Script_FrameCollisionTest
run compact runtime sentinels
preserve raw log
```

This baseline passed before the rewrite proceeded.

### Gate 1 — source/build audit after rewrite — CLOSED/PASS

Evidence: EV-208.

Historical requirements:

```text
git diff --check
bounded source diff audit against this contract
build Script_FrameCollisionTest diagnostic target
build Script_FrameCollisionBehaviorTest behavior-only target
verify behavior-only target does not compile/link CollisionDiagnostics or deep diagnostic sources
```

### Gate 2 — compact diagnostic sufficiency regression — CLOSED/PASS

Evidence: EV-209–EV-211.

Validated sentinels:

```text
known positive stale-source repair
ordinary native cleanup no-op
legitimate reaction cleanup no-op
Dual source independence
one marked-source regression
Fist/unarmed negative
crossbow negative
clean shutdown
```

### Gate 3 — behavior-only smoke/equivalence — CLOSED/PASS

Evidence: EV-212.

The behavior-only prototype was deployed instead of the diagnostic twin and passed the required smoke/equivalence boundary.

### Gate 4 — separate marker simplification — CLOSED/PASS

Evidence: EV-213, with literal historical regression closure EV-214 and final diagnostics-free architecture smoke EV-215.

Current accepted result:

```text
C1 monotonic generation
= durable marker occurrence/dedupe execution identity
```

Do not execute Gates 0–4 again as pending work absent a concrete contradiction or a later responsibility that intentionally changes the relevant architecture.

---

## 8. Production Direction Preserved

The mature research behavior core remains the architectural ancestor of the final `Script_G3AnimationBehaviors` DLL.

Do not pour this architecture back into the old v0.1 production hook/file layout.

Later, after marker/source/continuation maturity and the first New Balance/Jackydima compatibility gate:

```text
retain mature behavior core / central EngineBridge
→ migrate/redesign Raise + speed + config into it
→ later add independent systems such as target acquisition and climbing
→ build final public diagnostics-free Script_G3AnimationBehaviors
→ retain separate instrumented diagnostic twin for controlled reproduction
```

The public release contains behavior only. Diagnostics are never a production dependency.

# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — first per-CPP architecture review CLOSED; second-pass synthesis NEXT

C1-R1 controlled validation remains closed. Canonical result: **EV-206–EV-207**.

Validated C1-R1 behavior remains unchanged:

```text
exact outstanding source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList()
→ verify exact resulting group Item_Equipped(5)
```

Two qualifications remain explicit but do not reopen C1-R1:

```text
1. No positive runtime exercise of an outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED branch.
2. No positive NPC destructive-abandonment / C1 physical-repair case is claimed.
```

---

## Structural modularization already closed

### CollisionSources extraction

Implementation:

```text
43fa1e719b5af716c54e17430c101251bbc36ff8
```

Created `CollisionSources.h/.cpp`; moved unchanged:

```text
GetEquippedCollisionSources(...)
GetCollisionSourceUseType(...)
HasRequiredCollisionSources(...)
```

Validation:

```text
source/diff audit = PASS
local CMake Release build Script_FrameCollisionTest = PASS
```

### EngineBridge extraction

Frozen base:

```text
d0132b69df3add63641bc5d5fd5779f1037eaa99
```

Implementation head before documentation-only review commits:

```text
32ff447c9a678ba18c8234310564ff2475ba7dfb
```

Created `EngineBridge.h/.cpp`. `EngineBridge.cpp` owns all Gothic hooks/callback wrappers, RunScriptFunction TLS transport state and hook installation. `Script_FrameCollisionTest.cpp` is now DLL composition/init only.

Preserved proven transport/order:

```text
RunScriptFunction: scope live across original → restore → bridge retirement/logging
AICombatMoveInstr: BeginCombatMove → original → CompleteCombatMoveCandidate
AISetState: capture → native original → finalize after native cleanup opportunity
SetCollisionGroup: original setter → marker retirement → C1 observation → diagnostics
```

Explicit `.ThisCall()` remains on:

```text
RunScriptFunction
AISetState
AIFullStop
SetCollisionGroup
```

Validation:

```text
bounded source/diff audit = PASS
local CMake Release build Script_FrameCollisionTest = PASS
```

No post-EngineBridge runtime collision baseline has been run yet.

---

## Production migration direction

The mature modular research DLL is the likely architectural foundation of the eventual production `Script_G3AnimationBehaviors` DLL.

Do **not** plan to pour the mature collision system back into the old v0.1 source/hook structure. After the mature research collision system passes its compatibility gate, retain the modular foundation/central hook ownership and migrate or redesign Raise, speed, config and final DLL identity into it.

The final binary may still be named `Script_G3AnimationBehaviors`; implementation lineage does not require preserving the old v0.1 layout.

Infrastructure names such as `HookBridgeRuntime` remain provisional until final production responsibilities are known.

---

## First per-CPP review — CLOSED

All implementation files in `prototypes/Script_FrameCollisionTest/` now have a first-pass disposition.

```text
1. Script_FrameCollisionTest.cpp
   ACCEPTED AS-IS.
   Composition/init root only.

2. EngineBridge.cpp
   ACCEPTED for current research architecture.
   Second-pass items:
   - move marker-specific ownership/suppression policy into marker module;
   - reduce diagnostic-only permanent hook surface;
   - keep behavior-critical hook ordering/calling conventions unchanged.

3. CollisionSources.cpp
   ACCEPTED AS-IS.
   Generic source facts only; no feature policy/state/hook ownership.

4. HookBridgeRuntime.cpp
   ACCEPTED AS-IS.
   Currently high-resolution process-relative clock only; do not rename until final responsibility is known.

5. CollisionLifecycleGuard.cpp
   CORE C1/P2/R1 BEHAVIOR ACCEPTED.
   Second-pass correction:
   - remove dormant rejected eager ScriptFunction dispatch stack/API:
     ScriptFunctionDispatchToken,
     BeginScriptFunctionDispatch / EndScriptFunctionDispatch,
     g_ScriptFunctionDispatchStack,
     InvalidateScriptFunctionDispatchAfterAISetState + now-no-op EngineBridge call,
     unused <vector> afterward.
   Preserve the live P2 correlator machinery despite similar naming:
   ScriptFunctionDispatchContext,
   CaptureTopScriptFunction,
   CaptureCurrentTopScriptFunction,
   HasLiveCorrelator,
   OuterFrameBinding,
   exact pre-Combat bridge.
   Second-pass architecture item:
   - move lifecycle log formatting/emission out of behavior ownership while preserving two-phase reentrancy-safe finalization.

6. CollisionControl.cpp
   CORE MARKER BEHAVIOR ACCEPTED; current final boundary NOT accepted as production architecture.
   Preserve:
   - exact current-motion ownership;
   - RIGHT/LEFT/BOTH/OFF exact-set semantics;
   - authored occurrence/replay protection;
   - repeated-contact ClearTriggeredList rearm;
   - Quick/full-Whirl StatePosition suppression;
   - marker-owned source/window retirement through normal SetCollisionGroup path;
   - current Fist research behavior without generalizing it.
   Second-pass items:
   - fix/investigate permanent negative marker-cache hazard: current animation-name cache stores unresolved `foundMatchingMotion=false` results;
   - classify old execution-lifetime inference against C1 authority check-by-check;
   - move marker callback-ownership policy out of EngineBridge;
   - decide equipped-weapon physical-source operation adapter boundary;
   - remove temporary CollisionControl→CollisionSources diagnostic aliases;
   - reassess final `FrameCollisionMarkers` responsibility/name only after boundaries are resolved.

7. CollisionDiagnostics.cpp
   CORE OBSERVABILITY ACCEPTED; CURRENT DEFAULT LOGGER/HOOK SURFACE REQUIRES SECOND-PASS REDESIGN.
```

---

## CollisionDiagnostics first-pass classification

Authority: `docs/COLLISION_LOGGER_PLAN.md`.

### CORE COLLISION EVIDENCE — keep in default profile

Keep compact evidence sufficient to prove:

```text
startup/build/profile identity + clean unload
exact marker actor/current motion/action/phase/opcode
required/resolved RIGHT/LEFT/BOTH source set
native callback suppression ownership
marker accepted/rejected/duplicate/budget/OFF outcome
exact source-set switch / activation / deactivation / rearm
StatePosition mutation where used for native suppression
exact SetCollisionGroup source + relevant slot identity + requested/before/after
successful offense including 7 -> 7
successful cleanup transition away from Item_Attack
marker-owned source retirement through SetCollisionGroup
C1 lifecycle/generation start
C1 exact source offense request
C1 cleanup fulfilled
C1 finalization outcome
C1 repair attempted/result
PRECOMBAT_ACQUIRED
PRECOMBAT_BRIDGE_CONSUMED
relevant dispatch return after early offense
explicit marker/binding/generation/liveness/repair invariant failures
R1 outcomes:
  NO_OP_NO_OUTSTANDING
  UNRESOLVED_NOT_EQUIPPED
  NO_OP_PHYSICALLY_CLEAN_RECONCILED
  REPAIRED_TO_ITEM_EQUIPPED
  REPAIR_DIVERGED_FROM_ITEM_EQUIPPED
```

Current `LogOwnershipDecision`, marker context/result and compact `LogSetCollisionGroup` contain useful core facts, but should be compressed rather than removed.

`CollisionLifecycleGuard` currently formats/writes C1 logs directly. Second pass should move logging responsibility behind `CollisionDiagnostics` without moving lifecycle decisions out of the guard and without creating a generic event-bus abstraction.

### OPT-IN DEEP PROBES — retain but disable by default

```text
PrimaryFirst PlayMotion / StopMotion before/after snapshots
hit replacement stacks
empty-primary successor stacks
StopMotion hit stacks
AICombatMoveStartRecover begin/end + stacks
CombatMove FullStop stack/context
AIFullStop caller/input-duration/primary-motion/stack context
AISetState caller/state/primary-motion/stack context
outer ScriptFunction/state-stack snapshots
P1 detailed offense-scope pointer/SPU/runtime-stack snapshots
full native cleanup caller module/RVA + stack for every exact 7 -> 5
OnTick marker-owned PrimaryFirst lifetime tracking
```

These remain useful for a concrete future contradiction, `AttackContinuationProtection`, new cleanup/source-lifetime questions or hook-order investigation, but should not burden ordinary collision runs.

Where a hook exists solely for one of these probes, second pass must decide whether the hook itself is installed only in deep mode.

Current diagnostic-only hook candidates:

```text
PlayMotion
StopMotion
AICombatMoveStartRecover
OnTick
AIFullStop  [diagnostic-only today; may become behavior-relevant later for AttackContinuationProtection]
```

Behavior-critical hooks such as SetCollisionGroup, AISetState, RunScriptFunction, CombatMove, StartEffect and attack-family callbacks remain installed regardless of logger profile.

### OBSOLETE HISTORICAL NOISE — remove from normal implementation/output

The current startup banner contains large experiment chronology and stale statements, including historical B1–B9/O1/P1 banners and the now-false `C1 SHADOW ... WOULD_REPAIR only; no physical repair` statement. Replace with compact current build/profile/feature identity.

Also remove or collapse repetitive proof-era fields whose durable conclusion is already canonical evidence and that do not answer a current runtime question, e.g. repeated:

```text
CleanupBehaviorChanged: 0
LifecycleBehaviorChanged: 0
CollisionBehaviorChanged: 0
TopEntryAddressIsExecutionIdentity: 0
ArgumentsDereferencedOrClassified: 0
TLSRestoredBeforeLog: 1
ScopePersistedAfterReturn: 0
constant Item_Attack/Item_Equipped value labels on every event
large repeated player action/pose/state/source blocks when a compact exact-source transition already answers the question
```

Do not delete a useful deep probe merely because it is verbose; gate it instead.

### Diagnostic dependency cleanup

Second pass should remove the temporary source-query aliases in `CollisionControl.h`. Diagnostics should consume direct `CollisionSources` facts or, preferably, factual result structures already produced by behavior modules rather than re-querying behavior ownership through aliases.

Diagnostic state (`g_LastLoggedAni`, `g_LifetimeStateByActor`) must remain observation-only. `g_LifetimeStateByActor` belongs to deep mode; disabling/removing deep diagnostics must not change marker/lifecycle behavior.

---

## Mandatory second-pass architecture/correction synthesis — NEXT

The User explicitly requested a second review so unnecessary baggage is resolved while the complete architecture is still fresh rather than being carried across more chat boundaries.

This second pass remains **read-only for source** until one coherent rewrite contract is frozen.

Required synthesis questions:

```text
A. EngineBridge
- exact factual bridge API vs marker-policy leakage
- default vs deep diagnostic hook installation

B. CollisionLifecycleGuard
- remove rejected dormant dispatch machinery
- define clean diagnostics emission boundary without changing C1 ownership/finalization

C. CollisionControl / future FrameCollisionMarkers
- resolve marker-cache negative-caching hazard
- C1-vs-marker execution lifetime responsibilities
- callback suppression ownership API
- physical-source adapter boundary
- temporary alias removal

D. CollisionDiagnostics
- compact Core vs opt-in Deep profile
- move expensive capture behind profile checks
- reduce default log volume while preserving diagnostic sufficiency contract
- centralize C1 formatting without changing behavior

E. Production foundation
- decide whether any file/module names should change now or remain provisional
- preserve this mature modular foundation as the eventual Script_G3AnimationBehaviors base
```

If the frozen rewrite is broad, Normal Chat owns the architecture and should write the exact implementation contract into this file; Work/High may then perform the bounded rewrite but must not redesign it independently.

---

## Sequencing rule — preserve causal attribution

Do **not** implement the second-pass rewrite before proving the already-built EngineBridge structural extraction at runtime.

Preferred sequence now:

```text
first per-CPP review — CLOSED
→ second-pass architecture/correction synthesis — READ-ONLY / NEXT
→ freeze exact rewrite contract
→ compact post-EngineBridge runtime baseline on CURRENT UNCHANGED SOURCE/LOGGER
→ if baseline passes: bounded architecture/logger rewrite
→ build + source audit
→ compact/core diagnostic sufficiency regression
→ only then marker-bookkeeping simplification/feature expansion
```

Reason: the second-pass thinking should happen now while context is fresh, but the unchanged runtime baseline must still isolate the already-completed EngineBridge structural move from later observation/architecture changes.

---

## Forward roadmap after second-pass cleanup

```text
second-pass synthesis
→ unchanged post-EngineBridge baseline
→ bounded architecture/logger rewrite
→ build/source audit
→ core diagnostic sufficiency regression
→ marker-bookkeeping simplification audit against C1 authority
→ equipped-melee marker expansion one mechanism at a time
→ separate Fist source-adapter investigation/decision
→ full marker + lifecycle regression
→ modular AttackContinuationProtection investigation/implementation
→ guard + markers + continuation regression
→ mandatory New Balance/Jackydima compatibility on mature research DLL
→ retain mature modular foundation and migrate/redesign Raise + speed + config into final Script_G3AnimationBehaviors
→ final production DLL + New Balance/Jackydima compatibility regression
```

Overall architecture authority: `docs/DESIGN.md` §§10–11.  
Lifecycle authority: `docs/COLLISION_LIFECYCLE_PLAN.md`.  
Diagnostic authority: `docs/COLLISION_LOGGER_PLAN.md`.  
Staged validation authority: `docs/COLLISION_TEST_PLAN.md`.  
Future held-Use2 prevention: `docs/BAD_SKIP_FUTURE_INVESTIGATION.md`.

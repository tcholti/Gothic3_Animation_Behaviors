# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — modular structural extraction CLOSED; mandatory per-CPP review ACTIVE

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

## Structural modularization completed

### CollisionSources extraction — CLOSED

Implementation commit:

```text
43fa1e719b5af716c54e17430c101251bbc36ff8
```

Created `CollisionSources.h/.cpp` and moved unchanged:

```text
GetEquippedCollisionSources(...)
GetCollisionSourceUseType(...)
HasRequiredCollisionSources(...)
```

Validation:

```text
source/diff audit = PASS
local CMake Release build Script_FrameCollisionTest = PASS
runtime matrix = not required for this low-risk query extraction
```

### EngineBridge extraction — CLOSED

Frozen base before implementation:

```text
d0132b69df3add63641bc5d5fd5779f1037eaa99
```

Implementation head before later documentation-only commits:

```text
32ff447c9a678ba18c8234310564ff2475ba7dfb
```

Created `EngineBridge.h/.cpp`. `EngineBridge.cpp` now owns as one unit:

```text
all mCFunctionHook objects
all Gothic hook/callback wrappers
RunScriptFunctionScope TLS transport state
hook-local helpers
InstallHooks()
```

`Script_FrameCollisionTest.cpp` is reduced to DLL composition/init only.

Preserved proven ordering/reentrancy:

```text
RunScriptFunction: TLS scope before/across original → restore → bridge retirement/logging
AICombatMoveInstr: BeginCombatMove → original → CompleteCombatMoveCandidate
AISetState: capture → diagnostic pre-state → original → invalidate → finalize → diagnostic post-state
SetCollisionGroup: pre-context → original setter → marker retirement → C1 observation → diagnostics
AIFullStop / PlayMotion / StopMotion / StartRecover / OnTick ordering unchanged
StartEffect / attack callback ownership semantics unchanged
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

No runtime collision baseline has been run after EngineBridge extraction yet. First complete the mandatory read-only per-CPP review, then run the compact structural baseline with the unchanged existing logger.

---

## Production migration direction — clarified

The mature modular research DLL is increasingly the architectural foundation of the eventual production `Script_G3AnimationBehaviors` DLL.

Do **not** interpret production migration as pouring the mature collision system back into the old v0.1 file/hook structure. Instead, after the mature research collision system passes its compatibility gate, retain the proven modular foundation/central hook ownership and migrate or redesign the existing production responsibilities (Raise, speed, config, final DLL identity) into that architecture.

The final binary/module may still be named `Script_G3AnimationBehaviors`; implementation lineage does not require preserving the old v0.1 source layout.

This also means infrastructure names such as `HookBridgeRuntime` should not be renamed merely because their current research responsibility is small. Reassess naming only when the final production responsibility is known.

---

## Current responsibility — mandatory one-by-one `.cpp` review

Review every `.cpp` in:

```text
prototypes/Script_FrameCollisionTest/
```

one file at a time. Do not proceed to marker simplification or feature expansion until every file has an explicit disposition.

For each `.cpp`, record:

```text
- one-sentence responsibility / allowed ownership
- dependencies and dependency direction
- behavior-critical vs diagnostic-only code
- state/data ownership and lifetime
- hook/calling-convention/order assumptions where relevant
- duplicated responsibility / dead historical paths / unnecessary coupling
- marker/lifecycle/source invariants that must survive
- New Balance / Jackydima compatibility risk where relevant
- verdict: ACCEPTED AS-IS, or REQUIRES A SEPARATELY FROZEN BOUNDED CORRECTION
```

### First-pass rule

The first pass is now strictly **read-only for source**. Do not edit implementation files while later `.cpp` responsibilities are still being reviewed. Findings that need cleanup or architectural movement go into the explicit second-pass queue below.

This preserves one stable source baseline while the whole subsystem is classified and reduces the risk that an early cleanup changes the ground underneath later reviews.

### Mandatory second-pass architecture/correction gate

After every `.cpp` has an explicit first-pass disposition, perform a second read-only synthesis pass over all deferred/correction items **before** the post-EngineBridge runtime baseline or later feature expansion.

Purpose:

```text
re-evaluate every deferred item with the whole subsystem understood
→ resolve unnecessary historical baggage before it crosses more chat boundaries
→ decide which responsibility moves/removals/renames should happen now
→ freeze one coherent bounded rewrite plan
→ only then implement that rewrite
```

The second pass may conclude that an item should remain deferred, but that decision must be explicit rather than inherited automatically from an earlier file review.

If the resulting rewrite is broad enough to benefit from Work/High, Normal Chat should own the engineering/architecture and `BETWEEN_CHATS.md` should carry the frozen implementation contract into that bounded execution. Do not let Work redesign the architecture independently.

### First-pass review status

```text
1. Script_FrameCollisionTest.cpp  — ACCEPTED AS-IS
2. EngineBridge.cpp               — ACCEPTED for current research architecture
   second-pass queue: marker-policy leakage boundary after CollisionControl review
   second-pass queue: diagnostic-only hook install surface during logger consolidation
3. CollisionSources.cpp           — ACCEPTED AS-IS
4. HookBridgeRuntime.cpp          — ACCEPTED AS-IS
5. CollisionLifecycleGuard.cpp    — CORE C1/P2/R1 BEHAVIOR ACCEPTED
   second-pass correction: remove dormant rejected eager ScriptFunction dispatch stack/API
   second-pass review: diagnostics coupling remains embedded pending logger/architecture synthesis
6. CollisionControl.cpp           — next
7. CollisionDiagnostics.cpp       — pending
```

For `CollisionLifecycleGuard.cpp`, preserve during any later cleanup:

```text
C1 monotonic generation ownership
exact per-source offense/cleanup obligations
proven P2 temporary pre-Combat correlator
native cleanup precedence
post-AISetState exact current-equipped liveness gate
exact outstanding live/equipped Item_Attack 7 -> Item_Equipped 5 repair
no ClearTriggeredList in terminal repair
fixed two-source classify/repair phase before finalization log emission
```

Confirmed dead historical lifecycle item queued for second pass:

```text
ScriptFunctionDispatchToken
BeginScriptFunctionDispatch / EndScriptFunctionDispatch
g_ScriptFunctionDispatchStack
InvalidateScriptFunctionDispatchAfterAISetState and its now-no-op EngineBridge call
unused <vector> dependency once the dead stack is removed
```

Do **not** remove `ScriptFunctionDispatchContext`, `CaptureTopScriptFunction`, `CaptureCurrentTopScriptFunction`, `HasLiveCorrelator`, `OuterFrameBinding`, or the proven P2 pre-Combat bridge; those remain live architecture despite the similar naming.

Headers are inspected alongside their owning `.cpp` as needed, but the acceptance gate is recorded per `.cpp`.

### Diagnostics/logger rule

`CollisionDiagnostics.cpp` gets a dedicated classification:

```text
CORE COLLISION EVIDENCE
OPT-IN DEEP PROBES
OBSOLETE HISTORICAL NOISE
```

Do not slim the logger during the first-pass file review. The second-pass synthesis must decide the final logger/hook reduction boundary before implementation. After the approved rewrite is built, the compact post-EngineBridge runtime baseline must still use enough evidence to prove the structural/architectural changes did not alter collision behavior.

---

## Forward roadmap

```text
CollisionSources extraction — CLOSED
→ EngineBridge extraction — CLOSED / build PASS
→ mandatory one-by-one .cpp first review — ACTIVE
→ mandatory second-pass deferred/correction synthesis — REQUIRED
→ freeze/implement approved bounded architecture cleanup
→ build/source audit
→ compact post-EngineBridge collision baseline with sufficient unchanged/core evidence
→ approved logger reduction / opt-in deep probes as frozen by second pass
→ diagnostic sufficiency regression
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
Diagnostic authority: `docs/COLLISION_LOGGER_PLAN.md`.  
Staged validation authority: `docs/COLLISION_TEST_PLAN.md`.  
Future held-Use2 prevention: `docs/BAD_SKIP_FUTURE_INVESTIGATION.md`.

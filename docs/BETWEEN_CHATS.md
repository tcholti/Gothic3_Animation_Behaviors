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

No source edits during review unless a file is explicitly found to require a separately frozen correction and that correction is agreed before implementation.

### Per-CPP review status

```text
1. Script_FrameCollisionTest.cpp  — ACCEPTED AS-IS
2. EngineBridge.cpp               — ACCEPTED for current research architecture
   deferred: marker-policy leakage boundary after CollisionControl review
   deferred: diagnostic-only hook install surface during logger consolidation
3. CollisionSources.cpp           — ACCEPTED AS-IS
4. HookBridgeRuntime.cpp          — ACCEPTED AS-IS
5. CollisionLifecycleGuard.cpp    — CURRENT REVIEW
6. CollisionControl.cpp           — pending
7. CollisionDiagnostics.cpp       — pending
```

Headers are inspected alongside their owning `.cpp` as needed, but the acceptance gate is recorded per `.cpp`.

### Diagnostics/logger rule

`CollisionDiagnostics.cpp` gets a dedicated classification:

```text
CORE COLLISION EVIDENCE
OPT-IN DEEP PROBES
OBSOLETE HISTORICAL NOISE
```

Do not slim the logger before the post-EngineBridge compact runtime baseline. The existing logger must first prove the structural extraction did not alter behavior. After that baseline passes, freeze and implement any approved logger reduction separately, then prove diagnostic sufficiency.

---

## Forward roadmap

```text
CollisionSources extraction — CLOSED
→ EngineBridge extraction — CLOSED / build PASS
→ mandatory one-by-one .cpp review — ACTIVE
→ compact post-EngineBridge collision baseline with unchanged logger
→ approved logger reduction: compact core + opt-in deep probes
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

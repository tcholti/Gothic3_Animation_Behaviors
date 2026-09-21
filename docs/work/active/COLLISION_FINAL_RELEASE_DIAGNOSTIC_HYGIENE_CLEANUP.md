# Gothic 3 — Final Collision Release / Diagnostic Hygiene Cleanup

**Status:** ACTIVE — AUTHORIZED BOUNDED IMPLEMENTATION  
**Opened:** 2026-09-21  
**Finding source:** archived final source-quality audit B-02–B-05 + C-01  
**Behavior change intent:** NONE  
**Work build execution:** PROHIBITED

## Gate — SATISFIED

The prerequisite C1 metadata cleanup was implemented in `9789254866bb47dcbadb145aeb9831c7c0e4e97f` and independently reviewed PASS by Normal Chat.

This release/diagnostic hygiene cleanup is now the sole authorized Work implementation responsibility.

## Responsibility

Implement only the accepted release/diagnostic hygiene cleanup:

- B-02 raw8 diagnostic-only state/work removed from behavior compilation;
- B-03 dead closed TouchDamage diagnostic APIs removed;
- B-04 EquippedSprint CORE diagnostics compacted;
- B-05 behavior-core startup banner corrected;
- C-01 compact raw8 diagnostic APIs stripped of now-unused parameters.

No gameplay/feature semantics may change.

## B-02 — raw8 release purity

In `Raw8FistCollision`, the following are diagnostic-only and must not exist/do native observation work in the behavior twin:

```text
Raw8FistMarkerExecution:
  maxTime
  nativeThresholdConstant
  computedThreshold
  timingApplicationLogged

InvocationScope:
  fullStop

UpdateMarkerOwnership:
  ownership-time CaptureRaw8FistPrimaryTiming call used only for diagnostic address output
```

Use compile-time diagnostic guards where needed.

Preserve behavior-required:
- forcedPlayTime;
- timingAnimationActor / timingMotionType;
- timingActive;
- opportunityPending / ordinal;
- exact actor/source/SPU/C1 identity;
- the marker-time timing capture/calculation that determines forcedPlayTime;
- every latch/opportunity transition.

Do not remove or alter behavior-required GetPlayTime/OnDamage transports.

## B-03 — retire dead TouchDamage research logging

Remove only the dead no-caller closed-research diagnostic APIs:

```text
LogFistCanBeActivatedNow
LogFistTriggerTarget
LogFistHookEntry
LogFistHookEntryCap
```

and their now-private `LogFistGateDispatchContext` helper if no longer used.

Preserve:
- current CORE ONDAMAGE logging;
- current trigger-state snapshots that still have callers;
- active DEEP diagnostics/hooks;
- Hack callback identity diagnostics.

## B-04 — EquippedSprint CORE compaction

Current routine logging is pointer-rich and logs ordinary no-bound/no-op callback traffic repeatedly.

Required CORE rule:

```text
known healthy no-op/unbound traffic -> silent
material Sprint binding/authorization transition -> compact CORE
identity/lifetime contradiction or denial on an existing/expected bound execution -> compact CORE
rich addresses -> not routine CORE
```

At minimum:
- suppress routine ordinary true-Power `NO_BOUND_SPRINT_ORIGIN` callback spam;
- suppress routine unrelated/non-bound callback no-ops;
- avoid repeated identical healthy binding/continuation callback records when no material state/authorization transition occurred;
- remove actor/source raw addresses from routine CORE;
- preserve enough semantic identity to prove actor, action/family, C1, source UseTypes/required mask, marker, reason and motion when a material event is logged;
- retain/emit useful evidence for Sprint bind, same-C1 Action9 -> Action2 authorization, and actual mismatch/denial contradictions.

Do not add diagnostic-only release state merely to dedupe logs. Prefer existing behavior state/current decision comparisons.

No equipped Sprint behavior decision may change.

## B-05 — diagnostic startup identity

Update `BehaviorCore:` startup inventory to include permanent:

```text
EquippedSprintCollision
PhysicalFistCollision
```

Do not otherwise change startup behavior.

## C-01 — compact raw8 diagnostic signatures

Remove now-unused parameters from the compact `RAW8_OPPORTUNITY_*` diagnostic interfaces/call sites.

Accepted cleanup includes:
- `spu` where it is passed only to the compact identity helper and ignored;
- contact-consumed caller/Arg1/Arg2 parameters that are no longer emitted;
- CLOSE `opportunityPending` parameter now that CLOSE is emitted only for actually pending opportunities.

Preserve the current compact emitted semantics:
- actor name;
- action/family;
- motion;
- C1;
- raw8 source name;
- opportunity ordinal;
- event reason;
- latch/write/timing fields still relevant to that event.

Do not broaden CORE again.

## Expected source scope

```text
MODIFY prototypes/Script_FrameCollisionTest/Raw8FistCollision.cpp
MODIFY prototypes/Script_FrameCollisionTest/Raw8FistCollision.h

MODIFY prototypes/Script_FrameCollisionTest/EquippedSprintCollision.cpp

MODIFY prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
MODIFY prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
```

No CMake or EngineBridge change is expected.

If faithful implementation requires broader source scope or behavior changes, STOP and report contradiction.

## Protected behavior

Do not change:
- raw8 latch/opportunity/timing calculations;
- raw8 C1/source/SPU identity or finalization;
- raw8 hooks/original-call behavior;
- equipped Sprint eligibility, bound identity or authorization semantics;
- raw55 behavior;
- generic marker behavior;
- lifecycle/source operations;
- CMake source membership.

## Static verification

Verify:
- exact five-file scope;
- behavior twin contains no B-02 diagnostic-only fields/work;
- behavior-required raw8 timing state remains;
- four dead TouchDamage APIs/helper are absent and no live caller was removed;
- EquippedSprint routine CORE is compact/no pointer-rich no-op spam;
- material bind/continuation/contradiction evidence remains;
- startup `BehaviorCore` inventory names both permanent modules;
- compact raw8 diagnostic APIs have no accepted-unused parameters;
- behavior target/source membership unchanged;
- `git diff --check` PASS.

## Build / publication

Work build execution is PROHIBITED.

When this task becomes active, the User authorizes publication to branch `docs/collision-source-evidence`.

## Required report

Report final remote commit SHA, parent SHA, exact changed files, each finding result, static checks, and:
`Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`

Then STOP.

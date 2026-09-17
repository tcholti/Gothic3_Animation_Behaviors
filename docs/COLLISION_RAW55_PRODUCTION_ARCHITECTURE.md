# Gothic 3 Animation Behaviors — Permanent raw55 PhysicalFist Architecture

**Status:** FROZEN production-behavior architecture and bounded implementation contract  
**Date:** 2026-09-17  
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

Promote only the behavior proven by the completed PhysicalFist/raw55 research campaign into a permanent diagnostics-free collision feature owner.

This is a production-behavior promotion, not another causal probe. `PhysicalFistProbe` is evidence scaffolding and must not become production architecture.

The first permanent implementation belongs in the existing collision behavior-source assembly under `prototypes/Script_FrameCollisionTest/`, where the same behavior sources compile into both:

```text
Script_FrameCollisionBehaviorTest   diagnostics-free behavior target
Script_FrameCollisionTest           diagnostic twin
```

Do **not** migrate the collision subsystem into `src/Script_G3AnimationBehaviors` in this task. That remains a later integration step after focused acceptance and standalone collision regression.

---

## 1. Evidence Authority

The production contract is bounded by the closed raw55 evidence:

```text
Quick first/repeated contact          EV-265–EV-273
Normal native separation/first hit    EV-277–EV-279
Normal early marker/contact reset     EV-286–EV-292
true Power first/repeated contact     EV-274–EV-276, EV-293
Sprint first contact                  EV-280–EV-282
Sprint Action9 -> Action2 continuity  EV-283
Sprint repeated contact               EV-294
```

Governing conclusions:

```text
Authored FIST timing owns raw55 offensive timing.
Native premature raw55 opening must not substitute for the first authored FIST.
Repeated authored FIST uses contact-bookkeeping rearm only; it does not issue another physical group request.
Native damage/target/contact dispatch remains Gothic-owned.
Native final exact RIGHT 7 -> 5 cleanup remains Gothic-owned.
CollisionLifecycleGuard remains lifecycle protection/repair, not ordinary raw55 attack semantics.
```

---

## 2. Permanent Owner

Create:

```text
PhysicalFistCollision.cpp
PhysicalFistCollision.h
```

under:

```text
prototypes/Script_FrameCollisionTest/
```

Add both files to `FRAME_COLLISION_BEHAVIOR_SOURCES` so they compile identically into the diagnostics-free behavior target and diagnostic twin.

`PhysicalFistCollision` owns only:

```text
supported raw55 family policy: Normal / Quick / Power / Sprint
exact marked raw55 execution eligibility
minimal C1-scoped raw55 execution/origin state
selective premature native raw55 5 -> 7 suppression
accepted authored raw55 FIST operations
Sprint-origin continuity across same-C1 Action9 -> Action2
exact Normal native between-contact ALL-clear suppression when required
```

It does **not** own hooks, direct damage, target selection, terminal cleanup, raw8 behavior, equipped RIGHT/LEFT/BOTH/OFF semantics, or generic C1 lifecycle policy.

---

## 3. Permanent Module Boundaries

```text
EngineBridge
  sole physical Gothic hook owner
  callback/hook transport only
  delegates raw55 decisions to PhysicalFistCollision

FrameCollisionMarkers
  reserved marker recognition
  exact current-motion/frame-effect scan
  factual current Hit-family resolution
  stable equipped/raw8 marker path unchanged

CollisionSources
  factual source/UseType access only

CollisionSourceOperations
  generic physical source mutations
  expose opening and contact-rearm as separate primitives

CollisionLifecycleGuard
  C1 generation/source obligations
  native-cleanup reconciliation / terminal repair backup
  no new raw55 policy

Raw8FistCollision
  unchanged raw8 mechanism

PhysicalFistCollision
  permanent raw55 policy/state described by this contract

PhysicalFistProbe
  remove from build and delete after promotion
```

---

## 4. Exact raw55 Eligibility

A permanent raw55 execution may be owned only when all factual conditions hold:

```text
valid actor and current C1 generation
current Hit family belongs to Normal / Quick / Power / Sprint
exact current motion was found and scanned successfully
reserved markers are present
FIST count is 1 or 2
RIGHT / LEFT / BOTH / OFF counts are all zero
requiredSourceMask == none
raw8 ResolveFistCollisionSource(actor) is absent
exact current RIGHT equipped source exists
exact current RIGHT source UseType == gEUseType_PhysicalFist / raw55
```

No species/name gate. No filename-based family inference. No LEFT raw55 generalization. No mixed raw55 FIST + equipped-source marker execution. No support for more than two raw55 FIST markers in this first production scope.

Unmarked or unsupported cases remain native.

---

## 5. C1-Scoped Execution Identity

Use one minimal production execution record per actor, keyed by factual C1 generation.

Required semantic identity:

```text
actor instance
C1 generation
exact RIGHT raw55 source instance
immutable origin family
exact current animation identity
FIST authored count
accepted FIST count
whether the premature native 5 -> 7 was suppressed
first-marker StatePosition
whether the one Normal native ALL-clear was suppressed
last accepted FIST dispatch time/state-time needed for duplicate protection
```

The C1 generation is the execution lifetime authority. Do not create new executions from action, StatePosition, StateTime, source-group or callback rollback guesses.

A same-C1/source record keeps its origin family immutable.

The only proven cross-family continuation is:

```text
origin = Sprint / Action9
same actor + same C1 + same exact RIGHT
current factual action later becomes Power / Action2
-> keep origin = Sprint
```

Current Action2 alone must never overwrite or recreate that execution as true Power.

Any other same-C1 origin contradiction performs no new raw55 intervention and is surfaced by diagnostics; do not invent fallback ownership.

A single production map/state object may replace the many diagnostic per-family proof/intervention maps. Do not copy those maps into production.

---

## 6. Duplicate / Occurrence Protection

Raw55 FIST consumption is feature-local because the proven Sprint execution can cross Action9 -> Action2 while the same C1/source/motion continues.

Do not alter stable equipped/raw8 marker occurrence behavior merely to fit raw55.

For raw55:

```text
C1 generation + exact actor/source + exact motion + authored FIST count
= durable execution identity

acceptedFistCount < authoredFistCount
= occurrence budget

same marker dispatch with effectively identical StateTime and the existing narrow same-update elapsed window
= duplicate, no second operation
```

Action change alone does not reset or invalidate the raw55 occurrence budget when the immutable Sprint-origin continuation rule above is satisfied.

---

## 7. Native Callback Transport

Whole-callback suppression is forbidden.

The original callbacks always retain their native non-collision responsibilities unless existing equipped-marker ownership already suppresses them under the established stable path.

`PhysicalFistCollision` may expose one unified stack-scoped native-callback transport object used by `EngineBridge` for the four raw55 families:

```text
Normal  -> _AI_Attack
Quick   -> _AI_QuickAttack
Power   -> _AI_PowerAttack with factual Action2
Sprint  -> _AI_PowerAttack with factual Action9
```

The callback scope exists only so nested engine mutations can be attributed to the exact actor/source/C1/family invocation. It is transport state, not a diagnostic observation structure.

The bridge must not gain per-family raw55 policy.

---

## 8. Premature Native Opening Suppression

The existing `SetCollisionGroup` hook remains the sole transport boundary.

While an exact eligible marked raw55 callback scope is active **before the first authored FIST has been accepted**, suppress only:

```text
source       = exact current RIGHT raw55 source
before       = Item_Equipped / 5
requested    = Item_Attack / 7
same actor/C1/source callback scope
```

Families:

```text
Quick
Normal
true Power
Sprint
```

Record that the premature opening was suppressed for that execution.

Do not suppress:

```text
unmarked raw55 native attacks
other sources
other collision groups
native final 7 -> 5 cleanup
Normal/Quick native 7 -> 7 calls after an already-accepted early marker
any callback itself
```

The purpose is only to keep group5 closed until authored FIST when Gothic would otherwise open it prematurely.

---

## 9. Generic Source Operations

`CollisionSourceOperations::ActivateOrRearm()` currently combines two physical actions that raw55 evidence proves are independently owned.

Add two generic primitives without changing existing equipped semantics:

```text
ActivateAttackSource(source)
  -> request Item_Attack / 7 only
  -> no ClearTriggeredList

RearmTriggeredContacts(source)
  -> TouchDamage.ClearTriggeredList() only
  -> no collision-group request
```

Retain `ActivateOrRearm()` for equipped behavior, preferably as the same established composition of group request + clear.

`DeactivateOwnedAttackSource()` remains unchanged.

`PhysicalFistCollision` composes only the primitives required by the family/marker rules below.

---

## 10. First Authored FIST Semantics

The first accepted FIST requires exact current RIGHT raw55 group5 before activation.

### Quick

Supported proven orderings:

```text
StatePosition 0 before native Quick progression
OR
StatePosition 1 after exact premature 5 -> 7 suppression
```

Operation:

```text
5 -> 7
then one ClearTriggeredList
NO StatePosition write
```

### Normal

Early/pre-state ordering:

```text
StatePosition 0
-> 5 -> 7
-> one ClearTriggeredList
-> remember firstMarkerStatePosition = 0
```

Late/post-native-progression ordering:

```text
StatePosition 1
+ exact premature 5 -> 7 suppression already recorded
-> 5 -> 7
-> NO marker-issued clear for first contact
```

NO StatePosition write.

### true Power

Required:

```text
origin = Power
current factual family = Power / Action2
StatePosition = 1
exact premature 5 -> 7 suppression already recorded
```

Operation:

```text
5 -> 7
NO ClearTriggeredList
NO StatePosition write
```

### Sprint

Required:

```text
origin = Sprint
current factual family = Sprint / Action9
StatePosition = 1
exact premature 5 -> 7 suppression already recorded
```

Operation:

```text
5 -> 7
NO ClearTriggeredList
NO StatePosition write
```

---

## 11. Normal Native Between-Contact Clear

EV-291/EV-292 prove that when Normal's first authored FIST opens/rearms at StatePosition0, Gothic later performs an implicit public ALL clear during the native SP0 -> 1 callback transition that would create an un-authored later contact opportunity.

Permanent authored timing therefore requires one narrow production suppression seam.

Promote only the no-argument public hook:

```text
eCTrigger_PS::ClearTriggeredList()
Engine + 0x7DDA0
```

from diagnostic-only transport to the behavior hook owner.

Suppress only when all hold:

```text
current eligible Normal native-callback scope
same actor/C1/exact RIGHT raw55 execution
first authored FIST already accepted
firstMarkerStatePosition == 0
exact trigger == current RIGHT raw55 TouchDamage trigger
caller == Script_Game.dll + 0x386C6
this native clear has not already been suppressed for the execution
```

Then return without calling the original clear and mark the suppression consumed.

This rule applies even if the first contact happened to miss; production must not inspect `PC_Hero` or any target-specific visited-array state to decide authored semantics.

Do **not** promote the diagnostic entity-specific ClearTriggeredList hook. Do **not** copy trigger-state snapshots, player lookup, visited-array counting, ResetOnUntouch inspection or caller-path logging into production policy.

If Normal's first FIST is accepted only after native SP0 -> 1 progression at StatePosition1, this suppression is not armed because the native clear has already occurred before authored activation.

---

## 12. Repeated Authored FIST Semantics

For the second accepted FIST:

```text
same actor
same C1
same exact RIGHT raw55 source
first authored FIST already accepted
RIGHT currently Item_Attack / 7
authored FIST count == 2
accepted FIST count == 1
```

Operation for all four proven routes:

```text
one RearmTriggeredContacts(source)
NO SetCollisionGroup request
NO direct damage
NO StatePosition / Action / SPU write
```

Additional current-family requirements:

```text
Quick origin   -> current Quick Hit
Normal origin  -> current Normal Hit, StatePosition1
Power origin   -> current Power / Action2 Hit, StatePosition1
Sprint origin  -> current Power / Action2 Hit, StatePosition1,
                  while immutable origin remains Sprint
```

The production clear is target-agnostic. The probe's `PC_Hero` PRE/POST gates were causal-proof safeguards and must not become release behavior.

---

## 13. Cleanup / Lifecycle

No raw55 terminal-cleanup implementation is added.

A successful authored `5 -> 7` flows through the existing `SetCollisionGroup` hook and therefore through `CollisionLifecycleGuard`'s existing source-obligation observation.

Ordinary ownership remains:

```text
Gothic native exact RIGHT 7 -> 5 cleanup first
CollisionLifecycleGuard observes fulfillment
C1-R1 remains backup-only if an exact outstanding live current-equipped source is still group7 at finalization
```

Repeated FIST clear-only operations create no additional physical group request and no second cleanup obligation.

Do not add raw55 OFF, custom deactivation, polling, watchdogs, forced cleanup, direct damage, or trigger-target code.

---

## 14. Raw8 / Equipped Coexistence

Raw8 behavior is protected and unchanged.

```text
ResolveFistCollisionSource(actor) returns raw8 Fist
-> PhysicalFistCollision does not claim the execution
-> existing FrameCollisionMarkers + Raw8FistCollision path runs unchanged
```

Equipped RIGHT/LEFT/BOTH/OFF behavior is protected and unchanged.

`PhysicalFistCollision` claims only exact FIST-only raw55 executions satisfying this contract. All other marker traffic continues through the established `FrameCollisionMarkers::ProcessMarker()` path.

Do not change raw8 latch/timing permission, equipped source-set semantics, marker-owned windows, or generic cleanup semantics in order to implement raw55.

---

## 15. StartEffect / Marker Dispatch Seam

`EngineBridge::StartEffect` remains the sole reserved-marker hook owner.

For `G3AB_COL_FIST` only:

```text
ask PhysicalFistCollision whether the exact event is an owned raw55 FIST
if claimed:
    return its MarkerProcessResult-compatible factual result
    do not also run the raw8/equipped marker behavior path
if not claimed:
    run existing FrameCollisionMarkers::ProcessMarker unchanged
```

The raw55 owner may use the existing marker scan/family/C1/source APIs rather than duplicating frame-effect scanning.

Expose the current Hit-family resolver from `FrameCollisionMarkers` if needed; do not duplicate filename-based family logic in `PhysicalFistCollision`.

Because raw55 Sprint has a proven same-C1 Action9 -> Action2 transition, its occurrence budget may be feature-local as defined in §6. Do not weaken or redesign stable equipped/raw8 occurrence bookkeeping merely to accommodate that transition.

---

## 16. Diagnostics

Production behavior must not depend on diagnostics.

The diagnostic twin should retain enough existing CORE facts to prove:

```text
raw55 marker accepted / duplicate / rejected result
origin family and current family/action
C1 and exact RIGHT source
first activation group before/after
whether marker clear occurred
whether a premature native opening was suppressed
whether the exact Normal native ALL clear was suppressed
later native OnDamage
native 7 -> 5 cleanup
C1 outstanding/finalization result
```

Prefer compact stable records. Do not retain the probe's rich causal snapshots or per-experiment log vocabulary merely for history.

The diagnostics-free `Script_FrameCollisionBehaviorTest` must compile without `CollisionDiagnostics` or `PhysicalFistProbe` dependencies.

---

## 17. Research Scaffolding Removal

The production implementation must:

```text
remove PhysicalFistProbe.cpp/.h from the diagnostic target
remove all EngineBridge calls to PhysicalFistProbe
remove obsolete diagnostic-only raw55 callback-observation state
remove the diagnostic entity-specific ClearTriggeredList hook if it has no independent stable diagnostic owner
remove raw55 causal-only trigger snapshots/interventions from executable source
```

Delete `PhysicalFistProbe.cpp/.h` from the tree once no compiled source references remain.

Historical evidence remains in Git history, evidence ledgers and archived runtime artifacts.

---

## 18. Frozen Implementation Source Scope

Expected production implementation scope:

```text
ADD
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.h

MODIFY
prototypes/Script_FrameCollisionTest/CMakeLists.txt
prototypes/Script_FrameCollisionTest/CollisionSourceOperations.cpp
prototypes/Script_FrameCollisionTest/CollisionSourceOperations.h
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.cpp   [only smallest family/dispatch seam if needed]
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.h     [only smallest family/dispatch seam if needed]

DELETE
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
```

`CollisionSources.*` may be changed only if implementation needs one small factual raw55 source predicate; source-side/family policy must stay in `PhysicalFistCollision`.

`CollisionDiagnostics.*` may be changed only for the smallest compact stable CORE record required to validate the new permanent path. No causal-probe logger migration is authorized.

No other source file is in scope unless an exact compile/API contradiction makes the frozen design impossible; report such a contradiction rather than broadening silently.

---

## 19. Protected Behavior / Explicit Non-Goals

Preserve unchanged:

```text
raw8 FIST Normal/Power/Quick/Sprint behavior
RIGHT/LEFT/BOTH/OFF equipped semantics
Hack routing
C1 generation/lifecycle model
C1-R1 final repair policy
native target/contact/damage dispatch
native final raw55 cleanup
unmarked raw55 attacks
unsupported families
AttackContinuationProtection paused
Raise/speed paused
New Balance final regression paused
```

Forbidden in this task:

```text
whole AI callback suppression
Action/StatePosition/SPU writes for raw55
custom/direct damage
player/species/name special cases
manual visited-array mutation
ResetOnUntouch changes
new target-selection behavior
raw55 LEFT/BOTH/OFF semantics
more-than-two-FIST generalization
new polling/tick/watchdog behavior
new lifecycle cleanup system
copying PhysicalFistProbe wholesale
migration into src/Script_G3AnimationBehaviors
```

---

## 20. Work Execution Contract

This is a frozen production implementation task under `FEATURE_DEVELOPMENT_METHOD.md` and `WORK_IMPLEMENTATION_PROTOCOL.md`.

Work must:

```text
read SESSION_ENTRYPOINT.md
read BETWEEN_CHATS.md
read this file
read FEATURE_DEVELOPMENT_METHOD.md
read WORK_IMPLEMENTATION_PROTOCOL.md
inspect only the exact source/API needed for this responsibility
implement only the frozen permanent raw55 behavior
remove the temporary probe from the compiled architecture
source/static audit
publish to docs/collision-source-evidence
report final remote commit SHA, changed files, concise result, build status, contradictions
STOP
```

**Work build execution is PROHIBITED.**

Normal Chat + User own independent source review, local build, deployment and runtime acceptance.

---

## 21. Local Acceptance After Work

After independent source review:

```text
1. build Script_FrameCollisionBehaviorTest Release
2. build Script_FrameCollisionTest Release
3. behavior-only compile/load smoke
4. diagnostic deploy/hash/twin/startup gate
5. focused permanent raw55 runtime acceptance
```

Focused runtime acceptance must include factual controls for:

```text
Quick raw55 authored first/repeated contact
Normal raw55 early/pre-state first contact + marker2 rearm
true Power raw55 first/repeated contact
Sprint-origin raw55 Action9 -> Action2 first/repeated contact
unmarked raw55 native fallback
raw8 FIST sentinel
one equipped-marker sentinel
native 7 -> 5 cleanup / outstanding-zero finalization
```

Only after focused permanent raw55 acceptance closes does the project proceed to standalone collision regression and then the New Balance 0.7 exact distributed-bundle regression.

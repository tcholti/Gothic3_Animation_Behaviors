# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-17

## Current Bridge — EV-294 CLOSED; PERMANENT RAW55 ARCHITECTURE FROZEN; WORK IMPLEMENTATION READY

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical collision evidence is through **EV-294**.

Latest canonical evidence:

`docs/EVIDENCE_LEDGER_291_ONWARD.md` — EV-294

Frozen permanent production contract:

`docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`

All family-specific PhysicalFist/raw55 causal research is closed:

```text
Quick         repeated-FIST CLOSED/PASS — EV-273
Normal        repeated-FIST CLOSED/PASS — EV-292
true Power    repeated-FIST CLOSED/PASS — EV-293
Sprint-origin repeated-FIST CLOSED/PASS — EV-294
```

## Permanent owner

Create the dedicated behavior owner:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.h
```

It must compile as a behavior source into both:

```text
Script_FrameCollisionBehaviorTest
Script_FrameCollisionTest
```

Do not migrate the collision subsystem into `src/Script_G3AnimationBehaviors` in this task.

## Frozen semantics

```text
ELIGIBILITY
exact marked FIST-only execution
+ valid C1
+ family Normal / Quick / Power / Sprint
+ no raw8 resolver
+ exact current RIGHT source PhysicalFist/raw55
+ authored FIST count 1 or 2
-> permanent raw55 owner may claim the execution

PREMATURE NATIVE OPENING
exact same-C1/current-RIGHT raw55 5 -> requested7 before first authored FIST
-> suppress only the physical SetCollisionGroup request
-> preserve the original AI callback and native StatePosition progression

FIRST FIST — QUICK
SP0 before native progression, or SP1 after proven early suppression
-> exact RIGHT 5 -> 7
-> one ClearTriggeredList
-> no StatePosition write

FIRST FIST — NORMAL
SP0
-> exact RIGHT 5 -> 7
-> one ClearTriggeredList
-> remember pre-state first-marker ownership

SP1 after proven early suppression
-> exact RIGHT 5 -> 7
-> no first-marker clear

FIRST FIST — TRUE POWER
origin Power + current Action2/SP1 + early suppression
-> exact RIGHT 5 -> 7
-> no clear

FIRST FIST — SPRINT
origin Sprint + current Action9/SP1 + early suppression
-> exact RIGHT 5 -> 7
-> no clear

NORMAL HIDDEN NATIVE REARM
when first authored Normal FIST was accepted at SP0:
-> suppress only exact public ALL eCTrigger_PS::ClearTriggeredList()
-> trigger = exact current RIGHT raw55 TouchDamage trigger
-> caller = Script_Game.dll +0x386C6
-> one suppression per execution
-> no player/visited-array gate

SECOND FIST — ALL PROVEN ROUTES
same C1 + same exact RIGHT + source already group7
-> one ClearTriggeredList only
-> no second SetCollisionGroup request

SPRINT ORIGIN
same-C1/same-RIGHT Action9 -> Action2 keeps immutable Sprint origin
current Action2 alone never reclassifies that execution as true Power

CLEANUP
Gothic native exact RIGHT 7 -> 5 remains primary
CollisionLifecycleGuard remains backup-only
```

## Production state boundary

Use one minimal C1-scoped raw55 execution record per actor rather than the probe's many family-specific proof/intervention maps.

C1 generation is the factual execution lifetime authority. The record needs only the identity/state required by the frozen contract: actor, generation, exact RIGHT source, immutable origin family, motion identity, authored/accepted FIST count, early-suppression fact, first-marker StatePosition, one Normal native-clear-suppression fact, and narrow duplicate-protection facts.

Do not reset raw55 execution identity merely because Action changes. The only proven cross-family continuation is Sprint origin surviving same-C1/same-RIGHT Action9 -> Action2.

## Required generic source-operation split

`CollisionSourceOperations::ActivateOrRearm()` currently combines group opening and contact clear. Preserve its equipped behavior, but add separate generic primitives:

```text
ActivateAttackSource(source)
-> Item_Attack / 7 only
-> no clear

RearmTriggeredContacts(source)
-> ClearTriggeredList only
-> no collision-group request
```

`PhysicalFistCollision` composes those primitives according to the family rules above.

## Marker / hook seams

`EngineBridge` remains sole hook owner and transport-only.

Required minimal permanent seams:

```text
AI callbacks
-> establish exact stack-scoped raw55 callback transport around original callback

SetCollisionGroup hook
-> ask PhysicalFistCollision whether exact native 5 -> 7 request is suppressed

StartEffect / G3AB_COL_FIST
-> offer exact FIST event to PhysicalFistCollision first
-> if raw55 owner claims it, do not also execute stable raw8/equipped marker behavior
-> otherwise existing FrameCollisionMarkers::ProcessMarker path is unchanged

ClearTriggeredList() ALL hook at Engine +0x7DDA0
-> permanent transport only for the exact Normal hidden-native-clear suppression
```

Do not promote the entity-specific clear hook unless an independent stable purpose exists.

Stable equipped/raw8 marker occurrence behavior remains unchanged. Raw55 may keep a feature-local C1/source/motion FIST occurrence budget because Sprint can change Action9 -> Action2 inside the same execution.

## Research scaffolding removal

The production task must remove the temporary probe from executable architecture:

```text
remove PhysicalFistProbe.cpp/.h from CMake
delete PhysicalFistProbe.cpp/.h
remove EngineBridge probe calls/includes
remove per-family diagnostic callback observation structures/state
remove raw55 causal-only target/visited snapshots and interventions
remove diagnostic entity-specific ClearTriggeredList hook if probe-only
```

Do not copy the probe wholesale into `PhysicalFistCollision`.

## Frozen source scope

Expected scope:

```text
ADD
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.h

MODIFY
prototypes/Script_FrameCollisionTest/CMakeLists.txt
prototypes/Script_FrameCollisionTest/CollisionSourceOperations.cpp
prototypes/Script_FrameCollisionTest/CollisionSourceOperations.h
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.cpp  [smallest seam only if needed]
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.h    [smallest seam only if needed]

DELETE
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
```

Conditional narrow allowance only:

```text
CollisionSources.*     one small factual raw55-source predicate if genuinely needed
CollisionDiagnostics.* smallest compact stable CORE record needed for permanent acceptance
```

No other source broadening is authorized. If the exact source/API contradicts the frozen architecture, Work reports the contradiction and stops rather than inventing semantics.

## Protected behavior

Preserve unchanged:

```text
raw8 FIST Normal/Power/Quick/Sprint
RIGHT/LEFT/BOTH/OFF equipped markers
Hack motion routing
C1 generation/lifecycle model and C1-R1 repair
native target/contact/damage dispatch
native final raw55 cleanup
unmarked raw55 attacks
unsupported families
```

Forbidden:

```text
whole AI callback suppression
raw55 Action/StatePosition/SPU writes
custom/direct damage
player/species/name special cases
manual visited-array mutation or ResetOnUntouch changes
raw55 LEFT/BOTH/OFF
more-than-two-FIST generalization
polling/tick/watchdog behavior
new cleanup system
migration into src/Script_G3AnimationBehaviors
```

## Current responsibility — WORK PRODUCTION IMPLEMENTATION

The architecture is frozen. Work may now implement the exact production responsibility in `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`.

Read order:

1. `docs/SESSION_ENTRYPOINT.md`
2. this file
3. `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`
4. `docs/FEATURE_DEVELOPMENT_METHOD.md`
5. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
6. only the exact source/API required by the frozen scope.

Work sequence:

```text
implement minimum permanent PhysicalFistCollision behavior
remove temporary PhysicalFistProbe executable scaffolding
source/static audit including exact scope and protected behavior
git diff --check / equivalent static cleanliness
publish to docs/collision-source-evidence
report final remote commit SHA + changed files + concise result + build status + contradictions
STOP
```

**WORK BUILD EXECUTION IS PROHIBITED.**

Normal Chat + User own independent source review, local build, deployment and runtime acceptance after Work returns.

## After Work

```text
independent source review
-> build Script_FrameCollisionBehaviorTest Release
-> build Script_FrameCollisionTest Release
-> behavior-only load smoke
-> diagnostic deploy/hash/startup
-> focused permanent raw55 acceptance:
   Quick first/repeat
   Normal SP0 first + marker2
   true Power first/repeat
   Sprint-origin Action9 -> Action2 first/repeat
   unmarked raw55 native fallback
   raw8 FIST sentinel
   equipped-marker sentinel
   native 7 -> 5 / outstanding-zero lifecycle
-> standalone collision regression
-> New Balance 0.7 exact distributed-bundle regression with AttackCollision included
-> migrate mature collision assembly into Script_G3AnimationBehaviors
```

## Still paused

```text
NO source migration into final Script_G3AnimationBehaviors yet
NO broad collision certification before focused permanent raw55 acceptance
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

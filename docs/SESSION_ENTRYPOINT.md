# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-17

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is the diagnostic twin. Permanent collision behavior must also compile in diagnostics-free `Script_FrameCollisionBehaviorTest`. Final migration into `src/Script_G3AnimationBehaviors` occurs only after focused acceptance and standalone collision regression.

> **LARGE-LOG RULE:** Do not orient by scanning raw/archive logs. Use canonical EV first and committed derived packages for large-log retrieval. Processed source evidence moves unchanged to `research/archive/`.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Frozen production contract: `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`  
Latest canonical evidence: **EV-294** in `docs/EVIDENCE_LEDGER_291_ONWARD.md`

## Current checkpoint

```text
raw55 Quick         repeated-FIST CLOSED/PASS — EV-273
raw55 Normal        repeated-FIST CLOSED/PASS — EV-292
raw55 true Power    repeated-FIST CLOSED/PASS — EV-293
raw55 Sprint-origin repeated-FIST CLOSED/PASS — EV-294

ALL FAMILY-SPECIFIC RAW55 CAUSAL RESEARCH CLOSED
PERMANENT RAW55 ARCHITECTURE FROZEN
```

## Frozen permanent architecture

Permanent owner:

```text
PhysicalFistCollision.cpp/.h
```

First implementation location:

```text
prototypes/Script_FrameCollisionTest/
```

The files are behavior sources and must compile into both:

```text
Script_FrameCollisionBehaviorTest
Script_FrameCollisionTest
```

Do **not** migrate collision into `src/Script_G3AnimationBehaviors` yet.

Core production semantics:

```text
exact FIST-only current-motion ownership
+ exact current RIGHT PhysicalFist/raw55 source
+ valid factual C1 generation
+ family in Normal / Quick / Power / Sprint
-> PhysicalFistCollision may own authored raw55 timing

premature native exact RIGHT 5 -> 7 before first FIST
-> suppress only that physical request
-> original AI callback/state progression remains native

first FIST:
Quick SP0 or proven post-suppression SP1 -> 5 -> 7 + ClearTriggeredList
Normal SP0 -> 5 -> 7 + ClearTriggeredList
Normal proven post-suppression SP1 -> 5 -> 7 only
Power proven post-suppression SP1 -> 5 -> 7 only
Sprint proven post-suppression Action9/SP1 -> 5 -> 7 only

Normal first FIST at SP0
-> suppress only exact native ALL ClearTriggeredList from Script_Game.dll +0x386C6
-> prevents Gothic's hidden between-contact rearm from substituting for marker2

second FIST:
RIGHT already group7
-> ClearTriggeredList only
-> NO second SetCollisionGroup request

Sprint origin:
Action9 origin persists across same-C1/same-RIGHT Action9 -> Action2
current Action2 alone never reclassifies it as true Power

cleanup:
Gothic native exact RIGHT 7 -> 5 remains primary
CollisionLifecycleGuard remains backup-only
```

Production deliberately excludes probe-only safety/causal state:

```text
NO PC_Hero visited-array gates
NO target-specific policy
NO causal snapshots
NO per-family proof maps
NO whole-callback suppression
NO Action/StatePosition/SPU writes
NO direct damage
NO custom cleanup
NO raw55 LEFT/BOTH/OFF
NO >2 FIST generalization
```

## Current responsibility — BOUNDED WORK PRODUCTION IMPLEMENTATION

The architecture is frozen. A Work implementation task may now be issued.

Work must read:

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`
4. `docs/FEATURE_DEVELOPMENT_METHOD.md`
5. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
6. only the exact source/API files required by the frozen source scope.

Work responsibility:

```text
implement the permanent PhysicalFistCollision owner exactly as frozen
add separate generic source primitives for group opening and contact rearm
add only the minimal EngineBridge transport seams
preserve stable raw8/equipped/lifecycle behavior
remove PhysicalFistProbe from the compiled architecture and delete its source
publish one bounded production implementation
source/static audit
STOP
```

**Work build execution is PROHIBITED.**

Normal Chat + User own independent source review and both local builds after Work returns.

## Expected source scope

```text
ADD
PhysicalFistCollision.cpp/.h

MODIFY
CMakeLists.txt
CollisionSourceOperations.cpp/.h
EngineBridge.cpp
FrameCollisionMarkers.cpp/.h only for the smallest dispatch/family seam if needed

DELETE
PhysicalFistProbe.cpp/.h
```

`CollisionSources.*` and `CollisionDiagnostics.*` are conditional narrow allowances only as specified by the frozen architecture. No other source broadening is authorized without an exact contradiction.

## After Work

```text
independent Normal Chat source review
-> build Script_FrameCollisionBehaviorTest Release
-> build Script_FrameCollisionTest Release
-> behavior-only load smoke
-> diagnostic deploy/hash/startup
-> focused permanent raw55 acceptance
-> standalone collision regression
-> New Balance 0.7 exact distributed-bundle regression, AttackCollision included
-> migrate mature collision assembly into Script_G3AnimationBehaviors
```

## Still paused

```text
NO collision migration into src/Script_G3AnimationBehaviors yet
NO standalone broad regression before permanent raw55 focused acceptance
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

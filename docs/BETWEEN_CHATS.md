# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-17

## Current Bridge — EV-294 CLOSED; PERMANENT RAW55 IMPLEMENTED + SOURCE REVIEW PASS

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical collision evidence is through **EV-294**.

Frozen permanent contract:

`docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`

Permanent implementation:

```text
21853392f146febbc2d1aad4e501baa741fd65b2
```

Frozen base:

```text
71a5ae377c4043677c0a8edd86801d2db697fac0
```

Normal Chat independent source review: **PASS**.

## Review result

The implementation is exactly one commit over the frozen base and stays inside the authorized source scope:

```text
ADD
PhysicalFistCollision.cpp/.h

MODIFY
CMakeLists.txt
CollisionSourceOperations.cpp/.h
EngineBridge.cpp
FrameCollisionMarkers.cpp/.h

DELETE
PhysicalFistProbe.cpp/.h
```

No conditional `CollisionSources.*` or `CollisionDiagnostics.*` broadening was required.

Review confirms the permanent design rather than probe promotion:

```text
one actor/C1 raw55 execution record
exact RIGHT PhysicalFist/raw55 FIST-only eligibility
immutable origin family
Sprint origin survives same-C1/same-RIGHT Action9 -> Action2
feature-local authored FIST count + duplicate budget
stack-scoped native callback transport
selective premature exact RIGHT 5 -> 7 suppression only before first accepted FIST
Quick first FIST = 5 -> 7 + clear
Normal SP0 first FIST = 5 -> 7 + clear
Normal SP1 first FIST after suppression = 5 -> 7 only
Power SP1 first FIST after suppression = 5 -> 7 only
Sprint Action9/SP1 first FIST after suppression = 5 -> 7 only
second FIST = clear only, no second group request
Normal hidden native ALL clear suppression = exact trigger + Script_Game.dll+0x386C6 + one-shot
Gothic native 7 -> 5 cleanup remains primary
```

Production exclusions are preserved:

```text
NO whole-callback suppression
NO PC_Hero / target-specific eligibility
NO visited-array or ResetOnUntouch policy
NO Action / StatePosition / SPU writes
NO direct/custom damage
NO raw55 LEFT/BOTH/OFF
NO custom cleanup
NO polling/watchdog
```

Stable coexistence review:

```text
Raw8FistCollision behavior unchanged
FrameCollisionMarkers equipped/raw8 processing body unchanged
only existing family resolver + marker-result constructor were exposed
ActivateOrRearm equipped semantics retained through separated primitives
Hack routing unchanged
CollisionLifecycleGuard / C1-R1 unchanged
StartEffect gives raw55 first refusal only for exact owned FIST; otherwise existing marker path runs
Raw8 timing-permission call sees raw55 UseType55 and naturally ignores it
```

Probe removal is complete from executable architecture:

```text
PhysicalFistProbe source deleted
CMake probe entries removed
EngineBridge probe calls removed
entity-specific ClearTriggeredList hook removed
public ALL ClearTriggeredList hook promoted as permanent behavior transport
```

No material source contradiction found.

## Immediate next responsibility — LOCAL BUILDS ONLY

Do not launch Work.

1. GitHub Desktop: **Fetch origin -> Pull origin -> Fetch origin**.
2. Confirm branch `docs/collision-source-evidence` is current and `Changes = 0`.
3. Build diagnostics-free permanent behavior target:

```powershell
cmake --build build --config Release --target Script_FrameCollisionBehaviorTest
```

4. If PASS, build diagnostic twin:

```powershell
cmake --build build --config Release --target Script_FrameCollisionTest
```

5. STOP on the two build results.

## After both builds PASS

```text
behavior-only load smoke
-> diagnostic deploy/hash/startup
-> focused permanent raw55 acceptance
```

Focused acceptance scope:

```text
Quick first/repeat
Normal SP0 first + marker2
true Power first/repeat
Sprint-origin Action9 -> Action2 first/repeat
unmarked raw55 native fallback
raw8 FIST sentinel
equipped-marker sentinel
native raw55 7 -> 5 / outstanding-zero lifecycle
```

Only after focused permanent acceptance closes:

```text
standalone collision regression
-> New Balance 0.7 exact distributed bundle regression with AttackCollision included
-> mature collision migration into Script_G3AnimationBehaviors
```

## Still paused

```text
NO new Work task during local validation
NO broad standalone collision regression yet
NO New Balance final regression yet
NO collision migration into src/Script_G3AnimationBehaviors yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

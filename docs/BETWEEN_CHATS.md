# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-17

## Current Bridge — EV-294 CLOSED; PERMANENT RAW55 BUILT + BEHAVIOR-ONLY SMOKE PASS

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

## Local validation so far — PASS

Release builds:

```text
Script_FrameCollisionBehaviorTest  PASS
Script_FrameCollisionTest          PASS
```

Behavior-only deployment:

```text
only live collision DLL: Script_FrameCollisionBehaviorTest.dll
length: 418304 bytes
built/live SHA256:
0EB935FCBFD5B7A2D2D56683971641EA42B9F7FF074D5B7F2EC2FD353594833A
```

The attempted live process-module query returned no `Script_FrameCollision*` module. Do not treat that as a failure criterion; the behavior product is diagnostics-free and prior canonical behavior-only gates use isolated deployment + runtime behavior/load/exit rather than persistent module enumeration.

User then performed a stronger functional smoke with the behavior-only DLL:

```text
Troll spawned and exercised:
- attacks could damage twice, behavior not observed before permanent raw55 support

Golem spawned and attacked with:
- 2H
- Dual 1H/1H
- Staff
Established authored marker behavior appeared to work normally.

Hack attack exercised and appeared to work normally.
```

Therefore the behavior-only release-purity/functional smoke is **PASS** for this bounded scope.

This functional result does not replace internal diagnostic proof of C1/source/family transitions.

## Immediate next responsibility — DIAGNOSTIC DEPLOY / STARTUP ONLY

Do not launch Work.

Remove `Script_FrameCollisionBehaviorTest.dll` from the live scripts directory and deploy the freshly built reviewed:

```text
build/prototypes/Script_FrameCollisionTest/Release/Script_FrameCollisionTest.dll
```

Do **not** restore an older held diagnostic DLL.

Verify:

```text
exactly one live Script_FrameCollision* DLL
name = Script_FrameCollisionTest.dll
built/live SHA256 match
```

Then launch Gothic 3 only far enough to load scripts and exit normally.

Verify startup log shows:

```text
diagnostic build loaded
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
unique Hack callback identity
Installing behavior hooks...
Hooks installed.
clean unload
```

STOP on startup result.

## After diagnostic startup PASS

Run the focused permanent raw55 acceptance only:

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

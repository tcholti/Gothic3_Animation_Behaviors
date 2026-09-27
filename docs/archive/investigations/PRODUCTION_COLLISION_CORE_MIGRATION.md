# Production Collision Core Migration

**Status:** CLOSED — source migration complete / independent static review PASS  
**Closed:** 2026-09-27  
**Implementation commit:** `9da92dc559d8897a675d575f8d88b3631470ed7d`  
**Original task class:** Bounded production implementation / source-only migration  
**Original branch:** `docs/collision-source-evidence`  
**Build/run in Work:** PROHIBITED

## Closure result

Work completed the frozen responsibility with no material contradiction. Independent Normal Chat review confirmed:

```text
implementation scope = exact 23 production-path files
21 migrated collision behavior files = matching Git blobs vs prototype counterparts
production CMake = Script_G3AnimationBehaviors entry + complete collision behavior core only
AttackRaise / AttackSpeed / SharedConfig = physically preserved but excluded from target
collision diagnostics = excluded from production target
production bootstrap = RuntimeClock::InitializeClock + EngineBridge::InstallHooks + ScriptInit return
prototype/diagnostic source = unchanged
source/static review = PASS
```

Runtime production-integration validation is a separate subsequent gate; it was never part of this source-only Work contract.

---

## 1. Responsibility

Migrate the already accepted EV-389 diagnostics-free collision **behavior core** from:

```text
prototypes/Script_FrameCollisionTest/
```

into the production target:

```text
src/Script_G3AnimationBehaviors/
Script_G3AnimationBehaviors.dll
```

This is a **migration of proven behavior**, not a collision redesign and not a Raise/Speed implementation task.

The final source-only result of this task must make `Script_G3AnimationBehaviors` build from the same established collision behavior core that produced the accepted EV-389 behavior-only runtime result, subject only to the narrowly authorized production-entry/build adaptations below.

## 2. Read first

Read only:

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. this file
4. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
5. `docs/FEATURE_DEVELOPMENT_METHOD.md`
6. `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`
7. `docs/DESIGN.md` §§1, 4, 6–8, 10–12
8. `prototypes/Script_FrameCollisionTest/CMakeLists.txt`
9. the exact behavior-source files named by `FRAME_COLLISION_BEHAVIOR_SOURCES`
10. `src/Script_G3AnimationBehaviors/CMakeLists.txt`
11. `src/Script_G3AnimationBehaviors/Script_G3AnimationBehaviors.cpp`

Do not broaden into closed evidence campaigns or archived probes unless a concrete source contradiction requires it.

## 3. Frozen source of truth

The accepted behavior-source set is the `FRAME_COLLISION_BEHAVIOR_SOURCES` list in:

```text
prototypes/Script_FrameCollisionTest/CMakeLists.txt
```

At task freeze it contains:

```text
AttackMotionRouting.cpp/.h
CollisionLifecycleGuard.cpp/.h
CollisionSourceOperations.cpp/.h
CollisionSources.cpp/.h
EngineBridge.cpp/.h
EquippedSprintCollision.cpp/.h
FrameCollisionMarkers.cpp/.h
FrameCollisionShared.h
PhysicalFistCollision.cpp/.h
Raw8FistCollision.cpp/.h
RuntimeClock.cpp/.h
Script_FrameCollisionTest.cpp
```

The EV-389 accepted behavior binary was built from this behavior source set without `FRAME_COLLISION_DIAGNOSTICS`.

## 4. Exact implementation contract

### 4.1 Migrate the behavior modules verbatim

Copy these files from `prototypes/Script_FrameCollisionTest/` into `src/Script_G3AnimationBehaviors/`:

```text
AttackMotionRouting.cpp
AttackMotionRouting.h
CollisionLifecycleGuard.cpp
CollisionLifecycleGuard.h
CollisionSourceOperations.cpp
CollisionSourceOperations.h
CollisionSources.cpp
CollisionSources.h
EngineBridge.cpp
EngineBridge.h
EquippedSprintCollision.cpp
EquippedSprintCollision.h
FrameCollisionMarkers.cpp
FrameCollisionMarkers.h
FrameCollisionShared.h
PhysicalFistCollision.cpp
PhysicalFistCollision.h
Raw8FistCollision.cpp
Raw8FistCollision.h
RuntimeClock.cpp
RuntimeClock.h
```

For every file above, production copy content must remain byte-for-byte identical to the prototype source at the frozen task base unless a mechanical path/include issue makes that impossible.

If an identical copy cannot compile structurally because of a concrete path/include dependency, STOP and report the contradiction rather than refactoring behavior.

Do **not**:

- rename the `FrameCollision` namespace;
- rename internal hook callback suffixes merely for cosmetics;
- rewrite behavior helpers;
- simplify conditionals;
- change hooks/RVAs;
- change marker semantics;
- change raw8/raw55/equipped ownership;
- change C1/lifecycle behavior;
- change Hack routing;
- change Sprint continuation behavior;
- remove conditional diagnostic blocks from shared behavior files merely to make production source look cleaner.

The release target simply does not define the diagnostic macros, so those blocks remain mechanically absent from the release binary.

### 4.2 Production entry point

Replace the old Raise/Speed-oriented body of:

```text
src/Script_G3AnimationBehaviors/Script_G3AnimationBehaviors.cpp
```

with the **behavior-only startup semantics** of the accepted prototype entry point:

```text
GetScriptInit()
RuntimeClock::InitializeClock()
EngineBridge::InstallHooks()
return &GetScriptInit()
DllMain DisableThreadLibraryCalls
```

The production entry point must contain no collision diagnostic initialization, log setup, diagnostic probe, or diagnostic shutdown code.

Do not add new startup behavior during this task. In particular, do not add a new explicit `LoadScriptDLL`, config loader, Raise/Speed installer, dependency detector, New Balance detector, or load-order mechanism merely because the older production entry point had one.

### 4.3 Production CMake target

Rewrite only `src/Script_G3AnimationBehaviors/CMakeLists.txt` as needed so:

```text
Script_G3AnimationBehaviors
```

compiles:

```text
Script_G3AnimationBehaviors.cpp
+ the migrated collision behavior core
```

and does **not** compile:

```text
AttackRaise.cpp/.h
AttackSpeed.cpp/.h
SharedConfig.cpp/.h
CollisionDiagnostics.cpp/.h
CollisionDiagnosticsDeep.cpp/.h
```

Do not define:

```text
FRAME_COLLISION_DIAGNOSTICS
FRAME_COLLISION_DIAGNOSTICS_DEEP
```

for the production target.

Do not rename the final target. The shipping output remains:

```text
Script_G3AnimationBehaviors.dll
```

### 4.4 Old Raise / Speed / config files

The existing files:

```text
AttackRaise.cpp/.h
AttackSpeed.cpp/.h
SharedConfig.cpp/.h
Ini/G3AnimationBehaviors.ini
```

are **not part of this migration implementation**.

Leave them physically untouched in this task, but exclude their `.cpp` files from the production target.

Their redesign/removal/reintroduction is a later bounded responsibility under ADR-0004 / ADR-0005.

### 4.5 Prototype / diagnostic source

Do not modify:

```text
prototypes/Script_FrameCollisionTest/
```

The prototype behavior/diagnostic twins remain the preserved accepted reference and diagnostic product for this migration step.

Do not create a second new diagnostic target inside `src/` during this task.

## 5. Protected behavior

All accepted collision behavior is frozen and protected, including:

```text
generic RIGHT / LEFT / BOTH / OFF authored windows
repeated equipped-contact rearm
Hack optional motion routing
Power / Pierce / SimpleWhirl / Whirl behavior already accepted
Sprint-origin equipped continuation
raw8 FIST Normal / Power / Quick / Sprint opportunity behavior
raw8 exact timing permission / contact-consumption transport
raw55 Normal / Quick / true Power / Sprint-origin behavior
raw55 one/two-FIST contract
raw55 first physical opening + second clear-only rearm
raw55 Sprint-origin same-C1 Action9 -> Action2 continuation
raw55 current-SP1/current-SP2 accepted second-FIST correction
C1 lifecycle ownership / native-first cleanup / C1-R1 backup repair
unmarked / unsupported native fallback
native target/contact/damage ownership
```

EV-389 is the release-purity acceptance gate for this source lineage. This task must not reinterpret it.

## 6. Hook ownership / New Balance boundary

`EngineBridge` remains the sole physical hook owner inside `Script_G3AnimationBehaviors`.

Do not alter shared-hook topology with `Script_AttackCollision.dll` or New Balance in this migration task. Existing tested coexistence is protected; load-order independence remains a separate question if later contradictory integration evidence appears.

The final DLL name is frozen:

```text
Script_G3AnimationBehaviors.dll
```

No load-order rename experiment is authorized here.

## 7. Explicit exclusions

Do NOT implement or redesign:

```text
Raise control
Speed control v1 or v2
G3AnimationBehaviors.ini profile parsing
AttackContinuationProtection
TargetAcquisition
Climbing
new collision markers
new hook points
New Balance-specific branches
Script_AttackCollision-specific branches
DLL/version detection
load-order compensation
namespace cleanup
broad file/folder restructuring
prototype deletion
historical documentation cleanup
```

## 8. Allowed files

Implementation edits are limited to:

```text
src/Script_G3AnimationBehaviors/CMakeLists.txt
src/Script_G3AnimationBehaviors/Script_G3AnimationBehaviors.cpp
src/Script_G3AnimationBehaviors/AttackMotionRouting.cpp
src/Script_G3AnimationBehaviors/AttackMotionRouting.h
src/Script_G3AnimationBehaviors/CollisionLifecycleGuard.cpp
src/Script_G3AnimationBehaviors/CollisionLifecycleGuard.h
src/Script_G3AnimationBehaviors/CollisionSourceOperations.cpp
src/Script_G3AnimationBehaviors/CollisionSourceOperations.h
src/Script_G3AnimationBehaviors/CollisionSources.cpp
src/Script_G3AnimationBehaviors/CollisionSources.h
src/Script_G3AnimationBehaviors/EngineBridge.cpp
src/Script_G3AnimationBehaviors/EngineBridge.h
src/Script_G3AnimationBehaviors/EquippedSprintCollision.cpp
src/Script_G3AnimationBehaviors/EquippedSprintCollision.h
src/Script_G3AnimationBehaviors/FrameCollisionMarkers.cpp
src/Script_G3AnimationBehaviors/FrameCollisionMarkers.h
src/Script_G3AnimationBehaviors/FrameCollisionShared.h
src/Script_G3AnimationBehaviors/PhysicalFistCollision.cpp
src/Script_G3AnimationBehaviors/PhysicalFistCollision.h
src/Script_G3AnimationBehaviors/Raw8FistCollision.cpp
src/Script_G3AnimationBehaviors/Raw8FistCollision.h
src/Script_G3AnimationBehaviors/RuntimeClock.cpp
src/Script_G3AnimationBehaviors/RuntimeClock.h
```

No other source, prototype, configuration, documentation, submodule, or build file is authorized for implementation edits.

## 9. Required static audit

Before commit, perform all applicable source-only checks:

1. Verify each migrated core file listed in §4.1 is byte-for-byte identical to its prototype counterpart.
2. Verify the production entry point contains only the authorized behavior startup semantics.
3. Verify `Script_G3AnimationBehaviors` CMake sources include the complete migrated behavior core.
4. Verify the production target excludes `AttackRaise.cpp`, `AttackSpeed.cpp`, `SharedConfig.cpp`, and all collision diagnostic `.cpp` files.
5. Verify the production target defines no collision diagnostic compile macro.
6. Verify `prototypes/Script_FrameCollisionTest/` is unchanged.
7. Verify no hook address/RVA or hook type changed in migrated files.
8. Run `git diff --check` or equivalent static whitespace validation.
9. Inspect the final diff against this contract.

Do not build, configure, generate, or run anything.

## 10. Stop conditions

STOP and report instead of broadening if:

- any migrated behavior file appears to require semantic edits;
- exact-copy migration exposes a missing production dependency requiring architectural choice;
- release compilation would require diagnostic implementation/state;
- hook ownership would need to change;
- old Raise/Speed code must be changed to make collision migration work;
- a New Balance / AttackCollision compatibility change appears necessary;
- implementation would require touching files outside §8;
- the migration cannot be explained as exact behavior-core promotion plus entry/build adaptation.

## 11. Publication

Publication to:

```text
repository: tcholti/Gothic3_Animation_Behaviors
branch: docs/collision-source-evidence
```

is authorized for this bounded task after the source/static audit passes.

The launcher will provide the exact required remote HEAD containing this frozen task. Verify it before editing.

## 12. Required handoff

Report only:

```text
Task document: docs/work/active/PRODUCTION_COLLISION_CORE_MIGRATION.md
Responsibility complete: YES/NO
Files added/changed
Exact parity check result for migrated behavior files
Production target source/exclusion summary
Prototype unchanged: YES/NO
Static checks
Build: NOT ATTEMPTED — Work build execution was not authorized for this task.
Material contradiction: NONE / exact issue
Final remote implementation SHA
```

Then STOP. Do not archive this task document; Normal Chat owns independent review and closure.

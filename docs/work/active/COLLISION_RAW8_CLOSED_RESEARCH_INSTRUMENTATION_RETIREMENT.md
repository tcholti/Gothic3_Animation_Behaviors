# Gothic 3 — Raw8 Closed Research Instrumentation Retirement

**Status:** ACTIVE — BOUNDED DIAGNOSTIC-CLEANUP IMPLEMENTATION TASK  
**Opened:** 2026-09-20  
**Evidence basis:** EV-347–EV-349 + collision-vs-damage drift audit  
**Production behavior change:** PROHIBITED  
**Work build execution:** PROHIBITED

## Repository

`https://github.com/tcholti/Gothic3_Animation_Behaviors.git`

Branch:

`docs/collision-source-evidence`

Required base HEAD:

`c7706b7c66812cf0fc31b84a24b5a77bb6e38262`

## Read first

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. this document
4. `docs/work/active/COLLISION_RAW8_FIST_AUTHORING_SEMANTICS_REVIEW.md`
5. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
6. `docs/FEATURE_DEVELOPMENT_METHOD.md`
7. `docs/COLLISION_DIAGNOSTICS.md`
8. `docs/SOURCE_HOOK_GUIDE.md`

Then inspect only the exact source required by this frozen cleanup contract.

## Why this cleanup exists

EV-347–EV-349 used two temporary raw8 diagnostics/research mechanisms:

1. the post-attempt observation scope in permanent `Raw8FistCollision` source, compiled only under `FRAME_COLLISION_DIAGNOSTICS`;
2. the temporary diagnostic-only `Raw8FistWindowProbe`, which used an `ExactNativeDamageObserved` research classifier to gate the EV-348 latch-rearm causal intervention.

Those experiments are closed.

The collision-vs-damage drift audit established:

- permanent collision behavior did **not** drift into HP-damage ownership;
- the damage-correlated logic is confined to closed diagnostic/research instrumentation;
- collision authoring owns collision/contact opportunity and lifecycle only;
- gameplay block/parry/immunity/reaction/HP damage remain Gothic/behavior-owned;
- historical `OnDamage` evidence remains valid provenance but must not remain active raw8 policy scaffolding.

Before new causal research, restore the diagnostic twin to a neutral baseline.

## Single responsibility

Retire the **closed raw8 damage-correlated research instrumentation** and nothing else.

After this task:

- no `Raw8FistWindowProbe` source, state, bridge delegation or CMake inclusion remains;
- no raw8 post-attempt observation scope/counting remains in `Raw8FistCollision`;
- no `CORE RAW8_FIST_POST_ATTEMPT` logger implementation/declaration remains;
- the generic diagnostic `ENTITY_ON_DAMAGE_ENTRY` hook/logger remains available as contextual factual observation only;
- permanent raw8 marker ownership/latch/timing behavior is byte-for-byte semantically unchanged;
- behavior-only twin remains behaviorally unchanged.

## Exact removals

### A. Remove temporary window probe

Delete:

```text
prototypes/Script_FrameCollisionTest/Raw8FistWindowProbe.cpp
prototypes/Script_FrameCollisionTest/Raw8FistWindowProbe.h
```

Remove from diagnostic CMake source list.

Remove only the corresponding `EngineBridge.cpp` diagnostic-only pieces:

- `#include "Raw8FistWindowProbe.h"`;
- `Raw8FistWindowProbe::ObserveTimingResult(...)`;
- `Raw8FistWindowProbe::InvocationScope`;
- `Raw8FistWindowProbe::BeginInvocation(...)`;
- `Raw8FistWindowProbe::CompleteInvocation(...)`;
- `Raw8FistWindowProbe::ObserveOnDamage(...)`.

Restore the raw8 timing wrapper to simply return the permanent `Raw8FistCollision::ApplyTimingPermission(...)` result in both products.

### B. Remove closed EV-347 post-attempt observer

From `Raw8FistCollision.h/.cpp`, remove only the `FRAME_COLLISION_DIAGNOSTICS` post-attempt research API/state:

- `PostAttemptObservationScope`;
- `BeginPostAttemptObservation`;
- `ObservePostAttemptOnDamageEntry`;
- `CompletePostAttemptObservation`;
- its thread-local scope pointer and associated diagnostic-only bookkeeping.

From `EngineBridge.cpp`, remove only:

- `Raw8FistCollision::PostAttemptObservationScope`;
- `BeginPostAttemptObservation(...)`;
- `CompletePostAttemptObservation(...)`;
- `ObservePostAttemptOnDamageEntry(...)`.

From `CollisionDiagnostics.h/.cpp`, remove only:

- `LogRaw8FistPostAttempt(...)`;
- the `CORE RAW8_FIST_POST_ATTEMPT` emission.

## Must remain

Do **not** remove or alter:

- permanent `Raw8FistCollision::UpdateMarkerOwnership`;
- permanent `ApplyAcceptedMarkerLatch`;
- permanent `UpdateTimingPermissionFromMarker`;
- permanent `ApplyTimingPermission`;
- raw8 timing/latch diagnostics such as ownership, opportunity, permission-consumed and permission-retired logging;
- generic diagnostic `Hook_EntityOnDamage`;
- generic `g_EntityOnDamageEntryOrdinal`;
- generic `CollisionDiagnostics::LogEntityOnDamageEntry` / cap logging;
- raw55 diagnostics or behavior;
- equipped collision / equipped Sprint;
- lifecycle guard;
- production integration under `src/Script_G3AnimationBehaviors`.

The generic `ENTITY_ON_DAMAGE_ENTRY` logger is retained because it is a neutral observation surface used to correlate Gothic events. Its presence must not drive collision behavior.

## Protected behavior

This task must not:

- add any new hook;
- add any new state or policy;
- change any latch write;
- change any timing return value;
- change marker recognition or ownership;
- change collision groups;
- clear any trigger lists;
- change C1 lifecycle/finalization;
- change raw55;
- change equipped weapon behavior;
- change Sprint behavior;
- add or remove FIST/FIST_OFF semantics;
- implement the persistent raw8 opportunity redesign;
- reinterpret `Game+0x16E348` as the production consumption boundary.

This is cleanup only.

## Expected changed files

The narrow expected set is:

```text
prototypes/Script_FrameCollisionTest/CMakeLists.txt
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
prototypes/Script_FrameCollisionTest/Raw8FistCollision.cpp
prototypes/Script_FrameCollisionTest/Raw8FistCollision.h
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
DELETE prototypes/Script_FrameCollisionTest/Raw8FistWindowProbe.cpp
DELETE prototypes/Script_FrameCollisionTest/Raw8FistWindowProbe.h
```

If faithful cleanup requires broader source changes, STOP and report the contradiction.

## Static verification

Before publication, verify at minimum:

- no `Raw8FistWindowProbe` references remain;
- no `PostAttemptObservationScope` references remain;
- no `ObservePostAttemptOnDamageEntry` references remain;
- no `RAW8_FIST_POST_ATTEMPT` emission remains;
- generic `ENTITY_ON_DAMAGE_ENTRY` hook/logging remains;
- permanent raw8 latch/timing source is otherwise unchanged;
- behavior-only source set remains unchanged;
- `git diff --check` passes.

## Build / publication

Work build execution is **PROHIBITED**.

The User explicitly authorizes publication of this bounded cleanup implementation to:

- repository: `tcholti/Gothic3_Animation_Behaviors`
- branch: `docs/collision-source-evidence`

Perform source/static checks only.

## Required report

Report:

- final remote commit SHA;
- parent SHA;
- changed/deleted files;
- concise cleanup result;
- confirmation generic `ENTITY_ON_DAMAGE_ENTRY` diagnostics remain;
- confirmation permanent raw8 behavior is unchanged;
- confirmation behavior-only twin source set is unchanged;
- source/static checks;
- `Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`;
- any material contradiction.

Then STOP.

# Gothic 3 — Final C1 Metadata Retirement Cleanup

**Status:** ACTIVE — FROZEN BOUNDED IMPLEMENTATION  
**Opened:** 2026-09-21  
**Finding source:** archived final source-quality audit B-01  
**Behavior change intent:** NONE — metadata lifetime correction only  
**Work build execution:** PROHIBITED

## Responsibility

Implement only generation-qualified retirement of C1-scoped metadata/state that currently survives after its exact C1 has finalized.

This cleanup exists to make permanent state lifetime match factual C1 lifetime before the expensive final validation campaign.

It must **not** change marker semantics, equipped Sprint semantics, raw55 semantics, physical collision cleanup, latch behavior or generic lifecycle policy.

## Read first

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. this document
4. `docs/archive/investigations/COLLISION_FINAL_SOURCE_QUALITY_MODULARITY_AUDIT.md`
5. `docs/DESIGN.md`
6. `docs/COLLISION_LIFECYCLE.md`
7. `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`
8. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`

Then inspect only the exact source required by this contract.

## Exact accepted finding

The following records are factual per-C1 state/metadata but currently retire only opportunistically when a later generation is observed:

```text
FrameCollisionMarkers:
  g_LastAcceptedMarkerDispatchByActor
  g_MarkerExecutionBudgetByActor

EquippedSprintCollision:
  g_BoundSprintExecutionByActor

PhysicalFistCollision:
  g_Executions
```

They are generation-checked before use, so this is **not a demonstrated behavior bug**. The issue is stale execution metadata/raw-pointer/string retention after factual C1 end and lifetime broader than the state contract.

Do not alter `g_MarkerOwnedWindowByActor` in this task; its physical marker-window lifetime is already tied to source retirement/cleanup and was not part of the accepted audit finding.

## Required architecture

`EngineBridge` remains the sole AISetState hook owner.

Each feature owner must expose the smallest metadata-retirement API required for its own state. The bridge may delegate the captured finalization generation to those owners at the existing post-native AISetState finalization seam.

Do not move feature state into `CollisionLifecycleGuard`.

Do not create a generic registry/observer framework.

### Generation safety

Retirement must be exact and generation-qualified:

```text
captured finalization token actor + generation
-> owner finds actor record
-> erase ONLY if stored record belongs to captured generation
-> if stored record already belongs to a replacement generation, leave it untouched
```

The APIs must perform metadata/state erasure only.

No:
- collision-group write;
- raw8 latch write;
- raw55 group mutation;
- marker activation/deactivation;
- native call;
- source repair.

### Ordering

Use the existing post-native AISetState seam. Preserve all existing native/original ordering.

The existing permanent raw8 generation-safe finalization remains unchanged.

The generic `CollisionLifecycleGuard::FinalizeAfterAISetState` remains the lifecycle/physical-repair authority and remains unchanged.

The new metadata retirement may occur only at the bounded post-native finalization seam and must not create another hook.

## Exact source scope

Expected files only:

```text
MODIFY prototypes/Script_FrameCollisionTest/EngineBridge.cpp

MODIFY prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.cpp
MODIFY prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.h

MODIFY prototypes/Script_FrameCollisionTest/EquippedSprintCollision.cpp
MODIFY prototypes/Script_FrameCollisionTest/EquippedSprintCollision.h

MODIFY prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
MODIFY prototypes/Script_FrameCollisionTest/PhysicalFistCollision.h
```

If faithful implementation requires any other file or behavior change, STOP and report the contradiction.

## Protected behavior

Do not change:
- marker scan/acceptance/dedupe rules;
- authored occurrence budgets;
- generic RIGHT/LEFT/BOTH/OFF semantics;
- marker-owned physical windows;
- equipped Sprint eligibility/binding/Action9 -> same-C1 Action2 policy;
- raw55 eligibility, suppression, FIST activation/rearm or Normal clear suppression;
- raw8 code/state/finalization;
- `CollisionLifecycleGuard`;
- source resolution/mutation;
- diagnostics;
- CMake/hook installation.

## Static verification

Verify:
- exact seven-file scope;
- only generation-qualified metadata/state erasure added;
- replacement-generation records are protected;
- no physical mutation added to retirement APIs;
- no new hook;
- AISetState original call order unchanged;
- raw8 finalization unchanged;
- generic lifecycle finalization/repair unchanged;
- no marker/raw55/Sprint decision changes;
- `git diff --check` PASS.

## Build / publication

Work build execution is PROHIBITED.

The User authorizes publication of this bounded cleanup to branch `docs/collision-source-evidence`.

## Required report

Report:
- final remote commit SHA;
- parent SHA;
- exact changed files;
- exact retirement APIs/delegation order;
- proof that erasure is generation-qualified and metadata-only;
- static checks;
- `Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`;
- material contradiction, if any.

Then STOP.

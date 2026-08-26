# Session Entry Point

**Purpose:** Minimal durable handoff for any new Chat or Work session. Read this first; open deeper project files only as needed.

**Branch:** `docs/collision-source-evidence`  
**Updated:** 2026-08-26

For the role and authority of the broader documentation set, see `docs/README.md`.

## Where We Are

Frame-controlled weapon collision is the active subsystem. The validated RIGHT/LEFT/BOTH/OFF marker core is established. `G3AB_COL_OFF` is **optional authored early shutoff**, never the general end-of-Hit safety mechanism.

Full Whirl/block-timeout testing exposed a native lifecycle defect: weapon collision can remain `Item_Attack` after the relevant attack lifecycle fails to clean normally. The defect is not marker-created and is broader than Staff Whirl; native Dual Quick also produced a later `7 -> 7` attack request from an already-stale source.

Recover is not the universal cleanup owner.

## v0.20 Finding That Changed the Design

`Script_FrameCollisionTest v0.20` proved action/phase is not a reliable lifetime owner after a Hit has begun: a 2H Whirl drifted from action 10 to Stand/action 0 while the exact Whirl Hit remained the live PrimaryFirst/current motion at about `0.611 / 0.800 s`.

Actual motion execution is therefore the preferred lifetime authority after acquisition, pending a better event-driven motion-lifecycle hook.

## Preferred Cleanup Architecture

**Prefer System 1: execution-level native cleanup guard.**

- acquire a real attack-Hit execution using native semantics;
- capture the exact actual motion execution;
- marked motion: suppress native timed activation and let markers control activation/rearm;
- unmarked motion: leave native activation untouched;
- if the execution requests offensive collision, remember the execution-level fact `collision requested`, including `7 -> 7`;
- follow the actual Hit execution until it genuinely ends/replaces;
- if Gothic 3 already performed proper native cleanup, do nothing;
- if it did not, invoke the native cleanup Gothic 3 should have performed;
- do not create separate cleanup branches for block timeout, Recover, Staff, Quick, Whirl, damage, terrain, etc. unless evidence proves the universal rule insufficient.

**System 2 is fallback only:** track/repair individual physical sources if cleanup proves genuinely source-specific or capable of partial independent failure.

Complete System 1/System 2 diagrams and hypotheses are in `docs/COLLISION_LIFECYCLE_PLAN.md`.

## Marker Rule While Hit Is Alive

Markers define the complete desired offensive collision set:

```text
RIGHT = {RIGHT}
LEFT  = {LEFT}
BOTH  = {RIGHT, LEFT}
OFF   = {}
```

Conceptually: make offensive collision equal to the authored desired set. This is separate from end-of-Hit cleanup.

## Step A Modularization Status

The v0.20 source modularization is committed and pushed at:

`325c98e725502229bf796083e52c0fa977803cc0` — `Modularize frame collision research DLL`

The single research DLL now has separated source responsibilities:

- `Script_FrameCollisionTest.cpp` — main/bootstrap and authoritative hook bridge;
- `CollisionControl.cpp/.h` — collision behavior and behavioral state;
- `CollisionDiagnostics.cpp/.h` — logging and observational state;
- `FrameCollisionShared.h` — shared factual structures/enums;
- `HookBridgeRuntime.cpp/.h` — shared high-resolution timing;
- `CMakeLists.txt` — includes all modules in the same DLL.

All six hooks remain owned/installed exactly once by the main hook bridge:

- `OnAI_Attack`;
- `OnAI_QuickAttack`;
- `OnAI_WhirlAttack`;
- `OnTick`;
- `StartEffect`;
- `eCEntity::SetCollisionGroup`.

**Important:** this is source-level completion only. No compile, DLL-load, or Gothic 3 runtime parity test has yet been performed because the commit was made away from the authoritative home development PC.

Do not call Step A validated until the home-PC parity gate passes.

## Current Code Still Provisional

Modularization intentionally preserved v0.20 behavior/scaffolding. Do not assume these mechanisms belong in the final cleanup design:

- `MarkerOwnedCollisionWindow` as lifetime owner;
- strict source + animation + action + phase matching for ownership lifetime;
- `MarkerWindowStillMatchesActorExecution(...)`;
- `RetireMarkerOwnedSource(...)` as source-by-source lifetime retirement;
- action/phase as a continuing marker-time veto after execution acquisition;
- interruption-specific cleanup contingencies.

Preserve unrelated proven marker behavior until separate evidence says otherwise: RIGHT/LEFT/BOTH exact-set switching, repeated-marker rearm, optional OFF, replay/dedup/occurrence guards, and marked-motion native callback suppression.

## Chat / Work Execution Model

`docs/WORK_IMPLEMENTATION_PROTOCOL.md` is the execution contract.

Default workflow:

```text
Chat: design / evidence / freeze one code task
        ↓
Work: bounded source change + source review + commit/push + STOP
        ↓
Chat + home PC: sync / build / runtime test / interpret logs
        ↓
Chat: update evidence/docs and choose the next change
```

Work is primarily a scarce coding/refactor resource. Routine build verification, runtime tests, log interpretation, documentation, and next-step planning stay in Chat/local testing by default unless a particular coding problem explicitly requires Work to do them.

## Immediate Next Step — NOT a Work Coding Task Yet

On the home PC:

1. synchronize `docs/collision-source-evidence`;
2. configure/build `Script_FrameCollisionTest`;
3. resolve only concrete compile/link issues if any;
4. verify DLL load/hook installation;
5. run focused v0.20 behavior/diagnostic parity checks;
6. bring build/runtime output and logs back to Chat for interpretation.

Only after Step A parity passes should we freeze the bounded Step B diagnostic redesign and send that code task to Work.

Do **not** implement production collision cleanup yet.

## Read Order for the Next Work Coding Task

When another code task is explicitly assigned, Work should read:

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
3. `docs/ENGINEERING_GUIDE.md`
4. `docs/COLLISION_LIFECYCLE_PLAN.md`
5. the specific current implementation plan, e.g. `docs/COLLISION_LOGGER_PLAN.md`
6. only the relevant modular source files
7. `docs/SOURCE_HOOK_GUIDE.md` only as needed.

Deeper evidence should be opened only when the current question requires it.

Keep this file short. Update it when the active problem, chosen model, validated checkpoint, or immediate next step materially changes.

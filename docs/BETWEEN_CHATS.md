# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest handoff

**From:** Normal Chat  
**To:** Work  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

## Task — Step B1 PrimaryFirst Event Probe

Step A modularization is validated. Do not revisit or broaden it.

Read only what is needed for this bounded task:

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
3. `docs/COLLISION_LOGGER_PLAN.md`
4. `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
5. `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp/.h`
6. official SDK headers for `eCVisualAnimation_PS`, `eCWrapper_emfx2Actor`, and `eCEntityPropertySet` as needed.

### Implement

Add **diagnostic-only** hooks, owned exactly once by the existing main/hook bridge, for:

- `eCVisualAnimation_PS::PlayMotion` — `RVA_Engine(0x30860)`;
- `eCVisualAnimation_PS::StopMotion` — `RVA_Engine(0x30980)`.

Requirements:

- observe/log only motion type `0`, the validated PrimaryFirst slot;
- use `eCVisualAnimation_PS::GetEntity()` to identify the owning entity/actor where available;
- capture a compact PrimaryFirst snapshot immediately **before** the original function and immediately **after** it;
- reuse/refactor the existing diagnostic snapshot code rather than creating a second independent definition of PrimaryFirst state;
- useful snapshot fields are: motion name, has-motion-instance, running, play time, max time, play speed; action/phase/current movement may be logged only as context where readily available;
- distinguish PlayMotion request/result from StopMotion request/result in the log;
- keep the existing v0.20 `OnTick` PrimaryFirst lifetime probe unchanged as a temporary comparator;
- preserve all collision-control behavior exactly.

### Do not add

- production cleanup;
- new collision-control decisions;
- lifecycle ownership/correlation tables;
- new persistent execution state merely for this probe;
- Quick/Whirl/Staff/block-specific behavior;
- `StopAtLoopEnd` hook in this first probe;
- wrapper-level `eCWrapper_emfx2Actor::PlayMotion/StopMotion` hooks unless source/API evidence proves the requested high-level hooks cannot observe the needed events.

Source evidence already established that `StopAtLoopEnd` schedules a future loop stop rather than representing an actual end event, so it is intentionally excluded from this probe.

### Scope and stop condition

This task tests whether the high-level PrimaryFirst motion events can replace polling later. It does **not** decide that question in code.

If the specified high-level hook signatures/RVAs cannot be used cleanly, STOP and report the concrete contradiction rather than adding a broader interception architecture.

Do not build or run Gothic 3 in Work. Normal Chat/home PC owns compilation and runtime validation.

### Finish

When source implementation/review is complete:

1. commit and push to `docs/collision-source-evidence`;
2. overwrite this file with a concise report containing changed files, hook ownership, logged event fields, preserved behavior, unresolved source/API issues, and commit SHA;
3. STOP. Do not proceed to broader lifecycle diagnostics or cleanup.

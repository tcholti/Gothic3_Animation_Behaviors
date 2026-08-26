# Session Entry Point

**Purpose:** Minimal durable handoff for any new Chat or Work session. Read this first; open deeper project files only as needed.

**Branch:** `docs/collision-source-evidence`  
**Updated:** 2026-08-26

For document roles and authority, see `docs/README.md`. For the latest Chat/Work bridge, see `docs/BETWEEN_CHATS.md`.

## Active Subsystem

Frame-controlled melee collision lifecycle.

The RIGHT/LEFT/BOTH/OFF marker core is established. `G3AB_COL_OFF` is optional authored early shutoff inside a live Hit; it is not the general end-of-Hit safety mechanism.

Known native lifecycle defect: offensive weapon collision can remain `Item_Attack` after a Hit is replaced/interrupted without normal cleanup. This is not marker-created and is broader than Staff Whirl; Dual Quick has also reproduced stale carryover and later `7 -> 7` activation.

Recover is not the universal cleanup owner.

## Preferred Cleanup Model

Prefer **System 1: execution-level native cleanup guard**.

For every real attack-Hit execution that requests offensive collision:

1. acquire the real Hit using native action/phase/callback semantics;
2. capture the exact actual motion execution;
3. marked motion: markers own activation timing;
4. unmarked motion: Gothic 3 keeps native activation timing;
5. remember that offensive collision was requested, including `7 -> 7`;
6. follow the exact actual Hit execution rather than action/phase after acquisition;
7. when that Hit actually ends or is replaced, determine whether proper native cleanup occurred;
8. if yes, do nothing; if no, invoke the native cleanup Gothic 3 should have performed.

Use **System 2 source-aware cleanup only if evidence proves cleanup is genuinely source-specific or partially independent**.

Detailed architecture: `docs/COLLISION_LIFECYCLE_PLAN.md`.

## Marker Rule While Hit Is Alive

```text
RIGHT = {RIGHT}
LEFT  = {LEFT}
BOTH  = {RIGHT, LEFT}
OFF   = {}
```

Each marker defines the complete desired offensive collision set.

## Step A — VALIDATED

Commit:

`325c98e725502229bf796083e52c0fa977803cc0` — `Modularize frame collision research DLL`

The research DLL remains one DLL with one owner for each hook, split into:

- `Script_FrameCollisionTest.cpp` — bootstrap / hook bridge;
- `CollisionControl.cpp/.h` — behavior and behavioral state;
- `CollisionDiagnostics.cpp/.h` — observational diagnostics;
- `FrameCollisionShared.h` — shared facts/results/enums;
- `HookBridgeRuntime.cpp/.h` — shared high-resolution timing.

Home-PC validation on 2026-08-26:

- MSVC Release build succeeded;
- built and installed DLL SHA-256 matched: `4CD111D0B92A562AD8831BA81FA00C6E8A29BE5EC3F66E5920D6B214F99553DD`;
- Gothic 3 loaded and ran without crash;
- smoke test covered marked Normal/Quick/Whirl across 2H, Staff, and Dual/1H+1H;
- marker ownership, `SetCollisionGroup`, Quick/Whirl `StatePosition`, source resolution, and PrimaryFirst lifetime diagnostics remained present;
- known stale-lifecycle behavior remained reproducible, as expected because Step A intentionally changed structure only.

Evidence log:

`research/raw/2026-08-26_framecollision_modular_v0.20_parity_smoke.log` (may be moved to `research/archive/` after processing).

Conclusion: **Step A behavior-parity gate passed for the intended structural refactor.**

## Current Code Still Provisional

The modular refactor intentionally preserved v0.20 scaffolding. Do not assume these belong in the final design:

- `MarkerOwnedCollisionWindow` as lifetime owner;
- strict source + animation + action + phase matching for ownership lifetime;
- `MarkerWindowStillMatchesActorExecution(...)`;
- `RetireMarkerOwnedSource(...)` as source-by-source lifetime retirement;
- action/phase as continuing marker-time veto after execution acquisition;
- interruption-specific cleanup contingencies.

Preserve proven marker behavior until evidence says otherwise: source-explicit markers, exact-set switching, rearm, optional OFF, replay/dedup/occurrence protection, and marked-motion native callback suppression.

## Chat / Work Execution Model

```text
Chat: design / evidence / freeze one bounded code task
        ↓
Work: source implementation/refactor + targeted review + commit/push + STOP
        ↓
Chat + home PC: sync / build / runtime test / interpret logs
        ↓
Chat: update evidence/docs and choose next code task
```

Routine build verification, runtime testing, log interpretation, documentation, evidence consolidation, and next-step planning stay in Chat/local testing by default.

## Immediate Next Step

Do **not** implement production cleanup yet.

Next phase is Step B: redesign lifecycle diagnostics around the smallest questions required to choose System 1 or System 2.

Before sending any code task to Work, normal Chat should:

1. archive processed raw logs so active context stays small;
2. review `docs/COLLISION_LOGGER_PLAN.md` against the now-modular source;
3. freeze the smallest bounded diagnostic change;
4. write that assignment into `docs/BETWEEN_CHATS.md`;
5. only then send Work the bounded Step B code task.

Keep this file short. Update it only when the active problem, validated checkpoint, or immediate next step materially changes.

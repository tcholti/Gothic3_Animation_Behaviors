# Session Entry Point

**Purpose:** Minimal durable handoff for any new Chat or Work session. Read this first; open deeper project files only as needed.

**Branch:** `docs/collision-source-evidence`  
**Updated:** 2026-08-26

## Where We Are

Frame-controlled weapon collision is the active subsystem. The validated RIGHT/LEFT/BOTH/OFF marker core is established. `G3AB_COL_OFF` is **optional authored early shutoff**, never the general end-of-Hit safety mechanism.

Full Whirl/block-timeout testing exposed a native lifecycle defect: weapon collision can remain `Item_Attack` after the relevant attack lifecycle fails to clean normally. The defect is not marker-created and is broader than Staff Whirl; native Dual Quick also produced a later `7 -> 7` attack request from an already-stale source.

Recover is not the universal cleanup owner.

## v0.20 Finding That Changed the Design

`Script_FrameCollisionTest v0.20` is read-only. It proved action/phase is not a reliable lifetime owner after a Hit has begun: a 2H Whirl drifted from action 10 to Stand/action 0 while the exact Whirl Hit remained the live PrimaryFirst/current motion at about `0.611 / 0.800 s`. The strict action/phase marker gate then rejected later markers that still belonged to that surviving Hit.

Actual motion execution is therefore the preferred lifetime authority after acquisition, pending a better event-driven motion-lifecycle hook.

## Preferred Cleanup Architecture

**Prefer System 1: execution-level native cleanup guard.**

- acquire a real attack-Hit execution using native semantics;
- capture the exact actual motion execution;
- marked motion: suppress native timed activation and let markers control activation/rearm;
- unmarked motion: leave native activation untouched;
- if the execution requests offensive collision, remember the execution-level fact `collision requested` (including `7 -> 7` requests);
- follow the actual Hit execution until it genuinely ends/replaces;
- if Gothic 3 already performed proper native cleanup, do nothing;
- if it did not, invoke the native cleanup Gothic 3 should have performed;
- do not create separate cleanup branches for block timeout, Recover, Staff, Quick, Whirl, damage, terrain, etc. unless evidence proves the universal rule insufficient.

**System 2 is fallback only:** track/repair individual physical sources if cleanup proves genuinely source-specific or capable of partial independent failure.

Exact flow diagrams are in `docs/COLLISION_LIFECYCLE_MODELS.md`.

## Marker Rule While Hit Is Alive

Markers define the complete desired offensive collision set:

```text
RIGHT = {RIGHT}
LEFT  = {LEFT}
BOTH  = {RIGHT, LEFT}
OFF   = {}
```

Conceptually: make offensive collision equal to the authored desired set. This is separate from end-of-Hit cleanup.

## Current Code to Treat as Provisional

Do not delete yet, but do not assume these v0.20 cleanup/lifetime mechanisms belong in the next production design:

- `MarkerOwnedCollisionWindow` as lifetime owner;
- strict source + animation + action + phase matching for ownership lifetime;
- `MarkerWindowStillMatchesActorExecution(...)`;
- `RetireMarkerOwnedSource(...)` as source-by-source lifetime retirement;
- action/phase as a continuing marker-time veto after execution acquisition;
- any new interruption-specific cleanup contingencies.

Preserve unrelated proven marker behavior: RIGHT/LEFT/BOTH desired-set switching, repeated-marker rearm, optional OFF, replay/dedup/occurrence guards, and marked-motion native callback suppression.

## Research DLL / Diagnostics Decision

Keep collision behavior and collision-lifecycle diagnostics in **one research DLL while they need overlapping Gothic 3 hooks**.

Do not create a second independent logger DLL that competes for the same hook addresses unless explicit hook-chaining safety is later proven.

Instead redesign `Script_FrameCollisionTest` as a multi-file DLL with one authoritative hook owner and separate responsibilities:

```text
Main / Hook Bridge
    installs each engine hook once
        ├──> Collision Control
        └──> Collision Diagnostics
```

Intended source separation is approximately:

- Main/Hook Bridge — `ScriptInit`, shutdown, shared engine-hook installation/dispatch;
- `CollisionControl.cpp` — behavior only;
- `CollisionDiagnostics.cpp` — observational logging only;
- small shared header/event structures only where genuinely needed.

**Dependency rule:** collision behavior must not depend on diagnostics. Removing the diagnostic source from a build must leave collision behavior unchanged.

This structure is deliberate preparation for later extraction. After research is complete, stable collision behavior can be built into a production DLL (final name to be chosen later) without carrying the diagnostic module or rewriting the behavior architecture.

`Script_CombatMoveLogger v0.4` remains a separate proven combat-move/speed tool and should not be expanded automatically into the collision logger.

Detailed diagnostic/module plan: `docs/COLLISION_LOGGER_PLAN.md`.

## Work Coding Discipline

`docs/WORK_IMPLEMENTATION_PROTOCOL.md` is the execution contract for the next coding session.

It defines:

- **behavior integrity** — anything outside the explicitly targeted change must remain semantically unchanged;
- principle-first implementation rather than symptom-by-symptom fixes;
- one runtime hook owner with modular source responsibilities;
- smallest-sufficient state/model;
- deliberate resource use regardless of available compute/context/tool capacity;
- explicit stop conditions when implementation starts growing beyond what the agreed model can explain;
- required evidence/handoff after each meaningful step.

A Work session may challenge the design when engine/API evidence contradicts it. It must not silently replace the design with accumulated compensating code.

## Test Sequence

The staged tests are in `docs/COLLISION_TEST_PLAN.md`.

Do not begin with a huge combat matrix. First prove the redesigned diagnostic module can show one clean lifecycle and one stale lifecycle clearly. Then test whether legitimate native collision ever survives one physical Hit into the next, interruption convergence, block/parade behavior, marked/native convergence, and only then broaden across weapon/action families and NPCs.

## Immediate Next Coding Step

The next Work/code task should be:

1. **modularize the existing `Script_FrameCollisionTest` DLL without changing v0.20 behavior**;
2. keep each overlapping hook installed once;
3. separate collision behavior from diagnostic output;
4. build/test parity with the current v0.20 behavior;
5. only after parity, add the lifecycle diagnostic events required by `docs/COLLISION_LOGGER_PLAN.md`.

Do **not** implement production collision cleanup yet.

A new Work chat should read, in this order:

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
3. `docs/ENGINEERING_GUIDE.md`
4. `docs/COLLISION_LIFECYCLE_PLAN.md`
5. `docs/COLLISION_LIFECYCLE_MODELS.md`
6. `docs/COLLISION_LOGGER_PLAN.md`
7. `docs/COLLISION_TEST_PLAN.md`
8. `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
9. `prototypes/Script_FrameCollisionTest/CMakeLists.txt`
10. `tools/Script_CombatMoveLogger/Script_CombatMoveLogger.cpp` only as a reference for proven diagnostic patterns
11. `docs/SOURCE_HOOK_GUIDE.md` only as needed for hook/source research

Work should first check whether the modular single-DLL plan can preserve each current hook and v0.20 behavior cleanly. If engine/API evidence contradicts the plan, report the contradiction rather than silently adding a more complicated architecture.

## Deeper Evidence Only As Needed

- `research/raw/2026-08-25_framecollision_v0.20_player_staff_2h_dual_block_timeout_*.log`
- `docs/HANDOFF.md`
- `docs/RESEARCH_MAP.md`
- `docs/EVIDENCE_LEDGER.md`
- pinned Jackydima SDK/reference source

Keep this file short. Update it when the active problem, chosen model, or immediate next step materially changes.

# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Work result — C1-O2 RunScriptFunction pure pass-through isolation

**Date:** 2026-08-29
**Branch:** `docs/collision-source-evidence`
**Implementation commit:** `089817a4e7a5a0baab2c7cba0540aa31d6f17726`
**Crash-evidence base:** `2319bc09661520e7237eb956921632854e37cbaf`

Implemented only the frozen isolation:

- retained the explicit `gCScriptAdmin *this` wrapper signature and recursion-safe `.Prepare(...).ThisCall().Hook()` installation;
- reduced `RunScriptFunction_FrameCollisionTest` to one return statement that invokes Gothic's original exactly once with `this`, script name, runtime stack and SPU unchanged;
- removed all C1-O2 dispatch capture and completion/retirement calls from this wrapper only;
- changed only the C1-O2 startup banner to identify the pure pass-through isolation build.

Changed files:

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`

Source audit passed:

- the wrapper contains no operation before or after the original call except returning its exact result;
- it calls neither `BeginScriptFunctionDispatch` nor `EndScriptFunctionDispatch`, and performs no logging, entity/SPU/stack access or collision work;
- `CollisionLifecycleGuard` remains compiled but is unreachable from RunScriptFunction in this isolation build;
- CombatMove, AISetState, SetCollisionGroup, marker/callback, C1 generation/source-obligation, collision and physical-repair semantics are unchanged;
- no unrelated diagnostic, classifier, fallback, timer, polling, scan or refactor was added;
- `git diff --check` passed.

Contradictions / stop conditions: none.

Gothic 3 was not built or run. The isolated runtime result must determine whether direct RunScriptFunction detouring remains viable.

No further Work task is frozen here. STOP.

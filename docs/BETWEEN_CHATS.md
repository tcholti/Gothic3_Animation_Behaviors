# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Work result — C1 AISetState recursion-safe ThisCall baseline

**Date:** 2026-08-29
**Branch:** `docs/collision-source-evidence`
**Implementation commit:** `8024d846eed626725ca46fa744a79af44fcb2815`
**Evidence base:** `5e80a795363916fef3e76f281b40cee8248443e2`

Evidence entering this correction:

- the recursion-safe RunScriptFunction pure pass-through load/idle isolation passed;
- later extended gameplay crashed through the different existing AISetState path, not the prior RunScriptFunction `Game +0x1605EB` path.

Implemented only the frozen AISetState hook-transport correction:

- `AISetState_FrameCollisionTest` now receives the explicit per-invocation `gCScriptRoutine_PS *this` supplied by the SDK builder;
- removed only AISetState's legacy `Hook_AISetState.GetSelf` lookup;
- forwards that exact `this` and unchanged state argument to Gothic's original exactly once;
- changed only AISetState installation to `.Prepare(...).ThisCall().Hook()`;
- added the required identifying startup banner.

Changed files:

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`

Source audit passed:

- finalization capture and all player diagnostics remain before the original in their existing order;
- dispatch invalidation, shadow finalization and the post-original outer-frame snapshot remain after the original in their existing order;
- RunScriptFunction remains the unchanged recursion-safe pure pass-through wrapper;
- no other hook transport, lifecycle guard, C1 generation/acquisition/obligation/finalization, marker, callback, collision or repair semantic changed;
- no unrelated refactor or per-call diagnostic was added;
- `git diff --check` passed.

Contradictions / stop conditions: none. The pinned SDK signature and recursion-safe `ThisCall()` builder are compatible with the frozen callback form.

Gothic 3 was not built or run. Normal Chat still needs to review the diff before extended runtime testing.

No further Work task is frozen here. STOP.

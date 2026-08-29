# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Work result — C1-O2 RunScriptFunction ABI / recursion-safety correction

**Date:** 2026-08-29
**Branch:** `docs/collision-source-evidence`
**Implementation commit:** `52196a5fecf36187658c4f69d58b1ebe5b58b899`
**Crash-evidence base:** `7be5962f9073b2d889db5b040a5694014805555f`

Implemented only the frozen hook-transport correction:

- changed `RunScriptFunction_FrameCollisionTest` to receive the real `gCScriptAdmin *this` supplied by the pinned SDK's recursion-safe hook builder;
- forwards that exact `this` plus the unchanged script name, runtime stack and SPU to Gothic's original exactly once, preserving its result;
- replaced only this hook's legacy `mEHookType_ThisCall` installation with `.Prepare(...).ThisCall().Hook()`;
- changed the C1-O2 startup banner so the corrected build is distinguishable from the crashing build.

Changed files:

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`

Source audit passed:

- no RunScriptFunction `GetSelf`, `GetLastSelf`, `SetSelf` or legacy shared-this transport remains;
- the SDK builder stores each invocation's real ECX/this on that invocation's stack and restores it before the original call, so nested calls do not overwrite shared this state;
- the existing pre-original dispatch capture and post-original completion/retirement calls are unchanged;
- `CollisionLifecycleGuard`, HookBridge, collision control, C1 generation/acquisition/reuse/obligation/finalization semantics, markers, callbacks and physical collision behavior are unchanged;
- no classifier, fallback, timer, polling, scan, repair, unrelated diagnostic or refactor was added;
- `git diff --check` passed.

Contradictions / stop conditions: none. The pinned SDK `ThisCall()` builder safely represents the actual member signature.

Gothic 3 was not built or run. Normal Chat still needs to review the diff before build/load/runtime testing.

No further Work task is frozen here. STOP.

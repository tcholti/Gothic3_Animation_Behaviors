# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work. Replace rather than accumulate chronology.

## Frozen Work task — AIFullStop recursion-safe ThisCall transport

- Universal-guard-first architecture/current-state maintenance is published in commit `32fd1b353417c8baf4b3d5acfe2d07e61071052c`.
- C1-O2 direct `RunScriptFunction` dispatch capture remains suspended; `RunScriptFunction` stays recursion-safe pure pass-through.
- AISetState stays on its validated recursion-safe explicit-this `.ThisCall()` baseline.
- The next bounded Work task is an isolated transport-only correction for `gCScriptRoutine_PS::AIFullStop` in `Script_FrameCollisionTest`.
- Convert only AIFullStop from legacy shared `GetSelf` ThisCall transport to explicit per-invocation `gCScriptRoutine_PS *this`, forward that exact pointer to the original exactly once, and install the hook through the recursion-safe `.ThisCall()` builder.
- Preserve `_ReturnAddress`, caller/context stack capture, primary-motion snapshot, current-state/input/duration diagnostics and their pre-original ordering unchanged.
- Add only the identifying startup banner for this baseline.
- Do not change FullStop semantics, collision/lifecycle classification, C1 generation/obligation/finalization, marker behavior, physical repair, held-Use2/2500-ms behavior, AISetState, RunScriptFunction or any other legacy ThisCall hook.
- Work should edit only `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp` and `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`, source-audit, commit/push, report the source commit, and stop. No build or runtime test in Work.
- After Work returns, Normal Chat independently reviews the actual diff before any build/deploy/runtime step.
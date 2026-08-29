# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Work result — C1-O1 shadow outer ScriptFunction identity probe

**Date:** 2026-08-29
**Branch:** `docs/collision-source-evidence`
**Implementation commit:** `54a64552514f4d6795b4a51cbad7848b5df3795b`

### Implemented

- Added one reusable, stateless top-SPU-frame snapshot and logger using pinned SDK `gCScriptProcessingUnit::m_StateStack` / `gScriptRunTimeSingleState` fields.
- Logs `OUTER_FRAME OFFENSE` and `OUTER_FRAME CLEANUP` for exact currently equipped player sources after the existing SetCollisionGroup consequence sequence.
- Logs `OUTER_FRAME COMBAT_MOVE_INITIAL` for the existing non-FullStop initial-invocation condition using the supplied SPU.
- Logs player `OUTER_FRAME AI_SET_STATE_BEFORE` before original and `OUTER_FRAME AI_SET_STATE_AFTER` after original and the unchanged C1 finalization call.
- Records actor/source/group context, SPU/count, top index/address, script name/type, break block, raw arguments pointer, local callback, final float, CurrentState, Action, StatePosition and StateTime.
- Added the required C1-O1 startup banner.

### Protected behavior and source audit

- Top-entry address is explicitly diagnostic-only; `m_pArguments` is copied as a pointer value only and is never dereferenced or classified.
- No persistent identity state, map, cache, table, counter, classifier or ownership record was added.
- No hook was added. Existing AICombatMoveInstr, AISetState and SetCollisionGroup wrappers still call their originals exactly once and retain existing C1/marker/diagnostic ordering.
- No collision repair, C1 lifecycle-semantic change, marker/callback/bookkeeping change, OnTick change or production configuration was added.
- Only the three allowed diagnostic source files changed; the pinned SDK remained at `90bfd344de4510dda7ac9da7461cc7f1eac911f7`; `git diff --check` and targeted protected-scope/original-call audits passed.
- No source/API contradiction was found.

### Still required outside Work

- Independent diff-against-contract review.
- Build/load verification and the separately frozen C1-O1 runtime fixture.
- No build or Gothic 3 run was performed in Work, as required.

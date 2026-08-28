# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Current result — B9 implementation independently reviewed

**Date:** 2026-08-28  
**Branch:** `docs/collision-source-evidence`  
**B9 implementation:** `55e268901aaf06758cb5d88085c865457684992c`

### Independent Normal Chat review — PASS

- The implementation commit is exactly one commit after the frozen B9 contract and changes only the three expected diagnostic source files.
- One new player-only diagnostic hook is installed at tested `Game +0x164320 = gCScriptRoutine_PS::AISetState(bCString const&)` using the already-proven ThisCall hook pattern.
- The wrapper captures the requested state, immediate caller, 16-frame stack, current state/action/phase/StateTime/StatePosition/movement, PrimaryFirst, and equipped-source context before the original state replacement.
- The new diagnostic gate is player identity only; it does not classify or gate by attack family, input, action, phase, collision group, requested state, FullStop caller, or cleanup state.
- The original AISetState is called exactly once with the unchanged real argument and there is no post-call mutation.
- Existing B1–B7b diagnostics and collision/marker/callback/bookkeeping behavior were preserved; the implementation commit contains additions only.
- No forbidden production cleanup, lifecycle/pending state, timer/polling/scan/cache, ProcessScript/internal-SPU/call-site hook, classifier, or guessed layout was introduced.

### Next step

Build `Script_FrameCollisionTest` from the current branch. Do not deploy or run Gothic 3 until the build succeeds and Normal Chat gives the isolated deployment/load step.

After build/load verification, Normal Chat will freeze the exact B9 runtime fixture and raw filename.

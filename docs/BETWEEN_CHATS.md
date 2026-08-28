# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Current result — C1 shadow lifecycle guard independently reviewed

**Date:** 2026-08-28  
**Branch:** `docs/collision-source-evidence`  
**C1 implementation:** `3778517f421d07e940c620745bc7ccdf0da54313`

### Independent Normal Chat review — PASS

- The implementation is exactly one commit after the frozen C1 contract and changes only the five allowed implementation files: new `CollisionLifecycleGuard.h/.cpp`, `CMakeLists.txt`, `CollisionDiagnostics.cpp`, and `Script_FrameCollisionTest.cpp`.
- C1 lifecycle state is actor-generic; C1 log output remains player-focused to keep the controlled runtime log bounded.
- A candidate begins only on non-FullStop `sAICombatMoveInstr` with non-null args/SPU, snapshots exact equipped RIGHT/LEFT entities before original, attributes synchronous requests while candidate, and is persisted only on original `GEFalse`; immediate `GETrue` cancels the shadow candidate.
- Exact successful `Item_Attack` results create/refresh per-source obligations after the original SetCollisionGroup call. `7 -> 7` is intentionally counted. Actual transition out of `Item_Attack` fulfills that exact source obligation.
- FullStop/AIFullStop do not alter C1 ownership.
- AISetState captures only the actor/generation token before original, calls Gothic exactly once with the unchanged state argument, then evaluates after original. Generation mismatch is invariant-only; tracked clean sources no-op; outstanding group-7 sources still equipped log `WOULD_REPAIR`; outstanding group-7 sources no longer equipped log `UNRESOLVED_NOT_EQUIPPED`.
- Finalization retires only the shadow model. C1 contains no physical `SetCollisionGroup`, marker retirement, `ClearTriggeredList`, StatePosition, callback suppression, timer/polling/scan, new hook, family/action/state/input/caller classifier, or production configuration.
- Existing SetCollisionGroup physical call and marker-retirement ordering are preserved; the new C1 consequence observer runs afterward. Existing B1–B9 diagnostics remain intact.
- No source/API contradiction was found in independent review. Build is still required before deployment/runtime validation.

### Next step

Build `Script_FrameCollisionTest` from the current branch. Do not deploy or run Gothic 3 until the build succeeds and Normal Chat gives the isolated deployment/load step.

After build/load verification, Normal Chat will freeze the C1 shadow runtime matrix. Production repair remains disabled.

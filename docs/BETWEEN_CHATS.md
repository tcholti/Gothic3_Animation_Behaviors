# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Work result — C1-O2 shadow outer ScriptFunction binding integration

**Date:** 2026-08-29
**Branch:** `docs/collision-source-evidence`
**Implementation commit:** `1b222e5382eef6b3ae2cc70e90b9aba39800c380`

Implemented only the frozen C1-O2 integration:

- added the single allowed `gCScriptAdmin::RunScriptFunction(...)` hook at tested `Game +0x1604E0`, using the pinned SDK member signature and established `ThisCall` hook convention;
- added a nesting-safe, synchronous dispatch stack and lifetime-bound outer-frame correlation using only exact SPU, top ScriptFunction, non-null arguments pointer equality, and ScriptFunction name equality;
- added pre-CombatMove shadow acquisition only for the dispatch SPU actor's exact currently equipped RIGHT/LEFT source on a successful `Item_Attack` result, including `7 -> 7`;
- reused the same outer-owned generation at later matching CombatMove initial invocation without candidate cancellation;
- preserved the ordinary CombatMove candidate path when no matching pre-acquired binding exists;
- retired live bindings on true ScriptFunction return and invalidated transient dispatch correlation at AISetState; outstanding true-return obligations emit `OUTER_RETURN_OUTSTANDING` and remain shadow-only for the existing AISetState path;
- added focused C1-O2 acquisition/reuse/binding/retirement/invariant records and a distinct startup banner.

Changed files:

- `prototypes/Script_FrameCollisionTest/CollisionLifecycleGuard.h`
- `prototypes/Script_FrameCollisionTest/CollisionLifecycleGuard.cpp`
- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`

Bounded source/diff audit passed:

- the new wrapper calls Gothic's original exactly once with all three real arguments unchanged;
- transient dispatch context is LIFO/nesting-safe and is removed on every normal wrapper exit;
- no top-entry address, stack index/count, break block, action/phase/state/input, callback, or family value is used as identity;
- native correlator pointers are cleared on true-return retirement, destroyed with record removal, and invalidated at AISetState;
- pre-CombatMove acquisition requires exact equipped RIGHT/LEFT identity from the supplied SPU actor;
- matching CombatMove reuses the generation; unmatched CombatMove retains the existing candidate behavior;
- cleanup remains source/consequence based, and existing AISetState capture/original/finalization ordering and `WOULD_REPAIR` classification remain intact;
- no physical collision call/repair, marker/callback/bookkeeping change, classifier, timer, polling, scan, or extra hook was added;
- only allowed prototype files changed and `git diff --check` passed.

Contradictions / stop conditions: none encountered in source implementation. Relevant null-arguments and frame-overlap cases are logged and deliberately left unacquired as frozen.

Gothic 3 was not built or run. Normal Chat still needs to review the diff before the home-PC build/load/runtime matrix.

No further Work task is frozen here. STOP.

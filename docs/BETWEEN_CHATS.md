# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Work result — C1 shadow execution-level collision lifecycle guard

**Date:** 2026-08-28
**Branch:** `docs/collision-source-evidence`
**Implementation commit:** `3778517f421d07e940c620745bc7ccdf0da54313`

### Implemented

- Added separate `CollisionLifecycleGuard.h/.cpp` shadow responsibility and registered it in the prototype CMake source list.
- Non-FullStop CombatMove calls now create actor-generic monotonically numbered candidates from exact RIGHT/LEFT equipped-source snapshots before original; `GEFalse` persists the generation and `GETrue` cancels it after original.
- Successful tracked-source `Item_Attack` results, including `7 -> 7`, create/refresh per-source obligations; observed results outside `Item_Attack` fulfill them.
- AISetState captures the current generation before original and evaluates it only after original, logging explicit `NO_OP`, `WOULD_REPAIR`, `UNRESOLVED_NOT_EQUIPPED` or generation-invariant outcomes before retiring only the shadow record.
- Added player-focused C1 lifecycle/invariant diagnostics and the required startup banner; underlying lifecycle tracking remains actor-generic.

### Protected behavior and source audit

- C1 never calls `SetCollisionGroup`, `RetireMarkerOwnedSource`, `ClearTriggeredList`, changes StatePosition, suppresses callbacks or mutates physical collision/marker behavior. `WOULD_REPAIR` is log-only.
- FullStop and AIFullStop do not mutate C1 ownership. No new hook, classifier, timer, polling/scan, production configuration or marker-core change was added.
- Existing AICombatMoveInstr, AISetState and SetCollisionGroup wrappers still call their originals exactly once; the real AISetState argument and native return behavior are preserved.
- Existing marker retirement order and all B1–B9 diagnostics/collision/marker/source/callback/bookkeeping behavior remain intact.
- The published diff contains only the five allowed files; `git diff --check` and targeted forbidden-mutation/original-call audits passed.
- No source/API contradiction was found.

### Still required outside Work

- Independent diff-against-contract review.
- Build/load verification and the separately frozen C1 runtime matrix.
- No build or Gothic 3 run was performed in Work, as required.

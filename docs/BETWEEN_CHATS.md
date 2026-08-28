# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Work result — Step B6-C empty-Primary successor PlayMotion stack diagnostic

**Date:** 2026-08-28
**Branch:** `docs/collision-source-evidence`
**Implementation commit:** `55ca9148b0c6f3be8e65b5d483eeabec85195a08`

### Changed

- Added diagnostic-only `HIT EMPTY-PRIMARY SUCCESSOR STACK` capture in the existing player/type-0 PlayMotion hook.
- The new pre-original branch requires an available-but-empty Primary snapshot plus the existing `CollisionControl::IsAttackHit(actor, AttackFamily_Normal)` predicate.
- It captures the established short Win32 stack, incoming request address, actor/action/phase/state-time/state-position/current-movement context and equipped-source snapshot.
- The new record is emitted only after original PlayMotion installs a factual successor Primary motion instance; it does not classify that successor.
- Updated the B6 runtime banner with `EMPTY-PRIMARY SUCCESSOR`.

### Protected behavior and source audit

- Original PlayMotion remains called exactly once per existing path with unchanged arguments.
- Existing direct replacement capture/gate/logging and PrimaryFirst before/after logging remain present and unchanged.
- Existing StopMotion and StartRecover probes are unchanged.
- No new hook, cleanup/repair, lifecycle or persistent diagnostic state, timer, polling, scan, cache, classifier, reaction-family rule, collision-group gate or guessed layout was added.
- Collision, marker, callback and bookkeeping behavior is untouched.
- Only the three allowed source files changed; `git diff --check` passed.

### Still required outside Work

- Independent diff-against-contract review.
- Build/load verification, then repeat the controlled B6-C legitimate interruption fixture and verify interpretable `HIT EMPTY-PRIMARY SUCCESSOR STACK` records.
- No build or Gothic 3 run was performed in Work, as required.

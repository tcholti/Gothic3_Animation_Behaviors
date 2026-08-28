# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Work result — Step B6 StartRecover-BEGIN stack diagnostic

**Date:** 2026-08-28
**Branch:** `docs/collision-source-evidence`
**Implementation commit:** `8aa50c1493d22733a51e53de82cbc36e0d983d78`

### Changed

- Added diagnostic-only `HIT STARTRECOVER BEGIN STACK` capture inside the existing player `sAICombatMoveStartRecover` hook.
- The new branch runs only when the current Primary snapshot passes the existing `IsAttackHitPrimaryMotion` classifier.
- It captures the established short Win32 stack plus outgoing Primary motion, actor, action, phase, state time, current movement and equipped-source context before original StartRecover.
- Updated the B6 load banner to identify the StartRecover, StopMotion and direct-replacement stack probes.

### Protected behavior and source audit

- Existing `COMBATMOVE STARTRECOVER BEGIN` and `END` records remain present around the unchanged original call.
- Original StartRecover remains called exactly once with the unchanged SPU argument.
- Existing direct PlayMotion replacement-stack and StopMotion probes are unchanged.
- No new hook, cleanup/repair, lifecycle state, timer, polling, scan, cache, classifier, family rule or guessed layout was added.
- Collision, marker and callback behavior is untouched.
- Only the three allowed source files changed; `git diff --check` passed.

### Still required outside Work

- Independent diff-against-contract review.
- Build/load verification and a repeated B6-B clean 2H Normal control to confirm interpretable `HIT STARTRECOVER BEGIN STACK` records.
- No build or Gothic 3 run was performed in Work, as required.

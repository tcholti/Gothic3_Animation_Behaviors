# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Work result — Step B6 outgoing-Hit StopMotion stack diagnostic

**Date:** 2026-08-27
**Branch:** `docs/collision-source-evidence`
**Implementation commit:** `c99949d9ff2eeb7a6ce6242764d26d6a6574f299`

### Changed

- Added diagnostic-only `HIT STOP STACK` capture in the existing player/type-0 `StopMotion` hook when its before-snapshot passes the existing `IsAttackHitPrimaryMotion` classifier.
- Captures the established short Win32 stack plus factual actor, action, phase, movement, equipped-source, motion-type and blend-time context before original `StopMotion`.
- Labels the stop as not a confirmed replacement so runtime analysis can correlate it with the immediately following existing PlayMotion record.
- Preserved the existing StopMotion before/after event log.

### Source audit

- Original StopMotion remains called exactly once per existing path with unchanged arguments.
- Attack-Hit snapshot/context/stack capture occurs before original StopMotion and only inside the existing player/type-0 path.
- Existing direct PlayMotion replacement-stack logic is unchanged.
- No new hook, lifecycle state, cleanup/repair behavior, timer, polling, family rule, classifier, or guessed layout was added.
- Collision, marker and callback behavior is untouched.
- `git diff --check` passed.

### Still required outside Work

- Independent diff-against-contract review.
- Build/load verification, then B6-B clean control, B6-C legitimate reaction interruption and B6-D bad block-skip direct replacement runtime tests.
- No build or Gothic 3 run was performed in Work, as required.

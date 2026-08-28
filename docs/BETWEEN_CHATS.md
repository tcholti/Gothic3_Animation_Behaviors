# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Work result — Step B9 native AISetState ordering diagnostic

**Date:** 2026-08-28  
**Branch:** `docs/collision-source-evidence`  
**Implementation commit:** `55e268901aaf06758cb5d88085c865457684992c`

### Changed

- Added one diagnostic ThisCall interception at tested `Game + 0x164320` using the authoritative `void gCScriptRoutine_PS::AISetState(bCString const&)` signature.
- Added player-only pre-original `AISETSTATE CALLSITE` records resolved from the original routine property-set `this` and `this->GetEntity()`.
- Records the unchanged requested state argument, immediate caller module/RVA, unchanged 16-frame stack, current routine state, action/phase/StateTime/StatePosition, movement, PrimaryFirst and equipped-source context.
- Added the Step B9 startup banner.

### Protected behavior and source audit

- Original AISetState is called exactly once with the unchanged real argument; void return behavior is preserved and there is no post-call mutation.
- The new record is gated only to the player, not by input, attack/family, action, phase, collision group, state name, successor, FullStop caller or cleanup state.
- Existing B7, B7b and B1–B6 diagnostics, direct motion probes, native cleanup observation, PrimaryFirst logging, and all collision/marker/callback/bookkeeping behavior remain unchanged.
- No production cleanup/repair, lifecycle or persistent state, timer, polling, scan, cache, classifier, forbidden hook, call-site interception, offensive-request stack capture or guessed layout was added.
- Only the three expected diagnostic source files changed; `git diff --check` passed and the published comparison matches the audited source scope.

### Still required outside Work

- Independent diff-against-contract review.
- Build/load verification and the separately frozen B9 runtime fixture.
- No build or Gothic 3 run was performed in Work, as required.

# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Work result — Step B7b exact AIFullStop caller observation

**Date:** 2026-08-28
**Branch:** `docs/collision-source-evidence`
**Implementation commit:** `806c5bc2c6253c9c878161289aee667ea1bad5a6`

### Changed

- Added one diagnostic ThisCall interception at tested `Game + 0x164430` using the authoritative `void gCScriptRoutine_PS::AIFullStop()` member signature.
- Added player-only `AIFULLSTOP CALLSITE` capture using the original routine property-set `this` and `this->GetEntity()`.
- Captures `_ReturnAddress()`, immediate caller module/RVA, the unchanged 16-frame stack, action/phase/current state/StateTime/StatePosition, CharacterControl PressedKey/IsPressed/IsPressedBefore/DurationPressedMSecs, movement, PrimaryFirst and equipped-source context before original.
- Added the B7b runtime banner.

### Protected behavior and source audit

- Original AIFullStop remains called exactly once through the existing ThisCall self mechanism; void return semantics are preserved.
- No input-key or collision-group gate was added; those values are factual context only.
- Existing B7, B1–B6 and B4/B5 diagnostics are unchanged.
- No ProcessScript, AIStopCombatMove or individual Script_Game FullStop-site hook was added.
- No production cleanup/repair, lifecycle or persistent state, timer, polling, scan, cache, classifier, offensive-request stack capture, successor gate or guessed layout was added.
- Collision, marker, source, callback, bookkeeping and native cleanup behavior are untouched.
- Only the three expected source files changed; `git diff --check` passed.

### Still required outside Work

- Independent diff-against-contract review.
- Build/load verification and controlled B7b clean/reaction/bad-skip runtime comparison.
- No build or Gothic 3 run was performed in Work, as required.

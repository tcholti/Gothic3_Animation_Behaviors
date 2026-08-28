# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Work result — Step B7 CombatMove full-stop stack diagnostic

**Date:** 2026-08-28
**Branch:** `docs/collision-source-evidence`
**Implementation commit:** `7b1096284f7385af5822c59735191dcf47c2e097`

### Changed

- Added one diagnostic hook at tested `Game + 0x1696E0` using the authoritative SDK `sAICombatMoveInstr(GELPVoid, gCScriptProcessingUnit *, GEBool)` `GE_STDCALL` signature.
- Added player-only `COMBATMOVE FULLSTOP STACK` capture when `a_bFullStop == GETrue` and the SPU SelfEntity resolves to the player.
- The record captures the existing 16-frame Win32 caller stack plus factual action, phase, StateTime, StatePosition, movement, PrimaryFirst and equipped-source context before original.
- Added the B7 runtime banner.

### Protected behavior and source audit

- Original `sAICombatMoveInstr` is called exactly once with unchanged arguments and its result is returned unchanged.
- Non-full-stop calls perform no diagnostic work before forwarding to original.
- The new record has no collision-group, attack-family, reaction, block, successor-name or other cause gate.
- No ProcessScript, AIFullStop or AIStopCombatMove hook was added.
- Existing B1–B6 and B4/B5 diagnostics are unchanged.
- No production cleanup/repair, lifecycle or persistent diagnostic state, timer, polling, scan, cache or guessed layout was added.
- Collision, marker, callback, bookkeeping and native cleanup behavior is untouched.
- Only the three expected source files changed; `git diff --check` passed.

### Still required outside Work

- Independent diff-against-contract review.
- Build/load verification, then controlled clean, legitimate-reaction and bad block-skip B7 comparisons.
- No build or Gothic 3 run was performed in Work, as required.

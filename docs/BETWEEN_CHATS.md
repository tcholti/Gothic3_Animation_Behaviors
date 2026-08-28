# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Current result — B7 CombatMove full-stop causality resolved

**Date:** 2026-08-28
**Branch:** `docs/collision-source-evidence`
**B7 implementation:** `7b1096284f7385af5822c59735191dcf47c2e097`
**B7 raw runtime log:** `research/raw/2026-08-28_b7_player_combatmove_fullstop_clean_reaction_blockskip.log`
**Raw commit:** `49e99a933ce2bb02ae6434ec077fb7f549b1f7f5`
**Canonical evidence:** EV-185–EV-186

### Resolved

- Bad full-Whirl block-skip explicitly invokes `sAICombatMoveInstr(..., fullStop=true)`.
- Bad-path FullStop stack is stable: `Game +0x164441` (`gCScriptRoutine_PS::AIFullStop`) -> `Script_Game +0x61866` -> `Game +0x16093B`.
- Armed bad cases FullStop while the weapon is already `Item_Attack(7)`; no StartRecover or native cleanup follows, and Ambient can inherit the stale group 7.
- Legitimate Normal/Quick reactions also FullStop the active CombatMove, but through a distinct Script_Game caller chain; an armed reaction then receives the separate established `Script_Game +0x24AFF` cleanup.
- Therefore FullStop is a native instruction-termination boundary, not collision cleanup itself.

### Next responsibility

Do **not** add another runtime diagnostic yet.

Normal Chat should statically/source-audit the stable bad caller path around `Script_Game +0x61866` and compare it with the legitimate-reaction FullStop caller chain. The goal is to identify what control path owns the bad FullStop and why no replacement cleanup responsibility follows.

Production collision repair, lifecycle state, timers/polling and marker-core simplification remain blocked until that comparison is understood.

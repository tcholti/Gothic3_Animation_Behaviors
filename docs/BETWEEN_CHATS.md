# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Current result — B7b exact AIFullStop caller resolved

**Date:** 2026-08-28
**Branch:** `docs/collision-source-evidence`
**B7b implementation:** `806c5bc2c6253c9c878161289aee667ea1bad5a6`
**B7b raw runtime log:** `research/raw/2026-08-28_b7b_player_aifullstop_exact_caller_clean_reaction_blockskip.log`
**Raw commit:** `9fe85819e44cc33b7d2d6846e24097861b28a8ca`

### Resolved

- Tested bad player full-Whirl skips use the exact `PSRoutine::FullStop()` call at `Script_Game +0x633F1`; B7b observes the immediate return at `+0x633F7`.
- The tested bad records are in `PS_Melee_WhirlAttack`, `PressedKey=16` (`Use2`), `IsPressed=1`, `IsPressedBefore=1`. Both pre-activation and armed skips use this same caller.
- Static code immediately before this call compares the press-duration result against `0x9C4` (2500 ms) and bypasses the branch while the duration is `<= 2500`. Runtime bad samples at this caller report durations such as 2502 and 2508 ms.
- Immediately after the bad FullStop, the same branch calls `PSRoutine::SetState()` at `Script_Game +0x63409`.
- The official SDK documents `SetState` as clearing the SPU state stack and resetting state position/break-block bookkeeping. Combined with the proven full-Whirl suspended CombatMove break-block continuation, this explains why the old Whirl ScriptFunction cannot resume into ordinary cleanup `+0x4E03C` after this bad transition.
- Tested legitimate Normal/Quick reactions use a different exact FullStop site: `Script_Game +0x2D0F2`, observed as return `+0x2D0F8`. That site jumps back into reaction control rather than immediately calling SetState; established reaction cleanup `+0x24AFF` follows when the weapon had armed.
- Extra post-skip movement in the B7b fixture continued while the right-hand weapon remained group 7, reinforcing prior evidence that ordinary movement does not repair stale offense.

### Qualification

The exact `+0x633F1 -> SetState` abandonment path is proven for the tested player full-Whirl/held-Use2 failure. Do **not** generalize that exact caller to Dual Quick or every stale-collision family yet. Earlier evidence proves the stale-collision defect is broader, but the higher-level state-reset path may differ.

### Next responsibility

No new implementation is needed yet. Reuse the currently deployed B7b diagnostic for the smallest cross-family check: reproduce the already-known player Dual Quick bad skip and determine whether its active CombatMove is terminated through the same `AIFullStop -> SetState` path or a different state-stack-abandonment route.

Production cleanup/repair, lifecycle/pending state, timers/polling, family-specific repair and marker-core simplification remain blocked until that generality question is answered.

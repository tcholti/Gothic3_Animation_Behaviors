# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Current result — B8/B9 state-stack abandonment and cleanup ordering resolved

**Date:** 2026-08-28  
**Branch:** `docs/collision-source-evidence`  
**B9 implementation:** `55e268901aaf06758cb5d88085c865457684992c`  
**B9 raw:** `research/raw/2026-08-28_b9_player_aisetstate_cleanup_ordering.log`  
**B9 raw commit:** `ae0a78787cb811f9de551997505ea4bd14370846`

### B8 generality result

- The held-Use2 stale-collision mechanism is not full-Whirl-specific. Tested player Quick attacks with Dual (1H+1H), plain 1H, and Shield+1H use the same `Script_Game +0x633F1` FullStop path (observed return `+0x633F7`) and can enter successor Ambient/Parade with an armed weapon still at group 7.
- Therefore the tested failure class is a shared player held-Use2 state-stack-abandonment mechanism across multiple attack families/weapon configurations, not a Whirl or Dual special case.

### B9 ordering result

- Tested bad held-Use2 full-Whirl cases order as `AIFullStop -> CombatMove fullStop -> AISetState` with no native cleanup between them. In representative armed cases `AISetState` is entered while the old attack Hit is still the current pre-original state context and the equipped weapon is still `Item_Attack(7)`.
- Tested clean full Whirl, Normal and Quick completion performs ordinary native `7 -> 5` cleanup before the later `AISetState(...PS_Melee_Loop)` call.
- Tested armed legitimate Normal/Quick reactions order as `AIFullStop -> CombatMove fullStop -> reaction cleanup +0x24AFF -> reaction successor`; no `AISetState` intervenes before that cleanup in the tested samples.
- B9 also exposed an additional legitimate-reaction AIFullStop caller at `Script_Game +0x2B8CB` in addition to the previously confirmed `+0x2D0F8`. Do not treat one reaction call site as universal.
- Result: destructive native state replacement is now a strong tested post-opportunity checkpoint for the known held-Use2 abandonment class, but `AISetState` itself is generic and must **not** become an unconditional cleanup hook.

### Pierce Raise subtest qualification

- The B9 log contains repeated plain-1H and Dual Pierce `Raise -> Hit` sequences.
- No `AIFULLSTOP CALLSITE` record was found while `PS_Melee_PierceAttack` was active; the held-Use2 `+0x633F7` events around those attempts occurred in `PS_Melee_Loop` before/after the Pierce execution.
- Therefore this run does not newly prove a destructive bad skip occurring inside Pierce Raise. Preserve the user's earlier/repeated runtime observation that Raise can still proceed to Hit after a skip as an observation until directly reproduced under the indexed diagnostic.

### Additional runtime observation

- Across the current and previous bad-Hit reproductions, the user repeatedly observes the attack's native forward movement stopping immediately when the bad skip occurs. This is consistent with active CombatMove termination but displacement was not instrumented, so treat it as repeated user runtime observation rather than log-proven positional evidence.

## Next responsibility — C1 design, not another broad probe

The previous production gate was to establish a general event-driven finalization mechanism. B8/B9 now satisfy that research gate for the tested known stale class strongly enough to design the smallest execution-level guard.

Normal Chat should design the guard before any Work implementation. The design must preserve the governing invariant:

> For an exact real attack-Hit execution that actually requested offensive collision, allow Gothic its legitimate cleanup opportunity; if native cleanup occurred, no-op; if destructive state replacement abandons the execution with the obligation still outstanding, repair only that execution's remaining offensive source(s) using native cleanup semantics.

The design should be driven by native events already proven: offensive request, native cleanup observation, CombatMove fullStop/termination, and destructive AISetState finalization. It must remain general and event-driven, with no family/cause matrix, polling, timer, unconditional AISetState cleanup, or marker-bookkeeping regression.

Do not start Work until Normal Chat freezes the exact C1 production state/transition model and bounded implementation contract.

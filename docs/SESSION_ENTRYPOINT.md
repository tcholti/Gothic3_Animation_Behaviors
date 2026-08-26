# Session Entry Point

**Purpose:** Minimal durable handoff for any new Chat or Work session. Read this first; open deeper project files only as needed.

**Branch:** `docs/collision-source-evidence`  
**Updated:** 2026-08-26

## Where We Are

Frame-controlled weapon collision is the active subsystem. The validated RIGHT/LEFT/BOTH/OFF marker core is established. `G3AB_COL_OFF` is **optional authored early shutoff**, never the general safety mechanism.

Full Whirl testing exposed a native lifecycle defect: weapon collision can remain `Item_Attack` when an attack is disrupted around block timeout. The defect is not marker-created and is broader than Staff Whirl; the new native control also contains a Dual Quick execution whose next attack begins from collision group 7 (`7 -> 7`) before a later reset.

Recover is not the universal cleanup owner. Earlier Quick controls reset at the same boundary with or without a Recover asset.

## v0.20 Findings

`v0.20` is read-only. Its marked log proves that action/phase is **not** a reliable lifetime owner after a marked Hit has begun. In a 2H Whirl fault, action drifted from Whirl (`10`) to Stand (`0`) while the exact owned Whirl Hit remained both `CurrentMovementAni` and `PrimaryFirst`, was still running, and was only at about `0.611 / 0.800 s`. The current strict action gate consequently rejected later authored OFF/RIGHT markers that still belonged to that surviving Hit.

On the following lifetime sample, the owned Whirl had been replaced by an Ambient primary/current motion while the source was still marker-owned and armed. Actual motion replacement therefore provides a promising cleanup boundary.

A normal marked Dual Quick sample reached `0.399928 / 0.400000 s` on the owned Hit; about 17 ms later Gothic 3 performed its normal `7 -> 5` reset in Recover phase. This supports actual Hit end as a plausible lifetime boundary, but does not yet prove a universal engine rule.

The v0.20 Script `OnTick` probe is diagnostic only and samples too coarsely to be the production cleanup mechanism.

Finishing attacks with working Raise survived the tested block-timeout timing and reached normal cleanup. Treat this only as a lead: FinishingAttack also uses a different action/lifecycle, so Raise itself is not yet proven causal.

## New Balance Comparison

Pinned Jackydima New Balance source shows that with `UseStaticBlocks == false` it byte-patches `Script_Game` specifically to **remove the player block limiter**. This changes/avoids the block-timeout trigger; it is not a collision-lifetime cleanup implementation to copy.

## Immediate Next Step

Search the SDK/binary/reference paths for a sufficiently immediate, event-driven signal or hook for actual primary Hit end/replacement. The working design hypothesis is:

- once an exact marked execution has acquired collision ownership, harmless action/phase drift must not invalidate later markers while that same actual Hit motion survives;
- if that owned Hit actually ends or is replaced, all sources still owned by that execution must be closed independently of optional `G3AB_COL_OFF`;
- decide separately how to repair the broader native/unmarked stale-collision defect without changing valid native contact windows.

Do **not** implement this production rule until the lifetime hook/boundary is identified and checked against genuine interruption cases.

## Read Next Only As Needed

1. `research/raw/2026-08-25_framecollision_v0.20_player_staff_2h_dual_block_timeout_*.log` — immediate evidence.
2. `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp` — v0.20 probe/current prototype.
3. `docs/HANDOFF.md` — detailed continuation state.
4. `docs/RESEARCH_MAP.md` and `docs/EVIDENCE_LEDGER.md` — broader research/evidence state.
5. `references/jackydima-gothic3sdk/scripts/Script_NewBalance/CodePatch.cpp` — block-limiter comparison.

Keep this file short; update it only when the immediate problem, current prototype, or next step materially changes.
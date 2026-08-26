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

## Working Cleanup Design

The preferred direction is now a **single execution-level guard**, documented in `docs/COLLISION_LIFECYCLE_PLAN.md`:

- acquire a real attack-Hit execution using native semantics;
- marked motions suppress native activation timing, unmarked motions remain native;
- once offensive collision is requested, the exact actual Hit execution becomes the preferred lifetime authority;
- when that Hit actually ends/replaces, do nothing if Gothic 3 already performed native cleanup; otherwise invoke the native cleanup it should have performed;
- how the Hit ended should not create separate cleanup branches.

Preferred main plan tracks only execution-level `collision requested / cleanup observed` state. Per-source ownership is the fallback only if native cleanup proves source-specific or partially independent.

Current v0.20 source masks/windows and action/phase-based lifetime-retirement checks are therefore **provisional cleanup scaffolding to revisit, not assumed production architecture**. Do not remove them yet. RIGHT/LEFT/BOTH exact-set switching, repeated-marker rearm, optional `COL_OFF`, and replay/occurrence guards solve separate authored-marker problems and are not currently targeted for removal.

## New Balance Comparison

Pinned Jackydima New Balance source shows that with `UseStaticBlocks == false` it byte-patches `Script_Game` specifically to **remove the player block limiter**. This changes/avoids the block-timeout trigger; it is not a collision-lifetime cleanup implementation to copy.

## Immediate Next Step

Design and run the research tests in `docs/COLLISION_LIFECYCLE_PLAN.md` before implementing cleanup:

1. determine whether any legitimate native sequence carries `Item_Attack` across the end of one physical Hit execution into another;
2. inspect attacker/defender weapon and shield collision behavior during successful block/parade/stumble cases;
3. locate Gothic 3's actual native cleanup operation and determine whether it is attack-wide or per-source;
4. identify an immediate/event-driven signal for actual Hit end/replacement and validate it against normal completion, block-timeout drift, and genuine interruption.

Only after those questions are stable should the logger be upgraded around the exact required evidence. Do **not** add new Quick/Whirl/Staff/block/Recover-specific cleanup branches while the unified rule is under investigation.

## Read Next Only As Needed

1. `docs/COLLISION_LIFECYCLE_PLAN.md` — current main/fallback cleanup plan, provisional v0.20 paths to revisit, and next tests.
2. `research/raw/2026-08-25_framecollision_v0.20_player_staff_2h_dual_block_timeout_*.log` — immediate evidence.
3. `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp` — v0.20 probe/current prototype.
4. `docs/HANDOFF.md` — detailed continuation state.
5. `docs/RESEARCH_MAP.md` and `docs/EVIDENCE_LEDGER.md` — broader research/evidence state.
6. `references/jackydima-gothic3sdk/scripts/Script_NewBalance/CodePatch.cpp` — block-limiter comparison.

Keep this file short; update it only when the immediate problem, current prototype, or next step materially changes.
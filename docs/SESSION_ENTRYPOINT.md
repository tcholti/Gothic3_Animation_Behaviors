# Session Entry Point

**Purpose:** Minimal durable handoff for any new Chat or Work session. Read this first; use the linked canonical documents only as needed.

**Branch:** `docs/collision-source-evidence`  
**Updated:** 2026-08-26

## Where We Are

Frame-controlled weapon collision is the active subsystem. The validated RIGHT/LEFT/BOTH/OFF marker core is established; `G3AB_COL_OFF` is **optional authored early shutoff**, never the general safety mechanism.

Full 2H/Staff Whirl support exposed a native lifecycle defect: Staff Whirl can leave the weapon in `Item_Attack` after the attack effectively ends, including in an unmarked native control. Separate Shield+1H and 1H Quick tests show collision can reset at the same boundary even when no Recover animation exists, so Recover is not the universal cleanup owner.

`v0.20` is a **read-only primary-motion lifetime probe** built on the current Whirl path. Its purpose is to distinguish harmless action/phase drift while the same Hit execution still survives from a true motion end/replacement that must close marker-owned collision.

## Immediate Next Step

Review and compare the two committed `v0.20` block-timeout logs at commit `ffec1e8` before changing cleanup behavior. Determine whether the primary motion instance/running state, motion identity, play/max time, or another observed signal reliably identifies the lifetime of the actual Hit execution.

Do **not** implement a production cleanup rule until that evidence is reviewed.

## Read Next Only As Needed

1. `docs/HANDOFF.md` — detailed continuation state.
2. `docs/RESEARCH_MAP.md` — research state and next work.
3. `docs/EVIDENCE_LEDGER.md` — fact/hypothesis status.
4. `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp` — current prototype.
5. `research/raw/2026-08-25_framecollision_v0.20_player_staff_2h_dual_block_timeout_*.log` — immediate evidence.

Update this file whenever the immediate problem, current prototype, or next step materially changes. Keep it short.
# Gothic 3 Animation Behaviors — RAW55 Quick Early-Window Control Probe

**Status:** SUPERSEDED BEFORE IMPLEMENTATION BY EV-268  
**Date:** 2026-09-12  
**Scope:** historical diagnostic contract only

## Supersession

Do **not** implement this probe.

The User performed a stronger animation-authored timing control before this Work task was sent for implementation:

```text
research/raw/2026.09.12_troll_quick_fist_activation_frame_4.log
research/raw/2026.09.12_troll_quick_fist_activation_frame_1.log
```

EV-268 records the result.

The frame-4 marked fixture moved authored `G3AB_COL_FIST` early enough that it arrived after native Quick had already made the EV-265-suppressed raw55 request and advanced StatePosition to 1. The existing EV-267 FIST-time activation/rearm then executed around StateTime ~0.16 and Troll Quick produced repeated `OnDamage` against `PC_Hero`, including early-in-swing and later re-entry contact observed by the User.

The frame-1 marked fixture produced the more important boundary: `G3AB_COL_FIST` itself was observed repeatedly with valid C1 and factual RIGHT `TrollFist` / PhysicalFist/raw55 while StatePosition was still 0, before the native Quick raw55 request around StateTime ~0.10. The current temporary `PhysicalFistProbe` requires an earlier EV-265 suppression proof and later StatePosition 1, so it did not intervene; no `CORE RAW55_QUICK_FIST_REARM_PROBE` and no `OnDamage` occurred.

Therefore the prior timing-vs-geometry question no longer requires this control. The stronger conclusion is that the current temporary probe has a **pre-StatePosition FIST ordering gap**.

Current authority:

```text
docs/COLLISION_RAW55_QUICK_PRESTATE_FIST_PROBE.md
```

Current handoff:

```text
docs/BETWEEN_CHATS.md
```

This file remains only to prevent stale handoffs from being executed.
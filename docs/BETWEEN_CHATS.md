# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest handoff

**From:** Normal Chat / home-PC validation  
**To:** Normal Chat planning before next Work task  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

### Step A status

**VALIDATED.**

Implementation commit:

`325c98e725502229bf796083e52c0fa977803cc0`

Home-PC validation:

- Release build succeeded;
- installed DLL matched built DLL SHA-256 `4CD111D0B92A562AD8831BA81FA00C6E8A29BE5EC3F66E5920D6B214F99553DD`;
- Gothic 3 loaded and ran without crash;
- marked Normal/Quick/Whirl smoke test covered 2H, Staff, and Dual/1H+1H;
- v0.20 marker/control/diagnostic behavior remained present;
- known stale collision/lifetime defect still reproduced, as expected for a parity-only refactor.

Smoke log:

`research/raw/2026-08-26_framecollision_modular_v0.20_parity_smoke.log`

### Next action

Do not send another coding task to Work yet.

Normal Chat should first:

1. archive processed raw logs;
2. review/finalize the smallest Step B lifecycle-diagnostic change from `docs/COLLISION_LOGGER_PLAN.md`;
3. overwrite this file with that bounded Work assignment.

Do **not** implement production collision cleanup yet.

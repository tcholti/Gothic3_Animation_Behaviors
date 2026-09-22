# Gothic 3 Animation Behaviors — Evidence Ledger EV-365 Onward

**Status:** Active evidence/provenance ledger  
**Opened:** 2026-09-22

## Purpose

Record new evidence after EV-364 using a compact provenance-first format.

This ledger is **proof history, not the normal knowledge interface**. Current established collision facts belong in `COLLISION_REFERENCE.md` and owning architecture/reference documents.

The EV-342–EV-364 ledger and all earlier closed volumes are routed through `EVIDENCE_INDEX.md`.

## Entry format

Each EV should contain only what is needed to preserve the evidence transaction:

```text
### EV-xxx — short factual title

Observed:
- direct factual result(s)

Scope / limits:
- exact actor/action/source/build/test limits
- explicit non-claims when important

Provenance:
- source/log/commit/hash/path as applicable

Disposition:
- PASS / FAIL / NEGATIVE CONTROL / INCONCLUSIVE / SUPERSEDED
- current-reference or architecture consequence, if any
```

Keep interpretation concise. Long causal reasoning belongs in the active investigation while open; reusable conclusions must be promoted to current reference/architecture before that investigation is archived.

## Entries

### EV-365 — Final frozen-source Stage-A body-contact batch PASS

Observed:
- Wolf marked raw8: native Wolf and transformed-player Wolf both entered the permanent raw8 mechanism. 32 authored opportunities opened; 15 were consumed by exact native contact dispatch and 17 closed unused (16 `C1_FINALIZED`, 1 `C1_GENERATION_REPLACED`). Accounting balanced exactly and 15 native Fist contacts were observed.
- Wolf unmarked/native control: 9 attack-ownership observations were all `MarkerPresent=0 / FistMarkers=0 / Raw8Fist=<none> / SuppressNative=0`; zero raw8 ownership/open/consume/close/marker state appeared, while 17 native Fist contacts remained present across native-Wolf and transformed-player directions.
- Minecrawler: marked Normal/Power/Quick raw8 traffic remained healthy; 9 opportunities opened and all 9 were consumed by exact native contact dispatch. Player 1H Normal/Quick/Power/Pierce marker traffic coexisted. Two late QuickAttack RIGHT callbacks arrived after the supported action/C1 had ended and were rejected fail-closed at Action0 with the sword already group5. One exact outstanding player 1H lifecycle state was repaired group7 -> group5 by C1-R1 with no divergence.
- Bloodfly: marked raw8 Normal plus Sprint-origin traffic remained healthy; 12 opportunities opened and all 12 were consumed by exact native contact dispatch. Player 1H+torch marker traffic coexisted. One player right-side Normal motion was genuinely unmarked/native and created no marker ownership.
- Boar: marked Normal/Sprint/Power raw8 traffic opened 13 opportunities; 12 were consumed by exact native contact and 1 closed unused at C1 finalization. Player 1H+torch marker traffic coexisted.
- Bison: marked Normal/Power raw8 traffic opened 13 opportunities; 12 were consumed by exact native contact and 1 closed unused at C1 finalization. Player 1H+torch marker traffic coexisted.
- All six diagnostic logs loaded and unloaded cleanly. No invariant warning, generation inconsistency, contradiction, repair divergence, explicit error/exception/failure, or raw8 accounting leak was found.

Scope / limits:
- This closes comprehensive frozen-source release campaign Stage A only. Equipped observations here are coexistence corroboration, not the Stage-B full weapon/family/side matrix.
- The successful Minecrawler-run C1 repair is expected lifecycle-backup behavior; it proves convergence for that exact occurrence, not that native cleanup can never be missed.
- The two late Minecrawler-run player marker callbacks were unsupported/stale timing traffic rejected without physical activation; they do not establish a new supported family/action.
- The file basename `2026-09-22_wolf_fist_marked_hero_1h_marked_test.log` is misleading: its runtime actor is Minecrawler. The basename is preserved unchanged for provenance.
- This batch did not independently re-hash the deployed DLL; it was run as part of the already-frozen diagnostic-source campaign and the batch commit contains raw evidence only.

Provenance:
- frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- uploaded raw-evidence commit: `0fccfcd9ec2945467cb9af5d4a202822e29be9e7`;
- `research/archive/2026-09-22_wolf_fist_marked_test.log` — blob `17cb29f6ef38b478d5023c9988f834d9ab79a7d3`, 268,997 bytes;
- `research/archive/2026-09-22_wolf_fist_unmarked_test.log` — blob `aed9776105815616914ec808a8153950b2116083`, 50,409 bytes;
- `research/archive/2026-09-22_wolf_fist_marked_hero_1h_marked_test.log` — Minecrawler fixture, blob `7b65aafc4fabde460082051f03efbd0de694ffe4`, 141,172 bytes;
- `research/archive/2026-09-22_bloodfly_fist_marked_hero_1h_torch_marked_test.log` — blob `d26ea1e9cc4335fec8e4d1f55a87bf318e967d47`, 117,448 bytes;
- `research/archive/2026-09-22_boar_fist_marked_hero_1h_torch_marked_test.log` — blob `0225f93c961b1a1b77c53780d6bbe92d915ea665`, 74,382 bytes;
- `research/archive/2026-09-22_bison_fist_marked_hero_1h_torch_marked_test.log` — blob `adb539548840a2fe04b0ec8b6b4ca27775310867`, 105,652 bytes.

Disposition:
- **PASS — comprehensive frozen-source Stage A CLOSED.**
- No source change is justified.
- Continue `COLLISION_TEST_PLAN.md` §3.8 at Stage B equipped actors + player weapon matrix.

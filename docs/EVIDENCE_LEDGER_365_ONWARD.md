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

### EV-366 — Final Stage-A unequipped-opponent extension PASS

Observed:
- Ripper raw8: 24 authored opportunities opened; 20 ended by exact native contact and 4 unused opportunities closed at C1 finalization. Normal plus Sprint-origin transport remained healthy. Player dual-1H RIGHT/LEFT/BOTH/OFF coexistence produced no collision/lifecycle anomaly.
- ScorpionKing raw8: 19 opportunities opened and all 19 were consumed by exact native contact across Normal, Power and Quick. Player dual-1H coexistence remained clean.
- Snapper raw8: 19 opportunities opened and all 19 were consumed by exact native contact across Quick, Normal and Sprint-origin transport. Player Staff Normal/Quick/Power/Hack marker traffic remained clean.
- TRex raw8: 40 opportunities opened; 38 were consumed by exact native contact and 2 closed on factual C1 generation replacement. Normal, Quick, Power and Sprint-origin traffic remained accounted. Player 2H Normal/Quick/Power/Whirl/Hack coexistence remained clean.
- Waran raw8: 16 opportunities opened and all 16 were consumed by exact native contact across Normal, Power and Sprint-origin transport. Player 2H coexistence remained clean.
- Troll stayed on factual `TrollFist` / UseType55 permanent raw55 rather than raw8: 21 accepted raw55 FIST markers across Normal, Quick and Sprint-origin; physical group transitions showed 16 exact 5->7 openings, 5 expected 7->7 repeated-marker cases and 16 exact 7->5 cleanups. Player Staff coexistence remained clean.
- All six logs loaded/unloaded cleanly with zero C1 finalization repair/divergence, marker anomaly/discovery, invariant contradiction, explicit error/exception/failure, or cross-mechanism leakage.

Scope / limits:
- EV-365's earlier “Stage A CLOSED” wording was premature as a workflow-state statement because the User still had additional ordinary unequipped-opponent fixtures prepared. No technical EV-365 result is retracted.
- The User identified this as the last normal unequipped-opponent batch. With EV-365 plus this batch, comprehensive frozen-source Stage A is now actually complete.
- Player dual-1H/Staff/2H observations are coexistence corroboration only; they do not replace the dedicated Stage-B equipped matrix.
- Sprint-origin raw8 opportunities may be consumed after the factual same-C1 Action9 -> Action2 transport; this is the already-accepted permanent transport semantic, not mismatched accounting.

Provenance:
- frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- uploaded raw-evidence commit: `24c09e5d0cfb44479710413d93a049ea73e3b007`;
- `research/archive/2026-09-22_ripper_fist_marked_hero_1h_1h_marked_test.log` — blob `138eddac792650e4bf683d363eb752a3864d0cdd`, 207,077 bytes;
- `research/archive/2026-09-22_scorpionking_fist_marked_hero_1h_1h_marked_test.log` — blob `7c422e2a74fc49d41868a108261425ff03f84ee6`, 165,200 bytes;
- `research/archive/2026-09-22_snapper_fist_marked_hero_staff_marked_test.log` — blob `067ab89301c00776466442d32ee5c856b592810f`, 111,041 bytes;
- `research/archive/2026-09-22_trex_fist_marked_hero_2h_marked_test.log` — blob `de2fe938f1e92b945d895c8f5b5f2bfbab15ea55`, 354,439 bytes;
- `research/archive/2026-09-22_troll_fist_marked_hero_staff_marked_test.log` — blob `1fe1da08255870fd91694ae70136f3520ab36848`, 178,825 bytes;
- `research/archive/2026-09-22_waran_fist_marked_hero_2h_marked_test.log` — blob `6e2f3caff63b979a0705f514e9c2849756b3a52f`, 130,684 bytes.

Disposition:
- **PASS — comprehensive frozen-source Stage A now genuinely CLOSED across EV-365–EV-366.**
- No source change is justified.
- Dedicated equipped coverage remains next under `COLLISION_TEST_PLAN.md` §3.8 Stage B.

### EV-367 — Final-source destructive bad-skip / C1-R1 stress PASS

Observed:
- The dedicated bad-skip log produced 10 real `CORE C1 FINALIZATION ANOMALY / REPAIR` events after native `AISetState` opportunity.
- Every repaired source was an exact currently equipped source with a real outstanding obligation and factual group7 before repair; every repair requested Item_Equipped and verified group5 afterward with `PhysicalCollisionChanged=1`.
- Coverage included: plain 1H RIGHT (2 repairs), 1H+torch RIGHT (3), dual-1H RIGHT (1), dual-1H LEFT (2), Staff RIGHT (1), and 2H RIGHT (1).
- Zero `REPAIR_DIVERGED_FROM_ITEM_EQUIPPED` or `UNRESOLVED_NOT_EQUIPPED` outcomes occurred.
- 14 late marker-discovery records were all fail-closed `REJECTED_UNSUPPORTED_HIT` callbacks at Action0 / no valid C1 with the relevant source already at group5; none reactivated stale collision.
- All 67 compact C1 final records ended with zero outstanding obligation, and the DLL unloaded cleanly.

Scope / limits:
- This is regression validation of the existing `CollisionLifecycleGuard / C1-R1` safety net under the known destructive-skip class.
- It does **not** prevent the destructive animation/script continuation loss itself and does not implement, reopen or close the separate future `AttackContinuationProtection` responsibility.
- It does not replace the later Stage-D mixed stress campaign; it is a targeted lifecycle stress control performed during the Stage-A completion batch.

Provenance:
- frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- uploaded raw-evidence commit: `24c09e5d0cfb44479710413d93a049ea73e3b007`;
- `research/archive/2026-09-22_various_bad_skips_marked_test.log` — blob `acd954f61d6f96f246d1a570b70cdf79d6789abd`, 143,548 bytes.

Disposition:
- **PASS — final-source C1-R1 bad-skip safety regression.**
- Existing lifecycle architecture is corroborated; no architecture/source change is justified.
- `AttackContinuationProtection` remains paused and separate.


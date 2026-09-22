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

### EV-368 — Final frozen-source equipped-opponent / cumulative player matrix PASS

Observed:
- Demon / factual 2H raw3: 26 exact `It_2H_DemonSword_01` 5->7 openings matched 26 exact 7->5 cleanups across Quick/Normal/Power. Player 2H Flamberge simultaneously exercised Quick/Normal/Power/Hack/Whirl with 43 openings and 43 cleanups plus expected repeated 7->7 requests.
- Goblin / factual 1H raw2: two factual club sources remained balanced (`It_1H_Club_01` 13/13 and `It_1H_Club_Summon` 16/16 openings/cleanups). Five factual Action9/Sprint executions each produced one eligible native-open suppression and one matching generic RIGHT authorization. Player 1H remained balanced 19/19.
- Ogre / factual Axe raw52: `It_Axe_OgreMorningStar_01` produced 19 openings and 19 cleanups across Normal/Power/Quick. Player 1H simultaneously produced 43 openings and 43 cleanups across Quick/Normal/Pierce/Power.
- Orc Raider / factual Axe raw52: `It_Axe_Orc_01` produced 19 openings, 19 cleanups and 7 expected repeated 7->7 requests across Quick/Power/Hack/Normal/Whirl. Player 1H+shield produced 24 openings and 24 cleanups across Normal/Quick/Power/Pierce.
- Orc Staff + Fist: factual `It_Halberd_Orc_01` / raw51 produced 17 openings, 17 cleanups and 5 expected 7->7 repeats across Whirl/Quick/Power/Hack/Normal. Raw8 Fist coexistence remained fully accounted: 16 opportunities total (13 Orc, 3 player) -> 11 exact-contact consumptions + 5 factual Orc lifecycle closes. Player 1H+shield/Fist traffic remained healthy.
- Stalker / factual Axe raw52: `It_Axe_SpikedClub_01` produced 16 openings and 16 cleanups across Normal/Quick/Power. Player 1H+shield produced 24 openings and 24 cleanups.
- Across all six logs, every marked attack-ownership observation was accepted in its supported path; there were zero C1 repair/divergence events, zero marker anomaly/discovery records, zero invariant/contradiction/error/failure records, and every DLL instance unloaded cleanly.

Scope / limits:
- This closes §3.8 Stage B using the campaign's compositional coverage rule. The User's standing pattern is one no-opponent/full-attack pass per tested player weapon followed by live-combat use; final-source Stage-A/EV-367 combat evidence already supplied dual-1H, 1H+torch, Staff, 2H and lifecycle-stress coverage, while this batch adds/reinforces 1H, 1H+shield, 2H and the equipped-opponent source matrix.
- The User reports this batch completes all equipped opponents they intended to include in the comprehensive release pass.
- This is regression/compatibility evidence, not a new causal claim about damage policy or animation naming.
- No source modification is justified.

Provenance:
- frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- uploaded raw-evidence commit: `16ab72bec38da4ab9beb0169e0aef164014ac533`;
- `research/archive/2026-09-22_demon_2h_marked_hero_2h_marked_test.log` — blob `bf4e2ade83be54d4e7dfd09f9da1158bb000df3c`, 210,741 bytes;
- `research/archive/2026-09-22_goblin_1h_marked_hero_1h_marked_test.log` — blob `bf50b476616da1bccf15c9118002eaa826f3798c`, 147,091 bytes;
- `research/archive/2026-09-22_ogre_2h_marked_hero_1h_marked_test.log` — blob `77533879f220b115d03b6e5e0979bef5a793a4db`, 168,952 bytes;
- `research/archive/2026-09-22_orc_2h_marked_hero_1h_shield_marked_test.log` — blob `6f3aab25739e89764a09471465b750d81b9fc62a`, 126,592 bytes;
- `research/archive/2026-09-22_orc_staff_fist_marked_hero_1h_shield_fist_marked_test.log` — blob `3f267a6abfd3b51c2ac2f92395c428225c8d736f`, 222,050 bytes;
- `research/archive/2026-09-22_stalker_2h_marked_hero_1h_shield_marked_test.log` — blob `b1ee30163d7ae4f1b432cca2c6da83923078ff42`, 129,977 bytes.

Disposition:
- **PASS — comprehensive frozen-source Stage B CLOSED.**
- Continue §3.8 Stage C modded/custom animation compatibility.

### EV-369 — Native zombie animation-set baseline/control PASS

Observed:
- This batch was run **before** enabling the planned zombie animation-separation mod. It is the native control baseline for later comparison.
- Under native Gothic 3 behavior, the tested zombie/mummy actors use the ordinary human animation sets. The diagnostic runtime therefore correctly exposed `Hero_...` CurrentMovementAni identifiers for all three actor classes.
- Mummy / factual raw8 Fist UseType8: 28 marked attack ownership observations across Normal and Power. Thirty-three accepted FIST opportunities occurred because five Power C1s accepted a later FIST that superseded the prior still-open opportunity. The current opportunities then resolved as 15 exact native-contact consumptions + 13 factual lifecycle closes (11 C1_FINALIZED, 2 C1_GENERATION_REPLACED), with all C1 finals at outstanding zero. Player 2H coexistence remained healthy.
- BenSala_Zombie_02 / factual `It_Pickaxe` UseType52 (Axe/raw52): 42 marked supported attack observations across Quick/Power/Whirl/Normal/Hack plus one genuinely unmarked FinishingAttack-classified Hack fallback. The Pickaxe produced 62 exact 5->7 openings and 62 exact 7->5 cleanups. Marker traffic included expected RIGHT/OFF, authored-occurrence-budget ignores and same-update duplicate ignores without anomaly. Player 2H coexistence remained balanced.
- UndeadPriest / factual `It_Staff_Quarterstaff_01` UseType12: 51 marked attack observations across Power/Whirl/Quick/Normal/Hack. The Quarterstaff produced 64 exact 5->7 openings and 64 exact 7->5 cleanups. Expected RIGHT/OFF + occurrence-budget/dedupe behavior remained healthy. Player 2H coexistence produced 24 openings and 24 cleanups.
- All three logs loaded and unloaded cleanly. There were zero marker anomaly/discovery records, zero C1 repair/divergence events, zero invariant/generation contradictions, and zero explicit error/exception/failure records.

Scope / limits:
- **Interpretive correction:** the previous repository wording incorrectly described this as a zombie-separation-mod run. The User clarified that no zombie separation mod had yet been enabled. The runtime artifacts and technical collision observations remain valid; only their test role was misclassified.
- EV-369 is the native baseline/control to compare against the forthcoming zombie-separation-mod test.
- Native non-Staff two-handed weapon routes may use the ordinary 2H animation set while the factual equipped source remains Axe/UseType52. Therefore BenSala_Zombie_02 using `Hero_..._2H_...` motion identifiers together with exact `It_Pickaxe` / UseType52 is expected native behavior, not a mismatch. Staff remains its own animation set.
- The later Axe-separation mod is specifically intended to give Axe its own animation set; that future compatibility test must compare against this native shared-2H baseline.
- The single unmarked zombie FinishingAttack observation remained native (`MarkerPresent=0 / SuppressNative=0`) and is useful fallback corroboration.
- No source change is justified.

Provenance:
- frozen collision source: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- uploaded raw-evidence commit: `961bee8f212c86510e962aef3a13ce71cf8aea06`;
- `research/archive/2026-09-22_mummy_fist_marked_hero_2h_marked_test.log` — blob `a6437b1275bd3164bde3d890d29847498e54bcce`, 310,750 bytes;
- `research/archive/2026-09-22_zombie_2h_marked_hero_2h_marked_test.log` — blob `5df784d4dc4ebf7e4b0bc4bc6b7a4f26bc76399f`, 177,749 bytes;
- `research/archive/2026-09-22_zombie_staff_marked_hero_2h_marked_test.log` — blob `c94e569360cfa522e0f015b69e0bf8e87312fc08`, 249,686 bytes.

Disposition:
- **PASS — native zombie baseline/control established.**
- Zombie animation-separation compatibility remains OPEN/NEXT in Stage C.
- Stage C remains active for the zombie-separation run and subsequent Axe/Rapier/custom fixtures.


# Gothic 3 Animation Behaviors — Evidence Ledger EV-309 Onward

**Status:** Active evidence/provenance ledger  
**Opened:** 2026-09-19

## Purpose

Record new evidence after EV-308 using a compact provenance-first format.

This ledger is **proof history, not the normal knowledge interface**. Current established collision facts belong in `COLLISION_REFERENCE.md` and owning architecture/reference documents.

Previous ledger volumes are archived under `docs/archive/evidence/` and routed through `EVIDENCE_INDEX.md`.

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

### EV-309 — Orc Staff-animation + raw8 Fist regression PASS

Observed:
- `Montera_Orc_01` Staff-animation attacks used factual RIGHT source `It_Halberd_Orc_01` / UseType 51. The run contains 28 accepted RIGHT markers and 7 accepted OFF markers across Hack, Whirl, Quick-right, Quick-left, Power and Normal; every tested equipped family produced at least one native `ONDAMAGE Target=PC_Hero` after authored activation.
- The same Orc's unarmed attacks resolved factual `Fist` / raw8. Seventeen FIST markers were accepted across Normal and Power, with confirmed raw8 ownership/timing and native `Game.dll+0x0016E348` damage to `PC_Hero`.
- Orc finalization showed no outstanding collision obligation, repair/divergence, ownership anomaly, invariant warning or marker rejection.
- User visual observation: all tested Orc Staff and Fist attack types successfully damaged the player.

Scope / limits:
- One attributable Orc Staff/Fist run. “Staff” here names the animation set; the factual equipped source in this fixture is Halberd / UseType 51.
- Confirms the prepared Normal/Quick/Power/Whirl/Hack Staff-animation routes and raw8 Normal/Power routes in this actor/fixture; it does not generalize untested Orc weapon/source types.

Provenance:
- User upload commit `6d8a18ae6226cc2d9d435aa196708057810c0222`; integrated branch head `e6642f395598622a994f2594c7cccba5e2778b84`.
- Canonical archived log: `research/archive/2026-09-19_validation_orc_staff_fist_marker_test.log`.
- Git blob `d8c150b2ad19018b518e501c1c05014590a09810`; 231,860 bytes / 1,157 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- PASS — Orc Staff-animation equipped marker behavior and Orc raw8 Fist marker behavior pass the standalone regression fixture.
- Phase-2 Orc coverage continues only with the separate 2H-animation run below.

### EV-310 — Orc 2H-animation regression PASS

Observed:
- `Montera_Orc_Raider_01` 2H-animation attacks used factual RIGHT source `It_Axe_Orc_01` / UseType 52. The run contains 25 accepted RIGHT markers and 2 accepted OFF markers across Quick-right, Quick-left, Normal, Power, Hack and Whirl.
- Every tested 2H-animation family produced at least one native `ONDAMAGE Target=PC_Hero` after an accepted offensive marker.
- All Orc C1 finalizations were free of outstanding collision obligations; there were no ownership anomalies, invariant warnings, repair/divergence outcomes, unsupported classifications or marker rejections.
- User visual observation: all tested Orc 2H attack types successfully damaged the player.

Scope / limits:
- One attributable Orc Raider 2H-animation run. “2H” names the animation set; the factual equipped source in this fixture is Axe / UseType 52.
- Confirms the prepared Quick/Normal/Power/Hack/Whirl routes for this actor/source fixture; it is not a blanket claim about every Orc weapon.

Provenance:
- User upload commit `6d8a18ae6226cc2d9d435aa196708057810c0222`; integrated branch head `e6642f395598622a994f2594c7cccba5e2778b84`.
- Canonical archived log: `research/archive/2026-09-19_validation_orc_2h_marker_test.log`.
- Git blob `0652e65e096c8801b03eff804502693a9f82850d`; 82,693 bytes / 422 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- PASS — Orc 2H-animation marker behavior passes the standalone regression fixture.
- Together with EV-309, Phase 2 Orc attack-matrix coverage is CLOSED/PASS; next validation phase is the prepared other weapon-using creature/NPC set.


### EV-311 — Goblin 1H post-raw55 regression PASS + equipped-Sprint boundary discovery

Observed:
- `Goblin` used factual RIGHT source `It_1H_Club_01` / UseType 2. Eleven supported RIGHT markers were accepted across Normal and Quick-left/right, and all eleven were followed by native `ONDAMAGE Target=PC_Hero`.
- Supported executions cleaned the exact source back to group 5 and finalized with no outstanding obligation, repair/divergence or ownership/invariant failure.
- One additional PowerAttack-named execution was factually `Action=9 / Family=SPRINT`. Its equipped `G3AB_COL_RIGHT` marker was `REJECTED_UNSUPPORTED_HIT`, matching the current rule that equipped Sprint marker semantics are not production-supported.
- User visual observation: the tested Goblin attacks were able to damage the player.

Scope / limits:
- Post-raw55 regression control for the established Goblin 1H/raw2 marker route previously closed at EV-252.
- EV-311 adds a concrete factual equipped-Sprint fixture; it does **not** promote equipped Sprint marker support. Any such extension remains a separate future responsibility.
- No raw55/PhysicalFist intervention appeared in this log.

Provenance:
- User upload commit `181fb1eab09607771b1ef3ec16af5b5f34d4c887`.
- Canonical archived log: `research/archive/2026-09-19_validation_goblin_1h_marker_test.log`.
- Git blob `d9e20404324311faa3d058f4ecc293efc75c4b41`; 50,739 bytes / 301 lines.
- Diagnostic profile: CORE; user states this batch used the current/latest diagnostic DLL.

Disposition:
- PASS — established Goblin Normal/Quick 1H marker behavior remains compatible after the raw55 implementation.
- DEFERRED SCOPE DISCOVERY — factual equipped Sprint/right/raw2 exists, but current production correctly rejects that marker family; do not reinterpret native damage capability as marker support.

### EV-312 — Demon 2H/raw3 post-raw55 regression PASS

Observed:
- `Demon` used factual RIGHT source `It_2H_DemonSword_01` / UseType 3.
- Fifteen RIGHT markers were accepted across Normal, Quick-left/right and Power, and all fifteen were followed by native `ONDAMAGE Target=PC_Hero`.
- Finalization remained clean with no outstanding obligation, repair/divergence, marker rejection, ownership anomaly or invariant warning.
- User visual observation: all tested Demon attack types damaged the player.

Scope / limits:
- Post-raw55 regression control for the established Demon 2H/raw3 route previously closed at EV-253.
- No raw55/PhysicalFist intervention appeared in this log.

Provenance:
- User upload commit `181fb1eab09607771b1ef3ec16af5b5f34d4c887`.
- Canonical archived log: `research/archive/2026-09-19_validation_demon_2h_marker_test.log`.
- Git blob `02379f7a4a74c9051270e91f17299ddf1681cb90`; 84,214 bytes / 433 lines.
- Diagnostic profile: CORE; user states this batch used the current/latest diagnostic DLL.

Disposition:
- PASS — Demon 2H/raw3 marker behavior remains compatible after the raw55 implementation.

### EV-313 — Ogre Axe/raw52 post-raw55 regression PASS

Observed:
- `Ogre` used factual RIGHT source `It_Axe_OgreMorningStar_01` / UseType 52.
- Twelve RIGHT markers were accepted across Power, Normal and Quick-right, and all twelve were followed by native `ONDAMAGE Target=PC_Hero`.
- Completed Ogre generations carried no outstanding obligation or repair/divergence result; there were no marker rejections, ownership anomalies or invariant warnings.
- One cancelled candidate was followed by a native/unowned 5 -> 7 source transition; it was not a marker-owned obligation and did not produce a lifecycle contradiction.
- User visual observation: all tested Ogre attack types damaged the player.

Scope / limits:
- Post-raw55 regression control for the established Ogre Axe/raw52 route previously closed at EV-254.
- No raw55/PhysicalFist intervention appeared in this log.

Provenance:
- User upload commit `181fb1eab09607771b1ef3ec16af5b5f34d4c887`.
- Canonical archived log: `research/archive/2026-09-19_validation_ogre_2h_marker_test.log`.
- Git blob `c7b03b6969b93db018cdd0df8c5b2a74f6750118`; 59,860 bytes / 321 lines.
- Diagnostic profile: CORE; user states this batch used the current/latest diagnostic DLL.

Disposition:
- PASS — Ogre Axe/raw52 marker behavior remains compatible after the raw55 implementation.

### EV-314 — Stalker Axe/raw52 regression PASS

Observed:
- `Stalker` used factual RIGHT source `It_Axe_SpikedClub_01` / UseType 52.
- Twenty-five RIGHT markers were accepted across Normal, Power and Quick-right. Eighteen accepted opportunities produced native `ONDAMAGE Target=PC_Hero`; every tested family produced damage at least once.
- Non-damaging accepted opportunities are consistent with native contact/reaction geometry and did not leave collision obligations outstanding.
- Finalization showed no repair/divergence, marker rejection, ownership anomaly or invariant warning.
- User visual observation: all tested Stalker attack types damaged the player.

Scope / limits:
- New prepared weapon-using actor/source regression fixture.
- Confirms the tested Stalker Normal/Power/Quick-right routes on factual Axe/raw52; it does not generalize untested Stalker actions.
- No raw55/PhysicalFist intervention appeared in this log.

Provenance:
- User upload commit `181fb1eab09607771b1ef3ec16af5b5f34d4c887`.
- Canonical archived log: `research/archive/2026-09-19_validation_stalker_2h_marker_test.log`.
- Git blob `499caefc8471ffd7ab351e54ce443b1c9975df5a`; 117,929 bytes / 639 lines.
- Diagnostic profile: CORE; user states this batch used the current/latest diagnostic DLL.

Disposition:
- PASS — Stalker Axe/raw52 joins the current equipped-NPC regression coverage.
- Together with EV-311–EV-313, Phase 3 weapon-using creature/NPC regression is CLOSED/PASS for its prepared scope, with the equipped-Sprint fixture from EV-311 explicitly deferred as a separate unsupported scope question.

### EV-315 — Goblin equipped-Sprint generic marker causal handoff PASS

Observed:
- The committed run contains two factual Goblin `Action=9 / Family=SPRINT` Hit executions, C1 generations 59 and 79, using RIGHT source `It_1H_Club_01` / UseType 2 and motion `Goblin_Stand_None_1H_P0_PowerAttack_Hit_N_Fwd_00_%_00_P1_100_R.xmot`.
- In both executions the Goblin C1 begins with the RIGHT source at collision group 5. The diagnostic Sprint probe then records `CALLBACK Decision=SUPPRESS_NATIVE Reason=ELIGIBLE`; no Goblin RIGHT-source 5 -> 7 transition occurs before the authored marker.
- At the authored RIGHT event the probe records `MARKER Decision=AUTHORIZE_GENERIC_EQUIPPED Reason=BOUND_EXECUTION_MATCHED`. Generic marker processing then changes the exact RIGHT source 5 -> 7 and records `CORE MARKER ... Action=9 Family=SPRINT ... Marker=RIGHT Result=ACCEPTED`.
- Both factual Sprint executions are followed by native `ONDAMAGE Target=PC_Hero`, exact-source native cleanup 7 -> 5, `C1 CLEANUP FULFILLED`, and Goblin finalization with `Outstanding=0`.
- Later ordinary Goblin `Action=1 / Family=NORMAL` markers are explicitly `DENY_GENERIC_EQUIPPED Reason=NOT_FACTUAL_SPRINT_HIT` by the Sprint probe while the ordinary marker path still accepts them. This is a bounded scoping control showing the diagnostic Sprint permission does not own those Normal executions.
- No raw55 identity contradiction, generic ownership contradiction, invariant failure or Sprint marker rejection appears in the factual Sprint executions.
- User observation: Sprint and Power are difficult to distinguish visually because they share the animation; knockdown behavior suggested Sprint. The log resolves the identity factually as Action9/SPRINT.

Scope / limits:
- Causal PASS for the first EV-311 fixture only: Goblin, equipped RIGHT 1H/raw2, authored RIGHT marker, temporary diagnostic Sprint handoff.
- This does not yet prove LEFT/BOTH/OFF combinations, other equipped UseTypes/species, protected raw8/raw55/true-Power sentinels, or production support.
- Equipped Sprint remains unsupported in the current production/behavior baseline until the active diagnostic investigation completes and promotion is separately decided.

Provenance:
- User upload commit `f884659345a8572a9e476fadaab7e0031ab3c0a4`.
- Reviewed diagnostic implementation: `d2c6c8be0d56129ec6725571324a9066b181242c`.
- Built/live diagnostic DLL SHA256: `A42176DC0309662932089324565CAFBEC77DCA51D9CCCF2D3958B31CBD33CFC7`; build, deployment/hash and startup/load gates PASS.
- Canonical archived log: `research/archive/2026-09-19_equipped_sprint_goblin_right_raw2_causal_probe.log`.
- Git blob `2b534f564108f064b7fc7a043202df8c6cbdf483`; 161,165 bytes / 789 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- PASS — suppressing native early `OnAI_PowerAttack` timing allows the existing generic equipped marker mechanism to own the first factual Goblin Sprint RIGHT/raw2 fixture at authored marker timing while preserving native damage and cleanup.
- Active investigation continues with protected raw8 Sprint, raw55 Sprint-origin and equipped true-Power sentinels before broader equipped-Sprint fixtures or any permanent promotion decision.

### EV-316 — Sabretooth raw8 Sprint protected sentinel PASS

Observed:
- The current equipped-Sprint diagnostic build captured five factual native-Sabretooth `Action=9 / Family=SPRINT` executions: C1 generations 8, 34, 44, 55 and 109. Each used factual `Fist` / raw8 with `RequiredMask=0` and the PowerAttack-named Sprint motion.
- In every Sprint generation, existing raw8 ownership remained authoritative: `RAW8_FIST_OWNERSHIP ... InitialClose=0->1 Result=CONFIRMED`; the equipped-Sprint probe explicitly recorded `DELEGATE_NATIVE Reason=FIST_MARKER_PRESENT` rather than suppressing/claiming the callback.
- Each factual Sprint accepted `G3AB_COL_FIST` at `StatePosition=1`, confirmed latch rearm `1->0 / LatchConfirmed=1`, armed and consumed the existing bounded early timing permission, and produced native `ONDAMAGE Target=PC_Hero Arg2=Sabertooth Caller=Game.dll+0x0016E348`.
- All five Sprint C1 generations finalized with `Outstanding=0`, `PhysicalChanged=0` and `NO_OP_NO_OUTSTANDING`. No raw55 ownership contradiction, C1 invariant warning, lifecycle issue, repair divergence or unresolved equipped-source outcome appeared.
- New bounded observation: after the successful Action9/SPRINT FIST/contact in each of these five generations, the same PowerAttack-named motion later continued under factual `Action=2 / Family=POWER` within the same C1 and a later FIST dispatch was rejected as `REJECTED_C1_GENERATION_INCONSISTENCY`. The accepted Sprint FIST, raw8 timing permission, native damage and clean C1 finalization had already occurred before this replay/rejection. The older EV-251 sample did not capture this repeated Action9->Action2 replay shape. On the current evidence it is a fail-safe identity rejection after successful Sprint ownership, not a protected-raw8 regression and not equipped-Sprint ownership.

Scope / limits:
- Protected sentinel for native Sabretooth raw8 Sprint while the temporary equipped-Sprint diagnostic seam is present.
- Confirms that the new equipped-Sprint probe excludes FIST-marked Sprint and leaves the established raw8 mechanism operational in five current executions.
- The later Action2 same-C1 replay observation is preserved for future contradiction/reproduction checks; no source change or separate causal investigation is justified by this sentinel alone.

Provenance:
- User upload commit `d7c93d59f27d90752bea125ae351c9afec4ecf8e`.
- Reviewed diagnostic implementation: `d2c6c8be0d56129ec6725571324a9066b181242c`.
- Built/live diagnostic DLL SHA256: `A42176DC0309662932089324565CAFBEC77DCA51D9CCCF2D3958B31CBD33CFC7`.
- Canonical archived log: `research/archive/2026-09-19_equipped_sprint_sentinel_sabretooth_raw8_sprint.log`.
- Git blob `2c6a0faff392436d85dc9f4fedca070c0e26a715`; 400,433 characters / 1,547 lines.
- Diagnostic profile: CORE; DEEP disabled.
- Comparison baseline: EV-251 / `research/archive/2026.09.11_sprint_raw8_production_validation.log`.

Disposition:
- PASS — raw8 Sprint remains protected under the generic equipped-Sprint diagnostic seam, and FIST-marked Sprint is explicitly delegated rather than claimed.
- Active investigation advances to the raw55 Sprint-origin protected sentinel.

### EV-317 — Troll raw55 Sprint-origin protected sentinel PASS

Observed:
- The current equipped-Sprint diagnostic build captured four factual Troll raw55 Sprint-origin executions: C1 generations 9, 21, 37 and 58. Each used exact current RIGHT `TrollFist` / PhysicalFist raw55 with factual origin `Action=9 / Family=SPRINT`.
- In all four Sprint-origin executions, the temporary equipped-Sprint probe explicitly records `DELEGATE_NATIVE Reason=FIST_MARKER_PRESENT`; it does not suppress or claim the FIST/raw55 callback path.
- Permanent raw55 ownership remains intact: `RAW55_PHYSICAL_FIST_NATIVE_OPEN_SUPPRESSED` suppresses the premature exact RIGHT raw55 `5 -> 7` opening while the callback/state progression continues.
- At the authored FIST in each sampled Sprint-origin C1, `RAW55_PHYSICAL_FIST_MARKER` records `OriginFamily=SPRINT`, `CurrentFamily=SPRINT`, `Action=9`, `StatePosition=1`, `GroupBefore=5`, `GroupAfter=7`, `EarlyOpeningSuppressed=1`, `GroupRequested=1`, `ClearTriggeredList=0`; the ordinary marker record is `FIST Result=ACCEPTED`.
- Each sampled Sprint-origin execution produces native damage to `PC_Hero`, then continues within the same C1 after factual `Action9 -> Action2`; the temporary equipped-Sprint probe correctly reports `DELEGATE_NATIVE Reason=NOT_SPRINT_FAMILY` during the later Action2 tail while permanent raw55 Sprint-origin ownership remains the established semantic owner.
- Gothic later performs native exact RIGHT cleanup `7 -> 5`; C1 generations 9, 21, 37 and 58 each record `C1 CLEANUP FULFILLED` and finalize with `Outstanding=0`, `Cleanup=1`, `PhysicalChanged=0`, `NO_OP_NO_OUTSTANDING`.
- Whole-log scan found no contradiction, invariant warning, lifecycle issue, repair divergence, unresolved equipped-source outcome, rejected marker, or `ReplacedOutstanding=1`.

Scope / limits:
- Protected sentinel for permanent raw55 Sprint-origin behavior while the temporary generic equipped-Sprint diagnostic seam is present.
- Confirms coexistence for the tested Troll RIGHT raw55 Sprint-origin route; it does not broaden raw55 production scope beyond the existing permanent architecture.
- No production equipped-Sprint promotion follows from this sentinel alone.

Provenance:
- User upload commit `a505aee3ec70476fd8d034b4b314d262dd69b8a0`.
- Reviewed diagnostic implementation: `d2c6c8be0d56129ec6725571324a9066b181242c`.
- Built/live diagnostic DLL SHA256: `A42176DC0309662932089324565CAFBEC77DCA51D9CCCF2D3958B31CBD33CFC7`.
- Canonical archived log: `research/archive/2026-09-19_equipped_sprint_sentinel_raw55_sprint_origin.log`.
- Git blob `b83196b0bfd5f8770f26f06bcc4cd91694f35a55`; 177,635 characters / 680 lines.
- Diagnostic profile: CORE; DEEP disabled.
- Comparison baseline: raw55 Sprint-origin closure EV-280–EV-285, EV-294 and permanent focused acceptance EV-298.

Disposition:
- PASS — permanent raw55 Sprint-origin behavior remains protected under the temporary generic equipped-Sprint diagnostic seam.
- Active investigation advances to the final protected sentinel: one equipped true-Power route.

### EV-318 — equipped true-Power protected sentinel PASS

Observed:
- The current generic equipped-Sprint diagnostic build was exercised with player 2H true Power using exact RIGHT `It_2H_Sword_Flamberge` / UseType 3 against Golem.
- The log contains 19 explicit `CORE ATTACK_OWNERSHIP Actor=PC_Hero Family=POWER Action=2` callback-ownership records. Every one is `MarkerPresent=1 RequiredMask=1 FistMarkers=0 SuppressNative=1 Classification=ROUTINE`, confirming the established generic equipped-Power callback owner remains authoritative.
- The run contains 25 distinct accepted factual `Action=2 / Family=POWER` RIGHT-marker C1 generations: 1, 3, 14, 21, 24, 34, 41, 46, 52, 58, 72, 77, 83, 89, 95, 101, 108, 114, 120, 126, 135, 139, 142, 146 and 150. Each accepted RIGHT marker activates the exact Flamberge source and each of those 25 C1 generations later records `C1 CLEANUP FULFILLED ... Group=5` and `C1_FINAL ... Outstanding=0` without repair.
- Twelve factual true-Power contacts produce native `CORE ONDAMAGE Target=Golem` while the player remains `PlayerAction=2` in a PowerAttack Hit motion.
- There are zero `CORE EQUIPPED_SPRINT_PROBE` records for `Actor=PC_Hero`. This matches hook ordering: existing `EvaluateAttackCallback(... AttackFamily_Power ...)` returns `suppressNativeCallback=true` for supported equipped Power and returns from the callback before the diagnostic Sprint probe is consulted. The Sprint diagnostic seam therefore does not participate in or reclassify these true-Power executions.
- Whole-log checks found zero true-Power marker rejection, zero nonzero PC_Hero finalization, zero terminal repair, zero ownership contradiction, zero invariant warning, zero lifecycle issue, zero repair divergence and zero `ReplacedOutstanding=1`.

Scope / limits:
- Protected coexistence sentinel for the established equipped true-Power route while the temporary generic equipped-Sprint diagnostic seam is present.
- Confirms that the Sprint diagnostic work does not steal or alter supported player 2H true-Power ownership.
- This completes the three protected sentinels required after EV-315; it does not by itself prove additional equipped-Sprint UseTypes or LEFT/BOTH/OFF Sprint authoring.

Provenance:
- User upload branch state/head: `193c7d6548f1dbce8e8e28f6e66c173be4dde31b`.
- Reviewed diagnostic implementation: `d2c6c8be0d56129ec6725571324a9066b181242c`.
- Built/live diagnostic DLL SHA256: `A42176DC0309662932089324565CAFBEC77DCA51D9CCCF2D3958B31CBD33CFC7`.
- Canonical archived log: `research/archive/2026-09-19_equipped_sprint_sentinel_equipped_true_power_2h.log`.
- Git blob `4f27c15c7ad184126c382f2feb49c8efce6226be`; 335,919 characters / 1,395 lines.
- Diagnostic profile: CORE; DEEP disabled.
- Comparison baseline: equipped Power support EV-241–EV-244 and current player 2H regression EV-302.

Disposition:
- PASS — established equipped true Power remains structurally and behaviorally isolated from the temporary equipped-Sprint diagnostic seam.
- Protected sentinel stage is COMPLETE/PASS: raw8 Sprint EV-316, raw55 Sprint-origin EV-317, equipped true Power EV-318.
- Active investigation advances to additional factual equipped-Sprint fixtures across other available equipped UseTypes/animation sets before any permanent-promotion decision.

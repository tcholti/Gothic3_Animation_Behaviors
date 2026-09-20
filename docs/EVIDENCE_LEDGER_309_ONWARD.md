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

### EV-319 — Ogre raw52 broader equipped-Sprint fixture NOT EXERCISED / regression healthy

Observed:
- The broader equipped-Sprint fixture attempt used `Ogre` with exact RIGHT `It_Axe_OgreMorningStar_01` / UseType 52 under the current diagnostic Sprint build.
- The complete run contains **zero factual Ogre `Action=9 / Family=SPRINT` executions**. Therefore this run does not test the generic equipped-Sprint causal handoff for raw52 and cannot be counted as a Sprint PASS or FAIL.
- Ogre instead exercised 10 factual true-Power ownership events, 10 Normal events and 6 Quick events. Twenty-eight Ogre RIGHT markers were accepted and 26 native damage events targeted `PC_Hero`.
- All 72 Ogre C1 finalizations record `Outstanding=0`. No Ogre terminal repair was required.
- Whole-log checks found no marker rejection, ownership contradiction, invariant warning, lifecycle issue, repair divergence, unresolved equipped-source outcome or `ReplacedOutstanding=1`.

Interpretation:
- **NOT EXERCISED** for the intended Sprint/raw52 question because the factual Action9 condition never occurred.
- The run is still a healthy current-build regression control for Ogre Normal/Quick/true-Power raw52 and provides no evidence of collateral breakage.
- Do not generalize EV-315's Goblin Sprint PASS to raw52 from this run.

Provenance:
- User upload branch state/head: `72889c76d6f493d7ffcfecc5ee55763b3e42411d`.
- Reviewed diagnostic implementation: `d2c6c8be0d56129ec6725571324a9066b181242c`.
- Built/live diagnostic DLL SHA256: `A42176DC0309662932089324565CAFBEC77DCA51D9CCCF2D3958B31CBD33CFC7`.
- Canonical archived log: `research/archive/2026-09-19_equipped_sprint_ogre_raw52_causal_fixture.log`.
- Git blob `89482478d09fd4756a95bdb2d25cc67b781f203c`; 330,147 characters / 1,719 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- Do not repeat this same Ogre setup merely to accumulate ordinary Power/Normal/Quick traffic.
- Continue broader Sprint-fixture discovery using evidence for which actors/routes can factually enter Action9.

### EV-320 — Goblin Sprint RIGHT -> OFF controlled fixture exposes origin-continuation gap

Observed:
- The controlled motion keeps the known factual Goblin Sprint route and authors `RIGHT` followed later by `OFF`; complete-motion scan remains `RequiredMask=1` because OFF is non-activating.
- Four factual Goblin Action9/SPRINT executions accepted the authored RIGHT marker through the diagnostic Sprint handoff. In the three executions that reached the authored OFF (C1 6, 80 and 112), RIGHT was first authorized under factual Sprint and opened the exact club `5 -> 7`; native damage to `PC_Hero` occurred before OFF in the sampled sequences.
- Before OFF fired, Gothic changed the same C1 and same PowerAttack-named motion from factual Action9/SPRINT to Action2/POWER.
- At OFF, `EquippedSprintProbe` denied authorization with `NOT_FACTUAL_SPRINT_HIT` even though actor, C1 generation, motion, required-source mask and exact RIGHT source still belonged to the already-bound Sprint execution.
- The generic marker layer then rejected OFF as `REJECTED_C1_GENERATION_INCONSISTENCY` because its marker-owned window/budget identity is action-sensitive: the window was opened under Action9 and OFF arrived under Action2.
- Native cleanup later returned the club `7 -> 5`; the affected C1s finalized `Outstanding=0`.
- User observation: Goblin damaged the player during the test.

Interpretation:
- RIGHT Sprint handoff remains confirmed.
- The intended RIGHT -> OFF Sprint continuation is **not yet supported by the current diagnostic implementation**.
- This is a real same-execution identity gap, not a malformed animation: the same C1/motion/source survives while Gothic changes factual action 9 -> 2 before the later marker.
- The permanent raw55 architecture already has the relevant precedent: immutable Sprint origin may continue under current Power only when the same execution identity remains intact.
- Do not solve this by weakening generic action identity globally. The correction must be bounded to an already-bound Sprint-origin execution and preserve exact C1/motion/source identity.

Provenance:
- User upload commit `11cec8b2cd285dd2a6cd09482dd893c97630fd62`.
- Diagnostic implementation under test: `d2c6c8be0d56129ec6725571324a9066b181242c`.
- Built/live DLL SHA256: `A42176DC0309662932089324565CAFBEC77DCA51D9CCCF2D3958B31CBD33CFC7`.
- Canonical archived log: `research/archive/2026-09-19_sprint_goblin_on_off_marker_test.log`.
- Git blob `4d6b386b74d466b5d2a83deddd87208807f05f6d`; 209,735 characters / 1,089 lines.

Disposition:
- TARGETED CORRECTION REQUIRED before production-promotion decision.
- Freeze a bounded diagnostic-only Sprint-origin continuation correction; no further random vanilla fixture testing is useful until that gap is resolved.

### EV-321 — Goblin Sprint BOTH with missing LEFT negative fixture PASS

Observed:
- The controlled Goblin Sprint motion authors `BOTH`, producing complete-motion `RequiredMask=3` (RIGHT | LEFT).
- The Goblin has exact RIGHT `It_1H_Club_01` / raw2 and no LEFT source.
- Factual Action9/SPRINT is captured repeatedly. At callback time the generic ownership diagnostic reports required sources unavailable and the Sprint probe repeatedly records `DELEGATE_NATIVE Reason=REQUIRED_EQUIPPED_SOURCE_MISSING`.
- No Sprint binding is created. At the authored BOTH marker, the probe records `DENY_GENERIC_EQUIPPED Reason=NO_BOUND_EXECUTION`; the marker is rejected as `REJECTED_UNSUPPORTED_HIT`.
- Because the diagnostic probe delegates instead of suppressing the native Power callback, Gothic opens the factual RIGHT club natively `5 -> 7`, can damage `PC_Hero`, and later cleans the club `7 -> 5`.
- Three complete sampled Sprint C1s (8, 34, 45) show this reject/native-fallback/cleanup pattern and finalize `Outstanding=0`; a fourth Sprint C1 is interrupted before the authored marker.
- The `Classification=CONTRADICTION` ownership diagnostic is expected in this deliberately malformed source-availability fixture: that logger defines a marked motion requiring an unavailable equipped source as a contradiction. It is the intended negative-test condition, not evidence that the fail-closed policy malfunctioned.
- User observation: Goblin damaged the player with the BOTH-authored motion; runtime evidence confirms that damage came from the delegated native path rather than accepted BOTH marker ownership.

Interpretation:
- **NEGATIVE PASS.**
- Complete-motion required-source validation prevents partial BOTH ownership when LEFT is missing.
- Native fallback remains intact when the generic Sprint probe declines ownership.

Provenance:
- User upload commit `11cec8b2cd285dd2a6cd09482dd893c97630fd62`.
- Diagnostic implementation under test: `d2c6c8be0d56129ec6725571324a9066b181242c`.
- Built/live DLL SHA256: `A42176DC0309662932089324565CAFBEC77DCA51D9CCCF2D3958B31CBD33CFC7`.
- Canonical archived log: `research/archive/2026-09-19_sprint_goblin_both_marker_test.log`.
- Git blob `961a6b7a12dc44d9d8354246409b0d674967b73e`; 134,769 characters / 716 lines.

Disposition:
- PASS — the generic required-source gate fails closed and preserves native fallback for a Sprint BOTH motion when LEFT is absent.

### EV-322 — equipped Sprint origin-continuation RIGHT -> OFF correction PASS

Observed:
- Runtime validation used the reviewed correction implementation `c338d9224a4de6b81466ba5b9e2a3e3c8ba67f86` with the controlled Goblin Sprint RIGHT -> OFF fixture from EV-320.
- Eight factual Goblin Action9/SPRINT executions accepted the authored RIGHT marker. Six executions on the P0 fixture motion reached the authored OFF after Gothic changed current factual state to Action2/POWER: C1 generations 24, 34, 45, 84, 92 and 101.
- In all six complete continuations, RIGHT first opened exact `It_1H_Club_01` / raw2 `5 -> 7`; the later OFF marker was explicitly authorized by `EquippedSprintProbe` with `Reason=BOUND_SPRINT_ORIGIN_POWER_CONTINUATION`.
- All six OFF markers remained factually visible as `Action=2 Family=POWER` and returned `Result=OFF_ACCEPTED`.
- At OFF timing the exact club was deactivated `7 -> 5`; each C1 recorded `C1 CLEANUP FULFILLED` and finalized `Outstanding=0`.
- The run contains zero OFF rejection, zero `REJECTED_C1_GENERATION_INCONSISTENCY`, zero nonzero Goblin finalization, zero terminal repair and no invariant/lifecycle/repair-divergence flag.
- The two other factual Sprint executions used the alternate P1 PowerAttack motion and did not exercise the authored OFF fixture; they are not counted against the RIGHT -> OFF acceptance question.
- Native contact remained possible; the run contains 19 `ONDAMAGE Target=PC_Hero` events overall.

Interpretation:
- **PASS.**
- EV-320's exact defect is corrected: immutable Sprint-origin execution identity now survives the proven same-C1 Action9 -> Action2 transition long enough for the later generic OFF marker to close the marker-owned window.
- Factual current Action2 remains visible in diagnostics while generic marker bookkeeping stays coherent to the bound Sprint origin.
- This result does not yet close the correction as a whole; the EV-321 missing-LEFT/BOTH negative rerun and EV-318 true-Power protected control remain required.

Provenance:
- User upload commit `514aad0f55ab9e3f90076ff832c598c5d83d32fc`.
- Reviewed correction implementation: `c338d9224a4de6b81466ba5b9e2a3e3c8ba67f86`.
- Canonical archived log: `research/archive/2026-09-19_sprint_origin_continuation_right_off_validation.log`.
- Git blob `011c674b890593c4a69b18d46902842df8b1a41f`; 206,966 characters / 940 lines.
- Diagnostic profile: CORE; DEEP disabled.
- Startup/load gate passed before this run. The POP-03 built/live SHA256 was not reproduced in the chat transcript for this validation cycle; the runtime log itself contains the correction-specific `BOUND_SPRINT_ORIGIN_POWER_CONTINUATION` signature from the reviewed implementation.

Disposition:
- Positive correction gate PASS.
- Next required runtime gate: rerun EV-321 BOTH with LEFT absent and require the prior fail-closed/native-fallback behavior to remain intact.

### EV-323 — equipped Sprint BOTH with missing LEFT negative rerun PASS after continuation correction

Observed:
- Runtime negative-control validation used correction implementation `c338d9224a4de6b81466ba5b9e2a3e3c8ba67f86` with the controlled Goblin P0 Sprint motion authored with `BOTH`.
- Four factual P0 Action9/SPRINT executions scanned `RequiredMask=3` (RIGHT | LEFT): C1 generations 42, 51, 81 and 100. The Goblin had exact RIGHT `It_1H_Club_01` / raw2 and no LEFT source.
- All four repeatedly delegated native at callback time with `REQUIRED_EQUIPPED_SOURCE_MISSING`; there were zero `SUPPRESS_NATIVE Reason=ELIGIBLE` decisions for `RequiredSourceMask=3` and zero `BOUND_SPRINT_ORIGIN_POWER_CONTINUATION` authorizations for that mask.
- C1 42, 81 and 100 reached BOTH while still factual Sprint: no Sprint binding existed, the probe logged `DENY_GENERIC_EQUIPPED Reason=NO_BOUND_EXECUTION`, and generic marker processing returned `REJECTED_UNSUPPORTED_HIT`.
- C1 51 transitioned to factual Action2/POWER before BOTH. The probe continued to report `NO_BOUND_SPRINT_ORIGIN`; generic Power-family marker processing then rejected BOTH as `UNSUPPORTED_MISSING_SOURCE`. This is also fail-closed and does not create/inherit Sprint ownership.
- In all four complete P0 executions, Gothic's delegated native path opened the exact RIGHT club `5 -> 7`, native damage to `PC_Hero` occurred, native cleanup returned the club `7 -> 5`, and the Goblin C1 finalized `Outstanding=0`.
- Whole-log scan found zero nonzero Goblin finalizations, zero terminal repair, and no invariant/lifecycle/repair-divergence flag.

Interpretation:
- **NEGATIVE PASS.**
- The EV-320 continuation correction did not weaken complete-motion required-source validation.
- A Sprint motion requiring BOTH cannot acquire partial RIGHT-only marker ownership when LEFT is absent.
- A later same-C1 Action2 state without a prior Sprint binding remains outside Sprint-origin continuation and is still rejected by missing-source validation.
- Native fallback remains intact.

Provenance:
- User upload commit `ae09db4ef2ec610430c247976969abf9c27498ea`.
- Reviewed correction implementation: `c338d9224a4de6b81466ba5b9e2a3e3c8ba67f86`.
- Canonical archived log: `research/archive/2026-09-19_sprint_origin_continuation_both_missing_left_negative_validation.log`.
- Git blob `ebd813a2fabbd4a0f249652b66d69309711799d0`; 226,802 characters / 1,135 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- EV-321 negative-control semantics are preserved under the corrected implementation.
- One required runtime gate remains before correction closure: the EV-318 equipped true-Power protected control.

### EV-324 — equipped true-Power protected control PASS after Sprint-origin correction

Observed:
- Runtime protected-control validation used implementation `c338d9224a4de6b81466ba5b9e2a3e3c8ba67f86` with the established player 2H true-Power fixture: `PC_Hero`, exact RIGHT `It_2H_Sword_Flamberge` / UseType 3, Golem target.
- Twelve ordinary equipped-Power ownership records were observed with factual `Action=2 / Family=POWER`, `RequiredMask=1`, `FistMarkers=0`, `SuppressNative=1`, `Classification=ROUTINE`.
- Fourteen factual Power RIGHT markers were accepted on the Flamberge. Fourteen matching cleanup events returned the exact source to group 5.
- Eight native `ONDAMAGE Target=Golem` contacts occurred while `PlayerAction=2`.
- There were **zero** `EQUIPPED_SPRINT_PROBE` records for `Actor=PC_Hero` and zero `BOUND_SPRINT_ORIGIN_POWER_CONTINUATION` signatures anywhere in the run.
- There were zero true-Power marker rejections, zero nonzero PC_Hero finalizations, zero terminal repairs, and no contradiction/invariant/lifecycle/repair-divergence flag.

Interpretation:
- **PASS.**
- Ordinary equipped true Power remains structurally upstream/outside the diagnostic Sprint-origin seam after the EV-320 correction.
- The correction does not fabricate Sprint origin for a new true-Power execution.
- Together with EV-322 positive RIGHT->OFF and EV-323 missing-LEFT/BOTH negative rerun, this completes the bounded Sprint-origin continuation correction runtime acceptance.

Provenance:
- User upload commit `01ace221d5049803fa27166ca00e21eb6a596a8c`.
- Reviewed correction implementation: `c338d9224a4de6b81466ba5b9e2a3e3c8ba67f86`.
- Canonical archived log: `research/archive/2026-09-19_sprint_origin_continuation_true_power_protected_validation.log`.
- Git blob `01b57db6f3450d06ab6c5ab66c48b4e6a654a81d`; 57,783 characters / 330 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- PASS — bounded correction acceptance COMPLETE.
- Next responsibility returns to the parent generic equipped-Sprint investigation: decide whether the now-proven diagnostic architecture should be promoted into production behavior, without performing that promotion implicitly.

### EV-325 — promoted equipped Sprint intended RIGHT->OFF artifact NOT EXERCISED AS NAMED

Observed:
- The uploaded file named `2026-09-20_equipped_sprint_production_right_off_validation.log` did not contain the intended P0 RIGHT->OFF authored fixture.
- Its P0 Sprint motion `Goblin_Stand_None_1H_P0_PowerAttack_Hit_N_Fwd_00_%_00_P1_100_R.xmot` scanned `RequiredMask=3` and emitted BOTH plus a later OFF while the Goblin had exact RIGHT `It_1H_Club_01` / raw2 and no LEFT source.
- Complete P0 generations 22, 50, 62, 74 and 83 therefore followed the missing-source/native-fallback path: native RIGHT opened 5->7; BOTH and later OFF were rejected/fail-closed; native damage occurred; exact RIGHT cleaned 7->5; finalization ended `Outstanding=0`.
- The same log also contains two separate P1 Sprint executions, C1 31 and 41, whose different P1 motion scanned `RequiredMask=1`; RIGHT was authorized/accepted and cleaned normally.
- No accepted OFF occurs for the intended positive P0 fixture in this artifact. No generation-inconsistency, repair, lifecycle, or outstanding-finalization anomaly was observed.

Scope / limits:
- This artifact cannot be used as the promoted RIGHT->OFF positive acceptance control because the authored P0 marker shape does not match the filename/intended setup.
- It is still valid runtime evidence for fail-closed malformed/missing-source behavior and for unrelated P1 RIGHT-only Sprint behavior.
- The stronger EV-326 RIGHT->OFF->RIGHT run independently covers and exceeds the required positive continuation control, so no separate RIGHT->OFF rerun is required.

Provenance:
- Integrated uploaded batch head: `d54bbca1fd9b101b5d18b95d049169381426984a`.
- Promoted implementation: `218c7ab73815a9afc46fc3ea5ac7246998bc2b1b`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_equipped_sprint_production_right_off_validation.log`.
- Git blob `d7fc25da8b6239d59778c55fae98510dd0d57cc1`; 210,656 characters / 1,200 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **NOT EXERCISED AS NAMED / SAFE MIXED FIXTURE.**
- Do not cite this artifact as a RIGHT->OFF positive pass.
- No source correction is indicated.

### EV-326 — promoted equipped Sprint RIGHT->OFF->RIGHT production control PASS

Observed:
- Seven complete factual Goblin P0 Sprint executions, C1 generations 10, 19, 27, 35, 48, 60 and 71, used exact RIGHT `It_1H_Club_01` / raw2 and `RequiredMask=1`.
- Every execution repeated the same permanent production sequence:
  - factual Action9/SPRINT callback -> `EQUIPPED_SPRINT_COLLISION SUPPRESS_NATIVE Reason=ELIGIBLE`;
  - authored RIGHT -> `BOUND_EXECUTION_MATCHED`, RIGHT accepted, exact club 5->7;
  - native damage to `PC_Hero`;
  - same C1 becomes factual Action2/POWER;
  - authored OFF -> `BOUND_SPRINT_ORIGIN_POWER_CONTINUATION`, OFF accepted, exact club 7->5;
  - later authored RIGHT under the same continuation -> authorized, accepted, exact club 5->7;
  - native cleanup returns exact club 7->5;
  - C1 finalizes `Outstanding=0 / NO_OP_NO_OUTSTANDING`.
- All seven executions therefore show physical sequence `5->7 -> 7->5 -> 5->7 -> 7->5` with two offense requests and clean lifecycle closure.
- No `REJECTED_C1_GENERATION_INCONSISTENCY`, marker rejection, repair, invariant, lifecycle, or nonzero-finalization failure appears in the relevant executions.

Scope / limits:
- Production-promotion diagnostic acceptance for the established Goblin P0 Sprint/right/raw2 fixture on the permanent `EquippedSprintCollision` implementation.
- This run is stronger than the original EV-322 RIGHT->OFF control because it also proves same-C1 reactivation after OFF under immutable Sprint-origin continuation.
- It does not replace the separate ordinary true-Power protected control.

Provenance:
- Integrated uploaded batch head: `d54bbca1fd9b101b5d18b95d049169381426984a`.
- Promoted implementation: `218c7ab73815a9afc46fc3ea5ac7246998bc2b1b`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_equipped_sprint_production_right_off_right_validation.log`.
- Git blob `faeb2aefc116d17a8523b8aaa705e2598843c679`; 159,514 characters / 716 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- The permanent promoted Sprint owner preserves exact Action9-origin continuity across Action2 and supports OFF plus later same-C1 reactivation through existing generic equipped semantics.
- This closes the positive Sprint continuation runtime gate for production promotion.

### EV-327 — promoted equipped Sprint BOTH with missing LEFT negative control PASS

Observed:
- Five complete factual Goblin P0 Sprint executions, C1 generations 15, 32, 42, 53 and 60, scanned `RequiredMask=3` with exact RIGHT `It_1H_Club_01` / raw2 present and LEFT absent.
- The permanent Sprint owner repeatedly delegated native with `REQUIRED_EQUIPPED_SOURCE_MISSING`; no Sprint binding was created.
- Native Gothic behavior opened RIGHT 5->7 and produced damage to `PC_Hero` in every sampled execution.
- When BOTH arrived while current action was still Sprint (C1 15 and 42), the permanent owner denied `NO_BOUND_EXECUTION` and marker processing reported `REJECTED_UNSUPPORTED_HIT`.
- When the same native execution had already become Action2/POWER before BOTH (C1 32, 53 and 60), no Sprint origin existed and generic processing reported `UNSUPPORTED_MISSING_SOURCE`.
- All five executions later cleaned exact RIGHT 7->5 and finalized `Outstanding=0 / NO_OP_NO_OUTSTANDING`.
- No partial authored RIGHT ownership, continuation authorization, generation-inconsistency, repair, invariant, lifecycle, or nonzero-finalization failure appeared.

Scope / limits:
- Negative production-promotion control for complete-motion BOTH requirements when LEFT is absent.
- Confirms the permanent extraction preserves the EV-321/EV-323 fail-closed boundary and native fallback.
- Does not test a real actor with both required equipped sources present.

Provenance:
- Integrated uploaded batch head: `d54bbca1fd9b101b5d18b95d049169381426984a`.
- Promoted implementation: `218c7ab73815a9afc46fc3ea5ac7246998bc2b1b`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_equipped_sprint_production_both_validation.log`.
- Git blob `60321380a1c975a311aa4b16dfb59a057b876a40`; 169,381 characters / 881 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **NEGATIVE PASS.**
- Missing required LEFT cannot produce partial authored Sprint ownership; native fallback and cleanup remain intact.
- This closes the missing-source negative runtime gate for production promotion.

### EV-328 — promoted equipped Sprint ordinary true-Power protected control PASS

Observed:
- The promoted permanent equipped-Sprint diagnostic binary captured nine ordinary `PC_Hero Action=2 / Family=POWER` ownership records using exact RIGHT `It_2H_Sword_Flamberge` / UseType 3.
- All nine ownership records remained under the established generic equipped-Power owner with `SuppressNative=1 / Classification=ROUTINE`.
- Nine factual Power RIGHT markers were accepted and nine native `ONDAMAGE Target=Golem` events occurred while `PlayerAction=2`.
- There were **zero** `EQUIPPED_SPRINT_COLLISION` records for `Actor=PC_Hero`.
- There were **zero** `BOUND_SPRINT_ORIGIN_POWER_CONTINUATION` signatures anywhere in the run.
- There were zero true-Power marker rejections, zero PC_Hero nonzero finalizations, zero repair events, and no contradiction/invariant/lifecycle/repair-divergence flag.

Scope / limits:
- Production-promotion protected control for ordinary equipped true Power on the established player 2H/Flamberge/raw3 fixture.
- Confirms the permanent Sprint extraction does not steal, fabricate or inherit Sprint ownership for a new true-Power execution.
- Does not replace the final diagnostics-free behavior-only Goblin Sprint smoke.

Provenance:
- User upload commit/head `807a52cdaaae6ae56df06df285d340950ee00737`.
- Promoted implementation: `218c7ab73815a9afc46fc3ea5ac7246998bc2b1b`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_equipped_sprint_production_true_power_protected_validation.log`.
- Git blob `ddfdb72c1c9a3fed2dcc48a71e7134eb175b7c9e`; 180,803 characters / 693 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Ordinary equipped true Power remains isolated from the permanent Sprint owner after production extraction.
- Together with EV-326 positive continuation and EV-327 missing-source negative control, all diagnostic runtime gates for the production promotion are now complete.

### EV-329 — diagnostics-free behavior-only equipped Sprint smoke PASS

Observed:
- The already-built behavior-only twin `Script_FrameCollisionBehaviorTest.dll` was redeployed as the sole live collision twin.
- Built/live SHA256 matched exactly: `FE31030B35868EBF30B9644650991D8136625C4DBFD6263403350DB612BDB250`.
- Deployment reported `BEHAVIOR DEPLOYMENT PASS`.
- The user then performed the known Goblin P0 Sprint gameplay fixture with the permanent diagnostics-free product and reported that all tested behavior appeared to work normally.

Scope / limits:
- This is the final diagnostics-free product smoke required by the production-promotion contract.
- It is intentionally a user-observed gameplay smoke: the behavior-only twin produces no diagnostic log, so this entry does not claim new causal detail beyond the log-backed EV-326–EV-328 controls.
- Exact positive/negative/true-Power causal semantics remain grounded in EV-326, EV-327 and EV-328 respectively.

Provenance:
- Permanent implementation: `218c7ab73815a9afc46fc3ea5ac7246998bc2b1b`.
- Behavior-only DLL SHA256: `FE31030B35868EBF30B9644650991D8136625C4DBFD6263403350DB612BDB250`.
- User runtime observation on 2026-09-20 after sole-live behavior deployment/hash verification.

Disposition:
- **PASS.**
- Diagnostics-free product acceptance for permanent equipped Sprint is complete.
- Together with source review, both builds/startups, EV-326 positive continuation, EV-327 missing-source negative, and EV-328 true-Power protection, this closes the production-promotion acceptance.

### EV-330 — current-build Orc Whirl RIGHT->OFF->RIGHT + player 1H spot-check PASS

Observed:
- Current diagnostic build rechecked Orc Staff-animation behavior on exact RIGHT `It_Halberd_Orc_01` / UseType 51.
- Three complete factual Orc Whirl executions, C1 generations 12, 23 and 31, each authored:
  `RIGHT -> OFF -> RIGHT`.
- Every Whirl repeated the same physical sequence:
  `5->7 -> 7->5 -> 5->7 -> 7->5`.
- Each Whirl recorded two authored offense requests and finalized with the exact Halberd source `Outstanding=0 / Cleanup=1 / NO_OP_NO_OUTSTANDING`.
- Native damage occurred in two of the three Whirls; the non-contact Whirl still executed the full authored source-window lifecycle correctly.
- The same log also spot-checked player ordinary 1H/raw2 marker behavior against the Orc: Normal RIGHT was accepted, opened `It_1H_Sword_Rust_01` 5->7, damaged the Orc, cleaned 7->5 and finalized cleanly. A Quick-left motion also accepted RIGHT on the factual RIGHT sword source and cleaned correctly, although that particular swing did not contact.
- Broader Orc Staff marker traffic in the same run remained accepted across Hack, Normal, Whirl and Power.
- No contradiction, invariant, lifecycle, repair-divergence or unresolved equipped-source flag appeared.

Scope / limits:
- Current-build corroboration of already-established OFF-gap/reactivation semantics and ordinary player 1H source behavior.
- This is not a new semantic extension: it confirms the present accepted build still implements previously proven RIGHT/OFF/repeated-contact behavior.
- Lack of damage on an individual accepted opportunity is not treated as failure because contact/geometry remain Gothic-owned.

Provenance:
- User upload batch head: `e4642a2d662a82e1594d00a260dd438f2a6176dd`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_orc_current_build_whirl_marker_on_off_on_recheck.log`.
- Git blob `6c6aadd7b7e7e357ee5b6f63606e042ccff1d0e9`; 86,975 characters / 458 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS / CORROBORATION.**
- Current accepted build preserves Orc Whirl OFF-gap reactivation and ordinary player 1H marker behavior.

### EV-331 — current-build Orc repeated-RIGHT Whirl + raw8 + player 1H+torch coexistence PASS

Observed:
- Four Orc Whirl C1s (7, 30, 39, 60) each authored two accepted RIGHT markers with no OFF between them.
- The exact Halberd/raw51 source followed the established repeated-contact shape: first RIGHT opened 5->7; second RIGHT requested 7 while already at 7 and rearmed contact bookkeeping; native cleanup later returned the source 7->5. Every sampled Whirl finalized `Outstanding=0 / Cleanup=1`.
- The repeated second RIGHT was therefore not deduped away merely because the source was already active.
- Orc raw8 Fist also remained healthy: seven accepted FIST markers across Normal and Power produced seven native damage events to `PC_Hero`. The established raw8 early-permission path armed/consumed normally in sampled complete C1s and finalized without outstanding collision obligation.
- Player raw8 Fist remained healthy in the same mixed run: three accepted player FIST executions produced native Orc damage and clean finalization.
- Player 1H+torch marker behavior was sampled across Quick, Normal and Power. Sixteen accepted RIGHT-marker attack C1s used factual RIGHT `It_1H_Sword_Rust_01`; the sword opened/cleaned through the expected equipped path while `It_Torch_Burning` remained tracked as LEFT with no authored collision-group mutation in those RIGHT-only samples.
- Every listed 1H+torch C1 finalized with sword and torch obligations at zero. Native Orc damage occurred on fourteen of the sixteen accepted marked attacks; two Quick opportunities did not contact, without lifecycle failure.
- No contradiction, invariant, lifecycle, repair-divergence or unresolved equipped-source flag appeared.

Scope / limits:
- Current-build coexistence/regression corroboration for:
  - repeated same-source RIGHT rearm during Whirl;
  - Orc raw8 Normal/Power FIST;
  - player raw8 FIST;
  - player 1H+torch RIGHT marker ownership.
- The torch observation is specific to RIGHT-authored samples in this log: it proves the tracked LEFT torch was not spuriously mutated by those RIGHT markers; it does not claim a new authored LEFT-torch feature.
- No new collision mechanism is inferred from this corroboration run.

Provenance:
- User upload batch head: `e4642a2d662a82e1594d00a260dd438f2a6176dd`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_orc_current_build_whirl_marker_on_on_fist_recheck.log`.
- Git blob `ddb59896124e491ed917890f37bb10bd20828285`; 325,662 characters / 1,158 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS / CORROBORATION.**
- Current accepted build preserves repeated-RIGHT rearm, Orc/player raw8 behavior and 1H+torch source separation in the sampled routes.

### EV-332 — mixed dual-1H player vs Ogre/raw52 regression PASS

Observed:
- The Ogre used factual RIGHT `It_Axe_OgreMorningStar_01` / raw52. Nineteen authored RIGHT markers were accepted across Power (12), Normal (4) and Quick (3).
- Ogre source mutation remained balanced: 19 exact RIGHT 5->7 openings and 19 exact RIGHT 7->5 cleanups. Eighteen native damage events reached `PC_Hero`.
- The player used two live `It_1H_Sword_Rust_01` instances, distinguished factually by RIGHT and LEFT equipped slots despite sharing the same item template.
- Authored dual-wield coverage included Quick RIGHT/LEFT, Power BOTH/LEFT/RIGHT/OFF combinations, SimpleWhirl LEFT/RIGHT, Pierce LEFT/RIGHT, and Normal BOTH.
- Forty-one ordinary authored marker events were accepted and six OFF events were accepted. Duplicate/replayed callbacks beyond the authored occurrence budget were fail-safe ignored as `AUTHORED_OCCURRENCE_BUDGET_IGNORED` or `DUPLICATE_SAME_UPDATE_IGNORED`; they did not create extra authored contacts.
- Detailed Power samples prove desired-set semantics:
  - BOTH opens both sword instances;
  - BOTH -> LEFT retires RIGHT and rearms LEFT;
  - BOTH -> RIGHT retires LEFT and rearms RIGHT;
  - OFF closes the remaining active authored source;
  - later BOTH reactivates both sources.
- Across the whole player run, RIGHT physical openings/cleanups balance 47/47 and LEFT openings/cleanups balance 37/37; repeated active-source rearms appear as expected 7->7 operations.
- Thirteen native damage events reached the Ogre from the player-side mixed route.
- All tracked C1 finalizations in the fixture closed without outstanding collision obligation. No contradiction, invariant, lifecycle, repair-divergence or unresolved-source flag appeared.

Scope / limits:
- Mixed current-build regression for dual-1H slot identity, desired-set semantics, occurrence/dedupe protection and Ogre raw52 coexistence.
- Some ordinary native/unmarked dual-wield attacks also appear in the log; they remain native and cleanly finalized.
- Individual authored opportunities that do not contact are not failures because target/contact geometry remains Gothic-owned.

Provenance:
- User upload batch head: `b422ddd78804d852882bfdd1301f0698a9297cde`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_1h_1h_ogre_2h_marker_test.log`.
- Git blob `8c6d43c2e79aad3bbae772407734f6d92562c3b8`; 235,935 characters / 1,175 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Dual-source equipped semantics and Ogre raw52 behavior remain healthy on the accepted current build.

### EV-333 — player 1H vs Orc Raider/raw52 mixed regression PASS

Observed:
- `Montera_Orc_Raider_01` used factual RIGHT `It_Axe_Orc_01` / raw52.
- Twenty Orc authored RIGHT markers were accepted across Normal (3), Hack (2), Power (3), Whirl (9) and Quick (3).
- The Orc source produced 16 exact 5->7 openings, 16 exact 7->5 cleanups and four expected 7->7 repeated-marker rearms. Fourteen native damage events reached `PC_Hero`.
- The player used factual RIGHT `It_1H_Sword_Rust_01` / raw2.
- Twenty-nine player authored RIGHT markers were accepted across Normal (18), Quick (8), Power (2) and Pierce (1).
- Player sword operations balanced 33 exact 5->7 openings with 33 exact 7->5 cleanups; eleven 7->7 operations reflect repeated/native rearm opportunities rather than stuck collision.
- Twenty-four native damage events reached the Orc Raider.
- All tracked player/Orc C1 obligations finalized cleanly; one source-less Orc reaction C1 is benign. No contradiction, invariant, lifecycle, repair-divergence or unresolved-source flag appeared.

Scope / limits:
- Current-build mixed regression for player 1H/raw2 against Orc Raider Axe/raw52, including the Orc Normal/Hack/Power/Whirl/Quick family set.
- Confirms coexistence and lifecycle balance; it does not claim every accepted opportunity must make contact.

Provenance:
- User upload batch head: `b422ddd78804d852882bfdd1301f0698a9297cde`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_1h_orc_2h_marker_test.log`.
- Git blob `385a979100595cb292653faf7528651369fad1f9`; 140,954 characters / 725 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Orc Raider raw52 and player 1H marker behavior coexist cleanly on the current build.

### EV-334 — player 1H+shield vs Demon/raw3 source-separation regression PASS

Observed:
- Demon used factual RIGHT `It_2H_DemonSword_01` / raw3.
- Thirty-two Demon authored RIGHT markers were accepted across Quick (8), Normal (14) and Power (10).
- Demon source operations balance exactly: 32 5->7 openings and 32 7->5 cleanups. Twenty-six native damage events reached `PC_Hero`.
- The player used factual RIGHT `It_1H_Sword_Rust_01` / raw2 while factual LEFT `It_Shield_StewarkGreat` remained equipped/tracked at group5.
- Sixty-four player RIGHT markers were accepted across Normal (25), Quick (31), Power (4) and Pierce (4).
- Player sword operations balance 74 exact 5->7 openings with 74 exact 7->5 cleanups; ten expected 7->7 rearm operations also occur.
- There are **zero** collision-group mutations for `It_Shield_StewarkGreat` in the entire log. RIGHT-only authoring therefore does not spuriously activate or clean the tracked LEFT shield.
- Thirty-eight native damage events reached the Demon from the player side.
- Every tracked equipped obligation finalized cleanly; no contradiction, invariant, lifecycle, repair-divergence or unresolved-source flag appeared.

Scope / limits:
- Current-build source-separation regression for player 1H+shield against Demon 2H/raw3.
- This confirms RIGHT marker isolation while a real LEFT shield/raw9 is equipped. It does not claim shield-bash damage support or authored LEFT-shield behavior beyond prior evidence.

Provenance:
- User upload batch head: `b422ddd78804d852882bfdd1301f0698a9297cde`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_1h_shield_demon_2h_marker_test.log`.
- Git blob `d260baf4e12662c258591c4768af8cdba17275e3`; 326,977 characters / 1,628 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Demon raw3 and player 1H+shield source separation remain healthy.

### EV-335 — player 2H vs Stalker/raw52 mixed regression PASS

Observed:
- Stalker used factual RIGHT `It_Axe_SpikedClub_01` / raw52.
- Thirteen Stalker authored RIGHT markers were accepted across Power (6) and Normal (7).
- Stalker source operations balance exactly: 13 5->7 openings and 13 7->5 cleanups. Ten native damage events reached `PC_Hero`.
- The player used factual RIGHT `It_2H_Sword_Flamberge` / raw3.
- Twenty-eight ordinary authored player markers were accepted across Normal (4), Quick (19), Power (2), Whirl RIGHT (2) and Hack (1), plus one accepted Whirl OFF.
- The Whirl sample explicitly executes `RIGHT -> OFF -> RIGHT`; the extra replayed OFF/RIGHT callbacks are correctly filtered by occurrence/deduplication protection.
- Player 2H source operations balance 34 exact 5->7 openings with 34 exact 7->5 cleanups; six expected 7->7 rearm operations occur.
- Seventeen native damage events reached the Stalker.
- All tracked C1 obligations finalized cleanly; no contradiction, invariant, lifecycle, repair-divergence or unresolved-source flag appeared.

Scope / limits:
- Current-build mixed regression for player 2H/raw3 Normal/Quick/Power/Whirl/Hack against Stalker Axe/raw52.
- Corroborates Whirl OFF-gap semantics and the established 2H Hack path without creating new architecture.

Provenance:
- User upload batch head: `b422ddd78804d852882bfdd1301f0698a9297cde`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_2h_stalker_2h_marker_test.log`.
- Git blob `0d726c1a05bcd7bd6c1d177f8fc1383324b83a8f`; 136,363 characters / 723 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Player 2H and Stalker raw52 routes remain healthy on the accepted current build.

### EV-336 — player raw8 Fist vs Goblin/raw2 + permanent Sprint mixed regression PASS

Observed:
- Goblin used factual RIGHT `It_1H_Club_01` / raw2.
- Forty-two Goblin authored RIGHT markers were accepted across Quick (14), Normal (16) and factual Sprint (12).
- Goblin club operations balance exactly: 42 5->7 openings and 42 7->5 cleanups.
- Thirty-six native damage events reached `PC_Hero` across the mixed Goblin attack run.
- All twelve factual Goblin Sprint executions independently show the permanent `EquippedSprintCollision` path:
  - eligible Action9/Sprint callback suppression;
  - `BOUND_EXECUTION_MATCHED` marker authorization;
  - RIGHT accepted;
  - exact club 5->7;
  - native damage to the player;
  - exact club 7->5 cleanup;
  - C1 finalization with `Outstanding=0`.
- The player used factual raw8 `Fist`.
- Fifty-six player FIST markers were accepted across 56 distinct C1s. All 56 armed the established raw8 early timing permission and all 56 consumed it; zero FIST markers were rejected.
- Five native Fist damage events reached the Goblin. The lower contact count reflects native geometry/contact opportunity rather than marker/timing failure.
- Player raw8 C1s finalized without outstanding collision obligation. No contradiction, invariant, lifecycle, repair-divergence or unresolved-source flag appeared.

Scope / limits:
- Mixed current-build regression for player raw8 Fist against Goblin 1H/raw2.
- Provides strong post-promotion corroboration of permanent equipped Sprint in ordinary noisy combat, not a replacement for the controlled EV-326–EV-329 acceptance chain.
- Raw8 marker acceptance opens native contact opportunity; it does not guarantee physical contact on every authored attempt.

Provenance:
- User upload batch head: `b422ddd78804d852882bfdd1301f0698a9297cde`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_fist_goblin_1h_marker_test.log`.
- Git blob `3a27c94a9bc883d063debdcd907e7198664c3c5d`; 347,358 characters / 1,592 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Player raw8, Goblin raw2 and permanent equipped Sprint coexist cleanly on the accepted current build.

### EV-337 — Sabretooth raw8 double-FIST native + transformed regression PASS

Observed:
- Native `Sabertooth` used factual `Fist` / UseType 8 under the production raw8 mechanism.
- Nineteen Sabertooth C1s contained accepted FIST authoring in the double-marker fixture: sixteen reached both FIST markers; three were interrupted/replaced after the first marker before the second authored occurrence.
- Across those C1s, 35 FIST markers were accepted. The first accepted FIST in each marked C1 armed/consumed the established bounded early timing permission; all sixteen C1s that reached the second FIST logged the later marker as `NATIVE_TIMING`.
- The native Sabertooth side produced 15 native Fist damage events to `PC_Hero`. Covered families include Quick, Normal, Sprint and Power. Lack of contact on individual accepted opportunities is geometry/native-contact outcome, not marker failure.
- `Transform_Sabertooth_Potion` independently exercised ten complete double-FIST C1s: all ten accepted two FIST markers, all ten armed/consumed the first-marker early permission, all ten accepted the second marker at native timing, and 14 native Fist damage events reached the native Sabertooth.
- All recorded transformed C1 finals were clean. The three interrupted native Sabertooth C1s have no bad/nonzero final; whole-log finalization contains zero unresolved collision obligation and zero invariant/lifecycle/repair anomaly.

Scope / limits:
- Current-build actor-general regression for raw8 repeated-FIST semantics using native Sabertooth and player-transformed Sabertooth.
- Confirms the mechanism follows factual raw8 source/family/runtime state rather than a human-only actor rule.
- Interrupted executions are not counted as failed double-marker executions when the second authored marker was never reached.

Provenance:
- User upload batch head: `914b2b93bc8229b293503c0396148bd8a3768a14`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_sabertooth_npc_sabertooth_double_marker_test.log`.
- Git blob `510c8f6b264afc6f44841deba616e596a79ae495`; 552,275 characters / 1,520 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Native and transformed Sabertooth preserve repeated-FIST raw8 behavior on the accepted current build.

### EV-338 — Sabretooth raw8 single-FIST native + transformed regression PASS

Observed:
- Native `Sabertooth` exercised 30 distinct single-FIST C1s using factual `Fist` / UseType 8.
- All 30 FIST markers were accepted; all 30 armed and consumed the established early timing permission; no second-marker native-timing path was present, as expected for a single-marker fixture.
- Native Sabertooth covered Quick, Normal, Power and Sprint and produced 10 native Fist damage events to `PC_Hero`.
- `Transform_Sabertooth_Potion` exercised 11 distinct single-FIST C1s across Normal, Quick and Power. All 11 markers were accepted, all 11 armed/consumed the raw8 timing permission, and 10 native Fist damage events reached the native Sabertooth.
- Every marked C1 in this fixture finalized cleanly with zero outstanding collision obligation. No contradiction, invariant, lifecycle, repair-divergence or unresolved-source flag appeared.

Scope / limits:
- Current-build single-marker actor-general raw8 regression for native and player-transformed Sabertooth.
- Contact count is not expected to equal marker count because Gothic owns geometry/contact/damage dispatch.

Provenance:
- User upload batch head: `914b2b93bc8229b293503c0396148bd8a3768a14`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_sabertooth_npc_sabertooth_marker_test.log`.
- Git blob `8e90e2a6c4e97d64a4e50399adee3d607e2b4968`; 555,176 characters / 1,551 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Single-FIST raw8 semantics remain healthy for native and transformed Sabertooth.

### EV-339 — Wolf marked raw8 native + transformed regression PASS

Observed:
- Native `Wolf` resolves a factual RIGHT `Fist` source with UseType 8 and uses the production raw8 mechanism when authored FIST markers are present.
- Twenty-seven distinct Wolf marked C1s were observed across Normal, Power and Sprint. All 27 FIST markers were accepted; all 27 armed and consumed the established raw8 early timing permission.
- Eight native Fist damage events reached `PC_Hero`.
- Twenty-six of the 27 marked Wolf C1s have an ordinary clean final; the remaining marked C1 was interrupted/replaced before its final record. Whole-log finalization contains zero nonzero/outstanding failure.
- `Transform_Wolf_Potion` exercised 15 distinct marked raw8 C1s across Normal and Power. All 15 FIST markers were accepted, all 15 timing permissions armed/consumed, all 15 C1s finalized cleanly, and 8 native Fist damage events reached the native Wolf.
- No contradiction, invariant, lifecycle, repair-divergence or unresolved-source flag appeared.

Scope / limits:
- First current Phase-4 Wolf proof of the established raw8 mechanism across both native Wolf and player-transformed Wolf.
- Confirms factual source identity, not animal name, governs applicability.

Provenance:
- User upload batch head: `914b2b93bc8229b293503c0396148bd8a3768a14`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_wolf_npc_wolf_marker_test.log`.
- Git blob `e3fa6498735439bf85efc0dedc84803d22fa8276`; 554,454 characters / 1,607 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Marked Wolf raw8 behavior is healthy and actor-general across native/transformed use.

### EV-340 — Wolf unmarked raw8 native-fallback control PASS

Observed:
- The unmarked Wolf fixture still exposes factual RIGHT `Fist` / UseType 8 in C1/source and callback facts.
- The entire log contains zero authored collision markers, zero `RAW8_FIST_OWNERSHIP` records and zero `RAW8_FIST_TIMING` records.
- Attack ownership remains `MarkerPresent=0 / FistMarkers=0 / SuppressNative=0`; the marker system therefore does not claim raw8 behavior merely because the factual source is UseType 8.
- Native Wolf combat remains functional: 8 native Fist damage events reached `PC_Hero`.
- Player-transformed Wolf also remains native without markers: 15 native Fist damage events reached the native Wolf with zero marker/timing intervention.
- The log contains 47 native-Wolf and 17 transformed-Wolf C1 starts tracking factual Fist source state, with no unresolved collision obligation, contradiction, invariant, lifecycle or repair-divergence failure.

Scope / limits:
- Strong negative/native-fallback control paired directly with EV-339 on the same Wolf family.
- Confirms raw8 authored behavior is explicit marker opt-in; factual raw8 alone does not enable the marker timing mechanism.

Provenance:
- User upload batch head: `914b2b93bc8229b293503c0396148bd8a3768a14`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_wolf_npc_wolf_without_marker_test.log`.
- Git blob `523d16d494a456ddb352a81fcea1d3fb95440d3d`; 487,122 characters / 1,411 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **NEGATIVE/NATIVE-FALLBACK PASS.**
- Unmarked Wolf raw8 remains completely native while marked Wolf in EV-339 opts into authored timing.

### EV-341 — Troll raw55 mixed single/double FIST + player Staff regression PASS

Observed:
- Native `Troll` uses the separate permanent raw55 `TrollFist` / UseType 55 mechanism.
- Twenty-five Troll C1s contained accepted permanent raw55 FIST behavior: sixteen single-marker C1s and nine complete double-marker C1s, for 34 accepted FIST markers total.
- Family coverage in the marked raw55 set includes Normal (8 C1 / 8 FIST), Quick (13 C1 / 22 FIST) and Sprint-origin (4 C1 / 4 FIST).
- Every first accepted FIST opened the exact RIGHT TrollFist path; 25 physical RIGHT 5->7 openings are matched by 25 exact 7->5 cleanups.
- In all nine complete double-FIST Quick C1s, the later FIST is a contact rearm only: group remains 7->7, `GroupRequested=0`, and `ClearTriggeredList=1`. No second physical opening is requested.
- Normal/Sprint routes show the evidence-backed premature native-opening suppression before authored activation. Seventeen native-open suppression records occur across the mixed run, including interrupted/marker-not-reached executions.
- The 25 marked raw55 C1s produced 25 native damage events to `PC_Hero`. Five marked/intervened C1s were interrupted/replaced before an ordinary final line; whole-log finals contain zero nonzero outstanding obligation.
- Player Staff used factual `Wrestling` equipped source and exercised Normal, Quick, Power, Hack and Whirl authoring. Staff physical operations balance 28 exact 5->7 openings with 28 exact 7->5 cleanups, plus four expected 7->7 repeated-marker rearms.
- Player Whirl included accepted RIGHT/OFF behavior with replayed callbacks filtered by occurrence/deduplication protection. Twenty-seven native damage events reached the Troll.
- No contradiction, invariant, lifecycle, repair-divergence or unresolved-source flag appeared.

Scope / limits:
- Current-build mixed regression for permanent raw55 single/double-FIST behavior plus player Staff equipped behavior.
- Raw55 remains a distinct mechanism from raw8; this evidence must not be generalized by animation token alone.

Provenance:
- User upload batch head: `914b2b93bc8229b293503c0396148bd8a3768a14`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_staff_npc_troll_marker_test.log`.
- Git blob `a36829a795633f33360797934a9c6b5d4d09906a`; 268,001 characters / 1,108 lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Permanent Troll raw55 and player Staff behavior remain healthy under mixed single/double-marker combat.

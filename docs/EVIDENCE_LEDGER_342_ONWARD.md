# Gothic 3 Animation Behaviors — Evidence Ledger EV-342 Onward

**Status:** Active evidence/provenance ledger  
**Opened:** 2026-09-20

## Purpose

Record new evidence after EV-341 using a compact provenance-first format.

This ledger is **proof history, not the normal knowledge interface**. Current established collision facts belong in `COLLISION_REFERENCE.md` and owning architecture/reference documents.

The previous EV-309–EV-341 ledger and all earlier closed volumes are routed through `EVIDENCE_INDEX.md`.

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


### EV-342 — Minecrawler marked raw8 regression PASS

Observed:
- Native Minecrawler uses factual RIGHT `Fist` / UseType 8 and enters the ordinary production raw8 mechanism when authored FIST markers are present.
- Twelve marked raw8 C1s were observed: Normal 5, Power 1, Quick 6 (Action4 2 / Action5 4). All twelve FIST markers were accepted and all twelve ownership checks confirmed the exact raw8 source.
- Normal/Power timing used the bounded early permission in six C1s; all six Quick C1s resolved through native timing after the authored rearm.
- Eight native `Fist -> PC_Hero` damage events occurred. Four accepted marked executions (one Power and three Normal) produced no native damage event in this capture, while marker ownership/timing still completed and each C1 finalized cleanly at outstanding zero. Because target/contact/damage remain Gothic-owned, these are recorded as non-contact executions rather than collision failures.
- The mixed player 1H-family equipped control remained balanced: 14 exact 5->7 openings and 14 exact 7->5 cleanups, plus one expected 7->7 rearm; 11 native damage events reached Minecrawler.
- No anomaly, warning, contradiction, rejected marker, repair or divergence record appeared; the diagnostic DLL unloaded cleanly.

Scope / limits:
- Confirms Minecrawler factual raw8 marker compatibility across Normal, Power marker/timing transport and both Quick directions.
- Does not claim that the single tested Power execution made physical contact; no Power ONDAMAGE is present in this log.

Provenance:
- User upload batch head: `6b2a34bf0d2d63f2a6350570bad8e83a64942d42`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_1h_1h_npc_minecrawler_marker_test.log`.
- Git blob `80da4464fa24f36a60cca7fa1f27772c8f55680b`; 393 non-empty lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Minecrawler broadens Phase-4 factual Fist/raw8 creature coverage without introducing species-specific behavior.

### EV-343 — Bloodfly marked raw8 Normal/Power/Sprint regression PASS

Observed:
- Native Bloodfly uses factual RIGHT `Fist` / UseType 8.
- Ten marked raw8 C1s were observed: Normal 8, Power 1 and Sprint 1. All ten FIST markers were accepted and all ten ownership checks confirmed the exact raw8 source.
- All ten authored opportunities resolved at native timing after the marker-owned rearm; ten native `Fist -> PC_Hero` damage events followed.
- The factual Sprint C1 remained correctly separated from equipped Sprint ownership: `EquippedSprintCollision` delegated native with `Reason=FIST_MARKER_PRESENT`.
- The mixed player 1H/raw2 control remained balanced with six 5->7 openings and six 7->5 cleanups; five native damage events reached Bloodfly.
- Every marked Bloodfly C1 finalized at outstanding zero. No anomaly, warning, contradiction, rejected marker, repair or divergence record appeared; the diagnostic DLL unloaded cleanly.

Scope / limits:
- Confirms Bloodfly factual raw8 marker compatibility for Normal, Power and Sprint in this fixture.
- This is native Bloodfly coverage only; no transformed-player Bloodfly fixture was exercised.

Provenance:
- User upload batch head: `6b2a34bf0d2d63f2a6350570bad8e83a64942d42`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_1h_npc_bloodfly_marker_test.log`.
- Git blob `64171546e8cb3765d2801b16fe702350ec16bcd7`; 320 non-empty lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Bloodfly extends current raw8 Phase-4 coverage and provides another factual Sprint/FIST separation control.

### EV-344 — Boar marked raw8 Normal regression PASS

Observed:
- Native Boar uses factual RIGHT `Fist` / UseType 8.
- Nine marked Normal C1s were observed. All nine FIST markers were accepted and all nine ownership checks confirmed the exact raw8 source.
- Eight executions consumed the bounded early timing permission and one resolved at native timing.
- All nine marked Boar C1s produced native `Fist -> PC_Hero` damage and finalized at outstanding zero.
- The mixed player 1H+shield fixture preserved ordinary equipped 1H/raw2 behavior: six 5->7 openings matched six 7->5 cleanups and six native damage events reached Boar. This is coexistence evidence, not a shield-bash test.
- No anomaly, warning, contradiction, rejected marker, repair or divergence record appeared; the diagnostic DLL unloaded cleanly.

Scope / limits:
- Confirms Boar factual raw8 Normal marker compatibility in the tested native fixture.
- Does not generalize to untested Boar attack families or transformed-player behavior.

Provenance:
- User upload batch head: `6b2a34bf0d2d63f2a6350570bad8e83a64942d42`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_1h_shield_npc_boar_marker_test.log`.
- Git blob `b6a4511494ef4443ed6aadcbdfcf0f55db050ade`; 253 non-empty lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Boar extends current factual Fist/raw8 creature coverage with clean marker timing, native damage and finalization.

### EV-345 — Bison marked raw8 Normal regression PASS

Observed:
- Native Bison uses factual RIGHT `Fist` / UseType 8.
- Twelve marked Normal C1s were observed. All twelve FIST markers were accepted, all twelve ownership checks confirmed the exact raw8 source, and all twelve consumed the bounded early timing permission.
- All twelve marked Bison C1s produced native `Fist -> PC_Hero` damage and finalized at outstanding zero.
- The mixed player 2H Flamberge / UseType 3 control remained balanced with eight 5->7 openings, eight 7->5 cleanups and eight native damage events to Bison.
- No anomaly, warning, contradiction, rejected marker, repair or divergence record appeared; the diagnostic DLL unloaded cleanly.

Scope / limits:
- Confirms Bison factual raw8 Normal marker compatibility in the tested native fixture.
- Does not generalize to untested Bison attack families or transformed-player behavior.

Provenance:
- User upload batch head: `6b2a34bf0d2d63f2a6350570bad8e83a64942d42`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Canonical archived log: `research/archive/2026-09-20_validation_me_2h_npc_bison_marker_test.log`.
- Git blob `93d7d8b67c5bc86cb61f60563983ccbf367f03c8`; 313 non-empty lines.
- Diagnostic profile: CORE; DEEP disabled.

Disposition:
- **PASS.**
- Bison extends current factual Fist/raw8 creature coverage with clean marker timing, native damage and finalization.


### EV-346 — Gargoyle raw8 Power marker-time sweep exposes one-shot authoring semantics

Observed:
- All tested Gargoyle attacks in the four-run sweep are factual `Action=2 / Family=POWER` with exact RIGHT `Fist` / UseType 8. No factual Gargoyle Sprint/Action9 execution was observed.
- Native/no-marker control: 7 observed Gargoyle Power attacks produced 7 native `Fist -> PC_Hero` damage events. The native damage point occurred about 200–210 ms after the Power callback's ordinary Fist timing/group-request point.
- Approximate frame-3 FIST test: 10/10 FIST markers were accepted with exact raw8 ownership; all 10 used the bounded early timing permission, but only 5/10 produced native damage while the player stood still.
- Frame-1 FIST test: 4/4 markers were accepted with exact raw8 ownership and all 4 used synthetic early timing; 0/4 produced native damage.
- Frame-6 FIST test: 8/8 markers were accepted with exact raw8 ownership and 8/8 produced native damage. Marker timing was ~208–222 ms after the same callback point, and each consumed the permission with `SyntheticApplied=0 / Classification=NATIVE_TIMING`, i.e. the real animation clock had reached Gothic's native gate by the next exact comparison.
- No anomaly, warning, contradiction, rejected marker, repair, divergence or nonzero-finalization record appeared in the four logs; every run unloaded cleanly.

Interpretation:
- The current production raw8 contract is functioning as designed: marked executions close native permission before the first FIST, and each accepted FIST rearms one native opportunity; when the marker is before Gothic's native threshold, one exact timing comparison is advanced synthetically.
- Gargoyle demonstrates that an early accepted FIST is an authored **one-shot native contact opportunity**, not a persistent body-contact window. If that early opportunity occurs before the moving body reaches the target, Gothic can consume the opportunity without damage and no later native contact occurs in that C1 unless another authored FIST rearms it.
- This does not contradict the existing raw8 implementation contract, but it exposes a material author-facing semantics question: whether FIST should remain a one-shot contact pulse or instead mean a window that remains eligible from the marker until contact/end-of-Hit, analogous to the broader marker-authoring model.

Scope / limits:
- The sweep establishes the current behavior for Gargoyle factual raw8 Power and demonstrates marker-time sensitivity under a stationary-player fixture.
- It does not establish that Gargoyle can never use Sprint in other circumstances; only that no Action9 occurred in these tests.
- No redesign mechanism is proven by this evidence. Persistent-window semantics, successful-contact detection, rearm rules and any FIST_OFF requirement remain open design/research questions.

Provenance:
- Gargoyle batch head including frame-6 run: `b7c83a7a55c31235e90a2f4187d05fae477d3673`.
- Diagnostic DLL SHA256: `DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A`.
- Archived logs:
  - `research/archive/2026-09-20_validation_me_staff_npc_Gargoyle_marker_test.log` — blob `f67705c17ca5059867180823e61fc123aa3b730c`.
  - `research/archive/2026-09-20_validation_me_staff_npc_gargoyle_marker_frame_1_test.log` — blob `e19f7d0a4ce0f12d255756e0817b8e5a3bfb3120`.
  - `research/archive/2026-09-20_validation_me_staff_npc_gargoyle_marker_frame_6_test.log` — blob `e3e7bf3d7e233e9e4fe944a19b013e1aa98ed58e`.
  - `research/archive/2026-09-20_validation_me_staff_npc_gargoyle_native_test.log` — blob `7dcddf757c4da80a95537ce9a09e245d86015623`.

Disposition:
- **CONFIRMED DESIGN DISCOVERY / RAW8 AUTHORING-SEMANTICS GATE OPEN.**
- Pause broad Phase-4 certification until the project explicitly retains the one-shot FIST contract or freezes a bounded research path toward persistent-window semantics.


### EV-347 — Gargoyle raw8 post-attempt latch observation proves attempt-level latch consumption

Observed:
- Controlled runtime used the reviewed diagnostics-only implementation `4ab9a77557f9ad5057d158b7d26a3098db657b28` and diagnostic DLL SHA256 `3EDC9FC0B6BE0BC8B4ED3249D4CC6F99F613694FC32ECC867DF9B6396FFC5CD3`.
- The frame-3 Gargoyle factual `Action=2 / POWER`, exact RIGHT `Fist` / UseType8 fixture produced four exact marked raw8 C1 observations with `SyntheticApplied=1`.
- C1 6: no same-invocation native raw8 damage; post-original `SPU+0x164 = 1`.
- C1 9: exact native raw8 damage occurred at `Game.dll+0x0016E348` with `Arg1=Fist`, `Arg2=Gargoyle`, `Target=PC_Hero`; post-original `SPU+0x164 = 1`.
- C1 18: no same-invocation native raw8 damage; post-original `SPU+0x164 = 1`.
- C1 50: exact native raw8 damage occurred at `Game.dll+0x0016E348` with `Arg1=Fist`, `Arg2=Gargoyle`, `Target=PC_Hero`; post-original `SPU+0x164 = 1`.
- All four observations preserved exact SPU/actor/C1/source/motion identity (`SPUActorMatch=1 C1Match=1 SourceMatch=1 MotionMatch=1`).
- User runtime observation matched the log: close-range frame-3 attacks hit; farther frame-3 attacks missed even though the Gargoyle later reached the player during the remaining attack motion.
- Every marked Gargoyle C1 finalized at outstanding zero. No anomaly, warning, contradiction, rejected marker, repair or divergence record appeared; the diagnostic DLL unloaded cleanly.

Interpretation:
- On the tested raw8 Power route, Gothic closes `SPU+0x164` after the native contact **attempt**, not only after successful damage.
- Therefore the current early synthetic FIST opportunity is consumed even when no native damage/contact result occurs.
- The existing same-invocation `gCEntity::OnDamage` hook plus exact caller/source/actor identity provides a bounded factual success signal for this tested route.
- This explains the EV-346 Gargoyle timing behavior and confirms the exact mismatch with the agreed persistent authored-opportunity semantic.

Scope / limits:
- Proves attempt-level latch consumption for the tested Gargoyle raw8 Power synthetic path.
- Does not yet prove the final production success detector across every raw8 actor/family.
- Does not prove that post-miss latch rearm alone is sufficient for the desired persistent opportunity; timing rearm remains deliberately untested.

Provenance:
- Work implementation: `4ab9a77557f9ad5057d158b7d26a3098db657b28`.
- Normal Chat source review: PASS.
- Local two-twin build: PASS.
- Diagnostic deployment/startup: PASS; built/live SHA256 matched `3EDC9FC0B6BE0BC8B4ED3249D4CC6F99F613694FC32ECC867DF9B6396FFC5CD3`.
- Canonical archived log: `research/archive/2026-09-20_observation_gargoyle_marker_frame_3_test.log`.
- Git blob: `7b2262ee2acf2d8e5da3fea4a3c5984eb849a9b8`.

Disposition:
- **CAUSAL OBSERVATION PASS.**
- Close the post-attempt observation probe. Next bounded question: whether one exact post-miss latch rearm, without timing rearm, preserves a later native opportunity while successful early contact remains consumed.


### EV-348 — Gargoyle raw8 post-miss latch rearm restores later native opportunity

Observed:
- Runtime used reviewed diagnostic-only probe implementation `ea652e3324fffb07da013229a2fd374c4f3b1c6b` and diagnostic DLL SHA256 `63261A1A4778FF293BDA94495B57EE363546650A7D386507304CA3D5FD9AB3FC`.
- Thirteen exact Gargoyle factual `Action=2 / POWER`, RIGHT `Fist` / UseType8 frame-3 synthetic attempts were observed.
- Four close-range synthetic attempts produced exact same-invocation native raw8 damage at `Game.dll+0x0016E348`; all four correctly performed no probe rearm.
- Nine synthetic attempts produced no exact same-invocation raw8 damage and met every post-miss identity condition; all nine performed one confirmed `SPU+0x164: 1 -> 0` rearm.
- Seven of those nine rearmed misses later produced exact native `Fist -> PC_Hero` damage before the same C1 finalized, at approximately 100.6–109.8 ms after the rearm.
- C1 22 and C1 43 rearmed successfully but produced no later native damage before C1 finalization.
- User visual observation: all attacks appeared to connect except one case where distance was so large that the Gargoyle never reached the player by the end of the motion. The log nevertheless contains two rearmed/no-damage C1s, so the second visual/log discrepancy remains unassigned rather than guessed.
- All probe identities matched; no anomaly, warning, contradiction, rejected marker, repair or divergence record appeared; every marked Gargoyle C1 finalized cleanly.

Interpretation:
- A single post-miss latch-only rearm is sufficient to restore a later native raw8 damage opportunity on the tested Gargoyle Power route.
- Successful early native damage remains consumed: the exact-hit branch performs no rearm and no second same-C1 raw8 damage was observed.
- Because the probe did not rearm synthetic timing, the restored opportunity occurs later under Gothic's ordinary timing path rather than by another synthetic early comparison.
- This proves a smaller mechanism than a full timing redesign can recover later native opportunity after an early authored miss.
- It does **not** yet prove continuous eligibility from the FIST marker until contact; transient contact before Gothic's later native timing remains an open semantic/mechanism question.

Scope / limits:
- Tested factual raw8 Power only.
- Does not generalize the exact success detector or post-miss policy to Normal/Quick/Sprint yet.
- Does not resolve the two rearmed/no-damage C1s beyond preserving their factual result.
- Does not establish final production architecture.

Provenance:
- User-upload head: `40081c3e6994c895202713b5ccdd5997896ebef5`.
- Diagnostic DLL SHA256: `63261A1A4778FF293BDA94495B57EE363546650A7D386507304CA3D5FD9AB3FC`.
- Canonical archived log: `research/archive/2026-09-20_observation_gargoyle_marker_frame_3_test_2.log`.
- Git blob: `b447d1a3995118e84b0884801c0347b49efd15d8`.

Disposition:
- **CAUSAL INTERVENTION PASS.**
- The post-miss latch-rearm probe is closed. The next design/research question is whether the agreed FIST semantic requires eligibility throughout the interval from marker time to Gothic's later native threshold, or whether latch-only recovery at native timing is sufficient.


### EV-349 — Gargoyle rearm control exposes native knockdown rejection and cross-C1 opportunity leak

Observed:
- Runtime reused reviewed diagnostic-only latch-rearm probe implementation `ea652e3324fffb07da013229a2fd374c4f3b1c6b` and diagnostic DLL SHA256 `63261A1A4778FF293BDA94495B57EE363546650A7D386507304CA3D5FD9AB3FC`.
- Twelve exact Gargoyle factual `Action=2 / POWER`, RIGHT `Fist` / UseType8 frame-3 synthetic attempts were observed.
- Four attempts produced exact same-invocation native raw8 `Game.dll+0x0016E348` entries and correctly performed no latch rearm.
- Eight attempts missed the exact synthetic invocation and all eight performed one confirmed `SPU+0x164: 1 -> 0` post-miss rearm.
- Six of those eight rearms produced later exact native `Fist -> PC_Hero` `OnDamage` entries before the original Hit C1 was replaced/finalized, approximately 99.4–112.4 ms after rearm.
- C1 5 rearmed successfully but produced no later `OnDamage` entry before finalization.
- C1 55 rearmed at 109656.881 ms; the next Gargoyle C1 generation 57 replaced generation 55 at 109773.729 ms; an exact native `Fist -> PC_Hero` `OnDamage` entry then occurred at 109773.833 ms, after the generation replacement, while the player was `Action=31`, phase 1, motion `Hero_SitKnockDown_None_1H_P0_GetUpParade_Hit_N_Fwd_00_%_00_P0_0.xmot`.
- User observed two attacks with no visible damage because the player was already knocked down / in the protected part of getting up. The log directly confirms one native `OnDamage` entry during `GetUpParade`; the C1 5 no-`OnDamage` case is temporally consistent with the other user-observed knocked-down rejection but does not itself log the player's exact action at that moment.
- No anomaly, warning, contradiction, rejected marker, repair or divergence record appeared.

Interpretation:
- Visible health damage is not a valid collision/contact-consumption oracle. The Parade case proves the native raw8 `OnDamage` boundary can be entered while the defensive stance prevents visible damage.
- The collision feature should therefore remain policy-neutral: it authors when native collision/contact opportunity is open, rearmed or closed; Gothic and other behavior systems own block/parry, immunity, knockdown/get-up vulnerability, reactions and HP damage.
- A future authored opportunity should be consumed by the factual native hit/contact-resolution event for its target, regardless of whether gameplay damage is full, reduced, blocked or zero. If no such native resolution occurs, the opportunity may remain pending only until the exact Hit/C1 lifetime ends.
- The C1 5 case does not require the collision system to diagnose why no `OnDamage` boundary was reached; that reason may remain entirely within Gothic/behavior policy.
- The temporary latch-only rearm also demonstrates a lifecycle hazard: an unused rearmed opportunity can remain live across the original Hit C1 replacement into Recover unless the future design explicitly closes it at the agreed C1/Hit lifetime boundary.

Scope / limits:
- Tested Gargoyle factual raw8 Power only under the diagnostic-only rearm probe.
- The log does not yet prove the smallest production-safe native hit/contact-resolution boundary. `Game+0x16E348` is a strong tested-route candidate but must not be equated with HP damage.
- It does not establish the final production opportunity-consumption detector.
- User reports that New Balance changes some knockdown/get-up behavior; that statement is retained as a future compatibility-test reason, not as a verified New Balance mechanism in this standalone run.

Provenance:
- User-upload head immediately before closure: current branch commit adding `research/raw/2026-09-20_observation_gargoyle_marker_frame_3_test_3.log`.
- Diagnostic DLL SHA256: `63261A1A4778FF293BDA94495B57EE363546650A7D386507304CA3D5FD9AB3FC`.
- Canonical archived log: `research/archive/2026-09-20_observation_gargoyle_marker_frame_3_test_3.log`.
- Git blob: `9e46fa742d94d8e569226c51e509b224ac391ac1`.

Disposition:
- **CAUSAL CORROBORATION / NEW LIFECYCLE + TARGET-STATE DISCOVERY.**
- Do not advance directly to production. The remaining research must identify the smallest factual native hit/contact-resolution boundary, independent of gameplay damage policy, and must close any unused opportunity at the exact C1/Hit lifetime boundary.


### EV-350 — Raw8 closed-research retirement neutral-baseline control PASS

Observed:
- Reviewed cleanup implementation: `ac1373a88b17c1fc36f8c2b7e06ce394d2777cc3`.
- Both collision twins built successfully locally.
- Diagnostic deployment contained exactly one live collision twin: `Script_FrameCollisionTest.dll`.
- Built/live SHA256 matched `C33046D1AE139B5D905CF5E1004F725F07A5FE8CAC3A9705F11691497D7CD17D`.
- Diagnostic startup/unload was clean.
- The User additionally repeated the frame-3 Gargoyle factual `Action=2 / POWER`, RIGHT `Fist` / UseType8 control after retirement.
- Five marked C1s were observed: 7, 13, 17, 22 and 29.
- All five accepted FIST, confirmed latch `1 -> 0`, armed early timing permission and consumed it with `SyntheticApplied=1`.
- C1 22 and C1 29 entered the generic native `Game.dll+0x0016E348` `OnDamage` API boundary approximately 0.15 ms and 0.14 ms after the synthetic opportunity respectively.
- C1 7, C1 13 and C1 17 had no such native hit/contact-path entry before their C1 finalized.
- User runtime observation matched the old pre-probe behavior: close-starting Gargoyle attacks could make contact at the frame-3 opportunity; farther-starting attacks missed even when the motion later carried the Gargoyle into range.
- No `RAW8_FIST_WINDOW_PROBE` record appeared.
- No `RAW8_FIST_POST_ATTEMPT` record appeared.
- Generic `CORE ONDAMAGE` observation remained present.
- No anomaly, warning, contradiction, rejected marker, repair or divergence record appeared.

Interpretation:
- Retirement restored the diagnostic product to the intended neutral baseline without changing permanent raw8 marker/latch/timing behavior.
- The temporary EV-348 post-miss rearm effect is gone; frame-3 raw8 again exhibits the previously proven one-shot authored-opportunity behavior.
- Generic `OnDamage` logging remains observation only. The two entries in this control are treated as native hit/contact-path evidence, not as ownership of gameplay damage policy.

Scope / limits:
- This is a cleanup/runtime-equivalence control, not a new production mechanism proof.
- It does not establish `Game+0x16E348` as the final production opportunity-consumption boundary.
- It does not alter the agreed persistent-opportunity design target.

Provenance:
- Cleanup implementation: `ac1373a88b17c1fc36f8c2b7e06ce394d2777cc3`.
- Diagnostic DLL SHA256: `C33046D1AE139B5D905CF5E1004F725F07A5FE8CAC3A9705F11691497D7CD17D`.
- Canonical archived log: `research/archive/2026-09-20_observation_gargoyle_marker_frame_3_test_4.log`.
- Git blob: `06d1e22353f017f536d1c8c2d039e5fe34fd1e0b`.

Disposition:
- **CLEANUP / NEUTRAL-BASELINE PASS.**
- Closed raw8 damage-correlated research instrumentation is retired. Future raw8 research starts from this neutral baseline.


### EV-351 — Raw8 TouchDamage virtual contact-boundary observation rules out exact callbacks on tested combat-loop route

Observed:
- Reviewed diagnostic-only implementation: `929bba9974788c873860f8e33f504c091f7aa524`.
- Both collision twins built successfully locally.
- Diagnostic deployment contained exactly one live collision twin: `Script_FrameCollisionTest.dll`.
- Built/live SHA256 matched `F6EB69B1AFAFCB4C8F99FBE4C5CFDE1DC411FA074F109E7F5515D068E76096DD`.
- Startup, hook installation and unload were clean.
- Runtime fixture reused the factual Gargoyle `Action=2 / POWER`, exact RIGHT `Fist` / UseType8 frame-3 FIST control.
- Six exact marked C1s were observed: 4, 14, 21, 24, 33 and 36.
- All six accepted FIST and consumed the permanent early raw8 timing permission.
- C1 14, 24 and 33 entered the generic exact raw8 `Game.dll+0x0016E348` `CORE ONDAMAGE` boundary approximately 0.145 ms, 0.141 ms and 0.132 ms after the synthetic timing opportunity respectively.
- C1 4, 21 and 36 had no such native hit/contact-path entry before C1 finalization.
- User visual observation matched the log split: attacks starting near enough connected; attacks needing more travel after frame 3 did not.
- Across all six factual raw8 invocations:
  - `CORE RAW8_CONTACT_GATE` count = 0;
  - `CORE RAW8_CONTACT_TARGET` count = 0.
- Therefore the exact current raw8 Fist TouchDamage source did not produce an observed `gCTouchDamage_PS::CanBeActivatedNow` or `gCTouchDamage_PS::TriggerTarget` boundary even in the three close/contact cases.
- No anomaly, warning, contradiction, rejected marker, repair or divergence record appeared.

Interpretation:
- On the tested raw8 Gargoyle Power combat-loop route, the ordinary `gCTouchDamage_PS::CanBeActivatedNow` and `gCTouchDamage_PS::TriggerTarget` virtual boundaries are not the exact raw8 contact-consumption boundary.
- This is a clean negative result because the exact actor/SPU/C1/raw8-source/TouchDamage invocation scope remained active around `AICombatMoveInstr`; had either virtual been reached on that exact source, the diagnostic record would have been emitted.
- The three exact `Game+0x16E348` entries without either TouchDamage callback show that raw8 contact resolution on this route bypasses those ordinary virtual trigger callbacks.
- The result does **not** yet prove that the raw8 source's inherited `EntitiesVisited` / `EntitiesVisitedCount` arrays never change elsewhere. Because the probe captured those arrays only at the two candidate virtual boundaries, their absence leaves direct invocation-level visited-state behavior unresolved.
- Therefore the physical-source visited-list concept remains worth one smaller read-only check before abandoning it as a raw8 contact fact.

Scope / limits:
- Tested factual raw8 Gargoyle Power only.
- Rules out the exact `Game+0x692F0` / `Game+0x693B0` callbacks as the contact boundary on this tested route.
- Does not establish the final raw8 production consumption boundary.
- Does not prove absence of inherited trigger bookkeeping through some other internal path.
- Does not alter collision/opportunity behavior.

Provenance:
- Work implementation: `929bba9974788c873860f8e33f504c091f7aa524`.
- Diagnostic DLL SHA256: `F6EB69B1AFAFCB4C8F99FBE4C5CFDE1DC411FA074F109E7F5515D068E76096DD`.
- Canonical archived log: `research/archive/2026-09-20_observation_gargoyle_marker_frame_3_test_5.log`.
- Git blob: `ffb6d7ca49ee05b79a98320e5cd32ddfc594e88b`.

Disposition:
- **OBSERVATION PASS / CANDIDATE CALLBACKS RULED OUT.**
- Close the TouchDamage virtual-boundary probe.
- Before moving deeper into `Game+0x16E1A3 -> +0x16E348`, perform one minimal read-only check of the exact raw8 TouchDamage source's inherited visited bookkeeping across the whole combat-move invocation.

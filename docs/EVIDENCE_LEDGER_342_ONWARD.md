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


### EV-352 — Native human raw8 Fist group-combat control supports target-directed single-opportunity model

Observed:
- Runtime reused reviewed diagnostic implementation `929bba9974788c873860f8e33f504c091f7aa524`.
- The User entered group combat unarmed, locked onto `ReddockOrcScoutLeader`, and deliberately attempted native human Fist attacks with other opponents positioned between the player and the locked target, beside the target, and otherwise inside plausible body-swing geometry.
- The User observed no Fist hits on any non-target opponent.
- The complete log contains 25 player Fist C1 starts and eight exact native raw8 contact-path entries with:
  - `Caller=Game.dll+0x0016E348`;
  - `Arg1=Fist`;
  - `Arg2=PC_Hero`;
  - `Raw8UseType=8`.
- All eight exact entries target only `ReddockOrcScoutLeader`.
- No exact player-Fist `Game+0x16E348` entry targets any other Orc in the group.
- The eight entries span both native human Normal-Fist left/right attack motions.
- No `CORE RAW8_CONTACT_GATE` or `CORE RAW8_CONTACT_TARGET` record appears, consistent with EV-351's finding that this combat-loop route bypasses the ordinary TouchDamage virtual trigger callbacks.
- No anomaly, warning, contradiction, rejected marker, repair or divergence record appeared.

Interpretation:
- This controlled runtime strongly supports treating the tested native raw8 combat-loop mechanism as **target-directed**, rather than as a weapon-like spatial collision volume capable of consuming separate opportunities against every body intersecting the swing.
- Combined with EV-233 and EV-351, the result materially reduces the value of reproducing weapon/raw55 per-target visited-list bookkeeping for authored raw8.
- A smaller authoring model is justified for the next causal prototype: one pending authored raw8 opportunity per exact marked actor/C1 execution, with Gothic retaining target selection and contact resolution.
- The exact `Game+0x16E348` raw8 dispatch remains a contact-resolution candidate, not an HP-damage-success oracle. EV-349 already proves this boundary can be entered while Parade prevents visible damage.

Scope / limits:
- Native human Normal/Fist group-combat control only.
- The User's locked-target condition is part of the runtime fixture.
- This does not prove that no conceivable raw8 actor/family/state can ever resolve against a non-focused entity.
- It does not itself establish the final production pending-opportunity mechanism.

Provenance:
- Diagnostic implementation: `929bba9974788c873860f8e33f504c091f7aa524`.
- Canonical archived log: `research/archive/2026-09-20_observation_human_native_fist_not_targeted_hit_test.log`.
- Git blob: `cfceadf106abb5d955d299077682d38bfecfde6a`.
- User runtime observation: locked `ReddockOrcScoutLeader`; deliberate non-target interception attempts produced no observed Fist hits.

Disposition:
- **TARGET-DIRECTED RAW8 CONTROL PASS.**
- Do not add weapon-style per-target hit bookkeeping to the next raw8 prototype.
- Replace the planned standalone visited-list probe with the smaller pending-opportunity-token causal design.


### EV-353 — Raw8 persistent authored-opportunity token causal probe PASS

Runtime implementation:
- diagnostic probe implementation `e86c1ce03b36ef0ef7421a19284c5b38e58615ed`;
- generation-safe finalization correction `015a3ef90bf135cf502ac6507fb68f7c8c962800`;
- behavior-only twin source set unchanged;
- permanent `Raw8FistCollision.cpp/.h` unchanged.

Build/deployment:
- both collision twins built locally by the User;
- diagnostic twin deployed alone;
- built/live SHA256 both `539282F9DAD4A690CFE5AA22B5C5A85066EDFC81C617859EEDDE5341CE869DD5`;
- diagnostic deployment PASS;
- CORE profile, DEEP disabled;
- hooks installed and diagnostic DLL unloaded cleanly.

Marked-opportunity accounting across the four marked runtime logs:
- 81 accepted FIST opportunity opens;
- 59 exact `Game+0x16E348` raw8 contact-dispatch consumptions;
- 21 unused opportunities closed by C1 lifecycle;
- one earlier token ordinal was superseded by a later accepted FIST in the same C1, leaving one pending entitlement rather than stacking;
- therefore all 81 opens are accounted for;
- 614 exact miss-rearm writes were observed;
- 361 bounded timing-hold observations were observed;
- 41 contact-consumed tokens reached contact without a prior miss-rearm;
- **18 contact-consumed tokens first underwent one or more miss-rearms and later reached exact native contact in the same C1**;
- zero anomaly, contradiction, lifecycle-issue, repair-divergence or rejected-marker flags occurred in the five reviewed logs.

Gargoyle frame-3 Power fixture:
- test 6: 17 opportunities -> 15 exact contacts against `PC_Hero` + 2 clean `C1_FINALIZED` closes;
- 9 of the 15 contacts followed one or more miss-rearms;
- the two non-contact opportunities remained pending through 33 and 32 miss-rearms respectively, then closed at C1 finalization with confirmed latch `0 -> 1` and no contact;
- test 7: 4 opportunities -> 4 exact contacts; one followed five miss-rearms;
- additional Gargoyle attack executions deliberately interrupted by the User before frame-3 FIST acquired raw8 marked-execution ownership but never opened an opportunity token, as expected.
- User visual result: Gargoyle connected from near through the extreme end of its attack travel whenever the player remained reachable; deliberately moving out of range could avoid the hit.

Marked human group-combat control:
- 24 FIST opens: 22 Normal + 2 Power;
- 8 exact contact consumptions, all against `ReddockOrcScoutLeader`;
- 15 lifecycle closes: 12 `C1_FINALIZED`, 3 `C1_GENERATION_REPLACED`;
- one first token in C1 7 was superseded by a later FIST in the same C1; the replacement token then closed normally;
- the three generation-replacement closures occurred after an opportunity was already pending and while the player entered reaction generations (including QuickStumble-shaped transitions);
- each wrote the old pending latch `0 -> 1` with confirmed readback;
- after each close, the next exact player raw8 contact occurred only after a later FIST opened a new token;
- no old-opportunity cross-C1 contact leak occurred.
- User visual result: nearby, behind and intervening non-target opponents were not hit; several knockdowns/reactions occurred during the group fight.

Marked human one-on-one control:
- 36 FIST opens: 29 Normal + 7 Power;
- 32 exact contact consumptions against Golem: 25 Normal + 7 Power;
- 4 unused Normal opportunities closed at C1 finalization;
- 4 of the 32 contacts followed one or more miss-rearms;
- User visual timing result: behavior appeared correct.

Native unmarked human group-combat control:
- zero persistent-opportunity probe records, as required;
- 12 exact native Fist `Game+0x16E348` contacts;
- targets were only the two opponents the User reports deliberately locking/switching between: `ReddockOrcScoutLeader` (8) and `ReddockOrcScout02` (4);
- no non-target Fist contact was observed by the User despite opponents near, behind and between player and target.

Interpretation:
- **CAUSAL PASS.**
- An authored raw8 FIST opportunity can persist across repeated native one-shot misses and later be consumed by the first exact native raw8 contact-resolution dispatch within the same attack execution.
- Persistence does not force contact: moving fully out of reach leaves the opportunity pending until lifecycle closure.
- Exact C1 finalization/replacement closes unused opportunity and prevents observed cross-C1 leakage.
- Target selection/contact geometry remain Gothic-owned; the mechanism does not turn raw8 into weapon-style area collision.
- Unmarked raw8 remains native.
- The tested contact-consumption boundary remains policy-neutral with respect to HP outcome by design and prior EV-349 evidence; this batch did not add a dedicated Parade control.
- The corrected `FINALIZATION_GENERATION_CHANGED_NO_LATCH_WRITE` branch was not observed in this batch; its safety remains source-reviewed rather than runtime-exercised.

Provenance:
- User deployment/startup report, 2026-09-20.
- `research/archive/2026-09-20_observation_gargoyle_marker_frame_3_test_6.log`, blob `47d0eb29bd39b32b3397b74fb239dc5611723637`.
- `research/archive/2026-09-20_observation_gargoyle_marker_frame_3_test_7.log`, blob `bc55cb657483663a5e918e2edb595899ba45fc7c`.
- `research/archive/2026-09-20_observation_human_marked_fist_not_targeted_hit_test.log`, blob `d50beda22c7b49553818c19340efb03567dc296f`.
- `research/archive/2026-09-20_observation_human_marked_fist_one_on_one_hit_test.log`, blob `5ef5749588476b99987ee1f042e0cca8bc6680ec`.
- `research/archive/2026-09-20_observation_human_native_fist_not_targeted_hit_test2.log`, blob `5fc350209e2e2f9eba651993a89575e71bd1652a`.

Disposition:
- **RAW8 PERSISTENT OPPORTUNITY CAUSAL PROBE CLOSED/PASS.**
- Do not run another exploratory contact-boundary/visited-list probe.
- Next responsibility is Normal Chat production-architecture review/freeze; production promotion is not implied by this evidence entry.


### EV-354 — Sabretooth raw8 Sprint-origin Action9 -> Action2 pending-opportunity sentinel PASS

Fixture:
- native Sabretooth;
- existing single-FIST marked raw8 fixture;
- source-unchanged EV-353 diagnostic implementation;
- factual Sprint action uses the same PowerAttack-named Hit motion as Power in the tested Sabretooth route; this test concerns action/origin transport inside one motion/C1, not a Sprint-animation -> Power-animation asset change.

Large-log provenance:
- canonical raw: `research/archive/2026-09-20_observation_sabertooth_marker_power_sprint_transition_test.log`;
- source SHA256: `B799B07228C83AE1A6D09928835A206DC7BDFAF77BBF8F5D8771D6EB3E4BE845`;
- source size: 1,261,750 bytes / 4,068 lines;
- deterministic POP-07 package: `research/derived/2026-09-20_observation_sabertooth_marker_power_sprint_transition_test_large_log/`;
- package contains 22 complete line-numbered full-source parts.

Whole-run raw8 opportunity accounting:
- 55 accepted single-FIST opportunities opened;
- 36 exact native raw8 contact-dispatch consumptions;
- 19 unused opportunities closed at `C1_FINALIZED`;
- 824 miss-rearm writes;
- 332 timing-hold observations;
- therefore all 55 opens have exactly one terminal disposition;
- zero marker rejection, contradiction, lifecycle-issue, repair-divergence, invariant-warning or generation-changed/no-write anomaly was found in the complete mirror.

Decisive Sprint-origin transport:
- **20 distinct tokens opened while factual `Action=9 / SPRINT` and were later consumed while factual `Action=2 / POWER` in the same C1**;
- C1 generations: 36, 45, 55, 64, 75, 85, 94, 103, 114, 124, 134, 143, 153, 174, 183, 193, 207, 216, 229, 239;
- every one kept the same token ordinal across the Action9 -> Action2 observation;
- none was closed or consumed merely because Action/family changed;
- all 20 ended in exact native `Game+0x16E348` contact consumption.

Strong delayed-contact samples:
- C1 183 / token 43:
  - OPEN under Action9/SPRINT;
  - pre-threshold timing permission;
  - native miss -> confirmed latch `1 -> 0` rearm under Action9;
  - same token remains live;
  - exact contact consumption occurs under Action2/POWER using the same `Sabertooth_..._PowerAttack_...xmot` motion;
  - immediate matching native `OnDamage` dispatch to `PC_Hero`.
- C1 207 / token 47 shows the same sequence independently.

User visual observation:
- Sabretooth could hit whenever it should have during the long run; no visible failure was observed from the Sprint/Power action transition.

Interpretation:
- **PASS.**
- Raw8 opportunity lifetime must be bound to factual C1 execution identity, not current Action/family.
- In the tested native Sabretooth route, Sprint is an Action9 origin/state using the PowerAttack-named animation motion; the same motion later appears under Action2/POWER inside the same C1.
- An already-open opportunity survives that factual Action9 -> Action2 change and remains available until exact native contact.
- The result directly validates the permanent architecture's protected Sprint-origin lifecycle rule before production implementation.

Disposition:
- Pre-Work Sprint-transport sentinel CLOSED/PASS.
- No source change is required from this sentinel.
- The frozen permanent raw8 production implementation may proceed after current-state promotion and POP-12 validation.


### EV-355 — Permanent raw8 production-candidate broad diagnostic smoke PASS

Build/runtime identity:
- local checkout before build: `95e8a24800dae778166788de36a31818933e3ff1`;
- permanent raw8 source candidate: `7c9c9c2a4512b44ff64c09ef9866b7160f4d5cbd` (all later commits through the tested checkout were documentation-only);
- both `Script_FrameCollisionBehaviorTest` and `Script_FrameCollisionTest` built successfully from the same checkout;
- deployed diagnostic twin SHA256: `D257DEA36BFF74BFBCF00D54BD36E08769D19DCA794E96CCA93AD48169D0023A`;
- POP-03 sole-live diagnostic deployment/hash gate PASS;
- POP-04 diagnostic startup/hook-install/clean-unload gate PASS.

Batch scope:
- marked single-FIST Sabretooth, native creature then transformed-player symmetry;
- unmarked Wolf/raw8, native creature then transformed-player symmetry;
- marked single-FIST Wolf, native creature then transformed-player symmetry;
- Troll/raw55 four-family coexistence plus player marked equipped attacks;
- broad player marked equipped-weapon attacks against Golem;
- previously untested `Nemora_TRex_01` / T-Rex ("Snorting Monster" animation set) as an unmarked raw8 creature while the player used marked 1H+shield attacks.

Raw8 production accounting:
- Sabretooth log: 29 accepted opportunities opened; 15 exact contact consumptions; 14 unused lifecycle closes; 460 miss-rearms; therefore all 29 opportunities reached exactly one terminal disposition and no contact-consumed opportunity later emitted `RAW8_OPPORTUNITY_CLOSE`.
- Native Sabretooth contributed 22 opens -> 8 contact consumptions + 14 closes; transformed-Sabretooth contributed 7 opens -> 7 contact consumptions.
- Marked Wolf log: 35 opens; 17 exact contact consumptions; 17 lifecycle closes; 515 miss-rearms. Every completed opportunity had exactly one terminal disposition. The sole unmatched final open was Wolf C1=47 / ordinal 35, opened and miss-rearmed three times immediately before normal DLL unload with no later C1-finalization event; it is bounded as test termination during an in-progress attack, not an observed continued-runtime leak.
- Marked Wolf transformed-player route fully accounted: 11 opens -> 10 contact consumptions + 1 close.
- All observed raw8 opportunity latch writes/rearms requiring confirmation were confirmed.
- No opportunity emitted both `CONTACT_CONSUMED` and later routine `CLOSE`.
- No same-opportunity Action9/SPRINT -> Action2/POWER transport happened naturally in this smoke; that lifetime rule remains directly proven by EV-354 rather than re-proven here.

Native fallback / coexistence:
- unmarked Wolf log contained zero `RAW8_FIST_OWNERSHIP`, zero `RAW8_OPPORTUNITY_*`, and zero authored marker events while native raw8 contacts continued; native fallback remained intact in both native/transformed portions of the run.
- Troll/raw55 produced 37 accepted FIST marker observations across all permanent families: Quick 20, Normal 11, Power 2, Sprint 4. Existing selective native-open suppression and authored-FIST activation remained active without contradiction.
- The same Troll coexistence run also accepted 33 player RIGHT equipped markers across factual UseTypes 2, 3 and 12, including Normal/Quick/Power/Hack/Pierce coverage.
- The Golem-target run exercised player RIGHT/LEFT/BOTH/OFF markers across factual UseTypes 2, 3 and 12; routine duplicate/authored-occurrence-budget ignores remained diagnostic dedupe rather than rejection. One `ONDAMAGE_CAP` after 64 entries was normal diagnostic throttling.
- The T-Rex run is **not** a marked-T-Rex raw8 proof: its own factual Fist/UseType8 attacks were unmarked/native. It adds compatibility confidence for an untested creature/animation set while 12 player 1H RIGHT markers were accepted against it with normal equipped cleanup.

Whole-batch health:
- zero marker rejection;
- zero contradiction/invariant/error/failure diagnostics;
- zero completed C1 final records with outstanding source obligations;
- no behavior repair divergence observed;
- all six logs ended with clean diagnostic DLL unload.

User-observed setup:
- Sabretooth and both Wolf runs let the creature attack first, then used god mode + transformation to attack back as that creature.
- Troll/Golem target runs used multiple player weapons with marked animations.
- T-Rex/Snorting-monster target run used player sword+shield marked attacks.
- User intentionally broadened the smoke beyond the minimum frozen request to increase confidence before the final source-quality audit.

Provenance:
- uploaded in commits `82fbd5767d94ba6de2f87206623d14af2b886fc9` and `abb80f2b25b2e230b45f34cac8f9a3d03c79b4a1`;
- `research/archive/2026-09-21_raw8prod_smoke_sabretooth_single_fist.log`, blob `88981e3d3c712c3e0b91cd919fb1fe8496bedd37`, 515,928 bytes / 1,548 lines;
- `research/archive/2026-09-21_raw8prod_smoke_wolf_native_single_fist.log`, blob `618fa3d6ed49674fc5411d560e71e105f04d7dfb`, 319,486 bytes / 922 lines;
- `research/archive/2026-09-21_raw8prod_smoke_wolf_marked_single_fist.log`, blob `3e267b5c3aa6870c99b1b97c4cc8df55f3a9605b`, 649,809 bytes / 1,946 lines;
- `research/archive/2026-09-21_collision_smoke_native_fallback_raw55_coexistence.log`, blob `5e6c159a323ff68d5fc304563ce6d06353609ec6`, 355,749 bytes / 1,451 lines; this is the Troll/raw55 coexistence fixture;
- `research/archive/2026-09-21_raw8prod_smoke_Troll_marked_single_fist.log`, blob `2e3e2bd06fe8645c361491997fb12e28c0470796`, 560,566 bytes / 2,211 lines; despite the filename, the recorded target fixture is Golem and the filename is preserved unchanged as raw provenance;
- `research/archive/2026-09-21_raw8prod_smoke_Trex_marked_single_fist.log`, blob `283ca916dc6805a367538b1a12c5bfc664fb206c`, 198,800 bytes / 794 lines.

Interpretation:
- **PASS — BROAD DIAGNOSTIC SMOKE.**
- The permanent raw8 source candidate behaves coherently under marked native/transformed raw8, unmarked native fallback, permanent raw55 coexistence, multiple equipped weapon sources, a familiar Golem target and a previously untested T-Rex target fixture.
- The diagnostics-only compaction correction is runtime-consistent: contact-consumed opportunities do not later produce routine lifecycle CLOSE records.
- No new causal or architecture question is opened by this batch.

Disposition:
- Diagnostic smoke gate CLOSED/PASS.
- This batch does not replace the frozen focused permanent raw8 acceptance matrix and does not certify the new T-Rex as a marked raw8 route.
- Next gate is a minimal diagnostics-free behavior-twin smoke from the already-built same-source binary, followed by the planned bounded read-only code-quality/modularity audit before any full acceptance campaign.


### EV-356 — Diagnostics-free behavior-twin broad functional smoke PASS

Build/runtime identity:
- source candidate: `7c9c9c2a4512b44ff64c09ef9866b7160f4d5cbd`;
- both collision twins had already built successfully from the same checkout used for EV-355;
- deployed behavior twin: `Script_FrameCollisionBehaviorTest.dll`;
- SHA256 built/live: `14F1AFE65CBE78E75B73535E46A71E43BEA5CCC6E95BC58EFFF894EC2888B324`;
- POP-03 behavior sole-live deployment/hash gate: PASS;
- diagnostics are absent by design in this product; no diagnostic log is expected.

User functional smoke:
- opponents/fixtures included Wolf, Sabretooth, Golem and Troll;
- player exercised 1H, 1H+torch, dual-1H, 2H and Staff marked attacks;
- all tested behavior remained visually functional and no startup/runtime crash was observed.

Useful positive discriminators observed by the User:
- Hack attack behavior worked; this is a mod-provided route rather than a useful native fallback equivalence.
- Troll Quick attack produced its authored repeated/two-contact behavior under the permanent raw55 system.
- On the tested first normal 1H+torch attack, native Gothic places collision on the wrong/left hand relative to the authored right-hand strike; the authored RIGHT marker produced collision on the intended right-hand source.
- On the tested dual-1H Power attack, native Gothic normally resolves only two contacts although the animation is authored for three; the marked behavior produced all three authored contacts.

Interpretation:
- **PASS — DIAGNOSTICS-FREE BEHAVIOR SMOKE.**
- The behavior-only twin preserves intended collision behavior without `CollisionDiagnostics` compiled in, providing a direct release-purity/parity sentinel after the permanent raw8 promotion.
- The positive-discriminator observations provide stronger confidence than a crash-only smoke because they exercise behavior that would visibly differ under native-only execution.
- This remains a pre-audit smoke, not the full frozen acceptance/regression campaign.

Future New Balance note:
- New Balance fixes some useful vanilla collision mistakes, so later compatibility/regression should prefer deliberately authored positive discriminators (for example attacks authored for three Normal/Quick contacts) rather than relying on vanilla bugs remaining observable.

Disposition:
- Behavior-only smoke gate CLOSED/PASS.
- Diagnostic + behavior smoke prerequisites for the planned final source-quality/modularity audit are complete.
- Next responsibility is the bounded read-only formal audit; no source cleanup is authorized by EV-356 itself.


### EV-357 — Final post-cleanup diagnostic build/startup + targeted re-smoke PASS

Source/build identity:
- final source candidate: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- combined cleanup includes `9789254866bb47dcbadb145aeb9831c7c0e4e97f` generation-qualified C1 metadata retirement plus `f1f5d2aad3edc3564a9a8b40541840b94f8fa903` release/diagnostic hygiene;
- both twins built successfully from the maintained checkout after both cleanups;
- deployed diagnostic SHA256 built/live: `5AD5B33A8826DB5E78F4AECADC3FF48546E1C54ADA3BE9ED2BE9A54E6190E313`;
- sole-live diagnostic deployment/hash: PASS;
- CORE startup/hook installation/clean unload: PASS;
- startup `BehaviorCore:` correctly includes permanent `EquippedSprintCollision` and `PhysicalFistCollision`.

Raw8 Sabretooth re-smoke:
- 31 marked opportunities opened;
- 16 exact contact consumptions;
- 14 exact C1-finalization closes;
- 485 miss-rearms;
- zero opportunity received both CONTACT_CONSUMED and CLOSE;
- 30 completed opportunities therefore have exactly one terminal disposition;
- the sole unmatched final opportunity was Sabretooth C1=44 / ordinal 31, opened under Action9/SPRINT and still actively miss-rearming immediately before normal DLL unload, with no later C1 finalization in the file; bounded as test termination during an in-progress attack, not continued-runtime stale state;
- native Sabretooth portion: 23 opens, 8 contacts, 14 closes plus the final in-progress opportunity;
- transformed-Sabretooth portion: 8 opens -> 8 contact consumptions;
- all observed miss rearm writes remained 1->0 with confirmed readback;
- no double-terminal, rejection, contradiction, invariant, repair or error record.

Equipped-Sprint compact-CORE re-smoke:
- Goblin/raw2 produced four factual Action9/SPRINT bindings and four corresponding generic RIGHT marker authorizations;
- all eight material `CORE EQUIPPED_SPRINT_COLLISION` records are compact and pointer-free;
- no routine `NO_BOUND_SPRINT_ORIGIN` or unrelated no-bound callback spam appeared;
- all four marker authorizations were accepted;
- this particular runtime sample did not naturally enter the same-C1 Action9 -> Action2 continuation, so EV-357 does not re-prove that already-closed behavior sentinel; static review confirms the material marker authorization path still emits `BOUND_SPRINT_ORIGIN_POWER_CONTINUATION` when factual Power continuation occurs;
- the same log finalized 101 C1s at outstanding zero with no stale marker/binding contradiction.

Raw55 + generic equipped re-smoke:
- Troll/raw55 produced 36 accepted FIST marker events across Quick 26, Normal 6 and Sprint 4;
- 12 separate Quick C1s each completed the authored two-FIST sequence: AcceptedFistCount 1 -> 2 in the same C1;
- player marked attacks against Troll exercised 1H1H and Staff-related factual sources, with RIGHT/LEFT/BOTH/OFF traffic and factual UseTypes 2 and 12;
- 78 total marker records: 62 ACCEPTED, 4 OFF_ACCEPTED, 8 AUTHORED_OCCURRENCE_BUDGET_IGNORED and 4 DUPLICATE_SAME_UPDATE_IGNORED;
- the ignored occurrence/dedupe records were confined to their own finalized C1s; no generation/identity-inconsistent result occurred;
- 94 C1 finals all ended at outstanding zero;
- zero raw55 identity contradiction, marker rejection, lifecycle invariant, repair divergence or error.

Whole-batch result:
- visual behavior reported normal by the User;
- raw8 persistent opportunity remains healthy after release-purity cleanup;
- generation-qualified metadata retirement produced no stale-state or premature-retirement symptom across heavy C1 churn;
- raw55 repeated-FIST same-C1 ownership survived;
- generic equipped marker occurrence/dedupe state resets correctly across generations;
- compact EquippedSprint CORE is materially quieter while retaining actual bind/authorization evidence;
- startup identity correction is runtime-confirmed.

Provenance:
- `research/archive/2026-09-21_final_cleanup_resmoke_raw8_sabretooth.log`, blob `8cc386857e42484a9280b113adf06e7111a083ae`, 262,205 bytes / 965 lines;
- `research/archive/2026-09-21_final_cleanup_resmoke_equipped_sprint.log`, blob `b0a9ac1e132149dc2dfba9bcec682be352cdfa9a`, 295,601 bytes / 1,266 lines;
- `research/archive/2026-09-21_final_cleanup_resmoke_raw55_equipped.log`, blob `45bc70ffcf632c544e54ec4318531b51a8b51e8c`, 203,990 bytes / 971 lines.

Interpretation:
- **PASS — FINAL POST-CLEANUP DIAGNOSTIC RE-SMOKE.**
- No source contradiction or new cleanup requirement was exposed.
- Next gate is the diagnostics-free behavior-twin deployment/hash + small functional parity re-smoke from the already-built same-source binary.


### EV-358 — Final post-cleanup diagnostics-free behavior parity smoke PASS / source freeze

Source/build identity:
- final source candidate: `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- both collision twins had rebuilt successfully from the same maintained checkout after the two accepted final cleanup commits;
- deployed behavior twin: `Script_FrameCollisionBehaviorTest.dll`;
- built/live SHA256: `A806EC6523116286335A659735067B1AA6C581837B3E0D604E6271AC98079340`;
- POP-03 behavior sole-live deployment/hash gate: PASS;
- diagnostics are absent by design; no runtime log is expected.

User functional parity smoke:
- marked Sabretooth/raw8 contacted the player normally;
- Troll/raw55 Quick produced the authored repeated/two-contact result;
- tested first Normal 1H+torch attack used the authored right-hand collision source rather than Gothic's known native left-hand mismatch on that animation;
- 2H Hack worked;
- Staff Hack worked;
- dual-1H Power produced all three authored contacts;
- ordinary marked 1H behavior was visually improved relative to the native timer on the User's fast authored animations, where the native collision opening can occur late enough to miss;
- no crash or visible regression was reported.

Interpretation:
- **PASS — FINAL POST-CLEANUP DIAGNOSTICS-FREE BEHAVIOR PARITY SMOKE.**
- The final release-purity cleanup did not remove behavior required by raw8, raw55, equipped markers, Hack or repeated-contact semantics.
- The observations are positive mod discriminators rather than crash-only equivalence: several tested outcomes are known to differ from or improve on the native collision route for these authored fixtures.
- Together EV-357 + EV-358 close the final post-audit re-smoke requirement for the combined cleanup source.

Source-freeze disposition:
- `f1f5d2aad3edc3564a9a8b40541840b94f8fa903` is **SOURCE-FROZEN FOR FOCUSED PERMANENT RAW8 ACCEPTANCE**.
- No further source cleanup is justified by the final audit/re-smoke sequence.
- Any later source modification requires a newly demonstrated contradiction, a newly frozen bounded responsibility, rebuild of both twins, and revalidation of affected acceptance evidence.
- Next gate is the focused permanent raw8 acceptance matrix in `COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md` §14 before Phase 4 broad regression resumes.

Provenance:
- behavior DLL SHA256 `A806EC6523116286335A659735067B1AA6C581837B3E0D604E6271AC98079340`;
- User visual runtime report on 2026-09-21;
- no diagnostic artifact expected from behavior-only product.


### EV-359 — Focused permanent raw8 acceptance batch 1

Source/runtime:
- frozen source `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- diagnostic DLL SHA256 `5AD5B33A8826DB5E78F4AECADC3FF48546E1C54ADA3BE9ED2BE9A54E6190E313`;
- visual behavior reported normal.

Gargoyle frame-3 Power:
- 7 marked POWER opportunities opened and all 7 later contacted;
- 78 miss-rearms;
- six opportunities survived one or more misses before contact;
- strongest delayed contacts were ~203 ms / 25 rearms and ~246 ms / 32 rearms after OPEN;
- zero contradiction, rejection, invariant, repair divergence or error.
- Acceptance item 1: close/immediate and delayed-contact PASS; true far/no-contact terminal case not observed because every opportunity eventually contacted.

Marked human raw8:
- NORMAL: 23 opens -> 18 contacts + 5 exact C1-finalization closes;
- POWER: 53 opens -> 29 contacts + 15 exact C1-finalization closes + 9 first opportunities superseded by a later accepted FIST in the same C1;
- 20 POWER C1s contained two accepted FIST opens;
- 11 of those showed OPEN -> CONTACT -> later OPEN -> CONTACT in the same C1;
- all 20 unused-opportunity closes were `C1_FINALIZED`, exact latch `0->1`, write-confirmed;
- zero contradiction, rejection, invariant, generation inconsistency, repair divergence or error.

Focused acceptance status:
1. Gargoyle close/delayed/no-contact: PARTIAL — close + delayed PASS; far/no-contact still open.
2. Human Normal/Power timing/contact: PASS.
3. Later FIST same C1 reopening without stacking: PASS.
4. Ordinary no-contact C1 finalization: PASS.
5. Post-FIST reaction/generation replacement: OPEN.
6. Replacement/interruption -> later unmarked raw8 native fallback: OPEN.
7. Native unmarked human target-directed control on frozen source: OPEN.
8. Sprint-origin same-C1 Action9 -> Action2 sentinel on frozen source: OPEN.
9. raw55 + equipped coexistence: PASS EV-357.
10. diagnostic/behavior parity: PASS EV-357 + EV-358.

Provenance:
- `research/archive/2026-09-21_raw8_final_acceptance_gargoyle_frame3_power.log`, blob `2ee001836dcd396593e2417f14a9a7f6757367ae`, 117,349 bytes / 570 lines;
- `research/archive/2026-09-21_raw8_final_acceptance_human_normal_power.log`, blob `b010fbb2cc873eac1f64d1cc5e4047810ff6e660`, 690,945 bytes / 2,959 lines.

Interpretation:
- **PASS for focused items 2, 3 and 4; PARTIAL for item 1.**
- No frozen-source contradiction exposed.


### EV-360 — Focused permanent raw8 acceptance batch 2

Source/runtime:
- frozen source `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- diagnostic DLL SHA256 `5AD5B33A8826DB5E78F4AECADC3FF48546E1C54ADA3BE9ED2BE9A54E6190E313`;
- User reported all four runs visually healthy.

Gargoyle frame-3 far/no-contact:
- 11 marked POWER opportunities opened;
- 8 later contacted;
- 3 ended without contact;
- C1 6 / ordinal 2 survived 33 miss-rearms for ~262 ms and closed at `C1_FINALIZED`, exact latch `0->1`, confirmed;
- C1 77 / ordinal 9 survived 33 miss-rearms for ~251 ms and closed at `C1_FINALIZED`, exact latch `0->1`, confirmed;
- C1 115 / ordinal 11 survived 4 miss-rearms and closed on factual generation replacement with exact latch `0->1`, confirmed;
- zero contradiction/rejection/invariant/repair/error.
- Combined with EV-359 close/immediate + delayed-contact evidence, focused item 1 is PASS.

Human reaction/replacement:
- the dedicated reaction-replacement file exercised extensive marked human raw8 traffic against Wolf/Golem plus player Wrestling/UseType12 marker traffic, but it did not itself capture a raw8 `C1_GENERATION_REPLACED` terminal event;
- no contradiction/rejection/invariant/repair/error occurred.
- Therefore replacement acceptance is taken from the group-combat control below, not inferred from this file.

Human group combat / replacement:
- 56 marked human FIST opportunities were opened; this file is therefore **not** an unmarked/native control despite its filename;
- 7 pending opportunities closed specifically as `C1_GENERATION_REPLACED`;
- replacement actions were factual Action26 four times and Action29 three times, consistent with reaction/stumble/knockdown-style replacement traffic in the observed motions;
- every replacement close wrote old pending latch `0->1` with confirmed readback;
- no replaced old opportunity ordinal later produced `CONTACT_CONSUMED`;
- player exact native raw8 contact-dispatch entries targeted only `ReddockOrcScoutLeader` (7) and `ReddockOrcWarrior01` (1); no Fist contact was logged against the other nearby Orcs;
- User deliberately switched targets and reported being unable to hit non-target opponents despite trying;
- Orc weapon traffic concurrently exercised factual Staff/halberd raw51 and Axe/raw52 Normal/Quick/Power/Whirl/Hack marker routes without collision/lifecycle contradiction.
- Focused item 5 PASS: pending marked opportunities are closed on reaction/generation replacement and no old-opportunity cross-generation contact leak is observed.
- Focused item 7 remains OPEN because the human attacks in this file were marked, not native/unmarked.
- Focused item 6 remains OPEN: after the first two replacement closures, the next player raw8 contacts were preceded by a new accepted FIST; after the later replacement closures no later player raw8 contact occurred. Thus this batch does not prove replacement -> later **unmarked** native fallback.

Sabretooth Sprint-origin transport:
- native Sabretooth opened 57 raw8 opportunities: 40 SPRINT-origin, with 24 contacts and 33 closes overall;
- **15 distinct opportunities opened under factual Action9/SPRINT and were later consumed under factual Action2/POWER in the same C1, same opportunity ordinal and same PowerAttack-named motion**;
- transformed player `Transform_Sabertooth_Potion` separately opened 27 marked opportunities across Normal 10, Quick 12 and Power 5; all 27 were contact-consumed, with zero lifecycle close;
- player concurrently exercised Rusty 1H/raw2 Normal + Quick marker traffic without contradiction.
- Focused item 8 PASS on the frozen source.

Additional side coverage:
- Gargoyle run exercised player 2H Flamberge/UseType3 Normal + Quick marker traffic;
- reaction run exercised player Wrestling/UseType12 Normal + Quick;
- group-combat run exercised multiple Orc raw51/raw52 weapon families;
- Sprint run exercised player Rusty 1H/raw2 and transformed-Sabretooth raw8;
- all side routes were visually reported healthy and emitted no contradiction/rejection/invariant/repair/error.

Focused acceptance status after EV-360:
1. Gargoyle close/delayed/no-contact -> PASS EV-359 + EV-360.
2. Human Normal/Power timing/contact -> PASS EV-359.
3. Later FIST same C1 reopening -> PASS EV-359.
4. Ordinary no-contact finalization -> PASS EV-359.
5. Reaction/generation replacement -> PASS EV-360.
6. Replacement -> later unmarked native fallback -> OPEN.
7. Native unmarked human target-directed control -> OPEN.
8. Sprint Action9 -> Action2 transport -> PASS EV-360.
9. raw55 + equipped coexistence -> PASS EV-357.
10. Diagnostic/behavior parity -> PASS EV-357 + EV-358.

Provenance:
- `research/archive/2026-09-21_raw8_final_acceptance_gargoyle_frame3_far_no_contact.log`, blob `c1b95f07bb78acd76329fb567da9b409f8d32f18`, 163,643 bytes / 782 lines;
- `research/archive/2026-09-21_raw8_final_acceptance_human_reaction_replacement.log`, blob `6913d6ee4ef81ead30ab5e5511ce0aebd18812aa`, 781,802 bytes / 3,413 lines;
- `research/archive/2026-09-21_raw8_final_acceptance_human_unmarked_target_control.log`, blob `41dd4d097b3d548e5e1b7021dc424ceff41907ba`, 808,102 bytes / 3,571 lines;
- `research/archive/2026-09-21_raw8_final_acceptance_sabretooth_sprint_transport.log`, blob `eed08f55f979407cc805aaa4b71f4377cece107e`, 828,946 bytes / 3,309 lines.

Interpretation:
- **PASS for focused items 1, 5 and 8.**
- Items 6 and 7 remain the only open focused raw8 acceptance responsibilities.
- No frozen-source contradiction exposed.


### EV-361 — Motion-specific correction: frozen-source native/unmarked human target-directed control PASS

Reason for revisit:
- The EV-360 group-combat log was initially classified too coarsely at file level because the same session contained many marked human FIST attacks.
- The User clarified that `Hero_Stand_None_Fist_P1_Attack_Hit_N_Fwd_00_%_00_P0_100_L.xmot` had deliberately had its marker removed so marked and genuinely unmarked human raw8 attacks would coexist in one group-combat session.
- Re-analysis was therefore performed by exact motion identity.

Exact unmarked-motion evidence:
- target motion: `Hero_Stand_None_Fist_P1_Attack_Hit_N_Fwd_00_%_00_P0_100_L.xmot`;
- 29 `CORE ATTACK_OWNERSHIP` records for that motion;
- all 29: `MarkerPresent=0`, `RequiredMask=0`, `FistMarkers=0`, `Raw8Fist=<none>`, `Raw8UseType=-1`, `SuppressNative=0`, `Classification=ROUTINE`;
- zero `RAW8_FIST_OWNERSHIP` records on that motion;
- zero `RAW8_OPPORTUNITY_OPEN` records on that motion;
- zero `RAW8_OPPORTUNITY_CONTACT_CONSUMED` records on that motion;
- zero authored FIST marker records on that motion.

Native contact evidence:
- 2 exact raw8 native contacts occurred while that exact unmarked motion was active;
- both entered through caller `Game.dll+0x0016E348`;
- both were factual `Arg1=Fist / Arg2=PC_Hero`;
- both targeted `ReddockOrcScoutLeader`;
- no unmarked left-hand Fist contact was observed against the other nearby Orcs.
- The User reports deliberately switching targets and repeatedly trying to hit non-target opponents during the group fight, while only targeted opponents could be hit.

Interpretation:
- The exact P1-left human Normal motion remained fully native/unmarked in the frozen diagnostic build even though marked human Fist animations were exercised in the same session.
- Its native contact path remained target-directed and did not become weapon-style area collision.
- Focused §14 item 7, native unmarked human target-directed group control, is **PASS** on frozen source `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`.

Item 6 remains open:
- the same group-combat run contains seven valid marked-opportunity `C1_GENERATION_REPLACED` closures;
- however, the two observed unmarked P1-left contact events were not cleanly the first raw8 contacts after a replacement with no intervening newly marked opportunity;
- therefore the stricter sentinel `marked pending -> replacement/interruption -> later unmarked raw8 native fallback` is not yet closed by this batch.

Correction to EV-360 interpretation:
- EV-360's file-level statement that the human control was not usable as unmarked/native evidence was too broad.
- The file is mixed: marked P0/right human Fist routes coexist with a genuinely unmarked P1/left Normal route.
- EV-360's replacement findings remain valid; EV-361 corrects only the unmarked-control disposition.

Provenance:
- same canonical archived log: `research/archive/2026-09-21_raw8_final_acceptance_human_unmarked_target_control.log`;
- blob `41dd4d097b3d548e5e1b7021dc424ceff41907ba`;
- User clarification on exact unmarked motion, 2026-09-21.

Focused acceptance status after EV-361:
1. Gargoyle close/delayed/no-contact -> PASS EV-359 + EV-360.
2. Human Normal/Power timing/contact -> PASS EV-359.
3. Later FIST same C1 reopening -> PASS EV-359.
4. Ordinary no-contact finalization -> PASS EV-359.
5. Reaction/generation replacement -> PASS EV-360.
6. Replacement -> later unmarked native fallback -> OPEN.
7. Native unmarked human target-directed control -> PASS EV-361.
8. Sprint Action9 -> Action2 transport -> PASS EV-360.
9. raw55 + equipped coexistence -> PASS EV-357.
10. Diagnostic/behavior parity -> PASS EV-357 + EV-358.

Interpretation:
- **Only focused item 6 remains open.**
- No frozen-source contradiction exposed.


### EV-362 — Final focused fallback sentinel attempt: fixture correct, decisive replacement sequence not captured

Source/runtime:
- frozen source `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- diagnostic DLL unchanged from frozen-source acceptance campaign;
- User intentionally reversed marker polarity for the human Normal pair:
  - marked: `Hero_Stand_None_Fist_P1_Attack_Hit_N_Fwd_00_%_00_P0_100_L.xmot`;
  - unmarked/native: `Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot`.
- visual behavior reported normal.

Marked P1-left route:
- 38 attack-ownership observations and 39 accepted FIST markers;
- 39 exact raw8 opportunities opened;
- 31 contact consumptions;
- 8 ordinary `C1_FINALIZED` closes;
- terminal accounting therefore complete for all 39 opens;
- zero marked-opportunity `C1_GENERATION_REPLACED` close occurred in this run.

Unmarked P0-right route:
- 39 attack-ownership observations;
- every observed execution: `MarkerPresent=0 / RequiredMask=0 / FistMarkers=0 / Raw8Fist=<none> / Raw8UseType=-1 / SuppressNative=0 / Classification=ROUTINE`;
- zero raw8 ownership records on the motion;
- zero raw8 opportunity opens on the motion;
- zero raw8 opportunity-consumption records on the motion;
- zero authored FIST markers on the motion;
- 7 exact native raw8 contacts through `Game.dll+0x0016E348`;
- native contacts targeted the currently engaged Orc routes: `ReddockOrcScoutLeader`, `ReddockOrcWarrior01`, and `ReddockOrcScout01`.

Replacement analysis:
- the log contains 16 factual `C1_START ... ReplacedGeneration=...` events for the player;
- **none** of those replaced-generation ids intersects a C1 that had an open marked P1-left opportunity;
- therefore the required sequence `marked pending -> generation replacement -> later unmarked native fallback` did not occur;
- this is a test-window miss, not a behavioral contradiction.

Diagnostics:
- zero contradiction;
- zero invariant warning;
- zero generation inconsistency;
- zero repair divergence;
- zero explicit error/failure/rejection record;
- clean runtime behavior reported by the User.

Focused acceptance disposition:
- item 6 remains OPEN solely because the decisive pending-marked replacement chronology was not observed;
- item 7 remains PASS and is independently reinforced by the healthy unmarked P0-right route in this run;
- no source change is justified.

Provenance:
- `research/archive/2026-09-22_human_fist_marked_unmarked_test.log`;
- blob `6052582be2139d16bf13fdff0ecd879fc2e507de`;
- 429,381 bytes.

Interpretation:
- **INFORMATIVE / NO CONTRADICTION.**
- Fixture polarity is now correct for the final sentinel.
- The next attempt should focus only on getting an opponent reaction/interruption during the short interval after the marked P1-left FIST has opened and before that opportunity contacts or finalizes.


### EV-363 — Final focused fallback sentinel: replacement timing captured, but intended fallback motion remained marked at runtime

Source/runtime:
- frozen source `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- source log `2026-09-22_human_fist_marked_unmarked_test2.log`;
- source SHA256 `1176CF999FBDAAE70C4D1AACD8730A3F917CAE86A66006F99E2FD4F91D1440AB`;
- 1,791,903 bytes / 7,726 source lines;
- analyzed losslessly through the deterministic `Prepare-Log.cmd` package in `research/derived/2026-09-22_human_fist_marked_unmarked_test2_large_log/`.

Intended fixture:
- marked P1-left: `Hero_Stand_None_Fist_P1_Attack_Hit_N_Fwd_00_%_00_P0_100_L.xmot`;
- intended unmarked P0-right: `Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot`.

Observed runtime marker state:
- P1-left: 60 ATTACK_OWNERSHIP observations, all `MarkerPresent=1 / FistMarkers=1`;
- P0-right: 60 ATTACK_OWNERSHIP observations, all `MarkerPresent=1 / FistMarkers=1`;
- P0-right therefore remained a marked raw8 route at runtime rather than the intended native/unmarked fallback;
- P0-right opened 91 raw8 opportunities and emitted raw8 contact/finalization/replacement behavior, confirming the marker was behaviorally active rather than a stale display field.

Decisive timing was nevertheless captured twice:
1. P1-left C1=8 / opportunity 4:
   - marked opportunity OPEN at 41758.757 ms;
   - `C1_GENERATION_REPLACED` close at 41972.990 ms;
   - next relevant P0-right ATTACK_OWNERSHIP at 42764.795 ms;
   - zero intervening raw8 opportunity opens;
   - but P0-right reported `MarkerPresent=1 / FistMarkers=1`, so it was not native fallback.

2. P1-left C1=219 / opportunity 44:
   - marked opportunity OPEN at 137271.170 ms;
   - `C1_GENERATION_REPLACED` close at 137391.387 ms;
   - next relevant P0-right ATTACK_OWNERSHIP at 137724.533 ms;
   - zero intervening raw8 opportunity opens;
   - P0-right again reported `MarkerPresent=1 / FistMarkers=1`.

Thus the difficult interruption chronology is now proven reproducible. The only missing condition for focused item 6 is a truly unmarked P0-right runtime asset.

Additional lifecycle evidence:
- the large-log package surfaced two `CORE C1 FINALIZATION ANOMALY / REPAIR` events;
- both belong to Orc equipped weapon sources, not raw8:
  - `ReddockOrcWarrior01 / It_Axe_OrcSword_02 / raw52`;
  - `ReddockOrcScout02 / It_Axe_OrcSword_01 / raw52`;
- both had factual outstanding Item_Attack group7 state and were repaired to Item_Equipped group5;
- both report `REPAIRED_TO_ITEM_EQUIPPED`, actual group after repair 5 and physical collision changed;
- no repair-divergence evidence is present;
- these are successful generic lifecycle-backup repairs under interruption/churn, not a raw8 contradiction.

Focused acceptance disposition:
- item 6 remains OPEN because the intended fallback motion was still marked at runtime;
- this run is **INFORMATIVE / FIXTURE-STATE MISMATCH, NO SOURCE CONTRADICTION**;
- no source change is justified;
- next retry should first verify that the actual game-loaded P0-right motion resolves `MarkerPresent=0 / FistMarkers=0`, then repeat the same group-combat setup. The interruption timing itself already succeeded twice.

Provenance:
- raw blob `50a70ac6611dde6dfc2da3afa95c803132e43912`;
- derived package retained under `research/derived/2026-09-22_human_fist_marked_unmarked_test2_large_log/`.


### EV-364 — Final focused raw8 sentinel PASS / §14 acceptance COMPLETE

Source/runtime:
- frozen source `f1f5d2aad3edc3564a9a8b40541840b94f8fa903`;
- diagnostic DLL remains the frozen-source diagnostic twin;
- source log `2026-09-22_human_fist_marked_unmarked_test3.log`, blob `16cdaa4f5dad7af0a249cb1b3d784b7a57b0a449`, 798,665 bytes / 3,735 lines;
- User corrected the fixture so only P1 Normal was marked and P0 Normal was genuinely unmarked.

Fixture identity:
- marked: `Hero_Stand_None_Fist_P1_Attack_Hit_N_Fwd_00_%_00_P0_100_L.xmot`;
- unmarked/native: `Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot`.

Unmarked P0 runtime proof:
- 25 ATTACK_OWNERSHIP observations;
- all 25 `MarkerPresent=0`;
- all 25 `FistMarkers=0`;
- all 25 `Raw8Fist=<none> / Raw8UseType=-1 / SuppressNative=0`;
- zero `RAW8_FIST_OWNERSHIP` records on P0;
- zero `RAW8_OPPORTUNITY_OPEN` records on P0;
- zero `RAW8_OPPORTUNITY_CONTACT_CONSUMED` records on P0;
- 3 exact native Fist contacts through `Game.dll+0x0016E348`, targeting `ReddockOrcScoutLeader`, `ReddockOrcWarrior01`, and `ReddockOrcScout02`.

Decisive marked-replacement -> unmarked-fallback proof:
- 8 marked P1 opportunities closed by `Reason=C1_GENERATION_REPLACED`;
- all 8 replacement closes wrote latch `0->1`, with `LatchWriteAttempted=1 / LatchWriteConfirmed=1`;
- for all 8 replacement closures, the next relevant human Normal ATTACK_OWNERSHIP was the exact P0 unmarked motion;
- for all 8, there were **zero intervening raw8 opportunity opens** between replacement close and the P0 attack;
- the P0 attack remained fully native/unmarked and created no raw8 ownership/opportunity state.

Representative exact sequences:
- C1=53 / opportunity 5: P1 OPEN 63507.203 ms -> generation-replaced CLOSE 63696.051 ms -> P0 unmarked ATTACK_OWNERSHIP 65023.856 ms, zero intervening opens;
- C1=65 / opportunity 7: P1 OPEN 67014.047 -> generation-replaced CLOSE 67397.334 -> P0 unmarked 74403.785, zero intervening opens;
- C1=227 / opportunity 13: P1 OPEN 134511.556 -> generation-replaced CLOSE 134537.502 -> P0 unmarked 135096.836, zero intervening opens;
- C1=379 / opportunity 24: P1 OPEN 192586.165 -> generation-replaced CLOSE 192848.853 -> P0 unmarked 193247.298, zero intervening opens.

Diagnostics/invariants:
- zero C1 finalization anomaly/repair records;
- zero C1 invariant warnings;
- zero repair divergence;
- zero generation inconsistency;
- zero contradiction;
- zero explicit error/exception/failure;
- clean DLL unload.

Focused §14 final disposition:
1. Gargoyle close/delayed/no-contact -> PASS EV-359 + EV-360.
2. Human Normal/Power timing/contact -> PASS EV-359.
3. Later FIST same C1 reopening -> PASS EV-359.
4. Ordinary no-contact finalization -> PASS EV-359.
5. Reaction/generation replacement -> PASS EV-360.
6. Replacement -> later unmarked native fallback -> **PASS EV-364**.
7. Native unmarked human target-directed control -> PASS EV-361.
8. Sprint Action9 -> Action2 transport -> PASS EV-360.
9. raw55 + equipped coexistence -> PASS EV-357.
10. Diagnostic/behavior parity -> PASS EV-357 + EV-358.

Interpretation:
- **PASS — PERMANENT RAW8 FOCUSED ACCEPTANCE COMPLETE.**
- The frozen source satisfies all ten §14 acceptance requirements.
- No source contradiction was exposed.
- Phase 4 broad/comprehensive frozen-source regression may resume under `COLLISION_TEST_PLAN.md` §3.8.

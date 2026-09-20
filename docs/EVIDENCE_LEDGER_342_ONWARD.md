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

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


### EV-342 — Minecrawler marked raw8 regression PASS with contact qualification

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
- **PASS with native-contact qualification.**
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

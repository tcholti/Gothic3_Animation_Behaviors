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


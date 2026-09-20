# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-20

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Current gate: **Phase 4 non-weapon creature regression ACTIVE / PARTIAL PASS through EV-345.**

No active Work implementation contract.

Current diagnostic test product remains:

```text
Script_FrameCollisionTest.dll
SHA256 DAC9FFD8D4853947CEAD1F74569A6071E3C24AA716DC100064DBBC45086D7F3A
```

Latest Phase-4 batch:
- EV-342 Minecrawler factual Fist/raw8 Normal/Power/Quick = PASS with native-contact qualification;
- EV-343 Bloodfly factual Fist/raw8 Normal/Power/Sprint = PASS;
- EV-344 Boar factual Fist/raw8 Normal = PASS;
- EV-345 Bison factual Fist/raw8 Normal = PASS.

Important distinctions:
- Minecrawler has 12 accepted/owned raw8 FIST C1s and clean timing/finalization throughout; 8 native Fist damage contacts reached the player. One Power and three Normal executions produced no ONDAMAGE, so EV-342 does not claim 12/12 physical contact.
- Bloodfly 10/10, Boar 9/9 and Bison 12/12 marked raw8 C1s produced native Fist damage to the player and finalized cleanly.
- Bloodfly Sprint remains factual raw8/FIST; `EquippedSprintCollision` correctly delegates native with `Reason=FIST_MARKER_PRESENT`.
- Mixed player 1H-family, 1H+shield and 2H controls retained balanced equipped opening/cleanup with no cross-mechanism interference.
- Across all four logs there are no anomaly, warning, contradiction, rejected-marker, repair, divergence or nonzero-finalization records.

Phase 4 remains open because more animal/monster fixtures are planned.

Next responsibility:
- continue `docs/COLLISION_TEST_PLAN.md` Phase 4 with additional non-weapon creature/body-contact fixtures;
- preserve factual runtime source/UseType and do not infer raw8/raw55 from species or animation names;
- do not reopen source implementation unless a runtime contradiction appears.

`research/raw/` should contain only `Keep.txt`.

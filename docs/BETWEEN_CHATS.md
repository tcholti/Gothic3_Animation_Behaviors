# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-19

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Technical active branch: `docs/collision-source-evidence`  
Current gate: standalone collision regression — **Phase 4 non-weapon creatures**.

Corrected closed state:

```text
human marked attack matrix = CLOSED/PASS
Golem = consistent target fixture only, not the behavior under test
Sabretooth marked single-marker route = CLOSED/PASS
Sabretooth raw8 double-marker same-C1 control = CLOSED/PASS at EV-307
```

Latest closure:

```text
EV-309 Orc Staff-animation / factual Halberd raw51 + raw8 Fist = PASS
EV-310 Orc 2H-animation / factual Axe raw52                   = PASS
Phase 2 Orc attack matrix                                    = CLOSED/PASS
```

User visual observation: all tested Orc attack types damaged the player. CORE logs show no marker rejection, ownership/invariant anomaly, outstanding finalization, repair or divergence in the tested Orc routes.

Latest Phase-3 closure:

```text
EV-311 Goblin 1H/raw2     PASS; equipped Sprint/right/raw2 marker scope DISCOVERED/DEFERRED
EV-312 Demon 2H/raw3      PASS
EV-313 Ogre Axe/raw52     PASS
EV-314 Stalker Axe/raw52  PASS
Phase 3                   CLOSED/PASS
```

Goblin/Demon/Ogre were deliberately rerun on the current post-raw55 build to protect against cross-feature regression; their established supported routes remain healthy. Stalker adds a new current Axe/raw52 actor fixture. The Goblin Action9/SPRINT RIGHT-marker rejection is a known unsupported-scope discovery, not evidence that equipped Sprint markers are supported.

Immediate continuation: Phase 4 — test prepared non-weapon animals/monsters. Do not repeat Troll/BlackTroll or Sabretooth merely for duplication because their current-DLL raw55/raw8 paths are already covered.

Latest closed evidence is EV-314. `research/raw/` is clean except `Keep.txt`.

The knowledge-lifecycle restructure, formal post-restructure audit, and bounded M-1 through M-5 corrections are CLOSED/PASS. Ordinary reference-first retrieval and automated knowledge-state validation are now the baseline.

Use `COLLISION_REFERENCE.md` for settled facts. Use `EVIDENCE_INDEX.md` only when proof/provenance is needed.

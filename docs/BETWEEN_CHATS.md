# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-19

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Technical active branch: `docs/collision-source-evidence`  
Current gate: **generic equipped Sprint diagnostic causal probe**, with Goblin RIGHT/raw2 retained only as the first causal fixture. Phase 4 non-weapon regression is temporarily held.

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

Active frozen task:

`docs/work/active/COLLISION_EQUIPPED_SPRINT_GENERIC_CAUSAL_PROBE.md`

Question: can factual Action9/Sprint use the established generic equipped RIGHT/LEFT/BOTH/OFF marker mechanism safely when native early `OnAI_PowerAttack` timing is suppressed, with ordinary complete-motion required-source validation deciding which equipped sources must exist? Goblin RIGHT/raw2 is the first test fixture only.

Hard boundary: diagnostic-only temporary probe; no production promotion yet. Existing source commit `1ae0731cd501e6d72bbbf6642188a3047d134805` is the superseded narrow RIGHT/raw2 implementation and was not built/tested; do not build it before the generic replacement is independently reviewed.

After independent source review, runtime order is:

```text
Goblin equipped Sprint/right/raw2 causal fixture FIRST
-> if PASS: Sabretooth raw8 Sprint sentinel
-> Troll/BlackTroll raw55 Sprint-origin sentinel
-> one equipped true-Power sentinel
-> then decide permanent promotion
```

Phase 4 remains held until this scope question is resolved.

Latest closed evidence is EV-314. `research/raw/` is clean except `Keep.txt`.

The knowledge-lifecycle restructure, formal post-restructure audit, and bounded M-1 through M-5 corrections are CLOSED/PASS. Ordinary reference-first retrieval and automated knowledge-state validation are now the baseline.

Use `COLLISION_REFERENCE.md` for settled facts. Use `EVIDENCE_INDEX.md` only when proof/provenance is needed.

# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-20

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Phase 4 remains paused at raw8 FIST authoring-semantics research. Latest completed evidence: **EV-351**. No active Work task.

## Agreed ownership / terminology

```text
opportunity
= authored logical OPEN / CLOSED / rearmed state

collision/contact
= native physical/contact resolution

native hit/contact-resolution boundary
= factual Gothic boundary under research

damage
= literal Gothic API/log name or HP result only
```

The mod owns authored collision/contact opportunity and exact Hit/C1 lifetime. Gothic/behavior mods own block/parry/immunity/reactions/HP damage.

## EV-351

Reviewed diagnostic implementation:
`929bba9974788c873860f8e33f504c091f7aa524`

Diagnostic DLL SHA256:
`F6EB69B1AFAFCB4C8F99FBE4C5CFDE1DC411FA074F109E7F5515D068E76096DD`

Six Gargoyle factual raw8 Power frame-3 invocations:
- C1 14, 24, 33 -> exact `Game+0x16E348` contact-path entry;
- C1 4, 21, 36 -> no contact-path entry;
- visual close-vs-far result matched;
- exact raw8 `CORE RAW8_CONTACT_GATE` = 0;
- exact raw8 `CORE RAW8_CONTACT_TARGET` = 0;
- no anomalies or contradictions.

Conclusion:
- `gCTouchDamage_PS::CanBeActivatedNow` and `TriggerTarget` are not the contact-consumption boundary on this tested raw8 route;
- the ordinary TouchDamage virtual trigger path is bypassed here;
- this does **not** yet prove that inherited `EntitiesVisited` / `EntitiesVisitedCount` never change elsewhere.

Canonical log:
`research/archive/2026-09-20_observation_gargoyle_marker_frame_3_test_5.log`  
Git blob `ffb6d7ca49ee05b79a98320e5cd32ddfc594e88b`.

## Next smallest question

Before abandoning the physical-source bookkeeping analogy:

> Observe the exact raw8 Fist TouchDamage source's inherited `EntitiesVisited` / `EntitiesVisitedCount` at whole-`AICombatMoveInstr` entry and exit. Do close/contact cases add the player while far misses do not?

Observation must remain read-only.

If visited bookkeeping remains unchanged in both cases, stop pursuing the trigger-list model and move deeper into the static raw8 `Game+0x16E1A3 -> +0x16E348` branch region.

## Current stop gate

Run:

```text
python tools/knowledge/validate_knowledge_state.py
```

Require:

```text
Knowledge-state validation PASS
```

Do not freeze or launch the next Work task before PASS.

`research/raw/` should contain only `Keep.txt`.

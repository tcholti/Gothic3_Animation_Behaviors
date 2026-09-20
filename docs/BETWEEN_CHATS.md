# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-20

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Phase 4 remains paused at raw8 FIST authoring-semantics research. Latest completed evidence: **EV-352**.

Active bounded Work task:

`docs/work/active/COLLISION_RAW8_PERSISTENT_OPPORTUNITY_TOKEN_CAUSAL_PROBE.md`

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

The mod owns authored collision/contact opportunity and exact Hit/C1 lifetime. Gothic/behavior mods own target selection, block/parry/immunity/reactions/HP damage.

## EV-351–EV-352

EV-351:
- exact raw8 `CanBeActivatedNow` / `TriggerTarget` callbacks absent on six Gargoyle frame-3 invocations;
- three close cases still reached exact `Game+0x16E348`;
- ordinary TouchDamage virtual trigger route is not the raw8 contact boundary on that path.

EV-352:
- native human group-combat control with locked `ReddockOrcScoutLeader`;
- 25 player Fist C1 starts;
- eight exact raw8 `Game+0x16E348` entries;
- all eight targeted only the locked leader;
- zero exact Fist entries against deliberately interposed/adjacent non-target Orcs.

Together with EV-233, do not reproduce weapon/raw55 per-target visited bookkeeping for raw8.

## Frozen causal model

Use one pending token per exact marked actor/C1:

```text
marked C1 start
-> native latch CLOSED

accepted FIST
-> token OPEN
-> latch OPEN
-> marker-time timing permission available

native attempt misses
-> token remains OPEN
-> re-open latch
-> keep marker-time synthetic timing eligibility while still pre-threshold

exact raw8 Game+0x16E348 dispatch entered
-> token CONSUMED before native original
-> do not inspect HP/block/immunity outcome
-> no further rearm

later FIST
-> one token OPEN again, no stacking

same C1 Action/family/phase transport
-> token stays with the attack execution
-> specifically preserve proven Sprint-origin Action9 -> Action2

Hit/C1 execution genuinely ends or generation is replaced
-> unused token CLOSED
-> latch forced CLOSED
-> timing helper retired
-> no cross-C1 leak
```

This is not custom contact/damage. It repeatedly makes Gothic's already-proven one-shot raw8 mechanism eligible while the authored opportunity token remains pending.

The exact `Game+0x16E348` path is treated only as native raw8 contact-resolution dispatch entry under strict caller/source/actor/C1 identity. EV-349 proves it can occur with zero visible HP damage.

## Current stop gate

The frozen task was corrected after User review: token lifetime is C1/execution-scoped rather than Action-scoped. This correction changed lifecycle-sensitive project state.

Run:

```text
python tools/knowledge/validate_knowledge_state.py
```

Require:

```text
Knowledge-state validation PASS
```

Only after PASS send the **corrected** frozen task to Work.

`research/raw/` should contain only `Keep.txt`.

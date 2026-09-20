# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-20

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

## Current state

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Latest completed evidence: **EV-353**.

Permanent raw8 architecture:
`docs/COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md`

Active Work task:
`docs/work/active/COLLISION_RAW8_PERSISTENT_OPPORTUNITY_PRODUCTION_IMPLEMENTATION.md`

Resolved raw8 semantics review and causal probe are archived.

## Frozen production responsibility

`Raw8FistCollision` absorbs the proven pending-opportunity mechanism; the temporary `Raw8FistPersistentOpportunityProbe` is deleted.

Required semantic:

```text
marked C1 -> raw8 native opportunity closed
FIST -> one pending opportunity
miss -> restore native one-shot eligibility, keep pending
exact Game+0x16E348 raw8 contact dispatch -> consume
later FIST same C1 -> reopen one, no stacking
same-C1 Action/family transport -> preserve
exact C1 finalization/replacement -> close unused opportunity
unmarked raw8 -> native
```

The behavior-only twin must include the exact pass-through `gCEntity::OnDamage` hook because contact consumption is production behavior. Damage outcome remains entirely Gothic-owned.

Do not merge raw8 with equipped/raw55 or add FIST_OFF, target lists, ClearTriggeredList, custom damage, polling, species rules or Action/state cleanup taxonomy.

Important focused regression after implementation: `marked pending -> replacement/interruption -> later unmarked raw8` must prove native fallback remains intact.

## Stop gate

Run:

```text
python tools/knowledge/validate_knowledge_state.py
```

Require `Knowledge-state validation PASS` before sending the production task to Work.

`research/raw/` should contain only `Keep.txt`.
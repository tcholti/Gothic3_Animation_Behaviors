# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-07 — true Finishing/Action15 exclusion check ACTIVE

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`
Stable main: `e899f37092706a9846312b93d6b52b34e715b53d`
Active branch: `development`

## Closed bad-block state

EV-449–EV-450:
- protect player QuickAttackR(4), QuickAttackL(5), WhirlAttack(10), factual Hit, raw>2500;
- branch-local return 2500 is causally sufficient.

EV-451:
- repeated Pierce/Action11 and Hack/Action14 attempts under production G3AB + New Balance;
- no visual bad skip;
- timeout observer saw zero factual Action11/14 Hit records;
- keep Action11/14 excluded from v1.

## Active gate

`docs/work/active/BAD_BLOCK_FINISHING_EXCLUSION_VALIDATION.md`

True Finishing/Action15 only.

Probe:
`Script_G3AB_BadBlockExclusionProbe.dll`

At `Script_Game +0x633BF`:
```text
if player
AND factual Action == FinishingAttack(15)
AND phase == Hit
-> first observation logs HIT-SEEN with raw
-> same Hit crossing raw > 2500 logs OVERDUE
-> always return native raw unchanged
```

Runtime fixture:
- production G3AB ON;
- New Balance ON;
- observe-only probe ON;
- old protection/control research DLLs OFF.

User test:
use god mode if useful, knock down NPCs, hold RMB near timeout, then perform true executions by holding LMB over the downed target. Repeat at aggressive timing and watch for visible bad skip.

Frozen raw:
`research/raw/2026-10-07_bad_block_finishing_exclusion_probe.log`

If clean:
-> lean diagnostics-free standalone protector
-> visual acceptance
-> production G3AB integration
-> final visual release-candidate smoke.

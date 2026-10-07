# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-07 — EV-452 Action15 exclusion closed

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`
Stable main: `e899f37092706a9846312b93d6b52b34e715b53d`
Active branch: `development`

## Closed bad-block first-release scope

EV-449–EV-450:
- proven protected set = player QuickAttackR(4), QuickAttackL(5), WhirlAttack(10), factual Hit, raw>2500;
- stateless branch-local return 2500 is causally sufficient.

EV-451:
- repeated Pierce/Action11 and Hack/Action14 attempts;
- no visible bad skip;
- zero factual Action11/14 Hit observations at the timeout seam;
- keep Action11/14 excluded.

EV-452:
- about five true 2H finishing executions plus more 1H finishing executions;
- no visible bad skip;
- 1H finishing attacks were long-Hit / no-Raise yet still did not fail;
- zero factual Action15 Hit observations at the timeout seam;
- keep Action15 excluded;
- do not claim a proven native Finishing guard from seam absence alone.

## Next gate

Build the leanest diagnostics-free standalone protector from the EV-450 mechanism before production integration.

Exact rule:
```text
call native DurationPressedMSecs getter exactly once

if raw > 2500
AND actor == player
AND factual Action in {QuickAttackR(4), QuickAttackL(5), WhirlAttack(10)}
AND phase == Hit
-> return 2500

otherwise
-> return raw
```

Remove:
- all loggers;
- A/B control mode;
- diagnostic episode state;
- Pierce/Hack/Finishing exclusion observer code.

Do not add:
- actor/timer maps;
- gameplay tokens;
- NPC handling;
- global getter mutation;
- FullStop/SetState suppression;
- collision-guardian coupling.

After lean standalone visual acceptance:
-> integrate same minimum into production G3AB
-> final visual release-candidate smoke.

# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-07 — bad-block player A/B mechanism CLOSED/PASS

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`

Stable release branch:
`main @ e899f37092706a9846312b93d6b52b34e715b53d`

Active branch:
`development`

## Stable baseline

Collision + Speed + Raise + Movement remain accepted through the pre-final-fix stable baseline on main (EV-447).

EV-448 exact remaining-time pause research remains parked. ADR-0012 requires only that block-timeout teardown not destroy the demonstrated protected live attack; native held-input time may continue advancing.

## Closed player mechanism experiment

Archived task:
`docs/archive/investigations/BAD_BLOCK_SKIP_ATTACK_PROTECTION_OPTIONS.md`

Exact proven seam:
`Script_Game +0x633BF`

Runtime-proven rule:

```text
native/current DurationPressedMSecs getter called exactly once

if raw > 2500
AND receiver-owning actor == player
AND factual Routine Action in:
    QuickAttackR = 4
    QuickAttackL = 5
    WhirlAttack  = 10
AND factual phase == Hit
-> return 2500 for this call only

otherwise
-> return raw
```

This is stateless branch-local deferral, not timer mutation and not pause/resume.

### EV-449 — A / CONTROL

Same hook/classifier/logger source, but qualifying calls returned native raw.

Observed:
- 17 qualifying factual-Hit episodes;
- Action10=3, Action5=11, Action4=3;
- every episode had `effective == raw`;
- User reproduced bad skip repeatedly;
- final stale armed weapon damaged NPCs merely by running into them.

Archived artifact:
`research/archive/2026-10-07_bad_block_player_whirl_control.log`

### EV-450 — B / PROTECTION

Same source and fixture; only qualifying return policy changed to `2500`.

Observed:
- 20 qualifying factual-Hit episodes;
- Action10=10, Action5=8, Action4=2;
- every episode had native `raw > 2500` and `effective=2500`;
- User could not reproduce bad skip across the vulnerable weapon routes;
- final run-into-NPC stale-collision test caused no damage.

Archived artifact:
`research/archive/2026-10-07_bad_block_player_whirl_protection.log`

Conclusion:
**MECHANISM CLOSED / RUNTIME CAUSAL PASS.**

The A/B evidence supports the minimum stateless player Hit deferral and does not justify a stateful gameplay token, timer map, global timing mutation, or collision-guardian coupling.

## Next decision gate

Do not reopen mechanism research before choosing product placement.

User + Normal Chat must choose one:
1. integrate the proven minimum into production `Script_G3AnimationBehaviors.dll`;
2. clean the proven minimum into a separate optional production DLL;
3. decline shipment.

After that decision, freeze a new bounded production implementation task. Do not modify production source before that task exists.

NPC overlap remains a separate unresolved question. The designed `Script_Game +0x46F39` observer is not authorized by EV-450 and is not a blocker for the proven player fix.

# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-07 — lean standalone protector DEPLOYED / runtime acceptance pending

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`
Stable main: `e899f37092706a9846312b93d6b52b34e715b53d`
Active branch: `development`

## Closed bad-block first-release scope

EV-449–EV-450:
- proven protected set = player QuickAttackR(4), QuickAttackL(5), WhirlAttack(10), factual Hit, raw>2500;
- stateless branch-local return 2500 is causally sufficient.

EV-451:
- keep Pierce/Action11 and Hack/Action14 excluded.

EV-452:
- keep true Finishing/Action15 excluded;
- do not infer a proven native Finishing guard from seam absence alone.

## Active gate

`docs/work/active/BAD_BLOCK_LEAN_STANDALONE_ACCEPTANCE.md`

Candidate:
`Script_G3AB_BadBlockProtector.dll`

Exact behavior:
```text
call native/current DurationPressedMSecs getter exactly once

if raw > 2500
AND actor == player
AND factual Action in {QuickAttackR(4), QuickAttackL(5), WhirlAttack(10)}
AND phase == Hit
-> return 2500

otherwise
-> return raw
```

The standalone candidate must contain no:
- logger;
- A/B mode;
- diagnostic episode state;
- exclusion observer;
- actor/timer map;
- gameplay token;
- NPC handling;
- global getter mutation;
- FullStop/SetState suppression;
- collision-guardian coupling.

Implementation checkpoint:
`development @ bc7d341abd71dc064e6be6faf88d51dff6d62eb4`

Built/live lean protector:
`SHA256 6A04B4AB4529EF2C7FD6BEB6450572BD504AF188FB3BD45FBCFD116E5AB5A03A`

Runtime acceptance fixture is already deployed and left in place:
- production G3AB ON — `4F05583E74F0B2F49FBC3682DB244EDE86C277BA810DBFE0C985859D69A32B68`;
- New Balance ON — `0C06C35F294F2FDF3011AC82FF506CA422947B6908CE2530AA1B057A243A6F88`;
- lean protector ON — `6A04B4AB4529EF2C7FD6BEB6450572BD504AF188FB3BD45FBCFD116E5AB5A03A`;
- all old bad-block research/control/exclusion products OFF.

Runtime acceptance has not started yet.

Exact next step:
1. launch Gothic 3 to main menu and exit normally; no log is expected;
2. if startup is clean, repeatedly try to reproduce known Quick/Whirl bad skip;
3. if clean, integrate the same minimum into production G3AB and run final release-candidate smoke.

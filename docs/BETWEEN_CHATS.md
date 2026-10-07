# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-07 — lean standalone protector acceptance ACTIVE

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

Runtime acceptance fixture:
- production G3AB ON;
- New Balance ON;
- lean protector ON;
- all old bad-block research/control/exclusion products OFF.

Acceptance is visual only:
repeatedly try to reproduce known Quick/Whirl bad skip. If clean, integrate the same minimum into production G3AB and run final release-candidate smoke.

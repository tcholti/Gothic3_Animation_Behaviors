# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-07 — Pierce / Hack exclusion validation ACTIVE

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`

Stable release branch:
`main @ e899f37092706a9846312b93d6b52b34e715b53d`

Active branch:
`development`

## Proven baseline

EV-449–EV-450 closed the player bad-block A/B mechanism with runtime causal PASS.

Proven protected set:
```text
raw > 2500
+ player
+ factual Action in {QuickAttackR(4), QuickAttackL(5), WhirlAttack(10)}
+ factual Hit
-> branch-local return 2500
```

No gameplay token, timer map, global duration mutation, or collision-guardian coupling is justified.

## Active gate

`docs/work/active/BAD_BLOCK_PIERCE_HACK_EXCLUSION_VALIDATION.md`

Purpose:
challenge the current exclusion of Pierce/Action11 and Hack/Action14 before lean-protector cleanup and production integration.

Probe:
`Script_G3AB_BadBlockExclusionProbe.dll`

Exact seam:
`Script_Game +0x633BF`

Probe rule:
```text
native getter called exactly once

if actor == player
AND factual Action in {PierceAttack(11), HackAttack(14)}
AND phase == Hit
-> first observation logs HIT-SEEN with current raw
-> if same Hit later reaches raw > 2500, log OVERDUE
-> always return native raw unchanged

otherwise
-> return native raw unchanged
```

This probe never protects Action11/14.

Frozen runtime stack:
- production `Script_G3AnimationBehaviors.dll` ON;
- `Script_NewBalance.dll` ON;
- exclusion probe ON;
- old bad-block research/control DLLs OFF;
- existing third-party stack otherwise unchanged.

Frozen raw filename:
`research/raw/2026-10-07_bad_block_pierce_hack_exclusion_probe.log`

Interpretation:
- qualifying episode + visible bad skip = current exclusion contradicted;
- qualifying episode + no bad skip = evidence supporting exclusion;
- no qualifying episode after deliberate attempts = negative evidence only, not proof of impossibility.

After this gate, if no contradiction:
1. perform one separate small true Finishing/Action15 execution check with knocked-down NPCs;
2. build the leanest diagnostics-free standalone protector;
3. User performs visual bad-skip acceptance;
4. integrate the same minimum into production G3AB;
5. run one final visual release-candidate smoke.

NPC overlap remains separate and is not part of this gate.

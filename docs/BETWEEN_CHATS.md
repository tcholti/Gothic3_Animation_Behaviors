# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — EV-428 Raise coverage clarification

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`  
`main` remains frozen.

## Accepted Raise mechanism

Collision, Speed v2, Raise phase-speed/Hack compatibility and the Normal AddRaise direction correction remain CLOSED/PASS on their tested routes.

Accepted direction source:

`1da12cead5acfb54c5520a34d07bccc4c32fd64f`

Normal direction carry:
```text
pending Normal synthetic Raise
-> Gothic selects native Fwd/Left/Right
-> capture exact direction bCString + current gEDirection at Game+0x16B056
-> stored Action1 Hit
-> restore same gEDirection + reuse same direction bCString
-> Gothic GetAniName resolves Hit normally
```

EV-426 source review = PASS / blocker 0 / major 0 / minor 0.

## EV-428 scope clarification

"All works" for the latest local run means **all behavior actually exercised in that run worked**. It does not certify every possible Gothic 3 animation set.

Latest exercised coverage:
```text
dual 1H_1H:
  Normal Fwd rule-derived Raise P0/P1
  Normal Left/Right native directional Raises
  ordinary P0/P1 QuickAttackR/L rule-derived Raises
  native timing
  BaseSpeed=0.1 timing inheritance

2H controls:
  Normal
  Quick
  Whirl

ordinary combat:
  Golem encounter using 2H and dual 1H_1H
```

Exact dual authoring examples and the tested derivation recipe are durable in `ANIMATION_RULES.md §5.1`.

Do not interpret EV-427/EV-428 as universal Raise coverage. Many Normal/Quick families need matching Raise assets authored before they can be exercised.

## Active responsibility

`docs/work/active/RAISE_PRE_RELEASE_VALIDATION.md`

Remaining representative pre-release Raise fixtures:
```text
1. human Fist Normal
2. Sabretooth
3. Troll
```

These three are the remaining Raise tests the User wants before considering the implementation sufficiently tested for the initial Animation Behaviors release.

Exhaustively authoring/testing Raise for every Gothic 3 attack family is **not** a release gate. Broader coverage will continue later while the User redesigns the Gothic 3 Animations Redone combat animation mods and through focused post-release contradictory reports.

Animation corpus/reference:
`https://www.nexusmods.com/gothic3/mods/77`

## Protected state

```text
EV-423/EV-424 direction defect remains closed
Speed core remains closed
phase-speed composition remains closed
Hack compatibility remains closed
Collision remains closed/protected
no new production change unless one of the remaining fixtures produces contradictory evidence
```

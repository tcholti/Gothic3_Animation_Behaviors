# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — attack forward displacement research opened

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `development`

## Stable baseline

`main` contains the deliberately promoted Collision + Speed + Raise checkpoint through EV-433.

```text
Collision = CLOSED/PASS
Speed v2 = CLOSED/PASS
Raise = CLOSED/PASS / well tested
New Balance / AttackCollision compatibility = protected
```

## Active responsibility

`docs/work/active/ATTACK_FORWARD_DISPLACEMENT_RESEARCH.md`

Research/design only:

**How far may an attack move the acting character forward?**

Established project starting surfaces:
```text
Game+0x16B8A3  CombatMove reach/vector call
Game+0x16B8A9  CombatMove movement call
```

Preliminary current-upstream New Balance lead:
```text
CombatMoveScale at Game+0x16B8A9
GetCombatMoveLength(current action)
+ animation max time / AniSpeedScale
+ normalized m_DirectionVec
+ ATTACK_REACH_MULTIPLIER
```

This upstream observation must be reverified against the project-pinned Jackydima reference before becoming canonical evidence.

First priority:
1. prove native ownership of `m_DirectionVec`/CombatMove displacement;
2. prove New Balance's exact intervention and action scope;
3. separate total travel distance from velocity/timing;
4. determine a compatibility composition model;
5. only then discuss INI/profile/production architecture.

Do not implement yet.

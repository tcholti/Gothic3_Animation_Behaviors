# Attack Forward Displacement — Research / Architecture

**Status:** ACTIVE  
**Branch:** `development`  
**Stable baseline:** `main` contains the accepted Collision + Speed + Raise checkpoint through EV-433.

## Purpose

Research how Gothic 3 decides **how far an attack moves the acting character forward**, and determine the smallest compatible architecture for making that distance configurable.

This is research/design only. Do not implement production behavior until native ownership, New Balance intervention, timing interaction and compatibility composition are causally understood.

## Protected accepted systems

```text
Collision = CLOSED/PASS
Speed = CLOSED/PASS
Raise = CLOSED/PASS
New Balance compatibility = protected
AttackCollision compatibility = protected
```

Do not redesign or weaken those systems to obtain displacement control.

## Established project seed

`SOURCE_HOOK_GUIDE.md §3B` already preserves two factual starting surfaces:

```text
Game+0x16B8A3  CombatMove reach/vector call
Game+0x16B8A9  CombatMove movement call
```

These are starting surfaces only, not ownership proof.

Research must separate:

```text
animation/root translation contribution
CombatMove-requested displacement
motion/pose descriptor values
action-specific Script_Game policy
New Balance intervention
speed / animation-duration interaction
```

Do not call the feature root-motion control unless root motion is actually proven to own the observed attack displacement.

## New Balance compatibility lead — verify against project pin

A preliminary lookup of current upstream `Jackydima/gothic3sdk` shows a `CombatMoveScale` hook installed at `Game+0x16B8A9`.

Its current upstream shape is approximately:

```text
GetCombatMoveLength(Self, current instruction action)
-> obtain current animation max time
-> divide max time by request AniSpeedScale to obtain animation duration
-> normalize SPU m_DirectionVec
-> scale direction vector by:
   CombatMoveLength / animationDuration * ATTACK_REACH_MULTIPLIER
```

Important:
- treat this as a research lead, not yet canonical evidence;
- reverify the exact code/hook against the repository-pinned Jackydima reference before drawing conclusions;
- determine whether this applies generically to all actions with a valid CombatMove length or whether practical behavior is limited by Gothic's `GetCombatMoveLength` policy;
- determine whether New Balance is preserving a Gothic distance while changing velocity/timing, changing total travel distance through `ATTACK_REACH_MULTIPLIER`, or both.

## First research questions

1. What native Gothic code produces / consumes `m_DirectionVec` for melee CombatMove Hit movement?
2. What exactly happens at `Game+0x16B8A3` and `Game+0x16B8A9` in the tested executable?
3. What does native `GetCombatMoveLength` return for:
   - Normal;
   - QuickAttackR / QuickAttackL;
   - Power;
   - full Whirl;
   - SimpleWhirl;
   - Pierce;
   - Hack;
   - Sprint-origin shared routes;
   - representative nonhuman attacks?
4. Is the numeric movement/reach field serialized in animation names related to this distance, merely correlated, or independent?
5. How does `AniSpeedScale` affect total distance vs movement velocity?
6. Does New Balance's hook execute before/after any G3AB Speed/Raise/Collision intervention in a way that creates double composition risk?
7. Is a configurable feature best expressed as:
   - absolute desired total attack travel distance;
   - multiplier over compatible/native total distance;
   - per-profile/per-attack authored value;
   - another factual quantity?
8. Can compatible New Balance behavior be preserved in a composition model rather than replaced?
9. Which actions should be in initial public scope, based on actual native semantics rather than symmetry?

## Evidence order

Use:

```text
current project source/reference
-> pinned official SDK
-> pinned Jackydima/New Balance reference
-> tested Gothic binary reference/static inspection
-> smallest controlled runtime probe only if static ownership remains unresolved
```

Do not create a probe merely because one could provide more data. First exhaust the existing source/binary surfaces.

## Non-goals

- no production implementation;
- no INI key creation yet;
- no new hook yet;
- no Collision/Speed/Raise redesign;
- no broad movement/traversal system;
- no climbing/vaulting implementation;
- no assumption that every attack should move or should share one distance rule.

## Closure target

Research closes only when we can state:
- native displacement owner/mechanism;
- New Balance ownership/intervention and compatibility consequence;
- exact interaction with animation speed;
- safe composition quantity if one exists;
- supported initial attack scope;
- smallest production seam or a reason not to implement.

Then freeze a separate production task if implementation is justified.

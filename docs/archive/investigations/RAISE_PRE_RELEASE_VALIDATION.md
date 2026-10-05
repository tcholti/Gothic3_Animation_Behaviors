# Raise — Pre-Release Representative Validation

**Status:** CLOSED/PASS — EV-429 representative Raise type coverage complete  
**Branch:** `development`  
**Production direction source:** `1da12cead5acfb54c5520a34d07bccc4c32fd64f`  
**Current evidence baseline:** EV-420–EV-428

## Purpose

Finish the **representative pre-release Raise validation** the User wants before considering the Raise feature sufficiently tested for the initial Gothic 3 Animation Behaviors release.

This is not an exhaustive every-animation-in-the-game certification task.

## Already accepted / exercised

```text
2H Normal AddRaise
2H Quick AddRaise
2H Whirl AddRaise
dual 1H_1H Normal Fwd with rule-derived Raise assets
dual 1H_1H Normal Left/Right with native directional Raise assets
dual 1H_1H ordinary P0/P1 QuickAttackR/L with rule-derived Raise assets
native-speed behavior
configured BaseSpeed=0.1 behavior on the newly authored dual Raises
ordinary Golem combat using 2H and dual 1H_1H
```

EV-428 owns the exact scope clarification. Do not rewrite this into a claim that all Gothic 3 animation families are tested.

## Remaining pre-release fixtures

Run only these three representative Raise fixtures unless one produces contradictory evidence:

```text
1. human Fist Normal
2. Sabretooth
3. Troll
```

### Exact asset plan

Human Fist Normal — **native Raise assets already exist**:

```text
Hit:
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R
Raise:
Hero_Stand_None_Fist_P0_Attack_Raise_N_Fwd_00_%_00_P0_0_R

Hit:
Hero_Stand_None_Fist_P1_Attack_Hit_N_Fwd_00_%_00_P0_100_L
Raise:
Hero_Stand_None_Fist_P1_Attack_Raise_N_Fwd_00_%_00_P1_0_L
```

Troll — **no native Normal/Quick Raise assets found; create these candidates**:

```text
Troll_Stand_Fist_Fist_P0_Attack_Raise_N_Fwd_00_%_00_P0_0
Troll_Stand_Fist_Fist_P0_QuickAttackR_Raise_N_Fwd_00_%_00_P0_0
Troll_Stand_Fist_Fist_P0_QuickAttackL_Raise_N_Fwd_00_%_00_P0_0
```

The Troll candidates preserve the factual `Fist_Fist` route and its lack of a final R/L token. The family has a native pose-preserving zero-reach Power Raise, which supports this shape, but the Normal/Quick candidates remain unproven until runtime.

Sabretooth — **no native Normal/Quick Raise assets found; create these candidates**:

```text
Sabertooth_Stand_None_Fist_P0_Attack_Raise_N_Fwd_00_%_00_P0_0
Sabertooth_Stand_None_Fist_P0_QuickAttackR_Raise_N_Fwd_00_%_00_P0_0_R
Sabertooth_Stand_None_Fist_P0_QuickAttackL_Raise_N_Fwd_00_%_00_P0_0_L
```

The Sabretooth family has a native pose-preserving zero-reach Power Raise. Snapper provides a close native `None_Fist/P0` Normal+Quick analogue with the same Raise transformation and preserved Quick R/L suffixes. The Sabretooth candidates nevertheless remain unproven until runtime.

Do **not** add any Troll/Sabretooth candidate to `user_created_tested_animation_names.txt` until Gothic actually selects and plays it correctly.

For each fixture:
1. inspect the exact factual Hit route(s) and existing native Raise examples;
2. author only the Raise asset(s) needed to exercise the intended route;
3. preserve Gothic filename semantics according to `ANIMATION_RULES.md`;
4. enable the appropriate existing AddRaise setting/profile;
5. verify Raise selection, continuation into Hit, and timing behavior;
6. include a simple combat/control pass sufficient to reveal obvious state or collision interaction;
7. if it passes, record the tested scope precisely and add every newly authored + runtime-proven exact animation name to `data/animation_names/user_created_tested_animation_names.txt`;
8. if it contradicts current architecture, stop and research the smallest causal difference before changing production code.

## Authoring rule reference

`ANIMATION_RULES.md §5.1` owns the tested dual P0/P1 Raise derivation examples and the general filename constraints.

Do not assume the exact dual destination-pose/reach transformation applies universally. Prefer a matched native Raise example for the new family when one exists.

## Deferred broader coverage

Broader Raise asset coverage is intentionally staged rather than required before the initial Animation Behaviors release.

The User plans to redesign the existing Gothic 3 Animations Redone combat animation mods after the behavior mod release. As Normal/Quick assets are redesigned across weapon families, matching Raise assets can be authored and the behavior can be exercised naturally on those families. Contradictory post-release user reports should likewise become focused fixtures.

External animation corpus/reference supplied by the User:

`https://www.nexusmods.com/gothic3/mods/77`

That all-in-one page links the individual Gothic 3 Animations Redone mods and is the practical long-term animation-authoring surface; it is not a required dependency of this code repository.

## Closure

Close/archive this task when:
- human Fist Normal passes;
- Sabretooth passes;
- Troll passes;
- any discovered contradiction is either resolved or explicitly converted into a separate bounded task;
- the tested-scope conclusion is promoted to durable reference/evidence.

Exhaustive Raise testing for every existing/optional animation asset is **not** required for closure.


## Closure — EV-429

Human Fist Normal, Sabretooth and Troll passed the requested representative runtime validation. The same run also added a Staff control. All tested routes worked in/out of combat as applicable and followed configured speed at `0.1`.

The six newly authored Troll/Sabretooth Raise names were promoted to `data/animation_names/user_created_tested_animation_names.txt`.

The pre-release conclusion is **representative structural/type coverage complete for the public Normal / Quick / full Whirl AddRaise surface**, not exhaustive per-animation coverage.

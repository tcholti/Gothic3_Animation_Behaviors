# Gothic 3 Animation Rules

**Status:** Canonical engine-facing animation reference  
**Date:** 2026-08-22

## 1. Purpose

This document records Gothic 3 animation-state and filename rules relevant to scripting, animation authoring, and `Script_G3AnimationBehaviors`.

It separates verified rules from interpretations that are still hypotheses.

The preferred runtime architecture should use native enums/state directly where available. Filename fields are treated as a serialized representation/contract, not the only source of truth.

## 2. Canonical Filename Example

Example:

`Demon_Stand_None_2H_P1_Attack_Hit_N_Fwd_00_%_00_P0_150_L`

Current field interpretation:

1. animation actor/family: `Demon`
2. `gEAniState`: `Stand`
3. left animation UseType: `None`
4. right animation UseType: `2H`
5. current/source `gEPose`: `P1`
6. `gEAction`: `Attack`
7. `gEPhase`: `Hit`
8. animation type: `N`
9. `gEDirection`: `Fwd`
10. separator/unknown metadata group: `00_%_00`
11. next/destination pose: `P0`
12. CombatMove distance/length value: `150`
13. final side/attack-direction token: `L` — exact semantics not fully established

## 3. Animation Actor / Family

The first token identifies the animation actor/family/resource family.

Examples include `Hero`, `Demon`, `Goblin`, and other creature families.

`Hero` does not mean player-only. Compatible human NPCs also use Hero-family animations.

## 4. `gEAniState`

```cpp
enum gEAniState
{
    gEAniState_Dummy0 = 0,
    gEAniState_Dummy1 = 1,
    gEAniState_Stand = 2,
    gEAniState_Sneak = 3,
    gEAniState_Parade = 4,
    gEAniState_Kneel = 5,
    gEAniState_SitGround = 6,
    gEAniState_SitStool = 7,
    gEAniState_SitBench = 8,
    gEAniState_SitThrone = 9,
    gEAniState_SleepBed = 10,
    gEAniState_SleepGround = 11,
    gEAniState_TiltOrcBoulder = 12,
    gEAniState_HoldOrcBoulder = 13,
    gEAniState_LiftOrcBoulder = 14,
    gEAniState_SitKnockDown = 15,
    gEAniState_LieKnockDown = 16,
    gEAniState_LieKnockOut = 17,
    gEAniState_LieStraightDead = 18,
    gEAniState_LieDead = 19,
    gEAniState_LiePiercedKO = 20,
    gEAniState_LiePiercedDead = 21,
    gEAniState_TalkStand = 22,
    gEAniState_TalkSitGround = 23,
    gEAniState_TalkSitStool = 24,
    gEAniState_TalkSitBench = 25,
    gEAniState_TalkSitThrone = 26,
    gEAniState_Wade = 27,
    gEAniState_Swim = 28,
    gEAniState_Dive = 29,
    gEAniState_Count = 30
};
```

The current state influences which animation family/state combination is eligible.

## 5. Left/Right Animation UseTypes

Filename order is:

`LeftAnimationUseType_RightAnimationUseType`

Example:

`None_2H`

means no left-hand animation UseType and a 2H animation UseType in the right-hand position.

## 6. Raw `gEUseType` -> Animation Token Mapping

Raw engine item UseType and animation filename UseType are not always 1:1.

| Raw `gEUseType` | Animation token |
|---|---|
| None | None |
| Action | Action |
| 1H | 1H |
| 2H | 2H |
| Arrow | Arrow |
| Bow | Bow |
| CrossBow | CrossBow |
| Bolt | Bolt |
| Fist | Fist |
| Shield | Shield |
| Armor | Armor |
| Helmet | Helmet |
| Staff | Staff |
| Amulet | Amulet |
| Ring | Ring |
| Cast | Cast |
| Potion | Potion |
| Plant | Bread |
| Meat | Meat |
| Fruit | Fruit |
| Bread | Bread |
| Bottle | Potion |
| Cup | Cup |
| Bowl | Bowl |
| Torch | Torch |
| Alarmhorn | Alarmhorn |
| Broom | Staff |
| Brush | Block |
| Lute | Lute |
| Rake | Staff |
| TrophyTeeth | TrophyTeeth |
| Valuable | Valuable |
| Smoke | Smoke |
| OrcPipe | OrcPipe |
| Scoop | Tool |
| Stick | Tool |
| Shovel | Staff |
| Hammer | Tool |
| Fan | Staff |
| Pan | Tool |
| Saw | Tool |
| TrophySkin | TrophySkin |
| Map | Letter |
| Book | Letter |
| Letter | Letter |
| Key | Key |
| Lockpick | Key |
| CarryFront | CarryFront |
| CarryShoulder | CarryShoulder |
| Pickaxe | 2H |
| TrophyFur | TrophyFur |
| Halberd | Staff |
| Axe | 2H |
| ITEM_E | ITEM_E |
| Modify | Modify |
| PhysicalFist | Fist |
| ITEM_H | ITEM_H |
| Anvil | Anvil |
| Forge | Forge |
| GrindStone | GrindStone |
| Cauldron | Cauldron |
| Barbecue | Barbecue |
| Alchemy | Alchemy |
| Bookshelf | Bookshelf |
| Bookstand | Bookstand |
| TakeStone | TakeStone |
| DropStone | DropStone |
| PickOre | PickOre |
| PickGround | PickGround |
| DigGround | DigGround |
| Field | Field |
| Repair | Repair |
| SawLog | SawLog |
| Lumberjack | Lumberjack |
| Bed | Bed |
| SleepGround | SleepGround |
| CleanFloor | CleanFloor |
| Dance | Dance |
| FanBoss | FanBoss |
| Boss | Boss |
| Throne | Throne |
| Pace | Pace |
| Bard | Bard |
| Stool | Stool |
| Bench | Bench |
| Waterpipe | Waterpipe |
| WaterBarrel | WaterBarrel |
| PirateTreasure | Stove |
| Campfire | Campfire |
| SitCampfire | SitCampfire |
| SitGround | SitGround |
| Smalltalk | Smalltalk |
| Preach | Preach |
| Spectator | Spectator |
| Stand | Stand |
| Guard | Guard |
| Trader | Trader |
| Listener | Listener |
| OrcDance | OrcDance |
| Stoneplate | Stoneplate |
| OrcDrum | OrcDrum |
| Door | Door |
| OrcBoulder | OrcBoulder |
| EatGround | EatGround |
| DrinkWater | DrinkWater |
| Pee | Pee |
| Chest | Chest |
| Shrine | Shrine |
| AttackPoint | AttackPoint |
| Roam | Roam |
| BODY_A | BODY_A |
| Beard | Beard |
| Hair | Hair |
| Head | Head |
| Body | Body |
| Flee | Flee |
| Talk | Talk |

Implementation consequence:

configuration/profile matching should use **animation UseType categories**, not blindly serialize raw item UseType names.

## 7. Current / Source Pose

The pose token before the action is the entity's current/source pose.

Examples:

- `P0`
- `P1`
- `P2`
- `P3`
- composite labels such as `P10`, `P21`, etc.

Do not simplify composite poses away in code.

## 8. `gEAction`

Combat-relevant values:

```cpp
enum gEAction
{
    gEAction_None = 0,
    gEAction_Attack = 1,
    gEAction_PowerAttack = 2,
    gEAction_QuickAttack = 3,
    gEAction_QuickAttackR = 4,
    gEAction_QuickAttackL = 5,
    gEAction_SimpleWhirl = 6,
    gEAction_TurnLeft = 7,
    gEAction_TurnRight = 8,
    gEAction_SprintAttack = 9,
    gEAction_WhirlAttack = 10,
    gEAction_PierceAttack = 11,
    gEAction_JumpAttack = 12,
    gEAction_RamAttack = 13,
    gEAction_HackAttack = 14,
    gEAction_FinishingAttack = 15,
    gEAction_Parade = 16,
    gEAction_ParadeR = 17,
    gEAction_ParadeL = 18,
    gEAction_ExitParade = 19,
    gEAction_QuickParadeStumble = 20,
    gEAction_ParadeStumble = 21,
    gEAction_ParadeStumbleR = 22,
    gEAction_ParadeStumbleL = 23,
    gEAction_HeavyParadeStumble = 24,
    gEAction_QuickStumble = 25,
    gEAction_Stumble = 26,
    gEAction_StumbleR = 27,
    gEAction_StumbleL = 28,
    gEAction_SitKnockDown = 29,
    gEAction_GetUpAttack = 30,
    gEAction_GetUpParade = 31,
    gEAction_LieKnockDown = 32,
    gEAction_LieKnockOut = 33,
    gEAction_PierceStumble = 34,
    gEAction_Die = 35,
    gEAction_LieDead = 36,
    gEAction_LiePiercedKO = 37,
    gEAction_LiePiercedDead = 38,
    gEAction_AbortAttack = 39,
    gEAction_Aim = 40,
    gEAction_Shoot = 41,
    gEAction_Reload = 42,
    gEAction_Cock = 43,
    gEAction_Cast = 44,
    gEAction_PowerCast = 45,
    gEAction_MagicParade = 46,
    gEAction_QuickCast = 47,
    gEAction_Summon = 48,
    gEAction_Heal = 49,
    gEAction_Wait = 50,
    gEAction_JumpBack = 51,
    gEAction_Fwd = 52,
    gEAction_Back = 53,
    gEAction_Left = 54,
    gEAction_Right = 55,
    gEAction_Move = 56,
    gEAction_Jump = 57,
    gEAction_Evade = 58,
    gEAction_Slide = 59,
    gEAction_Fall = 60,
    gEAction_Dive = 61,
    gEAction_COMBATACTIONS_END = 62
};
```

The full enum continues through `gEAction_Count = 145`.

Use the exact native action rather than collapsing QuickAttackR/L into a filename heuristic. In the current stateless marker prototype, exact Quick/QuickR/QuickL action values also let global `StartEffect` correlate the marker with the Quick callback family whose native timer was suppressed.

Inventory caveat: serialized action tokens are not proven to map 1:1 to enum names in every family. Native filenames contain `LightStumble`, while the SDK exposes `gEAction_Stumble` but no separate `gEAction_LightStumble`. A mapping from `gEAction_Stumble` to the `LightStumble` resource token is plausible but remains unverified.

### 8.1 Whirl-family naming and input coverage

Do not equate a serialized `WhirlAttack` filename token with the full
`gEAction_WhirlAttack` path without runtime action logging.

Current human-melee observations:

- Dual has SimpleWhirl only, but its exact Hit/Recover filenames use
  `WhirlAttack`; input is an attack hold slightly shorter than PowerAttack.
- 2H and Staff have full Whirl; input is Block + quick attack.
- Block + held attack with 2H/Staff selects Finishing rather than Whirl.
- ordinary 1H families have no Whirl.
- hand-to-hand coverage remains unknown.

This family mismatch is another reason to use native callback/action identity for
behavior and filenames for exact asset selection/cataloging.

## 9. `gEPhase`

```cpp
enum gEPhase
{
    gEPhase_Raise = 0,
    gEPhase_Hit = 1,
    gEPhase_Aim = 2,
    gEPhase_Recover = 3,
    gEPhase_Begin = 4,
    gEPhase_Loop = 5,
    gEPhase_End = 6,
    gEPhase_Full = 7,
    gEPhase_Walk = 8,
    gEPhase_Run = 9,
    gEPhase_Sprint = 10,
    gEPhase_Far = 11,
    gEPhase_Stand = 12,
    gEPhase_StrafeL = 13,
    gEPhase_StrafeR = 14,
    gEPhase_Turn90 = 15,
    gEPhase_Ambient = 16,
    gEPhase_Proud = 17,
    gEPhase_Approve = 18,
    gEPhase_Thoughtful = 19,
    gEPhase_Angry = 20,
    gEPhase_Threaten = 21,
    gEPhase_Nervous = 22,
    gEPhase_Point = 23,
    gEPhase_Preach = 24,
    gEPhase_Beg = 25,
    gEPhase_Sad = 26,
    gEPhase_None = 27
};
```

Current combat work primarily uses Raise, Hit, Recover, and Begin/Loop/End for other action families where relevant.

## 10. Animation Type Token

The supplied naming analysis identifies:

- `N` — normal / non-overlay animation;
- `O` — overlay animation;
- `I` — interaction animation.

This classification is useful for filename analysis.

Exact engine enum/internal representation should be source-verified before using these one-letter tokens as runtime authority.

## 11. `gEDirection`

```cpp
enum gEDirection
{
    gEDirection_None = 0,
    gEDirection_Fwd = 1,
    gEDirection_Back = 2,
    gEDirection_Left = 3,
    gEDirection_Right = 4,
    gEDirection_FwdLeft = 5,
    gEDirection_FwdRight = 6,
    gEDirection_BackLeft = 7,
    gEDirection_BackRight = 8
};
```

The direction token is part of animation resolution and filename serialization.

## 12. Separator / Unknown Metadata Field

Example:

`_00_%_00_`

Current source material treats this mainly as a separator/unknown metadata group.

**Status: UNKNOWN.**

Do not assign semantic meaning in production code without new evidence.

## 13. Destination / Next Pose

The pose token after the separator indicates the destination/next pose used after the animation.

Example:

`...P1_Attack_Hit...P0...`

means a P1-source attack Hit that resolves toward P0.

Repeated animation-modding tests strongly support that changing the final pose identifier can change the stance the actor ends in.

Raise commonly preserves source pose while Hit performs the meaningful pose transition.

## 14. Composite Pose Labels

Observed labels include P10, P21, P30, P12, P22, P32, P11, P31, P60, and P61.

Strongly supported:

these are meaningful engine pose/state identifiers and must be preserved.

Working interpretation from repeated observations:

the second digit often correlates with a broader destination/main pose family while the first digit distinguishes a more specific transition/attack variant.

This interpretation is not yet a fully reverse-engineered formal rule.

## 15. CombatMove Distance Field

Example:

`...P1_125_R`

The numeric field is used by CombatMove animation movement/reach logic.

Source material reports a game function `GetCombatMoveLength`, but for relevant Hit animations Gothic 3 uses the loaded animation filename convention rather than the returned scripted value.

Important asset-replacement caveat from supplied research:

a renamed animation can be treated as a different animation resource rather than a true overwrite, and the engine may keep the first matching resource loaded from the lower archive hierarchy.

This can require archive/resource management when changing distance-encoded animation names.

## 16. Final Side / Attack-Direction Token

Examples: `L`, `R`.

The native SDK exposes a separate two-valued `gEHitDirection` (`Left`, `Right`) on `gCScriptRoutine_PS`. The complete native filename inventory strongly correlates attack-side naming with the final token:

- every indexed Hero `QuickAttackR` Hit ends in `R`;
- every indexed Hero `QuickAttackL` Hit ends in `L`;
- every indexed Hero Normal `N_Left` Hit ends in `L`;
- every indexed Hero Normal `N_Right` Hit ends in `R`;
- forward Normal attacks use P0/P2 -> `R` and P1/P3 -> `L` across the indexed human equipment families.

Jackydima's commented Normal-Attack experiment assigns `PropertyHitDirection` using the same P0/P2 -> Right and P1/P3 -> Left pattern. Because that block is disabled reconstruction/reference code, it supports the correlation but does not prove the native assignment pipeline.

**Status: STRONGLY SUPPORTED as logical attack/hit-direction metadata; exact causal pipeline remains UNKNOWN.**

This direction channel is not a physical collision-arm selector. Animation-author runtime evidence shows that changing the visible swing direction without changing animation identity does not change gameplay behavior, and known Torch+1H/Dual cases can use the left-hand source independently of QuickAttackR/QuickAttackL. Never use the final token or action-side letter alone to choose right-hand, left-hand, or both collision sources.

## 17. Human Melee Pose Patterns

### 2H

Main normal attack poses: P0 and P1.

Normal attack alternation has been observed as P0 <-> P1.

### Staff

Melee Staff is structurally very close to 2H and commonly uses the same P0/P1 pattern.

### 1H

Main normal attack pose chain uses P0/P1/P2/P3.

Forward normal attacks form a four-pose cycle.

### Dual / 1H1H

Primarily P0/P1 but with attack/source-selection exceptions.

## 18. Movement Animation Set Rule

Supplied Hero forward movement example:

- `...Move_Sprint...P0_600.xmot`
- `...Move_Run...P0_400.xmot`
- `...Move_Walk...P0_160.xmot`
- `...Move_Stand...P0_0.xmot`

The source material states that multiple movement modes are needed for blending across movement speed.

The interpretation that the numeric values are literal blending weights/dominance values is a **working hypothesis** and should not be promoted to confirmed without runtime/source verification.

## 19. Frame Indexing and Duration Convention

Gothic 3 animations are authored starting at frame 0. Therefore a Blender range
from frame 0 through frame N inclusive contains N + 1 sampled frames.

Canonical documentation should state both values when timing or rescaling matters:

- `0–12 inclusive` = 13 sampled frames;
- `0–4 inclusive` = 5 sampled frames;
- `0–8 inclusive` = 9 sampled frames.

A bare phrase such as "12-frame animation" is ambiguous in this project because
the animation author has often used the ending frame number as shorthand. Ask
whether the number means the inclusive ending index or the actual sampled-frame
count before performing duration, speed, or rescaling calculations. Authored
marker indices such as frame 2, 3, or 8 remain literal Blender frame indices.

## 20. Authoring Rule for Frame Collision

For marker-controlled attacks:

- the collision marker belongs to the exact Hit animation motion;
- marker timing is authored in animation frames;
- marker presence declares that execution frame-controlled;
- the current system must not infer ownership from source pose alone.

The animation author's general working preference is to place collision one
authored frame before the intended visual contact. Exact-contact placement can
look as though collision begins only after the weapon has entered the target.
This is an authoring judgement, not a hardcoded engine delay; marker timing must
remain per animation.

For the earlier tested 2H normal attack authored from frame 0 through frame 12
inclusive (13 sampled frames):

- first plausible visual contact: frame 9;
- marker at frame 8 felt best in controlled testing.

The later double-contact fixture used markers and whooshes at frames 4 and 15,
one authored frame before its intended visual contacts. These fixtures support
the preference, but do not prove why the one-frame lead looks better or require
other animators/animations to use the same offset.

## 21. Filename Rule vs Runtime Rule

Use filenames for authoring, asset inspection, debugging, identifying serialized state, and cases where no higher-level semantic API is available.

Prefer runtime native values for behavior decisions:

- exact `gEAction`;
- exact `gEPhase`;
- normalized left/right animation UseTypes;
- current motion resource and marker list;
- actor animation family where needed.

This keeps code aligned with the engine rather than depending on fragile substring patterns.

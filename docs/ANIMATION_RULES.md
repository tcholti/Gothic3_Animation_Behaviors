# Gothic 3 Animation Rules

**Status:** Canonical engine-facing animation/authoring reference  
**Updated:** 2026-09-08

## 1. Purpose

Record generalized Gothic 3 animation-state, filename, UseType, and authored collision-marker rules relevant to `Script_G3AnimationBehaviors`.

Prefer native runtime enums/state when available. Filename fields are serialized asset contracts, not the sole behavior parser. Full enum declarations remain in the pinned Gothic 3 SDK `GameEnum.h`; this file preserves the project-specific normalization and authoring semantics that are not recoverable from the enum declarations alone.

---

## 2. Filename Structure

Canonical example:

```text
Demon_Stand_None_2H_P1_Attack_Hit_N_Fwd_00_%_00_P0_150_L
```

Current field interpretation:

```text
AnimationFamily
AniState
LeftAnimationUseType
RightAnimationUseType
SourcePose
gEAction serialization
gEPhase serialization
animation type N/O/I
direction
opaque 00_%_00 metadata group
DestinationPose
CombatMove distance/length value
final side/hit-direction token when present
```

Composite poses such as P10/P21/P30/P61 are meaningful and must not be simplified away.

---

## 3. Animation Family / Actor

The first token is the animation/resource family: `Hero`, `Demon`, `Goblin`, etc.

`Hero` is not player-only. Compatible human NPCs use Hero-family resources.

Behavior may use actor family where needed, but should prefer exact native action/phase/UseType/current motion over filename inference.

---

## 4. Raw gEUseType -> Animation Token Normalization

Filename order is:

```text
LeftAnimationUseType_RightAnimationUseType
```

Raw engine UseType and serialized animation token are not always 1:1. Preserve the established project mapping:

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

Use normalized animation categories for profile matching; do not blindly serialize raw enum spelling.

**Important collision consequence:** raw `Fist` and raw `PhysicalFist` both map to the serialized token `Fist`, but this does **not** prove that they use the same native damage mechanism. Current production `FIST` authoring is proven only for exact human `gEUseType_Fist` / raw 8. Raw 55 remains a separate discovery responsibility.

---

## 5. Combat Actions / Phases

Project-relevant `gEAction` values include:

```text
Attack=1
PowerAttack=2
QuickAttack=3
QuickAttackR=4
QuickAttackL=5
SimpleWhirl=6
WhirlAttack=10
PierceAttack=11
HackAttack=14
FinishingAttack=15
GetUpAttack=30
GetUpParade=31
AbortAttack=39
```

Use exact native action when behavior depends on family semantics. Do not treat serialized `WhirlAttack` as proof of runtime `gEAction_WhirlAttack`; Dual SimpleWhirl is a known mismatch. Hack and true Finishing likewise require runtime action distinction.

Project-relevant phases:

```text
Raise=0
Hit=1
Recover=3
Begin=4
Loop=5
End=6
```

Authored collision markers belong to the exact Hit motion.

---

## 6. Pose / Type / Direction / Distance

- source/current pose appears before the action;
- destination pose appears after the opaque metadata group;
- Raise often preserves pose while Hit performs the meaningful pose transition;
- `N` = normal/non-overlay, `O` = overlay, `I` = interaction in the current asset interpretation;
- direction tokens include Fwd/Back/Left/Right and diagonals;
- the numeric suffix participates in CombatMove movement/reach logic;
- final `L/R` strongly correlates with logical hit/attack direction, but **does not select physical collision hand/source**.

Known Torch+1H and Dual cases prove physical left/right source selection can differ from QuickAttackR/L or final filename R/L.

---

## 7. Human Melee Pose / Family Notes

```text
2H / Staff normals: mainly P0 <-> P1
1H normals: P0/P1/P2/P3 chain
Dual: mainly P0/P1 with action/source exceptions
```

Dual uses `gEAction_SimpleWhirl` while exact Hit assets serialize `WhirlAttack`.

Full Whirl exists for 2H/Staff; ordinary 1H has no equivalent full-Whirl path in current human melee coverage.

---

## 8. Frame Indexing

Animations are authored from frame 0. Therefore:

```text
0–12 inclusive = 13 sampled frames
0–4 inclusive  = 5 sampled frames
0–8 inclusive  = 9 sampled frames
```

Marker indices are literal authored frame indices.

---

## 9. Authoring Rule — Equipped Collision

For marker-controlled equipped attacks:

```text
G3AB_COL_RIGHT -> exact active set {RIGHT}; RIGHT rearmed
G3AB_COL_LEFT  -> exact active set {LEFT}; LEFT rearmed
G3AB_COL_BOTH  -> exact active set {RIGHT, LEFT}; both rearmed
G3AB_COL_OFF   -> exact active set {}
```

Rules:

- RIGHT/LEFT mean Gothic equipped slots, not filename R/L;
- use at most one collision command on an authored frame;
- use BOTH rather than same-frame RIGHT + LEFT;
- keep OFF and a later activation on separate frames;
- repeating a source marker later in the Hit authors a new contact and rearms it through `ClearTriggeredList()`;
- OFF is an intra-Hit inactive gap and does not clear triggered lists;
- marker timing is per animation;
- do not invent action-specific RIGHT/LEFT/BOTH/OFF marker names.

The animation author's general preference is often to place collision one authored frame before intended visual contact, but this is an authoring judgement, not an engine constant.

---

## 10. Authoring Rule — Production Human Fist

Production author-facing human Fist uses:

```text
G3AB_COL_FIST
```

Meaning:

> Rearm one native human raw-8 body-damage opportunity at this authored Hit frame.

This is **not** an equipped source-set command.

Production semantics relevant to the animator:

```text
unmarked exact human Fist Hit
-> native behavior

marked exact human raw-8 Fist Hit
-> custom ownership closes the native opportunity before first FIST
-> each FIST rearms one native opportunity
-> native target/contact/damage remains Gothic's responsibility
```

There is **no authored `G3AB_COL_FIST_OFF`** in the production vocabulary. Gothic self-closes a successful human Fist opportunity; the next `FIST` marker rearms the next intended contact.

Do not apply weapon semantics to FIST:

```text
NO RIGHT/LEFT equipped mask
NO Item_Attack / Item_Equipped window
NO ClearTriggeredList authoring meaning
NO weapon C1 cleanup obligation
```

Current proven authoring scope is exact human `gEUseType_Fist` / raw 8, including tested Normal/Power production behavior. Do **not** author `FIST` for `gEUseType_PhysicalFist` / raw 55 or monsters until separate discovery proves equivalence and the project deliberately extends the contract.

---

## 11. Supported Family Semantics

Current equipped marker support includes the proven Normal/Quick/full-Whirl foundation plus Power, Pierce, SimpleWhirl, and tested 2H/Staff Hack scope.

Important native restrictions remain part of the authoring contract:

- physical source control does not guarantee identical character-hit eligibility across action families;
- SimpleWhirl final StatePosition remains `1`; its native character-hit eligibility is substantially selected-target-centered but not strictly selected-target-only;
- Power native contact sensitivity is preserved;
- Pierce retains its native target/reaction semantics;
- true FinishingAttack remains outside ordinary marker treatment.

Exact current scope/proof: `EVIDENCE_INDEX.md`.

---

## 12. Filename vs Runtime Rule

Use filenames for authoring, exact asset inspection, debugging, and serialized-state identification.

Prefer runtime native values for behavior:

```text
exact gEAction
exact gEPhase
normalized left/right animation UseTypes
current resolved motion and marker list
actor animation family where needed
```

This keeps behavior aligned with Gothic rather than fragile substring parsing.

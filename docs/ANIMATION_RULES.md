# Gothic 3 Animation Rules

**Status:** Canonical engine-facing animation/authoring reference  
**Updated:** 2026-09-13

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

### 2.1 CombatMove movement field and distribution constraint

The serialized combat-movement distance/length field is an authored gameplay input, not cosmetic metadata. EV-434 statically proves that native CombatMove parses this field from the **selected resource name** and uses it to construct the commanded movement velocity.

Longstanding author/runtime practice further establishes:
- ordinary attack Raise/Recover resources are normally authored with movement `0`;
- the Hit resource normally carries the nonzero combat movement value;
- the character's gameplay translation therefore occurs during the resource/phase carrying that value, normally Hit;
- combat movement remains subject to native blocking/navigation rules, including stopping near ledges or physical obstruction; it is not an unconditional final-position command.

Do not treat renaming the resource as the preferred runtime/configuration mechanism. Gothic's packed animation resource precedence means a differently named file does not transparently replace the already-packed original resource; changing the serialized movement field requires replacing/removing/injecting the corresponding compiled animation resource. The current displacement feature therefore aims to control the proven CombatMove movement mechanism **without requiring animation renaming/repacking**. A future archive-injection authoring tool is separate scope.


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

This table is authoritative for serialized animation filename/resource tokens. Under ADR-0011, Speed/Raise profile identity uses the **actual resolved request-time animation tokens** returned by Gothic, not a static raw-UseType normalization. Therefore native Axe can resolve token `2H` and share the 2H Speed profile, while Axe Separation can resolve token `Axe`; a Rapier item may remain raw `1H` while resolving token `Rapier`. Shared resolved animation tokens share Speed profiles; distinct resolved tokens are independently configurable.

**Important collision consequence:** raw `Fist` and raw `PhysicalFist` both map to the serialized token `Fist`, but the token does **not** identify the factual runtime source. Raw8 `gEUseType_Fist` and raw55 `gEUseType_PhysicalFist` now both have accepted production behavior, but they remain separate mechanisms with different source/contact rules. Production `FIST` authoring is governed by factual runtime source identity and the evidence-backed family contract; never infer raw8 vs raw55 from the serialized token alone.

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

### 5.1 Raise filename patterns

**Historical 2H Raise runtime proof:** the early G3AB prototype requested only factual `gEAction_Attack` + phase `Raise` through Gothic's `sAICombatMoveInstr`; it did not construct a filename. Runtime acceptance recorded that Gothic automatically resolved the correct P0/P1 Raise animation. Thus Raise filenames are the serialized result of Gothic's normal animation-selection rules, not names G3AB should invent.

Native inventory confirms these serialized phase/action patterns:

```text
Normal:
..._Attack_Hit_...
..._Attack_Raise_...

Quick right:
..._QuickAttackR_Hit_...
..._QuickAttackR_Raise_...

Quick left:
..._QuickAttackL_Hit_...
..._QuickAttackL_Raise_...

Full Whirl:
..._WhirlAttack_Hit_...
..._WhirlAttack_Raise_...
```

Current inventory counts: 64 Normal `Attack_Raise`, 12 `QuickAttackR_Raise`, 16 `QuickAttackL_Raise`, and 6 `WhirlAttack_Raise` names. These counts demonstrate native naming patterns, not universal asset availability for every profile.

Do not infer that a Raise asset can always be authored by changing only `Hit` to `Raise`. Native names show that destination pose and movement/reach suffixes may differ between the matching Raise and Hit.

For a rule-derived Raise candidate, preserve the factual Hit request's serialized direction token exactly:

```text
Hit ..._Fwd_...   -> Raise ..._Fwd_...
Hit ..._Left_...  -> Raise ..._Left_...
Hit ..._Right_... -> Raise ..._Right_...
```

Do not substitute a different directional variant merely because an existing Raise file with that direction is present in the inventory. For example, Dual `Attack_Raise_N_Left/Right` assets do not authorize using those files for a factual `Attack_Hit_N_Fwd` route.

Raise derivation is independent of Recover. Do **not** use a Recover filename, Recover destination pose, or Recover availability to construct or validate a Raise name. Runtime testing has established that Hit execution can continue when matching Recover animation assets are removed; Recover is therefore not an authoring dependency for Raise-name derivation.

Release authoring guidance must explain the filename fields Gothic derives from its factual action/phase/source-pose/use-type/direction state and use matched real examples of the exact Raise resource Gothic requests whenever available.

EV-423 runtime validation adds a tested dual-wield authoring example. The following rule-derived assets were selected and played correctly when AddRaise requested them:

```text
Hero_Stand_1H_1H_P0_Attack_Raise_N_Fwd_00_%_00_P0_0_R
Hero_Stand_1H_1H_P1_Attack_Raise_N_Fwd_00_%_00_P1_0_L

Hero_Stand_1H_1H_P0_QuickAttackR_Raise_N_Fwd_00_%_00_P0_0_R
Hero_Stand_1H_1H_P0_QuickAttackL_Raise_N_Fwd_00_%_00_P0_0_L
Hero_Stand_1H_1H_P1_QuickAttackR_Raise_N_Fwd_00_%_00_P1_0_R
Hero_Stand_1H_1H_P1_QuickAttackL_Raise_N_Fwd_00_%_00_P1_0_L
```

The rule-derived P3 QuickAttackL Raise candidate was not observed, matching non-observation of its corresponding P3 -> P61 Hit route in ordinary runtime testing. Treat that route as unproven/unused in current testing rather than deleting the inventory fact.

For the **tested ordinary dual P0/P1 candidates above**, the successful authoring transformation was more specific than changing only the phase token:

```text
start from the factual Hit route
-> preserve actor/state/use types
-> preserve source pose before the action
-> preserve factual action (Attack / QuickAttackR / QuickAttackL)
-> Hit -> Raise
-> preserve N/O/I type and factual direction token
-> make Raise pose-preserving: destination pose = source pose
-> movement/reach numeric suffix = 0
-> preserve the final logical R/L token
```

Concrete tested Normal example:

```text
Hit:   Hero_Stand_1H_1H_P0_Attack_Hit_N_Fwd_00_%_00_P1_118_R
Raise: Hero_Stand_1H_1H_P0_Attack_Raise_N_Fwd_00_%_00_P0_0_R
```

Concrete tested Quick example:

```text
Hit:   Hero_Stand_1H_1H_P0_QuickAttackR_Hit_N_Fwd_00_%_00_P0_100_R
Raise: Hero_Stand_1H_1H_P0_QuickAttackR_Raise_N_Fwd_00_%_00_P0_0_R
```

This is a **runtime-validated dual P0/P1 authoring pattern**, not authority to blindly apply the same destination/reach fields to every animation family. For another family, prefer an exact native matched Raise example when one exists, then use the general filename-field rules plus runtime validation.

Once a user-authored animation name is actually selected and played correctly at runtime, add its exact name to `data/animation_names/user_created_tested_animation_names.txt`. Do not add merely planned, generated, inferred, or unobserved candidates. The native `all_animation_names.txt` remains unchanged as the original Gothic inventory.

EV-430 adds a tested pose-changing Shield+1H Quick example. The Hit may change pose, while the preceding Raise remains pose-preserving at its factual source pose:

```text
Hit:   Hero_Stand_Shield_1H_P1_QuickAttackL_Hit_N_Fwd_00_%_00_P50_100_L
Raise: Hero_Stand_Shield_1H_P1_QuickAttackL_Raise_N_Fwd_00_%_00_P1_0_L

Hit:   Hero_Stand_Shield_1H_P3_QuickAttackL_Hit_N_Fwd_00_%_00_P70_100_L
Raise: Hero_Stand_Shield_1H_P3_QuickAttackL_Raise_N_Fwd_00_%_00_P3_0_L
```

In the same runtime fixture, `Quick_AddRaise=On` remained safe for other Shield+1H Quick routes that had no matching Raise resource: those attacks still executed normally. Treat that as tested runtime behavior for partial asset coverage, not as evidence for a specific uninstrumented engine return code.

Historical implementation warning from EV-423: native directional Normal Left/Right Raises played correctly, but the inserted continuation initially re-resolved the following Action1 Hit as Fwd. EV-424 identified the cause, EV-426 source-accepted the correction, and EV-427 runtime-accepted preserved Fwd/Left/Right continuation. Do not rename directional Raise assets to compensate for continuation behavior.

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

EV-271 positively validates both **frame 0 and frame 1** marker delivery/acceptance for tested equipped 2H Normal `RIGHT` and raw8 Sabretooth Quick `FIST`. There is no global "frame 1 minimum" rule.

The behavioral meaning of an early marker is mechanism-specific:

```text
EQUIPPED RIGHT / LEFT / BOTH
-> opens/rearms the selected physical source window at that authored frame
-> window remains active until OFF, source replacement, or native/terminal cleanup

RAW8 FIST
-> rearms one native body-damage opportunity at that authored frame
-> it is not a persistent equipped collision window
```

Therefore frame 0 is a valid authored index, but it is not automatically the best timing. In the EV-271 Sabretooth Quick control, frame-0 FIST was accepted and its timing permission was armed/consumed correctly, yet the User observed more misses than with frame 1. This is consistent with rearming a one-shot native opportunity before useful physical contact, not with marker transport failure.

Author markers according to the desired physical contact timing, not simply at the earliest legal frame.

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
- slot selection does not imply that Gothic has a native damage route for every equipped source type; EV-308 shows that LEFT can activate a shield/raw9 source `5 -> 7` and clean it back to `5`, yet the tested Quick shield-bash fixture produces no native damage;
- use at most one collision command on an authored frame;
- use BOTH rather than same-frame RIGHT + LEFT;
- keep OFF and a later activation on separate frames;
- repeating a source marker later in the Hit authors a new contact and rearms it through `ClearTriggeredList()`;
- OFF is an intra-Hit inactive gap and does not clear triggered lists;
- marker timing is per animation;
- frame 0 is valid when the intended equipped collision window should begin immediately; EV-271 validates frame-0 2H Normal RIGHT activation, damage and cleanup;
- do not invent action-specific RIGHT/LEFT/BOTH/OFF marker names.
- current production authoring does **not** claim shield-bash damage support. Do not author `LEFT` on a shield expecting damage; a future shield-bash feature requires separate research into damage eligibility/dispatch.

The animation author's general preference is often to place collision one authored frame before intended visual contact, but this is an authoring judgement, not an engine constant.

---

## 10. Authoring Rule — Production Raw8 Fist

Production author-facing raw8 Fist uses:

```text
G3AB_COL_FIST
```

Meaning:

> Create or refresh one persistent native raw-8 body-contact opportunity at this authored Hit frame.

This is **not** an equipped source-set command.

Production semantics relevant to the animator:

```text
unmarked exact raw8 Fist Hit
-> native behavior

marked exact supported raw8 Fist Hit
-> custom ownership closes the native opportunity before first FIST
-> each accepted FIST creates or refreshes ONE pending opportunity for exact actor/C1/source/SPU
-> while pending, timing permission may repeat at proven Game+0x16E180 checkpoint
   for matching timing actor/motion while real time is below threshold + epsilon
-> native miss rearms latch 1 -> 0 without consuming the opportunity
-> first exact native contact-resolution dispatch at caller-return Game+0x16E348
   consumes the pending opportunity before Gothic original; it is not an HP-success test
-> later FIST refreshes/reopens one opportunity, never stacks opportunities
-> execution replacement/finalization/end may retire an unused pending opportunity
-> native contact geometry/target/damage remains Gothic's responsibility
```

There is **no authored `G3AB_COL_FIST_OFF`** in the production vocabulary. Timing permission itself is not consumption and never mutates the real animation clock. Timing retirement (including timing identity changes) does not consume the logical opportunity. The exact contact dispatch consumes it even if Gothic subsequently blocks damage; the next `FIST` can reopen the next intended contact. Permanent owner: [COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md](COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md), §§3–9; evidence EV-346–EV-364.

EV-305 directly confirms the multi-contact authoring meaning on human raw8 Fist: two authored `FIST` markers in one supported Hit are accepted in the same C1, and on contacting executions they produce two native damage contacts. EV-307 independently confirms the same mechanism on Sabretooth/transformed Sabretooth: marker1 uses the early-permission path, marker2 is accepted later as `NATIVE_TIMING`, and contacting executions can damage twice. Therefore repeat `FIST` only when the animation genuinely intends another body-contact hit; the rule is factual-source/mechanism based, not human-species specific.

Do not apply weapon semantics to FIST:

```text
NO RIGHT/LEFT equipped mask
NO Item_Attack / Item_Equipped window
NO ClearTriggeredList authoring meaning
NO weapon C1 cleanup obligation
```

Frame 0 is a valid raw8 FIST frame in the tested Sabretooth Quick mechanism, but it rearms the opportunity immediately. EV-271 observed more frame-0 misses than frame 1 despite correct marker acceptance/timing-permission use. For practical authoring, place FIST near the intended physical contact rather than at frame 0 merely because frame 0 is legal.

Current proven raw8 family scope is Normal/Power/Quick/Sprint and is summarized in `COLLISION_REFERENCE.md`. Raw55/PhysicalFist is a separate permanent mechanism under `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`; it must not inherit raw8 latch semantics merely because both serialize as `Fist`.

### Raw55 / PhysicalFist FIST authoring

Raw55 uses the same authored marker token:

```text
G3AB_COL_FIST
```

but a different runtime mechanism.

Current supported/proven raw55 scope is factual current RIGHT PhysicalFist/raw55 in Normal, Quick, true Power and Sprint-origin marked executions. One or two authored FIST markers are supported. The first FIST owns the authored physical opening/contact opportunity; a later FIST in the same C1 rearms another contact opportunity without authoring another physical group opening.

Author each FIST at the intended physical contact. Do not infer raw55 support merely from the serialized animation token `Fist`; runtime source identity decides raw8 vs raw55 behavior.

Current exclusions:

```text
NO FIST_OFF
NO LEFT raw55 generalization
NO mixed FIST + equipped RIGHT/LEFT/BOTH/OFF execution
NO more than two raw55 FIST markers
NO custom/direct damage semantics
```

Evidence: EV-262–EV-298. Current behavior summary: `COLLISION_REFERENCE.md`.

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
factual raw left/right gEUseType for source diagnostics/collision where needed
request-time resolved left/right animation tokens for Speed/Raise profile identity
current resolved motion and marker list
actor animation family where needed
```

This keeps behavior aligned with Gothic rather than fragile substring parsing.

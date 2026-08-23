# Gothic 3 Animation Catalog

**Status:** Curated working catalog  
**Date:** 2026-08-22  
**Scope:** Current human melee attacks and selected stumble animations

## 1. Purpose

This catalog indexes exact Gothic 3 animation names together with animation-author observations that may help explain action selection, pose transitions, collision-source behavior, Raise availability, and naming rules.

It complements `ANIMATION_RULES.md`:

- `ANIMATION_RULES.md` records generalized engine-facing naming semantics.
- this catalog records concrete animation families, exact examples, and unresolved patterns.
- the verbatim source preserves every supplied filename and note without editorial rewriting.

Filename patterns are evidence, but they are not automatically engine behavior. Runtime conclusions must continue to use the project's evidence vocabulary and controlled tests.

## 2. Current Sources

### Author-grouped attacks and stumbles

Verbatim source:

`data/animation_names/author_grouped_attacks_and_stumbles.txt`

Received: 2026-08-22.

Contents:

- 341 unique exact animation-name entries;
- grouped attacks for 1H, Torch+1H, Shield+1H, 2H, Staff, and Dual wield;
- Raise/Hit/Recover relationships;
- pose transitions;
- known and uncertain collision-source notes;
- custom Recover files made by the animation author;
- possibly unused animation files;
- selected 1H and 2H stumble animations.

The source file is authoritative for the exact names and original annotations. This catalog summarizes it without replacing it.

### Complete native animation-name inventory

Generated source:

`data/animation_names/all_animation_names.txt`

Generated: 2026-08-22.

Extraction sources:

- `_compiledAnimation_pak`
- `_compiledAnimation_p00`

The two extracted sources are dated 2026-08-10 in the user's working archive and together represent all natively used animations available to this catalog.

Generation method:

- recursively enumerate `.xmot` files in both sources;
- remove only the `.xmot` extension;
- combine both sources;
- sort names;
- remove duplicate names.

Result: **5,991 unique animation names**.

The inventory remains a raw, sorted, unique list. Curated interpretations belong in this document rather than inside the generated file.

## 3. Evidence Labels Used Here

- **Known** — direct animation-author observation and/or converging source evidence.
- **Strongly supported** — repeated animation-author evidence but not yet isolated by the current logger.
- **Working hypothesis** — plausible interpretation requiring controlled verification.
- **Unknown** — file exists or a visual expectation exists, but runtime selection/source is not established.
- **Design note** — desired project behavior rather than native engine behavior.

The canonical status of engineering claims remains `EVIDENCE_LEDGER.md`.

## 4. Current Family Coverage

| Animation family | Current catalog coverage |
|---|---|
| None + 1H | Forward/Right/Left Normal, Quick, Power, Parade Pierce/Finishing, Fwd/Back GetUp |
| Torch + 1H | Forward/Right/Left Normal, Quick, Power, Parade Pierce/Finishing, Fwd/Back GetUp |
| Shield + 1H | Forward Normal, Quick, Power, Parade Pierce/Finishing, Fwd/Back GetUp |
| None + 2H | Normal, Quick, Power, Parade Whirl/Finishing, Fwd/Back GetUp |
| None + Staff | Normal, Quick, Power, Parade Whirl/Finishing, Fwd/Back GetUp |
| 1H + 1H | Forward/Right/Left Normal, Quick, Power, Whirl, Parade Pierce/Finishing, Fwd/Back GetUp |
| Selected stumbles | 2H LightStumble/StumbleL/StumbleR/PierceStumble and 1H ParadeStumble/QuickStumble/StumbleL/StumbleR |

This is not yet a complete inventory of every combat animation or every actor family.

## 5. Raise Availability and Current Project Relevance

| Family/action | Source-file observation | Current project interpretation |
|---|---|---|
| 1H Normal | Raise files exist but do not work natively | Future custom Raise target |
| 1H Quick | Raise files do not exist in the supplied set | New Raises must be authored |
| 1H Power | Raise works | Preserve native behavior |
| 1H Parade Pierce | Raise works | Preserve native behavior |
| Torch+1H Normal | Raise files exist but do not work natively | Future custom Raise target |
| Torch+1H Quick | Raise files do not exist in the supplied set | New Raises must be authored |
| Shield+1H Normal | Raise files exist but do not work natively | Future custom Raise target |
| Shield+1H Quick | Raise files do not exist in the supplied set | New Raises must be authored |
| 2H Normal | Raise files exist but do not work natively | Custom insertion already proven |
| 2H Quick | Raise files exist but do not work natively | Current/future custom Raise target |
| 2H Parade Whirl | Raise probably does not work | Selected future Raise candidate |
| Staff Normal | Raise files exist but do not work natively | Same broad problem family as 2H |
| Staff Quick | Raise files exist but do not work natively | Current/future custom Raise target |
| Staff Parade Whirl | Raise probably does not work | Selected future Raise candidate |
| Dual Forward Normal | Raise files absent | New Raises must be authored |
| Dual directional Normal | Raise files exist but do not work natively | Future custom Raise target |
| Dual Quick | Raise files absent | New Raises must be authored |
| Dual Power/Pierce | Raise works | Preserve native behavior |
| Dual Whirl/Finishing | Raise not needed in supplied notes | No immediate Raise work |

The v0.13 2H Quick collision regression played no Raise. This is the expected
current implementation state: the test validates collision ownership and Quick
bookkeeping only; custom Quick Raise insertion has not yet been enabled.

## 6. Known Left-Hand Collision Annotations

The usual weapon collision source is reported as `Slot_RightHand_Weapon`. The supplied source explicitly annotates the following exceptions.

### Torch + 1H Quick

```text
Hero_Stand_Torch_1H_P1_QuickAttackL_Hit_N_Fwd_00_%_00_P1_100_L
Hero_Stand_Torch_1H_P1_QuickAttackR_Hit_N_Fwd_00_%_00_P1_100_R
Hero_Stand_Torch_1H_P3_QuickAttackL_Hit_N_Fwd_00_%_00_P31_100_L
```

All three are annotated as using `Slot_LeftHand_Weapon`.

### Dual wield

```text
Hero_Stand_1H_1H_P0_Attack_Hit_N_Fwd_00_%_00_P1_118_R
Hero_Stand_1H_1H_P1_QuickAttackR_Hit_N_Fwd_00_%_00_P1_100_R
Hero_Stand_1H_1H_P1_QuickAttackL_Hit_N_Fwd_00_%_00_P1_100_L
Hero_Stand_1H_1H_P0_WhirlAttack_Hit_N_Fwd_00_%_00_P1_100_L
Hero_Parade_1H_1H_P1_PierceAttack_Hit_N_Fwd_00_%_00_P1_50_F
```

These are annotated as using `Slot_LeftHand_Weapon`.

Controlled v0.10 player runtime established the broader Dual source map:

| Exact execution | Source |
|---|---|
| `Hero_Stand_1H_1H_P0_Attack_Hit_N_Fwd_00_%_00_P1_118_R` | LEFT |
| `Hero_Stand_1H_1H_P1_Attack_Hit_N_Fwd_00_%_00_P0_119_L` | RIGHT |
| `Hero_Stand_1H_1H_P0_QuickAttackR_Hit_N_Fwd_00_%_00_P0_100_R` | RIGHT |
| `Hero_Stand_1H_1H_P0_QuickAttackL_Hit_N_Fwd_00_%_00_P0_100_L` | RIGHT |
| `Hero_Stand_1H_1H_P1_QuickAttackR_Hit_N_Fwd_00_%_00_P1_100_R` | LEFT |
| `Hero_Stand_1H_1H_P1_QuickAttackL_Hit_N_Fwd_00_%_00_P1_100_L` | LEFT |
| `Hero_Parade_1H_1H_P0_PierceAttack_Hit_N_Fwd_00_%_00_P0_50_F` | RIGHT |
| `Hero_Parade_1H_1H_P1_PierceAttack_Hit_N_Fwd_00_%_00_P1_50_F` | LEFT |
| `Hero_Stand_1H_1H_P0_PowerAttack_Hit_N_Fwd_00_%_00_P0_180_R` | RIGHT + LEFT |
| `Hero_Stand_1H_1H_P1_PowerAttack_Hit_N_Fwd_00_%_00_P1_190_L` | RIGHT + LEFT |

The two P0 Quick variants sharing RIGHT and the two P1 variants sharing LEFT
confirm that QuickAttackR/L naming is not a collision-hand selector.

The supplied Dual P3 Quick file is visually left-handed, but its runtime use is unconfirmed:

```text
Hero_Stand_1H_1H_P3_QuickAttackL_Hit_N_Fwd_00_%_00_P61_100_L
```

These examples must not yet be used to claim that the final filename R/L token directly selects the physical collision source. That question remains open for the later R/L analysis.

## 7. Dual Animations with Visually Multiple Weapon Contacts

The following supplied animations are described as visually involving both weapons while their exact native collision-source behavior is not fully established:

```text
Hero_Stand_1H_1H_P0_Attack_Hit_N_Right_00_%_00_P11_110_R
Hero_Stand_1H_1H_P1_Attack_Hit_N_Right_00_%_00_P31_90_R
Hero_Stand_1H_1H_P0_Attack_Hit_N_Left_00_%_00_P0_90_L
Hero_Stand_1H_1H_P1_Attack_Hit_N_Left_00_%_00_P21_90_L
```

Dual Power attacks are visually whirl-like. Controlled v0.10 runtime confirmed
both equipped weapons activate for P0 and P1, converging with Jackydima's
initial collision code:

```text
Hero_Stand_1H_1H_P0_PowerAttack_Hit_N_Fwd_00_%_00_P0_180_R
Hero_Stand_1H_1H_P1_PowerAttack_Hit_N_Fwd_00_%_00_P1_190_L
```

The visual contact order is:

- P0: right -> left -> right;
- P1: left -> right -> left.

Native gameplay is reported to damage only twice. Initial BOTH activation lets
each weapon hit once, but the first weapon needs its triggered list rearmed
before the third visual contact. Jackydima's later Dual-specific list clearing
is intended to address this missing repeated contact; exact runtime rearm timing
still needs logging.

### Dual SimpleWhirl

Dual has SimpleWhirl rather than the separate full Whirl used by 2H/Staff, even
though its exact filenames contain `WhirlAttack`. Supplied files:

```text
Hero_Stand_1H_1H_P0_WhirlAttack_Hit_N_Fwd_00_%_00_P1_100_L
Hero_Stand_1H_1H_P1_WhirlAttack_Recover_N_Fwd_00_%_00_P1_0_L
Hero_Stand_1H_1H_P1_WhirlAttack_Hit_N_Fwd_00_%_00_P0_100_R
Hero_Stand_1H_1H_P1_WhirlAttack_Recover_N_Fwd_00_%_00_P1_0_L
```

It is selected by holding attack slightly less than the PowerAttack threshold,
making accidental Power selection easy. Visually the actor turns and finishes
with one sword extended forward and the other backward. Whether one or both
weapons are intended to damage is unknown. The P0 Hit has an older left-source
annotation, while Jackydima's SimpleWhirl pose rule would use right in P0 and
left in P1; controlled runtime logging must resolve this conflict.

### Full Whirl and Finishing coverage

For human melee:

- full Whirl exists for 2H and Staff and is selected by Block + quick attack;
- ordinary 1H families have no Whirl;
- hand-to-hand coverage is not yet known;
- Block + held attack with 2H/Staff selects Finishing rather than Whirl.

On a downed enemy, Finishing death timing is timer-based rather than collision-
impact-based. Raise-length changes did not disturb the timing, strongly
supporting that the timer begins with Hit. Preserve the established Hit length
when authoring replacements. A standing target may select HackAttack instead,
but that exact selection remains a working hypothesis.

Dual Finishing attacks may also visually contact with both weapons. A single
damaging source is acceptable for those particular animations until there is a
gameplay reason to require both.

## 8. Custom Recover Files in the Supplied Set

The animation author created the following Recover files:

```text
Hero_Stand_None_1H_P50_QuickAttackL_Recover_N_Fwd_00_%_00_P0_0_L
Hero_Stand_None_1H_P70_QuickAttackL_Recover_N_Fwd_00_%_00_P0_0_L
Hero_Stand_None_1H_P60_QuickAttackR_Recover_N_Fwd_00_%_00_P0_0_R
Hero_Stand_Shield_1H_P50_QuickAttackL_Recover_N_Fwd_00_%_00_P0_0_L
Hero_Stand_Shield_1H_P70_QuickAttackL_Recover_N_Fwd_00_%_00_P0_0_L
Hero_Stand_Shield_1H_P60_QuickAttackR_Recover_N_Fwd_00_%_00_P0_0_R
```

These should not be mistaken for confirmed stock files when later comparing the catalog with the complete game inventory.

## 9. Possibly Unused or Unimplemented Assets

### 1H PowerAttack Loop

Four 1H-only `PowerAttack_Loop` files are included in the supplied source. The animation author reports that they are not implemented in gameplay as far as currently known.

Status: **Unknown runtime use**.

### 2H and Staff P1 Parade files

The supplied source marks the following P1 Whirl/Finishing variants as probably unused or unnecessary:

- 2H P1 Parade Whirl Raise/Hit;
- 2H P1 Parade Finishing Raise;
- Staff P1 Parade Whirl Raise/Hit;
- Staff P1 Parade Finishing Raise.

Status: **Unknown runtime use**.

### Dual P3 Quick

The P3-to-P1 Dual Quick file is visually meaningful but may not be selected by the current game.

Status: **Unknown runtime use**.

## 10. R/L Attack and Stumble Inventory Analysis

Analysis of all 5,991 native names found 540 Hero-family stumble entries. Counts include Hit and Recover resources across equipment families:

| Serialized action token | Final token | Count |
|---|---:|---:|
| `LightStumble` | `U` | 68 |
| `ParadeStumbleL` | none | 24 |
| `ParadeStumbleR` | none | 24 |
| `PierceStumble` | none | 102 |
| `QuickStumble` | none | 104 |
| `StumbleL` | none | 109 |
| `StumbleR` | none | 109 |

`QuickStumble` is a systematic non-R/L family rather than an isolated missing suffix. Human melee variants include P0, P1 -> P10, P2 -> P20, and P3 -> P30 transitions across 1H, Staff, Shield+1H, and Torch+1H. A QuickStumble may therefore lean strongly or change stance without belonging to an R/L action pair.

The native action enum likewise contains one `gEAction_QuickStumble` but separate `gEAction_StumbleR` and `gEAction_StumbleL` values. `LightStumble` appears in filenames even though the SDK has no separate `gEAction_LightStumble`; its exact runtime action mapping remains open.

The attack inventory shows strong direction correlations:

- 11 indexed Hero QuickAttackR Hit files all end in `R`;
- 16 indexed Hero QuickAttackL Hit files all end in `L`;
- 10 Normal `N_Left` Hits all end in `L`;
- 10 Normal `N_Right` Hits all end in `R`;
- 20 forward Normal Hits consistently map P0/P2 to `R` and P1/P3 to `L`.

Current interpretation: R/L is logical attack/hit-direction metadata that may participate in selecting directional reaction actions. It is not physical weapon-trajectory measurement and is not a collision-hand selector. Exact causality among action R/L, final filename R/L, `Routine.HitDirection`, and victim `StumbleR/L` remains unproven and is not required by current v0.7, Raise, or speed plans.

### 10.1 2H/Staff Quick selection and movement observations

The controlled v0.13 repeated-marker log selected these exact 2H Hit motions:

```text
Hero_Stand_None_2H_P0_QuickAttackR_Hit_N_Fwd_00_%_00_P1_90_R
Hero_Stand_None_2H_P0_QuickAttackL_Hit_N_Fwd_00_%_00_P1_90_L
```

Three no-target executions used QuickAttackR/action 4. The final targeted
execution used QuickAttackL/action 5. All four began in P0 and transitioned
toward P1 according to the serialized Hit names.

Separate animation-author observation, outside the preserved log, found:

- the first 2H Quick after drawing the weapon selected P0 QuickAttackR;
- returning from P1 to P0 through a Normal attack and then requesting Quick
  selected QuickAttackR again;
- 2H movement resources such as
  `Hero_Stand_None_2H_P0_Move_Run_N_Fwd_00_%_00_P0_400` and the corresponding
  P1-to-P0 resource reset the visible pose to P0;
- after a movement reset, QuickAttackL could be selected, while a subsequent
  movement reset was followed by QuickAttackR;
- the same broad behavior was observed with Staff, while a few preliminary 1H
  observations appeared to alternate R/L more consistently.

These observations disprove the earlier tentative description of a separate
"moving Quick attack." Melee Quick actions cancel locomotion and play their own
non-overlay attack motion. They do not yet establish the hidden engine state or
complete selection algorithm that chooses QuickAttackR versus QuickAttackL.
That algorithm is not required for marker ownership: the callback/action/phase
adapter accepts both exact Quick sides, and each exact marked motion carries
its own authored collision schedule.

## 11. Fist v0.9 Causal-Test Fixture and Results

Each variant replaced the same P0 Hit animation and used a separate game launch
and preserved log.

Exact runtime files:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R
Hero_Stand_None_Fist_P1_Attack_Recover_N_Fwd_00_%_00_P1_0_R
```

All Hit variants were authored from frame 0 through frame 8 inclusive
(9 sampled frames) and retained the same filename, action, P0 -> P1 transition,
target-focus requirement, and v0.9 DLL. Each variant could
use a custom marker-free Recover starting from its own final pose.

Results:

| Contact motion | Marker frame | Damage | Marker path |
|---|---:|---|---|
| native left hand | 3 | passed | UseType 8; group 0 -> 0; group request skipped; list cleared |
| custom right hand | 3 | passed | UseType 8; group 0 -> 0; group request skipped; list cleared |
| custom left leg | 3 | passed | UseType 8; group 0 -> 0; group request skipped; list cleared |
| custom right leg | 2 | passed | UseType 8; group 0 -> 0; group request skipped; list cleared; collision/whoosh frames were accidentally swapped |
| custom head | 3 | passed | UseType 8; group 0 -> 0; group request skipped; list cleared |

The right-leg marker frame 2 differs from the planned common frame 3 because the
author accidentally placed collision on frame 2 and whoosh on frame 3. This is a
confirmed fixture-authoring mistake, not a discovered engine timing rule. Because
the attack still damaged while the group request was omitted, it remains valid
source/contact evidence but is not an identical marker-timing comparison.

The four focused-neutral custom-motion sessions were closed quickly after
contact, so Recover completion was not established. This does not weaken the
Fist group-call causal result.

An unfocused allied human did not receive damage from repeated marked P0 or
unmarked legacy/native P1 Fist attacks, while a marked 2H weapon attack could
damage that unfocused setup. Future Fist/body tests require a focusable target.

Describe the completed result as tested left/right hand, left/right leg, and head
contacts. Do not claim that every body part, PhysicalFist, or monster body is a
proven source.

## 12. Marked 2H Normal Multi-Target Fixture

The controlled v0.10 player fixture used:

- Raise frame range 0 through 4 inclusive (5 sampled frames);
- Hit frame range 0 through 12 inclusive (13 sampled frames);
- whoosh at Hit frame 6;
- `G3AB_COL_TEST` collision marker at Hit frame 7;
- right-hand 2H source `It_2H_Sword_Flamberge`;
- three spawned wolves, with god mode used to keep the test stable;
- NewBalance and `Script_AttackCollision` absent.

Four marked Normal attacks alternated the P0/P1 Hit files. Every attack produced
one accepted frame-7 marker, one right-weapon 5 -> 7 activation/list clear, and
one natural 7 -> 5 reset in phase 3, with no additional player weapon
activation. Visually, one swing damaged three wolves and at least two swings
damaged two wolves. This confirms that one marker-controlled 2H weapon window
can damage multiple distinct targets physically reached by the blade.

It does not establish completely unmodified native behavior or repeated damage
to the same target without a second source marker.

### Same-motion 2H Normal double-contact fixture

All three controlled variants replaced only:

```text
Hero_Stand_None_2H_P0_Attack_Raise_N_Fwd_00_%_00_P0_0_R
Hero_Stand_None_2H_P0_Attack_Hit_N_Fwd_00_%_00_P1_90_R
Hero_Stand_None_2H_P1_Attack_Recover_N_Fwd_00_%_00_P1_0_R
```

Fixture timing:

- Raise: frame 0 through 4 inclusive (5 sampled frames);
- Hit: frame 0 through 20 inclusive (21 sampled frames);
- whooshes: Hit frames 4 and 15;
- authored marker variants: none, frame 4 only, or frames 4 and 15;
- markers were placed one authored frame before intended visual contact.

Native/no-marker and frame-4-only variants each damaged the same target once per
attack. The frame-4 plus frame-15 variant damaged the same target at both visual
contacts, including confirmation against two separately tested targets. This is
the controlled proof that repeating a source marker rearms the weapon against an
already visited target.

The two-marker log contains four attacks. Each has one early accepted marker
near state time 0.32–0.34, two duplicate late dispatches near 0.77, and one
natural phase-3 reset. The duplicate late clear did not create a third visual
damage contact.

The v0.11 regression repeated the same two-marker motion six times. Every
execution kept one early and one late accepted marker, ignored one duplicate
late dispatch at identical state time, cleared the list twice, and naturally
reset once. Two-contact behavior remained visible against two targets.

v0.12 added two controlled fixture groups:

- horizontal 2H sweep: Raise frames 0–4, Hit frames 0–12, whoosh frame 6,
  ON frame 7, with either no OFF, OFF frame 9, or OFF frame 8;
- double attack: Raise frames 0–4, Hit frames 0–20, whooshes/ON frames 4 and
  15, OFF frame 10.

The horizontal ON-only control could damage all three grouped wolves. OFF at
frame 9 usually limited the sweep to one target and sometimes two when wolves
stood very close; OFF at frame 8 never allowed more than one. The double attack
still damaged one or multiple targets on both intended swings.

The double motion has five authored frame effects, matching two whooshes, two
ON entries, and one OFF. Nevertheless, every late contact dispatched `ON, OFF,
ON` at identical state time. This is runtime marker replay, not evidence of
additional authored entries; occurrence-aware suppression is required.

v0.13 repeated the exact double fixture seven times. Every execution admitted
only the authored two ON and one OFF operations, rejected the replayed late OFF
and extra ON, cleared the list twice, and naturally reset once. Both intended
swings remained visually effective against each of two independently tested
targets on their first attack. The animation asset and marker placement were
unchanged; only runtime replay filtering changed.

The same 0–20 ON-f4/OFF-f10/ON-f15 schedule was then applied to 2H Quick. Four
Quick executions—three QuickAttackR/action 4 and one QuickAttackL/action 5—each
accepted exactly two ON/clears and one OFF/no-clear, rejected the replayed OFF
by occurrence budget, rejected the final repeated ON by the same-update guard,
and naturally reset once. The targeted QuickAttackL damaged the opponent on
both intended swings. The first genuine ON changed Quick StatePosition 0 -> 1;
the second genuine ON preserved 1 -> 1. This completes the family-specific
Quick regression without adding Whirl ownership.

## 13. Catalog Maintenance Rules

When new animation information becomes important for future reasoning:

1. preserve exact filenames without normalization or spelling changes;
2. retain the source/provenance of author notes;
3. distinguish stock files from author-created replacements/additions;
4. distinguish file existence from confirmed runtime selection;
5. record collision-source evidence separately from visual attack direction;
6. promote hypotheses only after source or controlled runtime evidence;
7. add raw bulk inventories under `data/animation_names/`;
8. update this curated catalog when a new pattern changes project reasoning.

## 13. Next Catalog Steps

1. Continue distinguishing stock, author-created, absent, duplicate-pattern, and possibly unused entries when that distinction affects implementation.
2. Expand beyond human melee into movement, blocks, reactions, interactions, creatures, and other animation families as useful.
3. If logical hit direction later affects a planned feature, add controlled logging/testing that pairs attacker `Routine.HitDirection` with the victim's selected reaction action and motion.

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

Dual Power attacks are visually whirl-like. Jackydima's current collision code activates both equipped weapons, which matches the desired visual behavior:

```text
Hero_Stand_1H_1H_P0_PowerAttack_Hit_N_Fwd_00_%_00_P0_180_R
Hero_Stand_1H_1H_P1_PowerAttack_Hit_N_Fwd_00_%_00_P1_190_L
```

Dual Finishing attacks may also visually contact with both weapons, but execution death timing was observed to be timer-based rather than impact-frame-based. A single damaging source is acceptable for those particular animations until there is a gameplay reason to require both.

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

## 10. Stumble Set Reserved for R/L Analysis

The supplied list includes selected exact 1H and 2H stumble names, including:

- `LightStumble`;
- `StumbleL`;
- `StumbleR`;
- `PierceStumble`;
- `ParadeStumbleL`;
- `ParadeStumbleR`;
- `QuickStumble`.

They preserve source poses, destination/composite poses, directions, distances, and sometimes final R/L/U tokens.

No interpretation of their R/L meaning is frozen here. They are cataloged so the animation-author hypothesis can be evaluated against attacks and non-attack reactions together.

## 11. Catalog Maintenance Rules

When new animation information becomes important for future reasoning:

1. preserve exact filenames without normalization or spelling changes;
2. retain the source/provenance of author notes;
3. distinguish stock files from author-created replacements/additions;
4. distinguish file existence from confirmed runtime selection;
5. record collision-source evidence separately from visual attack direction;
6. promote hypotheses only after source or controlled runtime evidence;
7. add raw bulk inventories under `data/animation_names/`;
8. update this curated catalog when a new pattern changes project reasoning.

## 12. Next Catalog Steps

1. Compare the complete inventory against the supplied grouped list.
2. Mark stock-only, author-created, absent, duplicate-pattern, and possibly unused entries.
3. Expand beyond human melee into movement, blocks, reactions, interactions, creatures, and other animation families as useful.
4. Evaluate the animation author's R/L hypothesis using both attack and stumble names.

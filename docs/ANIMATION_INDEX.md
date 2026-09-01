# Gothic 3 Animation Knowledge Index

**Status:** Cold/reference routing index  
**Updated:** 2026-09-01

## Purpose

Route animation questions to the smallest useful section or data source without loading the full animation reference/catalog.

Main authorities:

- `ANIMATION_RULES.md` — generalized engine-facing semantics;
- `ANIMATION_CATALOG.md` — concrete families, exact assets, author observations and controlled fixtures;
- `data/animation_names/all_animation_names.txt` — complete native name inventory (5,991 unique names);
- `data/animation_names/author_grouped_attacks_and_stumbles.txt` — author-grouped exact names/notes.

Runtime behavior claims remain evidence-bounded. Filename structure is valuable, but native action/phase/source semantics take precedence when the engine exposes them.

---

## 1. Quick Routing by Question

| Question | Start here |
|---|---|
| How is an animation filename structured? | `ANIMATION_RULES.md` §2 |
| Does `Hero` mean player-only? | `ANIMATION_RULES.md` §3 |
| What are the `gEAniState` values / Wade/Swim/etc.? | `ANIMATION_RULES.md` §4 |
| Which filename token is left/right animation UseType? | `ANIMATION_RULES.md` §5 |
| How does raw `gEUseType` map to animation tokens? | `ANIMATION_RULES.md` §6 |
| What does P0/P1/P10/etc. mean? | `ANIMATION_RULES.md` §7, §14, §17 |
| Which `gEAction` values matter for combat? | `ANIMATION_RULES.md` §8 |
| Why can a `WhirlAttack` filename be SimpleWhirl? | `ANIMATION_RULES.md` §8.1; `ANIMATION_CATALOG.md` §7 |
| What are the phase values? | `ANIMATION_RULES.md` §9 |
| What do N/O/I animation-type tokens mean? | `ANIMATION_RULES.md` §10 |
| What does direction Fwd/Back/Left/Right mean? | `ANIMATION_RULES.md` §11 |
| What is `_00_%_00_`? | `ANIMATION_RULES.md` §12 — unknown/opaque |
| What does destination pose do? | `ANIMATION_RULES.md` §13 |
| How should composite poses be handled? | `ANIMATION_RULES.md` §14 |
| What is the numeric CombatMove distance suffix? | `ANIMATION_RULES.md` §15 |
| What does final `L/R` mean? | `ANIMATION_RULES.md` §16 |
| Does final `L/R` choose collision hand? | **No**; `ANIMATION_RULES.md` §16 / EV-059 |
| What are common human melee pose chains? | `ANIMATION_RULES.md` §17 |
| How do movement Walk/Run/Sprint resource sets relate? | `ANIMATION_RULES.md` §18 |
| Does frame 0–12 mean 12 or 13 samples? | `ANIMATION_RULES.md` §19 |
| How should collision markers be authored? | `ANIMATION_RULES.md` §20 |
| When should runtime code use filename vs native values? | `ANIMATION_RULES.md` §21 |
| Which families have Raise files / missing Raises? | `ANIMATION_CATALOG.md` §5 |
| Which exact attacks have known LEFT-source annotations? | `ANIMATION_CATALOG.md` §6 |
| Which Dual attacks have multiple weapon contacts? | `ANIMATION_CATALOG.md` §7 |
| Which custom Quick Recover files exist? | `ANIMATION_CATALOG.md` §8 |
| Which assets may be unused/unimplemented? | `ANIMATION_CATALOG.md` §9 |
| What did the R/L + stumble inventory analysis show? | `ANIMATION_CATALOG.md` §10 |
| What exact Fist contact fixture was tested? | `ANIMATION_CATALOG.md` §11 |
| What exact multi-target/double-contact marker fixtures were used? | `ANIMATION_CATALOG.md` §12 |
| I only need to know whether an exact filename exists | search `data/animation_names/all_animation_names.txt` |
| I need the author's exact grouped notes/names | search `data/animation_names/author_grouped_attacks_and_stumbles.txt` |

---

## 2. Filename Field Map

Canonical example:

```text
Demon_Stand_None_2H_P1_Attack_Hit_N_Fwd_00_%_00_P0_150_L
```

Search route by field:

```text
family/actor                 -> ANIMATION_RULES §3
AniState                     -> §4
left/right animation UseType -> §5–§6
source/current pose          -> §7
Action                       -> §8
Phase                        -> §9
N/O/I type                   -> §10
Direction                    -> §11
00_%_00 metadata             -> §12
next/destination pose        -> §13–§14
CombatMove distance          -> §15
final side/direction token   -> §16
```

Do not reconstruct behavior by parsing all fields when native state exposes stronger authority.

---

## 3. UseType Normalization Search Terms

Raw item UseType and serialized animation category are not always identical.

Important non-1:1 examples:

```text
Axe / Pickaxe     -> 2H
Halberd / Rake / Shovel / Broom / Fan -> Staff
PhysicalFist      -> Fist
Plant             -> Bread
Bottle            -> Potion
Map / Book        -> Letter
Lockpick          -> Key
```

The full table lives in `ANIMATION_RULES.md` §6.

Use this mapping for semantic animation-profile matching; do not blindly use raw enum spelling as the filename category.

---

## 4. Human Melee Family Routing

### 1H

Catalog coverage includes:

- Normal forward/right/left;
- Quick;
- Power;
- Parade Pierce/Finishing;
- GetUp;
- selected stumble families.

Use catalog §4–§6 and the raw grouped source for exact assets.

### Torch + 1H

Important because physical collision source can differ from ordinary right-hand assumptions.

Use:

- catalog §5 Raise availability;
- catalog §6 Torch Quick left-source annotations;
- EV-051–EV-053 for source evidence.

### Shield + 1H

Use catalog §4–§5 and exact filename data. No-Recover Quick lifecycle evidence is separate from asset existence; see EV-154/EV-161.

### 2H

Important routes:

- Normal/Quick Raise assets: catalog §5;
- full Whirl/Finishing: catalog §7;
- multi-contact fixtures: catalog §12;
- normal P0/P1 pose pattern: rules §17.

### Staff

Structurally close to 2H for many melee animations, but source/runtime behavior must still be evidence-backed.

Use catalog §5/§7 plus evidence for full-Whirl cleanup edge.

### Dual / 1H+1H

Important routes:

- exact physical source map: catalog §6;
- multiple weapon contacts / Power / SimpleWhirl: catalog §7;
- final marker-source fixtures: catalog §12;
- R/L is not collision-hand authority: rules §16 / EV-059.

---

## 5. Action-Family Mismatches to Remember

### QuickAttackR / QuickAttackL

These distinguish logical action/direction variants. They do **not** select the physical right/left damage source.

### Dual SimpleWhirl

Dual uses native `gEAction_SimpleWhirl` / `OnAI_SimpleWhirl`, but serialized Hit files contain the token `WhirlAttack`.

### Hack vs Finishing

The same serialized 2H `FinishingAttack` asset family has been observed under both runtime `gEAction_HackAttack` and `gEAction_FinishingAttack`, reaching different native cleanup paths.

Conclusion:

> animation filename = asset identity/serialized contract; runtime action = behavior authority when established.

---

## 6. Collision Marker Authoring Routing

Frozen equipped-slot commands:

```text
G3AB_COL_RIGHT
G3AB_COL_LEFT
G3AB_COL_BOTH
G3AB_COL_OFF
```

Semantics:

```text
RIGHT -> {RIGHT}
LEFT  -> {LEFT}
BOTH  -> {RIGHT, LEFT}
OFF   -> {}
```

Detailed authoring rules: `ANIMATION_RULES.md` §20.

Important distinctions:

- RIGHT/LEFT = equipped slots, not final filename R/L;
- repeated source command later in the Hit = new authored contact/rearm;
- OFF = deliberate inactive gap, not mandatory terminal cleanup;
- marker timing is per animation;
- current authoring preference often places collision one authored frame before visual contact, but this is not an engine hardcode.

---

## 7. Exact Asset Search Strategy

When the question is “does this exact animation exist?” or “what variants exist?” do **not** read the catalog first.

Use:

```text
data/animation_names/all_animation_names.txt
```

Useful query fragments:

```text
Hero_Stand_None_2H
QuickAttackR_Hit
WhirlAttack_Raise
FinishingAttack_Hit
GetUpAttack
_Wade_
_Jump_
_Move_Run_
```

Then open the catalog/rules only if interpretation is needed.

For author-curated grouping and notes use:

```text
data/animation_names/author_grouped_attacks_and_stumbles.txt
```

---

## 8. Evidence Routing for Animation Claims

| Claim family | Evidence route |
|---|---|
| Hero is not player-only | EV-036 + NPC marker evidence |
| composite poses are meaningful | EV-037–EV-038 |
| final R/L is not collision hand | EV-039, EV-059, EV-060–EV-063 |
| raw UseType normalization is required | EV-042 |
| LightStumble enum/name mismatch | EV-065 |
| Dual native source map | EV-090–EV-094 |
| final marker vocabulary | EV-143–EV-144 |
| Whirl filename/action mismatch | EV-145, EV-164 |
| no-Recover asset vs lifecycle cleanup | EV-154, EV-161 |

Use `EVIDENCE_INDEX.md` for broader routing.

---

## 9. Maintenance Rule

When new animation knowledge matters:

1. put exact bulk filenames in the data lists;
2. put generalized naming/engine semantics in `ANIMATION_RULES.md`;
3. put concrete family/asset observations and useful fixtures in `ANIMATION_CATALOG.md`;
4. put controlled runtime/source claims in the Evidence Ledger;
5. update this index only when a new route/search term would materially improve retrieval.

Do not copy the same animation history into Design, Source Guide, Evidence Index, and Catalog. Historical chronology belongs behind the exact EV/provenance route and Git history when needed.

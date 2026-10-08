# Gothic 3 Animation Knowledge Index

**Status:** Cold/reference routing index  
**Updated:** 2026-10-07

## Purpose

Route animation questions to the smallest useful owner without loading the full catalog or evidence history.

Main authorities:

- `ANIMATION_RULES.md` — generalized engine-facing naming/authoring semantics;
- `ANIMATION_CATALOG.md` — concrete families, exact assets, fixtures, author observations;
- `data/animation_names/all_animation_names.txt` — complete native name inventory;
- `data/animation_names/user_created_tested_animation_names.txt` — exact user-authored names admitted only after runtime selection/playback is proven;
- `data/animation_names/author_grouped_attacks_and_stumbles.txt` — author-grouped exact names/notes.

Runtime claims remain evidence-bounded; native action/phase/source semantics outrank filename inference.

---

## 1. Quick Routing

| Question | Start here |
|---|---|
| filename structure / poses / final R/L | `ANIMATION_RULES.md` §§2, 6 |
| Hero player-only? | `ANIMATION_RULES.md` §3 |
| raw UseType -> animation category | `ANIMATION_RULES.md` §4 |
| Fist vs PhysicalFist normalization | `ANIMATION_RULES.md` §4; collision mechanism distinction §§10–11 |
| combat action / phase values | `ANIMATION_RULES.md` §5 |
| player LMB/RMB input -> attack family | `ANIMATION_RULES.md` §5 |
| Dual SimpleWhirl filename/action mismatch | `ANIMATION_RULES.md` §§5, 7; `ANIMATION_CATALOG.md` §6 |
| frame 0–N sampled-frame convention | `ANIMATION_RULES.md` §8 |
| equipped collision marker authoring | `ANIMATION_RULES.md` §9 |
| raw8 FIST marker authoring | `ANIMATION_RULES.md` §10 |
| may I use FIST on raw55/PhysicalFist animations? | Yes, within the proven raw55 contract; `ANIMATION_RULES.md` §10; `COLLISION_REFERENCE.md` §4.2 |
| supported family/native eligibility restrictions | `ANIMATION_RULES.md` §11; `EVIDENCE_INDEX.md` |
| exact native asset exists? | search `data/animation_names/all_animation_names.txt` |
| exact user-authored + runtime-tested asset exists? | search `data/animation_names/user_created_tested_animation_names.txt` |
| author-curated exact notes | `data/animation_names/author_grouped_attacks_and_stumbles.txt` |
| Raise availability / concrete human families | `ANIMATION_CATALOG.md` |
| exact historical Fist body-contact fixture | `ANIMATION_CATALOG.md` §10; production result is EV-240 |

---

## 2. Important UseType Normalization

```text
Axe / Pickaxe                          -> 2H
Halberd / Rake / Shovel / Broom / Fan -> Staff
PhysicalFist                           -> Fist
Plant                                  -> Bread
Bottle                                 -> Potion
Map / Book                             -> Letter
Lockpick                               -> Key
```

`PhysicalFist -> Fist` is an **animation-token mapping only**. Both raw8 Fist and raw55 PhysicalFist now have production `FIST` behavior, but runtime source identity selects two different mechanisms; never infer the mechanism from the serialized token alone.

---

## 3. Human Melee Family Routing

### 1H / Torch+1H / Shield+1H

Use `ANIMATION_CATALOG.md` for exact assets and known Raise/source exceptions. Torch+1H remains important because physical source can differ from ordinary right-hand assumptions.

### 2H / Staff

Use catalog Raise/full-Whirl/Hack assets plus evidence routing for lifecycle and marker behavior.

### Dual

Use catalog/evidence for exact physical source map, Power, SimpleWhirl and repeated contacts. QuickAttackR/L and final filename R/L are not collision-hand selectors.

### Human Fist

Use `ANIMATION_RULES.md` §10 for current authoring. Current raw8 mechanism is `COLLISION_REFERENCE.md` §4.1; foundations EV-221–EV-251 and persistent-opportunity acceptance EV-346–EV-364.

### PhysicalFist / raw55

A production authoring contract is now established for factual current RIGHT PhysicalFist/raw55 in supported Normal, Quick, true Power and Sprint-origin executions. Use `ANIMATION_RULES.md` §10 for marker rules and `COLLISION_REFERENCE.md` for current mechanism limits. Do not infer raw55 from the serialized `Fist` token alone.

---

## 4. Action-Family Mismatches

- QuickAttackR/L identify action variants, not physical right/left damage source.
- Dual SimpleWhirl uses native `gEAction_SimpleWhirl` while exact Hit assets serialize `WhirlAttack`.
- Hack action 14 and true Finishing action 15 may reference related asset naming, but runtime action remains the behavior authority.

---

## 5. Collision Marker Routing

### Equipped

```text
RIGHT -> {RIGHT}
LEFT  -> {LEFT}
BOTH  -> {RIGHT, LEFT}
OFF   -> {}
```

### Raw8 Fist

```text
FIST -> open/refresh one pending native raw8 contact opportunity; exact contact consumes, not visible damage
```

There is no production `FIST_OFF`.

Important distinctions:

- RIGHT/LEFT = equipped slots;
- repeated equipped markers rearm contact through `ClearTriggeredList()`;
- OFF = equipped inactive gap, not terminal cleanup;
- FIST is not an equipped source set and has no weapon ClearTriggeredList meaning;
- raw55/PhysicalFist uses `FIST` under its separate proven production contract; do not apply raw8 latch semantics or equipped-source semantics to it.

Detailed rules: `ANIMATION_RULES.md` §§9–11.

---

## 6. Current Collision Evidence Routes

| Claim | Evidence |
|---|---|
| final equipped RIGHT/LEFT/BOTH/OFF vocabulary | EV-143–EV-144 |
| generation-scoped marker bookkeeping | EV-213–EV-214 |
| Power marker/source/lifecycle closure | EV-241 |
| Pierce closure + bounded compatibility control | EV-242 |
| SimpleWhirl target/StatePosition closure | EV-217–EV-220, EV-243 |
| Hack callback identity | EV-216 |
| Hack tested 2H/Staff marker/source closure | EV-244 |
| production human raw-8 Fist | EV-221–EV-240 |
| persistent-opportunity raw8 acceptance | EV-346–EV-364, EV-377, EV-389–EV-390 |
| permanent raw55 PhysicalFist acceptance / final explicit Sprint gates | EV-262–EV-298, EV-382, EV-385–EV-390 |

Use `EVIDENCE_INDEX.md` for exact routing/provenance.

---

## 7. Maintenance Rule

- generalized animation semantics -> `ANIMATION_RULES.md`;
- concrete asset/family observations -> `ANIMATION_CATALOG.md`;
- controlled runtime/source facts -> Evidence Ledger;
- native bulk exact names -> `all_animation_names.txt`;
- user-authored exact names -> `user_created_tested_animation_names.txt` only after runtime proof;
- this index changes only when retrieval materially improves.

Do not copy experiment chronology into animation authorities.

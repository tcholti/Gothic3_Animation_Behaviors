# Gothic 3 Animation Catalog

**Status:** Curated working catalog  
**Updated:** 2026-09-08  
**Scope:** Human melee families, exact high-value assets/fixtures, and author observations

## 1. Purpose / Sources

This catalog records concrete animation families, exact examples, author observations, and controlled fixtures. Generalized engine/authoring rules belong in `ANIMATION_RULES.md`; runtime claims are bounded by the Evidence Ledger.

Primary exact-name sources:

```text
data/animation_names/all_animation_names.txt
    5,991 unique native animation names

data/animation_names/author_grouped_attacks_and_stumbles.txt
    author-grouped human attacks/stumbles and notes
```

Use those data files when exhaustive exact-name inventory matters; this catalog is intentionally curated.

---

## 2. Current Human Melee Coverage

| Family | Catalog focus |
|---|---|
| None + 1H | Normal, Quick, Power, Parade Pierce/Finishing, GetUp |
| Torch + 1H | same broad families; important left-source exceptions |
| Shield + 1H | Normal, Quick, Power, Parade Pierce/Finishing, GetUp |
| None + 2H | Normal, Quick, Power, full Whirl/Finishing, Hack, GetUp |
| None + Staff | Normal, Quick, Power, full Whirl/Finishing, Hack, GetUp |
| 1H + 1H | Normal, Quick, Power, SimpleWhirl, Pierce/Finishing, GetUp |
| Human Fist | body-contact fixtures + final Normal/Power production acceptance |

This remains a human-melee-first catalog, not a complete creature/monster inventory.

---

## 3. Raise Availability

Current authoring observations:

```text
1H Normal                 Raise assets exist but do not work natively -> future custom Raise
1H Quick                  Raise assets absent -> must be authored
Torch+1H Normal/Quick     same broad custom-Raise need
Shield+1H Normal/Quick    same broad custom-Raise need
2H Normal                 custom insertion already proven
2H Quick                  Raise exists but does not work natively -> custom target
Staff Normal/Quick        same broad problem as 2H
2H/Staff full Whirl       tested native path entered Hit without playing corresponding Raise
Dual Normal/Quick         many Raises absent/nonfunctional -> future authored/custom Raise
Power/Pierce families     native Raise generally preserved where already working
```

Raise remains separate from collision behavior.

---

## 4. Physical Source Notes

### Torch + 1H Quick

Author notes and runtime evidence include left-hand damage-source cases. Therefore Torch+1H must not inherit a blanket right-hand assumption.

### Dual native source map — high-value examples

```text
P0 Normal forward -> LEFT
P1 Normal forward -> RIGHT
P0 Quick R/L      -> RIGHT
P1 Quick R/L      -> LEFT
P0 Pierce         -> RIGHT
P1 Pierce         -> LEFT
P0/P1 Power       -> RIGHT + LEFT
```

Exact runtime names remain in the grouped source/data and EV-090–EV-094 / later family evidence.

QuickAttackR/L and final filename R/L are not physical collision-hand selectors.

---

## 5. Dual Power / Repeated Contacts

Native Dual Power visually contains multiple weapon contacts:

```text
P0 visual order: right -> left -> right
P1 visual order: left -> right -> left
```

Production marker architecture now supports exact RIGHT/LEFT/BOTH/OFF source sets and repeated authored rearm. Power equipped marker/source/lifecycle expansion is CLOSED/PASS in EV-241.

Preserve native Power target/contact sensitivity; a visually plausible native Power swing can still fail to damage because of Gothic's downstream eligibility/contact behavior.

---

## 6. Dual SimpleWhirl

Dual uses native `gEAction_SimpleWhirl` even though exact Hit/Recover resources serialize `WhirlAttack`.

High-value resources include:

```text
Hero_Stand_1H_1H_P0_WhirlAttack_Hit_N_Fwd_00_%_00_P1_100_L
Hero_Stand_1H_1H_P1_WhirlAttack_Hit_N_Fwd_00_%_00_P0_100_R
```

The physical marker/source layer is now closed: authored BOTH can activate/rearm both exact equipped sources and later clean them naturally.

Native character-hit eligibility is a separate action-specific layer. Current bounded conclusion:

```text
SimpleWhirl is substantially selected-target-centered
but not strictly selected-target-only;
some nearby/intervening actors can become eligible.
```

A temporary StatePosition `1 -> 2` probe did not make SimpleWhirl Power-like. Final StatePosition remains `1`. See EV-217–EV-220 and EV-243.

Do not treat a failure to damage every actor visually crossed by a blade as proof that the physical source failed to activate.

---

## 7. Full Whirl / Hack / Finishing

- full Whirl exists for 2H and Staff and is selected by the full-Whirl action path;
- ordinary 1H has no equivalent full-Whirl family in current human melee coverage;
- true `FinishingAttack(15)` remains native and is deliberately outside ordinary marker treatment;
- `HackAttack(14)` is now runtime-proven for tested 2H/Staff routing/source/marker behavior rather than merely a filename hypothesis.

Hack optional asset routing is narrow: when runtime action is HackAttack and the ordinary resolved name contains `_FinishingAttack_`, a matching `_HackAttack_` resource may substitute only if that candidate exists. True Finishing remains untouched.

Evidence: EV-216 callback identity; EV-244 actual tested 2H/Staff Hack behavior.

---

## 8. Custom Recover / Uncertain Assets

The author-created Quick Recover files and possibly unused PowerAttack-loop / P1 Whirl/Finishing / Dual P3 Quick assets remain preserved in the exact grouped data file.

Do not promote file existence to runtime selection without evidence.

No-Recover asset presence/absence also does not define collision cleanup; lifecycle authority is separate.

---

## 9. Final R/L Interpretation

Inventory strongly correlates QuickAttackR/QuickAttackL and directional Normal names with final R/L tokens, but current project interpretation remains:

> final R/L is logical attack/hit-direction metadata, not physical collision-source authority.

Exact causal relationship to victim StumbleR/L remains unnecessary for current collision behavior.

---

## 10. Historical Human Fist Body-Contact Fixture

Early v0.9 fixture used:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R
Hero_Stand_None_Fist_P1_Attack_Recover_N_Fwd_00_%_00_P1_0_R
```

Controlled contact variants established successful human raw-8 damage through:

```text
left hand
right hand
left leg
right leg
head
```

The right-leg fixture accidentally placed collision at frame 2 rather than the common planned frame 3; treat that as authoring error, not engine timing law.

Those early tests used historical prototype operations including triggered-list clearing. **Do not infer current production Fist architecture from the old fixture implementation.** The surviving factual result is body-contact capability, not weapon-style source semantics.

Do not claim every body part, `PhysicalFist`, or monster body is proven from this fixture.

---

## 11. Production Human Fist Acceptance Fixture

Final production acceptance used the controlled Golem setup with frame-12-only `FIST` on P0 Normal and P0 Power double-swing fixtures.

```text
3 x Normal
3 x Power
visual result all six:
    first swing  = NO damage
    second swing = YES damage
```

Engine-side all six:

```text
marked-execution initial close SPU+0x164: 0 -> 1
frame-12 FIST rearm:                         1 -> 0
real play time already above native threshold
no synthetic timing permission armed
zero pre-marker Game+0x16E348 damage events
exactly one post-marker Hero raw-8 Fist -> Golem +0x16E348 event
```

Canonical result: EV-240.  
Archived log:

```text
research/archive/2026-09-07_fist_production_frame12_normal_power_acceptance.log
```

Current production authoring is `FIST` only; no authored FIST_OFF.

---

## 12. PhysicalFist / Monster Status

`gEUseType_PhysicalFist` / raw 55 normalizes to the serialized animation token `Fist`, but no production collision mechanism is yet claimed.

Transformed animal/monster forms are the preferred next controlled discovery fixtures. Until that work is interpreted:

```text
NO assumption raw55 == human raw8
NO monster FIST authoring contract
NO per-limb/body marker vocabulary
```

Route the active discovery contract through `DESIGN.md` / `COLLISION_TEST_PLAN.md`.

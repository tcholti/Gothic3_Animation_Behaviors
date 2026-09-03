# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-03

## Current bridge — SimpleWhirl character-hit semantics

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and follow its bootstrap. If the previous Chat failed or hit maximum context, use POP-11 before trusting stale `NEXT` wording.

CAM is the constitutional collaboration layer; `docs/README.md` is the highest Gothic-specific project charter beneath CAM. Do not modify CAM from Gothic 3 work.

---

## Closed / protected boundary

```text
collision architecture verification             COMPLETE — EV-206–EV-215
Hack callback runtime identity                  CLOSED — EV-216
Power marker adapter validation                 CLOSED/PASS
Pierce marker adapter validation                CLOSED/PASS
SimpleWhirl physical marker/source mechanics    PASS — current evidence
```

Do not reopen C1 lifecycle/generation architecture, Power, Pierce, or the SimpleWhirl physical source mechanics without contradicting evidence.

Branch lifecycle remains:

```text
complete collision on docs/collision-source-evidence
→ migrate mature collision behavior into Script_G3AnimationBehaviors
→ validate diagnostics-free collision integration
→ promote completed collision checkpoint to main
→ create feature/raise-attack-speed from updated main
```

Do not create `feature/raise-attack-speed` early.

---

## Implemented remaining-melee batch

Implementation:

`f0d929c90fbe086f44f66f91a2523904d06c3903`

Generic marker StatePosition diagnostics:

`7c31784c5ef86bc79b54d573144b8e40f33e5e6b`

Bookkeeping currently implemented:

```text
Power ordinary/non-Dual -> StatePosition 1
Power Dual              -> StatePosition 2
Pierce                   -> StatePosition 1
SimpleWhirl              -> StatePosition 1
Hack                     -> OnAI_HackAttack -> StatePosition 1
```

`GetUpAttack` is not part of the planned marker roadmap. `FinishingAttack` remains deliberately native/unmarked. Fist/body contact remains a separate later source-adapter responsibility.

---

## SimpleWhirl evidence recovered after failed previous Chat

Compact checkpoint:

`research/derived/2026-09-03_simplewhirl_validation_and_target_semantics_checkpoint.md`

Canonical raw evidence remains in `research/raw/` because the causal question is still open.

### Native adapter

`research/raw/2026-09-03_simplewhirl_native_marker_adapter_isolated_validation.log`  
commit `b11c2c8e7052e5bb2f9d09ce876395928df2ed1f`

Validated action-6 / `_AI_SimpleWhirl` marker ownership, native-callback suppression, accepted exact-source marker behavior, StatePosition `0 -> 1`, C1 generation bookkeeping, rearm and natural exact-source `7 -> 5` cleanup.

### BOTH physical source behavior

`research/raw/2026-09-03_simplewhirl_authored_both_source_validation.log`  
commit `1759083d55611b34185a66a835f118d3cfaa188c`

An accepted SimpleWhirl `G3AB_COL_BOTH` directly activated both exact Dual equipped sources `5 -> 7`, created both C1 obligations, rearmed both lists, kept `StatePositionAfterMarker: 1`, and naturally cleaned both sources `7 -> 5` without C1 repair.

Therefore the G3AB physical-source layer itself can make both weapons offensive in SimpleWhirl.

### Single-twin crash control

`research/raw/2026-09-03_simplewhirl_authored_both_single_twin_crash_control.log`  
commit `b417ea353e00379c0be9a38c5ce01dcfd3e2fa29`

The earlier crash run had more than one collision twin/module live, including a renamed `.dll.disabled` sibling. Correcting deployment to the intended single diagnostic twin preserved repeated healthy BOTH `5 -> 7 -> 5` behavior and did not reproduce the crash in the control run.

Current qualification:

> accidental co-loading is the strongest identified crash explanation and is strongly supported by the control, but is not claimed as a universally proven sole crash cause.

Do not investigate further unless a comparable crash recurs under verified single-twin deployment.

### Target-lock / swapped-motion probe

`research/raw/2026-09-03_simplewhirl_target_lock_and_swapped_motion_contact_probe.log`  
commit `b22eabd71c6dfffa45dee48e3a3b12c54569ef7f`

User observations:

- strict “selected target only” is false; unselected actors could sometimes be damaged;
- one initial swapped-motion observation appeared to show the two swords damaging two different actors in one execution;
- deliberate repetition did **not** reproduce that two-target result.

Do not promote the non-reproduced two-target observation as confirmed evidence.

### Same authored motion content: SimpleWhirl versus PowerAttack

`research/raw/2026-09-03_simplewhirl_vs_power_same_motion_target_semantics_comparison.log`  
commit `ee75fb8bcf8fe3e3aeb43e88d114b0ab3c221710`

Strongest current comparison:

```text
SimpleWhirl
Action 6 / _AI_SimpleWhirl
same Power-derived Dual motion content
same BOTH -> single -> OFF -> BOTH physical marker program
StatePositionAfterMarker = 1
both exact sources physically activated/rearmed as authored

true Dual Power
Action 2 / _AI_PowerAttack
same authored motion content class
same physical marker program behavior
StatePositionAfterMarker = 2
```

User observation with the matched motion content:

```text
true Power -> broad actor contacts from the swords can damage actors touched
SimpleWhirl -> substantially more target-directed; usually focused target, but not strictly focused-target-only
```

Safe current interpretation:

> **SimpleWhirl has action-specific character-hit eligibility that is substantially more target-directed than PowerAttack.**

The difference is not explained by animation geometry alone and not by failure of `G3AB_COL_BOTH` to activate both physical weapons. Exact native mechanism remains unknown.

---

## Current architecture distinction

```text
G3AB markers
= WHEN collision is offensive
+ WHICH equipped physical source set is offensive/rearmed

native/action-specific character-hit semantics
= which actor contacts are eligible to become character damage/effects for that action
```

SimpleWhirl physical source control is validated. Uniform actor-hit eligibility across action families is **not** yet established.

No release contract has been chosen yet between:

```text
normalize eligibility safely across supported families
OR preserve/document native family restrictions
OR normalize only evidence-supported families while preserving intentional special semantics elsewhere
```

---

## Exact immediate next test — temporary StatePosition control

StatePosition is the smallest visible causal candidate because SimpleWhirl remains `1` while true Dual Power uses `2`.

This is a **temporary diagnostic falsification**, not a design decision:

```text
keep unchanged:
  Action 6 / SimpleWhirl
  OnAI_SimpleWhirl
  same Power-derived Dual motion fixture
  same BOTH -> single -> OFF -> BOTH markers
  same source activation/rearm
  same target/group setup

change only:
  accepted SimpleWhirl marker bookkeeping StatePosition 1 -> 2
```

Interpretation:

```text
if actor-hit behavior becomes Power-like
→ StatePosition participates in deeper native eligibility
→ investigate legitimate semantic rule; do not generalize immediately

if behavior stays substantially target-directed
→ StatePosition is likely bookkeeping/suppression only
→ revert temporary change
→ trace Action 6 / SimpleWhirl-specific native hit-eligibility path
```

Do not move to Hack runtime validation until this SimpleWhirl causal question is resolved enough to define the intended framework guarantee.

Hack implementation remains present and pending isolated marker/routing validation afterward.

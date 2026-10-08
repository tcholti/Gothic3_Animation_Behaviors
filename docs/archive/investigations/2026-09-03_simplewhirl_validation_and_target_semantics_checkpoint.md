# SimpleWhirl Validation + Character-Hit Semantics Checkpoint

**Date:** 2026-09-03  
**Branch:** `docs/collision-source-evidence`  
**Status:** Physical marker/source behavior validated; native character-hit eligibility investigation OPEN  
**Purpose:** Compact retrieval checkpoint for the five committed SimpleWhirl runtime logs and the User observations needed to continue the current causal question. Raw logs remain canonical evidence; this file is a derived retrieval aid.

## Implementation baseline

- Remaining melee marker adapters + optional Hack routing: `f0d929c90fbe086f44f66f91a2523904d06c3903`
- Generic before/after-marker StatePosition diagnostics: `7c31784c5ef86bc79b54d573144b8e40f33e5e6b`

Current relevant bookkeeping:

```text
SimpleWhirl -> StatePosition 1
Dual Power  -> StatePosition 2
```

Do not interpret that difference causally yet. Prior Quick/full-Whirl work proved StatePosition matters for suppressing competing native timed activation/bookkeeping; it did not prove that StatePosition owns character-hit eligibility.

---

## Canonical raw evidence

### 1. Native SimpleWhirl adapter

`research/raw/2026-09-03_simplewhirl_native_marker_adapter_isolated_validation.log`  
commit `b11c2c8e7052e5bb2f9d09ce876395928df2ed1f`

Direct logger facts include:

```text
ScriptFunction: _AI_SimpleWhirl
Family: SIMPLE_WHIRL
Action: 6
accepted authored source marker
StatePositionBeforeMarker: 0
StatePositionAfterMarker: 1
valid C1 generation
exact selected source 5 -> 7
ClearTriggeredList rearm
natural exact-source cleanup 7 -> 5
C1 cleanup fulfilled
```

Result: the new SimpleWhirl callback/action adapter and StatePosition-1 bookkeeping work for the tested native-source marker path.

### 2. Authored BOTH source behavior

`research/raw/2026-09-03_simplewhirl_authored_both_source_validation.log`  
commit `1759083d55611b34185a66a835f118d3cfaa188c`

The log directly proves that an accepted SimpleWhirl `G3AB_COL_BOTH` resolves both equipped Dual sources and requests both exact sources `5 -> 7`, records two C1 offense obligations, clears/rearms both triggered lists, keeps `StatePositionAfterMarker: 1`, and later observes natural `7 -> 5` cleanup for both sources without C1 repair.

Therefore the G3AB physical source layer is capable of making both equipped weapons offensive during SimpleWhirl.

### 3. Single-twin crash control

`research/raw/2026-09-03_simplewhirl_authored_both_single_twin_crash_control.log`  
commit `b417ea353e00379c0be9a38c5ce01dcfd3e2fa29`

After the earlier crash run was found to have more than one collision twin/module live (including a renamed `.dll.disabled` sibling), the corrected deployment used the intended single diagnostic twin. Repeated SimpleWhirl BOTH executions then showed the same healthy two-source `5 -> 7 -> 5` behavior without reproducing the crash in the control run.

Bounded conclusion:

> Accidental co-loading of collision twins is the strongest identified explanation for the earlier crash and is strongly supported by the single-twin control, but one control does not prove it is the universal/sole possible crash cause.

Do not reopen crash investigation unless a comparable crash recurs with verified single-twin deployment.

### 4. Target-lock + swapped-motion contact probe

`research/raw/2026-09-03_simplewhirl_target_lock_and_swapped_motion_contact_probe.log`  
commit `b22eabd71c6dfffa45dee48e3a3b12c54569ef7f`

The logger continued to show healthy SimpleWhirl action-6 marker/source bookkeeping. The important additional evidence here is User observation:

- explicit target lock did **not** make SimpleWhirl strictly selected-target-only; nearby/unselected actors could sometimes still be damaged;
- after swapping the authored P0/P1 motion content while keeping the logical resource slots, one initial observation appeared to show two different targets being hit by the two swords in one execution;
- that two-target result **could not be reproduced on deliberate repetition**.

Therefore:

```text
strict "selected target only" model -> rejected by observation
"both swords can reliably damage two separate actors in SimpleWhirl" -> NOT established
```

The unstable two-target observation must not be promoted as confirmed evidence.

### 5. Same motion content: SimpleWhirl versus true PowerAttack

`research/raw/2026-09-03_simplewhirl_vs_power_same_motion_target_semantics_comparison.log`  
commit `ee75fb8bcf8fe3e3aeb43e88d114b0ab3c221710`

This is the strongest current causal comparison.

The User ran Dual PowerAttack animation content under SimpleWhirl and also performed true Dual PowerAttack using the same authored motion content in the same broader test context.

Direct logger facts establish that the SimpleWhirl executions remained:

```text
Action: 6
ScriptFunction: _AI_SimpleWhirl
same authored BOTH -> single -> OFF -> BOTH physical marker program
both exact equipped sources activated/rearmed as authored
StatePositionAfterMarker: 1
```

True Dual Power executions in the same log remained:

```text
Action: 2
ScriptFunction: _AI_PowerAttack
same class of Dual BOTH -> single -> OFF -> BOTH marker/source behavior
StatePositionAfterMarker: 2
```

User contact observation under the matched motion content:

```text
true PowerAttack
-> broad character contacts from the swords could damage actors touched by the motion

SimpleWhirl
-> substantially more target-directed
-> usually the selected/focused target was damaged
-> an unselected actor could still sometimes be damaged, especially when physically in/interfering with the path to the focused target
```

Safest current interpretation:

> **SimpleWhirl has action-specific character-hit eligibility that is substantially more target-directed than PowerAttack.**

Do **not** simplify this to “selected target only.”

Because the authored motion content and G3AB physical source activation can be held effectively constant while the action changes, the observed difference is not explained by animation geometry alone and is not explained by failure of `G3AB_COL_BOTH` to activate both physical weapons.

The exact native eligibility mechanism is still unknown.

---

## Current architecture distinction

The current evidence requires separating two responsibilities that were easy to conflate:

```text
G3AB marker/source layer
= WHEN an equipped source is offensive
+ WHICH equipped source set is physically offensive/rearmed

native/action-specific character-hit semantics
= which actor contacts are actually eligible to become character damage/effects under that action
```

For SimpleWhirl, the first layer is validated. The second layer remains intentionally open.

This distinction also matches the earlier Pierce result, where custom marker/source behavior did not erase native Pierce target/reaction semantics.

No final framework policy has been chosen yet. Before public release, the animator-facing marker guarantee must be explicit:

```text
A. normalize character-hit eligibility safely across supported families; OR
B. preserve native family restrictions and document that markers guarantee physical source control only; OR
C. normalize only evidence-supported families while deliberately preserving special native semantics in others.
```

Do not choose among A/B/C until the causal mechanism and safety consequences are understood.

---

## Next falsification — StatePosition causal control

StatePosition is the smallest currently visible causal candidate because the matched comparison keeps SimpleWhirl at `1` while true Dual Power uses `2`.

The next test is a **temporary diagnostic control**, not a design decision:

```text
keep:
  Action = 6 / SimpleWhirl
  OnAI_SimpleWhirl
  same Power-derived Dual motion fixture
  same BOTH -> single -> OFF -> BOTH markers
  same source activation/rearm behavior
  same target/group setup

change only for accepted SimpleWhirl marker bookkeeping:
  StatePosition 1 -> 2
```

Compare against the existing true Dual Power / StatePosition-2 behavior.

Interpretation:

```text
if SimpleWhirl becomes Power-like in broad character-hit eligibility
-> StatePosition participates in the deeper native eligibility semantics
-> investigate the legitimate family/marker bookkeeping rule from evidence
-> do not immediately generalize "BOTH means StatePosition 2"

if SimpleWhirl remains substantially target-directed
-> StatePosition is likely bookkeeping/suppression rather than the eligibility owner
-> revert the temporary diagnostic change
-> trace Action 6 / SimpleWhirl-specific native character-hit eligibility instead
```

Hack isolated marker/routing validation remains pending **after** this SimpleWhirl causal question is resolved enough to define the framework contract.

---

## Raw/archive status

All five SimpleWhirl logs remain in `research/raw/` intentionally. The current causal gate is unresolved, so archive migration is premature. This checkpoint is a retrieval aid only and does not replace those raw artifacts or the canonical EV entries.

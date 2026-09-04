# SimpleWhirl StatePosition + Character-Hit Semantics Closure

**Date:** 2026-09-04  
**Branch:** `docs/collision-source-evidence`  
**Status:** CLOSED for the current equipped-melee marker stage  
**Purpose:** Preserve the completed SimpleWhirl causal result and the qualified target-contact observations without claiming an exact native eligibility algorithm.

## Closed physical marker/source responsibility

The existing SimpleWhirl marker/source implementation remains validated for the tested fixtures:

```text
Action 6 / _AI_SimpleWhirl ownership works
RIGHT / LEFT / BOTH / OFF exact-set marker behavior works
BOTH activates and rearms both exact Dual equipped weapon sources
both swords can connect against the selected target
natural exact-source cleanup returns live weapon sources to Item_Equipped
C1 generation / occurrence / replay protections remain healthy
```

Canonical prior checkpoint:

`research/derived/2026-09-03_simplewhirl_validation_and_target_semantics_checkpoint.md`

## StatePosition-2 causal probe

Temporary implementation:

`a48449fcd9e2514a6d1c1f9943eb04004a5778f3` — `Add temporary SimpleWhirl StatePosition causal probe`

The probe changed only accepted SimpleWhirl marker bookkeeping:

```text
SimpleWhirl StatePosition 1 -> 2
```

The authoritative runtime artifact is:

`research/raw/2026-09-04_simplewhirl_stateposition2_causal_probe.log`  
commit `ed40a6d901efc4bb30800e170bc850857d8f6dda`

The logger confirmed the test variable was active: accepted SimpleWhirl markers reported `StatePositionAfterMarker: 2` while the same physical marker program remained healthy.

User runtime observation:

- SimpleWhirl remained substantially target-directed;
- occasional non-selected hits still occurred;
- overall actor-hit behavior felt materially the same as before the StatePosition change.

Conclusion:

> **StatePosition 2 is rejected as a sufficient explanation or normalization for the observed SimpleWhirl-vs-Power character-hit difference.**

This does not imply StatePosition has no other bookkeeping or native suppression role.

## Restored native regression

The temporary probe was reverted by:

`9120ca32466b257722a4fe553f64063f331249b4`

Final accepted bookkeeping is therefore restored:

```text
SimpleWhirl -> StatePosition 1
```

Final regression artifact:

`research/raw/2026-09-04_simplewhirl_native_stateposition1_final_regression.log`  
commit `003c4c5c4baaa72401f6743c408f14db476b8887`

The final logger run again showed healthy `BOTH -> single -> OFF -> BOTH` marker/source behavior with `StatePositionAfterMarker: 1`, valid C1 generations, normal occurrence/replay protection and no observed C1 repair requirement or generation inconsistency.

The User confirmed that both swords could connect against the same selected target.

## Qualified non-selected-target observation

Non-selected actors were also damaged in several repetitions. The repeated visual pattern was:

- secondary targets that were hit were roughly beside or in front of the selected target, or otherwise spatially associated with the line toward that target;
- in one deliberate setup, the User locked one target and placed other actors between the Hero and that selected target; one or two of those intervening actors were hit.

Safe interpretation:

> **SimpleWhirl is substantially selected-target-centered but not strictly selected-target-only; some nearby/intervening actors can become eligible.**

Do **not** promote this observation into a proven cone, corridor, ordering rule, between-target classifier, or exact native geometry. The exact native character-hit eligibility mechanism remains unknown.

## Current framework decision

For the current collision scope:

```text
G3AB SimpleWhirl markers
= control WHEN authored collision is offensive
+ WHICH equipped physical source set is active/rearmed

Gothic SimpleWhirl semantics
= retain the native substantially target-directed actor-hit eligibility
```

The cost/reward decision is to stop the deeper SimpleWhirl eligibility investigation here. The marker/source feature works as intended, and the remaining action-specific restriction does not justify deeper reverse engineering or additional engine-facing code for the present framework goal.

This is a scope decision, not a claim that the native rule is immutable or uninteresting. If future target-acquisition or action-specific hit-semantics work needs to revisit the rule, start from this closure plus the September 3 checkpoint and raw evidence rather than rediscovering the physical marker/source layer.

## Next responsibility

```text
HackAttack isolated marker/routing validation
-> combined remaining-melee marker/lifecycle regression
```

Do not reopen Power, Pierce, SimpleWhirl physical-source behavior, C1 lifecycle architecture or Gate-4 execution identity without concrete contradicting evidence.

# Gothic 3 Animation Behaviors — Evidence Ledger EV-380 Onward

**Status:** Active evidence/provenance ledger  
**Opened:** 2026-09-26

## Purpose

Record evidence after the closed EV-373–EV-379 New Balance compatibility volume.

This ledger is proof history, not the normal knowledge interface. Current established collision facts belong in `COLLISION_REFERENCE.md` and owning architecture/reference documents.

## Entry format

```text
### EV-xxx — short factual title

Observed:
- direct factual result(s)

Scope / limits:
- exact actor/action/source/build/test limits
- explicit non-claims when important

Provenance:
- source/log/commit/hash/path as applicable

Disposition:
- PASS / FAIL / NEGATIVE CONTROL / INCONCLUSIVE / SUPERSEDED
```

## Entries

### EV-380 — New Balance raw55 Sprint second-FIST timing envelope mapped; frame8 straddles Action9→Action2 transition

Observed:
- The User published three BlackTroll raw55 double-FIST timing fixtures under the same current New Balance environment: markers at frames `1+3`, `1+8`, and `1+15`.
- In the `1+3` run, every reviewed Sprint-origin marker1 is already factual `Action9 / SPRINT / StatePosition2` around `StateTime ~= 1.90` and is accepted/open. Marker2 around `StateTime ~= 1.95` remains `Action9 / SPRINT / SP2`, RIGHT is already group7, and the current Sprint-origin second-FIST predicate rejects it. Moving marker2 almost immediately after marker1 therefore does not expose Sprint/SP1; the tested Hit motion is already at SP2 by frame1.
- The `1+8` run straddles the factual transition. Most reviewed executions have marker1 at `SPRINT/SP2` and marker2 at `POWER/SP2`, where marker2 is accepted with `ClearTriggeredList=1` and no second physical opening. At least one execution (C1=103) has the same frame8 marker2 still at `SPRINT/SP2`, where it is rejected. Thus identical authored timing can land on either side of the native Action9→Action2 transition.
- The `1+15` run consistently places reviewed marker2 after the transition at `POWER/SP2`; those markers are accepted as clear-only rearm. The full `1+15` log contains no `CORE MARKER ANOMALY / DISCOVERY` record.
- The timing sweep therefore establishes the tested legitimate Sprint-origin second-FIST state envelope as including current `SPRINT/Action9/SP2` and current `POWER/Action2/SP2`. No Sprint/SP1 second FIST was observed, and the deliberate earliest practical frame1/3 probe could not reach it.
- Incidental evidence from the early-marker fixtures exposes a separate Normal raw55 authoring-boundary question: very early Normal marker2 can arrive at `NORMAL/SP0` and is rejected by the current Normal second-FIST SP1 gate. Reviewed Quick traffic demonstrates that early repeated raw55 FIST rearm can occur at Quick/SP0. This finding is not part of the Sprint correction and does not authorize a Normal change.
- The User additionally reports that sheathing the player's weapon immediately before a Troll Sprint sometimes appears to reduce the number of contacts that land. Current logs do not prove marker failure: accepted marker opportunities do not guarantee native contact/damage, and separate Normal/Quick examples produce `ONDAMAGE` while the player motion is `HoldRight_End`. The sheath effect therefore remains an open downstream native-contact/target-state question requiring controlled marked-vs-unmarked A/B evidence.

Scope / limits:
- This is a state-mapping result for the tested BlackTroll/New Balance/raw55 Sprint route. It does not prove every species or external speed environment produces identical transition timing.
- The smallest evidence-backed Sprint second-FIST extension is asymmetric: preserve existing current-Power explicit `{SP1,SP2}` acceptance and additionally admit current-Sprint **SP2 only** for the same exact immutable Sprint-origin execution. Evidence does not justify current-Sprint SP1 acceptance or generic `>=1`.
- No production source was changed by this evidence batch.
- The Normal/SP0 discovery is deliberately separated for future causal research because the project's animator-authored-timing principle makes the reason for that restriction important, but native prerequisite vs historical guard is not yet established.
- The sheath observation must not be solved by custom damage or marker widening without proving whether the same effect exists in unmarked/native Sprint.

Provenance:
- current Sprint-first compatibility source: `ce59e5a2bad564652eaba970e959bdef0b479d82` plus later documentation-only lineage;
- diagnostic built/live SHA256 from EV-379/current deployment: `490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C`;
- timing-sweep upload commit: `58e32ae8599dc3a4c6a902a794e678f38172ef72`;
- `1+3`: `research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_3.log`, Git blob `cf0bd2e8883658697f66f4d2c0e5e2833b454289`;
- `1+8`: `research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_8.log`, Git blob `0b66fa4f17ec0909fa1f173a7fac9fdb4c30b070`;
- `1+15`: `research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_15.log`, Git blob `c9a199d6acea5dd303d8d0eaff3f44411123668f`.

Disposition:
- **PASS — SPRINT SECOND-FIST FACTUAL STATE ENVELOPE MAPPED FOR THE TESTED TIMING RANGE.**
- **IMPLEMENTATION BASIS READY:** current Sprint/SP2 is a legitimate second-FIST state; current Power/SP1+SP2 remains preserved; Sprint/SP1 remains unproven and must not be added generically.
- Keep the immediate comparison logs in `research/raw/` only while the sheath/native-contact control remains open; archive them under POP-06 when that controlled comparison closes.
- Before final Sprint acceptance, run a controlled sheath/no-sheath comparison and an unmarked/native Sprint control if the observed missing-contact behavior persists.

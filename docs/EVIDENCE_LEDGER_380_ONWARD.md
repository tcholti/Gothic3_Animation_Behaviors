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

### EV-381 — New Balance raw55 Sprint second-FIST SP2 correction runtime PASS; native-contact misses separated from marker ownership

Observed:
- The User built and deployed the reviewed Sprint second-FIST correction from the current branch. Built and live diagnostic SHA256 matched exactly: `B4161D74DD849F4B7B67D9ACCFC42A8D8784F7EF19FB968F2E44D67ED57BD689`.
- The `1+3` fixture directly retests the exact EV-380 failure. Repeated Sprint-origin executions show marker1 at factual `SPRINT / Action9 / SP2` accepted with exact RIGHT raw55 `5 -> 7`; marker2 remains factual `SPRINT / Action9 / SP2`, is now accepted, performs `ClearTriggeredList=1`, requests no second physical opening, and leaves RIGHT at group7 until native cleanup. Representative C1=68 and C1=114 both show `AcceptedFistCount=2`, `GroupRequested=0`, `ClearTriggeredList=1` on marker2.
- No Sprint-family `CORE MARKER ANOMALY / DISCOVERY` was found in the corrected `1+3` log. The anomaly traffic in that deliberately early fixture is the already-separated Normal/SP0 second-marker question.
- The corrected `1+8` fixture preserves the transition continuation route. Reviewed Sprint executions have marker1 at `SPRINT/SP2` accepted/open and marker2 at `POWER/SP2` accepted as clear-only rearm. EV-380 already proved the same authored frame8 marker can also remain `SPRINT/SP2`; the corrected `1+3` run directly proves that newly added arm. Together the evidence covers both factual sides of the frame8 transition race.
- The corrected `1+15` fixture has zero `CORE MARKER ANOMALY / DISCOVERY` records. Reviewed Sprint executions preserve `SPRINT/SP2` marker1 -> `POWER/SP2` marker2, with marker2 accepted clear-only and normal native cleanup.
- True-Power double-FIST control remains correct: first FIST at POWER/SP2 opens `5 -> 7`; second POWER/SP2 FIST is accepted with clear-only rearm; native cleanup returns group7 -> group5.
- The User observed several Power/power-animation attacks apparently miss completely in the `1+15` run. Diagnostics confirm this can occur **after correct marker behavior**. For example true-Power C1=9, C1=27 and C1=40 each accept both authored FISTs with correct first-open/second-rearm semantics and normal cleanup, yet no `ONDAMAGE` is logged during that attack window. Therefore those misses are downstream native contact/target/geometry outcomes, not marker rejection or failed rearm.
- The unmarked/native control independently proves that complete native misses exist without authored marker ownership. Native raw55 executions can open TrollFist `5 -> 7`, produce no `ONDAMAGE`, and later clean `7 -> 5`; reviewed examples include native Normal C1=13, C1=59 and C1=62.
- The native control also confirms that weapon sheathing/drawing is not a universal immunity state: native attacks can damage `PC_Hero` while the player's motion is `HoldRight_End` or `HoldRight_Begin`.
- The User's gameplay observation that the first attack around sheath/draw often misses is therefore consistent with a native/New Balance downstream contact-state phenomenon rather than something introduced by G3AB markers. The current native log does **not** isolate a native Sprint-after-sheath miss specifically; all directly retrieved native Sprint examples in this batch happen to damage. Exact sheath-specific Sprint causality remains narrower than the collision-correctness conclusion.

Scope / limits:
- Runtime acceptance applies to the tested BlackTroll/raw55/New Balance environment and diagnostic build hash above.
- The corrected Sprint second-FIST rule remains evidence-bounded: immutable origin Sprint; current Power accepts explicit SP1/SP2; current Sprint accepts SP2 only. No Sprint/SP1 or `>=1` generalization is established.
- The early Normal/SP0 second-FIST rejection remains a separate deferred authoring-boundary question. It is not a regression from the Sprint correction.
- `ONDAMAGE` is supporting contact evidence, not a requirement for every accepted authored opportunity. Correct marker acceptance/open/rearm plus native cleanup can coexist with a legitimate native miss.

Provenance:
- production behavior change: `4c85193f4efd31e789bc07d7e3c71d31a9b5326e`;
- independent reviewed branch lineage before build: `011808c211dea81d47d572aeb76cadb82c400976` plus later runtime-log upload commits;
- diagnostic built/live SHA256: `B4161D74DD849F4B7B67D9ACCFC42A8D8784F7EF19FB968F2E44D67ED57BD689`;
- corrected `1+3`: `research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_3_test2.log`, blob `c2d6937feb521b213b8141d702e44b2f23342378`;
- corrected `1+8`: `research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_8_test2.log`, blob `99fe4f3fb5373088da155740d440b486fb6ac9c6`;
- corrected `1+15`: `research/raw/2026.09.26_newbalance_blacktroll_all_double_markers_1_15_test2.log`, blob `1c9e57619387f2a34ca7ea3bc73131f1056c95e1`;
- unmarked/native control: `research/raw/2026.09.26_newbalance_blacktroll_all_native_test.log`, blob `67a834077c04b4c980e78a13649ab9a20b18077e`.

Disposition:
- **PASS — RAW55 SPRINT SECOND-FIST SP2 COMPATIBILITY CORRECTION RUNTIME ACCEPTED.**
- The focused New Balance raw55 Sprint compatibility contradiction from EV-376–EV-380 is CLOSED for the tested route.
- Sheath/draw-associated misses are **not a collision-marker blocker** on current evidence. Native unmarked collision windows can also miss entirely; do not add custom damage/contact policy to G3AB for this behavior.
- Preserve the exact native-Sprint-after-sheath subtype as a non-blocking observation unless future evidence makes that distinction relevant.
- The separate Normal/SP0 second-FIST authoring-boundary question remains DEFERRED and requires its own causal task before any widening.
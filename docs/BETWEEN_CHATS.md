# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-18

## Current Bridge — EV-305; GOLEM PHASE 1 FIRST TWO BATCHES CLOSED/PASS

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Focused permanent raw55 acceptance remains CLOSED/PASS at **EV-298**. Standalone regression Phase 1 is now PASS through **EV-305**: 1H, 1H+torch, dual-1H, 2H, Staff, human raw8 Fist single-marker/native-fallback, and human raw8 Fist double-marker repeated-contact.

Permanent raw55 contract:

`docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`

Permanent implementation:

```text
21853392f146febbc2d1aad4e501baa741fd65b2
```

Permanent implementation Normal Chat source review: **PASS**.

## Local product validation already PASS

```text
Script_FrameCollisionBehaviorTest Release build PASS
Script_FrameCollisionTest Release build PASS
behavior-only isolated deployment / functional smoke PASS
diagnostic deployment / startup / clean unload PASS
permanent raw55 four-family behavior core acceptance PASS
```

Behavior-only SHA256:

`0EB935FCBFD5B7A2D2D56683971641EA42B9F7FF074D5B7F2EC2FD353594833A`

Pre-correction diagnostic SHA256:

`4A402FD2300C95344657719895BCEF49F07AD417AAFCF1287F5421F641311FCA`

## Permanent raw55 core acceptance evidence

```text
research/raw/2026.09.17_troll_raw55_permanent_acceptance.log
research/derived/2026.09.17_troll_raw55_permanent_acceptance_large_log/
upload commit 6ae7dcc315e0859ab8ff061f1576d52206d21008
SHA256 AA866E70BF2DB42CF7CE73607040443A9F8725F05CCFDDB01116E582956DA6A7
blob 8ae8cd8da6e958f6b7f0b139a17467fcc7dd3c6b
150110 bytes / 1011 lines
```

Representative Quick, Normal, true-Power and Sprint-origin routes all show intended first/repeated FIST behavior, two native damage opportunities, native exact RIGHT `7 -> 5` cleanup and outstanding-zero finalization.

## Diagnostic correction 1 — CORE ownership classifier

Commit:

```text
314f284dbaaf05c5f185811aab107e84f1d434ce
```

Changed only:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
```

Purpose:

```text
treat factual no-mask + no-raw8-resolver + current-RIGHT-PhysicalFist
FIST source shape as routine raw55 diagnostic ownership
```

Normal Chat independent source review: **PASS**.

Local rebuild/runtime validation: pending.

## Astra independent audit

Astra read-only formal result:

```text
PASS WITH NON-BLOCKING FINDINGS
```

No confirmed release-behavior defect.

Disposition saved in:

`docs/ASTRA_RAW55_INDEPENDENT_AUDIT_RESULT.md`

F1 nested marker/callback attribution remains a documented evidence-bounded risk with **NO SOURCE CHANGE**.

F2 callback-entry same-C1 identity contradiction was a genuine diagnostics-only contract omission.

## Diagnostic correction 2 — callback identity contradiction surfacing

Astra published:

```text
6795377f2a827a8c06a531006a56a87b457e8642
```

Exact branch relation:

```text
base d3f4dfb5e58d458b3c9673ba4b7b2e48290e79da
-> one commit
-> 6795377f2a827a8c06a531006a56a87b457e8642
```

Changed only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
+27 / -0
```

Normal Chat independent source review result: **PASS**.

The added helper is inside the existing `FRAME_COLLISION_DIAGNOSTICS` block and logs only the already-computed `identityContradiction`:

```text
CORE RAW55_PHYSICAL_FIST_IDENTITY_CONTRADICTION
Actor
C1
StoredOriginFamily
CallbackFamily
StoredRight
CurrentRight
StoredMotion
CurrentMotion
StoredAuthoredFistCount
CurrentAuthoredFistCount
Rejected=1
```

The original behavior remains:

```text
identity contradiction
-> no callback scope activation
-> no new raw55 intervention
-> return
```

No identity, eligibility, marker, hook, lifecycle, raw8/equipped or F1 logic changed.

## Immediate next responsibility — CONTINUE REMAINING GOLEM SETUPS

Closed Phase-1 evidence so far:

```text
EV-299  1H                         PASS
EV-300  1H+torch                   PASS
EV-301  dual 1H                    PASS
EV-302  2H                         PASS
EV-303  Staff                      PASS
EV-304  human Fist single marker   PASS
EV-305  human Fist double markers  PASS
```

Second-batch facts:

```text
2H:
  RIGHT It_2H_Sword_Flamberge raw3
  Normal/Quick/Power/Whirl/Hack
  40 exact 5->7 and 40 exact 7->5
  18 Golem damage events
  1 deliberate C1-R1 bad-skip repair PASS
  late Action0/no-C1 Whirl markers safely rejected

Staff:
  RIGHT Wrestling Staff_BBM raw12
  Normal/Quick/Power/Whirl/Hack
  39 exact 5->7 and 39 exact 7->5
  22 Golem damage events
  bad-skip attempts cleaned to group5 before terminal repair
  no repair was required
  late Action0/no-C1 Whirl markers safely rejected

human Fist single marker:
  factual raw8 Fist/UseType8
  marked Normal + Power P0 use established latch/timing path
  19 accepted FIST markers
  Power P1 intentionally unmarked:
    MarkerPresent=0 / SuppressNative=0
    contacting executions still damage through Game.dll+0x16E348
  13 Golem damage events

human Fist double markers:
  21 marked executions / 42 accepted FIST callbacks
  first FIST = early-permission rearm
  second FIST = same-C1 NATIVE_TIMING rearm
  10 target-contact executions = 2 Golem damage events each
  20 Golem damage events total

whole batch:
  ownership anomalies = 0
  C1 invariant warnings = 0
  repair divergences = 0
  all PC_Hero C1 finals Outstanding=0
```

User observation: where applicable attacks were first exercised without a target and then against Golem; all intended target attacks connected. Bad skip was deliberately tested in 2H and Staff. Power Hit P1 in the single-FIST set intentionally had no authored marker.

Archived canonical sources:

```text
research/archive/researchraw2026-09-19_regression_golem_2h.log
research/archive/researchraw2026-09-19_regression_golem_staff.log
research/archive/researchraw2026-09-19_regression_golem_human_fist.log
research/archive/researchraw2026-09-19_regression_golem_human_fist_double_markers.log
```

Current raw intake:

```text
research/raw/Keep.txt
```

Next local session:

```text
1. GitHub Desktop Fetch/Pull.
2. No rebuild/redeploy solely for evidence/docs maintenance.
3. Continue any remaining prepared Golem setups under COLLISION_TEST_PLAN §8.1.
4. If the prepared Golem setup matrix is complete, explicitly close Phase 1 before moving to Orc Phase 2.
5. One complete log per setup; upload small batches whenever convenient.
6. Normal Chat fully closes every uploaded batch before requesting the next.
```

## Evidence transaction / archive status

EV-299–EV-305 are canonically recorded. All seven Phase-1 source logs processed so far are archived byte-identically; no completed artifact remains in `research/raw/`.

Phase 1 remains open only for any prepared Golem setup(s) the User has not yet exercised.

## Sequence after standalone collision regression

```text
complete all seven standalone regression phases
-> New Balance 0.7 exact distributed-bundle regression with AttackCollision
-> mature collision migration into src/Script_G3AnimationBehaviors
-> later Raise/speed
```

## Still paused

```text
standalone collision regression = CURRENT GATE
current subphase = §8.1 Golem player equipped/setup matrix; EV-299–EV-305 PASS
publication cadence = 2–3 logs allowed; complete POP-06 closure after every upload batch
NO New Balance final regression yet
NO collision migration into src/Script_G3AnimationBehaviors yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

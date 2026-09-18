# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-18

## Current Bridge — PERMANENT RAW55 CORE PASS; ASTRA AUDIT COMPLETE; ONE DIAGNOSTIC CONTRACT OMISSION FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Canonical family-specific causal evidence remains closed through **EV-294**.

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
```

Behavior-only SHA256:

`0EB935FCBFD5B7A2D2D56683971641EA42B9F7FF074D5B7F2EC2FD353594833A`

Pre-correction diagnostic SHA256:

`4A402FD2300C95344657719895BCEF49F07AD417AAFCF1287F5421F641311FCA`

## Permanent raw55 four-family behavior core acceptance — PASS

Evidence upload:

```text
6ae7dcc315e0859ab8ff061f1576d52206d21008
```

Source:

```text
research/raw/2026.09.17_troll_raw55_permanent_acceptance.log
SHA256 AA866E70BF2DB42CF7CE73607040443A9F8725F05CCFDDB01116E582956DA6A7
Git blob 8ae8cd8da6e958f6b7f0b139a17467fcc7dd3c6b
150110 bytes / 1011 lines
```

Derived:

`research/derived/2026.09.17_troll_raw55_permanent_acceptance_large_log/`

Representative factual routes are clean:

```text
Quick C1=3
marker1 SP0 5->7 + clear
-> first OnDamage
marker2 clear-only / no second group request
-> second OnDamage
-> native 7->5
-> outstanding zero

true Power C1=6
premature 5->7 suppressed
marker1 Action2/SP1 5->7 no clear
-> first OnDamage
marker2 clear-only
-> second OnDamage
-> native 7->5
-> outstanding zero

Normal C1=33
marker1 SP0 5->7 + clear
-> first OnDamage
exact Script_Game.dll+0x386C6 native ALL clear suppressed
marker2 SP1 clear-only
-> second OnDamage
-> native 7->5
-> outstanding zero

Sprint-origin C1=42
premature 5->7 suppressed
marker1 Origin=SPRINT / Action9 SP1 5->7 no clear
-> first OnDamage
same C1/right Action9 -> Action2
marker2 Origin=SPRINT / Current=POWER clear-only
-> second OnDamage during LieKnockDown_Begin
-> native 7->5
-> outstanding zero
```

No `C1 INVARIANT WARNING` found in the processed source.

## CORE ownership-classifier correction — source review PASS

Work source commit:

```text
314f284dbaaf05c5f185811aab107e84f1d434ce
```

Frozen base:

```text
7563af64a2104ce1246e9482aa8a4a48fe54b27a
```

Diff is exactly one commit / one source file:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
+10 / -1
```

Normal Chat independently reviewed the exact diff.

Result: **SOURCE REVIEW PASS**.

The correction adds only the factual routine raw55 candidate shape:

```text
has FIST markers
requiredSourceMask == none
raw8 fist resolver absent
current RIGHT exists
current RIGHT UseType == PhysicalFist/raw55
```

and prevents only that shape from tripping the old raw8-only FIST contradiction assumption.

No production behavior path changes.

Local rebuild/runtime validation has not yet been performed.

## Astra independent permanent-source audit

User supplied Astra's read-only formal report for source state `314f284d...`.

Astra verdict:

```text
PASS WITH NON-BLOCKING FINDINGS
```

Astra found no confirmed release-behavior defect.

Full project disposition:

`docs/ASTRA_RAW55_INDEPENDENT_AUDIT_RESULT.md`

### F1 — defensible nested attribution risk

Astra observed that if an authored first FIST were dispatched reentrantly while the exact eligible native callback scope were still active, its own `5 -> 7` activation could satisfy the premature-native-opening suppression predicate.

Source logic confirms the hypothetical route.

Current decision: **NO SOURCE CHANGE**.

Why:

- accepted SP0 Quick/Normal first-marker openings physically succeed;
- late Quick/Normal and Power/Sprint markers follow the proven native callback progression/suppression route;
- an active matching callback scope around those successful authored `5 -> 7` calls would have suppressed the marker-owned opening and caused activation failure;
- no such failure occurs in the supported tested routes.

Therefore this is a non-blocking evidence-bounded risk, not a demonstrated release defect. Do not add speculative production complexity.

### F2 — confirmed diagnostics-only contract omission

In `PhysicalFistCollision::BeginNativeCallbackScope()`, `ResolveExecution()` may set `identityContradiction=true`; the function correctly returns without intervention, but it can do so without logging the contradiction.

Frozen architecture §5 requires non-Sprint same-C1 origin contradictions to:

```text
perform no new raw55 intervention
AND be surfaced by diagnostics
```

The behavior half is correct; the diagnostic half is incomplete.

Frozen correction authority:

`docs/COLLISION_RAW55_CALLBACK_IDENTITY_DIAGNOSTIC_SURFACING_CORRECTION.md`

## Immediate next responsibility — bounded Work diagnostic surfacing correction

Expected source scope:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
```

Add only one compact stable CORE diagnostic record, under `FRAME_COLLISION_DIAGNOSTICS`, when the already-computed callback-entry identity contradiction occurs.

Do not change:

```text
ResolveExecution identity rules
execution state
eligibility
callback scope activation
premature opening suppression
marker semantics
Normal clear suppression
EngineBridge
hooks
lifecycle
raw8/equipped behavior
F1
```

**WORK BUILD EXECUTION IS PROHIBITED.**

After Work returns:

```text
1. Normal Chat independent source review.
2. Sync local branch.
3. Build Script_FrameCollisionTest Release only.
4. Deploy diagnostic twin alone; verify hash/startup/clean unload.
5. Small marked raw55 control proving:
   - legitimate raw55 ownership = Classification=ROUTINE
   - no false CORE ATTACK OWNERSHIP ANOMALY
   - permanent marker/damage/cleanup facts remain healthy
6. Remaining focused sentinels:
   - unmarked raw55 native fallback
   - raw8 FIST
   - one equipped authored-marker route
7. Close focused permanent acceptance.
```

No dedicated runtime reproduction of an identity contradiction is required before focused acceptance continues; this correction is a source-contract observability fix.

Do not rerun the full four-family Troll acceptance unless behavior-facing source unexpectedly broadens.

## Evidence transaction / archive status

Do not create the next canonical EV or move the permanent-acceptance source from `research/raw/` to `research/archive/` yet.

The four-family behavior core is PASS, but focused permanent acceptance remains open until the corrected diagnostics and three bounded sentinels pass.

## After focused permanent acceptance closes

```text
archive permanent-acceptance raw source unchanged
record canonical permanent-acceptance evidence
update EVIDENCE_INDEX
standalone collision regression
-> New Balance 0.7 exact distributed-bundle regression with AttackCollision
-> mature collision migration into src/Script_G3AnimationBehaviors
-> later Raise/speed
```

## Still paused

```text
NO broad standalone collision regression yet
NO New Balance final regression yet
NO collision migration into src/Script_G3AnimationBehaviors yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

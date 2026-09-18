# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-18

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is the diagnostic twin. Permanent collision behavior must also compile in diagnostics-free `Script_FrameCollisionBehaviorTest`. Final migration into `src/Script_G3AnimationBehaviors` occurs only after focused acceptance and standalone collision regression.

> **LARGE-LOG RULE:** Do not orient by scanning raw/archive logs. Use canonical EV first and committed derived packages for large-log retrieval. Processed source evidence moves unchanged to `research/archive/` after evidence closure.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Permanent raw55 contract: `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`  
Astra audit result/disposition: `docs/ASTRA_RAW55_INDEPENDENT_AUDIT_RESULT.md`  
Current bounded correction: `docs/COLLISION_RAW55_CALLBACK_IDENTITY_DIAGNOSTIC_SURFACING_CORRECTION.md`  
Latest closed causal evidence: **EV-294** in `docs/EVIDENCE_LEDGER_291_ONWARD.md`

## Current checkpoint

```text
raw55 Quick repeated-FIST CLOSED/PASS — EV-273
raw55 Normal repeated-FIST CLOSED/PASS — EV-292
raw55 true Power repeated-FIST CLOSED/PASS — EV-293
raw55 Sprint-origin repeated-FIST CLOSED/PASS — EV-294

PERMANENT RAW55 IMPLEMENTATION 21853392... SOURCE REVIEW PASS
BOTH RELEASE TARGETS BUILD PASS
BEHAVIOR-ONLY FUNCTIONAL/RELEASE-PURITY SMOKE PASS
DIAGNOSTIC DEPLOYMENT + STARTUP PASS
PERMANENT RAW55 FOUR-FAMILY BEHAVIOR CORE ACCEPTANCE PASS

CORE OWNERSHIP CLASSIFIER CORRECTION 314f284d...:
- Work static audit PASS
- Normal Chat independent source review PASS
- Astra independent review agrees classifier correction is narrow/correct
- local rebuild/runtime validation not yet performed

ASTRA PERMANENT RAW55 AUDIT:
PASS WITH NON-BLOCKING FINDINGS
- no confirmed release-behavior defect
- F1 nested marker/callback attribution = defensible risk, no change
- F2 callback-entry identity contradiction not always surfaced = confirmed diagnostics-only contract omission
```

## Permanent core acceptance evidence

```text
research/raw/2026.09.17_troll_raw55_permanent_acceptance.log
research/derived/2026.09.17_troll_raw55_permanent_acceptance_large_log/
upload commit 6ae7dcc315e0859ab8ff061f1576d52206d21008
SHA256 AA866E70BF2DB42CF7CE73607040443A9F8725F05CCFDDB01116E582956DA6A7
blob 8ae8cd8da6e958f6b7f0b139a17467fcc7dd3c6b
150110 bytes / 1011 lines
```

Representative Quick, Normal, true-Power and Sprint-origin two-FIST routes all show intended first-marker behavior, clear-only marker2 rearm, two native damage opportunities, native exact RIGHT `7 -> 5` cleanup and outstanding-zero finalization.

The full focused permanent-acceptance transaction is still open until the diagnostic corrections and three bounded sentinels pass. Do not archive/canonicalize this source yet.

## Independent Astra audit disposition

Saved full project disposition:

`docs/ASTRA_RAW55_INDEPENDENT_AUDIT_RESULT.md`

### F1 — nested marker inside active callback scope

Source makes the hypothetical suppression collision logically possible, but accepted runtime evidence demonstrates it does not occur in the supported tested first-marker routes. Do **not** add speculative release behavior.

### F2 — callback identity contradiction surfacing

Confirmed frozen-contract omission:

`PhysicalFistCollision::BeginNativeCallbackScope()` correctly declines intervention on a same-C1 identity/origin contradiction but can return without surfacing that fact diagnostically.

Behavior is correct; diagnostics are incomplete.

Frozen correction:

`docs/COLLISION_RAW55_CALLBACK_IDENTITY_DIAGNOSTIC_SURFACING_CORRECTION.md`

## Current responsibility — bounded Work diagnostic surfacing correction

Allowed expected source:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
```

Add only one compact diagnostic fact under `FRAME_COLLISION_DIAGNOSTICS` when the already-computed callback-entry `identityContradiction` occurs.

Do not change behavior, identity rules, eligibility, callback scope decisions, markers, hooks, lifecycle, raw8/equipped behavior or F1.

**WORK BUILD EXECUTION IS PROHIBITED.**

After Work:

```text
Normal Chat independent source review
-> build Script_FrameCollisionTest Release only
-> deploy/hash/startup
-> small marked raw55 control:
   legitimate raw55 ownership = ROUTINE
   no false CORE ATTACK OWNERSHIP ANOMALY
   behavior facts still healthy
-> remaining focused sentinels:
   unmarked raw55 native fallback
   raw8 FIST
   one equipped authored-marker route
-> close focused permanent acceptance
```

Do not rerun the full four-family Troll acceptance unless behavior-facing source unexpectedly broadens.

## After focused permanent acceptance closes

```text
archive permanent-acceptance source unchanged
record canonical permanent-acceptance evidence
update EVIDENCE_INDEX
standalone collision regression
-> New Balance 0.7 exact distributed bundle regression with AttackCollision included
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

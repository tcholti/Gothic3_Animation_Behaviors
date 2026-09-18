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
- local rebuild/runtime validation pending

CALLBACK IDENTITY DIAGNOSTIC SURFACING 6795377f...:
- Astra implementation/static audit PASS
- Normal Chat independent source review PASS
- exactly one source file, +27/-0
- diagnostics-only under FRAME_COLLISION_DIAGNOSTICS
- local rebuild/runtime validation pending

ASTRA PERMANENT RAW55 AUDIT:
PASS WITH NON-BLOCKING FINDINGS
- no confirmed release-behavior defect
- F1 nested marker/callback attribution = defensible risk, no change
- F2 callback-entry identity contradiction surfacing = corrected by 6795377f...
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

The full focused permanent-acceptance transaction remains open until the corrected diagnostics and three bounded sentinels pass. Do not archive/canonicalize this source yet.

## Independent Astra audit disposition

Saved full project disposition:

`docs/ASTRA_RAW55_INDEPENDENT_AUDIT_RESULT.md`

### F1 — nested marker inside active callback scope

Source makes the hypothetical suppression collision logically possible, but accepted runtime evidence demonstrates it does not occur in the supported tested first-marker routes. Do **not** add speculative release behavior.

### F2 — callback identity contradiction surfacing

The diagnostics-only contract omission is now source-corrected by:

```text
6795377f2a827a8c06a531006a56a87b457e8642
```

Changed only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
```

The new helper is compiled only under `FRAME_COLLISION_DIAGNOSTICS` and emits:

```text
CORE RAW55_PHYSICAL_FIST_IDENTITY_CONTRADICTION
```

using the already-computed callback-entry contradiction. Behavior still returns without raw55 intervention exactly as before.

Normal Chat independent source review: **PASS**.

## Current responsibility — LOCAL DIAGNOSTIC DEPLOYMENT GATE

The User returned to the authoritative local build machine and successfully built:

```text
Script_FrameCollisionTest Release — PASS
build source checkout = 8abe9c30cae5755184bb5ed22b2959998ad22d33
```

After that build, repository changes were documentation/procedure maintenance only; no executable source changed. Do **not** require a rebuild merely because remote HEAD advanced through those docs-only commits.

The Assistant has since published documentation/procedure-only commits after the successful local build. Before any further local PowerShell command, the User must perform the normal POP-01 GitHub Desktop handoff:

```text
GitHub Desktop
-> repository = Gothic3_Animation_Behaviors
-> branch = docs/collision-source-evidence
-> Fetch origin
-> Pull origin
-> top action returns to Fetch origin
-> no unexpected local Changes
```

These pulled changes are documentation only; they do **not** invalidate the already-built diagnostic DLL and do not require a rebuild.

The next runtime step after Desktop synchronization is therefore:

```text
POP-03 exact diagnostic-twin deployment block
-> sole-live collision DLL + built/live SHA256 PASS
-> POP-04 exact diagnostic startup/load block
-> small marked raw55 control:
   legitimate raw55 ownership = ROUTINE
   no false CORE ATTACK OWNERSHIP ANOMALY
   marker/damage/cleanup facts healthy
-> remaining focused sentinels:
   unmarked raw55 native fallback
   raw8 FIST
   one equipped authored-marker route
-> close focused permanent acceptance
```

**Procedure lock:** routine Git synchronization/publication uses GitHub Desktop under POP-01. After Desktop synchronization, execute POP-03 and POP-04 from `PROJECT_OPERATING_PROCEDURES.md` verbatim. Do not insert an extra artifact-formatting/hash-precheck or reconstruct equivalent PowerShell from memory.

For any new oversized runtime log, use `tools/log_evidence/Prepare-Log.cmd`, then GitHub Desktop Commit + Push **both** the unchanged `research/raw/` log and generated `research/derived/<stem>_large_log/` package. Normal Chat analyzes the derived package by default.

No dedicated runtime reproduction of the identity contradiction is required before focused acceptance continues.

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

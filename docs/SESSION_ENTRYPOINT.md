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
Latest canonical evidence: **EV-295** in `docs/EVIDENCE_LEDGER_291_ONWARD.md`

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
- runtime control PASS — EV-295
- legitimate raw55 ownership is ROUTINE; false CORE ATTACK OWNERSHIP ANOMALY count = 0

CALLBACK IDENTITY DIAGNOSTIC SURFACING 6795377f...:
- Astra implementation/static audit PASS
- Normal Chat independent source review PASS
- exactly one source file, +27/-0
- diagnostics-only under FRAME_COLLISION_DIAGNOSTICS
- legitimate control produced no contradiction, as expected
- source-contract correction remains PASS

FOCUSED SENTINELS:
- equipped authored-marker sentinel PASS inside EV-295
- unmarked raw55 native fallback OPEN
- raw8 FIST OPEN

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

## Current responsibility — FINAL TWO FOCUSED SENTINELS

The current diagnostic binary has already passed build, deployment, binary-identity and startup/load gates:

```text
Script_FrameCollisionTest Release — BUILD PASS
build source checkout = 8abe9c30cae5755184bb5ed22b2959998ad22d33
built/live DLL SHA256 = 68C750860ABB901B5F6E7D1291838ED7C50CC6E33D3A124E448D42C59BBD14BD
POP-03 deployment PASS
POP-04 startup/load/clean-unload PASS
```

EV-295 then validated the corrected diagnostics and permanent raw55 behavior:

```text
raw55 Quick/Normal/Power/Sprint ownership = ROUTINE
false CORE ATTACK OWNERSHIP ANOMALY = 0
identity-contradiction diagnostic = 0 in legitimate control
C1 invariant/repair/divergence = 0
raw55 cleanup/finalization healthy
equipped Flamberge authored-marker sentinel = PASS
```

The control log is only 64,805 bytes / 323 lines. POP-07 processing was harmless but unnecessary; use `Prepare-Log.cmd` only when a new log is genuinely large enough that direct retrieval is inefficient.

Assistant-side commits after that runtime control are documentation/evidence maintenance only. Before the next local test, perform the ordinary POP-01 GitHub Desktop Fetch/Pull handoff. **Do not rebuild, redeploy or repeat startup merely because these docs-only commits advanced remote HEAD.**

Only two focused sentinels remain:

```text
1. unmarked raw55 native fallback
2. raw8 FIST
```

After both pass, close focused permanent raw55 acceptance and proceed to standalone collision regression.

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

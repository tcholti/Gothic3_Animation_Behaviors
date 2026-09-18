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
Latest canonical evidence: **EV-298** in `docs/EVIDENCE_LEDGER_291_ONWARD.md`

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
- equipped authored-marker sentinel PASS — EV-295
- unmarked raw55 native fallback PASS — EV-296
- raw8 FIST coexistence PASS — EV-297
- focused permanent raw55 acceptance CLOSED/PASS — EV-298

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

The focused permanent-acceptance transaction is CLOSED/PASS at EV-298. Its processed runtime sources have been archived byte-identically; do not rerun the focused raw55 matrix without concrete contradictory evidence.

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

## Current responsibility — STANDALONE REGRESSION PHASE 1: GOLEM WEAPON MATRIX

Focused permanent raw55 acceptance is now **CLOSED/PASS — EV-298**.

Final raw8 sentinel EV-297 proves the established raw8 mechanism remains healthy under the permanent raw55 source state:

```text
47 accepted FIST markers with Fist / Raw8UseType=8
native Sabertooth -> PC_Hero damage = 11
transformed Sabertooth -> native Sabertooth damage = 13
native + transformed C1 finalizations = 47 clean
raw55 intervention in raw8 route = 0
ownership anomaly / invariant / repair / divergence = 0
```

The four focused acceptance sources were archived byte-identically in:

```text
5700aedb2feadbde1d1a635a9538ed788836f36d
```

Current diagnostic binary remains the already-verified product:

```text
build source checkout = 8abe9c30cae5755184bb5ed22b2959998ad22d33
built/live DLL SHA256 = 68C750860ABB901B5F6E7D1291838ED7C50CC6E33D3A124E448D42C59BBD14BD
build/deploy/startup PASS
```

All repository commits after that binary build are documentation/evidence maintenance only unless a later source change is explicitly introduced.

Before the next local test, use the normal POP-01 GitHub Desktop Fetch/Pull handoff. Then begin the restored seven-phase standalone campaign in `COLLISION_TEST_PLAN.md` §8. Current phase is §8.1: the User attacks a Golem with each prepared weapon/setup, using one runtime run/log per weapon. The User may upload the logs in small batches (typically 2–3 at a time) rather than waiting for the full weapon matrix. After every uploaded batch, Normal Chat must complete POP-06 evidence/document/archive cleanup before requesting the next batch. Do not reopen raw55 family-specific probing.

## Next sequence after standalone collision regression

```text
standalone collision regression
-> New Balance 0.7 exact distributed bundle regression with AttackCollision included
-> mature collision migration into src/Script_G3AnimationBehaviors
-> later Raise/speed
```

## Still paused

```text
standalone collision regression = CURRENT GATE
current subphase = §8.1 Golem player equipped-weapon matrix
publication cadence = small batches allowed; each batch fully closes before next
NO New Balance final regression yet
NO collision migration into src/Script_G3AnimationBehaviors yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

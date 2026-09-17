# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-17

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is the diagnostic twin. Permanent collision behavior must also compile in diagnostics-free `Script_FrameCollisionBehaviorTest`. Final migration into `src/Script_G3AnimationBehaviors` occurs only after focused acceptance and standalone collision regression.

> **LARGE-LOG RULE:** Do not orient by scanning raw/archive logs. Use canonical EV first and committed derived packages for large-log retrieval. Processed source evidence moves unchanged to `research/archive/` after evidence closure.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Permanent raw55 contract: `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`  
Diagnostic correction authority: `docs/COLLISION_RAW55_CORE_DIAGNOSTIC_CLASSIFICATION_CORRECTION.md`  
Saved Astra audit experiment: `docs/ASTRA_RAW55_INDEPENDENT_AUDIT_TASK.md`  
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
DIAGNOSTIC OWNERSHIP FALSE-POSITIVE IDENTIFIED
DIAGNOSTIC-ONLY CORRECTION 314f284d... PUBLISHED; INDEPENDENT REVIEW PENDING
```

## Permanent core acceptance result

Evidence:

```text
research/raw/2026.09.17_troll_raw55_permanent_acceptance.log
research/derived/2026.09.17_troll_raw55_permanent_acceptance_large_log/
upload commit 6ae7dcc315e0859ab8ff061f1576d52206d21008
SHA256 AA866E70BF2DB42CF7CE73607040443A9F8725F05CCFDDB01116E582956DA6A7
blob 8ae8cd8da6e958f6b7f0b139a17467fcc7dd3c6b
150110 bytes / 1011 lines
```

Factual representative routes are complete and clean:

```text
Quick C1=3:
first FIST 5->7 + clear -> damage
second FIST clear-only -> second damage
native 7->5 -> outstanding zero

Power C1=6:
early native opening suppressed
first FIST Action2/SP1 5->7, no clear -> damage
second FIST clear-only -> second damage
native 7->5 -> outstanding zero

Normal C1=33:
first FIST SP0 5->7 + clear -> damage
exact native Script_Game+0x386C6 ALL clear suppressed
second FIST SP1 clear-only -> second damage
native 7->5 -> outstanding zero

Sprint-origin C1=42:
early native opening suppressed
first FIST Action9/SP1 5->7, no clear -> damage
same C1/right Action9->Action2
second FIST keeps Origin=SPRINT, Current=POWER, clear-only
second damage occurs during LieKnockDown_Begin
native 7->5 -> outstanding zero
```

User observed all exercised two-swing attacks damage twice; Sprint knocked the player down.

The full focused permanent-acceptance transaction is still open until the corrected CORE diagnostic classification and three bounded sentinels pass. Do not archive/canonicalize this source yet.

## Current published source change — diagnostics only

Work commit:

```text
314f284dbaaf05c5f185811aab107e84f1d434ce
```

Changed only:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
```

Purpose:

```text
Treat the exact no-mask / no-raw8-resolver / current-RIGHT-PhysicalFist
FIST ownership shape as routine raw55 diagnostic ownership rather than a contradiction.
Preserve contradiction reporting for malformed FIST shapes.
```

Work reports static checks PASS, build not attempted, no contradiction. Normal Chat independent source review and local validation are still pending.

## Tomorrow first — Astra review experiment

The User wants to evaluate GPT-6 Astra against the mature raw55 implementation before deciding whether its engineering benefit justifies its much higher usage cost.

Use exactly:

`docs/ASTRA_RAW55_INDEPENDENT_AUDIT_TASK.md`

Run only after the Astra allowance is fully reset. It is read-only: no edits, build or publication. Its report is not project authority; Normal Chat must independently verify every substantive finding.

The first 2026-09-17 attempt exhausted the remaining ~32% five-hour allowance in about three minutes and returned no final report. It produced no engineering conclusion.

## After Astra / if skipped

```text
Normal Chat independent review of 314f284d...
-> rebuild Script_FrameCollisionTest only
-> diagnostic deploy/startup
-> small marked raw55 control:
   Classification=ROUTINE
   no false CORE ATTACK OWNERSHIP ANOMALY
   behavior facts still healthy
-> remaining focused sentinels:
   unmarked raw55 native fallback
   raw8 FIST
   one equipped authored-marker route
```

Do not rerun the full four-family Troll acceptance unless the diagnostic-only correction unexpectedly broadens into behavior-facing source.

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

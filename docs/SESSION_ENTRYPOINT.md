# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-17

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is the diagnostic twin. Permanent collision behavior must also compile in diagnostics-free `Script_FrameCollisionBehaviorTest`. Final migration into `src/Script_G3AnimationBehaviors` occurs only after focused acceptance and standalone collision regression.

> **LARGE-LOG RULE:** Do not orient by scanning raw/archive logs. Use canonical EV first and committed derived packages for large-log retrieval. Processed source evidence moves unchanged to `research/archive/`.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Permanent raw55 contract: `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`  
Current bounded correction: `docs/COLLISION_RAW55_CORE_DIAGNOSTIC_CLASSIFICATION_CORRECTION.md`  
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
CORE DIAGNOSTIC OWNERSHIP CLASSIFIER FALSE-POSITIVE FOUND
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

## Current diagnostic gap

`CollisionDiagnostics::LogAttackCallbackOwnership()` predates permanent raw55 and currently calls every FIST marker with a non-raw8 resolver a contradiction:

```cpp
result.decision.hasFistMarkers
&& fistUseType != static_cast<GEInt>(gEUseType_Fist)
```

The acceptance run therefore produced 19 `CORE ATTACK OWNERSHIP ANOMALY` blocks for legitimate raw55 executions. Source inspection proves these are false positives: permanent raw55 intentionally has no raw8 resolver and instead owns exact RIGHT PhysicalFist/UseType55.

Behavior is not implicated. Fix the diagnostic classification before continuing certification so future CORE regression signals remain meaningful.

## Current responsibility — BOUNDED WORK DIAGNOSTIC-ONLY CORRECTION

Read:

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. `docs/COLLISION_RAW55_CORE_DIAGNOSTIC_CLASSIFICATION_CORRECTION.md`
4. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
5. exact `CollisionDiagnostics.cpp` source only as required.

Allowed source change:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
```

No behavior/core/hook/CMake source change is authorized.

**WORK BUILD EXECUTION IS PROHIBITED.**

After Work:

```text
independent source review
-> rebuild diagnostic target only
-> redeploy/startup
-> small marked raw55 control proving routine ownership classification
-> remaining focused sentinels: unmarked raw55, raw8 FIST, equipped marker
```

Do not rerun the full four-family permanent acceptance unless source scope unexpectedly broadens.

## Still paused

```text
NO broad standalone collision regression yet
NO New Balance final regression yet
NO collision migration into src/Script_G3AnimationBehaviors yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

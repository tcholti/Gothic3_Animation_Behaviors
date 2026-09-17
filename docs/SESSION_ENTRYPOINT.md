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
Frozen production contract: `docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`  
Latest canonical evidence: **EV-294** in `docs/EVIDENCE_LEDGER_291_ONWARD.md`

## Current checkpoint

```text
raw55 Quick         repeated-FIST CLOSED/PASS — EV-273
raw55 Normal        repeated-FIST CLOSED/PASS — EV-292
raw55 true Power    repeated-FIST CLOSED/PASS — EV-293
raw55 Sprint-origin repeated-FIST CLOSED/PASS — EV-294

ALL FAMILY-SPECIFIC RAW55 CAUSAL RESEARCH CLOSED
PERMANENT RAW55 ARCHITECTURE FROZEN
PERMANENT RAW55 IMPLEMENTATION PUBLISHED + INDEPENDENT SOURCE REVIEW PASS
BOTH PERMANENT LOCAL TARGETS BUILD PASS
BEHAVIOR-ONLY DEPLOYMENT + FUNCTIONAL SMOKE PASS
DIAGNOSTIC DEPLOYMENT + STARTUP/LOAD/UNLOAD PASS
```

Permanent implementation commit:

```text
21853392f146febbc2d1aad4e501baa741fd65b2
```

Independent Normal Chat source review: **PASS**.

## Local build / behavior-only smoke — PASS

Both Release targets built successfully:

```text
Script_FrameCollisionBehaviorTest  PASS
Script_FrameCollisionTest          PASS
```

Behavior-only deployment identity:

```text
only live collision DLL: Script_FrameCollisionBehaviorTest.dll
length: 418304 bytes
built/live SHA256:
0EB935FCBFD5B7A2D2D56683971641EA42B9F7FF074D5B7F2EC2FD353594833A
```

User functional smoke under the behavior-only DLL:

```text
spawned Troll
observed attacks capable of damaging twice, behavior not previously available before permanent raw55 support

spawned Golem
attacked with 2H, Dual 1H/1H and Staff
observed established authored marker behavior still functioning

exercised Hack attack
observed Hack behavior still functioning
```

This is functional/release-purity evidence only; internal family/C1/source proof belongs to the diagnostic twin.

## Diagnostic deployment / startup — PASS

Reviewed diagnostic twin deployed alone:

```text
only live collision DLL: Script_FrameCollisionTest.dll
length: 457728 bytes
built/live SHA256:
4A402FD2300C95344657719895BCEF49F07AD417AAFCF1287F5421F641311FCA
```

Startup/load/unload verified:

```text
Script_FrameCollisionTest diagnostic build loaded.
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
HACK_CALLBACK_IDENTITY ... ExactlyOne=1 ... Name=OnAI_HackAttack
Installing behavior hooks...
Hooks installed.
Script_FrameCollisionTest unloading cleanly.
```

## Immediate next responsibility — FOCUSED PERMANENT RAW55 ACCEPTANCE

Do not launch Work.

Run one controlled diagnostic Troll session using the marked two-FIST fixture. Exercise enough attacks to capture factual examples of:

```text
Quick first/repeated FIST
Normal SP0 first FIST + marker2
true Power first/repeated FIST
Sprint-origin Action9 -> Action2 first/repeated FIST
native raw55 7 -> 5 cleanup / outstanding-zero lifecycle
```

Visual family identification is not authoritative. Use runtime action/family/C1 records.

Also include, if practical in the same session or immediately after:

```text
one unmarked Troll/native raw55 fallback sample
one raw8 FIST sentinel
one equipped-marker sentinel
```

The first analysis target is the permanent raw55 Troll route. Do not broaden into full standalone regression until it passes.

## Still paused

```text
NO new Work task during local validation
NO collision migration into src/Script_G3AnimationBehaviors yet
NO standalone broad regression before focused permanent raw55 acceptance
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

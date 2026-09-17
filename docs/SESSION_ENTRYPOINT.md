# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-17

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. The eventual shipped plugin remains `Script_G3AnimationBehaviors`; `PhysicalFistProbe` is not production architecture.

> **LARGE-LOG RULE:** Do not orient by scanning raw/archive logs. Use canonical EV first and the committed derived package for large-log retrieval. Processed source evidence moves unchanged to `research/archive/`.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe: `docs/COLLISION_RAW55_POWER_REPEAT_FIST_REARM_PROBE.md`  
Latest canonical evidence: **EV-292** in `docs/EVIDENCE_LEDGER_291_ONWARD.md`

## Current checkpoint

```text
raw55 Quick       CLOSED/PASS through EV-273
raw55 true Power  first-contact CLOSED/PASS through EV-276
raw55 Normal      repeated-FIST contact rearm CLOSED/PASS — EV-292
raw55 Sprint      first-contact CLOSED/PASS through EV-282
raw55 two-FIST cross-family runtime CLOSED — EV-283
raw55 Normal native 7->7 setter as second-rearm source REJECTED — EV-288
raw55 Normal native trigger-bookkeeping reset before marker2 CONFIRMED — EV-289
raw55 Normal exact native public ALL-clear reset operation IDENTIFIED — EV-290
raw55 Normal native ALL-clear causal necessity CLOSED/PASS — EV-291
raw55 Normal authored marker2 replacement-clear sufficiency CLOSED/PASS — EV-292
```

## Power repeated-FIST implementation under local validation

Frozen contract:

```text
docs/COLLISION_RAW55_POWER_REPEAT_FIST_REARM_PROBE.md
```

Implementation commit:

```text
d3388d5c38c29ea4453259e9efb3fd67916d865e
```

Required implementation base:

```text
f5559a38866a7781be3de4e8ac8847b1a1f531c7
```

Independent Normal Chat source review: **PASS**.

Review findings:

```text
one commit over frozen base
one changed source file only:
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp

preserves EV-275 early Power selective suppression
preserves original _AI_PowerAttack / StatePosition progression
preserves EV-276 first authored Power activation with ClearTriggeredList=0
adds one per-proof/C1 repeatFistRearmUsed flag
reuses/extracts read-only exact trigger-state capture while preserving Normal wrapper behavior
requires exact actor/C1/current-RIGHT/source identity
requires Action2 / Power Hit / exactly two FIST markers / group7 / StatePosition1
requires earlySuppressionProven + activationUsed + repeat not yet used
requires PRE aligned PC_Hero visited exactly once / visit count >=1
executes exactly one RIGHT TouchDamage.ClearTriggeredList()
captures/logs POST trigger state
issues no second collision-group request
```

No `EngineBridge.cpp`, header API, hook, RVA, CMake or production change occurred. Quick/Normal/Sprint/raw8 behavior remains structurally outside the new Power path. Work build status: **NOT ATTEMPTED — correctly prohibited**.

## Immediate next responsibility — LOCAL BUILD ONLY

Do not launch another Work task.

```text
GitHub Desktop: Fetch origin -> Pull origin -> Fetch origin
-> confirm Changes = 0 changed files
-> confirm branch docs/collision-source-evidence is current
-> build Script_FrameCollisionTest Release only
-> STOP on build result
```

Build command:

```powershell
cmake --build build --config Release --target Script_FrameCollisionTest
```

If build passes, Normal Chat will continue with the established POP-03/04 deploy/hash/twin/startup gates before runtime.

Runtime question after those gates:

```text
Does one exact second-Power-FIST ClearTriggeredList(), with RIGHT already group7 and factual first-contact visit still present, restore a second same-C1 damage opportunity without another group request?
```

## Evidence retrieval discipline

Do not scan `research/raw/` or `research/archive/` during orientation.

Use:

1. this file;
2. `BETWEEN_CHATS.md`;
3. `COLLISION_RAW55_POWER_REPEAT_FIST_REARM_PROBE.md`;
4. EV-275/EV-276 in `EVIDENCE_LEDGER_274_ONWARD.md`;
5. EV-283 in `EVIDENCE_LEDGER_283_ONWARD.md`;
6. exact runtime evidence only after the new test exists.

## Still paused

```text
NO permanent PhysicalFistCollision
NO promotion/copy of PhysicalFistProbe scaffolding
NO Sprint repeated-FIST intervention yet
NO permanent raw55 architecture until Power + Sprint repeated-contact work closes
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

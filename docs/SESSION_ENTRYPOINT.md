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

## EV-292 factual result

Representative Normal route is closed:

```text
marker1 at SP0
-> exact RIGHT raw55 5 -> 7 + authored contact clear
-> hit1

native hidden between-contact clear suppressed
-> player remains visited
-> SP0 -> 1 survives

marker2 at SP1
-> one authored replacement ClearTriggeredList
-> PRE player visited / POST player absent
-> hit2 returns

native 7 -> 5 cleanup
-> clean C1 finalization
```

Conclusion:

> Authored Normal marker2 `ClearTriggeredList()` is sufficient to replace Gothic's suppressed native between-contact clear and causally owns the second same-C1 contact rearm in the tested route.

Canonical EV-292 source:

```text
research/archive/2026.09.17_troll_raw55_normal_marker2_replacement_clear.log
SHA256 = 4AE9700C2944FC2940AB194E018478B88EF00A90157BC8DC3AC1FDB48BEDD91D
```

## Power repeated-FIST causal route

Canonical Power evidence now reconstructs:

```text
EV-275
native true-Power early RIGHT raw55 5 -> 7 is selectively suppressed
original _AI_PowerAttack still advances StatePosition 0 -> 1
RIGHT remains group5

EV-276
first authored Power FIST at StatePosition1
-> exact RIGHT raw55 5 -> 7
-> ClearTriggeredList=0
-> native first damage
-> native cleanup remains healthy

EV-283 controlled two-FIST fixture
later second authored Power FIST is delivered in the same C1
after the first authored FIST already opened RIGHT raw55 and produced damage
RIGHT remains group7
temporary activationUsed one-shot policy prevents any second intervention
```

Therefore the remaining Power question is contact rearm only; another physical activation test is not required.

## Immediate next responsibility — BOUNDED WORK IMPLEMENTATION

Implement only:

```text
docs/COLLISION_RAW55_POWER_REPEAT_FIST_REARM_PROBE.md
```

Frozen question:

```text
at exact later authored true-Power FIST in the controlled two-FIST fixture
+ same actor / same C1 / same exact RIGHT raw55 source
+ first Power activation already used
+ RIGHT already group7 / StatePosition1
+ factual PC_Hero visited exactly once from first contact

perform exactly one TouchDamage.ClearTriggeredList()
without any second collision-group request

Does this create the second same-C1 damage opportunity?
```

Expected source scope:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

No `EngineBridge.cpp`, header API, new hook/RVA, CMake or production change is expected. A smallest internal read-only trigger-state capture extraction/reuse inside `PhysicalFistProbe.cpp` is allowed only if existing Normal behavior remains unchanged.

Work build execution is not authorized. Work performs source/static audit, publishes the bounded implementation, reports final remote SHA/changed files/result/build status/contradictions, then stops.

Normal Chat independently reviews before any User-local build.

## Evidence retrieval discipline

Do not scan `research/raw/` or `research/archive/` during orientation.

Use:

1. this file;
2. `BETWEEN_CHATS.md`;
3. `COLLISION_RAW55_POWER_REPEAT_FIST_REARM_PROBE.md`;
4. EV-275/EV-276 in `EVIDENCE_LEDGER_274_ONWARD.md`;
5. EV-283 in `EVIDENCE_LEDGER_283_ONWARD.md`;
6. exact source needed for the bounded implementation.

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

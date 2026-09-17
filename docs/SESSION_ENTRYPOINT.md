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
Current frozen probe: `docs/COLLISION_RAW55_NORMAL_MARKER2_REPLACEMENT_CLEAR_PROBE.md`  
Latest canonical evidence: **EV-291** in `docs/EVIDENCE_LEDGER_291_ONWARD.md`

## Current checkpoint

```text
raw55 Quick       CLOSED/PASS through EV-273
raw55 true Power  first-contact CLOSED/PASS through EV-276
raw55 Normal      first-contact + SP0 route CLOSED/PASS through EV-287
raw55 Sprint      first-contact CLOSED/PASS through EV-282
raw55 two-FIST cross-family runtime CLOSED — EV-283
raw55 Normal native 7->7 setter as second-rearm source REJECTED — EV-288
raw55 Normal native trigger-bookkeeping reset before marker2 CONFIRMED — EV-289
raw55 Normal exact native public ALL-clear reset operation IDENTIFIED — EV-290
raw55 Normal native ALL-clear causal necessity CLOSED/PASS — EV-291
```

## Current factual model

EV-291 establishes:

```text
marker1 at SP0
-> exact RIGHT raw55 5 -> 7
-> marker-owned ClearTriggeredList
-> hit1
-> PC_Hero visited/count1

native Normal transition
-> exact native 7 -> 7 setter suppressed
-> exact native ALL clear from Script_Game.dll +0x386C6 suppressed
-> player remains visited/count1
-> SP0 -> 1 still completes

marker2
-> player still visited/count1
-> no hit2

native exact RIGHT 7 -> 5 cleanup
-> clean C1
```

Therefore the exact native ALL clear is causally required for the implicit second contact opportunity in the tested Normal route.

## Immediate next responsibility — bounded Work implementation

The next one-variable probe is frozen in:

```text
docs/COLLISION_RAW55_NORMAL_MARKER2_REPLACEMENT_CLEAR_PROBE.md
```

Implement only that diagnostics-only contract.

Frozen question:

```text
keep EV-291 native clear suppression unchanged
+ at exact later authored Normal FIST only
+ require player still factually visited
+ perform one replacement ClearTriggeredList()

Does hit2 return?
```

Expected source scope:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

No `EngineBridge.cpp`, header API, hook, RVA, CMake or production change is expected. If implementation requires broader scope, STOP and report the contradiction.

Work build execution is not authorized. Work performs source/static audit, publishes the bounded implementation, reports final remote SHA/changed files/result/build status/contradictions, then stops.

Normal Chat must independently review the Work commit before any User-local build.

## Retrieval discipline

Do not scan raw/archive logs during orientation.

Use:

1. this file;
2. `BETWEEN_CHATS.md`;
3. `COLLISION_RAW55_NORMAL_MARKER2_REPLACEMENT_CLEAR_PROBE.md`;
4. EV-291 only if factual causal verification is needed;
5. exact source files required for the bounded implementation.

EV-291 derived package:

```text
research/derived/2026.09.16_troll_raw55_normal_native_trigger_clear_suppression_large_log/
```

## Still paused

```text
NO permanent PhysicalFistCollision
NO promotion/copy of PhysicalFistProbe scaffolding
NO production Normal marker2 behavior until replacement-clear causal proof closes
NO Power/Sprint repeated-FIST work yet
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

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
Current frozen probe: `docs/COLLISION_RAW55_SPRINT_ORIGIN_REPEAT_FIST_REARM_PROBE.md`  
Latest canonical evidence: **EV-293** in `docs/EVIDENCE_LEDGER_291_ONWARD.md`

## Current checkpoint

```text
raw55 Quick       repeated-FIST CLOSED/PASS through EV-273
raw55 true Power  repeated-FIST CLOSED/PASS — EV-293
raw55 Normal      repeated-FIST CLOSED/PASS — EV-292
raw55 Sprint      first-contact CLOSED/PASS through EV-282; repeated-FIST implementation under local validation
raw55 two-FIST cross-family runtime CLOSED — EV-283
```

## Sprint-origin repeated-FIST implementation under local validation

Frozen contract:

```text
docs/COLLISION_RAW55_SPRINT_ORIGIN_REPEAT_FIST_REARM_PROBE.md
```

Implementation commit:

```text
32dc52dcba327e74436dcd76b70b21251e06565c
```

Required implementation base:

```text
aedc129a09f0eebc4d00c55106848f21f5d8c147
```

Independent Normal Chat source review: **PASS**.

Review findings:

```text
one commit over frozen base
one changed source file only:
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp

preserves EV-281 Sprint selective early raw55 5 -> 7 suppression
preserves original _AI_PowerAttack and Sprint StatePosition 0 -> 1 progression
preserves EV-282 first authored Sprint activation under Action9 with ClearTriggeredList=0
preserves EV-293 true-Power repeated-FIST behavior
adds one per-Sprint-proof/C1 repeatFistRearmUsed flag
preserves that flag only for matching actor/source/C1 Sprint proof refresh
later marker requires same Sprint-origin actor/source/C1 proof
later marker requires current Action2 / Family POWER Hit, exactly two FIST markers, SP1, RIGHT raw55 group7
rejects matching true-Power proof for same actor/source/C1 as ambiguous ownership
requires exact PRE aligned PC_Hero visit exactly once/count >=1
executes exactly one RIGHT TouchDamage.ClearTriggeredList()
captures/logs POST trigger state
issues no second collision-group request
writes no Action/StatePosition/SPU and performs no direct damage
```

The `OnMarkerProcessed` ordering is correct for the established Action9 -> Action2 route:

```text
first Action9 FIST
-> existing Sprint activation succeeds and returns

later Action2 FIST
-> Sprint activation fails by current Action
-> Sprint-origin repeat probe evaluates preserved Sprint proof
-> only if that path does not own the marker can ordinary true-Power repeat handling run
```

No `EngineBridge.cpp`, header API, hook, RVA, CMake, production module, stable marker/lifecycle/source change occurred. Work build status: **NOT ATTEMPTED — correctly prohibited**.

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

If build passes, Normal Chat continues with the established POP-03 deploy/hash/twin gate and POP-04 startup gate before runtime.

Frozen runtime question:

```text
Does one later-FIST ClearTriggeredList(), owned by the original Sprint Action9 proof across the same-C1 Action9 -> Action2 transition, restore a second same-C1 damage opportunity without another group request?
```

## Evidence retrieval discipline

Use:

1. this file;
2. `BETWEEN_CHATS.md`;
3. `COLLISION_RAW55_SPRINT_ORIGIN_REPEAT_FIST_REARM_PROBE.md`;
4. EV-281/EV-282 in `EVIDENCE_LEDGER_280_ONWARD.md`;
5. EV-283 in `EVIDENCE_LEDGER_283_ONWARD.md`;
6. EV-293 in `EVIDENCE_LEDGER_291_ONWARD.md` only as the clear-only repeated-contact precedent;
7. exact runtime evidence only after local validation.

## Still paused

```text
NO permanent PhysicalFistCollision
NO promotion/copy of PhysicalFistProbe scaffolding
NO permanent raw55 architecture until Sprint repeated-contact closes
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

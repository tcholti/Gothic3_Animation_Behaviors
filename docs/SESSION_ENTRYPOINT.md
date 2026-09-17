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
raw55 Sprint      first-contact CLOSED/PASS through EV-282; repeated-FIST next
raw55 two-FIST cross-family runtime CLOSED — EV-283
```

## EV-293 factual result — true Power repeated-FIST

Representative factual Action2 Power C1=6:

```text
native early 5 -> 7 suppressed at SP0
-> original _AI_PowerAttack still advances SP0 -> 1
-> RIGHT remains group5

first authored FIST at SP1
-> exact RIGHT raw55 5 -> 7
-> ClearTriggeredList=0
-> first native ONDAMAGE
-> PC_Hero becomes visited/count1

later second authored FIST, same C1/source
-> Action2 / POWER / SP1 / RIGHT group7
-> exact two-FIST decision
-> PRE PC_Hero visited exactly once/count1
-> one TouchDamage.ClearTriggeredList()
-> POST PC_Hero absent / aligned arrays
-> later second native ONDAMAGE

native exact RIGHT 7 -> 5 cleanup
-> outstanding=0
-> clean C1 finalization
```

Independent factual Power C1=52 repeats the same first activation -> first damage -> marker2 clear -> second damage -> cleanup route.

Conclusion:

> **Power repeated-FIST contact rearm is CLOSED/PASS for the tested raw55 route.** Marker1 owns the single physical `5 -> 7` opening; marker2 needs contact-bookkeeping clear only and no second group request.

Diagnostic implementation:

```text
d3388d5c38c29ea4453259e9efb3fd67916d865e
```

Local built/live DLL SHA256:

```text
1EAD1E361755368DF9DAC5C8A068549CFC63BDD95381247F41F1B4BA68693B7E
```

Canonical source:

```text
research/archive/2026.09.17_troll_raw55_power_repeat_fist_rearm.log
SHA256 = 61F572B13D78C25A7363FC85076AEC7FAEC48CD8A51EC540F012D7541D1C42D5
Git blob = ffa3777e9a9311afc77af2ffff4e84eb05fa6cdc
```

Derived retrieval package:

```text
research/derived/2026.09.17_troll_raw55_power_repeat_fist_rearm_large_log/
```

## Sprint-origin repeated-FIST boundary

EV-281/282 + EV-283 establish:

```text
Sprint origin:
Action9 / Family SPRINT
-> native early 5 -> 7 suppressed while SP0 -> 1 survives
-> first authored FIST under Action9 opens exact RIGHT 5 -> 7
-> ClearTriggeredList=0
-> first native damage

same C1 / same exact RIGHT continues
-> factual Action9 -> Action2 transition
-> RIGHT remains group7
-> later second authored FIST is delivered under current Action2 / Family POWER
```

The current Action2 label does **not** make this a true-Power-origin execution. Origin ownership remains the factual Sprint proof tied to actor + exact RIGHT source + C1 generation.

## Immediate next responsibility — BOUNDED WORK IMPLEMENTATION

Implement only:

```text
docs/COLLISION_RAW55_SPRINT_ORIGIN_REPEAT_FIST_REARM_PROBE.md
```

Frozen question:

```text
Sprint-origin proof from Action9 first-contact path remains same actor/source/C1
+ first Sprint activation already used
+ C1 has transitioned to current Action2
+ second authored FIST arrives at SP1 with RIGHT already group7
+ exact first-contact PC_Hero visit still present

perform exactly one current-RIGHT TouchDamage.ClearTriggeredList()
without another group request

Does second native damage return while native cleanup and same-C1 continuity remain healthy?
```

Expected source scope:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

Expected implementation shape:

```text
add one Sprint-proof repeatFistRearmUsed flag
preserve it only for matching actor/source/C1 proof refresh
preserve EV-281/EV-282 behavior unchanged
at later current-Action2 FIST, require Sprint-origin proof + exact same C1/source
reject an ambiguous matching true-Power proof
require exactly two FIST markers, SP1, RIGHT raw55 group7
require PRE aligned PC_Hero visited exactly once/count>=1
perform one ClearTriggeredList only
capture/log POST state
```

No `EngineBridge.cpp`, header API, new hook/RVA, CMake or production change is expected. Work build execution is not authorized. Normal Chat independently reviews before local build.

## Evidence retrieval discipline

Do not scan `research/raw/` or `research/archive/` during orientation.

Use:

1. this file;
2. `BETWEEN_CHATS.md`;
3. `COLLISION_RAW55_SPRINT_ORIGIN_REPEAT_FIST_REARM_PROBE.md`;
4. EV-281/EV-282 in `EVIDENCE_LEDGER_280_ONWARD.md`;
5. EV-283 in `EVIDENCE_LEDGER_283_ONWARD.md`;
6. EV-293 in `EVIDENCE_LEDGER_291_ONWARD.md` only for the proven clear-only repeated-contact precedent;
7. exact diagnostic source needed for implementation.

## Still paused

```text
NO permanent PhysicalFistCollision
NO promotion/copy of PhysicalFistProbe scaffolding
NO permanent raw55 architecture until Sprint repeated-contact closes
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

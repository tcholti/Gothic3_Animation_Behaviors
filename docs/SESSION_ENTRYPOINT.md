# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-14

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. `Script_FrameCollisionBehaviorTest` is the diagnostics-free behavior twin. The eventual shipped plugin remains `Script_G3AnimationBehaviors`; proven collision responsibilities must be deliberately promoted into permanent release-owned modules while `PhysicalFistProbe` and diagnostic scaffolding are excluded/removed.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe authority: `docs/COLLISION_RAW55_SPRINT_FIST_ACTIVATION_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_280_ONWARD.md` through **EV-281**  
Authoring semantics: `docs/ANIMATION_RULES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Current Checkpoint

```text
raw55 Quick       CLOSED/PASS through EV-273
raw55 true Power  CLOSED/PASS through EV-276
raw55 Normal      CLOSED/PASS through EV-279
raw55 Sprint callback ownership CLOSED/PASS — EV-280
raw55 Sprint selective group suppression CLOSED/PASS — EV-281
raw55 Sprint authored-FIST activation FROZEN NEXT PROBE
```

Raw8 FIST and raw8 Sprint remain separate proven mechanisms and must not be altered by raw55 research.

No permanent raw55 implementation is authorized yet.
Recovery Lock remains **CLOSED**.

---

## EV-280 — Sprint Callback Ownership

Factual Sprint is `Action=9 / Family=SPRINT` at the existing `_AI_PowerAttack` transport.

Repeated runtime samples prove the same original Action9 callback invocation owns both:

```text
StatePosition 0 -> 1
exact RIGHT PhysicalFist/raw55 5 -> 7
```

Whole-callback Sprint suppression is therefore rejected. Authored FIST is later delivered while Action9 / SPRINT remains factual.

---

## EV-281 — Sprint Selective Group Suppression

Implementation under test:

```text
86656776e3856d00cbf684418cabd3714b7fff74
```

Runtime:

```text
research/raw/2026.09.14_troll_raw55_sprint_group_suppression.log
raw upload commit 78fc110c5d58a890b9be8fe100fb99a533502c76
SHA256 D0A61ADB25E8F348C06B22E078F165D644680CDE31B3D3FC23B758FAA8B4FB8D
```

Repeated factual Sprint C1s prove the exact nested RIGHT raw55 opening can be suppressed while required native callback progression survives:

```text
RAW55_SPRINT_GROUP_SUPPRESSION
    Action=9
    BeforeGroup=5
    RequestedGroup=7
    StatePosition=0
    SUPPRESS_GROUP=1

RAW55_SPRINT_CALLBACK_BOUNDARY
    SameC1=1
    SameRight=1
    Action=9->9
    StatePosition=0->1
    RightGroup=5->5
    NativeResult=1
```

Representative C1=41 then receives authored `G3AB_COL_FIST` at `Action=9 / Family=SPRINT / StatePosition=1`, with RIGHT still group5 because no Sprint FIST activation intervention exists yet.

The Sprint C1 ends:

```text
Outstanding=0
Cleanup=0
Outcome=NO_OP_NO_OUTSTANDING
```

so the suppressed request creates no false offense obligation or repair need.

No true-Power `RAW55_POWER_CALLBACK_BOUNDARY` or `RAW55_POWER_GROUP_SUPPRESSION` event appears in this causal run. The PowerAttack-named motions exercised here are factual Sprint/Action9.

User visually observed no damage from the repeated Power-animation attacks, consistent with the source remaining group5.

POP-07 retrieval package:

```text
research/derived/2026.09.14_troll_raw55_sprint_group_suppression_large_log/
```

The package includes event/signal indexes plus complete line-numbered source chunks and is tied to the raw log by SHA256.

---

## Current Frozen Responsibility — Work Sprint Authored-FIST Activation Probe

Frozen authority:

```text
docs/COLLISION_RAW55_SPRINT_FIST_ACTIVATION_PROBE.md
```

Single causal question:

```text
after proven early Action9 5 -> 7 suppression,
can authored G3AB_COL_FIST at factual Sprint StatePosition=1
activate only the exact current equipped RIGHT PhysicalFist/raw55 source 5 -> 7,
with ClearTriggeredList=0,
then allow native contact/damage and native cleanup?
```

Implementation boundary:

```text
PhysicalFistProbe owns Sprint research state/policy
preserve EV-281 selective suppression unchanged
preserve original Sprint callback exactly once
extend SprintEarlySuppressionProof only as needed for activationUsed
reuse existing OnMarkerProcessed delegation
require Action9 / Family SPRINT / Hit / StatePosition1
require same actor + exact RIGHT source + C1 suppression proof
request exact RIGHT group7 once
log CORE RAW55_SPRINT_FIST_ACTIVATION_PROBE
ClearTriggeredList=0
```

`EngineBridge` should remain unchanged. Stable marker semantics remain unchanged. No custom damage, cleanup compensation, StatePosition/SPU write, new hook/RVA, timer, polling or family generalization is authorized.

Work must not build. Source/static audit -> publish -> STOP.

After independent Normal Chat source review, User + Normal Chat own build/deploy/runtime evidence.

Preferred future runtime artifact:

```text
research/raw/2026.09.14_troll_raw55_sprint_fist_activation.log
```

---

## Still Paused

```text
NO permanent raw55 architecture
NO promotion/copy of PhysicalFistProbe into release code
NO Sprint ClearTriggeredList/rearm assumption
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```

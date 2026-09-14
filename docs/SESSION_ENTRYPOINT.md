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
raw55 Sprint authored-FIST activation IMPLEMENTED + INDEPENDENTLY REVIEWED; RUNTIME PENDING
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

Implementation:

```text
86656776e3856d00cbf684418cabd3714b7fff74
```

Runtime:

```text
research/raw/2026.09.14_troll_raw55_sprint_group_suppression.log
raw upload commit 78fc110c5d58a890b9be8fe100fb99a533502c76
SHA256 D0A61ADB25E8F348C06B22E078F165D644680CDE31B3D3FC23B758FAA8B4FB8D
```

Repeated factual Sprint C1s prove:

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

Authored `G3AB_COL_FIST` then arrives at factual Action9/Sprint/StatePosition1 while RIGHT remains group5. Completed Sprint C1s finalize `Outstanding=0`, `Cleanup=0`, `NO_OP_NO_OUTSTANDING`; therefore suppressed opening creates no false offense obligation or repair.

---

## Current Reviewed Implementation — Sprint Authored-FIST Activation

Frozen authority:

```text
docs/COLLISION_RAW55_SPRINT_FIST_ACTIVATION_PROBE.md
```

Frozen base:

```text
c09c5bdac60d30b02ec10f2fa51f59da1b816109
```

Work implementation:

```text
545863c0c522b2cd2d2748f6823a23662bf0ffbf
```

Normal Chat independent source review: **PASS**.

Remote comparison:

```text
exactly one commit ahead of frozen base
only changed source:
    prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
+103 / -0
```

Reviewed behavior:

```text
SprintEarlySuppressionProof now carries activationUsed
same-C1/same-source repeated suppression preserves activationUsed
TryApplySprintFistActivationProbe() runs on existing OnMarkerProcessed seam
requires current factual Action9 + Family SPRINT Hit
requires exact same actor/current equipped RIGHT/C1 as prior EV-281 proof
requires exact FIST / stable UNSUPPORTED_MISSING_SOURCE marker shape
requires raw8 resolver absent
requires exact RIGHT PhysicalFist/raw55 still group5
requires StatePosition=1
one-shot marks activationUsed then requests exact RIGHT group7 through ordinary setter
logs CORE RAW55_SPRINT_FIST_ACTIVATION_PROBE
ClearTriggeredList=0
```

Marker-dispatch ordering is safe: preceding Normal/Power activation probes reject factual Action9; Sprint acts before Quick-specific pre-state/rearm logic.

No EngineBridge/CMake/release change. No ClearTriggeredList, custom damage, StatePosition/SPU write, cleanup compensation, new hook/RVA/timer/polling, or family generalization.

Build: **NOT RUN per Work boundary**.  
Runtime: **NOT YET TESTED**.

No new Work/source task is authorized until this runtime evidence transaction closes.

---

## Current Responsibility — User + Normal Chat

```text
sync local branch to current remote HEAD
build Script_FrameCollisionTest
manually deploy diagnostic DLL
verify built/live SHA256 equality
run Troll until factual Action9 / Family SPRINT
preserve raw log unchanged
copy raw log into research/raw with final filename
drag raw log onto Prepare-Log shortcut
commit/push raw + generated derived package
Normal Chat closes POP-06 transaction
```

Preferred artifact:

```text
research/raw/2026.09.14_troll_raw55_sprint_fist_activation.log
```

Primary expected causal chain:

```text
RAW55_SPRINT_GROUP_SUPPRESSION
    Action=9
    BeforeGroup=5
    RequestedGroup=7
    StatePosition=0
    SUPPRESS_GROUP=1

RAW55_SPRINT_CALLBACK_BOUNDARY
    StatePosition=0->1
    RightGroup=5->5
    NativeResult=1

authored FIST at Action9 / SPRINT / StatePosition1

RAW55_SPRINT_FIST_ACTIVATION_PROBE
    GroupBefore=5
    RequestedGroup=7
    GroupAfter=7
    EarlySuppressionProof=1
    ClearTriggeredList=0
    ACTIVATE_FIST=1
```

Then determine whether native damage follows and whether Gothic later performs exact RIGHT `7 -> 5` cleanup with clean C1 fulfillment/finalization.

If group7 opens but damage does not return despite contact, the next question is Sprint-specific contact/rearm. Do not infer `ClearTriggeredList` from Quick without a dedicated probe.

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

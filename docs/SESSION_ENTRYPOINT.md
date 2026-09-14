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
Current frozen probe authority: `docs/COLLISION_RAW55_SPRINT_GROUP_SUPPRESSION_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_280_ONWARD.md` through **EV-280**  
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
raw55 Sprint selective group suppression CURRENT RUNTIME VALIDATION
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

with `SameC1=1`, `SameRight=1`, `Action=9->9`, `NativeResult=1`.

Authored FIST is later delivered while Action9 / SPRINT remains factual. Native damage and native exact RIGHT `7 -> 5` cleanup occur in exercised executions. Whole-callback Sprint suppression is rejected.

Later callbacks in the same PowerAttack-named motion may become factual Action2 / POWER after contact; animation filename is not Sprint authority.

Runtime artifact:

```text
research/raw/2026.09.14_troll_raw55_sprint_fist_activation.log
upload commit 077aeea6943fddb82d001031d95e40af968fd459
```

The filename says `fist_activation`, but that build contained only callback observation.

The same mixed log also supports legitimate-reaction cleanup: sampled User-induced hit reactions clean native `7 -> 5` and reach `Outstanding=0` before `_AI_Stumble` replacement; there are no `ReplacedOutstanding=1` or repair events in that run.

---

## Current Reviewed Implementation — Sprint Selective Group Suppression

Frozen base:

```text
0a002405ce2fc4d6d8a2024f07c361137a966c38
```

Work implementation:

```text
86656776e3856d00cbf684418cabd3714b7fff74
```

Normal Chat independent source review: **PASS**.

Only changed source file:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

The diagnostic intervention:

```text
reuses existing SprintCallbackObservation
requires exact active factual Action9 Sprint scope
requires exact actor + current equipped RIGHT source + same C1
requires PhysicalFist/raw55
requires current/before group5 and requested group7
requires Sprint Hit eligibility
suppresses only that exact mutation
logs CORE RAW55_SPRINT_GROUP_SUPPRESSION
```

The current factual Action9 check prevents later Action2 callbacks from borrowing Sprint suppression. No EngineBridge/CMake/release changes were made.

Explicitly absent:

```text
NO whole-callback Sprint suppression
NO Sprint authored-FIST activation
NO Sprint ClearTriggeredList
NO StatePosition/SPU write
NO custom damage
NO cleanup compensation
NO lifecycle-policy change
NO new hook/RVA/timer/polling
```

Build: **NOT RUN per Work boundary**.  
Runtime: **NOT YET TESTED**.

No new Work/source task is authorized until the runtime evidence transaction closes.

---

## Current Responsibility — User + Normal Chat

```text
sync local branch
build Script_FrameCollisionTest
manually deploy diagnostic DLL
verify built/live SHA256 equality
run Troll until factual Action9 / Family SPRINT
preserve raw log unchanged
commit/push raw evidence
Normal Chat closes POP-06 transaction
```

Preferred artifact:

```text
research/raw/2026.09.14_troll_raw55_sprint_group_suppression.log
```

Primary expected positive result:

```text
RAW55_SPRINT_GROUP_SUPPRESSION
    Action=9
    BeforeGroup=5
    RequestedGroup=7
    SUPPRESS_GROUP=1

RAW55_SPRINT_CALLBACK_BOUNDARY
    SameC1=1
    SameRight=1
    Action=9->9
    StatePosition=0->1
    RightGroup=5->5
    NativeResult=1
```

Also determine whether:

```text
authored FIST still arrives at StatePosition1
RIGHT stays group5 through FIST
another raw55 5 -> 7 occurs later
factual Action2 later attempts an opening and is caught by existing Power suppression
any offense obligation or repair appears
```

Do not implement authored-FIST activation/rearm until this runtime is closed.

---

## Still Paused

```text
NO permanent raw55 architecture
NO promotion/copy of PhysicalFistProbe into release code
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```

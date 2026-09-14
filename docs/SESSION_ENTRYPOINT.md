# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-14

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. `Script_FrameCollisionBehaviorTest` is the diagnostics-free behavior twin used to verify preprocessing/source separation during development. The eventual shipped plugin target remains `Script_G3AnimationBehaviors`; proven collision behavior must be deliberately promoted into permanent release-owned modules there, while `PhysicalFistProbe` and diagnostic scaffolding are excluded/removed.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe authority: `docs/COLLISION_RAW55_SPRINT_GROUP_SUPPRESSION_PROBE.md`  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_280_ONWARD.md` through **EV-280**; EV-274–EV-279 remain in `docs/EVIDENCE_LEDGER_274_ONWARD.md`; EV-269–EV-273 remain in `docs/EVIDENCE_LEDGER_269_ONWARD.md`; earlier evidence remains in preceding ledgers  
Authoring semantics: `docs/ANIMATION_RULES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Current Checkpoint

Raw55 Quick is closed for the tested scope through EV-273:

```text
preserve original Quick callback/state progression
exact authored FIST can open exact RIGHT PhysicalFist/raw55
Quick tested contact requires ClearTriggeredList rearm
later authored FIST can rearm another contact in same C1
native cleanup returns exact RIGHT 7 -> 5
```

True raw55 Power is closed through EV-276:

```text
preserve original factual Action2 / Family POWER _AI_PowerAttack
suppress only premature exact scoped RIGHT raw55 5 -> 7
native StatePosition 0 -> 1 survives
authored FIST activates exact RIGHT raw55 5 -> 7
ClearTriggeredList=0
native damage returns
native cleanup returns exact RIGHT 7 -> 5
```

Raw55 Normal is closed through EV-279:

```text
same original _AI_Attack invocation owns StatePosition 0 -> 1 + RIGHT raw55 5 -> 7
exact premature 5 -> 7 can be suppressed while StatePosition 0 -> 1 survives
authored FIST then opens exact RIGHT raw55 5 -> 7 at StatePosition1
ClearTriggeredList=0
native OnDamage returns
native cleanup returns 7 -> 5
C1 finalizes cleanly
```

Raw55 Sprint callback ownership is now closed through EV-280:

```text
factual Sprint = Action9 / Family SPRINT
existing _AI_PowerAttack transport remains authoritative
same original Action9 callback invocation owns:
    StatePosition 0 -> 1
    exact RIGHT PhysicalFist/raw55 5 -> 7
same C1 later reaches authored FIST while Action9 / SPRINT is still factual
native damage occurs in exercised Sprint executions
native exact RIGHT cleanup 7 -> 5 fulfills the obligation
whole-callback Sprint suppression is rejected
```

Later callbacks in the same PowerAttack-named motion may become factual Action2 / Family POWER after contact. Animation filename is therefore not Sprint authority; current and future Sprint policy must key to factual Action9 / exact Sprint callback scope.

Canonical runtime evidence is through **EV-280**. Recovery Lock remains **CLOSED**.

No permanent raw55 implementation is authorized yet.

---

## Closed / Current Collision Boundary

```text
C1-R1 lifecycle safety                         CLOSED — EV-206–EV-207
collision architecture verification            CLOSED/PASS — EV-208–EV-215
Power / Pierce / SimpleWhirl / Hack equipped   CLOSED/PASS — EV-216–EV-244
raw8 FIST shared mechanism + controls           CLOSED/PASS through EV-271
raw8 Sprint                                     CLOSED/PASS — EV-251
native NPC equipped controls                    CLOSED/PASS — EV-252–EV-258
Stalker factual Axe/raw52 control               CLOSED/PASS — EV-259
fall-down logger boundary                       CLOSED — EV-260
BluntArrow/BluntBolt classification             CLOSED — EV-261
raw55 early callback causal ownership           CONFIRMED — EV-262
raw55 uniform whole-callback production gate    FAILED/REJECTED — EV-262
raw55 Quick mechanism                           CLOSED/PASS through EV-273
raw55 true Power mechanism                      CLOSED/PASS through EV-276
raw55 Normal mechanism                          CLOSED/PASS through EV-279
raw55 Sprint callback ownership                 CLOSED/PASS — EV-280
raw55 Sprint selective group suppression        CURRENT RESEARCH
```

Raw8 FIST remains a separate proven mechanism. Raw55 findings must not be generalized back onto raw8 or across raw55 families without evidence.

---

## EV-280 Runtime Result

Implementation under test:

```text
5c9e40c53162c4f16099107a44892e8c03f2bdaf
```

Runtime artifact:

```text
research/raw/2026.09.14_troll_raw55_sprint_fist_activation.log
runtime upload commit 077aeea6943fddb82d001031d95e40af968fd459
```

The artifact filename says `fist_activation`, but the binary contained only the Sprint callback-boundary observer; no Sprint authored-FIST intervention existed.

Repeated factual Sprint C1s include 8, 34, 45, 58, 73, 85, 96, 107 and 118. Their decisive Action9 callback has the repeated shape:

```text
CORE COLLISION_GROUP ... TrollFist UseType=55 Requested=7 Before=5 After=7
CORE RAW55_SPRINT_CALLBACK_BOUNDARY ...
    SameC1=1
    SameRight=1
    Action=9->9
    StatePosition=0->1
    RightGroup=5->7
    NativeResult=1
```

Authored FIST is then delivered at StatePosition1 while Action9 / Family SPRINT remains factual. Native damage and later exact RIGHT `7 -> 5` cleanup occur in exercised executions. Representative C1s finalize with `Outstanding=0`, `Cleanup=1`, `PhysicalChanged=0`, `NO_OP_NO_OUTSTANDING`.

### Supporting interruption result

The same mixed run includes many User-induced Troll hit reactions. Targeted checks found:

```text
ReplacedOutstanding=1      -> none
REPAIRED_TO_ITEM_EQUIPPED  -> none
```

Representative interrupted attacks perform native `TrollFist 7 -> 5`, log `C1 CLEANUP FULFILLED`, and only then enter a new `_AI_Stumble` generation with `ReplacedOutstanding=0`.

This supports the existing legitimate-reaction rule: normal hit reaction can interrupt the attack while native cleanup fulfills the exact-source obligation before replacement. It is not the destructive-continuation-loss / C1-R1 repair case.

---

## Current Frozen Responsibility — Raw55 Sprint Selective Group Suppression

Authority:

```text
docs/COLLISION_RAW55_SPRINT_GROUP_SUPPRESSION_PROBE.md
```

Single question:

> While the exact marked factual raw55 Sprint / Action9 `_AI_PowerAttack` callback executes normally, can only its exact nested RIGHT PhysicalFist/raw55 `5 -> 7` request be suppressed while native `StatePosition 0 -> 1` survives?

Frozen diagnostic mechanism:

```text
reuse existing reentrancy-safe SprintCallbackObservation
require exact factual Action9 / Family SPRINT scope
inside existing SetCollisionGroup delegation:
    exact scoped actor + RIGHT source + C1
    PhysicalFist/raw55
    current factual Action9
    before/current group5
    requested group7
-> suppress only that physical mutation
-> emit CORE RAW55_SPRINT_GROUP_SUPPRESSION
```

Expected positive separability shape:

```text
CORE RAW55_SPRINT_GROUP_SUPPRESSION ... SUPPRESS_GROUP=1
CORE RAW55_SPRINT_CALLBACK_BOUNDARY ...
    SameC1=1
    SameRight=1
    Action=9->9
    StatePosition=0->1
    RightGroup=5->5
    NativeResult=1
```

A suppressed request must not call original SetCollisionGroup and must not fabricate an offense obligation.

Important control: if factual Action later becomes 2 in the same Sprint-origin motion and another `5 -> 7` is attempted, existing true-Power suppression/logging may expose it. That is a real second activation path and must be investigated rather than hidden.

No Sprint authored-FIST activation or `ClearTriggeredList` belongs in this task.

---

## Still Paused

Until Sprint raw55 mechanism is sufficiently proven or explicitly deferred:

```text
NO permanent raw55 implementation
NO promotion/copy of PhysicalFistProbe into release code
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```

# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-14

## Current Bridge — EV-281 CLOSED; SPRINT FIST ACTIVATION IMPLEMENTATION REVIEWED; RUNTIME PENDING

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical runtime evidence is through **EV-281**.

No permanent raw55 implementation is authorized yet.
No new Work/source task is authorized before the Sprint authored-FIST activation runtime transaction is closed.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_RAW55_SPRINT_FIST_ACTIVATION_PROBE.md
4. EVIDENCE_LEDGER_280_ONWARD.md — EV-280 and EV-281
5. EVIDENCE_LEDGER_274_ONWARD.md — EV-274 through EV-279 only as needed for Power/Normal comparison
6. exact PhysicalFistProbe source only if runtime interpretation requires it
```

---

## Closed Evidence — EV-280 Sprint Callback Compound Ownership

Factual raw55 Sprint is `Action=9 / Family=SPRINT` at the existing `_AI_PowerAttack` transport.

EV-280 proves the same original Action9 callback invocation owns both:

```text
StatePosition 0 -> 1
exact RIGHT TrollFist/raw55 5 -> 7
```

Therefore whole-callback Sprint suppression is rejected. Authored FIST arrives later while Action9/SP1 is still factual. Animation filename is not family authority.

---

## Closed Evidence — EV-281 Sprint Selective Group Suppression

Probe implementation:

```text
86656776e3856d00cbf684418cabd3714b7fff74
```

Canonical runtime:

```text
research/raw/2026.09.14_troll_raw55_sprint_group_suppression.log
raw upload commit 78fc110c5d58a890b9be8fe100fb99a533502c76
SHA256 D0A61ADB25E8F348C06B22E078F165D644680CDE31B3D3FC23B758FAA8B4FB8D
```

POP-07 retrieval package:

```text
research/derived/2026.09.14_troll_raw55_sprint_group_suppression_large_log/
chat-friendly package committed through 96b47af88a9b72e4f1f315ad2bbb2d60d65de7c5
```

Repeated factual Sprint C1s including 41, 50, 57, 78, 107 and 138 prove:

```text
CORE RAW55_SPRINT_GROUP_SUPPRESSION
    Action=9
    Right=TrollFist
    RightUseType=55
    RequestedGroup=7
    BeforeGroup=5
    StatePosition=0
    SUPPRESS_GROUP=1

CORE RAW55_SPRINT_CALLBACK_BOUNDARY
    SameC1=1
    SameRight=1
    Action=9->9
    Phase=1->1
    StatePosition=0->1
    RightGroup=5->5
    NativeResult=1
```

Representative C1=41 then receives authored `G3AB_COL_FIST` at factual `Action=9 / Family=SPRINT / StatePosition=1` while RIGHT remains group5.

Sprint C1 finalization is clean:

```text
TrollFist RIGHT
Outstanding=0
Cleanup=0
Outcome=NO_OP_NO_OUTSTANDING
```

The suppressed opening therefore creates no fake offense obligation, cleanup requirement or repair.

The causal run contains no `RAW55_POWER_CALLBACK_BOUNDARY` and no `RAW55_POWER_GROUP_SUPPRESSION`; the PowerAttack-named executions exercised here were factual Sprint/Action9.

User visually observed repeated Power-animation attacks did not damage the character, consistent with RIGHT remaining group5.

---

## Reviewed Sprint Authored-FIST Activation Implementation

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
message: Add raw55 Sprint FIST activation probe
```

Independent Normal Chat source review: **PASS**.

Remote comparison proves:

```text
exactly one commit ahead of frozen base
only changed file:
    prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
+103 / -0
no EngineBridge change
no CMake change
```

Reviewed implementation shape:

```text
extends SprintEarlySuppressionProof with activationUsed
preserves activationUsed across repeated same-C1/same-source suppression callbacks
adds TryApplySprintFistActivationProbe()
reuses existing PhysicalFistProbe::OnMarkerProcessed seam
requires:
    valid current C1 == stored Sprint suppression-proof C1
    same actor
    exact current equipped RIGHT == stored proof source
    prior Sprint early suppression proof
    activation not already used
    exact FIST marker / stable UNSUPPORTED_MISSING_SOURCE result
    factual current Action9
    Family SPRINT Hit eligibility
    valid matching marked motion with only FIST source semantics
    raw8 resolver absent
    exact RIGHT PhysicalFist/raw55
    RIGHT current group5
    StatePosition=1
matching event sets activationUsed and requests exact RIGHT group7 once
emits CORE RAW55_SPRINT_FIST_ACTIVATION_PROBE
ClearTriggeredList=0
```

Marker dispatch order is safe: Normal and Power branches precede Sprint but reject Action9 by their own family/action gates; Sprint executes before Quick-specific pre-state/rearm logic.

No Sprint `ClearTriggeredList`, no custom damage, no StatePosition/SPU write, no cleanup compensation, no new hook/RVA/CMake/release change. Quick/Power/Normal/raw8 behavior is unchanged.

Work static/source audit reported PASS including `git diff --check`. Normal Chat found no material contradiction.

Build status: **NOT RUN per task boundary**.
Runtime status: **NOT YET TESTED**.

---

## Exact Next Step — User + Normal Chat Runtime

Do not start another Work/source task.

```text
1. sync local branch to current remote HEAD
2. build Script_FrameCollisionTest
3. manually deploy Script_FrameCollisionTest.dll
4. verify built/live SHA256 equality
5. run Troll until factual Action9 / Family SPRINT occurs
6. preserve raw diagnostic log unchanged
7. copy raw log into research/raw with final filename
8. drag the raw log onto Prepare-Log shortcut to generate POP-07 package
9. commit/push raw + derived package
10. Normal Chat closes the evidence transaction
```

Preferred runtime artifact:

```text
research/raw/2026.09.14_troll_raw55_sprint_fist_activation.log
```

Primary expected positive chain:

```text
CORE RAW55_SPRINT_GROUP_SUPPRESSION
    Action=9
    RequestedGroup=7
    BeforeGroup=5
    StatePosition=0
    SUPPRESS_GROUP=1

CORE RAW55_SPRINT_CALLBACK_BOUNDARY
    SameC1=1
    SameRight=1
    Action=9->9
    StatePosition=0->1
    RightGroup=5->5
    NativeResult=1

authored FIST at factual Action9 / Family SPRINT / StatePosition1

CORE RAW55_SPRINT_FIST_ACTIVATION_PROBE
    GroupBefore=5
    RequestedGroup=7
    GroupAfter=7
    EarlySuppressionProof=1
    ClearTriggeredList=0
    ACTIVATE_FIST=1
```

Then determine causally:

```text
does native contact/damage against PC_Hero occur after authored opening?
does Gothic later clean exact RIGHT 7 -> 5?
does C1 obligation fulfill and finalize cleanly?
```

Interpretation boundary:

```text
if authored FIST opens group7 and damage occurs:
    Sprint activation alone is sufficient, matching tested Power/Normal first-contact behavior

if authored FIST opens group7 but damage does not occur despite contact:
    activation is proven but contact/rearm remains a separate Sprint question
    do NOT infer or add ClearTriggeredList from Quick without a dedicated probe
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

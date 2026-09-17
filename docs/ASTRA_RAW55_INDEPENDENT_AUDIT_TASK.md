# GPT-6 Astra — Independent Permanent raw55 Implementation Audit

**Status:** Saved read-only review task for model-quality evaluation  
**Date:** 2026-09-17  
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

Use GPT-6 Astra as an independent, adversarial, read-only reviewer of the mature permanent raw55 implementation. This task is intentionally broader than the normal bounded implementation review because the purpose is to evaluate whether Astra finds a real engineering issue that GPT-5.6 Sol missed.

This task is **not** project authority by itself. Astra must not change repository state. Any finding must later be independently checked by Normal Chat + User against source, frozen architecture, and canonical evidence before it can alter project conclusions or implementation.

The task should be run when the user's Astra allowance is fully reset so the model can complete the audit without an artificial usage interruption.

---

## Paste the following task into Astra

```text
GOTHIC 3 — INDEPENDENT PERMANENT RAW55 IMPLEMENTATION AUDIT

This is a READ-ONLY FORMAL ENGINEERING REVIEW.

Do NOT modify repository files.
Do NOT create commits.
Do NOT implement fixes.
Do NOT build.
Do NOT treat previous reviewer conclusions as authoritative.

Repository:
https://github.com/tcholti/Gothic3_Animation_Behaviors.git

Branch:
docs/collision-source-evidence

Review source state at:

314f284dbaaf05c5f185811aab107e84f1d434ce

The purpose of this task is to independently determine whether the permanent raw55 PhysicalFist implementation is technically correct, evidence-backed, minimal, and architecturally sound.

This is deliberately an independent review. Do not search commit messages or documentation merely to discover whether another reviewer previously passed or failed the implementation. Derive your own conclusions from the architecture contract, source, APIs, and evidence.

## Formal review preflight

Before evaluating the implementation, apply POP-10 in:

docs/PROJECT_OPERATING_PROCEDURES.md

Read/confirm:

1. docs/README.md §0
2. the intended Purpose / Scope / owner of each review target
3. docs/SESSION_ENTRYPOINT.md
4. docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md
5. docs/FEATURE_DEVELOPMENT_METHOD.md

Do not begin substantive review until that preflight is complete.

Use docs/BETWEEN_CHATS.md only for current repository orientation, not as evidence that the implementation is correct.

## Review target

Primary permanent feature:

prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.h

Review its integration through only the relevant portions of:

prototypes/Script_FrameCollisionTest/EngineBridge.cpp
prototypes/Script_FrameCollisionTest/CollisionSourceOperations.cpp
prototypes/Script_FrameCollisionTest/CollisionSourceOperations.h
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.cpp
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.h
prototypes/Script_FrameCollisionTest/CollisionSources.cpp
prototypes/Script_FrameCollisionTest/CollisionSources.h
prototypes/Script_FrameCollisionTest/CollisionLifecycleGuard.cpp
prototypes/Script_FrameCollisionTest/Raw8FistCollision.cpp
prototypes/Script_FrameCollisionTest/CMakeLists.txt

Also review the current raw55-related CORE diagnostic classification in:

prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp

but keep diagnostics conceptually separate from production behavior.

## Evidence authority

Reconstruct only the evidence necessary to validate production assumptions.

The important closed evidence is:

- Quick repeated-FIST: EV-265 through EV-273
- Normal native separation / repeated-FIST: EV-277 through EV-279 and EV-286 through EV-292
- true Power: EV-274 through EV-276 and EV-293
- Sprint: EV-280 through EV-283 and EV-294

Use:

docs/EVIDENCE_INDEX.md

to locate only the relevant canonical evidence.

Do not broadly scan old research logs or reconstruct the entire collision project.

## Questions the audit must answer

### 1. Ownership and eligibility

Verify that raw55 ownership is restricted to the exact proven shape:

- valid actor/current C1;
- supported family Normal / Quick / Power / Sprint;
- exact current motion found and scanned;
- FIST-only marker ownership;
- 1 or 2 authored FIST markers;
- no RIGHT / LEFT / BOTH / OFF marker mixing;
- required source mask none;
- raw8 Fist resolver absent;
- exact current RIGHT source exists;
- RIGHT UseType PhysicalFist/raw55.

Look for any route where unsupported or unmarked behavior could accidentally be claimed.

### 2. Execution identity

Audit the C1-scoped execution record.

Verify:

- actor + C1 + exact RIGHT source identity;
- immutable origin family;
- correct animation identity;
- authored/accepted FIST occurrence budget;
- duplicate protection;
- no execution reset from StatePosition, StateTime, Action, or collision-group guesses;
- Sprint Action9 -> Action2 preserves Sprint origin;
- current Action2 alone cannot turn a Sprint-origin execution into true Power.

Look especially for stale state, actor/source reuse, C1 replacement, or map-lifetime problems.

### 3. Native callback transport

Verify EngineBridge remains transport-only.

Check:

- original callbacks remain called;
- no whole-callback suppression;
- stack-scoped callback attribution cannot leak across nested/reentrant calls;
- Normal, Quick, true Power and Sprint are factually distinguished;
- no feature policy has leaked unnecessarily into EngineBridge.

Pay particular attention to reentrancy and nested callback safety.

### 4. Premature native 5 -> 7 suppression

Verify suppression can affect ONLY:

- exact current RIGHT raw55 source;
- exact actor/C1/source callback scope;
- before group 5;
- requested group 7;
- before first authored FIST;
- supported marked raw55 execution.

Check that it cannot suppress:

- unmarked native raw55 behavior;
- unrelated sources;
- final 7 -> 5 cleanup;
- later ordinary 7 -> 7 calls;
- other actors or generations.

### 5. First-FIST semantics

Verify implementation matches the evidence exactly:

Quick:
- SP0 OR proven late ordering;
- 5 -> 7;
- clear once.

Normal SP0:
- 5 -> 7;
- clear once;
- arm exact native-clear suppression.

Normal SP1 after premature-open suppression:
- 5 -> 7;
- no first-marker clear.

Power:
- true Power origin;
- SP1;
- prior premature-open suppression;
- 5 -> 7;
- no clear.

Sprint:
- Sprint origin;
- Action9/SP1;
- prior premature-open suppression;
- 5 -> 7;
- no clear.

No Action, StatePosition, SPU or direct-damage writes are permitted.

### 6. Normal hidden native ALL-clear suppression

Audit the permanent no-argument eCTrigger_PS::ClearTriggeredList() hook very carefully.

Suppression must require all of:

- eligible Normal callback scope;
- same actor/C1/exact RIGHT raw55 execution;
- first FIST already accepted;
- firstMarkerStatePosition == 0;
- exact RIGHT TouchDamage trigger;
- caller exactly Script_Game.dll + 0x386C6;
- one-shot suppression.

Check hook ownership and calling convention/API correctness.

Look for false-positive suppression, missed cleanup, reentrancy problems, stale callback scope, or caller-address assumptions that are weaker than the frozen contract.

### 7. Repeated FIST

For marker2 verify:

- same actor/C1/exact source;
- exactly two authored FIST markers;
- first already accepted;
- group currently 7;
- accepted count exactly 1;
- correct current-family rule;
- Sprint may be current Power/Action2 while origin remains Sprint.

Operation must be ONLY:

ClearTriggeredList()

There must be:

- no second SetCollisionGroup request;
- no direct damage;
- no target-specific policy;
- no PC_Hero dependency;
- no StatePosition/Action write.

### 8. Cleanup / lifecycle

Verify ordinary raw55 termination remains Gothic-owned:

7 -> 5

and that CollisionLifecycleGuard merely observes fulfillment / retains its existing backup responsibility.

Look for:

- duplicate cleanup obligations;
- raw55-specific forced cleanup;
- outstanding obligations that can survive legitimate completion;
- accidental interaction with C1-R1;
- lifecycle state that raw55 can leave behind after interrupted or replaced generations.

### 9. Raw8 and equipped coexistence

Audit specifically for regressions in:

- raw8 FIST;
- equipped RIGHT / LEFT / BOTH / OFF;
- Hack;
- generic marker occurrence bookkeeping;
- existing ActivateOrRearm() semantics.

The raw55 implementation must not have generalized its special Sprint occurrence model into the stable equipped/raw8 path.

### 10. Diagnostics

Review the current diagnostic classifier after commit:

314f284dbaaf05c5f185811aab107e84f1d434ce

Verify that the logger now recognizes the factual supported raw55 candidate shape without silently copying permanent feature policy into diagnostics.

Diagnostics must not become a second behavior authority.

## Review standard

Do not report speculative concerns merely because something could theoretically be rewritten.

For every finding, classify it as one of:

- CONFIRMED DEFECT
- CONTRACT VIOLATION
- EVIDENCE GAP
- DEFENSIBLE RISK
- NON-ISSUE

For any item above NON-ISSUE, provide:

1. exact file/function;
2. exact factual source behavior;
3. exact frozen contract/evidence it conflicts with;
4. causal failure route;
5. whether it can affect release behavior, diagnostics only, or maintainability only;
6. smallest correction direction — but DO NOT implement it.

Do not recommend broad refactors without a demonstrated correctness reason.

Do not treat style preferences as engineering defects.

## Required final report

Return:

1. Preflight status
2. Files actually inspected
3. Architecture/ownership assessment
4. Confirmed findings, ordered by technical consequence
5. Rejected concerns / things checked and found correct
6. Evidence-to-code consistency assessment
7. Raw8/equipped coexistence assessment
8. Diagnostic-separation assessment
9. Residual uncertainties, if any
10. Overall source-review result:
   - PASS
   - PASS WITH NON-BLOCKING FINDINGS
   - BLOCKED BY CONFIRMED DEFECT

Do not change any file.

Do not publish anything.

This task ends with the review report.
```

---

## After Astra returns

Do not accept or reject findings by model reputation.

Normal Chat should independently verify each substantive finding against:

1. exact source at the reviewed commit;
2. `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`;
3. only the smallest relevant canonical EV evidence;
4. protected raw8/equipped/lifecycle behavior.

Then compare Astra vs Sol on concrete review quality:

```text
confirmed defects found
false positives
missed issues
scope discipline
evidence discipline
architecture understanding
cost / usage consumed
```

The purpose is to decide empirically whether Astra adds enough engineering value for this project to justify its much higher usage cost.

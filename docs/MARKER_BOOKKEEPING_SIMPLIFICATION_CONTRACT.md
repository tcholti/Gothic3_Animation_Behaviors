# Marker Bookkeeping Simplification Contract

**Status:** IMPLEMENTED + VALIDATED — GATE 4 CLOSED/PASS  
**Date:** 2026-09-01  
**Scope:** marker execution identity/bookkeeping only

## 1. Purpose

Gate 4 audited the current `FrameCollisionMarkers` bookkeeping against the historical marker regressions and the proven C1 lifecycle authority.

The accepted result is deliberately narrow:

> **Use the existing monotonic C1 generation as durable marker-execution identity where that generation is already valid; remove older marker-local guesses about whether a new attack execution has begun. Preserve all independent authored-marker semantics and protections.**

This is not a C1 redesign, not a marker redesign, and not an attack-family expansion.

## 2. Evidence basis

Mandatory causal route:

```text
EV-066–EV-075
EV-108–EV-117
EV-128–EV-133
EV-143–EV-147
EV-155–EV-156
EV-167
EV-182–EV-196
EV-206–EV-207
EV-209–EV-213
COLLISION_LIFECYCLE_PLAN.md §9
```

Key historical distinction:

- EV-131 proved occurrence-budget state could leak across two separate attacks when marker-local source/motion/action/phase/state-time identity failed to establish a fresh execution.
- EV-133 proved natural marker-owned source retirement fixed that tested case; callback state-time rollback was not the observed boundary that supplied the fix.
- EV-167 explicitly classifies `RetireMarkerOwnedSource()` as marker-bookkeeping retirement, separate from physical cleanup.
- C1 now has the durable monotonic attack generation that the old marker module did not have.
- EV-213 closes the implementation and regression gate for replacing the old inferred execution boundary with C1 generation identity.

## 3. Classification result

### A — execution-lifetime inference superseded by C1 generation

The following responsibilities were removed or consolidated:

```text
ObserveControlledAttackCallback() retirement based on:
- source-key change
- animation/action/phase change
- state-time rollback

MarkerExecutionBudget::lastControlledCallbackStateTime

MarkerWindowStillMatchesActorExecution() as an execution-lifetime test

TryConsumeAuthoredMarkerOccurrence() deciding "new execution" from:
- source pointer changes
- motion filename changes
- action changes
- phase changes
- state-time rollback
- authored-count changes

RetireMarkerOwnedSource() deciding that the whole marker execution ended by
re-running motion/action/phase/state-time heuristics
```

These mechanisms were historical substitutes for a durable execution identity.

### B — independent marker invariants that remain mandatory

Preserve unchanged in meaning:

```text
exact current-motion marker ownership
Normal / Quick / full-Whirl supported-family predicates
required RIGHT/LEFT source preflight
RIGHT / LEFT / BOTH / OFF exact-set semantics
marker-owned current active source mask/window
authored occurrence budgets
same-update duplicate/replay suppression
repeated-contact ClearTriggeredList rearm
exact-set source switching
natural SetCollisionGroup retirement of the affected marker-owned source bit
OFF as an intra-Hit inactive gap
Quick/full-Whirl StatePosition suppression
Fist/PhysicalFist current research group-skip + rearm behavior
unmarked/unsupported native fallback
late/dead/unsupported marker rejection
valid-motion-only marker caching
```

C1 tracks lifecycle obligations. It does not replace the animator-authored desired source set, occurrence counts, duplicate suppression, rearm, OFF, or native-activation suppression.

## 4. Implemented responsibility

Implementation commit:

```text
7667c428a580d18f625317702ededb76aa5e8bb5
```

### 4.1 Factual current C1 generation

`CollisionLifecycleGuard` exposes a read-only current-generation query for the actor without creating, replacing, finalizing, repairing or otherwise mutating a generation.

Conceptual rule:

```text
no actor record -> invalid token
actor record exists -> exact current actor + monotonic generation
no lifecycle mutation
no new hook
no polling
```

### 4.2 Marker execution budget scoped to C1 generation

A marker execution-budget record carries the exact C1 generation that owns it.

For later reserved-marker callbacks:

```text
same actor + same valid C1 generation
→ same marker execution for occurrence/dedupe purposes

different valid C1 generation
→ fresh marker execution budget and dedupe state
```

State time, action, phase, motion filename, source pointers and authored-count changes remain independent validation/ownership facts where needed; they are not durable execution identity.

### 4.3 Fail closed on internal inconsistency inside one generation

If one valid C1 generation presents marker-budget identity facts that contradict the stored record in a way unsupported by existing marker semantics, the marker remains non-mutating/rejected rather than silently resetting the budget as a fabricated new execution.

### 4.4 Narrow natural source retirement

`RetireMarkerOwnedSource()` remains wired through the existing SetCollisionGroup bridge.

Its factual responsibility is only:

```text
source successfully leaves Item_Attack
→ clear that exact active source bit from matching marker-owned window(s)
→ erase window when no active source bits remain
```

It no longer uses action/phase/motion/state-time heuristics to decide that the actor's occurrence/dedupe execution record ended.

Natural source cleanup, explicit OFF and exact-set switching remain distinct operations.

### 4.5 Marker-window semantics preserved

C1 cleanup fulfillment does not replace marker-window meaning.

Examples:

```text
RIGHT -> LEFT
= retire RIGHT physical marker-owned bit, activate/rearm LEFT, same C1 generation

RIGHT -> OFF -> RIGHT
= close authored window, then later reopen/rearm RIGHT, same C1 generation

natural 7 -> 5 cleanup
= retire exact physical marker-owned source bit; occurrence history remains scoped to the same generation until C1 changes/finalizes
```

### 4.6 C1 lifecycle ownership remains unchanged

`FrameCollisionMarkers` does not create, finalize, replace or repair C1 generations.

The existing lifecycle remains authoritative:

```text
CombatMove / proven pre-Combat path creates or binds C1 generation
SetCollisionGroup observations create/fulfill exact-source obligations
post-native AISetState finalizes/repairs only the established outstanding predicate
```

If no valid C1 generation exists at a legitimate marker point where generation-scoped bookkeeping is required, fail closed; do not invent a fallback execution-ID scheme.

## 5. Explicit non-goals

Gate 4 did not change:

```text
marker names
marker frames/count interpretation
RIGHT/LEFT/BOTH/OFF behavior
source resolution policy
attack-family coverage
Normal/Quick/Whirl eligibility semantics
Quick/Whirl StatePosition behavior
ClearTriggeredList behavior
Fist semantics
C1 obligation or repair predicates
AISetState finalization ordering
SetCollisionGroup calling convention/order
RunScriptFunction/P2 behavior
bad-skip prevention
Dual P1 Quick marker authoring
Raise/speed/config
New Balance / Jackydima integration
production migration
```

No new hooks or deep diagnostic probes were added by the bounded simplification.

## 6. Source scope / audit result

The bounded implementation stayed within the expected marker/C1/transport/compact-observability source area. Independent Normal Chat review confirmed:

```text
read-only generation transport
no marker semantic removed
no C1 lifecycle mutation semantics changed
no new hook added
RetireMarkerOwnedSource still retires exact physical source bits
OFF/exact-set switching cannot retire the whole occurrence execution
duplicate + authored occurrence protection remain active
same-generation inconsistency fails closed
```

## 7. Validation result

### CORE diagnostic identity

```text
Script_FrameCollisionTest.dll
Length: 416768
SHA256: E69FB2602E3599A0905B63F2064B732D57CA9E1817CDED2BD7AB6C01C08392E9
```

Controlled diagnostic regression established:

```text
PASS same-generation full-Whirl RIGHT -> OFF -> RIGHT
PASS first genuine RIGHT 0 -> 1
PASS OFF accepted without occurrence execution reset
PASS later genuine RIGHT 1 -> 2
PASS replay OFF rejected by authored occurrence budget
PASS replay RIGHT rejected by same-update duplicate guard
PASS natural cleanup retires exact physical marker-owned source bit
PASS incomplete prior execution cannot leak occurrence state into later same-motion generation
PASS marked full-Whirl destructive bad skip cannot reopen through dead/late callbacks
PASS exact C1 terminal repair remains unchanged
PASS 1H/Dual source-specific regression
PASS unsupported Power/native fallback regression
PASS no no-generation/generation-inconsistency/invariant/divergence/unresolved failure signal
PASS clean diagnostic unload
```

Final no-leak qualification:

```text
The current marked 2H Normal P0 asset now reports one authored RIGHT,
so the historical EV-131 two-RIGHT Normal fixture cannot be reproduced literally.

The equivalent occurrence-lifetime failure class was tested with the still-two-contact
P0 full Whirl:

Generation 34, exact motion
Hero_Parade_None_2H_P0_WhirlAttack_Hit_N_Fwd_00_%_00_P0_150_R.xmot
→ first RIGHT accepted 0 -> 1 with ExecutionBudgetReset: 1
→ execution ends before OFF/second RIGHT

Later Generation 40, same exact motion
→ first RIGHT accepted 0 -> 1 with ExecutionBudgetReset: 1
→ later genuine RIGHT accepted 1 -> 2
```

This directly proves the incomplete previous execution no longer leaks its authored occurrence budget into the next same-motion execution.

### Behavior-only follow-up identity

```text
Script_FrameCollisionBehaviorTest.dll
Length: 378880
SHA256: 41424651B352EEA5009F9E93FA18B67AB1BF5BDBC55BDE2A721ACA0355D5CFB3
```

It was deployed alone, reached main menu, exited normally and passed user-observed Staff/1H/2H combat plus repeated destructive bad-skip smoke with no visible stuck collision, crash or regression.

Canonical evidence: EV-213.

## 8. Gate state

```text
Gate 4 audit/classification: CLOSED/PASS
Gate 4 bounded implementation: CLOSED/PASS
Gate 4 CORE diagnostic regression: CLOSED/PASS
Gate 4 behavior-only follow-up: CLOSED/PASS
```

Gate 4 is complete. Do not reopen it merely for additional incidental combat coverage.

## 9. Next responsibility

The next responsibility is **equipped-melee marker expansion planning**, one bounded mechanism/family at a time.

Explicit first review item:

```text
tested Dual P1 Quick authored marker = G3AB_COL_RIGHT
older tested native-source evidence = LEFT
```

Resolve that discrepancy deliberately as part of the equipped-melee planning boundary. Do not mix it with Fist source adaptation, AttackContinuationProtection, C1 redesign, Raise/speed/config or compatibility work.

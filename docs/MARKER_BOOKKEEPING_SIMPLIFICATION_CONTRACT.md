# Marker Bookkeeping Simplification Contract

**Status:** FROZEN GATE 4 IMPLEMENTATION CONTRACT  
**Date:** 2026-08-31  
**Scope:** marker execution identity/bookkeeping only

## 1. Purpose

Gate 4 audited the current `FrameCollisionMarkers` bookkeeping against the historical marker regressions and the now-proven C1 lifecycle authority.

The result is deliberately narrow:

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
EV-209–EV-212
COLLISION_LIFECYCLE_PLAN.md §9
```

Key historical distinction:

- EV-131 proved occurrence-budget state could leak across two separate attacks when marker-local source/motion/action/phase/state-time identity failed to establish a fresh execution.
- EV-133 proved natural marker-owned source retirement fixed that tested case; callback state-time rollback was not the observed boundary that supplied the fix.
- EV-167 explicitly classifies `RetireMarkerOwnedSource()` as marker-bookkeeping retirement, separate from physical cleanup.
- C1 now has the durable monotonic attack generation that the old marker module did not have.

## 3. Classification result

### A — execution-lifetime inference superseded by C1 generation

The following responsibilities may be removed or consolidated:

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

## 4. Frozen implementation responsibility

Implement only the following.

### 4.1 Expose factual current C1 generation

Add one read-only `CollisionLifecycleGuard` query that returns the actor's currently active C1 generation token/fact without creating, replacing, finalizing, or mutating a generation.

Conceptual API:

```text
CaptureCurrentGenerationToken(actorInstance)
```

Exact naming may follow existing local conventions.

Rules:

```text
no actor record -> invalid token
actor record exists -> exact current actor + monotonic generation
no lifecycle mutation
no new hook
no polling
```

### 4.2 Scope marker execution budget to C1 generation

A marker execution-budget record must carry the exact C1 generation that owned its first accepted marker.

For later reserved-marker callbacks:

```text
same actor + same valid C1 generation
→ same marker execution for occurrence/dedupe purposes

different valid C1 generation
→ fresh marker execution budget and dedupe state
```

Do not infer a new execution from state time, action, phase, motion filename, source pointers, or authored-count changes.

Those facts remain validation/ownership facts where independently required; they are no longer durable execution identity.

### 4.3 Fail closed on internal inconsistency inside one generation

If the same C1 generation unexpectedly presents marker-budget identity facts that contradict the record in a way the existing supported marker semantics do not permit, do **not** silently reset the budget and call it a new execution.

The marker must remain non-mutating/rejected unless an already-proven intra-execution operation explains the difference.

Do not invent recovery policy during this task.

### 4.4 Narrow natural source retirement

Keep `RetireMarkerOwnedSource()` and the existing SetCollisionGroup bridge call.

Its factual responsibility becomes only:

```text
source successfully leaves Item_Attack
→ clear that exact active source bit from matching marker-owned window(s)
→ erase window when no active source bits remain
```

It must no longer use action/phase/motion/state-time heuristics to decide that the actor's authored occurrence/dedupe execution record has ended.

Natural source cleanup, explicit OFF, and exact-set switching remain distinct operations.

### 4.5 Preserve marker-window semantics

Do not use C1 cleanup fulfillment as a substitute for marker-window meaning.

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

`FrameCollisionMarkers` must not create, finalize, replace, or repair C1 generations.

The existing lifecycle remains authoritative:

```text
CombatMove / proven pre-Combat path creates or binds C1 generation
SetCollisionGroup observations create/fulfill exact-source obligations
post-native AISetState finalizes/repairs only the established outstanding predicate
```

If no valid C1 generation exists at a marker point where generation-scoped bookkeeping is required, STOP during implementation/source audit and report the concrete contradiction instead of inventing a fallback execution-ID scheme.

## 5. Explicit non-goals

Do not change:

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

Do not add new hooks or deep diagnostic probes.

## 6. Expected source scope

The bounded implementation should normally require only the files necessary for:

```text
CollisionLifecycleGuard.h/.cpp
FrameCollisionMarkers.h/.cpp
FrameCollisionShared.h        only if the generation fact must cross an existing result structure
EngineBridge.cpp              only for factual generation transport / existing call wiring
CollisionDiagnostics.cpp/.h   only if compact observability needs a generation/result field for validation
```

Do not broaden beyond these without a concrete compile/API contradiction.

## 7. Required implementation audit

Before publishing source implementation:

```text
confirm no marker semantic was removed
confirm no C1 lifecycle mutation semantics changed
confirm no new hook added
confirm RetireMarkerOwnedSource still retires exact physical source bits
confirm OFF/exact-set switching cannot retire the whole occurrence execution
confirm duplicate + occurrence protection remain active
git diff --check
```

If a concrete API/calling-convention/lifecycle contradiction appears, STOP and report it rather than improvising.

## 8. Validation after implementation

First perform source review/build separation as usual.

Then use the CORE diagnostic product alone for a compact marker regression that specifically proves:

```text
1. two-contact same-motion attack:
   first and later genuine marker both accepted
   replay callbacks still rejected

2. interrupted attack after first marker -> immediate same-motion new attack:
   new attack receives a fresh C1 generation
   first marker receives a fresh occurrence budget
   later genuine marker remains accepted

3. explicit OFF / exact-set switching inside one execution:
   does not create a fresh marker execution

4. natural cleanup inside one execution:
   retires physical marker-owned source/window bit
   does not fabricate a new C1 generation

5. marked full-Whirl destructive bad skip:
   dead/late callbacks do not reopen collision
   C1 terminal repair behavior remains unchanged

6. no invariant/divergence/unresolved/failure signal
   clean shutdown
```

Behavior-only smoke follows only if the diagnostic regression passes.

## 9. Gate state

```text
Gate 4 audit/classification: CLOSED/PASS
Gate 4 bounded implementation: FROZEN / NOT YET IMPLEMENTED
```

Next responsibility is a bounded Work implementation of this contract, followed by independent Normal Chat source review and the frozen regression above.

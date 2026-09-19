# Independent Astra Audit — Permanent raw55 PhysicalFist

**Reviewed source state:** `314f284dbaaf05c5f185811aab107e84f1d434ce`  
**Date:** 2026-09-18  
**Mode:** read-only independent formal audit

## External audit result

Astra returned:

```text
PASS WITH NON-BLOCKING FINDINGS
```

It found no confirmed release-behavior defect in the proven Normal / Quick / true-Power / Sprint raw55 routes.

## Normal Chat independent disposition

### F1 — authored first-marker opening vs active native callback scope

Astra identified a logically possible attribution collision:

```text
active eligible raw55 callback scope
+ first authored FIST arrives reentrantly
+ marker-owned ActivateAttackSource issues exact RIGHT 5 -> 7
-> ShouldSuppressCollisionGroupRequest could mistake that request for the premature native opening
```

Source inspection confirms that the suppression predicate itself does not distinguish native-vs-feature-owned requests.

Current disposition: **DEFENSIBLE RISK / NO CHANGE YET**.

Reason:

- the permanent acceptance and preceding family evidence already exercise all supported first-marker timing classes;
- early Quick/Normal SP0 markers successfully perform their authored 5 -> 7 opening;
- late Quick/Normal and Power/Sprint markers occur after the factual premature native opening has already been suppressed and native callback progression completed;
- if an active matching callback scope had enclosed those successful first-marker 5 -> 7 operations, the current suppression predicate would have suppressed them and the marker would have failed activation;
- no such failure appears in the accepted runtime routes.

Therefore the reviewed evidence demonstrates that this nested ordering does not occur in the supported tested paths. It does not prove that Gothic can never produce such ordering elsewhere.

Do not add release complexity solely for this hypothetical route. If a future runtime exposes marker dispatch inside an active raw55 callback scope, return to diagnosis and then add the narrowest feature-owned activation attribution needed.

### F2 — same-C1 callback identity contradiction not always surfaced

Astra identified a real frozen-contract omission.

In `PhysicalFistCollision::BeginNativeCallbackScope()`:

```cpp
PhysicalFistExecution *const execution = ResolveExecution(
    facts, created, identityContradiction);
if (execution == nullptr || identityContradiction)
    return;
```

The behavior decision is correct: the contradictory callback receives no new raw55 intervention.

However, `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md` §5 explicitly requires:

```text
Any other same-C1 origin contradiction performs no new raw55 intervention
and is surfaced by diagnostics.
```

A callback-entry contradiction can therefore disappear silently when no later marker reaches the marker rejection logger.

Current disposition: **CONFIRMED DIAGNOSTIC CONTRACT VIOLATION / RELEASE BEHAVIOR UNAFFECTED**.

The smallest correction belongs inside the diagnostic side of `PhysicalFistCollision` and should surface the exact callback-entry contradiction without changing behavior, state, eligibility or bridge policy.

## 314f diagnostic-classifier correction

Normal Chat independently re-reviewed Work commit:

```text
314f284dbaaf05c5f185811aab107e84f1d434ce
```

against base:

```text
7563af64a2104ce1246e9482aa8a4a48fe54b27a
```

Result: **SOURCE REVIEW PASS**.

The commit is exactly one commit ahead and changes only:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
```

The correction adds the narrow factual raw55 candidate shape:

```text
FIST markers
requiredSourceMask == none
no raw8 fist resolver
current RIGHT exists
current RIGHT UseType == PhysicalFist/raw55
```

and exempts only that shape from the older raw8-only contradiction assumption.

No production behavior path is changed.

## Next engineering sequence

Before rebuilding the diagnostic target, close F2 with one tiny diagnostics-only correction so one local build can validate both diagnostic fixes.

Then:

```text
independent source review
-> build Script_FrameCollisionTest Release only
-> deploy/hash/startup
-> small marked raw55 control:
   legitimate raw55 ownership = ROUTINE
   no false CORE ATTACK OWNERSHIP ANOMALY
-> remaining focused sentinels:
   unmarked raw55 native fallback
   raw8 FIST
   one equipped authored-marker route
-> close focused permanent acceptance
```

F1 remains documented as a non-blocking evidence-bounded risk, not an implementation task.

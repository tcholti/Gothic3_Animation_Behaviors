# Gothic 3 Animation Behaviors — raw55 CORE diagnostic classification correction

**Status:** FROZEN bounded diagnostics-only correction  
**Date:** 2026-09-17

## Purpose

Correct one stale CORE diagnostic classification exposed by the first permanent raw55 acceptance run. This task changes no collision behavior.

## Runtime finding

Permanent raw55 behavior itself passed the marked Troll core acceptance for factual Quick, Normal, true Power and Sprint-origin routes. The production `RAW55_PHYSICAL_FIST_*` records, `OnDamage`, native `7 -> 5` cleanup and clean C1 finalizations are coherent.

However, each legitimate marked raw55 execution is also logged by the older generic attack-ownership diagnostic as:

```text
Classification=CONTRADICTION
===== CORE ATTACK OWNERSHIP ANOMALY =====
```

Source inspection identifies the exact stale rule in `CollisionDiagnostics::LogAttackCallbackOwnership()`:

```cpp
result.decision.hasFistMarkers
&& fistUseType != gEUseType_Fist
```

The generic logger was written when an authored FIST marker was expected to resolve only through the raw8 `Fist` resolver. Permanent raw55 intentionally satisfies the opposite factual shape:

```text
FIST marker present
raw8 ResolveFistCollisionSource(actor) absent
requiredSourceMask == none
current RIGHT equipped source exists
RIGHT UseType == PhysicalFist / 55
```

Therefore the current anomaly is a diagnostic false positive, not a production ownership contradiction.

## Frozen correction

Modify only the compact CORE ownership-classification logic in:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
```

A FIST-bearing attack must not be classified as a contradiction solely because the raw8 resolver is absent/non-Fist when the factual current source shape is the permanent raw55 candidate shape:

```text
requiredSourceMask == none
raw8 fist source absent
exact current RIGHT source present
RIGHT source UseType == gEUseType_PhysicalFist / 55
```

Keep the logger diagnostic-only. It may compute this factual raw55-candidate predicate from the already supplied marker decision and equipped-source facts.

Do **not** call into `PhysicalFistCollision` or duplicate its full eligibility/ownership state machine in diagnostics. The logger only needs enough factual source classification to stop calling the now-supported raw55 source shape a contradiction.

Preserve existing contradiction detection for:

```text
matching motion not found
invalid marker scan
required equipped source mask missing
FIST-bearing cases that are neither the established raw8 Fist source shape nor the factual raw55 candidate source shape
```

Existing record fields and anomaly block format should remain unchanged unless the smallest correction mechanically requires otherwise. A valid raw55 candidate should simply classify as routine rather than emit the anomaly block.

## Protected behavior / scope

This task must not modify:

```text
PhysicalFistCollision.*
EngineBridge.*
FrameCollisionMarkers.*
Raw8FistCollision.*
CollisionSources.*
CollisionSourceOperations.*
CollisionLifecycleGuard.*
CMakeLists.txt
production behavior
hooks
marker semantics
raw8 semantics
raw55 semantics
C1 lifecycle or repair
```

No new runtime state, hook, feature policy, probe, source mutation or fallback is authorized.

## Validation

Work performs source/static audit only and publishes the bounded correction.

**Work build execution is PROHIBITED.**

After independent Normal Chat review, the User will rebuild only `Script_FrameCollisionTest`, redeploy it and run a small marked raw55 diagnostic control. Acceptance requires:

```text
legitimate raw55 attack ownership -> Classification=ROUTINE
zero corresponding CORE ATTACK OWNERSHIP ANOMALY blocks
permanent RAW55_PHYSICAL_FIST behavior records unchanged in meaning
```

Then the existing permanent raw55 acceptance evidence remains valid and focused sentinel validation can continue.

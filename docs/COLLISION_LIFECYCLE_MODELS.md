# Collision Lifecycle Models

**Status:** Working architecture models / not yet implemented  
**Updated:** 2026-08-26

This document contains the compact models for the two cleanup systems currently under consideration and the agreed marker-set semantics. `docs/COLLISION_LIFECYCLE_PLAN.md` remains the concise design authority; this file exists so future coding sessions can see the exact models without expanding the main plan.

## Preferred System — Execution-Level Native Cleanup Guard

```text
REAL ATTACK-HIT EXECUTION X BEGINS
        ↓
Capture the exact actual motion execution
        ↓
Does this execution contain our collision markers?
        ↓
        ┌───────────────────────┬───────────────────────┐
        │ MARKED                │ NATIVE                │
        │                       │                       │
        │ Suppress native       │ Leave Gothic 3's     │
        │ collision timing      │ collision behavior   │
        │                       │ completely untouched │
        │ Markers control       │                       │
        │ collision timing      │ Native code controls │
        │                       │ collision timing     │
        └───────────┬───────────┴───────────┬───────────┘
                    │                       │
                    └───────────┬───────────┘
                                ↓
             Did this Hit execution request
                  offensive collision?
                                ↓
                         NO → nothing
                                ↓
                         YES → remember:
                       "collision requested"
                                ↓
              Continue following the exact
                  actual Hit execution
                                ↓
           Hit finishes OR is genuinely replaced
           OR interrupted — reason does not matter
                                ↓
             Did Gothic 3 perform the proper
                    native attack cleanup?
                                ↓
                    ┌───────────┴───────────┐
                    │                       │
                   YES                     NO
                    │                       │
               DO NOTHING           INVOKE GOTHIC 3'S
                                    NATIVE CLEANUP
```

### Preferred invariant

> For every real attack-Hit execution that requests offensive collision, proper native cleanup must have occurred by the time that exact Hit execution actually ends or is replaced. If Gothic 3 already cleaned it, do nothing. If it did not, invoke the native cleanup Gothic 3 should have performed.

The reason the Hit ended is intentionally irrelevant to production cleanup. Block timeout, normal completion, damage interruption, terrain interruption, skipped Recover, and other genuine replacements should become test cases for the same rule rather than separate cleanup branches.

### Preferred minimal state

If native cleanup is attack-wide and observable, the preferred runtime model is only:

```text
Execution X
    exact actual Hit execution
    collisionRequested = true/false
    nativeCleanupObserved = true/false
```

Do not add per-source ownership merely because the current prototype already contains source masks.

## Fallback System — Source-Aware Cleanup Guard

Use this only if research proves that Gothic 3 has no usable attack-wide cleanup operation, or that individual physical sources can clean or fail independently.

```text
REAL ATTACK-HIT EXECUTION X BEGINS
        ↓
Capture the exact actual motion execution
        ↓
Marked or native collision behaves
according to the same activation policy
described in the preferred system
        ↓
Observe offensive collision requests
during execution X
        ↓
Record which physical sources were requested

Example:
RIGHT requested Item_Attack → X owns RIGHT
LEFT requested Item_Attack  → X owns LEFT

A request counts even if:
7 → 7
        ↓
Continue following the exact
actual Hit execution
        ↓
Hit finishes / is replaced / interrupted
        ↓
Check each offensive source associated with X
        ↓
        RIGHT clean?          LEFT clean?
           ↓                     ↓
      YES → nothing         YES → nothing
      NO  → native          NO  → native
             source                 source
             cleanup                cleanup
```

The fallback preserves the same principle as the preferred system; it merely verifies cleanup at source level because the engine evidence would require it.

## Marker System — Desired Offensive Collision Set

While a marked Hit is still alive, markers define the complete desired offensive collision set:

```text
RIGHT = desired offensive collision set {RIGHT}
LEFT  = desired offensive collision set {LEFT}
BOTH  = desired offensive collision set {RIGHT, LEFT}
OFF   = desired offensive collision set {}
```

Examples:

```text
RIGHT → LEFT
{RIGHT} → {LEFT}
```

```text
BOTH → RIGHT
{RIGHT, LEFT} → {RIGHT}
```

```text
OFF
{}
```

The conceptual rule is not a matrix of previous-marker combinations. It is:

> Make the offensive collision state equal to the currently authored desired set.

The implementation may use a native collision-only deactivation operation if Gothic 3 exposes one that is safe inside a still-live Hit. Do not invoke a whole-attack finalization routine merely to switch the active source set unless research proves that operation is safe for that purpose.

`G3AB_COL_OFF` remains an authored early shutoff inside a live Hit. It is not the end-of-Hit safety guard.

## Two Governing Rules

```text
WHILE THE HIT IS ALIVE:
Markers define the desired offensive collision set.
```

```text
WHEN THE HIT IS OVER:
Offensive attack collision must be clean.
If Gothic 3 already cleaned it → do nothing.
If Gothic 3 failed → invoke the proper native cleanup.
```

## Preference Order

1. **Preferred:** execution-level guard using Gothic 3's native attack cleanup.
2. **Fallback:** source-aware guard only if the engine evidence requires independent source tracking/cleanup.
3. Avoid interruption-specific cleanup branches unless a real case is proven unable to follow either general model.

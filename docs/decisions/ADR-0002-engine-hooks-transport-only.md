# ADR-0002 — Keep Engine Hooks Transport-Only

**Status:** Accepted  
**Date:** 2026-09-19  
**Evidence basis:** EV-208–EV-215, EV-250, EV-262–EV-298

## Context

Collision research repeatedly needed the same physical Gothic callbacks for different feature mechanisms. Putting source/family policy, causal-probe state, or permanent behavior directly into the hook owner would couple unrelated mechanisms and make experimental and production responsibilities difficult to separate.

Raw8 and raw55 also demonstrated that similar animation naming does not imply the same underlying mechanism.

## Decision

`EngineBridge` owns each low-level physical hook exactly once and remains transport-oriented:

```text
capture native facts
-> normalize stable context
-> delegate to the owning feature/probe
-> enact only the narrow returned transport decision
```

Feature policy/state belongs in the permanent feature module that owns the mechanism. Unknown behavior belongs in a temporary diagnostic probe while it is being researched.

## Consequences

- multiple features can share one physical hook without merging their semantics;
- experimental code remains removable;
- diagnostics/release separation is easier to preserve;
- raw8, raw55 and equipped mechanisms remain distinct;
- adding a new behavior may require a small bridge delegation seam, but not a competing hook owner.

## Current authorities

- `DESIGN.md`
- `FEATURE_DEVELOPMENT_METHOD.md`
- `WORK_IMPLEMENTATION_PROTOCOL.md`
- `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`

This ADR preserves the rationale. Current architecture/reference documents remain authoritative for what applies now.

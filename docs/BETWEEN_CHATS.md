# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-20

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

## Current state

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Latest completed runtime evidence: **EV-354**.

Permanent raw8 architecture:
`docs/COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md`

Published production implementation:
`3426cede41c0087e43edc0d81c825ff167e8e034`

Independent Normal Chat static review:
- exact eight-path implementation scope: PASS;
- permanent raw8 behavior/state-machine promotion: PASS;
- temporary probe retirement: PASS;
- behavior-vs-diagnostic separation: PASS;
- no protected behavior module changed;
- no material behavior contradiction found.

## Bounded review correction before build

The implementation is not yet ready for build because two diagnostics-only contract mismatches were found:

1. `CloseAndEraseExecution` currently emits `CORE RAW8_OPPORTUNITY_CLOSE` even when the opportunity was already contact-consumed. CORE semantics require:
   - exact native contact -> `CONTACT_CONSUMED`;
   - unused pending opportunity -> lifecycle `CLOSE`.
2. Routine `CORE RAW8_OPPORTUNITY_*` identity currently includes raw actor/source/SPU and contact argument/caller addresses. Routine CORE must remain compact; rich raw addresses belong to DEEP/anomaly diagnostics.

Frozen correction:
`docs/work/active/COLLISION_RAW8_PRODUCTION_DIAGNOSTIC_COMPACTION_CORRECTION.md`

The correction is diagnostics-only. It must not alter raw8 opportunity state, latch behavior, timing behavior, hooks, invocation identity or finalization.

## Stop gate

No build or runtime test yet.

First require POP-12 validation of this maintained handoff state. Then execute/review the bounded diagnostics-only correction. After that, build both twins and begin the focused permanent raw8 acceptance matrix from `docs/COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md` §14.

`research/raw/` remains closed from EV-354 and should contain only `Keep.txt`.

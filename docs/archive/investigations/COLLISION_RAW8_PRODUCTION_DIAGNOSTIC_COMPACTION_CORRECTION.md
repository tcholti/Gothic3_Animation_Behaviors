# Gothic 3 — Raw8 Production Diagnostic Compaction Correction

**Status:** CLOSED — IMPLEMENTED AND INDEPENDENTLY REVIEWED PASS  
**Opened:** 2026-09-20  
**Reviewed implementation:** `3426cede41c0087e43edc0d81c825ff167e8e034`  
**Architecture:** `docs/COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md`  
**Diagnostics authority:** `docs/COLLISION_DIAGNOSTICS.md`  
**Work build execution:** PROHIBITED

## Completion

Implemented in `7c9c9c2a4512b44ff64c09ef9866b7160f4d5cbd` with parent `70c393de7fe0ffce020266a1a3c890ebcb364ea6`.

Independent Normal Chat review: **PASS**.

Verified correction scope is exactly the two frozen source files. `CORE RAW8_OPPORTUNITY_CLOSE` now emits only for an actually pending unused opportunity, and the four routine CORE opportunity records no longer carry raw pointer addresses. No raw8 state, latch, timing, hook, contact-predicate or finalization behavior changed.

Next gate: build both collision twins and run the agreed small smoke before the final read-only code-quality/modularity audit.

## Review result

Normal Chat independently reviewed the published production promotion at `3426cede41c0087e43edc0d81c825ff167e8e034`.

The permanent raw8 behavior implementation is accepted at static review:

- `Raw8FistCollision` owns the persistent per-C1 opportunity and timing substate;
- exact accepted FIST opens/refreshes one opportunity;
- native misses rearm only an exact pending opportunity;
- exact `Game+0x16E348` contact consumes the opportunity;
- contact keeps the C1 execution record alive for a later FIST;
- timing retirement does not consume the logical opportunity;
- same-C1 Action/family change is not terminal authority;
- post-native `AISetState` finalization is generation-safe;
- the behavior-only twin receives the same behavior-required OnDamage/combat-move/timing/finalization transport;
- the temporary diagnostic probe is removed;
- protected behavior modules were unchanged.

No behavior correction is authorized by this task.

Two diagnostics-only mismatches remain before build/runtime acceptance.

## Correction 1 — lifecycle CLOSE must mean unused pending opportunity

Current `CloseAndEraseExecution` emits `CORE RAW8_OPPORTUNITY_CLOSE` even when `opportunityPending == false`, for example when a contact-consumed execution record later retires at C1 finalization.

That creates two apparent terminal records for one opportunity:

```text
RAW8_OPPORTUNITY_CONTACT_CONSUMED
...
RAW8_OPPORTUNITY_CLOSE OpportunityPending=0
```

This conflicts with the established CORE semantic:

```text
exact native contact -> opportunity CONSUMED
unused opportunity -> lifecycle CLOSE
```

Required correction:

- keep execution-record retirement exactly as implemented;
- keep all latch/timing behavior exactly as implemented;
- emit `CORE RAW8_OPPORTUNITY_CLOSE` only when the retiring execution actually has an unused pending opportunity;
- a previously consumed/non-pending execution may retire silently at this opportunity-event layer;
- do not reintroduce probe-style erasure on contact.

## Correction 2 — routine CORE opportunity records must remain compact

The new shared `LogRaw8OpportunityIdentity` currently places raw addresses such as actor/source/SPU addresses into every routine CORE opportunity event, and the routine contact-consumed line additionally prints caller/argument addresses.

The diagnostics authority requires routine CORE raw8 evidence to preserve semantic identity and lifecycle facts, while rich addresses belong to DEEP/anomaly diagnostics.

Required routine CORE identity is sufficient as:

```text
actor name
factual action/family
motion
C1 generation
raw8 Fist source name/identity
opportunity ordinal
event-specific semantic fields
```

Required correction:

- remove routine actor/source/SPU raw-address fields from the four `CORE RAW8_OPPORTUNITY_*` records;
- remove routine caller/Arg1/Arg2 raw-address fields from `CORE RAW8_OPPORTUNITY_CONTACT_CONSUMED`;
- preserve the semantic `Reason=EXACT_NATIVE_CONTACT_DISPATCH` fact;
- detailed addresses may remain available under `FRAME_COLLISION_DIAGNOSTICS_DEEP` if useful, but adding new DEEP output is optional;
- do not change behavior or make behavior depend on diagnostics.

## Exact source scope

Expected source changes only:

```text
MODIFY prototypes/Script_FrameCollisionTest/Raw8FistCollision.cpp
MODIFY prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
```

No header/signature change is required for the frozen correction. Existing diagnostic function parameters may remain and be explicitly unused when necessary.

If faithful correction requires any behavior-policy change, hook change, protected-module change, or broader source scope, STOP and report the contradiction.

## Protected implementation

Do not change:

- raw8 opportunity state transitions;
- latch reads/writes;
- timing calculations or timing retirement;
- invocation-scope identity;
- contact-consumption predicates;
- C1 generation/finalization logic;
- OnDamage hook installation or original-call behavior;
- `EngineBridge.cpp`;
- `Raw8FistCollision.h`;
- `CollisionDiagnostics.h`;
- CMake;
- any raw55/equipped behavior;
- any protected module from the parent production task.

## Static verification

Before publication verify:

- exact two-file source scope;
- no behavior-state/latch/hook changes;
- contact-consumed opportunity no longer later produces a routine opportunity CLOSE merely because its execution record finalizes;
- an unused pending opportunity still produces `CORE RAW8_OPPORTUNITY_CLOSE`;
- routine four-event CORE identity contains no raw pointer addresses;
- contact-consumed CORE still states exact native contact-dispatch semantic;
- `git diff --check` passes.

## Build / publication

Work build execution is PROHIBITED.

The User authorizes publication of this bounded diagnostics-only correction to `tcholti/Gothic3_Animation_Behaviors`, branch `docs/collision-source-evidence`.

## Required report

Report final remote commit SHA, parent SHA, exact changed files, both correction results, static checks, and:

`Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`

Then STOP.

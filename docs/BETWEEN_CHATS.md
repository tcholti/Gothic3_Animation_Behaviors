# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-20

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

## Current state

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Phase 4 raw8 FIST authoring-semantics research remains active.  
Latest completed evidence: **EV-352**.

Active task:

`docs/work/active/COLLISION_RAW8_PERSISTENT_OPPORTUNITY_TOKEN_CAUSAL_PROBE.md`

Raw8 remains mechanically separate from equipped collision. Shared principle only:

```text
state belongs to an exact attack execution / C1 generation
-> same-C1 Action/family/phase transport may continue
-> factual C1 finalization/replacement terminates it
```

Protected Sprint fact: Action9/SPRINT -> Action2/POWER can occur inside one C1.

## Current source-review block

Reviewed implementation:

`e86c1ce03b36ef0ef7421a19284c5b38e58615ed`

Most probe invariants PASS. One narrow lifecycle correction is required before build/runtime.

Current defect:

`CloseForFinalization()` runs after native `AISetState`. It verifies stored token == captured pre-call generation and revalidates actor/SPU/source, but does **not** verify that the actor's **current C1 generation still equals that captured generation** before writing `SPU+0x164 = 1`.

Risk:

```text
native AISetState creates/replaces C1
-> actor/SPU/Fist source remain reusable
-> old token cleanup could write latch 1 into new generation
```

That cross-C1 mutation is prohibited.

## Exact correction

Change only:

`prototypes/Script_FrameCollisionTest/Raw8FistPersistentOpportunityProbe.cpp`

Inside `CloseForFinalization(generation)`, before any latch write:

1. recapture `CollisionLifecycleGuard::CaptureCurrentGenerationToken(generation.actorInstance)`;
2. if current generation is valid and equals captured generation:
   - preserve existing exact terminal close;
   - latch may be safely forced to `1`;
3. if current generation is invalid or changed:
   - retire/erase stale logical token and timing state only;
   - log a factual no-write close reason;
   - **do not write the latch**.

Do not change:
- miss rearm;
- timing persistence;
- contact consumption;
- accepted-FIST OPEN;
- Action/Sprint lifetime semantics;
- permanent raw8 source;
- behavior-only source set;
- raw55/equipped behavior.

Expected correction diff: **one file only**.

## Current gate

POP-12 knowledge-state validation: **PASS**.

The one-file generation-safe finalization correction is cleared for Work.

No build/runtime is authorized until Normal Chat independently reviews the correction commit.

`research/raw/` should contain only `Keep.txt`.

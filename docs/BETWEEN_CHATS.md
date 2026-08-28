# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Frozen Work task — Step B6-C empty-Primary successor PlayMotion stack diagnostic

**Date:** 2026-08-28  
**Branch:** `docs/collision-source-evidence`

### Why this diagnostic is needed

B6-C legitimate player 2H Normal reaction evidence is now captured and promoted as EV-177.

The usable interruption cases show:

```text
attack Hit / weapon 7
→ legitimate reaction cleanup at Script_Game + 0x24AFF: 7 -> 5
→ old attack PrimaryFirst already empty before StopMotion
→ reaction PlayMotion starts from empty PrimaryFirst
→ Stumble / KnockDown successor is installed
```

At the cleanup/reaction boundary, the old attack action/phase/current-movement context can still be visible while `Routine.StateTime` and `Routine.StatePosition` have already reset. The existing direct `HIT REPLACEMENT STACK` probe cannot capture this path because it requires an outgoing attack-Hit Primary to still exist at PlayMotion entry.

This task closes only that diagnostic gap. It does **not** define production Hit ownership or reaction semantics.

### Frozen question

> When the legitimate B6-C reaction successor is requested after the outgoing attack Primary has already disappeared, what caller/SPU stack surrounds that existing type-0 `PlayMotion` request, and does it reach the same useful `ProcessScript()` context seen in B6-B?

### Required source change

Use only the **already-existing player/type-0 `PlayMotion_FrameCollisionTest` hook**.

Before calling original PlayMotion:

1. preserve the existing `before` Primary snapshot and existing direct replacement-stack logic unchanged;
2. add a second, diagnostic-only branch when:
   - the `before` Primary snapshot is available;
   - `before.primary.hasMotionInstance == false`;
   - the already-existing `CollisionControl::IsAttackHit(actor, AttackFamily_Normal)` predicate is true;
3. do **not** add any new action/phase/filename/reaction classifier;
4. do **not** gate on StateTime, StatePosition, collision group, successor name, Stumble, KnockDown, or any other inferred cause;
5. capture the same supported short Win32 stack using `CaptureStackBackTrace` and `NativeCleanupStackCapacity`;
6. capture factual pre-original context using the existing replacement-context machinery where suitable, including:
   - actor;
   - current movement animation;
   - action;
   - phase;
   - state time;
   - **state position**;
   - incoming PlayMotion request address;
   - equipped-source snapshot;
   - captured stack frames.

Call original PlayMotion **exactly once with the unchanged arguments**.

After original returns:

7. preserve the existing `after` Primary snapshot and existing direct replacement-stack logging unchanged;
8. for the new empty-Primary branch, emit a clearly named diagnostic record only if the `after` Primary snapshot is available and now has a motion instance;
9. name the record:

```text
HIT EMPTY-PRIMARY SUCCESSOR STACK
```

10. log factual post-original successor information, at minimum:
   - `PrimaryWasEmptyBefore: 1`;
   - installed/successor Primary motion name;
   - the pre-original context above;
   - stack frames;
   - `CleanupBehaviorChanged: 0`.

The successor must be reported factually from the `after` Primary snapshot. Do **not** classify it as a reaction, Stumble, KnockDown, Recover, or any other family in source.

### Diagnostic semantics

The existing Normal attack-Hit predicate is reused only because the controlled B6-C fixture is player 2H Normal and the old semantic context is still observable after physical Primary disappearance.

This branch is **diagnostic correlation only**. It must not be described or implemented as:

- universal Hit lifetime authority;
- production ownership;
- proof that stale action/phase/current-movement fields remain authoritative after Primary disappearance;
- a cleanup trigger;
- a reaction classifier.

### Protected behavior

Preserve unchanged:

- existing direct `HIT REPLACEMENT STACK` probe and its gate;
- existing `PRIMARYFIRST PlayMotion` before/after logging;
- existing StopMotion probe;
- existing StartRecover BEGIN stack probe and BEGIN/END records;
- all collision, marker, callback and bookkeeping behavior;
- original PlayMotion call count/arguments/order.

No new Gothic 3 hook.

### Explicit exclusions

Do **not** add:

- production cleanup or repair;
- lifecycle ownership or pending-finalization state;
- persistent diagnostic state;
- timers, polling, per-frame scans or caches;
- a new classifier or reaction-family rule;
- Stumble/KnockDown/Recover-specific source logic;
- a collision-group gate for this diagnostic;
- guessed stack/frame/object layouts;
- changes to `CollisionControl` merely to support this probe;
- unrelated cleanup/refactor/generalization.

### Allowed source files

Only:

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h`

If faithful implementation requires any other source file or a new semantic decision, STOP and report the contradiction.

### Runtime banner

Update the B6 banner only enough to make the deployed diagnostic unambiguous. It must contain:

```text
STEP B6 HIT STARTRECOVER / STOP / REPLACEMENT / EMPTY-PRIMARY SUCCESSOR STACK PROBE
```

Do not alter behavior merely for the banner.

### Work execution contract

Read:

1. `docs/SESSION_ENTRYPOINT.md`;
2. this file;
3. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`;
4. only the allowed source files and narrowly necessary already-established API/source definitions.

Then:

```text
implement only this bounded diagnostic
→ source-audit against this contract
→ git diff --check
→ commit and push/publish on docs/collision-source-evidence
→ overwrite docs/BETWEEN_CHATS.md with a concise Work result + final commit SHA
→ STOP
```

Do **not** build or run Gothic 3 in Work.

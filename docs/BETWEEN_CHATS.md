# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Frozen Work task — Step B6-C3 factual empty-Primary successor PlayMotion stack diagnostic

**Date:** 2026-08-28
**Branch:** `docs/collision-source-evidence`

### Why this refinement is needed

EV-178 shows that the first empty-Primary refinement used the existing Normal attack-Hit semantic predicate as a pre-original correlation gate, but that gate is no longer true by the time a legitimate Stumble/KnockDown successor PlayMotion is requested.

Representative controlled Normal sequence:

```text
Normal Hit / weapon armed
→ legitimate Script_Game + 0x24AFF cleanup 7 -> 5
→ Primary already empty at StopMotion
→ reaction PlayMotion begins from empty Primary
→ LieKnockDown_Begin installed
→ no HIT EMPTY-PRIMARY SUCCESSOR STACK record
```

All emitted records from the previous refinement instead corresponded to fresh Normal `Attack_Hit` installation from empty Primary.

The B6-C caller-stack question therefore remains unresolved. This task changes only the observation gate; it does not change collision or lifecycle behavior.

### Frozen question

> When any player/type-0 PlayMotion request begins with an available-but-empty Primary during the controlled interruption fixture and actually installs a successor Primary, what caller stack surrounds that request? In particular, what stack is recorded for the factual Stumble/KnockDown successor, and does it expose the same useful `ProcessScript()` context seen in EV-176?

### Required source change

Use only the **already-existing player/type-0 `PlayMotion_FrameCollisionTest` hook**.

Before calling original PlayMotion:

1. preserve the existing `before` Primary snapshot and existing direct replacement-stack logic unchanged;
2. refine the existing empty-Primary diagnostic branch so its pre-original gate is only:
   - the existing player/type-0 hook context;
   - `before` Primary snapshot is available;
   - `before.primary.hasMotionInstance == false`;
3. remove the `CollisionControl::IsAttackHit(actor, AttackFamily_Normal)` requirement from this empty-Primary diagnostic branch;
4. do **not** replace that gate with action, phase, StateTime, StatePosition, collision group, current-movement name, successor filename, Stumble, KnockDown, Recover, Quick, or any other semantic/cause classifier;
5. capture the same existing supported stack/context using `CaptureHitReplacementContext` / `NativeCleanupStackCapacity` or the current equivalent machinery. Do not change stack capacity: it is already 16 and the prior six-frame records were not buffer-truncated.

Call original PlayMotion **exactly once with unchanged arguments and ordering**.

After original returns:

6. preserve the existing `after` Primary snapshot and direct replacement-stack logging unchanged;
7. for the refined empty-Primary branch, emit a diagnostic record only when the `after` snapshot is available and contains a real Primary motion instance;
8. report the installed successor factually from the `after` Primary snapshot;
9. rename the record to remove the misleading implication that the capture itself is Hit-classified:

```text
EMPTY-PRIMARY SUCCESSOR STACK
```

10. rename the corresponding diagnostic helper from `LogHitEmptyPrimarySuccessorStack` to `LogEmptyPrimarySuccessorStack` if needed for source clarity; make no broader refactor;
11. retain factual pre-original context already supported by the current snapshot machinery, including actor, action, phase, StateTime, StatePosition, current movement, equipped-source snapshots, incoming request address and captured frames. These fields are context only, not capture gates;
12. include `CleanupBehaviorChanged: 0` as before.

The broader diagnostic is expected to capture unrelated player/type-0 empty-Primary successor installations during the short controlled run. That is acceptable. Normal Chat will identify the controlled Stumble/KnockDown records **post hoc** from the factual installed successor name.

### Protected behavior

Preserve unchanged:

- existing direct `HIT REPLACEMENT STACK` probe and gate;
- existing `PRIMARYFIRST PlayMotion` before/after logging;
- existing StopMotion probe;
- existing StartRecover BEGIN stack probe and BEGIN/END records;
- existing B4/B5 `SetCollisionGroup` cleanup diagnostics;
- all collision, marker, callback, StatePosition-bookkeeping and occurrence-budget behavior;
- original PlayMotion call count/arguments/order.

No new Gothic 3 hook.

### Explicit exclusions

Do **not** add:

- production cleanup or repair;
- lifecycle ownership or pending-finalization state;
- persistent diagnostic state;
- timers, polling, per-frame scans or caches;
- a reaction classifier or attack-family classifier for this branch;
- Stumble/KnockDown/Recover/Quick-specific source logic;
- a collision-group gate;
- successor-name gating;
- guessed stack/frame/object layouts;
- changes to `CollisionControl` merely to support this probe;
- unrelated cleanup/refactor/generalization.

### Allowed source files

Only:

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h`

If faithful implementation requires another source file, a new hook, persistent state, or a semantic decision not frozen above, STOP and report the contradiction.

### Runtime banner

Update the B6 banner only enough to distinguish this build. It must contain:

```text
STEP B6 HIT STARTRECOVER / STOP / REPLACEMENT / UNGATED EMPTY-PRIMARY SUCCESSOR STACK PROBE
```

Do not alter behavior merely for the banner.

### Work execution contract

Read:

1. `docs/SESSION_ENTRYPOINT.md`;
2. this file;
3. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`;
4. only the three allowed source files and narrowly necessary already-established API/source definitions.

Then:

```text
implement only this bounded diagnostic refinement
→ source-audit against this frozen contract
→ git diff --check
→ commit and push/publish on docs/collision-source-evidence
→ overwrite docs/BETWEEN_CHATS.md with a concise Work result + implementation/final commit SHA
→ STOP
```

Do **not** build or run Gothic 3 in Work.
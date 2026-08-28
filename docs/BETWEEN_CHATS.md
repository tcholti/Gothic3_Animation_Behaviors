# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Normal Chat -> Work — Step B6 StartRecover-BEGIN stack diagnostic

**Date:** 2026-08-28  
**Branch:** `docs/collision-source-evidence`

### Why this bounded revision exists

Valid B6-B runtime evidence (`research/raw/2026-08-28_b6b_player_2h_normal_clean_completion_stopmotion_stack_valid.log`, commit `e8e02c5ba53d05747ded6bad1ab70df0c6ac70ee`) corrected the earlier EV-174 interpretation:

```text
StartRecover BEGIN: outgoing attack Hit Primary still exists
→ inside original StartRecover execution, Primary disappears
→ by entry to the existing type-0 StopMotion hook, PrimaryFirst is already empty
→ successor Recover PlayMotion
→ StartRecover END
→ native weapon cleanup 7 -> 5
```

Therefore the existing StopMotion before-snapshot cannot capture the clean outgoing-Hit stack. This is a diagnostic-observation limitation, not a lifecycle conclusion. EV-174/EV-175 and the current B6 docs have already been corrected in Normal Chat.

### Frozen task

Add one diagnostic-only Win32 caller-stack record at the **existing player `sAICombatMoveStartRecover` BEGIN hook**, while the outgoing attack-Hit Primary is still observable and **before** the unchanged original StartRecover call.

The purpose is only to answer the clean-path B6 question:

> What Game / Script_Game / Engine / SPU caller context surrounds clean StartRecover entry while the exact outgoing Hit is still visible, so it can later be compared with legitimate reaction replacement and bad direct replacement?

### Required behavior

Inside the already-existing `AICombatMoveStartRecover_FrameCollisionTest` hook:

1. preserve the existing player-only gating;
2. preserve the existing `COMBATMOVE STARTRECOVER BEGIN` record;
3. before the original StartRecover call, if the current Primary snapshot is an attack-Hit using the already-existing `CollisionDiagnostics::IsAttackHitPrimaryMotion` classifier, capture a short stack with the already-supported `CaptureStackBackTrace` mechanism and the established stack capacity;
4. emit a clearly named record such as `HIT STARTRECOVER BEGIN STACK` containing only factual context already supported by the current diagnostics: outgoing Primary motion, actor, action, phase, state time, current movement animation, equipped-source snapshot, captured stack frames, and `CleanupBehaviorChanged: 0`;
5. call the original StartRecover exactly once with the same argument;
6. preserve the existing `COMBATMOVE STARTRECOVER END` record unchanged.

The exact small helper shape/naming is an implementation detail as long as the semantic contract above is preserved.

### Protected behavior / frozen non-decisions

Do **not**:

- add a new Gothic 3 hook;
- add production cleanup/repair;
- add lifecycle ownership/pending-finalization state;
- add timers, polling, per-frame scans, caches, or persistent diagnostic state;
- add a new attack-family/cause classifier;
- treat StartRecover as production Hit-end authority;
- change collision/marker behavior;
- change the existing direct PlayMotion replacement-stack probe;
- change the existing StopMotion probe except for a strictly necessary compile/mechanical dependency (none is currently expected);
- infer or read guessed stack/frame/object layouts;
- build or run Gothic 3 in Work.

StartRecover is being used here only as a **clean-path diagnostic observation point** because the valid B6-B run proves the outgoing Hit is still present at BEGIN. Bad paths are already known to bypass StartRecover.

### Allowed source files

Only these source files may be changed unless a concrete compile-level dependency makes one additional file strictly necessary:

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h`

If an additional source file appears necessary for semantic reasons, stop and report the contradiction instead of broadening the task.

### Required source audit

Before commit, verify from the diff/source that:

- the new stack capture can run only on the existing player StartRecover path and only when the current Primary is an attack Hit;
- capture/logging occurs before the original StartRecover call;
- original StartRecover remains called exactly once with the unchanged SPU argument;
- existing BEGIN/END boundary logging remains present;
- direct PlayMotion replacement-stack logic is unchanged;
- StopMotion behavior is unchanged;
- no cleanup, repair, state, timer, polling, family rule, new hook, or guessed layout was added;
- collision/marker behavior is untouched;
- `git diff --check` passes.

### Work completion

Follow `docs/WORK_IMPLEMENTATION_PROTOCOL.md`:

1. read `docs/SESSION_ENTRYPOINT.md`, this file, and `docs/WORK_IMPLEMENTATION_PROTOCOL.md`;
2. inspect only the assigned source needed for this change;
3. implement the bounded diagnostic;
4. source-audit against this contract;
5. commit and publish on `docs/collision-source-evidence` (use the documented GitHub API fallback only if CLI push fails solely for missing credentials);
6. overwrite this file with a concise Work result including files changed, protected behavior, checks, what still needs build/runtime verification, and the final commit SHA;
7. STOP.

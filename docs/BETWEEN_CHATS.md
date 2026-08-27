# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Current bounded Work task

**From:** Normal Chat after isolated B6-B runtime interpretation  
**To:** Work  
**Date:** 2026-08-27  
**Branch:** `docs/collision-source-evidence`

## Step B6 — Add outgoing-Hit StopMotion stack diagnostic

### Why this task exists

EV-174 established three isolated clean 2H Normal transitions with this sequence:

```text
attack Hit Primary exists
→ StartRecover BEGIN
→ StopMotion(type 0) removes outgoing Hit Primary
→ Recover PlayMotion(type 0)
→ StartRecover END
→ native weapon cleanup 7 -> 5
```

The current B6 PlayMotion-only stack probe cannot emit on this clean path because the outgoing Hit has already been removed before successor PlayMotion begins.

This is a diagnostic limitation, not evidence against the lifecycle hypothesis.

### Target change

Add diagnostic-only Win32 stack capture to the **already-existing** player/type-0 `StopMotion` hook when its before-snapshot is an attack-Hit PrimaryFirst.

### Question the code must answer

> What script/SPU stack surrounds the outgoing attack-Hit StopMotion on StopMotion-first teardown paths, so runtime evidence can compare clean/reaction teardown with the existing direct PlayMotion replacement stack on bad paths?

### Frozen semantics

- Keep the existing direct PlayMotion B6 replacement-stack probe unchanged.
- In `StopMotion_FrameCollisionTest`, capture the before-snapshot exactly as today.
- If and only if that before-snapshot is an attack-Hit Primary according to the already-existing `CollisionDiagnostics::IsAttackHitPrimaryMotion` helper, capture a short `CaptureStackBackTrace` stack and factual actor/context **before** calling original StopMotion.
- Call original StopMotion exactly once with unchanged arguments.
- Emit a clearly named diagnostic record such as `HIT STOP STACK`; do not label the stop itself as a confirmed replacement.
- Preserve the existing StopMotion before/after log. Runtime analysis will correlate that record with the already-existing immediately following PlayMotion record to identify the actual successor.
- Use supported Win32 stack capture/module resolution only; no manual frame walking.

### Protected behavior

Do not change:

- collision activation/cleanup behavior;
- marker behavior or marker bookkeeping;
- attack callback suppression;
- B4/B5 SetCollisionGroup cleanup diagnostics;
- B3 StartRecover diagnostics;
- existing direct PlayMotion replacement-stack behavior;
- original StopMotion/PlayMotion call count or arguments.

### Allowed source scope

Expected source files only:

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h`

Use fewer files if possible. `docs/BETWEEN_CHATS.md` may be overwritten with the concise Work result at the end.

### Allowed hooks/interfaces

- existing `Hook_StopMotion`;
- existing `Hook_PlayMotion` remains unchanged;
- existing supported `CaptureStackBackTrace` / module-resolution pattern already used by B5/B6.

### Forbidden changes

Do **not** add:

- any new Gothic 3 hook;
- a `ProcessScript`, RunScript, CombatMove, ItlLoop, OnTick, timer, polling, or frame-loop hook/change;
- production cleanup or fallback repair;
- lifecycle ownership/pending-finalization state;
- family/cause-specific repair logic;
- new attack/filename classification rules;
- guessed motion-descriptor or stack-frame layouts;
- unrelated refactors.

### Authority to read

Start with:

1. `docs/SESSION_ENTRYPOINT.md`;
2. this file;
3. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`;
4. `docs/COLLISION_LOGGER_PLAN.md` §6 and §11;
5. EV-174 in `docs/EVIDENCE_LEDGER_STEP_B.md`;
6. only the exact source files above.

Do not load the whole repository/corpus unless a concrete implementation contradiction requires it.

### Required source audit

Before commit verify:

- original StopMotion is still called exactly once with unchanged arguments;
- stack/context capture happens before original only when the before-snapshot is an attack-Hit Primary;
- the new record is diagnostic-only and clearly distinguishes stop from confirmed replacement;
- no new hook or persistent lifecycle state was introduced;
- existing direct PlayMotion B6 logic is unchanged except for unavoidable mechanical sharing, if any;
- collision/marker behavior is untouched.

### Stop conditions

If the existing StopMotion hook cannot expose the required before-snapshot/context using the already-supported APIs, report the contradiction and stop. Do not add another hook or unsafe stack mechanism to compensate.

### Completion

Do not build or run Gothic 3.

Commit and push the source change on `docs/collision-source-evidence`, overwrite this file with the concise Work result + final commit SHA, then STOP.

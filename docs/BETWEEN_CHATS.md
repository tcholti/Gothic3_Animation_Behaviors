# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest handoff

**From:** Normal Chat  
**To:** Work  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

## Step B4/B4b Result — NATIVE CLEANUP ARCHITECTURE MAPPED

Read first:

- `docs/SESSION_ENTRYPOINT.md`
- `docs/COLLISION_CLEANUP_CALLSITE_MAP.md`
- `docs/COLLISION_LIFECYCLE_PLAN.md`
- `docs/WORK_IMPLEMENTATION_PROTOCOL.md`

B4/B4b established that exact native player weapon `7 -> 5` cleanup is performed from multiple action-specific `Script_Game.dll` call sites, plus a separate tested interruption cleanup call site at `Script_Game + 0x24AFF`.

Do **not** implement one hook per cleanup family. The production target remains one execution-level Hit lifecycle guard.

## Step B5 — BOUNDED CLEANUP PARENT-STACK PROBE

### Purpose

Answer only this question:

> Do the action-specific native cleanup paths and the tested interruption cleanup path share a useful higher caller/dispatcher/CombatMove boundary after the native cleanup opportunity?

### Implement only this diagnostic change

Use the **existing** `eCEntity::SetCollisionGroup` hook. Do not add another Gothic 3 hook.

At wrapper entry, for calls that are plausible cleanup candidates (`requested Item_Equipped` and current/before group `Item_Attack`), capture a short raw call stack as stack-local diagnostic data using a robust supported Win32 mechanism if available (for example `RtlCaptureStackBackTrace` / `CaptureStackBackTrace`).

Do not manually walk guessed EBP/frame layouts or depend on compiler-specific stack offsets. If robust stack capture is not viable in this Win32 build, report that contradiction and STOP rather than implementing an unsafe substitute.

After the original `SetCollisionGroup` call, preserve the existing B4 exact player-slot `7 -> 5` gate. For those exact cleanup records, extend `NATIVE CLEANUP CALL SITE` with a compact ordered stack list containing, for each captured frame where practical:

- frame index;
- raw address;
- containing module name/base;
- RVA relative to that module.

Keep the existing immediate caller/module/RVA fields unchanged so B4 evidence remains directly comparable.

Do not interpret or classify a frame as the common parent in code. The diagnostic should only expose the raw resolved stack; Normal Chat will compare families after runtime testing.

### Preserve existing behavior

- original `SetCollisionGroup` called exactly once with unchanged argument;
- collision-control behavior unchanged;
- marker behavior unchanged;
- existing StartRecover and player-only PrimaryFirst diagnostics may remain;
- no cleanup behavior;
- no lifecycle ownership/state;
- no timers;
- no Script `OnTick` expansion;
- no family-specific repair rules;
- no hook on any action-specific Script_Game cleanup function;
- no `sAICombatMoveItlLoop` hook yet;
- do not investigate/fix the deeper block-skip teardown in this task.

The stack capture data must remain local to the current SetCollisionGroup invocation; add no persistent runtime ownership state.

### Documentation

Do not rewrite the architectural docs from source speculation. If implementation reveals a source/API/platform contradiction, record it in this handoff.

`docs/COLLISION_CLEANUP_CALLSITE_MAP.md` is the detailed B4/B4b address authority.

### Acceptance

Source should allow a later native-only runtime comparison to answer whether Normal, Quick, Power/Pierce, Whirl, finishing/GetUp, and damage-interruption cleanup share any stable higher caller frame.

Do not build or run Gothic 3 in Work.

Commit and push the source changes, overwrite this file with a concise Work-to-Chat result and final commit SHA, then STOP.

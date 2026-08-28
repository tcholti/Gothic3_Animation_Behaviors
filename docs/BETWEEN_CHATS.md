# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Frozen Work task — Step B7 CombatMove full-stop stack diagnostic

**Date:** 2026-08-28
**Branch:** `docs/collision-source-evidence`

### Why this diagnostic is now justified

B6 rejected the replacement-triggered deferred-`ProcessScript()` candidate but strengthened the execution-level cleanup invariant.

B7 static/source audit then established:

- the SPU persists the current asynchronous AI instruction through `m_pfInstrCallback` plus instruction timing fields;
- `gCScriptRoutine_PS::AIFullStop()` invokes the currently persisted instruction callback with `fullStop=true`;
- `gCScriptRoutine_PS::AIStopCombatMove()` does the same only when that callback is exactly `gCScriptProcessingUnit::sAICombatMoveInstr`;
- the tested `sAICombatMoveInstr` stores its own address as the active instruction callback while CombatMove is still running and returns false; terminal/full-stop handling clears the callback and returns true;
- clean full Whirl Script_Game control flow calls the asynchronous CombatMove break block, returns false while it is still active, and only after CombatMove returns true falls through to the ordinary collision cleanup at `Script_Game +0x4E03C`;
- Script_Game reaction-control regions contain explicit `PSRoutine::FullStop()` calls before their later reaction handling, while tested legitimate reaction cleanup uses the separate `+0x24AFF` route.

The exact missing causal fact is now:

> **Does the bad block-skip terminate the persisted CombatMove instruction through `sAICombatMoveInstr(..., fullStop=true)`, and if so what caller stack/context does that full-stop have compared with legitimate reaction?**

Do not assume the answer.

### Frozen implementation contract

Use only the already-established tested-build `gCScriptProcessingUnit::sAICombatMoveInstr` function at:

```text
Game + 0x1696E0
```

Add **one diagnostic-only function hook** for this function using its authoritative SDK signature.

The hook must:

1. preserve every non-full-stop call unchanged except for forwarding it to the original exactly once;
2. only emit the new diagnostic record when:
   - `a_bFullStop == GETrue`;
   - `a_pSPU != nullptr`;
   - the SPU SelfEntity resolves to the player;
3. capture the factual caller stack **before** calling original;
4. capture only already-supported factual context, using existing helpers where possible:
   - actor;
   - native action;
   - animation phase;
   - `Routine.StateTime`;
   - `Routine.StatePosition`;
   - current movement animation;
   - current PrimaryFirst snapshot/name when available;
   - currently resolved equipped left/right collision-source snapshots/groups;
5. emit a clearly delimited record headed exactly:

```text
===== COMBATMOVE FULLSTOP STACK =====
```

6. call original `sAICombatMoveInstr` exactly once with the original arguments and return its original result unchanged;
7. update the startup banner so this B7 full-stop probe is identifiable at runtime.

The stack is factual caller/context evidence only. Do **not** classify the caller as block, reaction, Normal, Quick, Whirl or any other cause/family in source.

### Preserve unchanged

- B1 PrimaryFirst PlayMotion/StopMotion logging;
- B3 StartRecover BEGIN/END and StartRecover stack probe;
- B4/B5 cleanup call-site/parent-stack diagnostics;
- B6 direct replacement and factual ungated empty-Primary successor stack probes;
- existing 16-frame stack capacity;
- all collision marker/source behavior;
- attack callback suppression/bookkeeping behavior;
- marker occurrence/execution bookkeeping;
- all existing native cleanup behavior.

### Explicitly do NOT add

- production cleanup or repair;
- lifecycle ownership or pending-finalization state;
- persistent diagnostic state;
- timers, polling, per-frame/world scans or caches;
- a `ProcessScript` hook;
- separate `AIFullStop` or `AIStopCombatMove` hooks;
- offensive `5 -> 7` / `7 -> 7` stack capture in this task;
- attack/reaction/block-family classifiers;
- collision-group gating for whether the full-stop record is emitted;
- successor-name gating;
- guessed layouts or unsupported fields;
- changes outside the existing diagnostic source unless compilation strictly requires an already-authoritative include/signature adjustment.

### Source scope

Expected source scope only:

```text
prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
```

If the authoritative SDK signature cannot be hooked safely within this bounded scope, STOP and report the exact contradiction rather than expanding scope or guessing.

### Work procedure

Read:

```text
docs/SESSION_ENTRYPOINT.md
docs/BETWEEN_CHATS.md
docs/WORK_IMPLEMENTATION_PROTOCOL.md
```

Then:

1. implement only the frozen diagnostic above;
2. source-audit against every bounded rule;
3. do **not** build or run Gothic 3;
4. commit and push/publish the source change;
5. overwrite this file with a concise Work result including implementation/final commit SHA;
6. STOP.

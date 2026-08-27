# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest result

**From:** Normal Chat static binary/source inspection  
**To:** Work — bounded diagnostic implementation  
**Date:** 2026-08-27  
**Branch:** `docs/collision-source-evidence`

## Project scope context

For technical engine-facing prompts, use `docs/PROJECT_SCOPE_CONTEXT.md`.

> Context: authorized offline modding/reverse-engineering of the 2006 single-player game Gothic 3 using community SDK tooling. The target is the user's local game installation and our own mod DLL.

## Established architecture before B6

B5 parents are identified:

```text
Game + 0x1603D0 = gCScriptAdmin::RunScriptState(...)
Game + 0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
Game + 0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

These are generic script-execution machinery, not a combat-cleanup owner.

`gCScriptProcessingUnit::sAICombatMoveInstr` at tested `Game + 0x1696E0` is also too early: the CombatMove instruction can finish/return before action-specific `Script_Game` code performs native weapon `7 -> 5` cleanup.

Static comparison found no common immediate Script_Game post-cleanup helper across Normal/Quick/full Whirl. The first demonstrated shared ordinary post-cleanup point is the generic `RunScriptFunction` return.

Current candidate remains:

```text
exact owned offensive Hit replacement observed
-> mark exact execution pending-finalization
-> let Gothic finish its current native script dispatch
-> one tightly gated post-script opportunity:
       native cleanup observed -> no-op
       cleanup absent          -> repair
```

The script boundary would provide timing only. Exact Hit/source ownership must be acquired independently.

## Step B6 — HIT REPLACEMENT STACK PROBE — FROZEN

### Purpose

Determine whether all relevant actual attack-Hit replacement events occur inside the same SPU / `gCScriptProcessingUnit::ProcessScript()` execution context, so that a later one-shot post-script check would reliably occur after Gothic has had its native cleanup opportunity.

The runtime comparison must distinguish:

1. clean Hit -> Recover replacement;
2. legitimate damage/reaction replacement;
3. bad block-skip direct replacement with missing native cleanup.

### Allowed implementation

Use only the existing player/type-0 `eCVisualAnimation_PS::PlayMotion` hook established in B1.

At PlayMotion entry, use the already-retained outgoing PrimaryFirst identity from the B1 design. When the outgoing motion is an actual attack `Hit` execution and the incoming PrimaryFirst motion replaces it, emit one bounded diagnostic record, for example:

```text
===== HIT REPLACEMENT STACK =====
```

Record at minimum:

- high-resolution elapsed timestamp;
- outgoing exact PrimaryFirst motion name;
- incoming motion name/request;
- current action, phase and movement context already available to the probe;
- player LEFT/RIGHT equipped source names and current collision groups;
- a short supported Win32 stack captured with `CaptureStackBackTrace` (up to 16 frames is sufficient);
- for each captured frame, resolve containing module, module base and RVA using a supported Win32 module/address mechanism.

Capture the stack at the PlayMotion replacement boundary before the original PlayMotion call changes the observed execution state.

Preserve the existing SetCollisionGroup/native-cleanup diagnostics so replacement events can later be correlated with `7 -> 5` cleanup timing.

### Restrictions

- Do not add another Gothic 3 hook.
- Do not hook `ProcessScript`, `RunScriptFunction`, `RunScriptState`, `sAICombatMoveInstr`, or `sAICombatMoveItlLoop` in B6.
- Do not implement cleanup or lifecycle behavior.
- Do not add timers, polling, family-specific repair rules, block-skip fixes, or production state ownership.
- Do not manually walk guessed stack-frame layouts.
- If robust supported stack capture/module resolution is not viable in this hook context, document the contradiction and stop rather than using an unsafe workaround.
- Preserve existing collision and marker behavior exactly.
- Do not build or run Gothic 3 in Work.

### Work handoff requirement

Implement only this bounded diagnostic, source-review it, commit and push it, overwrite this `docs/BETWEEN_CHATS.md` with the concise Work-to-Chat result and final commit SHA, then STOP.

Runtime build/test/log interpretation remains Normal Chat + the user's authoritative Gothic 3 machine.

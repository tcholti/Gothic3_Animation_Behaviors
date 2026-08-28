# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Current result — B8 held-Use2 state-stack abandonment generalized

**Date:** 2026-08-28  
**Branch:** `docs/collision-source-evidence`  
**B7b diagnostic implementation:** `806c5bc2c6253c9c878161289aee667ea1bad5a6`  
**B8 raw:** `research/raw/2026-08-28_b8_player_dual_quick_state_stack_abandonment.log`  
**B8 raw commit:** `3c8484f3e6a123e6a5c5901318bd9c444cc0107b`

### B8 resolved

- The same held-Use2 FullStop path previously proven for full Whirl also appears in tested player Quick attacks across Dual (1H+1H), plain 1H, and Shield+1H.
- In the first physical copy of the B8 raw, Quick-state AIFullStop observations were 17 Dual, 11 plain-1H, and 7 Shield+1H. Every checked Quick-state record resolves to `Script_Game +0x633F7`, the return after the established `PSRoutine::FullStop()` call at `+0x633F1`, with `PressedKey=16` (`Use2`), `IsPressed=1`, `IsPressedBefore=1`.
- Representative armed failures in all three configurations show the weapon request `5 -> 7`, then the `+0x633F1` FullStop path while the Quick Hit is current, then Ambient/Parade with the weapon still group 7.
- Pre-activation failures also occur. Therefore the destructive state transition itself does not depend on whether offense was armed; the collision-cleanup obligation exists only when that execution actually requested offensive collision.
- The held-Use2 state-stack-abandonment mechanism is therefore not Whirl-specific and not Dual-specific for the tested player paths.

### Static/source follow-up resolved

The tested binaries and official SDK map one native state-change observation route:

```text
Script.dll PSRoutine::SetState                  +0x12F50
→ import gCScriptRoutine_PS::AISetState         Game +0x164320
→ SPU state-changing implementation             Game +0x16F5B0
```

Evidence:

- Script.dll export: `PSRoutine::SetState(bCString)` at `Script +0x12F50`.
- Script.dll disassembly at `+0x12F50` directly calls the imported `gCScriptRoutine_PS::AISetState`.
- Game.dll export: `gCScriptRoutine_PS::AISetState(bCString const&)` at `Game +0x164320`.
- Game disassembly shows the routine forwarding through the embedded SPU to `Game +0x16F5B0`.
- Official SDK documentation states SetState clears the state stack and resets state position / break-block bookkeeping.
- The bad held-Use2 branch performs `FullStop +0x633F1 -> SetState +0x63409` immediately.
- The tested legitimate reaction FullStop at `+0x2D0F2` instead returns at `+0x2D0F8` and jumps back into reaction control; it does not have the immediate bad-path `FullStop -> SetState` pair. Do not infer from this that reaction handling can never call SetState later.

## Frozen Work task — Step B9 native AISetState ordering diagnostic

### Exact question

> When player `gCScriptRoutine_PS::AISetState()` destructively replaces routine state, has Gothic's legitimate collision-cleanup opportunity already happened, or can native cleanup still occur afterward on legitimate paths?

This is **diagnostic only**. Do not add production cleanup or lifecycle behavior.

### One new hook only

Observe tested:

```text
Game +0x164320 = gCScriptRoutine_PS::AISetState(bCString const&)
```

Use the authoritative SDK/export signature and the existing proven `mCFunctionHook` ThisCall pattern already used for `gCScriptRoutine_PS::AIFullStop()`.

For player calls only, before the original AISetState executes, emit one factual record headed exactly:

```text
===== AISETSTATE CALLSITE =====
```

Record:

- elapsed time;
- actor address/name;
- requested state string from the real `bCString const&` argument;
- immediate caller address/module/RVA using `_ReturnAddress()`;
- a short caller stack, capacity 16;
- factual current routine state before original;
- action and ani phase;
- StateTime and StatePosition;
- current movement animation;
- PrimaryFirst snapshot using the existing diagnostic helper;
- existing left/right equipped-source factual snapshots;
- `CleanupBehaviorChanged: 0`.

Existing factual input fields may be reused if they already fall out of the shared B7b context helper, but **do not gate the new record on input, attack family, action, phase, collision group, requested state name, successor name, FullStop caller, or cleanup state**.

The diagnostic must call the original `AISetState` exactly once with the unchanged real argument and preserve its return/behavior. No post-call mutation.

Add a startup banner identifying Step B9 as a player AISetState ordering/callsite diagnostic.

### Preserve unchanged

Preserve:

- B7 `sAICombatMoveInstr(fullStop=true)` diagnostic;
- B7b `AIFULLSTOP CALLSITE` diagnostic;
- all B1–B6 diagnostics;
- direct PlayMotion / StopMotion / StartRecover probes;
- native cleanup observation;
- collision/marker/callback behavior;
- callback suppression/bookkeeping;
- marker occurrence/execution bookkeeping;
- PrimaryFirst logging.

### Forbidden

Do **not** add:

- production collision cleanup/repair;
- lifecycle ownership or pending-finalization state;
- persistent diagnostic state;
- timers, polling, per-frame/world scans, or caches;
- a ProcessScript hook;
- an internal `Game +0x16F5B0` hook;
- Script_Game call-site hooks at `+0x63409` or reaction locations;
- AIStopCombatMove hooks;
- offensive-request stack capture;
- attack/reaction/block/family classifiers;
- collision-group/input/state-name gating for the new record;
- guessed layouts.

### Work procedure

Read `docs/SESSION_ENTRYPOINT.md`, this file, and `docs/WORK_IMPLEMENTATION_PROTOCOL.md`. Use repository documentation as authority. Inspect only the source/API necessary for this frozen task.

Do not build or run Gothic 3 in Work.

Source-audit the result against this bounded contract, commit and push/publish the source changes, overwrite this file with a concise Work result and final commit SHA, then STOP.

### Runtime after Work — not part of Work

Normal Chat will independently source-review the implementation first. Only after review/build/deploy/load verification will the runtime fixture be frozen.

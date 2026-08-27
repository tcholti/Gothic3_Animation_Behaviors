# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest result

**From:** Normal Chat static binary/source inspection  
**To:** Next Normal Chat research/design session  
**Date:** 2026-08-27  
**Branch:** `docs/collision-source-evidence`

## Step B5 Parent Search — STATIC IDENTIFICATION COMPLETE

B5 runtime had shown:

```text
ordinary cleanup -> Game + 0x1605EB
interruption cleanup -> Game + 0x1604D3
```

Static export/disassembly inspection now identifies those parents exactly:

```text
Game + 0x1603D0 = gCScriptAdmin::RunScriptState(...)
    interruption post-call return = +0x1604D3

Game + 0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
    ordinary post-call return = +0x1605EB
```

Therefore B5 did **not** reach a central combat-cleanup function. It reached Gothic 3's generic script-execution layer.

Both paths converge one level higher in:

```text
Game + 0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

Inside the tested binary:

```text
+0x16F2C2 -> RunScriptFunction
+0x16F338 -> RunScriptState
+0x16F3A6 -> RunScriptState
```

The SDK confirms `ProcessScript()` is generic per-NPC ScriptFunction/ScriptState machinery, not combat-only. It also owns many non-combat delayed instructions. Do not treat `RunScriptFunction`, `RunScriptState`, or `ProcessScript` as unconditional collision-cleanup hooks.

B2 timing is now statically explained: after the main ScriptFunction/ScriptState dispatch, `ProcessScript()` later runs local/task callbacks through `gCScriptAdmin::RunScriptCallback()`. This matches the runtime observation that the original Quick callback begins after native cleanup and can repeat during Recover.

## Current Architectural Option — NOT YET FROZEN

One possible event-driven design is:

```text
exact owned offensive Hit replacement observed
-> mark that exact execution pending-finalization
-> let current native script dispatch finish
-> at a tightly gated post-script opportunity:
       native cleanup observed -> no-op
       cleanup absent          -> repair
```

This would use a broad script boundary only as a one-shot deferred checkpoint for an already-owned attack execution, never as attack ownership authority.

Before implementation, compare this design with any narrower CombatMove-specific post-native-cleanup boundary. Do not add a `ProcessScript` hook yet.

## Next Normal-Chat Questions

1. Is there a narrower combat-specific post-opportunity boundary below `ProcessScript`?
2. If not, is a one-shot deferred post-script checkpoint the smallest safe event-driven design?
3. What exact ownership/source gate would guarantee that Fist, bow, crossbow, magic and unrelated script actions cannot be mutated?
4. Which negative regression tests are still required after static/source analysis?

No Work coding task is frozen.

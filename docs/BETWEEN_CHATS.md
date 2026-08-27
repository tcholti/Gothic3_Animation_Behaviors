# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest result

**From:** Normal Chat static binary/source inspection  
**To:** Next Normal Chat research/design session  
**Date:** 2026-08-27  
**Branch:** `docs/collision-source-evidence`

## Step B5 Parent Search — STATIC IDENTIFICATION COMPLETE

B5 runtime parents are now identified:

```text
Game + 0x1603D0 = gCScriptAdmin::RunScriptState(...)
    interruption post-call return = +0x1604D3

Game + 0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
    ordinary post-call return = +0x1605EB
```

Therefore B5 reached Gothic 3's generic script-execution layer, not a central combat-cleanup function.

Both converge one level higher in:

```text
Game + 0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

The SDK confirms `ProcessScript()` is generic per-NPC ScriptFunction/ScriptState machinery with many non-combat delayed instructions.

B2 timing is now statically explained: main ScriptFunction/ScriptState work runs before later local/task `RunScriptCallback` processing. This matches the runtime observation that the original Quick callback begins after native cleanup.

## Narrower CombatMove Boundary Check

`gCScriptProcessingUnit::sAICombatMoveInstr` at tested `Game + 0x1696E0` is also too early as a post-cleanup boundary.

The tested binary:

- uses it as the active delayed-instruction callback while CombatMove is running;
- calls `sAICombatMoveStartRecover` from inside the instruction completion path when appropriate;
- clears the active instruction callback and returns success when the CombatMove instruction completes.

B4/B5 cleanup stacks do not contain `sAICombatMoveInstr`; native weapon cleanup happens afterward in the action-specific Script_Game function. Therefore instruction completion cannot itself be the fallback-cleanup point.

Static comparison also shows no common immediate Script_Game post-cleanup helper across even Normal/Quick versus full Whirl. The first demonstrated shared point after ordinary family-specific cleanup is the generic `RunScriptFunction` return.

## Current Architectural Candidate — NOT YET FROZEN

```text
exact owned offensive Hit replacement observed
-> mark that exact execution pending-finalization
-> let the current native script dispatch finish
-> at a tightly gated one-shot post-script opportunity:
       native cleanup observed -> no-op
       cleanup absent          -> repair
```

The generic boundary would be timing only; ownership must already belong to an exact attack execution/source.

## Recommended Next Diagnostic — DISCUSS BEFORE WORK

Before implementing cleanup, extend only the existing player/type-0 `PlayMotion` diagnostic to capture a short Win32 stack for **actual attack-Hit replacement events**.

Compare:

1. clean Hit -> Recover replacement;
2. legitimate damage/reaction replacement;
3. bad block-skip direct replacement with missing cleanup.

Question:

> Do all relevant replacement events occur inside the same SPU/`ProcessScript` invocation so that a post-`ProcessScript` one-shot check is guaranteed to run after Gothic's native cleanup opportunity?

Use the existing PlayMotion hook only; do not add a new Gothic hook or behavior yet.

## Negative-Scope Planning

If a generic SPU/script checkpoint survives the next diagnostic, later negative regression should include Fist, bow, crossbow and magic.

Fist is especially important because it can share ordinary melee actions while the tested logical Fist collision path does not request weapon-style `Item_Attack(7)`. Action enum alone must not define cleanup ownership.

Jackydima New Balance source confirms ranged/magic use distinct Aim/Reload/Cock/Cast/PowerCast and `PS_Ranged_*` paths, but source inspection cannot replace runtime proof that our eventual generic checkpoint remains a no-op for them.

No Work coding task is frozen yet.

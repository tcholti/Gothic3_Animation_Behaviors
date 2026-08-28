# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Frozen Work task — Step B7b exact AIFullStop caller observation

**Date:** 2026-08-28
**Branch:** `docs/collision-source-evidence`

### Established basis

B7 proved that bad full-Whirl block-skip and legitimate reactions both terminate the active CombatMove with `fullStop=true`, but only legitimate reaction proceeds to separate native collision cleanup.

Static tested-binary reconstruction now establishes:

- `Script_Game +0x61866` is the return point from the player-control `gESessionKey_Use2` handler (key 16);
- that handler calls helper `Script_Game +0x62FF0`;
- that helper contains exactly three `PSRoutine::FullStop()` calls: `+0x63108`, `+0x633F1`, `+0x6345F`;
- those calls are reached through different routine-state / button-edge / press-duration conditions;
- the B7 stack does not preserve enough optimized helper frames to distinguish which exact call fired.

Exact remaining question:

> Which exact FullStop caller is used by bad Whirl, what factual player routine/input state accompanies it, and how does it compare with legitimate reaction?

### Frozen implementation contract

Instrument only the already-established tested-build function:

```text
Game +0x164430 = gCScriptRoutine_PS::AIFullStop()
```

using its authoritative SDK member signature `void gCScriptRoutine_PS::AIFullStop()`.

Add one diagnostic-only function interception. Before original, obtain the original `gCScriptRoutine_PS *this`, capture `_ReturnAddress()` plus the existing short Win32 caller stack, and log only when `this` is non-null and `this->GetEntity()` resolves to the player.

Record factual context only:

- actor;
- immediate caller module/RVA;
- action and animation phase;
- `Routine.GetCurrentState()`;
- `Routine.StateTime` and `Routine.StatePosition`;
- `CharacterControl.PressedKey`;
- `CharacterControl.IsPressed`;
- `CharacterControl.IsPressedBefore`;
- `CharacterControl.DurationPressedMSecs`;
- current movement animation;
- PrimaryFirst snapshot/name when available;
- equipped left/right collision-source snapshots/groups;
- short caller stack.

Heading exactly:

```text
===== AIFULLSTOP CALLSITE =====
```

Call original exactly once with the original `this`; preserve return semantics. Update the startup banner to identify B7b.

Do not classify causes/families in source.

### Preserve unchanged

Preserve the B7 CombatMove fullStop diagnostic, all B1–B6 diagnostics, existing stack capacity, collision/marker/source behavior, callbacks/bookkeeping, marker occurrence/execution bookkeeping, and native cleanup.

### Explicitly do NOT add

Production cleanup/repair; lifecycle/pending-finalization state; persistent diagnostic state; timers/polling/scans/caches; ProcessScript or AIStopCombatMove instrumentation; instrumentation at the three individual Script_Game calls; offensive-request stack capture; family/reaction/block classifiers; collision-group/input-key/successor-name gates; guessed layouts.

### Source scope

Expected only:

```text
prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
```

If the authoritative member signature or player resolution cannot be implemented safely in that scope, STOP and report the exact contradiction rather than expanding or guessing.

### Work procedure

Read `docs/SESSION_ENTRYPOINT.md`, this file, and `docs/WORK_IMPLEMENTATION_PROTOCOL.md`; implement only this diagnostic; source-audit it; do not build/run Gothic 3; commit and push; overwrite this file with a concise Work result and final commit SHA; STOP.

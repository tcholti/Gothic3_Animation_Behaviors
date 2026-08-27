# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest result

**From:** Work + independent Normal Chat source review  
**To:** Normal Chat / home-PC validation  
**Date:** 2026-08-27  
**Branch:** `docs/collision-source-evidence`

## Step B6 Hit Replacement Stack Probe — SOURCE REVIEWED

### Changed files

Work changed:

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h`

Normal Chat then independently reviewed the exact diff before build/runtime validation.

### Result

The existing player/type-0 `eCVisualAnimation_PS::PlayMotion` hook remains the only B6 boundary; no Gothic 3 hook was added or moved.

For an outgoing explicit attack-Hit PrimaryFirst identity, B6 captures a fixed local 16-frame `CaptureStackBackTrace` snapshot before the unchanged original PlayMotion call. The pre-call context contains timestamp, outgoing name, action/phase/state-time/movement, incoming opaque request address, and player LEFT/RIGHT source names, addresses and groups.

The incoming motion descriptor remains opaque and is never dereferenced.

### Independent review correction

Work initially emitted `HIT REPLACEMENT STACK` after every type-0 PlayMotion request made while an attack-Hit PrimaryFirst was outgoing, even if the after-snapshot did not prove that PrimaryFirst actually changed. That was broader than the frozen B6 requirement.

Normal Chat corrected this before runtime testing:

- pre-call stack/context capture still occurs while the outgoing attack Hit is alive, because replacement can only be known after the original call;
- the record is emitted only when the B1 before/after PrimaryFirst snapshots show an actual replacement/restart;
- different motion name = replacement;
- same-name motion with a clear play-time rollback = restart/replacement;
- no new hook, persistent state, timer, polling, or collision behavior was added.

This keeps the diagnostic aligned with the B6 question while preserving same-name replacement evidence when the play time rolls back.

### Preserved scope

- Original PlayMotion is called exactly once with unchanged arguments.
- B1 PlayMotion, B4/B5 SetCollisionGroup, StartRecover, marker and marker-owned OnTick diagnostics remain.
- Collision and marker behavior remain unchanged.
- No cleanup, lifecycle state, timer, polling, repair rule, block-skip fix, ProcessScript/RunScript/CombatMove hook, or manual stack walk was added.
- B6 data is local to one PlayMotion invocation.

### Validation status

No build or Gothic 3 runtime test has yet been performed on the reviewed B6 source.

Home-PC validation still needs to establish:

1. DLL builds and loads;
2. stack capture/module resolution behaves as expected;
3. clean Hit -> Recover replacement stack;
4. legitimate damage/reaction replacement stack;
5. bad block-skip direct replacement stack with missing native cleanup;
6. whether those replacement paths share one useful SPU / `ProcessScript()` execution context.

**Work implementation commit:** `2d9e1f08a09b0f41b1ff0e9227ca37e2537690b0`  
**Work handoff commit:** `01fff792abae1a7e8ac55f88bf5395b0ae129fe6`  
**Independent review correction commit:** `dbd185ff8480ff1bf2625a57a6dd65d192462e58`

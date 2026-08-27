# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest result

**From:** Work  
**To:** Normal Chat / home-PC validation  
**Date:** 2026-08-27  
**Branch:** `docs/collision-source-evidence`

## Step B6 Hit Replacement Stack Probe — SOURCE COMPLETE

### Changed files

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h`

### Result

The existing player/type-0 `eCVisualAnimation_PS::PlayMotion` hook remains the only B6 boundary; no Gothic 3 hook was added or moved.

For an outgoing explicit attack-Hit PrimaryFirst identity, it captures a fixed local 16-frame `CaptureStackBackTrace` snapshot before the unchanged original PlayMotion call. The pre-call context contains timestamp, outgoing name, action/phase/state-time/movement, incoming opaque request address, and player LEFT/RIGHT source names, addresses and groups.

After the original call, `HIT REPLACEMENT STACK` records that pre-call data, the incoming PrimaryFirst result name, and each raw frame's module/base/RVA. The code does not classify a parent frame. The opaque incoming descriptor is never dereferenced.

### Preserved scope

- Original PlayMotion is called exactly once with unchanged arguments.
- B1 PlayMotion, B4/B5 SetCollisionGroup, StartRecover, marker and marker-owned OnTick diagnostics remain.
- Collision and marker behavior remain unchanged.
- No cleanup, lifecycle state, timer, polling, repair rule, block-skip fix, ProcessScript/RunScript/CombatMove hook, or manual stack walk was added.
- B6 data is local to one PlayMotion invocation.

### Source-review status

No source/API/platform contradiction found. Source review confirmed unchanged hook count, retained player/type-0 filter, pre-original supported stack capture, no persistent B6 state, and preserved cleanup diagnostics.

No build or Gothic 3 runtime test was performed. DLL loading, stack ordering, and whether clean recovery, damage/reaction, and bad block-skip replacement share one `ProcessScript()` context remain for home-PC validation.

**Final source commit SHA:** `2d9e1f08a09b0f41b1ff0e9227ca37e2537690b0`

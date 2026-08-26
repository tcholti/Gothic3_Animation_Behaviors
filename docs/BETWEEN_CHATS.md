# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest result

**From:** Work  
**To:** Normal Chat / home-PC validation  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

## Step B5 Cleanup Parent-Stack Probe — SOURCE COMPLETE

### Changed files

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h`

### Implemented diagnostic boundary

The existing main/hook bridge remains the sole owner of the existing `eCEntity::SetCollisionGroup` hook. No Gothic 3 hook was added or moved.

At wrapper entry, the existing immediate `_ReturnAddress()` capture remains unchanged. When the request is `Item_Equipped` and the before group is `Item_Attack`, the wrapper additionally captures up to 16 raw frames with the supported Win32 `CaptureStackBackTrace` API into a fixed stack-local snapshot before calling the original function.

After the original call, the existing B4 player equipped-slot and exact `7 -> 5` gate remains authoritative. Only those exact records append:

- captured frame count;
- ordered frame index and raw address;
- containing module name and base;
- RVA relative to the resolved module.

The code does not classify or interpret any frame as a common parent.

### Preserved behavior and scope

- Original `SetCollisionGroup` is called exactly once with the unchanged argument.
- Existing B4 immediate caller/module/base/RVA fields are unchanged.
- Existing general SetCollisionGroup, StartRecover, player-only PrimaryFirst, marker, and marker-owned OnTick diagnostics remain.
- Collision-control and marker behavior are unchanged.
- No cleanup, lifecycle ownership/state, timer, polling expansion, family-specific repair, action-specific cleanup hook, `sAICombatMoveItlLoop` hook, or block-skip fix was added.
- Stack capture data exists only for the current wrapper invocation.

### Source/API status

No source/API/platform contradiction was found. `CaptureStackBackTrace` is a supported Win32 stack-capture mechanism and avoids manual frame-layout walking.

Source review confirmed one existing SetCollisionGroup hook, one original call, pre-original candidate gating, post-original exact cleanup gating, fixed local storage, and per-frame from-address module resolution.

Compilation, DLL loading, actual stack depth/order, module/RVA resolution, and whether tested cleanup families share a stable higher frame remain unverified until home-PC build/runtime testing.

**Final source commit SHA:** `807307570b85bcdd4f1c3c703204dbd34560feb6`

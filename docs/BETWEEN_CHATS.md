# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest result

**From:** Work  
**To:** Normal Chat / home-PC validation  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

## Step B4 Native Cleanup Call-Site Probe — SOURCE COMPLETE

### Changed files

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h`

### Existing hook and call behavior

No hook was added or moved. The existing main/hook bridge remains the sole owner of the `eCEntity::SetCollisionGroup` hook.

At wrapper entry it now captures MSVC's raw `_ReturnAddress()` as a stack-local fact. The wrapper then:

1. reads the existing before group;
2. calls original `SetCollisionGroup` exactly once with the unchanged argument;
3. preserves existing marker-source retirement;
4. reads the existing after group;
5. forwards the caller address to diagnostics with the existing facts.

### New compact record

A `NATIVE CLEANUP CALL SITE` record is emitted only when:

- the changed entity matches the player's equipped LEFT and/or RIGHT source;
- requested group is `Item_Equipped` (5);
- before group is `Item_Attack` (7);
- after group is `Item_Equipped` (5).

The record contains:

- high-resolution elapsed time;
- source name/address and player-slot match;
- raw caller/return address;
- containing module resolution via `GetModuleHandleExA(FROM_ADDRESS | UNCHANGED_REFCOUNT)`;
- module filename and base;
- caller return-address RVA relative to that module;
- the exact requested/before/after groups.

No module is assumed in advance.

### Preserved behavior and scope

- Existing general `SetCollisionGroup` output is preserved.
- StartRecover, player-only PrimaryFirst, marker, and old marker-owned `OnTick` probes remain unchanged.
- Collision-control code and behavior are unchanged and independent of diagnostics.
- No cleanup, lifecycle ownership, timer, polling/checking mechanism, family-specific repair, production decision, new hook, or `sAICombatMoveItlLoop` path was added.
- The separate block-skip/CombatMove teardown problem was not investigated or changed.

### Source/API status

No source/API contradiction was found. Source review confirms unchanged hook count, one original `SetCollisionGroup` call, one wrapper-entry return-address capture, exact player-slot/`7 -> 5` gating, and from-address module resolution.

Compilation, DLL loading, intrinsic/hook runtime behavior, and the actual cleanup caller module/RVA remain unverified until home-PC testing.

`docs/SOURCE_HOOK_GUIDE.md` was intentionally not updated yet: the exact runtime call site/enclosing function has not been established.

**Final source commit SHA:** `ddb44930401d1c22821cbde23b16e9845b06a08d`

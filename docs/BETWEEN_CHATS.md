# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest result

**From:** Work  
**To:** Normal Chat / home-PC validation  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

## Step B3 CombatMove StartRecover Boundary Probe — SOURCE COMPLETE

### Changed files

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h`

### Hook ownership and call boundary

The existing main/hook bridge now owns exactly one additional diagnostic hook:

- `gCScriptProcessingUnit::sAICombatMoveStartRecover(gCScriptProcessingUnit *)`;
- tested `Game.dll` RVA `0x16E360`;
- SDK-matching static `void GE_STDCALL` signature;
- stack-only/default function-hook mode.

For the player entity only, the wrapper:

1. logs and flushes `COMBATMOVE STARTRECOVER BEGIN`;
2. calls the original StartRecover function exactly once with the unchanged argument;
3. logs and flushes `COMBATMOVE STARTRECOVER END`.

The original function is `void`, so return semantics remain unchanged.

### Boundary record fields

Each BEGIN/END record contains:

- high-resolution elapsed timestamp;
- actor address and name;
- current Action;
- current AniPhase;
- current movement animation;
- existing PrimaryFirst snapshot availability, motion name, has-motion-instance, running, play time, max time, and play speed;
- equipped LEFT and RIGHT source resolution, identity/address, and collision group when available.

The diagnostic module reuses the existing PrimaryFirst snapshot and collision-source resolution paths. No persistent state was added.

### Diagnostic-output reductions

- Existing PrimaryFirst `PlayMotion`/`StopMotion` hooks and original calls remain; their output is now limited to motion type `0` owned by the player entity.
- Temporary Step B2 original attack-callback BEGIN/END output was removed.
- The Normal/Quick/Whirl callback wrappers were restored to their pre-B2 bodies, including the unchanged marked-Hit suppression paths.
- `SetCollisionGroup`, marker records, and the old marker-owned `OnTick` comparator remain available.

### Preserved behavior and scope

- Collision-control files and behavior are unchanged and independent of diagnostics.
- No cleanup, lifecycle ownership, timer, polling/checking mechanism, family-specific cleanup rule, or production decision was added.
- No `sAICombatMoveItlLoop` hook or investigation was added.

### Source/API status

No source/API contradiction was found. Source review confirms exactly one new hook/RVA, one StartRecover original call, no B2 output, player filtering on both B1 hook outputs, and no `ItlLoop` path.

Compilation, DLL loading, live hook execution, log ordering, and whether native offensive-collision cleanup occurs between StartRecover BEGIN and END remain unverified until home-PC testing.

**Final source commit SHA:** `86fd222ace9ef27e88f4846cf0f720c32dce6f6a`

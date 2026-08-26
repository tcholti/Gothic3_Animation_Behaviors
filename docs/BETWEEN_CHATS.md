# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest result

**From:** Work  
**To:** Normal Chat / home-PC validation  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

## Step B2 Original-Callback Boundary Probe — SOURCE COMPLETE

### Changed files

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h`

### Existing hook ownership

No hook was added or moved. The existing main/hook bridge still owns the three callback hooks exactly once:

- `OnAI_Attack`;
- `OnAI_QuickAttack`;
- `OnAI_WhirlAttack`.

### Diagnostic boundary records

On unsuppressed paths, only when the callback actor is the player entity, each family now:

1. logs and flushes an `ORIGINAL ATTACK CALLBACK <family> BEGIN` record;
2. calls Gothic 3's original callback exactly once with the unchanged argument;
3. logs an `ORIGINAL ATTACK CALLBACK <family> END` record;
4. returns the original result unchanged.

Each BEGIN/END record contains:

- high-resolution elapsed timestamp;
- actor address and name;
- callback family;
- boundary label;
- current Action;
- current AniPhase;
- current movement animation;
- the existing PrimaryFirst snapshot fields: availability, motion name, has-motion-instance, running, play time, max time, and play speed.

The diagnostic module reuses the existing PrimaryFirst snapshot reader. No persistent state was added.

### Preserved behavior and probes

- The marked-Hit suppression path is unchanged and does not call or log around the original callback.
- Collision-control code and behavior are unchanged and remain independent of diagnostics.
- No hook, timer, polling/checking path, lifecycle state, cleanup behavior, or special-case behavior was added.
- Step B1 `PlayMotion`/`StopMotion`, the existing `SetCollisionGroup` logger, and the old `OnTick` comparator are unchanged.

### Source/API status

No source/API contradiction was found. Source review confirms unchanged hook count, one original call per callback wrapper, and six player-filtered boundary log calls.

Compilation, DLL loading, runtime ordering, and whether native `SetCollisionGroup(...5)` occurs between BEGIN and END remain unverified until home-PC testing.

**Final source commit SHA:** `106209bdefa6c9c52e1f1408a3d148dd52b2664e`

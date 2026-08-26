# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest result

**From:** Work  
**To:** Normal Chat / home-PC validation  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

## Step B1 PrimaryFirst Event Probe — SOURCE COMPLETE

### Changed files

- `prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h`

### Hook ownership

The existing main/hook bridge owns each new diagnostic hook exactly once:

- `eCVisualAnimation_PS::PlayMotion` — Engine RVA `0x30860`;
- `eCVisualAnimation_PS::StopMotion` — Engine RVA `0x30980`.

Only motion type `0` / PrimaryFirst is observed. Other motion types call the original function directly. No wrapper-level or `StopAtLoopEnd` hook was added.

### Logged event data

For both PlayMotion and StopMotion, diagnostics capture paired stack-local snapshots immediately before and after the original call, then log:

- request-before-original versus result-after-original;
- elapsed timestamp;
- owning entity address and name via `GetEntity()`, where available;
- motion type;
- snapshot availability;
- motion name;
- has-motion-instance;
- running;
- play time;
- max time;
- play speed.

The event probe reuses the existing `PrimaryMotionLifetimeSnapshot` definition and snapshot-reading path. It adds no persistent lifecycle state.

### Preserved behavior

- Collision-control code and decisions are unchanged.
- The existing v0.20 `OnTick` PrimaryFirst lifetime probe remains as the temporary comparator.
- No cleanup, ownership/correlation table, attack-family exception, or production decision was added.

### Source/API status

Official SDK declarations match the requested high-level signatures and RVAs cleanly. No source/API contradiction remains.

Compilation, DLL loading, hook execution, runtime logging, and whether these events cover every actual PrimaryFirst end/replacement remain unverified until home-PC build/runtime testing.

**Final source commit SHA:** `81e88026a4b47086a8995ab65d2933a041f8d2fd`  
(The probe implementation commit is `7dcd514b0bcd51c05453e3e55500a927b9063159`; the final source commit applies the required namespace qualification.)

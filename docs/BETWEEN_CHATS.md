# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

This file exists so the user does not need to copy long Work reports into Chat or long Chat instructions into Work.

## How to use it

- The session finishing a bounded task updates this file directly in GitHub.
- The receiving session reads this file before asking the user to repeat the handoff.
- For a Work task, normal Chat may replace the handoff below with the next bounded implementation assignment.
- At the end of that Work task, Work replaces it with its concise implementation report.
- Durable facts, architecture decisions, evidence, and project state still belong in their proper canonical documents. This file is only the latest bridge.
- Do not paste full diffs, logs, or long reports here. Point to the relevant commit/file when more detail is needed.

## Latest handoff

**From:** Work  
**To:** Normal Chat / local home-PC validation  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`  
**Implementation commit:** `325c98e725502229bf796083e52c0fa977803cc0`

### Completed

Step A source refactor is complete and pushed.

`Script_FrameCollisionTest` remains one research DLL with one owner for each Gothic 3 hook, but its source is now separated into:

- `Script_FrameCollisionTest.cpp` — bootstrap and hook bridge;
- `CollisionControl.cpp/.h` — collision behavior and behavioral state;
- `CollisionDiagnostics.cpp/.h` — observational logging and diagnostic state;
- `FrameCollisionShared.h` — shared facts/results/enums;
- `HookBridgeRuntime.cpp/.h` — shared high-resolution timing;
- `CMakeLists.txt` — builds all modules into the existing DLL.

Collision control does not depend on diagnostics. No lifecycle-cleanup redesign or new lifecycle logger behavior was added.

### Intended behavior parity

The refactor is intended to preserve v0.20 behavior for Normal/Quick/full-Whirl eligibility, marked-motion suppression, native fallback, RIGHT/LEFT/BOTH/OFF exact-set behavior, rearm, deduplication, authored-occurrence budgets, marker-owned-window bookkeeping, Quick/Whirl `StatePosition`, and existing diagnostics.

### Not yet verified

No compilation or Gothic 3 runtime test was performed in Work.

Still unverified:

- MSVC compilation/linkage;
- DLL loading and hook installation;
- live marker/native behavior parity;
- diagnostic ordering/output;
- PrimaryFirst lifetime probe after modularization.

### Next action

On the home PC:

1. synchronize the local repository to the current branch;
2. configure/build `Script_FrameCollisionTest`;
3. if compilation fails, diagnose the smallest source/interface correction in normal Chat before returning to Work;
4. if it builds, install and run a small v0.20 parity test before beginning Step B;
5. do not start the lifecycle diagnostic redesign until Step A parity is established.

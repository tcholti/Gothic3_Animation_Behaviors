# Local Workstation Paths

**Status:** Workstation-specific operational reference  
**Updated:** 2026-09-18

## Purpose

Record the User's current Windows paths for Gothic 3 development and testing. These paths are operational data for this workstation, not portable project requirements.

## Canonical paths

| Purpose | Current path |
|---|---|
| Gothic 3 runtime/game root | `E:\SteamLibrary\steamapps\common\Gothic 3` |
| Gothic 3 executable | `E:\SteamLibrary\steamapps\common\Gothic 3\Gothic3.exe` |
| Runtime mod-script DLL directory | `E:\SteamLibrary\steamapps\common\Gothic 3\scripts` |
| Gothic / mod INI directory | `E:\SteamLibrary\steamapps\common\Gothic 3\Ini` |
| Unpacked custom animation directory | `E:\SteamLibrary\steamapps\common\Gothic 3\Data\_compiledAnimation` |
| G3 Animation Behaviors repository | `E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\Gothic3_Animation_Behaviors` |
| User save/options/crash-log directory | `C:\Users\Tamerlan\Documents\Gothic3` |

## Operational rules

- Do not derive the installed Gothic 3 runtime root by walking upward from the repository path.
- `E:\Mods\1.Game Files\Gothic 3\Modkit\Gothic 3\Gothic3.exe` is a separate Modkit copy, not the runtime used for these tests.
- `E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 Edit (world)\Gothic 3\Gothic3.exe` is a separate editor/tool copy, not the runtime used for these tests.
- **Deploy `Script_FrameCollisionTest.dll` / `Script_FrameCollisionBehaviorTest.dll` only to the runtime mod-script DLL directory `E:\SteamLibrary\steamapps\common\Gothic 3\scripts`, never to the Gothic 3 runtime/game root.**
- `Script_FrameCollisionBehaviorTest.dll` and `Script_FrameCollisionTest.dll` are mutually exclusive runtime twins.
- Runtime logs such as `Script_FrameCollisionTest.log` are written in the Gothic 3 runtime root.
- Exact sync/build/deploy/hash/startup commands are owned by `PROJECT_OPERATING_PROCEDURES.md` POP-01 through POP-04. This file owns paths/environment facts only; do not duplicate or improvise a competing deployment procedure here.
- On this workstation, CMake is available in **Developer PowerShell for VS 2022**; an ordinary Windows PowerShell session may not have `cmake` on `PATH`. Use the Developer PowerShell environment for CMake build commands rather than treating a plain-PowerShell `cmake` lookup failure as a missing project dependency.
- The Python knowledge-state validator may be run from an ordinary PowerShell session where `python` is on `PATH`; Python is not part of the Gothic DLL build toolchain.
- If a future path stops resolving, verify it with the User or the filesystem rather than silently inventing a replacement.

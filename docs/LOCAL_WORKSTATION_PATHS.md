# Local Workstation Paths

**Status:** Workstation-specific operational reference  
**Updated:** 2026-09-02

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
- `Script_FrameCollisionBehaviorTest.dll` and `Script_FrameCollisionTest.dll` are mutually exclusive runtime twins.
- Runtime logs such as `Script_FrameCollisionTest.log` are written in the Gothic 3 runtime root.
- If a future path stops resolving, verify it with the User or the filesystem rather than silently inventing a replacement.

# Gothic 3 Animation Behaviors

General Gothic 3 animation-behavior research and implementation for configurable Raise behavior, attack playback speed, and animation-authored frame collision.

## Documentation

- [Documentation map and authority guide](docs/README.md) — explains which documents describe Gothic 3, active technical design, engineering/collaboration method, and historical material.
- [Session entry point](docs/SESSION_ENTRYPOINT.md) — read first when continuing the current work.
- [Work implementation protocol](docs/WORK_IMPLEMENTATION_PROTOCOL.md) — required before an active coding/Work session changes the collision research DLL.

Do not load every document by default. Follow the documentation map and open deeper files only when the current question requires them.

## Searchable animation-name data

- [Author-grouped attacks and stumbles](data/animation_names/author_grouped_attacks_and_stumbles.txt)
- [Complete native animation-name inventory](data/animation_names/all_animation_names.txt) — 5,991 sorted unique names from extracted `pak` + `p00` sources

## Standalone build

Initialize the pinned official SDK dependency:

```powershell
git submodule update --init --recursive
```

Configure the project for Gothic 3's required 32-bit target:

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A Win32
```

Build an individual DLL target:

```powershell
cmake --build build --config Release --target Script_FrameCollisionTest
```

Other available targets are `Script_G3AnimationBehaviors`, `Script_FrameEffectLogger`, and `Script_CombatMoveLogger`.

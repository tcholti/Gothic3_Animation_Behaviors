# Gothic 3 Animation Behaviors

General Gothic 3 animation-behavior research and implementation for configurable Raise behavior, attack playback speed, and animation-authored frame collision.

## Canonical documentation

- [Design](docs/DESIGN.md)
- [Research map](docs/RESEARCH_MAP.md)
- [Evidence ledger](docs/EVIDENCE_LEDGER.md)
- [Animation rules](docs/ANIMATION_RULES.md)
- [Animation catalog](docs/ANIMATION_CATALOG.md)
- [Source and hook guide](docs/SOURCE_HOOK_GUIDE.md)
- [Continuation handoff](docs/HANDOFF.md)

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

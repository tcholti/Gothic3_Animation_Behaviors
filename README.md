# Gothic 3 Animation Behaviors

General Gothic 3 animation-behavior research and implementation for configurable Raise behavior, attack playback speed, animation-authored frame collision, and reusable Gothic 3 modding knowledge.

## Branches

- **`docs/collision-source-evidence`** — current active development/research branch. It contains the newest collision implementation, current project state, and latest evidence.
- **`main`** — stable integration and reusable Gothic 3 knowledge baseline. Stable documentation/research improvements may be promoted here before the active collision implementation is ready; unfinished collision code should remain on the active branch until a deliberate stable integration point.

When continuing the current collision work, do not assume `main` contains the newest implementation state.

## Start Here

- [Session entry point](docs/SESSION_ENTRYPOINT.md) — minimal current-state front door.
- [Documentation and knowledge map](docs/README.md) — Hot/Warm/Cold retrieval routes and authority by question.
- [Evidence index](docs/EVIDENCE_INDEX.md) — route engine/research questions to exact EV ranges and raw logs.
- [Animation knowledge index](docs/ANIMATION_INDEX.md) — route filename/UseType/action/pose/asset questions to exact sections/data.
- [Knowledge maintenance protocol](docs/KNOWLEDGE_MAINTENANCE.md) — event-driven local documentation/evidence/archive updates; use when completing meaningful engineering events, not as routine pre-reading.
- [Knowledge authority registry](docs/KNOWLEDGE_REGISTRY.md) — tells which document owns each knowledge responsibility and what changes trigger an update.
- [Work implementation protocol](docs/WORK_IMPLEMENTATION_PROTOCOL.md) — compact bounded-implementation contract for Work/coding sessions.
- [Gothic 3 project collaboration delta](docs/COLLABORATION_RULES.md) — project-specific collaboration rules; broader CAM authority is external and should not be reloaded for normal prompts.

Do **not** load every document by default. The repository is designed as deep external memory: start with current state, then spot-search the exact technical knowledge needed for the current responsibility.

The maintenance protocol/registry are process tools, not mandatory context for every prompt. Normal Chat should apply their trigger logic automatically when a meaningful project event completes so the User does not have to request documentation housekeeping separately.

## Gothic 3 Knowledge Base Direction

The repository intentionally preserves detailed evidence, animation semantics, hook/source research, reverse-engineering results, test methodology, and searchable asset data so they can be reused beyond the current collision feature.

Large technical documents should be indexed and retrieved by topic/section/evidence ID/symbol rather than treated as mandatory reading.

> **Not necessary to read now does not mean not necessary to preserve.**

## Searchable Animation-Name Data

- [Author-grouped attacks and stumbles](data/animation_names/author_grouped_attacks_and_stumbles.txt)
- [Complete native animation-name inventory](data/animation_names/all_animation_names.txt) — 5,991 sorted unique names from extracted `pak` + `p00` sources

## Standalone Build

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

# Gothic 3 Animation Behaviors

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

General Gothic 3 animation-behavior research and implementation for configurable Raise behavior, attack playback speed, animation-authored frame collision, and reusable Gothic 3 modding knowledge.

## Branches

- **`docs/collision-source-evidence`** — current active development/research branch. It contains the newest implementation, current project state, and latest evidence.
- **`main`** — stable integration and reusable Gothic 3 knowledge baseline. Promotion from the active branch is deliberate rather than automatic.

Do not assume `main` contains the newest working implementation merely because it is the default branch.

## Start Here

This repository `README.md` is the **canonical front door** for both ordinary continuation and recovery after an interrupted/max-context Chat.

### Ordinary continuation

Use one first hop:

1. [Session entry point](docs/SESSION_ENTRYPOINT.md) — read this first for the active branch, current responsibility, recovery cue, and exact next route.

### If the previous Chat failed, hit max context, or became unusable

**Paste into a fresh Chat when no reliable handoff was possible:**

> Continue `Gothic3_Animation_Behaviors` in **NORMAL CHAT**. The previous Chat ended unexpectedly or reached maximum context before a reliable handoff could be prepared. Start from this README's interrupted-Chat **Recovery Lock**, treat `SESSION_ENTRYPOINT.md` and `BETWEEN_CHATS.md` as clues until reconciled, reconstruct only the recent durable tail on `docs/collision-source-evidence`, and do not begin new implementation or runtime testing until recovery is closed.

Do **not** blindly follow the old `NEXT` pointer. Start here and enter **Recovery Lock**:

1. do not start new implementation, freeze/run a new runtime experiment, or launch a new Work task;
2. read [Session entry point](docs/SESSION_ENTRYPOINT.md) first as a **clue, not unquestioned truth**;
3. orient only through the smallest necessary authority chain: [project charter](docs/README.md) §0 → [authority registry](docs/KNOWLEDGE_REGISTRY.md) → [knowledge maintenance](docs/KNOWLEDGE_MAINTENANCE.md) → the relevant specialist owner;
4. confirm the active branch/newest remote tail and reconstruct only what happened after the last trusted durable checkpoint;
5. close any missed POP-06 evidence transaction, perform missed smallest-owner maintenance, and repair stale `SESSION_ENTRYPOINT.md` / `BETWEEN_CHATS.md` pointers;
6. if recovery exposes broad cross-authority drift, unclear ownership, or document-structure questions, stop bounded recovery and invoke POP-10 before broader review edits;
7. verify that a fresh Chat starting from this README would now reach the correct responsibility with only intentionally active raw inputs, then release Recovery Lock.

[POP-11](docs/PROJECT_OPERATING_PROCEDURES.md#13-pop-11--normal-chat-continuity-and-interrupted-context-recovery) owns the **detailed** continuity/recovery mechanics. This root README owns their discoverable first hop. A review/audit should preserve that division unless the User deliberately changes the project entry model.

Only broaden when the current responsibility requires it:

- [Project charter and knowledge map](docs/README.md) — highest Gothic-specific authority beneath CAM; use for project purpose, long-term direction, authority topology, formal-audit preflight, or one-time subsystem orientation.
- [Collision reference](docs/COLLISION_REFERENCE.md) — compact current collision facts; use before evidence for already-settled questions.
- [Evidence index](docs/EVIDENCE_INDEX.md) — route proof-sensitive questions to exact EV ranges and provenance only when needed.
- [Animation knowledge index](docs/ANIMATION_INDEX.md) — route filename/UseType/action/pose/asset questions to exact sections/data.
- [Project operating procedures](docs/PROJECT_OPERATING_PROCEDURES.md) — retrieve the exact recurring Git/build/deploy/test/evidence/review/continuity procedure when that operation is active.
- [Work implementation protocol](docs/WORK_IMPLEMENTATION_PROTOCOL.md) — retrieve for bounded Work/coding sessions.
- [Knowledge maintenance protocol](docs/KNOWLEDGE_MAINTENANCE.md) and [authority registry](docs/KNOWLEDGE_REGISTRY.md) — maintenance/update routing tools, applied when meaningful project events or ownership questions require them.
- [Gothic 3 project collaboration delta](docs/COLLABORATION_RULES.md) — project-specific participant/tool allocation and CAM operationalization; retrieve when the collaboration boundary itself matters.

Do **not** load every document by default. The repository is designed as deep external memory: start with current state, then spot-search the exact technical knowledge needed for the current responsibility.

For a formal review/audit, do not start by treating documents as peers. Apply POP-10: establish `CAM → Gothic project charter → specialist authority → procedure/task` and each target's intended use before evaluating contradiction, duplication or cleanup.

The maintenance protocol/registry are process tools, not mandatory context for every prompt. Normal Chat should apply their trigger logic automatically when a meaningful project event completes so the User does not have to request documentation housekeeping separately.

## Gothic 3 Knowledge Base Direction

The repository intentionally preserves detailed evidence, animation semantics, hook/source research, reverse-engineering results, test methodology, and searchable asset data so they can be reused beyond the current collision feature.

Ordinary work consumes **current reference/architecture first**. Closed probes, audits and ledger volumes are cold archive material and are opened only for provenance, contradiction or reconstruction. The canonical lifecycle is `docs/KNOWLEDGE_MAINTENANCE.md` and is checked mechanically by `tools/knowledge/validate_knowledge_state.py`.

> **Preserve proof deeply; present current knowledge shallowly. Not necessary to read now does not mean not necessary to preserve.**

## Searchable Animation-Name Data

- [Author-grouped attacks and stumbles](data/animation_names/author_grouped_attacks_and_stumbles.txt)
- [Complete native animation-name inventory](data/animation_names/all_animation_names.txt) — 5,991 sorted unique names from extracted `pak` + `p00` sources

## Build Dependencies

The repository pins two SDK-related submodules with different responsibilities:

```text
thirdparty/gothic3sdk
= official Georgeto Gothic 3 SDK used by CMake/build targets

references/jackydima-gothic3sdk
= Jackydima SDK fork retained as source/API/reference material
  not a build dependency of the root CMake project
```

Initialize the pinned submodules with:

```powershell
git submodule update --init --recursive
```

Configure the project for Gothic 3's required 32-bit target:

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A Win32
```

## Current Build Products and Tools

The root CMake project currently exposes these DLL targets:

```text
Script_G3AnimationBehaviors
= production-direction behavior DLL
= currently owns the existing Raise / playback-speed implementation
= eventual public integration target; collision migration into it is later work

Script_FrameCollisionBehaviorTest
= diagnostics-free collision behavior research build
= same shared collision behavior source as the diagnostic twin

Script_FrameCollisionTest
= instrumented collision diagnostic twin
= same collision behavior source + CollisionDiagnostics / optional deep diagnostics

Script_CombatMoveLogger
= independent generic CombatMove / animation-speed diagnostic tool
= remains useful for future Raise/playback-speed research
```

`Script_FrameCollisionBehaviorTest` and `Script_FrameCollisionTest` are mutually exclusive runtime twins for controlled collision work; do not normally install/load both together.

The repository also contains the offline deterministic large-log processor under `tools/log_evidence/`. It is not a Gothic DLL build target.

For actual local validation, do **not** reconstruct build/deploy/hash/startup commands from this README or from historical task documents. Use the exact current blocks in `docs/PROJECT_OPERATING_PROCEDURES.md`:

```text
POP-01 = local branch synchronization
POP-02 = build target selection + exact build commands
POP-03 = selected-twin deployment + sole-live-DLL + SHA256 verification
POP-04 = startup/load verification
```

The obsolete `Script_FrameEffectLogger` target has been retired; its historical research remains recoverable through evidence/Git history.

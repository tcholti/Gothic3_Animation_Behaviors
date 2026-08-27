# Documentation Map

**Purpose:** Explain what each document is for, which documents are current authorities, and what a Chat/Work session should read for a given task.

Do **not** load every document by default. Start with the smallest set that answers the current question and broaden only when needed.

## 1. Start Here — Current Work

### `SESSION_ENTRYPOINT.md`

The current front door for any new Chat or Work session.

Use it to learn:

- what subsystem is active now;
- the current preferred architecture;
- what code is provisional;
- the immediate next step;
- which deeper files to read for the current task.

If another document's old "next step" conflicts with `SESSION_ENTRYPOINT.md`, use `SESSION_ENTRYPOINT.md` for the current continuation state.

### `BETWEEN_CHATS.md`

The short transient bridge between normal Chat and Work.

Use it only for the latest bounded handoff. It should be **overwritten, not accumulated**. Durable technical facts and decisions belong in their canonical documents.

### `WORK_IMPLEMENTATION_PROTOCOL.md`

The general execution contract for a coding/Work session.

Read this before changing code in Work.

### `FROZEN_WORK_TASK_RULES.md`

The stricter contract for an implementation task whose design has already been frozen in Normal Chat.

Read it before editing any frozen Work task. It defines the semantic preflight, missing-decision stop rule, operational meanings of simple/separate/good engineering, completion audit, and current independent-review expectation.

### `PROJECT_SCOPE_CONTEXT.md`

Short factual context for engine-facing Gothic 3 prompts involving hooks, disassembly, binary inspection or similar terminology. It also points frozen Work tasks to the required frozen-task rules.

## 2. Active Technical Design — What We Intend to Build

### `DESIGN.md`

Canonical overall project design for Raise control, playback-speed control, authored-frame collision control, native/fallback behavior, and general actor scope.

### `COLLISION_LIFECYCLE_PLAN.md`

Current authority for the collision-lifecycle redesign.

Contains:

- preferred execution-level cleanup model;
- fallback source-aware model;
- RIGHT/LEFT/BOTH/OFF desired-set semantics;
- Step-B causal constraints;
- ordinary/interruption/bad-skip three-path model;
- marker-bookkeeping versus physical-cleanup distinction;
- current research and implementation gates.

### `COLLISION_LOGGER_PLAN.md`

Current diagnostic design for collision-lifecycle research.

### `COLLISION_TEST_PLAN.md`

Current staged test design. Tests challenge the general architecture; they are not instructions to create one production branch per test case.

## 3. Gothic 3 Knowledge and Evidence — How the Game Works

### `EVIDENCE_LEDGER.md`

Canonical base evidence ledger, EV-001 through EV-157.

### `EVIDENCE_LEDGER_STEP_B.md`

Canonical continuation for Step-B lifecycle research, EV-158 onward.

It is separate only to preserve the large established base ledger without rewriting it during the 2026-08-26 consolidation. Read the two ledgers together as one numbered evidence sequence.

### `COLLISION_CLEANUP_CALLSITE_MAP.md`

Build-specific reverse-engineering map of successful native melee collision cleanup.

Use it for:

- action-specific `Script_Game.dll` cleanup call sites;
- LEFT/RIGHT branches;
- legitimate interruption cleanup at `Script_Game + 0x24AFF`;
- B5 stack-parent findings around `Game + 0x1604D3` and `Game + 0x1604E0..0x1605EB`;
- the direct evidence that runtime action semantics can differ while reusing the same serialized animation asset family.

This is evidence/reference, not production-hook authority.

### `ANIMATION_RULES.md`

Canonical engine-facing animation semantics and naming rules.

### `ANIMATION_CATALOG.md`

Curated catalog of exact animation families/names and animation-author observations.

### `SOURCE_HOOK_GUIDE.md`

Practical Gothic 3 source/hook/research guide.

Use it to decide where to search, which reference source to trust, and which proven hook/build patterns are available. Build-specific lifecycle call-site detail may be delegated to `COLLISION_CLEANUP_CALLSITE_MAP.md` rather than duplicated here.

### `RESEARCH_MAP.md`

Long-form engineering/research history. Useful for established findings and history, but older "current/next" sections may lag. `SESSION_ENTRYPOINT.md` is authoritative for the present continuation state.

### Searchable source data

Outside `docs/`:

- `data/animation_names/author_grouped_attacks_and_stumbles.txt`
- `data/animation_names/all_animation_names.txt`

Use these for exact filename searches rather than loading large catalogs into chat context unnecessarily.

## 4. Engineering and Collaboration Method — How We Work

### `ENGINEERING_GUIDE.md`

Language-independent principle-first engineering guide.

Core themes include understand before changing, invariants rather than symptoms, generative simplicity, smallest sufficient models, resource discipline, responsibility boundaries, and evidence-earned exceptions.

### `COLLABORATION_RULES.md`

Project collaboration and usage/review workflow.

### `WORK_IMPLEMENTATION_PROTOCOL.md`

Also belongs here, but is listed under Start Here because it is mandatory for active coding sessions.

### `FROZEN_WORK_TASK_RULES.md`

Operational contract for faithful implementation after Normal Chat has already resolved the architecture/semantics.

### `WORK_COLLABORATION_EVOLUTION.md`

Living empirical retrospective and future roadmap for collaboration with Work.

Use it to understand:

- which task types Work has handled well or poorly in actual sessions;
- the B1/B4/B5 positive patterns and B6 failure/correction lesson;
- how CAM principles are translated into operational definitions and checks;
- the frozen-task preflight template;
- the independent post-Work review loop;
- task-specific trust levels rather than global trust assumptions;
- the long-term plan for a reusable CAM-derived implementation-agent framework for Gothic 3, UAA and future projects.

This document records learning and evolution. It does not override the active implementation contracts.

## 5. Continuity and Historical Material

### `HANDOFF.md`

Detailed continuation/history document from earlier stages. Valuable for version-by-version detail, but **not the current front door**.

### `research/raw/`

Raw logs and research artifacts. Use them when a documented conclusion must be rechecked against original evidence; do not load them routinely.

## 6. Authority by Question

| Question | First document |
|---|---|
| What are we doing right now? | `SESSION_ENTRYPOINT.md` |
| What did the other Chat/Work session just do or ask for? | `BETWEEN_CHATS.md` |
| How must Work generally implement code? | `WORK_IMPLEMENTATION_PROTOCOL.md` |
| How must Work implement a frozen task? | `FROZEN_WORK_TASK_RULES.md` |
| What scope context should accompany engine-facing Gothic 3 prompts? | `PROJECT_SCOPE_CONTEXT.md` |
| What have we learned about collaborating with Work and how should it evolve? | `WORK_COLLABORATION_EVOLUTION.md` |
| What is the overall intended mod architecture? | `DESIGN.md` |
| What is the current collision design? | `COLLISION_LIFECYCLE_PLAN.md` |
| What are the tested native cleanup call sites/stacks? | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| What should the collision diagnostics capture? | `COLLISION_LOGGER_PLAN.md` |
| What tests should we run? | `COLLISION_TEST_PLAN.md` |
| Is this Gothic 3 behavior actually proven? | `EVIDENCE_LEDGER.md` + `EVIDENCE_LEDGER_STEP_B.md` |
| How do Gothic 3 animation names/states work? | `ANIMATION_RULES.md` |
| Which exact animations/assets are relevant? | `ANIMATION_CATALOG.md` + `data/animation_names/` |
| Where/how should we search or hook Gothic 3? | `SOURCE_HOOK_GUIDE.md` + `COLLISION_CLEANUP_CALLSITE_MAP.md` when lifecycle-specific |
| What engineering principles should guide the solution? | `ENGINEERING_GUIDE.md` |
| How should Chat/Work/reviews/documentation be managed? | `COLLABORATION_RULES.md` |
| What happened in older prototype versions? | `HANDOFF.md`, `RESEARCH_MAP.md`, evidence ledgers |

## 7. Consolidation Policy

Create a new document only when it has a distinct job that would become harder to understand if mixed into an existing authority.

Prefer merging when two files answer the same question, have the same authority level, are normally read together, or duplicate the same plan/model.

Do not merge merely to reduce file count when documents serve different responsibilities.

`BETWEEN_CHATS.md` is deliberately separate because it is only a short replaceable transport layer between sessions.

`WORK_COLLABORATION_EVOLUTION.md` is deliberately separate from the active Work contracts because it records empirical lessons and future experiments; `WORK_IMPLEMENTATION_PROTOCOL.md` and `FROZEN_WORK_TASK_RULES.md` remain the operational authorities.

`EVIDENCE_LEDGER_STEP_B.md` is an explicit preservation exception: it continues the numbered canonical ledger without risking an accidental rewrite of the large EV-001..EV-157 base during the 2026-08-26 consolidation. It may be merged into the base ledger later if a safe repository-local edit is convenient; until then the two files form one authority sequence.

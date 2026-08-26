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

Use it for only the latest bounded handoff so the user does not need to paste long Work reports into Chat or long Chat instructions into Work.

It should be **overwritten, not accumulated**. Durable technical facts and decisions still belong in their proper canonical documents.

### `WORK_IMPLEMENTATION_PROTOCOL.md`

The execution contract for a coding/Work session.

It defines behavior integrity, principle-first implementation, modularity, resource discipline, stop conditions, and the required implementation sequence.

Read this before changing code in Work.

## 2. Active Technical Design — What We Intend to Build

### `DESIGN.md`

Canonical overall project design for:

- Raise control;
- playback-speed control;
- authored-frame collision control;
- native/fallback behavior;
- general actor scope.

Use this for the broad intended architecture of `Gothic3_AnimationBehaviors`.

### `COLLISION_LIFECYCLE_PLAN.md`

Current authority for the collision-lifecycle redesign.

Contains:

- preferred System 1 execution-level cleanup model;
- fallback System 2 source-aware model;
- complete flow diagrams;
- RIGHT/LEFT/BOTH/OFF desired-set semantics;
- current hypotheses;
- v0.20 scaffolding to revisit;
- research-DLL modularization decision;
- implementation and test sequence.

### `COLLISION_LOGGER_PLAN.md`

Current diagnostic design for collision-lifecycle research.

Use it when changing or extending collision diagnostics.

### `COLLISION_TEST_PLAN.md`

Current staged test design.

Use it after the modularized logger/diagnostics are ready. The tests challenge the general architecture; they are not instructions to create one production branch per test case.

## 3. Gothic 3 Knowledge and Evidence — How the Game Works

These documents describe Gothic 3 itself, our observed evidence, or practical engine research. They are distinct from collaboration/engineering-method documents.

### `EVIDENCE_LEDGER.md`

Canonical fact/hypothesis/design-decision ledger.

Use it to determine whether a claim is:

- confirmed;
- strongly supported;
- a working hypothesis;
- unknown;
- a design decision.

Do not promote a hypothesis to engine fact merely because it appears in older code or documentation.

### `ANIMATION_RULES.md`

Canonical engine-facing animation semantics and naming rules.

Use it for native action/phase/state/UseType/filename interpretation.

### `ANIMATION_CATALOG.md`

Curated catalog of exact animation families/names and animation-author observations.

Use it for concrete animation examples and family-specific asset evidence.

### `SOURCE_HOOK_GUIDE.md`

Practical Gothic 3 source/hook/research guide.

Use it to decide where to search, which reference source to trust for a question, and which proven hook/build patterns are available.

### `RESEARCH_MAP.md`

Long-form engineering/research state accumulated across the project.

It remains useful for established findings and research history, but its older "current/next" sections may lag the immediate active task. For today's next step, `SESSION_ENTRYPOINT.md` is authoritative.

### Searchable source data

Outside `docs/`:

- `data/animation_names/author_grouped_attacks_and_stumbles.txt`
- `data/animation_names/all_animation_names.txt`

Use these for exact filename searches rather than loading large catalogs into chat context unnecessarily.

## 4. Engineering and Collaboration Method — How We Work

These are not Gothic 3 engine-reference documents. They define the reasoning and collaboration method used to produce the technical work.

### `ENGINEERING_GUIDE.md`

Language-independent principle-first engineering guide.

Core themes include:

- understand before changing;
- solve invariants rather than symptoms;
- generative simplicity;
- smallest sufficient models;
- deliberate resource use;
- clear responsibility boundaries;
- future separation boundaries;
- evidence-earned exceptions.

### `COLLABORATION_RULES.md`

Project collaboration and usage/review workflow.

Use it for:

- normal Chat versus Work responsibilities;
- reasoning-level guidance;
- targeted versus broad repository review;
- documentation checkpointing;
- continuity and usage-awareness practices.

### `WORK_IMPLEMENTATION_PROTOCOL.md`

Also belongs here, but is listed under Start Here because it is mandatory for active coding sessions.

It translates the broader engineering principles into concrete implementation rules.

## 5. Continuity and Historical Material

### `HANDOFF.md`

Detailed continuation/history document from earlier stages of the collision investigation.

It contains valuable version-by-version evidence and prior implementation state, but it is **not the current front door**. Do not use its older authority order or old "next step" over `SESSION_ENTRYPOINT.md` and the current active-design documents.

Open it when historical implementation detail is needed.

### `research/raw/`

Raw logs and research artifacts.

Use them when a specific documented conclusion must be rechecked against original evidence. Do not load them routinely.

## 6. Authority by Question

Use this rule of thumb:

| Question | First document |
|---|---|
| What are we doing right now? | `SESSION_ENTRYPOINT.md` |
| What did the other Chat/Work session just do or ask for? | `BETWEEN_CHATS.md` |
| How must Work implement it? | `WORK_IMPLEMENTATION_PROTOCOL.md` |
| What is the overall intended mod architecture? | `DESIGN.md` |
| What is the current collision design? | `COLLISION_LIFECYCLE_PLAN.md` |
| What should the collision diagnostics capture? | `COLLISION_LOGGER_PLAN.md` |
| What tests should we run? | `COLLISION_TEST_PLAN.md` |
| Is this Gothic 3 behavior actually proven? | `EVIDENCE_LEDGER.md` |
| How do Gothic 3 animation names/states work? | `ANIMATION_RULES.md` |
| Which exact animations/assets are relevant? | `ANIMATION_CATALOG.md` + `data/animation_names/` |
| Where/how should we search or hook Gothic 3? | `SOURCE_HOOK_GUIDE.md` |
| What engineering principles should guide the solution? | `ENGINEERING_GUIDE.md` |
| How should Chat/Work/reviews/documentation be managed? | `COLLABORATION_RULES.md` |
| What happened in older prototype versions? | `HANDOFF.md`, `RESEARCH_MAP.md`, `EVIDENCE_LEDGER.md` |

## 7. Consolidation Policy

Create a new document only when it has a distinct job that would become harder to understand if mixed into an existing authority.

Prefer merging when two files:

- answer the same question;
- have the same authority level;
- are normally read together;
- duplicate the same plan/model rather than separating responsibilities.

Do not merge merely to reduce file count when the documents serve different audiences or responsibilities.

Current example: the former `COLLISION_LIFECYCLE_MODELS.md` was merged into `COLLISION_LIFECYCLE_PLAN.md` because the models are part of the same design authority.

`BETWEEN_CHATS.md` is deliberately separate because it is not an authority or history file; it is only a short replaceable transport layer between sessions.

Future consolidation candidates should be reviewed at meaningful checkpoints rather than during every implementation cycle.

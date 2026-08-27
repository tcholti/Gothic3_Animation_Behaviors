# Gothic 3 Animation Behaviors — Documentation and Knowledge Map

**Purpose:** Route a Chat, Work session, contributor, or Gothic 3 modder to the smallest useful authoritative material without losing access to deep technical evidence.

> **Do not load every document by default. Find the current responsibility, open the smallest relevant source, and broaden only when the question requires it.**

---

## 1. Branch Model

### Active development branch

`docs/collision-source-evidence`

This is the current collision research/implementation branch and contains the newest project state, evidence, prototype code, and continuation material.

### Stable branch

`main`

`main` is the stable integration and reusable Gothic 3 knowledge baseline.

Stable documentation/research improvements may be promoted to `main` before the current collision implementation is ready. Experimental or not-yet-stable collision code should remain on the active branch until a deliberate stable integration point is reached.

When continuing current collision work, do **not** assume `main` contains the newest implementation state.

---

# 2. Retrieval Model — Hot / Warm / Cold

The documents are not a reading list. They are external project memory with different retrieval roles.

## HOT — normally enough to start or resume

### `SESSION_ENTRYPOINT.md`

The front door for current project work.

Read it to learn:

- active branch and subsystem;
- current durable model/invariant;
- latest established result;
- exact next responsibility;
- which deeper authority is relevant now.

### `BETWEEN_CHATS.md`

Short transient bridge for the latest real Chat/Work/context transition.

Read it only when continuing that handoff. It should remain small and be replaced rather than accumulated.

### `WORK_IMPLEMENTATION_PROTOCOL.md`

Read when Work or another implementation agent is assigned a bounded source task.

It includes the previous frozen-task safeguards. There is no separate active frozen-task manual anymore.

### `COLLABORATION_RULES.md`

Gothic 3 project-specific collaboration delta.

General collaboration authority lives in the CAM repository; do not reload CAM documents for normal Gothic 3 prompts unless a process/collaboration question actually requires them.

---

## WARM — current subsystem/design knowledge

Open these when the current responsibility needs their model, not automatically at session start.

### `DESIGN.md`

Canonical overall intended architecture for the project.

### `COLLISION_LIFECYCLE_PLAN.md`

Current collision-lifecycle architecture/research plan.

Use for lifecycle ownership, cleanup model, current architecture alternatives, and research/implementation gates.

### `COLLISION_LOGGER_PLAN.md`

Current diagnostic design for lifecycle research.

### `COLLISION_TEST_PLAN.md`

Current staged runtime test design.

### `PROJECT_SCOPE_CONTEXT.md`

Short factual scope context for engine-facing prompts involving hooks, disassembly, binary inspection, and related reverse engineering.

---

## COLD / REFERENCE — deep Gothic 3 knowledge and evidence

These documents are intentionally preserved even when large. Retrieve the relevant section, evidence range, symbol, action family, or search term rather than reading the whole file by default.

### `EVIDENCE_LEDGER.md`

Canonical base evidence ledger, EV-001 through EV-157.

### `EVIDENCE_LEDGER_STEP_B.md`

Continuation of the same canonical evidence sequence, EV-158 onward.

The split is a preservation/convenience boundary, not two competing authorities.

### `COLLISION_CLEANUP_CALLSITE_MAP.md`

Build-specific reverse-engineering map of tested native melee collision cleanup call sites and stack-parent findings.

Use for exact Script_Game/Game call-site questions; it is evidence/reference, not production-hook authority.

### `ANIMATION_RULES.md`

Canonical engine-facing animation semantics and naming rules.

### `ANIMATION_CATALOG.md`

Curated catalog of exact animation families/names and animation-author observations.

### `SOURCE_HOOK_GUIDE.md`

Practical Gothic 3 source/hook/research guide.

Use targeted heading/symbol searches for hook patterns, SDK/reference-source guidance, and known engine boundaries.

### `RESEARCH_MAP.md`

Long-form research/engineering history and accumulated findings.

Useful for reconstructing how the model developed or locating older findings. Its historical "current/next" statements do not override `SESSION_ENTRYPOINT.md`.

### `ENGINEERING_GUIDE.md`

General engineering principles developed during the project.

Useful for architecture/review questions; it is not mandatory pre-reading for every coding task.

### Searchable animation-name data

Outside `docs/`:

- `data/animation_names/author_grouped_attacks_and_stumbles.txt`
- `data/animation_names/all_animation_names.txt`

Search these directly for exact native names rather than loading a large catalog merely to find a filename.

### Raw evidence

`research/raw/` and `research/archive/`

Use raw logs when a documented conclusion must be rechecked against original evidence or when extracting a new fact not represented in the summaries.

Do not load raw logs routinely.

---

# 3. Retrieval by Question

| Question | Start here | Broaden only if needed |
|---|---|---|
| What are we doing right now? | `SESSION_ENTRYPOINT.md` | named current design/evidence source |
| What did the other Chat/Work context just do? | `BETWEEN_CHATS.md` | exact commit/diff/source |
| What branch is current? | `SESSION_ENTRYPOINT.md` / this file | Git branch history |
| How should a bounded Work task execute? | `WORK_IMPLEMENTATION_PROTOCOL.md` | task-named source/API reference |
| How should this Gothic project collaborate? | `COLLABORATION_RULES.md` | CAM repository only for broader process questions |
| What is the overall intended architecture? | `DESIGN.md` | relevant evidence/reference |
| What is the collision lifecycle model? | `COLLISION_LIFECYCLE_PLAN.md` | call-site map / evidence IDs |
| What diagnostics should exist? | `COLLISION_LOGGER_PLAN.md` | source + evidence |
| What runtime tests should be run? | `COLLISION_TEST_PLAN.md` | evidence/raw logs |
| Is an engine behavior proven? | relevant Evidence Ledger section | raw log/source/API evidence |
| Where does native collision cleanup occur? | `COLLISION_CLEANUP_CALLSITE_MAP.md` | evidence ledger / source reference |
| How do animation names/actions/UseTypes work? | `ANIMATION_RULES.md` | catalog/name data/evidence |
| Which exact animation asset is relevant? | animation-name data / `ANIMATION_CATALOG.md` | `ANIMATION_RULES.md` |
| Where/how should Gothic 3 be searched or hooked? | targeted `SOURCE_HOOK_GUIDE.md` section | SDK/reference source/call-site map |
| Why did an older technical decision exist? | `RESEARCH_MAP.md` / evidence ledger | archived docs / Git history / raw logs |

---

# 4. Spot Search / Context Search Pattern

For large knowledge documents, prefer targeted retrieval.

A useful sequence is:

```text
current question
    ↓
choose likely authority from this map
    ↓
search exact concept / symbol / action / evidence ID / heading
    ↓
read the local section with enough surrounding context
    ↓
follow cited evidence or raw source only if the answer requires verification
```

Examples:

- searching QuickAttack source behavior → search `QuickAttack`, `QuickAttackR`, `QuickAttackL`, source/slot terms in `ANIMATION_RULES`, catalog, and evidence rather than reading every animation document;
- investigating `SetCollisionGroup` cleanup → search the call-site map/evidence IDs first;
- checking one known hook → search the hook/function/symbol in `SOURCE_HOOK_GUIDE` rather than rereading the guide;
- checking an old runtime conclusion → retrieve its evidence entry, then the raw log only if necessary.

Use full-document reading when the task genuinely requires broad synthesis, architecture reconstruction, contradiction resolution, or major consolidation.

---

# 5. Current Work Read Order

## Normal Chat — normal continuation

Usually:

1. `SESSION_ENTRYPOINT.md`;
2. `BETWEEN_CHATS.md` only if a relevant transition exists;
3. exact current evidence/source supplied by the User or named by the entry point;
4. broader design/reference only when needed.

Do not reload unchanged stable documents after every prompt in the same context.

## Work — bounded source implementation

Read:

1. `SESSION_ENTRYPOINT.md`;
2. current `BETWEEN_CHATS.md` / frozen task when relevant;
3. `WORK_IMPLEMENTATION_PROTOCOL.md`;
4. assigned source files;
5. only the task-specific design/evidence/reference sections named by the task.

Additional source/API/repository inspection is allowed when implementation actually requires it. Broad project-document review is not the default implementation step.

---

# 6. Knowledge Preservation Policy

This repository is intended to accumulate reusable Gothic 3 modding knowledge.

Large technical documents are not considered waste merely because they are rarely read in full.

Preserve:

- confirmed/qualified evidence;
- source/hook findings;
- animation semantics and asset catalogs;
- build-specific reverse-engineering results;
- reusable test methodology;
- important negative findings;
- historical rationale that prevents rediscovery.

Optimize them through:

- clear headings;
- topical indexes;
- evidence IDs;
- stable terminology;
- cross-references;
- searchable symbols/keywords;
- separation of current conclusions from chronology where practical.

Do not solve context pressure by deleting the evidence needed to recover exact knowledge later.

> **Not necessary to read now does not mean not necessary to preserve.**

---

# 7. Archived Collaboration / Continuity Material

Superseded collaboration/handoff documents are stored under `docs/archive/` rather than remaining in the active reading surface.

They preserve the empirical path that produced the current rules and may be consulted for historical rationale, but they do not override current collaboration/continuity authority.

Current active authorities are:

- `COLLABORATION_RULES.md`;
- `WORK_IMPLEMENTATION_PROTOCOL.md`;
- `SESSION_ENTRYPOINT.md`;
- `BETWEEN_CHATS.md`.

---

# 8. Document-Creation Rule

Create a new document only when it has a distinct responsibility that would become harder to retrieve or understand if mixed into an existing authority.

Prefer adding an index/section to an existing knowledge document when the responsibility is already owned there.

Do not create one document per experiment, one rule per minor failure, or one handoff per prompt.

The objective is a repository that can be deep without making every task carry that depth in active context.

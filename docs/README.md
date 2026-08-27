# Gothic 3 Animation Behaviors — Documentation and Knowledge Map

**Purpose:** Route Chat, Work, contributors, and Gothic 3 modders to the **smallest useful authoritative material** while preserving deep technical knowledge for targeted recovery.

> **Do not load every document by default. Find the current responsibility, open the smallest relevant authority/index, and broaden only when the question requires it.**

---

## 1. Branch Model

### Active development / research

`docs/collision-source-evidence`

Contains the newest collision research, prototype implementation, current causal diagnostics, evidence and continuation state.

### Stable integration / reusable knowledge

`main`

`main` is the stable integration and reusable Gothic 3 knowledge baseline.

Stable documentation/research can be promoted independently of unfinished collision implementation. Do not assume `main` contains the newest prototype or current collision lifecycle candidate.

The branches currently diverge; `main` also contains one older collaboration-rules commit not present in the current branch history. Resolve that deliberately during promotion rather than blindly merging the entire development branch.

---

## 2. Retrieval Model — Hot / Warm / Cold

The repository is external project memory, **not a reading list**.

### HOT — start/resume here

#### `SESSION_ENTRYPOINT.md`

Minimal front door for the current branch/subsystem/next validation responsibility.

Read first for active collision work.

#### `BETWEEN_CHATS.md`

Transient latest Chat/Work handoff only.

Read only when continuing that exact transition. Replace rather than accumulate.

#### `COLLABORATION_RULES.md`

Gothic 3 project-specific collaboration delta.

General collaboration authority lives in the CAM repository; do not reload it for ordinary Gothic 3 engineering unless the process itself is being discussed.

#### `WORK_IMPLEMENTATION_PROTOCOL.md`

Read only for a bounded implementation/Work task.

---

### WARM — current architecture / current subsystem plans

Open only when the responsibility requires the model.

#### `DESIGN.md`

Canonical **project architecture** for Raise, speed and frame collision. It now avoids experiment chronology.

#### `COLLISION_LIFECYCLE_PLAN.md`

Current collision-lifecycle authority: execution ownership, cleanup invariant, Step-B constraints, deferred-finalization candidate and B6 gate.

#### `COLLISION_LOGGER_PLAN.md`

Current diagnostic architecture: hook ownership, factual event model, active B6 probe and diagnostic/release separation.

#### `COLLISION_TEST_PLAN.md`

Current staged validation plan beginning with B6 and continuing only if each causal gate passes.

#### `PROJECT_SCOPE_CONTEXT.md`

Short factual context for authorized local Gothic 3 engine-facing reverse engineering/modding prompts.

---

### COLD — routing indexes

Use these **before** opening the largest reference documents.

#### `EVIDENCE_INDEX.md`

Routes topics, symbols, Step-B stages and raw-log questions to exact EV ranges.

Use when asking “is this proven?” or “where did we establish this?”

#### `ANIMATION_INDEX.md`

Routes filename/UseType/action/phase/pose/R-L/asset/marker-authoring questions to exact sections or animation-name data.

Use before loading the full animation rules/catalog.

#### `RESEARCH_MAP.md`

Historical/topic router and milestone map.

It is **not current state**. Use it to recover where an older research line happened and where its durable result now lives.

---

### COLD — canonical deep references

Preserve these even when large. Search exact section/evidence/symbol rather than reading end-to-end by default.

#### `EVIDENCE_LEDGER.md`

Canonical EV-001 through EV-157.

#### `EVIDENCE_LEDGER_STEP_B.md`

Canonical continuation EV-158 onward.

The split is a preservation/convenience boundary, not competing authority.

#### `COLLISION_CLEANUP_CALLSITE_MAP.md`

Tested-build reverse-engineering lookup for action-specific native cleanup RVAs, interruption cleanup, B5 stacks, identified `RunScriptState` / `RunScriptFunction`, common generic `ProcessScript()`, and current B6 relationship.

#### `ANIMATION_RULES.md`

Canonical generalized animation filename/state/UseType/action/phase/pose/authoring semantics.

#### `ANIMATION_CATALOG.md`

Curated exact human-melee assets, family observations, source notes and controlled fixtures.

#### `SOURCE_HOOK_GUIDE.md`

Targeted source/API/symbol/RVA/hook-pattern lookup guide. Prototype chronology has been removed from the active guide and preserved elsewhere.

#### `ENGINEERING_GUIDE.md`

General engineering principles developed during the project. Useful for architecture/review questions, not routine pre-reading.

---

### COLD — searchable data / raw provenance

#### Animation-name data

- `data/animation_names/all_animation_names.txt` — 5,991 unique native names;
- `data/animation_names/author_grouped_attacks_and_stumbles.txt` — author-grouped exact names/notes.

For exact filename existence/variants, search these **before** opening the catalog.

#### Runtime/source evidence

- `research/raw/` — active/unprocessed causal artifacts;
- `research/archive/` — processed historical logs/source material.

Prefer an EV entry first. Open raw evidence when verifying wording, challenging an interpretation, or extracting a fact not represented canonically.

#### Superseded documentation snapshots

- `docs/archive/` — collaboration/continuity history;
- `docs/archive/technical_2026-08-27/` — byte-preserved technical documents from before the information-architecture cleanup.

Archived documents preserve history/rationale; they never override current authorities.

---

## 3. Retrieval by Question

| Question | Start here | Broaden only if needed |
|---|---|---|
| What are we doing now? | `SESSION_ENTRYPOINT.md` | named current architecture/source |
| What did the last Chat/Work handoff do? | `BETWEEN_CHATS.md` | exact commit/diff |
| How should bounded Work execute? | `WORK_IMPLEMENTATION_PROTOCOL.md` | only task-named source/API evidence |
| What is the overall architecture? | `DESIGN.md` | evidence index if a premise must be checked |
| What is the current collision lifecycle model? | `COLLISION_LIFECYCLE_PLAN.md` | cleanup map / EV range |
| What should current diagnostics capture? | `COLLISION_LOGGER_PLAN.md` | source + exact EV |
| What tests are next? | `COLLISION_TEST_PLAN.md` | evidence/raw only if a gate needs verification |
| Is an engine claim proven? | `EVIDENCE_INDEX.md` | exact ledger entry → raw/source |
| Where does native cleanup occur? | `COLLISION_CLEANUP_CALLSITE_MAP.md` | EV-163+ / raw B4-B5 logs |
| What does this animation token/UseType/action/pose mean? | `ANIMATION_INDEX.md` | exact `ANIMATION_RULES` section |
| Does this exact animation exist? | animation-name data | catalog/rules only for interpretation |
| Which family/fixture/source note is relevant? | `ANIMATION_INDEX.md` | `ANIMATION_CATALOG.md` |
| Where/how should I search or hook Gothic 3? | `SOURCE_HOOK_GUIDE.md` | SDK/reference/binary/evidence |
| Why did an older decision exist? | `RESEARCH_MAP.md` | EV entry → archive/raw/Git history |
| What is the historical pre-cleanup wording? | `docs/archive/technical_2026-08-27/` | Git history |

---

## 4. Spot-Search Pattern

For large knowledge sources:

```text
current question
→ choose authority/index from this map
→ search exact concept / symbol / action / EV ID / heading
→ read local section with enough context
→ follow provenance only if verification is necessary
```

Examples:

- `SetCollisionGroup` cleanup → `COLLISION_CLEANUP_CALLSITE_MAP`, not whole research history;
- `QuickAttackL` physical source → `ANIMATION_INDEX` + relevant EV/source section;
- `ProcessScript` lifecycle meaning → EV-170 + cleanup map §7;
- exact native `Wade` animation → search animation-name data first;
- old v0.13 occurrence-guard rationale → EV range / research archive / pre-IA history only if needed.

Read a full large document only for genuine broad synthesis, contradiction resolution, or another intentional information-architecture pass.

---

## 5. Current Read Orders

### Normal Chat — current continuation

Usually:

1. `SESSION_ENTRYPOINT.md`;
2. `BETWEEN_CHATS.md` only for an active handoff;
3. exact current evidence/source supplied by the User or named by the entry point;
4. an index/authority only when the question needs deeper context.

Within the same continuing context, do not reread unchanged authorities after every prompt.

### Work — bounded implementation

Usually:

1. `SESSION_ENTRYPOINT.md`;
2. relevant frozen task / `BETWEEN_CHATS.md`;
3. `WORK_IMPLEMENTATION_PROTOCOL.md`;
4. assigned source files;
5. task-specific authority/evidence section only.

Work may inspect necessary source/API material when implementation reveals a real need. It should not reconstruct the whole project by default.

---

## 6. Authority Boundaries

| Responsibility | Authority |
|---|---|
| current continuation / next validation | `SESSION_ENTRYPOINT.md` |
| transient cross-context handoff | `BETWEEN_CHATS.md` |
| overall intended system architecture | `DESIGN.md` |
| current collision lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| current diagnostic architecture | `COLLISION_LOGGER_PLAN.md` |
| current staged collision tests | `COLLISION_TEST_PLAN.md` |
| exact evidence status/provenance | evidence ledgers |
| evidence lookup | `EVIDENCE_INDEX.md` |
| animation generalized semantics | `ANIMATION_RULES.md` |
| concrete assets/fixtures | `ANIMATION_CATALOG.md` / data files |
| animation lookup | `ANIMATION_INDEX.md` |
| source/API/hook lookup | `SOURCE_HOOK_GUIDE.md` |
| build-specific cleanup reverse engineering | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| research chronology/topic history | `RESEARCH_MAP.md` / archives |
| actual implementation truth | current branch source + commits |

A historical “current/next” statement never overrides the current authority for that responsibility.

---

## 7. Knowledge Preservation Policy

This repository is intended to accumulate reusable Gothic 3 modding knowledge.

Preserve:

- confirmed and qualified evidence;
- important negative findings;
- raw logs needed for verification;
- source/API/hook/binary findings;
- animation semantics, inventories and author observations;
- build-specific reverse-engineering results;
- reusable diagnostic/test methods;
- historical rationale that prevents rediscovery.

Optimize retrieval through:

- stable headings;
- topic/index documents;
- evidence IDs;
- exact symbols/action names/RVAs;
- cross-references;
- separation of current architecture from chronology;
- archival snapshots before destructive consolidation.

> **Not necessary to read now does not mean not necessary to preserve.**

---

## 8. Archive Policy

Archive only when active placement is genuinely superseded.

Before archiving or compressing:

1. identify the durable technical value;
2. ensure canonical evidence/reference still carries it or preserve the original snapshot;
3. make the archived material discoverable from an active route when its history may still matter;
4. never archive a technical area merely because the current collision task does not use it.

The 2026-08-27 technical IA pass followed this rule by snapshotting old design/plan/source/history files before rewriting their active responsibilities.

---

## 9. Document-Creation Rule

Create a new document only when it has a distinct retrieval/authority responsibility.

Prefer:

- an index when a large knowledge document is hard to navigate;
- a new section when an existing authority already owns the topic;
- an evidence entry for a new proven fact;
- an archive snapshot for superseded chronology.

Avoid one document per experiment, one rule per minor failure, or another current-state document that competes with `SESSION_ENTRYPOINT.md`.

The objective is a repository that can be **deep without making every task carry that depth in active context**.

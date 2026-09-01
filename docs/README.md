# Gothic 3 Animation Behaviors — Documentation and Knowledge Map

**Purpose:** Route Chat, Work, contributors, and Gothic 3 modders to the **smallest useful authoritative material** while preserving deep technical knowledge for targeted recovery.  
**Updated:** 2026-09-01

> **Do not load every document by default. Find the current responsibility, recover a compact model of the relevant subsystem when needed, open the smallest relevant authority/index, and broaden only when the question requires it.**

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

### Relationship to the reusable CAM baseline

The central `tcholti/Collaborative-Agency-Model` repository separates its stable framework from a candidate reusable operational baseline on branch `current`.

Gothic 3 is an empirical project-specific instantiation of that broader model, not a file-for-file copy of its templates. The reusable baseline should be used as a comparison and starting structure; this project's mature authorities remain authoritative for their own responsibilities.

The project predates CAM's newer `PROJECT_MANIFEST.md` template. Its manifest responsibilities are already distributed across established authorities:

| Reusable project-manifest responsibility | Gothic 3 authority |
|---|---|
| repository / branch model | this `README.md` + `PROJECT_PIPELINE.md` |
| current-state entry point | `SESSION_ENTRYPOINT.md` |
| project-specific collaboration delta / participant allocation | `COLLABORATION_RULES.md` |
| stable naming/numbering/version/test/artifact conventions | `PROJECT_PIPELINE.md` |
| authority ownership / update triggers | `KNOWLEDGE_REGISTRY.md` |
| retrieval model / subsystem orientation routes | this `README.md` |
| evidence and maintenance lifecycle | `KNOWLEDGE_MAINTENANCE.md` + evidence authorities |
| recurring local operational sequences | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded implementation procedure | `WORK_IMPLEMENTATION_PROTOCOL.md` |
| transient continuation bridge | `BETWEEN_CHATS.md` when needed |
| technical architecture / intended behavior | `DESIGN.md` and subsystem authorities |

Do **not** create a parallel `PROJECT_MANIFEST.md` merely to conform to the newer template. Add one only if future project restructuring creates a genuinely distinct configuration responsibility that is no longer served clearly by the established authorities.

`PROJECT_PIPELINE.md` was added because a genuinely distinct responsibility was missing: project identity conventions such as test/gate numbering, EV/POP numbering, log/artifact naming, prototype/build identity and validation-stage meanings were scattered across procedures and history, allowing small arbitrary changes across Chat migrations.

When this project reveals a collaboration mechanism that may generalize, validate and apply it locally first, compare it with CAM `current` when useful, and preserve it as a candidate reusable lesson when warranted. Actual edits or promotion into the CAM repository are a separate dedicated CAM-evolution responsibility, not part of ordinary Gothic 3 maintenance. Conversely, when CAM `current` gains a new reusable mechanism, compare it against this project's actual needs and import only what fills a real gap rather than reshaping the project for template conformity.

---

## 2. Retrieval Model — Hot / Warm / Cold

The repository is external project memory, **not a reading list**.

The Hot/Warm/Cold model describes **where knowledge lives**. Normal Chat should also choose the right **retrieval depth** for the current situation.

### Retrieval depth A — current-state retrieval

Use when the immediate question is “where are we now?”

Normally read:

- `SESSION_ENTRYPOINT.md`;
- `BETWEEN_CHATS.md` only when an active transient handoff matters.

This recovers the active subsystem, accepted boundary and immediate responsibility.

The entry point may additionally route to one relevant `PROJECT_PIPELINE.md` section when the next task will create/change a project identifier, filename, version/build identity, branch/state meaning or validation/artifact-flow convention.

### Retrieval depth B — Subsystem Orientation Pass

Use once when entering a technical subsystem without a sufficiently fresh model of that subsystem in the current Chat context.

Typical triggers:

- a new Normal Chat enters ongoing work on collision, Raise, playback speed, animation selection or another substantial subsystem;
- the collaboration deliberately switches to a different subsystem inside the same Chat;
- work returns to a subsystem after substantial work elsewhere;
- the User identifies that previously established subsystem context is missing.

The orientation pass is **not** a full review. It should:

```text
identify subsystem
→ use the subject route / indexes below
→ spot-read the small set of canonical sections and evidence/topic routes needed for broad orientation
→ synthesize a temporary compact mental model
→ continue with question-specific retrieval
```

The temporary model should cover the subsystem's major mechanisms, established facts, important negative findings, known traps, relevant third-party/reference work and unresolved boundaries closely enough to avoid rediscovering established context.

Do **not** create another persistent summary document merely to hold this temporary model. Durable facts remain in their existing authorities.

Do not repeat the orientation pass for every prompt, every test, every Work handoff or every substep while the same subsystem model remains active.

### Retrieval depth C — Active-Problem Reconstruction Pass

Use once before proposing a new fix or architecture for a substantial active problem when the current Chat does not retain a sufficiently fresh causal model, even after current-state retrieval and subsystem orientation.

Typical triggers:

- a new Normal Chat resumes a long-running causal problem;
- work returns after enough implementation, isolation, contradiction resolution or runtime evidence that the causal route may have shifted;
- a proposed fix depends on distinguishing normal, legitimate interruption and failure paths;
- established negative results or scope boundaries are no longer fresh enough to constrain the next design safely.

Do **not** trigger this pass for every prompt, routine substep, already-frozen Work task, build/deploy continuation or another log inside the same still-fresh active problem.

Reconstruct only the targeted active problem by answering:

1. What is the observed phenotype?
2. How is it reproduced?
3. What is the normal mechanism?
4. What causal failure is established?
5. Which legitimate alternate or interruption paths exist?
6. What are the physical/gameplay consequences?
7. What scope has been proven?
8. Which explanations or fixes have been rejected?
9. Which observations or hypotheses remain unresolved?
10. Why does the current architecture or gate follow from that evidence?

Use `EVIDENCE_INDEX.md` plus the current subsystem authority; retrieve exact EV entries and raw/source provenance only as needed. Synthesize a temporary working model rather than creating another generic summary document. Keep that model for the same active problem and refresh it only when meaningful new evidence or a context change makes it stale.

### Retrieval depth D — question-specific retrieval

Use for ordinary ongoing work after current state and any necessary subsystem orientation are already known.

Retrieve only the exact EV entry, source section, symbol, hook, animation data, raw artifact, pipeline convention, or authority section needed for the current question.

The intended pattern is therefore:

```text
current state
→ subsystem orientation once when needed
→ active-problem reconstruction once when needed
→ exact retrieval for each concrete question
```

This keeps a **small active cognitive surface without reducing understanding to the current substep alone**.

---

### HOT — start/resume here

#### `SESSION_ENTRYPOINT.md`

Minimal front door for the current branch/subsystem/accepted boundary/immediate responsibility.

Read first for active project work.

#### `BETWEEN_CHATS.md`

Transient latest Chat/Work handoff only.

Read only when continuing that exact transition. Replace rather than accumulate.

#### `COLLABORATION_RULES.md`

Gothic 3 project-specific collaboration delta, including the current User/Normal Chat/Work division of labor and its intent.

General collaboration authority and the reusable candidate baseline live in the CAM repository; do not reload them for ordinary Gothic 3 engineering unless the collaboration/process itself is being discussed or compared.

#### `PROJECT_PIPELINE.md`

Stable project operating grammar: branch/state meanings, gate/test identifiers, EV/POP numbering, raw/derived artifact naming, prototype/build identity, document-versioning convention, validation stages and evidence-artifact flow.

Do **not** read end-to-end after every prompt. Retrieve the relevant section before creating or changing one of these conventions. A new Chat must preserve existing conventions rather than inventing new ones from preference.

#### `PROJECT_OPERATING_PROCEDURES.md`

Recurring concrete Git/build/deploy/load/test/evidence procedures. Read/spot-read only when entering those local operation sequences.

#### `WORK_IMPLEMENTATION_PROTOCOL.md`

Read only for a bounded implementation/Work task.

---

### WARM — current architecture / current subsystem plans

Open only when the responsibility requires the model.

#### `DESIGN.md`

Canonical **project architecture** for Raise, speed and frame collision. It avoids experiment chronology and routes current collision details to the subsystem authorities.

#### `COLLISION_LIFECYCLE_PLAN.md`

Current collision-lifecycle authority: exact execution/source obligations, temporary pre-Combat ScriptFunction bridge, native-cleanup precedence, controlled C1-R1 terminal repair and the current separation between generation-scoped marker identity and physical cleanup.

#### `COLLISION_LOGGER_PLAN.md`

Current diagnostic architecture: hook ownership, factual event model, C1/P2/R1/Gate-4 signal responsibilities and diagnostic/release separation.

#### `COLLISION_TEST_PLAN.md`

Current collision validation posture, closed gate boundaries and future required validation gates. It is not a chronological queue of already-completed tests.

#### `PROJECT_SCOPE_CONTEXT.md`

Short factual context for authorized local Gothic 3 engine-facing reverse engineering/modding prompts.

---

### COLD — routing indexes

Use these **before** opening the largest reference documents.

#### `EVIDENCE_INDEX.md`

Routes topics, symbols, lifecycle stages and raw-log questions to exact EV ranges.

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

Canonical EV-158 through EV-198.

#### `EVIDENCE_LEDGER_STEP_C.md`

Canonical EV-199 through EV-205.

#### `EVIDENCE_LEDGER_STEP_D.md`

Canonical EV-206 through EV-214: C1-R1 physical repair, second-pass structural/product gates and Gate-4/literal-regression closure.

#### `EVIDENCE_LEDGER_STEP_E.md`

Canonical EV-215 onward, beginning with final diagnostics-free architecture verification.

Ledger splits are preservation/retrieval boundaries, not competing authorities or new evidence namespaces.

#### `COLLISION_CLEANUP_CALLSITE_MAP.md`

Tested-build reverse-engineering lookup for action-specific native cleanup RVAs, interruption cleanup, script-runner stacks and generic script-processing context.

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

- `research/raw/` — active/unprocessed or still-comparative canonical raw artifacts;
- `research/archive/` — processed historical logs/source material;
- `research/derived/` — deterministic retrieval/analysis packages whose source raw artifacts remain canonical until deliberately migrated.

Prefer an EV entry first. Open raw evidence when verifying wording, challenging an interpretation, or extracting a fact not represented canonically. For oversized logs, use POP-07 and read the deterministic derived package before loading broad raw content.

Processed artifacts already cited under `research/raw/` are migrated only through a deliberate atomic provenance update; do not move them piecemeal for cosmetic cleanliness.

#### Superseded documentation snapshots

- `docs/archive/` — collaboration/continuity history;
- `docs/archive/technical_2026-08-27/` — byte-preserved technical documents from before the information-architecture cleanup.

Archived documents preserve history/rationale; they never override current authorities.

---

## 3. Retrieval by Question

| Question | Start here | Broaden only if needed |
|---|---|---|
| What are we doing now? | `SESSION_ENTRYPOINT.md` | `BETWEEN_CHATS.md` for exact transient continuation |
| What causal model constrains an active collision problem? | current subsystem authority | `EVIDENCE_INDEX.md` reconstruction route → exact EV entries |
| What did the last Chat/Work handoff do? | `BETWEEN_CHATS.md` | exact commit/diff |
| Who should own this responsibility / should this go to Work? | `COLLABORATION_RULES.md` §6 | `WORK_IMPLEMENTATION_PROTOCOL.md` only if bounded implementation is selected |
| What naming/numbering/version/test/artifact convention should I use? | `PROJECT_PIPELINE.md` relevant section | owning procedure/current plan only for task semantics |
| How do I execute the recurring Git/build/deploy/test/evidence operation? | `PROJECT_OPERATING_PROCEDURES.md` | `PROJECT_PIPELINE.md` only if a convention itself is relevant |
| How should bounded Work execute? | `WORK_IMPLEMENTATION_PROTOCOL.md` | only task-named source/API evidence |
| What is the overall architecture? | `DESIGN.md` | evidence index if a premise must be checked |
| What is the current collision lifecycle model? | `COLLISION_LIFECYCLE_PLAN.md` | cleanup map / EV range |
| What should current diagnostics capture? | `COLLISION_LOGGER_PLAN.md` | source + exact EV |
| What is the current collision validation posture / is any test actually pending? | `SESSION_ENTRYPOINT.md` → `COLLISION_TEST_PLAN.md` | `BETWEEN_CHATS.md` only for an exact active runtime contract |
| Is an engine claim proven? | `EVIDENCE_INDEX.md` | exact ledger entry → raw/source |
| Where does native cleanup occur? | `COLLISION_CLEANUP_CALLSITE_MAP.md` | relevant EV/raw logs |
| What does this animation token/UseType/action/pose mean? | `ANIMATION_INDEX.md` | exact `ANIMATION_RULES` section |
| Does this exact animation exist? | animation-name data | catalog/rules only for interpretation |
| Which family/fixture/source note is relevant? | `ANIMATION_INDEX.md` | `ANIMATION_CATALOG.md` |
| Where/how should I search or hook Gothic 3? | `SOURCE_HOOK_GUIDE.md` | SDK/reference/binary/evidence |
| Why did an older decision exist? | `RESEARCH_MAP.md` | EV entry → archive/raw/Git history |
| What is the historical pre-cleanup wording? | `docs/archive/technical_2026-08-27/` | Git history |

### Subsystem Orientation Routes

These routes are **subject guides**, not summaries. They point to the smallest set of existing authorities/indexes from which Normal Chat can reconstruct a broad working model before drilling into the current step.

| Subsystem | Orientation route |
|---|---|
| frame collision / collision lifecycle | `DESIGN.md` §§6–8 → collision rows in `EVIDENCE_INDEX.md` and `RESEARCH_MAP.md` → current `COLLISION_LIFECYCLE_PLAN.md`; use `SOURCE_HOOK_GUIDE.md` / `COLLISION_CLEANUP_CALLSITE_MAP.md` only for source/hook/cleanup context and `ANIMATION_INDEX.md` only when source/asset semantics matter |
| Raise | `DESIGN.md` §4 → Raise route in `EVIDENCE_INDEX.md` / `RESEARCH_MAP.md` → `ANIMATION_INDEX.md` for relevant Raise assets/selection; source guide only when implementation/hook details matter |
| playback speed | `DESIGN.md` §5 → CombatMove phase/speed route in `EVIDENCE_INDEX.md` / `RESEARCH_MAP.md` → speed section in `SOURCE_HOOK_GUIDE.md` when source/reference implementation context matters |
| animation semantics / selection | `ANIMATION_INDEX.md` → exact `ANIMATION_RULES.md` / `ANIMATION_CATALOG.md` / animation-name data routes → relevant evidence/research route only when behavior or historical interpretation must be recovered |
| source/API/hook investigation | `SOURCE_HOOK_GUIDE.md` → exact evidence/callsite authority named there → SDK/reference source only for the concrete symbol/API question |

When a new substantial subsystem becomes active, prefer adding a route here or to an existing index rather than creating another independently maintained subsystem-summary document.

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
- `ProcessScript` lifecycle meaning → exact EV + cleanup map section;
- exact native `Wade` animation → search animation-name data first;
- old v0.13 occurrence-guard rationale → EV range / research archive / pre-IA history only if needed;
- next runtime raw filename → `PROJECT_PIPELINE.md` §6, not old chat history.

Read a full large document only for genuine broad synthesis, contradiction resolution, or another intentional information-architecture pass.

---

## 5. Current Read Orders

### Normal Chat — current continuation

Usually:

1. `SESSION_ENTRYPOINT.md`;
2. `BETWEEN_CHATS.md` only for an active handoff;
3. if this Chat has not yet reconstructed a sufficiently fresh model of the active subsystem, perform the **Subsystem Orientation Pass once** using the relevant route above;
4. if substantial work on the active problem will interpret evidence or propose architecture and its causal model is stale, perform the targeted **Active-Problem Reconstruction Pass once**;
5. retrieve the relevant `PROJECT_PIPELINE.md` section only when the immediate responsibility creates/changes a project convention;
6. exact current evidence/source supplied by the User or named by the entry point;
7. question-specific authority/evidence only when the concrete step requires it.

Within the same continuing subsystem/problem context, do not rerun orientation or reconstruction, or reread unchanged authorities/procedures/pipeline sections, after every prompt.

### Work — bounded implementation

Usually:

1. `SESSION_ENTRYPOINT.md`;
2. relevant frozen task / `BETWEEN_CHATS.md`;
3. `WORK_IMPLEMENTATION_PROTOCOL.md`;
4. assigned source files;
5. task-specific authority/evidence section only.

Work should preserve already-frozen identifiers/filenames/build labels from the task contract and pipeline. It should not invent a new convention during bounded implementation.

Work may inspect necessary source/API material when implementation reveals a real need. It should not reconstruct the whole project by default. Subsystem orientation is primarily a Normal Chat research/design responsibility unless a Work task explicitly requires broader subsystem reasoning.

---

## 6. Authority Boundaries

| Responsibility | Authority |
|---|---|
| current continuation / immediate responsibility | `SESSION_ENTRYPOINT.md` |
| transient cross-context handoff | `BETWEEN_CHATS.md` |
| stable project naming/numbering/version/test/artifact conventions | `PROJECT_PIPELINE.md` |
| recurring local operational sequences | `PROJECT_OPERATING_PROCEDURES.md` |
| project collaboration configuration / relationship to CAM baseline | `COLLABORATION_RULES.md` + this `README.md` |
| documentation map / retrieval depth / subsystem orientation routing | `README.md` |
| overall intended system architecture | `DESIGN.md` |
| current collision lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| current diagnostic architecture | `COLLISION_LOGGER_PLAN.md` |
| current/future collision validation boundaries | `COLLISION_TEST_PLAN.md` |
| exact evidence status/provenance | `EVIDENCE_LEDGER.md` + Steps B/C/D/E |
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
- historical rationale that prevents rediscovery;
- historical identifiers/names necessary to preserve provenance even when later conventions evolve.

Optimize retrieval through:

- stable headings;
- topic/index documents;
- evidence IDs;
- stable gate/procedure/filename conventions;
- exact symbols/action names/RVAs;
- cross-references;
- separation of current architecture from chronology;
- archival snapshots before destructive consolidation;
- one-time subsystem orientation when broad context must be reconstructed.

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

Do not rename historical archived/raw evidence merely to conform to a newer pipeline convention unless a deliberate migration explicitly justifies doing so.

---

## 9. Document-Creation Rule

Create a new document only when it has a distinct retrieval/authority responsibility.

Prefer:

- an index when a large knowledge document is hard to navigate;
- a new subject/orientation route when the problem is broad retrieval rather than missing knowledge;
- a new section when an existing authority already owns the topic;
- an evidence entry for a new proven fact;
- an archive snapshot for superseded chronology.

`PROJECT_PIPELINE.md` is a justified distinct authority because project operating conventions are neither technical evidence nor recurring procedure sequences; scattering them across those layers had already caused cross-Chat drift.

Avoid one document per experiment, one rule per minor failure, another current-state document that competes with `SESSION_ENTRYPOINT.md`, a project manifest that merely duplicates the existing distributed configuration, or persistent “book summaries” that duplicate canonical authorities.

The objective is a repository that can be **deep without making every task carry that depth in active context**.

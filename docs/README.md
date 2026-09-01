# Gothic 3 Animation Behaviors — Documentation and Knowledge Map

**Purpose:** Route Chat, Work, contributors, and Gothic 3 modders to the **smallest useful authoritative material** while preserving deep technical knowledge for targeted recovery.  
**Updated:** 2026-09-01

> **Do not load every document by default. Find the current responsibility, recover a compact model of the relevant subsystem when needed, open the smallest relevant authority/index, and broaden only when the question requires it.**

---

## 1. Branch Model

### Active development / research

`docs/collision-source-evidence`

Contains the newest active research, implementation and continuation state.

### Stable integration / reusable knowledge

`main`

`main` is the stable integration and reusable Gothic 3 knowledge baseline. The verified collision-architecture checkpoint has already been deliberately promoted and verified; the temporary second-pass staging branch has been retired.

Normal development continues on `docs/collision-source-evidence`. Stable promotion remains deliberate rather than automatic.

### Relationship to CAM

CAM is the higher-order collaboration philosophy for this project. Gothic 3 is a project-specific operationalization of that constitutional layer, not a file-for-file copy of CAM templates.

The detailed Gothic↔CAM authority relationship is owned by `COLLABORATION_RULES.md`. In retrieval terms:

```text
CAM principles / philosophy
→ operationalized by Gothic project authorities
→ ordinary work reads the lowest relevant Gothic owner
```

Constitutional authority does not mean every engineering task must reread CAM. Use the maintained Gothic authorities for ordinary project work; retrieve CAM itself when collaboration structure, principle-level consistency, or a later upward-review question genuinely requires it.

A newer CAM revision does not silently rewrite Gothic project authorities. CAM evolution and project adoption are separate deliberate steps.

> **CAM boundary:** Gothic 3 work must not modify CAM rules, philosophy, profiles, procedures or theory. Any CAM evolution belongs to a separate User-authorized CAM-focused responsibility; applicable adopted changes are then deliberately operationalized back into Gothic authorities.

The project predates CAM's newer `PROJECT_MANIFEST.md` template. Its manifest responsibilities are already distributed across established authorities:

| Reusable project-manifest responsibility | Gothic 3 authority |
|---|---|
| repository / branch model | this `README.md` + `PROJECT_PIPELINE.md` |
| current-state entry point | `SESSION_ENTRYPOINT.md` |
| project-specific collaboration delta / participant allocation / CAM operationalization | `COLLABORATION_RULES.md` |
| stable naming/numbering/version/test/artifact conventions | `PROJECT_PIPELINE.md` |
| authority ownership / update triggers | `KNOWLEDGE_REGISTRY.md` |
| retrieval model / subsystem orientation routes | this `README.md` |
| evidence and maintenance lifecycle | `KNOWLEDGE_MAINTENANCE.md` + evidence authorities |
| recurring local operational sequences | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded implementation procedure | `WORK_IMPLEMENTATION_PROTOCOL.md` |
| transient continuation bridge | `BETWEEN_CHATS.md` when needed |
| technical architecture / intended behavior | `DESIGN.md` and subsystem authorities |

Do **not** create a parallel `PROJECT_MANIFEST.md` merely to conform to another template. Add one only if future restructuring creates a genuinely distinct configuration responsibility that is no longer served clearly by the established authorities.

`PROJECT_PIPELINE.md` exists because stable project identity conventions are a genuinely distinct responsibility from technical evidence and recurring procedures.

---

## 2. Retrieval Model — Hot / Warm / Cold

The repository is external project memory, **not a reading list**.

The Hot/Warm/Cold model describes where knowledge lives. Normal Chat should also choose the right retrieval depth for the current situation.

### Retrieval depth A — current-state retrieval

Use when the immediate question is “where are we now?”

Normally read:

- `SESSION_ENTRYPOINT.md`;
- `BETWEEN_CHATS.md` only when an active transient handoff matters.

This recovers the active subsystem, accepted boundary and immediate responsibility.

Retrieve a relevant `PROJECT_PIPELINE.md` section only when the next task creates or changes an identifier, filename, version/build identity, branch/state meaning or validation/artifact-flow convention.

### Retrieval depth B — Subsystem Orientation Pass

Use once when entering a technical subsystem without a sufficiently fresh model of that subsystem in the current Chat.

Typical triggers:

- a new Normal Chat enters ongoing collision, Raise, playback-speed, animation-selection or another substantial subsystem;
- the collaboration deliberately switches subsystem;
- work returns after substantial work elsewhere;
- the User identifies that previously established subsystem context is missing.

The orientation pass is **not** a full review:

```text
identify subsystem
→ use the subject route / indexes below
→ spot-read the small canonical sections/evidence routes needed for broad orientation
→ synthesize a temporary compact mental model
→ continue with question-specific retrieval
```

The temporary model should cover major mechanisms, established facts, important negative findings, known traps, relevant external/reference work and unresolved boundaries closely enough to avoid rediscovery.

Do not create another persistent summary document merely to hold this temporary model. Do not repeat the orientation pass while the same subsystem model remains fresh.

### Retrieval depth C — Active-Problem Reconstruction Pass

Use once before proposing a new fix or architecture for a substantial active problem when the current Chat lacks a sufficiently fresh causal model.

Reconstruct only the targeted problem:

1. observed phenotype;
2. reproduction;
3. normal mechanism;
4. established causal failure;
5. legitimate alternate/interruption paths;
6. physical/gameplay consequences;
7. proven scope;
8. rejected explanations/fixes;
9. unresolved observations/hypotheses;
10. why the current architecture/gate follows.

Use `EVIDENCE_INDEX.md` plus the current subsystem authority. Retrieve exact EV entries and raw/source provenance only as needed.

Do not rerun this pass for every prompt, routine substep, already-frozen Work task, build/deploy continuation or another log inside the same still-fresh problem.

### Retrieval depth D — question-specific retrieval

Use for ordinary ongoing work after current state and any necessary orientation/reconstruction are known.

Retrieve only the exact EV entry, source section, symbol, hook, animation data, artifact, pipeline convention or authority section needed for the current question.

The intended pattern is:

```text
current state
→ subsystem orientation once when needed
→ active-problem reconstruction once when needed
→ exact retrieval for each concrete question
```

---

### HOT — start/resume here

#### `SESSION_ENTRYPOINT.md`

Minimal durable front door for the current branch, accepted boundary and immediate responsibility. Read first for active project work.

#### `BETWEEN_CHATS.md`

Transient latest Chat/Work handoff only. Read only when continuing that exact transition; replace rather than accumulate.

#### `COLLABORATION_RULES.md`

Gothic 3 project-specific collaboration delta: CAM operationalization, User/Normal Chat/Work responsibility allocation, authorization boundaries and project-method evolution. CAM itself is constitutional context, not routine engineering pre-reading.

#### `PROJECT_PIPELINE.md`

Stable project operating grammar: branch/state meanings, gate/test identifiers, EV/POP numbering, raw/derived artifact naming, prototype/build identity, document-versioning convention, validation stages and evidence-artifact flow.

Retrieve the relevant section when a convention is actually involved; do not read it end-to-end after every prompt.

#### `PROJECT_OPERATING_PROCEDURES.md`

Recurring concrete Git/build/deploy/load/test/evidence procedures. Read/spot-read only when entering those local operation sequences.

#### `WORK_IMPLEMENTATION_PROTOCOL.md`

Read only for a bounded implementation/Work task.

---

### WARM — current architecture / subsystem plans

Open only when the responsibility requires the model.

#### `DESIGN.md`

Canonical project architecture for Raise, speed and frame collision, including the current modular behavior-core shape and implementation order.

#### `COLLISION_LIFECYCLE_PLAN.md`

Current collision-lifecycle authority: exact execution/source obligations, temporary pre-Combat ScriptFunction bridge, native-cleanup precedence, controlled C1-R1 terminal repair and generation-scoped marker-identity separation.

#### `COLLISION_LOGGER_PLAN.md`

Current diagnostic architecture: hook ownership, factual event model, compact/deep diagnostic responsibilities and diagnostic/release separation.

#### `COLLISION_TEST_PLAN.md`

Current collision validation posture, closed boundaries and future required validation gates, including the separate `AttackContinuationProtection` investigation boundary.

#### `PROJECT_SCOPE_CONTEXT.md`

Short factual context for authorized local Gothic 3 engine-facing reverse engineering/modding prompts.

---

### COLD — routing indexes

Use these **before** opening the largest reference documents.

#### `EVIDENCE_INDEX.md`

Routes topics, symbols, lifecycle stages, historical questions and future-responsibility cross-routes to exact EV ranges.

Use when asking “is this proven?”, “where did we establish this?”, or “why did an older technical decision exist?”.

#### `ANIMATION_INDEX.md`

Routes filename/UseType/action/phase/pose/R-L/asset/marker-authoring questions to exact sections or animation-name data.

---

### COLD — canonical deep references

Preserve these even when large. Search exact sections/evidence/symbols rather than reading end-to-end by default.

#### Evidence ledgers

```text
EVIDENCE_LEDGER.md                EV-001–EV-157
EVIDENCE_LEDGER_STEP_B.md         EV-158–EV-198
EVIDENCE_LEDGER_199_ONWARD.md     EV-199 onward
```

These are one global monotonic evidence namespace. File splits are retrieval/storage boundaries only.

#### `COLLISION_CLEANUP_CALLSITE_MAP.md`

Tested-build reverse-engineering lookup for native cleanup RVAs, interruption cleanup, script-runner stacks and generic script-processing context.

#### `ANIMATION_RULES.md`

Canonical generalized animation filename/state/UseType/action/phase/pose/authoring semantics.

#### `ANIMATION_CATALOG.md`

Curated exact human-melee assets, family observations, source notes and controlled fixtures.

#### `SOURCE_HOOK_GUIDE.md`

Targeted source/API/symbol/RVA/hook-pattern lookup guide.

#### `ENGINEERING_GUIDE.md`

General engineering principles developed during the project. Useful for architecture/review questions, not routine pre-reading.

---

### COLD — searchable data / provenance

#### Animation-name data

- `data/animation_names/all_animation_names.txt` — complete extracted native name inventory;
- `data/animation_names/author_grouped_attacks_and_stumbles.txt` — author-grouped exact names/notes.

For exact filename existence/variants, search these before opening broad catalog/rules material.

#### Runtime/source evidence

- `research/raw/` — active/unprocessed or intentionally still-comparative canonical raw artifacts;
- `research/archive/` — processed historical runtime/source provenance;
- `research/derived/` — deterministic retrieval/analysis packages whose source artifacts remain canonical.

Prefer an EV entry first. Open raw/archive evidence when verifying wording, challenging an interpretation, or extracting a fact not represented canonically. For oversized logs, use the recurring large-log procedure in `PROJECT_OPERATING_PROCEDURES.md` and read deterministic derived material before broad raw content where appropriate.

Raw→archive migration is a deliberate provenance transaction: preserve bytes and update canonical paths together.

#### Superseded documentation/history

Git history is the documentation archive.

Removed/superseded active documents and earlier wording remain recoverable from commits without maintaining a duplicate `docs/archive/` tree. Historical Git content never overrides current authorities.

`research/archive/` remains separate because runtime/source evidence has persistent provenance value that is not equivalent to ordinary document-version history.

---

## 3. Retrieval by Question

| Question | Start here | Broaden only if needed |
|---|---|---|
| What are we doing now? | `SESSION_ENTRYPOINT.md` | `BETWEEN_CHATS.md` for exact transient continuation |
| What causal model constrains an active collision problem? | current subsystem authority | `EVIDENCE_INDEX.md` reconstruction route → exact EV entries |
| What did the last Chat/Work handoff do? | `BETWEEN_CHATS.md` | exact commit/diff |
| How does CAM govern this project / who should own this responsibility / should this go to Work? | `COLLABORATION_RULES.md` | CAM itself only for a genuine principle-level comparison; `WORK_IMPLEMENTATION_PROTOCOL.md` only if bounded implementation is selected |
| What naming/numbering/version/test/artifact convention should I use? | `PROJECT_PIPELINE.md` relevant section | owning procedure/current plan only for task semantics |
| How do I execute recurring Git/build/deploy/test/evidence work? | `PROJECT_OPERATING_PROCEDURES.md` | `PROJECT_PIPELINE.md` only if a convention itself is relevant |
| How should bounded Work execute? | `WORK_IMPLEMENTATION_PROTOCOL.md` | only task-named source/API/evidence |
| How is project knowledge maintained? | `KNOWLEDGE_MAINTENANCE.md` | `KNOWLEDGE_REGISTRY.md` for exact owner/update trigger |
| Who owns this type of project knowledge? | `KNOWLEDGE_REGISTRY.md` | owning authority named there |
| What is the overall architecture? | `DESIGN.md` | evidence index if a premise must be checked |
| What is the current collision lifecycle model? | `COLLISION_LIFECYCLE_PLAN.md` | cleanup map / EV range |
| What should diagnostics capture? | `COLLISION_LOGGER_PLAN.md` | source + exact EV |
| What is the current collision validation posture? | `SESSION_ENTRYPOINT.md` → `COLLISION_TEST_PLAN.md` | `BETWEEN_CHATS.md` only for an active runtime contract |
| Is an engine claim proven? | `EVIDENCE_INDEX.md` | exact ledger entry → raw/source |
| Where does native cleanup occur? | `COLLISION_CLEANUP_CALLSITE_MAP.md` | relevant EV/raw logs |
| What does this animation token/UseType/action/pose mean? | `ANIMATION_INDEX.md` | exact `ANIMATION_RULES.md` section |
| Does this exact animation exist? | animation-name data | catalog/rules only for interpretation |
| Which family/fixture/source note is relevant? | `ANIMATION_INDEX.md` | `ANIMATION_CATALOG.md` |
| Where/how should I search or hook Gothic 3? | `SOURCE_HOOK_GUIDE.md` | SDK/reference/binary/evidence |
| Why did an older technical decision exist? | `EVIDENCE_INDEX.md` → exact EV/provenance | Git history/raw/archive evidence only if chronology/wording matters |
| What was historical pre-cleanup wording? | Git history | exact historical commit/file |

### Subsystem Orientation Routes

These routes are subject guides, not summaries.

| Subsystem | Orientation route |
|---|---|
| frame collision / collision lifecycle | `DESIGN.md` §§6–10 → collision routes in `EVIDENCE_INDEX.md` → current `COLLISION_LIFECYCLE_PLAN.md`; use `SOURCE_HOOK_GUIDE.md` / `COLLISION_CLEANUP_CALLSITE_MAP.md` only for source/hook/cleanup context and `ANIMATION_INDEX.md` only when source/asset semantics matter |
| Raise | `DESIGN.md` §4 → Raise route in `EVIDENCE_INDEX.md` → `ANIMATION_INDEX.md` for relevant assets/selection; source guide only when implementation/hook details matter |
| playback speed | `DESIGN.md` §5 → speed route in `EVIDENCE_INDEX.md` → speed section in `SOURCE_HOOK_GUIDE.md` when source/reference implementation context matters |
| animation semantics / selection | `ANIMATION_INDEX.md` → exact `ANIMATION_RULES.md` / `ANIMATION_CATALOG.md` / animation-name data routes → relevant evidence only when behavioral interpretation must be recovered |
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

- `SetCollisionGroup` cleanup → cleanup callsite map, not whole research history;
- `QuickAttackL` physical source → animation index + relevant EV/source section;
- `ProcessScript` lifecycle meaning → exact EV + cleanup map section;
- exact native `Wade` animation → animation-name data first;
- old v0.13 occurrence-guard rationale → evidence index → EV/provenance → Git history/raw only if needed;
- next runtime raw filename → `PROJECT_PIPELINE.md`, not old chat history.

Read a full large document only for genuine broad synthesis, contradiction resolution, or another intentional information-architecture pass.

---

## 5. Current Read Orders

### Normal Chat — current continuation

Usually:

1. `SESSION_ENTRYPOINT.md`;
2. `BETWEEN_CHATS.md` only for an active handoff;
3. perform the Subsystem Orientation Pass once if the active subsystem is not sufficiently fresh;
4. perform the targeted Active-Problem Reconstruction Pass once if substantial reasoning requires a stale causal route;
5. retrieve the relevant `PROJECT_PIPELINE.md` section only when the immediate responsibility creates/changes a project convention;
6. retrieve exact current evidence/source supplied by the User or named by the entry point;
7. broaden only when the concrete question requires it.

Within the same continuing subsystem/problem context, do not rerun orientation/reconstruction or reread unchanged authorities/procedures after every prompt.

### Work — bounded implementation

Usually:

1. `SESSION_ENTRYPOINT.md`;
2. relevant frozen task / `BETWEEN_CHATS.md`;
3. `WORK_IMPLEMENTATION_PROTOCOL.md`;
4. assigned source files;
5. task-specific authority/evidence only.

Work preserves already-frozen identifiers, filenames and build labels. It may inspect necessary source/API material when implementation reveals a concrete need, but should not reconstruct the whole project by default.

---

## 6. Authority Boundaries

| Responsibility | Authority |
|---|---|
| current continuation / immediate responsibility | `SESSION_ENTRYPOINT.md` |
| transient cross-context handoff | `BETWEEN_CHATS.md` |
| project-specific CAM operationalization / participant allocation / authorization | `COLLABORATION_RULES.md` |
| stable project naming/numbering/version/test/artifact conventions | `PROJECT_PIPELINE.md` |
| recurring local operational sequences | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded implementation execution | `WORK_IMPLEMENTATION_PROTOCOL.md` |
| knowledge-maintenance process | `KNOWLEDGE_MAINTENANCE.md` |
| knowledge ownership/update triggers | `KNOWLEDGE_REGISTRY.md` |
| documentation map / retrieval depth / subsystem orientation | this `README.md` |
| overall intended system architecture | `DESIGN.md` |
| current collision lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| current diagnostic architecture | `COLLISION_LOGGER_PLAN.md` |
| current/future collision validation boundaries | `COLLISION_TEST_PLAN.md` |
| release/diagnostic product architecture | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` |
| exact evidence status/provenance | three canonical evidence ledgers listed above |
| evidence/history lookup | `EVIDENCE_INDEX.md` → exact EV/provenance → Git history/raw only when needed |
| animation generalized semantics | `ANIMATION_RULES.md` |
| concrete assets/fixtures | `ANIMATION_CATALOG.md` / data files |
| animation lookup | `ANIMATION_INDEX.md` |
| source/API/hook lookup | `SOURCE_HOOK_GUIDE.md` |
| build-specific cleanup reverse engineering | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| actual implementation truth | current branch source + commits |

A historical “current/next” statement never overrides the current authority for that responsibility.

---

## 7. Knowledge Preservation Policy

This repository is intended to accumulate reusable Gothic 3 modding knowledge.

Preserve:

- confirmed and qualified evidence;
- important negative findings;
- raw/archive evidence needed for verification;
- source/API/hook/binary findings;
- animation semantics, inventories and author observations;
- build-specific reverse-engineering results;
- reusable diagnostic/test methods;
- historical rationale that prevents rediscovery;
- historical identifiers/names necessary for provenance even when later conventions evolve.

Optimize retrieval through:

- stable headings;
- topic/index documents;
- evidence IDs;
- stable project conventions;
- exact symbols/action names/RVAs;
- cross-routes instead of duplicated fact copies;
- separation of current architecture from chronology;
- Git history for superseded documentation wording;
- one-time subsystem orientation when broad context must be reconstructed.

> **Not necessary to read now does not mean not necessary to preserve.**

---

## 8. History / Archive Policy

### Documentation

Ordinary document history belongs in Git.

Before deleting a current document as structurally redundant:

1. identify any durable knowledge it uniquely owns;
2. move that durable knowledge into the correct surviving authority if necessary;
3. update active routes first;
4. rely on Git history for the superseded file/wording once no unique active responsibility remains.

Do not maintain duplicate documentation snapshots merely because a document changed.

### Runtime/source evidence

Runtime/source artifacts follow a different provenance model:

```text
research/raw     active/unprocessed or intentionally comparative evidence
research/archive processed durable provenance
research/derived deterministic navigation/analysis material
```

Do not delete or rename historical runtime/source evidence merely because Git also versions it. Preserve provenance and migrate paths deliberately.

---

## 9. Document-Creation Rule

Create a new document only when it has a distinct retrieval/authority responsibility.

Prefer:

- an index when a large knowledge source is hard to navigate;
- a new subject/orientation route when the problem is retrieval rather than missing authority;
- a new section when an existing authority owns the topic;
- an evidence entry for a new proven fact;
- Git history for superseded ordinary documentation.

Avoid one document per experiment, one rule per minor failure, another current-state document that competes with `SESSION_ENTRYPOINT.md`, a project manifest that merely duplicates distributed configuration, or persistent summary/history documents that duplicate canonical authorities and evidence.

The objective is a repository that can be **deep without making every task carry that depth in active context**.

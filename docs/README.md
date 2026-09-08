# Gothic 3 Animation Behaviors — Project Charter and Knowledge Map

**Purpose:** Highest project-specific authority beneath CAM for the Gothic 3 project's **purpose, long-term direction, scope, authority topology, and retrieval model**. Route Chat, Work, contributors, and Gothic 3 modders to the **smallest useful authoritative material** while preserving deep technical knowledge for targeted recovery.  
**Updated:** 2026-09-08

> **Understand the project authority structure before judging lower-level documents. For ordinary engineering, do not load every document by default: find the current responsibility, recover a compact model of the relevant subsystem when needed, open the smallest relevant authority/index, and broaden only when the question requires it.**

---

## 0. Project Charter — Highest Gothic-Specific Authority

### Authority position

CAM is the constitutional collaboration layer above this project. This file is the **highest project-specific authority immediately beneath CAM** for why this repository exists, what it is trying to achieve over the long term, what belongs inside the project, and how the project's specialist authorities relate to one another.

```text
CAM constitutional collaboration philosophy
        ↓
this Gothic project charter (`docs/README.md`)
        ↓
specialist Gothic authorities within their delegated domains
        ↓
recurring procedures / bounded implementation protocols
        ↓
current-state / exact task execution
```

Specialist authorities remain primary inside their assigned domains. The charter defines the purpose and authority topology those lower authorities operationalize.

A lower authority may specialize or constrain a higher one for its own domain, but it must not silently redefine project purpose, long-term direction, scope, or the CAM relationship. Material change at those levels is surfaced explicitly and made deliberately with the User.

CAM itself is not modified from Gothic 3 project work. Possible CAM evolution belongs to a separate User-authorized CAM responsibility; adopted CAM changes are then deliberately operationalized back into this project.

### Why this project exists

The project exists to turn Gothic 3 animation-behavior research into **robust, reusable, configurable systems** rather than a collection of one-off patches.

Durable aims:

- improve animation behavior where Gothic 3's fixed/native behavior blocks intended animation design;
- prefer animation-authored and native-semantic control where those are strongest facts;
- preserve native fallback and compatibility for unconfigured, unmarked, or unsupported cases;
- build systems generally for supported actors/animations rather than Hero-only by accident;
- separate production behavior from research diagnostics;
- preserve reusable Gothic 3 engine, animation, source/API, testing and compatibility knowledge so future work does not rediscover established facts.

Research prototypes, evidence logs, reverse engineering and diagnostic tools are means to that end, not the final product by themselves.

### Deliberate scope and native-constraint guide

The project does not aim to erase every meaningful difference between Gothic 3 attack/action types merely to maximize arbitrary authoring freedom. Native actions may carry useful targeting, reaction, source, state, effect or other gameplay semantics beyond motion content.

When a native constraint is discovered:

```text
constraint observed
→ would removing it materially improve the intended mod/framework?
→ can it likely be changed narrowly without replacing meaningful native semantics or creating disproportionate complexity?
→ is the question valuable or interesting enough to justify a bounded research detour even if no product change follows?
```

Preserving/documenting a native constraint is valid when removal brings little benefit or disproportionate risk. Curiosity-driven investigation is also valid when deliberately bounded. The User may deliberately expand scope when benefit, learning or curiosity justifies it.

### Long-term goal

The engineering destination is a maintainable Gothic 3 behavior system centered on a diagnostics-free production DLL:

```text
Script_G3AnimationBehaviors.dll
```

It should host selectively enabled, compatible modules such as animation-authored frame collision, Raise control, playback-speed control, and future animation/gameplay behavior modules when deliberately adopted.

Research instrumentation remains available separately through diagnostic twins/tools. Final public behavior must not depend on diagnostic state, research logs, or diagnostic-only hooks.

The durable knowledge base is part of the long-term result: future Chat/Work contexts should recover established Gothic 3 facts through a small retrieval surface instead of carrying the whole project history in active context.

### Specialist authority topology

The main specialist authorities sit beneath this charter but are not one total order:

```text
collaboration / CAM operationalization
→ COLLABORATION_RULES.md

technical architecture / subsystem meaning
→ DESIGN.md + subsystem/release authorities

stable conventions / authority ownership
→ PROJECT_PIPELINE.md + KNOWLEDGE_REGISTRY.md

recurring operations / bounded execution
→ PROJECT_OPERATING_PROCEDURES.md + WORK_IMPLEMENTATION_PROTOCOL.md

knowledge/evidence maintenance and proof
→ KNOWLEDGE_MAINTENANCE.md + evidence authorities/indexes

current responsibility / transient execution state
→ SESSION_ENTRYPOINT.md + BETWEEN_CHATS.md when needed
```

File size, age, detail, recency or proximity to implementation does not define authority outside the delegated responsibility.

When authorities appear to conflict:

```text
identify each responsibility
→ compare lower statement with charter + owning specialist authority
→ preserve factual evidence separately from normative/project-direction decisions
→ change the lowest correct owner
→ escalate genuine purpose/direction/topology conflict to User
→ never silently resolve a CAM-level conflict from Gothic work
```

### Mandatory review/audit principle

Formal project review/audit must first recover this hierarchy and the intended use of the material. `PROJECT_OPERATING_PROCEDURES.md` POP-10 owns the reusable preflight.

> **If the reviewer cannot explain the governing hierarchy and the intended responsibility of the documents/systems being reviewed, the review has not started yet.**

An interrupted-Chat recovery is not automatically a formal audit. POP-11 first runs a bounded authority-oriented recovery; if that recovery exposes broad cross-authority drift or unclear ownership, POP-10 must be invoked before broader review edits begin.

---

## 1. Branch Model

### Active development / research

`docs/collision-source-evidence`

Contains newest active research, implementation and continuation state.

### Stable integration / reusable knowledge

`main`

`main` is the stable integration and reusable Gothic 3 knowledge baseline. Promotion remains deliberate rather than automatic.

### Relationship to CAM

CAM is higher-order collaboration philosophy; Gothic 3 is project-specific operationalization, not a file-for-file CAM copy.

```text
CAM principles / philosophy
→ this project charter
→ specialist Gothic authorities
→ ordinary work reads the lowest relevant Gothic owner
```

Constitutional authority does not mean every engineering task rereads CAM. Retrieve CAM itself when collaboration structure, principle-level consistency, or a separate upward-review question genuinely requires it.

A newer CAM revision does not silently rewrite Gothic authorities. CAM evolution and project adoption are separate deliberate steps.

The project predates CAM's newer `PROJECT_MANIFEST.md` template. Its manifest responsibilities are already distributed across established authorities; do not create a parallel manifest merely to duplicate them.

---

## 2. Retrieval Model — Hot / Warm / Cold

The repository is external project memory, **not a reading list**.

### Retrieval depth A — ordinary current-state retrieval

Use when the question is “where are we now?”

Normally:

- read `SESSION_ENTRYPOINT.md`;
- read `BETWEEN_CHATS.md` only when an active transient handoff matters;
- retrieve a `PROJECT_PIPELINE.md` section only when the immediate task creates/changes a project convention.

### Retrieval depth A-R — interrupted-context recovery

Use when the previous Chat stopped abruptly, maxed context, became unusable, or failed before maintenance/handoff completed.

`SESSION_ENTRYPOINT.md` and `BETWEEN_CHATS.md` are then **clues, not unquestioned truth** until reconciled.

Follow POP-11:

```text
Recovery Lock
→ authority orientation: charter + ownership + maintenance + relevant specialist owner
→ compact recovery preflight
→ reconstruct only recent durable tail
→ close missed POP-06 evidence
→ perform missed smallest-owner maintenance
→ repair current-state pointers
→ contradiction gate: invoke POP-10 only if broad cross-authority drift/unclear ownership appears
→ verify fresh-Chat start state
→ release Recovery Lock
```

Do not start new implementation, new runtime research or a new Work task while Recovery Lock is active.

### Retrieval depth B — Subsystem Orientation Pass

Use once when entering a substantial subsystem without a sufficiently fresh model.

```text
identify subsystem
→ use subject route/indexes below
→ spot-read smallest canonical sections/evidence routes needed for orientation
→ synthesize temporary compact mental model
→ continue with question-specific retrieval
```

This is not a full review and should not create another persistent summary document.

### Retrieval depth C — Active-Problem Reconstruction Pass

Use once before proposing a new fix/architecture for a substantial active problem when causal context is stale.

Reconstruct only:

1. observed phenotype;
2. reproduction;
3. normal mechanism;
4. established causal failure;
5. legitimate alternate/interruption paths;
6. physical/gameplay consequences;
7. proven scope;
8. rejected explanations/fixes;
9. unresolved observations/hypotheses;
10. why current architecture/gate follows.

Use `EVIDENCE_INDEX.md` plus current subsystem authority; exact EV/raw/source only as needed.

### Retrieval depth D — question-specific retrieval

After state/orientation/reconstruction are known, retrieve only the exact EV, source section, symbol, hook, animation data, artifact, convention or authority needed for the current question.

---

### HOT — start/resume here

- `SESSION_ENTRYPOINT.md` — minimal durable current front door.
- `BETWEEN_CHATS.md` — transient latest Chat/Work handoff only.
- `COLLABORATION_RULES.md` — Gothic CAM operationalization and participant allocation.
- `PROJECT_PIPELINE.md` — stable branch/state, numbering, test/artifact/product conventions.
- `PROJECT_OPERATING_PROCEDURES.md` — recurring operations, POP-10 formal review preflight, POP-11 continuity/recovery.
- `WORK_IMPLEMENTATION_PROTOCOL.md` — bounded implementation only.

### WARM — current architecture / subsystem plans

- `DESIGN.md` — overall intended architecture and implementation order.
- `COLLISION_LIFECYCLE_PLAN.md` — collision lifecycle/cleanup authority.
- `COLLISION_LOGGER_PLAN.md` — diagnostic architecture.
- `COLLISION_TEST_PLAN.md` — validation posture and remaining collision gates.
- `PROJECT_SCOPE_CONTEXT.md` — short factual engine-facing scope context.

### COLD — routing indexes

- `EVIDENCE_INDEX.md` — routes proven claims/historical/future-responsibility questions to exact EV ranges.
- `ANIMATION_INDEX.md` — routes animation semantics/assets/authoring questions.

### COLD — canonical deep references

Evidence ledgers share one global monotonic namespace:

```text
EVIDENCE_LEDGER.md                EV-001–EV-157
EVIDENCE_LEDGER_STEP_B.md         EV-158–EV-198
EVIDENCE_LEDGER_199_ONWARD.md     EV-199–EV-231
EVIDENCE_LEDGER_232_ONWARD.md     EV-232 onward
```

File splits are retrieval/storage boundaries only.

Other deep references:

- `COLLISION_CLEANUP_CALLSITE_MAP.md` — tested cleanup RVAs/stacks.
- `ANIMATION_RULES.md` — generalized animation/state/UseType/authoring semantics.
- `ANIMATION_CATALOG.md` — concrete families/assets/fixtures.
- `SOURCE_HOOK_GUIDE.md` — targeted source/API/symbol/RVA/hook lookup.
- `ENGINEERING_GUIDE.md` — project-wide engineering principles.

### COLD — searchable data / provenance

- `data/animation_names/all_animation_names.txt` — complete extracted native names.
- `data/animation_names/author_grouped_attacks_and_stumbles.txt` — author-grouped exact names/notes.
- `research/raw/` — active/unprocessed or intentionally comparative canonical artifacts.
- `research/archive/` — processed durable provenance.
- `research/derived/` — deterministic retrieval/analysis aids whose source remains canonical.
- `research/README.md` — research-layer usage/processing map.
- `EVIDENCE_PATH_MIGRATIONS.md` — deliberate raw/archive path-migration lookup when historical paths differ from current storage.

Prefer EV first. Open raw/archive when verifying wording, challenging interpretation, or extracting a fact not represented canonically. For oversized logs, use POP-07.

Ordinary documentation history belongs in Git; historical Git content never overrides maintained current authorities.

---

## 3. Retrieval by Question

| Question | Start here | Broaden only if needed |
|---|---|---|
| Why does project exist / what is authority hierarchy? | this `README.md` §0 | owning specialist authority after charter role is clear |
| What are we doing now? | `SESSION_ENTRYPOINT.md` | `BETWEEN_CHATS.md` for exact transient continuation |
| Previous Chat died before handoff; what now? | `PROJECT_OPERATING_PROCEDURES.md` POP-11 | this charter §0 + `KNOWLEDGE_REGISTRY.md` + `KNOWLEDGE_MAINTENANCE.md` + recent durable tail; POP-10 only if contradiction gate fires |
| How must formal review/audit begin? | POP-10 | this charter + target Purpose/Scope + Registry ownership |
| What causal model constrains active collision problem? | current subsystem authority | `EVIDENCE_INDEX.md` reconstruction route → exact EV |
| What did last Chat/Work handoff do? | `BETWEEN_CHATS.md` | exact commit/diff |
| How does CAM govern project / who owns responsibility? | charter → `COLLABORATION_RULES.md` | CAM itself only for genuine principle-level comparison |
| What naming/numbering/test/artifact convention? | `PROJECT_PIPELINE.md` | owning procedure/current plan only for task semantics |
| How execute recurring Git/build/deploy/test/evidence work? | POPs | pipeline only when convention itself matters |
| How should bounded Work execute? | `WORK_IMPLEMENTATION_PROTOCOL.md` | only task-named source/API/evidence |
| How is knowledge maintained? | `KNOWLEDGE_MAINTENANCE.md` | Registry for exact owner/update trigger |
| Who owns this knowledge? | `KNOWLEDGE_REGISTRY.md` | owning authority named there |
| Overall architecture? | `DESIGN.md` | evidence index if premise must be checked |
| Current collision lifecycle? | `COLLISION_LIFECYCLE_PLAN.md` | cleanup map / EV |
| Diagnostics? | `COLLISION_LOGGER_PLAN.md` | source + exact EV |
| Collision validation posture? | `SESSION_ENTRYPOINT.md` → `COLLISION_TEST_PLAN.md` | transient handoff only when active |
| Is engine claim proven? | `EVIDENCE_INDEX.md` | exact ledger → raw/source |
| Where did an archived evidence file move? | `EVIDENCE_PATH_MIGRATIONS.md` | exact historical EV/commit when needed |
| Native cleanup callsite? | `COLLISION_CLEANUP_CALLSITE_MAP.md` | relevant EV/raw |
| Animation token/UseType/action/pose? | `ANIMATION_INDEX.md` | exact Rules section |
| Exact animation exists? | animation-name data | catalog/rules for interpretation |
| Family/fixture/source note? | `ANIMATION_INDEX.md` | Catalog |
| Gothic source/API/hook? | `SOURCE_HOOK_GUIDE.md` | SDK/reference/binary/evidence |
| Why older technical decision existed? | `EVIDENCE_INDEX.md` → exact EV/provenance | Git history/raw/archive only if chronology/wording matters |

### Subsystem Orientation Routes

| Subsystem | Orientation route |
|---|---|
| frame collision / lifecycle | `DESIGN.md` collision sections → collision routes in `EVIDENCE_INDEX.md` → `COLLISION_LIFECYCLE_PLAN.md`; Source Guide/Cleanup Map only for source/hook/cleanup context |
| Raise | `DESIGN.md` Raise section → Raise route in `EVIDENCE_INDEX.md` → `ANIMATION_INDEX.md` for asset/selection questions |
| playback speed | `DESIGN.md` speed section → speed evidence route → Source Guide when implementation/hook context matters |
| animation semantics / selection | `ANIMATION_INDEX.md` → exact Rules/Catalog/data → relevant evidence only when behavioral interpretation matters |
| source/API/hook investigation | `SOURCE_HOOK_GUIDE.md` → exact evidence/callsite authority named there → SDK/reference source for concrete symbol/API question |

Prefer adding a route to an existing owner/index over creating another independently maintained subsystem-summary document.

---

## 4. Spot-Search Pattern

```text
current question
→ choose authority/index from this map
→ search exact concept / symbol / action / EV ID / heading
→ read local section with enough context
→ follow provenance only if verification is necessary
```

Read a full large document only for genuine broad synthesis, contradiction resolution, or intentional information-architecture review.

---

## 5. Current Read Orders

### Normal Chat — ordinary continuation

1. `SESSION_ENTRYPOINT.md`;
2. `BETWEEN_CHATS.md` only for active handoff;
3. Subsystem Orientation Pass once if subsystem model is stale;
4. targeted Active-Problem Reconstruction once if causal model is stale;
5. pipeline section only when immediate task creates/changes a convention;
6. exact current evidence/source named by responsibility;
7. broaden only when concrete question requires it.

### Normal Chat — failed previous context

POP-11 overrides ordinary continuation until Recovery Lock ends:

1. read entry point as clue, not unquestioned NEXT;
2. orient to charter/ownership/maintenance/relevant specialist owner;
3. state recovery preflight;
4. reconstruct only recent durable gap;
5. close missed evidence/maintenance/current-state work;
6. invoke POP-10 only if contradiction gate reveals broad authority/structure issue;
7. verify fresh-Chat start state;
8. resume ordinary continuation.

### Formal review/audit

Before evaluating targets, apply POP-10 and recover charter hierarchy plus target owners/intended use. A failed-Chat recovery does not become a formal audit unless POP-11's contradiction gate fires.

### Work — bounded implementation

1. `SESSION_ENTRYPOINT.md`;
2. relevant frozen task / `BETWEEN_CHATS.md`;
3. `WORK_IMPLEMENTATION_PROTOCOL.md`;
4. assigned source;
5. task-specific authority/evidence only.

Work should not reconstruct the whole project by default.

---

## 6. Authority Boundaries

| Responsibility | Authority |
|---|---|
| project purpose / long-term direction / scope / authority topology / retrieval model | this charter |
| current continuation / immediate responsibility | `SESSION_ENTRYPOINT.md` |
| transient cross-context handoff | `BETWEEN_CHATS.md` |
| project-specific CAM operationalization / participant allocation | `COLLABORATION_RULES.md` |
| stable branch/state/numbering/version/test/artifact conventions | `PROJECT_PIPELINE.md` |
| recurring operations + formal review preflight + interrupted-context recovery | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded implementation execution | `WORK_IMPLEMENTATION_PROTOCOL.md` |
| knowledge-maintenance process | `KNOWLEDGE_MAINTENANCE.md` |
| knowledge ownership/update triggers | `KNOWLEDGE_REGISTRY.md` |
| overall intended system architecture | `DESIGN.md` |
| collision lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| diagnostic architecture | `COLLISION_LOGGER_PLAN.md` |
| collision validation boundaries | `COLLISION_TEST_PLAN.md` |
| release/diagnostic product architecture | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` |
| exact evidence status/provenance | four canonical evidence ledgers listed above |
| evidence/history lookup | `EVIDENCE_INDEX.md` |
| evidence storage migration lookup | `EVIDENCE_PATH_MIGRATIONS.md` |
| animation generalized semantics | `ANIMATION_RULES.md` |
| concrete assets/fixtures | `ANIMATION_CATALOG.md` / data files |
| animation lookup | `ANIMATION_INDEX.md` |
| source/API/hook lookup | `SOURCE_HOOK_GUIDE.md` |
| build-specific cleanup reverse engineering | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| actual implementation truth | current branch source + commits |

A historical “current/next” statement never overrides the maintained authority for that responsibility.

---

## 7. Knowledge Preservation Policy

Preserve confirmed/qualified evidence, important negative findings, raw/archive provenance, source/API/hook/binary facts, animation semantics/inventories/author observations, build-specific reverse engineering, reusable diagnostic/test methods, and historical rationale that prevents rediscovery.

Optimize retrieval through stable headings, indexes, evidence IDs, exact symbols/action names/RVAs, cross-routes instead of duplicated narratives, current-vs-history separation, Git history for superseded documentation, and one-time subsystem orientation when needed.

> **Not necessary to read now does not mean not necessary to preserve.**

---

## 8. History / Archive Policy

### Documentation

Ordinary document history belongs in Git. Before deleting a current document as redundant, identify unique durable knowledge, move it to the correct surviving owner if necessary, update routes, then rely on Git history.

### Runtime/source evidence

```text
research/raw      active/unprocessed or intentionally comparative evidence
research/archive  processed durable provenance
research/derived  deterministic navigation/analysis material
```

Do not delete or casually rename runtime/source evidence because Git versions it. Preserve provenance and migrate paths deliberately; use `EVIDENCE_PATH_MIGRATIONS.md` when historical paths differ from current storage.

---

## 9. Document-Creation Rule

Create a new document only when it has a distinct retrieval/authority responsibility.

Prefer an index when a large source is hard to navigate, a route when retrieval is the problem, a section when an existing authority owns the topic, an EV for a proven fact, and Git history for superseded ordinary documentation.

Avoid one document per experiment, another current-state document competing with `SESSION_ENTRYPOINT.md`, or persistent summary/history files duplicating canonical authorities/evidence.

The objective is a repository that can be **deep without making every task carry that depth in active context**.

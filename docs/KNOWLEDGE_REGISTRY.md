# Gothic 3 Knowledge Authority Registry

**Status:** Active authority/update-trigger registry  
**Updated:** 2026-09-08

## Purpose

Define **where project knowledge/responsibility belongs** and what kinds of events should update each authority.

Use this registry during maintenance in `KNOWLEDGE_MAINTENANCE.md`, during formal review/audit preflight in POP-10, and during POP-11 interrupted-context recovery when a fresh Chat must re-establish which owner may legitimately be changed.

This file owns authority/update routing. It does not repeat the project charter, maintenance procedure, recovery procedure, or review procedure itself.

> **One responsibility should have one primary authority. Other documents route to it.**

`README.md` is the project charter and highest project-specific authority beneath CAM for purpose, long-term direction, scope, authority topology and retrieval model. This registry maps specialist responsibilities beneath that charter.

---

## 1. Authority Registry

| Knowledge / project responsibility | Primary authority | Update when | Usually do NOT update when |
|---|---|---|---|
| project purpose / long-term direction / scope / authority topology / retrieval model / subsystem-orientation routes | `README.md` project charter | User-authorized purpose/direction/scope/topology change, or durable retrieval-model/current-context reconstruction structure materially changes | technical/evidence content changes inside already-valid specialist owner; routine current-state movement |
| current active subsystem / causal gate / immediate next responsibility | `SESSION_ENTRYPOINT.md` | active gate/subsystem/immediate candidate/next responsibility changes, including material temporary prerequisite/safety/contradiction/recovery route | routine continuation inside same route |
| transient Chat ↔ Work / context handoff | `BETWEEN_CHATS.md` | another context needs exact short-lived continuation detail not already durable | ordinary project facts already live in durable authorities |
| project-specific collaboration behavior / participant-tool allocation / Gothic↔CAM operationalization | `COLLABORATION_RULES.md` | recurring Gothic-specific collaboration lesson changes participant allocation, authorization/interaction behavior, or project-local CAM operationalization | technical result with no collaboration consequence; project purpose/topology change belonging in charter |
| stable operating conventions: branch/state meanings, gate/test IDs, evidence/procedure IDs, raw/derived naming, build identity, document versioning, validation/artifact flow | `PROJECT_PIPELINE.md` | accepted convention changes or a new convention responsibility/transition is defined | routine use of established convention |
| recurring project-local operations: Git handoff/sync, build/deploy/load, runtime-artifact intake/publish/closure, large-log/static retrieval, formal review preflight, Normal Chat continuity/recovery | `PROJECT_OPERATING_PROCEDURES.md` | repeated friction/mistake, one serious failure, clearly better recurring method, new recurring operation, or owned sequence changes | one-off command variation; review finding whose owner is another authority |
| workstation-specific repository/build/runtime paths | `LOCAL_WORKSTATION_PATHS.md` | actual local path changes or another workstation path becomes operationally necessary | portable procedure semantics or branch/build conventions |
| bounded Work execution contract | `WORK_IMPLEMENTATION_PROTOCOL.md` | Work authority/preflight/publication/stop/review/bounded-execution model changes | participant allocation without Work-execution change; unrelated technical result |
| knowledge maintenance / future-relevance / knowledge-health process | `KNOWLEDGE_MAINTENANCE.md` | maintenance transaction/event model, future-use routing, workaround reevaluation, audit-health/bloat process changes | ordinary technical result handled by existing process |
| authority/update routing | `KNOWLEDGE_REGISTRY.md` | responsibility gains/moves/loses owner or update-trigger logic changes | underlying knowledge grows inside existing authority |
| overall intended Raise/speed/frame-collision architecture | `DESIGN.md` | system responsibility/public behavior/major invariant/subsystem boundary/config model changes | experiment chronology, routine confirmation, build status |
| release/diagnostic product separation | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` | release-vs-diagnostic responsibility, compilation separation, coexistence/load rule, final extraction model changes | diagnostic result confirms existing model |
| collision execution/cleanup lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` | ownership/lifetime/cleanup invariant or causal architecture changes | test confirms model without changing it |
| collision diagnostic architecture | `COLLISION_LOGGER_PLAN.md` | hook ownership, diagnostic event model, CORE/deep boundary, or active probe responsibility changes | log adds evidence without changing diagnostic design |
| current/future collision validation boundaries | `COLLISION_TEST_PLAN.md` | gate, acceptance criteria, control matrix, interpretation rule, or future required validation boundary changes | historical completed-test detail preserved by evidence |
| exact evidence status/provenance | `EVIDENCE_LEDGER.md` + `EVIDENCE_LEDGER_STEP_B.md` + `EVIDENCE_LEDGER_199_ONWARD.md` + `EVIDENCE_LEDGER_232_ONWARD.md` | controlled/source fact established, qualified, contradicted, or materially reinterpreted | pure design preference without factual claim |
| evidence topic / future-responsibility routing | `EVIDENCE_INDEX.md` | new evidence domain/range/search route is useful, existing route materially changes, or proven knowledge becomes materially relevant to another future responsibility | every new EV already covered by existing route |
| deliberate canonical evidence storage-path migration lookup | `EVIDENCE_PATH_MIGRATIONS.md` | processed canonical evidence moves between repository storage layers and historical/current paths would otherwise be ambiguous | every evidence result; ordinary archive entry whose historical route remains unambiguous |
| generalized animation semantics / authoring rules | `ANIMATION_RULES.md` | generalized filename/UseType/action/phase/pose/authoring semantic changes | one concrete asset/test that does not generalize |
| concrete animation families/assets/fixtures | `ANIMATION_CATALOG.md` | reusable concrete family/asset/source annotation/fixture knowledge changes | runtime architecture result with no asset-level consequence |
| animation question routing | `ANIMATION_INDEX.md` | new animation category or materially changed route | ordinary catalog detail reachable by current routes |
| complete native animation filename existence | `data/animation_names/all_animation_names.txt` | authoritative inventory regenerated/replaced | interpretation of existing filenames |
| author-grouped exact animation names/notes | `data/animation_names/author_grouped_attacks_and_stumbles.txt` | authoritative grouped source changes | generalized interpretation derived from source |
| source/API/symbol/hook practical lookup | `SOURCE_HOOK_GUIDE.md` | reusable symbol/API/hook/address/search route established/revised | experiment chronology/one-off detail |
| native collision cleanup callsites/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` | tested cleanup RVA/stack/symbol/caller interpretation changes | higher-level lifecycle design with no callsite fact change |
| project-wide engineering principles | `ENGINEERING_GUIDE.md` | durable technical principle generalizes beyond one subsystem while consistent with charter | local workaround/test detail; project-purpose change |
| technical scope/context for engine-facing prompts | `PROJECT_SCOPE_CONTEXT.md` | factual engine-facing authorization/scope-context wording changes | ordinary technical evidence; charter-purpose change |
| research-layer intake/processing usage map | `research/README.md` | research storage workflow, processing/retrieval routing, or directory-layer meaning changes | every new archived log; evidence result already owned by EV/index |
| research chronology / why an older technical decision existed | `EVIDENCE_INDEX.md` → exact EV/provenance; Git history when exact historical wording/sequence is needed | evidence interpretation/retrieval route changes | ordinary chronology growth; do not maintain parallel milestone history |
| active/unprocessed runtime/source artifact | `research/raw/` | new artifact remains active input to interpretation/comparison | artifact canonically processed |
| processed runtime/source provenance | `research/archive/` | unchanged source artifact retains verification value after processing | active unresolved artifact; derived analysis |
| deterministic retrieval/analysis aid | `research/derived/` | canonical raw/archive artifact needs reproducible retrieval package/extract | source artifact itself; hand-written substitute for canonical evidence |
| superseded ordinary documentation wording/history | Git history | older wording/removed file must be recovered for historical reasoning | ordinary active retrieval; Git history is not competing current authority |

Canonical evidence remains one global monotonic namespace:

```text
EVIDENCE_LEDGER.md                EV-001–EV-157
EVIDENCE_LEDGER_STEP_B.md         EV-158–EV-198
EVIDENCE_LEDGER_199_ONWARD.md     EV-199–EV-231
EVIDENCE_LEDGER_232_ONWARD.md     EV-232 onward
```

---

## 2. Authority and Knowledge Direction

Normative/operational direction:

```text
CAM constitutional collaboration layer
        ↓
README.md project charter
        ↓
specialist Gothic authorities within delegated domains
        ↓
recurring procedures / bounded protocols
        ↓
current task execution
```

Specialist authorities may be parallel. Ownership is determined by responsibility, not file size, age, detail or recency.

Factual knowledge direction is mostly:

```text
raw/source observation
        ↓
canonical evidence
        ↓
canonical topic authority (only if meaning changes)
        ↓
index route (only if retrieval changes)
        ↓
current-state pointer (only if active responsibility changes)
```

Evidence may justify changes to normative/technical authority, but does not silently rewrite charter, architecture or procedure.

Stable operating conventions, workstation paths, participant allocation and implementation procedure are orthogonal specialist responsibilities; do not create sideways dependency chains where every authority repeats every other authority.

---

## 3. Interrupted-Context Ownership Rule

POP-11 owns the recovery sequence. The Registry determines which owners that recovery may change.

A recovering Chat must not infer ownership from whichever file appears newest or most detailed. Before documentation repair it should re-establish:

```text
README charter hierarchy
→ this Registry's owner/update route
→ KNOWLEDGE_MAINTENANCE transaction rule
→ relevant specialist owner
→ recent durable facts
```

If the durability gap is local, update only owners whose triggers actually fired.

If ownership itself is unclear or recovery discovers broad cross-authority contradiction, ordinary recovery stops and POP-10 formal review preflight becomes mandatory before broader edits.

---

## 4. Cross-Responsibility Routing Rule

When proven knowledge becomes materially relevant to another future responsibility:

```text
keep fact in one owning authority/evidence record
→ add smallest useful cross-route from future responsibility
→ preserve original regression/invariant route if new knowledge may replace a workaround
```

Do not copy the narrative into several subsystem documents. Vague “might be useful someday” relationships do not justify cross-routes.

---

## 5. Registry Maintenance / New-Authority Rule

A noticed gap/refinement/future dependency is not automatically a reason for another document.

Default order:

```text
noticed gap
→ does charter already define domain?
→ can existing specialist owner absorb it?
→ can existing section be strengthened?
→ can existing index/route solve retrieval?
→ can existing procedure be refined?
→ only then consider a genuinely new responsibility
```

Create a new authority only when placing the responsibility in an existing owner would blur ownership, distort purpose, or materially worsen retrieval.

A full registry review is appropriate only when the knowledge schema itself changes, repeated maintenance reveals unclear ownership, or a health check shows material retrieval/document burden. Such a formal review must apply POP-10 before judging structure.

The event-by-event maintenance procedure belongs in `KNOWLEDGE_MAINTENANCE.md`, not here.

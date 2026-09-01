# Gothic 3 Knowledge Authority Registry

**Status:** Active authority/update-trigger registry  
**Updated:** 2026-09-01

## Purpose

Define **where project knowledge/responsibility belongs** and what kinds of events should update each authority.

Use this registry during the maintenance transaction in `KNOWLEDGE_MAINTENANCE.md`.

This file owns authority/update routing. It does not repeat the maintenance procedure itself.

> **One responsibility should have one primary authority. Other documents route to it.**

---

## 1. Authority Registry

| Knowledge / project responsibility | Primary authority | Update when | Usually do NOT update when |
|---|---|---|---|
| current active subsystem / causal gate / immediate next responsibility | `SESSION_ENTRYPOINT.md` | active gate/subsystem/immediate candidate/next responsibility changes, including a material temporary prerequisite or safety/contradiction route | routine continuation or another confirmation inside the same route |
| transient Chat ↔ Work / context handoff | `BETWEEN_CHATS.md` | another context needs exact short-lived implementation/test/continuation detail not already represented durably | ordinary project facts already live in durable authorities |
| project-specific collaboration behavior / participant-tool allocation / Gothic↔CAM authority boundary | `COLLABORATION_RULES.md` | a recurring Gothic-specific collaboration lesson materially changes participant allocation, authorization/interaction behavior, or the project-local/CAM boundary | one isolated annoyance already covered elsewhere; technical result with no collaboration consequence |
| documentation map / retrieval depth / subsystem-orientation routes | `README.md` | document roles, Hot/Warm/Cold retrieval model, subject routes, or fresh-context retrieval structure materially changes | underlying technical/evidence content changes without affecting routing |
| stable operating conventions: branch/state meanings, gate/test IDs, evidence/procedure IDs, raw/derived naming, build identity, document versioning, validation/artifact flow | `PROJECT_PIPELINE.md` | an accepted convention changes or a new convention responsibility/transition must be defined | routine use of an established convention |
| recurring project-local operations: Git handoff/sync, build/deploy/load verification, runtime-artifact intake/publish, large-log reduction, static-reference retrieval | `PROJECT_OPERATING_PROCEDURES.md` | repeated friction/mistakes, one serious failure, a clearly better recurring method, or a genuinely new recurring operation changes the best procedure | every routine use or one-off command variation |
| bounded Work execution contract | `WORK_IMPLEMENTATION_PROTOCOL.md` | Work implementation authority, preflight, publication, stop conditions, review responsibility, or bounded-task execution model changes | participant allocation changes without changing Work execution itself; technical Gothic finding unrelated to Work behavior |
| knowledge maintenance / future-relevance / knowledge-health process | `KNOWLEDGE_MAINTENANCE.md` | maintenance transaction/event model, future-use routing rule, workaround-reevaluation rule, audit-health criteria, or bloat early-warning process changes | ordinary technical evidence/result handled by the existing process |
| authority/update routing | `KNOWLEDGE_REGISTRY.md` | a responsibility gains/moves/loses an owner or its update-trigger logic changes | underlying knowledge grows inside an existing authority |
| overall intended Raise/speed/frame-collision architecture | `DESIGN.md` | system responsibility, public behavior, major invariant, subsystem boundary, configuration model changes | experiment chronology, routine confirmations, build status |
| release/diagnostic product separation and release-purity architecture | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` | release-vs-diagnostic product responsibility, compilation separation, coexistence/load rule, or final release extraction model changes | a diagnostic test result confirms the existing product model |
| current collision execution/cleanup lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` | ownership/lifetime/cleanup invariant or causal architecture changes | a test confirms the existing lifecycle model without changing it |
| current collision diagnostic architecture | `COLLISION_LOGGER_PLAN.md` | hook ownership, diagnostic event model, CORE/deep boundary, or active probe responsibility changes | a log adds evidence without changing diagnostic design |
| current/future staged collision validation boundaries | `COLLISION_TEST_PLAN.md` | current gate, acceptance criteria, control matrix, interpretation rule, or future required validation boundary changes | historical completed-test detail already preserved by evidence |
| exact evidence status/provenance | `EVIDENCE_LEDGER.md` + `EVIDENCE_LEDGER_STEP_B.md` + `EVIDENCE_LEDGER_199_ONWARD.md` | a controlled/source fact is established, qualified, contradicted, or materially reinterpreted | pure design preference without factual claim |
| evidence topic / future-responsibility routing | `EVIDENCE_INDEX.md` | a new evidence domain/range/search route is useful, an existing route materially changes, or proven knowledge becomes materially relevant to a different future responsibility | every new EV already covered by an existing route |
| generalized animation semantics / authoring rules | `ANIMATION_RULES.md` | a generalized filename/UseType/action/phase/pose/authoring semantic changes | one concrete asset/test that does not generalize the rule |
| concrete animation families/assets/fixtures | `ANIMATION_CATALOG.md` | a concrete family/asset/source annotation/fixture materially changes reusable asset knowledge | runtime architecture result with no asset-level consequence |
| animation question routing | `ANIMATION_INDEX.md` | a new animation knowledge category appears or an existing route materially changes | ordinary new catalog detail already reachable by current routes |
| complete native animation filename existence | `data/animation_names/all_animation_names.txt` | authoritative extracted inventory is regenerated/replaced | interpretation of existing filenames |
| author-grouped exact animation names/notes | `data/animation_names/author_grouped_attacks_and_stumbles.txt` | authoritative grouped source changes | generalized interpretation derived from the source |
| source/API/symbol/hook practical lookup | `SOURCE_HOOK_GUIDE.md` | reusable symbol/API/hook pattern/address/search route is established/revised | experiment chronology or one-off implementation detail |
| native collision cleanup callsites/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` | tested cleanup RVA/stack/symbol/caller interpretation changes | higher-level lifecycle design changes with no native callsite fact |
| project-wide engineering principles | `ENGINEERING_GUIDE.md` | a durable technical engineering principle generalizes beyond one subsystem | local implementation workaround/test detail |
| technical project scope/context for engine-facing prompts | `PROJECT_SCOPE_CONTEXT.md` | factual scope or standard prompt-context wording changes | ordinary technical implementation/evidence |
| research chronology / why an older technical decision existed | `EVIDENCE_INDEX.md` → exact EV/provenance; Git history when historical wording/sequence is actually needed | evidence interpretation or retrieval route changes | ordinary chronology growth; do not maintain a parallel milestone/history summary |
| active/unprocessed runtime/source artifact | `research/raw/` | a new artifact is still active input to interpretation/comparison | artifact has been canonically processed |
| processed runtime/source provenance | `research/archive/` | an unchanged source artifact has durable verification value after processing | active unresolved artifact; derived analysis material |
| deterministic retrieval/analysis aid | `research/derived/` | a canonical raw/archive artifact needs a reproducible retrieval package/extract | source artifact itself; hand-written replacement for canonical evidence |
| superseded ordinary documentation wording/history | Git history | older wording/removed file must be recovered for historical reasoning | ordinary active retrieval; Git history is not a competing current authority |

Canonical evidence remains one global monotonic namespace:

```text
EVIDENCE_LEDGER.md                EV-001–EV-157
EVIDENCE_LEDGER_STEP_B.md         EV-158–EV-198
EVIDENCE_LEDGER_199_ONWARD.md     EV-199 onward
```

---

## 2. Dependency Direction

The intended knowledge direction is mostly:

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

Stable operating conventions are orthogonal project state; procedures and current-state documents route to `PROJECT_PIPELINE.md` rather than maintaining alternative naming/numbering/version schemes.

Participant allocation is likewise orthogonal: `COLLABORATION_RULES.md` chooses where a responsibility belongs; the owning execution/procedure authority then defines how that responsibility is performed.

Do not create sideways dependency chains where every authority repeats every other authority.

---

## 3. Cross-Responsibility Routing Rule

When proven knowledge becomes materially relevant to a different future responsibility:

```text
keep the fact in its one owning authority/evidence record
→ add the smallest useful cross-route from the future responsibility
→ preserve the original regression/invariant route if the new knowledge may replace a workaround
```

Do not copy the underlying narrative into several subsystem documents.

Vague “might be useful someday” relationships do not justify cross-routes.

---

## 4. Registry Maintenance / New-Authority Rule

A newly noticed gap, refinement, future dependency, or missing route is **not** by itself a reason to create another document.

Default order:

```text
noticed gap/refinement
→ can an existing authority absorb it cleanly?
→ can an existing section be strengthened?
→ can an existing index/route make it discoverable?
→ can an existing procedure be refined?
→ only then consider whether a genuinely new responsibility exists
```

Create a new authority only when placing the responsibility in an existing authority would blur ownership, distort that authority's purpose, or make retrieval materially worse.

Before creating another document ask:

1. Does an existing authority already own this responsibility?
2. Can the gap be solved by strengthening an existing section, procedure, or index route?
3. Is the problem actually missing indexing rather than missing authority?
4. Would a new document create another independently stale copy or another file fresh contexts must load?
5. Would adding the material to an existing authority genuinely distort that authority's responsibility?

A full registry review is appropriate only when the knowledge schema itself changes, repeated maintenance transactions reveal unclear ownership, or a knowledge-system health check shows material retrieval/document burden.

The event-by-event maintenance procedure belongs in `KNOWLEDGE_MAINTENANCE.md`, not here.

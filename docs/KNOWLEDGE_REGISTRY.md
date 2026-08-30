# Gothic 3 Knowledge Authority Registry

**Status:** Active authority/update-trigger registry  
**Updated:** 2026-08-30

## Purpose

Define where project knowledge belongs and what kinds of events should update each authority.

Use this registry during the maintenance transaction in `KNOWLEDGE_MAINTENANCE.md`.

The registry exists to prevent the same fact becoming a separately maintained copy in many documents.

> **One responsibility should have one primary authority. Other documents route to it.**

---

## Authority Registry

| Knowledge responsibility | Primary authority | Update when | Usually do NOT update when |
|---|---|---|---|
| current active subsystem / causal gate / immediate next responsibility | `SESSION_ENTRYPOINT.md` | active gate, subsystem, immediate candidate, or next responsibility changes; also when temporary prerequisite, isolation, contradiction-resolution or safety/hardening work materially replaces what a fresh Normal Chat should do next, even if the enclosing gate ID or long-term objective is unchanged | another test merely confirms the existing gate/model, or a trivial/routine substep does not materially change what a fresh Chat should do next |
| transient Chat ↔ Work / context handoff | `BETWEEN_CHATS.md` | another context needs exact transient implementation/test state | ordinary project facts already live in durable authorities |
| project-specific collaboration behavior / participant-tool division of labor | `COLLABORATION_RULES.md` | a recurring Gothic-3-specific collaboration lesson materially changes workflow, participant/tool allocation, delegated authority, or a material resource constraint such as Work budget changes the best responsibility split | one isolated annoyance/error that existing rules already cover, or a technical result that does not change collaboration responsibility |
| stable project operating conventions: branch/state meanings, gate/test IDs, evidence/procedure IDs, raw/derived naming, prototype/build identity, document versioning, validation/artifact flow | `PROJECT_PIPELINE.md` | an accepted convention changes, a genuinely new convention responsibility appears, or a transition/migration boundary must be defined | routine use of an established convention, every new test/log/evidence item, or a new Chat merely preferring another style |
| recurring project-local operations: Git handoff/sync, build/deploy/load verification, runtime-artifact intake/publish, large-log reduction, static-reference retrieval | `PROJECT_OPERATING_PROCEDURES.md` | repeated friction/mistakes, one serious operational failure, a clearly better recurring method, or a genuinely new recurring operation changes the best default procedure | every routine use, one-off command variation, or technical Gothic 3 result that does not change the procedure |
| bounded Work execution contract | `WORK_IMPLEMENTATION_PROTOCOL.md` | Work authority, stop conditions, review responsibility, or frozen-task execution model changes | a technical Gothic 3 finding unrelated to Work behavior |
| knowledge maintenance / future-relevance / knowledge-health process | `KNOWLEDGE_MAINTENANCE.md` | maintenance transaction/event model, future-use routing rule, workaround-reevaluation rule, project-to-CAM promotion boundary, audit-health criteria, or bloat early-warning responsibility changes | ordinary technical evidence/result already handled by the existing procedure |
| authority/update routing | `KNOWLEDGE_REGISTRY.md` | a responsibility gains/moves/loses authority or update-trigger logic changes | underlying knowledge grows inside an existing authority |
| overall intended Raise/speed/frame-collision system architecture | `DESIGN.md` | system responsibility, public behavior, major invariant, subsystem boundary, configuration model changes | experiment chronology, routine confirmations, build status |
| current collision execution/cleanup lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` | ownership/lifetime/cleanup invariant or causal architecture changes | a test confirms the existing lifecycle model without changing it |
| current collision diagnostic architecture | `COLLISION_LOGGER_PLAN.md` | hook ownership, diagnostic event model, active probe responsibility changes | a log adds evidence without changing diagnostic design |
| current staged collision validation gates | `COLLISION_TEST_PLAN.md` | current gate, acceptance criteria, control matrix, or interpretation rule changes | historical completed-test detail already preserved by evidence |
| exact evidence status/provenance | `EVIDENCE_LEDGER.md` + `EVIDENCE_LEDGER_STEP_B.md` | a controlled/source fact is established, qualified, contradicted, or materially reinterpreted | pure design preference without factual claim |
| evidence topic / future-responsibility routing | `EVIDENCE_INDEX.md` | a new evidence domain/range/search route is useful, an existing route materially changes, or proven knowledge becomes materially relevant to a different future engineering responsibility | every new EV already covered by an existing route or speculative “might be useful someday” relationships |
| generalized animation semantics / authoring rules | `ANIMATION_RULES.md` | a generalized filename/UseType/action/phase/pose/authoring semantic changes | one concrete asset/test that does not generalize the rule |
| concrete animation families/assets/fixtures | `ANIMATION_CATALOG.md` | a concrete family/asset/source annotation/fixture materially changes reusable asset knowledge | runtime architecture result with no asset-level consequence |
| animation question routing | `ANIMATION_INDEX.md` | a new animation knowledge category appears, an existing route changes, or another concrete animation responsibility needs a materially useful route | ordinary new catalog detail already reachable by current route |
| complete native animation filename existence | `data/animation_names/all_animation_names.txt` | source inventory is regenerated/replaced from authoritative extracted data | interpretation of existing filenames |
| author-grouped exact animation names/notes | `data/animation_names/author_grouped_attacks_and_stumbles.txt` | authoritative grouped source changes | generalized interpretation derived from the source |
| source/API/symbol/hook practical lookup | `SOURCE_HOOK_GUIDE.md` | reusable symbol/API/hook pattern/address/search route is established/revised | experiment chronology or one-off implementation detail |
| native collision cleanup callsites/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` | tested cleanup RVA/stack/symbol/caller interpretation changes | higher-level lifecycle design changes with no new native callsite fact |
| project-wide engineering principles | `ENGINEERING_GUIDE.md` | a durable technical engineering principle generalizes beyond one subsystem | local implementation workaround/test detail |
| research chronology / where an older line happened | `RESEARCH_MAP.md` | a meaningful historical milestone/topic route becomes hard to recover otherwise | every incremental test/result |
| active/unprocessed runtime/source artifact | `research/raw/` | new artifact still needs interpretation/comparison | artifact has already been canonically processed |
| processed provenance/history | `research/archive/` | artifact has durable verification value after processing | active unresolved artifact |
| superseded documentation wording/history | `docs/archive/` | active document is deliberately replaced/compressed and old wording retains historical value | ordinary edits that Git history already represents adequately |
| technical project scope/context for engine-facing prompts | `PROJECT_SCOPE_CONTEXT.md` | factual scope or standard prompt-context wording changes | ordinary technical implementation/evidence |

---

## Dependency Direction

The intended direction is mostly:

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

When proven knowledge becomes relevant to a different future responsibility, add a **small cross-route from that future responsibility to the existing authority/evidence**. Do not create another copy of the underlying fact.

Pipeline conventions are orthogonal durable operating state. Procedures and current-state documents should route to `PROJECT_PIPELINE.md` rather than maintaining independent naming/numbering/version schemes.

Do not create sideways dependency chains where every authority repeats every other authority.

---

## Common Event Examples

### New runtime result confirms an existing collision invariant

Likely updates:

```text
Evidence Ledger
research raw → archive
SESSION_ENTRYPOINT only if the active gate, direction, or immediate responsibility materially changes
```

Usually unchanged:

```text
DESIGN
ANIMATION_RULES
SOURCE_HOOK_GUIDE
ENGINEERING_GUIDE
PROJECT_PIPELINE
```

### New runtime result disproves the collision lifecycle candidate

Likely updates:

```text
Evidence Ledger
COLLISION_LIFECYCLE_PLAN
COLLISION_TEST_PLAN
SESSION_ENTRYPOINT
EVIDENCE_INDEX only if routing materially changes
research raw → archive when processed
```

### Temporary prerequisite changes the immediate route

```text
planned gate remains conceptually active
→ unexpected contradiction makes isolation or safety hardening prerequisite
→ SESSION_ENTRYPOINT changes to that immediate responsibility
→ after validation, SESSION_ENTRYPOINT may route back to the larger gate
```

`BETWEEN_CHATS.md` may carry exact short-lived continuation details, but it does not replace the current-state update.

### New engine knowledge may simplify an existing workaround later

Likely updates:

```text
owning Evidence Ledger / topic authority for the new fact
→ future-responsibility index route if the normal topic route would miss it
→ route future refactor to BOTH the newer mechanism and the older regression/invariant that caused the workaround
```

Usually do **not**:

```text
rewrite the workaround immediately
copy the new fact into several subsystem documents
create a new authority merely for the cross-relationship
```

### New exact animation file discovered

If it is merely existence:

```text
animation-name data / catalog as appropriate
```

If it reveals a generalized naming rule:

```text
ANIMATION_RULES
possibly ANIMATION_INDEX
Evidence Ledger only if the behavioral claim is controlled/source-backed
```

### Work implements an already-frozen diagnostic

Likely updates after independent review:

```text
SESSION_ENTRYPOINT or BETWEEN_CHATS if current continuation needs it
```

No architecture/evidence update until build/runtime/source contradiction provides new meaning.

### Project collaboration lesson appears reusable beyond Gothic 3

Default:

```text
fix the lowest owning Gothic 3 rule/procedure
→ preserve rationale / candidate wider relevance if useful
→ do not edit CAM as part of this transaction
→ dedicated CAM-evolution responsibility later decides cross-project promotion
```

### A new Chat proposes a different log/test/version naming style

Default:

```text
PROJECT_PIPELINE current convention
→ keep it
```

Only update if there is a real reason to change the convention, then define the transition deliberately. Context migration alone is not a change trigger.

---

## Registry Maintenance

### Existing-structure-first rule

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

Prefer strengthening the current knowledge structure over expanding the document set. Small refinements should normally improve an existing authority, section, index, or procedure rather than create a new file.

`PROJECT_PIPELINE.md` is justified as a distinct authority because stable operating conventions are neither technical evidence nor recurring procedure sequences, and scattering them across those documents produced the exact cross-Chat drift this responsibility is meant to prevent.

Create a new authority/document only when the responsibility is genuinely distinct enough that placing it in an existing authority would blur ownership, distort that authority's purpose, or make retrieval materially worse.

Add a new authority only when a genuinely distinct knowledge responsibility appears.

Before creating another document ask:

1. Does an existing authority already own this responsibility?
2. Can the apparent gap be solved by strengthening an existing section, procedure, or index route?
3. Is the problem really missing indexing rather than missing authority?
4. Would a new document create another independently stale copy or another file future chats must load?
5. Would adding the material to an existing authority actually distort that authority's responsibility? If not, prefer the existing authority.

Prefer a new index route or section over a new authority when possible.

A full registry review is appropriate only when the knowledge schema itself changes, repeated maintenance transactions reveal unclear ownership, or a knowledge-system health check shows that retrieval breadth/document growth is materially degrading work.

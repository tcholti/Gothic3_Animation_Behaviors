# Gothic 3 Knowledge Authority Registry

**Status:** Active authority/update-trigger registry  
**Updated:** 2026-09-20

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Purpose

Define **where current project knowledge belongs**, when each owner changes, and which material is only routing, temporary work, or archive.

This registry does not repeat the lifecycle. `KNOWLEDGE_MAINTENANCE.md` owns promotion/archive mechanics.

> **One responsibility should have one primary current owner. Evidence proves current statements; archive preserves history; neither silently becomes current architecture.**

---

## 1. Governing hierarchy

```text
CAM
↓
docs/README.md project charter
↓
specialist current authorities / references
↓
procedures / conventions / temporary work
↓
evidence and archive as supporting provenance
```

The repository root `/README.md` owns the discoverable startup front door. It is not the project charter.

---

## 2. Current authority registry

| Responsibility | Primary current owner | Update trigger |
|---|---|---|
| project purpose / long-term direction / scope / authority topology / retrieval model | `docs/README.md` | deliberate project-level change |
| ordinary + interrupted-Chat startup routing | root `/README.md` Start Here | startup/recovery route changes |
| current active gate / immediate responsibility | `SESSION_ENTRYPOINT.md` | gate/next responsibility changes |
| short-lived cross-context handoff | `BETWEEN_CHATS.md` | another context needs temporary continuation detail |
| collaboration / participant-tool allocation / Gothic↔CAM operationalization | `COLLABORATION_RULES.md` | collaboration rule changes |
| stable branch/test/evidence/procedure/artifact conventions | `PROJECT_PIPELINE.md` | convention changes |
| recurring operational sequences | `PROJECT_OPERATING_PROCEDURES.md` | recurring procedure changes |
| bounded Work execution behavior | `WORK_IMPLEMENTATION_PROTOCOL.md` | Work responsibility/execution rule changes |
| feature research→promotion method | `FEATURE_DEVELOPMENT_METHOD.md` | feature-development method changes |
| documentation/evidence promotion/archive lifecycle | `KNOWLEDGE_MAINTENANCE.md` | knowledge lifecycle changes |
| authority/update routing | `KNOWLEDGE_REGISTRY.md` | ownership or trigger changes |
| significant non-obvious decision rationale | `docs/decisions/` ADRs | accepted/superseded architectural/project decision |
| workstation-specific paths | `LOCAL_WORKSTATION_PATHS.md` | actual local path changes |
| overall behavior architecture / subsystem responsibilities | `DESIGN.md` | current intended architecture changes |
| release vs diagnostic product separation | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` | product/build separation changes |
| concise established collision facts | `COLLISION_REFERENCE.md` | reusable collision fact is established/qualified/contradicted |
| collision lifecycle / cleanup / terminal repair architecture | `COLLISION_LIFECYCLE.md` | lifecycle invariant/ownership changes |
| collision diagnostics architecture | `COLLISION_DIAGNOSTICS.md` | diagnostic ownership/event model changes |
| current/future collision validation gates | `COLLISION_TEST_PLAN.md` | test gate/matrix/acceptance changes |
| permanent Fist/raw8 behavior architecture | `COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md` | accepted raw8 production contract changes |
| permanent PhysicalFist/raw55 behavior architecture | `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md` | accepted raw55 production contract changes |
| exact source/hook/API facts | `SOURCE_HOOK_GUIDE.md` | reusable hook/source fact changes |
| exact collision cleanup callsite facts | `COLLISION_CLEANUP_CALLSITE_MAP.md` | cleanup callsite/stack fact changes |
| generalized animation semantics / authoring rules | `ANIMATION_RULES.md` | generalized authoring/runtime semantic changes |
| concrete animation families/assets/fixtures | `ANIMATION_CATALOG.md` | reusable asset-level fact changes |
| animation question routing | `ANIMATION_INDEX.md` | route/category changes |
| evidence topic/range routing | `EVIDENCE_INDEX.md` | EV range/topic route changes |
| current open evidence entries | `EVIDENCE_LEDGER_<start>_ONWARD.md` (exact active file routed by `EVIDENCE_INDEX.md`) | new EV entry or ledger rotation |
| deliberate evidence-storage path migration lookup | `EVIDENCE_PATH_MIGRATIONS.md` | historical/current path would become ambiguous |
| project engineering philosophy experiment | `ENGINEERING_GUIDE.md` | User accepts/revises the experimental engineering method |
| small factual project-scope context | `PROJECT_SCOPE_CONTEXT.md` | factual project context changes |

---

## 3. Supporting/non-current material

### Active temporary work

```text
docs/work/active/
```

Owns only currently unresolved probes, bounded implementation contracts, audit tasks and similar temporary work.

It is **not** current architecture/reference. Every temporary document must declare `**Status:** ACTIVE`.

### Closed investigations

```text
docs/archive/investigations/
```

Preserves completed probes, implementation contracts, audits and superseded work plans after reusable conclusions are promoted.

### Closed evidence ledgers

```text
docs/archive/evidence/
```

Preserves completed EV volumes. They are proof history, not ordinary retrieval.

### Runtime provenance

```text
research/raw/      open/unprocessed intake
research/derived/  deterministic retrieval aids
research/archive/  processed canonical runtime source
```

---

## 4. Knowledge direction

A new runtime/source fact should flow:

```text
evidence
-> current reference
-> architecture consequence only when responsibility/invariant changes
-> small routing/index update only when needed
```

A new design choice should flow:

```text
User + Normal Chat decision
-> owning architecture
-> ADR only if rationale is significantly non-obvious/future-relevant
-> bounded implementation contract under docs/work/active/ when implementation is needed
```

A temporary work item closes:

```text
proof/result
-> promotion to durable owner(s)
-> current-state update if needed
-> archive temporary document
```

Never reverse this direction by treating a closed probe/audit as the current system specification.

---

## 5. Evidence vs reference rule

Evidence says **what was observed, where, and under what scope**.

Current reference says **what we currently know**.

Architecture says **how our system is designed around that knowledge**.

Therefore:

- ordinary settled questions begin from current reference/architecture;
- exact proof questions route through `EVIDENCE_INDEX.md`;
- contradictions descend to the exact EV/raw source;
- a new EV that changes current knowledge must update the current owner before closure;
- adding evidence does not require duplicating its full narrative into reference.

---

## 6. Current-state rule

`SESSION_ENTRYPOINT.md` and `BETWEEN_CHATS.md` are pointers, not history.

They must not become owners of:

- completed campaign chronology;
- long audit results;
- detailed probe reasoning;
- engine reference facts;
- architectural explanations already owned elsewhere.

When such material accumulates, promote it to the correct owner and compress the pointer.

---

## 7. Registry maintenance

Create a new permanent authority only when a real responsibility has no suitable current owner.

Before creating one, ask:

1. Is this current fact, architecture, rationale, evidence, procedure, convention, routing, current state, or temporary work?
2. Does an existing owner already cover it?
3. Would a new document reduce retrieval ambiguity rather than add another copy?
4. Can the result be expressed as a section in an existing owner instead?

A new document without a distinct responsibility is duplication.

The knowledge-state validator enforces structural parts of this registry; semantic ownership remains a review responsibility.

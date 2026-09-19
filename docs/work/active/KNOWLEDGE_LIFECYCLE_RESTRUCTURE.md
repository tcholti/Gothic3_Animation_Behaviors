# Knowledge Lifecycle Restructure

**Status:** ACTIVE  
**Started:** 2026-09-19  
**Working branch:** `docs/knowledge-lifecycle-restructure`  
**Base technical branch:** `docs/collision-source-evidence`  
**Base SHA:** `a0edcf5556c25ea45e619c52d272d33a8b9cd326`

## Purpose

Perform the formal documentation/knowledge-architecture restructure agreed by the User without changing game behavior or interrupting the technical collision branch.

## Accepted direction

- current reference states settled facts compactly;
- current architecture states how the system uses those facts;
- ADRs preserve significant non-obvious rationale;
- evidence/ledgers preserve proof and provenance;
- temporary probes/tasks/audits live only while active, then archive after promotion;
- closed evidence-ledger volumes move out of ordinary retrieval;
- current-state files remain small;
- automation must enforce the lifecycle mechanically and consistently across rule/procedure authorities.

## Review boundary

This branch may change documentation structure, documentation-routing automation, and documentation-only CI.

It must not change Gothic runtime/source behavior.

## Acceptance gates before promotion

1. POP-10 hierarchy/ownership review complete.
2. Closed temporary investigations are archived only after reusable conclusions are represented by current reference/architecture/ADR owners.
3. Exactly one active evidence ledger remains in `docs/`; closed volumes are archived.
4. Ordinary retrieval is reference-first and evidence is escalation/provenance.
5. Root `README.md` remains the unique discoverable front door for ordinary and interrupted continuation.
6. Rule/procedure authorities route consistently to `KNOWLEDGE_MAINTENANCE.md`; no competing lifecycle variant remains.
7. `tools/knowledge/validate_knowledge_state.py` passes in GitHub Actions.
8. Manual semantic review finds no current-document references to superseded plan/probe names and no contradictory startup/retrieval instructions.
9. Compare against the base technical branch contains documentation / documentation-automation changes only.
10. Before promotion, this active work record is archived, current-state pointers are restored to the technical collision responsibility, and the final promotion diff is revalidated.

## Promotion plan

When all gates pass:

```text
final documentation branch audit
-> archive this temporary work record
-> restore post-promotion technical SESSION_ENTRYPOINT / BETWEEN_CHATS state
-> final knowledge-state CI PASS
-> promote reviewed branch into docs/collision-source-evidence
-> verify promoted branch
-> remove temporary review branch when tooling permits
```

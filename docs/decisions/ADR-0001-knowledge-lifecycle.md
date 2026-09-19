# ADR-0001 — Separate Current Knowledge from Historical Proof

**Status:** Accepted  
**Date:** 2026-09-19

## Context

The project accumulated strong evidence provenance, but temporary probes, implementation contracts, audits and large chronological evidence ledgers remained in the ordinary documentation surface after their questions were closed.

This caused fresh Chats to reconstruct settled behavior from historical material, increased context consumption, and made closed research documents appear comparable to current architecture.

## Decision

Use five distinct documentation roles:

```text
CURRENT REFERENCE
  concise established facts + evidence pointers

CURRENT ARCHITECTURE
  intended system responsibilities/invariants

DECISION RECORDS
  rationale for significant non-obvious choices

EVIDENCE / PROVENANCE
  exact observations, scope and proof trail

TEMPORARY WORK
  active probes, bounded implementation contracts and audits
```

Temporary work must leave the ordinary documentation surface when closed. Before archival, every reusable conclusion must be promoted to its durable owner.

Closed evidence ledgers are cold/archive material. Ordinary technical retrieval begins from current reference/architecture, not chronological evidence. Evidence is opened when provenance, qualification, contradiction or reinterpretation matters.

Current-state files remain small and replaceable.

The detailed lifecycle is owned by `KNOWLEDGE_MAINTENANCE.md`. Machine validation is provided by `tools/knowledge/validate_knowledge_state.py`.

## Consequences

- Research history remains preserved and searchable without being normal context.
- A closed probe is not treated as current authority.
- Evidence remains auditable but is not the default knowledge interface.
- New durable facts must have an explicit current owner.
- Documentation closure includes promotion + archival, not merely writing an EV.
- The repository gains mechanical checks against the most common lifecycle drift.

This decision is project-structure policy. Routine reviews/audits may improve its implementation but must not silently collapse the roles back together.

# Repository Health and Authority Audit

**Status:** ACTIVE  
**Task class:** Formal POP-10 repository review/audit — read-only analysis with one allowed result file  
**Branch:** `development`

## Purpose

Perform a bounded independent review of the current `Gothic3_Animation_Behaviors` repository before broad native Speed calibration resumes and before the project moves into a fresh Normal Chat.

The project has accumulated extensive engine research, collision evidence, Speed implementation/evidence, diagnostics, archived investigations, and long-term knowledge-management structure. The goal is to identify real drift, duplication, stale routing, ownership ambiguity, lifecycle problems, source/document mismatch, or retrieval friction **without destroying unique technical knowledge or historical proof**.

This audit is deliberately preservation-biased.

> **Do not clean as you go. First understand authority, classify the material, and report findings. Normal Chat will review the audit before any cleanup or restructuring is accepted.**

## Launch authority

The Work launcher must supply the exact remote `development` HEAD to audit. Work must confirm it is reviewing that exact branch state before substantive evaluation.

If the remote branch has advanced beyond the launcher-supplied HEAD, stop and report the mismatch rather than auditing an unagreed state.

## Required read order / POP-10 hard gate

Start from the repository, not remembered conversation context.

Read first:

1. root `README.md` — canonical front door / Start Here;
2. `docs/SESSION_ENTRYPOINT.md` — current state pointer;
3. `docs/README.md` §0 — Project Charter / highest Gothic-specific authority;
4. `docs/KNOWLEDGE_REGISTRY.md` — ownership/update routing;
5. `docs/KNOWLEDGE_MAINTENANCE.md` — lifecycle/preservation rules;
6. `docs/PROJECT_OPERATING_PROCEDURES.md` POP-10 and POP-12;
7. this audit task;
8. `docs/WORK_IMPLEMENTATION_PROTOCOL.md` only for Work execution/publication constraints.

Before evaluating any target, write a compact preflight in the audit report that states:

```text
governing hierarchy
review scope
intended use/owner of each major target class
higher-level intent that must be preserved
what this audit is NOT authorized to redefine
```

The formal audit has **not started** until that preflight is complete.

## Governing hierarchy to verify, not assume blindly

The expected hierarchy is:

```text
CAM constitutional collaboration layer
-> docs/README.md project charter
-> specialist current authorities/references
-> conventions/procedures/bounded active tasks
-> evidence/provenance
-> archive/history
```

File size, age, detail, recency, or textual similarity do not define authority.

## Audit scope

Review the current repository state broadly enough to answer whether a fresh Normal Chat can safely continue from the current authorities without rediscovering or accidentally contradicting established work.

### A. Startup / continuity / branch routing

Check:

- root README Start Here accuracy;
- active/stable/historical branch descriptions;
- `SESSION_ENTRYPOINT.md` and `BETWEEN_CHATS.md` size, accuracy and role discipline;
- whether a fresh Chat reaches the correct current responsibility through the intended route;
- stale pointers to old branches/tasks/results.

### B. Authority topology and current-document health

Check current authorities named in `KNOWLEDGE_REGISTRY.md` for:

- responsibility overlap;
- contradictory current claims;
- obsolete statements that conflict with later accepted evidence/architecture;
- current documents carrying excessive chronology/history that belongs in evidence/archive;
- missing durable owner for established reusable knowledge;
- duplicate permanent authorities without distinct responsibility.

Do not treat parallel specialist authorities as duplicates merely because topics overlap.

### C. Current Speed / Raise / collision architecture consistency

Review current source-facing authorities and implementation shape for agreement, especially:

```text
docs/DESIGN.md
docs/SOURCE_HOOK_GUIDE.md
docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md
docs/decisions/ADR-0004*
docs/decisions/ADR-0005*
docs/decisions/ADR-0006*
docs/decisions/ADR-0009*
docs/work/active/SPEED_EXPANDED_ATTACK_SCOPE_AND_GROUPED_PROFILE_IMPLEMENTATION.md
docs/work/active/SPEED_NATIVE_CALIBRATION_PROBE.md
src/Script_G3AnimationBehaviors/
tools/Script_SpeedCalibrationProbe/
root CMake / relevant target CMake files
```

Confirm or flag mismatches involving:

- grouped profile identity;
- seven current Speed attack prefixes;
- caller-side compatible composition;
- native `ReferenceHitBaseSpeed` semantics;
- Sprint inheriting Power timing on the proven shared route;
- production `+0x42A0` non-ownership;
- Raise remaining paused;
- production collision integration remaining closed/stable;
- diagnostics/release separation.

Do not redesign these mechanisms during the audit.

### D. Evidence / provenance health

Check:

- exactly one active evidence ledger;
- `EVIDENCE_INDEX.md` routing accuracy;
- EV monotonicity / obvious route gaps;
- whether settled reusable conclusions are promoted out of evidence into current owners;
- whether current evidence claims accidentally rely on missing/deleted source artifacts;
- `research/raw`, `research/derived`, and `research/archive` lifecycle consistency;
- whether any raw artifact retained in active intake has an explicit ongoing comparison reason;
- whether old paths are covered by `EVIDENCE_PATH_MIGRATIONS.md` when needed.

**Do not delete, move, compress, rewrite, or archive any evidence artifact in this task.**

Large raw logs and the 5,991-name inventory are not default reading material. Use metadata/indexes/search first. Open large evidence only when a concrete contradiction requires exact verification.

### E. Active temporary-work lifecycle

Inspect `docs/work/active/` and classify each item:

```text
genuinely active
closed but not yet archived
superseded
unclear
```

For anything that appears closable, verify whether its reusable conclusions have already been promoted before recommending archival.

**Do not archive/move/delete any active task in this audit.**

### F. Repository/product/tooling shape

Review at a structural/static level:

- root and target CMake topology;
- production vs diagnostics/probe target separation;
- obviously orphaned current tooling or stale README descriptions;
- obsolete paths/names that materially hurt retrieval;
- whether diagnostic tools that hook overlapping Gothic surfaces are clearly treated as mutually exclusive at runtime;
- whether the “renaming a DLL inside `scripts` is not a disable method” rule is consistently represented where operationally necessary.

Do not build.

### G. Reusable Gothic 3 engine knowledge preservation

Check that reusable reverse-engineering knowledge is not stranded only in old task/evidence history when it has clear future value.

In particular inspect the role/coverage of:

```text
docs/SOURCE_HOOK_GUIDE.md
docs/COLLISION_CLEANUP_CALLSITE_MAP.md
docs/ANIMATION_RULES.md
docs/ANIMATION_CATALOG.md
docs/ANIMATION_INDEX.md
```

Consider future reuse for Speed, Raise, attack displacement, climbing/traversal, targeting, and other engine-facing work.

Do not invent new facts from historical hints. Recommend promotion only when the underlying fact is already established.

### H. Documentation/context-bloat health

Identify current documents that are becoming routine context burdens, but distinguish:

```text
large because it wrongly contains chronology/duplication
vs
large because it is the rightful specialist authority/reference
vs
large cold evidence/archive that ordinary work does not load
```

The project principle is:

> **Preserve proof deeply; present current knowledge shallowly. Not necessary to read now does not mean not necessary to preserve.**

Do not recommend deletion merely to reduce repository size or token count.

## Mechanical validation

Run:

```text
python tools/knowledge/validate_knowledge_state.py
```

Record the exact PASS/failure result in the report.

If validation fails, diagnose the owning structural issue. **Do not weaken or edit the validator in this task.**

Other allowed static checks may include bounded file listings, Git status/history inspection, CMake/source searches, reference checks, and `git diff --check` for the report commit.

## Preservation rules — hard constraints

This audit is not authorized to remove project knowledge.

Do **not**:

```text
delete any file
move or rename any existing file
archive any active/temporary document
rotate the evidence ledger
rewrite or compact evidence history
rewrite accepted ADR history
modify production or diagnostic source code
modify CMake/build behavior
change current architecture or product semantics
change main
build or deploy anything
run Gothic 3
change runtime DLLs
start Raise work
start attack-displacement/climbing work
resume broad native calibration
```

Do not classify something as redundant unless you identify:

1. its intended role;
2. the surviving owner of every reusable fact/responsibility;
3. whether it contains unique provenance/history;
4. whether archive rather than deletion is the correct lifecycle action;
5. the preservation risk if your classification is wrong.

When uncertain, classify as **KEEP / NEEDS NORMAL CHAT REVIEW**, not delete.

## Findings discipline

Distinguish clearly between:

```text
factual contradiction
stale current statement
retrieval/routing problem
ownership ambiguity
duplicate responsibility
healthy historical duplication/provenance
closed temporary work candidate
context-bloat concern
optional improvement
no-action / healthy state
```

Do not turn stylistic preference into an audit defect.

Severity should reflect project risk, not document age/size:

```text
BLOCKER  = unsafe to continue ordinary work without resolution
HIGH     = material authority/evidence/source contradiction
MEDIUM   = meaningful stale routing/ownership/lifecycle problem
LOW      = bounded hygiene/retrieval improvement
INFO     = observation/no-action context
```

## Only authorized repository write

Work may create exactly one new file:

```text
docs/work/active/REPOSITORY_HEALTH_AND_AUTHORITY_AUDIT_RESULT.md
```

It must begin with:

```text
# Repository Health and Authority Audit Result

**Status:** ACTIVE — WORK RESULT PENDING NORMAL CHAT REVIEW
```

No other existing or new repository file may be changed by Work.

The result file may be committed/pushed to the same `development` branch. Publication authorization is limited to that one result file and the exact audited state.

If publication would require modifying any other file, stop and report rather than broadening.

## Required report structure

Use this structure:

```text
1. POP-10 preflight
2. Exact audited repository/branch/HEAD
3. Knowledge-state validation result
4. Executive summary
5. Findings table
   ID
   severity
   target(s)
   target role/owner
   finding
   evidence/reason
   smallest proposed correction
   preservation risk
   confidence
6. Active-work lifecycle classification
7. Evidence/raw/archive health
8. Source/docs/product-shape consistency
9. Reusable engine-knowledge preservation check
10. Context/retrieval health
11. Explicit KEEP / DO-NOT-REMOVE items
12. Proposed correction sequence for Normal Chat review
13. Audit limits / unresolved questions
```

For every proposed move/archive/consolidation, name the surviving current owner and explain why unique information would remain recoverable.

## Stop conditions

Stop and report without inventing a resolution if:

- authority ownership is genuinely ambiguous;
- a proposed cleanup might remove unique engine/evidence knowledge;
- current source contradicts a frozen architecture decision in a way requiring design judgment;
- project purpose/scope/topology would need to change;
- a CAM-level issue appears implicated;
- exact evidence needed to resolve a factual dispute is unavailable;
- remote `development` moved away from the launcher-supplied audit HEAD;
- the audit would need a build/runtime test to decide a claim.

## Completion

Success is **not** “fewest files.” Success is:

```text
formal hierarchy understood
current repository health assessed
material drift identified
preservation risks explicit
no project knowledge destroyed
one durable audit report published
Normal Chat can independently review findings before any cleanup
```

After publishing the result file, STOP. Do not implement the recommendations.

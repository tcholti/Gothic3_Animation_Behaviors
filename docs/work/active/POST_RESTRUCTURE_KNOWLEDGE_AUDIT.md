# Post-Restructure Knowledge / Documentation Audit

**Status:** ACTIVE  
**Type:** Formal read-only project review/audit  
**Created:** 2026-09-19  
**Owner:** Work Chat executes the audit; Normal Chat + User interpret findings and decide any corrections.

## Purpose

Independently test the large 2026-09-19 knowledge-lifecycle/documentation restructure before technical collision work resumes.

This is not another redesign task. The audit must determine whether the current repository is internally consistent, retrievable, evidence-grounded, resistant to future documentation bloat, and accurately represented by its rules/procedures/automation.

## Governing preflight

Apply POP-10 before evaluating targets.

The reviewer must first state:

```text
CAM
-> docs/README.md project charter
-> specialist current authorities/references
-> procedures/conventions/current-state/temporary work
-> evidence + archive as supporting provenance
```

Confirm the intended role of each major target before calling statements contradictory or redundant.

The accepted knowledge model to test, not silently redefine, is:

```text
current reference = what is established
architecture      = how the current system uses/owns it
ADR               = why significant non-obvious choices were made
evidence          = proof / provenance / scope
temporary work    = unresolved work only
archive           = closed history outside ordinary retrieval
current state     = small replaceable pointers
```

## Read first

1. root `README.md`
2. `docs/README.md` §0 and retrieval model
3. `docs/SESSION_ENTRYPOINT.md`
4. `docs/BETWEEN_CHATS.md`
5. `docs/PROJECT_OPERATING_PROCEDURES.md` — POP-10 and POP-12
6. `docs/KNOWLEDGE_MAINTENANCE.md`
7. `docs/KNOWLEDGE_REGISTRY.md`
8. this audit contract

Then inspect the other current authorities/references/procedures needed by the audit.

## Audit scope

Perform a **current-surface-first** audit. Do not enumerate/read the whole archive, all raw logs, or every evidence ledger by default.

### A. Authority / ownership consistency

Check that:

- every current document has a distinct purpose and primary owner;
- charter, registry, maintenance, pipeline, procedures, collaboration rules, feature method and Work protocol do not define competing lifecycle/startup/review rules;
- lower authorities specialize rather than contradict higher authorities;
- root `README.md` remains the unique discoverable ordinary + interrupted-Chat front door;
- `SESSION_ENTRYPOINT.md` and `BETWEEN_CHATS.md` remain pointers, not history stores;
- current vs historical material is unambiguous.

### B. Retrieval / context-efficiency

Test whether a fresh Chat can answer settled questions by:

```text
current state when needed
-> current reference
-> current architecture / ADR when needed
-> EVIDENCE_INDEX only for proof
-> exact EV
-> archive/raw only for verification/contradiction
```

Identify routes that still force broad historical reading, duplicate large narratives, or make ordinary retrieval ambiguous.

### C. Evidence integrity / stale-evidence risk

Check:

- `EVIDENCE_INDEX.md` routes all current/archived ledger ranges correctly;
- exactly one active ledger exists and numbering continues monotonically;
- current reference statements cite plausible EV ranges and do not rely only on archived task prose;
- no current factual conclusion is stranded only in an index, archive document, or chat-era task contract;
- evidence path migrations and archive paths are coherent;
- old EVs remain provenance, not silently rewritten current authority.

Do **targeted evidence tracing**, not a 308-EV reread. At minimum trace representative current claims for:
1. equipped collision/lifecycle;
2. raw8 Fist;
3. raw55 PhysicalFist;
4. Sprint identity/transport;
5. current regression status;
6. shield/raw9 negative control.

Descend to exact archived ledger/raw only where necessary to verify the route or resolve doubt.

### D. Architecture / source-reality consistency

Check current architecture/reference against repository reality at a structural level:

- named modules/files actually exist;
- release vs diagnostic product names and responsibilities agree with CMake/source tree;
- hook-owner / feature-owner separation is stated consistently;
- current raw55 architecture, lifecycle and diagnostics documents do not depend on archived probe semantics as current authority;
- plans do not claim implementation/test state contradicted by current source/tree/state pointers.

This is **not** a full source-code correctness audit. Inspect source only enough to verify documentation reality claims or a discovered contradiction.

### E. Plans / current-state consistency

Check that:

- `COLLISION_TEST_PLAN.md`, `SESSION_ENTRYPOINT.md`, and `BETWEEN_CHATS.md` agree on the paused technical gate and next technical step after this audit;
- completed phases/results are not presented as active research;
- future gates are not accidentally described as already certified;
- deprecated/superseded plan names do not remain in current guidance.

### F. ADR quality / rationale coverage

Check that:

- ADR-0001 and ADR-0002 do not duplicate current architecture instead of preserving rationale;
- significant non-obvious structural decisions introduced by the restructure are either adequately explained by an ADR or clearly do not need one;
- no accepted ADR conflicts with current architecture/reference.

Do not create ADRs during this audit; report candidates only.

### G. Automation / adversarial robustness

Review:

- `tools/knowledge/validate_knowledge_state.py`
- `.github/workflows/knowledge-state.yml`
- POP-12 and lifecycle rules that claim what automation guarantees.

Verify the current clean branch passes the validator / current GitHub Action.

Then reason adversarially about bypasses and false confidence. Examples:

- a closed task left ACTIVE forever;
- an ACTIVE task not routed by current state;
- a new permanent doc added without registry ownership;
- a closed ledger left hot;
- direct references to closed ledger filenames;
- stale plan/probe names reintroduced;
- root README recovery rule removed from one authority but not others;
- broken current Markdown links;
- duplicate current owners with different wording;
- reference grows into another monolith;
- evidence index grows into a second narrative knowledge base.

Distinguish what automation can enforce mechanically from what still requires semantic review. Do not weaken checks merely because a condition is inconvenient.

### H. Repository hygiene

Check current remote branches, current `docs/work/active/`, `research/raw/`, current archive routing, and obvious stale temporary surfaces.

Do not delete anything.

## Explicit exclusions

This audit is **READ-ONLY**.

Do not:

- edit, create, move, delete, commit or push repository files;
- create/delete branches;
- modify source code;
- build, configure, deploy or launch Gothic 3;
- run new runtime experiments;
- create new EVs;
- rewrite old evidence;
- redesign CAM or project purpose;
- implement fixes discovered by the audit.

Build execution is prohibited.

## Findings standard

For every finding give:

```text
Severity: BLOCKER / MATERIAL / MINOR
Category:
Files/sections:
Observed inconsistency or weakness:
Why it matters:
Smallest correct owner for a future correction:
Evidence/provenance check performed, if applicable:
Suggested correction direction (not implementation):
```

Do not inflate stylistic preferences into findings. A finding should identify a concrete ambiguity, contradiction, stale route, missing durable owner, evidence weakness, automation gap, retrieval-cost problem, or repository-reality mismatch.

Also report meaningful **PASS / strength** observations where the restructure is demonstrably coherent.

## Required final report

Return:

1. POP-10 preflight hierarchy + scope statement.
2. Coverage map of current authorities/surfaces actually reviewed.
3. Findings grouped by severity.
4. Evidence-trace sample results for the six required topics.
5. Automation-strength assessment: what is mechanically enforced vs semantic/manual.
6. Branch/work/archive/raw hygiene status.
7. Overall assessment of whether the restructure is safe to keep as the current baseline.
8. Exact recommended correction order, if findings exist.
9. Build status: `NOT ATTEMPTED — prohibited by task.`
10. Repository changes: `NONE — audit is read-only.`

Then STOP. Do not implement any recommendation.

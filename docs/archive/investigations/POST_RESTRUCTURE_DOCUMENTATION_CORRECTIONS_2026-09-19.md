# Post-Restructure Documentation Corrections

**Status:** CLOSED/PASS
**Type:** Bounded documentation / validation implementation
**Created:** 2026-09-19
**Owner:** Work Chat implements; Normal Chat independently reviews before closure.

**Closure result:** ACCEPTED after independent Normal Chat review.

**Work implementation commit:** `cb5c7d6b6750fb4b2e1ec3e188e4565d8886308b`

**Independent review:**

- diff is exactly one commit from the frozen base;
- changed files are limited to the eight authorized documentation/validator owners;
- M-1 through M-5 match the frozen correction contract;
- no Gothic source/CMake/runtime/evidence/archive/ADR files changed;
- stale `§8.1`, obsolete raw55-current-probe wording, and architecture-owned live regression progress are absent from the corrected owners;
- `phase-1-golem` is present and current-state links target it;
- strengthened validator retains semantic/manual-review boundaries;
- GitHub Knowledge state run `35452345601` passed on the exact Work commit.

No build was required or attempted.

## Purpose

Implement only the bounded corrections accepted after the formal post-restructure audit.

The restructure itself is retained. This task repairs findings M-1 through M-5 without redesigning the knowledge model, changing Gothic behavior, rewriting evidence, or changing repository branch-protection policy.

Audit provenance:

- `docs/archive/investigations/POST_RESTRUCTURE_KNOWLEDGE_AUDIT_2026-09-19.md`
- `docs/archive/investigations/POST_RESTRUCTURE_KNOWLEDGE_AUDIT_RESULT_2026-09-19.txt`

## Governing decisions

Preserve the accepted knowledge model:

- current reference = what is established;
- architecture = current responsibilities/invariants;
- ADR = why significant non-obvious choices were made;
- evidence = proof/provenance;
- temporary work = unresolved bounded responsibility only;
- archive = closed history outside ordinary retrieval;
- current state = small replaceable pointers.

Root `README.md` remains the unique discoverable ordinary/interrupted startup front door.

Live campaign progress belongs in `SESSION_ENTRYPOINT.md` and `COLLISION_TEST_PLAN.md`, not in architecture authorities.

Automation must enforce only mechanically decidable invariants. Semantic/factual contradiction detection remains a POP-10/manual review responsibility.

## Read first

1. root `README.md`
2. `docs/README.md` §0 and retrieval model
3. `docs/SESSION_ENTRYPOINT.md`
4. `docs/BETWEEN_CHATS.md`
5. this task
6. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
7. `docs/KNOWLEDGE_MAINTENANCE.md`
8. `docs/KNOWLEDGE_REGISTRY.md`
9. `docs/PROJECT_OPERATING_PROCEDURES.md` — POP-10 and POP-12

Then inspect only the affected current documents and validator/workflow necessary for M-1 through M-5.

## Required corrections

### M-1 — Remove closed raw55 research chronology from current diagnostics authority

Owner: `docs/COLLISION_DIAGNOSTICS.md`.

Required outcome:

- remove the statement that PhysicalFist/raw55 repeated-contact causality remains unresolved;
- remove EV-290/native-ALL-clear suppression as a current probe;
- remove future scheduling of Normal replacement-clear proof, Power/Sprint repeated-FIST closure, and permanent raw55 architecture;
- state instead that raw55 causal research is closed through EV-294 and focused permanent acceptance is CLOSED/PASS through EV-298;
- state that `PhysicalFistCollision` is the permanent behavior owner;
- diagnostics observe permanent behavior and may use DEEP only for a genuinely new contradiction/question;
- route historical causal sequence through `EVIDENCE_INDEX.md` / archive rather than retaining it as current architecture;
- preserve still-current AttackContinuationProtection guidance and generic future-unknown-source/family DEEP rules.

Do not turn `COLLISION_DIAGNOSTICS.md` into another raw55 history summary.

### M-2 — Correct Sprint scope in current factual reference

Owner: `docs/COLLISION_REFERENCE.md` §6.

The corrected distinction must be unambiguous:

- raw8 Sprint: supported FIST path; factual Action9 can arrive through Power-named callback transport;
- raw55 Sprint-origin: supported permanent PhysicalFist/raw55 FIST behavior across the proven same-C1 Action9 -> Action2 origin/continuity route;
- equipped Sprint RIGHT/LEFT/BOTH/OFF: unsupported without factual evidence.

Preserve raw8/raw55/equipped mechanism separation. Cite existing EV routes; do not add or rewrite evidence.

### M-3 — Replace broken immediate plan route with a stable validated anchor

Owners:

- `docs/COLLISION_TEST_PLAN.md`
- `docs/SESSION_ENTRYPOINT.md`
- `docs/BETWEEN_CHATS.md`

Add one explicit stable anchor immediately before the Phase-1 Golem heading, using `phase-1-golem` as the id. Keep the existing human-readable heading.

Replace stale `COLLISION_TEST_PLAN.md §8.1` references in both current-state files with a real Markdown link to `COLLISION_TEST_PLAN.md#phase-1-golem`.

The route must still mean: exercise any prepared remaining Golem setup, or explicitly close Phase 1 if none remain, then Phase 2. Do not change technical test scope.

### M-4 — Remove live campaign-progress ownership from architecture

Owners:

- `docs/DESIGN.md` §12
- `docs/COLLISION_LIFECYCLE.md` §10

Remove dynamic progress claims such as exact IN PROGRESS through EV-xxx status and CURRENT -> next setup state from architecture.

Retain only durable ordering/dependency constraints: closed architecture/features -> standalone collision regression campaign -> New Balance exact-bundle compatibility gate -> mature production collision migration -> diagnostics-free integration validation -> later independent feature work.

Route live campaign status/next setup to `SESSION_ENTRYPOINT.md` and `COLLISION_TEST_PLAN.md`.

Do not remove durable architecture facts merely because they have evidence citations.

### M-5 — Strengthen mechanically decidable validator coverage

Owners:

- `tools/knowledge/validate_knowledge_state.py`
- `docs/PROJECT_OPERATING_PROCEDURES.md` POP-12
- `docs/KNOWLEDGE_MAINTENANCE.md` mechanical-automation section only if needed so its claims match reality

Implement the smallest robust checks for:

A. Markdown fragment/anchor validity
- for current Markdown links to `.md#fragment`, verify file existence and that the fragment resolves to an explicit HTML id or normalized Markdown heading anchor;
- fail on missing fragments;
- ensure the new Phase-1 route is covered.

B. Numeric section-route validity
- detect current-document routes of the form `SOME_FILE.md §N` or `SOME_FILE.md §N.M` where practical;
- verify the target Markdown file contains a heading with that numbered section;
- do not convert every valid numbered reference merely for style.

C. docs-root allowlist ↔ authority-registry pairing
- every ordinary/current `docs/*.md` permanent allowlist entry must have recognizable ownership/routing presence in `KNOWLEDGE_REGISTRY.md`;
- use only narrow explicit exemptions where the registry intentionally owns a class rather than one filename;
- fail when a new allowlisted permanent root document has no registry route;
- do not infer semantic ownership beyond presence/routing.

D. Permitted current Markdown directory topology
- outside `docs/archive/`, accepted current Markdown locations are `docs/`, `docs/decisions/`, and `docs/work/active/`;
- fail if a current Markdown document appears in another unregistered `docs/` subdirectory;
- archive remains excluded from current scanning.

E. Semantic limit
- do not add brittle keyword checks pretending to detect whether raw55 research is semantically closed, whether architecture is technically true, or whether differently worded documents duplicate ownership;
- POP-12 must continue to state that those require evidence/POP-10/manual review.

### N-1 — Explicitly excluded

Do not change branch protection, required status checks, repository rulesets, or related policy in this task.

## Allowed files

Expected edit surface:

- `docs/COLLISION_DIAGNOSTICS.md`
- `docs/COLLISION_REFERENCE.md`
- `docs/COLLISION_TEST_PLAN.md`
- `docs/DESIGN.md`
- `docs/COLLISION_LIFECYCLE.md`
- `docs/SESSION_ENTRYPOINT.md`
- `docs/BETWEEN_CHATS.md`
- `tools/knowledge/validate_knowledge_state.py`
- `docs/PROJECT_OPERATING_PROCEDURES.md`
- `docs/KNOWLEDGE_MAINTENANCE.md` only if its automation description requires synchronization

If another current rule/procedure document must change solely to remove a direct contradiction introduced by these exact corrections, stop and report it before broadening.

Do not edit evidence ledgers, evidence index, archive provenance, ADRs, source/CMake, or runtime research.

## Validation

Work may run documentation/static validation only.

Required before commit:

1. run `python tools/knowledge/validate_knowledge_state.py`;
2. search for stale `COLLISION_TEST_PLAN.md §8.1` references;
3. search for stale raw55 unresolved/EV-290-current-probe wording;
4. inspect `DESIGN.md` and `COLLISION_LIFECYCLE.md` for dynamic regression progress;
5. inspect diff for M-1 through M-5 only;
6. confirm no source/runtime/evidence files changed.

Build execution is PROHIBITED.

## Publication

The User authorizes this bounded documentation/validator correction to be committed and pushed directly to `docs/collision-source-evidence`.

Start from the exact remote HEAD stated by the launcher.

## Required final report

Report:

- final remote commit SHA;
- changed files;
- M-1 through M-5 result, one concise item each;
- validator result;
- whether any material contradiction forced a stop/broadening request;
- `Build: NOT ATTEMPTED — prohibited by task.`

Then STOP.

Do not close/archive this correction task yourself. Normal Chat performs independent review and lifecycle closure after the Work result returns.

# Post-Release Repository Audit Preparation

**Status:** ACTIVE — preparation only; large audit not yet launched  
**Mode:** Normal Chat planning / User-priority capture  
**Stable comparison baseline:** `main @ 08a0bd8fcf42173088e233e09b706a80da882070`  
**Working branch:** `development`

## Purpose

Prepare the larger post-release repository/documentation review without allowing the audit itself to start before the User identifies documentation and knowledge areas that deserve special attention or protection.

The first-release `main` checkpoint is now the protected comparison baseline rather than the working branch.

## Immediate responsibility

The User first identifies documentation/knowledge areas that should receive special attention.

Normal Chat then incorporates those concerns into the bounded Work audit brief.

Do **not** launch the large audit before this User-priority step is complete.

## Frozen audit sequence

### Phase 1 — User priorities

Collect the specific documentation/knowledge concerns from the User.

These priorities are inputs to the audit contract, not merely optional suggestions. They exist to protect contextual material that a static repository review could misunderstand.

### Phase 2 — Work read-only large review/audit

Launch Work with a large but bounded **read-only** responsibility.

Work must:
- start repository-first;
- apply the formal project review/audit procedures and authority hierarchy;
- inspect architecture/document authority/current-state/release remnants/tooling/evidence routing/bloat/stale material;
- explicitly include the User-named documentation/knowledge concerns;
- return findings and proposed actions.

Work must **not** freely restructure, delete, archive, compact, or rewrite repository material during this first audit pass.

### Phase 3 — Normal Chat + User findings review

Review Work's findings together.

For proposed changes, explicitly decide:

```text
KEEP
CHANGE
ARCHIVE
REMOVE
```

This phase protects useful context and historical/operational material that a static audit might incorrectly classify as redundant.

### Phase 4 — Work approved maintenance implementation

Only after Normal Chat/User decisions are closed, launch Work again.

That task may implement **only the approved audit maintenance** on `development`.

Do not modify stable `main`.

### Phase 5 — Normal Chat post-audit review

Review the resulting post-audit `development` state before accepting the maintenance.

The post-audit development checkpoint must be explicit before the next comparison task.

### Phase 6 — Work independent main-vs-development loss detection

Launch a **second independent Work task** after the audited development state has been reviewed.

Its responsibility is:

> Assume `main` is the trusted pre-audit first-release knowledge snapshot. Identify anything materially useful, authoritative, operationally important, or historically necessary that existed on `main` but is missing, weakened, ambiguously relocated, or semantically altered on reviewed `development`.

Important qualification:
- deletion or compression is **not automatically a defect**;
- do not report loss when the same responsibility is still represented correctly by an appropriate current owner;
- focus on semantic/operational loss, weakened authority, broken retrieval, or lost necessary provenance.

### Phase 7 — Normal Chat final reconciliation

Review the loss-detection findings.

Repair any genuine loss before accepting the audited `development` state.

## Comparison checkpoints

```text
MAIN
= accepted first-release baseline before large audit
= main @ 08a0bd8fcf42173088e233e09b706a80da882070

DEVELOPMENT pre-audit
= first-release lineage
+ post-promotion / audit-preparation documentation
= working state from which the audit begins

DEVELOPMENT post-audit
= reviewed/refactored repository state
after approved audit maintenance
```

The branches need not remain byte-identical after post-promotion bookkeeping. `main` is the protected **semantic/reference snapshot**.

## Hard boundaries

- stay on `development` for audit work;
- do not modify or re-promote `main` during this cycle unless the User explicitly authorizes it;
- do not begin new feature work during the audit sequence;
- do not let the first Work review implement its own cleanup recommendations;
- do not skip the Normal Chat/User KEEP/CHANGE/ARCHIVE/REMOVE decision phase;
- do not skip the final independent main-vs-development loss-detection pass.

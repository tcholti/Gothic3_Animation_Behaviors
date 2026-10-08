# Post-Release Repository Audit Preparation

**Status:** ACTIVE — first documentation maintenance implemented; Normal Chat review / later stages pending
**Mode:** Normal Chat review / staged post-release maintenance
**Stable comparison baseline:** `main @ 08a0bd8fcf42173088e233e09b706a80da882070`  
**Working branch:** `development`

## Purpose

Track the deliberately staged post-release repository/knowledge-maintenance sequence. User priorities, two read-only audits and Normal Chat/User review have completed the pre-implementation gates for the first bounded documentation-consolidation task. The first-release main checkpoint remains the protected baseline.

## Immediate responsibility

Normal Chat reviews the current development documentation-consolidation commit and Work handoff. The approved stage entered at `fb61c6bedf84bae239610b2c37c205580a7fc63f`: one maintained COLLISION_REFERENCE, six archived former authorities, full old reference/pre-change DESIGN snapshots, bounded stale-description/ownership/navigation corrections and static checks. No source/configuration/build/runtime change or new EV.

The old “User priorities before initial audit” gate is complete. This document remains ACTIVE because review, remaining separately approved maintenance and the independent comparison/reconciliation sequence remain open. Work stops after publishing this stage; Normal Chat owns eventual closure/archive of this active document.

Deferred: KA-08/09 derived/manual evidence moves, KA-10 build defaults, KA-11 historical config/Movement seed and optional KA-12 automation. None belongs to this stage. Original Git/blob/SHA256 and historical-path recovery for the collision archives are in EVIDENCE_PATH_MIGRATIONS.

## Frozen audit sequence

### Phase 1 — User priorities

Completed for the frozen audits and first maintenance task; later scope decisions still require deliberate User review.

These priorities are inputs to the audit contract, not merely optional suggestions. They exist to protect contextual material that a static repository review could misunderstand.

### Phase 2 — Work read-only large review/audit

Completed: initial bounded read-only audit and targeted §3A follow-up. Their findings are advisory; they did not authorize unrelated maintenance.

Work must:
- start repository-first;
- apply the formal project review/audit procedures and authority hierarchy;
- inspect architecture/document authority/current-state/release remnants/tooling/evidence routing/bloat/stale material;
- explicitly include the User-named documentation/knowledge concerns;
- return findings and proposed actions.

Work must **not** freely restructure, delete, archive, compact, or rewrite repository material during this first audit pass.

### Phase 3 — Normal Chat + User findings review

Completed for the first consolidation contract; unapproved carry-forward proposals remain pending.

For proposed changes, explicitly decide:

```text
KEEP
CHANGE
ARCHIVE
REMOVE
```

This phase protects useful context and historical/operational material that a static audit might incorrectly classify as redundant.

### Phase 4 — Work approved maintenance implementation

The first approved stage is implemented for review. Any additional Work stage needs its own frozen scope after Normal Chat/User decisions.

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

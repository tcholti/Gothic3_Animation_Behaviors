# Post-Release Repository Audit Preparation

**Status:** ACTIVE — five stages reviewed/accepted; KA-12 next separately, independent comparison pending
**Mode:** Normal Chat review / staged post-release maintenance
**Stable comparison baseline:** `main @ 08a0bd8fcf42173088e233e09b706a80da882070`  
**Working branch:** `development`

## Purpose

Track the deliberately staged post-release repository/knowledge-maintenance sequence. User priorities, two read-only audits and Normal Chat/User review led to two accepted preservation-first stages and the third approved Practical Knowledge & Engineering Principles documentation task. The first-release main checkpoint remains the protected baseline.

## Immediate responsibility

Two approved preservation-first stages are implemented and independently reviewed in Normal Chat:

- Documentation consolidation: `development @ 2149a21e827c27a741d5291a4f5b1159b685c68b` — one maintained COLLISION_REFERENCE, complete archived former-authority/pre-change DESIGN snapshots, and corrected ownership/navigation. The original archive identities are recorded in EVIDENCE_PATH_MIGRATIONS.
- Completed derived-evidence archival: `development @ 975c7e2a1b17b47133a19f8091f158956a7de6b1` — 27 unchanged package subtrees and three unchanged manual checkpoints moved to preserved archives. Independent Git subtree/blob comparison confirms the complete frozen moved set and 462 unchanged pre-existing canonical archive entries; Work reports manifest, retrieval and structural checks passing. The historical mirror-index byte-count discrepancy remains a known limitation, not permission to rewrite provenance.

Third stage reviewed/accepted: **Practical Knowledge & Engineering Principles**, frozen from `development @ 6d224946490e424a91d5109d883a9fdb04595503`, published as `2f13fecf95d14d1819a64eaf233705be696ca1b8`. It improves existing user/agent navigation, the twelve-ADR status index, plain-language raw8 explanation, engineering-review connection and accurate retained-tool descriptions. Independent Normal Chat review found no blocking problem; full link/validator PASS is Work-reported, with important routes/source claims checked independently. ENGINEERING_GUIDE and every individual ADR remain unchanged.

KA-11 historical INI/Movement-seed archival was approved from `development @ 266ef970be17caff721aaac7987ba787e29e1e18` and published at `0288c3fc5d39c2e9ed02d3b978bf203c8fcff0f1`. Independently reviewed/accepted 2026-10-09: both complete originals match their archived Git blobs; the remaining Recover/timeout-pause research bodies are identical apart from heading numbers. [KA-11 path migrations](../../EVIDENCE_PATH_MIGRATIONS.md#ka-11-historical-configuration-and-movement-seed) owns retrieval. Current shipping INI and Movement authorities are unchanged; Work-reported link/validator checks passed, not independently rerun.

KA-10 Optional Research Build Defaults was approved from `development @ ed88e73e2bb884d0aa83199510b9b069cf2e6e69`, published as `4cd3c2d9e04ecf484bb7939f697649f693de5f30` and independently reviewed/accepted 2026-10-09. Exact CMake diff changes only the two research-group defaults to `OFF`; all research targets, diagnostic variants and protected subtree identities are preserved, production remains unconditional. README/POP-02 explain opt-ins and cached values. Static proof only; configure/build/runtime not attempted.

**Current gate: User-approved KA-12 direction, separately frozen before implementation.** The accepted KA-10 stage is closed; KA-12 will only extend the existing validator/maintenance routes within a bounded Work brief, not start automatically. Retained-tool descriptions do not authorize tool/build changes. The independent `main` comparison still follows final reviewed maintenance as its own bounded task. Do not begin further implementation, feature work, runtime tests or the independent comparison from this pointer. `main` remains protected at `08a0bd8fcf42173088e233e09b706a80da882070`; production source/configuration, all other CMake files and evidence are unchanged; no new EV or runtime fact.

This document remains ACTIVE because later authorized maintenance decisions and the mandatory independent `main` versus post-maintenance `development` loss-detection/reconciliation are unfinished. Normal Chat owns final closure/archive of this document only after that sequence has concluded.

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

The documentation consolidation, derived-evidence archival, Practical Knowledge & Engineering Principles, KA-11 archival and KA-10 optional research builds stages are completed/reviewed. KA-12 is next separately; further Work requires a newly frozen scope.

That task may implement **only the approved audit maintenance** on `development`.

Do not modify stable `main`.

### Phase 5 — Normal Chat post-audit review

The first five stages have been independently reviewed at the checkpoints recorded above. Review the separately bounded KA-12 implementation before advancing.

The final post-maintenance development checkpoint must be explicit before the independent comparison task.

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

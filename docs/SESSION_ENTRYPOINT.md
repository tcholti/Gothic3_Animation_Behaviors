# Session Entry Point

**Purpose:** minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `development`  
**Stable integration branch:** `main`  
**Updated:** 2026-10-09

> After abrupt/max-context recovery, return to root `README.md` and apply POP-11 before trusting this pointer.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate — Normal Chat review of Practical Knowledge & Engineering Principles

Collision, Speed, Raise, Movement and narrow player bad-block protection remain CLOSED/PASS. First-release checkpoint review EV-455, quick documentation review EV-456 and stable promotion EV-457 are complete. No feature/research task is active.

Protected stable baseline: `main @ 08a0bd8fcf42173088e233e09b706a80da882070`.

Accepted production DLL from EV-454 final smoke (recorded provenance, not remeasured here):
`SHA256 9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`.

The first documentation-consolidation stage was reviewed and accepted at `development @ 2149a21e827c27a741d5291a4f5b1159b685c68b`. The second, archival-only stage was published at `975c7e2a1b17b47133a19f8091f158956a7de6b1` and independently reviewed in Normal Chat on 2026-10-08: all 27 moved package subtrees have matching original Git tree identities; all three manual checkpoint blobs match; all 462 pre-existing canonical archive entries are unchanged. Work reported manifest/retrieval/static validation PASS, with a historical mirror-index byte-count discrepancy preserved rather than silently corrected. This review does not assert independently recomputed raw-source SHA256 or runtime validation. Both maintenance stages are accepted as reviewed checkpoints. Production source/configuration/build/runtime behavior is unchanged.

The third bounded documentation stage, **Practical Knowledge & Engineering Principles**, was approved from `development @ 6d224946490e424a91d5109d883a9fdb04595503`. It adds concise user/agent usability checks, current-question and decision navigation, a raw8 plain-language lead, targeted engineering-principle review and truthful retained-tool descriptions. The engineering guide, individual ADRs, source/tools/prototypes/configuration and preserved evidence are unchanged. The published stage checkpoint is the commit containing this update; the Work handoff supplies its full remote SHA.

**Immediate responsibility:** Normal Chat independently reviews this documentation-only stage against the frozen brief and static/navigation checks. Work stops here. KA-10 research build defaults, KA-11 historical configuration/Movement seed and broader optional KA-12 automation still require separate authorization. After approved maintenance is complete and reviewed, the separate independent `main`→`development` semantic loss-detection task and Normal Chat reconciliation remain mandatory. No build, runtime work or `main` promotion is authorized by this pointer.

The open sequence remains owned by [POST_RELEASE_AUDIT_PREPARATION.md](work/active/POST_RELEASE_AUDIT_PREPARATION.md). It stays active for remaining User decisions, eventual maintenance review and the independent comparison/reconciliation; the whole post-release audit cycle is not closed.

## Smallest technical routes

| Responsibility | Start with; broaden conditionally |
|---|---|
| Accepted collision / C1 / raw8 / raw55 / Sprint / reopening | [COLLISION_REFERENCE](COLLISION_REFERENCE.md) §§1–7 → named source; §8 only for specific proof/depth. |
| Profiles / Speed / Raise / Movement | [DESIGN](DESIGN.md) §§2–3 → named source and shipping INI; animation rules §5.1 for Raise assets. |
| Player bad-block scope | DESIGN §9 → hook guide §6 / ADR-0012 when changing the contract. |
| Exact engine/hook fact | [SOURCE_HOOK_GUIDE](SOURCE_HOOK_GUIDE.md) local subsection. |
| Proof / preserved historical path | [EVIDENCE_INDEX](EVIDENCE_INDEX.md) → exact EV; [path migrations](EVIDENCE_PATH_MIGRATIONS.md) for moved originals. |

Active evidence ledger: `EVIDENCE_LEDGER_455_ONWARD.md`; no new EV is created for editorial maintenance. [The archival migration record](EVIDENCE_PATH_MIGRATIONS.md#2026-10-08--completed-derived-evidence-archival) owns recovery of former package/checkpoint paths. The seven collision snapshots and pre-change DESIGN remain preserved from the reviewed first stage. Routine feature re-entry starts from current owners and source.

## Still frozen

Preserve native fallback, exact source/C1 identity and one physical hook owner. No `+0x42A0` entry takeover, New Balance value as native calibration, unproven Sprint keys, collision redesign or Raise resurrection. No climbing implementation. Runtime products/fixtures follow release architecture and POP-03, including physical removal of excluded DLLs from `scripts`.

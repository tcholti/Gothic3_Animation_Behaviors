# Session Entry Point

**Purpose:** minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `development`  
**Stable integration branch:** `main`  
**Updated:** 2026-10-09

> After abrupt/max-context recovery, return to root `README.md` and apply POP-11 before trusting this pointer.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate — KA-10 reviewed/accepted; prepare separately bounded KA-12

Collision, Speed, Raise, Movement and narrow player bad-block protection remain CLOSED/PASS. First-release checkpoint review EV-455, quick documentation review EV-456 and stable promotion EV-457 are complete. No feature/research task is active.

Protected stable baseline: `main @ 08a0bd8fcf42173088e233e09b706a80da882070`.

Accepted production DLL from EV-454 final smoke (recorded provenance, not remeasured here):
`SHA256 9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`.

The first documentation-consolidation stage was reviewed and accepted at `development @ 2149a21e827c27a741d5291a4f5b1159b685c68b`. The second, archival-only stage was published at `975c7e2a1b17b47133a19f8091f158956a7de6b1` and independently reviewed in Normal Chat on 2026-10-08: all 27 moved package subtrees have matching original Git tree identities; all three manual checkpoint blobs match; all 462 pre-existing canonical archive entries are unchanged. Work reported manifest/retrieval/static validation PASS, with a historical mirror-index byte-count discrepancy preserved rather than silently corrected. This review does not assert independently recomputed raw-source SHA256 or runtime validation. Both maintenance stages are accepted as reviewed checkpoints. Production source/configuration/build/runtime behavior is unchanged.

The third bounded documentation stage, **Practical Knowledge & Engineering Principles**, was approved from `development @ 6d224946490e424a91d5109d883a9fdb04595503`. It adds concise user/agent usability checks, current-question and decision navigation, a raw8 plain-language lead, targeted engineering-principle review and truthful retained-tool descriptions. The engineering guide, individual ADRs, source/tools/prototypes/configuration and preserved evidence are unchanged. The published third-stage checkpoint is `development @ 2f13fecf95d14d1819a64eaf233705be696ca1b8`, independently reviewed and accepted in Normal Chat on 2026-10-09. Review confirmed the exact nine-document scope, all twelve ADR entries, native-versus-persistent raw8 accuracy, targeted engineering-principle link and retained research-tool descriptions. ENGINEERING_GUIDE, individual ADRs, source, configuration, CMake and evidence remain unchanged. Work reports full link/validator PASS; Normal Chat independently checked the important new targets and relevant source contracts without re-running the whole validator.

KA-11 historical configuration/Movement-seed archival was implemented at `development @ 0288c3fc5d39c2e9ed02d3b978bf203c8fcff0f1` and independently reviewed/accepted in Normal Chat on 2026-10-09. Both original archives have identical Git blob identities; the Recover-cancellation and exact-pause bodies match their prior versions with headings renumbered; completed Movement was removed from the future list. [KA-11 path migrations](EVIDENCE_PATH_MIGRATIONS.md#ka-11-historical-configuration-and-movement-seed) records exact recovery. Shipping INI, current DESIGN/SOURCE_HOOK owners, engineering principles, tools, prototypes and CMake remain unchanged. Work reports full links/static validator PASS; those checks were not independently rerun.

KA-10 Optional Research Build Defaults was published at `development @ 4cd3c2d9e04ecf484bb7939f697649f693de5f30` and independently reviewed/accepted in Normal Chat on 2026-10-09. Only two root CMake option defaults change to `OFF`; production remains unconditional and the six diagnostic tool targets, two collision twins, deep-diagnostic setting, tool/prototype source and protected Git subtrees remain unchanged. README/POP-02 now document deliberate opt-ins and existing-cache behavior. Work reports full link/knowledge validation PASS; Normal Chat verified exact CMake equivalence and Git tree identities, but did not configure, build or run Gothic 3.

**Immediate responsibility:** KA-12 is the next User-approved maintenance direction, but only under a fresh, separately bounded Work brief after reviewing the existing validator. No KA-12 implementation is in progress. After KA-12 review, launch the separate independent `main`→`development` semantic loss-detection task and reconcile genuine loss. Do not build, run Gothic 3, start other Work, or promote `main` from this pointer.

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

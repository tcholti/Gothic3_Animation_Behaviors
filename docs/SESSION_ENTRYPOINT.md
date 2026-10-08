# Session Entry Point

**Purpose:** minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `development`  
**Stable integration branch:** `main`  
**Updated:** 2026-10-08

> After abrupt/max-context recovery, return to root `README.md` and apply POP-11 before trusting this pointer.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate — Normal Chat review of documentation consolidation

Collision, Speed, Raise, Movement and narrow player bad-block protection remain CLOSED/PASS. First-release checkpoint review EV-455, quick documentation review EV-456 and stable promotion EV-457 are complete. No feature/research task is active.

Protected stable baseline: `main @ 08a0bd8fcf42173088e233e09b706a80da882070`.

Accepted production DLL from EV-454 final smoke (recorded provenance, not remeasured here):
`SHA256 9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`.

The two read-only audits and User/Normal Chat decision review led to the first approved documentation-only maintenance stage, entered at `development @ fb61c6bedf84bae239610b2c37c205580a7fc63f`. This stage consolidates collision knowledge and corrects bounded stale routes; it changes no production source/configuration/build/runtime behavior. Its commit is the current development documentation-consolidation checkpoint; BETWEEN_CHATS and the Work handoff identify review details.

**Immediate responsibility:** Normal Chat reviews the published documentation diff against the frozen contract before accepting this stage. Do not launch further maintenance, the independent main comparison, new runtime tests or main promotion from this pointer.

The open sequence remains owned by [POST_RELEASE_AUDIT_PREPARATION.md](work/active/POST_RELEASE_AUDIT_PREPARATION.md). It stays active pending review and later decisions; the whole post-release audit cycle is not closed.

## Smallest technical routes

| Responsibility | Start with; broaden conditionally |
|---|---|
| Accepted collision / C1 / raw8 / raw55 / Sprint / reopening | [COLLISION_REFERENCE](COLLISION_REFERENCE.md) §§1–7 → named source; §8 only for specific proof/depth. |
| Profiles / Speed / Raise / Movement | [DESIGN](DESIGN.md) §§2–3 → named source and shipping INI; animation rules §5.1 for Raise assets. |
| Player bad-block scope | DESIGN §9 → hook guide §6 / ADR-0012 when changing the contract. |
| Exact engine/hook fact | [SOURCE_HOOK_GUIDE](SOURCE_HOOK_GUIDE.md) local subsection. |
| Proof / preserved historical path | [EVIDENCE_INDEX](EVIDENCE_INDEX.md) → exact EV; [path migrations](EVIDENCE_PATH_MIGRATIONS.md) for moved originals. |

Active evidence ledger: `EVIDENCE_LEDGER_455_ONWARD.md`; no new EV is created for editorial maintenance. The seven original collision documents and pre-change DESIGN are archived content-identically with source identities in the migration map. Routine feature re-entry requires no archived investigation.

## Still frozen

Preserve native fallback, exact source/C1 identity and one physical hook owner. No `+0x42A0` entry takeover, New Balance value as native calibration, unproven Sprint keys, collision redesign or Raise resurrection. No climbing implementation. Runtime products/fixtures follow release architecture and POP-03, including physical removal of excluded DLLs from `scripts`.

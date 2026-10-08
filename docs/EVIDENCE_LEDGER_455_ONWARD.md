# Gothic 3 Animation Behaviors — Evidence Ledger EV-455 Onward

**Status:** Active evidence/provenance ledger  
**Opened:** 2026-10-08

## Purpose

Record evidence after the closed EV-417–EV-454 first-release integration volume.

This ledger is proof history, not the normal knowledge interface. Established facts belong in their current reference/architecture owners; `EVIDENCE_INDEX.md` routes proof-sensitive retrieval.

## Entries


### EV-455 — First-release checkpoint review READY

Observed:
- reviewed `development @ 99ed4ac0b4883a082340c3eee41ae67ec69cb92a` against stable `main @ e899f37092706a9846312b93d6b52b34e715b53d`;
- `main` is an exact ancestor of the reviewed development checkpoint;
- only production-source delta is `src/Script_G3AnimationBehaviors/EngineBridge.cpp`;
- production INI is unchanged from stable main;
- no compiled binary/archive is tracked in the branch delta;
- raw intake contains only `Keep.txt`;
- public/integration product remains `Script_G3AnimationBehaviors.dll`;
- accepted built/live production SHA256 remains `9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`;
- knowledge-state validation PASS and current worktree clean.

Maintenance performed before verdict:
- corrected stale root README current-product routing;
- rotated closed EV-417–EV-454 ledger to archive and opened EV-455 onward.

Limits:
- this is a repository/release checkpoint review, not a new gameplay validation campaign;
- promotion to main is deliberately not automatic.

Disposition:
- **READY FOR MAIN PROMOTION / FIRST RELEASE CHECKPOINT.**


### EV-456 — Quick pre-promotion documentation review PASS

Reviewed documentation checkpoint:
`development @ 8d42e9fc9de1e6c07bc6dbbf6972d921804474c2`

Scope:
- deliberately shallow pre-promotion review only;
- current-state/release wording;
- stale active-task/current-feature claims;
- broken active/archive routes;
- contradictions with EV-454/EV-455;
- no broad authority, duplication, compression or repository-structure audit.

Corrections made:
- root README now routes the current decision to first-release main promotion and includes Movement/bad-block surfaces;
- canonical `DESIGN.md` no longer says Raise is active or attack displacement/bad-block protection are future-only;
- accepted Movement architecture is represented in `DESIGN.md`;
- accepted EV-449–EV-454 stateless player bad-block architecture replaces the obsolete future-module concept;
- `PROJECT_PIPELINE.md` now reflects the promoted EV-447 Collision/Speed/Raise/Movement baseline and the current first-release promotion gate;
- `FUTURE_INVESTIGATIONS.md` marks Movement resolved/production-integrated and keeps only exact-pause/NPC bad-block questions as optional future research;
- top-level `SOURCE_HOOK_GUIDE.md` movement rows now agree with the closed §3B mechanism;
- stale current-qualification text in ADR-0006/ADR-0008 was refreshed without rewriting their preserved historical decision bodies;
- two old `docs/work/active/` ADR links were repointed to their archived task locations;
- `SESSION_ENTRYPOINT.md` date/frozen-state wording now matches the release checkpoint.

Verification:
- no live non-archive `docs/work/active/<task>.md` references remain;
- `docs/work/active/` contains only its README placeholder;
- remaining historical "Speed active / Raise follows" wording is inside the explicitly preserved historical ADR-0006 decision body;
- `git diff --check` PASS on the review changes;
- knowledge-state validation PASS;
- no release/product code or INI change was made.

Disposition:
- **PASS — DOCUMENTATION IS CLEAN ENOUGH FOR FIRST-RELEASE MAIN PROMOTION.**
- larger documentation/repository review remains intentionally deferred until after the stable main checkpoint is created.

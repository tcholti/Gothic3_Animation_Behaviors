# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-08 — EV-454 final release-candidate smoke PASS / first-release checkpoint review ACTIVE

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`
Stable main: `e899f37092706a9846312b93d6b52b34e715b53d`
Active branch: `development`

## First-release candidate state

Collision = CLOSED/PASS.
Speed = CLOSED/PASS.
Raise = CLOSED/PASS.
Movement = CLOSED/PASS.
Bad-block protection = CLOSED/PASS through EV-454.

Bad-block production source:
`65a87e4e792e3da631856ae341df713742aac0db`

Accepted production DLL:
`SHA256 9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`

EV-454 final runtime smoke:
- repeated Quick/full-Whirl bad-skip attempts: clean;
- 2H Normal Speed override: clean;
- 2H Normal/Quick/Whirl Raise: clean;
- 2H Normal/Quick Movement override: clean;
- 1H Normal Speed 1.0 + authored collision-marker contact: clean;
- ordinary gameplay looked normal.

Bad-block work is finished for first release. Do not reopen without contradictory reproducible evidence.

## Active gate

`docs/work/active/FIRST_RELEASE_CHECKPOINT_REVIEW.md`

Read-only responsibility:
- reconcile current `development` against frozen `main`;
- confirm intended shipping surface and release purity;
- confirm default INI/help/current-state documentation;
- run repository/knowledge checks;
- return READY FOR MAIN PROMOTION / FIRST RELEASE CHECKPOINT, or smallest concrete blocker.

Do not add features during this review.
Do not promote to `main` automatically; promotion remains an explicit User + Normal Chat decision.

# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-08 — EV-455 first-release checkpoint review PASS / promotion decision pending

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`
Stable main: `e899f37092706a9846312b93d6b52b34e715b53d`
Active branch: `development`

## First-release checkpoint

EV-454:
- production bad-block integration PASS;
- final release-candidate gameplay smoke PASS;
- Collision, Speed, Raise, Movement and integrated bad-block protection all behaved normally.

EV-455:
- first-release repository/checkpoint review PASS;
- reviewed `development @ 99ed4ac0b4883a082340c3eee41ae67ec69cb92a`;
- stable main is an exact ancestor;
- only production-source delta from main is the accepted `EngineBridge.cpp` bad-block integration;
- production INI unchanged from main;
- no tracked binary/archive delta;
- raw intake clean;
- knowledge-state validation PASS;
- root README routing corrected;
- evidence ledger rotated: EV-417–454 archived, EV-455 onward active.

Accepted production DLL from final smoke:
`SHA256 9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`

## Current decision

**READY FOR MAIN PROMOTION / FIRST RELEASE CHECKPOINT.**

No feature/research task is active.

Do not promote automatically.
Promotion to `main` requires explicit User + Normal Chat approval.

After promotion, continue future feature work from `development`; do not reopen closed first-release systems without contradictory evidence.

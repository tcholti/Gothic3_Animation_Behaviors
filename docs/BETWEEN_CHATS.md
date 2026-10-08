# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-08 — EV-457 first-release promotion PASS / larger audit preparation pending

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`
Stable main: `08a0bd8fcf42173088e233e09b706a80da882070`
Active branch: `development`

## First-release stable checkpoint

EV-454:
- production bad-block integration PASS;
- final release-candidate gameplay smoke PASS;
- Collision, Speed, Raise, Movement and integrated bad-block protection all behaved normally.

EV-455:
- first-release repository/checkpoint review PASS.

EV-456:
- quick pre-promotion documentation/current-route review PASS;
- stale current-state architecture and broken historical routes corrected;
- no production code or INI changes.

EV-457:
- `development @ 08a0bd8fcf42173088e233e09b706a80da882070` was fast-forward promoted to `main`;
- remote `main` and `development` matched exactly at promotion;
- this SHA is the trusted first-release pre-audit comparison baseline.

Accepted production DLL from final smoke:
`SHA256 9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`

## Current state

No feature/research task is active.

The next larger review/audit has **not** been frozen yet.

Before launching it, the User will identify documentation that should receive special attention. Normal Chat should incorporate those priorities into the audit contract.

During the later audit:
- work only on `development`;
- keep `main @ 08a0bd8fcf42173088e233e09b706a80da882070` untouched as the trusted first-release baseline;
- after the audit and Normal Chat review, perform a deliberate loss-detection comparison of audited `development` against stable `main`.

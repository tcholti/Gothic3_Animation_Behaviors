# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-08 — first-release main frozen / post-release audit plan recorded / User priorities next

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`
Stable main: `08a0bd8fcf42173088e233e09b706a80da882070`
Active branch: `development`

## Stable release baseline

`main @ 08a0bd8fcf42173088e233e09b706a80da882070`
= accepted first-release baseline before the large audit.

It is the protected comparison baseline, not the working branch.

Accepted production DLL from final smoke:
`SHA256 9FD6962146DD8BC7A723B57C0DE9DF4F550BF18E236F71FC79791B1A0ECCCEE9`

Release closure:
- Collision = CLOSED/PASS;
- Speed = CLOSED/PASS;
- Raise = CLOSED/PASS;
- Movement = CLOSED/PASS;
- bad-block protection = CLOSED/PASS;
- EV-455 release checkpoint review = PASS;
- EV-456 quick documentation/current-route review = PASS;
- EV-457 first-release promotion to `main` = PASS.

## Current branch

Continue on `development`.

Pre-audit development is the first-release lineage plus post-promotion/audit-preparation documentation. It need not remain byte-identical to `main`; `main` is the frozen semantic/reference snapshot.

No feature/research task is active.

## Required next step — User priorities first

Do **not** launch the large audit yet.

The User will first point out documentation/knowledge areas that deserve special attention or protection. Normal Chat must incorporate those concerns into the audit brief before Work is tasked.

## Frozen audit sequence

1. **User priorities**
   - collect the specific documentation/knowledge concerns from the User.

2. **Work — read-only large review/audit**
   - start repository-first and apply the formal authority/review procedures;
   - inspect architecture/document authority/current-state/release remnants/tooling/evidence routing/bloat/stale material plus the User-named areas;
   - produce findings and proposed actions;
   - do not freely restructure, delete, archive or compact material.

3. **Normal Chat + User decision review**
   - review Work's findings together;
   - explicitly decide `KEEP / CHANGE / ARCHIVE / REMOVE`;
   - protect contextual material a static audit might misunderstand.

4. **Work — approved maintenance implementation**
   - implement only the changes approved in Normal Chat;
   - remain on `development`;
   - do not modify stable `main`.

5. **Normal Chat post-audit review**
   - review the resulting `development` state before treating the audit as accepted.

6. **Work — independent main-vs-development loss-detection comparison**
   - use stable `main @ 08a0bd8fcf42173088e233e09b706a80da882070` as the trusted pre-audit first-release knowledge snapshot;
   - compare it against reviewed post-audit `development`;
   - identify anything materially useful, authoritative, operationally important or historically necessary that existed on `main` but is missing, weakened, ambiguously relocated or semantically altered on `development`;
   - do not report deletion/compression as loss when the same responsibility is still represented correctly by an appropriate owner.

7. **Normal Chat final reconciliation**
   - review the loss-detection findings;
   - repair any genuine loss before accepting the audited development state.

## Comparison model

```text
MAIN
= accepted first-release baseline before large audit
= 08a0bd8fcf42173088e233e09b706a80da882070

DEVELOPMENT pre-audit
= first-release lineage
+ post-promotion / audit-preparation documentation
= audit starting state

DEVELOPMENT post-audit
= reviewed/refactored repository state
after approved audit maintenance
```

Do not modify or re-promote `main` during this audit/comparison cycle unless the User explicitly authorizes it.

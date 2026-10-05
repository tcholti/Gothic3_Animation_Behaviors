# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — EV-433 stable promotion completed

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`

## Stable checkpoint

```text
Collision = CLOSED/PASS
Speed v2 = CLOSED/PASS
Raise = CLOSED/PASS / well tested
final source review = PASS EV-431
repository release audit = PASS EV-432
main promotion = PASS EV-433
```

`main` now owns the deliberately promoted stable Collision + Speed + Raise baseline.

New engineering continues on `development`.

## Next responsibility

Research/design only:

**Attack forward displacement / how far attacks may move the character.**

Start from:
1. Gothic native displacement ownership/mechanism;
2. exact New Balance changes for Normal and Quick attacks;
3. compatibility/composition behavior;
4. profile/config design only after ownership is known.

Protect accepted Collision, Speed and Raise behavior.

Do not implement displacement before research closes.

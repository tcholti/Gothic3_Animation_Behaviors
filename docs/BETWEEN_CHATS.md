# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-05 — stable promotion checkpoint approved

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`

## Closed release gates

```text
Collision = CLOSED/PASS
Speed v2 = CLOSED/PASS
Raise = CLOSED/PASS through EV-430
final independent Speed+Raise source review = PASS EV-431
quick repository/authority release audit = PASS EV-432
```

EV-431:
- blocker 0 / major 0 / minor 0;
- New Balance compatibility PASS;
- AttackCollision compatibility PASS;
- Collision non-interference PASS;
- hook/profile/performance/source architecture PASS.

EV-432:
- authority topology coherent;
- no active temporary task remains after review closure;
- evidence/current-state sizes healthy;
- research/raw contains no open evidence;
- `main` is an ancestor of `development` with no divergence;
- repository is suitable for deliberate stable promotion.

## Immediate operation

Promote the accepted `development` checkpoint to `main`.

After promotion, continue new work only on `development`.

## Next engineering responsibility after promotion

Research/design only:

**Attack forward displacement / how far an attack may move the character.**

First questions:
1. identify Gothic's native displacement owner/mechanism;
2. identify exact New Balance changes for Normal and Quick attacks;
3. determine whether displacement can preserve compatible/native modifiers rather than replacing a final result;
4. determine configuration/profile shape only after mechanism ownership is understood;
5. protect accepted Collision, Speed and Raise behavior.

Do not implement displacement before research closes.

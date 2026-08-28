# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Reviewed Work result — Step B6-C3 factual empty-Primary successor stack diagnostic

**Date:** 2026-08-28
**Branch:** `docs/collision-source-evidence`
**Implementation commit:** `9f99d3d43a66321a9a0ddbc1df882d6daee6dddd`
**Independent Normal Chat review:** PASS

### Verified source change

- The existing player/type-0 empty-Primary PlayMotion probe now gates only on an available Primary snapshot with no motion instance.
- The obsolete Normal attack-family predicate was removed without replacement by another semantic/cause gate.
- The helper/record now uses factual `EMPTY-PRIMARY SUCCESSOR STACK` terminology.
- Runtime banner now reports `UNGATED EMPTY-PRIMARY SUCCESSOR`.
- Existing 16-frame stack capacity and factual context capture are unchanged.
- Original PlayMotion remains called exactly once with unchanged arguments/order.
- The post-original record still requires a real installed successor Primary instance and reports its name factually.
- Direct replacement, PrimaryFirst, StopMotion, StartRecover and B4/B5 cleanup diagnostics are preserved.
- No new hook, production behavior, lifecycle state, timer, polling, scan, cache, classifier, collision-group gate, successor-name gate or guessed layout was introduced.
- Collision, marker, callback and bookkeeping behavior is unchanged.

### Next responsibility

1. Fast-forward the authoritative home checkout.
2. Build `Script_FrameCollisionTest`.
3. Deploy the rebuilt DLL to the authoritative Gothic 3 `scripts` path and verify hash / single active matching DLL.
4. Load Gothic 3 and verify the revised `UNGATED EMPTY-PRIMARY SUCCESSOR` banner.
5. Run a short controlled legitimate player 2H Normal interruption fixture.
6. Preserve the raw log under the exact filename supplied by Normal Chat and push it.
7. Normal Chat compares factual Stumble/KnockDown successor stacks with EV-176 before B6-D.

No source change for the broader attack-lifecycle/"package" hypothesis is frozen yet. That idea remains a Normal Chat research hypothesis until the B6-C3 runtime result shows which additional control-flow facts are actually missing.

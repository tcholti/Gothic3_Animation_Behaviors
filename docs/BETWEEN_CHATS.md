# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest assignment

**From:** Normal Chat / Step B1 runtime analysis  
**To:** Work  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

## Step B1 result — RUNTIME PASSED / RESEARCH QUESTION ANSWERED

Step B1 source commits:

- `7dcd514b0bcd51c05453e3e55500a927b9063159` — PrimaryFirst event probe;
- `81e88026a4b47086a8995ab65d2933a041f8d2fd` — namespace fix.

Home-PC build and runtime test succeeded without crash. The test covered 2H Normal, Quick, clean Whirl, and two reproduced Whirl skip/stale-collision cases.

Important runtime findings:

- `eCVisualAnimation_PS::PlayMotion(type 0)` reports real PrimaryFirst Hit acquisition and successor/replacement immediately.
- In the two reproduced stale Whirl cases, the successor `PlayMotion` appeared roughly 0.51–0.66 seconds before the old Script `OnTick` lifetime probe noticed the mismatch.
- The `PlayMotion` before-snapshot is often already empty, so outgoing execution identity must come from previously acquired state rather than the hook's before-snapshot.
- `StopMotion(type 0)` is supporting evidence only; it did not provide the authoritative skipped-Whirl replacement signal.
- In clean 2H Normal, Quick, and Whirl transitions, successor Recover `PlayMotion` occurred first and native weapon cleanup `Item_Attack 7 -> Item_Equipped 5` followed about 0.059–0.062 ms later, effectively within the same transition/update.
- Therefore future cleanup must **not** fire immediately inside the successor `PlayMotion` hook; Gothic 3 must first get its normal same-transition opportunity to clean up.
- The global PrimaryFirst hooks are very noisy. Do not broaden logging; future diagnostics should be narrowly filtered/correlated.

Current open causal question:

> After successor PrimaryFirst starts, does the native `7 -> 5` cleanup occur inside the existing original attack-family callback (`OnAI_Attack`, `OnAI_QuickAttack`, or `OnAI_WhirlAttack`)?

If yes, the return from that original callback is a promising natural point at which Gothic 3 has already had its cleanup opportunity, avoiding a timer or world-lifetime polling loop.

## Bounded Work task — Step B2 original-callback boundary probe

Implement **diagnostic-only logging around the existing calls to Gothic 3's original attack-family callbacks** in:

- `OnAI_Attack_FrameCollisionTest`
- `OnAI_QuickAttack_FrameCollisionTest`
- `OnAI_WhirlAttack_FrameCollisionTest`

### Required behavior

1. **Do not add any new engine/script hook.** Reuse the three callbacks already owned by `Script_FrameCollisionTest.cpp`.
2. Preserve the current marked-Hit suppression path exactly. If the current code suppresses the original callback, continue returning exactly as before.
3. On a path that will call the original callback:
   - for the controlled diagnostic, log only when `SelfEntity == Entity::GetPlayer()` so the small runtime test is not flooded by unrelated actors;
   - immediately before calling the original, capture/log a high-resolution timestamp and PrimaryFirst snapshot using the existing diagnostic snapshot machinery;
   - identify the callback family (`Normal`, `Quick`, or `Whirl`) and label the record as original-callback **BEGIN**;
   - call the original callback exactly once with the same arguments;
   - immediately after it returns, capture/log another timestamp and PrimaryFirst snapshot and label the record as original-callback **END**;
   - return the original result unchanged.
4. Include only small useful context already available cheaply: actor identity/name, callback family, current Action, AniPhase/current movement animation, and the PrimaryFirst snapshot. Do not add a new collision-source table; the existing `SetCollisionGroup` hook already supplies the collision event and timestamp we need for correlation.
5. Add **no persistent lifecycle state**, pending-end state, cleanup behavior, timer, polling, attack-family special case, or production decision.
6. Keep Step B1 `PlayMotion`/`StopMotion` probes and the old `OnTick` comparator unchanged for this test.
7. Collision control must remain independent of diagnostics.

### Research acceptance question

The resulting log must let Normal Chat determine, for clean and skipped Whirl transitions, whether a native `SetCollisionGroup(...5)` cleanup event falls chronologically between:

```text
ORIGINAL CALLBACK BEGIN
    ... Gothic 3 original callback ...
ORIGINAL CALLBACK END
```

after the successor PrimaryFirst `PlayMotion` event.

Do not infer the answer in source code and do not change behavior based on it.

### Scope / stop rule

This is one diagnostic probe only. Do not redesign lifecycle ownership, remove the old probes, implement cleanup, or investigate unrelated speed/Raise code.

Do not build or run Gothic 3 in Work. Commit and push the source change, overwrite this file with a concise Work-to-Chat result including commit SHA, then **STOP**.

# ADR-0012 — Bad Block Skip Attack-Protection Contract

**Status:** Accepted  
**Date:** 2026-10-07  
**Related:** EV-185–EV-198, EV-448, `docs/SOURCE_HOOK_GUIDE.md §6`

## Context

The known bad block-skip path can tear down engine-side attack continuation while the visible attack animation continues playing.

After the collision lifecycle fix, stale offensive collision is correctly repaired/retired. That prevents lingering collision state, but it can expose a gameplay mismatch:

```text
visible attack animation continues
+ weapon visually connects
+ native attack continuation was already destroyed
-> no normal hit/damage outcome
```

This is visually confusing and gameplay-negative.

EV-448 researched a stronger requirement: mathematically pause the underlying block timeout and later resume with the exact remaining time. That exact-pause contract requires new stateful timer-episode ownership and was correctly classified as not clean enough for first release.

The stronger contract is not necessary to solve the gameplay problem.

## Decision

### 1. First-release requirement is attack protection, not exact timer preservation

For v1, it is sufficient to prevent the destructive block-timeout branch from tearing down a live factual attack.

The timeout may continue advancing internally.

Once the protected attack has safely ended, it is acceptable for the already-due timeout to fire immediately.

Example:

```text
block timeout becomes due during attack
-> defer destructive block skip
-> attack continues normally
-> native cleanup gets its ordinary opportunity
-> after attack is no longer protected, timeout may fire immediately
```

Exact remaining-time pause/resume is explicitly **not required** for v1.

### 2. Preserve collision safety

The collision guardian remains responsible for collision-state convergence if an abnormal teardown still occurs.

Attack protection does not weaken, replace or bypass collision cleanup.

### 3. Player stateless deferral is a valid candidate again

EV-448 recovered the exact player seam:

```text
Script_Game +0x633BF DurationPressedMSecs getter
+0x633C5 compare 2500
+0x633CA jbe bypass
otherwise:
+0x633F1 FullStop
+0x63409 SetState PS_Melee_Loop
```

A branch-local adapter that preserves the original getter once and returns a non-destructive threshold value only while the bound actor is factually attacking is a valid candidate under this revised contract.

Whether it belongs in the main DLL or an optional compatibility DLL remains an open product/packaging decision.

### 4. NPC timeout remains separate

EV-448 proved a separate Alternative-AI NPC parade timeout:

```text
StatePosition == 1
StateTime > 2.0
-> StopAIGoto
-> SetState ZS_Attack_Loop
```

It does not share the player's timer or call site.

Whether that NPC timeout can destructively overlap a live attack remains an evidence question. Do not assume either that NPCs are safe or that the player fix covers them.

### 5. Product/architecture decision stays with User + Normal Chat

Delegated research may recommend against an option, but unless explicitly delegated it does not decide that an imperfect solution is unacceptable.

For this feature, compare at least:
- integrated G3AB player deferral;
- optional separate bad-block-skip patch DLL;
- NPC-specific intervention only if evidence proves the same gameplay failure;
- no-change fallback.

## Consequences

- EV-448 remains valid for the exact-pause question.
- Its first-release disposition is qualified by this ADR because the v1 acceptance contract changed.
- The release-fix investigation is reopened under a smaller, stateless-deferral-friendly responsibility.
- Exact timer pause/resume is parked for future work, not required for v1.

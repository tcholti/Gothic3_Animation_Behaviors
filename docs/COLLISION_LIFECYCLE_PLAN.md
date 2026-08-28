# Collision Lifecycle Plan

**Status:** Current collision-lifecycle architecture / research authority  
**Updated:** 2026-08-28

## Purpose

Define the smallest authoritative rule that can guarantee offensive collision cleanup without creating one repair branch per attack family or interruption symptom.

Detailed proof history belongs in `EVIDENCE_INDEX.md` / the evidence ledgers. Build-specific cleanup and control-flow locations belong in `COLLISION_CLEANUP_CALLSITE_MAP.md` and `SOURCE_HOOK_GUIDE.md`.

The pre-information-architecture plan is preserved at:

`docs/archive/technical_2026-08-27/COLLISION_LIFECYCLE_PLAN_pre_ia.md`

---

## 1. Governing Invariant

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact Hit genuinely ends or is replaced, if proper cleanup already occurred, do nothing; if not, repair the remaining offensive collision using native cleanup semantics.**

How the Hit ended is not part of the production rule. Normal completion, damage/reaction interruption, state replacement, skipped Recover bookkeeping, terrain interruption and direct replacement are test cases for one lifecycle invariant.

The defect is native and broader than one animation family. An armed bad execution can lose its physical Hit and remain offensively active through Ambient/idle/movement and into a later independent attack until some later valid native cleanup occurs.

---

## 2. Preferred System — Execution-Level Native Cleanup Guard

```text
REAL ATTACK-HIT EXECUTION X BEGINS
        ↓
Acquire from native attack semantics + exact actual Hit motion
        ↓
Marked motion?
   ├─ YES → markers own collision timing inside Hit
   └─ NO  → native activation remains untouched
        ↓
Did X request offensive collision?
   ├─ NO  → no cleanup obligation
   └─ YES → remember obligation for X
        ↓
Follow exact actual Hit execution X
        ↓
X genuinely terminates / restarts / is replaced
        ↓
Allow Gothic its legitimate native cleanup opportunity
        ↓
Was X cleaned?
   ├─ YES → no-op
   └─ NO  → repair remaining offensive collision
        ↓
retire execution-level lifecycle/marker bookkeeping
```

A request counts even when the physical source is already offensive (`7 -> 7`). EV-181 proves why: a later attack can inherit stale group 7 from an earlier broken execution.

Preferred conceptual state remains:

```text
Execution X
    exact actual Hit execution identity
    collisionRequested
    nativeCleanupObserved
```

Production should remain event-driven. The final general finalization trigger is not yet chosen.

---

## 3. Three Established Ending Structures

### A — ordinary successful completion

For tested full Whirl:

```text
attack ScriptFunction reaches CombatMove break block
→ sAICombatMoveInstr persists while CombatMove is active
→ CombatMove eventually returns complete
→ suspended ScriptFunction resumes after break block
→ action-specific cleanup (+0x4E03C for tested full Whirl)
→ collision clean
```

Ordinary cleanup is Script_Game continuation after asynchronous CombatMove completion, not automatic animation teardown.

### B — legitimate damage/reaction interruption

Tested player Normal/Quick reactions:

```text
attack Hit active
→ Script_Game +0x2D0F2 calls PSRoutine::FullStop()
→ active CombatMove terminates
→ control returns through +0x2D0F8 into reaction handling
→ separate reaction cleanup +0x24AFF runs when offense had armed
→ reaction continuation owns successor
→ collision clean
```

FullStop is instruction termination, not cleanup itself.

### C — tested bad full-Whirl held-Use2 teardown

B7b resolves the tested player full-Whirl failure:

```text
Whirl ScriptFunction suspended at CombatMove break block
→ Use2 remains held beyond 2500 ms
→ Script_Game +0x633F1 calls PSRoutine::FullStop()
→ active CombatMove terminates
→ Script_Game +0x63409 calls PSRoutine::SetState(...)
→ SPU state stack / state-position / break-block bookkeeping reset
→ old Whirl ScriptFunction continuation is discarded
→ ordinary Whirl cleanup +0x4E03C cannot run
→ no reaction cleanup owner replaces it
→ armed weapon can remain Item_Attack(7)
```

Official SDK documentation states that `SetState` clears the state stack and resets state-position/break-block bookkeeping. Combined with the proven suspended Whirl continuation, this is the causal explanation for the tested stale-collision failure.

Evidence: EV-183, EV-185–EV-189.

---

## 4. Native Execution/State-Stack Authority

The native bookkeeping model now has two relevant layers:

```text
gCScriptProcessingUnit
    state stack of ScriptFunction/ScriptState break blocks
    m_pfInstrCallback
    m_fInstrPlayTime
    m_fInstrDuration


gCScriptRoutine_PS
    StateTime
    StatePosition
    CurrentBreakBlock
    Action
```

While CombatMove is active, `sAICombatMoveInstr` can persist in `m_pfInstrCallback` and the owning ScriptFunction can remain suspended in the SPU state stack.

`gCScriptRoutine_PS::AIFullStop()` invokes the current persisted instruction callback with `fullStop=true`. `AIStopCombatMove()` is narrower and does so only when that callback is exactly `sAICombatMoveInstr`.

The important B7b distinction is:

```text
FullStop alone
≠ proof cleanup should occur immediately

FullStop + state-stack replacement/destruction
= proven way an old suspended attack continuation can be lost
```

The tested Whirl `SetState` transition is therefore a strong execution-ending signal for that path, but it is not yet proven universal across other stale families.

---

## 5. Ownership Authority by Responsibility

### Attack acquisition

Use native callback/action/phase semantics to identify the relevant attack mechanism.

### Physical Hit identity

After acquisition, the exact actual PrimaryFirst Hit motion is the stronger physical execution observation. Filename/action alone must not own terminal behavior.

### Collision obligation

An actual offensive-collision request by execution X creates the cleanup obligation.

### Native cleanup observation

Observe the legitimate cleanup operation/consequence. Do not infer success because a successor animation was requested or because CombatMove was FullStopped.

### Terminal execution transition

Prefer native instruction/state-stack evidence when it proves that the suspended attack continuation can no longer resume. Do not use generic ProcessScript, action/phase, StartRecover, StopMotion or filename alone as universal finalization authority.

---

## 6. Marker Timing Remains Separate from Terminal Cleanup

Inside a live marked Hit:

```text
RIGHT = {RIGHT}
LEFT  = {LEFT}
BOTH  = {RIGHT, LEFT}
OFF   = {}
```

Each marker defines the complete desired offensive equipped-source set at that authored moment. Repeated source markers rearm through `ClearTriggeredList()`.

`G3AB_COL_OFF` is an authored inactive gap inside a still-live Hit. It is not terminal safety.

```text
WHILE HIT IS LIVE:
markers define desired offensive set.

WHEN HIT IS OVER:
offensive collision must be clean.
```

Physical collision cleanup and marker bookkeeping retirement remain separate responsibilities unless a stronger native execution boundary is later proven to own both safely.

---

## 7. Constraints Already Established by Step B

Any final design must preserve these facts:

- PrimaryFirst replacement is immediate evidence but can occur before native cleanup.
- Later original attack callbacks are not one-shot completion boundaries.
- StartRecover is too early and can be bypassed.
- Missing Recover assets are not the cause.
- Successful ordinary cleanup is action/path-specific.
- Tested legitimate reaction cleanup is a separate path.
- `RunScriptFunction`, `RunScriptState` and `ProcessScript` are generic infrastructure, not combat ownership.
- The rejected replacement-triggered deferred-ProcessScript strategy is not to be revived without new evidence.
- FullStop is not cleanup.
- The exact tested Whirl `+0x633F1 -> SetState` path is not automatically a universal stale-family rule.

Exact evidence routing: EV-158–EV-189.

---

## 8. Current Gate — Cross-Family Generality

The full-Whirl causal mechanism is resolved. The next architecture question is whether the same native **state-stack abandonment class** explains other already-proven stale families.

First target: player Dual Quick, because EV-162 already established a native stale-collision failure there.

> **Does Dual Quick bad skip also terminate its active CombatMove through the same AIFullStop/SetState route, or through another native state/task replacement that discards the suspended attack continuation?**

No new diagnostic is required for the first check. The current B7b AIFullStop observation can be reused.

Do not infer that another family uses the same `+0x633F1` call merely because the physical symptom is the same.

---

## 9. Future Marker-Core Simplification Gate

Current marker bookkeeping exists because of reproduced failures involving:

- required `StatePosition` advancement after custom ownership;
- repeated-contact occurrence handling;
- duplicate/replayed frame-effect dispatch;
- interrupted execution budgets surviving into later attacks;
- bookkeeping retirement after Gothic already performed physical cleanup.

Native CombatMove/state-stack lifetime may eventually provide stronger exact-execution identity than some current inference. Before simplifying anything, retrieve:

- EV-066–EV-075;
- EV-106–EV-116;
- EV-131–EV-133;
- EV-167;
- EV-182–EV-189;
- `EVIDENCE_INDEX.md` → Marker execution lifetime / bookkeeping.

Any simplification must preserve every established marker guarantee. The goal is less custom state only where Gothic's native lifetime is demonstrably stronger.

---

## 10. Production Implementation Gate

Production cleanup remains blocked until a general finalization mechanism is strong enough to avoid family-specific repair matrices or polling.

Do not default to:

- one cleanup hook per action family;
- cleanup at the Whirl-specific `+0x633F1` caller;
- unconditional cleanup on AIFullStop or SetState;
- unconditional cleanup on every `ProcessScript()` return;
- broad CombatMove-loop polling;
- wall-clock timers;
- block-timeout/Staff/Quick/Whirl-specific repair rules;
- action/phase-only lifetime authority;
- treating one tested state-reset path as universal before cross-family evidence.

If the native state-stack abandonment mechanism generalizes, use that evidence to design one execution-level finalization model rather than copying cause-specific branches.

---

## 11. Later Regression Requirements

Any final generic design must include negative/no-op validation for unrelated mechanics, especially:

- Fist;
- bow;
- crossbow;
- magic.

Fist is especially important because it can share melee action enums while not using the tested weapon-style `Item_Attack(7)` physical source model.

---

## 12. Preference Order

1. **Preferred:** one execution-level guard that observes/reuses Gothic's native cleanup semantics and uses a proven native terminal-execution boundary.
2. **Preferred marker direction if later proven:** replace custom lifetime inference with stronger native CombatMove/state-stack execution boundaries only where all marker guarantees survive.
3. **Fallback:** source-aware execution guard only if independent partial-source cleanup evidence requires it.
4. Avoid cause/family-specific production branches unless a real case is proven unable to fit either general model.

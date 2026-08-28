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

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if proper cleanup already occurred, do nothing; if not, repair only that execution's remaining offensive collision using native cleanup semantics.**

How the Hit ended is not part of the production rule. Normal completion, damage/reaction interruption, state replacement, skipped Recover bookkeeping, terrain interruption and direct replacement are test cases for one lifecycle invariant.

The defect is native and broader than one animation family. An armed bad execution can lose its normal ScriptFunction continuation and remain offensively active through successor Ambient/idle/movement and into a later independent attack.

---

## 2. Preferred System — Execution-Level Native Cleanup Guard

```text
REAL ATTACK-HIT EXECUTION X
        ↓
Acquire exact native attack semantics + actual Hit execution
        ↓
Marked motion?
   ├─ YES → markers own collision timing inside Hit
   └─ NO  → native activation remains untouched
        ↓
Did X request offensive collision?
   ├─ NO  → no cleanup obligation
   └─ YES → remember obligation for X and exact physical source(s)
        ↓
Native cleanup 7 -> 5 observed for X/source?
   ├─ YES → fulfill that obligation; no fallback
   └─ NO  → obligation remains outstanding
        ↓
Native execution is destructively finalized/abandoned
        ↓
Outstanding obligation?
   ├─ NO  → no-op
   └─ YES → repair only X's remaining offensive source(s)
        ↓
retire X lifecycle state
```

A request counts even when the physical source is already offensive (`7 -> 7`). EV-181 proves why: a later attack can inherit stale group 7 from an earlier broken execution.

Conceptual production state:

```text
Execution X
    exact execution identity / actor
    offensive source set actually requested by X
    cleanup obligation per owned source
    native cleanup observation
    terminal/finalization status
```

The state must be event-driven. No polling or wall-clock lifetime inference.

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
→ later AISetState(...Loop)
```

B9 confirms the ordinary cleanup occurs **before** the later destructive state replacement. The same ordering is observed for tested clean Normal/Quick cases.

### B — legitimate damage/reaction interruption

Tested armed player Normal/Quick reactions:

```text
attack Hit active
→ AIFullStop terminates active CombatMove
→ separate reaction cleanup +0x24AFF resets 7 -> 5
→ reaction successor owns motion/state flow
```

B9 found no AISetState interposed before that legitimate cleanup in the tested armed samples. More than one legitimate-reaction FullStop caller exists (`+0x2D0F8` and `+0x2B8CB` observed), so call-site identity is not the production classifier.

### C — tested bad held-Use2 state-stack abandonment

```text
attack ScriptFunction suspended at CombatMove break block
→ Use2 remains held beyond 2500 ms
→ Script_Game +0x633F1 calls PSRoutine::FullStop()
→ active CombatMove terminates
→ Script_Game +0x63409 calls PSRoutine::SetState(...)
→ Game +0x164320 AISetState begins destructive state replacement
→ old SPU state-stack / break-block continuation is lost
→ ordinary action cleanup can no longer resume
→ no reaction cleanup owner replaced it
→ armed source can remain Item_Attack(7)
```

B8 proves this tested abandonment class applies to full Whirl and Quick across Dual (1H+1H), plain 1H and Shield+1H player configurations.

B9 proves that, in representative armed bad cases, AISetState is entered while the old attack context is still visible pre-original and the weapon is still group 7, with no native cleanup between FullStop and AISetState.

---

## 4. Native Execution/State-Stack Authority

Relevant native layers:

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

While CombatMove is active, `sAICombatMoveInstr` persists in `m_pfInstrCallback` and the owning ScriptFunction can remain suspended in the SPU state stack.

`gCScriptRoutine_PS::AIFullStop()` invokes the current instruction callback with `fullStop=true`. This is instruction termination, not cleanup.

`PSRoutine::SetState` routes through tested `Game +0x164320 = gCScriptRoutine_PS::AISetState(bCString const&)`; SDK documentation states SetState clears the state stack and resets state-position/break-block bookkeeping.

The tested distinction is now:

```text
FullStop alone
≠ cleanup-finalization authority

native cleanup observed before state replacement
= obligation fulfilled

FullStop + AISetState with obligation still outstanding
= proven destructive abandonment for the known held-Use2 stale class
```

AISetState is generic infrastructure. Its meaning comes from an already-owned attack execution and outstanding cleanup obligation, not from the call alone.

---

## 5. Ownership Authority by Responsibility

### Attack execution acquisition

Use native callback/action/phase semantics to identify the relevant attack mechanism, then follow the exact actual Hit execution. Filename/action alone must not own terminal behavior.

### Collision obligation

An actual offensive-collision request by execution X creates the obligation for the exact physical source(s) requested by X. `7 -> 7` still counts as a request.

### Native cleanup observation

Observed native `7 -> 5` cleanup fulfills the corresponding outstanding source obligation. Do not infer cleanup because a successor animation, Recover, FullStop or state request occurred.

### Terminal execution transition

For the known tested stale class, destructive AISetState after CombatMove termination is a proven point at which the old suspended continuation is gone. Production may use this only in conjunction with exact execution ownership and an unfulfilled obligation.

### Physical source authority

Weapon collision ownership is per exact equipped entity/source. Fist/body collision semantics remain separate and must not be forced into weapon-style Item_Attack cleanup.

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

`G3AB_COL_OFF` is an authored inactive gap inside a still-live Hit. It is not terminal safety and must not retire the execution.

Physical cleanup and marker bookkeeping retirement remain separate responsibilities unless later C1 validation proves one native lifecycle boundary can safely own both while preserving all marker regressions.

---

## 7. Constraints Established by Step B

Any C1 design must preserve these facts:

- PrimaryFirst replacement can occur before native cleanup and is not itself the fallback point.
- Later original attack callbacks are not one-shot completion boundaries.
- StartRecover is too early and can be bypassed.
- Missing Recover assets are not the cause.
- Successful ordinary cleanup is action/path-specific.
- Legitimate reaction cleanup is a separate path.
- `RunScriptFunction`, `RunScriptState` and `ProcessScript` are generic infrastructure, not combat ownership.
- FullStop is instruction termination, not cleanup.
- Held-Use2 `FullStop -> SetState` abandonment generalizes across the tested player Whirl/Quick configurations, but the player input branch itself is not universal authority.
- AISetState is generic; it is useful only when paired with exact owned execution state and outstanding obligation.
- Intentional marker OFF/source switching is intra-Hit behavior, not execution finalization.

Exact evidence routing: EV-158 onward; B8/B9 raw logs are current decisive runtime evidence.

---

## 8. B8/B9 Research Gate — RESOLVED FOR C1 DESIGN

The former gate asked whether the full-Whirl abandonment mechanism generalized and whether destructive state replacement occurs before or after legitimate cleanup opportunity.

B8/B9 answer the tested question:

- same held-Use2 state-stack abandonment class appears in Whirl and Quick across multiple weapon configurations;
- bad armed path reaches AISetState with collision still 7 and no cleanup intervening;
- tested ordinary completion cleans before AISetState;
- tested armed Normal/Quick reactions clean through +0x24AFF before any relevant AISetState.

This is sufficient to stop broad diagnostic expansion and design C1. It does **not** prove every possible abnormal NPC/terrain/state path uses the same finalization sequence; later regression tests must expose any additional terminal class rather than pre-emptively building cause-specific branches.

---

## 9. C1 Design Gate — CURRENT

Before Work implementation, freeze one minimal event-driven state machine.

Candidate native events already proven and available:

```text
OFFENSIVE REQUEST
    existing SetCollisionGroup observation / marker request path

NATIVE CLEANUP
    observed Item_Attack(7) -> Item_Equipped(5)

INSTRUCTION TERMINATION
    sAICombatMoveInstr(..., fullStop=true) / AIFullStop evidence

DESTRUCTIVE FINALIZATION
    gCScriptRoutine_PS::AISetState before old state-stack continuation is cleared
```

The production rule must be consequence-based:

```text
if execution X never requested offense:
    no obligation

if Gothic cleaned X before finalization:
    no fallback

if X reaches destructive finalization with its own obligation still outstanding:
    repair only X's remaining owned offensive source(s)
```

Do **not** classify by Use2, Whirl, Quick, block timeout, state-name string, Script_Game call site or successor animation.

Before freezing Work, Normal Chat must specify:

1. exact lifecycle record/key;
2. exact event that creates/updates per-source obligation;
3. exact native cleanup event that fulfills it;
4. relation between CombatMove fullStop and AISetState finalization;
5. how pre-activation FullStop remains a no-op;
6. how `7 -> 7` requests are attributed to the new execution rather than inherited stale state;
7. how RIGHT/LEFT/BOTH/OFF source changes interact with the obligation;
8. when marker occurrence/execution bookkeeping is retired, without conflating it with physical cleanup;
9. actor/unload/reset fail-safe policy if needed by existing APIs/evidence;
10. negative scope for Fist/bow/crossbow/magic.

---

## 10. Future Marker-Core Simplification Gate

Current marker bookkeeping exists because of reproduced failures involving:

- required StatePosition advancement after custom ownership;
- repeated-contact occurrence handling;
- duplicate/replayed frame-effect dispatch;
- interrupted execution budgets surviving into later attacks;
- bookkeeping retirement after Gothic already performed physical cleanup.

C1 must preserve those guarantees unchanged first. Only after C1 regression validation may native CombatMove/state-stack lifetime be considered as a simplification of existing marker-lifetime inference.

Retrieve EV-066–EV-075, EV-106–EV-116, EV-131–EV-133, EV-167 and current Step-B lifecycle evidence before simplifying marker bookkeeping.

---

## 11. Production Restrictions / Regression Requirements

Do not default to:

- one cleanup hook per attack family;
- cleanup at the held-Use2 `+0x633F1` caller;
- unconditional cleanup on AIFullStop or AISetState;
- unconditional cleanup on every `ProcessScript()` return;
- polling, per-frame/world scans or wall-clock timers;
- input/block-timeout/family/state-name repair rules;
- action/phase-only terminal authority.

C1 validation must include ordinary completion, legitimate reaction interruption, armed/pre-activation bad abandonment, `7 -> 7` inherited-stale scenarios, marked RIGHT/LEFT/BOTH/OFF behavior, repeated markers, and negative/no-op coverage for unrelated mechanics.

Especially protect:

- Fist;
- bow;
- crossbow;
- magic.

Fist can share melee action enums while not using weapon-style Item_Attack(7) source ownership.

---

## 12. Preference Order

1. **Preferred:** one event-driven execution-level guard using actual offensive requests, observed native cleanup, and proven destructive finalization.
2. **Preferred source model:** exact actor + equipped physical source ownership, including per-source obligations for dual/source-switch cases.
3. **Preferred marker direction:** leave current marker lifetime/bookkeeping unchanged until C1 passes regression; simplify only afterward if native lifetime is demonstrably stronger.
4. **Fallback:** add another native terminal class only when a real reproduced case proves it cannot fit the current general model.
5. Avoid cause/family-specific production branches.

# Collision Lifecycle Plan

**Status:** Current collision-lifecycle architecture / research authority  
**Updated:** 2026-08-28

## Purpose

Define the smallest authoritative rule that can guarantee offensive collision cleanup without creating one repair branch per attack family or interruption symptom.

Detailed proof history belongs in `EVIDENCE_INDEX.md` / the evidence ledgers. Build-specific native cleanup locations belong in `COLLISION_CLEANUP_CALLSITE_MAP.md`.

The pre-information-architecture plan is preserved at:

`docs/archive/technical_2026-08-27/COLLISION_LIFECYCLE_PLAN_pre_ia.md`

---

## 1. Governing Invariant

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact Hit genuinely ends or is replaced, if proper cleanup already occurred, do nothing; if not, repair the remaining offensive collision using native cleanup semantics.**

How the Hit ended is not part of the production rule. Normal completion, damage/reaction interruption, block timeout, skipped Recover bookkeeping, terrain interruption, and direct replacement are test cases for one lifecycle invariant.

B6-D strengthened this invariant: an armed bad Whirl can lose its physical Hit, sit in ordinary idle for many seconds with the weapon still offensive, and carry that stale state into a later independent attack until a later valid cleanup finally occurs.

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
X genuinely ends / restarts / is replaced
        ↓
Allow Gothic its legitimate native cleanup opportunity
        ↓
Was X cleaned?
   ├─ YES → no-op
   └─ NO  → repair remaining offensive collision
        ↓
retire execution-level lifecycle/marker bookkeeping
```

A request counts even when the physical source was already offensive (`7 -> 7`). The obligation comes from execution X requesting offensive collision, not from observing a numerical group transition. EV-181 now directly shows why: a later Normal attack can inherit a stale group-7 weapon from a previous broken Whirl and therefore issue `7 -> 7` before eventually cleaning it.

Preferred minimal state remains conceptually:

```text
Execution X
    exact actual Hit execution identity
    collisionRequested
    nativeCleanupObserved
```

Production should remain event-driven. The exact finalization trigger/timing mechanism is **not yet chosen** after B6 rejected the earlier replacement-triggered deferred-`ProcessScript()` candidate.

---

## 3. Fallback — Source-Aware Guard Only If Evidence Requires It

Use per-source cleanup ownership only if runtime/source evidence proves attack-wide obligation is insufficient—for example, if one source can legitimately clean while another independently remains stale.

Do **not** adopt source-specific lifecycle bookkeeping merely because the marker implementation already has RIGHT/LEFT masks.

The preferred abstraction is execution-level. The physical source set is subordinate data unless evidence proves otherwise.

---

## 4. Marker Rule While the Hit Is Alive

Marker timing is separate from terminal lifecycle cleanup.

```text
RIGHT = {RIGHT}
LEFT  = {LEFT}
BOTH  = {RIGHT, LEFT}
OFF   = {}
```

Each marker defines the complete desired offensive equipped-source set at that authored moment.

Repeated source markers explicitly rearm their source through `ClearTriggeredList()`.

`G3AB_COL_OFF` is an optional authored inactive gap inside a still-live Hit. It is **not** terminal safety and must not replace the lifecycle guard.

Two governing rules:

```text
WHILE THE HIT IS ALIVE:
markers define the desired offensive set.
```

```text
WHEN THE HIT IS OVER:
offensive collision must be clean.
```

---

## 5. Ownership Authority

Use the strongest available facts for each responsibility.

### Attack-family acquisition

Native callback/action/phase semantics identify the relevant attack mechanism.

### Physical execution lifetime

After a real Hit is acquired, the exact actual PrimaryFirst Hit motion is the stronger physical-lifetime observation. Step-B evidence showed action/phase can drift and bad skip can return to ordinary action/idle while stale offensive collision survives.

### Collision obligation

An actual offensive-collision request by that execution creates the cleanup obligation.

### Native-cleanup observation

Observe the legitimate native cleanup operation/consequence for the owned source/execution. Do not infer success merely because a successor animation was requested.

### Generic script boundary

Generic script-processing can explain timing/control flow on successful paths, but B6 did not establish it as a universal observable replacement-time checkpoint. It must never acquire attack ownership by itself.

---

## 6. Native Cleanup Paths Are Opportunities, Not One Universal Function

Step B4/B4b/B5 established:

- successful ordinary completion uses multiple action-specific `Script_Game.dll` cleanup call sites;
- tested damage/reaction interruption uses a separate cleanup path beginning at `Script_Game + 0x24AFF`;
- those paths converge only later in generic script-execution machinery.

Therefore production should observe whether proper native cleanup occurred rather than hook a growing matrix of family-specific cleanup functions.

Exact action/RVA/stack map:

`COLLISION_CLEANUP_CALLSITE_MAP.md`

Evidence routing:

- EV-163 — action-specific cleanup matrix;
- EV-165 — separate tested interruption cleanup;
- EV-166 / EV-169–EV-171 — higher generic script parents;
- EV-179–EV-181 — reaction successor context, bad-skip context, and long-lived stale offense.

---

## 7. Step-B Constraints on Any Final Design

### B1 — replacement is immediate but too early for repair

`eCVisualAnimation_PS::PlayMotion(type 0)` can reveal PrimaryFirst replacement immediately.

In clean Hit -> Recover transitions, successor PlayMotion can occur **before** later native `7 -> 5` cleanup. Therefore replacement itself is not a post-cleanup repair boundary.

### B2 — later original callbacks are not one-shot completion

The original Quick callback can begin only after cleanup and then repeat during Recover. Callback return is not universal Hit completion.

### B3 — StartRecover is too early and not guaranteed

`sAICombatMoveStartRecover` returns before ordinary cleanup and can be bypassed entirely by broken direct-replacement paths.

### B3b — missing Recover assets are not the cause

A no-Recover animation asset can still receive engine Recover bookkeeping and cleanup; the same family can also take the broken path.

### B4/B4b — successful cleanup is action/path-specific

Do not translate native success locations into one hook per action.

### B5 + static identification — shared parents are generic script infrastructure

The B5 parents are identified:

```text
Game + 0x1603D0 = gCScriptAdmin::RunScriptState(...)
Game + 0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
Game + 0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

These are not combat-specific cleanup owners.

`sAICombatMoveInstr` is also too early: action-specific Script_Game cleanup can occur after it returns.

### B6 — one common replacement-time ProcessScript checkpoint was not demonstrated

Clean completion exposes `sAICombatMoveInstr -> ProcessScript()` at StartRecover. Legitimate reaction successor installation remains inside the reaction Script_Game/ScriptAdmin chain. But an armed bad Whirl can disappear to Ambient with a short observed successor stack containing only the diagnostic frame and `Game + 0xD9CB3`, while the weapon remains offensive.

Therefore B6 does **not** justify a production design that depends on every relevant Hit replacement occurring inside one useful currently observable `ProcessScript()` invocation.

---

## 8. Rejected Candidate — Replacement-Triggered Deferred ProcessScript Finalization

The previous candidate was:

```text
exact owned offensive Hit replacement/restart observed
        ↓
mark that exact execution pending-finalization
        ↓
let the current native script dispatch finish
        ↓
at one tightly gated post-script opportunity:
    native cleanup observed -> no-op
    cleanup absent          -> repair
```

B6-D rejects this **specific timing strategy in its present form**. The decisive bad replacement did not expose the useful ScriptAdmin/SPU context needed to guarantee that a replacement-triggered pending execution could be checked at the end of the same current ProcessScript invocation.

This does **not** reject:

- the execution-level cleanup invariant;
- event-driven lifecycle ownership;
- using native cleanup semantics;
- a later generic timing point if another reliably shared boundary is proven.

Do not add a ProcessScript behavior hook merely to rescue the rejected candidate.

---

## 9. Current Gate — B7 Attack-Lifecycle / Bookkeeping Reconstruction

The next question moves earlier than physical replacement:

> **What native CombatMove/routine/instruction bookkeeping established when an attack Hit starts keeps normal completion and legitimate reaction paths connected to cleanup, and what is reset, abandoned or bypassed differently on the bad block-skip path?**

The working model is deliberately structural, not literal object speculation:

```text
attack Hit begins
→ CombatMove / animation / movement execution established
→ Routine StateTime advances
→ Routine StatePosition / callback bookkeeping records one-shot progress
→ timed callback may request offensive collision
→ continuation remains connected to either:
     normal completion cleanup
     OR legitimate reaction cleanup

bad block skip
→ some part of that continuation/bookkeeping is abandoned or bypassed
→ physical Hit can disappear through another animation path
→ neither legitimate cleanup route is guaranteed
→ offensive collision can remain stale
```

This is a **working lifecycle/control-flow hypothesis**, not proof that Gothic allocates a literal attack "package" or that one specific field is destroyed.

Highest-value next targets:

- `sAICombatMoveStart`;
- `sAICombatMoveItlLoop`;
- `sAICombatMoveInstr` active instruction / `m_pfInstrCallback` state;
- `Routine.StateTime`;
- `Routine.StatePosition`;
- attack callback scheduling;
- action-specific Script_Game continuation after CombatMove;
- reaction state/reset path before `Script_Game +0x24AFF`.

Prefer static caller/control-flow reconstruction first. Add only the smallest runtime diagnostic needed to distinguish clean, legitimate-reaction, and bad-skip bookkeeping.

A particularly bounded future diagnostic is to reuse the existing `SetCollisionGroup` hook and capture a short stack for actual offensive requests (`5 -> 7`, and meaningful `7 -> 7`) so the timer/callback activation path can be compared with cleanup and teardown without adding a new Gothic hook.

---

## 10. Marker Bookkeeping vs Physical Cleanup

These are separate responsibilities but the bookkeeping evidence is now directly relevant to B7.

Earlier interruption work showed a case where Gothic physically cleaned a marked source but the marker occurrence/execution record could remain stale. `RetireMarkerOwnedSource()` exists to retire bookkeeping after an already-performed source reset; it is not physical fallback cleanup.

Likewise, marked Quick/full-Whirl activation had to advance `Routine.StatePosition` so Gothic would not later repeat its one-shot native timed activation. These proven failures demonstrate that attack behavior can depend materially on persistent bookkeeping even when the animation itself is already playing.

Intentional OFF or exact-set source switching is intra-Hit behavior and must not retire the entire execution.

Do not equate custom marker bookkeeping with Gothic's unknown native ownership fields; use it only as evidence that bookkeeping can be causally important.

---

## 11. Three Observed Ending Structures

### A — ordinary successful completion

```text
Hit
→ StartRecover / normal CombatMove continuation
→ action-specific Script_Game cleanup
→ RunScriptFunction/generic script return
→ collision clean
```

### B — legitimate damage/reaction interruption

```text
Hit
→ old routine timing/bookkeeping resets/changes
→ Script_Game interruption cleanup (+0x24AFF in tested matrix)
→ reaction ScriptState / Script_Game continuation
→ reaction motion
→ collision clean
```

### C — bad block skip / abnormal teardown

```text
Hit requests offense
→ no StartRecover
→ no tested reaction cleanup
→ Hit disappears to ordinary Ambient/idle through a different observed motion-request context
→ weapon may remain Item_Attack(7) for many seconds
→ a later independent attack can inherit stale 7 and request 7 -> 7
→ later valid native cleanup can finally reset it
```

The third structure is why a Staff-, Whirl-, Quick-, block-timeout-, or Recover-specific production repair would be the wrong abstraction.

---

## 12. Deeper Block-Skip Research Is Now the Immediate Architecture Search

Earlier the project intentionally separated deeper block-skip research from universal collision safety. B6 now shows that understanding the bookkeeping/control-flow loss is likely necessary to locate a reliable general finalization boundary.

That does not mean the final repair should restore the whole CombatMove system. The immediate purpose is narrower:

1. reconstruct what normal/legitimate paths keep alive that the bad skip loses;
2. identify the smallest general lifecycle signal that can establish terminal cleanup obligation/finalization;
3. only then decide whether collision-only repair is enough or a broader CombatMove repair is worthwhile.

The user has also observed attack-driven movement stop while the visual Hit continues in bad skip cases, which remains consistent with a wider CombatMove teardown defect but is not yet mapped to one native field/function.

Raise is not a collision cleanup fix. It may only alter when the vulnerable transition occurs.

---

## 13. Production Implementation Gate

Production cleanup remains blocked until a post-native-opportunity finalization mechanism is strong enough to avoid family-specific repair matrices or polling.

Do not default to:

- one cleanup hook per action family;
- unconditional cleanup on every `ProcessScript()` return;
- broad `sAICombatMoveItlLoop` polling;
- wall-clock timers;
- block-timeout/Staff/Quick/Whirl-specific cleanup rules;
- action/phase-only lifetime authority after exact Hit acquisition;
- treating `Game +0xD9CB3` as a known lifecycle owner before it is identified.

If implementation research reveals a conceptual contradiction, return to design/research.

---

## 14. Later Regression Requirements

If a final design eventually uses generic script timing, validate unrelated mechanics as negative/no-op cases—especially:

- Fist;
- bow;
- crossbow;
- magic.

Fist is especially important because it can share ordinary melee action enums while not using the tested weapon-style physical `Item_Attack(7)` request.

Any generic checkpoint must remain a complete no-op unless an exact owned offensive execution is pending finalization.

---

## 15. Preference Order

1. **Preferred:** execution-level guard that observes/reuses Gothic's native cleanup semantics, with a finalization boundary established from B7 evidence.
2. **Fallback:** source-aware execution guard only if independent partial-source cleanup evidence requires it.
3. Avoid cause/family-specific production branches unless a real case is proven unable to fit either general model.

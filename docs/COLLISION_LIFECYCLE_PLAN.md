# Collision Lifecycle Plan

**Status:** Current collision-lifecycle architecture / research authority  
**Updated:** 2026-08-27

## Purpose

Define the smallest authoritative rule that can guarantee offensive collision cleanup without creating one repair branch per attack family or interruption symptom.

Detailed proof history belongs in `EVIDENCE_INDEX.md` / the evidence ledgers. Build-specific native cleanup locations belong in `COLLISION_CLEANUP_CALLSITE_MAP.md`.

The pre-information-architecture plan is preserved at:

`docs/archive/technical_2026-08-27/COLLISION_LIFECYCLE_PLAN_pre_ia.md`

---

## 1. Governing Invariant

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact Hit genuinely ends or is replaced, if proper cleanup already occurred, do nothing; if not, repair the remaining offensive collision using native cleanup semantics.**

How the Hit ended is not part of the production rule. Normal completion, damage/reaction interruption, block timeout, skipped Recover bookkeeping, terrain interruption, and direct replacement are test cases for one lifecycle invariant.

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

A request counts even when the physical source was already offensive (`7 -> 7`). The obligation comes from execution X requesting offensive collision, not from observing a numerical group transition.

Preferred minimal state remains conceptually:

```text
Execution X
    exact actual Hit execution identity
    collisionRequested
    nativeCleanupObserved
```

A short transient `pendingFinalization` state is acceptable if the final event model requires replacement to be detected before the native cleanup opportunity has completed.

Production should remain event-driven.

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

After a real Hit is acquired, the exact actual PrimaryFirst Hit motion is the stronger lifetime authority. Step-B evidence showed action/phase can drift while the physical Hit continues.

### Collision obligation

An actual offensive-collision request by that execution creates the cleanup obligation.

### Native-cleanup observation

Observe the legitimate native cleanup operation/consequence for the owned source/execution. Do not infer success merely because a successor animation was requested.

### Generic script boundary

A generic script-processing boundary may provide **timing only**. It must never acquire attack ownership by itself.

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
- EV-166 / EV-169–EV-171 — higher generic script parents.

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

The B5 parents are now identified:

```text
Game + 0x1603D0 = gCScriptAdmin::RunScriptState(...)
Game + 0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
Game + 0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

These are not combat-specific cleanup owners.

`sAICombatMoveInstr` is also too early: action-specific Script_Game cleanup can occur after it returns.

Static comparison found no common immediate Script_Game helper after cleanup across the tested ordinary action families.

---

## 8. Current Candidate — Deferred One-Shot Finalization

Current candidate:

```text
exact owned offensive Hit replacement/restart observed
        ↓
mark that exact execution pending-finalization
        ↓
let the current native script dispatch finish
        ↓
at one tightly gated post-script opportunity:
    native cleanup observed -> no-op
    cleanup absent          -> repair exact owned offensive source(s)
```

Critical restriction:

> The post-script layer supplies only the **after-native-opportunity timing point**. Ownership was already established by the exact attack execution and its offensive collision request.

This remains a candidate, not production architecture, until B6 runtime validation proves whether the relevant replacement paths actually share a useful SPU / `ProcessScript()` context.

---

## 9. Step B6 — Current Validation Gate

The B6 source probe is implemented and independently source-reviewed. It adds no production cleanup.

It uses the existing player/type-0 `PlayMotion` hook to capture a short supported Win32 stack for **confirmed actual attack-Hit PrimaryFirst replacement/restart** events.

Current question:

> **Do clean Hit -> Recover replacement, legitimate damage/reaction replacement, and bad block-skip direct replacement all occur inside the same useful SPU / `ProcessScript()` invocation so that a one-shot post-script check would reliably occur after Gothic's native cleanup opportunity?**

Home-PC validation must compare:

1. clean Hit -> Recover replacement;
2. legitimate damage/reaction replacement;
3. bad block-skip direct replacement with missing cleanup.

Interpretation:

- **same useful script-processing context:** strengthens the deferred post-script candidate;
- **different/non-script replacement context:** reject or revise that checkpoint rather than adding special-case cleanup branches;
- **ambiguous stack:** improve only the diagnostic needed to answer the boundary question.

Do not add a `ProcessScript` behavior hook until B6 evidence justifies it.

---

## 10. Marker Bookkeeping vs Physical Cleanup

These are separate responsibilities.

Earlier interruption work showed a case where Gothic physically cleaned a marked source but the marker occurrence/execution record could remain stale. `RetireMarkerOwnedSource()` exists to retire bookkeeping after an already-performed source reset; it is not physical fallback cleanup.

Intentional OFF or exact-set source switching is intra-Hit behavior and must not retire the entire execution.

A final exact-Hit lifecycle boundary may simplify both bookkeeping retirement and physical cleanup verification, but only if it preserves authored intra-Hit source transitions and replay protection.

---

## 11. Three Observed Ending Structures

### A — ordinary successful completion

```text
Hit
→ action-specific Script_Game cleanup
→ RunScriptFunction/generic script return
→ collision clean
```

### B — legitimate damage/reaction interruption

```text
Hit
→ Script_Game interruption cleanup (+0x24AFF in tested matrix)
→ reaction Script_Game state
→ RunScriptState/generic script return
→ reaction motion
→ collision clean
```

### C — bad block skip / abnormal teardown

```text
Hit
→ part of CombatMove/gameplay ownership/bookkeeping is abandoned
→ ordinary cleanup not guaranteed
→ legitimate interruption cleanup not guaranteed
→ physical Hit can continue or later replace
→ stale offensive collision possible
```

The third structure is why a Staff-, Whirl-, Quick-, block-timeout-, or Recover-specific production repair would be the wrong abstraction.

---

## 12. Separate Deeper Block-Skip Research

Evidence supports a broader native CombatMove teardown defect beyond collision cleanup. The user has also observed attack-driven movement stop while the visual Hit continues in bad skip cases.

That deeper defect may later deserve repair, but it remains **separate** from the universal collision safety rule.

Research order:

1. finish the universal collision lifecycle guard;
2. validate it against ordinary and abnormal endings;
3. only later investigate whether preserving full CombatMove movement/activation/bookkeeping through the skip is worthwhile.

Raise is not a collision cleanup fix. It may only alter when the vulnerable transition occurs.

---

## 13. Production Implementation Gate

Production cleanup remains blocked until the post-native-opportunity timing boundary is strong enough to avoid family-specific repair matrices or polling.

Do not default to:

- one cleanup hook per action family;
- unconditional cleanup on every `ProcessScript()` return;
- broad `sAICombatMoveItlLoop` polling;
- wall-clock timers;
- block-timeout/Staff/Quick/Whirl-specific cleanup rules;
- action/phase-only lifetime authority after exact Hit acquisition.

If implementation research reveals a conceptual contradiction, return to design/research.

---

## 14. Later Regression Requirements

If the final design uses generic script timing, validate unrelated mechanics as negative/no-op cases—especially:

- Fist;
- bow;
- crossbow;
- magic.

Fist is especially important because it can share ordinary melee action enums while not using the tested weapon-style physical `Item_Attack(7)` request.

The generic checkpoint must remain a complete no-op unless an exact owned offensive execution is pending finalization.

---

## 15. Preference Order

1. **Preferred:** execution-level guard that observes/reuses Gothic's native cleanup semantics.
2. **Fallback:** source-aware execution guard only if independent partial-source cleanup evidence requires it.
3. Avoid cause/family-specific production branches unless a real case is proven unable to fit either general model.

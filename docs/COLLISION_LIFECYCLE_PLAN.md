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
- EV-179–EV-181 — reaction successor context, bad-skip context, and long-lived stale offense;
- EV-182–EV-184 — persisted CombatMove instruction state, clean Script_Game break-block continuation, and reaction-side FullStop structure.

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

Clean completion exposes `sAICombatMoveInstr -> ProcessScript()` at StartRecover. Legitimate reaction successor installation remains inside the reaction Script_Game/ScriptAdmin chain. But an armed bad Whirl can disappear to Ambient with a short observed successor stack containing only the diagnostic frame and `Game +0xD9CB3`, while the weapon remains offensive.

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

The question has now narrowed from the earlier structural "package" hypothesis to a concrete native mechanism:

> **Does bad block-skip forcibly terminate the persisted CombatMove instruction and then lose the owning attack continuation, or does the active CombatMove instruction disappear through another path?**

### B7 static reconstruction already established

The official SDK and tested binary expose two persistent bookkeeping layers:

```text
gCScriptProcessingUnit
    m_pfInstrCallback
    m_fInstrPlayTime
    m_fInstrDuration


gCScriptRoutine_PS
    StateTime
    StatePosition
    CurrentBreakBlock
    Action
```

A CombatMove does not require one attack-specific function to remain continuously on the native stack. While active, `sAICombatMoveInstr` can persist as the SPU instruction callback and the owning ScriptFunction can remain suspended at a break block.

The tested stop APIs are correspondingly direct:

```text
gCScriptRoutine_PS::AIFullStop()
→ if an instruction callback exists:
     invoke current callback with fullStop=true

AIStopCombatMove()
→ only if m_pfInstrCallback == sAICombatMoveInstr:
     invoke sAICombatMoveInstr(..., fullStop=true)
```

The tested `sAICombatMoveInstr` control flow supports the same model:

```text
CombatMove still active
→ advance/start/loop instruction
→ store sAICombatMoveInstr as current callback
→ return false

CombatMove terminal
→ terminal handling / Recover path as applicable
→ clear callback
→ return true

fullStop=true
→ bypass the normal ongoing/Recover decision path
→ stop internal CombatMove execution
→ clear callback
→ return true
```

### Clean full-Whirl continuation

The full-Whirl Script_Game function provides a concrete normal-path example:

```text
Script_Game +0x4DF8C
→ call CombatMove operation

+0x4DF92
→ test completion result

incomplete
→ ScriptFunction returns false
→ later cleanup is not reached yet

complete
→ ScriptFunction continues after the break block
→ ordinary full-Whirl weapon cleanup at +0x4E03C
```

This means ordinary collision cleanup is a **Script_Game continuation after the asynchronous CombatMove completes**, not an automatic consequence of the Hit animation disappearing.

### Legitimate reaction structure

Static reaction-control code contains explicit `PSRoutine::FullStop()` calls at `Script_Game +0x2246F` and `+0x23002`, in the same broad reaction functions represented by the legitimate reaction stacks. The tested reaction route separately supplies weapon cleanup through `Script_Game +0x24AFF`.

Do not overstate the ordering: the exact FullStop call used by every individual recorded Stumble/KnockDown has not yet been paired one-to-one at runtime.

### B7 runtime gate

The next smallest discriminating observation is therefore:

```text
sAICombatMoveInstr(..., fullStop=true)
```

If bad block-skip emits it, its caller stack can identify the path that forcibly terminates the active CombatMove. If bad block-skip does not emit it, this specific full-stop explanation is falsified and the instruction is being abandoned through another route.

Prefer that bounded diagnostic over broad attack-start, timer, or per-frame instrumentation.

Evidence: EV-182–EV-184.

---

## 10. Marker Bookkeeping vs Physical Cleanup — Future Marker Review Gate

These are separate responsibilities, but the B7 bookkeeping evidence is now directly relevant to how the marker core may eventually be simplified.

Earlier interruption work showed a case where Gothic physically cleaned a marked source but the marker occurrence/execution record could remain stale. `RetireMarkerOwnedSource()` exists to retire bookkeeping after an already-performed source reset; it is not physical fallback cleanup.

Likewise, marked Quick/full-Whirl activation had to advance `Routine.StatePosition` so Gothic would not later repeat its one-shot native timed activation. These proven failures demonstrate that attack behavior can depend materially on persistent bookkeeping even when the animation itself is already playing.

The new B7 static evidence adds an important possibility: Gothic itself has a persistent CombatMove instruction lifetime and ScriptFunction break-block continuation. If later evidence proves that one exact marked Hit execution can be safely correlated with that native instruction lifetime, some of the custom marker execution/occurrence inference may be reducible.

A future marker consolidation should therefore explicitly test whether the native lifecycle can replace or simplify parts of:

```text
MarkerExecutionBudget / occurrence identity
StateTime-rollback new-execution inference
RetireMarkerOwnedSource execution retirement
other custom lifetime guards whose only job is to infer that one CombatMove ended and another began
```

But **do not simplify these now**. Before any marker bookkeeping refactor/reimplementation, read:

- EV-066–EV-075 — Quick ownership and required `StatePosition` advancement;
- EV-106–EV-116 — repeated contact / occurrence / replay protection;
- EV-131–EV-133 — interrupted marked-execution retirement regression and fix;
- EV-167 — marker retirement is not physical cleanup;
- EV-182–EV-184 — persisted CombatMove/break-block/FullStop architecture;
- the then-current B7+ lifecycle evidence.

Any optimization must preserve all proven marker guarantees:

- marker ownership remains exact-motion opt-in;
- `StatePosition` must not allow Gothic's old timed activation to replay after custom ownership;
- repeated markers later in one Hit remain distinct authored contacts and rearm correctly;
- OFF and RIGHT/LEFT/BOTH exact-set source switching remain intra-Hit operations and must not retire the whole execution;
- duplicate/replayed frame-effect dispatch must not consume a new authored occurrence incorrectly;
- legitimate interruption must not let one execution's marker budget survive into the next;
- physical collision cleanup and marker bookkeeping retirement remain separate unless one proven native execution boundary can safely own both.

The preferred future result is not "more native-looking" code for its own sake. It is **less custom state only where Gothic's own execution lifetime provides stronger authority than our current inference**.

Primary retrieval route for future marker work: `EVIDENCE_INDEX.md` → **Marker execution lifetime / bookkeeping**.

---

## 11. Three Observed Ending Structures

### A — ordinary successful completion

```text
attack ScriptFunction reaches CombatMove break block
→ sAICombatMoveInstr persists while CombatMove is active
→ CombatMove eventually returns complete
→ ScriptFunction resumes after break block
→ action-specific Script_Game cleanup
→ RunScriptFunction/generic script return
→ collision clean
```

### B — legitimate damage/reaction interruption

```text
Hit active
→ reaction-control code can FullStop the current AI instruction
→ old routine timing/bookkeeping resets/changes
→ separate Script_Game interruption cleanup (+0x24AFF in tested matrix)
→ reaction ScriptState / Script_Game continuation
→ reaction motion
→ collision clean
```

The runtime/static evidence supports this structure, but the exact per-event FullStop call ordering still needs B7 confirmation.

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

The unresolved B7 question is whether this bad path also full-stops `sAICombatMoveInstr` and then loses the original ScriptFunction continuation, or abandons the instruction by another mechanism.

The third structure is why a Staff-, Whirl-, Quick-, block-timeout-, or Recover-specific production repair would be the wrong abstraction.

---

## 12. Deeper Block-Skip Research Is Now the Immediate Architecture Search

Earlier the project intentionally separated deeper block-skip research from universal collision safety. B6 showed that understanding the bookkeeping/control-flow loss is likely necessary to locate a reliable general finalization boundary; B7 static reconstruction has now identified the persisted CombatMove instruction and break-block continuation as concrete parts of that ownership chain.

That does not mean the final repair should restore the whole CombatMove system. The immediate purpose remains narrower:

1. determine how the bad path terminates or abandons the current CombatMove instruction;
2. determine whether the original ScriptFunction/break-block continuation is discarded at the same transition;
3. identify the smallest general lifecycle signal that can establish terminal cleanup obligation/finalization;
4. only then decide whether collision-only repair is enough or a broader CombatMove repair is worthwhile.

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
- treating `Game +0xD9CB3` as a known lifecycle owner before it is identified;
- treating `m_pfInstrCallback == sAICombatMoveInstr` alone as exact marker-execution identity before B7 proves that mapping.

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
2. **Preferred marker consolidation direction if B7 later supports it:** replace custom lifetime inference with stronger native CombatMove execution boundaries only where all current marker guarantees remain intact.
3. **Fallback:** source-aware execution guard only if independent partial-source cleanup evidence requires it.
4. Avoid cause/family-specific production branches unless a real case is proven unable to fit either general model.
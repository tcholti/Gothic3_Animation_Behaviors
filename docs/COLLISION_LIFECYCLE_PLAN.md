# Collision Lifecycle Plan

**Status:** Current collision-lifecycle architecture / research authority  
**Updated:** 2026-08-29

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

The guard owns **collision safety**, not general combat-balance or state-machine policy. Compatible native/modded setups remain free to decide how blocking and interruptions behave; the guard should intervene only when an exact offensive obligation is genuinely abandoned without cleanup.

---

## 2. Preferred System — Execution-Level Native Cleanup Guard

```text
REAL ATTACK-HIT EXECUTION X
        ↓
Acquire exact native attack execution/lifetime
        ↓
Marked motion?
   ├─ YES → markers own collision timing inside Hit
   └─ NO  → native activation remains untouched
        ↓
Did X request offensive collision?
   ├─ NO  → no cleanup obligation
   └─ YES → remember obligation for X and exact physical source(s)
        ↓
Native cleanup observed for X/source?
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

A request counts even when the physical source is already offensive (`7 -> 7`). EV-181 and EV-193 prove why: a later attack can inherit stale group 7 from an earlier broken execution, and the later execution must still own its own request/cleanup obligation.

Conceptual production state:

```text
Execution X
    durable plugin-side generation / actor
    live native outer-execution correlator while available
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
→ attack ScriptFunction completes / later state transition follows
```

B9 confirms ordinary cleanup occurs before the later destructive state replacement. C1-O1 additionally shows the live attack ScriptFunction remains identifiable through CombatMove/offense/cleanup in tested clean Normal/Whirl cases and is gone before the later enclosing state transition.

### B — legitimate damage/reaction interruption

Tested armed player Normal/Quick reactions:

```text
attack Hit active
→ AIFullStop terminates active CombatMove
→ separate reaction cleanup +0x24AFF resets offensive collision
→ reaction successor owns motion/state flow
```

B9 found no AISetState interposed before that legitimate cleanup in the tested armed samples. More than one legitimate-reaction FullStop caller exists (`+0x2D0F8` and `+0x2B8CB` observed), so call-site identity is not the production classifier.

Cleanup remains source/consequence based and does not require the old attack ScriptFunction to still be current when reaction cleanup occurs.

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

C1-O1 confirms the outer `_AI_WhirlAttack` ScriptFunction is still present at `AI_SET_STATE_BEFORE` and absent at `AI_SET_STATE_AFTER` in the tested bad path.

This bad held-Use2 path is an important **stress case**, not production classification authority. Preserve it while the universal guard is being validated; do not encode Use2, 2500 ms, Whirl/Quick or the Community Patch call site into the guard.

---

## 4. Native Execution/State-Stack Authority

Relevant native layers:

```text
gCScriptProcessingUnit
    m_StateStack of gScriptRunTimeSingleState
    m_pfInstrCallback
    m_fInstrPlayTime
    m_fInstrDuration


gScriptRunTimeSingleState
    m_iBreakBlock
    m_strScriptName
    m_bIsScriptState
    m_pArguments
    m_strLocalCallback


gCScriptRoutine_PS
    StateTime
    StatePosition
    CurrentBreakBlock
    Action
```

While CombatMove is active, `sAICombatMoveInstr` persists in `m_pfInstrCallback` and the owning ScriptFunction can remain suspended in the SPU state stack.

The pinned SDK and tested Game binary establish an outer ScriptFunction lifetime through `gCScriptAdmin::RunScriptFunction(...)` at tested `Game +0x1604E0`. The registered ScriptFunction is called at `+0x1605E9`; false return preserves the runtime frame, while true return removes the completed top frame before the runner returns.

C1-O1 establishes the runtime correlation rule for tested attack ScriptFunctions:

```text
exact SPU
+ live ScriptFunction frame
+ non-null m_pArguments
+ same ScriptFunction name
= usable lifetime-bound correlator
```

Break block can legitimately advance within one execution. Stack-entry address, stack index/count, action/phase/state, local callback and input are not execution identity authority. `m_pArguments` and stack-entry addresses can be reused after the previous frame retires, so they are not permanent IDs.

C1's monotonic generation remains the durable plugin-side identity. A native frame correlator must be explicitly retired before pointer reuse. A future relevant ScriptFunction with null `m_pArguments` must fail diagnostically rather than inventing a fallback identity rule.

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

`RunScriptFunction`, FullStop and AISetState are generic infrastructure. Their collision meaning comes only from an already-owned exact execution/source obligation; none is unconditional cleanup authority by itself.

---

## 5. Ownership Authority by Responsibility

### Attack execution acquisition

The outer ScriptFunction execution is the preferred native lifetime layer above CombatMove. C1-O1 proves that legitimate GetUpAttack weapon offense can occur before CombatMove while the same outer ScriptFunction later remains live through CombatMove and cleanup.

C1 must therefore acquire/bind the execution no later than the first real owned offensive request. For pre-CombatMove acquisition, the allowed general context is the exact currently executing `RunScriptFunction` dispatch SPU/actor plus the frozen live-frame correlator—not a GetUp/action/family classifier.

### Durable execution identity

C1's own monotonic generation is durable plugin-side identity. Native frame fields are temporary correlators only while their frame remains live.

### Collision obligation

An actual successful offensive-collision request by execution X creates/refreshes the obligation for the exact physical source(s) requested by X. `7 -> 7` still counts as a request.

### Native cleanup observation

Observed successful transition away from `Item_Attack` fulfills the corresponding outstanding source obligation. Do not infer cleanup because a successor animation, Recover, FullStop, ScriptFunction return or state request occurred.

### Terminal execution transition

For the known tested stale class, destructive AISetState after CombatMove termination is a proven point at which the old suspended continuation is gone. Existing C1 shadow finalization may use this only in conjunction with exact generation/source ownership and an unfulfilled obligation.

A normal `RunScriptFunction` true return is currently a native-frame **binding retirement** point, not production repair authority. C1-O2 may log an outstanding-at-return invariant for later interpretation but must not repair there.

### Physical source authority

Weapon collision ownership is per exact equipped entity/source. Pre-CombatMove acquisition requires the changed source to be the supplied SPU actor's exact currently equipped RIGHT or LEFT weapon entity. Fist/body collision semantics remain separate and must not be forced into weapon-style Item_Attack cleanup.

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

## 7. Established Constraints Through C1-O1

Any C1-O2 implementation must preserve these facts:

- PrimaryFirst replacement can occur before native cleanup and is not itself the fallback point.
- Later original attack callbacks are not one-shot completion boundaries.
- StartRecover is too early and can be bypassed.
- Missing Recover assets are not the cause.
- Successful ordinary cleanup is action/path-specific.
- Legitimate reaction cleanup is a separate path.
- `RunScriptFunction`, `RunScriptState` and `ProcessScript` are generic infrastructure, not combat ownership by themselves.
- FullStop is instruction termination, not cleanup.
- Held-Use2 `FullStop -> SetState` abandonment generalizes across the tested player Whirl/Quick configurations, but the player input branch itself is not universal authority.
- AISetState is generic; it is useful only when paired with exact owned execution state and outstanding obligation.
- C1's per-source obligation model passed the tested core matrix, including inherited stale `7 -> 7` attribution.
- CombatMove start is too late as a universal acquisition boundary because GetUpAttack can legitimately arm beforehand.
- A live outer ScriptFunction frame can bridge pre-CombatMove offense → CombatMove → cleanup in tested GetUp and clean attack cases.
- `m_pArguments`/frame addresses are lifetime-bound correlators only and can be reused after retirement.
- Intentional marker OFF/source switching is intra-Hit behavior, not execution finalization.

Exact evidence routing: `EVIDENCE_INDEX.md` → EV-158 onward, especially EV-190–EV-196 for B8/B9/C1/C1-O1.

---

## 8. B8/B9 and C1 Core Gates — RESOLVED

B8/B9 resolved the earlier generality/finalization gate:

- same held-Use2 state-stack abandonment class appears in Whirl and Quick across multiple tested weapon configurations;
- bad armed path reaches AISetState with collision still 7 and no cleanup intervening;
- tested ordinary completion cleans before AISetState;
- tested armed Normal/Quick reactions clean through +0x24AFF before any relevant AISetState.

C1 then implemented and runtime-tested the consequence-based shadow obligation model:

- 8 actual `WOULD_REPAIR` outcomes were accounted for by known armed bad abandonments;
- clean/pre-activation/reaction controls did not become repairs;
- inherited stale `7 -> 7` was attributed to the new execution and later fulfilled by native cleanup.

C1 also exposed the acquisition gap: legitimate GetUpAttack offense can occur before CombatMove begins.

C1-O1 resolved the next outer-lifetime question by proving that the same live ScriptFunction frame can correlate that pre-CombatMove offense with later CombatMove/cleanup, while also proving raw pointer reuse after frame retirement.

---

## 9. C1-O2 Higher-Level Gate — CURRENTLY SUSPENDED FOR HOOK-TRANSPORT HARDENING

The higher-level bounded question remains:

> **Can C1 bind its existing monotonic generation to the live outer ScriptFunction frame, acquire a generation when a legitimate equipped-weapon offense occurs before CombatMove, reuse that same generation when the later CombatMove begins, and retire the native frame binding before address reuse without changing the already-passed cleanup/finalization classification?**

Direct `RunScriptFunction` dispatch-capture integration is not currently active. The recursion-safe pure pass-through baseline remains in place while the remaining legacy hook transports are hardened one at a time. `SESSION_ENTRYPOINT.md` owns the exact immediate prerequisite responsibility.

Frozen lifecycle direction for C1-O2 when it resumes:

```text
ordinary CombatMove path
→ preserve existing candidate-generation behavior when no matching outer generation exists
→ bind candidate to current live outer ScriptFunction frame

pre-CombatMove successful Item_Attack request
→ only inside exact RunScriptFunction dispatch context
→ actor from supplied SPU GetSelfEntity()
→ source must be actor's exact currently equipped RIGHT/LEFT weapon
→ live frame must satisfy exact SPU + ScriptFunction + non-null arguments + same ScriptFunction name
→ create/reuse C1 monotonic generation for that live frame
→ apply existing source-obligation semantics to actual request, including 7 -> 7

later CombatMove
→ same actor + same still-live outer binding
→ reuse generation; CombatMove is an inner milestone, not a new execution

cleanup
→ remain source/consequence based even if current script context differs

RunScriptFunction false return
→ frame remains live; keep binding

RunScriptFunction true return
→ retire native correlator before pointer reuse
→ if obligation unexpectedly remains outstanding, log high-signal shadow invariant
→ do not physically repair there

AISetState
→ preserve existing shadow destructive-finalization / WOULD_REPAIR semantics
```

Explicit non-authorities:

- no GetUp/action/family/input/state-name ownership table;
- no arbitrary adoption of already-group-7 weapons;
- no unconditional cleanup on RunScriptFunction return, FullStop or AISetState;
- no null-arguments fallback identity;
- no polling/timers/world scans/per-frame repair;
- no marker-core simplification in C1-O2.

No C1-O2 implementation task is currently frozen. Production physical repair remains disabled.

---

## 10. Universal-Guard-First Development Order

The agreed development order is:

```text
preserve the proven marker system
→ finish stable universal shadow execution/source identity and acquisition
→ prove controlled native-equivalent physical repair
→ retain the known bad held-Use2 abandonment as the strongest destructive stress case
→ preserve ordinary completion / legitimate reaction / pre-activation no-op controls
→ preserve inherited stale 7 -> 7 attribution
→ broad marked/unmarked/player/NPC/negative regression
→ stable production integration
→ only later reconsider marker bookkeeping simplification
```

The known held-Use2 / Alternative-AI bad skip is **not** a bug this mod is obligated to rewrite. If the universal guard safely prevents stale offensive collision, leave the remaining external movement/state/gameplay behavior alone.

Root-cause repair of that skip becomes a fallback investigation only if evidence shows that the universal guard cannot safely guarantee collision integrity without changing the destructive path. Examples include loss of exact execution/source identity before safe repair, unsafe post-abandonment cleanup, inability to distinguish inherited ownership, or a supposed universal guard that starts requiring Use2/2500-ms/family/Community-Patch-specific production rules.

Compatibility with New Balance and other compatible combat setups means preserving their chosen combat-rule behavior where possible; `Script_G3AnimationBehaviors` should not recreate or remove another mod's block-balance mechanic merely to make the collision system work.

The universal guard's responsibility ends at collision safety. It does not promise to restore unrelated movement, state or gameplay effects caused by an external destructive interruption.

---

## 11. Future Marker-Core Simplification Gate

Current marker bookkeeping exists because of reproduced failures involving:

- required StatePosition advancement after custom ownership;
- repeated-contact occurrence handling;
- duplicate/replayed frame-effect dispatch;
- interrupted execution budgets surviving into later attacks;
- bookkeeping retirement after Gothic already performed physical cleanup.

C1 must preserve those guarantees unchanged first. Only after universal guard identity, physical repair and regression validation may native CombatMove/state-stack/outer-ScriptFunction lifetime be considered as a simplification of existing marker-lifetime inference.

Retrieve EV-066–EV-075, EV-106–EV-116, EV-131–EV-133, EV-167 and EV-182–EV-196 before simplifying marker bookkeeping.

Do not simplify merely for elegance. Keep duplicate/replay protection, occurrence protection, exact source-set control, repeated-contact rearm, Quick bookkeeping and every other mechanism whose original regression still requires it.

---

## 12. Production Restrictions / Regression Requirements

Do not default to:

- one cleanup hook per attack family;
- cleanup at the held-Use2 `+0x633F1` caller;
- unconditional cleanup on AIFullStop or AISetState;
- unconditional cleanup on `RunScriptFunction`/`ProcessScript()` return;
- polling, per-frame/world scans or wall-clock timers;
- input/block-timeout/family/state-name repair rules;
- action/phase-only terminal authority;
- persistent raw-pointer identity after native-frame retirement;
- rewriting external block/balance mechanics as a prerequisite for collision safety.

C1 validation must include ordinary completion, legitimate reaction interruption, armed/pre-activation bad abandonment, `7 -> 7` inherited-stale scenarios, marked RIGHT/LEFT/BOTH/OFF behavior, repeated markers, and negative/no-op coverage for unrelated mechanics.

Especially protect:

- Fist;
- bow;
- crossbow;
- magic.

Fist can share melee action enums while not using weapon-style Item_Attack(7) source ownership.

---

## 13. Preference Order

1. **Preferred:** one event-driven execution-level guard using actual offensive requests, observed native cleanup, a durable C1 generation, and a lifetime-bound native outer-frame correlator.
2. **Preferred source model:** exact actor + equipped physical source ownership, including per-source obligations for dual/source-switch cases.
3. **Preferred outer context:** minimal/nesting-safe `RunScriptFunction` dispatch context only where needed for pre-CombatMove acquisition; generic script infrastructure must not become attack classification.
4. **Preferred validation:** keep the known bad held-Use2 abandonment intact as a destructive stress case until universal physical repair is proven, while legitimate reactions remain critical negative controls.
5. **Preferred compatibility:** preserve native/modded combat-rule choices; do not turn the collision system into a block-balance replacement.
6. **Preferred marker direction:** leave current marker lifetime/bookkeeping unchanged until universal guard + physical repair + regression pass; simplify only afterward if native lifetime is demonstrably stronger.
7. **Fallback:** investigate another native terminal class or root-cause external lifecycle repair only when a real reproduced case proves the general guard cannot safely cover it.
8. Avoid cause/family-specific production branches.
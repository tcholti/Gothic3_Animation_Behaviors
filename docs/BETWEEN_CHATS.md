# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Frozen Work task — C1 shadow execution-level collision lifecycle guard

**Date:** 2026-08-28  
**Branch:** `docs/collision-source-evidence`

### Purpose

Implement exactly one **shadow-only** execution-level collision lifecycle guard for the existing `Script_FrameCollisionTest` prototype.

The guard must model the production architecture now supported by B8/B9, but **must not physically repair collision yet**. At destructive finalization it may log `WOULD_REPAIR`; it must never call `SetCollisionGroup`, `RetireMarkerOwnedSource`, `ClearTriggeredList`, change `StatePosition`, suppress a callback, or otherwise alter game/marker behavior.

Preserve all existing B1–B9 diagnostics and all current collision/marker/source/callback/bookkeeping behavior.

---

## Native events / frozen semantics

### 1. Native CombatMove generation

Use the existing tested `Game +0x1696E0 = sAICombatMoveInstr` hook.

A **new CombatMove candidate** is only:

```text
a_bFullStop != GETrue
AND a_pArgs != nullptr
AND a_pSPU != nullptr
```

Resolve the actor from `a_pSPU->GetSelfEntity()` and snapshot the exact currently equipped RIGHT/LEFT source entities using the existing source resolver.

Create the candidate before calling the original so any synchronous source-group request made inside the initial native call can still be attributed.

Call the original exactly once and preserve its return value.

Tested binary semantics:

```text
original returns GEFalse -> CombatMove persists asynchronously -> keep/commit generation
original returns GETrue  -> instruction completed/rejected immediately -> cancel candidate
```

Generation identity is actor-instance + monotonically increasing generation number. Do not use action, phase, animation filename, Use2, state-name strings, Script_Game caller RVAs or attack-family classifiers as generation identity.

If a new candidate begins while the actor still has an older model record:

- if the older record has no outstanding obligation, retire it and start the new candidate;
- if it has any outstanding obligation, emit a C1 invariant warning (`OVERLAP_OUTSTANDING` or equivalent), retire only the old **shadow model** without touching collision, then continue with the new candidate so diagnostics remain usable.

Any overlap warning means the C1 architecture requires review before production repair is enabled.

### 2. Per-source lifecycle record

The new module should be a separate responsibility, preferably `CollisionLifecycleGuard.h/.cpp`, not mixed into marker occurrence logic.

For each actor generation retain only the minimum exact state:

```text
actor instance
generation
candidate/persisted status
RIGHT source instance snapshot
LEFT source instance snapshot
per source:
    offensive request count
    outstanding cleanup obligation
    observed transition out of Item_Attack / cleanup fulfillment
```

Maintain exact source -> actor/generation ownership only as lifecycle state needed to attribute `SetCollisionGroup`; it is not a general cache and must not require polling/scanning.

The module must remain actor-generic. Lifecycle state should not be Hero-only. Diagnostic output may remain player-focused to keep the test log bounded.

### 3. Offensive request creates/refreshes obligation

Reuse the existing central `SetCollisionGroup` hook. Observe lifecycle consequence **after the original call** so the actual resulting group is known.

For a source owned by a current candidate/persisted generation:

```text
requested group == Item_Attack
AND resulting group == Item_Attack
```

means that exact generation requested offensive collision for that exact source.

- increment that source's request count;
- set/keep its cleanup obligation outstanding;
- **7 -> 7 counts exactly the same as 5 -> 7**.

Do not require collision-group-before == 5.

Do not infer source ownership from filename/action/hand letters. Ownership comes only from the exact equipped source entity snapshot registered to that generation.

For the controlled player diagnostic, if an `Item_Attack` request succeeds on a source that is currently equipped by the player but C1 cannot attribute it to a current candidate/persisted generation, emit an `UNOWNED_PLAYER_OFFENSE_REQUEST` invariant warning. Do not repair or guess ownership.

### 4. Cleanup fulfillment

For a tracked source with an outstanding obligation, any observed `SetCollisionGroup` result that leaves the source **not** `Item_Attack` fulfills the physical cleanup obligation for that generation/source.

Record the fulfillment fact. Existing native-cleanup stack diagnostics remain unchanged.

At finalization, if an outstanding model flag somehow remains but the source's actual current group is already not `Item_Attack`, treat it as physically fulfilled/no repair and log that factual reconciliation rather than forcing a repair.

### 5. FullStop is not finalization

Do not mutate C1 lifecycle ownership merely because `sAICombatMoveInstr(..., fullStop=true)` or `AIFullStop()` occurs.

B7/B9 prove legitimate reactions and bad abandonment both FullStop active CombatMove. FullStop remains factual instruction-termination evidence only.

### 6. AISetState destructive finalization

Use the existing tested `Game +0x164320 = gCScriptRoutine_PS::AISetState(bCString const&)` hook.

Before the original call, capture only an exact C1 finalization token for the actor's current generation (invalid token if none). Existing B9 diagnostic capture remains unchanged.

Call the original AISetState exactly once with the unchanged real `bCString const&` argument.

**Evaluate C1 finalization after the original returns.** This is intentional: if AISetState itself performs/triggers legitimate source cleanup, the central `SetCollisionGroup` observation must get the final opportunity to fulfill the obligation before C1 decides anything.

Post-original:

- if the token is invalid: no lifecycle action;
- if the actor record/generation no longer matches the token: emit `FINALIZATION_GENERATION_CHANGED` (or equivalent), do not guess/repair;
- otherwise evaluate each tracked source.

For each source:

```text
no outstanding obligation
    -> NO_OP / already fulfilled

outstanding but actual source group != Item_Attack
    -> reconcile as physically clean / NO_OP

outstanding AND actual source group == Item_Attack
    AND source is still one of the actor's currently equipped RIGHT/LEFT source entities
    -> log WOULD_REPAIR for that exact source

outstanding AND actual source group == Item_Attack
    BUT source is no longer currently equipped
    -> log UNRESOLVED_NOT_EQUIPPED; do not guess the correct target group
```

After logging, retire that finalized generation and its source-ownership entries from the **shadow model**. `WOULD_REPAIR` therefore simulates lifecycle retirement only; the physical source must remain untouched in C1 shadow mode.

This prevents the shadow model itself from carrying a known stale obligation into later test generations while still leaving Gothic's real stale collision visible for runtime verification.

### 7. Pre-activation bad skip

A generation that never successfully requested `Item_Attack` has no obligation. Therefore a pre-activation FullStop/AISetState path must finalize with zero `WOULD_REPAIR` records.

No special pre-activation classifier is allowed.

### 8. Marker RIGHT / LEFT / BOTH / OFF

C1 must not know marker opcodes.

Existing marker behavior naturally feeds the same central consequence observer:

- RIGHT/LEFT/BOTH activation -> exact source `Item_Attack` requests create/refresh obligations;
- source switching / OFF -> actual source transition out of `Item_Attack` fulfills that source's obligation;
- a later marker reactivation creates/refreshes the obligation again;
- repeated `7 -> 7` marker requests remain attributable to the same current generation.

Do not change marker occurrence budgets, duplicate protection, StatePosition advancement, callback suppression, source switching, OFF behavior, or current marker-owned-window bookkeeping.

### 9. Marker retirement remains separate

Keep the existing `SetCollisionGroup` wrapper's `CollisionControl::RetireMarkerOwnedSource()` behavior exactly as it is for real physical transitions.

C1 shadow `WOULD_REPAIR` must **not** call it and must not manually retire marker bookkeeping.

Only a later production repair, if validated, may pass through the normal physical cleanup path and thereby allow existing marker retirement semantics to run naturally.

### 10. Negative scope / no extra lifecycle hooks

Do not add actor-destruction, unload, OnTick, ProcessScript, task, timer, polling, frame/world scan, input, state-name, successor, family, reaction or call-site hooks for C1.

Fist/bow/crossbow/magic must create no repair obligation unless an exact source registered to a real CombatMove generation actually receives a successful `Item_Attack` request. Do not add special-case classifiers for those mechanics in the shadow implementation; later runtime negatives will validate the consequence-based scope.

---

## Diagnostic output

Add concise C1 records sufficient to reconstruct the state machine, for example:

```text
===== C1 LIFECYCLE START =====
===== C1 OFFENSE REQUEST =====
===== C1 CLEANUP FULFILLED =====
===== C1 FINALIZATION =====
===== C1 INVARIANT WARNING =====
```

Finalization output must make `WOULD_REPAIR` versus `NO_OP` versus unresolved/invariant cases explicit and include actor, generation, exact source address/name if safely available, original source side/mask, request count, outstanding flag, actual current group, cleanup-observed fact, and whether the source is still currently equipped.

Add startup banner:

```text
STEP C1 SHADOW LIFECYCLE GUARD: event-driven execution/source obligations; WOULD_REPAIR only; no physical repair.
```

Do not remove or weaken existing diagnostic records/banners needed for B1–B9 comparison.

---

## Expected source scope

Prefer only:

```text
prototypes/Script_FrameCollisionTest/CollisionLifecycleGuard.h      (new)
prototypes/Script_FrameCollisionTest/CollisionLifecycleGuard.cpp    (new)
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp
prototypes/Script_FrameCollisionTest/CMakeLists.txt
```

Do not modify `CollisionControl.cpp/.h` or `FrameCollisionShared.h` unless an actual compile/API contradiction makes it unavoidable; if so, stop and report the exact contradiction instead of broadening the design silently.

---

## Forbidden in this Work task

- no physical collision repair;
- no `SetCollisionGroup` call from C1;
- no marker cleanup/retirement from C1;
- no new callback suppression or callback changes;
- no production INI/config;
- no family/action/state/input/caller classification;
- no timers/polling/per-frame/world scans;
- no ProcessScript/AIStopCombatMove/individual Script_Game call-site hooks;
- no actor lifecycle/destruction hooks;
- no marker-core simplification;
- no removal of B1–B9 diagnostics;
- no build or Gothic 3 runtime test in Work.

---

## Work completion

Read `docs/SESSION_ENTRYPOINT.md`, this file, and `docs/WORK_IMPLEMENTATION_PROTOCOL.md`, then implement only this frozen C1 shadow guard.

After editing:

1. perform a bounded source/diff audit against this contract;
2. run source hygiene checks appropriate to editable source/docs;
3. update this `BETWEEN_CHATS.md` with the implementation commit/result and any exact unresolved contradiction;
4. commit and push to `docs/collision-source-evidence`;
5. STOP. Do not build or run Gothic 3.

Normal Chat will independently review the diff, then handle build/load and freeze the C1 runtime matrix.

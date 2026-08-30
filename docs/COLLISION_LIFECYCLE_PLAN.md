# Collision Lifecycle Plan

**Status:** Current collision-lifecycle architecture / research authority  
**Updated:** 2026-08-30

## Purpose

Define the smallest authoritative rule that guarantees offensive collision cleanup without creating one repair branch per attack family or interruption symptom.

Detailed proof history belongs in `EVIDENCE_INDEX.md` and the evidence ledgers. Build-specific cleanup/control-flow locations belong in `COLLISION_CLEANUP_CALLSITE_MAP.md` and `SOURCE_HOOK_GUIDE.md`. Current staged validation belongs in `COLLISION_TEST_PLAN.md`.

---

## 1. Governing Invariant

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if proper cleanup already occurred, do nothing; otherwise repair only that execution's remaining offensive collision using native cleanup semantics.**

How the Hit ended is not part of the production rule. Normal completion, reaction interruption, state replacement, skipped Recover bookkeeping, terrain interruption and direct replacement are test cases for one lifecycle invariant.

The guard owns **collision safety**, not general combat-balance or state-machine policy.

---

## 2. Accepted Execution / Source Model

```text
REAL ATTACK EXECUTION X
        ↓
Acquire C1 monotonic generation
        ↓
Did X actually request offensive collision on source S?
   ├─ NO  → no obligation for S
   └─ YES → exact source obligation for X/S
        ↓
Did S successfully transition away from Item_Attack?
   ├─ YES → obligation fulfilled
   └─ NO  → obligation remains outstanding
        ↓
Is X destructively finalized?
        ↓
Outstanding exact source obligation?
   ├─ NO  → no-op
   └─ YES → if source liveness/current offense is established,
            repair only that source using native cleanup semantics
```

A successful request counts even when the physical source was already offensive (`7 -> 7`). A later legitimate execution must own its own request and later cleanup obligation rather than inheriting the earlier execution's ownership.

Conceptual state:

```text
Execution X
    actor
    monotonic C1 generation
    temporary native ScriptFunction correlator only where acquisition needs it
    exact physical source set
    per-source offensive-request / outstanding-cleanup state
    cleanup observation
    terminal finalization status
```

The system is event-driven. No polling, wall-clock lifetime inference or global actor scan.

---

## 3. Three Established Ending Structures

### A — ordinary completion

```text
attack ScriptFunction / CombatMove
→ native action-specific cleanup resets exact source away from Item_Attack
→ later state transition/finalization sees no outstanding obligation
→ no repair
```

### B — legitimate reaction interruption

```text
attack active
→ CombatMove may be FullStopped
→ separate reaction-side native cleanup resets exact source
→ later finalization sees fulfilled obligation
→ no repair
```

FullStop is therefore instruction termination, not cleanup authority.

### C — destructive continuation loss

Known stress case:

```text
attack ScriptFunction suspended around CombatMove
→ destructive path terminates instruction
→ AISetState replaces state / clears old continuation
→ no ordinary or reaction cleanup occurred
→ exact source may remain Item_Attack(7)
→ C1 finalization sees real outstanding source obligation
```

Held Use2 / ~2500 ms is a reliable test trigger for one known class, not production classification authority.

---

## 4. Execution Identity Authority

C1-O1/P1/P2 establish the accepted split:

```text
live ScriptFunction frame
= lifetime-bound native correlator only where early acquisition needs it

C1 monotonic generation
= durable plugin execution identity
```

The proven temporary correlator requires:

```text
exact SPU
+ live ScriptFunction frame
+ non-null m_pArguments
+ same ScriptFunction name
```

Raw frame/argument addresses can be reused after retirement and are not durable IDs.

P2 proved that a legitimate pre-Combat GetUp offense can acquire the C1 generation inside the live lightweight RunScriptFunction scope, and matching CombatMove can consume/retire that native binding **before** the wrapper returns/suspends. Cross-suspension native-frame persistence is not required for the tested model.

Do not restore the rejected eager dispatch vector/string machinery.

---

## 5. Ownership Authority by Responsibility

### Execution acquisition

Ordinary attacks may acquire through the existing CombatMove-created generation path.

When a real equipped-source offense occurs before CombatMove, C1 may lazily acquire from the proven live RunScriptFunction scope only after exact SPU/state-stack/frame/source validation.

No GetUp/family/action/input classifier is part of ownership.

### Collision obligation

A successful `Item_Attack` request by execution X creates/refreshes the obligation for the exact physical source requested by X.

### Native cleanup observation

Successful transition away from `Item_Attack` fulfills that source obligation. Do not infer cleanup from Recover, animation replacement, callback return, FullStop or state request.

### Terminal finalization

For a generation captured before native AISetState, the existing finalizer runs only **after native AISetState has executed**. This gives native/reaction cleanup inside the original call precedence. If that cleanup occurred, the obligation is already fulfilled and repair is forbidden.

### Source liveness

Remembered raw source pointers may not be dereferenced merely because they were once owned. After native AISetState, exact current equipped RIGHT/LEFT pointer identity must establish the remembered source as live before group observation or mutation.

### Dual/source specificity

Each source obligation is independent. One outstanding side never authorizes mutation of the other side.

---

## 6. Native Cleanup Semantics for Proven Weapon Sources

The tested native cleanup matrix shows legitimate weapon cleanup as:

```text
Item_Attack(7)
→ SetCollisionGroup(Item_Equipped)
→ Item_Equipped(5)
```

This exact reset was observed across the established ordinary melee action matrix and the tested legitimate reaction cleanup route.

The current marker OFF/source-deactivation implementation likewise uses `SetCollisionGroup(Item_Equipped)` and does **not** call `ClearTriggeredList()`.

Therefore:

> For the currently proven equipped weapon-source domain, the minimum native-equivalent physical cleanup mutation is exactly one `SetCollisionGroup(Item_Equipped)` call on the owned source that is still live/equipped and still physically `Item_Attack`.

`ClearTriggeredList()` remains activation/rearm behavior, not terminal cleanup.

Fist/body-source semantics remain separate and are not forced into weapon-style Item_Attack cleanup.

---

## 7. C1-O2-P2 — CLOSED

Canonical result: EV-205 plus dedicated same-binary shutdown closure.

P2 establishes:

```text
pre-Combat exact offense
→ lazy C1 generation acquisition
→ matching CombatMove reuses same generation
→ temporary native binding consumed before RunScriptFunction return
→ durable source obligation continues on monotonic generation
```

Broad P2-D runtime evidence accounted for 293 observed offensive source obligations exactly as:

```text
264 observed cleanup fulfillments
+ 29 shadow WOULD_REPAIR outcomes
= 293
```

No C1/P2 binding/invariant failure signal occurred in that broad run.

Do not add:

```text
cross-suspension native-frame binding
family/action/input ownership tables
null-arguments fallback
arbitrary adoption of unrelated group-7 state
polling/timers/world scans
```

---

## 8. C1-R1 Controlled Physical Repair — CLOSED

Canonical result: EV-206–EV-207.

C1-R1 changes **only** the already-proven shadow `WOULD_REPAIR` branch.

Exact decision:

```text
outstandingCleanup == false
→ NO_OP_NO_OUTSTANDING

outstandingCleanup == true
+ source not exact current equipped RIGHT/LEFT
→ UNRESOLVED_NOT_EQUIPPED
→ no dereference / no mutation

outstandingCleanup == true
+ liveness established
+ actual group != Item_Attack
→ NO_OP_PHYSICALLY_CLEAN_RECONCILED

outstandingCleanup == true
+ liveness established
+ actual group == Item_Attack
→ SetCollisionGroup(Item_Equipped) exactly once on that source
→ no ClearTriggeredList()
→ verify result exactly Item_Equipped(5)
```

Successful outcome:

```text
REPAIRED_TO_ITEM_EQUIPPED
```

Any setter result other than exact group 5 remains a divergence/failure. C1-R1 does not retry or invent fallback mutation.

### Validated meaning

R1-A through R1-E established:

```text
exact positive stale-source 7 -> 5 repair
ordinary / reaction / pre-activation no-op behavior
P2 GetUp cleanup precedence
GetUpParade defensive no-offense
Dual RIGHT/LEFT source independence
marked-source terminal repair and dead-execution callback rejection
broad mixed player/NPC hook stability
unsupported marker-bearing fallback
Fist/body separation
crossbow unsupported-source negative behavior
supplemental bow/magic negative regression
```

The focused final R1-E run contains zero repair, divergence, unresolved-not-equipped or C1 invariant-warning records while exercising the remaining unsupported-source negatives. Therefore the controlled C1-R1 validation gate is closed; do not invent another broad R1 matrix.

Two limits remain explicit and do not reopen the gate:

```text
- no positive runtime exercise of an outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED branch;
- no positive NPC destructive-abandonment / physical-repair case is claimed.
```

### Repair passes through existing SetCollisionGroup observation

Do not bypass the already-tested SetCollisionGroup hook. The normal setter path continues to own:

- engine collision transition observation;
- source-obligation transition observation;
- existing marker-owned source retirement behavior.

No second repair dispatcher or parallel cleanup API is needed.

### Finalizer logging order

A repair setter can synchronously enter the existing SetCollisionGroup hook and emit diagnostics. Therefore the finalizer must not have an open half-written log block while mutation occurs.

Use two phases only:

```text
1. classify / repair into fixed stack-local per-source results (max 2)
2. emit the complete finalization diagnostic block afterward
```

This is diagnostic hygiene, not new lifecycle machinery.

---

## 9. Marker Timing Remains Separate

Inside a live marked Hit:

```text
RIGHT = {RIGHT}
LEFT  = {LEFT}
BOTH  = {RIGHT, LEFT}
OFF   = {}
```

Each marker defines the complete desired offensive equipped-source set at that authored moment. Repeated source markers rearm through `ClearTriggeredList()`.

`G3AB_COL_OFF` is an authored inactive gap inside a still-live Hit. It is not terminal safety and must not retire the execution by itself.

C1-R1 does not refactor marker occurrence budgets, duplicate protection, StatePosition handling or source-set semantics.

---

## 10. Production Restrictions / Regression Requirements

Do not default to:

- one cleanup hook per attack family;
- held-Use2 / timeout cleanup classification;
- unconditional cleanup on FullStop, AISetState or RunScriptFunction return;
- polling, per-frame/world scans or wall-clock timers;
- action/phase-only terminal authority;
- persistent raw-pointer identity after native-frame retirement;
- repair of every group-7 equipped item regardless of ownership;
- `ClearTriggeredList()` as terminal cleanup;
- rewriting external block/balance mechanics as a collision prerequisite.

Protect through production integration:

```text
ordinary native completion
legitimate reaction cleanup
pre-activation/no-offense cases
GetUpAttack P2 acquisition + native cleanup
GetUpParade/defensive no-offense
inherited 7 -> 7 attribution
Dual exact RIGHT/LEFT obligations
marked RIGHT/LEFT/BOTH/OFF behavior
Fist/body separation
bow/crossbow/magic negative regression
```

---

## 11. Universal-Guard-First Development Order

```text
stable shadow execution/source ownership        CLOSED through P2
→ controlled native-equivalent physical repair CLOSED through C1-R1 / EV-207
→ stable production integration                NEXT
→ only later reconsider marker-bookkeeping simplification
```

The next responsibility is to plan/freeze the smallest production integration of the validated guard/core. Integration must preserve the accepted execution/source model and existing marker behavior; it is not authorization to redesign lifecycle ownership.

The known held-Use2 / Alternative-AI skip remains a stress case rather than production classification authority. A future root-behavior investigation is separately preserved in `BAD_SKIP_FUTURE_INVESTIGATION.md`. Even if pursued later, it does not replace the C1-R1 collision-safety fail-safe and must not be folded automatically into production integration.

---

## 12. Preference Order

1. One event-driven execution/source guard.
2. Exact physical source ownership and per-source obligations.
3. Native cleanup always gets first opportunity.
4. Mutation only on the proven terminal outstanding-source predicate.
5. Exact native-equivalent `7 -> 5` reset for proven weapon sources.
6. No family/cause/input classification.
7. Preserve native/modded combat-rule choices.
8. Preserve proven marker core through production integration; simplify only later if a stronger native boundary is separately proven.
9. Investigate another terminal class/root-cause external repair only if a reproduced case proves the general guard insufficient.

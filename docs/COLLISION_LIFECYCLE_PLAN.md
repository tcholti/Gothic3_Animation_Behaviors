# Collision Lifecycle Plan

**Status:** Current collision-lifecycle architecture authority  
**Updated:** 2026-09-08

## Purpose

Define the smallest authoritative rule that guarantees equipped offensive collision cleanup without one repair branch per attack family or interruption symptom.

Detailed proof belongs in `EVIDENCE_INDEX.md`; staged validation in `COLLISION_TEST_PLAN.md`; build-specific cleanup locations in `COLLISION_CLEANUP_CALLSITE_MAP.md` / `SOURCE_HOOK_GUIDE.md`; overall module/order in `DESIGN.md`.

---

## 1. Governing Invariant

> For every real equipped attack-Hit execution that requests offensive collision, Gothic gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if proper cleanup already occurred, do nothing; otherwise repair only that execution's remaining exact offensive source using native cleanup semantics.

The guard owns collision safety, not input/combat policy.

---

## 2. Accepted Execution / Source Model

```text
real attack execution X
-> acquire monotonic C1 generation
-> successful exact-source Item_Attack request creates/refreshes X/S obligation
-> successful later transition away from Item_Attack fulfills X/S obligation
-> after native destructive finalization opportunity, inspect only outstanding obligations
```

A successful request counts even when the source was already offensive (`7 -> 7`). Dual source obligations are independent.

Durable identity:

```text
C1 monotonic generation
= plugin execution identity
= marker occurrence/dedupe execution identity
```

The live ScriptFunction frame/SPU/arguments/name correlator is temporary native context only where pre-Combat acquisition requires it. Raw frame/argument addresses are not durable IDs.

The system remains event-driven: no polling, wall-clock lifetime inference, or global actor scan.

---

## 3. Ending Structures

### Ordinary completion

```text
attack/CombatMove
-> native action-specific cleanup resets exact source away from Item_Attack
-> later finalization finds no outstanding obligation
-> no repair
```

### Legitimate reaction interruption

```text
attack active
-> CombatMove may FullStop
-> reaction-side native cleanup resets exact source
-> finalization finds obligation fulfilled
-> no repair
```

FullStop is instruction termination, not cleanup authority.

### Destructive continuation loss

Known stress class:

```text
attack ScriptFunction suspended around CombatMove
-> destructive FullStop/state replacement
-> old continuation discarded
-> ordinary/reaction cleanup may never run
-> exact equipped source may remain Item_Attack(7)
-> C1 finalization sees a real outstanding obligation
```

Held Use2 / ~2500 ms is a reproducible trigger for one known class, not production collision classification authority.

---

## 4. C1 Acquisition / Finalization Authority

Ordinary attacks may acquire generation through CombatMove. A proven pre-Combat equipped offense may lazily acquire through the live `RunScriptFunction` scope after exact SPU/state-stack/frame/source validation; matching CombatMove consumes/retires that temporary binding before wrapper return/suspension.

Successful transition away from `Item_Attack` is cleanup. Do not infer cleanup from Recover, animation replacement, callback return, FullStop, or state request.

For a generation captured before native `AISetState`, finalization runs only **after native AISetState returns**, giving native/reaction cleanup precedence.

Remembered raw source pointers may not be dereferenced after native state replacement without exact current-equipped RIGHT/LEFT identity establishing liveness.

---

## 5. Native Cleanup Semantics / C1-R1

For the proven equipped weapon-source domain, native-equivalent physical cleanup is:

```text
Item_Attack(7)
-> SetCollisionGroup(Item_Equipped)
-> Item_Equipped(5)
```

`ClearTriggeredList()` is activation/rearm behavior, not terminal cleanup.

Closed C1-R1 decision:

```text
outstanding == false
-> NO_OP_NO_OUTSTANDING

outstanding == true
+ source not exact current equipped RIGHT/LEFT
-> UNRESOLVED_NOT_EQUIPPED
-> no dereference / no mutation

outstanding == true
+ liveness established
+ actual group != Item_Attack
-> NO_OP_PHYSICALLY_CLEAN_RECONCILED

outstanding == true
+ liveness established
+ actual group == Item_Attack
-> SetCollisionGroup(Item_Equipped) once
-> verify exact Item_Equipped(5)
-> REPAIRED_TO_ITEM_EQUIPPED
```

Any other setter result is divergence; do not retry or invent fallback mutation.

C1-R1 validation is closed through EV-206–EV-207. Retained limits:

```text
no positive outstanding UNRESOLVED_NOT_EQUIPPED runtime case
no positive NPC destructive-abandonment physical-repair case claimed
```

These are claim limits, not open gates.

---

## 6. Marker Timing Is Separate From Lifecycle Repair

Inside a live marked equipped Hit:

```text
RIGHT = {RIGHT}
LEFT  = {LEFT}
BOTH  = {RIGHT, LEFT}
OFF   = {}
```

Each marker defines the complete desired equipped offensive set at that authored moment. Repeated source markers rearm via `ClearTriggeredList()`.

`OFF` is an intra-Hit inactive gap, not terminal finalization.

C1 generation supplies execution identity, but does not replace:

```text
exact current-motion ownership
supported family/action preflight
authored occurrence budgets
same-update duplicate/replay suppression
exact-set switching
physical marker-window state
repeated-contact rearm
StatePosition behavior
late/dead/unsupported rejection
native fallback
valid-motion-only caching
```

Gate 4 removed older marker-local guesses based on source/motion/action/phase/state-time changes or callback rollback. Natural `RetireMarkerOwnedSource()` handling retires only the exact physical marker-owned source bit/window.

---

## 7. Human Fist and Future PhysicalFist Separation

Production human `gEUseType_Fist` / raw 8 does **not** create an equipped `Item_Attack` obligation and does not use C1-R1 physical repair. Its native permission/latch mechanism is owned by the Fist behavior described in `DESIGN.md` and evidenced through EV-221–EV-240.

Future `gEUseType_PhysicalFist` / raw 55 remains unclassified. Do not assign weapon-style obligations or human-Fist lifecycle semantics until discovery proves the actual native mechanism.

---

## 8. AttackContinuationProtection Relationship

Bad-skip prevention remains separate from collision cleanup:

```text
AttackContinuationProtection
= prevent/defer the known destructive timeout consequence from killing a genuine active attack when that factual native condition becomes due

CollisionLifecycleGuard / C1-R1
= make an exact stale equipped source safe if cleanup is nevertheless lost
```

The future prevention module must be New Balance-compatible: if New Balance already prevents the destructive native condition, continuation protection should naturally do nothing.

Do not classify cleanup from the held-Use2 timer itself and do not merge continuation prevention into C1 ownership.

---

## 9. Production Restrictions

Do not default to:

- one cleanup hook per attack family;
- feature modules installing competing hooks on one Gothic function;
- timeout/input classification as collision ownership;
- unconditional cleanup on FullStop/AISetState/RunScriptFunction return;
- polling, world scans, or wall-clock repair timers;
- action/phase-only terminal authority;
- persistent raw-pointer identity after native-frame retirement;
- repair of every group-7 item regardless of ownership;
- `ClearTriggeredList()` as terminal cleanup;
- forcing human/monster body damage into equipped-source cleanup.

Protect through migration:

```text
ordinary native completion
legitimate reaction cleanup
pre-activation/no-offense
GetUpAttack pre-Combat acquisition + cleanup
GetUpParade/defensive no-offense
7 -> 7 attribution
Dual exact-source independence
marked RIGHT/LEFT/BOTH/OFF
human Fist separation
unsupported bow/crossbow/magic negatives
```

---

## 10. Development Order

Lifecycle architecture itself is closed. The surrounding collision roadmap is:

```text
bounded PhysicalFist/raw55 discovery
-> any deliberately accepted tractable extension
-> final native mixed collision regression
-> separate AttackContinuationProtection investigation/implementation
-> guard + marker + continuation regression
-> mandatory New Balance/Jackydima compatibility
-> production collision migration
```

Even if continuation prevention succeeds, C1-R1 remains the independent fail-safe.

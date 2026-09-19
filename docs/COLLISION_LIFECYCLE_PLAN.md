# Collision Lifecycle Plan

**Status:** Current collision-lifecycle architecture authority  
**Updated:** 2026-09-16

## Purpose

Define the smallest authoritative rule that guarantees offensive collision cleanup without one repair branch per attack family or interruption symptom.

Detailed proof belongs in `EVIDENCE_INDEX.md`; staged validation in `COLLISION_TEST_PLAN.md`; build-specific cleanup locations in `COLLISION_CLEANUP_CALLSITE_MAP.md` / `SOURCE_HOOK_GUIDE.md`; overall module/order in `DESIGN.md`.

---

## 1. Governing Invariant

> For every real physical attack-Hit execution that creates a source-specific offensive-collision obligation, Gothic gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if proper cleanup already occurred, do nothing; otherwise repair only an evidence-backed exact outstanding source using its proven native cleanup semantics.

The guard owns collision safety, not input/combat policy.

---

## 2. Accepted Execution / Source Model

For the proven equipped-source domain:

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

Raw8 Fist and PhysicalFist/raw55 have separate source semantics; neither may be forced into the equipped-source model by name alone. Their proven lifecycle consequences are stated explicitly below.

---

## 3. Ending Structures

### Ordinary completion

```text
attack/CombatMove
-> native action-specific cleanup resets exact source away from offensive state
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

Successful transition away from an evidence-backed offensive group is cleanup. Do not infer cleanup from Recover, animation replacement, callback return, FullStop, or state request.

For a generation captured before native `AISetState`, finalization runs only **after native AISetState returns**, giving native/reaction cleanup precedence.

Remembered raw source pointers may not be dereferenced after native state replacement without exact current-source identity establishing liveness under the source's proven rules.

---

## 5. Native Cleanup Semantics / C1-R1

For the proven equipped weapon-source domain, native-equivalent physical cleanup is:

```text
Item_Attack(7)
-> SetCollisionGroup(Item_Equipped)
-> Item_Equipped(5)
```

`ClearTriggeredList()` is activation/rearm behavior, not terminal cleanup.

Closed C1-R1 decision for equipped sources:

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

PhysicalFist/raw55 uses a real exact physical source in the accepted Troll/BlackTroll domain: `TrollFist`/raw55 transitions `Item_Equipped(5) -> Item_Attack(7)` under the frozen marked contract and later receives native exact `7 -> 5` cleanup. Permanent family/contact ownership is closed through EV-294 and focused acceptance through EV-298. No custom raw55 terminal-cleanup system is added; Gothic cleanup remains first authority and C1-R1 remains backup-only for an exact outstanding live/equipped source still at group7.

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

Raw55 repeated-contact timing is family-specific. Quick, Normal, true Power and Sprint-origin repeated-contact behavior is closed through EV-294; do not generalize one family's timing/rearm rule to another. Normal EV-291–EV-292 establishes the exact native between-contact clear ownership and its narrow permanent suppression/replacement behavior. These are contact semantics, not terminal lifecycle cleanup.

---

## 7. Raw8 Fist and PhysicalFist/raw55 Separation

Production `gEUseType_Fist` / raw 8 does **not** create an equipped `Item_Attack` obligation and does not use C1-R1 physical repair. Its native permission/latch mechanism is owned by the Fist behavior described in `DESIGN.md` and evidenced through the raw8 production chain.

`gEUseType_PhysicalFist` / raw 55 is now factually classified for tested Troll/BlackTroll attacks, but it remains a distinct mechanism:

```text
factual source          = exact TrollFist PhysicalFist/raw55
resting group           = Item_Equipped(5)
offensive group         = Item_Attack(7)
marker-authored opening = proven
native exact 7 -> 5     = proven cleanup
family contact/rearm    = not uniform
```

Quick repeated-contact behavior is closed through EV-273; Normal through EV-292; true Power through EV-293; Sprint-origin through EV-294. Permanent raw55 ownership is frozen in `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md` and focused acceptance is CLOSED/PASS at EV-298.

Do not assign raw8 latch semantics to raw55. Permanent raw55 uses its own family-specific marker/contact policy, preserves Gothic native final cleanup, and adds no independent terminal-cleanup mechanism.

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
- forcing raw8/body-damage semantics onto PhysicalFist/raw55 or equipped sources;
- assuming all PhysicalFist/raw55 families share one rearm/contact rule.

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
raw8 Fist separation
raw55 exact-source/native-cleanup facts
unsupported bow/crossbow/magic negatives
```

---

## 10. Development Order

Lifecycle architecture and permanent raw55 ownership are closed. The surrounding collision roadmap is:

```text
standalone collision regression — IN PROGRESS, EV-299–EV-305
-> finish remaining Phase-1 Golem setups
-> Orc / other weapon users / non-weapon creatures
-> Axe and Rapier separation-mod compatibility
-> stress regression
-> New Balance 0.7 bundle regression exactly as distributed, AttackCollision included
-> production collision migration
-> diagnostics-free integration validation
-> separate AttackContinuationProtection investigation/implementation when deliberately resumed
```

Even if continuation prevention later succeeds, C1-R1 remains the independent equipped-source fail-safe.

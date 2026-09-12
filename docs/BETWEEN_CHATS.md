# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-12

## Current Bridge — RAW55 PHYSICALFIST DESIGN / PROBE GATE

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat orientation:

```text
1. SESSION_ENTRYPOINT.md
2. FEATURE_DEVELOPMENT_METHOD.md
3. this file
4. troll raw log only as needed for exact runtime facts
5. DESIGN.md / COLLISION_TEST_PLAN.md only for deeper architecture/validation context
6. WORK_IMPLEMENTATION_PROTOCOL.md only after a bounded probe/production task is frozen
```

Project-wide rule:

```text
unknown mechanism -> isolated diagnostic probe
proven mechanism  -> permanent owning feature module
EngineBridge       -> hook transport/delegation only
final/broad tests  -> after known scope-changing design decisions are resolved
```

---

## Closed Starting Point

```text
production raw8 Sprint FIST support           CLOSED/PASS — EV-251
native Goblin/BlackGoblin 1H/raw2             CLOSED/PASS — EV-252
native Demon 2H/raw3                          CLOSED/PASS — EV-253
native Ogre Axe/raw52                         CLOSED/PASS — EV-254
Orc broad native raw52 control                CLOSED/PASS — EV-255
Orc Staff/raw51                               CLOSED/PASS — EV-256
Orc raw8 Fist Normal/Power                    CLOSED/PASS — EV-257
Orc Hack vs FinishingAttack separation        CLOSED/PASS — EV-258
```

Production raw8 behavior remains untouched.

Validated diagnostic built/live SHA256:
`1A58C6CF4D98B02873A114A7AF6F1AA372B8A937B1EC60DDA3A221F52879F74F`

---

## Factual raw55 discovery

Active artifact:

`research/raw/2026.09.12_troll_collision_test.log`

Troll and BlackTroll factually expose:

```text
RIGHT TrollFist / UseType55 / group5
LEFT  TrollFist / UseType55 / group5
Raw8Fist=<none>
```

Observed native tested attack behavior repeatedly uses the RIGHT raw55 source as the bookkeeping collision source:

```text
5 -> 7 offense
Game.dll+0x69484 TouchDamage-style damage when contact occurs
7 -> 5 native cleanup
clean C1 obligation/finalization
```

Do **not** interpret RIGHT as the damaging limb. Earlier Fist testing established that fist/body attacks can connect through multiple limbs, and animation-name `L/R` has not been proven to identify physical source side.

Current `G3AB_COL_FIST` rejects raw55 because it resolves only factual raw8. That rejection is expected under the current production boundary.

The Troll run also shows PowerAttack-named motion executing factually as Action9 / SPRINT. Native action remains semantic authority.

No `Troll_Stand_None_Fist...` motion was exercised. Do not investigate unused animation files merely from naming unless a runtime need appears.

---

## Why validation is paused

The broader native Fist sweep was intended to validate the final collision product broadly. Raw55 is now a concrete relevant mechanism that may be added to that product.

Therefore:

```text
STOP broad creature certification
-> classify raw55
-> decide defer/reject vs implement
-> if implementing, prove mechanism with isolated probe
-> implement clean permanent module
-> focused acceptance
-> resume broad validation on the intended final candidate
```

Continuing the full sweep first and then materially changing FIST behavior would weaken the meaning of those tests.

---

## Current design direction

Preferred author-facing contract if feasible:

```text
G3AB_COL_FIST
    raw8 source  -> Raw8FistCollision
    raw55 source -> separate PhysicalFist mechanism
```

Do not add `BIG_FIST` / `GROUP_FIST` merely to mirror an internal engine implementation unless evidence proves animators need a distinct authoring semantic.

Raw55 is currently expected to be physically closer to equipped group-based collision than to raw8:

```text
raw55 starts group5
native offense requests group7
native cleanup returns group5
existing C1 already tracks exact source obligation/cleanup
```

Do not reuse raw8 latch/timing logic for raw55.

---

## First causal question to freeze

Before production implementation, answer only:

> Can an exact marked factual raw55 execution suppress the native attack callback's physical activation without breaking the attack's normal animation/state/recover/next-attack progression?

Preferred temporary structure:

```text
PhysicalFistProbe.cpp/.h
    diagnostic-only build responsibility
    identifies exact marked raw55 fixture
    owns temporary suppression decision/state/logging

EngineBridge
    existing hook owner
    smallest delegation seam only
    no raw55 policy/state machine

Raw8FistCollision
    unchanged
```

Probe behavior should suppress only the native marked raw55 callback activation. **Do not yet activate raw55 at FIST in the same causal step.**

Expected positive result:

```text
marked raw55 attack
native callback activation suppressed
no native pre-marker TrollFist 5->7
no pre-marker raw55 damage
attack progression/recover/next attacks remain healthy
```

If this fails, return to design rather than accumulating compensating code.

If it passes, freeze a production contract for a dedicated permanent `PhysicalFistCollision` (or equivalent) module, implement only proven behavior, remove the temporary probe, then run focused acceptance before resuming broad tests.

---

## Other September 12 observations

```text
Stalker native baseline:
  factual Axe/raw52
  marked Normal/Power healthy

fall damage:
  no missing Fist/raw55 classification discovered

BluntArrow / BluntBolt:
  factual UseType4 / UseType7
  not raw55
```

Do not expand the fall/projectile discovery matrix.

---

## Later compatibility sequence

After raw55 disposition and resumed native validation:

```text
Axe separation: Hero/humans, Orc, Demon, Ogre, Stalker
Rapier separation: Hero/humans
Zombie-specific animation mod
```

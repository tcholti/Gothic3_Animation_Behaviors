# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-12

## Current Bridge — FROZEN RAW55 CALLBACK-SUPPRESSION PROBE

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat orientation:

```text
1. SESSION_ENTRYPOINT.md
2. FEATURE_DEVELOPMENT_METHOD.md
3. COLLISION_RAW55_CALLBACK_SUPPRESSION_PROBE.md
4. this file
5. troll raw log only as needed for exact runtime facts
6. WORK_IMPLEMENTATION_PROTOCOL.md only for the bounded implementation task
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
-> prove suppression mechanism with isolated probe
-> decide defer/reject vs production implementation
-> if implementing, build clean permanent module
-> focused acceptance
-> resume broad validation on the intended final candidate
```

Continuing the full sweep first and then materially changing FIST behavior would weaken the meaning of those tests.

---

## Frozen causal probe

Authority:

`docs/COLLISION_RAW55_CALLBACK_SUPPRESSION_PROBE.md`

Question:

> Can an exact marked factual raw55 execution suppress the native attack callback's physical activation without breaking the attack's normal animation/state/recover/next-attack progression?

Frozen temporary structure:

```text
PhysicalFistProbe.cpp/.h
    diagnostic-only
    exact raw55 eligibility
    temporary suppression decision
    temporary probe logging

EngineBridge
    existing hook owner
    minimal diagnostic-only delegation seam
    no raw55 policy/state machine

Raw8FistCollision
    unchanged
```

Eligible scope is deliberately bounded to factual marked raw55:

```text
Normal
Quick
Sprint / Action9 through OnAI_PowerAttack
```

No Power/Action2 raw55 behavior is inferred.

The exact intervention is only:

```text
eligible marked raw55 callback
-> suppress original native OnAI_* callback
```

The probe explicitly does NOT:

```text
activate raw55 at FIST
set group7/group5 itself
ClearTriggeredList
write raw8 latch/timing state
change StatePosition
change marker processing
add damage/target logic
add a new hook/RVA
```

The later authored FIST should still be reached and should still report raw55 unsupported/missing-source in this probe.

Expected PASS:

```text
probe suppression logged
no pre-marker TrollFist 5->7
no pre-marker raw55 damage
attack animation/state continues
recover/transition healthy
later attack generations continue
non-raw55 behavior unchanged
```

If suppression breaks progression or exposes a missing native side effect, return to Normal Chat. Do not add compensating behavior inside the probe or EngineBridge.

Even a perfect PASS does not authorize production raw55 support. Normal Chat must first freeze the permanent `PhysicalFistCollision` production contract; a separate Work task then implements it and removes the temporary probe.

---

## Expected Work scope for this probe

```text
NEW  prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
NEW  prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h
EDIT prototypes/Script_FrameCollisionTest/EngineBridge.cpp
EDIT prototypes/Script_FrameCollisionTest/CMakeLists.txt
```

Probe files must compile only into `Script_FrameCollisionTest`, never into `Script_FrameCollisionBehaviorTest`.

Work source/static audit only unless the launcher explicitly authorizes build execution.

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

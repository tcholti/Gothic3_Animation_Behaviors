# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-11

## Current Bridge — ORC NATIVE EXTENSION CLOSED; BROAD NATIVE FIST CREATURE SWEEP NEXT

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat orientation:

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_TEST_PLAN.md §8
4. EVIDENCE_LEDGER_250_ONWARD.md (EV-255–EV-258 are the latest closure)
5. WORK_IMPLEMENTATION_PROTOCOL.md only if a later bounded code task is frozen
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

Sprint production implementation remains:
`270d98f59fd7f83ab332d7cfbfc07d243273e0ca`

Validated diagnostic built/live SHA256 remains:
`1A58C6CF4D98B02873A114A7AF6F1AA372B8A937B1EC60DDA3A221F52879F74F`

No code changed after that production binary. No rebuild is needed for the next native validation runs.

---

## Orc closure details

### EV-255 — Orc broad raw52 control

The Orc used broad native `2H` animation naming while factual collision source was `It_Axe_OrcSword_01 / UseType 52`. This is normal native Gothic 3 architecture: factual weapon classification may be more specific than the broad 1H/2H animation-family selection.

Observed marked families included Normal, Quick L/R, Power and Whirl. Exact-source RIGHT ownership repeatedly followed `5 -> 7 -> 5`; Whirl also preserved `RIGHT -> OFF -> RIGHT`. FinishingAttack traffic remained native/marker-free in this fixture. No collision anomaly or repair was observed.

The later weapon-pickup crash is dispositioned outside collision: the Orc collision state had already finalized with no outstanding source, and the crash occurred in `SharedBase.dll`, not the collision DLL. Do not pursue unless it reproduces independently in ordinary play.

### EV-256 — Orc Staff/raw51

`Montera_Orc_01` used factual `It_Halberd_Orc_01 / UseType 51`. Marked Staff Normal, both Quick directions, Power and Whirl followed healthy accepted RIGHT `5 -> 7 -> 5` behavior with native contact/damage where exercised and clean C1 finalization.

### EV-257 — Orc raw8 Fist

Orc Fist resolved factual raw8/group0. Marked Normal and Power used the established shared raw8 mechanism: initial latch close, accepted FIST rearm, bounded early timing permission where required, native `Game.dll+0x16E348` damage, and no equipped-source obligation. No Orc-specific behavior is required.

### EV-258 — Hack vs FinishingAttack

This was independently confirmed for Orcs:

```text
same native _AI_HackAttack transport / Action 14

...FinishingAttack... motion
-> MarkerPresent=0
-> RequiredMask=0
-> SuppressNative=0
-> native behavior

...HackAttack... motion
-> Family=HACK
-> MarkerPresent=1
-> RequiredMask=1
-> RIGHT accepted
-> exact source 5 -> 7 -> 5
```

So actual motion routing, not callback/action name alone, correctly separates HackAttack from FinishingAttack.

Processed artifacts:

```text
research/archive/2026.09.11_orc_2h_native_control.log
research/archive/2026.09.11_orc_2h_pickup_crash_ge3log12.log
research/archive/2026.09.11_orc_staff_fist_native_control.log
research/archive/2026.09.11_orc_hack_native_control.log
```

---

## Next responsibility — broad native Fist creature sweep

The User has prepared marked animations for many native creatures, estimated roughly 70–80% of the creatures in the game. This is intentionally broad but not exhaustive.

Goal:

```text
prove the existing raw8 FIST marker mechanism broadly across native creature families
and let compact CORE diagnostics reveal any genuinely unknown action/family behavior
without inventing species-specific logic
```

For each practical creature test, interpret:

```text
actor / animation family
factual source + UseType
factual Action / resolved family
FIST ownership / latch behavior
native damage path when contact occurs
C1 finalization
any unknown/rejected/anomalous family
```

Separate logs by creature family or manageable fixture where practical so any discovery remains attributable.

If a new factual action/family appears, stop only that path for classification before changing behavior. Do not generalize from animation filenames.

---

## After creature sweep — bounded unresolved-Fist checks

Run exactly two short observational checks:

```text
A. Hero takes meaningful fall damage from a high fall.
B. Hero attacks an enemy with the special blunt arrow.
```

Question: does either event expose the unresolved other Fist/PhysicalFist-style action/source classification?

If yes, classify the factual action/source before deciding whether it is collision-marker relevant.
If no, leave the unresolved case deferred. Do not add more speculative probes.

---

## Later mod compatibility sequence

Axe animation-separation compatibility will be tested more strongly than first planned, with one quick attributable log for each family that receives unique Axe animations:

```text
Hero / humans
Orc
Demon
Ogre
Stalker
```

Rapier animation separation is Hero/humans only.

Zombie compatibility will later test the modded Zombie-specific animation family; native Zombies otherwise use the Hero family.

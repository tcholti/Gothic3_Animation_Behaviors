# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-11

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Completed Sprint implementation contract: `docs/COLLISION_SPRINT_RAW8_IMPLEMENTATION.md`  
Architecture/redesign authority: `docs/COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`  
Overall architecture: `docs/DESIGN.md`  
Validation: `docs/COLLISION_TEST_PLAN.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`; latest continuation: `docs/EVIDENCE_LEDGER_250_ONWARD.md`

---

## Closed Collision Boundary

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
collision architecture verification        CLOSED/PASS — EV-208–EV-215
Power                                      CLOSED/PASS — EV-241
Pierce                                     CLOSED/PASS — EV-242
SimpleWhirl                                CLOSED/PASS — EV-217–EV-220, EV-243
Hack tested 2H/Staff scope                 CLOSED/PASS — EV-216, EV-244
PhysicalFist/raw55 bounded discovery       CLOSED/DEFERRED — EV-245–EV-246
raw8 FIST Normal + Power + Quick scope     CLOSED/PASS — EV-221–EV-249
Stage A/B compact equivalence sentinel     CLOSED/PASS — EV-250
raw8 FIST Sprint production support        CLOSED/PASS — EV-251
native NPC 1H/raw2 control                 CLOSED/PASS — EV-252
native NPC 2H/raw3 control                 CLOSED/PASS — EV-253
native NPC Axe/raw52 control               CLOSED/PASS — EV-254
Orc broad raw52 native control             CLOSED/PASS — EV-255
Orc Staff/raw51 native control             CLOSED/PASS — EV-256
Orc raw8 Fist Normal/Power control         CLOSED/PASS — EV-257
Orc Hack vs FinishingAttack separation     CLOSED/PASS — EV-258
```

Raw8 FIST remains one shared native mechanism across the proven Normal, Power, Quick and Sprint family scope. Marker applicability is not species-gated. No authored FIST_OFF, Fist ClearTriggeredList, equipped Fist window/C1 weapon obligation, direct/custom damage, species branch, or raw55 generalization.

Sprint production implementation remains `270d98f59fd7f83ab332d7cfbfc07d243273e0ca`. No production behavior code changed after that commit; later work is runtime evidence/documentation only.

Validated diagnostic built/live SHA256 remains:
`1A58C6CF4D98B02873A114A7AF6F1AA372B8A937B1EC60DDA3A221F52879F74F`.

---

## Orc native extension — CLOSED/PASS

The User has now exercised every prepared native Orc animation type needed for the present collision question.

Evidence:

```text
EV-255  Orc 2H animation-family / factual Axe raw52 broad control
EV-256  Orc Staff / factual raw51 control
EV-257  Orc raw8 Fist Normal + Power control
EV-258  Orc actual HackAttack vs FinishingAttack separation
```

Important native-animation interpretation:

```text
Gothic 3 may classify weapons more specifically by factual UseType
while still selecting broad 1H / 2H animation families.
Staff happens to have its own native animation set.
Do not infer factual collision-source type from animation-family naming.
```

The Orc 2H control crash occurred only after combat when the User tried to pick up the defeated cheat-spawned Orc's weapon. Collision state had already finalized cleanly; the crash address was in `SharedBase.dll`, not `Script_FrameCollisionTest.dll`, with no collision-DLL stack frame. Treat it as non-collision unless independently reproduced in ordinary play.

Processed Orc evidence is archived under `research/archive/`.

---

## Current Immediate Responsibility — BROAD NATIVE FIST CREATURE SWEEP

The next activity is a broad native-creature validation of the existing raw8 FIST marker mechanism.

The User has prepared marked animations for many, but not all, native creatures — estimated coverage roughly 70–80% of the creatures in the game. The purpose is not exhaustive species certification. It is to build broad cross-creature evidence that the same marker mechanism remains actor-general and to give CORE diagnostics a chance to expose previously unknown action/family behavior, as happened with SprintAttack.

Use the existing diagnostic binary; no rebuild is required unless a concrete contradiction appears.

For each practical creature fixture, record:

```text
actor / animation family
factual source + UseType
factual action/family
accepted FIST behavior when marked
native damage path when contact occurs
C1 finalization
unknown/rejected/anomalous action-family traffic
```

Do not add species-specific behavior merely because a new creature family appears.

---

## After the native Fist sweep — exactly two bounded classification checks

After the prepared native-creature sweep is finished, run only these two short discovery checks for the still-unresolved other Fist/PhysicalFist-style classification question:

```text
1. fall damage:
   make Hero take meaningful damage from a high fall
   inspect action/source/damage classification

2. special blunt arrow:
   hit an enemy with the special blunt arrow
   inspect action/source/damage classification
```

These checks are observational only. If neither exposes the unresolved classification, leave it unresolved/deferred and do not expand the probe matrix.

---

## Later compatibility work already planned

After native creature/Fist work and the two bounded checks:

```text
Axe animation-separation mod:
  quick separate validation logs for Hero/humans, Orc, Demon, Ogre, Stalker
  (the mod supplies unique Axe animations for all five families)

Rapier animation-separation mod:
  Hero/human family only

Zombie animation mod:
  validate the modded Zombie-specific animation family;
  native Zombies otherwise reuse Hero-family animations
```

For the Axe mod, the stronger five-family pass is intentional compatibility coverage, not a claim that marker mechanics should become actor-specific.

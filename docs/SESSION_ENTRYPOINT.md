# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-11

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Completed Sprint implementation contract: `docs/COLLISION_SPRINT_RAW8_IMPLEMENTATION.md`  
Completed Sprint transport probe contract: `docs/COLLISION_SPRINT_TRANSPORT_PROBE.md`  
Architecture/redesign authority: `docs/COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`  
Overall architecture: `docs/DESIGN.md`  
Diagnostics: `docs/COLLISION_LOGGER_PLAN.md`  
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
Stage A architecture build/load gate       CLOSED/PASS — 2026-09-10
Stage B diagnostic build/load gate         CLOSED/PASS — 2026-09-10
Stage A/B compact equivalence sentinel     CLOSED/PASS — EV-250
Sprint transport observability probe       CLOSED/PASS — 2026-09-11
raw8 FIST Sprint production support        CLOSED/PASS — EV-251
native NPC 1H/raw2 equipped control        CLOSED/PASS — EV-252
native NPC 2H/raw3 equipped control        CLOSED/PASS — EV-253
native NPC Axe/raw52 equipped control      CLOSED/PASS — EV-254
native equipped-NPC §8.1 trio gate         CLOSED/PASS — EV-252–EV-254
```

Raw-8 FIST remains one shared native mechanism across the proven Normal, Power, Quick and Sprint scope. No authored FIST_OFF, Fist ClearTriggeredList, equipped Fist window/C1 weapon obligation, direct/custom damage, species branch, or raw55 generalization.

Stage A behavior architecture implementation: `7c5874932cd6eafa5af3414c65a4442b3d74bb73`.  
Stage B diagnostic implementation: `5737db32e5eda76810989ddfb5659f8405c0c458`.  
Sprint production implementation: `270d98f59fd7f83ab332d7cfbfc07d243273e0ca`.  
Validated diagnostic built/live SHA256: `1A58C6CF4D98B02873A114A7AF6F1AA372B8A937B1EC60DDA3A221F52879F74F`.

No production behavior code changed after the Sprint implementation; subsequent commits are runtime evidence and documentation only.

---

## Native equipped-NPC §8.1 controls — CLOSED/PASS

Authority:

```text
docs/COLLISION_TEST_PLAN.md §8.1
```

Closed controls:

```text
EV-252: Goblin / BlackGoblin -> factual 1H / raw2      CLOSED/PASS
EV-253: Demon                -> factual 2H / raw3      CLOSED/PASS
EV-254: Ogre                 -> factual Axe / raw52    CLOSED/PASS
```

Across the three controls, factual RIGHT equipped sources followed the established contract: Item_Equipped group 5, accepted RIGHT marker, exact-source `5 -> 7`, one offense request / `Clears=1`, native contact where exercised, native cleanup `7 -> 5`, and clean C1 finalization. No control required C1-R1 repair or exposed an invariant/source-resolution failure.

During the user's attempt to interrupt the Demon in the middle of attacks, one captured Power sequence additionally showed native cleanup `7 -> 5` completing before `_AI_Stumble` replaced the execution with `ReplacedOutstanding=0`. This was an ordinary mid-attack interruption attempt; the cleanup-before-reaction sequence was an incidental useful lifecycle observation, not the user's attempt to reproduce destructive continuation loss.

Processed evidence:

```text
research/archive/2026.09.11_goblin_1h_native_equipped_control.log
research/archive/2026.09.11_demon_2h_native_equipped_control.log
research/archive/2026.09.11_ogre_axe_native_equipped_control.log
```

---

## Current Immediate Responsibility — ORC MULTI-WEAPON NATIVE EXTENSION

The originally required §8.1 Goblin/Demon/Ogre gate is closed. The User has prepared marked Orc animations and wants to use Orcs as an intentional broader native-NPC validation because Orcs exercise more attack variety and multiple weapon types.

Run several separate Orc logs, keeping each log attributable to one weapon/setup where practical.

Purpose:

```text
broaden native-NPC evidence across Orc weapon/source and attack-family variety
without turning one mixed log into an ambiguous aggregate result
```

For each log, record factual equipped source / UseType, observed attack families, accepted marker/source transitions, native cleanup, C1 finalization, and any anomaly. Player counterattacks are allowed and can be separated by actor identity.

Do not treat the Orc extension as a prerequisite retroactively missing from §8.1. Do not modify behavior or diagnostics unless a concrete contradiction appears.

After the Orc extension is dispositioned, resume the standing sequence in `COLLISION_TEST_PLAN.md` rather than inventing additional matrix growth without a concrete compatibility question.

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
```

Raw-8 FIST remains one shared native mechanism across the proven Normal, Power, Quick and Sprint scope. No authored FIST_OFF, Fist ClearTriggeredList, equipped Fist window/C1 weapon obligation, direct/custom damage, species branch, or raw55 generalization.

Stage A behavior architecture implementation: `7c5874932cd6eafa5af3414c65a4442b3d74bb73`.  
Stage B diagnostic implementation: `5737db32e5eda76810989ddfb5659f8405c0c458`.  
Sprint production implementation: `270d98f59fd7f83ab332d7cfbfc07d243273e0ca`.  
Validated Sprint diagnostic built/live SHA256: `1A58C6CF4D98B02873A114A7AF6F1AA372B8A937B1EC60DDA3A221F52879F74F`.

---

## SprintAttack — CLOSED/PASS

EV-251 closes the focused evidence-backed raw8 Sprint responsibility.

Validated production facts for the tested native-Sabretooth case:

```text
factual action = 9 = gEAction_SprintAttack
semantic family = SPRINT
physical callback transport = existing OnAI_PowerAttack
phase = 1
marker-owned StatePosition = 1
motion = Sabretooth ... PowerAttack_Hit ...
marker = G3AB_COL_FIST
C1 generation = valid
source = Fist / gEUseType_Fist / raw8 / group0
RequiredSourceMask = 0
initial close = 0 -> 1
accepted FIST rearm = 1 -> 0
timing permission = existing raw8 mechanism
Sprint C1 finalization = clean / no equipped obligation
```

The production implementation remains deliberately bounded:

- Sprint is a first-class semantic family, not a Power alias;
- no new physical hook exists;
- factual actor routine Action 9 is the Sprint identity;
- current supported Sprint scope is raw8 `G3AB_COL_FIST` only;
- equipped Sprint RIGHT/LEFT/BOTH/OFF remains unsupported and unevidenced;
- no AI/distance rule is encoded or required;
- no raw55 or custom damage behavior is added.

Processed validation evidence:

```text
research/archive/2026.09.11_sprint_raw8_production_validation.log
```

---

## Current Immediate Responsibility — NATIVE EQUIPPED-NPC CONTROLS

Authority:

```text
docs/COLLISION_TEST_PLAN.md §8.1
```

Run separate evidence logs for:

```text
Goblin -> factual 1H / raw2
Demon  -> factual 2H / raw3
Ogre   -> factual Axe / raw52
```

Purpose:

```text
confirm equipped marker ownership follows factual equipped source/action semantics
for native NPC attackers as well as the already-proven player-side cases
```

Keep each actor in a separate log so any failure remains attributable. Use the existing compact CORE diagnostic product; do not add new behavior or diagnostics unless a concrete contradiction appears.

Do not broaden this gate into Sprint AI-selection research, raw55, final mixed regression, Raise, speed, or AttackContinuationProtection.

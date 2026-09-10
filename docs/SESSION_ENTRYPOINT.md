# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-10

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Architecture/redesign authority: `docs/COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`  
Stage B contract: `docs/COLLISION_STAGE_B_DIAGNOSTIC_REFACTOR.md`  
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
```

Raw-8 FIST remains one shared native mechanism. No authored FIST_OFF, Fist ClearTriggeredList, equipped Fist window/C1 weapon obligation, direct/custom damage, species branch, or raw55 generalization.

---

## Architecture + Diagnostic Refactor — CLOSED/PASS

Stage A behavior architecture implementation:

```text
7c5874932cd6eafa5af3414c65a4442b3d74bb73
Refactor collision behavior ownership boundaries
```

Stage B diagnostic implementation:

```text
5737db32e5eda76810989ddfb5659f8405c0c458
Refactor Stage B collision diagnostics
```

Both stages passed independent source review, local Release builds, exact diagnostic-DLL deployment hash verification, load/hook-install/clean-unload smoke, and the post-refactor compact equivalence sentinel.

Stage B validated diagnostic DLL SHA256:

```text
081CDF413EC623079B8E4F1934EA7F1C27A7FFC7307B3BA0B19EA000BDA108BD
```

EV-250 closes the refactor parity gate. The compact sentinel preserved:

```text
raw8 FIST Normal + Quick + Power on native/transformed Sabretooth
ordinary equipped marked attacks
equipped RIGHT -> OFF -> RIGHT rearm lifecycle
exact C1-R1 bad-skip terminal repair 7 -> 5
compact healthy CORE output
rich unsupported/anomaly output
```

No C1 invariant warning, repair divergence or raw8 timing anomaly was found in the sentinel logs. Both runs unloaded cleanly.

---

## SprintAttack Discovery — CURRENT OPEN RESPONSIBILITY

Sprint remains deliberately unsupported.

EV-249 first exposed the missing family. EV-250's new compact diagnostic run confirms the discovery path repeatedly and more cleanly:

```text
actor: native Sabretooth
action: 9 = gEAction_SprintAttack
phase: 1
StatePosition: 1
motion: Sabretooth ... PowerAttack_Hit ...
marker: G3AB_COL_FIST
result: REJECTED_UNSUPPORTED_HIT
C1 generation: valid
RIGHT source: Fist
UseType: 8 / raw8
collision group: 0
```

The PowerAttack-named motion does not make this a PowerAttack. Factual action identity remains authoritative.

Current evidence does **not** establish:

```text
Sprint callback/transport ownership
whether Sprint uses an existing callback under another script name
whether raw8 Sprint traverses the exact same latch/timing route
whether equipped Sprint exists
whether Sprint occurs for actors other than the tested native Sabretooth
```

Do not implement `AttackFamily_Sprint`, alias Sprint to Power, add a Sabretooth exception, or begin the broad Goblin/Demon/Ogre matrix yet.

---

## Current Immediate Responsibility — BOUNDED SPRINT RESEARCH / PLANNING

> **Normal Chat first determines SprintAttack's factual source/transport/mechanism boundary from current source/API/runtime evidence. No repository behavior edit is authorized yet.**

Investigate only what is required to answer:

```text
1. What script/native transport actually owns gEAction_SprintAttack?
2. Which factual source UseTypes are observed/possible in the bounded tested scope?
3. What StatePosition/action-phase contract does Sprint use?
4. Does raw8 Sprint traverse the same relevant SPU+0x164 / Game+0x16E180 / +0x16E1A3 / +0x16E348 mechanism?
5. Is practical equipped Sprint traffic evidenced by source/API/runtime material?
```

Use compact CORE first. Add DEEP instrumentation only if a specific required fact cannot be established otherwise.

Active Sprint evidence:

```text
research/raw/2026.09.10_sabertooth_npc_pc_marked_attacks_new.log
```

Processed EV-250 equipped sentinel evidence is archived:

```text
research/archive/2026.09.10_different_attacks.log
```

Only after the Sprint evidence boundary is frozen should Work receive a bounded implementation task, if implementation is justified at all.

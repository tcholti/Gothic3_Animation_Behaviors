# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-05

Immediate transient handoff: `docs/BETWEEN_CHATS.md`  
Project charter / highest Gothic-specific authority: `docs/README.md`  
Project collaboration/CAM operationalization: `docs/COLLABORATION_RULES.md`  
Stable conventions: `docs/PROJECT_PIPELINE.md`  
Recurring procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`  
Knowledge ownership: `docs/KNOWLEDGE_MAINTENANCE.md` / `docs/KNOWLEDGE_REGISTRY.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`

Local workstation/build/runtime paths: `docs/LOCAL_WORKSTATION_PATHS.md` (retrieve only when deployment paths matter)

---

## Authority / Release Boundary

CAM is the constitutional collaboration layer above this project. `docs/README.md` is the highest project-specific authority immediately beneath CAM.

> **Every released Gothic 3 behavior DLL contains behavior only. Research diagnostics are a separate build product and are not compiled into the release binary.**

Never normally load behavior-only and diagnostic collision twins together.

---

## Fresh Normal Chat / Work Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` for the exact active responsibility and frozen transient contract.
3. Work also reads `docs/WORK_IMPLEMENTATION_PROTOCOL.md` before bounded implementation.
4. Treat CAM -> project charter -> specialist authority and release purity as standing constraints.
5. Reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md` plus the owning subsystem authority when substantial reasoning requires it.
6. Retrieve `PROJECT_PIPELINE.md` before changing branch/test/evidence/procedure/version/artifact conventions.
7. Do not scan the whole repository or reconstruct the project from old chat history.
8. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.

After bootstrap, report briefly: current responsibility, relevant closed boundary, exact next step, and what remains deliberately outside scope.

---

## Closed Collision Architecture Boundary

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
Gate 1 source/build separation             CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency         CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke                 CLOSED/PASS — EV-212
Gate 4 generation-scoped bookkeeping       CLOSED/PASS — EV-213
literal historical EV-131 regression       CLOSED/PASS — EV-214
final behavior-only architecture smoke     CLOSED/PASS — EV-215
NEW COLLISION ARCHITECTURE VERIFICATION    COMPLETE
```

Do not reopen this architecture without concrete contradicting evidence.

Current equipped-melee expansion state remains:

```text
PowerAttack   CLOSED/PASS
PierceAttack  CLOSED/PASS
SimpleWhirl   CLOSED/PASS
HackAttack    isolated routing/source/marker validation PASS
```

Fist is a new source-adapter extension inside this closed architecture, not an architecture rewrite.

---

## Repository / Phase Boundary

```text
finish human Fist collision support on docs/collision-source-evidence
-> run final native mixed collision regression
-> run final New Balance + Script_AttackCollision mixed regression
-> complete collision knowledge/evidence closure
-> migrate mature collision behavior into Script_G3AnimationBehaviors
-> validate diagnostics-free collision integration
-> promote completed collision checkpoint to main
-> create feature/raise-attack-speed from updated main
```

Do not create `feature/raise-attack-speed` early.

---

## Current Responsibility — Fist Work A

The final collision regressions are temporarily postponed because human Fist support was identified as a missing collision feature that should be integrated before collision closure.

The full frozen implementation contract lives **once** in:

`docs/BETWEEN_CHATS.md`

Current bounded implementation stage:

```text
Work A — dedicated G3AB_COL_FIST baseline
```

Purpose:

```text
G3AB_COL_FIST
-> resolve proven human logical Fist source (gEUseType_Fist / raw 8)
-> dedicated Fist source operation
-> TouchDamage.ClearTriggeredList()
-> no weapon Item_Attack / Item_Equipped mutation
-> no DamageDisabled behavior yet
```

Important frozen separation:

```text
RIGHT / LEFT / BOTH / OFF
-> equipped-weapon source path
-> preserve unchanged

FIST
-> dedicated logical human Fist/body-contact source path
-> not SourceMask_Right/Left/Both
-> no SourceMask_Fist
```

Fist source selection must remain independent from attack-family selection. Existing Normal/Power/Quick/SimpleWhirl/Whirl/Pierce/Hack family semantics and StatePosition policies remain authoritative and unchanged.

The current branch source still contains the temporary `DamageDisabled=true` Fist causal probe from the earlier exploratory attempt. Work A must remove that probe and must contain **no DamageDisabled read/write behavior**.

Do not add `G3AB_COL_FIST_OFF` yet.

---

## Frozen Fist sequence after Work A

```text
A — dedicated FIST baseline
    prove the separated Fist route still damages using ClearTriggeredList only

B — one-variable DamageDisabled causal probe
    same proven FIST route + DamageDisabled=true

C — production FIST/FIST_OFF + exact baseline snapshot/restore lifecycle
    only after DamageDisabled is causally proven
```

After Work A publishes, Normal Chat independently reviews the diff against `BETWEEN_CHATS.md`. Then the authoritative home PC performs build/deploy/runtime validation.

---

## Deliberately outside Work A

- `G3AB_COL_FIST_OFF`;
- DamageDisabled reads/writes or diagnostics;
- persistent Fist marker-owned lifecycle state;
- Fist terminal/interruption restoration;
- PhysicalFist / monsters / generalized body collision;
- per-limb Fist markers;
- new attack actions or Quick-selection logic;
- attack-family / StatePosition redesign;
- C1 or weapon-lifecycle redesign;
- RIGHT/LEFT/BOTH/OFF behavior changes;
- Hack or SimpleWhirl changes;
- final mixed native/compatibility regression execution;
- Raise implementation;
- playback-speed redesign;
- target acquisition;
- climbing.

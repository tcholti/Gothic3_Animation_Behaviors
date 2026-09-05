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

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` for the exact active continuation.
3. Treat CAM -> project charter -> specialist authority and release purity as standing constraints.
4. Reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md` plus the owning subsystem authority when substantial reasoning requires it.
5. Retrieve `PROJECT_PIPELINE.md` before changing branch/test/evidence/procedure/version/artifact conventions.
6. Do not scan the whole repository or reconstruct the project from old chat history.
7. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.

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

Current equipped-melee expansion state:

```text
PowerAttack   CLOSED/PASS
PierceAttack  CLOSED/PASS
SimpleWhirl   CLOSED/PASS
HackAttack    isolated routing/source/marker validation PASS
```

Human Fist support is a source-adapter extension inside this closed architecture, not an architecture rewrite.

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

## Current Responsibility — Fist Stage A runtime validation

Work A source implementation is published as:

```text
5984738a41eca895900ae0929c3c930336c8ff53
Add dedicated Fist marker baseline
```

Normal Chat has independently reviewed the Work A diff against the frozen contract and found no material source-level contradiction.

Implemented Stage A contract:

```text
G3AB_COL_FIST
-> resolve proven human logical Fist source (gEUseType_Fist / raw 8)
-> dedicated Fist source operation
-> TouchDamage.ClearTriggeredList()
-> no weapon Item_Attack / Item_Equipped mutation
-> no DamageDisabled behavior
```

Important separation:

```text
RIGHT / LEFT / BOTH / OFF
-> equipped-weapon source path

FIST
-> dedicated logical human Fist/body-contact source path
-> not SourceMask_Right/Left/Both
-> no SourceMask_Fist
```

The temporary exploratory `DamageDisabled=true` mutation has been removed. `G3AB_COL_FIST_OFF` does not exist yet.

### Exact next step

Complete the authoritative home-PC Stage A validation:

```text
sync branch
-> build ONLY Script_FrameCollisionTest
-> deploy only the diagnostic collision twin
-> verify live SHA/startup
-> mark one known-good human Fist Hit with G3AB_COL_FIST at the proven timing
-> run one controlled valid-target contact test
-> preserve exact raw diagnostic log
-> interpret visual + logger evidence
```

Known historical fixture/timing for the first test:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
frame 3: G3AB_COL_FIST
```

Do not use `G3AB_COL_RIGHT` for Fist.

Stage A asks only whether the separated dedicated FIST route reproduces the already-proven damaging Fist behavior using `ClearTriggeredList()` alone.

---

## Frozen Fist sequence after Stage A

```text
A — dedicated FIST baseline
    current stage: local build/runtime validation

B — one-variable DamageDisabled causal probe
    only after A passes

C — production FIST/FIST_OFF + exact baseline snapshot/restore lifecycle
    only after B causally proves the mechanism
```

Stage B and Stage C are not authorized yet.

The full short-lived continuation, source-review facts, local-state caution and exact test boundary are in `docs/BETWEEN_CHATS.md`.

---

## Deliberately outside the immediate test

- `G3AB_COL_FIST_OFF`;
- DamageDisabled mutation until Stage A passes;
- persistent Fist marker-owned lifecycle state;
- Fist terminal/interruption restoration;
- PhysicalFist / monsters / generalized body collision;
- per-limb Fist markers;
- new attack actions or Quick-selection logic;
- attack-family / StatePosition redesign;
- C1 or weapon-lifecycle redesign;
- RIGHT/LEFT/BOTH/OFF behavior changes;
- Hack or SimpleWhirl redesign;
- final mixed native/compatibility regression execution;
- Raise implementation;
- playback-speed redesign;
- target acquisition;
- climbing.
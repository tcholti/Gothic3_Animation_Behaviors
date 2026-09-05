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

## Fist Stage A — CLOSED/PASS

Work A source implementation is published as:

```text
5984738a41eca895900ae0929c3c930336c8ff53
Add dedicated Fist marker baseline
```

Stage A runtime evidence is published as:

```text
91e6d4f81b5f8d549546686a6d308ddff3e3bd9f
Add Fist Stage A baseline runtime evidence
```

Validated diagnostic DLL SHA256:

```text
C9C6474D7A3EE6ABA0D260457DC85A597F5A7B1F614C01AD1A2BA15DDE890033
```

Validated fixture:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
frame 3: G3AB_COL_FIST
```

Stage A result:

```text
visual valid-target contact damage: YES
FIST accepted on valid C1 generation
logical Fist source resolved as gEUseType_Fist / raw 8
Fist collision group remained 0 -> 0
TouchDamage.ClearTriggeredList() occurred exactly once
no equipped-weapon source mask was activated/retired
no weapon collision-group request path was used by FIST
native callback was suppressed for the marker-owned execution
finalization had no outstanding weapon-style collision obligation
```

Therefore the separated dedicated FIST route reproduces the proven damaging human Fist contact using `ClearTriggeredList()` alone, without weapon Item_Attack / Item_Equipped mutation and without DamageDisabled behavior.

---

## Current Responsibility — Fist Stage B one-variable causal probe

Stage B is now authorized because Stage A passed. Its conceptual variable is deliberately singular:

```text
same proven dedicated FIST route
+ DamageDisabled = true
```

The question is only whether that otherwise-identical known-good Fist contact stops damaging.

### Exact next step

Freeze and execute a bounded Work B implementation that changes only the dedicated human FIST operation needed for this causal probe, then independently source-review it before local build/runtime validation.

Do not implement production `G3AB_COL_FIST_OFF` or persistent lifecycle ownership in Stage B.

---

## Frozen Fist sequence

```text
A — dedicated FIST baseline
    CLOSED/PASS

B — one-variable DamageDisabled causal probe
    CURRENT

C — production FIST/FIST_OFF + exact baseline snapshot/restore lifecycle
    only after B causally proves the mechanism
```

The full short-lived continuation and exact Stage B boundary are in `docs/BETWEEN_CHATS.md`.

---

## Deliberately outside the immediate Stage B responsibility

- production `G3AB_COL_FIST_OFF`;
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
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

Implementation:

```text
5984738a41eca895900ae0929c3c930336c8ff53
Add dedicated Fist marker baseline
```

Runtime evidence:

```text
91e6d4f81b5f8d549546686a6d308ddff3e3bd9f
Add Fist Stage A baseline runtime evidence
```

Validated fixture:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
frame 3: G3AB_COL_FIST
```

Stage A proved the separated dedicated FIST route reproduces damaging human Fist contact using `TouchDamage.ClearTriggeredList()` alone while preserving group `0 -> 0`, using no equipped-weapon source mask and creating no weapon-style C1 obligation.

---

## Fist Stage B — CLOSED/FAIL FOR DAMAGEDISABLED AS OFF MECHANISM

Temporary setter implementation:

```text
a8ce1487b53ff2f8e6b6b9d9e87ac36e2322c561
Add temporary Fist DamageDisabled causal probe
```

Exact readback implementation:

```text
933e652c7ee66a45b9cd826f249c93019c6248da
Add Fist DamageDisabled exact readback probe
```

Readback evidence:

```text
research/raw/2026-09-05_fist_stageb_damage_disabled_exact_readback.log
1f74a216b32008b968677af3d271694857e7aeba
SHA256 08A8D3D54BA878606D7C4BE5D0A4D022F85C7C5ACF9969F74845C2FAF6180152
```

Validated readback diagnostic DLL:

```text
SHA256 9D2BE5AC24F973F7EDEB2BD8183DB6D8CC458BF4BE9EC2F22776026D84172A09
```

Stage B established:

```text
visual valid-target contact damage: YES
first accepted FIST: DamageDisabled 0 -> 1
later accepted FIST executions: DamageDisabled 1 -> 1
same human gEUseType_Fist / raw 8 source
same Fist collision group 0 -> 0
same ClearTriggeredList behavior
no equipped-weapon source mask
```

Therefore `SetDamageDisabled(GETrue)` factually changes and persistently holds the exact resolved Fist TouchDamage property at true, but that state does **not** stop the tested human Fist damage path. `DamageDisabled` is rejected as the production `FIST_OFF` control mechanism for this path.

Do not infer the unresolved native reason. Do not build Stage C around `DamageDisabled`.

---

## Current Responsibility — restore Stage A FIST behavior

The currently published prototype source still contains the temporary Stage B setter/readback experiment. Before investigating another mechanism, restore the dedicated FIST operation to the proven Stage A behavior:

```text
G3AB_COL_FIST
-> validate gEUseType_Fist / raw 8
-> TouchDamage.ClearTriggeredList()
-> no DamageDisabled read/write
-> no weapon collision-group mutation
```

Remove only the temporary Stage B `DamageDisabled` setter and its diagnostic data/readback plumbing. Preserve all marker/C1/family/StatePosition/source-selection behavior unchanged.

After independent source review and build verification, Normal Chat should investigate the actual native Fist enable/disable mechanism from existing SDK/source/runtime evidence before authoring `G3AB_COL_FIST_OFF`.

---

## Frozen Fist sequence

```text
A — dedicated FIST baseline
    CLOSED/PASS

B — DamageDisabled causal investigation
    CLOSED/FAIL AS OFF MECHANISM
    setter confirmed 0 -> 1 and persistent
    damage still YES

R — restore Stage A FIST behavior after temporary probe
    CURRENT

C — production FIST/FIST_OFF lifecycle
    BLOCKED until a factual native control mechanism is identified and causally validated
```

---

## Deliberately outside the immediate restoration responsibility

- `G3AB_COL_FIST_OFF`;
- alternate Fist disable mechanism implementation;
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

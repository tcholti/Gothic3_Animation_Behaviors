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
research/raw/2026-09-05_fist_stagea_human_dedicated_fist_baseline.log
```

Validated fixture:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
frame 3: G3AB_COL_FIST
```

Stage A proved the separated dedicated FIST route reproduces damaging human Fist contact using `TouchDamage.ClearTriggeredList()` alone while preserving group `0 -> 0`, using no equipped-weapon source mask and creating no weapon-style C1 obligation.

---

## Fist Stage B — CLOSED/FAIL AS CURRENT MARKER-TIME OFF INTERVENTION

Temporary setter implementation:

```text
a8ce1487b53ff2f8e6b6b9d9e87ac36e2322c561
```

Exact readback implementation:

```text
933e652c7ee66a45b9cd826f249c93019c6248da
```

Readback evidence:

```text
research/raw/2026-09-05_fist_stageb_damage_disabled_exact_readback.log
commit 1f74a216b32008b968677af3d271694857e7aeba
SHA256 08A8D3D54BA878606D7C4BE5D0A4D022F85C7C5ACF9969F74845C2FAF6180152
```

Stage B established:

```text
first accepted FIST: DamageDisabled 0 -> 1
later accepted FIST executions: DamageDisabled 1 -> 1
visual valid-target contact damage: YES
same human gEUseType_Fist / raw 8 source
same collision group 0 -> 0
same ClearTriggeredList behavior
```

Therefore `SetDamageDisabled(GETrue)` factually changed and persistently held the exact resolved Fist TouchDamage property at true, but setting it at the authored `G3AB_COL_FIST` marker did **not** stop the tested human Fist damage. That marker-time intervention is rejected as the current production `FIST_OFF` mechanism.

Later static analysis of the tested binary established that `gCTouchDamage_PS::CanBeActivatedNow` checks `DamageDisabled` as a genuine activation gate and that the inherited `eCTrigger_PS` touch/intersect activation path reaches that virtual eligibility check. Stage B therefore does **not** prove that `DamageDisabled` is not a real native gate or is globally ineffective. Whether the relevant activation/dispatch passed the gate before the authored marker, or a later/native damage dispatch still occurs after it, remains unresolved.

---

## Fist restoration — CLOSED/PASS

Restoration implementation:

```text
1910c999fef91f97baadb6e19a1f4f393c9c4d5b
Restore proven Fist Stage A baseline
```

Independent source comparison from the proven Stage A implementation to the restored commit found no prototype/source differences; only later documentation/evidence artifacts differ.

The authoritative restored diagnostic target built successfully on the Windows/game PC and was deployed as the only live collision twin with exact built/live identity:

```text
Script_FrameCollisionTest.dll
SHA256 F31368142214B2F645F2D6B5EE67B6ADE939CB5DA9BE6F79908019E9A6B5C449
length 428032
```

Startup verification passed:

```text
Script_FrameCollisionTest diagnostic build loaded.
DiagnosticProfile: CORE
MarkerOpcodes: RIGHT LEFT BOTH OFF FIST
Hooks installed.
```

The live diagnostic is therefore back on the proven Stage A FIST behavior with no Stage B `DamageDisabled` mutation/readback code.

---

## Fist N1 — CLOSED/PASS AS OBSERVATION

Implementation and canonical runtime evidence:

```text
c1e390782309af5e9e54703389775a163b85612c
research/raw/2026-09-05_fist_n1_native_trigger_state_probe.log
evidence commit 1a475cd292abf526f2032262ac4300f18920e178
raw SHA256 113857F71C3A14A548582B4B254E0CF6C1CBCB79C285B158302E5B5AB34F1972
validated DLL SHA256 D543EEAF90B98287F0C306446C0752FF5676BC3684568381A5F5F42E28F30C8E
```

Across four intended native unmarked Normal/Fist executions (two P0 and two P1), the exact resolved human `gEUseType_Fist` / raw 8 source remained:

```text
FistCollisionGroup: 0
IsEnabled:          1
ReactToTouch:       1
ResetOnUntouch:     0
DamageDisabled:     0
```

No transition was observed at `NATIVE_ATTACK_BEFORE_ORIGINAL`, `NATIVE_ATTACK_AFTER_ORIGINAL`, `AISETSTATE_BEFORE_ORIGINAL`, or `AISETSTATE_AFTER_ORIGINAL`. Each intended execution still contained the native collision-group request `RequestedGroup: 7`, while the exact Fist source remained `0 -> 0`. Keep the separate short aborted `_AI_PowerAttack` generation outside the four-case Normal/Fist result.

N1 proves only that the tested native Normal/Fist cases did not expose their attack ON/OFF lifecycle through the logged collision-group or trigger-property state at those boundaries. It does not prove that no unobserved transient or other native control exists. See EV-222–EV-223.

---

## Current Responsibility — N2 damage-dispatch timing/path investigation

> **N2 — determine when the exact human Fist TouchDamage reaches its damage-dispatch / TriggerTarget path relative to the authored `G3AB_COL_FIST` marker and the previously tested `DamageDisabled` setter timing.**

This is the next causal investigation only. Determine whether the relevant activation/dispatch had already passed the genuine `DamageDisabled` gate before the marker or whether a later/native dispatch path remains after it. Do not select or implement a production `FIST_OFF` mechanism from property names or from N1 alone.

---

## Frozen Fist sequence

```text
A — dedicated FIST baseline
    CLOSED/PASS

B — DamageDisabled causal investigation
    CLOSED/FAIL AS OFF MECHANISM

R — restore exact Stage A FIST behavior
    CLOSED/PASS

N1 — observe native Fist trigger gates without mutation
    CLOSED/PASS AS OBSERVATION

D — close N1 / qualify Stage B / maintain procedures
    CLOSED

N2 — determine TriggerTarget/damage-dispatch timing
    CURRENT

C — production FIST/FIST_OFF lifecycle
    BLOCKED until a factual control mechanism is causally validated
```

---

## Deliberately outside the immediate N2 responsibility

- `G3AB_COL_FIST_OFF`;
- setting `IsEnabled`, `ReactToTouch`, or another candidate;
- choosing or implementing another Fist disable mechanism before the N2 timing/path evidence;
- mutating `IsEnabled`, `ReactToTouch`, `DamageDisabled`, or another candidate as a production decision;
- new hooks unless a separately frozen bounded N2 diagnostic proves one necessary;
- persistent Fist marker-owned lifecycle state;
- Fist terminal/interruption restoration;
- PhysicalFist / monsters / generalized body collision;
- per-limb Fist markers;
- weapon source-mask changes;
- attack-family / StatePosition redesign;
- C1 or weapon-lifecycle redesign;
- RIGHT/LEFT/BOTH/OFF behavior changes;
- final mixed native/compatibility regression execution;
- Raise implementation;
- playback-speed redesign;
- target acquisition;
- climbing.

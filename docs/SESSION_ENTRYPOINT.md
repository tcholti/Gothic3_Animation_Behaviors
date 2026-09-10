# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-10

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Frozen redesign authority: `docs/COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`  
Overall architecture: `docs/DESIGN.md`  
Diagnostics: `docs/COLLISION_LOGGER_PLAN.md`  
Validation: `docs/COLLISION_TEST_PLAN.md`  
Recurring procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`

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
```

Raw-8 FIST remains one shared native mechanism. No authored FIST_OFF, Fist ClearTriggeredList, equipped Fist window/C1 weapon obligation, direct/custom damage, species branch, or raw55 generalization.

---

## SprintAttack Discovery

EV-249 also exposed native Sabretooth `Action 9`, which is factual `gEAction_SprintAttack`, while reusing a PowerAttack-named motion and factual `Fist/raw8` source. Current collision source has no Sprint family/adapter, so the marker remains unsupported today.

Do not alias Sprint to Power from the filename and do not assume Sprint is Fist-only or creature-only. Sprint becomes a separate evidence-backed family investigation only after the architecture/diagnostic refactor and sentinel.

---

## Architecture Audit — COMPLETE

The 2026-09-10 Normal Chat audit is frozen in `COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`.

Confirmed healthy boundaries:

```text
CollisionSources              factual source identity / UseType
CollisionSourceOperations     physical source mutation / ClearTriggeredList
CollisionLifecycleGuard       C1 ownership, obligations, repair decision
FrameCollisionMarkers         exact marker ownership/occurrence/equipped semantics
RunScriptFunctionScope        legitimate EngineBridge hook-lifetime transport
EngineBridge                  sole physical Gothic hook/call-site owner
CMake                         behavior-only target excludes diagnostics mechanically
```

Confirmed drift:

```text
1. raw8 FIST state/policy split between EngineBridge and FrameCollisionMarkers
2. Hack CombatMove motion-routing policy inside EngineBridge
3. C1-R1 terminal physical mutation performed directly inside CollisionLifecycleGuard
4. research-era CORE diagnostic volume
```

No separate attack-family module is planned; current action/phase marker-family resolution belongs to `FrameCollisionMarkers`.

---

## Stage A Behavior Architecture Refactor — SOURCE IMPLEMENTED / STATIC REVIEW PASS

Published implementation:

```text
7c5874932cd6eafa5af3414c65a4442b3d74bb73
Refactor collision behavior ownership boundaries
```

The commit is exactly one commit ahead of the frozen Stage A base `5f8101179de6417dbb20d310b00b378a3f36ad8a`.

Implemented seams:

```text
Raw8FistCollision
  now owns the existing Normal+Power+Quick raw8 FIST family policy,
  marked-execution state, initial latch close, accepted-marker latch rearm,
  threshold/timing-permission state and exact one-shot timing decision

AttackMotionRouting
  now owns only the proven factual Hack optional _FinishingAttack_ ->
  _HackAttack_ candidate policy

EngineBridge
  still owns every physical hook/call-site, including Game+0x16E180 and
  Game+0x16B10C, and delegates feature behavior

FrameCollisionMarkers
  still owns generic marker scanning/ownership/occurrence/C1 bookkeeping,
  equipped RIGHT/LEFT/BOTH/OFF and StatePosition semantics; accepted FIST
  delegates its raw8 latch operation

CollisionLifecycleGuard
  still decides every C1-R1 repair criterion/classification but delegates
  the physical Item_Attack -> Item_Equipped mutation to CollisionSourceOperations

CMake
  both behavior-only and diagnostic twins share the same refactored behavior source set
```

Independent Normal Chat remote review: **PASS**.

Verified boundaries:

```text
NO Sprint support added
NO new physical hook
NO hook RVA/calling-convention change
NO supported-family change: raw8 remains Normal + Power + Quick
NO marker vocabulary/StatePosition/equipped semantic change
NO C1 decision/repair-criterion change
NO terminal ClearTriggeredList
NO diagnostic redesign in Stage A
```

Work static audit: PASS. `git diff --check`: PASS. Build: NOT RUN / PROHIBITED. Material contradiction: None.

Runtime parity is **not yet claimed** because Stage A has not been locally built/loaded.

---

## Current Immediate Responsibility — LOCAL BUILD/LOAD GATE

> **STOP source work until the User is back at the PC with the local repository, build environment, and Gothic 3 installation.**

Next required gate:

```text
sync local branch to current remote HEAD
build Script_FrameCollisionTest (and behavior-only twin if required by the frozen gate)
deploy diagnostic build
launch far enough to load scripts
confirm clean load/unload and no compile/runtime smoke failure
```

Do not begin Stage B diagnostic source edits before this local Stage A build/load gate passes.

The User is currently away from that PC, so Normal Chat may discuss/review documentation but should not advance implementation beyond this gate.

---

## After Stage A Build/Load PASS

Stage B is the already-designed diagnostic refactor:

```text
known healthy paths -> compact CORE
unknown/unsupported/anomaly/repair/invariant -> rich CORE
historical low-level probes -> opt-in DEEP
production -> diagnostics not compiled
```

After Stage B source review and second local build/load, run the compact equivalence sentinel:

```text
raw8 FIST: Sabretooth Normal + Quick + Power
equipped: one ordinary marked weapon attack
marker lifecycle: one established multi-marker / OFF / rearm fixture
C1 safety: one established destructive bad-skip -> exact terminal repair
```

Only after sentinel PASS begin the bounded SprintAttack investigation, then continue the larger compatibility matrix.

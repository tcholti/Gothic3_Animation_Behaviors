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

EV-249 also exposed native Sabretooth `Action 9`, which is factual `gEAction_SprintAttack`, while reusing a PowerAttack-named motion and factual `Fist/raw8` source. Current collision source has no Sprint family/adapter, so the marker is correctly unsupported today.

Do not alias Sprint to Power from the filename and do not assume Sprint is Fist-only or creature-only. Sprint becomes a separate evidence-backed family investigation **after** the architecture/diagnostic refactor and sentinel.

---

## Architecture Audit — COMPLETE

The 2026-09-10 Normal Chat source audit is frozen in `COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`.

Confirmed healthy boundaries to preserve:

```text
CollisionSources              factual source identity / UseType
CollisionSourceOperations     equipped physical mutation / ClearTriggeredList
CollisionLifecycleGuard       C1 ownership, obligations, repair decision
FrameCollisionMarkers         exact marker ownership/occurrence/equipped semantics
RunScriptFunctionScope        legitimate EngineBridge hook-lifetime transport
EngineBridge hook ownership   one physical owner per Gothic hook
CMake                         behavior-only target excludes diagnostics mechanically
```

Confirmed structural drift to correct:

```text
1. raw8 FIST state/policy split between EngineBridge and FrameCollisionMarkers
2. Hack CombatMove motion-routing policy inside EngineBridge
3. C1-R1 terminal physical mutation performed directly inside CollisionLifecycleGuard
4. research-era CORE diagnostic volume (separate Stage B after behavior refactor builds)
```

No separate attack-family module is planned; current action/phase marker-family resolution legitimately belongs to `FrameCollisionMarkers`.

---

## Current Immediate Responsibility — Stage A

> **Perform only the frozen behavior-architecture parity refactor.**

Target additions:

```text
Raw8FistCollision
  owns supported raw8 FIST family policy, execution state,
  initial latch close, accepted-marker rearm, timing permission

AttackMotionRouting
  owns the existing factual Hack optional motion-substitution policy
```

Other corrections:

```text
EngineBridge retains every physical hook/call-site and delegates behavior
FrameCollisionMarkers dispatches accepted FIST behavior to Raw8FistCollision
CollisionLifecycleGuard retains repair decision but uses CollisionSourceOperations for mutation
CMake adds the new behavior modules to both twins' shared behavior source set
```

Hard boundaries:

```text
NO Sprint support
NO new hooks or hook-address changes
NO marker vocabulary/family/StatePosition semantic changes
NO raw8/equipped/C1 behavior changes
NO diagnostic compaction in Stage A
NO AttackContinuationProtection
NO Raise/speed/config
NO raw55 behavior
```

Work build execution remains PROHIBITED.

After Stage A publishes, Normal Chat reviews the diff. **Then stop for User local build/smoke** on the PC with local GitHub/game installation. Do not start Stage B diagnostic source edits until that build gate passes.

---

## After Stage A Build PASS

Stage B is the already-designed diagnostic refactor:

```text
known healthy paths -> compact CORE
unknown/unsupported/anomaly/repair/invariant -> rich CORE
historical low-level probes -> opt-in DEEP
production -> diagnostics not compiled
```

Then build/load again, run the compact equivalence sentinel, and only after sentinel PASS investigate SprintAttack.

---

## User-Side Build Constraint for Current Session

The User is currently away from the PC containing the local repository, build environment, and Gothic 3 installation.

Normal Chat may research/design, maintain documentation, freeze Work tasks, and review remote diffs. When the next required gate is local build/deploy/runtime validation, STOP and continue when the User is back on that PC.

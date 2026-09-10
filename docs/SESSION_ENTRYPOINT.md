# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-10

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Frozen redesign authority: `docs/COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`  
Frozen Stage B task: `docs/COLLISION_STAGE_B_DIAGNOSTIC_REFACTOR.md`  
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
Stage A architecture build/load gate       CLOSED/PASS — 2026-09-10
```

Raw-8 FIST remains one shared native mechanism. No authored FIST_OFF, Fist ClearTriggeredList, equipped Fist window/C1 weapon obligation, direct/custom damage, species branch, or raw55 generalization.

---

## SprintAttack Discovery

EV-249 exposed native Sabretooth `Action 9`, factual `gEAction_SprintAttack`, while reusing a PowerAttack-named motion and factual `Fist/raw8` source. Current collision source has no Sprint family/adapter, so the marker remains unsupported today.

Do not alias Sprint to Power from the filename and do not assume Sprint is Fist-only or creature-only. Sprint becomes a separate evidence-backed family investigation only after Stage B diagnostics and the compact equivalence sentinel.

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

Stage A corrected the three behavior-architecture drifts: raw8 FIST feature ownership, Hack motion-routing ownership, and C1-R1 physical-mutation ownership. Research-era CORE diagnostic volume is the separate Stage B responsibility.

No separate attack-family module is planned; current action/phase marker-family resolution belongs to `FrameCollisionMarkers`.

---

## Stage A Behavior Architecture Refactor — CLOSED/PASS THROUGH BUILD/LOAD

Published implementation:

```text
7c5874932cd6eafa5af3414c65a4442b3d74bb73
Refactor collision behavior ownership boundaries
```

Implemented architecture:

```text
Raw8FistCollision
  owns existing Normal+Power+Quick raw8 FIST policy/state/latch/timing permission

AttackMotionRouting
  owns only factual Hack optional _FinishingAttack_ -> _HackAttack_ candidate policy

EngineBridge
  retains every physical hook/call-site and delegates feature behavior

FrameCollisionMarkers
  retains generic marker scan/ownership/occurrence/C1/equipped/StatePosition semantics

CollisionLifecycleGuard
  retains all C1-R1 repair criteria/classification
  delegates physical 7 -> 5 mutation to CollisionSourceOperations
```

Independent source review: **PASS**. Work static audit: PASS. `git diff --check`: PASS. Material contradiction: None.

### Local build/load gate — 2026-09-10

Both Release twins compiled and linked successfully:

```text
Script_FrameCollisionBehaviorTest.dll  PASS
Script_FrameCollisionTest.dll          PASS
```

The deployed diagnostic DLL matched the built DLL exactly:

```text
SHA256 07F682C2F7AD6227D0EE81CD2DE053C9704B8E7EC4AFFB54793E91A55BD7D945
```

Runtime smoke:

```text
diagnostic DLL loaded
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
Hack callback identity: ExactlyOne=1 / OnAI_HackAttack
behavior hooks installed
normal exit
Script_FrameCollisionTest unloading cleanly
```

Result: **Stage A compile/deploy/load/unload gate CLOSED/PASS.**

The build emitted non-fatal warnings, including behavior-only unused diagnostic values introduced by the raw8 move. They are not runtime defects. Stage B may clean only diagnostic-only warning residue without changing behavior.

The startup `BehaviorCore:` diagnostic text is stale because it omits `Raw8FistCollision` and `AttackMotionRouting`; Stage B must correct it.

---

## Current Immediate Responsibility — STAGE B DIAGNOSTIC REFACTOR

> **Implement only the frozen diagnostic-volume/parity refactor in `COLLISION_STAGE_B_DIAGNOSTIC_REFACTOR.md`.**

Governing policy:

> **Known successful behavior logs compactly. Unknown, unsupported, contradictory, repair, or invariant behavior logs richly.**

Frozen Stage B includes:

```text
Fist CanBeActivatedNow/TriggerTarget research hooks -> DEEP only
routine Fist state snapshots -> DEEP only
OnDamage hook remains CORE but routine output becomes compact
marker context+result -> one post-result CORE event
unsupported/unknown marker traffic -> automatic rich action/source/motion detail
attack ownership -> compact known-path event
raw8 FIST diagnostics -> factual Raw8 naming + compact known-path events
SetCollisionGroup -> compact meaningful physical events, preserving meaningful 7->7
healthy C1 chronology -> compact; repair/invariant -> rich
remove player-only lifecycle filtering where it hides NPC evidence
RunScriptFunctionScopeReturn chronology -> DEEP
stale startup metadata -> corrected
mechanical diagnostic-only warning cleanup allowed
```

Hard behavior boundaries:

```text
NO Sprint support
NO gameplay behavior change
NO behavior hook RVA/calling-convention change
NO marker vocabulary/StatePosition/raw8/equipped/C1 semantic change
NO AttackContinuationProtection
NO Raise/speed/config
NO raw55 behavior
```

Work build execution remains PROHIBITED.

After Stage B source publish, Normal Chat independently reviews the exact diff. Then User + Normal Chat locally build both twins, deploy/hash the diagnostic DLL and smoke-load it. Only after that PASS run the compact equivalence sentinel.

Sentinel:

```text
raw8 FIST: Sabretooth Normal + Quick + Power
equipped: one ordinary marked weapon attack
marker lifecycle: one established multi-marker / OFF / rearm fixture
C1 safety: one established destructive bad-skip -> exact terminal repair
```

Only after sentinel PASS begin the bounded SprintAttack investigation.

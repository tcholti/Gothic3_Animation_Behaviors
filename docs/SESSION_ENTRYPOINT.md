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
Stage B diagnostic build/load gate         CLOSED/PASS — 2026-09-10
```

Raw-8 FIST remains one shared native mechanism. No authored FIST_OFF, Fist ClearTriggeredList, equipped Fist window/C1 weapon obligation, direct/custom damage, species branch, or raw55 generalization.

SprintAttack remains deliberately unsupported. EV-249 established `Action 9 = gEAction_SprintAttack` for native Sabretooth using factual Fist/raw8 while reusing a PowerAttack-named motion. Do not alias Sprint to Power or assume Sprint is Fist-only.

---

## Stage A Architecture Refactor — CLOSED/PASS

Implementation:

```text
7c5874932cd6eafa5af3414c65a4442b3d74bb73
Refactor collision behavior ownership boundaries
```

Implemented architecture:

```text
Raw8FistCollision       raw8 Normal+Power+Quick policy/state/latch/timing
AttackMotionRouting     factual Hack-only optional motion substitution
EngineBridge            sole physical hook/call-site owner
FrameCollisionMarkers   generic marker/C1/equipped/StatePosition semantics
CollisionLifecycleGuard C1 policy/repair decision
CollisionSourceOperations physical source mutation including terminal 7 -> 5
```

Independent source review: PASS. Both Release twins built/linked. Built/live diagnostic DLL SHA256 matched exactly:

```text
07F682C2F7AD6227D0EE81CD2DE053C9704B8E7EC4AFFB54793E91A55BD7D945
```

Runtime smoke: CORE loaded, DEEP disabled, Hack callback identity `ExactlyOne=1`, hooks installed, clean unload. Stage A build/load gate is CLOSED/PASS.

---

## Stage B Diagnostic Refactor — CLOSED/PASS THROUGH LOCAL BUILD/LOAD

Frozen authority:

```text
docs/COLLISION_STAGE_B_DIAGNOSTIC_REFACTOR.md
```

Published implementation:

```text
5737db32e5eda76810989ddfb5659f8405c0c458
Refactor Stage B collision diagnostics
```

Parent is exactly frozen base:

```text
f9a88316e107e6d1ace6509f26dfe9980ec2f404
```

Changed files only:

```text
CollisionDiagnostics.cpp
CollisionDiagnostics.h
EngineBridge.cpp
Raw8FistCollision.cpp
```

Independent Normal Chat review: **PASS**.

Verified Stage B boundaries:

```text
CORE startup BehaviorCore metadata includes Stage A modules
FistCanBeActivatedNow / FistTriggerTarget hooks -> DEEP only, same RVAs/calling conventions/native calls
routine Fist state snapshots -> DEEP only
OnDamage remains CORE at Game+0x668D0, same wrapper/original call, compact routine output
marker logging -> one post-result CORE path
unsupported/unknown marker traffic -> automatic rich action/phase/StatePosition/motion/source detail
attack ownership -> compact known-path CORE, richer contradiction detail
raw8 diagnostics -> factual Raw8 naming, compact known path, rich anomaly/DEEP arithmetic
SetCollisionGroup -> compact meaningful attack-source events, meaningful 7->7 preserved
C1 player-only filtering removed; healthy lifecycle compact, repair/invariant rich
RunScriptFunctionScopeReturn chronology -> DEEP
NO Sprint support
NO behavior/RVA/calling-convention/marker/raw8/equipped/C1/Hack change
```

Work static audit: PASS. `git diff --check`: PASS. Material contradiction: None.

### Local Stage B build/load evidence — 2026-09-10

Both Release twins compiled and linked successfully:

```text
Script_FrameCollisionBehaviorTest.dll  PASS
Script_FrameCollisionTest.dll          PASS
```

Built/live diagnostic DLL SHA256 matched exactly:

```text
081CDF413EC623079B8E4F1934EA7F1C27A7FFC7307B3BA0B19EA000BDA108BD
```

Runtime smoke:

```text
Script_FrameCollisionTest diagnostic build loaded
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
BehaviorCore includes Raw8FistCollision + AttackMotionRouting
Hack callback identity ExactlyOne=1 / OnAI_HackAttack
behavior hooks installed
normal exit
Script_FrameCollisionTest unloading cleanly
```

Result: **Stage B compile/deploy/load/unload gate CLOSED/PASS.**

---

## Current Immediate Responsibility — COMPACT EQUIVALENCE SENTINEL

> **Validate behavior parity and the new compact CORE logger before any Sprint implementation/research expansion.**

Run the established sentinel only:

```text
raw8 FIST: Sabretooth Normal + Quick + Power
equipped: one ordinary marked weapon attack
marker lifecycle: one established multi-marker / OFF / rearm fixture
C1 safety: one established destructive bad-skip -> exact terminal repair
```

The sentinel must establish both:

```text
behavior remains equivalent after Stage A/B refactors
CORE logs are compact for healthy traffic while preserving rich anomaly/repair evidence
```

If any sentinel leg fails, stop and resolve that exact regression before Sprint.

Only after sentinel PASS begin bounded SprintAttack source/transport/mechanism investigation.

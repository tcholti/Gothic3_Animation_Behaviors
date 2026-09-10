# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-10

## Current Bridge — Stage B IMPLEMENTED/REVIEWED, LOCAL BUILD NEXT

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat orientation:

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_ARCHITECTURE_REDESIGN_PLAN.md
4. COLLISION_STAGE_B_DIAGNOSTIC_REFACTOR.md
5. COLLISION_LOGGER_PLAN.md
```

Do not begin Sprint implementation or Goblin/Demon/Ogre matrix testing yet.

---

## Closed Starting Point

Raw8 FIST Normal + Power + Quick is CLOSED/PASS through EV-249.

SprintAttack discovery remains:

```text
Action 9 = gEAction_SprintAttack
observed actor = native Sabretooth
observed source = Fist/raw8
motion happens to be PowerAttack-named
current behavior = unsupported
```

Sprint is a later first-class family investigation. Do not alias it to Power or assume it is Fist-only.

---

## Stage A Architecture Refactor — CLOSED/PASS

Implementation:

```text
7c5874932cd6eafa5af3414c65a4442b3d74bb73
```

Both Release twins compiled and linked. Built/live diagnostic DLL SHA256 matched:

```text
07F682C2F7AD6227D0EE81CD2DE053C9704B8E7EC4AFFB54793E91A55BD7D945
```

CORE loaded, hooks installed, Hack callback identity `ExactlyOne=1`, and clean unload occurred. Stage A build/load is CLOSED/PASS.

---

## Stage B Diagnostic Refactor — SOURCE IMPLEMENTED / INDEPENDENT REVIEW PASS

Frozen contract:

```text
docs/COLLISION_STAGE_B_DIAGNOSTIC_REFACTOR.md
```

Implementation:

```text
5737db32e5eda76810989ddfb5659f8405c0c458
Refactor Stage B collision diagnostics
```

Frozen base:

```text
f9a88316e107e6d1ace6509f26dfe9980ec2f404
```

Exact comparison: implementation is one commit ahead of frozen base.

Changed files only:

```text
CollisionDiagnostics.cpp
CollisionDiagnostics.h
EngineBridge.cpp
Raw8FistCollision.cpp
```

Independent review: **PASS**.

Verified:

```text
FistCanBeActivatedNow + FistTriggerTarget physical diagnostic hooks moved to DEEP only
same hook RVAs/calling conventions/native forwarding retained
routine Fist state snapshots moved to DEEP
OnDamage remains CORE at Game+0x668D0 and keeps bounded logging/original call
CORE OnDamage output compact; DEEP retains pointer/contact/integer detail
CORE marker logging is one post-result event
unsupported/unknown marker traffic is automatically rich enough for Sprint discovery
CORE attack ownership is compact; contradiction path rich
raw8 diagnostic interface renamed Raw8Fist and known-path output compact
raw8 behavior state/latch/timing sequence unchanged
SetCollisionGroup logging compact and source-centric; meaningful 7->7 retained
C1 output no longer player-only; healthy chronology compact, repair/invariant rich
RunScriptFunctionScopeReturn is DEEP-only
startup BehaviorCore metadata includes Raw8FistCollision + AttackMotionRouting
NO Sprint support or new hooks
NO collision behavior/RVA/calling-convention/marker/StatePosition/raw8/equipped/C1/Hack semantic change
```

Work static audit: PASS. `git diff --check`: PASS. Build: NOT RUN / PROHIBITED. No material contradiction.

---

## NEXT — Local Stage B Build/Load Gate

Sync local `docs/collision-source-evidence` to current remote HEAD, then:

```text
build Script_FrameCollisionBehaviorTest Release
build Script_FrameCollisionTest Release
```

If both build:

```text
deploy Script_FrameCollisionTest.dll
verify built/live SHA256 equality
remove old log
launch Gothic 3 far enough to load scripts
exit normally
confirm compact CORE startup + hooks installed + clean unload
```

If build/load fails, fix only that exact Stage B defect before advancing.

---

## After Stage B Build/Load PASS

Run the compact equivalence sentinel:

```text
raw8 FIST: Sabretooth Normal + Quick + Power
equipped: one ordinary marked weapon attack
marker lifecycle: one established multi-marker / OFF / rearm fixture
C1 safety: one established destructive bad-skip -> exact terminal repair
```

The sentinel must establish both behavioral parity and that the new CORE logger is readable while retaining rich anomaly/discovery output.

Only after sentinel PASS:

```text
SprintAttack factual source/transport/mechanism investigation
-> bounded first-class Sprint implementation if supported by evidence
-> focused Sprint validation
-> Goblin 1H / Demon 2H / Ogre Axe
-> remaining compatibility/stress sequence
```

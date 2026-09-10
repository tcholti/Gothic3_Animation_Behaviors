# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-10

## Current Bridge — Stage A Behavior Architecture Refactor

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat / Work orientation:

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_ARCHITECTURE_REDESIGN_PLAN.md
4. WORK_IMPLEMENTATION_PROTOCOL.md when implementing
```

Do not resume Sprint or Goblin/Demon/Ogre testing yet.

---

## Closed Starting Point

Raw8 FIST Normal + Power + Quick is CLOSED/PASS through EV-249.

```text
Quick implementation: 2c9f745106506fc6bdb009b35720a4bb7c81ea11
validation raw: research/raw/2026.09.09_sabertooth_npc_pc_marked_attacks.log
canonical evidence: EV-249
```

SprintAttack was also discovered in that raw:

```text
Action 9 = gEAction_SprintAttack
observed actor = native Sabretooth
observed source = Fist/raw8
motion happens to be PowerAttack-named
current marker behavior = unsupported
```

Sprint is a later first-class family investigation. Do not implement or alias it during Stage A.

---

## Architecture Audit Result

Normal Chat completed the full source/CMake boundary audit on 2026-09-10.

### Healthy boundaries — preserve

```text
CollisionSources
CollisionSourceOperations existing equipped operations
CollisionLifecycleGuard C1 policy/state
FrameCollisionMarkers generic/equipped marker semantics
RunScriptFunctionScope + preCombatBridge storage in EngineBridge
single EngineBridge physical-hook ownership
behavior-only vs diagnostic CMake separation
```

### Confirmed drift — Stage A addresses first three only

```text
1. raw8 FIST behavior/state split across EngineBridge + FrameCollisionMarkers
2. Hack motion-routing policy inside EngineBridge
3. terminal C1 repair mutation directly inside CollisionLifecycleGuard
4. CORE diagnostic verbosity -> Stage B, only after Stage A local build PASS
```

Full frozen target: `COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`.

---

## NEXT — Frozen Stage A Work Responsibility

Stage A is **behavior architecture parity only**.

### A. Add Raw8FistCollision

Create:

```text
prototypes/Script_FrameCollisionTest/Raw8FistCollision.h
prototypes/Script_FrameCollisionTest/Raw8FistCollision.cpp
```

Move the existing raw8 behavior/state currently named `HumanFist*` out of `EngineBridge.cpp` into this module, using factual `Raw8Fist*` internal naming.

The module owns the existing:

```text
Normal + Power + Quick supported FIST family predicate
marked-execution state map
primary motion timing capture
Game+0x308308 threshold-constant read
exact raw8 source validation
initial SPU+0x164 = 1 ownership close once per C1 generation
pending timing-permission retirement
accepted FIST SPU+0x164 = 0 latch rearm
post-marker timing-permission arming
exact one-shot +0x16E180 timing permission/identity/consumption
```

Preserve current diagnostic calls/output text for Stage A; diagnostic renaming/compaction is Stage B.

`EngineBridge` retains the physical `Game+0x16E180` hook. Its wrapper obtains the real play time and delegates only the existing permission decision to `Raw8FistCollision`.

`FrameCollisionMarkers` retains generic marker validation/C1 occurrence logic and delegates the accepted FIST latch behavior into `Raw8FistCollision` at the same semantic point.

### B. Add AttackMotionRouting

Create:

```text
prototypes/Script_FrameCollisionTest/AttackMotionRouting.h
prototypes/Script_FrameCollisionTest/AttackMotionRouting.cpp
```

Move only the existing Hack optional motion-routing policy out of `EngineBridge.cpp`:

```text
factual gEAction_HackAttack
+ queried name contains _FinishingAttack_
-> try _HackAttack_ candidate
-> return candidate only if it exists
```

Keep in `EngineBridge`:

```text
physical Game+0x16B10C query hook
SPU+0x154 factual-action extraction
original resource query fallback
```

No new routing behavior.

### C. Route terminal repair mutation through CollisionSourceOperations

`CollisionLifecycleGuard::FinalizeAfterAISetState` keeps every existing repair criterion and result classification.

Replace only its direct physical `SetCollisionGroup(Item_Equipped)` mutation with the existing:

```text
CollisionSourceOperations::DeactivateOwnedAttackSource(source)
```

Preserve:

```text
exact live current-equipped liveness requirement
outstanding obligation requirement
actual group must still be Item_Attack(7)
requested target Item_Equipped(5)
NO ClearTriggeredList
same before/after verification
same finalization outcomes
same existing SetCollisionGroup-hook reentrancy/observation path
```

### D. CMake

Add the new behavior module source/header files to `FRAME_COLLISION_BEHAVIOR_SOURCES` so diagnostic and behavior-only twins use the same refactored behavior core.

---

## Stage A Hard Boundaries

```text
NO SprintAttack support or AttackFamily_Sprint
NO new hook
NO hook-address/calling-convention change
NO marker opcode/vocabulary change
NO action-family semantic change
NO StatePosition change
NO raw8 latch/timing semantic change
NO equipped source semantic change
NO C1 generation/ownership/repair-criterion change
NO diagnostic-volume/log-format redesign
NO removal of research hooks yet
NO AttackContinuationProtection
NO Raise/speed/config
NO raw55 behavior
```

If moving the code reveals a material contradiction requiring behavior redesign, STOP and report it instead of broadening.

Work BUILD EXECUTION IS PROHIBITED.

---

## After Work Publishes Stage A

Normal Chat must independently inspect the exact diff for parity and architecture compliance.

Then the next required gate is **local build/smoke**, so stop if the User is still away from the PC with the local repository/build environment/game installation.

Do **not** begin Stage B diagnostic source changes before Stage A build/load PASS.

After Stage A build PASS:

```text
Stage B compact CORE / rich anomaly / opt-in DEEP diagnostic refactor
-> second build/load
-> compact post-refactor equivalence sentinel
-> SprintAttack investigation
```

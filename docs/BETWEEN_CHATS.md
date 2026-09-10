# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-10

## Current Bridge — Stage A Implemented, Awaiting Local Build/Load

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat orientation:

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_ARCHITECTURE_REDESIGN_PLAN.md
```

Do not resume Sprint or Goblin/Demon/Ogre testing yet.
Do not begin Stage B diagnostic source edits until Stage A builds/loads locally.

---

## Closed Starting Point

Raw8 FIST Normal + Power + Quick is CLOSED/PASS through EV-249.

```text
Quick implementation: 2c9f745106506fc6bdb009b35720a4bb7c81ea11
validation raw: research/raw/2026.09.09_sabertooth_npc_pc_marked_attacks.log
canonical evidence: EV-249
```

SprintAttack was discovered in that raw:

```text
Action 9 = gEAction_SprintAttack
observed actor = native Sabretooth
observed source = Fist/raw8
motion happens to be PowerAttack-named
current marker behavior = unsupported
```

Sprint is a later first-class family investigation. Do not alias it to Power or assume it is Fist-only.

---

## Architecture Audit — COMPLETE

Healthy boundaries preserved:

```text
CollisionSources
CollisionSourceOperations
CollisionLifecycleGuard C1 policy/state
FrameCollisionMarkers generic/equipped marker semantics
RunScriptFunctionScope + preCombatBridge transport in EngineBridge
single EngineBridge physical-hook ownership
behavior-only vs diagnostic CMake separation
```

Stage A addressed these structural drifts:

```text
1. raw8 FIST feature state/policy split across EngineBridge + FrameCollisionMarkers
2. Hack optional motion-routing policy inside EngineBridge
3. terminal C1 repair mutation directly inside CollisionLifecycleGuard
```

CORE diagnostic verbosity remains separate Stage B work.

---

## Stage A Published Implementation

Commit:

```text
7c5874932cd6eafa5af3414c65a4442b3d74bb73
Refactor collision behavior ownership boundaries
```

Frozen base:

```text
5f8101179de6417dbb20d310b00b378a3f36ad8a
```

Independent comparison confirms Stage A is exactly one commit ahead of that base.

Changed files:

```text
AttackMotionRouting.cpp/.h          added
Raw8FistCollision.cpp/.h           added
CMakeLists.txt                      shared behavior source membership
CollisionLifecycleGuard.cpp        repair mutation delegation only
EngineBridge.cpp                    transport/delegation refactor
FrameCollisionMarkers.cpp          accepted-FIST delegation/family predicate reuse
```

### Implemented responsibility ownership

```text
Raw8FistCollision
  Normal + Power + Quick supported FIST predicate
  raw8 marked-execution state
  primary timing/threshold capture
  exact raw8 source validation
  initial SPU+0x164 = 1 close once per C1 generation
  accepted FIST SPU+0x164 = 0 rearm
  timing-permission retirement/arming/identity/consumption

AttackMotionRouting
  factual Hack-only optional _FinishingAttack_ -> _HackAttack_ candidate policy

EngineBridge
  sole physical hook/call-site owner
  retains SPU+0x154 factual-action extraction
  retains original motion query fallback
  retains Game+0x16E180 timing hook and delegates raw8 decision

FrameCollisionMarkers
  retains generic current-motion scan, action/phase eligibility,
  marker occurrence/dedupe/C1 bookkeeping,
  equipped RIGHT/LEFT/BOTH/OFF and StatePosition semantics

CollisionLifecycleGuard
  retains all repair decision criteria and result classification
  delegates only physical repair mutation to CollisionSourceOperations
```

### Independent Normal Chat review

**PASS.**

Verified:

```text
raw8 supported set remains exactly Normal + Power + Quick
no Sprint family/callback/hook added
no new physical hooks
no hook RVA or calling-convention changes
Game+0x16E180 remains physically owned by EngineBridge
Game+0x16B10C remains physically owned by EngineBridge
Hack original-query fallback preserved
accepted FIST generic marker validation order preserved
terminal repair still requires outstanding + current-equipped liveness + group7
DeactivateOwnedAttackSource performs no ClearTriggeredList
behavior-only and diagnostic twins share refactored behavior sources
diagnostic source set/definitions unchanged in Stage A
```

Work report:

```text
static audit: PASS
git diff --check: PASS
build: NOT RUN / PROHIBITED
material contradiction: None
```

Runtime parity is not yet proven because no local build/load has occurred after Stage A.

---

## NEXT — Local Stage A Build/Load Gate

The User is currently away from the PC containing the local repository, build environment, and Gothic 3 installation.

Therefore STOP implementation here.

When the User is back at that PC:

```text
sync local docs/collision-source-evidence to current remote HEAD
build the diagnostic collision target
resolve any compile issue before advancing
if build passes, deploy diagnostic DLL
launch Gothic 3 far enough to load scripts
exit normally
confirm clean load/unload smoke
```

If Stage A does not compile/load, fix only that exact Stage A defect before any Stage B work.

---

## After Stage A Build/Load PASS

Freeze and implement Stage B diagnostic-volume refactor:

```text
known healthy paths -> compact CORE
unknown/unsupported/anomaly/repair/invariant -> rich CORE
historical detailed probes -> opt-in DEEP
production -> diagnostics not compiled
```

Important Stage B constraints already designed:

```text
move Fist CanBeActivatedNow/TriggerTarget research hooks to DEEP
move routine Fist trigger-state snapshots to DEEP
compact healthy C1 chronology
suppress meaningless SetCollisionGroup noise
compact known marker/raw8 timing success records
retain rich terminal repair/divergence/invariant evidence
retain rich unsupported/unknown-family evidence including Sprint
ensure CORE can observe NPC as well as player regression facts
```

After Stage B source review and its own local build/load, run the compact equivalence sentinel:

```text
raw8 FIST: Sabretooth Normal + Quick + Power
equipped: one ordinary marked weapon attack
marker lifecycle: one established multi-marker / OFF / rearm fixture
C1 safety: one established destructive bad-skip -> exact terminal repair
```

Only after sentinel PASS:

```text
SprintAttack factual source/transport/mechanism investigation
-> bounded Sprint implementation if evidence supports it
-> focused Sprint validation
-> Goblin 1H / Demon 2H / Ogre Axe
-> remaining compatibility/stress sequence
```

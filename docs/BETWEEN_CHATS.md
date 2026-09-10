# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-10

## Current Bridge — Stage A CLOSED/PASS, Stage B NEXT

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat / Work orientation:

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_ARCHITECTURE_REDESIGN_PLAN.md
4. COLLISION_LOGGER_PLAN.md
5. WORK_IMPLEMENTATION_PROTOCOL.md when implementing
```

Do not begin Sprint implementation or Goblin/Demon/Ogre matrix testing yet.

---

## Closed Starting Point

Raw8 FIST Normal + Power + Quick is CLOSED/PASS through EV-249.

SprintAttack was discovered in EV-249:

```text
Action 9 = gEAction_SprintAttack
observed actor = native Sabretooth
observed source = Fist/raw8
motion happens to be PowerAttack-named
current marker behavior = unsupported
```

Sprint is a later first-class family investigation. Do not alias it to Power and do not assume it is Fist-only.

---

## Stage A Architecture Refactor — CLOSED/PASS

Implementation:

```text
7c5874932cd6eafa5af3414c65a4442b3d74bb73
Refactor collision behavior ownership boundaries
```

Stage A moved existing behavior only:

```text
Raw8FistCollision
  raw8 Normal+Power+Quick policy/state/latch/timing

AttackMotionRouting
  factual Hack-only optional motion substitution policy

CollisionLifecycleGuard
  still decides C1-R1 repair
  physical repair now delegated to CollisionSourceOperations

EngineBridge
  still sole owner of all physical Gothic hooks/call-sites
```

Independent source review: PASS. Work static audit: PASS. `git diff --check`: PASS. No material contradiction.

### Local build/load evidence — 2026-09-10

Both Release twins compiled/linked successfully:

```text
Script_FrameCollisionBehaviorTest.dll  PASS
Script_FrameCollisionTest.dll          PASS
```

Built/live diagnostic DLL SHA256 matched exactly:

```text
07F682C2F7AD6227D0EE81CD2DE053C9704B8E7EC4AFFB54793E91A55BD7D945
```

Runtime smoke passed:

```text
CORE diagnostic build loaded
DEEP disabled
Hack callback identity ExactlyOne=1 / OnAI_HackAttack
hooks installed
normal process exit
Script_FrameCollisionTest unloading cleanly
```

Therefore **Stage A compile/deploy/load/unload gate is CLOSED/PASS.**

Non-fatal build warnings remain, including behavior-only unused values that are diagnostic-only after the raw8 move. These are not runtime failures.

The startup `BehaviorCore:` line is stale because it does not list `Raw8FistCollision` or `AttackMotionRouting`; Stage B should correct it.

---

## NEXT — Stage B Diagnostic Refactor

Stage B changes diagnostic architecture/volume only. It must preserve behavior exactly.

Governing rule:

> **Known successful behavior logs compactly. Unknown, unsupported, contradictory, repair, or invariant behavior logs richly.**

Target product split:

```text
PRODUCTION
  diagnostic sources/definitions absent

CORE
  compact known-path regression events
  enough source/action/marker/damage/lifecycle facts for validation
  rich records automatically for unsupported/unknown/anomalous traffic
  must support NPC as well as player-relevant evidence

DEEP
  retained opt-in historical reverse-engineering probes
```

### Stage B planned reductions

```text
Fist CanBeActivatedNow/TriggerTarget research hooks -> DEEP only
routine Fist trigger-state snapshots -> DEEP only
healthy C1 START/BINDING/STATUS chronology -> compact or DEEP
SetCollisionGroup no-op/raw8 0->0 noise -> suppress from CORE
known successful marker ownership/result -> compact events
known successful raw8 ownership/opportunity/timing -> compact events
OnDamage -> compact factual CORE event, detailed call internals in DEEP
terminal repair/divergence/invariant -> rich CORE
unsupported/unknown family/source -> rich CORE automatically
```

For unsupported traffic such as Sprint, CORE must preserve at minimum:

```text
actor
numeric action
phase
StatePosition
current motion
marker opcode/result
C1 generation when available
resolved source identity / UseType / collision group
rejection reason
native damage caller/entity correlation when observed
```

Reusable deep research capability should be moved/retained in DEEP, not deleted merely to reduce log volume.

### Hard behavior boundaries

```text
NO Sprint support or AttackFamily_Sprint
NO new gameplay behavior
NO hook RVA/calling-convention change
NO marker vocabulary change
NO StatePosition change
NO raw8 family/latch/timing semantic change
NO equipped source semantic change
NO C1 generation/repair semantic change
NO AttackContinuationProtection
NO Raise/speed/config
NO raw55 behavior
```

After Stage B Work publishes:

```text
Normal Chat independently reviews exact diff
-> local build both twins
-> deploy/hash diagnostic DLL
-> load/unload smoke
-> compact equivalence sentinel
```

Sentinel:

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

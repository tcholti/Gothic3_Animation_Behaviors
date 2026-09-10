# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-10

## Current Bridge — Stage A CLOSED/PASS, Stage B FROZEN/NEXT

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat / Work orientation:

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_ARCHITECTURE_REDESIGN_PLAN.md
4. COLLISION_LOGGER_PLAN.md
5. COLLISION_STAGE_B_DIAGNOSTIC_REFACTOR.md
6. WORK_IMPLEMENTATION_PROTOCOL.md when implementing
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

---

## NEXT — Frozen Stage B Diagnostic Refactor

Exact Work authority:

```text
docs/COLLISION_STAGE_B_DIAGNOSTIC_REFACTOR.md
```

Stage B changes diagnostics only and must preserve behavior exactly.

Governing rule:

> **Known successful behavior logs compactly. Unknown, unsupported, contradictory, repair, or invariant behavior logs richly.**

Frozen responsibility summary:

```text
Fist CanBeActivatedNow/TriggerTarget research hooks -> DEEP only
routine Fist trigger-state snapshots -> DEEP only
OnDamage hook stays CORE; normal output compact, deep internals retained in DEEP
marker context+result -> one post-result CORE event
unsupported/unknown marker traffic -> automatic rich action/source/motion detail
attack callback ownership -> compact routine event
raw8 FIST diagnostic naming -> Raw8; healthy ownership/timing events compact
SetCollisionGroup -> compact meaningful physical events; meaningful 7->7 retained
healthy C1 chronology -> compact; repair/invariant/unresolved -> rich
player-only C1 output filtering removed where it would hide NPC evidence
RunScriptFunctionScopeReturn chronology -> DEEP
startup BehaviorCore metadata corrected for Raw8FistCollision + AttackMotionRouting
Stage-A diagnostic-only warning residue may be cleaned mechanically
```

Hard behavior boundaries:

```text
NO Sprint support or AttackFamily_Sprint
NO new gameplay behavior
NO behavior hook RVA/calling-convention change
NO marker vocabulary change
NO StatePosition change
NO raw8 family/latch/timing semantic change
NO equipped source semantic change
NO C1 generation/repair semantic change
NO Hack routing change
NO AttackContinuationProtection
NO Raise/speed/config
NO raw55 behavior
```

Work BUILD EXECUTION / BUILD TOOLING PROBING remains PROHIBITED.

If a material contradiction requires behavior changes beyond the diagnostic contract, STOP and report it.

---

## After Stage B Work Publishes

Normal Chat independently reviews the exact diff.

Then User + Normal Chat locally:

```text
sync local branch
build both Release twins
deploy diagnostic DLL
verify built/live SHA256 equality
load/unload smoke
```

Only after that passes, run the compact equivalence sentinel:

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

# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-10

## Current Bridge — Stage A/B + Equivalence Sentinel CLOSED/PASS; Sprint Research NEXT

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat orientation:

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_TEST_PLAN.md
4. COLLISION_LOGGER_PLAN.md
5. EVIDENCE_LEDGER_250_ONWARD.md
6. EV-249 in EVIDENCE_LEDGER_232_ONWARD.md when historical Quick/Sprint discovery context is needed
```

Do not begin Sprint implementation or Goblin/Demon/Ogre matrix testing yet.

---

## Closed Refactor Boundary

Stage A behavior architecture implementation:

```text
7c5874932cd6eafa5af3414c65a4442b3d74bb73
```

Stage B diagnostic implementation:

```text
5737db32e5eda76810989ddfb5659f8405c0c458
```

Both passed independent source review and local build/deploy/load/unload gates.

Validated Stage-B diagnostic DLL SHA256:

```text
081CDF413EC623079B8E4F1934EA7F1C27A7FFC7307B3BA0B19EA000BDA108BD
```

---

## EV-250 — Compact Equivalence Sentinel CLOSED/PASS

Canonical evidence:

```text
docs/EVIDENCE_LEDGER_250_ONWARD.md
```

Runtime artifacts:

```text
research/archive/2026.09.10_different_attacks.log
research/raw/2026.09.10_sabertooth_npc_pc_marked_attacks_new.log
```

Published runtime commit:

```text
e963cf24db882a96cab1f16eef52b7951180cd7b
2026.09.10_redesign test
```

Archive move commit:

```text
f77bc18d82c4387dc5b4e59272b4f8aaff982b50
move
```

The equipped sentinel log is fully processed and archived. The Sabretooth log remains ACTIVE because it directly feeds the next Sprint investigation.

### Equipped/marker/C1 sentinel result

`2026.09.10_different_attacks.log` confirms:

```text
ordinary marked 2H Normal / Quick / Power / Hack paths healthy
2H Whirl RIGHT -> OFF -> RIGHT preserved within one C1 generation
first RIGHT: 5 -> 7 + offense obligation
OFF: 7 -> 5 + cleanup fulfillment
later RIGHT: 5 -> 7 + fresh offense/rearm
natural completion: 7 -> 5
meaningful duplicate/budget suppression remains compact
Dual 1H Power additionally exercised BOTH/LEFT/OFF/rearm and meaningful 7 -> 7
```

Deliberate destructive Whirl bad-skip generation 12:

```text
exact source = It_2H_Sword_Flamberge
side = RIGHT
outstanding before finalization = 1
cleanup observed before finalization = 0
live/equipped = yes
actual group before repair = 7
repair requested = 5
actual group after repair = 5
outcome = REPAIRED_TO_ITEM_EQUIPPED
PhysicalCollisionChanged = 1
```

Late old-Whirl marker callbacks arrived after factual action ownership was gone (`Action 0`, no valid C1 generation) and were `REJECTED_UNSUPPORTED_HIT`; they did not reopen collision.

No `C1 INVARIANT WARNING`, `REPAIR_DIVERGED` or `UNRESOLVED_NOT_EQUIPPED` was found. Clean unload present.

### Raw8 sentinel result

`2026.09.10_sabertooth_npc_pc_marked_attacks_new.log` confirms native Sabretooth and transformed-Hero Sabretooth marked raw8 executions across Normal, Quick and Power:

```text
Fist / raw8 / group0
initial ownership close 0 -> 1 confirmed
accepted FIST latch 1 -> 0 confirmed
ownership matched
early timing permission armed/used where required
native OnDamage caller = Game.dll +0x0016E348
```

No `RAW8 FIST TIMING ANOMALY`, C1 invariant warning or repair divergence was found. Clean unload present.

### Stage-B discovery logging also proved useful

The Sabretooth run contains 42 rich unsupported marker-discovery records corresponding to:

```text
Actor = Sabertooth
Action = 9
Family = UNKNOWN
AniPhase = 1
StatePosition = 1
motion = Sabertooth ... PowerAttack_Hit ...
marker = G3AB_COL_FIST
result = REJECTED_UNSUPPORTED_HIT
C1 generation = valid
RIGHT source = Fist / UseType 8 / group0
```

This is expected Sprint traffic, not a Quick/Power regression.

Therefore the Stage A/B refactor parity gate and compact CORE sufficiency gate are CLOSED/PASS.

---

## NEXT — Bounded SprintAttack Research

Sprint is not implemented yet.

Known factual runtime boundary:

```text
gEAction_SprintAttack = 9
observed actor = native Sabretooth
observed source = Fist/raw8/group0
observed phase = 1
observed StatePosition = 1
observed motion filename = PowerAttack-named
current marker behavior = unsupported
```

Do not infer Power semantics from the filename.

Normal Chat should now determine only:

```text
1. actual script/native callback or transport ownership for Sprint
2. bounded source UseType scope
3. exact StatePosition/action-phase contract
4. whether raw8 Sprint uses the same relevant latch/timing/native-damage mechanism
5. whether equipped Sprint traffic is evidenced in source/API/runtime material
```

Use existing source/API/current CORE evidence first. Add DEEP instrumentation only for a fact that cannot otherwise be established.

Do not give Work an implementation task until this boundary is frozen.

After any evidence-backed Sprint implementation and focused Sprint validation:

```text
Goblin 1H / Demon 2H / Ogre Axe
-> remaining compatibility/stress sequence
-> AttackContinuationProtection
```

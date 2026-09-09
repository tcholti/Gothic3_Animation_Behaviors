# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-09

## Current Bridge — Collision Architecture Audit Before Further Compatibility Testing

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat must read `SESSION_ENTRYPOINT.md` first, then this file.

---

## Newly Closed Result — Raw-8 Quick FIST

Implementation:

```text
2c9f745106506fc6bdb009b35720a4bb7c81ea11
Extend raw-8 FIST support to Quick attacks
```

The implementation changed only the two pre-existing Normal/Power FIST family gates:

```text
EngineBridge.cpp              UpdateHumanFistMarkerOwnership
FrameCollisionMarkers.cpp     ProcessMarker FIST supported-family gate
```

`AttackFamily_Quick` was admitted while every existing FIST mechanism and equipped-weapon behavior remained unchanged.

Post-change validation raw:

```text
research/raw/2026.09.09_sabertooth_npc_pc_marked_attacks.log
source commit: 1a0416b10bed694d47eb4809b7367b507228962d
```

Test shape:

```text
native Sabretooth -> player, repeated attacks
then god mode
Hero transformed to Sabretooth -> native Sabretooth, repeated attacks
```

### Quick result

Both native `Sabretooth` and `Transform_Sabertooth_Potion` exercised factual raw-8 Fist Quick-left/right (`Action 5` / `Action 4`). Representative executions in both directions show:

```text
Family = QUICK
source = Fist / raw8 / group0
initial marked-execution latch close = SPU+0x164 0 -> 1, confirmed
G3AB_COL_FIST = ACCEPTED
marker latch rearm = 1 -> 0, confirmed
Quick StatePosition = 1 -> 1
OwnershipMatched = 1
RealBelowThreshold = 1
TimingPermissionArmed = 1
SyntheticApplied = 1
PermissionConsumed = 1
native damage caller = Game +0x0016E348
```

For transformed Hero Quick, the damage record identifies:

```text
target = native Sabertooth
source = transformed Hero Fist / raw8
attacker = Transform_Sabertooth_Potion
caller = Game +0x0016E348
```

For native Sabretooth Quick, the corresponding damage record identifies `PC_Hero` as target, native Sabretooth `Fist` as source, and the same `Game +0x0016E348` caller.

The log contains `REJECTED_UNSUPPORTED_HIT` records, but traced examples are `Actor: Sabertooth`, `Action: 9`, executing the PowerAttack-named motion. They are not Quick `Action 4/5` failures and do not contradict the bounded Quick extension.

No `C1 INVARIANT WARNING`, `REPAIR_DIVERGED`, or `EXCEPTION` signal was found. The diagnostic DLL unloaded cleanly.

Conclusion:

> **Raw-8 FIST Quick is CLOSED/PASS for the tested native/transformed Sabretooth two-direction fixture.** The supported/proven raw-8 FIST attack-family set is now Normal + Power + Quick for this tested scope. No Quick-specific mechanism or species branch is justified.

Raw55/PhysicalFist remains unobserved/deferred.

---

## Artifact Disposition

The post-change validation log is **NEW CANONICAL EVIDENCE** pending/recorded as the next evidence row.

The earlier comparison raws have completed their Quick comparison responsibility:

```text
research/raw/2026.09.08_sabertooth_marked_attacks.log
research/raw/2026.09.09_sabertooth_npc_marked_attacks.log
```

They remain retained provenance, but are no longer an active open Quick comparison once the post-change result is canonically recorded.

---

## NEXT — Normal Chat Architecture Responsibility

Before running the larger NPC/mod-family compatibility matrix, perform a complete collision-framework architecture audit against the intended final modular design.

This is **research/design first, not immediate code editing**.

Reason for the ordering:

- collision is the mature foundation that later Raise/Speed/Config will join inside `Script_G3AnimationBehaviors`;
- the remaining NPC/mod-family tests should certify the architecture intended to survive into production;
- refactoring after those tests would leave avoidable uncertainty about whether the tested architecture still exists unchanged.

### Governing architecture

```text
EngineBridge
  owns physical Gothic hooks
  transports native facts/events
  delegates behavior

FrameCollisionMarkers
  exact motion/marker ownership and occurrence semantics

CollisionSources
  factual source identity / UseType

CollisionSourceOperations
  source-specific physical mutations

CollisionLifecycleGuard
  C1 execution/source obligations and terminal repair

Raw8FistCollision [candidate dedicated module]
  raw8 FIST execution state
  latch ownership policy
  timing permission state/identity
  raw8-specific behavior decisions

Diagnostics
  diagnostic product only; absent from production compilation
```

### Audit questions

Inspect the complete current collision behavior source for architectural drift, not only the already-obvious raw8 FIST concentration in `EngineBridge.cpp`.

Determine:

1. Which code in `EngineBridge` is true hook ownership/transport and should stay there.
2. Which feature policy/state has accumulated in `EngineBridge` and should move to a feature module.
3. Whether raw8 FIST should become a dedicated `Raw8FistCollision` module while `EngineBridge` retains the sole `+0x16E180` physical hook and delegates through it.
4. Whether any marker, source, source-operation, or lifecycle responsibility has crossed its intended module boundary.
5. Whether `RunScriptFunctionScope` / pre-combat bridge pieces are legitimate hook-lifetime transport or actual lifecycle policy; do not classify them as drift merely because they live in `EngineBridge`.
6. Whether dependency direction remains clean and avoids competing hook owners.
7. Whether diagnostics remain mechanically excluded from the behavior-only build, not merely disabled at runtime.
8. Whether historical `HumanFist*` names should become factual `Raw8Fist*` names now that human/species identity is disproven as the governing boundary.
9. Whether any other structural drift exists that should be corrected before further compatibility testing.

Do not change behavior merely for aesthetics. Preserve all proven marker/source/lifecycle/FIST semantics exactly unless the audit exposes a concrete contradiction.

After Normal Chat freezes the smallest justified architectural correction, give that bounded refactor to Work. After source review/build, run a small post-refactor equivalence sentinel before resuming the large compatibility matrix.

---

## Planned Post-Refactor Equivalence Sentinel

Keep this compact; it proves the refactor did not alter the architectural seams:

```text
raw8 FIST:
  Sabretooth Normal + Quick + Power

equipped marker:
  one ordinary marked weapon attack

marker lifecycle:
  one established multi-marker / OFF / rearm fixture

C1 safety:
  one established destructive bad-skip -> exact terminal repair
```

Only after that passes resume:

```text
native equipped-NPC marker controls:
  Goblin -> 1H / raw2
  Demon  -> 2H / raw3
  Ogre   -> Axe / raw52

-> additional prepared native/modded actor-family controls
-> separated 2H vs Axe compatibility
-> separated 1H vs Rapier compatibility
-> final native mixed/stress collision regression
-> separate AttackContinuationProtection
-> combined mature collision regression
-> production migration into Script_G3AnimationBehaviors
-> diagnostics-free production validation
-> integrate Raise + Speed + Config
```

If an intermediate family fails, stop and resolve that exact failure before continuing.

---

## GitHub Desktop Handoff

Assistant evidence/current-state maintenance may advance the remote branch beyond the User's local checkout.

Before the next local build/test window:

```text
open GitHub Desktop
-> select Gothic3_Animation_Behaviors
-> confirm Current branch = docs/collision-source-evidence
-> click Fetch origin
-> if offered, click Pull origin
-> verify Changes shows 0 changed files
```

The User is still a GitHub Desktop beginner; repeat these steps when needed.

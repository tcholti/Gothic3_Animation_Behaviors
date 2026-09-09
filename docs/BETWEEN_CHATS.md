# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-09

## Current Bridge — Architecture + Diagnostic Redesign Before Sprint and Broad Testing

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat must read:

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_ARCHITECTURE_REDESIGN_PLAN.md
```

Do not resume Goblin/Demon/Ogre compatibility testing yet.

---

## Closed Result — Raw-8 Quick FIST

Implementation:

```text
2c9f745106506fc6bdb009b35720a4bb7c81ea11
Extend raw-8 FIST support to Quick attacks
```

Post-change validation raw:

```text
research/raw/2026.09.09_sabertooth_npc_pc_marked_attacks.log
source commit: 1a0416b10bed694d47eb4809b7367b507228962d
canonical conclusion: EV-249
```

Test shape:

```text
native Sabretooth -> player, repeated attacks
then god mode
Hero transformed to Sabretooth -> native Sabretooth, repeated attacks
```

Both directions proved factual raw8 Quick-left/right (`Action 5` / `Action 4`) entering the existing FIST mechanism:

```text
Family = QUICK
source = Fist / raw8 / group0
initial marked-execution latch close = SPU+0x164 0 -> 1
G3AB_COL_FIST = ACCEPTED
marker latch rearm = 1 -> 0
Quick StatePosition = 1 -> 1
OwnershipMatched = 1
below-threshold timing permission armed/consumed when required
native damage caller = Game +0x0016E348
```

No `C1 INVARIANT WARNING`, `REPAIR_DIVERGED`, or `EXCEPTION` signal was found. Diagnostic unloaded cleanly.

Conclusion:

> **Raw-8 FIST Quick is CLOSED/PASS for the tested native/transformed Sabretooth two-direction fixture.** Supported/proven raw8 FIST family scope is Normal + Power + Quick for this tested scope.

---

## Newly Identified SprintAttack Gap

The same raw repeatedly contains:

```text
Actor: Sabertooth
Action: 9
AniPhase: Hit
CurrentMovementAni: Sabertooth_Stand_None_Fist_P0_PowerAttack_Hit_...
G3AB_COL_FIST = REJECTED_UNSUPPORTED_HIT
```

Gothic SDK identity:

```text
gEAction_SprintAttack = 9
```

Therefore these are **SprintAttack executions reusing a PowerAttack-named motion**.

They are:

```text
NOT gEAction_PowerAttack failures
NOT Quick failures
NOT evidence that filename should define family
```

Current source has no `AttackFamily_Sprint` and no SprintAttack family adapter/hook plumbing.

Accepted planning conclusion:

> SprintAttack is a factual missing attack family that the finished collision framework should investigate and, where evidence supports it, implement as a first-class family.

Current evidence only establishes Sprint on native Sabretooth with factual `Fist/raw8`. We have not yet observed Sprint in prior tests, with equipped sources, or with another factual source type.

Therefore do not assume Sprint is Fist-only, creature-only, Power-equivalent, or equipped-capable. Do not add a Sabretooth exception.

Full frozen planning authority: `COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`.

---

## NEXT — Normal Chat Architecture + Diagnostic Audit

This is **research/design first, not immediate code editing**.

Before any further large compatibility matrix:

1. audit the complete collision behavior structure for architectural drift;
2. design the final collision module seams intended to survive into production;
3. audit diagnostic output volume and redesign CORE/DEEP responsibilities;
4. ensure the target architecture can cleanly accommodate future `AttackFamily_Sprint` without implementing Sprint speculatively;
5. freeze bounded parity-preserving Work task(s);
6. after refactor, run one compact equivalence sentinel;
7. only then investigate Sprint and later resume broad compatibility testing.

### Governing architecture rule

```text
EngineBridge
  owns physical Gothic hooks
  transports native facts/events
  delegates behavior

EngineBridge
  does NOT own feature policy/state machines merely because a feature needs a hook
```

Bridge-local state whose lifetime is inherently hook-invocation/transport-local may stay. Audit by responsibility/lifetime rather than blindly moving everything.

### Candidate final collision modules

```text
EngineBridge
FrameCollisionMarkers
CollisionSources
CollisionSourceOperations
CollisionLifecycleGuard
Raw8FistCollision [candidate new feature module]
RuntimeClock
CollisionDiagnostics [diagnostic product only]
CollisionDiagnosticsDeep [opt-in research only]
AttackContinuationProtection [later]
```

### Known drift to inspect

Especially inspect current raw8 FIST state/policy inside `EngineBridge.cpp`, including stale `HumanFist*` naming. Also inspect marker/lifecycle/source-operation boundaries, persistent feature state ownership, CMake composition, dependency direction, hook ownership, and pre-combat `RunScriptFunctionScope` transport vs lifecycle-policy responsibility.

The refactor is parity-preserving. No behavior redesign merely for aesthetics.

---

## Diagnostic Redesign Decision

Formal rule:

> **Known successful behavior logs compactly. Unknown, unsupported, contradictory, repair, or invariant behavior logs richly.**

The current CORE logger still records substantial research-era detail that was useful during FIST/C1 discovery but makes larger tests unnecessarily huge.

Target products:

```text
PRODUCTION
  zero diagnostics compiled

CORE TEST
  compact regression facts for healthy known paths
  detailed records automatically for failures/anomalies/unknown families

DEEP TEST
  opt-in research instrumentation retaining historical low-level detail
```

CORE must remain sufficient to answer:

```text
what attack executed?
what factual source(s) were involved?
what marker existed?
accepted/rejected and why?
what physical state changed?
did native damage occur when relevant?
did C1/lifecycle finish correctly?
did anything unknown or anomalous happen?
```

For unsupported/unknown families — Sprint included until implemented — CORE must retain at minimum:

```text
actor
C1 generation if available
numeric + resolved action
phase / StatePosition
current animation
marker
source identity / UseType / collision group
equipped-side association if relevant
rejection reason
native damage target/source/attacker/caller correlation when it occurs
```

Potential default-noise reductions to audit:

```text
FIST trigger-state snapshots before/after every native callback
FIST trigger-state snapshots around ordinary AISetState
SetCollisionGroup records with no meaningful physical change
full healthy C1 START -> BINDING -> STATUS -> FINALIZATION chronology
full entity/contact addresses for every known successful damage
full ownership-decision dump for every healthy execution
full raw8 timing arithmetic for every already-proven early FIST
```

Do not simply delete reusable capability; move it to DEEP or make it anomaly/condition-driven where appropriate.

---

## Frozen Post-Refactor Sentinel

Before Sprint investigation or broader compatibility testing:

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

If this sentinel fails, stop and correct the refactor.

---

## Sequence After Sentinel

```text
SprintAttack factual source/transport/mechanism investigation
-> bounded first-class Sprint implementation only if evidence supports it
-> focused Sprint validation
-> native equipped-NPC marker controls: Goblin 1H / Demon 2H / Ogre Axe
-> additional prepared native/modded family controls
-> separated 2H vs Axe compatibility
-> separated 1H vs Rapier compatibility
-> final native mixed/stress collision regression
-> separate AttackContinuationProtection
-> combined mature collision regression
-> mature New Balance + relevant Jackydima compatibility
-> production migration into Script_G3AnimationBehaviors
-> diagnostics-free production validation
-> integrate Raise + Speed + Config
```

If any intermediate family fails, stop and resolve that exact failure before continuing.

---

## Tomorrow / New Chat

Do **not** give Work an open-ended architecture-design prompt.

Normal Chat should first inspect only the source/CMake/diagnostic material necessary to answer the audit questions and produce a concrete final design. Then freeze bounded mechanical Work task(s).

No more runtime testing is needed tonight.

---

## GitHub Desktop Handoff

Assistant documentation maintenance has advanced the remote branch beyond the User's local checkout.

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

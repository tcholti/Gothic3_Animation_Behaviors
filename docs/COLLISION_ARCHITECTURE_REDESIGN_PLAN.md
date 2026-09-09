# Collision Architecture and Diagnostic Redesign Plan

**Status:** Canonical planning authority for the next collision-framework redesign stage  
**Updated:** 2026-09-09  
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

Freeze the architecture, diagnostic-volume, SprintAttack-discovery, and sequencing decisions made after EV-249 so future chats and Work tasks do not reconstruct them from conversation memory.

This document does **not** authorize source changes by itself. Normal Chat must first complete the audit/design and freeze bounded Work responsibilities under `WORK_IMPLEMENTATION_PROTOCOL.md`.

Related authorities:

```text
SESSION_ENTRYPOINT.md          current front door
BETWEEN_CHATS.md               exact next-session handoff
DESIGN.md                      overall intended architecture
COLLISION_LOGGER_PLAN.md       diagnostic architecture
COLLISION_TEST_PLAN.md         validation authority
EVIDENCE_LEDGER_232_ONWARD.md  exact runtime conclusions
```

---

## 1. Closed Starting Point

The raw-8 FIST Quick family extension is CLOSED/PASS for the tested native/transformed Sabretooth fixture.

Implementation:

```text
2c9f745106506fc6bdb009b35720a4bb7c81ea11
```

Validation artifact:

```text
research/raw/2026.09.09_sabertooth_npc_pc_marked_attacks.log
source commit: 1a0416b10bed694d47eb4809b7367b507228962d
canonical conclusion: EV-249
```

Supported/proven raw-8 FIST families for the tested scope:

```text
Normal + Power + Quick
```

Preserve one shared raw-8 FIST mechanism. No Quick-specific hook, species branch, raw55 behavior, FIST_OFF, Fist ClearTriggeredList, equipped Fist window, direct damage, or weapon-C1 obligation is justified.

---

## 2. Newly Discovered SprintAttack Boundary

The EV-249 validation log repeatedly contains:

```text
Actor: Sabertooth
Action: 9
CurrentMovementAni: Sabertooth_Stand_None_Fist_P0_PowerAttack_Hit_...
G3AB_COL_FIST -> REJECTED_UNSUPPORTED_HIT
```

Gothic SDK action identity establishes:

```text
gEAction_SprintAttack = 9
```

Therefore these are **SprintAttack executions reusing a PowerAttack-named motion**, not `gEAction_PowerAttack` failures and not Quick failures.

Current source has no `AttackFamily_Sprint` and no SprintAttack callback/hook adapter in the collision framework.

### Accepted interpretation

SprintAttack is now a factual missing attack family that the finished collision framework should investigate and, where evidence supports it, implement as a **first-class family**.

Do not classify Sprint as Power merely because one observed motion contains `_PowerAttack_` in its filename. Native action identity outranks filename heuristics.

### Current evidence limit

So far SprintAttack has only been factually observed in this project on native Sabretooth using:

```text
source = Fist / raw8
```

No current evidence establishes that SprintAttack is Fist-only, creature-only, or absent from equipped attackers. Earlier test sets did not surface SprintAttack.

Therefore:

```text
DO NOT add a Sabretooth-specific exception
DO NOT assume Sprint == Power
DO NOT assume Sprint == Fist-only
DO NOT speculatively enable equipped RIGHT/LEFT/BOTH/OFF for Sprint
```

The target architecture must be able to accommodate a factual `AttackFamily_Sprint`, while the later Sprint investigation determines which source types/native mechanisms actually occur.

---

## 3. Why Architecture Redesign Comes Before More Compatibility Testing

The remaining NPC/mod-family/stress tests should certify the architecture intended to survive into production, not an intermediate layout that is refactored afterward.

Collision is currently the mature foundation that Raise, Speed, Config, and later independent behavior modules will join inside `Script_G3AnimationBehaviors`.

Therefore the sequence is deliberately:

```text
close Quick
-> audit/design final collision architecture
-> parity-preserving refactor
-> compact equivalence sentinel
-> investigate/implement SprintAttack
-> focused Sprint validation
-> resume broad compatibility matrix
```

This reduces the chance that large test campaigns must be repeated because structural changes happened afterward.

---

## 4. Governing Module Rule

```text
EngineBridge
=
sole physical Gothic hook owner
native callback/call-site transport
translation of hook-local facts
delegation into behavior modules

EngineBridge
!=
feature behavior owner
feature state-machine owner
collision policy owner
```

A bridge-resident object is not automatically architectural drift. State whose meaning/lifetime is inherently tied to one hook invocation or transport scope may legitimately remain in the bridge. The audit must classify by responsibility and lifetime, not by filename.

No feature module may install a competing physical hook for a hook already owned by `EngineBridge`.

---

## 5. Target Collision Structure

Candidate target after the audit/refactor:

```text
Script_G3AnimationBehaviors / research twin
|
+-- EngineBridge
|    sole physical hook owner
|    native transport/delegation only
|
+-- FrameCollisionMarkers
|    exact current-motion ownership
|    marker occurrence/dedupe
|    equipped RIGHT/LEFT/BOTH/OFF semantics
|    FIST marker dispatch into raw8 feature behavior
|
+-- CollisionSources
|    factual source identities / UseTypes
|
+-- CollisionSourceOperations
|    source-specific mutations
|
+-- CollisionLifecycleGuard
|    C1 execution/source obligations
|    exact terminal 7 -> 5 fail-safe
|
+-- Raw8FistCollision [candidate new module]
|    raw8 FIST execution state
|    initial latch ownership close
|    accepted-marker latch rearm policy
|    exact timing-permission state/identity
|    raw8-specific behavior decisions
|
+-- RuntimeClock
|
+-- AttackContinuationProtection [later independent module]
+-- AttackRaise
+-- AttackSpeed
+-- Config
+-- TargetAcquisition [future]
+-- Climbing [future]
```

The exact final module names and seams are frozen only after the source audit.

---

## 6. Known Architectural Drift to Audit

The most obvious current drift is raw-8 FIST feature state/policy inside `EngineBridge.cpp`, including concepts currently named `HumanFist*` even though human/species identity is no longer the governing boundary.

Audit at minimum:

1. raw8 FIST execution state and timing permission ownership;
2. marker behavior that may have leaked into the bridge;
3. lifecycle/C1 behavior that may have leaked into the bridge;
4. `RunScriptFunctionScope` and pre-combat bridge state — distinguish legitimate hook-lifetime transport from lifecycle policy;
5. source identity boundaries;
6. source-mutation boundaries;
7. feature dependency direction;
8. persistent feature state ownership;
9. CMake composition and behavior/diagnostic separation;
10. hook ownership — exactly one physical owner per Gothic hook;
11. stale `HumanFist*` naming that should become factual `Raw8Fist*` naming if moved/renamed without semantic change;
12. any other structural drift that would make future feature additions harder or blur responsibilities.

Architecture correction is parity-preserving. Do not redesign proven collision semantics merely for aesthetics.

---

## 7. Diagnostic Redesign — Governing Principle

> **Known successful behavior logs compactly. Unknown, unsupported, contradictory, or anomalous behavior logs richly.**

The current diagnostic product still carries research-era verbosity that was justified during discovery of FIST timing, C1 lifecycle, cleanup, and native damage routing. Those capabilities should not all remain in the default CORE output now that the mechanisms are established.

The goal is to support much larger regression/compatibility tests without creating logs that are unnecessarily huge or difficult to interpret.

---

## 8. Three Product/Diagnostic Levels

### Production

```text
Script_G3AnimationBehaviors
NO CollisionDiagnostics implementation
NO research log strings/state
NO diagnostic-only hooks
NO behavior dependency on diagnostics
```

This remains a mechanical compile/source-membership separation, not a runtime setting.

### CORE diagnostic twin — default testing

CORE should record the minimum facts needed to establish:

```text
what factual attack executed
what factual source(s) were involved
whether relevant marker(s) existed
accepted/rejected result and reason
physical source change when relevant
raw8 FIST opportunity outcome when relevant
native damage correlation when required
C1/lifecycle final outcome
repair/anomaly/failure if any
```

A healthy known execution should prefer compact event-style records rather than repeated full state blocks.

Conceptual example only:

```text
ATTACK gen=122 actor=... action=QuickR family=QUICK source=Fist/raw8 marker=FIST accepted=1
FIST   gen=122 latch=1->0 timing=EARLY_PERMISSION damage=Game+16E348 target=...
END    gen=122 lifecycle=PASS repair=NONE
```

This is a design target, not a frozen literal log syntax.

### DEEP diagnostic twin/profile — opt-in research

DEEP retains detailed historical/research instrumentation such as:

```text
full latch/SPU/animation-actor identities
real/max/threshold/synthetic timing arithmetic
hook-entry identities
contact iterator and detailed damage-call context
full AISetState before/after snapshots
full C1 transition chronology
caller/RVA/stack context where needed
motion lifetime probes
```

Deep instrumentation remains available for a concrete causal question but is disabled by default.

---

## 9. Conditional Verbosity Rules

Default CORE should automatically become more detailed when the event is important because it is not already a healthy known path.

```text
KNOWN + SUCCESSFUL
-> compact

KNOWN + FAILURE / REJECTION THAT SHOULD NOT OCCUR
-> detailed

UNSUPPORTED / UNKNOWN ACTION OR FAMILY
-> detailed

NEW SOURCE UseType / unexpected source identity
-> detailed

C1 anomaly / overlap / invariant issue
-> detailed

C1 repair / repair divergence
-> detailed

identity mismatch / stale timing permission / unexpected native route
-> detailed

DEEP explicitly enabled
-> full requested research detail
```

Do not reduce logs so aggressively that unknown families become invisible.

---

## 10. CORE Unknown-Family Discovery Contract

For unsupported/unknown attack traffic — including SprintAttack until implemented — retain at minimum:

```text
actor
C1 generation if available
numeric action
resolved action name when known
phase
StatePosition
current animation
marker opcode/name
source identity/name
source UseType
source collision group
equipped-side association if any
marker rejection reason
```

If native damage follows, correlate enough to establish:

```text
target
source
attacker
caller module/RVA
action/family context
generation when available
```

This contract is specifically intended to let larger tests discover SprintAttack or another unplanned family/source without requiring the old full-volume logger for every healthy execution.

---

## 11. High-Value CORE Compaction Candidates

During the diagnostic audit, explicitly evaluate whether these current records can move to DEEP or become anomaly/condition-driven:

```text
FIST trigger-state snapshot before/after every native attack callback
FIST trigger-state snapshot before/after ordinary AISetState
SetCollisionGroup records where no meaningful physical state changed
full healthy C1 START -> BINDING -> STATUS -> FINALIZATION chronology
full entity addresses/contact iterator data for every known successful damage
complete ownership-decision dump for every known successful attack
complete raw8 timing arithmetic for every already-proven early marker
```

Do not simply delete reusable capability. Prefer moving detail to DEEP or retaining it behind anomaly/unknown-family conditions.

C1 finalization, repair, divergence, and invariant failures must remain unambiguous in CORE.

---

## 12. SprintAttack Investigation After Refactor

After the architecture refactor and equivalence sentinel pass, investigate Sprint as a separate bounded responsibility.

Questions:

```text
Which actors actually execute gEAction_SprintAttack?
Which source UseTypes occur?
Is raw8 Fist the only factual source observed?
What script callback/hook transport owns SprintAttack?
What StatePosition does native Sprint use?
Does equipped SprintAttack exist in practical runtime?
For raw8 Sprint, does the same SPU+0x164 / Game+0x16E180 / +0x16E1A3 / +0x16E348 mechanism apply?
For equipped Sprint, if observed, does it use the established equipped marker/source path or require a distinct adapter?
```

Do not add behavior beyond what factual runtime/source/mechanism evidence supports.

If support is justified, prefer a first-class `AttackFamily_Sprint` adapter over species-, animation-name-, or Sabretooth-specific code.

---

## 13. Post-Refactor Equivalence Sentinel

Before Sprint research or the broad compatibility matrix, run one compact sentinel proving the structural refactor preserved established semantics:

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

If the sentinel fails, stop and fix the refactor before expanding testing.

---

## 14. Frozen Sequence From This Checkpoint

```text
1. Raw8 Quick FIST closure                               DONE — EV-249
2. SprintAttack missing-family discovery                IDENTIFIED
3. Complete collision architecture + diagnostic audit   NEXT — Normal Chat
4. Freeze parity-preserving structural correction        Normal Chat
5. Work performs bounded architecture/diagnostic refactor
6. Independent diff/static review + User local build
7. Compact post-refactor equivalence sentinel
8. SprintAttack source/transport/mechanism investigation
9. Bounded SprintAttack implementation if evidence supports it
10. Focused SprintAttack validation
11. Native equipped-NPC marker controls: Goblin/Demon/Ogre
12. Additional native/modded family controls
13. Separated 2H-vs-Axe compatibility
14. Separated 1H-vs-Rapier compatibility
15. Final native mixed/stress collision regression
16. Separate AttackContinuationProtection
17. Combined mature collision regression
18. Mature New Balance + relevant Jackydima compatibility
19. Production migration into Script_G3AnimationBehaviors
20. Diagnostics-free production validation
21. Integrate Raise + Speed + Config
```

No broad compatibility testing should be run before the architecture refactor and compact sentinel unless a new contradiction specifically requires it.

---

## 15. Next-Session Rule

Tomorrow/new chat:

1. read `SESSION_ENTRYPOINT.md`;
2. read `BETWEEN_CHATS.md`;
3. read this document;
4. inspect the current collision behavior/CMake/diagnostic source only as needed for the complete architecture audit;
5. Normal Chat designs the correction;
6. do **not** give Work an open-ended architecture-design task;
7. once design is frozen, create bounded Work task(s) that mechanically implement it.

The project resumes from the audit/design stage, not from Quick testing and not from Goblin/Demon/Ogre compatibility testing.

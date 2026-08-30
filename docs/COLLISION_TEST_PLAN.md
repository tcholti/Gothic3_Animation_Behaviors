# Collision Lifecycle Test Plan

**Status:** Current staged validation plan  
**Updated:** 2026-08-30

## Purpose

Validate the collision system through small falsifiable stages while preserving the already-closed lifecycle-safety contract.

Current state: `SESSION_ENTRYPOINT.md`.  
Exact transient continuation: `BETWEEN_CHATS.md`.  
Frozen rewrite: `SECOND_PASS_REWRITE_CONTRACT.md`.  
Lifecycle architecture: `COLLISION_LIFECYCLE_PLAN.md`.  
Release/build separation: `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

---

## 1. Current Rules

- Compare one conceptual variable at a time where practical.
- Do not reopen closed C1-R1 semantics because code structure changes.
- Do not add family/action/input/state-name-specific cleanup branches.
- Do not treat `RunScriptFunction`, FullStop or AISetState as unconditional cleanup authority.
- Preserve native behavior for executions that already clean themselves.
- Successful offensive request creates an exact physical-source obligation; successful transition away from `Item_Attack` fulfills it.
- Repair may act only on an already-owned exact outstanding source after native cleanup opportunity.
- Current equipped identity must establish source liveness before dereference/mutation.
- Keep structural rewrites behavior-preserving and validate before feature expansion.
- Preserve raw runtime logs exactly as produced.
- Do not ask the User to paste large successful logs into Chat; use repository raw artifacts.
- Follow `PROJECT_PIPELINE.md` for gate/artifact identity and `PROJECT_OPERATING_PROCEDURES.md` for build/deploy/test/log operations.
- Public release behavior must not depend on diagnostics; see `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

Authoritative research DLL remains:

```text
Script_FrameCollisionTest
```

until explicit later production migration.

---

## 2. Closed Gates — Retrieve, Do Not Rerun by Default

```text
B6 replacement/deferred ProcessScript candidate      EV-174–EV-181
B7/B7b termination / continuation loss               EV-182–EV-189
B8 cross-family abandonment generality               EV-190
B9 cleanup/finalization ordering                      EV-191
C1 shadow execution/source obligation core           EV-192–EV-193
C1 pre-Combat acquisition gap                        EV-194
C1-O1 outer ScriptFunction lifetime/correlation      EV-195–EV-196
hook/finalizer substrate stabilization               EV-199–EV-203
C1-O2-P1 lightweight dispatch bridge                 EV-204
C1-O2-P2 lazy pre-Combat acquisition/consumption     EV-205
C1-R1 controlled native-equivalent physical repair   EV-206–EV-207
post-EngineBridge unchanged runtime baseline         CLOSED/PASS 2026-08-30
```

C1-R1 validation is closed.

Validated R1 sequence:

```text
R1-A independent source audit = PASS
R1-B build / identity / isolated load-unload = PASS
R1-C targeted positive repair = PASS
R1-D no-op / reaction / GetUp controls = PASS
R1-E Dual source-specific repair = PASS
R1-E compact marked-Staff regression = PASS
R1-E broad mixed exercised coverage = PASS
R1-E focused unarmed/crossbow negative closure = PASS
```

Do not recreate the broad R1 program for structural changes. Use compact structural sentinels instead.

---

## 3. Accepted Collision-Safety Contract

```text
live ScriptFunction frame
= temporary correlator only where early acquisition needs it

C1 monotonic generation
= durable plugin execution identity

successful Item_Attack request
= exact source obligation

successful transition away from Item_Attack
= obligation fulfilled

destructive AISetState + obligation still outstanding
= terminal repair checkpoint
```

Accepted terminal repair:

```text
source obligation outstanding
+ exact current equipped RIGHT/LEFT pointer establishes liveness
+ actual current source group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList()
→ verify exact Item_Equipped(5)
```

Everything outside that predicate remains no-op/unresolved and non-mutating.

Two qualifications remain explicit and do not reopen the gate:

```text
- no positive runtime exercise of an outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED branch;
- no positive NPC destructive-abandonment / C1 physical-repair case is claimed.
```

---

## 4. Architecture Review / Synthesis — CLOSED

Completed:

```text
CollisionSources extraction
EngineBridge extraction + local build
one-by-one first per-CPP review
second-pass cross-file architecture synthesis
```

Frozen result:

```text
docs/SECOND_PASS_REWRITE_CONTRACT.md
```

Important second-pass correction:

```text
HookBridgeRuntime clock is behavior-required infrastructure
because marker same-update duplicate acceptance uses elapsed milliseconds.
```

Therefore the frozen rewrite renames it to `RuntimeClock`; it is not removed with diagnostics.

---

## 5. Post-EngineBridge Unchanged Runtime Baseline — CLOSED/PASS

Purpose was to prove the completed EngineBridge structural extraction at runtime using unchanged source/logger before changing architecture or diagnostics.

Primary compact raw artifact:

```text
research/raw/2026-08-30_post_enginebridge_unchanged_compact_collision_baseline.log
commit 5a33e5c134b027c440e40e6155cdf233aea049eb
SHA256 F42DCC7EFE7E178659861BD9E07E5631EB66E7C0DB1858D847C11656272E9783
```

Deterministic retrieval package:

```text
research/derived/2026-08-30_post_enginebridge_unchanged_compact_collision_baseline_large_log/
commit fb2644d2952923f5a9a3d41ba881a342ef0d8ff2
```

The compact run preserved:

```text
ordinary melee native cleanup with no R1 repair
known destructive stale-source exact C1-R1 physical repair
marked Staff RIGHT → OFF → RIGHT semantics
marker duplicate / authored occurrence protections
Dual source specificity
clean negative behavior / shutdown
```

The user omitted the intended focused Fist exercise from that primary session. The primary artifact was preserved unchanged and Fist was closed separately rather than rerunning or replacing it.

Supplemental Fist artifact:

```text
research/raw/2026-08-30_post_enginebridge_fist_negative_closure.log
commit 269faad334ef918ca16f6401751d47693e48520f
```

Focused Fist result:

```text
resolved current source = Fist
source collision group before = 0
Gothic requested Item_Attack(7)
actual resulting group after request = 0
therefore successfulOffenseRequest = false
C1 OffensiveRequestCount = 0
OutstandingBeforeFinalization = 0
RepairAttempted = 0
PhysicalCollisionChanged = 0
finalization = NO_OP_NO_OUTSTANDING
```

Conclusion:

> **EngineBridge extraction preserved the proven collision lifecycle, marker behavior, exact source ownership, native cleanup, C1-R1 repair and current Fist negative semantics.**

Do not rerun this unchanged baseline by default.

---

## 6. Current Gate — Frozen Rewrite Implementation

Architecture contract:

```text
docs/SECOND_PASS_REWRITE_CONTRACT.md
```

The rewrite is structural/semantic-preserving only.

Required source/build gate after implementation:

```text
git diff --check
bounded contract audit
build Script_FrameCollisionTest diagnostic target
build Script_FrameCollisionBehaviorTest behavior-only target
verify behavior-only target excludes diagnostic source/state/hooks
```

The behavior-only target is a mechanical architecture test: collision behavior must compile without `CollisionDiagnostics` or deep research instrumentation.

Do not deploy the diagnostic and behavior-only prototypes together.

If a concrete source/API/calling-convention contradiction appears during implementation:

```text
STOP
→ report the contradiction
→ do not redesign around it ad hoc
```

---

## 7. Post-Rewrite Diagnostic Sufficiency Regression

Run the diagnostic target with compact default diagnostics; deep probes stay off.

Minimum sentinels:

```text
known positive stale-source repair
ordinary native cleanup no-op
legitimate reaction cleanup no-op
Dual source independence
one marked-source regression
Fist/unarmed negative
crossbow negative
clean shutdown
```

Default compact diagnostics must still establish:

```text
marker ownership/suppression/result
exact source requested/before/after transition
C1 generation + exact source obligation
cleanup fulfillment
pre-Combat acquisition/consumption when present
finalization/repair outcome
explicit invariant/failure signals
```

If the compact logger makes any required fact ambiguous, the diagnostic reduction is too aggressive.

---

## 8. Behavior-Only Smoke / Equivalence

After diagnostic sufficiency passes, deploy the behavior-only prototype **instead of** the diagnostic target.

Purpose:

```text
prove intended behavior does not depend on diagnostic source/state/hooks
```

Freeze the exact small runtime matrix only after the diagnostic regression passes. Do not infer behavior-only correctness from successful compilation alone.

---

## 9. Later Phase — C1 vs Marker-Bookkeeping Simplification

Only after rewrite + diagnostic sufficiency + behavior-only smoke pass.

Classify every existing marker guard/check into:

```text
A. execution-lifetime inference genuinely superseded by stronger C1/native authority
B. independent marker invariant still required
```

Preserve group B:

```text
exact current-motion marker ownership
authored occurrence budgets
same-update duplicate/replay protection
repeated-contact ClearTriggeredList rearm
RIGHT/LEFT/BOTH/OFF exact-set behavior
StatePosition native-activation suppression
interruption/dead-execution rejection
```

EV-131–EV-133 and EV-167 are mandatory evidence before removing execution-retirement machinery.

---

## 10. Later Feature Sequence

### Equipped-melee marker expansion

Expand one native attack mechanism at a time. Do not invent action-specific marker names.

### Fist source-adapter decision

Investigate separately after equipped-melee marker coverage stabilizes. Do not force Fist through weapon `Item_Attack` semantics.

### Complete marker + lifecycle regression

Run purposeful broad regression after marker/source expansion.

### AttackContinuationProtection

Investigate/implement separately from `CollisionLifecycleGuard`. It prevents the known destructive consequence; C1-R1 remains the fail-safe underneath.

### Mature research compatibility gate

Test New Balance / relevant Jackydima stack before production migration. Do not rely on arbitrary load order or assumed hook chaining.

### Production foundation

Retain the mature modular research architecture and migrate/redesign Raise, speed and config into it. Do not pour the collision system back into the old v0.1 production layout.

Later systems such as target acquisition and climbing use the same central-bridge / independent-module / diagnostics-free-release architecture.

### Final public release

Final `Script_G3AnimationBehaviors` is diagnostics-free and receives its own New Balance/Jackydima compatibility regression. Retain a separate instrumented diagnostic twin for controlled reproduction.

---

## 11. Non-Combination Rules

Unless an explicitly frozen contract says otherwise, do not combine:

```text
structural rewrite + feature expansion
marker simplification + new attack-family support
Fist support + unrelated equipped-weapon changes
AttackContinuationProtection + CollisionLifecycleGuard redesign
production migration + bad-skip investigation
production migration + Raise/speed redesign
New Balance compatibility fixes + unrelated behavior changes
```

If a concrete source/API/calling-convention contradiction requires crossing one of these boundaries, stop and reassess in Normal Chat.

---

## 12. Evidence Handling

For implementation/runtime stages:

```text
freeze exact question/matrix/raw filename
→ preserve raw unchanged
→ publish raw
→ use deterministic large-log reduction only when retrieval requires it
→ interpret in Normal Chat
→ update canonical evidence/current authorities only when meaning changes
```

Do not paste large successful logs into Chat.

# Collision Validation Plan

**Status:** Current collision validation authority  
**Updated:** 2026-09-26

## Purpose

Define the current collision-validation gates, acceptance invariants, and remaining release sequence.

This file owns **what must still be tested and what counts as acceptance**. It does not own implementation architecture, settled collision semantics, probe chronology, or detailed proof.

Current state: `SESSION_ENTRYPOINT.md`.  
Established facts: `COLLISION_REFERENCE.md`.  
Architecture: `DESIGN.md` / `COLLISION_LIFECYCLE.md` / `COLLISION_DIAGNOSTICS.md`.  
Permanent raw55: `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`.  
Proof: `EVIDENCE_INDEX.md`.

The detailed pre-New-Balance standalone campaign plan is preserved at:
`archive/investigations/COLLISION_TEST_PLAN_PRE_NEW_BALANCE_2026-09-24.md`.

---

## 1. Standing validation rules

- Do not reopen a closed causal gate without concrete contradictory evidence or a deliberate scope extension.
- Factual native action/source/UseType identity outranks animation filename inference.
- Native cleanup gets first opportunity.
- Equipped RIGHT / LEFT / BOTH / OFF control the desired physical equipped-source set; they do not guarantee uniform native target/contact/damage eligibility.
- Raw8 FIST and raw55 PhysicalFist are separate mechanisms.
- C1 monotonic generation remains the durable execution identity for marker occurrence/dedupe and equipped-source obligations.
- C1-R1 may repair only an exact owned outstanding source after native cleanup opportunity and current-equipped liveness are established.
- Diagnostics must not be required for behavior correctness.
- Diagnostic and behavior-only collision twins are mutually exclusive at runtime.
- Freeze one falsifiable question and minimum controls before a new causal investigation.
- Large regression runs use compact CORE diagnostics; unknown/anomalous events retain richer classification.
- Every uploaded runtime batch closes fully under POP-06 before the next batch unless an explicit active-comparison need is recorded.
- If a broad test exposes a failure, reduce it to the smallest factual route before source changes are considered.

Current research products:

```text
Script_FrameCollisionTest
  instrumented diagnostic twin

Script_FrameCollisionBehaviorTest
  diagnostics-free behavior twin
```

---

## 2. Standalone collision regression — CLOSED/PASS

The mature collision feature completed the broad standalone final-source campaign on frozen source:

`f1f5d2aad3edc3564a9a8b40541840b94f8fa903`

Closed phase map:

```text
Phase 1  human marker matrix                  PASS EV-299–EV-306
Phase 2  Orc matrix                           PASS EV-309–EV-310
Phase 3  other equipped NPC/creatures         PASS EV-311–EV-314
         equipped Sprint promotion/acceptance PASS through EV-329
Phase 4  body-contact / raw8 / raw55          PASS EV-337–EV-367
Phase 5  Axe separation                       PASS EV-371
Phase 6  Rapier separation                    PASS EV-372
Phase 7  stress regression                    PASS EV-373–EV-374
```

Final frozen-source comprehensive stages A–D are CLOSED/PASS through EV-374. EV-375 additionally verifies the Zombie+Axe copied/renamed asset-gap remedy.

Later New Balance compatibility changes do not reopen the entire standalone campaign. §4.5 owns the bounded post-compatibility standalone sentinel.

---

## 3. Regression acceptance invariants

Across compatibility and later release validation protect at minimum:

```text
equipped RIGHT / LEFT / BOTH / OFF exact-set behavior
repeated-contact ClearTriggeredList semantics
Power / Pierce / SimpleWhirl / Hack behavior
supported raw8 Normal / Power / Quick / Sprint
supported permanent raw55 Normal / Quick / Power / Sprint-origin
supported permanent equipped Sprint RIGHT / LEFT / BOTH / OFF policy
unmarked raw8/raw55 native fallback
raw8/raw55/equipped coexistence
C1 generation-scoped occurrence/dedupe
C1-R1 exact-source terminal repair
native cleanup + outstanding-zero finalization
one-live-collision-twin deployment invariant
compact CORE anomaly discovery
Zombie/Axe/Rapier separation compatibility
EV-375 Zombie+Axe asset-gap remedy
```

---

## 4. New Balance exact distributed-bundle compatibility — OPEN / RAW55 SPRINT SECOND-FIST FOLLOW-UP CURRENT

Environment to certify:

```text
New Balance 0.7 as distributed
+ all normally used/distributed New Balance DLLs
+ relevant Jackydima collision DLLs including Script_AttackCollision where applicable
+ Zombie Separation
+ Axe Separation
+ Rapier Separation
+ EV-375 copied/renamed zombie Axe assets
+ exactly one Gothic3_Animation_Behaviors collision twin
```

Source-level preflight alone is not final certification.

### 4.1 Environment preflight

Require:

```text
exact intended New Balance bundle/DLL composition
separation mods + EV-375 zombie Axe asset fix
exactly one G3AB collision twin live
startup succeeds
expected diagnostic banner present for diagnostic twin
```

Record any environment difference because compatibility is environment-specific.

### 4.2 Representative full-gate coverage

Across the eventual complete gate include:

```text
equipped marker combat
  representative 1H / dual-1H / 2H / Staff

raw8 body-contact
  opportunity open/rearm/contact/finalization
  knocked-down/get-up control

raw55 PhysicalFist
  representative Troll/PhysicalFist marked routes

separation coexistence
  representative separated motions
  at least one Zombie+Axe EV-375 route

mixed stress
  actor/target/weapon/C1 churn with full intended stack
```

### 4.3 Acceptance

Require for the tested environment:

```text
no startup/load crash or hook conflict
expected factual action/source/UseType ownership
expected marker acceptance/fail-closed behavior
expected physical group activation/cleanup
raw8 opportunities consume/close correctly
raw55 routes remain bounded to their factual contract
separated animation families preserve factual source semantics
C1 final obligations zero, or bounded exact C1-R1 repair converges safely
no repair divergence
no invariant/generation contradiction
no unexpected stale ownership/dedupe leakage
clean unload
no user-observed collision regression
```

A compatibility failure does not authorize a broad patch. Reduce the exact factual route first.

### 4.4 Raw55 New Balance SP2 compatibility — EV-376–EV-380

Implemented and runtime-confirmed corrections:

```text
6eb3e3ca96da55e89127c24d5f656e05610d315f
  true-Power first FIST: current POWER + explicit {SP1,SP2} + earlyOpeningSuppressed
  true-Power second FIST: current POWER + explicit {SP1,SP2}
  Sprint-origin later/current-Power FIST: current POWER + explicit {SP1,SP2}
  runtime PASS EV-378

ce59e5a2bad564652eaba970e959bdef0b479d82
  Sprint-origin first FIST: current SPRINT + explicit {SP1,SP2} + earlyOpeningSuppressed
  runtime PASS EV-379
```

Current deployed diagnostic hash:

`490AC7F6F6931784EA9D5697BA5758DAB11FC0B9437A247FFA9FBC7E13BA1E4C`

EV-380 deliberate second-marker timing sweep:

```text
frame 1+3:
  marker1 SPRINT/SP2 -> accepted/open
  marker2 SPRINT/SP2 -> currently rejected

frame 1+8:
  marker1 SPRINT/SP2 -> accepted/open
  marker2 may be SPRINT/SP2 -> rejected
  OR POWER/SP2 -> accepted/clear-only rearm

frame 1+15:
  marker1 SPRINT/SP2 -> accepted/open
  marker2 POWER/SP2 -> accepted/clear-only rearm
  zero CORE marker anomalies in the full 1+15 log
```

The tested Hit motion is already SP2 by frame1, so the deliberate earliest marker probe did not expose Sprint/SP1.

The smallest evidence-backed follow-up rule is therefore:

```text
immutable origin = SPRINT

current POWER:
  preserve existing explicit SP1 or SP2

current SPRINT:
  additionally accept explicit SP2 only
```

Do **not** widen to current-Sprint SP1, generic `(SPRINT || POWER) && {SP1,SP2}`, or `StatePosition >= 1` without evidence.

Before source implementation, the active bounded investigation remains the controlling contract:

`work/active/COLLISION_NEW_BALANCE_RAW55_SPRINT_SECOND_FIST_STATE_INVESTIGATION.md`

#### Sheath/native-contact control

The User reports that sheathing immediately before Troll Sprint can sometimes appear to reduce landed contacts. Current logs do not establish a marker failure, because accepted markers author native opportunities rather than guarantee damage.

After the Sprint second-FIST source correction is implemented/reviewed, use a controlled A/B:

```text
A. marked Troll Sprint, no sheath
B. marked Troll Sprint, deliberate sheath immediately before attack
C. unmarked/native Troll Sprint, no sheath
D. unmarked/native Troll Sprint, same sheath timing
```

Interpretation:

```text
markers accepted/rearmed but no contact
-> downstream native target/contact/player-state question

marker rejected/ownership lost
-> G3AB marker-route question

same effect in unmarked/native Sprint
-> native/New Balance behavior rather than authored-marker ownership
```

Only add diagnostics if this controlled comparison remains ambiguous. Do not add production damage/contact policy.

#### Deferred Normal early-marker question

EV-380 incidentally shows very early Normal marker2 can arrive at `NORMAL/SP0` and is rejected by the current second-FIST SP1 gate, while reviewed Quick repeated FIST can succeed at SP0.

This is a separate future research responsibility relevant to animator-authored timing. Do not change Normal until a causal probe establishes whether SP1 is a genuine native prerequisite or a conservative historical guard.

### 4.5 Standalone / no-New-Balance post-compatibility sentinel

The mod must remain correct when New Balance / Script_AttackCollision is absent or disabled. New Balance support is additive, not a dependency.

Run after the focused New Balance correction closes and before final collision-source certification / production migration.

Environment:

```text
New Balance / Script_AttackCollision absent or disabled
normal standalone G3AB test environment
exactly one current diagnostic collision twin live
same final compatibility source
```

Minimum raw55 sentinel:

```text
1. Sprint-origin single-FIST
   -> ordinary standalone factual state accepted
   -> authored opening only
   -> native cleanup group5 / zero outstanding

2. Sprint-origin double-FIST
   -> first marker accepted/open
   -> later marker repeated-contact semantics
   -> clean cleanup

3. true-Power single + double control
4. Normal + Quick control
5. unmarked raw55 native-fallback sentinel
```

Acceptance:

```text
no crash/startup conflict
no new supported-traffic marker anomaly
SP1 behavior remains accepted where standalone produces SP1
SP2 widening creates no stale/cross-family ownership
first FIST opens once; second remains clear-only rearm
native cleanup returns exact raw55 source to group5
final obligations zero
unmarked fallback remains native
no user-observed regression
```

Do **not** rerun the full EV-299–EV-374 campaign unless this sentinel finds contradictory evidence.

---

## 5. Evidence / artifact boundary

For each runtime batch:

```text
freeze setup + filename
-> User runs locally
-> publish unchanged raw artifact
-> Normal Chat interprets
-> concise canonical EV
-> promote changed reusable fact
-> archive processed runtime artifact when no active comparison remains
-> restore research/raw/ to genuine open inputs only
-> run POP-12 validation
-> only then next batch
```

The EV-379 and EV-380 BlackTroll logs remain temporarily in `research/raw/` because the immediate Sprint timing/sheath comparison is still open. Archive under POP-06 when that controlled comparison closes.

---

## 6. Production collision migration — after compatibility gates

After New Balance compatibility **and** the standalone sentinel pass:

```text
mature collision behavior
-> migrate into src/Script_G3AnimationBehaviors
-> diagnostics remain separate
-> release-purity/integration validation
```

Do not migrate before both gates close.

---

## 7. AttackContinuationProtection — separate later responsibility

`AttackContinuationProtection` remains separate from collision cleanup and stays paused unless deliberately reopened.

```text
AttackContinuationProtection
= prevent/defer proven destructive bad-skip consequence at factual native decision point

CollisionLifecycleGuard / C1-R1
= exact-source fail-safe if cleanup is nevertheless lost
```

---

## 8. Current sequence

```text
standalone broad final-source regression    CLOSED/PASS EV-299–EV-374
Zombie+Axe asset-gap remedy                 PASS EV-375
New Balance controls                        PASS EV-377
first raw55 SP2 correction                  RUNTIME PASS EV-378
Sprint-first SP2 correction                 RUNTIME PASS EV-379
Sprint second-FIST state envelope           MAPPED EV-380
-> freeze smallest SPRINT/SP2 second-FIST source correction
-> focused runtime acceptance including frame8 transition-race fixture
-> controlled sheath/no-sheath + unmarked/native control
-> representative/full-stack New Balance compatibility
-> standalone/no-New-Balance raw55 sentinel
-> production collision migration
-> diagnostics-free integration validation
-> later Raise + Speed + Config under SPEED_CONTROL_ARCHITECTURE.md / ADR-0004

Normal early second-FIST SP0 question is separate/deferred.
AttackContinuationProtection remains separate unless deliberately reopened.
```

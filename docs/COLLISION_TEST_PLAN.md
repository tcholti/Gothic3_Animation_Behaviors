# Collision Validation Plan

**Status:** Current collision validation authority  
**Updated:** 2026-09-27

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
- An accepted marker/open/rearm does **not** guarantee `ONDAMAGE`; native target/contact/geometry/gameplay state remain authoritative.
- A processed large log is analyzed through its derived package under POP-07; the large raw artifact remains provenance and is not the routine retrieval surface.

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

Later compatibility changes do not reopen the entire standalone campaign. §4.5 owns the bounded post-compatibility standalone sentinel for the changed final candidate.

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

## 4. New Balance exact distributed-bundle compatibility — CLOSED/PASS EV-384

Environment certified by the representative gate:

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

### 4.1 Environment preflight

Required and satisfied for the tested compatibility environment:

```text
exact intended New Balance bundle/DLL composition
separation mods + EV-375 zombie Axe asset fix
exactly one G3AB collision twin live
startup succeeds
expected diagnostic banner present for diagnostic twin
```

Compatibility remains environment-specific. A materially different future DLL/mod composition is a new compatibility scope.

### 4.2 Representative full-gate coverage — CLOSED/PASS EV-383–EV-384

The complete gate covered representative equipped marker combat, raw8 body-contact, raw55 PhysicalFist, separation coexistence, and broad mixed gameplay/actor/source/weapon/world churn.

EV-383 adds dual-1H four-marker / three-offensive-window authoring proof. EV-384 supplies broad mixed-gameplay stress closure. The User reported correct gameplay behavior. Its processed whole-run package contains 27 C1 finalization/repair events and 5 marker anomalies; the reviewed marker anomalies are Whirl `REJECTED_C1_GENERATION_INCONSISTENCY` fail-closed stale callbacks, while reviewed single/dual-source C1-R1 repairs converge exact outstanding group7 sources to group5 with no sampled repair divergence. The run ends with normal cleanup and clean unload.

No production source file changed between the EV-382 correction and EV-383/EV-384 runtime evidence.

### 4.3 Acceptance — SATISFIED FOR TESTED ENVIRONMENT

The representative gate satisfies the intended New Balance environment requirements for startup/load compatibility, factual ownership, marker behavior, physical cleanup, raw8/raw55 bounded behavior, separation coexistence, lifecycle convergence, clean unload, and absence of user-observed collision regression.

Missing `ONDAMAGE` is not automatically a failure when ownership/open/rearm/cleanup are correct. EV-381 proves both marked and native raw55 collision windows can legitimately miss downstream.

### 4.4 Focused raw55 New Balance compatibility — CLOSED/PASS EV-376–EV-382

Runtime-confirmed corrections:

```text
6eb3e3ca96da55e89127c24d5f656e05610d315f
  true-Power first/second SP2 compatibility
  Sprint-origin later/current-Power SP2 compatibility

ce59e5a2bad564652eaba970e959bdef0b479d82
  Sprint-origin first current-Sprint SP2 compatibility

4c85193f4efd31e789bc07d7e3c71d31a9b5326e
  Sprint-origin second current-Sprint SP2 compatibility

a31c66b97e45c27d0739b7df51252d33f490e7e1
  Normal second-FIST explicit {SP0,SP1} acceptance
```

The New Balance evidence establishes the compatible SP2 and Action9→Action2 transition routes. It did not establish current-SPRINT/SP1 second-FIST behavior; the post-compatibility standalone sentinel deliberately exists to ensure those compatibility additions remain additive rather than becoming a New Balance dependency.

Hard boundaries remain:

```text
NO generic StatePosition range widening
NO family-independent Normal SP0 policy
NO visited-target or hit1 flags
NO marker delays/queues/timers
NO species/name/filename/DLL policy
NO custom damage/contact ownership
```

### 4.5 Standalone / no-New-Balance post-compatibility sentinel — PARTIAL FAIL EV-385 / CURRENT

The mod must remain correct when New Balance / Script_AttackCollision is absent or disabled. New Balance support is additive, not a dependency.

Environment:

```text
New Balance / Script_AttackCollision absent or disabled
normal standalone G3AB test environment
exactly one current diagnostic collision twin live
same final compatibility source lineage
```

Minimum raw55 sentinel:

```text
1. Sprint-origin single-FIST
2. Sprint-origin double-FIST
3. true-Power single + double control
4. Normal + Quick control
5. unmarked raw55 native-fallback sentinel
```

#### EV-385 first batch result

The User ran four BlackTroll/raw55 marked fixtures:

```text
double FIST 1+3
double FIST 1+8
double FIST 1+15
single-FIST control set
```

Result:

```text
1+3 Sprint-origin:
  first FIST current SPRINT/SP1 -> accepted/open
  second FIST same C1/source/origin, still current SPRINT/SP1
  -> REJECTED_UNSUPPORTED_HIT
  -> no second-FIST ClearTriggeredList
  repeats in four distinct Sprint C1s

1+8 / 1+15 Sprint-origin:
  first FIST current SPRINT/SP1 -> accepted/open
  second FIST same Sprint-origin after current Action9 -> Action2 transition
  -> current POWER/SP1
  -> accepted clear-only rearm
  -> clean native cleanup

single-FIST Sprint-origin:
  current SPRINT/SP1 accepted/open/clean cleanup
```

All four logs remain lifecycle-safe: no C1 invariant warning and no terminal C1 repair anomaly. The `1+3` failure is therefore a narrow supported-traffic eligibility hole, not cleanup corruption.

EV-385 directly establishes the previously missing factual state:

```text
origin family = SPRINT
current family = SPRINT
second authored FIST
StatePosition = SP1
same C1 + same exact RIGHT raw55 source
```

Current production code accepts current-SPRINT/SP2 only for this arm, so the sentinel **does not pass on the pre-correction source**.

#### Frozen correction gate

Active task:

`docs/work/active/COLLISION_RAW55_STANDALONE_SPRINT_SECOND_FIST_SP1_COMPATIBILITY_CORRECTION.md`

Required behavior after correction:

```text
Sprint-origin second FIST:
  current POWER  -> explicit SP1 or SP2
  current SPRINT -> explicit SP1 or SP2
```

This is an explicit evidence-backed union, not generic `>=1` widening.

#### Post-correction final-candidate acceptance

Before the standalone sentinel can close:

```text
standalone 1+3 direct retest:
  marker1 SPRINT/SP1 accepted/open
  marker2 SPRINT/SP1 accepted clear-only
  marker2 GroupRequested=0
  marker2 ClearTriggeredList=1
  native cleanup -> group5
  final Outstanding=0
  no supported-traffic marker anomaly

preserve representative:
  1+8 / 1+15 current POWER/SP1 continuation
  single-FIST current SPRINT/SP1

because behavior source changed after EV-384:
  bounded New Balance Sprint SP2 / transition regression

finish missing standalone controls:
  factual true-Power single + double
  unmarked raw55 native fallback
```

Normal and Quick marked traffic was healthy in EV-385, but factual true-Power origin was not observed in the four uploaded logs and unmarked raw55 was not part of the batch.

Do **not** rerun the full EV-299–EV-374 or full EV-384 campaigns unless focused final-candidate validation finds contradictory evidence.

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

The EV-382 Normal logs, EV-384 New Balance stress log, and EV-385 four-log standalone batch are processed and archived byte-identically. `research/raw/` should contain only `Keep.txt` after EV-385 closure.

---

## 6. Production collision migration — BLOCKED UNTIL CORRECTED SENTINEL PASS

The broader New Balance compatibility gate is closed through EV-384, but EV-385 found a standalone compatibility hole on the post-compatibility source.

Therefore:

```text
EV-385 correction
-> final-candidate focused standalone/New-Balance validation
-> finish missing standalone sentinel controls
-> only after full sentinel PASS:
   mature collision behavior
   -> migrate into src/Script_G3AnimationBehaviors
   -> diagnostics remain separate
   -> release-purity/integration validation
```

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
standalone broad final-source regression      CLOSED/PASS EV-299–EV-374
Zombie+Axe asset-gap remedy                   PASS EV-375
focused New Balance raw55 compatibility       CLOSED/PASS EV-376–EV-382
dual-1H four-marker / three-window authoring  PASS EV-383
representative/full-stack New Balance         CLOSED/PASS EV-384
standalone/no-New-Balance raw55 sentinel      PARTIAL FAIL EV-385
-> bounded Sprint-origin current-SPRINT/SP1 second-FIST correction CURRENT
-> focused corrected-final-candidate validation
-> finish true-Power + unmarked standalone sentinel controls
-> production collision migration only after sentinel PASS
-> diagnostics-free integration validation
-> later Raise + Speed + Config under DESIGN.md §3 / ADR-0004

AttackContinuationProtection remains separate unless deliberately reopened.
```
# Collision Validation Plan

**Status:** Current collision validation authority  
**Updated:** 2026-09-24

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
- Every uploaded runtime batch closes fully under POP-06 before the next batch.
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

The mature collision feature has completed the standalone final-source campaign on frozen source:

`f1f5d2aad3edc3564a9a8b40541840b94f8fa903`

Closed phase map:

```text
Phase 1  human marker matrix                  PASS EV-299–EV-306
Phase 2  Orc matrix                          PASS EV-309–EV-310
Phase 3  other equipped NPC/creatures        PASS EV-311–EV-314
         equipped Sprint promotion/acceptance PASS through EV-329
Phase 4  body-contact / raw8 / raw55          PASS EV-337–EV-367
Phase 5  Axe separation                       PASS EV-371
Phase 6  Rapier separation                    PASS EV-372
Phase 7  stress regression                    PASS EV-373–EV-374
```

Final frozen-source comprehensive stages:

```text
A. body-contact creatures                    CLOSED/PASS EV-365–EV-366
   supplemental destructive C1-R1 stress     PASS EV-367
B. equipped actors + cumulative player matrix CLOSED/PASS EV-368
C. separation compatibility                  CLOSED/PASS EV-369–EV-372
D. mixed stress                              CLOSED/PASS EV-373–EV-374
```

### Stage-D closure basis

EV-373 and EV-374 supply two long unscripted mixed-gameplay runs with heavy C1 churn, actor/target changes, weapon changes, raw8/equipped interleaving, repeated marker occurrences, and natural cleanup/repair opportunities.

EV-374 itself does **not** contain a raw55/Troll route. Stage-D closure is intentionally compositional, not based on pretending every mechanism appeared in one log. Exact frozen-source campaign evidence already supplies:

```text
raw55 + equipped coexistence      EV-366
raw8/raw55/equipped coexistence   EV-359–EV-364
long unscripted mixed churn       EV-373–EV-374
```

The standing campaign rule is therefore preserved: coverage is compositional when the exact frozen source and relevant semantics are actually exercised. Do not schedule redundant repeats solely because evidence was gathered under a different phase label.

No collision-source change is justified by EV-373 or EV-374.

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
Axe-separation compatibility
Rapier-separation compatibility
```

---

## 4. New Balance exact distributed-bundle compatibility — CURRENT

The next gate is runtime compatibility with the **exact New Balance 0.7 distributed bundle as the User actually runs it**, including its DLL set and the relevant Jackydima collision components such as `Script_AttackCollision` where applicable.

Source-level preflight evidence is not sufficient final certification.

Do not assume arbitrary same-function hook chaining or DLL load-order safety. Do not omit one of the normally installed New Balance DLLs merely to make the first test easier; reduction is appropriate only after a concrete failure needs isolation.

### 4.1 Environment preflight

Before interpreting gameplay:

```text
exact New Balance bundle installed
all normally distributed/used New Balance DLLs present
relevant AttackCollision component present where part of that environment
exactly one Gothic3_Animation_Behaviors collision twin live
startup succeeds
expected diagnostic banner present when using diagnostic twin
```

Record any load-order or DLL-composition difference because compatibility is environment-specific.

### 4.2 Representative runtime coverage

Use several representative cases rather than one smoke. Across the gate include:

```text
equipped marker combat
  -> representative 1H/dual-1H/2H/Staff behavior and cleanup

raw8 body-contact
  -> marked opportunity open/rearm/contact/finalization
  -> include knocked-down/get-up control because New Balance changes some behavior there

raw55 PhysicalFist
  -> representative Troll/PhysicalFist marked route

separation-mod compatibility
  -> at least one already-proven separated Axe or Rapier route if that mod is part of the intended installed environment

mixed stress
  -> actor/target/weapon/C1 churn with the New Balance DLL set live
```

The raw8 knocked-down/get-up control is policy-neutral. The collision system must not force damage or vulnerability; it only needs to preserve correct authored opportunity/open/rearm/close behavior while the installed gameplay stack remains free to permit, block, or alter the gameplay result.

### 4.3 Acceptance

For the tested environment require:

```text
no startup/load crash or hook conflict
expected factual action/source/UseType ownership
expected marker acceptance/fail-closed behavior
expected physical group activation/cleanup
raw8 opportunities consume/close correctly
raw55 routes remain bounded to their factual contract
C1 final obligations return to zero, or bounded exact C1-R1 repair converges safely
no repair divergence
no invariant/generation contradiction
no unexpected stale ownership/dedupe leakage
clean unload
no user-observed collision regression
```

A compatibility failure does not authorize an immediate broad source patch. First reduce the exact failing DLL composition and factual collision route.

---

## 5. Evidence / artifact boundary

For each runtime run:

```text
freeze setup + filename
-> User runs locally
-> publish unchanged raw artifact
-> Normal Chat interprets
-> concise canonical EV
-> promote changed reusable fact to current reference/architecture when needed
-> archive processed runtime artifact
-> restore research/raw/ to intake-only state
-> run POP-12 validation
-> only then next batch
```

`research/raw/` is active intake, not history storage.

---

## 6. Production collision migration — after compatibility gate

After standalone + New Balance compatibility pass:

```text
mature collision behavior
-> migrate into src/Script_G3AnimationBehaviors
-> diagnostics remain separate
-> release-purity/integration validation
```

Do not migrate before the compatibility gate closes.

---

## 7. AttackContinuationProtection — separate later responsibility

`AttackContinuationProtection` remains separate from collision cleanup.

```text
AttackContinuationProtection
= prevent/defer the proven destructive bad-skip consequence at its factual native decision point

CollisionLifecycleGuard / C1-R1
= exact-source fail-safe if collision cleanup is nevertheless lost
```

Before any later implementation, reproduce the known bad-skip route and validate outside-attack, legitimate-reaction, and New-Balance-enabled controls. Do not begin with an independent timer, polling loop, unconditional attack-state override, or teardown resurrection.

This work remains paused unless deliberately reopened.

---

## 8. Current sequence

```text
standalone final-source regression       CLOSED/PASS EV-299–EV-374
-> New Balance exact bundle compatibility CURRENT
-> production collision migration
-> diagnostics-free integration validation
-> later Raise + Speed + Config

AttackContinuationProtection remains separate unless deliberately reopened
```

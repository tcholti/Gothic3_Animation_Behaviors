# Collision Validation Plan

**Status:** Current collision validation authority  
**Updated:** 2026-09-25

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

Final frozen-source comprehensive stages:

```text
A. body-contact creatures                     CLOSED/PASS EV-365–EV-366
   supplemental destructive C1-R1 stress      PASS EV-367
B. equipped actors + cumulative player matrix CLOSED/PASS EV-368
C. separation compatibility                   CLOSED/PASS EV-369–EV-372
D. mixed stress                               CLOSED/PASS EV-373–EV-374
```

EV-375 additionally verifies the proposed Zombie+Axe asset-gap remedy: copied zombie `2H` assets renamed to `Axe` are resolved as `Zombie_..._Axe_...`, preserve factual Pickaxe/raw52 ownership, accept authored markers, and clean correctly.

The broad standalone campaign is not reopened merely because later compatibility work changes a bounded raw55 predicate. Instead, §4.5 owns a small post-compatibility standalone sentinel that proves the final compatibility source remains valid when New Balance / AttackCollision is absent.

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

## 4. New Balance exact distributed-bundle compatibility — OPEN / SPRINT-FIRST SP2 FOLLOW-UP CURRENT

The current gate is runtime compatibility with the **exact New Balance 0.7 distributed bundle as the User actually runs it**, including its DLL set and relevant Jackydima collision components such as `Script_AttackCollision` where applicable.

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

Source-level preflight evidence is not sufficient final certification.

### 4.1 Environment preflight

Before interpreting gameplay:

```text
exact New Balance bundle installed
all normally distributed/used New Balance DLLs present
relevant AttackCollision component present where part of that environment
Zombie/Axe/Rapier separation mods present
EV-375 zombie Axe asset fix present
exactly one Gothic3_Animation_Behaviors collision twin live
startup succeeds
expected diagnostic banner present when using diagnostic twin
```

Record any load-order or DLL-composition difference because compatibility is environment-specific.

### 4.2 Representative runtime coverage

Across the full gate include:

```text
equipped marker combat
  -> representative 1H/dual-1H/2H/Staff behavior and cleanup

raw8 body-contact
  -> marked opportunity open/rearm/contact/finalization
  -> include knocked-down/get-up control because New Balance changes some behavior there

raw55 PhysicalFist
  -> representative Troll/PhysicalFist marked route

separation coexistence
  -> representative separated motions with the full New Balance stack live
  -> at least one Zombie+Axe route using the EV-375 asset fix

mixed stress
  -> actor/target/weapon/C1 churn with the complete intended DLL/mod stack live
```

### 4.3 Acceptance

For the tested environment require:

```text
no startup/load crash or hook conflict
expected factual action/source/UseType ownership
expected marker acceptance/fail-closed behavior
expected physical group activation/cleanup
raw8 opportunities consume/close correctly
raw55 routes remain bounded to their factual contract
separated animation families preserve the expected factual source semantics
C1 final obligations return to zero, or bounded exact C1-R1 repair converges safely
no repair divergence
no invariant/generation contradiction
no unexpected stale ownership/dedupe leakage
clean unload
no user-observed collision regression
```

A compatibility failure does not authorize an immediate broad source patch. First reduce the exact factual collision route.

### 4.4 Raw55 SP2 compatibility corrections — EV-376–EV-378

EV-376 established the first New Balance raw55 StatePosition2 contradiction. EV-377 established healthy equipped-Sprint/raw8 controls. The first bounded source correction was implemented in:

`6eb3e3ca96da55e89127c24d5f656e05610d315f`

Independent Normal Chat static review: **PASS**.

The User then built/deployed the diagnostic twin and verified exact built/live SHA256 equality:

`E11D680590D2F9D87A50EAF64B642F70C8CECA019ABB651DC48B00AF01F37C74`

EV-378 runtime result for the first correction:

```text
single-FIST true Power raw55
  late first/only FIST current POWER / SP2 -> ACCEPTED
  exact RIGHT raw55 5 -> 7
  native cleanup returns 7 -> 5 / outstanding zero

double-FIST true Power raw55
  marker1 current POWER / SP1 -> ACCEPTED + physical opening
  marker2 same C1 current POWER / SP2 -> ACCEPTED
  marker2 ClearTriggeredList/rearm only
  no second physical opening

Sprint-origin double-FIST raw55
  marker1 Action9 / SPRINT / SP1 -> ACCEPTED + physical opening
  same C1 continues to Action2 / POWER
  marker2 SP2 -> ACCEPTED / clear-only rearm

Normal / Quick raw55 controls
  healthy
```

EV-378 additionally established:

```text
Sprint-origin single-FIST raw55
  exact owned execution remains factual Action9 / SPRINT
  premature native opening is suppressed
  first/only FIST may arrive at SP2
  earlyOpeningSuppressed = true
  RIGHT remains group5
  previous Sprint-first SP1-only predicate rejects it
```

The tiny follow-up correction was implemented at:

`ce59e5a2bad564652eaba970e959bdef0b479d82`

Independent Normal Chat diff-against-contract review: **PASS**.

Exact follow-up source change:

```text
PhysicalFistCollision.cpp only
IsFirstFistAllowed(...)
AttackFamily_Sprint branch only

before:
  current SPRINT
  && SP1
  && earlyOpeningSuppressed

after:
  current SPRINT
  && explicit {SP1, SP2}
  && earlyOpeningSuppressed
```

No generic `>=1` policy, authored-count branching, helper/state/module/hook, New Balance detection, or neighboring behavior change is present.

Focused post-follow-up New Balance acceptance:

```text
1. single-FIST Sprint-origin Action9/SP2 first/only marker -> accepted + 5->7 + cleanup
2. double-FIST Sprint-origin SP1 marker1 + current Power/SP2 marker2 -> remains accepted/rearm
3. representative true-Power single/double control -> remains accepted
4. Normal/Quick raw55 controls
5. representative equipped/raw8 controls
6. then resume broader New Balance full-stack coverage
```

Do not require every accepted marker to produce damage; marker acceptance/rearm correctness is primary and Gothic remains authoritative for contact/damage.

### 4.5 Standalone / no-New-Balance post-compatibility sentinel

The mod must remain correct when New Balance / Script_AttackCollision is **not installed or active**. The compatibility patches contain no New Balance detection or dependency and preserve the prior SP1 paths, but they changed raw55 production predicates after the broad standalone campaign closed. Therefore final certification requires a small direct standalone sentinel rather than assuming compatibility from static reasoning alone.

Run this **after** the focused New Balance correction passes and before final collision-source certification / production migration.

Environment:

```text
New Balance / Script_AttackCollision absent or disabled
normal standalone Gothic3_Animation_Behaviors test environment
exactly one current diagnostic collision twin live
same current final compatibility source
```

Minimum raw55 sentinel:

```text
1. Sprint-origin single-FIST
   -> ordinary standalone factual state accepted
   -> exact RIGHT raw55 opens only at authored FIST
   -> native cleanup returns to group5 / zero outstanding

2. Sprint-origin double-FIST
   -> first marker accepted/open
   -> later marker follows established repeated-contact semantics
   -> clean native cleanup

3. true-Power single + double control
   -> existing Power behavior remains healthy

4. Normal + Quick raw55 control
   -> unchanged behavior remains healthy

5. unmarked raw55 native-fallback sentinel
   -> remains completely native
```

Acceptance:

```text
no crash/startup conflict
no new marker anomaly on supported traffic
SP1 behavior remains accepted where standalone produces SP1
SP2 widening does not create stale or cross-family ownership
first FIST opens once; second FIST remains clear-only rearm
native cleanup returns exact raw55 source to group5
final C1 obligations zero
unmarked fallback remains native
no user-observed regression
```

Do **not** rerun the entire EV-299–EV-374 standalone campaign unless this sentinel finds contradictory evidence. The purpose is narrow post-change proof that New Balance compatibility is additive rather than required for correct behavior.

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
-> archive processed runtime artifact when no active comparison remains
-> restore research/raw/ to intake-only state
-> run POP-12 validation
-> only then next batch
```

`research/raw/` is active intake, not history storage. Processed New Balance evidence through EV-378 is archived byte-identically; raw intake should again contain only `Keep.txt`.

---

## 6. Production collision migration — after compatibility gates

After New Balance compatibility **and** the standalone post-compatibility sentinel pass:

```text
mature collision behavior
-> migrate into src/Script_G3AnimationBehaviors
-> diagnostics remain separate
-> release-purity/integration validation
```

Do not migrate before both gates close.

---

## 7. AttackContinuationProtection — separate later responsibility

`AttackContinuationProtection` remains separate from collision cleanup.

```text
AttackContinuationProtection
= prevent/defer the proven destructive bad-skip consequence at its factual native decision point

CollisionLifecycleGuard / C1-R1
= exact-source fail-safe if collision cleanup is nevertheless lost
```

This work remains paused unless deliberately reopened.

---

## 8. Current sequence

```text
standalone broad final-source regression    CLOSED/PASS EV-299–EV-374
Zombie+Axe asset-gap remedy                 PASS EV-375
New Balance controls                        PASS EV-377
first raw55 SP2 correction                  STATIC PASS / RUNTIME PARTIAL PASS EV-378
Sprint-first SP2 correction                 IMPLEMENTED / STATIC REVIEW PASS / RUNTIME PENDING
New Balance full intended-stack gate        OPEN
-> focused Sprint-first acceptance
-> representative/full-stack New Balance compatibility
-> standalone/no-New-Balance post-compat raw55 sentinel
-> production collision migration
-> diagnostics-free integration validation
-> later Raise + Speed + Config

AttackContinuationProtection remains separate unless deliberately reopened
```

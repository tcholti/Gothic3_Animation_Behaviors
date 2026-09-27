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
- **All runtime logs, regardless of size, are analyzed through POP-06 bounded retrieval; whole log bodies are not loaded/reproduced in Chat merely because they fit.**
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

Both twins compile the same `FRAME_COLLISION_BEHAVIOR_SOURCES`; the diagnostic twin adds diagnostic-only compilation/files. A behavior-facing shared-source change therefore changes the behavior twin's **source candidate** immediately, but the behavior DLL binary is not current until that target is rebuilt and hash-verified under POP-02/03.

Final-candidate hashes from reviewed source `1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0`:

```text
Behavior   D5BECB2C32A9766B1B444CB5864C0C30C9AC251A1679F605127F4D7318900B78
Diagnostic AEF0E18205BAA9258D50B2E934173C48B845E0F1B9A9F425D622F4E4598EE773
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

Later compatibility changes did not reopen the entire campaign. §4.5 owns the bounded post-compatibility standalone sentinel for the changed final candidate; that sentinel is now CLOSED/PASS EV-386–EV-387.

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

## 4. New Balance exact distributed-bundle compatibility — CLOSED/PASS EV-384, FINAL-CANDIDATE FOCUSED REGRESSION PENDING REVIEW

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

No production source file changed between the EV-382 correction and EV-383/EV-384 runtime evidence. The later standalone SP1 correction therefore requires only the bounded final-candidate New Balance regression defined below; it does not reopen the full EV-376–EV-384 campaign.

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

The New Balance evidence establishes the compatible SP2 and Action9→Action2 transition routes. It did not establish current-SPRINT/SP1 second-FIST behavior; the post-compatibility standalone sentinel deliberately existed to ensure those compatibility additions remained additive rather than becoming a New Balance dependency. EV-386–EV-387 now close that standalone requirement on the corrected final candidate.

Hard boundaries remain:

```text
NO generic StatePosition range widening
NO family-independent Normal SP0 policy
NO visited-target or hit1 flags
NO marker delays/queues/timers
NO species/name/filename/DLL policy
NO custom damage/contact ownership
```

### 4.5 Standalone / no-New-Balance post-compatibility sentinel — CLOSED/PASS EV-386–EV-387

The mod must remain correct when New Balance / Script_AttackCollision is absent or disabled. New Balance support is additive, not a dependency.

Environment:

```text
New Balance / Script_AttackCollision absent or disabled
normal standalone G3AB test environment
exactly one current diagnostic collision twin live
reviewed final candidate 1c45e5e...
```

Minimum raw55 sentinel:

```text
1. Sprint-origin single-FIST
2. Sprint-origin double-FIST
3. true-Power single + double control
4. Normal + Quick control
5. unmarked raw55 native-fallback sentinel
```

#### EV-385 contradiction and correction

EV-385 found one narrow failure: in the standalone `1+3` fixture marker1 was factual `SPRINT/Action9/SP1`, while marker2 remained in the same C1/source/origin at `SPRINT/Action9/SP1` and was rejected as `REJECTED_UNSUPPORTED_HIT`. Cleanup stayed healthy.

The reviewed final source changed only the Sprint-origin second-FIST current-SPRINT gate:

```text
current POWER  -> explicit SP1 or SP2
current SPRINT -> explicit SP1 or SP2
```

No generic widening or new mechanism was introduced.

#### EV-386 marked final-candidate acceptance

The User repeated four standalone BlackTroll/raw55 fixtures on the corrected final candidate:

```text
double FIST 1+3
double FIST 1+8
double FIST 1+15
single-FIST authored controls
```

Acceptance obtained:

```text
1+3:
  marker1 SPRINT/SP1 accepted/open
  marker2 same-C1 SPRINT/SP1 accepted clear-only
  GroupRequested=0 / ClearTriggeredList=1

1+8 / 1+15:
  marker1 SPRINT/SP1 accepted/open
  marker2 after same-C1 Action9->Action2 = POWER/SP1
  accepted clear-only

single SPRINT/SP1 = PASS
factual true-Power single + double = PASS
reviewed cleanup -> group5 / Outstanding=0
zero REJECTED_* / ANOMALY in the four-artifact batch
clean unload
```

Normal and Quick marked traffic remained healthy and did not require a broader matrix.

#### EV-387 unmarked final-candidate acceptance

One standalone BlackTroll/raw55 run removed authored FIST markers. Repeated Quick, Normal, factual true Power Action2 and Sprint Action9 are observed with:

```text
MarkerPresent=0
FistMarkers=0
SuppressNative=0
```

Bounded searches find:

```text
RAW55_PHYSICAL_FIST_MARKER = 0
RAW55_PHYSICAL_FIST_NATIVE_OPEN_SUPPRESSED = 0
REJECTED_* = 0
ANOMALY = 0
C1 INVARIANT = 0
```

Gothic performs the native exact RIGHT raw55 group5 -> group7 opening; contact/damage may occur; native cleanup returns group7 -> group5 with `Outstanding=0`; the diagnostic twin unloads cleanly.

Therefore:

```text
FINAL-CANDIDATE STANDALONE/NO-NEW-BALANCE DIAGNOSTIC RAW55 SENTINEL
= CLOSED/PASS EV-386–EV-387
```

### 4.5.1 Remaining diagnostic gate — bounded final-candidate New Balance regression

Because the behavior-facing source changed after EV-384, one focused New Balance regression remains required on the same reviewed final candidate.

The User has **already recorded** a New Balance matrix corresponding to the standalone fixtures. Do not ask for a rerun. Once published, review it under POP-06 bounded retrieval.

Minimum required proof from that already-run batch:

```text
New Balance final-candidate startup/load remains healthy
compatibility-sensitive Sprint-origin marked route remains accepted
established SP2 behavior remains supported when present
same-C1 Action9/SPRINT -> Action2/POWER continuation remains supported
second FIST remains clear-only / no second physical opening
native cleanup returns exact RIGHT raw55 to group5
Outstanding=0 at normal finalization
no new supported-traffic rejection / ownership contradiction
clean unload
```

The User's extra 1+3 / 1+8 / 1+15 / single-marker coverage may be used as additional confidence, but the full EV-376–EV-384 campaign must not be repeated absent contradictory evidence.

The diagnostic phase closes only when this bounded final-candidate New Balance regression passes.

### 4.6 Final behavior-only / diagnostics-free collision confirmation — REQUIRED AFTER DIAGNOSTIC PASS

After the final-candidate New Balance regression passes:

```text
deploy Script_FrameCollisionBehaviorTest ONLY
-> verify diagnostic twin physically absent
-> verify built/live behavior SHA256 match
-> startup smoke: no load/startup crash
-> run one observational functional session
```

This is a **release-purity behavior confirmation**, not a diagnostic evidence run. No `Script_FrameCollisionTest.log` is expected or required.

The behavior-only session should intentionally include:

```text
representative raw55 marked combat
representative ordinary equipped marker combat
representative native/unmarked behavior
several authored animations where the desired RIGHT collision window exists only because G3AB marker behavior owns/creates it
ordinary combat/weapon/source churn sufficient to reveal obvious cleanup or persistence failure
```

The last category is the strongest positive-control surface for the diagnostics-free twin: if those marker-dependent RIGHT windows work in-game, the behavior-only binary is demonstrably executing G3AB collision behavior rather than merely surviving startup while native Gothic behavior masks its absence.

Acceptance is observational plus binary identity:

```text
BEHAVIOR DEPLOYMENT PASS
no startup/load crash
marker-dependent RIGHT collision behavior visibly works where native behavior alone would not provide that authored window
representative raw55/equipped/native behavior looks correct
no stuck collision / obvious persistent-hit / cleanup regression
no user-observed collision regression
```

Because this product deliberately omits diagnostics, absence of a diagnostic log is expected and must not be treated as missing evidence. Record the exact final behavior SHA256 and the User's observational result as the release-purity validation evidence.

Do **not** rerun the full EV-299–EV-374 or full EV-384 campaigns unless focused final-candidate validation finds contradictory evidence.

---

## 5. Evidence / artifact boundary

For each diagnostic runtime batch:

```text
freeze setup + filename
-> User runs locally
-> publish unchanged raw artifact
-> Normal Chat interprets through POP-06 bounded retrieval
-> concise canonical EV
-> promote changed reusable fact
-> archive processed runtime artifact when no active comparison remains
-> restore research/raw/ to genuine open inputs only
-> run POP-12 validation
-> only then next batch
```

Behavior-only diagnostics-free validation follows §4.6 instead: exact binary identity + frozen observational matrix + User result; do not manufacture a raw log requirement for a product that intentionally emits no diagnostic evidence.

The EV-382 Normal logs, EV-384 New Balance stress log, EV-385 discovery batch, EV-386 corrected marked standalone batch, and EV-387 unmarked fallback run are processed and archived byte-identically. `research/raw/` should contain only `Keep.txt` after EV-387 closure.

---

## 6. Production collision migration — BLOCKED UNTIL FINAL BEHAVIOR-ONLY PASS

The broader New Balance compatibility gate is closed through EV-384, and the changed final candidate has now passed its complete standalone/no-New-Balance diagnostic sentinel through EV-386–EV-387.

Therefore:

```text
review already-run final-candidate New Balance/raw55 batch
-> bounded compatibility-sensitive regression PASS
-> diagnostic phase CLOSED
-> diagnostics-free behavior-twin observational confirmation
-> only after behavior-only PASS:
   mature collision behavior
   -> migrate into src/Script_G3AnimationBehaviors
   -> diagnostics remain separate
   -> production integration validation
```

The behavior twin is the pre-migration release-purity proof for the collision subsystem; production migration still remains a separate integration step into the shipping product.

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
standalone SP1 contradiction                  FOUND EV-385
corrected marked standalone matrix            PASS EV-386
unmarked native-fallback standalone           PASS EV-387
standalone final-candidate diagnostic gate    CLOSED/PASS EV-386–EV-387
-> review already-run New Balance final-candidate logs CURRENT
-> final diagnostics-free behavior-only observational confirmation
-> production collision migration only after behavior-only PASS
-> production integration validation
-> later Raise + Speed + Config under DESIGN.md §3 / ADR-0004

AttackContinuationProtection remains separate unless deliberately reopened.
```
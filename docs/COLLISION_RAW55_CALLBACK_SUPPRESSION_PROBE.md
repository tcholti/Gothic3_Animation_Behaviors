# Raw55 PhysicalFist Callback-Suppression Probe

**Project:** Gothic3_Animation_Behaviors  
**Status:** FROZEN diagnostic causal probe  
**Updated:** 2026-09-12

## Purpose

Answer one production-design question before any `PhysicalFist/raw55` marker behavior is implemented:

> Can an exact marked factual raw55 attack suppress the native attack callback's physical activation without breaking the attack's normal animation/state/recover/next-attack progression?

This is a **diagnostic-only causal probe**, not production raw55 support.

Project-wide method: `FEATURE_DEVELOPMENT_METHOD.md`.  
Bounded execution: `WORK_IMPLEMENTATION_PROTOCOL.md`.

---

## 1. Evidence Boundary

The active Troll/BlackTroll log establishes:

```text
RIGHT TrollFist / gEUseType_PhysicalFist / raw55 / group5
LEFT  TrollFist / gEUseType_PhysicalFist / raw55 / group5
Raw8Fist=<none>

observed native bookkeeping source:
RIGHT TrollFist 5 -> 7
Game.dll+0x00069484 damage when contact occurs
RIGHT TrollFist 7 -> 5 cleanup
```

Observed marked raw55 families in this fixture:

```text
Normal
Quick (Action4 / Action5)
Sprint (Action9 transported through OnAI_PowerAttack)
```

The RIGHT source is a factual bookkeeping/source identity only. Do not infer damaging limb from RIGHT, and do not infer physical source side from animation-name `L/R`.

Current `G3AB_COL_FIST` supports factual raw8 only, so raw55 FIST markers currently end as `UNSUPPORTED_MISSING_SOURCE`. That remains intentional during this probe.

---

## 2. Why This Probe Is Required

In the baseline Troll run, native raw55 can request group7 before a later authored FIST marker is reached. Therefore production raw55 support cannot be tested by merely activating group7 at FIST; the pre-marker native window must first be preventable safely.

The probe changes exactly one causal variable:

```text
exact marked raw55 callback
native original callback allowed    -> baseline
native original callback suppressed -> probe
```

It does **not** add replacement activation at FIST.

---

## 3. Mandatory Modular Structure

Create temporary diagnostic-only:

```text
PhysicalFistProbe.cpp
PhysicalFistProbe.h
```

Responsibility:

```text
identify the exact frozen raw55 fixture
own the temporary suppression decision
own temporary probe logging
return only a suppress/do-not-suppress decision to EngineBridge
```

`EngineBridge` remains the sole physical hook owner and may receive only the smallest diagnostic-only delegation seam needed to ask the probe for that decision.

Do not put raw55 probe policy/state into:

```text
EngineBridge
Raw8FistCollision
FrameCollisionMarkers
CollisionLifecycleGuard
CollisionSourceOperations
```

Do not create a permanent `PhysicalFistCollision` module in this task.

---

## 4. Build Boundary

`PhysicalFistProbe.cpp/.h` must be compiled **only** into `Script_FrameCollisionTest`.

It must not be part of `FRAME_COLLISION_BEHAVIOR_SOURCES` and must not compile into `Script_FrameCollisionBehaviorTest`.

Any include/call from shared `EngineBridge.cpp` must be guarded by the existing diagnostic compile boundary so behavior-only source semantics remain unchanged after preprocessing.

No new engine hook, callback hook, call hook, RVA, timer, polling loop, or per-frame path is authorized.

---

## 5. Exact Probe Eligibility

The probe may suppress the native attack callback only when all of the following are factual at callback entry:

```text
actor and actor instance are valid
SPU exists and SPU self == actor instance
current C1 generation is valid
attack Hit is eligible for the resolved family
family is one of: Normal, Quick, Sprint
matching current motion is found
marker scan is valid
a marker is present
the motion contains at least one authored G3AB_COL_FIST
no RIGHT / LEFT / BOTH / OFF marker is authored for this probe fixture
requiredSourceMask == SourceMask_None
raw8 fist resolver did not resolve a source
RIGHT slot source exists
RIGHT source UseType == gEUseType_PhysicalFist / raw55
RIGHT source collision group == Item_Equipped / group5 at the suppression decision
```

Do not gate by:

```text
Troll / BlackTroll species or entity name
animation family/name token beyond the ordinary marker scan
QuickAttackL / QuickAttackR suffix
LEFT source meaning a left damaging limb
```

The left raw55 source may be logged as context, but it is not an authorization to invent LEFT/BOTH raw55 behavior.

---

## 6. Exact Intervention

For an eligible execution:

```text
return a probe suppression decision
-> existing EngineBridge callback wrapper returns GETrue
-> native original OnAI_* callback is NOT called for that invocation
```

For every non-eligible execution:

```text
probe returns false
-> existing behavior is unchanged
```

The probe must not:

```text
set TrollFist/raw55 group7
set any source group5
ClearTriggeredList
write SPU+0x164
use Raw8 timing permission
modify StatePosition
accept/process the FIST marker differently
change C1 repair/lifecycle policy
perform damage
change target/contact logic
remember persistent feature state
```

`FrameCollisionMarkers::ProcessMarker` remains unchanged. The later FIST marker is expected to continue reporting current raw55 unsupported/missing-source behavior during this probe.

---

## 7. Bridge Seam

The preferred shape is conceptually:

```text
existing marker ownership evaluation
existing Raw8FistCollision ownership update
existing ownership diagnostics

#ifdef FRAME_COLLISION_DIAGNOSTICS
    probeSuppress = PhysicalFistProbe::ShouldSuppressNativeCallback(...)
#else
    probeSuppress = false
#endif

return existingProductionSuppress || probeSuppress
```

Exact local naming may differ. The semantic boundary may not.

Do not duplicate hook ownership or move existing hook logic into the probe.

---

## 8. Probe Logging

Probe-specific logging should live in `PhysicalFistProbe`, using the existing diagnostic log handle (`CollisionDiagnostics::GetLog()` is available) rather than adding policy to `CollisionDiagnostics` or `EngineBridge`.

For each actual suppression, emit enough compact facts to correlate the execution:

```text
actor
family
action
current motion
C1 generation
RIGHT source identity / UseType / group
LEFT source identity / UseType / group when present
SUPPRESS_NATIVE=1
```

No broad new logging framework is authorized.

---

## 9. Protected Behavior

Must remain unchanged:

```text
all raw8 FIST behavior
all equipped RIGHT / LEFT / BOTH / OFF behavior
all existing marker occurrence/dedupe semantics
C1 lifecycle tracking and C1-R1 repair
Hack / Sprint routing
unmarked raw55 behavior in production/behavior-only build
all non-raw55 attack callbacks
one physical hook owner in EngineBridge
```

The diagnostic probe may alter only exact eligible marked raw55 callback invocations.

---

## 10. Allowed Files

Expected implementation scope:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp      NEW
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.h        NEW
prototypes/Script_FrameCollisionTest/EngineBridge.cpp           minimal diagnostic-only delegation
prototypes/Script_FrameCollisionTest/CMakeLists.txt             diagnostic target only
```

Do not modify other behavior modules unless a compile-mechanical dependency proves unavoidable. A semantic need for additional behavior changes is a contradiction and must be returned to Normal Chat instead of implemented.

---

## 11. Work Validation Boundary

Work performs source/static audit only unless its launcher explicitly authorizes build execution.

Required source audit:

```text
probe files appear only in Script_FrameCollisionTest target
behavior twin does not compile/link PhysicalFistProbe
EngineBridge raw55 code exists only inside diagnostic compile guard
no new hook/RVA
no raw55 group mutation
no marker-processing modification
Raw8FistCollision unchanged
no species/name gate
only Normal/Quick/Sprint eligible
non-eligible path returns existing behavior unchanged
```

Then publish and STOP.

---

## 12. Local Runtime Test After Implementation

User + Normal Chat build/deploy the diagnostic twin locally and run Troll/BlackTroll with the existing marked assets.

Exercise practical samples of:

```text
Normal
QuickR / QuickL as available
Sprint / Action9 as available
```

Compare against the existing baseline `2026.09.12_troll_collision_test.log`.

### Expected positive result

For every probe-suppressed execution:

```text
RAW55 probe suppression record exists
no native TrollFist group5 -> group7 request occurs before FIST
no raw55 damage occurs before FIST
authored FIST is still reached and remains unsupported in this probe
attack animation/state continues
recover/transition remains healthy
later attack generations continue normally
no unrelated marker/lifecycle anomaly appears
```

Player equipped attacks in the same fight may serve as a practical negative control and must remain unchanged.

### Failure / return-to-design conditions

Return to Normal Chat rather than adding compensating code if suppression causes any of:

```text
attack animation/state stalls or cancels incorrectly
FIST frame is no longer reached
recover/normal transition is broken
next attacks stop or become abnormal
another required native side effect is lost
non-raw55 behavior is affected
C1/lifecycle anomalies are introduced
family-specific divergence requires new policy not frozen here
```

---

## 13. Stop Boundary

Even on a perfect runtime PASS, this probe does **not** authorize production raw55 support.

PASS means only:

> marked raw55 can safely take native callback activation ownership early enough to eliminate the pre-marker physical window for the tested Normal/Quick/Sprint scope.

After PASS:

```text
Normal Chat interprets evidence
-> freeze permanent PhysicalFistCollision production contract
-> separate Work task implements minimal proven production behavior
-> temporary PhysicalFistProbe is removed
-> focused production validation
-> broad creature validation resumes only afterward
```

Do not combine probe implementation and production implementation in one task.

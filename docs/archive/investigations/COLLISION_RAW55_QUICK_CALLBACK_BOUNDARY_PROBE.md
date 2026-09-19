# Raw55 PhysicalFist Quick Callback-Boundary Probe

**Project:** Gothic3_Animation_Behaviors  
**Status:** FROZEN diagnostic observation probe  
**Updated:** 2026-09-12

## Purpose

Answer one unresolved causal question from EV-262 before any permanent raw55 implementation is designed:

> During a normal, unsuppressed marked factual raw55 Quick execution, what changes across each invocation of the original native `_AI_QuickAttack` callback: StatePosition, TrollFist collision group, or both?

This is observation-only for Quick. It does not implement raw55 marker behavior and does not attempt to repair the failed suppression experiment.

Project-wide method: `FEATURE_DEVELOPMENT_METHOD.md`.  
Bounded execution: `WORK_IMPLEMENTATION_PROTOCOL.md`.

---

## 1. Evidence Boundary

EV-262 established two separate facts:

```text
native marked raw55 Quick:
    pre-FIST TrollFist 5 -> 7
    rejected raw55 FIST observed at StatePosition 1
    native cleanup 7 -> 5
    clean C1 finalization

suppressed marked raw55 Quick:
    old pre-FIST 5 -> 7 removed
    rejected raw55 FIST observed at StatePosition 0
    later post-FIST 5 -> 7 appears
    apparent cleanup occurs
    C1 can still finalize with raw55 group7/outstanding and repair to 5
```

The rejected raw55 FIST comparison is meaningful because the current raw55 marker path returns unsupported before the marker-owned Quick StatePosition write.

The September 12 Sabretooth Quick control confirms healthy raw8 Quick behavior for both native-NPC and transformed-player ownership. Its compact `CORE MARKER StatePosition=1` must **not** be treated as proof of pre-marker native StatePosition, because accepted Quick FIST processing itself writes the marker-owned StatePosition before that compact line is emitted.

Older equipped Quick evidence independently shows that an unaccepted/unmarked Quick execution can be at StatePosition 0 during Hit and StatePosition 1 by Recover. Therefore a real native Quick StatePosition progression exists, but its exact mutation point in the raw55 path is not yet known.

---

## 2. Single Probe Question

The probe brackets the already-owned original `_AI_QuickAttack` call and records the factual state immediately before and immediately after that native invocation.

For each eligible callback invocation record:

```text
C1 generation
Action before -> after
AniPhase before -> after
StateTime before -> after
StatePosition before -> after
current motion before -> after
RIGHT raw55 source identity / UseType
RIGHT raw55 collision group before -> after
native callback return value
```

The original native callback must execute exactly once.

---

## 3. Quick Intervention Change

The previous callback-suppression probe remains evidence, but Quick is no longer suppressed in this follow-up diagnostic build.

```text
Normal raw55 marked fixture -> previous suppression experiment unchanged
Sprint raw55 marked fixture -> previous suppression experiment unchanged
Quick raw55 marked fixture  -> SUPPRESSION DISABLED; native callback observed
```

This is not a production semantic decision. It is only the minimum change required to observe the native Quick callback boundary.

---

## 4. Exact Observation Eligibility

Observation is active only when callback entry factually satisfies the existing raw55 fixture identity:

```text
actor and actor instance valid
SPU exists and SPU self == actor instance
current C1 generation valid
Quick attack Hit eligible
matching current motion found
marker scan valid
marker present
at least one authored G3AB_COL_FIST
no RIGHT / LEFT / BOTH / OFF marker authored
requiredSourceMask == SourceMask_None
raw8 Fist resolver absent
RIGHT source exists
RIGHT source UseType == gEUseType_PhysicalFist / raw55
```

Unlike the old suppression decision, callback-boundary observation does **not** require RIGHT group5. Once the factual marked raw55 Quick execution is identified, later invocations in the same Hit must remain observable if the source has already become group7. This is required to distinguish the first mutation from later callback activity.

Do not gate by Troll/BlackTroll names, QuickAttackL/QuickAttackR filename suffixes, or species policy.

---

## 5. Modular Ownership

`EngineBridge` remains the sole `_AI_QuickAttack` hook owner.

Its diagnostic-only responsibility is limited to:

```text
EvaluateAttackCallback(...)
-> if existing production suppression applies, preserve it
-> ask PhysicalFistProbe for an observation token
-> call the same original native Quick callback exactly once
-> pass native result + post-call context back to PhysicalFistProbe
```

`PhysicalFistProbe` owns:

```text
raw55 Quick observation eligibility
before snapshot
post-call snapshot
compact RAW55_QUICK_CALLBACK_BOUNDARY log line
```

No new hook, RVA, timer, polling path, per-frame scan, or permanent module is authorized.

---

## 6. Forbidden Changes

The probe must not:

```text
set raw55 group7 or group5
ClearTriggeredList
write StatePosition
write SPU+0x164
use raw8 timing permission
accept/process raw55 FIST differently
change C1 lifecycle or repair policy
perform damage
change target/contact behavior
change Raw8FistCollision
change equipped RIGHT/LEFT/BOTH/OFF behavior
add species/name policy
```

For Quick, the probe observes native behavior only.

---

## 7. Diagnostic Build Boundary

All PhysicalFistProbe code remains diagnostic-only in `Script_FrameCollisionTest`.

`Script_FrameCollisionBehaviorTest` must remain free of `PhysicalFistProbe` after preprocessing/link source selection. The behavior-only Quick wrapper must still call the same original callback directly when existing production ownership does not suppress it.

---

## 8. Required Static Audit

Before publication verify:

```text
Quick probe suppression returns false
Normal/Sprint old suppression path remains unchanged in meaning
Quick original callback is called exactly once
before/after observation lives only under FRAME_COLLISION_DIAGNOSTICS
PhysicalFistProbe remains absent from behavior target sources
no new hook/RVA
no collision-group mutation added
no StatePosition write added
Raw8FistCollision unchanged
FrameCollisionMarkers unchanged
CollisionLifecycleGuard unchanged
```

Build execution is not authorized by this contract.

---

## 9. Local Runtime Test

Build/deploy `Script_FrameCollisionTest` locally and exercise several marked Troll/BlackTroll Quick attacks. No Normal/Sprint sampling is required for the causal answer unless a sanity control is convenient.

Target log tag:

```text
CORE RAW55_QUICK_CALLBACK_BOUNDARY
```

Correlate records by actor + C1 generation + action + motion and compare them with ordinary `CORE COLLISION_GROUP`, FIST marker, and C1 finalization records.

### Interpretation

If an invocation shows:

```text
StatePosition 0 -> 1
RightGroup    5 -> 7
```

then the original Quick callback itself performs both observed transitions in that invocation; whole-callback suppression removed a compound native responsibility.

If:

```text
StatePosition unchanged
RightGroup    5 -> 7
```

then collision activation is owned by that callback invocation but the native StatePosition progression occurs elsewhere.

If:

```text
StatePosition 0 -> 1
RightGroup unchanged
```

then the callback owns the StatePosition progression while raw55 collision activation occurs through another path.

If neither changes directly across any observed original callback invocation, the relevant effects are downstream/indirect and the next design step must investigate that downstream path rather than treating `_AI_QuickAttack` itself as the mutation site.

Do not infer production architecture until the actual runtime result is analyzed.

---

## 10. Stop Boundary

After one adequate runtime capture:

```text
Normal Chat analyzes exact callback-boundary records
-> update canonical evidence
-> decide whether the native Quick responsibilities are separable with an evidence-backed mechanism
```

Do not implement permanent `PhysicalFistCollision`, a compensating Quick patch, or another intervention in the same step.

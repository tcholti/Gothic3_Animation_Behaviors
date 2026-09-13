# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-13

## Current Bridge — RAW55 TRUE POWER CLOSED THROUGH EV-276; NORMAL CALLBACK OWNERSHIP FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical runtime evidence is through **EV-276**.

No permanent raw55 implementation is authorized yet.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_RAW55_NORMAL_CALLBACK_BOUNDARY_PROBE.md
4. EVIDENCE_LEDGER_274_ONWARD.md EV-274–EV-276
5. EVIDENCE_LEDGER_250_ONWARD.md EV-262 only if the old Normal/Sprint suppression evidence boundary is needed
6. COLLISION_RAW55_POWER_CALLBACK_BOUNDARY_PROBE.md only as prior observation-pattern reference
7. only exact PhysicalFistProbe / EngineBridge source required for the frozen Normal observation task
```

---

## Closed Result — EV-276

Runtime artifact:

```text
research/raw/2026.09.13_troll_raw55_power_fist_activation.log
upload commit 83d2150defd967e379d3ae602f6a2936e941d1bd
implementation 0131f7a04d548f186ed9c8581e59e84a7b24b1f7
```

Two factual true-Power executions, C1=6 and C1=11, independently show the complete tested mechanism.

Early native boundary in both:

```text
Action=2 / Family=POWER
exact RIGHT TrollFist / PhysicalFist raw55
premature native request 5 -> 7 suppressed at StatePosition=0
original _AI_PowerAttack still executes exactly once
StatePosition 0 -> 1
RightGroup 5 -> 5
SameC1=1
SameRight=1
NativeResult=1
```

At authored FIST in both:

```text
stable marker result remains UNSUPPORTED_MISSING_SOURCE
StatePosition=1
same actor/source/C1 suppression proof
RIGHT group5 -> group7 through ordinary setter
real C1 offense obligation observed
CORE RAW55_POWER_FIST_ACTIVATION_PROBE
EarlySuppressionProof=1
ClearTriggeredList=0
ACTIVATE_FIST=1
```

Then in both:

```text
native OnDamage against PC_Hero occurs
User visually observes damage
native cleanup returns exact RIGHT 7 -> 5
C1 cleanup fulfilled
C1 finalizes Outstanding=0 / Cleanup=1 / PhysicalChanged=0 / NO_OP_NO_OUTSTANDING
```

Conclusion:

```text
true Power tested mechanism CLOSED/PASS through EV-276
marker-time physical activation is sufficient for tested first Power FIST contact
NO probe-issued Power ClearTriggeredList is required
native damage and cleanup ownership remain intact
```

Do not generalize the Power no-rearm result to Quick, Normal, or Sprint.

---

## Release / Behavior-Only Boundary

The development target split remains intact:

```text
Script_FrameCollisionTest
= diagnostic research target
= behavior sources + CollisionDiagnostics + PhysicalFistProbe

Script_FrameCollisionBehaviorTest
= diagnostics-free behavior twin
= behavior sources only

Script_G3AnimationBehaviors
= eventual shipped plugin target
= proven collision responsibilities must be deliberately promoted here after research closure
```

If a local `--clean-first` build is followed by building only `Script_FrameCollisionTest`, an older `Script_FrameCollisionBehaviorTest.dll` may disappear from the Release output until that target is explicitly rebuilt. That is a build-output consequence, not removal of the behavior target from CMake.

Do not ship `Script_FrameCollisionTest` or promote `PhysicalFistProbe` as production code.

---

## Why Normal Is Next

EV-262 established that temporary whole-callback suppression for marked raw55 Normal:

```text
removes the old early/pre-marker 5 -> 7
removes observed Normal damage in the tested fixture
still lets the authored FIST later be reached as UNSUPPORTED_MISSING_SOURCE
remains lifecycle-clean in sampled Normal executions
```

But EV-262 did **not** bracket the native `_AI_Attack` callback and prove what else whole-callback suppression removes.

Quick later proved its native callback jointly owns `StatePosition 0 -> 1` and early raw55 `5 -> 7` (EV-264). True Power independently proved the same compound pattern (EV-274). Therefore the old temporary Normal whole-callback suppression must not be promoted merely because animations looked healthy.

---

## Current Frozen Work Responsibility

Authority:

```text
docs/COLLISION_RAW55_NORMAL_CALLBACK_BOUNDARY_PROBE.md
```

Single question:

> During an exact marked raw55 `Family=NORMAL` Hit, what changes across the original native `_AI_Attack` invocation that owns the old early RIGHT PhysicalFist/raw55 opening: StatePosition, collision group, or both?

For this diagnostic observation:

```text
remove Normal from the temporary whole-callback suppression family set
keep Sprint temporary whole-callback suppression unchanged
keep Quick precise research behavior unchanged
keep Power precise EV-275/EV-276 behavior unchanged
for eligible marked raw55 Normal only:
    snapshot before original _AI_Attack
    call original exactly once
    snapshot after
    emit CORE RAW55_NORMAL_CALLBACK_BOUNDARY
```

No Normal selective group suppression, authored-FIST activation, or ClearTriggeredList is part of this task.

---

## Expected Decisive Shape

If Normal matches the Quick/Power compound pattern:

```text
CORE RAW55_NORMAL_CALLBACK_BOUNDARY
SameC1=1
SameRight=1
StatePosition=0->1
RightGroup=5->7
NativeResult=1
```

then whole `_AI_Attack` suppression is rejected as a Normal production mechanism and the next smallest Normal question is selective exact `5 -> 7` suppression while preserving native progression.

If the boundary differs, follow the factual result rather than importing the Quick/Power mechanism by analogy.

---

## Protected Boundary

Preserve unchanged:

```text
Sprint/Action9 temporary whole-callback suppression
closed Quick behavior/research state
closed true-Power selective suppression + FIST activation research state
raw8 FIST
FrameCollisionMarkers semantics
CollisionSources semantics
CollisionSourceOperations semantics
CollisionLifecycleGuard / C1-R1
AttackMotionRouting
native target/contact/damage/cleanup outside the intentional restoration of native Normal
CMake target/source separation
```

Do not add:

```text
Normal selective group suppression yet
Normal authored-FIST activation/rearm
ClearTriggeredList for Normal
StatePosition/SPU writes
custom damage
manual cleanup compensation
new hook/RVA/timer/polling
species/name/filename policy
permanent PhysicalFistCollision
release-module promotion
```

Build execution is **not authorized for Work**.

---

## After Runtime

Normal Chat must classify factual Normal from logs; the User does not need to identify the animation visually.

Preferred artifact:

```text
research/raw/2026.09.13_troll_raw55_normal_callback_boundary.log
```

After one adequate factual Normal capture:

```text
commit raw unchanged
Normal Chat analyzes exact callback boundary
promote next canonical EV
freeze only the next smallest Normal causal question
```

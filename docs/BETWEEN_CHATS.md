# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-05

## Current bridge — N1 documented; N2 timing/path investigation next

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat / Work must read `docs/SESSION_ENTRYPOINT.md` first, then this file for the exact current continuation.

---

## Closed / protected boundary

```text
collision architecture verification             COMPLETE — EV-206–EV-215
Power marker adapter validation                 CLOSED/PASS
Pierce marker adapter validation                CLOSED/PASS
SimpleWhirl current marker/semantic stage       CLOSED/PASS
Hack isolated routing/source/marker validation  PASS
Fist Stage A dedicated baseline                 CLOSED/PASS — EV-221
Fist Stage B marker-time DamageDisabled probe   CLOSED/FAIL AS CURRENT OFF INTERVENTION
Fist Stage A restoration after Stage B          CLOSED/PASS
Fist N1 native trigger-state observation        CLOSED/PASS AS OBSERVATION
```

Do not reopen those areas without concrete contradictory evidence.

Fist remains a logical human body-contact source adapter inside the closed collision architecture. It is not another RIGHT/LEFT weapon source bit.

---

## N1 implementation / runtime evidence

Diagnostic implementation:

```text
c1e390782309af5e9e54703389775a163b85612c
```

Validated deployed N1 diagnostic:

```text
Script_FrameCollisionTest.dll
SHA256 D543EEAF90B98287F0C306446C0752FF5676BC3684568381A5F5F42E28F30C8E
```

Canonical full raw evidence:

```text
research/raw/2026-09-05_fist_n1_native_trigger_state_probe.log
commit 1a475cd292abf526f2032262ac4300f18920e178
SHA256 113857F71C3A14A548582B4B254E0CF6C1CBCB79C285B158302E5B5AB34F1972
length 303301
```

The run contains four intended native unmarked human Normal/Fist executions:

```text
2 x P0
2 x P1
```

There is also one short aborted `_AI_PowerAttack` generation. Keep it separate from the four intended Normal cases.

For the exact resolved logical human Fist source (`gEUseType_Fist`, raw 8), the observed state remained:

```text
FistCollisionGroup: 0
IsEnabled:          1
ReactToTouch:       1
ResetOnUntouch:     0
DamageDisabled:     0
```

No observed native transition occurred to group 7, `IsEnabled=0`, `ReactToTouch=0`, `ResetOnUntouch=1`, or `DamageDisabled=1` across the captured:

```text
NATIVE_ATTACK_BEFORE_ORIGINAL
NATIVE_ATTACK_AFTER_ORIGINAL
AISETSTATE_BEFORE_ORIGINAL
AISETSTATE_AFTER_ORIGINAL
```

Each intended native Normal/Fist execution still contained the familiar native collision-group request:

```text
RequestedGroup: 7
BeforeGroup:    0
AfterGroup:     0
```

N1 conclusion, narrow scope only:

> In the tested four native Normal/Fist cases and at the observed existing boundaries, stock human-Fist execution does not expose its attack ON/OFF lifecycle by changing collision group, IsEnabled, ReactToTouch, ResetOnUntouch, or DamageDisabled. The native callback does issue the group-7 request, but the Fist source remains group 0.

Do not infer that no unobserved transient state or other native control exists.

---

## Stage B interpretation — qualified by later static binary evidence

Stage B runtime facts remain valid:

```text
first accepted FIST: DamageDisabled 0 -> 1
later accepted FIST: DamageDisabled 1 -> 1
visual valid-target contact damage: YES
same exact human gEUseType_Fist / raw 8 source
same Fist collision group 0 -> 0
```

Therefore the tested marker-time intervention remains a failure as the current production OFF mechanism:

> Setting `DamageDisabled=true` at the authored `G3AB_COL_FIST` marker did not prevent the observed Fist damage in Stage B.

Later static analysis of the tested binary established an important qualification:

```text
gCTouchDamage_PS::CanBeActivatedNow checks DamageDisabled as a genuine activation gate.
The inherited eCTrigger_PS touch/intersect activation path reaches the virtual eligibility check, which resolves to the gCTouchDamage_PS override for this property set.
```

Therefore do NOT describe Stage B as proving that DamageDisabled is not a real gate or is globally ineffective.

The unresolved issue is timing/path only. Two possibilities remain unproven:

```text
A — the relevant damaging activation/dispatch already passed the gate before the authored FIST marker
B — a later/native damage dispatch still occurs after the marker and needs tracing
```

Do not choose between A and B yet.

---

## Documentation maintenance — CLOSED

N1 is recorded as CLOSED/PASS AS OBSERVATION in the current-state and evidence authorities. EV-222 records the four-case runtime observation; EV-223 records the tested-binary qualification that `DamageDisabled` is a genuine activation gate even though the Stage-B marker-time intervention failed as the current OFF mechanism. Fist/body-contact routing and the recurring Chat-safe output / repository-backed Work-launcher procedures are updated.

---

## Exact next responsibility — N2 timing/path investigation only

> **N2 — determine when the exact human Fist TouchDamage reaches its damage-dispatch / TriggerTarget path relative to the authored `G3AB_COL_FIST` marker and the previously tested `DamageDisabled` setter timing.**

N2 must distinguish whether the relevant activation/dispatch already passed the genuine native `DamageDisabled` gate before the authored marker or whether a later/native damage dispatch still occurs after it. Do not choose between those explanations from naming or from N1, and do not select or implement a production `FIST_OFF` mechanism before the timing/path evidence exists.

---

## Frozen continuation

```text
A  — dedicated FIST baseline                     CLOSED/PASS
B  — marker-time DamageDisabled investigation    CLOSED/FAIL AS CURRENT OFF INTERVENTION
R  — exact restoration to Stage A behavior       CLOSED/PASS
N1 — native trigger-state observation            CLOSED/PASS AS OBSERVATION
D  — close N1 / correct docs / procedure rules   CLOSED
N2 — TriggerTarget/damage-dispatch timing        CURRENT/NEXT
C  — production FIST/FIST_OFF lifecycle          BLOCKED until control mechanism is proven
```

---

## Explicit non-goals for N2

Do not implement or design:

```text
G3AB_COL_FIST_OFF
SetIsEnabled(...)
SetReactToTouch(...)
choosing or implementing another Fist disable mechanism before N2 evidence
production mutation of IsEnabled / ReactToTouch / DamageDisabled
new hooks unless a separately frozen bounded N2 diagnostic proves one necessary
persistent Fist marker-owned lifecycle state
baseline snapshot/restore
terminal/interruption restoration
PhysicalFist / monsters / generalized body collision
per-limb Fist markers
weapon source-mask changes
attack-family or StatePosition redesign
C1 or weapon-lifecycle redesign
RIGHT/LEFT/BOTH/OFF redesign
final mixed regressions
Raise / playback-speed work
```

---

## Local-state caution carried forward

Earlier local status showed this unrelated untracked file:

```text
research/raw/2026-09-04_hack_2h_dedicated_p0_override_validation.log
```

Do not delete, rename, stage, overwrite, or clean it merely to obtain a clean working tree.

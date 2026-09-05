# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-05

## Current bridge — N1 closed; N2A Fist gate/dispatch timing probe next

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
Fist N1 native trigger-state observation        CLOSED/PASS AS OBSERVATION — EV-222–EV-223
```

Do not reopen those areas without concrete contradictory evidence.

Fist remains a logical human body-contact source adapter inside the closed collision architecture. It is not another RIGHT/LEFT weapon source bit.

---

## N1 result carried into N2

Canonical N1 evidence:

```text
research/raw/2026-09-05_fist_n1_native_trigger_state_probe.log
commit 1a475cd292abf526f2032262ac4300f18920e178
SHA256 113857F71C3A14A548582B4B254E0CF6C1CBCB79C285B158302E5B5AB34F1972
```

Across four intended native unmarked Normal/Fist executions (2 x P0, 2 x P1), the exact resolved `gEUseType_Fist` / raw 8 source remained:

```text
FistCollisionGroup: 0
IsEnabled:          1
ReactToTouch:       1
ResetOnUntouch:     0
DamageDisabled:     0
```

No transition was observed across the N1 native OnAI_Attack or AISetState before/after boundaries. Each intended native execution still issued `RequestedGroup: 7` while the exact Fist source remained `0 -> 0`.

N1 therefore did not identify a persistent property/group ON/OFF transition. It does not rule out a transient or another native control.

---

## Stage B interpretation carried into N2

Stage B runtime facts remain:

```text
DamageDisabled 0 -> 1 at first accepted authored FIST marker
later accepted FIST: DamageDisabled 1 -> 1
valid-target Fist damage still observed
```

The tested marker-time setter intervention therefore failed as the current production OFF mechanism.

Later tested-binary analysis established:

```text
gCTouchDamage_PS::CanBeActivatedNow checks DamageDisabled as a genuine activation gate.
inherited eCTrigger_PS touch/intersect activation reaches that virtual eligibility check.
```

Do not describe `DamageDisabled` as fake or globally ineffective.

The unresolved causal question is timing/path:

```text
A — relevant eligibility/activation already passed the DamageDisabled gate before the authored FIST marker
B — a later/native dispatch path remains after the marker and needs tracing
```

EV-223 owns that qualification.

---

## Factual source/binary anchors for N2A

Tested SDK declaration:

```text
gCTouchDamage_PS : eCTrigger_PS
protected virtual GEBool CanBeActivatedNow(eCEntity *, eCContactIterator &)
protected virtual void TriggerTarget(eCEntity *, eCEntity *, eCContactIterator &)
```

Tested `Game.dll` exports independently identify the exact entries:

```text
Game + 0x692F0  gCTouchDamage_PS::CanBeActivatedNow
Game + 0x693B0  gCTouchDamage_PS::TriggerTarget
```

Static disassembly confirms `CanBeActivatedNow` begins by testing `gCTouchDamage_PS + 0xE9`, the SDK `DamageDisabled` property, and returns false through that gate when disabled.

Current `EngineBridge.cpp` already uses the recursion-safe explicit-this `.ThisCall()` hook transport for engine member functions. N2A must use that proven transport rather than legacy shared `GetSelf` transport.

The existing exact Fist source authority remains:

```text
CollisionSources::ResolveFistCollisionSource(actor)
-> current right-slot candidate
-> accept only factual gEUseType_Fist / raw 8
```

Do not create a second Fist source classifier.

---

## Exact next responsibility — N2A READ-ONLY FIST GATE/DISPATCH TIMING PROBE

Implement one bounded diagnostic-only, read-only timing probe.

### Objective

Observe the exact logical human-Fist TouchDamage path at:

```text
FIST_CAN_BE_ACTIVATED_BEFORE_ORIGINAL
FIST_CAN_BE_ACTIVATED_AFTER_ORIGINAL
FIST_TRIGGER_TARGET_BEFORE_ORIGINAL
FIST_TRIGGER_TARGET_AFTER_ORIGINAL
```

and correlate those records by ordinary log order / elapsed time with the already-existing `G3AB_COL_FIST` marker records.

N2A asks only:

> For the known marked human-Fist attack, does the genuine `CanBeActivatedNow` eligibility check occur before or after the authored FIST marker, and when does the exact `TriggerTarget` dispatch occur relative to both?

### Hook scope

Add exactly two diagnostic-only hooks:

```text
Game + 0x692F0  gCTouchDamage_PS::CanBeActivatedNow
Game + 0x693B0  gCTouchDamage_PS::TriggerTarget
```

Both hooks must:

- exist only in the diagnostic product (`FRAME_COLLISION_DIAGNOSTICS`);
- use explicit per-invocation `gCTouchDamage_PS *this` with `.ThisCall()`;
- call the original exactly once with unchanged arguments and ordering;
- return the exact original result where applicable;
- perform no property, collision, marker, lifecycle or target mutation.

The behavior-only product must contain neither N2A hook.

### Exact Fist filtering

Log only when the hooked `gCTouchDamage_PS *this` is the exact TouchDamage property set belonging to the player's source returned by the existing `CollisionSources::ResolveFistCollisionSource(player)`.

Use that resolver and exact property-set identity. Do not generalize by class alone, entity name, slot assumption beyond the resolver, filename, monster/body semantics, or `PhysicalFist`.

For all non-matching TouchDamage instances, forward original behavior exactly once without N2A logging.

### Required factual records

Each matching N2A record must include at minimum:

```text
Boundary
ElapsedMs
Actor/player identity
Action
AniPhase
StateTime
CurrentMovementAni
FistSourceAddress
FistUseType
FistCollisionGroup
DamageDisabled
```

For `CanBeActivatedNow` additionally report:

```text
argument entity address/identity without guessing its semantic role
contact iterator address
native result on AFTER_ORIGINAL
```

For `TriggerTarget` additionally report:

```text
first entity argument address/identity
second entity argument address/identity
contact iterator address
```

Do not invent Target/Inflictor labels unless the tested SDK/static evidence already establishes those parameter roles. Neutral names such as `EntityArg1` / `EntityArg2` are acceptable and preferred when role is not proven.

The existing marker logger already emits `ElapsedMs`, Action, phase, StateTime and current motion when `G3AB_COL_FIST` is received. Do not change marker behavior merely to improve correlation.

### N2A is read-only

Do NOT reintroduce the Stage-B setter in N2A.

Do NOT call:

```text
SetDamageDisabled(...)
SetIsEnabled(...)
SetReactToTouch(...)
SetCollisionGroup(...)
ClearTriggeredList() beyond the already-existing Stage-A marker behavior
```

No diagnostic event counter, persistent Fist execution state, cache, lifecycle state or new ownership model is required. Ordinary chronological log order plus `RuntimeClock` elapsed time is sufficient.

### Marked FIST behavior remains exact Stage A

`G3AB_COL_FIST` must remain:

```text
resolve/validate human gEUseType_Fist / raw 8
-> TouchDamage.ClearTriggeredList()
-> no DamageDisabled behavior
-> no collision-group mutation
-> no weapon source-mask semantics
```

Do not alter callback ownership/suppression, marker occurrence/dedupe, C1 generation, family, StatePosition, source resolution or lifecycle.

### Expected source scope

Expected changed prototype files:

```text
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
```

Do not modify CMake/build product separation unless a concrete compile dependency makes a minimal change unavoidable; report such a contradiction before broadening.

### N2A interpretation boundary

N2A may establish ordering only.

If the genuine `CanBeActivatedNow` call has already occurred before the FIST marker and the relevant `TriggerTarget` follows, that supports the marker-time setter being too late for that activation.

If the gate/dispatch ordering does not establish that explanation, do not improvise another setter or mechanism. Return the runtime result to Normal Chat for the next one-variable decision.

---

## N2A explicit non-goals

Do not implement or design:

```text
G3AB_COL_FIST_OFF
any production Fist disable mechanism
any DamageDisabled setter experiment
SetIsEnabled / SetReactToTouch
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

## Frozen continuation

```text
A   — dedicated FIST baseline                    CLOSED/PASS
B   — marker-time DamageDisabled intervention    CLOSED/FAIL AS CURRENT OFF INTERVENTION
R   — exact restoration to Stage A behavior      CLOSED/PASS
N1  — native trigger-state observation           CLOSED/PASS AS OBSERVATION
D   — close N1 / correct docs / procedures       CLOSED
N2A — read-only gate/TriggerTarget timing probe  CURRENT
N2B — only if N2A cannot resolve timing/path     BLOCKED
C   — production FIST/FIST_OFF lifecycle         BLOCKED until control mechanism is proven
```

---

## Local-state caution carried forward

Earlier local status showed this unrelated untracked file:

```text
research/raw/2026-09-04_hack_2h_dedicated_p0_override_validation.log
```

Do not delete, rename, stage, overwrite, or clean it merely to obtain a clean working tree.

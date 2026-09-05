# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-05

## Current bridge — N2A damaging run produced zero gate/dispatch records; N2B observability probe next

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

## N2A implementation / deployment / runtime evidence

N2A implementation:

```text
888f22fb02b0d6e524847dc28f4bbe3a5d9077a6
Add N2A Fist gate dispatch timing probe
```

N2A added diagnostic-only explicit-this `.ThisCall()` hooks at:

```text
Game + 0x692F0  gCTouchDamage_PS::CanBeActivatedNow
Game + 0x693B0  gCTouchDamage_PS::TriggerTarget
```

Independent Normal Chat source audit: PASS.

Local diagnostic build: PASS.

Validated deployed diagnostic:

```text
Script_FrameCollisionTest.dll
SHA256 20101D10F3A074746B3E7A321F754CDA7A32FE0B3EC049E472185C1D4FCC6A93
length 432640
```

Built/live SHA256 matched exactly. CORE startup PASS:

```text
Script_FrameCollisionTest diagnostic build loaded.
DiagnosticProfile: CORE
MarkerOpcodes: RIGHT LEFT BOTH OFF FIST
Hooks installed.
```

Canonical N2A raw evidence:

```text
research/raw/2026-09-05_fist_n2a_gate_dispatch_timing_probe.log
raw evidence commit 7060fc2f94be6d218e3c343225df076bced28cd2
```

Controlled case:

```text
player PC_Hero
known marked human Fist P0 Normal attack
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
G3AB_COL_FIST at authored frame 3
valid target
User visual damage observation: YES
```

The marked execution was valid and accepted:

```text
Family: NORMAL
Action: 1
RequiresFistSource: 1
FistSourceAddress: E6AB0210
FistSourceUseType: 8
FistSourceCollisionGroup: 0
SuppressNativeCallback: 1

FIST RECEIVED
ElapsedMs: 43063.346
StateTime: 0.127968
MarkerAction: ACCEPTED
TriggeredListClearCount: 1
FistTriggeredListCleared: 1
FistGroupBefore: 0
FistGroupAfter: 0
```

The User confirmed that this exact attack damaged the target.

However, the complete committed raw log contains zero records for all four intended N2A boundaries:

```text
FIST_CAN_BE_ACTIVATED_BEFORE_ORIGINAL
FIST_CAN_BE_ACTIVATED_AFTER_ORIGINAL
FIST_TRIGGER_TARGET_BEFORE_ORIGINAL
FIST_TRIGGER_TARGET_AFTER_ORIGINAL
```

There is likewise no `FIST GATE/DISPATCH TIMING` record anywhere in the run.

### N2A conclusion — narrow scope

N2A did **not** establish gate/marker/dispatch ordering.

A damaging marked human-Fist execution occurred while the current exact-filtered hooks emitted no matching records. This falsifies the assumption that the relevant path would necessarily be observable through those two hooks **as currently hooked and filtered**.

Do not infer yet that:

- `CanBeActivatedNow` is not called;
- `TriggerTarget` is not called;
- the tested RVAs are wrong;
- the hooks failed to install;
- the exact-Fist filter is wrong;
- the damaging path bypasses these methods.

N2A cannot distinguish those possibilities because it logged only after the exact-Fist filter accepted the hooked `this`.

No production behavior conclusion follows from this negative diagnostic result.

---

## Exact next responsibility — N2B READ-ONLY HOOK OBSERVABILITY / FILTER DISCRIMINATION

Implement one bounded diagnostic-only follow-up to distinguish exactly:

```text
1. hook entry never occurs during the damaging player Fist execution
vs
2. hook entry occurs but the existing exact-player-Fist filter rejects it
```

Do not investigate another gameplay control in N2B.

### Preserve the N2A hooks and transport

Keep the same two diagnostic-only hooks:

```text
Game + 0x692F0  gCTouchDamage_PS::CanBeActivatedNow
Game + 0x693B0  gCTouchDamage_PS::TriggerTarget
```

Preserve:

- explicit per-invocation `gCTouchDamage_PS *this`;
- recursion-safe `.ThisCall()` transport;
- original exactly once with unchanged arguments and ordering;
- exact native return value for `CanBeActivatedNow`;
- no behavior/property/collision/marker/lifecycle/target mutation;
- no N2B code in the behavior-only product.

### Add bounded pre-filter entry diagnostics

Before `ResolveExactPlayerFistSource(...)` decides whether the existing detailed N2A record is emitted, record a bounded diagnostic entry for the hook invocation.

The pre-filter trace must be small and deterministic. Use diagnostic-only counters/caps only as needed to prevent unbounded logging. Do not create gameplay/lifecycle state.

For each of the two hook types, the bounded entry record must make it possible to determine at minimum:

```text
HookKind: CAN_BE_ACTIVATED or TRIGGER_TARGET
ElapsedMs
HookEntryOrdinal
ThisTouchDamageAddress
ThisOwnerEntityAddress, using factual property-set ownership if available
ThisOwnerEntityName, if safely available
ThisOwnerUseType, if safely available
PlayerEntityAddress
ExistingResolverSourceAddress (or null)
ExactTouchDamageIdentityMatch: 0/1
PlayerAction
PlayerAniPhase
PlayerStateTime
PlayerCurrentMovementAni
DamageDisabled from hooked this, if safe
```

For the existing resolver outcome, preserve the current authority:

```text
CollisionSources::ResolveFistCollisionSource(player)
```

Do not create a second production Fist classifier.

The purpose of factual `this` owner/use-type logging is diagnostic discrimination only. It must not replace the existing resolver as behavior/source authority.

If direct owner access from `gCTouchDamage_PS` is not available or not safe in the tested SDK, record that field as unavailable rather than inventing a cast/path.

Keep the existing detailed N2A exact-match BEFORE/AFTER records unchanged when the exact filter succeeds.

### Boundedness

The trace must not dump every TouchDamage call indefinitely.

Prefer a small per-hook cap sufficient for one controlled attack. The log must explicitly report the ordinal so a cap is visible. If a suppression/cap indication is necessary, emit it once only.

Do not use filename text as the sole gate for whether the hook-entry trace exists. Runtime action/phase/player context remains factual context, while motion name is only a selector/correlation field.

### N2B interpretation

One controlled damaging marked player-Fist run should answer:

```text
A. zero pre-filter entries for a hook
   -> that exact hook entry was not observed during the run;
      current exact-filter logic is not the reason for its silence.

B. pre-filter entries exist but ExactTouchDamageIdentityMatch = 0
   -> hook is entered, but current exact-Fist matching/filter assumption rejects the observed this;
      inspect factual owner/source identity next.

C. exact-match pre-filter entry exists but detailed N2A record still does not
   -> diagnostic implementation defect; fix only that defect before further causal work.

D. exact-match detailed records appear
   -> N2B restores observability; return their timing/order to Normal Chat.
```

Do not choose a production FIST_OFF mechanism from N2B.

---

## N2B explicit non-goals

Do not implement or design:

```text
G3AB_COL_FIST_OFF
any production Fist disable mechanism
any DamageDisabled setter experiment
SetIsEnabled / SetReactToTouch
SetCollisionGroup changes
extra ClearTriggeredList behavior
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
N2A — exact-filtered gate/TriggerTarget timing   CLOSED/INCONCLUSIVE: damaging run, zero matching records
N2B — hook observability/filter discrimination   CURRENT/NEXT
C   — production FIST/FIST_OFF lifecycle         BLOCKED until control mechanism is proven
```

---

## Local-state caution carried forward

Earlier local status showed this unrelated untracked file:

```text
research/raw/2026-09-04_hack_2h_dedicated_p0_override_validation.log
```

Do not delete, rename, stage, overwrite, or clean it merely to obtain a clean working tree.

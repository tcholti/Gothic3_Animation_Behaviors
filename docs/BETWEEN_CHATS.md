# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-05

## Current bridge — restored Stage A FIST live; observe native trigger gates next

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and use this file only for the exact continuation details below.

---

## Closed / protected boundary

```text
collision architecture verification             COMPLETE — EV-206–EV-215
Power marker adapter validation                 CLOSED/PASS
Pierce marker adapter validation                CLOSED/PASS
SimpleWhirl current marker/semantic stage       CLOSED/PASS
Hack isolated routing/source/marker validation  PASS
Fist Stage A dedicated baseline                 CLOSED/PASS — EV-221
Fist Stage B DamageDisabled causal probe         CLOSED/FAIL AS OFF MECHANISM
Fist Stage A restoration after Stage B           CLOSED/PASS
```

Do not reopen those areas without concrete contradictory evidence.

Fist remains a logical human body-contact source adapter inside the closed collision architecture. It is not another RIGHT/LEFT weapon source bit.

---

## Stage B causal conclusion

Readback raw:

```text
research/raw/2026-09-05_fist_stageb_damage_disabled_exact_readback.log
commit 1f74a216b32008b968677af3d271694857e7aeba
SHA256 08A8D3D54BA878606D7C4BE5D0A4D022F85C7C5ACF9969F74845C2FAF6180152
```

Observed:

```text
first accepted FIST: DamageDisabled 0 -> 1
later accepted FIST: DamageDisabled 1 -> 1
visual valid-target contact damage: YES
```

Conclusion:

```text
SetDamageDisabled(GETrue) works on the exact resolved Fist TouchDamage property.
DamageDisabled=true persists.
DamageDisabled=true does not stop the tested human Fist damage path.
```

Reject `DamageDisabled` as the production `FIST_OFF` mechanism. Do not speculate about the underlying reason.

---

## Restored live baseline

Restoration commit:

```text
1910c999fef91f97baadb6e19a1f4f393c9c4d5b
Restore proven Fist Stage A baseline
```

Independent comparison to Stage A implementation `5984738a41eca895900ae0929c3c930336c8ff53` found no prototype/source differences.

Restored diagnostic built successfully on the Windows/game PC and is the only verified live collision twin:

```text
Script_FrameCollisionTest.dll
SHA256 F31368142214B2F645F2D6B5EE67B6ADE939CB5DA9BE6F79908019E9A6B5C449
length 428032
```

Startup PASS:

```text
Script_FrameCollisionTest diagnostic build loaded.
DiagnosticProfile: CORE
MarkerOpcodes: RIGHT LEFT BOTH OFF FIST
Hooks installed.
```

Current dedicated marker behavior is again exactly:

```text
G3AB_COL_FIST
-> resolve/validate human gEUseType_Fist / raw 8
-> TouchDamage.ClearTriggeredList()
-> no DamageDisabled read/write
-> no weapon collision-group mutation
```

---

## Factual SDK lead — not yet a mechanism

Tested SDK declarations establish:

```text
gCTouchDamage_PS : eCTrigger_PS

gCTouchDamage_PS:
- ResetOnUntouch
- DamageDisabled

eCTrigger_PS inherited trigger gates:
- IsEnabled
- ReactToTouch

trigger path:
- ClearTriggeredList()
```

`DamageDisabled` is already rejected. `IsEnabled` and `ReactToTouch` are factual native properties, but there is currently **no evidence that stock human Fist attack execution toggles either one**.

Do not mutate them yet.

---

## Exact next responsibility — N1 native Fist trigger-state observation

Implement one bounded diagnostic-only probe.

Use only existing hooks. Add no hook and change no behavior.

For a native **unmarked** human Normal/Fist execution where `OnAI_Attack` is forwarded to the original callback, resolve the same logical human `gEUseType_Fist` / raw 8 source and take factual read-only snapshots at:

```text
NATIVE_ATTACK_BEFORE_ORIGINAL
NATIVE_ATTACK_AFTER_ORIGINAL
AISETSTATE_BEFORE_ORIGINAL
AISETSTATE_AFTER_ORIGINAL
```

Each snapshot must report from the exact resolved Fist TouchDamage property set:

```text
FistSourceResolved
FistSourceAddress
FistUseType
FistCollisionGroup
IsEnabled
ReactToTouch
ResetOnUntouch
DamageDisabled
```

Include enough existing actor/action/phase/current-motion context to associate the snapshot with the native Fist execution, but do not add broad diagnostics.

The native attack callback must still execute exactly once with unchanged arguments and ordering.

The marked `G3AB_COL_FIST` path must remain untouched and must continue suppressing the native callback exactly as before.

Known unmarked player Fist motion seen in prior runtime evidence:

```text
Hero_Stand_None_Fist_P1_Attack_Hit_N_Fwd_00_%_00_P0_100_L.xmot
```

This filename is a convenient controlled fixture only. Runtime action/source identity remains authoritative.

### N1 question

> Does stock native human-Fist execution change `IsEnabled`, `ReactToTouch`, or another logged trigger-state value across the existing native attack/finalization boundaries?

Only after runtime evidence answers that question may Normal Chat choose the next causal probe.

---

## Explicit N1 non-goals

Do **not** implement:

```text
G3AB_COL_FIST_OFF
SetIsEnabled(...)
SetReactToTouch(...)
another DamageDisabled mutation
any alternate disable mechanism
new hooks
persistent Fist marker-owned state
baseline snapshot/restore
terminal/interruption restoration
PhysicalFist support
monster/general body collision
per-limb Fist markers
weapon source-mask changes
attack-family or StatePosition redesign
C1 or weapon-lifecycle redesign
RIGHT/LEFT/BOTH/OFF redesign
```

---

## Frozen continuation

```text
A  — dedicated FIST baseline                     CLOSED/PASS
B  — DamageDisabled causal investigation         CLOSED/FAIL AS OFF MECHANISM
R  — exact restoration to Stage A behavior       CLOSED/PASS
N1 — native trigger-state read-only observation  CURRENT
N2 — next causal probe                           BLOCKED until N1 runtime evidence
C  — production FIST/FIST_OFF lifecycle          BLOCKED until control mechanism is proven
```

---

## Local-state caution carried forward

Earlier local status showed this unrelated untracked file:

```text
research/raw/2026-09-04_hack_2h_dedicated_p0_override_validation.log
```

Do not delete, rename, stage, overwrite, or clean it merely to obtain a clean working tree.

---

## Deliberately outside the immediate continuation

```text
production G3AB_COL_FIST_OFF
persistent Fist marker-owned lifecycle
Fist terminal/interruption restoration
PhysicalFist / monsters / generalized body collision
per-limb Fist markers
new attack actions / Quick-selection logic
attack-family / StatePosition redesign
C1 or weapon-lifecycle redesign
RIGHT/LEFT/BOTH/OFF redesign
Hack / SimpleWhirl redesign
final native mixed regression
final New Balance + Script_AttackCollision mixed regression
Raise
playback-speed redesign
target acquisition
climbing
```

# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-05

## Current bridge — Fist Stage B contact still damaged; exact DamageDisabled readback next

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
```

Do not reopen those areas without concrete contradictory evidence.

The final native-control and New Balance + Script_AttackCollision mixed regressions remain postponed until human Fist collision support is integrated and validated.

Fist remains a logical human body-contact source adapter inside the closed collision architecture. It is not another RIGHT/LEFT weapon source bit.

---

## Proven Fist baseline

Stage A implementation:

```text
5984738a41eca895900ae0929c3c930336c8ff53
```

Stage A raw evidence:

```text
research/raw/2026-09-05_fist_stagea_human_dedicated_fist_baseline.log
91e6d4f81b5f8d549546686a6d308ddff3e3bd9f
```

Known-good fixture:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
frame 3: G3AB_COL_FIST
```

Stage A established:

```text
visual damage: YES
human Fist UseType: 8
collision group: 0 -> 0
ClearTriggeredList: yes
weapon source mask: none
weapon group request: none
valid C1 generation / accepted FIST marker
```

---

## Stage B first causal probe — RESULT QUALIFIED / NOT CLOSED

Temporary implementation:

```text
a8ce1487b53ff2f8e6b6b9d9e87ac36e2322c561
Add temporary Fist DamageDisabled causal probe
```

Only behavior change from Stage A source:

```text
same dedicated FIST route
same gEUseType_Fist / raw 8 validation
same ClearTriggeredList behavior
+ SetDamageDisabled(GETrue)
```

Validated diagnostic DLL:

```text
SHA256 A734F3C95A1A36A8B0FB3A1768AE8EEDF459AB2E0957FC34BD4E73E3E4CE6E38
```

Raw evidence:

```text
research/raw/2026-09-05_fist_stageb_damage_disabled_causal_probe.log
commit 626a6bca71469263a9da84959dfa203e4d0155ac
```

Runtime result:

```text
visual damage: YES
FIST route still accepted and healthy
human Fist UseType: 8
collision group: 0 -> 0
ClearTriggeredList: yes
weapon source mask: none
```

Important qualification:

```text
The logger does NOT record DamageDisabled before or after the setter.
```

Therefore do not conclude either:

```text
DamageDisabled definitely became true but does not control Fist damage
```

or:

```text
SetDamageDisabled failed to change the runtime property
```

Neither is established yet.

---

## Exact next responsibility — Stage B readback probe

Freeze one bounded Work task whose only purpose is to make the existing Stage B experiment factually observable.

Keep unchanged:

```text
same G3AB_COL_FIST route
same human Fist source resolution
same SetDamageDisabled(GETrue) call
same ClearTriggeredList call
same marker/C1/family bookkeeping
same StatePosition behavior
same collision-group behavior
same weapon-mask behavior
same hooks
same lifecycle behavior
```

Add only the smallest readback/diagnostic path necessary to report, for the exact resolved Fist TouchDamage property set used by `RearmFistSource()`:

```text
DamageDisabledBefore
DamageDisabledAfter
```

where `Before` is read immediately before the existing `SetDamageDisabled(GETrue)` call and `After` is read immediately after it.

Work must inspect only the necessary SDK/API declaration to use the factual getter/readback supported by the tested SDK. Do not guess the accessor name or introduce an alternate property path if the existing property set already exposes the factual value.

The resulting values must reach the existing CORE `FIST RECEIVED` diagnostic record without adding a new hook or changing behavior semantics.

### Runtime question after that implementation

> On the same known-good Fist marker execution, did the exact `DamageDisabled` runtime property change from its prior value to true?

Only after this is answered may Normal Chat decide whether to:

- investigate why true still allows damage, or
- correct the setter/property-access path if the value did not change.

Do not choose either branch in advance.

---

## Explicit non-goals

Do **not** implement yet:

```text
G3AB_COL_FIST_OFF
persistent Fist marker-owned state
baseline snapshot/restore
terminal/interruption restoration
alternate disable mechanisms
PhysicalFist support
monster/general body collision
per-limb Fist markers
weapon source-mask changes
new hooks
attack-family or StatePosition redesign
C1 or weapon-lifecycle redesign
```

Stage C remains blocked until Stage B identifies a proven control mechanism.

---

## Local-state caution carried forward

Earlier local status showed this unrelated untracked file:

```text
research/raw/2026-09-04_hack_2h_dedicated_p0_override_validation.log
```

Do not delete, rename, stage, or overwrite it merely to obtain a clean working tree.

---

## Deliberately outside the immediate continuation

```text
production G3AB_COL_FIST_OFF
persistent Fist marker-owned lifecycle state
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

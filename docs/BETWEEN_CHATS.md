# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-05

## Current bridge — Fist Stage B closed/failed for DamageDisabled; restore Stage A FIST behavior next

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
```

Do not reopen those areas without concrete contradictory evidence.

The final native-control and New Balance + Script_AttackCollision mixed regressions remain postponed until human Fist collision support is integrated and validated.

Fist remains a logical human body-contact source adapter inside the closed collision architecture. It is not another RIGHT/LEFT weapon source bit.

---

## Proven Stage A baseline

Implementation:

```text
5984738a41eca895900ae0929c3c930336c8ff53
```

Raw evidence:

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

## Stage B — CLOSED/FAIL FOR DAMAGEDISABLED AS FIST_OFF MECHANISM

Temporary setter implementation:

```text
a8ce1487b53ff2f8e6b6b9d9e87ac36e2322c561
```

Exact readback implementation:

```text
933e652c7ee66a45b9cd826f249c93019c6248da
```

Readback raw evidence:

```text
research/raw/2026-09-05_fist_stageb_damage_disabled_exact_readback.log
commit 1f74a216b32008b968677af3d271694857e7aeba
SHA256 08A8D3D54BA878606D7C4BE5D0A4D022F85C7C5ACF9969F74845C2FAF6180152
```

Validated readback diagnostic DLL:

```text
SHA256 9D2BE5AC24F973F7EDEB2BD8183DB6D8CC458BF4BE9EC2F22776026D84172A09
```

Causal result:

```text
first accepted FIST:
DamageDisabledBefore: 0
DamageDisabledAfter:  1
visual damage: YES

later accepted FIST executions:
DamageDisabledBefore: 1
DamageDisabledAfter:  1
visual damage remained possible
```

The same accepted FIST route still showed:

```text
human gEUseType_Fist / raw 8
collision group 0 -> 0
ClearTriggeredList yes
weapon source mask none
```

Conclusion:

```text
SetDamageDisabled(GETrue) DOES change the exact resolved Fist TouchDamage property.
The true value persists across later attacks.
DamageDisabled=true DOES NOT stop the tested human Fist damage path.
```

Therefore reject `DamageDisabled` as the production FIST_OFF mechanism for this path. Do not speculate yet about why the flag is ineffective.

---

## Exact next responsibility — restore the Stage A source baseline

The repository source still contains the temporary Stage B mutation/readback experiment. The next Work task is restoration only.

Restore the dedicated human FIST operation to:

```text
validate exact gEUseType_Fist / raw 8 source
TouchDamage.ClearTriggeredList()
no DamageDisabled setter
no DamageDisabled getter/readback
```

Remove only the temporary Stage B `DamageDisabled` data/diagnostic plumbing introduced for the causal/readback probes.

Keep unchanged:

```text
G3AB_COL_FIST opcode and route
human Fist source resolution
ClearTriggeredList timing/behavior
marker/C1/family bookkeeping
StatePosition behavior
collision-group behavior
weapon source masks
hooks
lifecycle behavior
RIGHT/LEFT/BOTH/OFF behavior
```

Do not add another candidate disable mechanism in the restoration task.

After Work publishes the restoration, Normal Chat must independently review the diff and build the diagnostic target. Only then begin the next source/evidence investigation into the factual native Fist enable/disable mechanism.

---

## Frozen continuation

```text
A — dedicated FIST baseline
    CLOSED/PASS

B — DamageDisabled causal investigation
    CLOSED/FAIL AS OFF MECHANISM

R — exact restoration to Stage A FIST behavior
    CURRENT

N — identify factual native Fist enable/disable mechanism
    NEXT AFTER RESTORATION
    source/evidence investigation first; no mechanism implementation by assumption

C — production FIST/FIST_OFF lifecycle
    BLOCKED until N yields a causally validated control mechanism
```

---

## Explicit restoration non-goals

Do **not** implement during restoration:

```text
G3AB_COL_FIST_OFF
alternate Fist disable mechanisms
persistent Fist marker-owned state
baseline snapshot/restore
terminal/interruption restoration
PhysicalFist support
monster/general body collision
per-limb Fist markers
weapon source-mask changes
new hooks
attack-family or StatePosition redesign
C1 or weapon-lifecycle redesign
```

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
alternate Fist disable mechanism implementation before factual investigation
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

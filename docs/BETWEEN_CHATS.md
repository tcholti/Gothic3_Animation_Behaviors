# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-03

## Current bridge — remaining equipped-melee marker validation

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and follow its bootstrap.

CAM is the constitutional collaboration layer; `docs/README.md` is the highest Gothic-specific project charter beneath CAM. Do not modify CAM from Gothic 3 work.

---

## Closed boundary

```text
collision architecture verification             COMPLETE — EV-206–EV-215
Hack callback runtime identity                  CLOSED — EV-216
Power marker adapter validation                 CLOSED/PASS
Pierce marker adapter validation                CLOSED/PASS
```

Do not reopen the verified C1 lifecycle/generation architecture, Power, or Pierce without concrete contradicting evidence.

Compact retrieval checkpoint for the completed Power/Pierce runtime evidence:

`research/derived/2026-09-03_power_pierce_marker_validation_checkpoint.md`

Branch lifecycle remains:

```text
complete collision on docs/collision-source-evidence
→ migrate mature collision behavior into Script_G3AnimationBehaviors
→ validate diagnostics-free collision integration
→ promote completed collision checkpoint to main
→ create feature/raise-attack-speed from updated main
```

Do not create `feature/raise-attack-speed` early.

---

## Implemented remaining-melee batch

Implementation:

`f0d929c90fbe086f44f66f91a2523904d06c3903` — remaining melee marker adapters + optional Hack routing

Generic marker StatePosition diagnostic correction:

`7c31784c5ef86bc79b54d573144b8e40f33e5e6b`

Implemented marker scope:

```text
PowerAttack
PierceAttack
SimpleWhirl
HackAttack
```

Bookkeeping:

```text
Power ordinary/non-Dual -> StatePosition 1
Power Dual              -> StatePosition 2
Pierce                   -> StatePosition 1
SimpleWhirl              -> StatePosition 1
Hack                     -> OnAI_HackAttack -> StatePosition 1
```

`GetUpAttack` is not part of the planned marker roadmap. `FinishingAttack` remains deliberately native/unmarked. Fist/body contact remains a separate later source-adapter responsibility.

---

## Power validation — CLOSED/PASS

Ordinary isolated evidence:

`research/raw/2026-09-02_power_marker_adapter_isolated_validation.log`  
commit `369f3ad6626417e319518c915f63b601b07fc60b`

Legitimate-interruption evidence:

`research/raw/2026-09-02_power_legitimate_interruption_cleanup_validation.log`  
raw commit `2f602453ae38fea120bbf5ff78c2d9fc953c4d99`  
derived package commit `a80162099f4248a446199b7f46ea981cc24a8de8`

Validated ordinary 1H/2H/Staff, Dual exact-set multi-contact behavior, StatePosition policy, unmarked fallback, natural cleanup and qualifying post-marker legitimate interruption cleanup. C1-R1 remained a no-op fail-safe beneath Gothic's native cleanup.

---

## Pierce validation — CLOSED/PASS

### Native Pierce source correspondence

Raw:

`research/raw/2026-09-02_pierce_native_marker_adapter_isolated_validation.log`  
commit `7accaaf9b254a9121ec111e02f65f9e8fca2d3a9`

Validated:

```text
Dual P0 Pierce -> RIGHT
Dual P1 Pierce -> LEFT
accepted Pierce marker -> StatePosition 1
```

User visually confirmed target collision.

### Power-motion / multi-marker Pierce

Raw:

`research/raw/2026-09-02_pierce_power_motion_multi_marker_validation.log`  
commit `c4026282b9277738468a6caf99f49b8f484f72dd`

Pierce action 11 successfully executed the copied Power motion marker programs:

```text
P0: BOTH -> LEFT  -> OFF -> BOTH
P1: BOTH -> RIGHT -> OFF -> BOTH
```

The result proves the intended separation:

```text
native Pierce action/family -> Pierce bookkeeping / StatePosition 1
authored markers            -> RIGHT / LEFT / BOTH / OFF physical source behavior
```

User visually confirmed all authored contacts could connect against the selected target.

### Legitimate interruption cleanup

Raw:

`research/raw/2026-09-02_pierce_power_motion_interruption_cleanup_validation.log`  
commit `327fb20247eedb443e57f4b7fe1d4c644a1e6655`

Strong qualifying cases captured both:

```text
BOTH live -> interruption -> both exact sources clean 7 -> 5 -> Stumble
BOTH -> LEFT -> interruption -> remaining LEFT cleans 7 -> 5 -> Stumble
```

No C1 repair was required.

### Native Pierce target/reaction observation

During multi-target combat the User observed that Pierce contacts affected the selected/focused target while another nearby target was not hit by the same swings. The exact internal mechanism is unproven and should not be conflated with Fist merely because the behavior looks similar.

Humanoid targets which normally perform the distinctive long Pierce stumble continued to perform that same reaction when the Pierce action used copied Power motion content. This supports an action-level/native Pierce semantic boundary independent of animation content.

Current bounded interpretation:

```text
G3AB markers control WHEN and WHICH physical weapon source is live.
Pierce action 11 retains native target/reaction semantics.
```

This makes alternate authored stabbing patterns using RIGHT, LEFT or both weapons useful, while broad sweeping Pierce animations may not behave like generic multi-target attacks.

### New Balance + Jackydima Script_AttackCollision control

Raw:

`research/raw/2026-09-03_pierce_native_marker_newbalance_badskip_control.log`  
commit `fd91f90a255559923f2ada7e83355333177931f0`

Configuration:

```text
New Balance bad-skip prevention active
Jackydima Script_AttackCollision active
no target
```

User performed four accepted Pierce executions in each configuration:

```text
1H                 x4
Torch + 1H         x4
Shield + 1H        x4
Dual P0 / RIGHT    x4
Dual P1 / LEFT     x4
```

All 20 accepted executions had valid C1 generation bookkeeping, `StatePositionAfterMarker: 1`, exact expected source `5 -> 7 -> 5`, no C1 repair/finalization physical change, and clean unload. Torch and Shield remained resolved-but-inactive LEFT partners under RIGHT-only Pierce markers.

Conclusion:

> Pierce marker handling is runtime-compatible with the tested New Balance + Jackydima Script_AttackCollision configuration for the tested Pierce equipment cases.

This is Pierce-specific compatibility evidence, not blanket compatibility certification for every callback/family in Script_AttackCollision.

### Benign diagnostic-cadence observation

Across repeated Pierce executions, a fresh `MARKER OWNERSHIP DECISION` block appears once per distinct motion rather than once per execution, while later executions still create fresh C1 generations, reset execution budgets, accept markers correctly, mutate exact physical sources correctly, and clean naturally.

The observation persists with New Balance bad-skip prevention active. Therefore bad skip is not required for it and should no longer be treated as its likely explanation.

A relationship to native Pierce target/effect semantics is plausible but unproven. Because behavior and bookkeeping are correct, do not investigate this further unless a future behavioral contradiction makes it relevant.

---

## HackAttack optional animation routing — implemented, runtime validation still pending

EV-216 closes the tested callback identity: `Script_Game +0x433D0` uniquely maps to `OnAI_HackAttack`.

Implemented optional routing responsibility:

```text
runtime action == HackAttack (14)
→ preserve final namespace/name produced by native or compatible resolver
→ at CombatMove QueryMotionDataEntity callsite, derive only _HackAttack_ token variant
→ matching Hack asset exists: use candidate resource
→ candidate absent: preserve original FinishingAttack resource unchanged
```

True runtime `FinishingAttack` action 15 remains unchanged/native.

Preferred authored fixtures:

```text
Hero_Parade_None_2H_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_2H_P0_HackAttack_Hit_N_Fwd_00_%_00_P0_100.xmot
Hero_Parade_None_2H_P0_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot

Hero_Parade_None_Staff_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_Staff_P0_HackAttack_Hit_N_Fwd_00_%_00_P0_100.xmot
Hero_Parade_None_Staff_P0_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot
```

The `100` suffix remains animation-author metadata, not DLL logic.

---

## AttackContinuationProtection — later, separate responsibility

Frozen outcome:

```text
prevent the known destructive continuation/bad-skip mechanism
from terminating or advancing through a legitimately live Hit execution
```

The mechanism is not frozen. Keep it separate from `CollisionLifecycleGuard`; C1-R1 remains the general lost-cleanup fail-safe.

---

## Immediate next step

Do not perform more work tonight merely to broaden Power/Pierce evidence.

Next session:

```text
SimpleWhirl isolated validation
→ Hack isolated validation
→ combined marker/lifecycle regression
```

For SimpleWhirl, first inspect only the exact existing SimpleWhirl fixtures/source evidence needed to freeze the isolated test. Do not guess assets or reopen Power/Pierce.

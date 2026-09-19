# SprintAttack raw8 FIST production implementation

## Status

Frozen production implementation contract.

This responsibility is intentionally narrow. It adds authored-frame `G3AB_COL_FIST` support for the evidenced raw8 SprintAttack case only.

## Evidence basis

The bounded Sprint transport probe established all of the following for the tested native Sabretooth SprintAttack executions:

- factual routine action is `gEAction_SprintAttack` / Action 9;
- the physical script transport is the existing `OnAI_PowerAttack` callback;
- at `OnAI_PowerAttack` callback ENTRY, actor routine action is already Action 9 while SPU+0x154 remains Action 2;
- the actor remains Action 9 after the original callback;
- the Sprint Hit motion is `Sabertooth_Stand_None_Fist_P0_PowerAttack_Hit_N_Fwd_00_%_00_P0_300.xmot` in the tested fixture;
- Sprint marker executions occur in `gEPhase_Hit` with `StatePosition=1`;
- the authored marker is `G3AB_COL_FIST`;
- C1 generation is valid;
- the factual collision source is `Fist`, `gEUseType_Fist` / raw8, collision group 0;
- `RequiredSourceMask=0` and there is no left/equipped weapon source;
- current rejection is `REJECTED_UNSUPPORTED_HIT` because Sprint is not yet a first-class supported attack family.

The tested fixture that reproduces Sprint traffic sufficiently for validation is:

1. enable god mode;
2. transform the player into Sabretooth;
3. spawn a native Sabretooth;
4. fight it, including Power attacks from range.

The exact AI decision rule for choosing SprintAttack is not part of this responsibility.

## Frozen responsibility

Implement production raw8 Sprint FIST marker support through the existing physical `OnAI_PowerAttack` transport.

### 1. Add a first-class Sprint attack family

Add `AttackFamily_Sprint` to the existing `AttackFamily` enum.

Map factual `gEAction_SprintAttack` to `AttackFamily_Sprint` in the existing attack-family resolver.

Diagnostics that name attack families/actions must report Sprint as `SPRINT` rather than `UNKNOWN`.

### 2. Route the existing Power callback by factual actor action

Do not add a new hook.

The existing physical `OnAI_PowerAttack` callback remains the sole transport owner for both ordinary Power and Sprint.

At callback entry, choose the semantic family from factual actor routine action:

- `gEAction_SprintAttack` -> `AttackFamily_Sprint`;
- otherwise preserve the existing ordinary Power path -> `AttackFamily_Power`.

Then call the existing `EvaluateAttackCallback(...)` once with that selected family.

Preserve the existing original-callback semantics exactly:

- if marker ownership suppresses native callback, return `GETrue` exactly as today;
- otherwise call the original `OnAI_PowerAttack` exactly once and return its result unchanged.

Do not use SPU+0x154 to classify Sprint semantically. The probe proved SPUAction remains 2 while actor routine action is 9.

### 3. Admit Sprint to the proven raw8 FIST mechanism

Extend `Raw8FistCollision::IsSupportedFamily()` to include `AttackFamily_Sprint`.

Do not create a separate Sprint raw8 implementation.

Sprint must reuse the existing raw8 mechanism unchanged:

- C1-scoped initial latch close (`SPU+0x164 = 1`) before first accepted FIST marker;
- accepted `G3AB_COL_FIST` latch write (`SPU+0x164 = 0`);
- existing early timing permission when marker playtime is below the native threshold;
- native Gothic contact/damage path remains authoritative;
- existing C1 generation identity and timing-permission retirement rules remain unchanged.

### 4. Sprint marker-owned StatePosition

The evidenced Sprint marker executions are `StatePosition=1`.

Add `AttackFamily_Sprint` to the existing marker-owned StatePosition mapping with value `1`.

Do not add Sprint-specific StatePosition bookkeeping. Reuse the existing generic marker path.

### 5. Keep equipped Sprint explicitly unsupported

This implementation is raw8-FIST-only.

Current Sprint evidence has:

- `RequiredSourceMask=0`;
- right source `Fist`, raw8;
- no left source;
- no evidenced equipped RIGHT/LEFT/BOTH/OFF Sprint execution.

Therefore this task must not enable equipped Sprint marker control.

A Sprint execution may be accepted only for `G3AB_COL_FIST` using an exact raw8 Fist source under the existing raw8 ownership checks.

Do not broaden Action 9 into equipped RIGHT/LEFT/BOTH/OFF marker behavior.

If the current generic marker-family admission would make equipped Sprint source markers eligible merely by adding `AttackFamily_Sprint`, add the smallest explicit guard necessary to keep Sprint FIST-only.

### 6. Retire the temporary Sprint transport probe

The `SPRINT_TRANSPORT` ENTRY / AFTER_ORIGINAL diagnostic probe has answered its question.

Remove the temporary probe logging and any helper declaration/use that exists solely for that diagnostic, provided doing so does not disturb the existing CombatMove factual-action helper used by `AttackMotionRouting`.

Do not remove or change the established factual-action helper itself if it is still required by motion routing.

## Explicit non-goals

Do not:

- add a new physical Sprint hook;
- add a new callback target, RVA, calling convention, or transport;
- alias Sprint semantically to Power;
- classify Sprint from animation filename alone;
- classify Sprint from SPU+0x154 Action 2;
- implement equipped Sprint RIGHT/LEFT/BOTH/OFF support;
- change marker vocabulary;
- change raw8 source resolution;
- change the native raw8 timing threshold or timing hook;
- change SPU+0x164 semantics beyond admitting Sprint into the existing proven mechanism;
- change C1 lifecycle semantics;
- change equipped collision cleanup / C1-R1 repair;
- change Hack routing;
- generalize to raw55;
- add custom damage;
- add species/name/Sabretooth special cases;
- investigate or encode the AI rule that causes SprintAttack;
- perform unrelated cleanup or refactoring.

## Preferred implementation surface

Expected files are limited to the smallest necessary subset of:

- `FrameCollisionShared.h`
- `FrameCollisionMarkers.cpp`
- `Raw8FistCollision.cpp`
- `EngineBridge.cpp`
- `CollisionDiagnostics.cpp`

A different existing file may be touched only if mechanically necessary for the exact frozen responsibility.

## Static audit requirements

Before publication verify:

- exactly the existing `OnAI_PowerAttack` physical hook remains the transport owner;
- no new hook / callback / RVA / calling convention exists;
- Action 9 resolves to `AttackFamily_Sprint`;
- the Power callback selects Sprint from factual actor routine action and otherwise preserves Power;
- raw8 supported-family admission includes Sprint;
- Sprint marker-owned StatePosition is 1;
- Sprint equipped source markers remain unsupported;
- Normal / Power / Quick / SimpleWhirl / Whirl / Pierce / Hack routing is unchanged;
- original `OnAI_PowerAttack` call count and return semantics are preserved;
- temporary `SPRINT_TRANSPORT` logging is removed;
- diagnostics remain mechanically absent from the behavior-only target as before;
- `git diff --check` passes.

## Build policy

Per `WORK_IMPLEMENTATION_PROTOCOL.md`, BUILD EXECUTION / BUILD TOOLING PROBING is prohibited in Work unless separately authorized.

Work must report build status as `NOT RUN / PROHIBITED`.

## Runtime validation after source review

After the Work commit is independently reviewed in Normal Chat, build both Release twins locally and deploy the diagnostic DLL.

Use the established fixture:

1. god mode;
2. transform player to Sabretooth;
3. spawn native Sabretooth;
4. fight, including Power attacks at range, until native Action 9 appears.

For a marked raw8 Sprint execution, expect the established production pattern:

- family resolves as `SPRINT`;
- `RAW8_FIST_OWNERSHIP` performs the initial close once for the C1 generation;
- `G3AB_COL_FIST` is `ACCEPTED` rather than `REJECTED_UNSUPPORTED_HIT`;
- marker action is 9, phase 1, StatePosition 1;
- exact raw8 Fist source remains group 0;
- latch transitions 1 -> 0 at the accepted marker;
- early permission is armed/used when below native threshold as appropriate;
- native `gCEntity::OnDamage` remains from the established Game.dll+0x16E348 caller path when contact occurs;
- no equipped collision behavior is introduced for Sprint;
- no lifecycle invariant warning or unrelated regression appears.

The exact distance/AI-selection rule for Sprint is not required for PASS.

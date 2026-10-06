# Attack Movement — Runtime Acceptance

**Status:** CLOSED / PASS — EV-445  
**Production source:** `7393f390f30d1981a5065b6342a684cd590fbac9`  
**Source review:** EV-441 PASS

## Purpose

Validate the new absolute per-profile Hit movement feature in the User's authoritative local Gothic 3 runtime.

## Build/deploy state

EV-442:
- User Fetch/Pull completed for the build state;
- Release Win32 `Script_G3AnimationBehaviors.dll` build succeeded;
- deployment/hash verification is the next step;
- runtime testing has not begun.

Next:
1. deploy with the previously accepted project PowerShell deployment/hash procedure;
2. capture the complete output;
3. require built/live DLL SHA256 match;
4. require source/live INI SHA256 match;
5. require exactly one live G3AB project DLL;
6. only after `G3AB RELEASE DEPLOYMENT PASS`, begin runtime testing.

Do not change source unless build/runtime evidence contradicts EV-441.

## Public-key cleanup — EV-444

After the first successful 2H runtime mechanism pass, the unreleased public key was renamed for clarity:

```text
<Attack>_Movement
->
<Attack>_MovementOverride
```

Reason: `Power_Movement=Off` can be misread as disabling movement itself. `Power_MovementOverride=Off` clearly means the override is disabled.

This is a parser/INI naming cleanup only. Internal movement policy, hook ownership and runtime calculation are unchanged.

Required before broader acceptance:
1. Fetch/Pull the rename;
2. rebuild Release Win32;
3. redeploy DLL + INI and verify hashes;
4. perform one quick sanity control on a previously proven 2H attack:
   - `Power_MovementOverride=Off`
   - `Power_MovementOverride=0`
   - `Power_MovementOverride=300`
5. if the three cases behave as before, do **not** repeat the full EV-443 2H matrix; continue representative broader validation.

## Minimum staged runtime acceptance

### A. Off-path compatibility

With all shipping MovementOverride keys left `Off`:
- run native-only fixture if convenient;
- run intended New Balance + AttackCollision fixture;
- verify ordinary attacks behave as before;
- verify no obvious movement, Speed, Raise or Collision regression.

This is the compatibility control.

### B. Strong numeric contrast

Choose one familiar human profile/attack with clear forward movement, preferably Staff or 2H Power.

Test the same factual attack/profile with:
```text
MovementOverride=0
Movement=50 or another visibly short value
Movement=150 or another visibly long value
```

Expected:
- 0: no CombatMove forward translation during Hit;
- short vs long: clear ordered difference;
- attack animation timing remains governed by Speed;
- native ledge/obstacle/target stopping still constrains actual travel.

### C. New Balance override

Keep New Balance active.

For the same configured attack:
- confirm numeric G3AB Movement visibly overrides New Balance reach;
- restore `MovementOverride=Off` and confirm New Balance reach returns without changing DLLs.

This is the decisive compatibility contract.

### D. Same-profile normalization sanity

Where practical, use two attacks/resources inside the same profile/action whose native filename movement values differ (the known Staff Power case is a good candidate).

With one numeric `Power_MovementOverride` value:
- both should target the same nominal configured distance despite different authored filename numbers;
- do not require pixel-perfect measurement; clear convergence/normalization is enough for first acceptance.

### E. Representative action coverage

After the mechanism passes, sample:
- Normal;
- Quick R/L;
- Power;
- one of Hack/Pierce/Whirl where available;
- one representative nonhuman profile;
- Sprint/Power shared route on a previously proven creature if practical.

Do not turn this into exhaustive every-animation testing before the basic mechanism is accepted.

## Failure capture

If any case fails, record:
- exact profile and INI Movement value;
- factual attack/action if known;
- animation name if readily available;
- whether New Balance / AttackCollision were active;
- observed behavior;
- whether Off restores prior behavior.

Use diagnostics only if visual/gameplay evidence cannot isolate the failure.

## Closure

PASS when:
- Off preserves native/intended-stack behavior;
- numeric values clearly own movement magnitude;
- 0 disables CombatMove translation;
- New Balance returns when switched back Off;
- representative human/nonhuman/action coverage shows no Speed/Raise/Collision regression.


## Closure — EV-445

Runtime acceptance is complete.

Validated:
- standard human weapon/animation families across all available Normal/Quick/Power/Whirl/SimpleWhirl/Hack/Pierce routes;
- separated/custom Axe and Rapier routes;
- representative Troll, Sabertooth and Demon Normal/Quick/Power/Sprint routes;
- Off and multiple numeric distances;
- native Gothic and New Balance operation.

All tested cases behaved as expected.

Known user-visible boundary:
```text
MovementOverride cannot add movement when the selected attack animation itself
has movement value 0 in its animation name, because the final compatible vector
contains no usable direction at the one-hook seam.
```

Rapier Quick is the confirmed current example. Changing its authored movement value from 0 to 100 made MovementOverride effective both with and without New Balance.

No second hook/state/direction cache is justified.

Final result:
**PASS — absolute attack movement accepted for production on development.**

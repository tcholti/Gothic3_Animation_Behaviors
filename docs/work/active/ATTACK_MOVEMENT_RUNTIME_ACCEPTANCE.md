# Attack Movement — Runtime Acceptance

**Status:** ACTIVE  
**Production source:** `7393f390f30d1981a5065b6342a684cd590fbac9`  
**Source review:** EV-441 PASS

## Purpose

Validate the new absolute per-profile Hit movement feature in the User's authoritative local Gothic 3 runtime.

## Build/deploy first

User:
1. Fetch/Pull `development`;
2. build Release Win32 `Script_G3AnimationBehaviors.dll`;
3. deploy using the normal project procedure;
4. verify built/live DLL identity before testing.

Do not change source unless build/runtime evidence contradicts EV-441.

## Minimum staged runtime acceptance

### A. Off-path compatibility

With all shipping Movement keys left `Off`:
- run native-only fixture if convenient;
- run intended New Balance + AttackCollision fixture;
- verify ordinary attacks behave as before;
- verify no obvious movement, Speed, Raise or Collision regression.

This is the compatibility control.

### B. Strong numeric contrast

Choose one familiar human profile/attack with clear forward movement, preferably Staff or 2H Power.

Test the same factual attack/profile with:
```text
Movement=0
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
- restore `Movement=Off` and confirm New Balance reach returns without changing DLLs.

This is the decisive compatibility contract.

### D. Same-profile normalization sanity

Where practical, use two attacks/resources inside the same profile/action whose native filename movement values differ (the known Staff Power case is a good candidate).

With one numeric `Power_Movement` value:
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

# Speed v2 S-01 Finite Output Guard

**Status:** ACTIVE  
**Opened:** 2026-09-28  
**Branch:** `development`  
**Base HEAD:** `19eff2b8cab0f3d0db46f7f90f86fd8e4b1d8d18`

## Responsibility

Implement only the MINOR S-01 correction identified by the completed deep independent Speed v2 static audit.

The audit proved that `BehaviorProfiles::ParsePositiveFiniteFloat()` intentionally accepts every positive finite `BaseSpeed`, but `AttackSpeed::ComposeCompatibleSpeed()` validates only its inputs before returning:

```cpp
compatibleSpeed * (profile->baseSpeed / referenceBase)
```

For an extreme but parser-valid finite `BaseSpeed`, the arithmetic can overflow to a non-finite result. The production policy is fail-closed, so a non-finite composed result must return the already-computed live compatible speed unchanged.

## Exact implementation boundary

Modify only:

`src/Script_G3AnimationBehaviors/AttackSpeed.cpp`

After all existing profile/reference/input validation:

1. compute the composed result from the existing expression;
2. test the composed result with `std::isfinite`;
3. if non-finite, return `compatibleSpeed` unchanged;
4. otherwise return the composed result.

## Hard exclusions

Do NOT:

- change `BehaviorProfiles` parsing or impose an arbitrary `BaseSpeed` upper bound;
- change the `C/B` composition algebra;
- change any technical base fact;
- change any six caller hook or `EngineBridge` transport;
- change the `Script_Game+0x42A0` ownership model;
- change profile identity/schema;
- broaden supported actions/families/use types;
- touch collision behavior;
- add diagnostics, logging, state, caches or lifecycle machinery;
- build, deploy or run Gothic 3 in this source-only task;
- begin Raise work.

## Acceptance

Source review must prove:

- ordinary finite composed results are unchanged;
- a non-finite composed result returns `compatibleSpeed`;
- no other production source changed;
- the six-call Speed v2 mechanism and all fail-closed routing remain unchanged.

On PASS, archive this task and the completed deep audit, record the audit/correction result durably, and return the project to the local build/deploy gate.

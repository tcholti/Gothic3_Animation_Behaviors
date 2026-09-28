# Speed Runtime Profile Identity Probe — Result

**Status:** CLOSED / RUNTIME EVIDENCE CAPTURED  
**Date:** 2026-09-28  
**Branch:** `development`

## Purpose

Close the bounded diagnostics-only probe created after the first Speed v2 runtime acceptance attempt showed no visible change even with extreme configured `BaseSpeed` values.

## Runtime result

The standalone `Script_SpeedIdentityProbe` loaded successfully alongside the production stack and reused the exact production `BehaviorProfiles` implementation.

For the player with an ordinary right-hand 1H weapon and empty left hand, every observed Normal and Quick combat move reported:

```text
AnimationResourceName=G3_Hero_Skeleton
RuntimeKeyBuilt=true
Key.AnimationFamily=g3_hero_skeleton
Key.LeftAnimationUseType=none
Key.RightAnimationUseType=1h
ProfileMatch=false
```

Observed action/phase facts were also correct:

```text
Normal: Action=1, ActionProfile=Normal, RequestedPhaseName=Hit
Quick:  Action=4 or 5, ActionProfile=Quick, RequestedPhaseName=Hit
RawLeftUseType=0
RawRightUseType=2
```

The live INI used the accepted ADR-0007 author-facing family token:

```text
AnimationFamily=Hero
```

Therefore the production runtime key did not match because `BehaviorProfiles::TryBuildRuntimeKey()` normalized the raw resource name literally to `g3_hero_skeleton` instead of mapping the factual Gothic resource family to the accepted schema token `hero`.

## Causal conclusion

The first failed Speed runtime test does **not** yet implicate the six Speed caller transports or compatible composition. The failure occurs earlier at the runtime profile-family normalization boundary.

The factual correction must preserve ADR-0007's user-facing `AnimationFamily=Hero` contract. The smallest evidence-bounded repair is to normalize the exact observed runtime resource `G3_Hero_Skeleton` to the schema token `hero` when building the runtime profile key. Do not broaden to unobserved family aliases without evidence.

## Provenance

- raw runtime source: `research/archive/2026.09.28_SpeedIdentityProbe.log` after POP-06 archival;
- probe implementation/task lineage: `docs/work/active/SPEED_RUNTIME_PROFILE_IDENTITY_PROBE.md` in Git history;
- probe deployment SHA256: `4CE2AE915B3B76D867DDDAD6F1AC2C1848389DAF3CBCFDEE0E3783BA2DB5CC8E` built/live;
- user-run runtime environment retained the production `Script_G3AnimationBehaviors.dll`, New Balance and AttackCollision stack.

## Disposition

- **PASS — PROBE ANSWERED ITS FROZEN CAUSAL QUESTION.**
- **RUNTIME PROFILE FAMILY NORMALIZATION BUG CONFIRMED.**
- Next gate: bounded production correction of only the observed Hero resource-family normalization, then rebuild/deploy and re-run the same 1H Normal/Quick Speed acceptance before any Speed transport redesign.

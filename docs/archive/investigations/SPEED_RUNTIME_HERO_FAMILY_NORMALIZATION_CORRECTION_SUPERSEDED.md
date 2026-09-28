# Speed Runtime Hero Family Normalization Correction — Superseded

**Status:** SUPERSEDED BEFORE BUILD/RUNTIME  
**Date:** 2026-09-28  
**Branch:** `development`

## Original issue

The first Speed runtime identity probe established:

```text
Animation.GetResourceName() = G3_Hero_Skeleton
normalized production key    = g3_hero_skeleton
INI family token              = Hero -> hero
ProfileMatch                  = false
```

A narrow correction was briefly prepared to translate exact runtime resource `g3_hero_skeleton -> hero`.

## Why it was superseded

Before rebuilding production, the User clarified that the human skeleton/armature identity is distinct from this animation resource name and noted the repository-wide animation naming convention in which human animations begin with `Hero`.

Canonical `ANIMATION_RULES.md` already defines the first animation-name token as the animation family (`Hero`, `Demon`, `Goblin`, etc.). The SDK also exposes multiple distinct identity surfaces:

```text
Animation.GetResourceName()
Animation.GetSkeletonName(...)
Entity.GetSkeletonName()
NPC.GetCurrentMovementAni()
```

Therefore mapping one incidental resource string directly to the schema family would prematurely freeze the wrong identity source.

At the same time, the shared profile design was refined so factual reference base speeds live in generic profile data instead of the Hero-only C++ technical-base table.

## Disposition

- The temporary production `g3_hero_skeleton -> hero` mapping was reverted before a new production build/runtime test.
- `BehaviorProfiles.cpp` returned to its pre-correction source content.
- The user-facing `AnimationFamily=Hero` contract remains correct.
- ADR-0007 was revised to use generic `ReferenceHitBaseSpeed`, optional `ReferenceRaiseBaseSpeed`, one desired `BaseSpeed`, and `RaiseOverride=On|Off`.
- Recover remains derived from effective Hit speed and receives no independent INI key or reference value.
- The next gate is a diagnostics-only family-source probe comparing current movement animation, resource name, animation skeleton name, and entity skeleton name before the generic production refactor.

No production behavior from this superseded narrow correction is accepted as final architecture.

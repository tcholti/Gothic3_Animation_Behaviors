# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-27

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `development`  
Stable branch: `main`

## Current state

```text
EV-390 production collision integration = CLOSED/PASS
ADR-0007 shared Speed/Raise profile schema = ACCEPTED
BehaviorProfiles implementation = PASS
implementation SHA = 81d4964201579c9f7a989404426c3d9dc9ab4834
CURRENT = Speed v2 mechanism research/design ONLY
RAISE = PAUSED until Speed closes
```

Completed config task: `docs/archive/investigations/SHARED_PROFILE_CONFIG_FOUNDATION.md`.  
`docs/work/active/` has no current bounded implementation task.

## Primary Speed compatibility stack

Keep live while developing/testing Speed:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

New Balance compatibility is the primary runtime target. Native-only testing is a later fallback/sanity control after the modded stack works.

Pinned Jackydima source `316d32406a133f8884e7e302752c35f66b4f54fc` was checked 2026-09-27 and still equals upstream `master`.

Relevant ownership:

```text
Script_NewBalance/FunctionHook.cpp
  owns Script_Game +0x42A0 GetAnimationSpeedModifier
  combines base choices with stamina/disease/arena/etc. contextual modifiers

Script_AttackCollision/Script_AttackCollision.cpp
  owns melee callback/collision-timing behavior, not GetAnimationSpeedModifier
  remains active for full-stack attack-flow compatibility
```

## Frozen Speed requirement and authoring goal

```text
unconfigured = B * M
configured   = C * M
```

G3AB owns configured base `C`; legitimate Gothic/New Balance contextual modifiers `M` remain effective.

For explicitly configured Normal/Quick profiles, the intended nominal authored baseline is `BaseSpeed=1.0`. Animation authors should be able to use a common convenient frame/timing standard in Blender instead of baking historical Gothic `0.6/0.7` differences into source animations. INI profiles may then deliberately use values such as `1.05`, `1.10`, `1.15`, etc. according to desired gameplay feel.

ADR-0007 semantics remain:

```text
BaseSpeed absent = no G3AB override
BaseSpeed=1.00   = explicit authored base 1.00
```

Native/New Balance base values such as `0.6`, `0.7`, `1.0` are technical evidence/calibration facts only, not desired authoring defaults. Do not request exhaustive native timer logging unless the selected composition mechanism actually requires missing factual `B` values.

The old prototype is not final architecture because it discards the previous hook's final result and returns the configured speed directly.

Current causal question:

```text
Where can G3AB substitute/transform B -> C while preserving M,
without competing for ownership of the whole +0x42A0 function or copying New Balance policy?
```

A downstream ratio transform `(B*M) * (C/B) = C*M` is a research candidate only; it is not accepted architecture until a stable consumer surface and trustworthy exact B source are proven.

## Exact next route

```text
1. continue static investigation of GetAnimationSpeedModifier consumers/downstream playback path
2. determine whether a stable composition surface exists outside the competing +0x42A0 entry hook
3. determine whether that mechanism needs factual native/mod B values
4. only then request missing logger evidence if necessary
5. if static/source evidence cannot resolve causality, freeze the smallest diagnostics-only runtime probe
6. only after mechanism proof, freeze bounded Speed implementation
7. Speed must close completely before Raise begins
```

Authorities: ADR-0004, ADR-0007, `DESIGN.md` §§2–3, `SOURCE_HOOK_GUIDE.md`, `references/README.md`.

Collision is closed through EV-390; do not reopen historical collision research absent contradictory evidence.

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

The completed config task is archived at:

```text
docs/archive/investigations/SHARED_PROFILE_CONFIG_FOUNDATION.md
```

`docs/work/active/` has no current bounded implementation task.

## Primary Speed compatibility stack

Keep these live while developing/testing Speed:

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
  hooks Script_Game +0x42A0 GetAnimationSpeedModifier
  Normal base examples: 0.6 / 0.7 / 1.0
  contextual multiPlier includes stamina, disease, arena and other conditions

Script_AttackCollision/Script_AttackCollision.cpp
  hooks melee AI callbacks and collision timing/state positions
  does NOT own GetAnimationSpeedModifier
  remains active for full-stack attack-flow compatibility
```

## Frozen Speed requirement

```text
unconfigured = B * M
configured   = C * M
```

G3AB owns configured base `C`; legitimate Gothic/New Balance contextual modifiers `M` must remain effective.

The old prototype is not final architecture because for a configured route it discards the previous hook's final result and returns the configured speed directly.

Current causal question:

```text
Can G3AB intervene at a stable point where only the base term B is chosen/replaced,
while New Balance/Gothic still owns M and final composition?
```

Do not freeze a same-function competing hook, copied New Balance multiplier table, or final-result replacement merely because it is easy.

## Exact next route

```text
1. inspect native/tested binary route around GetAnimationSpeedModifier and its consumers
2. locate possible narrower base-choice/input surfaces
3. compare those surfaces with New Balance hook ownership/chaining
4. if static/source evidence cannot resolve causality, freeze the smallest diagnostics-only runtime probe
5. only after mechanism proof, freeze bounded Speed implementation
6. Speed must close completely before Raise begins
```

Authorities: ADR-0004, ADR-0007, `DESIGN.md` §§2–3, `SOURCE_HOOK_GUIDE.md`, `references/README.md`.

Collision is closed through EV-390; do not reopen historical collision research absent contradictory evidence.

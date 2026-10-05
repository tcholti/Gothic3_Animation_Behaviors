# Attack Forward Displacement — Runtime Probe Implementation

**Status:** CANCELLED / REDUNDANT — EV-435  
**Branch:** `development`  
**Static evidence baseline:** EV-434  
**Parent research:** `docs/work/active/ATTACK_FORWARD_DISPLACEMENT_RESEARCH.md`

## Purpose

Implement the smallest **read-only diagnostic DLL** needed to close the final runtime question for attack forward displacement:

> Does the final compatible CombatMove velocity, integrated over the actual enabled movement interval, account for representative observed entity travel closely enough to support downstream scalar composition?

This probe must observe behavior only. It must not change attack movement, speed, animation selection, Collision, Raise, targeting, or third-party behavior.

## Product

Create a separate removable diagnostic target:

```text
Script_AttackDisplacementProbe.dll
```

Do not put experimental state or logging into `Script_G3AnimationBehaviors.dll`.

## Allowed repository files

```text
CMakeLists.txt
tools/Script_AttackDisplacementProbe/CMakeLists.txt
tools/Script_AttackDisplacementProbe/Script_AttackDisplacementProbe.cpp
```

No production source files may change.

## Required static preflight

Before coding, verify against the tested binary reference / SDK:

```text
Game+0x16B8B7 = CombatMove-specific EnableCombatMovementFromSPU call
Game+0x169819 = ordinary CombatMove cleanup disable call
```

Derive the exact call-site ABI/argument/register transport rather than guessing it.

If `+0x169819` cannot factually delimit the corresponding ordinary enabled interval for the requested fixture, STOP and report the smallest additional observation seam required. Do not broaden automatically.

## Probe boundary

Preferred observation surfaces:

1. `Game+0x16B8B7`
   - observe the final vector immediately before CharacterMovement receives it;
   - this is after native filename-distance scaling and after the project-pinned New Balance `CombatMoveScale` insertion at `+0x16B8A9`.

2. `Game+0x169819`
   - observe ordinary CombatMove movement disable/cleanup if static preflight confirms it is sufficient for the fixture.

Do not hook:
- `AICombatMoveInstr`;
- `GetAnimationSpeedModifier`;
- `GetAniName`;
- New Balance or AttackCollision DLL functions;
- Collision lifecycle hooks;
- generic frame/update movement unless the preflight proves the two bounded call sites cannot answer the question.

## Required observations

For each measured interval, record one compact START and one compact END record with a stable sequence/generation id.

START should capture, where factually available at this exact seam:

```text
sequence id
actor/entity identity
player vs NPC/transformed status if cheaply available
factual SPU instruction action
current phase
selected/current movement animation name
request/current AniSpeedScale if available without another policy query
final compatible movement vector X/Y/Z
final compatible horizontal vector magnitude
entity world position X/Y/Z
monotonic timestamp
New Balance module loaded yes/no
production G3AB module loaded yes/no
AttackCollision module loaded yes/no
```

END should capture:

```text
same sequence id
entity world position X/Y/Z
monotonic timestamp
horizontal observed displacement from START
elapsed enabled time
predicted travel = START horizontal vector magnitude * elapsed time
difference = observed - predicted
ratio when denominator is nonzero
```

Do not call `GetAnimationSpeedModifier`, `GetCombatMoveLength`, or rederive a replacement movement policy. Observe the already-final vector.

## State/lifecycle

Keep only the minimum temporary per-actor/per-SPU state necessary to pair START with the corresponding END.

Requirements:
- bounded state;
- no gameplay mutation;
- no persistence across unrelated requests;
- safe replacement/cancellation handling if a new START occurs before the old interval closes;
- log the unmatched/replaced interval rather than inventing a result;
- no per-frame polling.

The initial runtime fixture may use the transformed player for the nonhuman case, so the probe must not reject an actor merely because its skeleton/family is nonhuman.

## Logging

Use a dedicated bounded log:

`AttackDisplacementProbe.log`

Prefer pipe-delimited single-line records suitable for later search/processing.

Log startup identity and module-presence state once.

Flush after START/END records so a short test remains recoverable.

Avoid large repetitive logging.

## Compatibility constraints

The intended runtime fixture keeps these active:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
Script_AttackDisplacementProbe.dll
```

The probe must not require changing or disabling the accepted production stack.

New Balance project pin:

`references/jackydima-gothic3sdk @ 316d32406a133f8884e7e302752c35f66b4f54fc`

The probe must observe **after** New Balance's compatible vector policy, not compete with it.

## Build policy

This implementation task is source-only.

Do not build, deploy, run Gothic 3, create logs, or modify runtime files.

## Static review before commit

Check:
- only allowed files changed;
- exact hook RVAs and ABI match the tested build;
- both hooks are observational/pass-through;
- no production source changed;
- no global Speed/GetAniName/CombatMove hook added;
- no New Balance/AttackCollision hook;
- no behavior mutation;
- no unbounded logging/state;
- `git diff --check` on the implementation delta.

## Commit/publish

If the bounded source implementation passes its own static audit:
- commit/push to `development`;
- report exact commit SHA;
- report changed files;
- report hook/ABI facts;
- report build as **NOT ATTEMPTED — not authorized**;
- STOP for independent Normal Chat review.

## Stop conditions

STOP without implementation if:
- `+0x16B8B7` cannot expose the final compatible vector safely;
- `+0x169819` cannot delimit the corresponding interval and a materially broader hook would be required;
- coexistence with New Balance at `+0x16B8A9` is not statically safe;
- the required observation would need production-source or Collision changes.


## Cancellation — EV-435

The proposed probe was cancelled before implementation.

Reason:
- its primary question (whether CombatMove movement corresponds to the value-carrying attack phase and drives actor travel subject to native stopping) had already been established through longstanding User animation-authoring/runtime observations;
- EV-434 independently closed the low-level native/New Balance vector mechanism;
- repeating those facts would spend runtime/review effort without deciding the remaining product semantic.

No probe source was created. No build/deploy/runtime occurred.

The active research now proceeds directly to architecture semantics: what configured value `1.0` means in the presence of New Balance's replacement movement policy, and how Off/native-authored/compatible behavior should relate.

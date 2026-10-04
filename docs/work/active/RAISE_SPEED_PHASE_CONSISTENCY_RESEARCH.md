# Raise / Speed Phase Consistency Research

**Status:** ACTIVE  
**Branch:** `development`  
**Opened:** 2026-10-04  
**Evidence trigger:** EV-414  
**Mode:** NORMAL CHAT — bounded static/causal research only

## Purpose

Resolve the phase-speed inconsistency discovered during Raise acceptance before any further production implementation or assembled regression.

The accepted authoring model is not under reconsideration:

```text
one user-facing <Attack>_BaseSpeed
-> authors the attack consistently across Raise / Hit / Recover where those phases exist
-> preserves Gothic/New Balance phase-specific relative bases and contextual modifiers
-> uses a common nominal Blender timing/frame convention
```

No separate `RaiseSpeed` is planned unless later evidence proves one unavoidable. Current research should first satisfy ADR-0008 §6: establish the factual cause and find the smallest correction.

## Protected accepted state

Do not reopen or redesign:

- Collision behavior/lifecycle absent contradictory collision evidence;
- resolved animation-set profile identity / ADR-0011;
- Hit-side caller composition architecture `compatible * (C / B_hit)`;
- factual Quick Action4/5 selection;
- Sprint -> Power Speed-profile inheritance on the proven shared route;
- AddRaise sequencing/continuation already accepted by EV-411–EV-412;
- New Balance compatible-owner preservation principle.

Do not add:

- a `RaiseSpeed` or `ReferenceRaiseBaseSpeed` public key;
- a global final-speed override;
- a second physical `sAICombatMoveInstr` hook;
- a copied New Balance multiplier table;
- route-specific C++ weapon branches.

## Runtime contradiction to explain

At extreme authored `BaseSpeed=0.1`:

| Attack / phase route | Observed Raise behavior |
|---|---|
| Normal custom AddRaise | Raise did not follow authored speed |
| Quick custom AddRaise | Raise did not follow authored speed |
| Whirl custom AddRaise | Raise did not follow authored speed |
| Power native Raise | Raise did not follow authored speed |
| Hack native Raise | Raise followed authored speed |
| Pierce native Raise | Raise followed authored speed |

Hit/visible Recover followed the configured authored speed in the tested controls.

The approximately 0–10-frame custom Raise assets were intentionally made **longer** than the earlier approximately 0–3-frame Raise assets to make relative speed differences easier to see.

## Established static facts

### Custom AddRaise

Current `AttackRaise.cpp` creates Normal, Quick and Whirl Raise CombatMoves with:

```cpp
AniSpeedScale = 1.0f
```

The tested Game binary proves this field participates in timing:

```text
sAICombatMoveStart
Game+0x16B422  reads args +0x10 / AniSpeedScale
Game+0x16B42E  stores it to active SPU +0x160
Game+0x16B57B  uses request scale in motion-time division
```

Therefore the hard-coded `1.0` is part of the non-coupling cause.

### Power

Power has distinct live speed-policy calls:

```text
Script_Game+0x47D51 = Action2 / Raise
Script_Game+0x47F6C = Action2 / Hit
```

Production G3AB currently composes only the Hit caller.

Pinned New Balance also has phase-specific Power policy:

```text
Power Raise -> 1.5 * compatible multiplier for ordinary Hero route
Power Hit   -> normal action/loadout result (commonly 1.0 * multiplier)
```

So Power Raise must not simply be replaced with the Hit value.

### Hack / Pierce

Runtime shows Hack and Pierce already propagate the authored attack speed across their visible Raise phase.

That behavior is a protected positive control. Any correction that blindly applies the authoring ratio to every Raise risks double-applying those routes.

## Candidate invariant

Where a phase has an independently computed compatible Raise result:

```text
B_hit = factual native Hit reference base
C     = configured authored attack BaseSpeed
R     = C / B_hit

configuredRaise = compatibleRaise * R
```

This is the desired **relationship**, not yet a frozen transport.

It means native/live phase differences survive. Example:

```text
Power compatible Raise = 1.5 * M
Power B_hit             = 1.0
Power configured C      = 0.1

configured Raise = 1.5 * M * 0.1
```

The same authoring ratio applies on top of the live Raise result rather than flattening Raise to Hit.

## Research questions

Close these in order.

### R1 — Native route map

For every current configured attack family that can execute Raise, determine whether Raise:

1. has its own factual `GetAnimationSpeedModifier` consumer;
2. reuses a speed chosen for the attack state/Hit;
3. is custom-inserted by G3AB;
4. does not exist / is irrelevant.

At minimum resolve:

```text
Normal
Quick
Power
Pierce
Hack
SimpleWhirl
Whirl
Sprint/shared Power route where relevant
```

### R2 — Custom AddRaise scale semantics

Prove the smallest safe way for custom Normal/Quick/Whirl Raise to receive the attack authoring ratio while preserving Gothic/New Balance's own phase behavior.

Determine whether setting the CombatMove `AniSpeedScale` to the profile ratio is sufficient and compositional, or whether the live Raise speed result must be queried/composed explicitly first.

Do not infer this solely from the field name.

### R3 — Power independent Raise consumer

Determine whether the existing caller-side Speed thunk can safely extend to the factual Power Raise caller `+0x47D51` and compose the live result by the same attack authoring ratio.

Requirements:

- call the live `+0x42A0` owner exactly once;
- retain Action2 + Raise factual identity;
- preserve New Balance/Gothic Raise-specific `M`;
- avoid affecting unconfigured profiles;
- preserve Sprint facts on the already-proven shared route.

### R4 — Already-coupled Hack / Pierce

Establish why their Raise follows authored speed and ensure the correction leaves this path untouched unless evidence shows a real gap.

### R5 — Smallest production correction

Only after R1–R4 close, freeze the minimum source boundary.

Prefer reuse of the existing `AttackSpeed` authoring-ratio policy rather than duplicating profile math in `AttackRaise`.

## Static-first rule

Do not request another broad gameplay sweep while static evidence can answer the causal question.

A focused diagnostic/probe is justified only for a specific unresolved transport fact that static source/binary evidence cannot settle.

## Acceptance target after correction

Use obvious contrasting values such as neutral/default and an extreme slow control.

Require:

```text
Normal custom Raise + Hit + Recover = one coherent authored-speed relationship
Quick R/L custom Raise + Hit + Recover = coherent
Whirl custom Raise + Hit + Recover = coherent
Power native Raise retains native/live relative Raise-vs-Hit relationship while authored BaseSpeed scales both
Hack/Pierce remain correct and are not double-scaled
native stack = PASS
intended New Balance stack = PASS
unconfigured profiles = unchanged/fail-closed
```

## Stop conditions

Stop and preserve the exact fixture if a correction causes:

- double-scaled Hack/Pierce;
- loss of New Balance contextual modifiers;
- wrong Quick R/L behavior;
- changed AddRaise continuation semantics;
- Sprint/Power alias regression;
- unconfigured profile intervention;
- collision/lifecycle regression.

## Closure

This research closes only when the exact causal map and smallest implementation boundary are frozen.

Then prepare a separate bounded Work implementation contract. Do not implement production source from this research document directly.

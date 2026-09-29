# ADR-0009 — Sprint Inherits the Power Speed Profile

**Status:** Accepted  
**Date:** 2026-09-29  
**Related:** ADR-0004, ADR-0008, `docs/work/active/SPEED_EXPANDED_ATTACK_SCOPE_AND_GROUPED_PROFILE_IMPLEMENTATION.md`

## Context

ADR-0008 deliberately deferred Sprint / `gEAction_SprintAttack` / Action9 because static analysis had not yet proved its effective Hit-speed transport. The independent expanded-Speed review then found a specific ambiguity at the Power Hit caller `Script_Game+0x47F6C`: earlier code in the same routine recognizes current Action9, while the later speed call hard-sets `EAX=2` / Power.

A bounded diagnostics-only probe was therefore run at `Script_Game+0x47F6C` while leaving the live compatible speed result unchanged.

Runtime evidence now establishes the factual route.

## Evidence

### Goblin / equipped 1H

Repeated BlackGoblin Sprint observations showed:

```text
PassedAction=2
CurrentActionBefore=9
RequestedPhase=Hit
CurrentActionAfter=9
CurrentMovementAni=Goblin_..._PowerAttack_...
CompatibleSpeed=1.000000
```

An ordinary BlackGoblin Power observation in the same run used current Action2 and the same compatible base `1.000000`.

### Troll / Fist

Repeated BlackTroll Sprint observations showed:

```text
PassedAction=2
CurrentActionBefore=9
RequestedPhase=Hit
CurrentActionAfter=9
CurrentMovementAni=Troll_..._PowerAttack_...
CompatibleSpeed=1.500000
```

Ordinary BlackTroll Power observations in the same run used current Action2 and the same compatible base `1.500000`.

### Sabertooth / Fist

Repeated Sabertooth Sprint observations showed:

```text
PassedAction=2
CurrentActionBefore=9
RequestedPhase=Hit
CurrentActionAfter=9
CurrentMovementAni=Sabertooth_..._PowerAttack_...
CompatibleSpeed=1.000000
```

Transformed-player Sabertooth Power observations used current Action2 and the same compatible base `1.000000`.

### Zombie-family control

Mummy/Zombie Power calls reached the same caller with current Action2 and Power-named animations. No factual Action9 Sprint event was observed for that control. This is a Power-route control only; it neither proves nor disproves Sprint availability for Hero-derived/Zombie families.

## Decision

For Speed authoring, Sprint is **not** a separate user-facing attack profile.

Sprint factually remains Action9 in actor state, but its proven Hit-speed application is transported through the shared Power caller with passed Action2 and a Power-named animation. On the tested Goblin, Troll, and Sabertooth families, Sprint and ordinary Power also share the same factual compatible Hit base within each family.

Therefore:

```text
Power_ReferenceHitBaseSpeed
Power_BaseSpeed
```

own the playback timing for both:

```text
ordinary Power Hit
Sprint Hit using the shared Power animation/speed route
```

Do not add:

```text
Sprint_ReferenceHitBaseSpeed
Sprint_BaseSpeed
```

unless future contradictory evidence proves a materially separate authoring/timing route.

No new Action9 mapping is needed in `AttackSpeed`. The shared caller already supplies Action2, and the existing Power composition is the intended behavior on that route.

## Compatibility rule

The live compatible owner must still receive the original caller action exactly as Gothic supplied it:

```text
caller EAX=2
-> live Script_Game+0x42A0 / New Balance owner receives EAX=2
-> compatible speed is returned
-> G3AB applies the configured Power C/B composition when a valid Power profile exists
```

Do not rewrite the compatible owner's input from Action2 to Action9.

## Consequences

- The Work review's Sprint/Power non-interference blocker is resolved by runtime evidence, but the resolution is intentional **Power timing inheritance**, not Sprint suppression.
- The grouped INI stays simpler and more faithful to the animation-authoring model.
- The existing expanded production source at `642c88a4e6244ae7377ba835507750af7914e2f5` requires no code change for this Sprint timing behavior.
- ADR-0008 section 4 and its Sprint-specific fail-closed wording are superseded by this ADR.
- Collision may continue to treat Sprint as a distinct factual family where collision lifecycle semantics require it; this ADR concerns Speed authoring only.
- Raise remains paused until expanded Speed runtime acceptance closes.

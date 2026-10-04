# ADR-0008 — Grouped Loadout Profiles and Expanded Attack Scope

**Status:** Accepted  
**Date:** 2026-09-29  
**Related:** ADR-0004, ADR-0005, ADR-0006, ADR-0007, `docs/ANIMATION_RULES.md`

**Current Raise qualification — 2026-10-04:** Speed is closed. The dormant `<Attack>_RaiseOverride` spelling below is superseded for player-facing configuration by the additive keys `Normal_AddRaise`, `Quick_AddRaise`, and `Whirl_AddRaise`. `On` asks G3AB to insert the matching Gothic Raise before Hit; `Off`/missing adds nothing and never disables native Raise. Do not expose native-Raise attack switches merely for symmetry. See `docs/work/active/RAISE_GENERIC_COMBATMOVE_RESEARCH.md`.

**Current qualification — partial supersession:** The seven-prefix grouped-profile decision remains current. Its Sprint-deferral/fail-closed wording (§§4, 9 and consequences) is superseded by [ADR-0009](ADR-0009-sprint-inherits-power-speed-profile.md): Sprint has no separate key/profile and inherits Power on the proven shared route. [ADR-0011](ADR-0011-resolved-animation-set-speed-profile-identity.md) now owns grouped profile identity: request-time resolved animation-family/tokens select the profile. ADR-0010 is superseded. Other fail-closed rules remain valid.

The historical decision body below is preserved.

## Context

The first production Speed v2 implementation deliberately proved the architecture with Normal and Quick attacks only. Runtime acceptance established that:

- generic family/use-type profile matching works;
- one profile applies across concrete P0/P1/P2/P3 animation variants;
- caller-side compatible composition can author a configured base speed while preserving New Balance contextual modifiers.

After that proof, the product scope was deliberately revisited before Speed closure. The framework is intended to improve attack-animation authoring generally, not only Normal and Quick. The User also identified that one-section-per-attack becomes difficult to scan once many attack types and animation families are configured.

A second authoring requirement is equally important: Normal and Quick attacks do not normally use a Raise phase in Gothic 3, but the framework is intended to allow short authored Raise animations for such attacks. This permits fuller Hit animations and more consistent authoring ranges across 1H, 2H, Staff and other families. Raise behavior remains a later feature under ADR-0006; this ADR only freezes the shared configuration shape and the principle that no separate Raise-speed mechanism is added unless runtime evidence proves it necessary.

## Decision

### 1. One section represents one animation-family/loadout identity

The user-facing section groups all configured attack types for the same stable loadout identity:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
```

Example:

```ini
[Profile.Hero_None_1H]
AnimationFamily=Hero
LeftAnimationUseType=None
RightAnimationUseType=1H

Normal_ReferenceHitBaseSpeed=0.60
Normal_BaseSpeed=1.00
Normal_RaiseOverride=On

Quick_ReferenceHitBaseSpeed=1.00
Quick_BaseSpeed=1.00
Quick_RaiseOverride=On

Power_ReferenceHitBaseSpeed=1.00
Power_BaseSpeed=1.00
Power_RaiseOverride=Off

Pierce_ReferenceHitBaseSpeed=1.00
Pierce_BaseSpeed=1.00
```

The text after `Profile.` remains an author-facing label only. Runtime identity comes from the explicit fields.

This supersedes ADR-0007's one-section-per-ActionProfile layout.

### 2. Attack type is an attack-specific key prefix, not part of the section identity

Each supported attack type owns an optional set of prefixed keys inside the loadout section:

```text
<Attack>_ReferenceHitBaseSpeed
<Attack>_BaseSpeed
<Attack>_RaiseOverride
```

Examples:

```text
Normal_...
Quick_...
Power_...
Pierce_...
Hack_...
SimpleWhirl_...
Whirl_...
```

A missing attack block means G3AB does not intervene for that attack and the live Gothic/compatible result remains authoritative.

`BaseSpeed` remains the desired authored base `C`. `ReferenceHitBaseSpeed` remains factual calibration `B` required by the caller-side composition mechanism.

### 3. Expanded first Speed scope

Static analysis of the pinned tested Script_Game binary establishes factual Hit-speed consumers for these user-facing attack types:

```text
Normal
Quick
Power
Pierce
Hack
SimpleWhirl
Whirl
```

Factual engine actions:

```text
Normal      -> gEAction_Attack        / Action1
Quick       -> gEAction_QuickAttackR  / Action4
               gEAction_QuickAttackL  / Action5
Power       -> gEAction_PowerAttack   / Action2
SimpleWhirl -> gEAction_SimpleWhirl   / Action6
Whirl       -> gEAction_WhirlAttack   / Action10
Pierce      -> gEAction_PierceAttack  / Action11
Hack        -> gEAction_HackAttack    / Action14
```

Newly established direct Hit consumers on the tested build are:

```text
Power Hit:
  Script_Game+0x47F6C

Pierce Hit:
  Script_Game+0x47328
  Script_Game+0x4770F
  Script_Game+0x4786F

Hack Hit:
  Script_Game+0x42FF4
  Script_Game+0x431B4
  Script_Game+0x432EB

SimpleWhirl Hit:
  Script_Game+0x4C6FA

Whirl Hit:
  Script_Game+0x4DF1F
```

The already-proven Normal/Quick six-site caller set remains unchanged.

Power also has a distinct factual Raise-speed consumer at `Script_Game+0x47D51`. That is evidence for later Raise work, not authorization to begin Raise behavior while Speed remains open.

### 4. Sprint is explicitly deferred pending factual speed-route proof

`gEAction_SprintAttack` / Action9 exists and is queried by Gothic's combat/pose-selection paths, but the completed direct-caller analysis has not established a distinct Action9 Hit consumer of `Script_Game+0x42A0`.

Sprint also reuses Power-named animation assets in observed gameplay, but animation-file reuse is not sufficient evidence that Sprint should share Power's Speed profile or transport.

Therefore this ADR does **not** expose `Sprint_BaseSpeed` yet.

```text
Sprint remains native/compatible
until its factual speed application route is proven.
```

If later static or runtime evidence proves a safe route, Sprint can be added as another attack prefix without redesigning the grouped schema.

### 5. Compatible composition remains unchanged

For every supported Hit route:

```text
compatible = B_hit * M
configured = compatible * (BaseSpeed / ReferenceHitBaseSpeed)
           = BaseSpeed * M
```

G3AB must compose with the live compatible result. It must not copy New Balance's contextual policy or assume that every action uses the same multiplier set.

The pinned New Balance implementation demonstrates why this distinction matters: some actions multiply a contextual factor, while others such as its current Whirl and Sprint branches return fixed action speeds. G3AB preserves whatever the live compatible owner returns and changes only the configured base relationship.

### 6. One desired speed per attack; no separate Raise speed unless evidence requires it

The author-facing model stays simple:

```text
<Attack>_BaseSpeed = desired attack playback base
```

If later `RaiseOverride=On` inserts a Raise phase for that attack, the first implementation must test whether Gothic/the existing Speed path naturally keeps Raise timing consistent with the attack's configured `BaseSpeed`.

Do not add a separate user-facing `RaiseBaseSpeed`, `RaiseSpeed`, or extra Raise-speed composition mechanism pre-emptively.

The rule is:

```text
request/insert Raise using the smallest existing Gothic mechanism
-> test whether Raise naturally follows the configured attack speed
-> if yes: add no more code
-> if no: establish the factual cause and implement only the smallest correction
```

This supersedes ADR-0007's assumption that `ReferenceRaiseBaseSpeed` must be part of the initial shared profile schema.

### 7. RaiseOverride remains configuration data while Raise behavior is paused

`<Attack>_RaiseOverride=On|Off` may be represented by the grouped profile parser so the shared schema does not need redesign later.

During the Speed-only phase:

```text
RaiseOverride may be parsed/stored
but must not activate new Raise behavior.
```

Normal and Quick are intentionally allowed to request Raise later even though Gothic normally does not use Raise for those attacks. The goal is to let authors provide correctly named short Raise assets while Gothic continues to resolve concrete animation variants.

### 8. Recover remains derived

There is still no independent Recover speed control. Recover follows the effective Hit behavior already established by the earlier Speed architecture.

### 9. Fail-closed behavior remains mandatory

For any loadout or attack block:

```text
missing/invalid loadout identity
-> ignore section

missing attack BaseSpeed
-> no G3AB Speed intervention for that attack

BaseSpeed present + missing/invalid ReferenceHitBaseSpeed
-> no G3AB Speed intervention for that attack

unsupported/unproven factual action, including Sprint for now
-> return the live compatible result unchanged

duplicate normalized loadout identity
-> ambiguous; no G3AB intervention for that identity
```

## Consequences

- The public INI becomes substantially easier to scan when many families/loadouts and attack types are configured.
- Adding another proven attack type does not require another top-level profile section.
- Normal/Quick remain the already-runtime-proven baseline; additional attack types require implementation/static review/build/runtime acceptance before Speed closes.
- Sprint remains explicitly unsupported by G3AB Speed until factual transport evidence exists.
- Raise behavior remains paused under ADR-0006.
- No extra Raise-speed complexity is authorized without runtime evidence that the inserted Raise fails to follow the intended attack timing.

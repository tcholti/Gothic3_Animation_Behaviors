# Gothic 3 Native Collision Cleanup Call-Site Map

**Status:** Runtime-confirmed reverse-engineering map for the current tested build  
**Date:** 2026-08-26  
**Scope:** Native/unmarked player melee cleanup observations from Step B4/B4b

## Purpose

This document records the native `Script_Game.dll` call sites that reset an equipped offensive weapon from `Item_Attack` (`7`) to `Item_Equipped` (`5`).

The addresses below are **return-address RVAs immediately after the call to the imported `Entity::SetCollisionGroup` operation**. They are build-specific and must be reverified for another binary build.

The map exists for two reasons:

1. preserve durable reverse-engineering knowledge instead of leaving it only in raw logs/chat;
2. help identify a universal post-native-cleanup opportunity without hard-wiring production behavior to every attack family.

## Runtime Evidence

Primary logs:

- `research/raw/2026-08-26_stepB4_native_cleanup_callsite_probe.log`
- `research/raw/2026-08-26_stepB4b_native_manyattacks_cleanup_callsite.log`
- `research/raw/2026-08-26_stepB4b_native_finishing_blow_cleanup_callsite.log`
- `research/raw/2026-08-26_stepB4b_native_interruption_cleanup_callsite.log`

The B4 diagnostic records only exact player-equipped source transitions satisfying:

```text
requested = Item_Equipped (5)
before    = Item_Attack   (7)
after     = Item_Equipped (5)
```

All observed records resolved to `Script_Game.dll`.

## Action-Specific Cleanup Call Sites

| Native action | Action value | Observed RIGHT cleanup RVA | Observed LEFT cleanup RVA | Runtime note |
|---|---:|---:|---:|---|
| `gEAction_Attack` | 1 | `Script_Game + 0x3851A` | `Script_Game + 0x3854E` | Normal-family cleanup across tested 2H, Staff, 1H, Shield+1H and Dual cases. |
| `gEAction_PowerAttack` | 2 | `Script_Game + 0x4809D` | `Script_Game + 0x480E4` | Includes tested Dual both-source Power cleanup. |
| `gEAction_QuickAttackR/L` | 4 / 5 | `Script_Game + 0x48794` | `Script_Game + 0x487CC` | Same Quick cleanup path across tested weapon families. Generic action 3 was not observed in these B4/B4b runs. |
| `gEAction_SimpleWhirl` | 6 | `Script_Game + 0x4C828` | `Script_Game + 0x4C858` | Dual SimpleWhirl uses separate LEFT/RIGHT branches. |
| `gEAction_WhirlAttack` | 10 | `Script_Game + 0x4E03C` | not observed | Tested full 2H/Staff Whirl cleanup used RIGHT. |
| `gEAction_PierceAttack` | 11 | `Script_Game + 0x477E3` | `Script_Game + 0x4781C` | Source branch follows equipped damaging source, including Dual evidence. |
| `gEAction_HackAttack` | 14 | `Script_Game + 0x432BC` | not observed | Tested 2H block-breaking/heavy use of the serialized `FinishingAttack` motion. |
| `gEAction_FinishingAttack` | 15 | `Script_Game + 0x4178A` | `Script_Game + 0x417C2` | Tested actual finishing blows, including 1H/Dual source variants. |
| `gEAction_GetUpAttack` | 30 | `Script_Game + 0x41E10` | not observed | Tested knockdown/get-up attack cleanup. |

### Important filename/action result

The exact 2H serialized motion:

```text
Hero_Parade_None_2H_P0_FinishingAttack_Hit_N_Fwd_00_%_00_P1_100.xmot
```

was observed under two different native actions:

```text
gEAction_HackAttack      (14)
gEAction_FinishingAttack (15)
```

and the cleanup call site changed with the action:

```text
HackAttack      -> Script_Game + 0x432BC
FinishingAttack -> Script_Game + 0x4178A
```

This is direct evidence that the serialized animation filename is not sufficient behavioral authority. The native action semantics select different lifecycle code even when the same motion asset is used.

## Separate Interruption Cleanup Path

B4b also identified:

```text
Script_Game + 0x24AFF
```

as a separate native weapon-reset call site during tested combat interruptions.

Representative chronology:

```text
Routine still reports original Attack / Hit
weapon cleanup 7 -> 5 at Script_Game + 0x24AFF
~5 ms later PrimaryFirst is replaced by Stumble / knockdown motion
```

This path was observed repeatedly across Staff, 1H and 2H interruption cases.

Engineering interpretation:

- Gothic 3 already contains a distinct interruption cleanup path;
- normal action completion and damage/reaction interruption therefore do not rely on one single Script_Game cleanup function;
- the known block-skip failure can bypass the normal action cleanup path and also fail to receive this interruption cleanup, leaving the source stale at group 7.

Do **not** infer from `0x24AFF` alone that every possible interruption shares this exact call site. It is confirmed for the tested interruption matrix only.

## Relationship to Step B3

Step B3 established that `gCScriptProcessingUnit::sAICombatMoveStartRecover` is **not** the post-cleanup boundary:

```text
StartRecover BEGIN
Recover transition / motion handling
StartRecover END
native Script_Game SetCollisionGroup(5)
```

B4/B4b now show that the later cleanup is performed from action-specific Script_Game paths rather than one universal cleanup call site.

For example:

```text
Normal       -> +0x3851A / +0x3854E
Quick        -> +0x48794 / +0x487CC
Power        -> +0x4809D / +0x480E4
Pierce       -> +0x477E3 / +0x4781C
SimpleWhirl  -> +0x4C828 / +0x4C858
Whirl        -> +0x4E03C
Hack         -> +0x432BC
Finishing    -> +0x4178A / +0x417C2
GetUpAttack  -> +0x41E10
```

## Related Step-B Runtime Hook / RVA Reference

These addresses were established or exercised during the same lifecycle research and are preserved here because several are internal/runtime points not fully represented by the public SDK. They are **tested-build-specific**.

| Area | Tested symbol / purpose | Module + RVA | Evidence / confidence |
|---|---|---:|---|
| PrimaryFirst high-level play | `eCVisualAnimation_PS::PlayMotion` | `Engine + 0x30860` | Runtime-hooked in B1; immediate type-0 acquisition/replacement signal in controlled tests. |
| PrimaryFirst high-level stop | `eCVisualAnimation_PS::StopMotion` | `Engine + 0x30980` | Runtime-hooked in B1. |
| Wrapper motion play | `eCWrapper_emfx2Actor::PlayMotion` | `Engine + 0x476F0` | Tested binary/export reference; high-level PlayMotion delegates into wrapper path. |
| Wrapper motion stop | `eCWrapper_emfx2Actor::StopMotion` | `Engine + 0x47910` | Tested binary/export reference. |
| High-level loop-end request | `eCVisualAnimation_PS::StopAtLoopEnd` | `Engine + 0x309D0` | Source/binary inspection; schedules future loop stop, not actual motion-end event. |
| Wrapper loop-end request | `eCWrapper_emfx2Actor::StopAtLoopEnd` | `Engine + 0x479C0` | Source/binary inspection. |
| CombatMove Recover start | `gCScriptProcessingUnit::sAICombatMoveStartRecover` | `Game + 0x16E360` | Runtime-hooked in B3; begins Recover transition but returns before native weapon cleanup. |
| CombatMove iterative loop | `gCScriptProcessingUnit::sAICombatMoveItlLoop` | `Game + 0x16DD00` | Tested binary export/source declaration; deliberately not hooked yet because it may be a broad update loop. |
| CombatMove instruction | `gCScriptProcessingUnit::sAICombatMoveInstr` | `Game + 0x1696E0` | Tested binary export/source declaration. |
| CombatMove start | `gCScriptProcessingUnit::sAICombatMoveStart` | `Game + 0x16ABB0` | Tested binary export/source declaration. |
| Entity collision group | `eCEntity::SetCollisionGroup` | `Game + 0x225660` | Existing research hook; B4 captures native caller return addresses from this wrapper entry. |

Production code must not assume these addresses are stable across another Gothic 3 build. Revalidate against the binary reference and runtime before reuse.

## Binary-Reference Confirmation

The tested `Script_Game.dll` disassembly confirms that these RVAs correspond to code immediately following calls that pass collision group `5` to the imported entity collision-group setter.

Examples already inspected:

- Normal RIGHT: call ending at `Script_Game + 0x3851A`;
- Normal LEFT: call ending at `Script_Game + 0x3854E`;
- Quick RIGHT: call ending at `Script_Game + 0x48794`;
- Quick LEFT: call ending at `Script_Game + 0x487CC`;
- Finishing RIGHT: call ending at `Script_Game + 0x4178A`;
- interruption reset: call ending at `Script_Game + 0x24AFF`.

The current binary reference is:

`tcholti/Gothic3_Binary_Reference/builds/current_tested/modules/Script_Game/`

## Architectural Consequence

B4/B4b argue **against** a production design that hooks one cleanup function per attack family.

That would create a growing family matrix:

```text
Normal cleanup hook
Quick cleanup hook
Power cleanup hook
Pierce cleanup hook
SimpleWhirl cleanup hook
Whirl cleanup hook
Hack cleanup hook
Finishing cleanup hook
GetUp cleanup hook
interruption cleanup hook
...
```

The desired production rule remains execution-level:

> Follow a real offensive Hit execution. When that exact Hit reaches an end/replacement transition, allow Gothic 3 its normal cleanup opportunity; after that opportunity, if cleanup is still absent, repair the stale offensive collision.

This wording is deliberate: B1 proved that the successor PrimaryFirst `PlayMotion` can occur slightly **before** Gothic 3 performs its normal `7 -> 5` cleanup. Replacement detection alone is therefore not yet the post-opportunity repair boundary.

The action-specific call sites are evidence about **what native success looks like**, not a proposed list of production hooks.

## Current Open Question

The next useful reverse-engineering question is:

> Do these action-specific Script_Game cleanup functions converge on a common caller/dispatcher/CombatMove boundary after their native cleanup opportunity?

A narrow next diagnostic should prefer extending the existing cleanup probe to capture a short caller stack or another causal parent boundary before defaulting to separate family hooks or broad Script `OnTick` polling.

## Untested / Not Yet Claimed

This map does not claim coverage for every `gEAction` combat enum. In particular, the B4/B4b runs did not establish a cleanup call site for every possible SprintAttack, JumpAttack, RamAttack, generic Quick/action 3, monster/body attack, or other specialized action.

The current map is intentionally evidence-bounded.

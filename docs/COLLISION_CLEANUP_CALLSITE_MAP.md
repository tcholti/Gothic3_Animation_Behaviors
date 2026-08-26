# Gothic 3 Native Collision Cleanup Call-Site Map

**Status:** Runtime-confirmed reverse-engineering map for the current tested build  
**Date:** 2026-08-26  
**Scope:** Native/unmarked player melee cleanup observations from Step B4/B4b/B5

## Purpose

This document records the native call sites and higher stack paths that reset an equipped offensive weapon from `Item_Attack` (`7`) to `Item_Equipped` (`5`).

The Script_Game addresses below are **return-address RVAs immediately after the call to the imported entity collision-group setter**. B5 adds the higher captured stack frames. All addresses are build-specific and must be reverified for another binary build.

The map exists to:

1. preserve durable reverse-engineering knowledge instead of leaving it only in raw logs/chat;
2. identify the narrowest post-native-cleanup opportunity without hard-wiring production behavior to every attack family.

## Runtime Evidence

Primary logs:

- `research/raw/2026-08-26_stepB4_native_cleanup_callsite_probe.log`
- `research/raw/2026-08-26_stepB4b_native_manyattacks_cleanup_callsite.log`
- `research/raw/2026-08-26_stepB4b_native_finishing_blow_cleanup_callsite.log`
- `research/raw/2026-08-26_stepB4b_native_interruption_cleanup_callsite.log`
- `research/raw/2026-08-26_stepB5_cleanup_parent_stack_probe.log`

The B4/B5 diagnostic records only exact player-equipped source transitions satisfying:

```text
requested = Item_Equipped (5)
before    = Item_Attack   (7)
after     = Item_Equipped (5)
```

All observed immediate native cleanup callers resolved to `Script_Game.dll`.

## Action-Specific Cleanup Call Sites

| Native action | Action value | Observed RIGHT cleanup RVA | Observed LEFT cleanup RVA | Runtime note |
|---|---:|---:|---:|---|
| `gEAction_Attack` | 1 | `Script_Game + 0x3851A` | `Script_Game + 0x3854E` | Normal-family cleanup across tested 2H, Staff, 1H, Shield+1H and Dual cases. |
| `gEAction_PowerAttack` | 2 | `Script_Game + 0x4809D` | `Script_Game + 0x480E4` | Includes tested Dual both-source Power cleanup. |
| `gEAction_QuickAttackR/L` | 4 / 5 | `Script_Game + 0x48794` | `Script_Game + 0x487CC` | Same Quick cleanup path across tested weapon families. Generic action 3 was not established in these runs. |
| `gEAction_SimpleWhirl` | 6 | `Script_Game + 0x4C828` | `Script_Game + 0x4C858` | Dual SimpleWhirl uses separate LEFT/RIGHT branches. |
| `gEAction_WhirlAttack` | 10 | `Script_Game + 0x4E03C` | not observed | Tested full 2H/Staff Whirl cleanup used RIGHT. |
| `gEAction_PierceAttack` | 11 | `Script_Game + 0x477E3` | `Script_Game + 0x4781C` | Source branch follows equipped damaging source, including Dual evidence. |
| `gEAction_HackAttack` | 14 | `Script_Game + 0x432BC` | not observed | Tested standing/block-breaking heavy use of the serialized `FinishingAttack` motion. |
| `gEAction_FinishingAttack` | 15 | `Script_Game + 0x4178A` | `Script_Game + 0x417C2` | Tested true finishing blows in B4b, including 1H/Dual source variants. |
| `gEAction_GetUpAttack` | 30 | `Script_Game + 0x41E10` | not observed | Tested knockdown/get-up attack cleanup. |

## Filename vs Action — Direct Runtime Evidence

The exact 2H serialized motion:

```text
Hero_Parade_None_2H_P0_FinishingAttack_Hit_N_Fwd_00_%_00_P1_100.xmot
```

has been observed under different native action semantics.

B4b established:

```text
gEAction_HackAttack      (14) -> Script_Game + 0x432BC
gEAction_FinishingAttack (15) -> Script_Game + 0x4178A
```

B5 added a useful target-state case: an intended execution target stood up before the Hit. Gothic still played the `FinishingAttack_Raise` and `FinishingAttack_Hit` asset family, but the Hit/collision and StartRecover records were already `gEAction_HackAttack` (14). The B5 log does **not** establish an action-15 -> action-14 switch; the safe interpretation is that runtime action semantics selected Hack behavior while reusing the same serialized asset family.

Engineering consequence:

> Serialized animation filenames are selectors/assets, not sufficient behavioral authority. Native action semantics choose different lifecycle code even when the same motion resource is used.

## Separate Interruption Cleanup Path

B4b identified:

```text
Script_Game + 0x24AFF
```

as a separate native weapon-reset call site during tested combat interruptions.

Representative chronology:

```text
Routine still reports original Attack / Hit
weapon cleanup 7 -> 5 at Script_Game + 0x24AFF
~milliseconds later PrimaryFirst is replaced by Stumble / knockdown motion
```

This path was observed repeatedly across Staff, 1H and 2H interruption cases.

Engineering interpretation:

- Gothic 3 already contains a distinct legitimate interruption cleanup path;
- ordinary action completion and damage/reaction interruption do not rely on one single Script_Game cleanup function;
- the known block-skip failure can bypass the ordinary completion path and also fail to receive this interruption cleanup, leaving the source stale at group 7.

Do **not** infer from `0x24AFF` alone that every possible interruption shares this exact call site. It is confirmed for the tested interruption matrix only.

## Step B5 — Higher Parent-Stack Result

B5 captured up to 16 frames with Win32 `CaptureStackBackTrace` inside the existing `SetCollisionGroup` hook. In practice the relevant successful-cleanup stacks were short and highly structured.

### Ordinary action-completion cleanup

Across all ordinary action-specific cleanup records checked in the B5 sample, the stack was:

```text
FrameCollision wrapper
→ action-specific Script_Game cleanup return RVA
→ Game + 0x1605EB
```

Examples included Normal, Quick, Power, full Whirl, Pierce and Hack. The action-specific Script_Game frame changed; the Game frame remained `+0x1605EB`.

Binary-reference inspection shows `Game + 0x1605EB` is the return point immediately after an indirect call inside the Game function beginning at approximately:

```text
Game + 0x1604E0
```

The relevant end of that function is:

```text
Game + 0x1605EB  compare result after indirect call
...
Game + 0x1605FE / +0x160605 return paths
```

This is the strongest common parent found so far for ordinary successful melee completion cleanup.

### Legitimate damage/reaction interruption cleanup

The interruption stack remained different:

```text
FrameCollision wrapper
→ Script_Game + 0x24AFF
→ another Script_Game frame (varied in tested reactions, e.g. +0x235C7 / +0x227AD / +0x22D6D)
→ Game + 0x1604D3
```

Binary-reference inspection shows:

```text
Game + 0x1604D1  indirect call
Game + 0x1604D3  function epilogue/return
Game + 0x1604D8..+0x1604DF padding
Game + 0x1604E0  start of the ordinary sibling function
```

Thus B5 did **not** find one identical captured parent frame shared by successful completion and successful interruption. It found two adjacent sibling Game-level helper/dispatcher paths:

```text
interruption sibling: ends at Game + 0x1604D5
ordinary sibling:     begins at Game + 0x1604E0, common cleanup return at +0x1605EB
```

The adjacency is architecturally interesting, but it is not evidence that either function is a universal production cleanup boundary.

## Relationship to Step B3

Step B3 established that `gCScriptProcessingUnit::sAICombatMoveStartRecover` is **not** the post-cleanup boundary:

```text
StartRecover BEGIN
Recover transition / motion handling
StartRecover END
native Script_Game SetCollisionGroup(5)
```

B4/B4b/B5 now refine the later path:

```text
ordinary completion:
StartRecover returns
→ action-specific Script_Game cleanup
→ common ordinary Game sibling
```

while legitimate reaction interruption can use the separate `+0x24AFF` route and interruption Game sibling.

## Related Step-B Runtime Hook / RVA Reference

These addresses were established or exercised during the same lifecycle research and are **tested-build-specific**.

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
| Entity collision group | `eCEntity::SetCollisionGroup` | `Game + 0x225660` | Existing research hook; B4/B5 capture native caller and stack facts from this wrapper entry. |
| Ordinary cleanup parent helper | unidentified internal Game function | `Game + 0x1604E0` | B5 runtime stack + binary inspection; ordinary action cleanup returns at `+0x1605EB`. |
| Interruption cleanup parent helper | unidentified preceding internal Game function | ends at `Game + 0x1604D5` | B5 runtime stack + binary inspection; tested interruption stack returns at `+0x1604D3`. |

Production code must not assume these addresses are stable across another Gothic 3 build. Revalidate against the binary reference and runtime before reuse.

## Marker-Bookkeeping Retirement Is a Separate Responsibility

Do not mistake `RetireMarkerOwnedSource()` for physical fallback cleanup.

The earlier v0.15/v0.16 problem was:

```text
marked source becomes offensive
→ attack interrupted before later authored marker
→ Gothic physically cleans source 7 -> 5
→ stale marker occurrence/execution record can survive
```

`RetireMarkerOwnedSource()` observes the already-performed source reset and may retire marker bookkeeping when that reset represents execution end. Intentional intra-Hit OFF or exact-set source switching removes/changes marker ownership before requesting group 5 so those authored transitions do not retire the whole execution.

A future exact Hit-lifetime authority may replace this inference, but physical cleanup and marker-record retirement must remain conceptually distinct until then.

## Architectural Consequence

B4/B4b/B5 argue strongly **against** a production design that hooks one cleanup function per attack family.

That would create a growing matrix of Normal, Quick, Power, Pierce, SimpleWhirl, Whirl, Hack, Finishing, GetUp and interruption cleanup hooks.

The desired production rule remains execution-level:

> Follow a real offensive Hit execution. When that exact Hit reaches a genuine end/replacement transition, allow Gothic 3 its legitimate cleanup opportunity. After that opportunity, if cleanup is still absent, repair the stale offensive collision.

This wording is deliberate:

- B1 proved successor PrimaryFirst `PlayMotion` can happen before ordinary native cleanup;
- B4/B4b proved native success is split across multiple action/interruption paths;
- B5 found a common ordinary Game sibling but a separate adjacent interruption sibling.

Therefore none of the currently observed native cleanup callers should automatically become the production universal hook.

## Current Open Question

The next reverse-engineering question is:

> What calls/selects the adjacent Game cleanup sibling functions around `Game + 0x1604D3` and `Game + 0x1604E0..0x1605EB`, and is there a narrow event-driven boundary after either legitimate path has completed?

Inspect their callers/dispatch conditions first. Do not immediately hook both siblings merely because they are adjacent.

## Untested / Not Yet Claimed

This map does not claim coverage for every combat enum or actor/source type. In particular, generic Quick/action 3, SprintAttack, JumpAttack, RamAttack, monster/body attacks, Fist logical collision, and other specialized paths remain evidence-bounded.

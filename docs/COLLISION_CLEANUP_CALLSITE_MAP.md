# Gothic 3 Native Collision Cleanup Call-Site Map

**Status:** Runtime/static reverse-engineering reference for the current tested build  
**Updated:** 2026-09-01  
**Scope:** Native/unmarked player melee cleanup observations from Step B4/B4b/B5 plus later static parent identification

## Purpose

Preserve the exact tested native cleanup call sites, source branches, and higher script-dispatch paths without turning build-specific addresses into production architecture.

Use this file when searching by:

- native action;
- `Script_Game` cleanup RVA;
- `SetCollisionGroup`;
- `RunScriptFunction` / `RunScriptState` / `ProcessScript`;
- Step-B cleanup stack evidence.

Current lifecycle architecture is in `COLLISION_LIFECYCLE_PLAN.md`.

Superseded pre-information-architecture wording remains recoverable through Git history. Exact factual provenance routes through the EV entries and processed runtime logs below.

---

## 1. Evidence Basis

Primary processed runtime logs:

- `research/archive/2026-08-26_stepB4_native_cleanup_callsite_probe.log`
- `research/archive/2026-08-26_stepB4b_native_manyattacks_cleanup_callsite.log`
- `research/archive/2026-08-26_stepB4b_native_finishing_blow_cleanup_callsite.log`
- `research/archive/2026-08-26_stepB4b_native_interruption_cleanup_callsite.log`
- `research/archive/2026-08-26_stepB5_cleanup_parent_stack_probe.log`

Canonical evidence:

- EV-163 — action-specific native cleanup matrix;
- EV-164 — same serialized Finishing asset under different runtime actions;
- EV-165 — tested legitimate interruption cleanup route;
- EV-166 — B5 captured adjacent Game parents;
- EV-169 — parents identified as generic ScriptAdmin runners;
- EV-170 — common higher `ProcessScript()` dispatcher;
- EV-171 — callback ordering relative to main script dispatch;
- EV-172 — deferred finalization design hypothesis.

The B4/B5 diagnostic special record was gated to exact player-equipped transitions:

```text
requested = Item_Equipped (5)
before    = Item_Attack   (7)
after     = Item_Equipped (5)
```

All immediate native cleanup callers observed in that matrix resolved to `Script_Game.dll`.

---

## 2. Action-Specific Native Cleanup Return RVAs

The addresses below are **return-address RVAs immediately after the call to the imported entity collision-group setter** in the tested build.

| Native action | Value | RIGHT cleanup return | LEFT cleanup return | Runtime note |
|---|---:|---:|---:|---|
| `gEAction_Attack` | 1 | `Script_Game + 0x3851A` | `Script_Game + 0x3854E` | Normal cleanup across tested 2H, Staff, 1H, Shield+1H, Dual |
| `gEAction_PowerAttack` | 2 | `Script_Game + 0x4809D` | `Script_Game + 0x480E4` | includes tested Dual both-source cleanup |
| `gEAction_QuickAttackR/L` | 4 / 5 | `Script_Game + 0x48794` | `Script_Game + 0x487CC` | same tested Quick cleanup path across families; generic action 3 not established here |
| `gEAction_SimpleWhirl` | 6 | `Script_Game + 0x4C828` | `Script_Game + 0x4C858` | Dual SimpleWhirl separate LEFT/RIGHT branches |
| `gEAction_WhirlAttack` | 10 | `Script_Game + 0x4E03C` | not observed | tested full 2H/Staff Whirl used RIGHT |
| `gEAction_PierceAttack` | 11 | `Script_Game + 0x477E3` | `Script_Game + 0x4781C` | branch follows tested damaging equipped source |
| `gEAction_HackAttack` | 14 | `Script_Game + 0x432BC` | not observed | tested standing/block-breaking heavy use of serialized Finishing asset |
| `gEAction_FinishingAttack` | 15 | `Script_Game + 0x4178A` | `Script_Game + 0x417C2` | tested true finishing blows |
| `gEAction_GetUpAttack` | 30 | `Script_Game + 0x41E10` | not observed | tested get-up attack cleanup |

Engineering consequence:

> These sites describe **native successful cleanup implementations**, not a production hook matrix.

---

## 3. Filename vs Runtime Action — Direct Evidence

The serialized 2H motion family:

```text
Hero_Parade_None_2H_P0_FinishingAttack_Hit_N_Fwd_00_%_00_P1_100.xmot
```

has been observed under different runtime action semantics:

```text
gEAction_HackAttack      (14) -> Script_Game + 0x432BC
gEAction_FinishingAttack (15) -> Script_Game + 0x4178A
```

B5 also observed an intended execution target stand up before Hit: Gothic still used the FinishingAttack Raise/Hit asset family, while the Hit/collision records were already action 14.

The safe conclusion is **not** that a particular action switch necessarily occurred mid-Hit. The durable conclusion is:

> Runtime action semantics can select different behavior/cleanup code while reusing the same serialized animation asset family.

Therefore filenames alone are insufficient lifecycle authority.

---

## 4. Separate Tested Interruption Cleanup Route

B4b identified:

```text
Script_Game + 0x24AFF
```

as a native weapon-reset return site during the tested damage/reaction interruption matrix.

Representative ordering:

```text
Routine still reports original attack Hit
→ weapon cleanup 7 -> 5 at Script_Game + 0x24AFF
→ milliseconds later PrimaryFirst becomes Stumble/KnockDown/etc.
```

This route was observed across tested Staff, 1H and 2H reactions.

Do not claim that **every** possible interruption uses exactly this site. It is confirmed for the tested matrix.

Architectural consequence:

- legitimate interruption already has a native cleanup opportunity;
- ordinary completion and reaction interruption do not depend on one Script_Game cleanup function;
- bad block-skip teardown can miss both reliable ordinary completion cleanup and this tested reaction route.

---

## 5. B5 Higher Stack — Ordinary Completion

Captured ordinary cleanup stack shape:

```text
FrameCollision SetCollisionGroup wrapper
→ action-specific Script_Game cleanup return RVA
→ Game + 0x1605EB
```

Static identification now establishes:

```text
Game + 0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
Game + 0x1605EB = return point after its indirect Script_Game call
```

So `+0x1605EB` is **not a central combat cleanup helper**. It is the common post-indirect-call point reached by tested ordinary ScriptFunctions.

---

## 6. B5 Higher Stack — Legitimate Reaction Interruption

Captured interruption shape:

```text
FrameCollision SetCollisionGroup wrapper
→ Script_Game + 0x24AFF
→ reaction-specific Script_Game frame
→ Game + 0x1604D3
```

Static identification establishes:

```text
Game + 0x1603D0 = gCScriptAdmin::RunScriptState(...)
Game + 0x1604D3 = return point after its indirect Script_Game state call
```

The two B5 parent paths are adjacent in the binary but semantically generic sibling script runners:

```text
RunScriptState     starts Game + 0x1603D0
RunScriptFunction  starts Game + 0x1604E0
```

Adjacency is no reason to hook both.

---

## 7. Common Higher Dispatcher — `ProcessScript()`

Both script-runner paths converge one level higher in:

```text
Game + 0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

Tested binary structure includes calls approximately at:

```text
ProcessScript + ... -> RunScriptFunction
ProcessScript + ... -> RunScriptState
```

with selection influenced by `gScriptRunTimeSingleState::m_bIsScriptState`.

The official SDK makes clear that the SPU processes far more than combat: ScriptFunctions, ScriptStates, delayed instructions, routines/interactions, and callbacks.

Therefore:

> `ProcessScript()` is a **generic dispatcher**, not a collision-cleanup owner.

If it is ever used by a future lifecycle design, it may provide only a tightly gated timing checkpoint for an already-owned exact attack execution.

---

## 8. Callback Ordering — Why B2 Looked Late

Static inspection of `ProcessScript()` shows its main ScriptFunction/ScriptState dispatch occurs before later local/task callback processing through `RunScriptCallback(...)`.

This aligns with B2 runtime evidence where clean Quick native cleanup occurred before the later original callback began, and that callback then repeated during Recover.

Thus callback timing does not identify normal cleanup ownership.

---

## 9. `sAICombatMoveInstr` Is Too Early

Tested symbol:

```text
Game + 0x1696E0 = gCScriptProcessingUnit::sAICombatMoveInstr(...)
```

Static inspection shows it can:

- run `sAICombatMoveItlLoop` while the CombatMove instruction remains active;
- call `sAICombatMoveStart`;
- call `sAICombatMoveStartRecover` near completion;
- clear/finish the active instruction callback.

But the B4/B5 cleanup stack does **not** contain `sAICombatMoveInstr`: action-specific Script_Game cleanup occurs after the instruction returns.

Therefore CombatMove instruction completion is also too early to be the fallback cleanup point.

---

## 10. No Common Immediate Script_Game Post-Cleanup Helper Found

Static comparison of ordinary cleanup regions found no demonstrated common immediate Script_Game helper after cleanup across the tested Normal/Quick/full-Whirl paths.

Some families share local instruction shapes, but full Whirl diverges.

The first demonstrated ordinary common point is the generic `RunScriptFunction` return, which is broader than combat.

This is why the project proceeded to the later replacement/lifetime investigation rather than adding another family/helper hook.

---

## 11. Related Step-B Symbol / RVA Index

**Tested-build-specific.**

| Area | Symbol / purpose | Module + RVA | Established meaning |
|---|---|---:|---|
| PrimaryFirst play | `eCVisualAnimation_PS::PlayMotion` | `Engine + 0x30860` | B1/B6 immediate type-0 replacement/acquisition signal; replacement itself precedes clean cleanup |
| PrimaryFirst stop | `eCVisualAnimation_PS::StopMotion` | `Engine + 0x30980` | supporting B1 observation |
| loop-end request | `eCVisualAnimation_PS::StopAtLoopEnd` | `Engine + 0x309D0` | schedules stop; not actual end event |
| wrapper play | `eCWrapper_emfx2Actor::PlayMotion` | `Engine + 0x476F0` | lower wrapper path |
| wrapper stop | `eCWrapper_emfx2Actor::StopMotion` | `Engine + 0x47910` | lower wrapper path |
| wrapper loop-end | `eCWrapper_emfx2Actor::StopAtLoopEnd` | `Engine + 0x479C0` | lower wrapper path |
| CombatMove instruction | `sAICombatMoveInstr` | `Game + 0x1696E0` | too early for post-native-cleanup repair |
| CombatMove start | `sAICombatMoveStart` | `Game + 0x16ABB0` | start path |
| CombatMove loop | `sAICombatMoveItlLoop` | `Game + 0x16DD00` | iterative path; broad/polling risk |
| Recover start | `sAICombatMoveStartRecover` | `Game + 0x16E360` | B3: too early and bypassable |
| Script state runner | `RunScriptState` | `Game + 0x1603D0` | generic B5 interruption-side parent |
| Script function runner | `RunScriptFunction` | `Game + 0x1604E0` | generic B5 ordinary-side parent |
| script dispatcher | `ProcessScript` | `Game + 0x16F120` | common higher generic dispatcher |
| collision group | `eCEntity::SetCollisionGroup` | `Engine + 0x225660` | B4/B5 observation point |

For broader hook lookup use `SOURCE_HOOK_GUIDE.md`.

---

## 12. Marker Bookkeeping Is Separate

`RetireMarkerOwnedSource()` should not be confused with fallback physical cleanup.

The earlier problem was:

```text
marked source requests offense
→ execution interrupted
→ Gothic physically cleans 7 -> 5
→ old marker occurrence/execution bookkeeping can survive
```

The retirement helper reacts to an **already-performed** source reset and may retire the exact physical marker-owned source bit/window.

Intentional OFF and exact-set switching remain intra-Hit operations and must not retire the entire execution.

Current marker execution identity is the monotonic C1 generation; see `EVIDENCE_INDEX.md` → marker execution lifetime/bookkeeping and EV-213–EV-214.

---

## 13. Historical B6 Question — Resolved

B6 asked whether clean Hit→Recover replacement, legitimate damage/reaction replacement, and destructive direct replacement occurred in a useful current SPU/`ProcessScript()` context that could support a tightly gated post-native-cleanup check.

The subsequent B6–B9/C1/O1/P2 investigations superseded that candidate. The accepted architecture now uses:

```text
C1 monotonic generation
= durable execution/source-obligation identity

live ScriptFunction frame
= temporary correlator only where pre-Combat acquisition requires it

post-native AISetState finalization
= terminal exact-source repair checkpoint
```

Do not revive the old B6 `ProcessScript()` checkpoint candidate without new contradicting evidence.

Historical causal proof routes through `EVIDENCE_INDEX.md` (EV-174 onward) and exact raw/archive provenance.

---

## 14. Untested / Not Claimed

This map does not claim native cleanup coverage for every combat enum/source/actor type.

Not established by the original B4/B5 matrix include, among others:

- generic Quick/action 3;
- SprintAttack;
- JumpAttack;
- RamAttack;
- monster/body attacks;
- logical Fist cleanup semantics;
- ranged/magic execution cleanup.

That absence is a scope boundary, not evidence that separate production branches are needed.

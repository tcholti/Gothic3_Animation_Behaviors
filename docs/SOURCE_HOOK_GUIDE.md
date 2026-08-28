# Gothic 3 Animation Behaviors — Source & Hook Guide

**Status:** Canonical practical source/hook lookup guide  
**Updated:** 2026-08-28

## Purpose

Use this file to answer targeted questions such as:

- Which source tree should I search for this symbol?
- Which hook/API pattern has already worked?
- What tested RVA is associated with this function?
- Which evidence document contains the runtime meaning of that hook?

This is a **lookup and research-method guide**, not the project chronology and not the current continuation state.

Current state: `SESSION_ENTRYPOINT.md`  
Evidence routing: `EVIDENCE_INDEX.md`  
Detailed cleanup RVAs/stacks: `COLLISION_CLEANUP_CALLSITE_MAP.md`

The pre-information-architecture version, including v0.11–v0.19 implementation chronology, is preserved at:

`docs/archive/technical_2026-08-27/SOURCE_HOOK_GUIDE_pre_ia.md`

---

## 1. Source Roles

### Project repository

`Gothic3_Animation_Behaviors`

Home-PC path:

`E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\Gothic3_Animation_Behaviors`

Role:

- current project source;
- prototype/release modules;
- canonical docs/evidence;
- pinned third-party references.

### Official Gothic 3 SDK dependency

Project path:

`thirdparty/gothic3sdk`

Upstream:

`Georgeto/gothic3sdk`

Pinned revision recorded by the project:

`90bfd344de4510dda7ac9da7461cc7f1eac911f7`

Use first for:

- declarations/signatures;
- enums;
- property sets;
- wrappers;
- hook utilities;
- exposed low-level engine structures.

Do not silently replace this dependency with a reference fork.

### Jackydima reference source

Project path:

`references/jackydima-gothic3sdk`

Upstream:

`Jackydima/gothic3sdk`

Pinned reference revision recorded by the project:

`da61a791a97704ecebf166768c30564b6332d82d`

Use for:

- NewBalance / AttackCollision / animation examples;
- practical callback/source selection;
- collision rearm patterns;
- compatibility research;
- examples of animation-string interception and gameplay modifications.

Treat this as reference/compatibility evidence, not automatically as native engine truth.

### Binary reference repository

`tcholti/Gothic3_Binary_Reference`

Use for:

- tested-build disassembly slices;
- export identification;
- call-site/parent inspection;
- static confirmation around known RVAs.

Addresses remain build-specific.

### Historical examples environment

`E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\gothic3sdk-examples`

Use only when an older known-good example/build pattern is specifically needed. The current project repository is the authoritative build workspace.

---

## 2. Research Order

For an unknown engine-facing question:

```text
exact runtime question
→ official SDK declaration/API search
→ smallest known-good example/hook pattern
→ current third-party reference usage if relevant
→ binary reference/static inspection if ownership/order is unclear
→ controlled runtime evidence
→ animation asset evidence where relevant
→ smallest new diagnostic only if causality is still unresolved
```

Modify behavior only after the owning semantic layer is sufficiently understood.

---

## 3. Evidence Hierarchy by Question

| Evidence source | Best use | Main limitation |
|---|---|---|
| Official SDK declaration | signatures, enums, fields, exposed interfaces | does not prove internal runtime behavior |
| Small SDK/example | hook syntax, includes, minimal patterns | may be old/narrow |
| Current third-party source | real mod usage, compatibility, practical patterns | is mod behavior, not necessarily native behavior |
| Binary/disassembly | hidden control flow, callers, exact tested-build structure | build-specific; interpretation still needs care |
| Controlled runtime log | what the tested build actually did | bounded to tested scenario/build |
| Animation inventory/author evidence | asset naming, pose transitions, file existence, authored timing | file existence/naming alone does not prove runtime semantics |

Use converging sources when one layer cannot establish causality by itself.

---

## 4. Symbol Search Index

### Native semantic enums

Search official SDK `GameEnum.h` for:

- `gEAction`
- `gEPhase`
- `gEAniState`
- `gEPose`
- `gEUseType`
- `gEDirection`
- `gEHitDirection`

Animation-specific interpretation: `ANIMATION_INDEX.md` → `ANIMATION_RULES.md`.

### Script Processing / CombatMove

Search `ge_scriptprocessingunit.h`, `ge_scriptroutine_ps.h` and Script wrapper `gs_psroutine.h` for:

- `gCScriptProcessingUnit`
- `gCScriptRoutine_PS`
- `ProcessScript`
- `sAICombatMoveInstr_Args`
- `sAICombatMoveInstr`
- `sAICombatMoveStart`
- `sAICombatMoveItlLoop`
- `sAICombatMoveStartRecover`
- `m_pfInstrCallback`
- `m_fInstrPlayTime`
- `m_fInstrDuration`
- `StateTime`
- `StatePosition`
- `CurrentBreakBlock`
- `AIFullStop` / `FullStop`
- `AIStopCombatMove` / `StopAICombatMove`
- local/task callback helpers

B7 evidence EV-182–EV-184 shows that these symbols are part of a persisted asynchronous CombatMove/break-block lifetime. Do not assume `m_pfInstrCallback` alone is exact marked-Hit identity; use `EVIDENCE_INDEX.md` → Marker execution lifetime / bookkeeping before changing marker-core lifetime code.

### Script administration

Search SDK/binary exports for:

- `gCScriptAdmin::RunScriptFunction`
- `gCScriptAdmin::RunScriptState`
- `gCScriptAdmin::RunScriptCallback`
- `gScriptRunTimeSingleState::m_bIsScriptState`

These are generic script infrastructure; do not treat them as combat ownership simply because collision research reached them.

### Script control flow macros

Search `gs_scriptmacros.h` for:

- `BREAK_BLOCK`
- `PREPEND_BREAK_BLOCK_BEGIN`
- `PREPEND_BREAK_BLOCK_END`

The prepend pattern is proven for asynchronous custom Raise insertion before the original melee state. B7 also shows that native CombatMove attack logic can suspend a ScriptFunction at an asynchronous break block and resume later into action-specific continuation/cleanup.

### Animation selection / queries

Search SDK wrappers and Jackydima `Script_Animation` for:

- `GetAni`
- `GetAniEx`
- `GetAniName`
- `GetCurrentMovementAni`
- `GetCurrentAniPhase`
- `GetCurrentAniDirection`
- `GetPrimaryPoseExt`
- `FixAniDirection`
- `PlayMotion`
- `StopMotion`
- `StopAtLoopEnd`

### Collision / damage-source handling

Search reference source for:

- `OnAI_Attack`
- `OnAI_QuickAttack`
- `OnAI_PowerAttack`
- `OnAI_PierceAttack`
- `OnAI_SimpleWhirl`
- `OnAI_WhirlAttack`
- `OnAI_GetUpAttack`
- `SetCollisionGroup`
- `ClearTriggeredList`
- `PropertyResetOnUntouch`
- `gESlot_LeftHand`
- `gESlot_RightHand`
- `TouchDamage`

### Frame effects

Search for:

- `eCVisualAnimation_PS::UpdateFrameEffects`
- `GetFrameEffectList`
- `eSFrameEffect`
- `gCEffectSystem::StartEffect`
- motion resource/descriptor accessors

### Speed

Search for:

- `GetAnimationSpeedModifier`
- `AniSpeedScale`
- `m_fAniSpeedScale`
- `sAICombatMoveInstr`
- `PlayMotion`
- `GetMaxTime`

### Trigger visit/rearm state

Search SDK `eCTrigger_PS` for:

- `EntitiesVisited`
- `EntitiesVisitedCount`
- `ClearTriggeredList()`
- `ClearTriggeredList(eCEntity *)`

---

## 5. Tested RVA / Hook Index

**All addresses are tested-build-specific. Reverify against the current binary before reuse on another build.**

### Animation / CombatMove

| Symbol / purpose | Module + RVA | Current meaning |
|---|---:|---|
| `GetAnimationSpeedModifier` | `Script_Game + 0x42A0` | proven action/phase speed modifier hook; compatibility concern if another DLL owns same path |
| global attack-speed example | `Script_Game + 0x4D5B` | reference example, not current production authority |
| CombatMove animation-string call point | `Game + 0x16B065` | practical interception/substitution point used by NewBalance |
| CombatMove reach/vector call point | `Game + 0x16B8A3` | reference hook point |
| CombatMove movement call point | `Game + 0x16B8A9` | reference hook point |
| full-Whirl CombatMove break-block call/test | `Script_Game + 0x4DF8C / +0x4DF92` | B7 static proof: incomplete result returns ScriptFunction false; completed result falls through into later Whirl continuation/cleanup |
| full-Whirl ordinary collision cleanup continuation | `Script_Game + 0x4E03C` | reached after the CombatMove break block completes; not automatic animation teardown |
| `GetAniName` | `Game + 0x16F840` | animation name lookup |
| `GetAniEx` | `Script + 0x15C10` | animation query |
| `GetMotionDataEntityAniString` | `Game + 0xD97D5` | motion resource string |
| `GetCachedMotionDataActor` | `Game + 0xDA344` | cached animation actor |

### PrimaryFirst motion lifecycle

| Symbol / purpose | Module + RVA | Current meaning |
|---|---:|---|
| high `eCVisualAnimation_PS::PlayMotion` | `Engine + 0x30860` | B1/B6 type-0 immediate PrimaryFirst acquisition/replacement observation |
| high `eCVisualAnimation_PS::StopMotion` | `Engine + 0x30980` | supporting B1 motion stop observation |
| high `StopAtLoopEnd` | `Engine + 0x309D0` | schedules loop-end stop; not actual completion event |
| wrapper `eCWrapper_emfx2Actor::PlayMotion` | `Engine + 0x476F0` | lower wrapper path |
| wrapper `StopMotion` | `Engine + 0x47910` | lower wrapper path |
| wrapper `StopAtLoopEnd` | `Engine + 0x479C0` | lower wrapper path |

### CombatMove/SPU

| Symbol | Module + RVA | Established constraint |
|---|---:|---|
| `gCScriptRoutine_PS::AIFullStop` | `Game + 0x164430` | invokes the SPU's current persisted instruction callback with `fullStop=true` if one exists; generic instruction stop |
| `gCScriptRoutine_PS::AIStopCombatMove` | `Game + 0x1644D0` | invokes the callback with `fullStop=true` only when current callback is exactly `sAICombatMoveInstr` |
| `sAICombatMoveInstr` | `Game + 0x1696E0` | persisted asynchronous CombatMove instruction; while active can store itself in `m_pfInstrCallback`; terminal/full-stop handling clears callback; still too early to treat return as post-cleanup fallback |
| `sAICombatMoveStart` | `Game + 0x16ABB0` | CombatMove start |
| `sAICombatMoveItlLoop` | `Game + 0x16DD00` | iterative loop; broad, deliberately not production polling authority |
| `sAICombatMoveStartRecover` | `Game + 0x16E360` | B3: starts/attempts Recover but returns before native weapon cleanup and may be bypassed |
| `gCScriptProcessingUnit::ProcessScript` | `Game + 0x16F120` | common generic higher dispatcher; B6 rejected the earlier universal replacement-time checkpoint candidate |

### Script dispatch / lifecycle control

| Symbol | Module + RVA | Established constraint |
|---|---:|---|
| `gCScriptAdmin::RunScriptState` | `Game + 0x1603D0` | B5 interruption-side generic script runner |
| `gCScriptAdmin::RunScriptFunction` | `Game + 0x1604E0` | B5 ordinary-side generic script runner; action-specific cleanup returns around `+0x1605EB` |
| reaction-control `PSRoutine::FullStop()` call site | `Script_Game + 0x2246F` | B7 static reaction-region FullStop site; do not assume it maps one-to-one to every recorded reaction until runtime confirms |
| reaction-control `PSRoutine::FullStop()` call site | `Script_Game + 0x23002` | second B7 static reaction-region FullStop site; same qualification |

### Frame effects / collision

| Symbol / purpose | Module + RVA | Current meaning |
|---|---:|---|
| `eCVisualAnimation_PS::UpdateFrameEffects` | `Game + 0x2EFF0` | frame-effect update path |
| `GetFrameEffectList` | `Game + 0x12E460` | exact motion frame-effect list |
| `eSMotionDesc::GetMotion` | `Game + 0x2A0C0 / 0x2A0B0` | tested motion access reference |
| `gCEffectSystem::StartEffect` | `Game + 0x60850` | global authored effect dispatch used by marker prototype |
| `eCEntity::SetCollisionGroup` | `Game + 0x225660` | current research observation point for offensive activation/cleanup requests |

### Script action helpers

| Symbol | Module + RVA |
|---|---:|
| `AddAction` | `Script_Game + 0x7940` |
| `PopCurrentActionIfPlayer` | `Script_Game + 0x79A0` |
| `ClearNextActionsIfPlayer` | `Script_Game + 0x7A00` |

For exact native cleanup return RVAs by action and the tested interruption route, use `COLLISION_CLEANUP_CALLSITE_MAP.md` rather than duplicating that table here.

---

## 6. Tested Frame-Effect Layout

For the exact tested engine build, the prototype used:

`eSFrameEffect`

- stride: 8 bytes;
- `+0x00`: authored frame (`uint16`);
- `+0x04`: effect name (`bCString`).

This is build/layout-specific reverse-engineering evidence. Reverify before assuming another binary has the same layout.

---

## 7. Proven Hook Patterns

### Inserted call hook

Use when a known call site exposes the needed fact and original behavior should continue unchanged.

### Function hook with original fallback

Typical pattern:

```text
inspect authoritative context
→ if custom rule applies, perform bounded intervention
→ otherwise preserve original path
```

If used as pre/post observation, call the original exactly once unless the contract explicitly requires otherwise.

### `PREPEND_BREAK_BLOCK` state insertion

Proven for custom asynchronous Raise before the untouched original melee state.

### Named AI callback adapter

Prefer a named native callback when it already provides the correct attack-family semantics. The global marker dispatcher may then correlate the later effect with exact native action/phase and exact marked motion.

### Shared hook owner + factual dispatch

When diagnostics and behavior need the same low-level hook, install it once and dispatch factual context to the two responsibilities. Do not create competing DLL/module owners for convenience.

---

## 8. Same-Function Hook Caution

Do not assume two independently loaded `mCFunctionHook` instances on the same target chain safely.

Tested coexistence in one configuration does not prove arbitrary load order or hook timing.

Before release compatibility with NewBalance / `Script_AttackCollision`:

- inspect hook implementation/chaining semantics where relevant;
- retest if DLL naming/load order/marker timing changes;
- prefer one authoritative owner or a proven downstream/integration strategy.

Evidence routing: EV-035, EV-148–EV-150.

---

## 9. Attack Callback / Action Routing

| Callback family | Native action(s) currently established | Important note |
|---|---|---|
| `OnAI_Attack` | `gEAction_Attack` (1) | Normal |
| `OnAI_PowerAttack` | `gEAction_PowerAttack` (2) | Dual can use both equipped sources; repeated contact requires rearm |
| `OnAI_QuickAttack` | `QuickAttack`, `QuickAttackR`, `QuickAttackL` (3/4/5 family; 4/5 extensively tested) | R/L action side is not physical weapon hand |
| `OnAI_SimpleWhirl` | `gEAction_SimpleWhirl` (6) | Dual uses this despite serialized `WhirlAttack` filename token |
| `OnAI_WhirlAttack` | `gEAction_WhirlAttack` (10) | full 2H/Staff Whirl; separate from SimpleWhirl |
| `OnAI_PierceAttack` | `gEAction_PierceAttack` (11) | Dual source follows pose/source mapping |
| finishing/heavy paths | Hack (14), Finishing (15) | same serialized Finishing asset can run under different action semantics |
| `OnAI_GetUpAttack` | `gEAction_GetUpAttack` (30) | native collision observed; unmarked controls remain native |

Do not infer callback ownership from filename spelling where runtime action/source evidence differs.

---

## 10. Useful Third-Party Reference Patterns

### Dual Power rearm

Pinned NewBalance contains `FixDualOneHanded`, which clears both Dual weapon `TouchDamage` lists at a build-specific Script_Game hook. This is strong structural evidence for independent source rearm, not universal authored timing authority.

### Full Whirl reset-on-untouch

Jackydima's Whirl path uses `PropertyResetOnUntouch = GETrue` in its timer-owned model.

The project's authored marker model deliberately does not assume that property is desirable: repeated source markers explicitly rearm, and OFF explicitly authors inactive gaps. Automatic geometry-dependent rearm would be a different semantic model.

### CombatMove animation-string substitution

NewBalance uses the call point around `Game + 0x16B065` to substitute animation strings for custom combat behavior while retaining surrounding CombatMove machinery.

This is reusable engine knowledge for later animation-selection research (for example disabled/unused variants, jump/wade/climbing feasibility), but it is not part of the current collision implementation.

---

## 11. Build / Runtime Reference

Repository-local build:

```powershell
git submodule update --init --recursive
cmake -S . -B build -G "Visual Studio 17 2022" -A Win32
cmake --build build --config Release --target <TargetName>
```

Current known targets include:

- `Script_G3AnimationBehaviors`
- `Script_FrameCollisionTest`
- `Script_FrameEffectLogger`
- `Script_CombatMoveLogger`

Game scripts directory:

`E:\SteamLibrary\steamapps\common\Gothic 3\scripts`

Game INI directory:

`E:\SteamLibrary\steamapps\common\Gothic 3\Ini`

For isolated collision tests, remove conflicting collision DLLs unless compatibility is the explicit variable being tested.

**Live-script hygiene:** do not keep backup or renamed `Script_*.dll` files inside the live Gothic 3 `scripts` directory, even with an added extension such as `.bak`. EV-173 showed `Script_FrameCollisionTest.preB6.dll.bak` participating in runtime hook execution and duplicating diagnostics. Keep backups outside the live `scripts` directory during controlled tests.

---

## 12. Retrieval Routes

| Question | Start here |
|---|---|
| Exact native cleanup action/RVA/parent stack | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| Why a hook/path is accepted/rejected architecturally | `COLLISION_LIFECYCLE_PLAN.md` + evidence IDs |
| Marker execution lifetime / future bookkeeping simplification | `EVIDENCE_INDEX.md` → Marker execution lifetime / bookkeeping, then `COLLISION_LIFECYCLE_PLAN.md` §10 |
| CombatMove persisted instruction / FullStop / break-block continuation | EV-182–EV-184 + this guide §4–§5 |
| Exact evidence status/provenance | `EVIDENCE_INDEX.md` → evidence ledger |
| Animation action/UseType/pose/name meaning | `ANIMATION_INDEX.md` |
| Exact animation asset | animation-name data / `ANIMATION_CATALOG.md` |
| Old v0.x hook/prototype chronology | archived pre-IA guide / `RESEARCH_MAP.md` / evidence ledger |

When adding a new durable hook finding, prefer updating the relevant symbol/RVA/index row here and the exact evidence entry, rather than appending another long chronological narrative.
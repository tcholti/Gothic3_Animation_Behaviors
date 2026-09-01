# Gothic 3 Animation Behaviors — Source & Hook Guide

**Status:** Canonical practical source/hook lookup guide  
**Updated:** 2026-09-01

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

Historical pre-information-architecture wording and older v0.x implementation chronology remain recoverable through Git history and the exact EV/raw provenance routes. They are not maintained as a duplicate active documentation archive.

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

Use first for declarations/signatures, enums, property sets, wrappers, hook utilities and exposed low-level engine structures. Do not silently replace this dependency with a reference fork.

### Jackydima reference source

Project path: `references/jackydima-gothic3sdk`  
Pinned reference revision: `da61a791a97704ecebf166768c30564b6332d82d`

Use for NewBalance / AttackCollision / animation examples, practical callback/source selection, collision rearm patterns, compatibility research and animation-string interception examples. Treat it as reference/compatibility evidence, not automatically as native engine truth.

### Binary reference repository

`tcholti/Gothic3_Binary_Reference`

Use for tested-build disassembly slices, export/import identification, call-site/parent inspection and static confirmation around known RVAs. Addresses remain build-specific.

### Historical examples environment

`E:\Mods\1.Game Files\Gothic 3\Tools\Gothic 3 making scripts\gothic3sdk-examples`

Use only when an older known-good example/build pattern is specifically needed.

---

## 2. Research Order

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
- `gESessionKey`
- `gEDirection`
- `gEHitDirection`

Animation-specific interpretation: `ANIMATION_INDEX.md` → `ANIMATION_RULES.md`.

### Script Processing / CombatMove / outer state stack

Search `ge_scriptprocessingunit.h`, `ge_scriptroutine_ps.h`, `ge_scriptadmin.h` and Script wrapper `gs_psroutine.h` for:

- `gCScriptProcessingUnit`
- `gCScriptRoutine_PS`
- `gCScriptRoutine_PS::GetSPU`
- `gCScriptProcessingUnit::GetSelfEntity`
- `gScriptRunTimeSingleState`
- `ProcessScript`
- `sAICombatMoveInstr_Args`
- `sAICombatMoveInstr`
- `sAICombatMoveStart`
- `sAICombatMoveItlLoop`
- `sAICombatMoveStartRecover`
- `m_StateStack`
- `m_pfInstrCallback`
- `m_fInstrPlayTime`
- `m_fInstrDuration`
- `m_bIsScriptState`
- `m_iBreakBlock`
- `m_strScriptName`
- `m_pArguments`
- `m_strLocalCallback`
- `StateTime`
- `StatePosition`
- `CurrentBreakBlock`
- `AIFullStop` / `FullStop`
- `AIStopCombatMove` / `StopAICombatMove`
- `SetState`
- `SetTask`

EV-182–EV-191 establish persisted asynchronous CombatMove/break-block lifetime and the tested state-stack-abandonment class. EV-195–EV-196 establish the stronger outer ScriptFunction lifetime: a live ScriptFunction frame can predate CombatMove, persist while asynchronous work returns false, and bridge pre-CombatMove offense → later CombatMove → cleanup.

Do not assume `m_pfInstrCallback` alone is exact attack execution identity. Do not treat a raw state-stack entry address or `m_pArguments` address as a permanent ID; C1-O1 proved raw addresses can be reused after the old frame retires.

### Character control

Search Script wrappers / imports for:

- `PSCharacterControl::PressedKey`
- `PSCharacterControl::IsPressed`
- `PSCharacterControl::IsPressedBefore`
- `PSCharacterControl::DurationPressedMSecs`

B7b used these as factual context. They are not proposed as production collision classifiers.

### Script administration

Search SDK/binary exports for:

- `gCScriptAdmin::RunScriptFunction`
- `gCScriptAdmin::RunScriptState`
- `gCScriptAdmin::RunScriptCallback`
- `gScriptRunTimeSingleState::m_bIsScriptState`

Current C1-O1/static facts for `RunScriptFunction`:

```text
gCScriptAdmin::RunScriptFunction(
    bCString const &,
    bTObjStack<gScriptRunTimeSingleState> &,
    gCScriptProcessingUnit *)
```

- the runner receives the exact per-dispatch SPU explicitly;
- `spu->GetSelfEntity()` exposes the actor associated with that SPU;
- the tested binary calls the registered ScriptFunction at `Game +0x1605E9`;
- `Game +0x1605EB` is the first instruction after that registered call;
- false result returns without removing the live top frame;
- true result removes the completed top frame before the runner returns;
- `gCScriptAdmin` exposes no documented public accessor that should be treated as “the currently executing NPC SPU”; do not substitute its protected admin `m_SPU` for the explicit supplied SPU without evidence.

These are generic script infrastructure facts. The proven P1/P2 `RunScriptFunction` hook provides a narrow transient dispatch context for pre-Combat offense acquisition; it is not attack ownership or unconditional cleanup authority by itself. Durable identity remains the monotonic C1 generation.

Evidence: EV-169–EV-171, EV-195–EV-196, EV-204–EV-205.

### Script control flow macros

Search `gs_scriptmacros.h` for `BREAK_BLOCK`, `PREPEND_BREAK_BLOCK_BEGIN`, `PREPEND_BREAK_BLOCK_END`.

The prepend pattern is proven for custom asynchronous Raise. Native CombatMove attack logic also suspends a ScriptFunction at an asynchronous break block and can later resume into action-specific cleanup—unless a state-stack replacement discards that continuation.

### Animation selection / queries

Search SDK wrappers and Jackydima `Script_Animation` for `GetAni`, `GetAniEx`, `GetAniName`, `GetCurrentMovementAni`, `GetCurrentAniPhase`, `GetCurrentAniDirection`, `GetPrimaryPoseExt`, `FixAniDirection`, `PlayMotion`, `StopMotion`, `StopAtLoopEnd`.

### Collision / damage-source handling

Search reference source for `OnAI_Attack`, `OnAI_QuickAttack`, `OnAI_PowerAttack`, `OnAI_PierceAttack`, `OnAI_SimpleWhirl`, `OnAI_WhirlAttack`, `OnAI_GetUpAttack`, `SetCollisionGroup`, `ClearTriggeredList`, `PropertyResetOnUntouch`, `gESlot_LeftHand`, `gESlot_RightHand`, `TouchDamage`.

### Frame effects

Search for `eCVisualAnimation_PS::UpdateFrameEffects`, `GetFrameEffectList`, `eSFrameEffect`, `gCEffectSystem::StartEffect` and motion resource/descriptor accessors.

### Speed

Search for `GetAnimationSpeedModifier`, `AniSpeedScale`, `m_fAniSpeedScale`, `sAICombatMoveInstr`, `PlayMotion`, `GetMaxTime`.

### Trigger visit/rearm state

Search SDK `eCTrigger_PS` for `EntitiesVisited`, `EntitiesVisitedCount`, `ClearTriggeredList()` and `ClearTriggeredList(eCEntity *)`.

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
| full-Whirl CombatMove break-block call/test | `Script_Game + 0x4DF8C / +0x4DF92` | incomplete result returns ScriptFunction false; completed result falls through into later Whirl continuation/cleanup |
| full-Whirl ordinary collision cleanup continuation | `Script_Game + 0x4E03C` | reached only when the suspended Whirl ScriptFunction resumes after CombatMove completion |
| GetUp pre-CombatMove offense region | `Script_Game +0x41CA6` | legitimate weapon offense can occur before later CombatMove; establishes acquisition gap |
| GetUp later CombatMove call | `Script_Game +0x41D5A` | same GetUp outer ScriptFunction later reaches CombatMove in tested path |
| GetUp ordinary cleanup | `Script_Game +0x41E10` | tested ordinary GetUp weapon cleanup region |
| `GetAniName` | `Game +0x16F840` | animation name lookup |
| `GetAniEx` | `Script +0x15C10` | animation query |
| `GetMotionDataEntityAniString` | `Game +0xD97D5` | motion resource string |
| `GetCachedMotionDataActor` | `Game +0xDA344` | cached animation actor |

### PrimaryFirst motion lifecycle

| Symbol / purpose | Module + RVA | Current meaning |
|---|---:|---|
| high `eCVisualAnimation_PS::PlayMotion` | `Engine +0x30860` | type-0 immediate PrimaryFirst acquisition/replacement observation |
| high `eCVisualAnimation_PS::StopMotion` | `Engine +0x30980` | supporting motion-stop observation; not proven universal end authority |
| high `StopAtLoopEnd` | `Engine +0x309D0` | schedules loop-end stop; not actual completion event |
| wrapper `eCWrapper_emfx2Actor::PlayMotion` | `Engine +0x476F0` | lower wrapper path |
| wrapper `StopMotion` | `Engine +0x47910` | lower wrapper path |
| wrapper `StopAtLoopEnd` | `Engine +0x479C0` | lower wrapper path |

### CombatMove / SPU

| Symbol | Module + RVA | Established constraint |
|---|---:|---|
| `gCScriptRoutine_PS::AIFullStop` | `Game +0x164430` | invokes the current persisted instruction callback with `fullStop=true`; generic instruction stop |
| `gCScriptRoutine_PS::AIStopCombatMove` | `Game +0x1644D0` | invokes `fullStop=true` only when current callback is exactly `sAICombatMoveInstr` |
| `sAICombatMoveInstr` | `Game +0x1696E0` | persisted asynchronous CombatMove instruction; terminal/full-stop handling clears callback |
| `sAICombatMoveStart` | `Game +0x16ABB0` | CombatMove start |
| `sAICombatMoveItlLoop` | `Game +0x16DD00` | iterative loop; deliberately not production polling authority |
| `sAICombatMoveStartRecover` | `Game +0x16E360` | starts/attempts Recover but returns before native weapon cleanup and may be bypassed |
| `gCScriptProcessingUnit::ProcessScript` | `Game +0x16F120` | generic higher dispatcher; not combat ownership or a proven universal replacement-time checkpoint |

### Script dispatch / lifecycle control

| Symbol / path | Module + RVA | Established constraint |
|---|---:|---|
| `gCScriptAdmin::RunScriptState` | `Game +0x1603D0` | interruption-side generic script runner |
| `gCScriptAdmin::RunScriptFunction` | `Game +0x1604E0` | generic ScriptFunction runner; explicit-SPU member hook is tested as the P1/P2 transient pre-Combat bridge context |
| registered ScriptFunction indirect call | `Game +0x1605E9` | exact tested call inside `RunScriptFunction` |
| post-registered-call point | `Game +0x1605EB` | first tested instruction after registered ScriptFunction returns |
| completed-frame removal helper | `Game +0x1627B0` | used by tested true-result path to remove completed top runtime frame |
| tested legitimate-reaction `PSRoutine::FullStop()` | `Script_Game +0x2D0F2` | B7b exact Normal/Quick reaction FullStop call; return `+0x2D0F8`; control remains in reaction path and later cleanup can run |
| additional tested legitimate-reaction AIFullStop caller | `Script_Game +0x2B8CB` | observed by B9; confirms one reaction caller RVA is not universal |
| player Use2 helper | `Script_Game +0x62FF0` | higher player-control helper reached by the B7 bad full-Whirl path; common caller returns at `+0x61866` |
| tested bad full-Whirl `PSRoutine::FullStop()` | `Script_Game +0x633F1` | B7b exact held-Use2 bad caller; immediate return `+0x633F7`; branch is reached after press duration exceeds 2500 ms in tested path |
| tested bad full-Whirl immediate `PSRoutine::SetState(...)` | `Script_Game +0x63409` | follows the bad FullStop; SDK documents SetState as clearing SPU state stack and resetting state-position/break-block bookkeeping |
| `gCScriptRoutine_PS::AISetState` | `Game +0x164320` | generic destructive state replacement; C1 captures exact generation before original and finalizes only after native AISetState returns |
| older static reaction-region FullStop site | `Script_Game +0x2246F` | broad reaction-control static site; not the exact B7b Normal/Quick caller |
| older static reaction-region FullStop site | `Script_Game +0x23002` | broad reaction-control static site; not the exact B7b Normal/Quick caller |

Tested bad held-Use2 causal class:

```text
attack ScriptFunction suspended at CombatMove break block
→ +0x633F1 FullStop
→ active CombatMove terminated
→ +0x63409 SetState
→ AISetState destructive replacement
→ old SPU state-stack/break-block continuation discarded
→ ordinary attack cleanup continuation cannot resume
```

B8 generalized this tested failure class to Quick configurations beyond full Whirl; B9 established that clean/reaction controls perform cleanup before the relevant destructive finalization. Do **not** hook the held-Use2 path as collision repair.

Current C1-O2/P2 route follows the outer ScriptFunction lifetime generically: exact SPU + live ScriptFunction + non-null arguments + same script name as a temporary correlator, while C1's monotonic generation remains durable identity.

### Frame effects / collision

| Symbol / purpose | Module + RVA | Current meaning |
|---|---:|---|
| `eCVisualAnimation_PS::UpdateFrameEffects` | `Game +0x2EFF0` | frame-effect update path |
| `GetFrameEffectList` | `Game +0x12E460` | exact motion frame-effect list |
| `eSMotionDesc::GetMotion` | `Game +0x2A0C0 / +0x2A0B0` | tested motion access reference |
| `gCEffectSystem::StartEffect` | `Game +0x60850` | global authored effect dispatch used by marker prototype |
| `eCEntity::SetCollisionGroup` | `Engine +0x225660` | tested shared observation/intervention path for offensive activation, native cleanup, marker retirement and C1-R1 repair re-entry |

### Script action helpers

| Symbol | Module + RVA |
|---|---:|
| `AddAction` | `Script_Game +0x7940` |
| `PopCurrentActionIfPlayer` | `Script_Game +0x79A0` |
| `ClearNextActionsIfPlayer` | `Script_Game +0x7A00` |

For exact native cleanup return RVAs by action and the tested interruption route, use `COLLISION_CLEANUP_CALLSITE_MAP.md` rather than duplicating that table here.

---

## 6. Tested Frame-Effect Layout

For the exact tested engine build, the prototype used `eSFrameEffect` stride 8 bytes:

- `+0x00`: authored frame (`uint16`);
- `+0x04`: effect name (`bCString`).

This is build/layout-specific reverse-engineering evidence. Reverify before assuming another binary has the same layout.

---

## 7. Proven Hook Patterns

### Inserted call hook

Use when a known call site exposes the needed fact and original behavior should continue unchanged.

### Function hook with original fallback

```text
inspect authoritative context
→ if custom rule applies, perform bounded intervention
→ otherwise preserve original path
```

If used as pre/post observation, call the original exactly once unless the contract explicitly requires otherwise.

### Recursion-safe explicit-this member hook

The current proven member-hook transport for the lifecycle substrate is the explicit per-invocation `this` pattern:

```text
wrapper receives native this as its first explicit argument
→ hook is prepared with .ThisCall()
→ original is called with that same explicit this exactly once
```

This transport has runtime validation for the current responsibilities on:

```text
gCScriptAdmin::RunScriptFunction  Game +0x1604E0
gCScriptRoutine_PS::AISetState    Game +0x164320
gCScriptRoutine_PS::AIFullStop    Game +0x164430
eCEntity::SetCollisionGroup       Engine +0x225660
```

The older shared `GetSelf()` ThisCall mechanism was useful during earlier probes but was replaced on these paths because nested/recursive entry can overwrite shared hook-self state. Do not regress these tested paths back to shared `GetSelf()` transport merely during structural refactoring.

Evidence route: EV-199–EV-205 plus EV-206/R1 validation.

### `PREPEND_BREAK_BLOCK` state insertion

Proven for custom asynchronous Raise before the untouched original melee state.

### Named AI callback adapter

Prefer a named native callback when it already provides correct attack-family semantics. The global marker dispatcher may then correlate the later effect with exact native action/phase and exact marked motion.

### Shared hook owner + factual dispatch

When diagnostics and behavior need the same low-level hook, install it once and dispatch factual context to the independent responsibilities. Do not create competing DLL/module owners for convenience.

For the planned modular DLL, preserve one physical hook owner and keep feature decisions outside the transport wrapper where practical. Refactoring must preserve tested pre/original/post ordering and re-entrant SetCollisionGroup behavior, not merely the target address.

---

## 8. Same-Function Hook Caution

Do not assume two independently loaded `mCFunctionHook` instances on the same target chain safely. Tested coexistence in one configuration does not prove arbitrary load order or hook timing.

Before release compatibility with NewBalance / `Script_AttackCollision`, inspect hook implementation/chaining semantics where relevant, retest if DLL naming/load order/marker timing changes, and prefer one authoritative owner or a proven downstream/integration strategy.

Evidence routing: EV-035, EV-148–EV-150.

The same rule applies inside G3AnimationBehaviors itself: if several feature modules need the same Gothic function, one engine-bridge owner should hook it once and dispatch the factual event/context. Do not create internal same-function hook competition.

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
| `OnAI_GetUpAttack` | `gEAction_GetUpAttack` (30) | can legitimately arm before CombatMove; do not special-case action 30 for ownership |

Do not infer callback ownership from filename spelling where runtime action/source evidence differs.

---

## 10. Useful Third-Party Reference Patterns

### Dual Power rearm

Pinned NewBalance contains `FixDualOneHanded`, which clears both Dual weapon `TouchDamage` lists at a build-specific Script_Game hook. This is strong structural evidence for independent source rearm, not universal authored timing authority.

### Full Whirl reset-on-untouch

Jackydima's Whirl path uses `PropertyResetOnUntouch = GETrue` in its timer-owned model. The project's authored marker model deliberately does not assume that property is desirable: repeated source markers explicitly rearm, and OFF explicitly authors inactive gaps.

### CombatMove animation-string substitution

NewBalance uses the call point around `Game +0x16B065` to substitute animation strings while retaining surrounding CombatMove machinery. This is reusable engine knowledge for later animation-selection research, not part of current collision implementation.

---

## 11. Build / Runtime Reference

Repository-local build:

```powershell
git submodule update --init --recursive
cmake -S . -B build -G "Visual Studio 17 2022" -A Win32
cmake --build build --config Release --target <TargetName>
```

Current known targets include `Script_G3AnimationBehaviors`, `Script_FrameCollisionTest`, `Script_FrameCollisionBehaviorTest`, and `Script_CombatMoveLogger`.

Game scripts directory:

`E:\SteamLibrary\steamapps\common\Gothic 3\scripts`

Game INI directory:

`E:\SteamLibrary\steamapps\common\Gothic 3\Ini`

For isolated collision tests, remove conflicting collision DLLs unless compatibility is the explicit variable being tested.

**Live-script hygiene:** do not keep backup or renamed `Script_*.dll` files inside the live Gothic 3 `scripts` directory, even with an added extension such as `.bak`. EV-173 showed such a backup participating in runtime hook execution. Keep backups outside the live directory during controlled tests.

---

## 12. Retrieval Routes

| Question | Start here |
|---|---|
| Exact native cleanup action/RVA/parent stack | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| Why a hook/path is accepted/rejected architecturally | `COLLISION_LIFECYCLE_PLAN.md` + evidence IDs |
| Marker execution lifetime / generation-scoped bookkeeping | `EVIDENCE_INDEX.md` → Marker execution lifetime / bookkeeping, then `COLLISION_LIFECYCLE_PLAN.md` |
| CombatMove persisted instruction / FullStop / SetState / state-stack abandonment | EV-182–EV-191 + this guide §4–§5 |
| Outer ScriptFunction lifetime / `RunScriptFunction` persistence | EV-195–EV-196 + this guide §4–§5 |
| Proven P1/P2 `RunScriptFunction` bridge / explicit-this transport | EV-199–EV-205 + this guide §§4–8 |
| C1-R1 repair / SetCollisionGroup transport | EV-203, EV-206–EV-207 + this guide §§5–8 |
| GetUp pre-CombatMove boundary | EV-194–EV-196 + this guide §5 |
| Exact tested bad full-Whirl caller | EV-187/EV-189 + this guide §5 |
| Tested legitimate-reaction FullStop callers | EV-188/EV-191 + this guide §5 |
| Exact evidence status/provenance | `EVIDENCE_INDEX.md` → evidence ledger |
| Animation action/UseType/pose/name meaning | `ANIMATION_INDEX.md` |
| Exact animation asset | animation-name data / `ANIMATION_CATALOG.md` |
| Old v0.x hook/prototype chronology | `EVIDENCE_INDEX.md` → exact EV/provenance → Git history/raw/archive only when needed |

When adding a new durable hook finding, update the relevant symbol/RVA/index row here and the exact evidence entry rather than appending another long chronological narrative.
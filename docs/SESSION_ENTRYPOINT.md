# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-28

`docs/collision-source-evidence` contains the newest collision research/prototype state. `main` is the stable integration baseline.

Document roles / Hot-Warm-Cold retrieval: `docs/README.md`  
Transient Chat ↔ Work handoff when relevant: `docs/BETWEEN_CHATS.md`

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` only when the current responsibility depends on an active/recent Work handoff.
3. If the active subsystem is not already oriented in the current Chat, perform the one-time Subsystem Orientation Pass from `docs/README.md`.
4. Do not scan the whole repository or reconstruct the project from old chat history.
5. Retrieve only the deeper authority listed under **Retrieval — Only What the Question Needs**.

Within one continuing subsystem context, do not repeatedly reread unchanged authorities.

---

## Active Subsystem

**Frame-controlled melee collision lifecycle.**

Preferred invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact Hit genuinely ends or is replaced, if cleanup was observed, do nothing; if not, repair the remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. End-of-Hit safety is one shared execution-level responsibility for marked and native attacks.

Architecture authority: `docs/COLLISION_LIFECYCLE_PLAN.md`.

---

## Established Native Failure Model

CombatMove is asynchronous. The owning ScriptFunction can be suspended at a break block while `sAICombatMoveInstr` persists in the SPU.

On ordinary completion, CombatMove finishes and the ScriptFunction resumes into its action-specific cleanup. Tested full Whirl reaches ordinary cleanup at `Script_Game +0x4E03C` only after its CombatMove break block completes.

Tested legitimate Normal/Quick reactions can FullStop the active CombatMove through `Script_Game +0x2D0F2`, then continue under reaction control and later use the established `+0x24AFF` collision cleanup when offense had armed.

The tested bad held-Use2 path is different:

```text
Use2 held beyond 2500 ms
→ Script_Game +0x633F1 calls PSRoutine::FullStop()
→ Script_Game +0x63409 calls PSRoutine::SetState(...)
→ SetState clears the SPU state stack / resets state-position and break-block bookkeeping
→ the suspended attack ScriptFunction continuation is discarded
→ its ordinary action-specific cleanup can no longer run
→ if offense had armed, Item_Attack(7) can survive into Ambient/idle/movement
```

B8 generalized this same tested control path beyond full Whirl. Player Quick attacks with **Dual (1H+1H), plain 1H, and Shield+1H** all produced `PS_Melee_QuickAttack` AIFullStop records through the same `Script_Game +0x633F7` return from the `+0x633F1` FullStop call while Use2 was held. Representative armed cases in all three configurations had already requested `5 -> 7` and then entered Ambient/Parade while the weapon remained group 7.

Therefore the held-Use2 state-stack-abandonment mechanism is **not Whirl-specific and not Dual-specific** in the tested player cases.

Important qualification: this does not prove that every possible abnormal attack termination, NPC path, or stale-collision cause uses the same player input branch.

B8 raw:

```text
research/raw/2026-08-28_b8_player_dual_quick_state_stack_abandonment.log
```

B8 raw commit:

```text
3c8484f3e6a123e6a5c5901318bd9c444cc0107b
```

---

## Current Gate — B9 Native AISetState Ordering

Static/source audit maps one authoritative native state-change observation point:

```text
Script.dll PSRoutine::SetState       +0x12F50
→ gCScriptRoutine_PS::AISetState     Game +0x164320
→ SPU state-changing implementation  Game +0x16F5B0
```

The official SDK declares `gCScriptRoutine_PS::AISetState(bCString const&)`; Script.dll's `PSRoutine::SetState` wrapper directly imports that routine. The SDK documents SetState as clearing the state stack and resetting state-position/break-block bookkeeping.

The next exact question is:

> **Relative to this native destructive state replacement, when has Gothic's legitimate collision-cleanup opportunity already happened, and when has it been lost?**

B9 is diagnostic-only. Observe player `gCScriptRoutine_PS::AISetState()` ordering against the already-existing AIFullStop, native cleanup, StartRecover and motion diagnostics on:

- clean ordinary completion;
- legitimate Normal/Quick reactions;
- the known bad held-Use2 full-Whirl path.

Do not repair collision at AISetState. If legitimate reaction cleanup can still occur after AISetState, AISetState is too early to be a repair checkpoint even though it proves the old continuation was discarded.

Use `docs/BETWEEN_CHATS.md` for the frozen B9 Work contract.

---

## Relevant Tested Symbols

```text
Game +0x164320 = gCScriptRoutine_PS::AISetState(bCString const&)
Game +0x164430 = gCScriptRoutine_PS::AIFullStop()
Game +0x1644D0 = gCScriptRoutine_PS::AIStopCombatMove()
Game +0x1696E0 = gCScriptProcessingUnit::sAICombatMoveInstr(...)
Game +0x16E360 = gCScriptProcessingUnit::sAICombatMoveStartRecover(...)
Game +0x16F120 = gCScriptProcessingUnit::ProcessScript()
Game +0x16F5B0 = SPU state-changing implementation reached by AISetState
```

Relevant Script_Game points:

```text
+0x2D0F2 / +0x2D0F8  tested legitimate-reaction FullStop call / return
+0x4DF8C              full-Whirl CombatMove break-block operation
+0x4E03C              ordinary full-Whirl cleanup continuation
+0x62FF0              player Use2 helper
+0x633F1 / +0x633F7   held-Use2 FullStop call / return
+0x63409               immediate SetState in held-Use2 abandonment branch
```

All addresses are tested-build-specific.

---

## Future Marker-Core Review — Preserve This Route

Native CombatMove/state-stack lifetime may eventually replace some custom marker lifetime inference, but do not simplify the marker core until the native termination/finalization model is shown to preserve every proven marker regression.

Retrieve:

```text
EVIDENCE_INDEX.md
→ Marker execution lifetime / bookkeeping
→ future marker-core simplification / native execution boundary
→ COLLISION_LIFECYCLE_PLAN.md §10
```

---

## Do Not Do Yet

Until a reliable general finalization mechanism is established:

- do not implement production cleanup/repair;
- do not add lifecycle/pending-finalization state;
- do not add ProcessScript behavior hooks, timers, polling or scans;
- do not add family/cause-specific repair branches;
- do not clean unconditionally at AIFullStop, SetState or AISetState;
- do not treat the held-Use2 player branch as universal for all abnormal endings;
- do not simplify proven marker bookkeeping yet;
- do not move unfinished collision behavior to `main`.

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| current bounded continuation | `BETWEEN_CHATS.md` |
| exact evidence | `EVIDENCE_INDEX.md` → `EVIDENCE_LEDGER_STEP_B.md` |
| native cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| CombatMove/API/symbol/caller lookup | `SOURCE_HOOK_GUIDE.md` |
| marker execution lifetime / future simplification | `EVIDENCE_INDEX.md` Marker execution lifetime → `COLLISION_LIFECYCLE_PLAN.md` §10 |
| diagnostic architecture | `COLLISION_LOGGER_PLAN.md` |
| staged validation | `COLLISION_TEST_PLAN.md` |
| animation semantics/assets | `ANIMATION_INDEX.md` |
| overall Raise/speed/collision architecture | `DESIGN.md` |
| older chronology | `RESEARCH_MAP.md` / archive only when specifically needed |

Do **not** load the whole documentation corpus by default.

---

## After Collision

Broad priority order remains:

1. finish collision lifecycle safety and integrate stable collision behavior;
2. generalize Raise for intended Normal/Quick and selected full-Whirl families;
3. implement/calibrate profile-aware playback speed;
4. later investigate broader animation-selection/gameplay systems such as jumping, wading and climbing.

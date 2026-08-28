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

Confirmed native defect: an offensive attack Hit can lose the ScriptFunction continuation that normally performs collision cleanup. The physical Hit can disappear while the weapon remains `Item_Attack(7)` through Ambient/idle/movement and even into a later independent attack.

Preferred invariant remains:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact Hit genuinely ends or is replaced, if cleanup was observed, do nothing; if not, repair the remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. End-of-Hit safety is one shared execution-level responsibility for marked and native attacks.

Architecture authority: `docs/COLLISION_LIFECYCLE_PLAN.md`.

---

## Established Lifecycle Model

### Ordinary completion

CombatMove persists asynchronously through `gCScriptProcessingUnit::m_pfInstrCallback`; its owning ScriptFunction can remain suspended at a break block.

For tested full Whirl:

```text
CombatMove operation at Script_Game +0x4DF8C
→ incomplete: ScriptFunction returns false / continuation remains suspended
→ later CombatMove completion
→ ScriptFunction resumes after break block
→ ordinary Whirl collision cleanup at +0x4E03C
```

### Legitimate reaction

Tested player Normal/Quick reactions can FullStop the active CombatMove through:

```text
Script_Game +0x2D0F2  PSRoutine::FullStop()
return +0x2D0F8
```

That path continues under reaction control and, when offense had armed, later performs the established reaction cleanup at `Script_Game +0x24AFF`.

### Tested bad full-Whirl block-skip

B7b identifies the exact bad player-control branch:

```text
held Use2 duration > 2500 ms
→ Script_Game +0x633F1  PSRoutine::FullStop()
→ return +0x633F7
→ Script_Game +0x63409  PSRoutine::SetState(...)
```

Runtime bad samples are action 10 / Hit / `PS_Melee_WhirlAttack`, `PressedKey=16`, `IsPressed=1`, `IsPressedBefore=1`; both pre-activation and armed failures use the same FullStop site.

Official SDK documentation states that `SetState` clears the SPU state stack and resets state-position/break-block bookkeeping. Therefore, for this tested failure:

```text
Whirl ScriptFunction suspended at CombatMove break block
→ held-Use2 branch FullStops CombatMove
→ SetState clears the old state stack / break-block continuation
→ old Whirl ScriptFunction cannot resume
→ ordinary +0x4E03C cleanup is never reached
→ no reaction cleanup owner replaces it
→ armed weapon can remain Item_Attack(7)
```

This resolves the causal mechanism for the tested player full-Whirl stale-collision path.

Canonical evidence: current Step-B ledger, B7/B7b raw logs.

B7b raw:

```text
research/raw/2026-08-28_b7b_player_aifullstop_exact_caller_clean_reaction_blockskip.log
```

Raw commit:

```text
9fe85819e44cc33b7d2d6846e24097861b28a8ca
```

---

## Current Gate — Cross-Family Generality

Do **not** generalize the exact full-Whirl `+0x633F1 -> SetState` path to every stale-collision case yet.

Earlier evidence already proves that stale collision is broader than full Whirl, including player Dual Quick. The next smallest question is therefore:

> **Does the already-known Dual Quick bad skip also terminate its active CombatMove through the same AIFullStop/SetState state-stack abandonment mechanism, or through a different native state/task reset path?**

No new implementation is required for this check. The currently deployed B7b diagnostic already observes player `AIFullStop()` callers and the existing collision/motion context.

Use `docs/BETWEEN_CHATS.md` for the current bounded continuation state.

---

## Relevant Tested Symbols

```text
Game +0x164430 = gCScriptRoutine_PS::AIFullStop()
Game +0x1644D0 = gCScriptRoutine_PS::AIStopCombatMove()
Game +0x1696E0 = gCScriptProcessingUnit::sAICombatMoveInstr(...)
Game +0x16E360 = gCScriptProcessingUnit::sAICombatMoveStartRecover(...)
Game +0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

Tested Script_Game control points now relevant:

```text
+0x2D0F2 / +0x2D0F8  legitimate-reaction FullStop call / return
+0x4DF8C              full-Whirl CombatMove break-block operation
+0x4E03C              ordinary full-Whirl cleanup continuation
+0x62FF0              player Use2 helper
+0x633F1 / +0x633F7   tested bad full-Whirl FullStop call / return
+0x63409               immediate SetState in tested bad branch
```

All addresses are tested-build-specific.

---

## Future Marker-Core Review — Preserve This Route

Current marker bookkeeping exists because of reproduced failures involving StatePosition replay, repeated-contact occurrence handling, frame-effect replay, and interrupted-execution budget survival.

Native CombatMove/state-stack lifetime may eventually provide a stronger execution boundary for some custom marker lifetime inference, but do not simplify the marker core until the native termination model is shown to generalize safely and all old marker regressions remain protected.

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
- do not clean unconditionally at AIFullStop or SetState;
- do not treat the tested full-Whirl `+0x633F1` caller as universal;
- do not simplify proven marker bookkeeping yet;
- do not move unfinished collision behavior to `main`.

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| lifecycle architecture / current native-termination model | `COLLISION_LIFECYCLE_PLAN.md` |
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

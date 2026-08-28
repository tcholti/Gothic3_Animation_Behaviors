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

Confirmed native defect: a real offensive attack Hit can be terminated in a way that prevents Gothic 3 from reaching its normal attack cleanup and does not transfer cleanup responsibility elsewhere. The physical Hit can disappear while the weapon remains `Item_Attack(7)` through Ambient/idle and even into a later independent attack.

Preferred invariant remains:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact Hit genuinely ends or is replaced, if cleanup was observed, do nothing; if not, repair the remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. End-of-Hit safety is one shared execution-level responsibility for marked and native attacks.

Architecture authority: `docs/COLLISION_LIFECYCLE_PLAN.md`.

---

## Current Established Lifecycle Facts

### Ordinary completion

A CombatMove persists asynchronously through `gCScriptProcessingUnit::m_pfInstrCallback`. Its owning ScriptFunction can remain suspended at a break block. In the tested full-Whirl function:

```text
Script_Game +0x4DF8C  CombatMove operation
Script_Game +0x4DF92  completion test

incomplete
→ ScriptFunction returns false

complete
→ ScriptFunction continues after break block
→ ordinary Whirl collision cleanup at +0x4E03C
```

Thus collision cleanup is Script_Game continuation after successful asynchronous CombatMove completion, not automatic animation teardown.

### Legitimate reaction

B7 runtime proves that legitimate Normal/Quick reactions can explicitly FullStop the active CombatMove and then continue under reaction ownership. In armed samples, the separate reaction cleanup at `Script_Game +0x24AFF` follows the FullStop and resets the weapon `7 -> 5`.

Representative FullStop path:

```text
sAICombatMoveInstr(fullStop=true)
← Game +0x164441  inside gCScriptRoutine_PS::AIFullStop
← reaction Script_Game chain
```

### Bad block-skip

B7 runtime proves that bad full-Whirl block-skip also explicitly FullStops the active CombatMove. Armed cases can FullStop while the exact Whirl Hit is still current and the right weapon is already group 7, then reach Ambient without StartRecover or any native collision cleanup.

Stable B7 bad unwind:

```text
sAICombatMoveInstr(fullStop=true)
← Game +0x164441
← Script_Game +0x61866
← Game +0x16093B
```

Therefore:

> **FullStop is an instruction-termination boundary, not collision cleanup.**

The difference between legitimate reaction and bad skip is what control/cleanup ownership follows termination.

Canonical evidence: EV-182–EV-186.

B7 raw:

```text
research/raw/2026-08-28_b7_player_combatmove_fullstop_clean_reaction_blockskip.log
```

Raw commit:

```text
49e99a933ce2bb02ae6434ec077fb7f549b1f7f5
```

---

## Current Gate — B7b Exact AIFullStop Caller

Static reconstruction of `Script_Game +0x61866` has now identified the higher-level bad control path.

### Player-control dispatcher

The dispatcher reads `PSCharacterControl::PressedKey`. For key values 1–16 it uses a jump table. Official SDK enum mapping establishes:

```text
gESessionKey_Use1 = 15
gESessionKey_Use2 = 16
```

The relevant routes are:

```text
Use1
→ helper Script_Game +0x62480
→ return at Script_Game +0x61852

Use2
→ helper Script_Game +0x62FF0
→ return at Script_Game +0x61866
```

The bad Whirl B7 stack therefore identifies the **Use2 player-control helper**, not the Whirl attack ScriptFunction itself.

### Use2 helper

Tested-binary static inspection finds exactly three imported `PSRoutine::FullStop()` calls inside `Script_Game +0x62FF0`:

```text
Script_Game +0x63108
Script_Game +0x633F1
Script_Game +0x6345F
```

They sit behind different combinations of current routine-state checks and CharacterControl button-edge / press-duration conditions. One branch explicitly tests `IsPressed == true` and `IsPressedBefore == false` before FullStop. Other branches use different state/duration conditions.

The existing B7 `CaptureStackBackTrace` collapses optimized helper frames and only exposes the common caller return `+0x61866`. Static evidence therefore cannot identify which of the three exact FullStop sites caused an individual bad Whirl event.

### Exact unresolved question

> **Which exact `PSRoutine::FullStop()` call inside the Use2 helper terminates the bad Whirl CombatMove, what factual routine/input state accompanies it, and how does that exact caller compare with legitimate reaction FullStop?**

The smallest discriminating observation is now `gCScriptRoutine_PS::AIFullStop()` itself at tested `Game +0x164430`, using `_ReturnAddress()` plus factual player routine/input context.

The bounded B7b Work task is frozen in `docs/BETWEEN_CHATS.md`.

---

## Relevant Authoritative SDK Facts

```text
Game +0x164430 = gCScriptRoutine_PS::AIFullStop()
Game +0x1644D0 = gCScriptRoutine_PS::AIStopCombatMove()
Game +0x1696E0 = gCScriptProcessingUnit::sAICombatMoveInstr(...)
Game +0x16E360 = gCScriptProcessingUnit::sAICombatMoveStartRecover(...)
Game +0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

Official SDK exposes:

- `void gCScriptRoutine_PS::AIFullStop();`
- `eCEntityPropertySet::GetEntity()`;
- `PSRoutine::GetCurrentState()` / StateTime / StatePosition;
- `PSCharacterControl::PressedKey`;
- `PSCharacterControl::IsPressed`;
- `PSCharacterControl::IsPressedBefore`;
- `PSCharacterControl::DurationPressedMSecs`.

Do not guess layouts when these authoritative APIs/properties exist.

---

## Future Marker-Core Review — Preserve This Route

Current marker bookkeeping exists because of reproduced failures: StatePosition replay, repeated-contact occurrence handling, frame-effect replay, and interrupted-execution budget survival.

Native CombatMove termination may eventually provide a stronger execution boundary for some custom marker lifetime inference, but B7 also proves FullStop alone does **not** tell us whether physical collision should be repaired immediately.

When marker consolidation becomes active, retrieve:

```text
EVIDENCE_INDEX.md
→ Marker execution lifetime / bookkeeping
→ future marker-core simplification / native execution boundary
→ COLLISION_LIFECYCLE_PLAN.md §10
```

Preserve the old regression reasons and the newer native lifecycle evidence together.

---

## Do Not Do Yet

Until a reliable general post-native-opportunity finalization mechanism is established:

- do not implement production cleanup/repair;
- do not add lifecycle/pending-finalization state;
- do not add ProcessScript behavior hooks, timers, polling or scans;
- do not add family/cause-specific repair branches;
- do not treat FullStop alone as proof that immediate collision repair is correct;
- do not treat action/phase/filename/StopMotion/StartRecover alone as universal lifetime authority;
- do not simplify proven marker bookkeeping yet;
- do not move unfinished collision behavior to `main`.

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| lifecycle architecture / B7+ model | `COLLISION_LIFECYCLE_PLAN.md` |
| current bounded Work task | `BETWEEN_CHATS.md` |
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

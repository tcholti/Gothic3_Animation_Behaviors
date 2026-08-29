# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-29

`docs/collision-source-evidence` contains the newest collision research/prototype state. `main` is the stable integration baseline.

Document roles / Hot-Warm-Cold retrieval: `docs/README.md`  
Transient Chat ↔ Work handoff when relevant: `docs/BETWEEN_CHATS.md`  
Recurring Git/build/deploy/test/log procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` only when the current responsibility depends on an active/recent transient handoff.
3. If the active subsystem is not already oriented in the current Chat, perform the one-time Subsystem Orientation Pass from `docs/README.md`.
4. Read `docs/PROJECT_OPERATING_PROCEDURES.md` once when entering an active local Git/build/deploy/runtime-artifact sequence; do not reread it after every prompt.
5. Do not scan the whole repository or reconstruct the project from old chat history.
6. Retrieve only the deeper authority listed under **Retrieval — Only What the Question Needs**.

Within one continuing subsystem context, do not repeatedly reread unchanged authorities or procedures.

---

## Active Subsystem

**Frame-controlled melee collision lifecycle.**

Preferred invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if cleanup was observed, do nothing; if not, repair only that execution's remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. End-of-execution safety is one shared execution-level responsibility for marked and native attacks.

Architecture authority: `docs/COLLISION_LIFECYCLE_PLAN.md`.

Production repair is still **disabled**.

---

## C1 Shadow Guard — Implemented and Core Runtime-Tested

C1 is an event-driven **shadow-only** execution/source obligation model. It tracks real offensive `Item_Attack` requests, including inherited `7 -> 7`, observes native cleanup, and reports `WOULD_REPAIR` at destructive AISetState finalization without physically changing collision.

Key implementation/review commits:

```text
3778517f421d07e940c620745bc7ccdf0da54313  C1 implementation
f04c3e18f4129e0ee7727a3f266d6fc55fb13a8c  independent source review PASS
```

Local validation completed:

```text
build PASS
single live DLL PASS
built/live SHA256 match PASS
startup/load banner PASS
```

Core runtime raw evidence:

```text
research/raw/2026-08-28_c1_shadow_core_lifecycle_matrix.log
raw commit: a3c41c829a0e7d083ccfc657eafc285f68b60d4b
```

Derived retrieval extract:

```text
research/archive/2026-08-28_c1_shadow_core_lifecycle_matrix_connector_extract.txt
extract commit: e5d8da1323b3c43c52ce0f58ea010081e00a364f
```

### Core result

The shadow classification itself behaved strongly in the tested matrix:

- **8 actual `WOULD_REPAIR` outcomes** were accounted for by known armed bad held-Use2 abandonments:
  - 1 full Whirl;
  - 7 Dual Quick;
- clean ordinary completions did not become repair candidates;
- tested pre-activation bad skips did not become repair candidates;
- tested legitimate reaction interruptions cleaned natively and did not become repair candidates;
- the inherited-stale control passed:
  - one bad Whirl left the real weapon physically at group 7;
  - the next Normal attack requested `7 -> 7` on the same weapon;
  - C1 attributed that request to the **new** generation;
  - native cleanup later reset `7 -> 5`;
  - the new generation finalized as no-op.

This validates the consequence-based obligation model for those paths without requiring family/cause-specific repair logic.

---

## New C1 Boundary Finding — CombatMove Start Is Too Late Universally

The same runtime matrix produced **11 `UNOWNED_PLAYER_OFFENSE_REQUEST` warnings** during knockdown/GetUp-related handling.

Narrow static inspection confirmed this is not random logger noise:

```text
GetUpAttack Script_Game region
+0x41CA6  weapon can be set to Item_Attack(7)
+0x41D5A  later call to the same CombatMove import used by full Whirl
+0x41E10  known later GetUpAttack cleanup to Item_Equipped(5)
```

Therefore some legitimate collision-owning attack ScriptFunction work begins **before** the current C1 `new CombatMove initial invocation` boundary.

Important consequence:

```text
CombatMove start
= strong inner asynchronous-instruction boundary
≠ universal outer collision-owning attack-execution start
```

Do **not** fix this with a GetUpAttack/action-30 special case.

Do **not** simply adopt an already-equipped group-7 weapon when CombatMove begins; that would blur legitimate pre-CombatMove arming with inherited stale collision from a previous broken execution.

---

## Current Gate — Find the General Outer Execution Identity

Normal Chat's current question is:

> **Does Gothic 3 expose a stable ScriptFunction/SPU execution identity or native boundary above CombatMove that already exists when a pre-CombatMove offensive request occurs and remains identifiable when the later CombatMove instruction begins?**

Preferred route:

```text
pre-CombatMove real offense request
→ bind to exact native ScriptFunction/SPU execution identity
→ later CombatMove belongs to that same execution
→ native cleanup fulfills obligation if observed
→ destructive abandonment finalizes only that execution
```

If source/static evidence cannot identify such a stable identity directly, freeze the smallest factual diagnostic needed to compare the relevant SPU/ScriptFunction identity at:

1. the unowned offensive request;
2. the later CombatMove entry;
3. cleanup/finalization.

### Current constraints

- no production physical repair yet;
- no GetUpAttack/action/family ownership table;
- no input-key/cause classifier;
- no unconditional cleanup on FullStop/AISetState;
- no adoption of arbitrary pre-existing group 7 as ownership proof;
- no timers, polling, world scans or per-frame repair;
- preserve all existing marker occurrence/execution/source bookkeeping;
- Fist/body semantics remain separate from weapon-style `Item_Attack` ownership.

Do not start another bounded implementation until Normal Chat freezes the next exact boundary/diagnostic question.

---

## Relevant Tested Native Points

```text
Game +0x164320 = gCScriptRoutine_PS::AISetState(bCString const&)
Game +0x164430 = gCScriptRoutine_PS::AIFullStop()
Game +0x1696E0 = gCScriptProcessingUnit::sAICombatMoveInstr(...)
Game +0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

Known bad held-Use2 abandonment:

```text
Script_Game +0x633F1 / +0x633F7  FullStop call / observed return
Script_Game +0x63409            immediate SetState in bad branch
```

GetUpAttack boundary evidence:

```text
Script_Game +0x41CA6  pre-CombatMove Item_Attack request region
Script_Game +0x41D5A  CombatMove call
Script_Game +0x41E10  ordinary cleanup
```

All addresses are tested-build-specific.

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| current outer-lifetime / cleanup architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| transient exact continuation | `BETWEEN_CHATS.md` when needed |
| recurring Git/build/deploy/test/log procedure | `PROJECT_OPERATING_PROCEDURES.md` |
| exact evidence | `EVIDENCE_INDEX.md` → `EVIDENCE_LEDGER_STEP_B.md` |
| native cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| SPU / CombatMove / source/API/symbol lookup | `SOURCE_HOOK_GUIDE.md` + pinned SDK/static reference as needed |
| diagnostic architecture | `COLLISION_LOGGER_PLAN.md` |
| staged validation | `COLLISION_TEST_PLAN.md` |
| marker execution lifetime / future simplification | `EVIDENCE_INDEX.md` Marker execution lifetime → `COLLISION_LIFECYCLE_PLAN.md` |
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

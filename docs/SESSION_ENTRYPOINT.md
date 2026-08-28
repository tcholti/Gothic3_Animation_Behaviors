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

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if cleanup was observed, do nothing; if not, repair only that execution's remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. End-of-Hit safety is one shared execution-level responsibility for marked and native attacks.

Architecture authority: `docs/COLLISION_LIFECYCLE_PLAN.md`.

---

## Established Native Failure Model

CombatMove is asynchronous. The owning ScriptFunction can remain suspended at a break block while `sAICombatMoveInstr` persists in the SPU.

Ordinary completion resumes the owning ScriptFunction into its action-specific cleanup. Tested full Whirl reaches cleanup at `Script_Game +0x4E03C` only after its CombatMove break block completes.

The known bad player held-Use2 path instead does:

```text
Use2 held beyond 2500 ms
→ Script_Game +0x633F1 calls PSRoutine::FullStop()
→ active CombatMove receives fullStop=true
→ Script_Game +0x63409 calls PSRoutine::SetState(...)
→ native AISetState destroys/replaces the old SPU state-stack continuation
→ the suspended attack ScriptFunction can no longer resume into ordinary cleanup
→ if offense had armed, Item_Attack(7) can survive into successor state/motion
```

B8 proves this is not full-Whirl-specific: tested player Quick attacks with Dual (1H+1H), plain 1H and Shield+1H use the same held-Use2 abandonment path and can retain armed collision afterward.

Important qualification: this establishes one shared tested stale class, not every possible NPC/terrain/abnormal-ending cause.

---

## B9 Finalization Ordering Result

B9 observes tested:

```text
Game +0x164320 = gCScriptRoutine_PS::AISetState(bCString const&)
```

before the original destructive state replacement.

### Bad held-Use2 path

Representative armed full-Whirl ordering:

```text
AIFullStop / +0x633F1 branch
→ CombatMove fullStop
→ AISetState entered almost immediately
   old attack Hit/state context still visible
   equipped weapon still Item_Attack(7)
→ no legitimate native cleanup intervened
```

### Ordinary successful completion

Tested clean full Whirl, Normal and Quick:

```text
CombatMove terminal / Recover path
→ ordinary action-specific native cleanup 7 -> 5
→ later AISetState(...PS_Melee_Loop)
```

### Legitimate reaction interruption

Tested armed Normal/Quick reactions:

```text
AIFullStop
→ CombatMove fullStop
→ separate reaction cleanup +0x24AFF resets 7 -> 5
→ reaction successor
```

No AISetState intervenes before the legitimate cleanup in those tested samples. B9 also confirms more than one legitimate-reaction FullStop caller (`+0x2D0F8` and `+0x2B8CB` observed), so no single reaction call-site classifier is authoritative.

**Engineering consequence:** destructive AISetState is now a strong tested **post-cleanup-opportunity / abandonment checkpoint** for the known held-Use2 stale class. It is still generic script-state infrastructure and must not become an unconditional cleanup hook.

B9 raw:

```text
research/raw/2026-08-28_b9_player_aisetstate_cleanup_ordering.log
```

B9 raw commit:

```text
ae0a78787cb811f9de551997505ea4bd14370846
```

---

## Pierce Raise Subtest — Qualification

B9 contains repeated plain-1H and Dual Pierce `Raise -> Hit` sequences. However, no `AIFULLSTOP CALLSITE` record was captured while `PS_Melee_PierceAttack` was active; the held-Use2 `+0x633F7` events around those attempts occurred in `PS_Melee_Loop` before/after the Pierce execution.

Therefore this indexed B9 run does **not** newly prove a destructive bad skip inside Pierce Raise. Preserve the user's earlier/repeated runtime observation that Raise may still proceed to Hit after a skip as an observation until directly reproduced under indexed diagnostics.

The user also repeatedly observes that a bad skip during Hit stops the attack's native forward movement. This is consistent with CombatMove termination, but displacement was not instrumented, so keep it as repeated runtime observation rather than log-proven positional evidence.

---

## Current Gate — C1 Execution-Level Guard Design

The former gate was to find a general event-driven finalization mechanism. B8/B9 satisfy that research gate strongly enough for the tested known stale class to begin **designing** C1.

Do not start Work yet. Normal Chat must first freeze the smallest production state/transition model.

The design target is:

```text
exact attack-Hit execution X
→ X actually requests offensive collision
→ remember an outstanding cleanup obligation for X
→ Gothic native cleanup observed?
     YES → obligation fulfilled; no-op
     NO  → keep obligation
→ CombatMove termination / destructive AISetState abandons X
→ if obligation still outstanding at the proven finalization checkpoint
     repair only X's remaining offensive source(s)
→ retire X lifecycle state
```

Design requirements:

- event-driven only;
- no family/cause-specific repair matrix;
- no input-key classifier;
- no polling, timer or world/per-frame scan;
- no unconditional cleanup on AIFullStop/AISetState;
- track an actual offensive request, including `7 -> 7` requests that may inherit stale state;
- native `7 -> 5` cleanup must fulfill/retire the obligation before fallback;
- exact equipped physical source ownership must be preserved;
- intentional marker OFF/source switching remains intra-Hit behavior, not terminal retirement;
- existing callback suppression, StatePosition advancement, occurrence/replay protection and marker execution bookkeeping must remain intact;
- Fist/body semantics remain separate from weapon-style Item_Attack ownership.

Use `docs/BETWEEN_CHATS.md` for the current C1 design handoff.

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
+0x24AFF              established reaction-side collision cleanup
+0x2B8CB              additional tested legitimate-reaction AIFullStop return
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

Native CombatMove/state-stack lifetime may eventually replace some custom marker lifetime inference, but do not simplify the marker core until the C1 lifecycle guard is validated and every proven marker regression remains protected.

Retrieve:

```text
EVIDENCE_INDEX.md
→ Marker execution lifetime / bookkeeping
→ future marker-core simplification / native execution boundary
→ COLLISION_LIFECYCLE_PLAN.md
```

---

## Do Not Do Yet

Until the C1 state/transition design is frozen:

- do not implement production cleanup/repair;
- do not add an ad-hoc pending-finalization flag without exact lifecycle rules;
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
| lifecycle architecture / C1 design | `COLLISION_LIFECYCLE_PLAN.md` |
| current bounded continuation | `BETWEEN_CHATS.md` |
| exact evidence | `EVIDENCE_INDEX.md` → `EVIDENCE_LEDGER_STEP_B.md` |
| native cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| CombatMove/API/symbol/caller lookup | `SOURCE_HOOK_GUIDE.md` |
| marker execution lifetime / future simplification | `EVIDENCE_INDEX.md` Marker execution lifetime → `COLLISION_LIFECYCLE_PLAN.md` |
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

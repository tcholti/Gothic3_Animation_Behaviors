# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-29

`docs/collision-source-evidence` contains the newest collision research/prototype state. `main` is the stable integration baseline.

Document roles / Hot-Warm-Cold retrieval: `docs/README.md`  
Transient Chat ↔ Work handoff when relevant: `docs/BETWEEN_CHATS.md`  
Stable naming/numbering/version/test/artifact conventions: `docs/PROJECT_PIPELINE.md`  
Recurring Git/build/deploy/test/log procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` only when the current responsibility depends on an active/recent transient handoff.
3. If the active subsystem is not already oriented in the current Chat, perform the one-time Subsystem Orientation Pass from `docs/README.md`.
4. Read `docs/PROJECT_OPERATING_PROCEDURES.md` once when entering an active local Git/build/deploy/runtime-artifact sequence; do not reread it after every prompt.
5. Before assigning or changing a gate/test ID, evidence/procedure ID, raw/derived filename, prototype/build/version label, branch/state meaning, or validation/artifact-flow convention, retrieve the relevant section of `docs/PROJECT_PIPELINE.md`. Preserve the established convention unless there is a deliberate reason to change it.
6. Do not scan the whole repository or reconstruct the project from old chat history.
7. Retrieve only the deeper authority listed under **Retrieval — Only What the Question Needs**.

Within one continuing subsystem context, do not repeatedly reread unchanged authorities, procedures, or pipeline conventions.

A Chat migration is not a reason to rename, renumber, restart, or reinterpret project conventions.

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

Core runtime evidence:

```text
research/raw/2026-08-28_c1_shadow_core_lifecycle_matrix.log
raw commit: a3c41c829a0e7d083ccfc657eafc285f68b60d4b
research/archive/2026-08-28_c1_shadow_core_lifecycle_matrix_connector_extract.txt
extract commit: e5d8da1323b3c43c52ce0f58ea010081e00a364f
```

### Core result

- **8 actual `WOULD_REPAIR` outcomes** were accounted for by known armed bad held-Use2 abandonments: 1 full Whirl and 7 Dual Quick;
- clean ordinary completions did not become repair candidates;
- tested pre-activation bad skips did not become repair candidates;
- tested legitimate reaction interruptions cleaned natively and did not become repair candidates;
- inherited-stale control passed: bad Whirl left group 7, the next Normal execution legitimately requested `7 -> 7`, C1 attributed that request to the **new** generation, and later native `7 -> 5` cleanup fulfilled the new generation.

The remaining defect exposed by this matrix was acquisition: GetUpAttack can legitimately request `Item_Attack(7)` before CombatMove begins, so CombatMove cannot be the universal outer execution start.

---

## C1-O1 — Outer ScriptFunction Lifetime Probe Resolved the Identity Gate

Implementation and evidence:

```text
54a64552514f4d6795b4a51cbad7848b5df3795b  C1-O1 diagnostic implementation
research/raw/2026-08-29_c1o1_outer_scriptfunction_identity_probe.log
raw commit: adf6a6102007c56f7502b01072acbe00bcbc35a4
research/archive/2026-08-29_c1o1_outer_scriptfunction_identity_probe_connector_extract.txt
extract commit: 5da094a0c2d6fc58fe260933799a76e43ef7d1d3
```

### Runtime result

C1-O1 positively identified a usable native outer **lifetime**, with an important qualification about identity tokens.

Representative GetUpAttack:

```text
pre-CombatMove Item_Attack request
→ top frame = _AI_GetUpAttack
→ later CombatMove initial invocation
→ same SPU / same live ScriptFunction / same non-null m_pArguments
→ later cleanup
→ same live _AI_GetUpAttack frame; break block advanced
```

Repeated GetUp executions used different argument pointers, confirming distinct live executions.

Clean Normal/Whirl likewise retained the same attack ScriptFunction frame through CombatMove/offense/cleanup and removed it before the later enclosing state transition.

Bad full Whirl retained `_AI_WhirlAttack` at `AI_SET_STATE_BEFORE`; `AI_SET_STATE_AFTER` no longer contained that frame, and no cleanup occurred between those observations.

### Critical qualification — pointer reuse

`m_pArguments` and the stack-entry address are **not globally unique execution IDs**. C1-O1 observed an address reused by a later different ScriptFunction shortly after the previous frame was retired.

Therefore:

```text
raw frame/arguments address
= lifetime-bound correlator only
≠ permanent execution identity
```

C1's own monotonic generation remains the durable plugin-side execution identity. Any native frame correlator must be explicitly retired before address reuse.

The tested attack ScriptFunction snapshots used non-null argument pointers. Null argument records were observed for ScriptStates; future relevant null-argument ScriptFunctions must fail diagnostically rather than be guessed into ownership.

---

## Static Follow-Up — General Pre-CombatMove Actor/SPU Context

Pinned SDK and tested Game.dll establish:

```text
gCScriptAdmin::RunScriptFunction(..., stateStack, spu)
    receives the exact SPU
    → spu->GetSelfEntity() exposes the actor
    → calls the registered ScriptFunction at Game +0x1605E9
    → Game +0x1605EB is the first instruction after that ScriptFunction call
```

When the ScriptFunction returns false because asynchronous work remains active, the state-stack frame is retained. When it returns true, the tested runner removes the completed top frame before returning.

`gCScriptAdmin` does not expose a documented public accessor that can safely be treated as “the currently executing NPC SPU”; its protected admin `m_SPU` must not be substituted for the explicit per-dispatch SPU without evidence.

`RunScriptFunction` is **generic infrastructure**. It must not become combat ownership or unconditional cleanup authority. Its only proposed C1-O2 role is a narrow transient execution context so a synchronous pre-CombatMove `Item_Attack` request can be tied to the exact actor/SPU that is executing it.

---

## Current Gate — C1-O2 Shadow Outer-Frame Binding Integration

The next bounded question is:

> **Can C1 bind its existing monotonic generation to the live outer ScriptFunction frame, acquire a generation when a legitimate equipped-weapon offense occurs before CombatMove, reuse that same generation when the later CombatMove begins, and retire the native frame binding before address reuse without changing the already-passed cleanup/finalization classification?**

Frozen semantic direction:

```text
ordinary path
→ existing new-CombatMove candidate behavior remains available
→ attach current live outer ScriptFunction correlator

pre-CombatMove weapon offense
→ only while inside the exact RunScriptFunction dispatch context
→ actor comes from supplied SPU
→ source must be that actor's exact currently equipped LEFT/RIGHT weapon entity
→ successful Item_Attack request creates/binds the C1 generation if none already owns that live frame

later CombatMove
→ same actor + same still-live outer frame = reuse existing generation
→ different/no binding = preserve existing new-candidate behavior

cleanup
→ remains source/consequence based; current frame need not match

RunScriptFunction true return
→ retire that native frame binding before pointer reuse
→ if its bound generation still has an outstanding obligation, log a shadow invariant/candidate for investigation
→ do NOT physically repair and do NOT yet promote true return to production finalization authority

AISetState
→ preserve existing C1 shadow destructive-finalization behavior
```

`m_pArguments` may participate only as part of a **live-frame correlator** together with exact SPU and ScriptFunction context. Script name/action/family/input must not become attack classifiers.

### Current constraints

- no production physical repair;
- no GetUpAttack/action/family ownership table;
- no input-key/cause classifier;
- no unconditional cleanup on RunScriptFunction return, FullStop or AISetState;
- no adoption of arbitrary pre-existing group 7;
- no timers, polling, world scans or per-frame repair;
- preserve all existing marker occurrence/execution/source bookkeeping;
- preserve the C1 core source-obligation semantics, including `7 -> 7` attribution;
- Fist/body semantics remain separate from weapon-style `Item_Attack` ownership;
- generic `RunScriptFunction` context must stay minimal/nesting-safe and call its original exactly once.

The exact frozen implementation handoff lives in `BETWEEN_CHATS.md` while C1-O2 Work is active.

---

## Relevant Tested Native Points

```text
Game +0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
Game +0x1605E9 = indirect registered ScriptFunction call
Game +0x1605EB = first instruction after that call
Game +0x164320 = gCScriptRoutine_PS::AISetState(bCString const&)
Game +0x164430 = gCScriptRoutine_PS::AIFullStop()
Game +0x1696E0 = gCScriptProcessingUnit::sAICombatMoveInstr(...)
Game +0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

GetUpAttack boundary evidence:

```text
Script_Game +0x41CA6  pre-CombatMove Item_Attack request region
Script_Game +0x41D5A  later CombatMove call
Script_Game +0x41E10  ordinary cleanup
```

All addresses are tested-build-specific.

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| current outer-lifetime / cleanup architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| transient exact C1-O2 Work handoff | `BETWEEN_CHATS.md` |
| naming/numbering/version/test/artifact conventions | `PROJECT_PIPELINE.md` relevant section only |
| recurring Git/build/deploy/test/log procedure | `PROJECT_OPERATING_PROCEDURES.md` |
| exact evidence | `EVIDENCE_INDEX.md` → `EVIDENCE_LEDGER_STEP_B.md` |
| native cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| SPU / ScriptFunction / CombatMove / hook lookup | `SOURCE_HOOK_GUIDE.md` + pinned SDK/static reference as needed |
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

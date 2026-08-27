# Session Entry Point

**Purpose:** Minimal durable front door for the current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper project knowledge only as the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-27

`docs/collision-source-evidence` contains the newest collision research, prototype implementation, and current continuation state. `main` is the stable integration/reusable knowledge baseline and should not be assumed to contain the latest collision implementation until a deliberate stable integration occurs.

For document roles and Hot/Warm/Cold retrieval, see `docs/README.md`.

For the latest real Chat/Work transition, read `docs/BETWEEN_CHATS.md` only when that transient bridge is relevant.

---

## Minimum Context for Current Work

Normally start with this file plus the exact current evidence/source supplied by the User or named below.

Do not automatically reread the full evidence ledgers, research map, design, hook guide, animation catalog, or raw logs between prompts.

Use targeted section/evidence/symbol searches when an exact technical detail is needed.

---

## Project Scope

Technical engine-facing work in this repository is authorized offline modding/reverse-engineering of the 2006 single-player game Gothic 3 using community SDK tooling. The target is the User's local game installation and the project's own mod/research DLLs.

Reusable scope guidance: `docs/PROJECT_SCOPE_CONTEXT.md`.

---

## Active Subsystem

**Frame-controlled melee collision lifecycle.**

Known native defect: an offensive Hit can lose enough CombatMove/action ownership/bookkeeping that the physical Hit motion continues or later replaces while Gothic 3 fails to run normal collision cleanup. This is confirmed natively and is not introduced by frame markers.

Preferred invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact Hit genuinely ends or is replaced, if cleanup was observed, do nothing; if not, repair the remaining offensive collision using native cleanup semantics.**

Marker control changes collision inside a live Hit; end-of-Hit cleanup should remain one shared invariant for marked and native attacks.

Current collision architecture authority: `docs/COLLISION_LIFECYCLE_PLAN.md`.

---

## Established Step-B Results

Canonical continuation evidence: `docs/EVIDENCE_LEDGER_STEP_B.md`, EV-158 onward.

Detailed native cleanup map: `docs/COLLISION_CLEANUP_CALLSITE_MAP.md`.

Current established results relevant to the next task:

1. `eCVisualAnimation_PS::PlayMotion(type 0)` is an immediate PrimaryFirst replacement signal, but clean successor Recover PlayMotion can occur before later native cleanup; replacement itself is too early for immediate repair.
2. Later original attack callbacks and `sAICombatMoveStartRecover` are not reliable universal post-cleanup boundaries.
3. Missing Recover assets are not the root cause; native Dual/Quick/Whirl cases reproduce the stale-collision structure.
4. Successful native completion cleanup is action-specific inside `Script_Game.dll`; legitimate damage/reaction interruption has a separate tested cleanup path at `Script_Game + 0x24AFF`.
5. B5 stack capture reached generic script execution:

```text
Game + 0x1603D0 = gCScriptAdmin::RunScriptState(...)
Game + 0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
Game + 0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

These are not themselves combat-specific cleanup owners.

6. Tested `gCScriptProcessingUnit::sAICombatMoveInstr` at `Game + 0x1696E0` is also too early: CombatMove instruction completion can occur before action-specific Script_Game code performs native weapon `7 -> 5` cleanup.
7. Static comparison found no common immediate Script_Game post-cleanup helper across Normal/Quick/full Whirl.

Do not reread the complete ledgers to use these established results unless a detail must be verified or challenged.

---

## Current Design Candidate

```text
exact owned offensive Hit replacement observed
→ mark exact execution pending-finalization
→ let Gothic finish the current native script dispatch
→ at one tightly gated post-script opportunity:
       native cleanup observed → no-op
       cleanup absent          → repair
```

The generic script boundary would provide timing only. It must never define attack ownership by itself.

This remains a candidate until the current causal test establishes whether the relevant replacement paths share a suitable script-processing boundary.

---

## Step B6 — Current Frozen Task / Validation Boundary

The bounded B6 implementation has been source-reviewed and committed. Current transient details and exact commit references are in `docs/BETWEEN_CHATS.md`.

The B6 probe uses only the existing player/type-0 `PlayMotion` hook to capture a short supported Win32 stack for an **actual** attack-Hit PrimaryFirst replacement/restart.

No production cleanup is implemented.

### Home-PC validation still required

Establish:

1. DLL builds and loads;
2. stack capture/module resolution behaves as expected;
3. clean Hit -> Recover replacement stack;
4. legitimate damage/reaction replacement stack;
5. bad block-skip direct replacement stack with missing native cleanup;
6. whether those replacement paths share one useful SPU / `ProcessScript()` execution context.

### B6 question

> **Do all relevant replacement events occur inside the same SPU / `ProcessScript()` invocation so that a later one-shot post-script check is guaranteed to run after Gothic's native cleanup opportunity?**

Do not implement production cleanup until this question is resolved sufficiently.

---

## After the Lifecycle Architecture Is Proven

Before release, test negative/regression cases if the final design uses a generic SPU/script timing checkpoint, especially:

- Fist;
- bow;
- crossbow;
- magic.

Fist is especially important because it can share ordinary melee action enums while not using the tested weapon-style `Item_Attack(7)` source request. Action enum alone must not define ownership.

Research order remains:

1. finish the universal execution-level collision safety rule;
2. later, if worthwhile, investigate the deeper block-skip/CombatMove teardown itself;
3. preserve useful animation/CombatMove discoveries for broader Gothic 3 modding knowledge without diverting the active collision work prematurely.

---

## Current Collaboration / Implementation Route

For normal project collaboration use `docs/COLLABORATION_RULES.md`.

For a bounded Work/source task use `docs/WORK_IMPLEMENTATION_PROTOCOL.md`.

The default is selective retrieval:

```text
this entry point
→ exact current task / source
→ task-specific authority
→ deeper evidence/reference only when needed
```

Do not make a new session reconstruct the whole project before it can continue the current responsibility.

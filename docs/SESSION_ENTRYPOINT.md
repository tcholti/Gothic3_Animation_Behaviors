# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-27

`docs/collision-source-evidence` contains the newest collision research/prototype state. `main` is the stable integration and reusable Gothic 3 knowledge baseline.

Document roles / Hot-Warm-Cold retrieval: `docs/README.md`  
Latest transient Chat/Work bridge, only when relevant: `docs/BETWEEN_CHATS.md`

---

## Active Subsystem

**Frame-controlled melee collision lifecycle.**

Confirmed native defect: a real offensive Hit can lose enough CombatMove/action bookkeeping that the physical Hit continues or later replaces while Gothic 3 fails to run normal collision cleanup. This defect is native and is not introduced by frame markers.

Preferred invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact Hit genuinely ends or is replaced, if cleanup was observed, do nothing; if not, repair the remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. End-of-Hit safety should be one shared invariant for marked and native attacks.

Current architecture: `docs/COLLISION_LIFECYCLE_PLAN.md`.

---

## Step-B Facts Needed Now

- type-0 `eCVisualAnimation_PS::PlayMotion` gives immediate PrimaryFirst acquisition/replacement evidence, but clean successor PlayMotion can occur **before** native cleanup;
- later original attack callbacks are not one-shot completion boundaries;
- `sAICombatMoveStartRecover` is too early and can be bypassed;
- missing Recover assets are not the root cause;
- successful ordinary cleanup is action-specific inside `Script_Game.dll`;
- tested damage/reaction interruption uses a separate cleanup route at `Script_Game + 0x24AFF`;
- B5/static identification reached generic script infrastructure:

```text
Game + 0x1603D0 = gCScriptAdmin::RunScriptState(...)
Game + 0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
Game + 0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

- `sAICombatMoveInstr` is also too early;
- no common immediate Script_Game post-cleanup helper has been demonstrated across tested ordinary families.

These generic script functions are **not combat ownership authority**.

Exact evidence/RVAs: `EVIDENCE_INDEX.md` and `COLLISION_CLEANUP_CALLSITE_MAP.md`.

---

## Current Candidate

```text
exact owned offensive Hit replacement/restart observed
→ mark that exact execution pending-finalization
→ let Gothic finish current native script dispatch
→ at one tightly gated post-script opportunity:
     native cleanup observed -> no-op
     cleanup absent          -> repair
```

A generic script layer may provide **timing only**. Exact attack execution ownership and its offensive-collision request must already exist.

This remains a hypothesis.

---

## Current Gate — B6 Runtime Validation

B6 source instrumentation is implemented and independently source-reviewed. No production cleanup and no new Gothic hook were added.

The current Win32 Release source built successfully on the authoritative home PC at branch commit `d0863b15ad4ef5ff777b7f75330f18737c45e023`. The installed active DLL matched the built SHA-256 and the game loaded/exited normally.

B6 reuses the existing player/type-0 `PlayMotion` hook and emits a short Win32 stack only after existing before/after PrimaryFirst evidence confirms an actual outgoing attack-Hit replacement/restart.

The first B6-B clean-control runtime attempt is **invalid for lifecycle interpretation**: a backup `Script_FrameCollisionTest.preB6.dll.bak` left in the live Gothic 3 `scripts` directory participated in hook execution, duplicating diagnostics. See EV-173. The backup must be moved outside the live `scripts` directory before retesting.

Next responsibility:

1. isolate the live script environment so only the intended `Script_FrameCollisionTest.dll` is present from this prototype;
2. rerun B6-B clean Hit -> Recover control;
3. if clean, continue to legitimate damage/reaction replacement;
4. then test bad block-skip direct replacement with missing cleanup.

Question:

> **Do the relevant replacement paths occur inside one useful SPU / `ProcessScript()` invocation so a tightly gated one-shot checkpoint can reliably run after Gothic's native cleanup opportunity?**

Exact procedure/interpretation: `COLLISION_TEST_PLAN.md` Gate B6.

---

## Do Not Do Yet

Until B6 answers the boundary question:

- do not implement production cleanup;
- do not hook `ProcessScript` as unconditional behavior;
- do not add family/cause-specific repair branches;
- do not add timers/polling;
- do not treat action/phase alone as continuing physical Hit lifetime authority;
- do not move unfinished collision implementation to `main`.

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| diagnostics | `COLLISION_LOGGER_PLAN.md` |
| current test gates | `COLLISION_TEST_PLAN.md` |
| exact evidence | `EVIDENCE_INDEX.md` |
| cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| hook/API/symbol lookup | `SOURCE_HOOK_GUIDE.md` |
| animation semantics/assets | `ANIMATION_INDEX.md` |
| overall Raise/speed/collision architecture | `DESIGN.md` |
| older chronology | `RESEARCH_MAP.md` / archive only if needed |

Do **not** load the whole documentation corpus by default.

---

## After Collision

Broad priority order remains:

1. finish collision lifecycle safety and integrate stable collision behavior;
2. generalize Raise for intended Normal/Quick and selected full-Whirl families;
3. implement/calibrate profile-aware playback speed;
4. later investigate broader animation-selection/gameplay possibilities such as jumping, wading and climbing when they become active goals.

If the final lifecycle uses generic script timing, later negative/no-op regression must include Fist, bow, crossbow and magic; Fist is particularly important because melee action enums alone do not imply weapon-style `Item_Attack(7)` ownership.
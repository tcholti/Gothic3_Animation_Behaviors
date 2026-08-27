# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-27

`docs/collision-source-evidence` contains the newest collision research/prototype state. `main` is the stable integration and reusable Gothic 3 knowledge baseline.

Document roles / Hot-Warm-Cold retrieval: `docs/README.md`  
Latest transient Chat/Work bridge, only when relevant: `docs/BETWEEN_CHATS.md`

---

## Fresh Normal Chat Bootstrap

For a newly opened Normal Chat:

1. read this file first and treat it as the current-state authority;
2. do **not** reconstruct the project from old chat history or scan the whole repository;
3. read `docs/BETWEEN_CHATS.md` only when the current responsibility depends on an active/recent Work task or transient handoff;
4. retrieve only the exact deeper authority listed under **Retrieval — Only What the Question Needs** when the current question requires it;
5. continue the current Normal Chat responsibility from the repository state. The User should not need to restate project history already preserved here or in the routed authorities.

A new Normal Chat should normally need no custom handoff document beyond this front door. `BETWEEN_CHATS.md` remains the replaceable transient bridge for exact Chat ↔ Work continuity.

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
- no common immediate Script_Game post-cleanup helper has been demonstrated across tested ordinary families;
- EV-174: in three isolated clean 2H Normal transitions, Gothic performed `StartRecover BEGIN -> StopMotion(type 0) -> Recover PlayMotion(type 0) -> StartRecover END -> native 7 -> 5 cleanup`;
- therefore a PlayMotion-before snapshot cannot observe every outgoing Hit: the clean path has already removed it through StopMotion.

These generic script functions are **not combat ownership authority**. StopMotion is currently a diagnostic teardown event, not yet production Hit-end authority.

Exact evidence/RVAs: `EVIDENCE_INDEX.md` and `COLLISION_CLEANUP_CALLSITE_MAP.md`.

---

## Current Candidate

```text
exact owned offensive Hit teardown/replacement observed
→ mark that exact execution pending-finalization
→ let Gothic finish current native script dispatch
→ at one tightly gated post-script opportunity:
     native cleanup observed -> no-op
     cleanup absent          -> repair
```

A generic script layer may provide **timing only**. Exact attack execution ownership and its offensive-collision request must already exist.

This remains a hypothesis.

---

## Current Gate — B6 StopMotion / Direct-Replacement Stack Validation

The initial B6 PlayMotion-only stack probe built and loaded correctly after the live `scripts` directory was isolated. EV-173 preserves the backup-DLL contamination lesson; the invalid log is archived.

The isolated B6-B control then exposed a diagnostic contradiction rather than a lifecycle contradiction: all three clean 2H Normal transitions stopped the outgoing Hit Primary through the already-hooked type-0 `StopMotion` before successor Recover `PlayMotion`. The current direct PlayMotion replacement probe therefore emitted no replacement stack in that clean path. See EV-174.

### Next bounded implementation

Revise B6 diagnostics only:

1. keep the existing direct PlayMotion replacement-stack probe unchanged for paths where the outgoing Hit remains visible at PlayMotion entry;
2. in the **already-existing** player/type-0 `StopMotion` hook, if the before-snapshot is an attack-Hit Primary, capture a short supported Win32 stack/context before the unchanged original StopMotion call;
3. emit a clearly named outgoing-Hit StopMotion stack diagnostic and preserve the existing StopMotion before/after log;
4. use the existing immediately following PlayMotion record during runtime analysis to identify the actual successor;
5. add no new Gothic hook, production cleanup, polling, lifecycle ownership state, family-specific repair rule, or guessed stack/frame layout.

After source review/build, rerun B6-B clean control, then B6-C legitimate reaction interruption, then B6-D bad block-skip direct replacement.

Question:

> **Do clean StopMotion-first teardown, legitimate reaction teardown/replacement, and bad direct replacement occur inside one useful SPU / `ProcessScript()` context so a tightly gated one-shot checkpoint can reliably run after Gothic's native cleanup opportunity?**

Exact procedure/interpretation: `COLLISION_TEST_PLAN.md` Gate B6. Diagnostic authority: `COLLISION_LOGGER_PLAN.md` §6.

---

## Do Not Do Yet

Until B6 answers the boundary question:

- do not implement production cleanup;
- do not hook `ProcessScript` as unconditional behavior;
- do not add family/cause-specific repair branches;
- do not add timers/polling;
- do not treat StopMotion, action/phase, or filename alone as universal continuing physical Hit lifetime authority;
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

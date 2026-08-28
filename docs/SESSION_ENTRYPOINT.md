# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-28

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
- EV-174/EV-175: in three valid clean 2H Normal transitions, `StartRecover BEGIN` still observed the outgoing Hit Primary, but by entry to the player/type-0 `StopMotion` hook PrimaryFirst was already empty; Recover PlayMotion, StartRecover END, and native `7 -> 5` cleanup followed;
- therefore clean-path Hit disappearance occurs after `StartRecover BEGIN` but before the StopMotion hook's first observable snapshot;
- StopMotion itself is **not proven** to remove the outgoing Hit, and the revised StopMotion stack branch cannot fire on this clean path because its gate requires that already-missing PrimaryFirst Hit.

These generic script functions are **not combat ownership authority**. StopMotion is currently nearby diagnostic timing evidence only, not production Hit-end authority.

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

## Current Gate — B6 Clean Disappearance / Direct-Replacement Stack Validation

The B6 direct PlayMotion replacement probe remains valid for paths where an outgoing Hit is still visible at PlayMotion entry.

The bounded StopMotion-stack revision in commit `c99949d9ff2eeb7a6ce6242764d26d6a6574f299` passed source review and built successfully. Deployment was then corrected and verified against the authoritative live Steam path:

```text
E:\SteamLibrary\steamapps\common\Gothic 3\scripts\Script_FrameCollisionTest.dll
```

The built and live DLLs were byte-identical, and the runtime banner confirmed:

```text
STEP B6 HIT STOP / REPLACEMENT STACK PROBE
```

Valid B6-B raw evidence:

```text
research/raw/2026-08-28_b6b_player_2h_normal_clean_completion_stopmotion_stack_valid.log
```

Commit: `e8e02c5ba53d05747ded6bad1ab70df0c6ac70ee`.

### Valid B6-B result

All three clean 2H Normal attacks showed:

```text
attack Hit Primary
→ StartRecover BEGIN still sees Hit
→ PrimaryFirst already empty at StopMotion hook entry
→ StopMotion(type 0)
→ Recover PlayMotion(type 0)
→ StartRecover END
→ native cleanup 7 -> 5
```

Zero `HIT STOP STACK` records were emitted. Source confirms the stack branch is gated solely by `IsAttackHitPrimaryMotion(before)`, so this is a diagnostic limitation, not evidence against the lifecycle architecture.

EV-174 has been corrected and EV-175 records the valid revised run.

### Immediate Normal Chat responsibility

Before freezing another Work task, design the smallest diagnostic refinement that can capture the clean transition despite the already-empty PrimaryFirst snapshot at StopMotion entry.

Preferred direction if source review supports it:

- preserve the existing player/type-0 StopMotion hook and direct PlayMotion replacement probe;
- use already-available CombatMove action/phase/current-movement facts only as **diagnostic correlation context** to identify the relevant StopMotion call, not as continuing physical-Hit ownership authority;
- capture the supported Win32 stack/context before original StopMotion when that narrow correlation is satisfied;
- otherwise identify the nearest earlier supported boundary where the Hit is still observable;
- add no production cleanup, lifecycle state, polling, family-specific repair rule, extra Gothic hook, or guessed stack/frame layout unless evidence forces it.

Do **not** advance to B6-C legitimate reaction interruption until B6-B produces an interpretable clean boundary stack/context. After that, compare B6-C and then B6-D bad block-skip direct replacement.

Question:

> **Do clean Hit disappearance, legitimate reaction teardown/replacement, and bad direct replacement occur inside one useful SPU / `ProcessScript()` context so a tightly gated one-shot checkpoint can reliably run after Gothic's native cleanup opportunity?**

Exact procedure/interpretation: `COLLISION_TEST_PLAN.md` Gate B6. Diagnostic authority: `COLLISION_LOGGER_PLAN.md` §6. Canonical evidence: EV-174–EV-175.

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

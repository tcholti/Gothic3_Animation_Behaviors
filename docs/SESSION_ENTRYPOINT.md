# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-28

`docs/collision-source-evidence` contains the newest collision research/prototype state. `main` is the stable integration and reusable Gothic 3 knowledge baseline.

Document roles / Hot-Warm-Cold retrieval / Subsystem Orientation Pass: `docs/README.md`  
Latest transient Chat/Work bridge, only when relevant: `docs/BETWEEN_CHATS.md`

---

## Fresh Normal Chat Bootstrap

For a newly opened Normal Chat:

1. read this file first and treat it as the current-state authority;
2. read `docs/BETWEEN_CHATS.md` only when the current responsibility depends on an active/recent Work task or transient handoff;
3. if the active technical subsystem is not already sufficiently oriented in the current Chat context, perform the **one-time Subsystem Orientation Pass** from `docs/README.md`;
4. do **not** reconstruct the project from old chat history, scan the whole repository, or create another persistent subsystem-summary document;
5. retrieve only the exact deeper authority listed under **Retrieval — Only What the Question Needs**;
6. continue from repository state without asking the User to restate preserved project history.

Within the same continuing subsystem context, do not rerun the orientation pass or reread unchanged authorities after every prompt.

---

## Active Subsystem

**Frame-controlled melee collision lifecycle.**

Confirmed native defect: a real offensive Hit can lose enough CombatMove/action continuation that Gothic 3 fails to run normal collision cleanup. The physical Hit may disappear and the weapon may remain offensively active through ordinary idle and into a later independent attack. This defect is native and is not introduced by frame markers.

Preferred invariant remains:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact Hit genuinely ends or is replaced, if cleanup was observed, do nothing; if not, repair the remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. End-of-Hit safety should be one shared invariant for marked and native attacks.

Current architecture: `docs/COLLISION_LIFECYCLE_PLAN.md`.

---

## Established Step-B Facts Needed Now

- type-0 `PlayMotion` gives immediate PrimaryFirst acquisition/replacement evidence, but clean successor PlayMotion can occur before native cleanup;
- later original attack callbacks are not one-shot completion boundaries;
- `sAICombatMoveStartRecover` is too early and can be bypassed;
- missing Recover assets are not the root cause;
- successful ordinary cleanup is action-specific inside `Script_Game.dll`;
- tested legitimate reaction cleanup uses `Script_Game + 0x24AFF`;
- generic script infrastructure is established as:

```text
Game + 0x1603D0 = gCScriptAdmin::RunScriptState(...)
Game + 0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
Game + 0x16F120 = gCScriptProcessingUnit::ProcessScript()
Game + 0x1696E0 = gCScriptProcessingUnit::sAICombatMoveInstr(...)
Game + 0x16ABB0 = gCScriptProcessingUnit::sAICombatMoveStart(...)
Game + 0x16DD00 = gCScriptProcessingUnit::sAICombatMoveItlLoop(...)
Game + 0x16E360 = gCScriptProcessingUnit::sAICombatMoveStartRecover(...)
```

These generic functions are timing/control-flow evidence, **not combat ownership authority**.

Exact evidence/RVAs: `EVIDENCE_INDEX.md`, `COLLISION_CLEANUP_CALLSITE_MAP.md`, `SOURCE_HOOK_GUIDE.md`.

---

## B6 Result — Deferred ProcessScript Candidate Rejected in Its Present Form

Latest combined raw:

```text
research/raw/2026-08-28_b6c3_b6d_player_2h_clean_skip_and_reaction_successor_stacks.log
```

Raw commit:

```text
b4e2af53adcab87ac0f18c445944603ff11bc1b9
```

Diagnostic implementation:

```text
9f99d3d43a66321a9a0ddbc1df882d6daee6dddd
```

Independent source review/build/deploy/load: **PASS**.

### Clean completion

EV-176 and the latest clean Whirl controls show:

```text
Hit / weapon 7
→ StartRecover BEGIN
→ sAICombatMoveInstr
→ ProcessScript()
→ Recover
→ later action-specific native cleanup 7 -> 5
```

### Legitimate reaction

EV-179 now captures the actual successors:

```text
attack Hit / weapon 7
→ +0x24AFF cleanup 7 -> 5
→ reaction Script_Game / RunScriptState chain
→ empty Primary
→ Stumble / KnockDown successor installed inside reaction Script_Game/ScriptAdmin context
```

The captured unwind stops at `RunScriptState`; static EV-170 places that runner under `ProcessScript()`, but the exact outer ProcessScript invocation is not directly identified by the runtime backtrace.

### Bad armed Whirl skip

EV-180/EV-181 show:

```text
Whirl Hit starts normally
→ timer/callback arms weapon 5 -> 7
→ NO StartRecover
→ NO ordinary Whirl cleanup
→ Hit disappears
→ Ambient/idle installed while weapon remains 7
→ observed successor stack only:
     diagnostic
     → Game +0xD9CB3
```

The strongest case then remained group 7 through ordinary Ambient/idle for roughly nineteen seconds. A later Normal attack began with the stale group 7, requested `7 -> 7`, and only that later Normal's clean completion finally performed `7 -> 5` at `Script_Game +0x3851A`.

The User additionally observed that a newly spawned golem placed directly in front of the idle Hero immediately took damage on contact during this stale interval. The prototype log confirms persistent group 7; it does not itself log health/damage.

### B6 architectural consequence

B6 did **not** establish one useful observable current ProcessScript/ScriptAdmin replacement-time context across all relevant ending paths.

Therefore the previous candidate:

```text
replacement observed
→ mark pending
→ wait for end of same current ProcessScript dispatch
→ inspect/repair
```

is **rejected in its present form**.

This does **not** reject the execution-level cleanup invariant. Do not proceed to C1 or add a ProcessScript behavior hook.

Canonical evidence: EV-179–EV-181.

---

## Current Gate — B7 Attack-Lifecycle / Bookkeeping Reconstruction

Current question:

> **What native CombatMove/routine/instruction bookkeeping established at attack-Hit start keeps normal completion and legitimate reaction paths connected to cleanup, and what is abandoned, reset, or bypassed differently on the bad block-skip path?**

Working model — structural, not literal object speculation:

```text
attack Hit begins
→ CombatMove / animation / movement execution established
→ Routine StateTime advances
→ Routine StatePosition / callback bookkeeping records one-shot progress
→ timed callback may request offensive collision
→ continuation remains connected to:
     normal completion cleanup
     OR legitimate reaction cleanup

bad block skip
→ some continuation/bookkeeping is abandoned or bypassed
→ Hit can disappear through ordinary animation handling
→ neither legitimate cleanup route is guaranteed
→ stale offense survives
```

This is compatible with earlier proven bookkeeping failures in marked attacks:

- Quick/full-Whirl marker activation had to advance `Routine.StatePosition` to prevent Gothic repeating the native timed activation later;
- interrupted marker occurrence budgets required execution-boundary retirement even after Gothic had already physically cleaned the weapon.

Those facts make bookkeeping causally important, but they do not prove which native field/function owns the current defect.

### Immediate Normal Chat responsibility

1. source/static-audit the smallest relevant CombatMove/routine control flow around:
   - `sAICombatMoveStart`;
   - `sAICombatMoveItlLoop`;
   - `sAICombatMoveInstr` / exposed instruction callback state;
   - Routine StateTime / StatePosition reset/progression;
   - action-specific continuation after CombatMove;
   - reaction reset/state path leading to `+0x24AFF`;
2. compare clean Normal/Quick/Whirl, legitimate reaction, and bad Whirl as mechanisms rather than family-specific fixes;
3. freeze a new runtime diagnostic only if static evidence leaves one exact missing fact.

Likely bounded diagnostic if still needed:

> Reuse the existing `SetCollisionGroup` hook to capture the caller stack for actual offensive `5 -> 7` and meaningful `7 -> 7` requests. Do not add another Gothic hook merely to observe the timer/callback activation path.

Exact procedure: `COLLISION_TEST_PLAN.md` Gate B7.  
Architecture: `COLLISION_LIFECYCLE_PLAN.md` §§8–12.  
Canonical evidence: EV-179–EV-181 plus earlier StatePosition/bookkeeping evidence.

---

## Do Not Do Yet

Until B7 identifies a reliable general finalization mechanism:

- do not implement production cleanup;
- do not add a `ProcessScript` behavior hook to rescue the rejected candidate;
- do not add family/cause-specific repair branches;
- do not add timers/polling/per-frame scans;
- do not treat StartRecover, StopMotion, action/phase, filename, or `Game +0xD9CB3` alone as universal lifetime authority;
- do not move unfinished collision implementation to `main`.

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| documentation/retrieval model or subsystem orientation route | `README.md` |
| lifecycle architecture / B7 model | `COLLISION_LIFECYCLE_PLAN.md` |
| current tests / B7 | `COLLISION_TEST_PLAN.md` |
| diagnostic architecture | `COLLISION_LOGGER_PLAN.md` |
| exact evidence | `EVIDENCE_INDEX.md` |
| cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| CombatMove/API/symbol lookup | `SOURCE_HOOK_GUIDE.md` |
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

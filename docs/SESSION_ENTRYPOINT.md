# Session Entry Point

**Purpose:** Minimal durable handoff for any new Chat or Work session. Read this first; open deeper project files only as needed.

**Branch:** `docs/collision-source-evidence`  
**Updated:** 2026-08-27

For document roles and authority, see `docs/README.md`. For the latest Chat/Work bridge, see `docs/BETWEEN_CHATS.md`.

## Active Subsystem

Frame-controlled melee collision lifecycle.

The RIGHT/LEFT/BOTH/OFF marker core is established. `G3AB_COL_OFF` is optional authored early shutoff inside a live Hit; it is not the general end-of-Hit safety mechanism.

Known native defect: an offensive Hit can lose enough CombatMove/action ownership/bookkeeping that the physical Hit motion continues or later replaces while Gothic 3 fails to run normal collision cleanup. This is confirmed natively and is not introduced by frame markers.

## Preferred Cleanup Invariant

Prefer **System 1: execution-level native cleanup guard**.

> For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact Hit genuinely ends or is replaced, if cleanup was observed, do nothing; if not, repair the remaining offensive collision using native cleanup semantics.

Marked and native attacks should differ primarily in activation timing. Marker control changes collision **inside** the Hit; end-of-Hit cleanup remains one shared invariant.

Native cleanup paths are opportunities, not guarantees.

Detailed architecture: `docs/COLLISION_LIFECYCLE_PLAN.md`.

## Marker Rule While Hit Is Alive

```text
RIGHT = {RIGHT}
LEFT  = {LEFT}
BOTH  = {RIGHT, LEFT}
OFF   = {}
```

Each marker defines the complete desired offensive collision set.

## Step-B Runtime Evidence

Canonical continuation: `docs/EVIDENCE_LEDGER_STEP_B.md`, EV-158 onward.

Key established results:

1. **B1:** `eCVisualAnimation_PS::PlayMotion(type 0)` is an immediate PrimaryFirst acquisition/replacement signal, but clean successor Recover PlayMotion occurs before later native `7 -> 5` cleanup. Replacement itself is too early for immediate repair.
2. **B2:** the later original Quick/AI callback begins after native cleanup and can repeat during Recover; it is not a one-shot completion event.
3. **B3:** `gCScriptProcessingUnit::sAICombatMoveStartRecover` at tested `Game + 0x16E360` returns while the weapon can still be group 7. Broken Hits can bypass StartRecover entirely.
4. **B3b:** Recover animation assets are not required for cleanup. Native Dual Quick and no-Recover Quick reproduce the same structural stale-collision defect.
5. **B4/B4b:** successful completion cleanup is action-specific inside `Script_Game.dll`; legitimate damage/reaction interruption uses separate `Script_Game + 0x24AFF` cleanup. Do not create one hook per action family.
6. **B5:** ordinary successful cleanup stacks reached `Game + 0x1605EB`; tested interruption cleanup reached `Game + 0x1604D3` through another Script_Game reaction frame.

Detailed action/call-site map: `docs/COLLISION_CLEANUP_CALLSITE_MAP.md`.

## B5 Static Identification — 2026-08-27

The B5 Game parents are now identified exactly in the tested binary:

```text
Game + 0x1603D0 = gCScriptAdmin::RunScriptState(...)
    tested interruption post-call return: +0x1604D3

Game + 0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
    tested ordinary post-call return: +0x1605EB
```

Therefore B5 did **not** discover a central combat-cleanup function. It reached Gothic 3's generic script-execution layer.

Both paths converge one level higher in:

```text
Game + 0x16F120 = gCScriptProcessingUnit::ProcessScript()
```

Inside the tested binary:

```text
+0x16F2C2 -> RunScriptFunction
+0x16F338 -> RunScriptState
+0x16F3A6 -> RunScriptState
```

The official SDK confirms the SPU is generic per-NPC ScriptFunction/ScriptState machinery with many non-combat instructions as well as CombatMove. `ProcessScript()`, `RunScriptFunction()`, and `RunScriptState()` are therefore too broad to treat as unconditional collision-cleanup owners.

`ProcessScript()` performs its main ScriptFunction/ScriptState dispatch before later local/task callback processing. The latter reaches:

```text
Game + 0x160610 = gCScriptAdmin::RunScriptCallback(...)
```

This statically explains B2: the later original Quick callback is downstream of the main ScriptFunction path where ordinary native cleanup has already happened.

## Action Semantics Over Filename Identity

The same serialized 2H `FinishingAttack` Hit asset has been observed under different runtime actions and different native cleanup functions.

In the B5 target-standing case Gothic still played the FinishingAttack Raise/Hit asset family, but by Hit/collision the runtime action was already `gEAction_HackAttack` (14). No action-15 -> action-14 transition was directly logged.

Use native action semantics as behavioral authority; animation filenames alone are not sufficient.

## Marker-Bookkeeping Clarification

`RetireMarkerOwnedSource()` is not physical fallback cleanup.

The earlier v0.15/v0.16 interruption issue occurred when Gothic had already physically reset a marked source `7 -> 5`, but our marker occurrence/execution record could remain stale. Natural reset was used as evidence to retire marker bookkeeping. Intentional OFF/source switching remains intra-Hit and must not retire the whole execution.

Physical cleanup and marker-record lifetime remain separate responsibilities until a stronger exact Hit-lifetime authority replaces the old inference.

## Current Three-Path Model

```text
A. NORMAL COMPLETION
Hit
-> action-specific Script_Game cleanup
-> RunScriptFunction return
-> collision clean
```

```text
B. LEGITIMATE DAMAGE/REACTION INTERRUPTION
Hit
-> Script_Game interruption cleanup (+0x24AFF)
-> RunScriptState return
-> reaction motion
-> collision clean
```

```text
C. BAD BLOCK SKIP / ABNORMAL TEARDOWN
Hit
-> some gameplay/CombatMove ownership is abandoned
-> neither proper completion nor interruption cleanup is guaranteed
-> physical Hit may continue or replace
-> stale collision possible
```

## Current Design Candidate — NOT FROZEN

A possible event-driven design is:

```text
exact owned offensive Hit replacement observed
-> mark that exact execution pending-finalization
-> let the current native script dispatch finish
-> at a tightly gated one-shot post-script opportunity:
       native cleanup observed -> no-op
       cleanup absent          -> repair
```

A broad script boundary would be used only as a **timing checkpoint** for an already-owned exact attack execution, never as attack ownership authority.

Before implementation, compare this with any narrower CombatMove-specific post-native-cleanup boundary.

## Immediate Next Research Questions

1. Is there a narrower combat-specific post-native-cleanup boundary below `ProcessScript()`?
2. If no such boundary exists, is a one-shot deferred post-script checkpoint the smallest reliable event-driven design?
3. What exact execution/source gate guarantees unrelated actions cannot be mutated?
4. After the architecture is chosen, which negative regression tests are required for Fist, bow, crossbow, magic and other non-melee behavior?

Do **not** send another Work coding task yet. Static inspection and design discussion come first.

## Research Order Decision

Keep two problems separate:

1. first finish the universal execution-level collision safety rule;
2. later, if worthwhile, investigate the deeper block-skip/CombatMove teardown itself to preserve movement, activation/timing and other gameplay behavior.

Do not make universal cleanup depend on fixing the deeper block-skip cause.

## Current Testing Rule

For lifecycle research, prefer native/unmarked attacks while isolating Gothic's own behavior. Reintroduce marked fixtures when validating convergence of the final execution-level guard.

If the final design uses a generic SPU/script checkpoint, negative regression tests for Fist, bow, crossbow, magic and unrelated action families become important before release even when strict attack ownership should make them no-ops.

## Repository Access Note

Use the connected GitHub interface as authoritative assistant-side repository access. The user's home checkout remains authoritative for local build/install/runtime testing.

## Chat / Work Execution Model

```text
Chat: design / evidence / freeze one bounded code task
        ↓
Work: source implementation/refactor + targeted review + commit/push + STOP
        ↓
Chat + home PC: sync / build / runtime test / interpret logs
        ↓
Chat: update evidence/docs and choose next code task
```

# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Current state — C1 shadow core passed; outer ScriptFunction frame found

**Date:** 2026-08-29  
**Branch:** `docs/collision-source-evidence`

C1 remains **shadow-only**. Production physical repair is disabled.

Durable current state is in `docs/SESSION_ENTRYPOINT.md`. Recurring local Git/build/deploy/test/log patterns live in `docs/PROJECT_OPERATING_PROCEDURES.md` and should be read once when that operational sequence is entered, not after every prompt.

## C1 core result to preserve

Raw:

`research/raw/2026-08-28_c1_shadow_core_lifecycle_matrix.log`

Derived connector extract:

`research/archive/2026-08-28_c1_shadow_core_lifecycle_matrix_connector_extract.txt`

The tested shadow classification behaved as intended for the main matrix:

- 8 actual `WOULD_REPAIR` outcomes = 1 armed bad full Whirl + 7 armed bad Dual Quick;
- clean completion = no repair candidate;
- pre-activation bad skip = no repair candidate;
- tested legitimate interruption = native cleanup, no repair candidate;
- inherited stale `7 -> 7` on the next Normal attack was attributed to the new generation and then fulfilled by native `7 -> 5` cleanup.

The same run exposed 11 `UNOWNED_PLAYER_OFFENSE_REQUEST` warnings around knockdown/GetUp handling. Static inspection established why:

```text
Script_Game +0x41CA6  GetUpAttack can request Item_Attack(7)
Script_Game +0x41D5A  later call to the same CombatMove import used by full Whirl
Script_Game +0x41E10  known ordinary cleanup
```

Therefore CombatMove is an inner asynchronous-instruction boundary, not the universal start of the collision-owning attack ScriptFunction execution.

## New SDK/static result — outer execution layer exists

Pinned SDK `Georgeto/gothic3sdk@90bfd344de4510dda7ac9da7461cc7f1eac911f7` exposes the actor SPU's ScriptState/ScriptFunction execution stack:

```text
gCScriptRoutine_PS::GetSPU()
→ gCScriptProcessingUnit::m_StateStack
→ top gScriptRunTimeSingleState
```

Each `gScriptRunTimeSingleState` is 0x18 bytes and exposes:

- `m_iBreakBlock`;
- `m_strScriptName`;
- `m_bIsScriptState` (false = ScriptFunction);
- `m_pArguments`;
- `m_strLocalCallback`;
- one additional float.

The SDK explicitly states that ScriptFunctions/States are backed by this stack and that when execution returns false because a delayed action is active, the frame remains so it can continue later.

Tested Game.dll independently confirms the persistence rule in `gCScriptAdmin::RunScriptFunction`:

```text
Game +0x1605E9  invoke registered ScriptFunction
Game +0x1605EB  compare result with true
true  -> use stack count-1 and call removal helper at +0x1627B0
false -> return false at +0x160601 without removing the frame
```

This matches the established CombatMove model: the outer ScriptFunction frame survives while the inner asynchronous CombatMove is active and is removed only after the ScriptFunction completes.

## Exact current Normal Chat question

The outer lifecycle layer is no longer the main unknown. The remaining question is **how to correlate the exact same live stack frame safely across existing hooks**.

Do not assume yet that any one exposed field is sufficient production identity:

- stack-entry address can be invalidated by underlying array movement;
- script name/type/break block are diagnostic fingerprints, not guaranteed unique invocation identity;
- `m_pArguments` is promising but source/static evidence has not yet proven it is always non-null and stable enough for this purpose.

### Smallest next evidence step

Freeze a **shadow-only outer-frame identity probe** using existing hook owners only; no new engine hook and no behavior change.

At minimum log the same top-frame snapshot at:

1. a successful equipped-player Item_Attack request that C1 currently sees as unowned;
2. new CombatMove initial invocation;
3. AISetState before the original destructive replacement (and after only if useful).

Snapshot fields should include SPU address, state-stack count, top-entry address, script name, State-vs-Function, break block, `m_pArguments`, local callback, and existing action/phase/source context.

Primary runtime target: reproduce GetUpAttack pre-arm and prove whether the same frame identity/fingerprint persists into its later CombatMove. Include a repeated/new-execution control sufficient to show how a later execution is distinguished.

If the probe proves a robust correlator, redesign C1 so the outer ScriptFunction execution owns the generation and CombatMove becomes an inner milestone/attachment rather than the universal generation start.

Do **not**:

- add a GetUpAttack/action/family special case;
- use script name as a production attack classifier;
- blindly adopt any group-7 weapon at CombatMove start;
- enable physical repair;
- add polling/timers/per-frame/world scans;
- weaken existing marker bookkeeping.

There is currently **no frozen Work implementation task**. The next responsibility is Normal Chat freezing the smallest identity probe before bounded implementation.

# Between Chats

**Purpose:** Small transient bridge between normal Chat and Work.  
**Rule:** Keep this file short and overwrite the current handoff; do not accumulate history here.

## Latest result

**From:** Normal Chat / home-PC runtime validation  
**To:** Next Normal Chat research session  
**Date:** 2026-08-26  
**Branch:** `docs/collision-source-evidence`

## Step B5 — VALIDATED AND CONSOLIDATED

Source commit:

`807307570b85bcdd4f1c3c703204dbd34560feb6`

Runtime log:

`research/raw/2026-08-26_stepB5_cleanup_parent_stack_probe.log`

### Main B5 result

Ordinary successful action-specific cleanup stacks converged to:

```text
FrameCollision wrapper
→ action-specific Script_Game cleanup site
→ Game + 0x1605EB
```

Binary inspection places `+0x1605EB` inside an internal Game helper beginning near `Game + 0x1604E0`.

Legitimate damage/reaction interruption remained different:

```text
FrameCollision wrapper
→ Script_Game + 0x24AFF
→ another Script_Game reaction frame
→ Game + 0x1604D3
```

Binary inspection shows `+0x1604D3` at the return/end of the immediately preceding sibling Game helper; the ordinary sibling begins at `+0x1604E0`.

Therefore B5 did **not** identify one identical parent frame shared by all successful cleanup paths. It identified adjacent sibling Game-level paths.

### Finishing/Hack target-state observation

One intended execution target stood up before Hit. Gothic still played the `FinishingAttack_Raise` and `FinishingAttack_Hit` asset family, but Hit/collision and StartRecover were already `gEAction_HackAttack` (14). No action-15 -> action-14 switch is directly proven. Preserve the stronger rule: runtime action semantics, not filename identity, choose behavior.

### Marker-retirement clarification

`RetireMarkerOwnedSource()` is not physical fallback cleanup. Earlier v0.15/v0.16 interruption work used an already-performed Gothic `7 -> 5` reset as evidence to retire stale marker occurrence/execution bookkeeping. Intentional OFF/source switching must remain intra-Hit and must not retire the whole execution.

## Consolidated docs

- `docs/SESSION_ENTRYPOINT.md`
- `docs/COLLISION_LIFECYCLE_PLAN.md`
- `docs/COLLISION_CLEANUP_CALLSITE_MAP.md`
- `docs/EVIDENCE_LEDGER_STEP_B.md` — canonical continuation EV-158 onward
- `docs/README.md`

The large original `EVIDENCE_LEDGER.md` remains untouched through EV-157; the Step-B continuation is explicitly indexed as the next canonical ID range.

## Next research question

Do **not** send a coding task to Work yet.

Next Normal Chat should first inspect the two adjacent Game sibling functions and their callers/dispatch conditions:

```text
interruption sibling: around Game + 0x1604D3 / return near +0x1604D5
ordinary sibling:     starts near Game + 0x1604E0; common B5 return +0x1605EB
```

Question:

> What calls/selects these sibling helpers, and is there a narrow event-driven boundary after either legitimate completion/interruption cleanup opportunity?

Only after static inspection identifies a plausible candidate should another bounded runtime probe be frozen for Work.

Do not implement production cleanup, timers, broad polling, one hook per action family, or a block-skip-specific repair yet.

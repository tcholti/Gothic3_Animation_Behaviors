# Collision Lifecycle Plan

**Status:** Working design / research target, not yet implemented  
**Updated:** 2026-08-26

## Goal

Replace accumulated cleanup/interruption contingencies with one execution-level invariant wherever the engine evidence permits it.

> For every real attack-Hit execution that requests offensive collision, the corresponding native cleanup must have occurred by the time that exact Hit execution actually ends or is replaced. If Gothic 3 already cleaned it, do nothing. If it did not, invoke the native cleanup Gothic 3 should have performed.

How the Hit ends is intentionally irrelevant: normal completion, block timeout, damage interruption, terrain interruption, skipped Recover, or another genuine replacement should all converge on the same end-of-execution guard.

`G3AB_COL_OFF` is **not** this guard. It remains optional authored early shutoff inside a still-live Hit.

## Main Plan — Execution-Level Guard

1. **Acquire a real attack-Hit execution.**
   - Use Gothic 3 native callback/action/phase semantics at acquisition where available.
   - Do not track every animation whose filename contains `Hit`.
   - A second valid acquisition signal is an offensive collision request occurring during the relevant Hit execution.

2. **Capture the exact actual motion execution.**
   - After acquisition, actual motion lifetime becomes the preferred lifetime authority.
   - Action/phase may help identify the execution initially, but v0.20 proves they can drift to Stand while the same Hit motion is still running.

3. **Choose activation policy only.**
   - **Marked motion:** suppress the native timed collision callback; RIGHT/LEFT/BOTH markers control activation/rearm timing.
   - **Unmarked motion:** leave Gothic 3's native collision behavior untouched.

4. **Record that this execution requested offensive collision.**
   - A request counts even when the source was already `Item_Attack` (`7 -> 7`).
   - Preferred minimal state is execution-level: `collisionRequested = true` plus whether the corresponding native cleanup was observed.

5. **When the exact Hit execution actually ends/replaces, verify cleanup.**
   - If the native cleanup already occurred: do nothing.
   - If it did not: invoke the same native cleanup operation Gothic 3 normally uses.

Preferred implementation is event-driven. The v0.20 Script `OnTick` probe is diagnostic and too coarse to become the production mechanism.

## Fallback Plan — Source-Aware Guard

Use per-source ownership only if research proves that Gothic 3 has no usable attack-wide cleanup operation, or that one physical source can clean successfully while another independently remains attack-active.

Fallback state would associate the exact Hit execution with each source on which offensive collision was requested, including `7 -> 7` requests, and verify/repair them independently at execution end.

Do **not** implement source bookkeeping merely because the current prototype already has RIGHT/LEFT masks. First establish what native cleanup actually is.

## v0.20 Cleanup/Lifetime Scaffolding to Revisit

The following current mechanisms are useful prototype safeguards but are **not presumed production architecture**. Do not remove them yet; flag them for review once the execution-level guard and native cleanup path are proven.

1. **`MarkerOwnedCollisionWindow` as the lifetime owner**
   - stores right/left source instances, an active-source mask, animation name, action, and phase;
   - likely over-specified if cleanup can be guarded at attack-execution level.

2. **`FindMatchingMarkerOwnedWindow(...)` strict identity**
   - currently requires source snapshot + animation + action + phase;
   - v0.20 shows action/phase can become invalid while the exact Hit execution still survives.

3. **`MarkerWindowStillMatchesActorExecution(...)`**
   - currently uses animation + action + phase, plus state-time comparison, to decide whether a natural source reset retires execution state;
   - this is a prime candidate to be replaced by exact actual-motion lifetime.

4. **`RetireMarkerOwnedSource(...)` as cleanup-lifetime retirement**
   - current global `SetCollisionGroup` hook retires marker ownership source-by-source when a source leaves `Item_Attack`;
   - may become unnecessary for lifetime ownership if one attack-level cleanup event can be observed and guarded.

5. **Action/phase as a continuing marker-time veto after ownership was already acquired**
   - v0.20 proves this can reject legitimate later markers during a still-running Hit after block-timeout state drift;
   - likely change: strict native semantics at acquisition, then exact execution identity for the rest of that Hit.

6. **Interruption-specific cleanup assumptions**
   - do not add new block-timeout, skipped-Recover, terrain, damage, Quick, Whirl, or Staff cleanup branches while the unified rule is under investigation.

### Keep Unless Separate Evidence Says Otherwise

These solve different problems and are **not** currently marked for removal:

- RIGHT/LEFT/BOTH source-explicit marker vocabulary;
- exact-set source switching within a live Hit;
- repeated source markers and `ClearTriggeredList()` rearm for later authored contacts;
- `G3AB_COL_OFF` as optional authored early shutoff;
- duplicate same-update marker suppression;
- authored-occurrence budgets that reject Gothic 3's interleaved/replayed frame-effect dispatches;
- native callback suppression only for exact marked motions whose required sources can be resolved.

Execution identity may later simplify some bookkeeping, but that is a separate question from cleanup.

## Tests Before Implementation

### T1 — Cross-Hit Collision Carryover

Determine whether any legitimate native combat sequence intentionally keeps offensive `Item_Attack` active after one physical Hit execution ends and into another.

Use representative Normal, Quick, Power, Whirl/SimpleWhirl, 1H, Shield+1H, Dual, 2H, and Staff sequences, including rapid chaining and ordinary completion. The critical pattern is:

`Hit A collision ON -> Hit A actual motion ends -> Hit B begins`, with no native cleanup between them.

If such a legitimate case exists, the universal end guard needs an explicit ownership-transfer rule. If it does not, the simple end-of-Hit invariant becomes much stronger.

### T2 — Real Combat / Interruption Matrix

Exercise the same weapon families while:

- attacking and being hit back;
- attacking into a block;
- blocking then attacking near block timeout;
- allowing block to expire without attacking;
- chaining attacks as quickly as Gothic 3 allows;
- allowing attacks to complete normally;
- triggering genuine damage/terrain interruptions where possible.

Purpose: verify that different failure paths converge on actual Hit end/replacement rather than needing separate cleanup rules.

### T3 — Defensive Collision / Parade Behavior

Determine what successful blocking actually does to weapon/shield collision state.

Record attacker and defender equipment collision-group changes around:

- successful block;
- attacker bounce/reaction;
- defender ParadeStumble / related block-stumble transitions;
- shield versus weapon blocks where possible.

Do not assume the visual weapon clash is physical weapon-to-weapon collision; it may be combat-state logic after ordinary attack contact.

### T4 — Native Cleanup Mechanism

Find the native operation responsible for ending offensive attack collision.

Questions:

- Is cleanup one attack-wide operation or per physical source?
- Does it simply call `SetCollisionGroup`, or is there a higher-level routine/state operation?
- Can one Dual source clean while another remains stale?
- What correct non-attack group should be restored in weapon-state transitions where `Item_Equipped (5)` is not the only observed safe group?

Prefer invoking the native cleanup operation over hard-coding `Item_Attack -> Item_Equipped`.

### T5 — Production Motion-Lifetime Signal

Find an immediate/event-driven hook for actual primary Hit end/replacement.

Validate it against:

- normal completion;
- block-timeout action drift where the same Hit continues;
- genuine interruption/replacement;
- repeated/same-name executions and play-time rollback/restart cases.

Do not use Script `OnTick` polling as the final mechanism unless no lighter stable event exists.

## Logger Upgrade Direction

Do not change the logger until the test questions are frozen, but the next diagnostic version will probably need to correlate:

- exact attack-Hit execution identity / PrimaryFirst lifetime;
- every offensive `Item_Attack` request, including `7 -> 7`;
- every corresponding native cleanup request/event;
- actual Hit end/replacement;
- attacker and defender equipped-item collision transitions during block/parade tests;
- enough action/phase/motion context to explain events without making those values lifetime authority.

The logger should remain observational. Do not add the production cleanup rule until these tests identify the native cleanup path and stable motion-lifetime boundary.

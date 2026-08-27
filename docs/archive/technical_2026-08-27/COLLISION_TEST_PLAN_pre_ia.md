# Collision Lifecycle Test Plan

**Status:** Planned research sequence / not yet run  
**Updated:** 2026-08-26

## Purpose

Test the preferred execution-level cleanup model before production implementation, using the smallest sequence of experiments that can disprove or strengthen it.

The tests are designed around universal questions, not around creating separate fixes for weapon families or interruption types.

## Rules for This Test Phase

- logger remains observational;
- do not add production cleanup during these tests;
- do not add Quick/Whirl/Staff/block-specific cleanup branches;
- preserve native behavior for unmarked controls;
- use marked attacks only where needed to compare marker-controlled activation with native activation;
- record visual observations, but accept/reject technical conclusions from logs/source evidence rather than visual impression alone;
- stop and revise the logger if the required event ordering cannot be read clearly.

## Gate 0 — Validate the New Logger Before Broad Testing

Purpose: prove the logger can express one complete lifecycle clearly.

Use one ordinary native attack with a weapon/path already known to clean normally.

Required readable sequence:

```text
Attack-Hit execution X acquired
X requests Item_Attack/offensive collision
same exact actual Hit execution continues
native cleanup occurs
X actual Hit ends/replaces
```

Then use one known stale-collision reproduction if practical.

Required readable failure sequence:

```text
Attack-Hit execution Y acquired
Y requests offensive collision
Y actual Hit ends/replaces
no corresponding native cleanup occurs
source remains attack-active
```

If either sequence cannot be reconstructed unambiguously, revise the logger before proceeding.

## Gate 1 — Does Native Collision Ever Intentionally Survive One Hit Into the Next?

This is the most important test of the preferred universal rule.

### Initial small matrix

Start with representative native/unmarked attacks rather than every possible animation:

1. 1H — Normal and Quick.
2. Shield+1H — Normal and Quick.
3. Dual — Normal and Quick.
4. 2H — Normal and full Whirl where available.
5. Staff — Normal and full Whirl where available.

Add Power/SimpleWhirl only after the basic lifecycle is readable; they are useful expansion cases, not required for the first pass.

### For each representative path

Perform:

- one attack allowed to finish normally;
- several attacks chained as quickly as Gothic 3 naturally permits;
- repeated attacks without intentionally taking damage or blocking.

### Critical question

Look specifically for:

```text
Hit A requests offensive collision
Hit A actual motion ends
Hit B begins
NO cleanup occurred between them
```

Interpretation:

- **never observed in legitimate sequences:** strengthens the preferred execution-level end guard;
- **observed and clearly intentional:** investigate whether ownership transfers from Hit A to Hit B before adopting the universal end rule;
- **observed only as stale/bugged state:** it is evidence for the guard, not an exception.

Do not infer intent merely because a `7 -> 7` request appears. Determine whether the earlier Hit actually ended without cleanup or whether the source was already stale due to a defect.

## Gate 2 — Different End/Interruption Causes, Same Lifecycle Boundary?

Purpose: determine whether the cleanup rule can remain ignorant of why the Hit ended.

Use a smaller representative set first: one 1H/Dual case plus 2H or Staff, then broaden only if results differ.

Test:

1. normal completion;
2. attack while being hit/damaged by an opponent;
3. attack into a successful block;
4. block, then initiate attack near block timeout;
5. let block expire without attacking;
6. terrain/position interruption if a reproducible case exists;
7. rapid transition into another legal combat action.

For every case record:

```text
exact Hit execution acquired
↓
offensive collision requested? yes/no
↓
actual Hit execution survives / ends / is replaced
↓
native cleanup occurred? yes/no
```

The production architecture should not care whether the cause was block timeout, damage, terrain, Recover absence, or another reason if the same actual-motion boundary and cleanup requirement applies.

## Gate 3 — Block / Parade / Defensive Collision Behavior

Purpose: determine whether blocking introduces defensive collision states that affect the meaning of "clean all offensive collision."

### Test pairs

At minimum:

- weapon attacking weapon block;
- weapon attacking shield block;
- 2H/Staff attack into block where bounce is visually obvious;
- one case that produces a defender ParadeStumble/block-stumble animation.

### Record for attacker and defender

- attack-Hit motion/action context;
- all relevant right/left/shield collision-group requests and transitions;
- offensive `Item_Attack` request on attacker;
- any defender item collision-group request around block;
- attacker bounce/reaction transition;
- defender Parade/ParadeStumble transition.

Questions:

1. Does a blocking weapon/shield enter `Item_Attack` or another special collision group?
2. Is visible weapon bounce caused by actual weapon/shield collision, or by combat-state logic after contact?
3. Could an end-of-Hit offensive cleanup accidentally disturb a legitimate defensive state?

Do not change the architecture until this evidence is understood.

## Gate 4 — Marked and Native Activation Share the Same End Rule?

Purpose: test the core convergence of the preferred architecture.

Use one or two already validated marked fixtures plus equivalent/native controls.

For marked execution:

```text
exact Hit acquired
marker presence suppresses native timed activation
marker requests offensive collision
actual Hit ends
native cleanup already happened? yes/no
```

For native execution:

```text
exact Hit acquired
native callback requests offensive collision
actual Hit ends
native cleanup already happened? yes/no
```

The only intended architectural difference should be activation timing/ownership. End-of-Hit cleanup verification should be the same principle for both.

## Gate 5 — Marker Desired-Set Semantics

Purpose: preserve authored multi-source behavior while simplifying implementation.

Use existing validated marker fixtures rather than inventing new ones unless necessary.

Confirm that the conceptual rule remains valid:

```text
RIGHT = {RIGHT}
LEFT  = {LEFT}
BOTH  = {RIGHT, LEFT}
OFF   = {}
```

Representative sequences:

```text
RIGHT → LEFT
```

```text
BOTH → RIGHT
```

```text
RIGHT → OFF → RIGHT
```

```text
BOTH → LEFT → OFF → BOTH
```

The test is not whether old source-mask code still works. The question is whether every sequence can be correctly described as "make the desired offensive source set equal to the current marker."

If Gothic 3 exposes a safe native collision-only deactivation operation, later implementation may use it. Do not use a whole-attack finalizer for intra-Hit set changes unless proven safe.

## Gate 6 — Preferred Versus Fallback Cleanup Model

After the native cleanup operation/path is identified, decide between the two systems.

### Prefer System 1 if:

- one native cleanup operation semantically closes the attack's offensive collision lifecycle;
- observing that cleanup is sufficient to know the execution is clean;
- Dual/multi-source tests do not show independent partial cleanup failures that require source-specific repair.

### Use System 2 only if:

- cleanup is genuinely per-source; or
- one source can clean while another independently remains stale; or
- no safe attack-wide cleanup operation exists.

Do not choose System 2 merely because existing prototype code already tracks RIGHT/LEFT masks.

## Broad Regression Phase — Only After the Model Is Chosen

Once the preferred/fallback decision is evidence-backed, broaden across:

- 1H;
- Shield+1H;
- Dual;
- 2H;
- Staff;
- Normal;
- Quick;
- Power;
- SimpleWhirl/full Whirl where applicable;
- player and controlled human NPC;
- marked and unmarked cases;
- rapid chaining;
- block/damage/interruption scenarios.

The purpose of the broad phase is to challenge one chosen rule, not to create one rule per matrix cell.

## What Success Looks Like

The research phase succeeds when we can answer, with evidence:

1. what constitutes a real attack-Hit execution;
2. what event/signal identifies its actual end/replacement;
3. what counts as an offensive collision request, including `7 -> 7`;
4. what Gothic 3's proper native cleanup operation is;
5. whether cleanup is attack-wide or source-specific;
6. whether any legitimate native sequence carries offensive collision across physical Hit executions;
7. whether defensive block/parade collision requires a separate state consideration;
8. whether the preferred System 1 survives all of the above.

Only then should Work implement the next production/prototype cleanup version.

# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-07 — frozen bad-block player Hit deferral experiment

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`

Stable release branch:
`main @ e899f37092706a9846312b93d6b52b34e715b53d`

Active branch:
`development`

## Stable baseline

Collision + Speed + Raise + Movement remain accepted.  
EV-447 stable promotion remains the release fallback.

EV-448 exact mathematical pause research remains valid but is not the first-release contract. ADR-0012 requires only that block-timeout teardown not destroy a protected live attack; native held-input time may continue and an already-due timeout may fire after protection ends.

## Active responsibility

`docs/work/active/BAD_BLOCK_SKIP_ATTACK_PROTECTION_OPTIONS.md`

The previous option-comparison gate is closed for the **first experiment only**. User + Normal Chat accepted the smallest evidence-backed player classifier.

Frozen research-DLL experiment:

```text
Script_G3AB_BadBlockResearch.dll only
Script_Game +0x633BF

call native DurationPressedMSecs getter exactly once

if raw > 2500
AND owning actor == player
AND factual Action is:
    QuickAttackR = 4
    QuickAttackL = 5
    WhirlAttack  = 10
AND phase == Hit

-> return 2500 for this call only

otherwise
-> return raw
```

Explicit exclusions:
```text
Normal
Power
SimpleWhirl
Sprint
Pierce
Hack
Raise
Recover
NPCs
persistent timer/actor state
production G3AB changes
```

Minimal diagnostics:
log only actual clamp events with raw duration + factual action + phase (+ player identity if cheaply available from the same established facts). Do not create a getter-call trace.

## Why this classifier is intentionally narrow

Positive destructive bad-skip evidence exists for Quick R/L and full Whirl while still in Hit. Pierce was specifically tested without reproducing destructive abandonment. Working Raise has not reproduced this specific defect. No corresponding positive evidence currently exists for the other excluded attack families/phases.

Player input mapping is now durable in `ANIMATION_RULES.md §5`:
- press LMB -> Normal;
- hold LMB -> Power;
- press RMB -> Quick;
- hold RMB -> Block/Parade;
- hold RMB + hold LMB -> Hack for 2H/Staff, Pierce for 1H;
- hold RMB + press LMB -> full Whirl for 2H/Staff, Quick for 1H;
- short hold LMB below Power threshold -> SimpleWhirl for 1H+1H.

This strengthens the causal hypothesis because the demonstrated vulnerable positive families are the held-RMB/block + **press-LMB** continuation routes. Keep input Action1/Action2 separate from `gEAction` enum values.

## Research vehicle / implementation boundary

```text
Script_G3AnimationBehaviors.dll
= protected production candidate

Script_G3AB_BadBlockResearch.dll
= isolated temporary research target
= tools/Script_G3AB_BadBlockResearch/
```

For the bounded Work implementation:
- source edit + static audit + publication to `development` are authorized;
- BUILD is prohibited;
- DEPLOYMENT is prohibited;
- Gothic runtime is prohibited.

After Work publishes, Normal Chat performs an independent diff-against-contract review before local build/runtime.

Final product placement remains undecided:
- integrate proven minimum into G3AB;
- clean into separate optional DLL;
- discard experiment.

NPC overlap remains unresolved and separate. The designed `+0x46F39` observer is not part of this task.

# Bad Block Skip — Player Hit Deferral Experiment

**Status:** ACTIVE  
**Mode:** bounded research-DLL source implementation  
**Decision authority:** implementation only; User + Normal Chat retain experiment interpretation and final product placement  
**Stable fallback:** `main @ e899f37092706a9846312b93d6b52b34e715b53d`  
**Implementation launch base:** `8e277379e14cd94bbb9113f85ffe01fe8e2c4b48`

## Purpose

Test the smallest evidence-backed intervention for the demonstrated player bad-block skip defect:

```text
do not let the player block-timeout teardown destroy a demonstrated vulnerable attack Hit
```

This is a **temporary mechanism experiment**, not production architecture.

Exact remaining-time pause/resume is not required. The native held-input timer may keep advancing and an already-due timeout may fire immediately after the protected Hit ends.

The completed option research is archived at:

`docs/archive/investigations/bad_block_attack_protection_options_2026-10-07.md`

Reusable source/hook facts are owned by `docs/SOURCE_HOOK_GUIDE.md §6`.  
Player input -> attack-family mapping is owned by `docs/ANIMATION_RULES.md §5`.

## Protected production boundary

During this experiment:

```text
Script_G3AnimationBehaviors.dll
= PROTECTED
= no bad-block research hooks/state/experiments

Script_G3AB_BadBlockResearch.dll
= ONLY implementation target
= tools/Script_G3AB_BadBlockResearch/
```

Do not modify production Collision, Speed, Raise, Movement, BehaviorProfiles, EngineBridge, or production INI behavior.

Final disposition remains deliberately open:
1. integrate a proven minimum into G3AB;
2. clean it into a separate optional production DLL;
3. discard the experiment.

This task does not decide among them.

## Exact proven player seam

Tested `Script_Game` path:

```text
+0x633BF  call PropertyDurationPressedMSecs getter
+0x633C5  cmp eax, 2500
+0x633CA  jbe bypass
else:
+0x633F1  PSRoutine::FullStop
+0x63409  PSRoutine::SetState("PS_Melee_Loop")
```

Historical EV-185/187/190 establish destructive bad-skip cases for:
- factual `QuickAttackR = 4`;
- factual `QuickAttackL = 5`;
- factual `WhirlAttack = 10`;
- critical timeout selection while the vulnerable attack is still in `Hit`.

EV-191 did not reproduce the destructive abandonment for Pierce. EV-198 preserves the observation that the specific failure has not been successfully reproduced when the attack has a working Raise.

No corresponding positive bad-skip evidence currently exists for Normal, Power, SimpleWhirl, Sprint, Hack, Raise, or Recover.

## Frozen experiment classifier

At the exact `Script_Game +0x633BF` call site:

1. call the native/current `DurationPressedMSecs` getter **exactly once**;
2. preserve that raw return value unless every condition below matches;
3. when every condition matches, return `2500` for this call only.

```text
raw > 2500
AND receiver-owning actor == player
AND factual Routine Action is one of:
    QuickAttackR = 4
    QuickAttackL = 5
    WhirlAttack  = 10
AND factual phase == Hit

-> return 2500

otherwise
-> return raw
```

This is stateless branch-local deferral, not timer mutation and not pause/resume.

### ABI / actor-resolution requirement

The duration-getter receiver is the CharacterControl wrapper.

Its stored pointer is an engine property set. Resolve the owning actor through:

`eCEntityPropertySet::GetEntity()`

Do **not** cast that stored pointer directly to `eCEntity*`.

If the required ABI/receiver/actor/action/phase transport cannot be implemented faithfully from established source/API facts, STOP and report the contradiction. Do not invent another ownership route.

## Explicit exclusions

The first experiment must not protect:

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
```

Also prohibited:
- persistent actor or timer state;
- global hook/override of the shared duration getter/IAT;
- mutation of generic CharacterControl timing;
- global suppression of FullStop or SetState;
- NPC `+0x46F39` observer/intervention;
- new attack-family inference from filenames;
- production G3AB changes;
- unrelated cleanup/refactor.

## Diagnostic surface

Keep diagnostics minimal and A/B-comparable.

Normal Chat runtime refinement authorized by the User on 2026-10-07:
- build CONTROL and PROTECTION from the same hook/classifier/logger source;
- CONTROL preserves native `raw`;
- PROTECTION returns `2500` only for the frozen qualifying predicate;
- use diagnostic-only episode suppression so one continuous qualifying window emits one concise `Episode start` record instead of one line per getter call;
- the diagnostic episode latch/ordinal must not decide protection, extend protection, mutate timing, or become gameplay lifecycle state;
- any non-matching call rearms the diagnostic latch.

Each episode-start record must include:
- mode (CONTROL / PROTECTION);
- raw duration;
- effective duration;
- factual action;
- factual phase;
- actor/player identity;
- diagnostic episode ordinal.

Startup/unload logging may remain. Do not restore the previous high-volume per-call clamp trace.

## Question this experiment must answer

```text
Is suppressing only the demonstrated player's overdue block-timeout selection
during Quick R / Quick L / full Whirl Hit sufficient to preserve the native
attack continuation and normal hit/damage opportunity, while leaving all other
block timing and attack lifecycle behavior native?
```

## Build / runtime authorization

For the bounded Work/source implementation:

```text
BUILD = PROHIBITED
DEPLOYMENT = PROHIBITED
GOTHIC RUNTIME = PROHIBITED
```

Work may perform source/static audit only and publish the bounded source edit to:
- repository: `tcholti/Gothic3_Animation_Behaviors`;
- branch: `development`.

After Work publishes, Normal Chat must independently review the diff against this contract before any local build/runtime validation.

## Source implementation / independent review

Work implementation candidate:
`6ab5bd8e3e7ee75a1707d412f00d9f35dcbbdae2`

Independent Normal Chat source review: **PASS**.

Review confirmed:
- commit is exactly one commit ahead of launch base `8e277379e14cd94bbb9113f85ffe01fe8e2c4b48`;
- only the four files under `tools/Script_G3AB_BadBlockResearch/` changed;
- one `mCCallHook` owns only `Script_Game +0x633BF`;
- SDK default hook mode is `OnlyStack`; `.AddThisArg()` passes original ECX without shared receiver storage;
- the six-byte indirect call is replaced as a whole and native `cmp eax,2500` / `jbe` remain intact;
- the adapter reads the current `+0xE4990` IAT target and invokes that getter exactly once with the original receiver;
- actor ownership resolves through `m_pEngineEntityPropertySet->GetEntity()`;
- only player factual Action4 / Action5 / Action10 + factual Hit can clamp;
- every other condition returns the native raw value;
- diagnostics occur only on actual clamps;
- no persistent actor/timer state, NPC handling, production G3AB change, global duration mutation, or global FullStop/SetState suppression was added.

No source/API contradiction was found.

Build/runtime acceptance remains open. Keep this task ACTIVE until runtime evidence closes the causal question.

## Future runtime fixture — not part of this task

Initial causal fixture when the User is back at the authoritative Gothic build PC:

```text
Gothic 3 / CP + Alternative AI
+ Script_G3AB_BadBlockResearch.dll
- Script_G3AnimationBehaviors.dll
- Script_NewBalance.dll
```

Minimum intended player cases:

```text
1H:
hold RMB > 2.5 s
while still holding RMB, press LMB
-> Quick
-> normal attack continuation/hit should survive

2H / Staff:
hold RMB > 2.5 s
while still holding RMB, press LMB
-> full Whirl
-> normal attack continuation/hit should survive
```

Control behavior outside the frozen classifier remains native.

### Frozen A/B causal comparison — 2026-10-07

Use the same initial causal fixture for both runs:

```text
Gothic 3 / CP + Alternative AI
- Script_G3AnimationBehaviors.dll
- Script_NewBalance.dll
```

The two products are built from the same research source:

```text
A / CONTROL:
+ Script_G3AB_BadBlockResearch_Control.dll
qualifying call -> log episode start -> return native raw unchanged

B / PROTECTION:
+ Script_G3AB_BadBlockResearch.dll
qualifying call -> log episode start -> return 2500
```

The intended first A/B case is the historically repeatable 2H/staff full-Whirl failure:
1. hold RMB long enough that the timeout is overdue;
2. trigger full Whirl with press-LMB while still holding RMB;
3. target the timing where bad skip historically occurs after weapon collision has armed;
4. let the visible attack finish;
5. before any new attack, stumble, weapon change, or other cleanup action, run the still-drawn weapon into an NPC.

Causal outcome:
- CONTROL should preserve the native destructive behavior when the historical failure is reproduced; stale armed collision afterward is a strong visible signature.
- PROTECTION should record the same qualifying Action10/Hit overdue condition but prevent the destructive timeout; native attack continuation/cleanup should survive and running into the NPC afterward should not cause stale-collision damage.

Freeze raw filenames:
- `research/raw/2026-10-07_bad_block_player_whirl_control.log`
- `research/raw/2026-10-07_bad_block_player_whirl_protection.log`

Do not broaden the classifier or add NPC intervention between A and B.

NPC overlap remains a separate later evidence question. The already-designed `+0x46F39` observer is not authorized by this task.

## Work deliverable

Implement only the frozen research-DLL experiment, audit the exact diff, commit/publish to `development`, and report:
- files changed;
- exact hook/transport used;
- exact classifier implemented;
- diagnostic line shape;
- protected production files confirmed unchanged;
- source/static checks performed;
- any source/API contradiction;
- final remote commit SHA;
- `Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`

Then STOP. Do not archive this document; Normal Chat owns review, runtime freeze, evidence promotion, and eventual closure.

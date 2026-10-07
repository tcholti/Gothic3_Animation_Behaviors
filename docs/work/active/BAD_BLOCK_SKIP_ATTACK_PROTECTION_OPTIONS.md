# Bad Block Skip — Attack Protection Options

**Status:** ACTIVE  
**Mode:** bounded read-only architecture / option comparison  
**Decision authority:** advisory only for any delegated Work task; User + Normal Chat retain final choice  
**Stable fallback:** `main @ e899f37092706a9846312b93d6b52b34e715b53d`

## User-visible problem

A bad block skip can destroy the engine-side attack continuation while the visible attack animation keeps playing.

After collision repair, stale collision is correctly cleaned, but the surviving animation can visibly connect without a normal hit/damage outcome.

The first-release goal is therefore:

```text
do not let block-timeout teardown destroy a live attack
```

Exact remaining-time pause/resume is **not required**.

It is acceptable if the native timer continues internally and the block skip fires immediately after the attack has safely completed.

Prefer, if practical:

```text
defer until the ordinary native attack/cleanup path has had its opportunity
```

If exact cleanup completion cannot be observed cheaply, protect the smallest factual attack lifetime that reliably prevents the visible missed-hit problem.

## Proven static facts

Player:
```text
+0x633BF DurationPressedMSecs getter
+0x633C5 compare 2500
+0x633CA jbe bypass
else:
+0x633F1 FullStop
+0x63409 SetState PS_Melee_Loop
```

NPC Alternative AI:
```text
OnAI_Parade
non-player
StatePosition == 1
StateTime > 2.0
-> +0x46F39 StopAIGoto
-> +0x46F51 SetState ZS_Attack_Loop
```

These are separate mechanisms.

## Required option space

Do not decide that an imperfect option is unacceptable. Return evidence, costs and options to User + Normal Chat.

Compare at minimum:

### Option A — Integrated player deferral in main G3AB DLL

One narrow call-site adapter at the proven player duration getter seam.

Questions:
- exact actor resolution/ABI;
- smallest factual attack-active classifier;
- which phases/actions must be protected;
- whether allowing timeout immediately after protected state ends is mechanically safe;
- compatibility with New Balance and existing hooks;
- runtime cost and regression surface.

### Option B — Separate optional bad-block-skip patch DLL

Same or equivalent narrow player intervention, packaged independently.

Questions:
- hook/load-order interaction with G3AB/New Balance;
- whether it can remain truly optional and removable;
- installation/config clarity;
- whether duplicate/shared hook ownership creates avoidable risk;
- maintenance burden versus compatibility benefit.

### Option C — NPC-specific protection

Do not implement or recommend automatically.

First decide whether current evidence is enough to show the NPC 2-second parade timeout can overlap a factual attack. If not, preserve the already-defined smallest observation-only probe at `Script_Game +0x46F39`.

If overlap is proven later, compare:
- integrated NPC branch deferral;
- optional patch ownership;
- whether player/NPC can share policy while keeping separate physical seams.

### Option D — No change for v1

Keep as a real fallback and state the gameplay consequence clearly.

## Acceptance / approximation boundary

Hard requirement:
- do not silently break legitimate reaction interruption paths;
- do not globally mutate CharacterControl timing;
- do not globally suppress FullStop/SetState;
- preserve Collision, Speed, Raise and Movement.

Accepted imperfection:
- native block timer may continue to advance during the attack;
- once attack protection ends, an already-due bad skip may fire immediately;
- exact remaining-time preservation is unnecessary.

Open preference:
- ideally allow ordinary native attack cleanup before the skip becomes eligible again.

## Deliverable

Return:
- strongest viable integrated option;
- strongest viable optional-DLL option;
- NPC evidence status and smallest next step;
- exact differences/trade-offs;
- recommendation if useful;
- **do not close the product decision**.

No implementation until User + Normal Chat choose an option.


## Research vehicle decision — separate experimental DLL

Accepted by User + Normal Chat before probe/intervention implementation.

During all bad-block research:

```text
Script_G3AnimationBehaviors.dll
= protected production candidate
= no bad-block research hooks/state/experiments

Script_G3AB_BadBlockResearch.dll
= isolated research vehicle
= probes/interventions may change freely
= removable without changing production behavior
```

Repository target:
`tools/Script_G3AB_BadBlockResearch/`

The research DLL begins as an intentionally empty bootstrap target with startup logging and **no hooks**.

Allowed future contents are limited to the bad-block responsibility:
- player timeout observation/deferral;
- NPC timeout observation/deferral;
- factual attack-active classification needed by those experiments;
- diagnostics required to validate those mechanisms.

Do not copy into it:
- Collision guardian behavior;
- Speed;
- Raise;
- Movement;
- production BehaviorProfiles;
- unrelated diagnostics.

Final product placement remains open:
1. prove behavior in research DLL, then integrate the minimum proven policy into G3AB;
2. clean the research mechanism into a separate optional production DLL;
3. discard the experiment with no production impact.

### Isolation test fixtures

Initial causal fixture:
```text
Gothic 3 / CP + Alternative AI
+ Script_G3AB_BadBlockResearch.dll
- Script_G3AnimationBehaviors.dll
- Script_NewBalance.dll
```

This fixture intentionally lacks the production collision guardian. Native stale-collision consequences in control cases are therefore expected evidence, not a G3AB regression.

Later integration fixtures:
```text
Research DLL + G3AB, New Balance OFF
Research DLL + G3AB + New Balance
```

Do not choose final integrated-vs-optional packaging from the research target alone.


## Work advisory research result — 2026-10-07

Durable report:
`docs/archive/investigations/bad_block_attack_protection_options_2026-10-07.md`

Research completed read-only. No implementation/build/deployment/runtime work was performed.

### Player

Strongest minimal candidate is **P1 stateless player deferral**:

```text
Script_Game +0x633BF
call current native DurationPressedMSecs getter exactly once

if raw > 2500
+ receiver-owning actor is player
+ factual Routine Action is ordinary protected melee
+ phase is Raise / Hit / Recover
-> return 2500 for this call only

otherwise
-> return raw
```

Important ABI correction:
- receiver is the CharacterControl wrapper;
- its stored pointer is an engine property set;
- resolve the owning actor through `eCEntityPropertySet::GetEntity()`;
- do not cast that stored pointer directly to `eCEntity*`.

One call-site hook; no persistent actor/timer state; O(1).

Three viable classifier variants remain:
- P1: action + Raise/Hit/Recover;
- P2: action regardless of phase;
- P3: P1 plus proven live outer attack ScriptFunction context.

P1 is the recommended **first mechanism experiment**, not automatically the final classifier.

### NPC

NPC timeout overlap remains unresolved statically.

Smallest later observer:
`Script_Game +0x46F39` immediately before `StopAIGoto`.

One positive record showing the same actor at this exact selected timeout branch with a factual live attack instruction or evidenced live attack continuation is sufficient to prove existential overlap.

No positive record in a finite run does not prove impossibility.

A future NPC intervention, only if overlap is proven, has a plausible sibling seam at the `StateTime` getter before the native 2.0-second comparison; this is not authorized yet.

### Current decision gate

User + Normal Chat must choose the next experiment.

Work recommendation:
1. first run isolated player P1 deferral;
2. if P1 cleanup-exit behavior is insufficient, evaluate P3;
3. investigate NPC overlap with the designed observer as a separate experiment.

No production placement decision is made.

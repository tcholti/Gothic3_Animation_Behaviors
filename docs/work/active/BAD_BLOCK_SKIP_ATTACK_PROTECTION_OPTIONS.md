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

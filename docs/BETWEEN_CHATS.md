# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-08

## Current Bridge — Sabretooth Cross-Actor Compatibility Before Any New Code

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat must read `SESSION_ENTRYPOINT.md` first, then this file. No Work implementation task is frozen.

---

## Stable State

The mature collision foundation remains closed through the previous checkpoints:

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
architecture verification                  CLOSED/PASS — EV-208–EV-215
Power                                      CLOSED/PASS — EV-241
Pierce                                     CLOSED/PASS — EV-242
SimpleWhirl                                CLOSED/PASS — EV-217–EV-220, EV-243
Hack tested 2H/Staff scope                 CLOSED/PASS — EV-216, EV-244
human raw-8 FIST Normal/Power              CLOSED/PASS — EV-221–EV-240
PhysicalFist/raw55 bounded discovery       CLOSED/DEFERRED — EV-245–EV-246
```

Raw55 remains unobserved/deferred. Do not create a raw55 implementation without future factual runtime `UseType == 55` evidence.

The September 8 native-source survey established several native body attackers as factual `Fist` / raw8 / group0 with damaging caller `Game +0x16E348`, while Demon/Goblin/Ogre resolved their factual equipped 2H/1H/Axe sources. That survey alone did not prove marker compatibility.

---

## New Evidence — EV-247

Published source artifact:

```text
research/raw/2026.09.08_sabertooth_marked_attacks.log
source commit: bf1c59f15815cbac11b75ffcee9ebc6d424c7840
```

Test setup:

- actor: `Transform_Sabertooth_Potion`;
- target: Boar;
- marked Normal, Quick-left/right and Power Sabretooth attacks;
- User visual observation: all selected attacks physically connected.

Interpretation:

### Normal — PASS

The marked Normal animation resolved factual `Fist` / raw8, entered the existing FIST ownership mechanism, accepted `G3AB_COL_FIST`, matched ownership/timing state and damaged the Boar through `Game +0x16E348` after the authored opportunity.

### Power — PASS

The marked Power animation likewise resolved factual raw8 `Fist`, entered ownership, accepted the FIST marker and damaged through the native `Game +0x16E348` body-damage route.

### Quick-left/right — NOT MARKER-CONTROLLED

Quick-left/right also resolved factual raw8 `Fist` and physically damaged through `Game +0x16E348`, but every authored FIST marker was:

```text
MarkerAction: REJECTED_UNSUPPORTED_HIT
```

Source review explains the result exactly: current marker processing rejects FIST unless the family is Normal or Power. Quick therefore remained native despite visually connecting.

Canonical evidence: EV-247.

Artifact disposition:

```text
research/raw/2026.09.08_sabertooth_marked_attacks.log
= ACTIVE COMPARISON — KEEP RAW
```

Do not archive it yet. It is the transformed-player comparison input for the next native-Sabretooth run.

---

## Architecture Clarification Frozen Today

The desired architecture is **not human-animation-family-only** and should not grow species-specific marker rules.

The earlier “human raw-8 Fist” wording came from two evidence limitations:

1. raw8 vs raw55 was initially suspected to separate human and monster/body mechanisms;
2. humans gave us testable FIST Normal/Power cases but no Quick-Fist fixture, so Quick was deliberately left unsupported rather than guessed.

EV-245–EV-247 now clarify the intended model:

```text
factual source = gEUseType_Fist / raw8
+
supported/proven native attack-family mechanism
+
Hit phase
+
exact current animation contains G3AB_COL_FIST

-> authored raw8 FIST opportunity
```

Do not add a Human_ filename check, Sabretooth-specific branch, species table or separate monster marker vocabulary.

Raw55/PhysicalFist remains a separate unsupported source type unless future factual raw55 evidence appears.

---

## NEXT — Native Sabretooth NPC -> Player Control

**Do not write code first.**

Use the same marked Sabretooth Normal/Power animations that already passed while transformed, then let a genuine native Sabretooth NPC attack the player.

Question:

> Does the existing raw8 Normal/Power FIST mechanism still own authored timing when the attacker is a native NPC rather than `Transform_Sabertooth_Potion`?

Before the run, freeze one exact raw filename under POP-05.

Minimum useful cases:

```text
marked Normal
marked Power
```

Quick does not need to be part of this first actor-side control because current code already rejects it by design.

What to require from the log:

```text
Actor = native Sabretooth NPC
factual source = Fist / raw8
HasFistMarkers = 1
Normal/Power FIST marker = ACCEPTED
ownership/timing identity matches
no pre-marker native damage leak
contact damage, when it occurs, follows through native Game +0x16E348
```

If native Sabretooth Normal/Power passes, the actor-family question is substantially closed for this fixture and the next responsibility is Quick mechanism classification.

If it fails, stop and classify the exact actor-side difference before any broadening.

---

## After Native Sabretooth — Planned Bounded Sequence

### 1. Raw8 Quick mechanism classification

Current facts from EV-247:

```text
Quick source = raw8 Fist
Quick damage caller = Game +0x16E348
FIST markers = explicit REJECTED_UNSUPPORTED_HIT
```

Before implementation, determine whether Quick uses the same relevant `SPU+0x164` / timing-opportunity mechanism sufficiently to reuse the existing FIST contract.

Only if that is proven should the smallest family-gate extension be implemented and validated.

### 2. Native equipped-NPC marker controls

User plans separate logs for:

```text
Goblin -> 1H / raw2
Demon  -> 2H / raw3
Ogre   -> Axe / raw52
```

Put ordinary equipped collision markers on selected native NPC attack animations and let each NPC attack the player. Keep each NPC in a separate log.

Purpose: confirm equipped marker behavior follows factual source/action semantics for NPC attackers rather than depending on player/human animation-family assumptions.

### 3. Separated 2H vs Axe mod

Install the mod that separates 2H from Axe animation families, mark selected new 2H and Axe animations, and validate collision ownership independently.

### 4. Separated 1H vs Rapier mod

Install the mod that separates ordinary 1H from Rapiers, mark selected animations from each side, and validate collision ownership independently.

### 5. Final native mixed collision regression

Only after the bounded compatibility gates above are closed.

Then continue the established roadmap:

```text
final native mixed regression
-> separate AttackContinuationProtection
-> combined marker/lifecycle/continuation regression
-> mature New Balance + relevant Jackydima compatibility
-> production collision migration
```

---

## Hard Boundaries

```text
NO code before the native Sabretooth actor-side control
NO raw55 implementation without factual UseType55 evidence
NO species/name-specific marker branching
NO separate monster marker vocabulary
NO Quick FIST implementation before native-mechanism proof
NO AttackContinuationProtection work inside these compatibility gates
NO Raise/speed work
NO broad source/lifecycle redesign
```

---

## GitHub Desktop Handoff

This planned maintenance commit will advance the remote branch beyond the User's local checkout.

Before the next local test/write window, guide the User through:

```text
open GitHub Desktop
-> select Gothic3_Animation_Behaviors
-> confirm Current branch = docs/collision-source-evidence
-> click Fetch origin
-> if offered, click Pull origin
-> verify Changes shows 0 changed files
```

The User is still a GitHub Desktop beginner; repeat these concrete steps when next needed.

---

## Evidence / Continuity Rule

Continue POP-05/POP-06 for every new runtime artifact:

```text
freeze exact test + filename
-> User runs locally
-> copy unchanged log to research/raw
-> Commit + Push
-> Normal Chat interprets
-> promote reusable result to canonical EV
-> explicit artifact disposition
-> archive only when no active comparison still needs raw
-> update smallest affected authorities/current-state pointers
-> then advance
```

This is a trustworthy planned handoff once the accompanying maintenance commit is published.

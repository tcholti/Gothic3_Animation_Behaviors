# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-15

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. `Script_FrameCollisionBehaviorTest` is the diagnostics-free behavior twin. The eventual shipped plugin remains `Script_G3AnimationBehaviors`; proven collision responsibilities must be deliberately promoted into permanent release-owned modules while `PhysicalFistProbe` and diagnostic scaffolding are excluded/removed.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe authority: **none — Normal Chat causal planning is current**  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_283_ONWARD.md` through **EV-283**  
Authoring semantics: `docs/ANIMATION_RULES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Current Checkpoint

```text
raw55 Quick       CLOSED/PASS through EV-273
raw55 true Power  first-contact CLOSED/PASS through EV-276
raw55 Normal      first-contact CLOSED/PASS through EV-279
raw55 Sprint      first-contact CLOSED/PASS through EV-282
raw55 two-FIST cross-family runtime CLOSED as evidence — EV-283

NEW OPEN BOUNDARIES FROM EV-283:
    Normal pre-StatePosition FIST ownership
    non-Quick repeated-FIST contact/rearm semantics
    Sprint-origin same-C1 Action9 -> Action2 repeated-marker continuity

New Balance 0.7.0 released 2026-09-14:
    stale public GitHub source shows no identified direct old-code overlap
    exact 0.7.0 source not represented by linked GitHub master
    runtime compatibility certification REQUIRED

permanent raw55 architecture synthesis = PAUSED until causal + compatibility gates are closed
```

Raw8 FIST remains a separate proven mechanism and must not be altered by raw55 research.

No permanent raw55 implementation is authorized yet.  
No Work/source task is currently frozen.  
Recovery Lock remains **CLOSED**.

---

## EV-283 — What Changed

Runtime:

```text
research/raw/2026.09.15_troll_raw55_double_fist_activation.log
SHA256 3771B3A9601D5CF3A715B6B15DF39DA5B55B0881CF8A127D1E9CFE436E898E43
```

### Quick

Quick positively repeats the already-closed EV-273 semantics: two authored FIST occurrences can create two native damage events in the same C1 when the later occurrence performs the proven triggered-list rearm. A second marker is an opportunity, not guaranteed damage if contact geometry misses.

### Normal

The first FIST can arrive at `StatePosition=0` before the Normal suppression proof exists. The current diagnostic Normal probe ignores that first occurrence; a later SP1 FIST becomes the first activation. This is a genuine pre-state ownership gap, not proof that Normal can only hit once.

### Power

A second FIST is delivered in the same C1 after first-contact opening/damage, but the current diagnostic Power proof is one-shot and does not attempt repeat rearm. Therefore repeated Power semantics remain untested.

### Sprint-origin execution

Repeated C1s show:

```text
FIST #1 while factual Action9 / SPRINT -> 5 -> 7 -> native damage
same C1 then changes to factual Action2 / POWER
FIST #2 arrives under Action2 while the same source remains group7
current family-specific one-shot proofs do nothing
native cleanup later returns 7 -> 5
```

The post-contact Action2 state is not a new C1 or new attack execution. Permanent marker-occurrence ownership must eventually respect that continuity.

### Prohibited inference

Do not copy `activationUsed` one-shot diagnostic bookkeeping into production. EV-270 already rejected that as final authoring semantics; EV-273 proves each legitimate Quick FIST occurrence can be its own rearm opportunity.

---

## Current Responsibility — Normal Chat Causal Closure Before Architecture

Do **not** launch permanent implementation Work.

Choose and freeze the smallest next causal responsibility from:

```text
1. Normal pre-state FIST
   Establish whether a legitimate Normal FIST at SP0 can own the initial exact RIGHT raw55 opening
   while native StatePosition progression and native cleanup survive.
   Do not assume Quick's ClearTriggeredList requirement applies.

2. Non-Quick repeated FIST
   Establish what exact operation, if any, FIST #2 needs while the raw55 source is already group7
   to create another native contact opportunity for Normal/Power/Sprint-origin executions.
   Test rather than infer ClearTriggeredList.

3. Sprint-origin Action9 -> Action2 continuity
   Repeated-FIST permission must be scoped to the same factual C1/source execution rather than treating
   the post-contact Action2 state as an independent Power attack.
```

Freeze only one causal intervention at a time.

---

## New Balance 0.7.0 Compatibility Requirement

Compatibility with Jackydima's New Balance is mandatory for this mod.

Current release evidence:

```text
New Balance version = 0.7.0
last updated on Nexus = 2026-09-14
```

Linked public source:

```text
Jackydima/G3Script_NewBalance
master = 6f527c103d08708e89a80fc4fc8954546e1b93b1
master date = 2024-11-27
```

The linked GitHub source therefore predates 0.7.0 and cannot certify the current release.

Historical public Fist patch:

```text
commit 2a82f9cb604262ee6ce24aceeffc81e674224e8c
Script_Game +0xAA5E6..+0xAA5EB
removes a current/friendly-target limitation for Fist attacks, especially transformed PC_Hero
```

No direct address/function collision with this project's known marker/raw55 transport surfaces has been identified in that historical source, so old-source static overlap risk is LOW.

This is not a 0.7.0 compatibility result. Final raw55 closure requires runtime coexistence validation against New Balance 0.7.0, including actual Fist/raw55 behavior rather than load-only smoke.

---

## Still Paused

```text
NO permanent raw55 architecture freeze
NO production PhysicalFistCollision
NO copying PhysicalFistProbe scaffolding
NO assumption about non-Quick repeated ClearTriggeredList
NO ignoring Normal SP0 marker delivery
NO blanket New Balance 0.7.0 compatibility claim from stale GitHub source
NO broad native-creature certification continuation
NO Axe/Rapier compatibility sequence
NO AttackContinuationProtection work
```

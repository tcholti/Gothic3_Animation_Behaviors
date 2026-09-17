# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-17

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. The eventual shipped plugin remains `Script_G3AnimationBehaviors`; `PhysicalFistProbe` is not production architecture.

> **LARGE-LOG RULE:** Do not orient by scanning raw/archive logs. Use canonical EV first and the committed derived package for large-log retrieval. Processed source evidence moves unchanged to `research/archive/`.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Latest canonical evidence: **EV-294** in `docs/EVIDENCE_LEDGER_291_ONWARD.md`

## Current checkpoint

```text
raw55 Quick         repeated-FIST CLOSED/PASS — EV-273
raw55 Normal        repeated-FIST CLOSED/PASS — EV-292
raw55 true Power    repeated-FIST CLOSED/PASS — EV-293
raw55 Sprint-origin repeated-FIST CLOSED/PASS — EV-294

ALL FAMILY-SPECIFIC RAW55 CAUSAL PROBING CLOSED
```

## EV-294 factual result — Sprint-origin repeated FIST

Representative factual Troll C1=24:

```text
Action9 / Family SPRINT
-> EV-281 exact premature RIGHT raw55 5 -> requested7 suppression
-> original _AI_PowerAttack still advances StatePosition 0 -> 1
-> RIGHT remains group5

first authored Sprint FIST at SP1
-> exact RIGHT raw55 5 -> 7
-> ClearTriggeredList=0
-> first native ONDAMAGE

same actor / same C1 / same exact RIGHT continues
-> factual Action9 -> Action2 transition
-> RIGHT remains group7

second authored FIST under current Action2 / Family POWER
-> SprintOriginProof=1
-> FirstSprintActivationUsed=1
-> SameC1=1 / SameRight=1
-> MatchingPowerProof=0
-> PRE PC_Hero visited exactly once/count1/aligned
-> one exact RIGHT TouchDamage.ClearTriggeredList()
-> POST PC_Hero absent/aligned
-> no second collision-group request
-> later second native ONDAMAGE

player is already in LieKnockDown_Begin at second ONDAMAGE
-> first-hit knockdown obscured visual confirmation but did not remove hit2

native exact RIGHT 7 -> 5 cleanup
-> outstanding=0
-> clean C1 finalization
```

C1=44, C1=58 and C1=70 independently repeat the decisive Sprint-origin marker2 ownership and PRE visited -> POST absent contact reset.

Runtime identity:

```text
implementation:
32dc52dcba327e74436dcd76b70b21251e06565c

built/live DLL SHA256:
50DA8C98D5C059A857383B2C690D499E1E2F0A3B21760B7626FBA60BDF52D1B8

canonical source:
research/archive/2026.09.17_troll_raw55_sprint_origin_repeat_fist_rearm.log

source SHA256:
5F4AB5E6F0C2C8BE7A0E7331493B7FA7DC02D19139B3218062513CE9FDA05A3C

source Git blob:
f429aa4ccadc08e75a542ad5b12f0e3d372702c1

source upload + derived package commit:
a684dfba2ecc4f72b46140cf8beef3bdf9ceb946

byte-identical archive commit:
08e29d3a4453759dcc53733b7270b4585afe0599
```

## Permanent raw55 synthesis facts

The diagnostic campaign now provides the permanent-design constraints:

```text
1. Authored marker timing owns raw55 offensive timing; native premature raw55 opening must not.

2. Hooks remain transport-only. Proven behavior belongs in a permanent raw55 owner module, not in EngineBridge policy.

3. Quick is the special pre-StatePosition route and retains its proven repeated-contact rearm behavior.

4. Normal:
   marker1 = physical opening + first-contact reset where required by the proven route
   marker2 = contact-bookkeeping clear only
   no marker2 group transition

5. True Power:
   preserve original _AI_PowerAttack and native StatePosition progression
   suppress only premature exact RIGHT raw55 5 -> 7
   marker1 = exact RIGHT 5 -> 7, no clear
   marker2 = contact-bookkeeping clear only

6. Sprint origin:
   preserve original Action9 callback/state progression
   suppress only premature exact RIGHT raw55 5 -> 7
   marker1 under Action9 = exact RIGHT 5 -> 7, no clear
   origin identity must survive factual same-C1 Action9 -> Action2
   marker2 = Sprint-origin contact-bookkeeping clear only
   current Action2 alone must not reclassify the C1 as true-Power origin

7. Repeated FIST does not issue another physical group request where clear-only rearm is proven.

8. Gothic's native final exact RIGHT 7 -> 5 cleanup remains primary ownership.
   CollisionLifecycleGuard remains protection/repair, not ordinary attack semantics.

9. PhysicalFistProbe is disposable diagnostic scaffolding. Do not promote/copy it wholesale.
```

## Immediate next responsibility — NORMAL CHAT ARCHITECTURE SYNTHESIS ONLY

Do **not** launch another Work implementation task yet.

Normal Chat must now inspect the existing permanent module boundaries and synthesize the smallest production responsibility for raw55 PhysicalFist support from the closed EV set.

Before freezing Work:

```text
identify the permanent owner module
identify the smallest required transport seam from existing hooks
separate family-independent raw55 source/contact operations from family-specific routing/timing
preserve existing raw8 Fist behavior unchanged
preserve stable marker semantics and CollisionLifecycleGuard ownership
specify how Sprint-origin identity is represented without diagnostic probe maps/scaffolding
specify removal/non-use of temporary PhysicalFistProbe behavior in production
freeze exact source scope and regression obligations
```

Only after that architecture is documented/frozen may a bounded Work implementation begin.

## Evidence retrieval discipline

Do not scan `research/raw/` or `research/archive/` during orientation.

Use canonical evidence first:

- EV-273 for Quick repeated FIST;
- EV-281/EV-282 for Sprint first-contact transport/timing;
- EV-283 for Sprint Action9 -> Action2 continuity;
- EV-292 for Normal repeated FIST;
- EV-293 for true-Power repeated FIST;
- EV-294 for Sprint-origin repeated FIST.

## Remaining collision order

```text
permanent raw55 architecture synthesis
-> freeze bounded production implementation
-> permanent raw55 implementation
-> standalone collision regression
-> New Balance 0.7 bundle regression exactly as distributed, AttackCollision included
-> collision module complete
-> Raise / speed-control work
```

## Still paused

```text
NO Work task until permanent architecture is frozen
NO promotion/copy of PhysicalFistProbe scaffolding
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

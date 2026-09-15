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
Latest canonical evidence: `docs/EVIDENCE_LEDGER_283_ONWARD.md` through **corrected EV-285**  
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

New Balance 0.7.0 current source:
    Jackydima/gothic3sdk/scripts/Script_NewBalance
    version authority = 0.7.0.0
    source-level compatibility preflight PASS — EV-284
    active Fist change = animation-speed policy

Bundled Script_AttackCollision:
    overlaps equipped-collision callback responsibility
    BUT coexistence already runtime-PASS for marked 2H Whirl (EV-035/EV-150)
    AND a 20-execution Pierce matrix with 1H/Torch+1H/Shield+1H/Dual (EV-242)
    prior mutual-exclusion interpretation is SUPERSEDED — corrected EV-285
    full current 0.7 bundle/family regression remains REQUIRED

Torch+1H authored markers:
    LEFT genuinely supports real torch-strike animations
    RIGHT supports right-hand weapon strikes
    exact slot must follow intended physical contact, not action R/L naming

permanent raw55 architecture synthesis = PAUSED until causal + runtime compatibility gates are closed
```

Raw8 FIST remains a separate proven mechanism and must not be altered by raw55 research.

No permanent raw55 implementation is authorized yet.  
No Work/source task is currently frozen.  
Recovery Lock remains **CLOSED**.

---

## EV-283 — Current Raw55 Open Questions

Runtime:

```text
research/raw/2026.09.15_troll_raw55_double_fist_activation.log
SHA256 3771B3A9601D5CF3A715B6B15DF39DA5B55B0881CF8A127D1E9CFE436E898E43
```

Quick positively repeats the already-closed EV-273 semantics: two authored FIST occurrences can create two native damage events in the same C1 when the later occurrence performs the proven triggered-list rearm. The User also observed the Quick attacks visibly damaging twice.

Normal exposed a pre-StatePosition first-marker boundary; Power and Sprint-origin repeat-FIST semantics remain untested because the current diagnostic proofs are one-shot. Sprint-origin executions additionally show same-C1 Action9 -> Action2 continuity after first contact.

Do not copy `activationUsed` diagnostic bookkeeping into production.

---

## EV-284 — New Balance 0.7.0 Source Compatibility

Current source authority:

```text
https://github.com/Jackydima/gothic3sdk/tree/master/scripts/Script_NewBalance
master = a9f736603bb42c40b6e1556619051b57f9f525b6
Script_NewBalance.rc = 0.7.0.0
```

Source-level compatibility preflight is PASS. Active Fist-specific behavior is animation speed (`Attack=0.70`, `PowerAttack=0.80`); the older Fist friendly/current-target patch is inactive. New Balance's dual-1H triggered-list fix and combat-move scaling are separate from raw55 marker ownership.

---

## Corrected EV-285 — Bundled AttackCollision Coexistence

`Script_AttackCollision` is a separate DLL target but is bundled with New Balance according to the User's current package knowledge. Its source overlaps the same equipped-collision callbacks and uses fixed timer-based collision operations, so it is a real compatibility surface.

Existing controlled evidence nevertheless proves coexistence in the tested installation/load order:

```text
EV-035 / EV-150
New Balance + AttackCollision + FrameCollision v0.19
marked 2H Whirl PASS
no duplicate/timer-owned activation

EV-242
New Balance bad-skip prevention + AttackCollision loaded
20 Pierce executions across 1H / Torch+1H / Shield+1H / Dual P0/P1 PASS
```

Therefore AttackCollision is **not** currently classified as mutually exclusive. The final New Balance 0.7.0 regression must use the bundle as actually shipped, with AttackCollision active when bundled, and broaden coverage to the mature marker families.

Torch+1H correction:

```text
EV-051  P1/P3 Quick can genuinely strike with the LEFT torch
EV-052  some P0 Normal native left-torch openings are unintended for those animations
EV-053  AttackCollision regular Torch+1H Normal routes RIGHT
```

Our marker API intentionally resolves factual equipped slots, so `LEFT` supports a torch strike and `RIGHT` supports the right-hand weapon. Do not infer source from QuickAttackR/L or filename direction tokens.

---

## Current Responsibility — Normal Chat Causal Closure Before Architecture

Do **not** launch permanent implementation Work.

Choose and freeze the smallest next causal responsibility from:

```text
1. Normal pre-state FIST
   Establish whether a legitimate Normal FIST at SP0 can own the initial exact RIGHT raw55 opening
   while native StatePosition progression and native cleanup survive.

2. Non-Quick repeated FIST
   Establish what exact operation, if any, FIST #2 needs while the raw55 source is already group7
   to create another native contact opportunity for Normal/Power/Sprint-origin executions.

3. Sprint-origin Action9 -> Action2 continuity
   Repeated-FIST permission must be scoped to the same factual C1/source execution rather than treating
   the post-contact Action2 state as an independent Power attack.
```

Freeze only one causal intervention at a time.

---

## Still Paused

```text
NO permanent raw55 architecture freeze
NO production PhysicalFistCollision
NO copying PhysicalFistProbe scaffolding
NO assumption about non-Quick repeated ClearTriggeredList
NO ignoring Normal SP0 marker delivery
NO blanket New Balance 0.7.0 full-family runtime compatibility claim yet
NO assumption that bundled AttackCollision must be removed
NO broad native-creature certification continuation
NO Axe/Rapier compatibility sequence
NO AttackContinuationProtection work
```

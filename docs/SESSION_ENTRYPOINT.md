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
Latest canonical evidence: `docs/EVIDENCE_LEDGER_283_ONWARD.md` through **EV-285**  
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
    no direct raw55/marker hook/address collision identified
    active Fist change = animation-speed policy
    runtime coexistence certification still REQUIRED

Script_AttackCollision current source:
    separate optional DLL, not a New Balance dependency
    hooks same attack callbacks and owns timed SetCollisionGroup/ClearTriggeredList/StatePosition
    incompatible with this project's authored marker collision ownership — EV-285
    MUST be absent/disabled when this project's marker system is active

permanent raw55 architecture synthesis = PAUSED until causal + runtime compatibility gates are closed
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

Quick positively repeats the already-closed EV-273 semantics: two authored FIST occurrences can create two native damage events in the same C1 when the later occurrence performs the proven triggered-list rearm. The User also observed the Quick attacks visibly damaging twice. A second marker is an opportunity, not guaranteed damage if contact geometry misses.

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

## EV-284 — New Balance 0.7.0 Source Compatibility

Current source authority:

```text
https://github.com/Jackydima/gothic3sdk/tree/master/scripts/Script_NewBalance
master = a9f736603bb42c40b6e1556619051b57f9f525b6
Script_NewBalance.rc = 0.7.0.0
```

The source-level compatibility preflight is PASS.

Active Fist-specific behavior in 0.7.0 is animation speed:

```text
Script_Game +0x42A0 GetAnimationSpeedModifier
Human Fist Attack = 0.70
Human Fist PowerAttack = 0.80
```

The older Fist friendly/current-target patch at `Script_Game +0xAA5E6..+0xAA5EB` is commented out and inactive.

New Balance's dual-1H `ClearTriggeredList()` fix at `Script_Game +0x482E7` is gated to two 1H weapons and is not the PhysicalFist/raw55 path.

New Balance combat-move scaling at `Game +0x16B8A9` is distinct from this project's `AICombatMoveInstr` entry hook at `Game +0x1696E0`; our wrapper calls the original path, so the New Balance scaling remains reachable.

No direct New Balance ownership of the current `_AI_Attack`, `_AI_PowerAttack`, `_AI_QuickAttack`, `Engine +0x225660 SetCollisionGroup`, or `Game +0x60850` marker transport surfaces has been identified.

Therefore source-level compatibility is established, but one runtime coexistence test with New Balance 0.7.0 active is still required because its faster playback/movement can alter practical contact timing without creating a hook collision.

---

## EV-285 — AttackCollision Is a Separate Incompatible Collision Controller

Current source authority:

```text
https://github.com/Jackydima/gothic3sdk/tree/master/scripts/Script_AttackCollision
```

`Script_AttackCollision` is built as its own shared library. `Script_NewBalance` is also its own shared library and neither links nor loads AttackCollision as a dependency.

AttackCollision hooks the same callback family used by this project's authored collision ownership:

```text
OnAI_Attack
OnAI_PowerAttack
OnAI_QuickAttack
OnAI_PierceAttack
OnAI_SimpleWhirl
OnAI_WhirlAttack
```

plus `OnAI_GetUpAttack`.

It then implements its own fixed-time source activation by calling `SetCollisionGroup(Item_Attack)`, `ClearTriggeredList()` and writing `StatePosition`. It hard-codes hand choice from pose/loadout, including selecting LEFT for dual/Torch+1H Quick P1, rather than respecting per-animation RIGHT/LEFT/BOTH/OFF markers.

That is the same responsibility this project's marker system owns, so simultaneous installation is not a supported composition. Hook load order must not be used as a compatibility mechanism.

Product rule:

```text
Script_NewBalance + Gothic3_Animation_Behaviors = supported target combination
Script_AttackCollision + Gothic3_Animation_Behaviors = NOT supported; mutually exclusive collision authorities
```

Before release, add a clear compatibility warning/guard if `Script_AttackCollision.dll` is loaded. `attacks.ini` belongs to AttackCollision's timer system and is irrelevant to this project's authored markers.

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

## Still Paused

```text
NO permanent raw55 architecture freeze
NO production PhysicalFistCollision
NO copying PhysicalFistProbe scaffolding
NO assumption about non-Quick repeated ClearTriggeredList
NO ignoring Normal SP0 marker delivery
NO blanket runtime compatibility claim before New Balance 0.7.0 coexistence test
NO simultaneous Script_AttackCollision collision ownership
NO broad native-creature certification continuation
NO Axe/Rapier compatibility sequence
NO AttackContinuationProtection work
```
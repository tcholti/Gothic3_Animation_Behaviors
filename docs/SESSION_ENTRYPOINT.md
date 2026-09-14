# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-14

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. `Script_FrameCollisionBehaviorTest` is the diagnostics-free behavior twin. The eventual shipped plugin remains `Script_G3AnimationBehaviors`; proven collision responsibilities must be deliberately promoted into permanent release-owned modules while `PhysicalFistProbe` and diagnostic scaffolding are excluded/removed.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If a Normal Chat ends before evidence closure, use `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11 and enter Recovery Lock before new implementation/runtime/Work. Oversized runtime logs use §9 POP-07.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current frozen probe authority: **none — Normal Chat architecture synthesis is current**  
Latest canonical evidence: `docs/EVIDENCE_LEDGER_280_ONWARD.md` through **EV-282**  
Authoring semantics: `docs/ANIMATION_RULES.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`  
Local paths: `docs/LOCAL_WORKSTATION_PATHS.md`

---

## Current Checkpoint

```text
raw55 Quick       CLOSED/PASS through EV-273
raw55 true Power  CLOSED/PASS through EV-276
raw55 Normal      CLOSED/PASS through EV-279
raw55 Sprint callback ownership CLOSED/PASS — EV-280
raw55 Sprint selective group suppression CLOSED/PASS — EV-281
raw55 Sprint authored-FIST activation CLOSED/PASS — EV-282

raw55 family causal research: COMPLETE ENOUGH FOR PERMANENT ARCHITECTURE SYNTHESIS
```

Raw8 FIST and raw8 Sprint remain separate proven mechanisms and must not be altered by raw55 architecture work.

No permanent raw55 implementation is authorized yet.  
No Work/source task is currently frozen.  
Recovery Lock remains **CLOSED**.

---

## Closed Raw55 Mechanism Summary

### Quick

Quick is the proven special case:

```text
preserve native Quick callback/state progression
suppress premature exact RIGHT PhysicalFist/raw55 opening
authored FIST controls delayed physical opening
pre-StatePosition FIST ordering can occur
ClearTriggeredList/rearm is required for contact behavior
later FIST can rearm repeated contact within the same C1
native cleanup remains Gothic-owned
```

### True Power and Normal

Both prove the simpler first-contact pattern:

```text
preserve native callback
suppress only premature exact RIGHT raw55 5 -> 7
native StatePosition 0 -> 1 survives
authored FIST at StatePosition1 opens exact RIGHT 5 -> 7
ClearTriggeredList=0
native damage
native cleanup 7 -> 5
```

### Sprint — EV-280 through EV-282

Factual Sprint is `Action=9 / Family=SPRINT` at the existing `_AI_PowerAttack` transport.

EV-280 proves the same original Action9 callback owns both native `StatePosition 0 -> 1` and the premature exact RIGHT PhysicalFist/raw55 `5 -> 7`, so whole-callback suppression is invalid.

EV-281 proves that exact nested opening is selectively suppressible while the callback still advances StatePosition and RIGHT remains group5 through authored FIST.

EV-282 closes activation. Three independent Sprint C1s — 16, 57 and 81 — repeat:

```text
Action9/SP0 exact RIGHT 5 -> 7 suppressed
StatePosition 0 -> 1 survives
RIGHT remains group5

authored FIST at factual Action9 / SPRINT / SP1
exact RIGHT raw55 5 -> 7
ClearTriggeredList=0
native damage to PC_Hero
native exact RIGHT 7 -> 5 cleanup
clean C1 fulfillment/finalization
```

Canonical EV-282 runtime:

```text
research/raw/2026.09.14_troll_raw55_sprint_fist_activation_2.log
SHA256 5CB3DCF52A68669C24C44279B69DC84ED404E78C61029DF76499B79088B0361C
```

Probe implementation:

```text
545863c0c522b2cd2d2748f6823a23662bf0ffbf
```

User-local build/deploy identity:

```text
SHA256 783747CC5E6627A1AC0092BB05C7F110813C940B940B208A835C0B2D28A5C597
```

Later callbacks in the same PowerAttack-named motion may become factual Action2 after Sprint contact. Keep that factually separate; family authority is current engine action/ownership, not animation filename.

No Sprint `ClearTriggeredList`/rearm step is currently justified.

---

## Current Responsibility — Normal Chat Architecture Synthesis

Do **not** launch Work yet.

The task is to synthesize a permanent raw55 design from the now-closed family evidence, preserving responsibility separation.

The design must distinguish:

```text
COMMON Power/Normal/Sprint responsibility
    preserve original callback/state progression
    suppress only premature exact RIGHT PhysicalFist/raw55 group5 -> group7
    authored FIST opens the exact current RIGHT raw55 source
    no ClearTriggeredList for first contact
    Gothic owns damage and native cleanup

QUICK specialization
    same delayed authored-opening intent
    supports proven pre-StatePosition marker ordering
    owns the proven triggered-list clear/rearm requirement
```

Standing boundaries:

```text
EngineBridge = hook/transport only
FrameCollisionMarkers = stable author-marker semantics
CollisionLifecycleGuard = offense-obligation/native-cleanup/repair lifecycle owner
Raw8FistCollision = separate raw8 mechanism
PhysicalFistProbe = temporary diagnostics/research only
permanent raw55 behavior must live in an appropriately named responsibility-owned permanent module
```

Do not copy diagnostic maps, observer scopes, probe logs or experimental scaffolding wholesale into production. Promote only proven behavioral responsibilities and the minimum state needed to express them.

Normal Chat and User must agree on this module/responsibility shape before a bounded Work implementation contract is frozen.

---

## Still Paused

```text
NO permanent raw55 implementation yet
NO automatic copy/promotion of PhysicalFistProbe
NO new family probe unless architecture synthesis exposes a real unresolved causal question
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```

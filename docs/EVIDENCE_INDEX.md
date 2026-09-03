# Gothic 3 Animation Behaviors — Evidence Index

**Status:** Cold/reference routing index  
**Updated:** 2026-09-03

## Purpose

Route a technical question to the smallest relevant evidence range without loading the complete evidence ledgers.

Canonical evidence remains one global monotonic namespace split only for storage/retrieval:

```text
EVIDENCE_LEDGER.md                EV-001–EV-157
EVIDENCE_LEDGER_STEP_B.md         EV-158–EV-198
EVIDENCE_LEDGER_199_ONWARD.md     EV-199 onward
```

This index does **not** restate or change evidence status. Open the exact EV entry when wording, qualification, provenance, build scope or engineering consequence matters.

Raw logs are verification/provenance, not routine reading.

Current project responsibility is never owned by this historical index. Use `SESSION_ENTRYPOINT.md` / `BETWEEN_CHATS.md` for current state.

---

## 1. Fast Topic Routing

| Topic / search intent | Start with | Then broaden if needed |
|---|---|---|
| CombatMove fields, native phase/speed baselines | EV-001–EV-011 | `SOURCE_HOOK_GUIDE.md` speed / CombatMove symbols |
| Raise prepend proof / engine animation resolution | EV-006–EV-007 | `DESIGN.md` Raise architecture |
| frame effects / marker channel / frame-effect layout | EV-012–EV-018 | source guide Frame effects |
| ordinary natural weapon reset / marker timing | EV-019–EV-023 | lifecycle evidence for abnormal endings |
| Staff + NPC actor-general marker proof | EV-024–EV-028 | Quick evidence EV-066+; R1-E stability EV-207 |
| Fist/body-contact source semantics | EV-029–EV-032, EV-080–EV-085, EV-207, EV-211 | `ANIMATION_CATALOG.md` Fist fixture |
| repeated-hit rearm / triggered lists | EV-033, EV-106–EV-116 | marker exact-set/replay evidence |
| Hero family / poses / UseType / R-L semantics | EV-036–EV-065 | `ANIMATION_INDEX.md` |
| Quick marker ownership / StatePosition | EV-066–EV-075 | EV-182–EV-196 for lifecycle context |
| Dual native source map / source-explicit marker review | EV-090–EV-094 | EV-207, EV-211, EV-214 |
| multi-target, OFF, duplicate/replay/occurrence guard | EV-106–EV-116 | EV-131–EV-144; archived fixture logs |
| historical marker occurrence-budget leak | EV-131–EV-133 | EV-167; EV-213–EV-214 for C1-generation replacement/closure |
| final RIGHT/LEFT/BOTH/OFF vocabulary | EV-143–EV-144 | `DESIGN.md` / `ANIMATION_RULES.md` |
| Whirl callback/action/source separation | EV-145–EV-147 | `ANIMATION_RULES.md` / cleanup map |
| Hack callback identity / remaining marker expansion | EV-216 | `DESIGN.md` §6.6 |
| SimpleWhirl physical source validation / actor-hit eligibility / Power comparison / StatePosition causal probe | EV-217–EV-220 | `research/derived/2026-09-03_simplewhirl_validation_and_target_semantics_checkpoint.md`; `COLLISION_TEST_PLAN.md` §6 |
| New Balance / AttackCollision Whirl compatibility | EV-035, EV-148–EV-150 | source-guide same-function caution |
| Staff full-Whirl cleanup anomaly | EV-151–EV-156 | EV-180–EV-191, EV-206–EV-207 |
| Recover asset vs lifecycle cleanup | EV-154, EV-160–EV-162 | `COLLISION_LIFECYCLE_PLAN.md` |
| native stale collision / running consequence | EV-156, EV-181, EV-187, EV-190, EV-197–EV-198, EV-202–EV-203, EV-206 | stale-collision reconstruction below |
| PlayMotion / PrimaryFirst replacement timing | EV-157–EV-160 | EV-174–EV-180 |
| action-specific native cleanup matrix | EV-163–EV-166 | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| marker bookkeeping vs physical cleanup | EV-167 | EV-182–EV-196, EV-206–EV-207, EV-213–EV-214 |
| generic script parents / ProcessScript | EV-169–EV-171, EV-195 | cleanup map / source guide |
| rejected deferred replacement finalization | EV-172, EV-180 | historical only; do not revive without new evidence |
| live `scripts` backup-DLL contamination | EV-173, EV-218 | source-guide/build procedure cautions; SimpleWhirl single-twin control |
| CombatMove FullStop / SetState continuation loss | EV-182–EV-191 | `COLLISION_LIFECYCLE_PLAN.md` |
| Alternative-AI held-Use2 trigger | EV-187, EV-197 | test trigger only, not production classifier |
| C1 shadow execution/source obligation | EV-192–EV-193 | lifecycle plan |
| GetUp pre-CombatMove acquisition gap | EV-194 | EV-195–EV-196 |
| outer ScriptFunction lifetime / pointer reuse | EV-195–EV-196 | lifecycle plan execution identity |
| hook transport stabilization / recursion-safe explicit-this | EV-199–EV-203 | `SOURCE_HOOK_GUIDE.md` if implementation detail needed |
| C1-O2 pre-Combat bridge closure | EV-204–EV-205 | lifecycle plan |
| C1-R1 physical repair closure | EV-206–EV-207 | exact-source `7 -> 5`; controlled validation closed |
| second-pass source/build separation | EV-208 | `DESIGN.md` modular architecture / release architecture |
| second-pass CORE diagnostic sufficiency | EV-209–EV-211 | `COLLISION_TEST_PLAN.md` |
| first behavior-only architecture smoke | EV-212 | release architecture |
| Gate 4 C1-generation marker bookkeeping | EV-213 | `COLLISION_LIFECYCLE_PLAN.md` §9 / `DESIGN.md` §8 |
| literal EV-131 same-motion interruption/restart closure | EV-214 | restored 2H Normal fixture / Gate-4 evidence route |
| final diagnostics-free architecture verification | EV-215 | new architecture verification complete |

---

## 2. Native Stale Melee Collision — Causal Reconstruction Route

Use this ordered route only when stale collision/lifecycle safety is again the active engineering responsibility. Do not reread all raw logs.

1. Trigger/reproduction context: EV-187, EV-197–EV-198.
2. Physical stale consequence/persistence: EV-156, EV-162, EV-181, EV-193, EV-202–EV-203, EV-206.
3. Ordinary attack continuation/cleanup: EV-163, EV-182–EV-183.
4. Legitimate reaction interruption + separate cleanup ownership: EV-165, EV-184, EV-186, EV-188, EV-191, EV-203, EV-206, EV-210.
5. Bad held-Use2 abandonment chain: EV-185, EV-187, EV-189–EV-191.
6. Cross-family generality: EV-162, EV-190.
7. Rejected Recover/StartRecover/replacement/callback explanations: EV-154, EV-159–EV-162, EV-168, EV-174–EV-181.
8. C1 execution/source-obligation model: EV-192–EV-196.
9. Hook/finalizer stabilization: EV-199–EV-203.
10. Outer pre-Combat acquisition closure: EV-204–EV-205.
11. Controlled native-equivalent physical repair: EV-206–EV-207.
12. Post-rewrite regression/architecture verification: EV-208–EV-215.

Current architecture: `COLLISION_LIFECYCLE_PLAN.md`.  
Current validation posture: `COLLISION_TEST_PLAN.md`.

---

## 3. Evidence by Engineering Domain

### A. Raise and playback speed

Search terms:

```text
AniSpeedScale
GetAnimationSpeedModifier
PREPEND_BREAK_BLOCK
Raise
RecoverSpeed
```

Evidence: EV-001–EV-011.  
Architecture: `DESIGN.md` Raise / Playback-Speed sections.

### B. Animation-authored frame effects

Search terms:

```text
UpdateFrameEffects
StartEffect
eSFrameEffect
marker frame
playback synchronization
```

Evidence: EV-012–EV-023.  
Reference: `SOURCE_HOOK_GUIDE.md`; `ANIMATION_RULES.md`.

### C. Physical source selection and action-specific character-hit eligibility

Search terms:

```text
RIGHT
LEFT
BOTH
Fist
Torch
Dual
Pierce
Power
SimpleWhirl
character-hit eligibility
target-directed
StatePosition
QuickAttackR
QuickAttackL
Crossbow
```

Evidence anchors:

```text
EV-029–EV-032
EV-047–EV-059
EV-080–EV-085
EV-090–EV-094
EV-145–EV-147
EV-192–EV-194
EV-206–EV-207
EV-211
EV-214
EV-217–EV-220
```

Current SimpleWhirl distinction:

```text
G3AB exact-set markers
= physical equipped-source activation/rearm semantics

native action-specific character-hit eligibility/effects
= separate until evidence proves a uniform framework guarantee
```

EV-217 validates SimpleWhirl physical marker/source behavior. EV-219 rejects a strict selected-target-only model but does not establish reliable two-target/two-sword damage. EV-220 strongly supports a SimpleWhirl-vs-Power action-specific character-hit difference under matched motion content and leaves StatePosition as an unresolved causal candidate.

Asset-level routing: `ANIMATION_INDEX.md`.

### D. Triggered-list rearm / multi-contact / exact-set markers

Search terms:

```text
ClearTriggeredList
EntitiesVisited
multi-target
same-target
duplicate dispatch
occurrence budget
RIGHT LEFT BOTH OFF
```

Evidence:

```text
EV-033
EV-106–EV-116
EV-131–EV-144
EV-213–EV-214
EV-217
EV-220
```

Historical fixture details: `ANIMATION_CATALOG.md` and archived v0.10–v0.18 logs.

### E. Marker execution lifetime / bookkeeping

Search terms:

```text
MarkerExecutionBudget
RetireMarkerOwnedSource
StatePosition
interruption
stale budget
C1Generation
ExecutionBudgetReset
```

Mandatory causal route before changing marker execution identity:

```text
EV-066–EV-075
EV-108–EV-117
EV-128–EV-133
EV-143–EV-147
EV-155–EV-156
EV-167
EV-182–EV-196
EV-206–EV-207
EV-209–EV-214
COLLISION_LIFECYCLE_PLAN.md §9
DESIGN.md §8
```

Accepted current result:

```text
C1 monotonic generation = durable marker occurrence/dedupe execution identity
```

The old source/motion/action/phase/state-time and controlled-callback rollback execution-boundary guesses were superseded by Gate 4. Independent marker invariants remain mandatory.

EV-220 creates a **separate** StatePosition causal question about SimpleWhirl character-hit eligibility. It does not reopen C1-generation marker execution identity.

### F. Native collision cleanup lifecycle

Search terms:

```text
Item_Attack
Item_Equipped
SetCollisionGroup
cleanup
FullStop
AISetState
RunScriptFunction
FinalizeAfterAISetState
LivenessEstablished
REPAIRED_TO_ITEM_EQUIPPED
```

Evidence: EV-151–EV-215 plus SimpleWhirl healthy-cleanup confirmation EV-217.  
Exact native RVAs/stacks: `COLLISION_CLEANUP_CALLSITE_MAP.md`.  
Architecture: `COLLISION_LIFECYCLE_PLAN.md`.

### G. Animation semantics and naming

Search terms:

```text
gEUseType
gEAction
gEPhase
gEPose
HitDirection
destination pose
R/L
overlay
CombatMove distance
```

Evidence: EV-036–EV-065.  
Main routing: `ANIMATION_INDEX.md`.

### H. Compatibility / hook ownership

Search terms:

```text
NewBalance
Script_AttackCollision
same-function hook
load order
ResetOnUntouch
backup DLL
collision twin
```

Evidence: EV-035, EV-045, EV-148–EV-150, EV-173, EV-218.  
Practical source route: `SOURCE_HOOK_GUIDE.md` compatibility/same-function sections; deployment rule: POP-03.

### I. Architecture rewrite / diagnostics-free product separation

Search terms:

```text
EngineBridge
CollisionDiagnostics
Script_FrameCollisionBehaviorTest
release purity
CORE diagnostics
Gate 1 Gate 2 Gate 3 Gate 4
```

Evidence:

```text
EV-208 source/build separation
EV-209–EV-211 CORE diagnostic sufficiency
EV-212 behavior-only smoke
EV-213 Gate-4 generation bookkeeping
EV-214 literal historical regression closure
EV-215 final behavior-only functional/release-purity smoke
```

Authorities:

```text
DESIGN.md
GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md
COLLISION_LIFECYCLE_PLAN.md
COLLISION_TEST_PLAN.md
```

---

## 4. Closed Architecture Boundary

The following is established and should not be rediscovered from older evidence unless a contradiction appears:

```text
C1-R1 lifecycle repair                      CLOSED — EV-206–EV-207
second-pass source/build separation         CLOSED — EV-208
CORE diagnostic sufficiency                 CLOSED — EV-209–EV-211
behavior-only product smoke                 CLOSED — EV-212
C1-generation marker bookkeeping            CLOSED — EV-213
literal EV-131 regression                   CLOSED — EV-214
final behavior-only architecture smoke      CLOSED — EV-215
```

```text
NEW COLLISION ARCHITECTURE VERIFICATION = COMPLETE
```

This index therefore must not route a fresh Chat into C1-O2, Gate 4 implementation, the literal EV-131 regression or final behavior-only smoke as pending work.

The open SimpleWhirl character-hit eligibility question in EV-219–EV-220 is a **new family/framework semantic responsibility**, not a contradiction in the closed C1/Gate-4 architecture.

---

## 5. Future-Responsibility Cross-Routes

### Equipped-melee marker expansion

Before changing ownership/source behavior:

```text
DESIGN.md collision architecture
COLLISION_LIFECYCLE_PLAN.md §9
EV-143–EV-147
EV-206–EV-215
EV-216 for the tested Hack callback identity
EV-217–EV-220 for current SimpleWhirl physical-source / character-hit distinction
ANIMATION_INDEX.md / ANIMATION_CATALOG.md for exact assets
```

Current SimpleWhirl causal checkpoint:

`research/derived/2026-09-03_simplewhirl_validation_and_target_semantics_checkpoint.md`

Do not infer a uniform actor-hit guarantee merely from correct RIGHT/LEFT/BOTH/OFF physical source transitions. The current next falsification is the temporary SimpleWhirl StatePosition-2 control defined in `COLLISION_TEST_PLAN.md` / `SESSION_ENTRYPOINT.md`.

### Fist/body source adapter

```text
EV-029–EV-032
EV-080–EV-085
EV-207
EV-211
DESIGN.md physical source model
```

Do not force weapon `Item_Attack` semantics onto Fist/body sources.

### AttackContinuationProtection

```text
EV-182–EV-191
EV-197–EV-198
COLLISION_TEST_PLAN.md
COLLISION_LIFECYCLE_PLAN.md
```

Prevention must remain separate from lifecycle repair.

### New Balance / Jackydima compatibility

```text
EV-035
EV-148–EV-150
SOURCE_HOOK_GUIDE.md same-function caution
DESIGN.md compatibility section
```

Compatibility is required once on the mature research collision assembly and again on final `Script_G3AnimationBehaviors` after Raise/speed migration.

### Production collision migration / Raise / speed

Start from current architecture authorities and only the exact historical proof routes required by the subsystem being migrated. Do not reconstruct collision chronology wholesale.

---

## Core Retrieval Rule

> **Use the index to find the smallest authority/evidence route, then open the exact EV or authority. Do not treat historical route text as current project state, and do not load whole ledgers merely to regain context.**

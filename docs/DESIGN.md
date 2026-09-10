# Gothic 3 Animation Behaviors — Design

**Status:** Canonical project architecture  
**Updated:** 2026-09-10  
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

`Script_G3AnimationBehaviors` is the general animation-behavior layer for Gothic 3. Active behavior domains are Raise-phase control, attack playback-speed control, and authored-frame collision control. Future independent domains may include target acquisition and climbing.

This file owns overall intended architecture and implementation order. Collision redesign detail is frozen in `COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`; collision lifecycle authority is `COLLISION_LIFECYCLE_PLAN.md`; validation authority is `COLLISION_TEST_PLAN.md`; diagnostics are owned by `COLLISION_LOGGER_PLAN.md`; practical source/hook lookup is `SOURCE_HOOK_GUIDE.md`; exact proof routes through `EVIDENCE_INDEX.md`.

---

## 1. Governing Principles

1. Prefer Gothic native action/phase/UseType/current-motion semantics over filename heuristics when available.
2. Preserve Gothic's own animation resolution whenever possible.
3. Custom behavior is explicit opt-in: config for Raise/speed, exact reserved markers for collision.
4. Separate attack family/phase from the physical damage source.
5. Keep responsibilities separate: physical hook transport in `EngineBridge`, behavior in feature modules, factual source identity in `CollisionSources`, source mutations in `CollisionSourceOperations`, diagnostics in diagnostic-only code.
6. Preserve proven paths while expanding one meaningful responsibility at a time.
7. Unconfigured/unmarked cases fall back to native behavior.
8. Load configuration once into normalized in-memory rules.
9. Require evidence before generalizing actor/family/source-mechanism behavior.
10. One DLL owns each physical Gothic hook; feature modules consume shared bridge facts rather than installing competing hooks.
11. Public release behavior contains no research diagnostics.
12. Known successful runtime behavior should log compactly in CORE; unknown, unsupported, contradictory, repair, or invariant behavior should become richer automatically. Detailed historical probes belong in opt-in DEEP diagnostics.
13. A feature family is defined by factual Gothic action semantics, not by whatever animation filename happens to be playing.

---

## 2. Configuration Identity

Profile identity remains:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile
```

Normalize raw `gEUseType` to animation categories according to `ANIMATION_RULES.md`.

---

## 3. Raise and Speed

### Raise

A configured custom Raise is prepended before the untouched original melee state. Preserve native Raise where already correct. Keep Raise independent from collision lifecycle and continuation protection.

### Speed

Apply speed authority only to matching configured action/profile/phase. Avoid global speed replacement and unsafe same-hook load-order assumptions. `Script_Game +0x42A0 GetAnimationSpeedModifier` remains proof-of-concept, not frozen final architecture. Re-evaluate the final intervention point against New Balance/Jackydima before production speed work.

Recover follows the effective Hit speed; no separate user-facing `RecoverSpeed` key is planned.

---

## 4. Authored-Frame Collision

### 4.1 Generic ownership

At Hit execution, inspect the exact resolved motion and frame effects. No relevant marker means no custom collision ownership. Relevant markers plus valid native/action/phase/source context opt that exact execution into authored timing.

Shared marker infrastructure is limited to:

```text
exact motion/frame-effect scan
reserved marker recognition
occurrence/dedupe bookkeeping
C1 generation as factual execution identity
exact action/phase/animation context
marked-execution opt-in
```

After that, equipped weapons and raw-8 Fist use different native mechanisms.

### 4.2 Equipped weapon vocabulary

```text
G3AB_COL_RIGHT -> {RIGHT}
G3AB_COL_LEFT  -> {LEFT}
G3AB_COL_BOTH  -> {RIGHT, LEFT}
G3AB_COL_OFF   -> {}
```

RIGHT/LEFT identify equipped Gothic slots, not filename side metadata.

Equipped semantics:

```text
marker
-> desired equipped source set
-> Item_Attack / Item_Equipped transitions
-> ClearTriggeredList rearm on each authored contact
```

Repeated source markers later in the same Hit author new contacts. OFF is an intra-Hit physical-source gap, not terminal cleanup.

### 4.3 Production raw-8 Fist

`gEUseType_Fist` / raw 8 is body-contact damage, not a literal right-hand weapon source.

The governing boundary is factual raw-8 source identity plus a supported/proven native attack-family mechanism and exact current Hit/marker context. Human/species identity and animation-family naming are not governing applicability rules.

Known relevant native route in the tested Game.dll:

```text
gCScriptProcessingUnit::sAICombatMoveItlLoop = Game +0x16DD00
SPU+0x164 gate check                         = Game +0x16DFB9
GetMaxTime motion-0 arm                     = Game +0x16E160..+0x16E164
GetPlayTime motion-0 call                   = Game +0x16E180
threshold compare                           = Game +0x16E18C..+0x16E190
native latch close SPU+0x164 = 1            = Game +0x16E1A3
observed gCEntity::OnDamage caller return    = Game +0x16E348
native threshold constant double             = Game +0x308308
```

The alternate timing sub-arm that writes the latch at `Game +0x16E13E` returns before the later `+0x16E348` damage dispatch and therefore cannot explain the tested damaging Quick route.

Production semantics for a supported/proven raw-8 Fist attack family:

```text
UNMARKED RAW-8 FIST
-> completely native

MARKED RAW-8 FIST EXECUTION
-> once per factual C1 generation, close SPU+0x164 to 1 before first FIST

EACH ACCEPTED FIST
-> SPU+0x164 = 0
-> if real motion-0 play time is below threshold,
   arm one exact one-shot permission for the Game+0x16E180 comparison
-> otherwise use native timing

NATIVE GOTHIC PATH
-> owns target/contact/damage
-> successful opportunity self-closes latch to 1
```

Timing permission is bound to exact actor/SPU/C1 generation/animation-actor/motion/callsite/current-animation identity and dies on factual identity/generation replacement.

Production exclusions:

```text
NO authored FIST_OFF
NO Fist ClearTriggeredList
NO Fist-specific weapon callback suppression
NO equipped Item_Attack/Item_Equipped Fist window
NO weapon C1 physical cleanup obligation
NO direct/custom damage
NO global animation-clock mutation
NO dedicated Fist interruption repair
NO raw55/PhysicalFist generalization
NO species/name-based FIST special cases
NO unproven attack-family extension merely because source token is Fist
```

Evidence progression:

```text
human Normal + Power production acceptance                 EV-240
transformed Sabretooth Normal + Power compatibility        EV-247
native Sabretooth Normal + Power + Quick mechanism proof   EV-248
bounded Quick family extension + two-direction validation  EV-249
```

Supported/proven raw-8 FIST family set for the tested current scope:

```text
Normal + Power + Quick
```

### 4.4 Current supported family boundary

```text
Normal / Quick / Whirl foundation                 CLOSED/PASS
PowerAttack                                       CLOSED/PASS — EV-241
PierceAttack                                      CLOSED/PASS — EV-242
SimpleWhirl                                      CLOSED/PASS — EV-217–EV-220, EV-243
HackAttack tested 2H/Staff scope                  CLOSED/PASS — EV-216, EV-244
raw8 FIST Normal + Power + Quick tested scope     CLOSED/PASS — EV-221–EV-249
SprintAttack                                      MISSING FAMILY / investigation planned
```

SimpleWhirl final StatePosition remains `1`; StatePosition `2` was tested and rejected as sufficient normalization. Native character-hit eligibility remains action-specific.

Hack optional asset routing remains narrow: only factual `HackAttack(14)` may substitute `_FinishingAttack_` with `_HackAttack_` at the CombatMove motion-resource query when the candidate asset exists. True `FinishingAttack(15)` remains native.

### 4.5 SprintAttack — factual missing family, not Power alias

EV-249's Sabretooth fight exposed repeated:

```text
Action = 9
motion name contains _PowerAttack_Hit_
source = Fist/raw8
FIST marker = REJECTED_UNSUPPORTED_HIT
```

Gothic action identity defines:

```text
gEAction_SprintAttack = 9
```

Therefore the current framework is missing SprintAttack support. The motion filename does not authorize treating Sprint as Power.

Current evidence only establishes native Sabretooth Sprint using factual raw8 Fist. It does **not** establish that Sprint is Fist-only, creature-only, or absent from equipped attackers. Earlier test sets did not surface Sprint.

Target design:

```text
first-class AttackFamily_Sprint if/when evidence-backed implementation begins
NO Sabretooth-specific branch
NO filename-based Power alias
NO speculative source semantics
```

Sprint implementation is deliberately postponed until after the architecture/diagnostic refactor and compact equivalence sentinel. The later bounded Sprint investigation must establish source types, native callback/transport, StatePosition, and mechanism before behavior is added.

---

## 5. PhysicalFist/raw55 — Bounded Discovery Deferred

`gEUseType_PhysicalFist` / raw 55 maps to the serialized animation token `Fist`, but EV-245–EV-246 showed why the serialized token cannot identify the native source mechanism.

The bounded discovery found:

```text
Hero Wolf/Sabretooth transformations -> factual Fist / raw 8
native body attackers sampled         -> factual Fist / raw 8 / group 0 / Game+0x16E348 damage caller
native weapon controls                -> factual 2H/1H/Axe UseTypes and equipped/TouchDamage path
Dragon capture                        -> factual Cast/raw15 fireball; physical attack not captured
raw55                                  -> not observed
```

Therefore the current architecture deliberately carries **no raw55 implementation**. Raw55 is unobserved/deferred, not globally proven unused.

Reopen this responsibility only if future runtime evidence establishes a relevant factual `UseType == 55`. At that point classify the actual mechanism before any marker extension.

---

## 6. Collision Lifetime and Cleanup

For equipped weapons, a successful exact-source `Item_Attack` request creates/refreshes an obligation on the current C1 generation. Successful transition away fulfills it. Native cleanup always gets first opportunity. After native AISetState returns, C1-R1 may repair only an exact outstanding current-equipped live source still at group 7:

```text
Item_Attack(7)
-> CollisionSourceOperations::DeactivateOwnedAttackSource
-> Item_Equipped(5)
-> verify Item_Equipped(5)
```

`CollisionLifecycleGuard` decides whether exact terminal repair is justified; `CollisionSourceOperations` performs the physical mutation. No `ClearTriggeredList()` is part of terminal cleanup. Raw-8 Fist and any future reopened PhysicalFist mechanism do not acquire weapon obligations unless separately proven to use equipped sources.

C1-R1 remains closed through EV-206–EV-207; the Stage A ownership refactor is source-reviewed but still awaiting local build/load parity confirmation.

---

## 7. Collision Architecture — Stage A Source Implemented

The 2026-09-10 architecture audit is complete. Stage A implemented the three justified behavior-boundary corrections in commit:

```text
7c5874932cd6eafa5af3414c65a4442b3d74bb73
Refactor collision behavior ownership boundaries
```

Independent Normal Chat static review: PASS. Runtime parity remains pending local build/load.

Governing rule:

```text
EngineBridge
=
sole physical Gothic hook owner
hook/call-site transport
translation of native facts
delegation

EngineBridge
!=
feature behavior owner
feature state-machine owner
collision policy owner
```

Implemented ownership:

```text
Raw8FistCollision
  raw8 Normal+Power+Quick FIST family policy
  marked-execution state
  initial latch close + accepted-marker rearm
  threshold/timing permission and exact one-shot decision

AttackMotionRouting
  proven factual Hack optional motion-substitution policy

CollisionLifecycleGuard
  C1 policy/repair decision and result classification

CollisionSourceOperations
  physical equipped source mutations, including terminal 7 -> 5 repair
```

`RunScriptFunctionScope` remains in `EngineBridge` because its lifetime is hook-invocation transport, not feature policy. Current action/phase family resolution remains in `FrameCollisionMarkers` because it is part of marker ownership; no separate family module is planned.

Full authority: `COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`.

---

## 8. Diagnostic Architecture

Production remains mechanically diagnostics-free.

Default research/testing should use a compact CORE profile; opt-in DEEP retains detailed reverse-engineering probes.

Governing rule:

> **Known successful behavior logs compactly. Unknown, unsupported, contradictory, repair, or invariant behavior logs richly.**

Target:

```text
PRODUCTION
  diagnostics not compiled

CORE
  compact known-path regression facts
  enough information to prove marker/source/damage/lifecycle outcomes
  automatically richer records for unknown actions/families/source UseTypes and anomalies

DEEP
  detailed hook/SPU/timing/AISetState/C1/caller/stack instrumentation for a concrete research question
```

Stage B diagnostic compaction is deliberately postponed until Stage A compiles and smoke-loads locally. Do not simply delete reusable detailed probes; move them to DEEP or condition them on anomaly/unknown-family cases where appropriate.

CORE must remain capable of discovering SprintAttack and other future unexpected traffic without requiring full research-era verbosity for every healthy execution.

Detailed authority: `COLLISION_LOGGER_PLAN.md` and `COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`.

---

## 9. AttackContinuationProtection

The known held-Use2 destructive bad-skip route remains a **separate prevention module** from collision cleanup.

Intended future module:

```text
AttackContinuationProtection.cpp
```

Responsibility:

```text
native bad-skip timeout/consumer does not become due
-> do nothing

native destructive timeout/consumer becomes due
+ no genuine attack CombatMove would be destroyed
-> native behavior unchanged

native destructive timeout/consumer becomes due
+ genuine attack CombatMove would be destroyed
-> suppress/defer only that destructive consequence
```

New Balance compatibility is a hard constraint. New Balance already prevents the bad skip on most melee blocks; where it prevents the native destructive condition, our module should naturally never intervene. Known coverage concern is left-held Staff; hand-to-hand/other forms remain unproven.

Do not begin with an independent timer, polling loop, permanent watchdog, unconditional attack-state override, or resurrection after teardown. Evidence decides the exact native boundary.

`CollisionLifecycleGuard`/C1-R1 remains the independent fail-safe underneath.

---

## 10. Compatibility

Do not rely on arbitrary DLL load order or assumed same-function hook chaining.

Required checkpoints:

```text
mature collision assembly after AttackContinuationProtection
-> New Balance + relevant Jackydima / Script_AttackCollision compatibility

migrated diagnostics-free Script_G3AnimationBehaviors
-> integration compatibility

later Raise + speed + config assembly
-> final assembled compatibility/regression
```

EV-242 is Pierce-specific compatibility evidence only, not blanket certification.

---

## 11. Current Modular DLL Architecture

```text
Script_G3AnimationBehaviors / research twin
|
+-- EngineBridge
|    sole shared-hook owner
|    transport/delegation only
+-- FrameCollisionMarkers
|    exact current-motion ownership
|    action/phase marker-family resolution
|    equipped RIGHT/LEFT/BOTH/OFF
|    marker occurrence bookkeeping
|    FIST dispatch into Raw8FistCollision
+-- CollisionSources
|    factual source identities / UseTypes
+-- CollisionSourceOperations
|    source-specific mutations
|    equipped activation/rearm + terminal deactivation/repair mutation
+-- CollisionLifecycleGuard
|    C1 execution/source obligations
|    terminal repair decision/classification
+-- Raw8FistCollision
|    raw8 FIST Normal+Power+Quick policy/state/latch/timing
+-- AttackMotionRouting
|    factual Hack optional motion-substitution policy
+-- RuntimeClock
+-- AttackContinuationProtection [later, separate cpp]
+-- AttackRaise
+-- AttackSpeed
+-- Config
+-- TargetAcquisition [future]
+-- Climbing [future]
```

Diagnostic research product adds compact CORE diagnostics and opt-in DEEP modules; public release does not compile them.

The Stage A source structure above is implemented and static-reviewed; local build/load confirmation remains pending.

---

## 12. Current Implementation Order

```text
collision architecture foundation                     CLOSED — EV-206–EV-215
Power / Pierce / SimpleWhirl / Hack expansion          CLOSED for tested scope — EV-241–EV-244
human raw-8 FIST production                            CLOSED/PASS — EV-221–EV-240
PhysicalFist/raw55 bounded discovery                   CLOSED/DEFERRED — EV-245–EV-246
transformed Sabretooth Normal/Power raw8 proof         PASS — EV-247
native Sabretooth + Quick mechanism classification     PASS/CLASSIFIED — EV-248
raw8 Quick family extension + validation               CLOSED/PASS — EV-249
SprintAttack missing-family discovery                  IDENTIFIED
collision architecture + diagnostic audit              DONE
Stage A behavior architecture source refactor          IMPLEMENTED / STATIC REVIEW PASS
-> Stage A local build/load
-> Stage B compact CORE / rich anomaly / opt-in DEEP diagnostic refactor
-> Stage B local build/load
-> compact post-refactor equivalence sentinel
-> SprintAttack source/transport/mechanism investigation
-> bounded first-class Sprint implementation only if evidence supports it
-> focused Sprint validation
-> native equipped-NPC marker controls: Goblin 1H / Demon 2H / Ogre Axe
-> additional prepared native/modded family controls
-> separated 2H-vs-Axe mod marker compatibility
-> separated 1H-vs-Rapier mod marker compatibility
-> final native mixed/stress collision regression over supported scope
-> separate AttackContinuationProtection research/implementation
-> combined marker + lifecycle + continuation regression
-> mature New Balance + relevant Jackydima compatibility gate
-> migrate collision into Script_G3AnimationBehaviors
-> diagnostics-free collision integration validation
-> integrate Raise + action/profile Speed + Config
-> final assembled compatibility/regression
```

Post-refactor equivalence sentinel:

```text
Sabretooth raw8 Normal + Quick + Power
one ordinary marked equipped attack
one established multi-marker / OFF / rearm fixture
one established destructive bad-skip -> exact terminal repair
```

Do not create `feature/raise-attack-speed` early.

---

## 13. Non-Goals During Current Redesign Stage

Do not combine the architecture/diagnostic redesign with:

- new collision behavior merely for aesthetics;
- Sprint implementation before its post-refactor factual mechanism investigation;
- new equipped marker vocabulary;
- raw55/PhysicalFist work absent new factual runtime UseType 55 evidence;
- species-specific monster/body marker vocabulary or filename-based actor gating;
- authored FIST_OFF resurrection;
- speculative generalized monster/body framework;
- AttackContinuationProtection implementation;
- Raise/speed/configuration implementation;
- target acquisition or climbing.

---

## 14. Retrieval

| Need | Authority |
|---|---|
| Current exact task | `SESSION_ENTRYPOINT.md` + `BETWEEN_CHATS.md` |
| Current architecture/diagnostic redesign | `COLLISION_ARCHITECTURE_REDESIGN_PLAN.md` |
| Overall architecture/order | this file |
| Collision lifecycle | `COLLISION_LIFECYCLE_PLAN.md` |
| Validation | `COLLISION_TEST_PLAN.md` |
| Diagnostics | `COLLISION_LOGGER_PLAN.md` |
| Source/hooks/RVAs | `SOURCE_HOOK_GUIDE.md` |
| Animation authoring semantics | `ANIMATION_INDEX.md` -> `ANIMATION_RULES.md` |
| Exact evidence | `EVIDENCE_INDEX.md` -> canonical ledgers -> archived provenance |

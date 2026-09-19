# Gothic 3 Animation Behaviors — Design

**Status:** Canonical project architecture  
**Updated:** 2026-09-19
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

`Script_G3AnimationBehaviors` is the general animation-behavior layer for Gothic 3. Active behavior domains are Raise-phase control, attack playback-speed control, and authored-frame collision control. Future independent domains may include target acquisition and climbing.

This file owns overall intended architecture and implementation order. Established collision facts are projected in `COLLISION_REFERENCE.md`; collision lifecycle authority is `COLLISION_LIFECYCLE.md`; validation authority is `COLLISION_TEST_PLAN.md`; diagnostics are owned by `COLLISION_DIAGNOSTICS.md`; permanent raw55 behavior is owned by `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`; practical source/hook lookup is `SOURCE_HOOK_GUIDE.md`; exact proof routes through `EVIDENCE_INDEX.md`.

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
14. Unknown feature behavior is researched in a dedicated temporary probe/research module, not accumulated in `EngineBridge` or another stable owner. When the mechanism is proven, re-express only the proven responsibilities in their proper permanent modules and remove the research scaffolding.

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

After that, equipped weapons, raw-8 Fist, and PhysicalFist/raw55 use three distinct proven production mechanisms. Permanent raw55 behavior is owned by `PhysicalFistCollision` under `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`; it must not be folded into equipped or raw8 behavior merely because the serialized animation token is also `Fist`.

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

Equipped source activation is not itself proof of native damage eligibility for every UseType. EV-308 shows that a factual LEFT shield/raw9 can be selected by `LEFT`, transition `5 -> 7`, rearm, and cleanly return `7 -> 5`, while Gothic dispatches no damage in the tested Quick shield-bash fixture. Shield-bash damage is therefore outside the current supported collision feature set and is deferred to a separate future research responsibility.

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
raw8 Sprint production support                              EV-251
post-raw55 coexistence sentinel                             EV-297
human single-marker/native fallback regression              EV-304
human double-marker same-C1 repeated-contact regression     EV-305
Sabretooth actor-general double-marker regression             EV-307
```

Supported/proven raw-8 FIST family set for the tested current scope:

```text
Normal + Power + Quick + Sprint
```

### 4.4 Current supported family boundary

```text
Normal / Quick / Whirl foundation                 CLOSED/PASS
PowerAttack                                       CLOSED/PASS — EV-241
PierceAttack                                      CLOSED/PASS — EV-242
SimpleWhirl                                      CLOSED/PASS — EV-217–EV-220, EV-243
HackAttack tested 2H/Staff scope                  CLOSED/PASS — EV-216, EV-244
raw8 FIST Normal + Power + Quick + Sprint         CLOSED/PASS — EV-221–EV-251, EV-297, EV-304–EV-305
SprintAttack                                      CLOSED/PASS — EV-251
```

SimpleWhirl final StatePosition remains `1`; StatePosition `2` was tested and rejected as sufficient normalization. Native character-hit eligibility remains action-specific.

Hack optional asset routing remains narrow: only factual `HackAttack(14)` may substitute `_FinishingAttack_` with `_HackAttack_` at the CombatMove motion-resource query when the candidate asset exists. True `FinishingAttack(15)` remains native.

### 4.5 SprintAttack — first-class supported family, Power callback transport

EV-249 established that factual Sprint is `gEAction_SprintAttack = 9` even when the current motion filename contains `_PowerAttack_Hit_`. EV-251 then closed the production transport/mechanism question.

Current rule:

```text
semantic family = Sprint / Action9
callback transport = existing OnAI_PowerAttack hook
raw8 FIST uses the same proven latch/timing-permission mechanism
StatePosition/timing follows the evidence-backed Sprint contract
NO filename-based Power alias
NO Sabretooth-specific branch
```

For equipped markers, the diagnostic causal case is now accepted through EV-315 and EV-320–EV-324. ADR-0003 approves promotion into a permanent `EquippedSprintCollision` behavior owner, but the current behavior-only baseline does not gain that support until the active promotion task is implemented and accepted. The permanent rule must preserve immutable Sprint origin across only the exact same-C1 Action9 -> Action2 continuation; a new true-Power execution never becomes Sprint.

---

## 5. PhysicalFist/raw55 — Permanent Separate Production Mechanism

`gEUseType_PhysicalFist` / raw55 maps to the serialized animation token `Fist`, but the token does not identify the runtime source mechanism. Factual Troll/BlackTroll evidence EV-262 onward established a distinct exact RIGHT `TrollFist` source with resting group5/offensive group7 semantics. Family-specific causal work closed through EV-294; focused permanent acceptance closed/PASS at EV-298.

Permanent owner:

```text
PhysicalFistCollision
=
supported raw55 family policy: Normal / Quick / Power / Sprint
C1-scoped immutable origin/source identity
premature native-opening suppression
family-specific first-FIST activation
Normal native between-contact clear suppression
repeated authored FIST rearm
Sprint-origin Action9 -> Action2 continuity
```

Boundaries:

```text
EngineBridge = shared hook transport/delegation only
FrameCollisionMarkers = generic marker scan/current-motion ownership
CollisionSources / CollisionSourceOperations = generic factual source/mutation helpers
PhysicalFistCollision = permanent raw55 policy/state
Raw8FistCollision = raw8 latch/timing policy only
```

Permanent raw55 does **not** own direct damage, target selection, raw8 behavior, equipped RIGHT/LEFT/BOTH/OFF semantics, or custom terminal cleanup.

Accepted behavior:

```text
marked eligible raw55:
  family-specific authored FIST behavior for Normal / Quick / Power / Sprint
  up to the frozen supported one/two-FIST contract
  native Gothic damage/contact remains authoritative

unmarked raw55:
  completely native fallback — EV-296

cleanup:
  Gothic native exact RIGHT 7 -> 5 first
  C1-R1 remains backup-only for an exact outstanding live/equipped group7 source
  no raw55 OFF / forced deactivation / polling / direct damage
```

Full authority: `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`.

---



## 6. Collision Lifetime and Cleanup

For equipped weapons, a successful exact-source `Item_Attack` request creates/refreshes an obligation on the current C1 generation. Successful transition away fulfills it. Native cleanup always gets first opportunity. After native AISetState returns, C1-R1 may repair only an exact outstanding current-equipped live source still at group 7:

```text
Item_Attack(7)
-> CollisionSourceOperations::DeactivateOwnedAttackSource
-> Item_Equipped(5)
-> verify Item_Equipped(5)
```

`CollisionLifecycleGuard` decides whether exact terminal repair is justified; `CollisionSourceOperations` performs the physical mutation. No `ClearTriggeredList()` is part of terminal cleanup. Raw-8 Fist does not acquire weapon obligations. Permanent raw55 owns its frozen family-specific marker/contact policy, while Gothic retains native exact RIGHT `7 -> 5` cleanup. `CollisionLifecycleGuard`/C1-R1 remains backup-only for an exact outstanding live/equipped raw55 source still at group7; no custom raw55 terminal cleanup is added.

C1-R1 remains closed through EV-206–EV-207.

---

## 7. Collision Architecture — Stage A Source Implemented

The 2026-09-10 architecture audit is complete. Stage A implemented the three justified behavior-boundary corrections in commit:

```text
7c5874932cd6eafa5af3414c65a4442b3d74bb73
Refactor collision behavior ownership boundaries
```

Independent Normal Chat static review: PASS.

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
research/probe policy owner
```

Implemented ownership:

```text
Raw8FistCollision
  raw8 Normal+Power+Quick+Sprint FIST family policy
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

Unknown/new mechanisms follow `FEATURE_DEVELOPMENT_METHOD.md`: dedicated temporary probe first, then the smallest proven permanent owner after research closure.

Current architecture is owned by this file plus `COLLISION_REFERENCE.md`, `COLLISION_LIFECYCLE.md`, and `COLLISION_DIAGNOSTICS.md`; the completed redesign plan is archived provenance.

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

Temporary behavior probes such as `PhysicalFistProbe` are separate from both stable behavior modules and generic diagnostics: they may intervene for a bounded causal experiment, compile only into the research target, and must be removable when the mechanism is promoted or rejected.

CORE must remain capable of discovering SprintAttack and other future unexpected traffic without requiring full research-era verbosity for every healthy execution.

Detailed authority: `COLLISION_DIAGNOSTICS.md` and `FEATURE_DEVELOPMENT_METHOD.md`. The completed redesign/refactor plan is archived historical provenance.

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
|    equipped RIGHT/LEFT/BOTH/OFF generic semantics
|    marker occurrence bookkeeping
|    production FIST dispatch into proven feature owner(s)
+-- EquippedSprintCollision [promotion task active]
|    factual Sprint eligibility + bound Sprint-origin identity
|    exact Action9 -> same-C1 Action2 continuation policy
|    authorization into generic equipped marker semantics
+-- CollisionSources
|    factual source identities / UseTypes
+-- CollisionSourceOperations
|    source-specific mutations
|    equipped activation/rearm + terminal deactivation/repair mutation
+-- CollisionLifecycleGuard
|    C1 execution/source obligations
|    terminal repair decision/classification
+-- Raw8FistCollision
|    raw8 FIST Normal+Power+Quick+Sprint policy/state/latch/timing
+-- PhysicalFistCollision
|    permanent raw55 Normal/Quick/Power/Sprint policy/state/rearm
|    Sprint-origin continuity + narrow Normal native-clear suppression
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

Diagnostic research products may add dedicated removable probes for future unknown mechanisms; probes are not permanent children of `EngineBridge`. The completed raw55 `PhysicalFistProbe` research path has been replaced by permanent `PhysicalFistCollision` behavior.

---

## 12. Durable Implementation Order

```text
closed collision architecture + evidence-backed feature scope
-> standalone collision regression campaign
-> New Balance 0.7 exact distributed-bundle regression incl. AttackCollision
-> mature collision migration into Script_G3AnimationBehaviors
-> diagnostics-free production integration validation
-> later Raise + action/profile Speed + Config
-> AttackContinuationProtection remains a separate responsibility
```

Live campaign status and the exact next setup belong in `SESSION_ENTRYPOINT.md` and `COLLISION_TEST_PLAN.md`, not in this architecture authority.

Do not create `feature/raise-attack-speed` early.

---

## 13. Non-Goals During Current Standalone Regression

Do not combine the current regression campaign with:

- reopening closed raw55 causal research without contradictory evidence;
- raw8 or raw55 redesign from routine regression confirmation;
- moving feature policy/state into `EngineBridge`;
- species-specific monster/body marker vocabulary or filename-based actor gating;
- authored FIST_OFF resurrection;
- unrelated marker-vocabulary changes;
- AttackContinuationProtection implementation;
- Raise/speed/configuration implementation;
- target acquisition or climbing.

---

## 14. Retrieval

| Need | Authority |
|---|---|
| Current exact task | `SESSION_ENTRYPOINT.md` + `BETWEEN_CHATS.md` |
| Feature research -> production method | `FEATURE_DEVELOPMENT_METHOD.md` |
| Current established collision facts | `COLLISION_REFERENCE.md` |
| Overall architecture/order | this file |
| Collision lifecycle | `COLLISION_LIFECYCLE.md` |
| Validation | `COLLISION_TEST_PLAN.md` |
| Diagnostics | `COLLISION_DIAGNOSTICS.md` |
| Source/hooks/RVAs | `SOURCE_HOOK_GUIDE.md` |
| Animation authoring semantics | `ANIMATION_INDEX.md` -> `ANIMATION_RULES.md` |
| Exact evidence | `EVIDENCE_INDEX.md` -> canonical ledgers -> archived provenance |

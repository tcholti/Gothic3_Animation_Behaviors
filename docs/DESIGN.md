# Gothic 3 Animation Behaviors — Design

**Status:** Canonical project architecture  
**Updated:** 2026-09-08  
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

`Script_G3AnimationBehaviors` is the general animation-behavior layer for Gothic 3. Active behavior domains are Raise-phase control, attack playback-speed control, and authored-frame collision control. Future independent domains may include target acquisition and climbing.

This file owns overall intended architecture and implementation order. Collision lifecycle authority is `COLLISION_LIFECYCLE_PLAN.md`; validation authority is `COLLISION_TEST_PLAN.md`; diagnostics are owned by `COLLISION_LOGGER_PLAN.md`; practical source/hook lookup is `SOURCE_HOOK_GUIDE.md`; exact proof routes through `EVIDENCE_INDEX.md`.

---

## 1. Governing Principles

1. Prefer Gothic native action/phase/UseType/current-motion semantics over filename heuristics when available.
2. Preserve Gothic's own animation resolution whenever possible.
3. Custom behavior is explicit opt-in: config for Raise/speed, exact reserved markers for collision.
4. Separate attack family/phase from the physical damage source.
5. Keep responsibilities separate: transport in `EngineBridge`, behavior in feature modules, factual source identity in `CollisionSources`, source mutations in `CollisionSourceOperations`, diagnostics in diagnostic-only code.
6. Preserve proven paths while expanding one meaningful responsibility at a time.
7. Unconfigured/unmarked cases fall back to native behavior.
8. Load configuration once into normalized in-memory rules.
9. Require evidence before generalizing player/human/family behavior.
10. One DLL owns each physical Gothic hook; feature modules consume shared bridge facts rather than installing competing hooks.
11. Public release behavior contains no research diagnostics.

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

After that, equipped weapons and human Fist use different native mechanisms.

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

### 4.3 Production human raw-8 Fist

Human `gEUseType_Fist` / raw 8 is body-contact damage, not a literal right-hand weapon source. Controlled evidence established damage through left/right hands, left/right legs and head.

Tested generic-human native path:

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

The special arm associated with `[SPU+0x154] == 0x39` is outside the proven generic-human model.

Production semantics:

```text
UNMARKED HUMAN FIST
-> completely native

MARKED HUMAN FIST EXECUTION
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
NO creature/monster authored-FIST generalization
```

Final Normal + Power production acceptance: EV-240.

### 4.4 Current equipped-family boundary

```text
PowerAttack   CLOSED/PASS — EV-241
PierceAttack  CLOSED/PASS — EV-242
SimpleWhirl   CLOSED/PASS — EV-217–EV-220, EV-243
HackAttack    CLOSED/PASS for tested 2H/Staff scope — EV-216, EV-244
Human raw8    CLOSED/PASS — EV-221–EV-240
```

SimpleWhirl final StatePosition remains `1`; StatePosition `2` was tested and rejected as sufficient normalization. Native character-hit eligibility remains action-specific.

Hack optional asset routing remains narrow: only factual `HackAttack(14)` may substitute `_FinishingAttack_` with `_HackAttack_` at the CombatMove motion-resource query when the candidate asset exists. True `FinishingAttack(15)` remains native.

---

## 5. PhysicalFist/raw55 — Bounded Discovery Deferred

`gEUseType_PhysicalFist` / raw 55 maps to the serialized animation token `Fist`, but EV-245–EV-246 showed why the serialized token cannot identify the native source mechanism.

The bounded discovery found:

```text
Hero Wolf/Sabertooth transformations -> factual Fist / raw 8
native body attackers sampled         -> factual Fist / raw 8 / group 0 / Game+0x16E348 damage caller
native weapon controls                -> factual 2H/1H/Axe UseTypes and equipped/TouchDamage path
Dragon capture                        -> factual Cast/raw15 fireball; physical attack not captured
raw55                                  -> not observed
```

Therefore the current architecture deliberately carries **no raw55 implementation**. Raw55 is unobserved/deferred, not globally proven unused.

Reopen this responsibility only if future runtime evidence establishes a relevant factual `UseType == 55`. At that point classify the actual mechanism before any marker extension.

The native creature raw-8 survey does not establish the complete human timing/latch mechanism for those families and does not authorize `G3AB_COL_FIST` for monsters. Production authored `FIST` remains exact-human raw-8 only.

---

## 6. Collision Lifetime and Cleanup

For equipped weapons, a successful exact-source `Item_Attack` request creates/refreshes an obligation on the current C1 generation. Successful transition away fulfills it. Native cleanup always gets first opportunity. After native AISetState returns, C1-R1 may repair only an exact outstanding current-equipped live source still at group 7:

```text
Item_Attack(7)
-> SetCollisionGroup(Item_Equipped)
-> verify Item_Equipped(5)
```

No `ClearTriggeredList()` is part of terminal cleanup. Human Fist and any future reopened PhysicalFist mechanism do not acquire weapon obligations unless separately proven to use equipped sources.

C1-R1 remains closed through EV-206–EV-207.

---

## 7. AttackContinuationProtection

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

Do not begin with an independent timer, polling loop, permanent watchdog, unconditional attack-state override, or resurrection after teardown. Pausing the underlying timer is only one candidate; blocking/defering the destructive consumer may be safer. Evidence decides the exact native boundary.

`CollisionLifecycleGuard`/C1-R1 remains the independent fail-safe underneath.

---

## 8. Compatibility

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

## 9. Target Modular DLL Architecture

```text
Script_G3AnimationBehaviors / research twin
|
+-- EngineBridge
|    sole shared-hook owner
+-- FrameCollisionMarkers
|    exact current-motion ownership
|    equipped RIGHT/LEFT/BOTH/OFF
|    human FIST opportunities
|    C1-generation marker bookkeeping
+-- CollisionSources
|    factual source identities / UseTypes
+-- CollisionSourceOperations
|    source-specific mutations
+-- CollisionLifecycleGuard
|    C1 execution/source obligations
|    terminal exact 7 -> 5 fail-safe
+-- RuntimeClock
+-- AttackContinuationProtection [later, separate cpp]
+-- AttackRaise
+-- AttackSpeed
+-- Config
+-- TargetAcquisition [future]
+-- Climbing [future]
```

Diagnostic research product adds diagnostic modules; public release does not compile them.

---

## 10. Current Implementation Order

```text
collision architecture foundation                     CLOSED — EV-206–EV-215
Power / Pierce / SimpleWhirl / Hack expansion          CLOSED for tested scope — EV-241–EV-244
human raw-8 FIST production                            CLOSED/PASS — EV-221–EV-240
PhysicalFist/raw55 bounded discovery                   CLOSED/DEFERRED — EV-245–EV-246
-> final native mixed collision regression over supported scope
-> separate AttackContinuationProtection research/implementation
-> combined marker + lifecycle + continuation regression
-> mature New Balance + relevant Jackydima compatibility gate
-> collision knowledge/evidence closure
-> migrate collision into Script_G3AnimationBehaviors
-> diagnostics-free collision integration validation
-> promote collision checkpoint to main
-> create feature/raise-attack-speed from updated main
-> mature Raise + action/profile speed + configuration
-> final assembled compatibility/regression
-> promote mature Raise/speed checkpoint
-> first public framework release with 2H animation content
```

Do not create `feature/raise-attack-speed` early.

---

## 11. Non-Goals During Collision Closure

Do not combine the remaining collision work with:

- new equipped marker vocabulary or source/lifecycle redesign;
- `GetUpAttack` or true `FinishingAttack` redesign;
- another human raw-8 Fist causal probe absent contradiction;
- raw55/PhysicalFist work absent new factual runtime UseType 55 evidence;
- creature/monster `G3AB_COL_FIST` generalization;
- authored FIST_OFF resurrection;
- speculative generalized monster/body framework;
- Raise/speed/configuration implementation;
- target acquisition or climbing.

---

## 12. Retrieval

| Need | Authority |
|---|---|
| Current exact task | `SESSION_ENTRYPOINT.md` + `BETWEEN_CHATS.md` |
| Overall architecture/order | this file |
| Collision lifecycle | `COLLISION_LIFECYCLE_PLAN.md` |
| Validation | `COLLISION_TEST_PLAN.md` |
| Diagnostics | `COLLISION_LOGGER_PLAN.md` |
| Source/hooks/RVAs | `SOURCE_HOOK_GUIDE.md` |
| Animation authoring semantics | `ANIMATION_INDEX.md` -> `ANIMATION_RULES.md` |
| Exact evidence | `EVIDENCE_INDEX.md` -> canonical ledgers -> archived provenance |

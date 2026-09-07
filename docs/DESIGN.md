# Gothic 3 Animation Behaviors — Design

**Status:** Canonical project architecture  
**Updated:** 2026-09-07  
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

`Script_G3AnimationBehaviors` is intended to provide a general animation-behavior layer for Gothic 3 that can support rebuilt animations without forcing them to inherit every legacy timing assumption.

The active behavior domains are:

1. Raise-phase control;
2. attack playback-speed control;
3. authored-frame collision control.

Future independent behavior domains may include target acquisition, climbing and other animation/gameplay systems.

This file defines the intended architecture and current implementation order. It does not preserve experiment chronology. Proof history routes through `EVIDENCE_INDEX.md` -> the evidence ledgers/raw/archive evidence; collision lifecycle authority is `COLLISION_LIFECYCLE_PLAN.md`; staged validation authority is `COLLISION_TEST_PLAN.md`; release/build separation is owned by `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

Superseded design wording remains recoverable through Git history rather than a parallel active design archive.

---

## 1. Scope

The system is actor-general by design.

`Hero` is an animation-family identifier used by compatible human actors; it is not a player-only selector. Collision, Raise and speed systems should remain technically extensible to other actor/animation families when their native semantics and physical damage sources are understood.

Current practical development emphasis remains human melee because that is the animation set being rebuilt and tested first.

Unconfigured profiles and unmarked animations must retain native behavior.

---

## 2. Governing Design Principles

### DP-01 — Native semantics first

Prefer Gothic 3's native action, phase, animation state, pose, UseType, resolved motion and source/API facts over filename heuristics when those native facts are available.

Filenames remain important asset selectors and serialized state, but they must not become the sole behavioral parser.

### DP-02 — Preserve engine animation resolution

Do not manually construct exact P0/P1/P2/P10/etc. filenames when Gothic 3 can resolve the correct animation from native actor/state/action/phase/pose/use-type context.

When Gothic already consumes filename fields as part of its serialized animation contract, leave those semantics with Gothic. A future feature may intervene in one narrow animation-selection dimension only when evidence requires it, while preserving the rest of Gothic's normal resolver contract.

### DP-03 — Explicit opt-in ownership

- Raise/speed ownership comes from matching configuration.
- Frame collision ownership comes from reserved markers in the exact current Hit motion plus the relevant native callback/action/phase/source context.
- Missing configuration/marker means custom behavior does not take ownership.

### DP-04 — Separate attack semantics from physical damage source

Action/callback/phase identify the attack mechanism. The physical source that can produce damaging contact is a separate concern.

Possible sources include equipped right weapon, equipped left weapon, both equipped weapons, logical human Fist/body-contact source, and future monster/body sources.

Never infer the physical source solely from a generic `Hit`, final filename `R/L`, or QuickAttackR/L token.

Proving a physical source is offensive also does not prove that every Gothic action family applies identical target/contact/effect eligibility to every actor crossed by that source.

### DP-05 — Separate responsibilities

```text
EngineBridge
    physical Gothic hook ownership / transport / factual context

Behavior modules
    Raise / speed / marker / lifecycle / continuation decisions

CollisionSources
    factual source identity and metadata

CollisionSourceOperations
    source-specific engine mutations after behavior has decided them

Runtime infrastructure
    neutral behavior-required services such as monotonic timing

Diagnostics
    observation only; diagnostic builds only
```

Production behavior must remain correct when diagnostics are not compiled.

### DP-06 — Preserve proven paths while expanding

Change one meaningful subsystem/family responsibility at a time when that improves causal confidence. Do not rewrite a proven path merely because another family is being added.

### DP-07 — Controlled fallback

If a custom rule does not intentionally apply, preserve the original/native path.

### DP-08 — Configuration loaded once

Parse configuration during initialization into normalized in-memory rules. Do not repeatedly parse the INI during attacks.

### DP-09 — Evidence before generalization

Player-only success is not sufficient evidence for an actor-general feature. Use controlled NPC cases when actor scope matters, and use runtime/source evidence for subtle engine behavior.

### DP-10 — One hook owner, independent feature modules

One DLL may contain many independent behavior modules, but one central engine-bridge layer owns each shared Gothic hook. Feature modules consume authoritative bridge events/facts; they do not independently compete for the same physical Gothic function.

### DP-11 — Diagnostics-free release product

Every released Gothic 3 behavior DLL contains behavior only.

```text
shared behavior architecture
-> diagnostics-free RELEASE build
-> separate instrumented DIAGNOSTIC twin used in place of release during controlled testing
```

---

## 3. Configuration Identity

The intended profile identity is:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile
```

Raw `gEUseType` values must be normalized to the animation categories used by Gothic 3 resources. Canonical mapping and filename semantics are in `ANIMATION_RULES.md`; use `ANIMATION_INDEX.md` for targeted routing.

Configuration should allow behavior modules to be independently enabled/configured while still sharing one DLL and one engine bridge.

---

## 4. Raise Architecture

A normal 2H Attack Raise has been proven by prepending an asynchronous Raise with `PREPEND_BREAK_BLOCK` before the untouched original melee state.

```text
configured custom Raise
-> original state
-> original Hit
-> native continuation
```

Production rules:

- enable Raise only for matching configured profiles/actions;
- reuse the highest-level proven native/state mechanism where sufficient;
- do not reconstruct actions that already have correct native Raise behavior;
- keep Raise separate from collision lifecycle repair and attack-continuation protection;
- install/consume shared hooks through the common engine bridge.

Exact Raise proof routes through `EVIDENCE_INDEX.md`.

---

## 5. Playback-Speed Architecture

`AniSpeedScale` participates in real animation duration and action/phase-aware speed control has been proven feasible.

Production goal:

> Apply speed authority only to matching configured profiles/phases while preserving unrelated native/mod behavior.

Requirements:

- avoid global replacement of unrelated attack speeds;
- avoid unsafe dependence on DLL load order when another mod hooks the same upstream speed path;
- prefer the narrowest point that provides final authority for the configured execution;
- calibrate final family values from measured native/custom durations;
- keep speed control independent from Raise, collision markers, lifecycle repair and attack-continuation protection.

The current `src/Script_G3AnimationBehaviors/AttackSpeed.cpp` direct hook of `Script_Game +0x42A0 GetAnimationSpeedModifier` is a proof-of-concept implementation, not frozen production architecture. Re-evaluate the intervention point against New Balance/Jackydima behavior before final speed implementation.

### Recover policy

There is intentionally no planned user-facing `RecoverSpeed` key. Controlled Recover should follow the effective Hit speed for that attack profile.

---

## 6. Authored-Frame Collision Architecture

### 6.1 Generic ownership declaration

At attack-Hit execution/start, inspect the exact resolved Hit motion and its frame-effect list.

If no reserved G3AB collision marker is present, custom frame collision does not take ownership.

If relevant reserved markers are present and the native/action/phase/source preflight succeeds, that exact execution opts into authored timing. What competing native mechanism must be suppressed is source-specific: equipped weapons and human Fist share generic marker infrastructure but do not share the same native damage mechanism.

Marker-specific ownership policy belongs to `FrameCollisionMarkers`, not transport-only `EngineBridge`.

### 6.2 Equipped-weapon marker vocabulary

```text
G3AB_COL_RIGHT
G3AB_COL_LEFT
G3AB_COL_BOTH
G3AB_COL_OFF
```

Exact-set semantics:

```text
RIGHT -> {RIGHT}
LEFT  -> {LEFT}
BOTH  -> {RIGHT, LEFT}
OFF   -> {}
```

RIGHT/LEFT mean Gothic 3 equipped slots, not animation-direction metadata.

The exact-set contract is a physical-source contract:

```text
marker
-> desired equipped source set
-> Item_Attack / Item_Equipped transitions as required
-> ClearTriggeredList rearm on each authored contact
```

Authoring rules:

- at most one G3AB collision command on one authored frame;
- use BOTH instead of same-frame RIGHT + LEFT;
- keep OFF and a later activation on different frames;
- a repeated source marker later in the same Hit is a new authored contact and rearms that source with `ClearTriggeredList()`;
- marker timing is animation-specific;
- do not create action-specific RIGHT/LEFT/BOTH/OFF marker names;
- physical source activation is separate from action-specific native target/contact/effect eligibility.

### 6.3 Shared marker infrastructure; separate native mechanisms

Shared generic pieces are limited to genuinely mechanism-neutral infrastructure:

- exact animation/frame-effect scanning;
- reserved marker recognition;
- marker occurrence/dedupe bookkeeping;
- C1 generation as factual execution identity;
- exact animation/action/phase context;
- marked-execution opt-in.

After that ownership layer the paths separate:

```text
Generic authored-marker infrastructure
        |
        +--> Equipped weapons
        |       RIGHT / LEFT / BOTH / OFF
        |       equipped source identity
        |       Item_Attack / Item_Equipped
        |       ClearTriggeredList repeated-contact semantics
        |       marker-owned source masks/windows
        |       C1 weapon lifecycle / C1-R1 cleanup
        |
        +--> Human Fist/body damage
                FIST only
                exact human gEUseType_Fist / raw 8
                sAICombatMoveItlLoop native permission/timing path
                SPU+0x164 native latch
                native gCEntity::OnDamage

                no equipped source masks
                no Item_Attack ownership
                no weapon marker-owned source window
                no weapon C1 cleanup obligation
                no Fist ClearTriggeredList
                no Fist-specific weapon callback suppression
```

Weapon markers and Fist markers must not be mixed in native-mechanism code merely because both use frame-effect markers.

#### Equipped-weapon mechanism

```text
FrameCollisionMarkers
    -> desired equipped source set / authored contact
CollisionSources
    -> factual RIGHT/LEFT source identity
CollisionSourceOperations
    -> Item_Attack / Item_Equipped
    -> repeated-contact ClearTriggeredList rearm
marker-owned weapon windows + C1 lifecycle
```

The closed equipped-weapon RIGHT/LEFT/BOTH/OFF architecture remains unchanged.

#### Production human Fist/body-damage mechanism

Exact logical human `gEUseType_Fist` / raw 8 damage has body-contact semantics, not literal right-hand weapon collision. Controlled tests established damaging contact through at least left/right hands, left/right legs and head.

The tested generic human native path is:

```text
gCScriptProcessingUnit::sAICombatMoveItlLoop
    +0x16DFB9 checks SPU+0x164
        nonzero -> exits before damage

    +0x16E160 GetMaxTime(motion 0)
    * native double at Game +0x308308
    +0x16E180 GetPlayTime(motion 0)
    +0x16E186..+0x16E190 compare
        below threshold -> common exit +0x16E352
        threshold reached -> native damage preparation

    +0x16E1A3 native write SPU+0x164 = 1
    ...
    +0x16E348 observed gCEntity::OnDamage caller return
```

The special native arm associated with `[SPU+0x154] == 0x39` is outside the proven generic-human model and must not be generalized from these facts.

Production authored semantics are:

```text
UNMARKED HUMAN FIST
    completely native

MARKED HUMAN FIST EXECUTION
    exact current Hit contains one or more FIST markers
    + exact human raw-8 identity established
        -> once per factual C1 generation, close SPU+0x164 to 1
           before the first authored FIST

EACH ACCEPTED FIST
    -> SPU+0x164 = 0
    -> inspect real motion-0 timing

    if real play time < native threshold
        -> arm one exact bounded permission for the proven
           Game +0x16E180 GetPlayTime comparison
        -> call native GetPlayTime
        -> return threshold + epsilon to that matching comparison only
        -> consume permission
        -> do not alter the actual animation clock

    if real play time >= native threshold
        -> no synthetic timing permission

NATIVE GOTHIC PATH
    -> owns downstream target/contact/damage
    -> successful opportunity writes SPU+0x164 = 1
    -> next authored FIST may rearm a later intended opportunity
```

Timing permission is bound to the factual actor, SPU, C1 generation, animation actor, motion/callsite and current animation identity. It dies rather than leaking across a factual generation/identity change.

`G3AB_COL_FIST_OFF` is not part of the production author-facing vocabulary. The historical FIST_OFF experiments established useful latch facts, but final authored semantics need only `FIST`: marked execution start closes the native permission, each FIST opens/rearms one native opportunity, and Gothic self-closes successful opportunities.

Human Fist production therefore also has:

- no `TouchDamage.ClearTriggeredList()` operation;
- no Fist-specific weapon-style `OnAI_Attack` suppression;
- no custom/direct damage dispatch;
- no actual animation-clock mutation;
- no dedicated interruption-repair state machine;
- no current theoretical bad-skip fix;
- no generalization to `gEUseType_PhysicalFist` / raw 55 or monsters.

Final Normal + Power production acceptance is EV-240.

### 6.4 Repeated contacts

For equipped weapons, repeated authored contacts rearm the selected logical source through `ClearTriggeredList()`.

For human Fist, repeated authored opportunities are separate accepted `FIST` occurrences; the native latch self-closes a successful opportunity and the next FIST rearms it. Do not import weapon triggered-list semantics into Fist.

### 6.5 Marker decision caching

Only cache a marker/no-marker decision after the exact current motion is resolved and the frame-effect scan is valid enough to establish a factual result.

Do not permanently cache a transient unresolved-motion failure as a negative marker decision.

### 6.6 Current equipped-melee expansion boundary

Current validated expansion state:

```text
PowerAttack   CLOSED/PASS
PierceAttack  CLOSED/PASS
SimpleWhirl   CLOSED/PASS for the current marker/semantic stage
HackAttack    CLOSED/PASS for isolated routing/source/marker scope
Human Fist    CLOSED/PASS for current Normal + Power raw-8 production scope
```

`GetUpAttack` is not part of the planned marker roadmap. `FinishingAttack` remains native and deliberately excluded from ordinary marker treatment.

The next responsibility is not another family-specific source redesign; it is final mixed regression of the mature collision behavior, followed by the separate third-party compatibility gate.

Hack optional asset routing remains:

```text
active resolver produces ordinary resource name
-> factual action == HackAttack (14)
-> at the narrow CombatMove motion-resource query
-> if ordinary name contains _FinishingAttack_:
       derive candidate replacing only that action token with _HackAttack_
       candidate exists -> use it
       candidate absent -> untouched ordinary FinishingAttack resource
-> true FinishingAttack (15) and non-Hack actions remain native
```

Matching asset existence is the opt-in. Do not globally patch `GetAniName` or reimplement ordinary filename metadata.

---

## 7. Collision Lifetime and Cleanup

Marker timing inside a live Hit and terminal collision safety are separate responsibilities.

```text
WHILE THE HIT IS ALIVE:
markers define the desired offensive equipped-source set.
```

```text
WHEN AN EQUIPPED-WEAPON EXECUTION ENDS OR IS DESTRUCTIVELY ABANDONED:
Gothic gets its legitimate cleanup opportunity first.
If the exact source obligation is fulfilled -> no-op.
If it remains outstanding -> repair only that exact live/equipped source.
```

Accepted equipped-weapon lifecycle architecture:

```text
real attack execution
-> monotonic C1 generation
-> successful exact-source Item_Attack request creates/refreshes obligation
-> successful later transition away from Item_Attack fulfills obligation
-> post-native-AISetState finalization checks only remaining obligations
```

For proven equipped sources, terminal repair is exactly:

```text
outstanding exact source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual group == Item_Attack(7)
-> SetCollisionGroup(Item_Equipped)
-> verify exact Item_Equipped(5)
```

No `ClearTriggeredList()` is part of terminal cleanup.

Human Fist does not create this equipped-source obligation and does not use C1-R1 physical repair.

C1-R1 controlled validation is closed through EV-206–EV-207. Preserve the liveness fail-closed branch and do not invent family-specific cleanup matrices, timers, polling or broad source scans.

### Known bad-skip relationship

The known held-Use2 destructive route remains a separate future prevention responsibility:

```text
AttackContinuationProtection
= prevent the destructive route from killing a valid active attack

CollisionLifecycleGuard
= make an exact stale equipped offensive source safe if cleanup is nevertheless lost
```

Do not merge these responsibilities.

---

## 8. Marker Bookkeeping Is Not Physical Cleanup

Marker occurrence/duplicate/window bookkeeping is separate from physically returning a stale equipped offensive source to a safe group.

Accepted durable marker execution identity:

```text
C1 monotonic generation
```

Gate 4 removed the older marker-local guesses that a new execution began from source/motion/action/phase/state-time changes or callback rollback inference.

Natural `RetireMarkerOwnedSource()` handling retires only the exact physical marker-owned equipped source bit/window; it is not whole-execution retirement authority.

Preserve independent marker invariants:

- required `Routine.StatePosition` behavior for supported equipped families;
- repeated-marker/repeated-contact semantics;
- occurrence budgets and replay/duplicate protection;
- exact-set RIGHT/LEFT/BOTH/OFF switching;
- OFF as an intra-Hit equipped-source gap;
- interruption/dead-execution rejection;
- supported-family/current-motion/source preflight;
- valid-motion-only marker caching;
- native fallback for unmarked/unsupported cases.

EV-213–EV-215 close the generation-scoped architecture verification. Do not restore superseded execution-boundary heuristics merely because later work touches marker code.

---

## 9. Compatibility

Do not rely on arbitrary DLL load order or assumed same-function hook chaining.

When another mod owns the same engine function/path, choose deliberately among a single shared/downstream intervention, integration into one authoritative owner, a proven chain-safe mechanism, or a documented replacement/integration path.

Unmarked/unconfigured attacks must remain compatible with native behavior.

Compatibility with New Balance and the relevant Jackydima DLL stack is a required project constraint.

Required checkpoints:

```text
mature collision research behavior
-> final native mixed regression
-> New Balance + relevant Jackydima collision compatibility regression

migrated diagnostics-free Script_G3AnimationBehaviors collision integration
-> integration smoke/compatibility
-> promote collision checkpoint to main

later Raise + speed + config assembly
-> final assembled compatibility/regression before later promotion/release
```

---

## 10. Target Modular DLL Architecture

```text
Script_FrameCollisionTest / later Script_G3AnimationBehaviors
|
+-- EngineBridge
|    sole shared-hook owner / calling-convention-safe transport
|
+-- FrameCollisionMarkers
|    exact current-motion ownership
|    attack-family policy
|    equipped RIGHT/LEFT/BOTH/OFF
|    human FIST authored opportunities
|    C1-generation occurrence/replay bookkeeping
|
+-- CollisionSources
|    factual source identities / UseTypes
|
+-- CollisionSourceOperations
|    source-specific physical operations
|
+-- CollisionLifecycleGuard
|    C1 generation / durable execution identity
|    pre-Combat correlator
|    equipped exact-source offense obligations
|    terminal exact 7 -> 5 fail-safe
|
+-- RuntimeClock
|    monotonic timing service
|
+-- AttackContinuationProtection [later]
+-- AttackRaise [later production module]
+-- AttackSpeed [later production module]
+-- Config [later production]
+-- TargetAcquisition [future]
+-- Climbing [future]
```

Research product adds `CollisionDiagnostics` and opt-in `CollisionDiagnosticsDeep`. Public release removes all diagnostic source/state/hooks/strings.

---

## 11. Current Implementation Order

Closed foundation:

```text
second-pass rewrite / product separation      EV-208–EV-212
Gate-4 generation-scoped marker bookkeeping  EV-213–EV-215
Power / Pierce / SimpleWhirl / Hack expansion CLOSED for current scope
human raw-8 FIST production                   CLOSED/PASS — EV-232–EV-240
```

Current accepted sequence:

```text
final native mixed collision regression
-> final New Balance + Script_AttackCollision / relevant Jackydima compatibility regression
-> collision knowledge/evidence closure
-> migrate mature collision behavior into Script_G3AnimationBehaviors
-> diagnostics-free collision integration validation
-> promote collision checkpoint to main
-> create feature/raise-attack-speed from updated main
-> mature Raise + action/profile speed + configuration redesign
-> final assembled compatibility/regression
-> promote mature Raise/speed checkpoint to main
-> first public framework release with 2H animation content
```

Do not create `feature/raise-attack-speed` early.

### Release 1 boundary

Framework:

```text
general marker/collision framework
+ validated AttackContinuationProtection / bad-skip prevention when that later responsibility is reached
+ mature Raise framework
+ general/action/profile attack-speed + configuration framework
+ required compatibility/regression
```

Release 1 animation content is intentionally 2H only. Framework completeness does not require every weapon family to have finished replacement animations.

---

## 12. Non-Goals for the Current Collision-Closure Responsibility

Do not combine final regression/closure with:

- new marker vocabulary;
- GetUpAttack or FinishingAttack redesign;
- new human-Fist causal probes absent contradictory evidence;
- authored FIST_OFF resurrection;
- monster/raw55/general body adapters;
- theoretical Fist bad-skip repair;
- parsing/reimplementing Gothic's ordinary filename metadata;
- equipped source/lifecycle redesign;
- C1-R1 or Gate-4 redesign;
- Raise/speed/configuration work;
- creating `feature/raise-attack-speed` before collision promotion;
- target acquisition or climbing.

AttackContinuationProtection remains a separate later collision responsibility and should not be silently folded into a regression-only step.

---

## 13. Retrieval Routes

| Need | Authority |
|---|---|
| Current exact task / branch state | `SESSION_ENTRYPOINT.md` + `BETWEEN_CHATS.md` |
| Current roadmap / overall architecture | this `DESIGN.md` §§10–11 |
| Production human Fist architecture/evidence | this `DESIGN.md` §6.3 -> `EVIDENCE_INDEX.md` -> EV-232–EV-240 |
| Collision lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| Current collision validation posture | `COLLISION_TEST_PLAN.md` |
| Diagnostic architecture | `COLLISION_LOGGER_PLAN.md` |
| Hook/source/API/New Balance lookup | `SOURCE_HOOK_GUIDE.md` |
| Marker execution lifetime | `EVIDENCE_INDEX.md` -> EV-131–EV-133 / EV-167 / EV-213–EV-214 |
| C1-R1 evidence | `EVIDENCE_LEDGER_199_ONWARD.md` EV-206–EV-207 |
| Gate-4/final architecture verification | `EVIDENCE_LEDGER_199_ONWARD.md` EV-213–EV-215 |
| SimpleWhirl/Hack expansion evidence | `EVIDENCE_INDEX.md` -> EV-216–EV-220 plus later archived September evidence |
| Exact evidence claim/provenance | `EVIDENCE_INDEX.md` -> canonical evidence ledgers -> `research/archive/` |
| Animation semantics / UseType / pose | `ANIMATION_INDEX.md` -> `ANIMATION_RULES.md` |
| Exact asset/family/fixture | `ANIMATION_INDEX.md` -> `ANIMATION_CATALOG.md` |
| Historical design/prototype chronology | exact EV/provenance -> Git history / archived raw evidence |

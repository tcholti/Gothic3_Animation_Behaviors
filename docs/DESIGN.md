# Gothic 3 Animation Behaviors — Design

**Status:** Canonical project architecture  
**Updated:** 2026-08-30  
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

`Script_G3AnimationBehaviors` is intended to provide a general animation-behavior layer for Gothic 3 that can support rebuilt animations without forcing them to inherit every legacy timing assumption.

The active behavior domains are:

1. Raise-phase control;
2. attack playback-speed control;
3. authored-frame collision control.

This file defines the **intended architecture and current implementation order**. It does not preserve experiment chronology. For proof history and exact tested claims use `EVIDENCE_INDEX.md` → the evidence ledgers/raw logs. For the current collision-lifecycle model use `COLLISION_LIFECYCLE_PLAN.md`; for staged collision validation use `COLLISION_TEST_PLAN.md`.

The pre-information-architecture design, including detailed prototype chronology, is preserved at:

`docs/archive/technical_2026-08-27/DESIGN_pre_ia.md`

---

## 1. Scope

The system is actor-general by design.

`Hero` is an animation-family identifier used by compatible human actors; it is **not** a player-only selector. Collision, Raise, and speed systems should remain technically extensible to other actor/animation families when their native semantics and physical damage sources are understood.

Current practical development emphasis remains human melee because that is the animation set being rebuilt and tested first.

Unconfigured profiles and unmarked animations must retain native behavior.

---

## 2. Governing Design Principles

### DP-01 — Native semantics first

Prefer Gothic 3's native action, phase, animation state, pose, UseType, resolved motion, and source/API facts over filename heuristics when those native facts are available.

Filenames remain important asset selectors and serialized state, but they must not become the sole behavioral parser.

### DP-02 — Preserve engine animation resolution

Do not manually construct exact P0/P1/P2/P10/etc. filenames when Gothic 3 can resolve the correct animation from native actor/state/action/phase/pose/use-type context.

### DP-03 — Explicit opt-in ownership

- Raise/speed ownership comes from matching configuration.
- Frame collision ownership comes from reserved markers in the **exact current Hit motion** plus the relevant native callback/action/phase context.
- Missing configuration/marker means custom behavior does not take ownership.

### DP-04 — Separate attack semantics from physical damage source

Action/callback/phase identify the attack mechanism. The physical source that damages a target is a separate concern.

Possible sources include:

- equipped right weapon;
- equipped left weapon;
- both equipped weapons;
- logical Fist/body-contact source;
- future monster/body/limb/head sources.

Never infer the physical source from a generic `Hit`, final filename `R/L`, or QuickAttackR/L token alone.

### DP-05 — Separate responsibilities

Conceptually:

```text
Engine bridge / hook transport
    owns physical Gothic hook installation and reports authoritative events/facts

Behavior modules
    own Raise / speed / marker / lifecycle / continuation decisions

Physical source adapters
    translate a behavior decision into the correct source-specific engine operation

Diagnostics
    observe and record facts
```

Diagnostics must remain removable/reducible without changing production behavior.

### DP-06 — Preserve proven paths while expanding

Change one meaningful subsystem/family responsibility at a time when that improves causal confidence. Do not rewrite a proven path merely because another family is being added.

### DP-07 — Controlled fallback

If a custom rule does not intentionally apply, preserve the original/native path.

### DP-08 — Configuration loaded once

Parse configuration during initialization into normalized in-memory rules. Do not repeatedly parse the INI during attacks.

### DP-09 — Evidence before generalization

Player-only success is not sufficient evidence for an actor-general feature. Use controlled NPC cases when actor scope matters, and use runtime/source evidence for subtle engine behavior.

### DP-10 — One hook owner, independent feature modules

One DLL may contain many independent behavior modules, but one central engine-bridge layer owns each shared Gothic hook.

Feature modules consume authoritative bridge events/facts; they do **not** independently compete for the same physical Gothic function merely because each feature needs information from that function.

This rule is especially important for shared lifecycle/control paths such as `RunScriptFunction`, CombatMove, `AISetState`, `AIFullStop`, `SetCollisionGroup`, animation callbacks and future speed/compatibility interception points.

A module may be enabled/disabled or replaced without redefining another module's semantic responsibility.

---

## 3. Configuration Identity

The intended profile identity is:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile
```

Raw `gEUseType` values must be normalized to the animation categories used by Gothic 3 resources. The canonical mapping and filename semantics are in `ANIMATION_RULES.md`; use `ANIMATION_INDEX.md` for targeted routing.

The exact user-facing INI syntax can evolve while the implementation is still being consolidated, but the profile identity should remain semantic rather than filename-specific.

Configuration should eventually allow behavior modules to be independently enabled/configured while still sharing one DLL and one engine bridge.

---

## 4. Raise Architecture

A normal 2H Attack Raise has already been proven by prepending an asynchronous Raise with `PREPEND_BREAK_BLOCK` before the untouched original melee state.

Conceptually:

```text
configured custom Raise
→ original state
→ original Hit
→ native continuation
```

The engine resolves the correct pose-specific Raise asset.

Production rules:

- enable Raise only for matching configured profiles/actions;
- reuse the highest-level proven native/state mechanism where sufficient;
- do not reconstruct actions that already have correct native Raise behavior;
- keep Raise separate from collision lifecycle repair and attack-continuation protection;
- initially generalize Normal and Quick families, then selected full-Whirl paths where evidence/assets justify it;
- install/consume hooks through the common engine-bridge architecture when a hook path is shared with another behavior.

Exact Raise proof evidence routes through `EVIDENCE_INDEX.md`.

---

## 5. Playback-Speed Architecture

`AniSpeedScale` participates in real animation duration and action/phase-aware speed control has been proven feasible.

Production goal:

> Apply speed authority only to matching configured profiles/phases while preserving unrelated native/mod behavior.

Requirements:

- avoid global replacement of unrelated attack speeds;
- avoid unsafe dependence on DLL load order when another mod hooks the same upstream speed path;
- prefer the narrowest point that provides final authority for the configured execution;
- calibrate final family values from measured native/custom durations rather than freezing provisional authoring guesses;
- keep speed control independent from Raise, collision markers, lifecycle repair and attack-continuation protection.

The current `src/Script_G3AnimationBehaviors/AttackSpeed.cpp` direct hook of `Script_Game +0x42A0 GetAnimationSpeedModifier` is a **proof-of-concept implementation, not frozen production architecture**. The project source guide already records this path as a compatibility concern when another DLL owns the same function. Before final speed implementation, re-evaluate the intervention point against New Balance/Jackydima behavior rather than assuming same-function hook chaining/load order is safe.

### Recover policy

There is intentionally no planned user-facing `RecoverSpeed` key.

**Design decision:** controlled Recover should follow the effective Hit speed for that attack profile.

This is desired project behavior, not a claim that vanilla Gothic 3 always does so automatically.

---

## 6. Authored-Frame Collision Architecture

### 6.1 Ownership declaration

At attack-Hit execution/start, inspect the exact resolved Hit motion and its frame-effect list.

If no reserved G3AB collision marker is present, custom frame collision does not take ownership.

If a reserved marker is present and the relevant native callback/action/phase/source preflight succeeds, that exact execution opts into authored collision timing and its competing native timed activation must be suppressed.

### 6.2 Frozen equipped-slot marker vocabulary

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

Authoring rules:

- at most one G3AB collision command on one authored frame;
- use BOTH instead of same-frame RIGHT + LEFT;
- keep OFF and a later activation on different frames;
- a repeated source marker later in the same Hit is a new authored contact and rearms that source with `ClearTriggeredList()`;
- marker timing is animation-specific, not a universal fixed offset;
- do not create action-specific marker names such as Power/Quick/Whirl RIGHT variants; action-family support belongs in the adapter/ownership layer, not the marker vocabulary.

Body/Fist/monster marker vocabulary remains separate and must not be invented before its source model is understood.

### 6.3 Physical source model

Equipped weapon sources use the corresponding equipped entity and weapon-style offensive collision operation.

Fist/body contact is **not** assumed to use the same physical collision-group mechanism. Controlled Fist evidence shows logical rearm/contact can work while the logical Fist entity remains outside weapon-style `Item_Attack` group handling.

Treat weapon activation and body/Fist rearm as separate source adapters behind one higher collision-control responsibility.

Conceptually:

```text
FrameCollisionMarkers
    ↓ desired source set / authored contact
CollisionSources
    ├─ EquippedWeaponSourceAdapter
    │    weapon Item_Attack / Item_Equipped semantics
    │    repeated-contact ClearTriggeredList rearm
    └─ FistSourceAdapter [only if separately proven]
         no forced weapon collision-group mutation
         Fist-specific rearm/contact semantics
```

### 6.4 Repeated contacts

A weapon/entity visit list can suppress repeated damage to the same target. Repeated authored contacts therefore rearm the selected logical source through `ClearTriggeredList()`.

`BOTH` rearms both selected sources at that authored moment; it is not a substitute for later repeated source markers.

---

## 7. Collision Lifetime and Cleanup

Marker timing inside a live Hit and terminal collision safety are separate responsibilities.

Governing rules:

```text
WHILE THE HIT IS ALIVE:
markers define the desired offensive collision set.
```

```text
WHEN THE EXECUTION ENDS OR IS DESTRUCTIVELY ABANDONED:
Gothic 3 gets its legitimate cleanup opportunity first.
If the exact source obligation is already fulfilled -> no-op.
If it remains outstanding -> repair only that exact live/equipped offensive source using native cleanup semantics.
```

The accepted lifecycle architecture is an **execution-level exact-source cleanup guard**:

```text
real attack execution
→ monotonic C1 generation
→ successful exact-source Item_Attack request creates/refreshes obligation
→ successful later transition away from Item_Attack fulfills obligation
→ destructive post-native-AISetState finalization checks only remaining obligations
```

Execution identity is intentionally split:

```text
live ScriptFunction frame
= temporary native correlator only where pre-Combat acquisition needs it

C1 monotonic generation
= durable plugin execution identity
```

C1-O2-P2 proved the early-offense bridge can be consumed by matching CombatMove before `RunScriptFunction` returns/suspends. Cross-suspension raw-frame persistence is not part of the durable ownership model.

For currently proven equipped weapon sources, the native-equivalent terminal repair is exactly:

```text
outstanding exact source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual group == Item_Attack(7)
→ SetCollisionGroup(Item_Equipped)
→ verify exact Item_Equipped(5)
```

No `ClearTriggeredList()` is part of terminal cleanup. Trigger-list clearing remains activation/rearm behavior.

C1-R1 controlled validation is **closed** through EV-207. Direct evidence covers targeted positive repair, reaction precedence, pre-activation no-offense, GetUp bridge/cleanup, GetUpParade, Dual source specificity, marked-source terminal repair, broad mixed player/NPC stability, Fist/body separation and crossbow negative behavior. Bow and magic also received supplemental negative regression coverage.

The outstanding `LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED` branch remains fail-closed and is not claimed positively runtime-exercised. Natural NPC combat/Staff marker traffic supports actor-general stability, but no positive NPC destructive-abandonment physical-repair case is claimed.

Current lifecycle authority and constraints:

- `COLLISION_LIFECYCLE_PLAN.md`
- `COLLISION_TEST_PLAN.md`
- `COLLISION_CLEANUP_CALLSITE_MAP.md`
- `EVIDENCE_INDEX.md` → EV-151–EV-207

Do not implement family-specific cleanup matrices, timers, polling, held-Use2 classifiers, arbitrary group-7 adoption, or broad scans merely because native cleanup has several internal paths.

### Known bad-skip root relationship

The known held-Use2 destructive route is a separate future prevention responsibility. C1-R1 deliberately fails closed after ownership has already been destroyed; it does not attempt to resurrect that attack.

The future module is provisionally named:

```text
AttackContinuationProtection
```

It should ask whether the destructive FullStop/state-replacement consequence can be suppressed/deferred while a real attack CombatMove is active without changing legitimate reactions or non-attack held-Use2 behavior.

It must **not** be implemented inside `CollisionLifecycleGuard`. Both modules may consume facts from the shared engine bridge, but their responsibilities remain independent:

```text
AttackContinuationProtection
= prevent the known destructive route from killing a valid active attack

CollisionLifecycleGuard
= make an exact stale offensive source safe if cleanup is nevertheless lost
```

Authority: `BAD_SKIP_FUTURE_INVESTIGATION.md`.

Even if such prevention later succeeds, keep C1-R1 as the general lost-cleanup fail-safe.

---

## 8. Marker Bookkeeping Is Not Physical Cleanup

The marker occurrence/duplicate/window state used to survive Gothic frame-effect replay is a different responsibility from physically returning a stale offensive source to a safe state.

A natural/native source reset may retire marker bookkeeping when it proves the old execution ended. Intentional intra-Hit OFF/source switching must not retire the entire execution.

Existing marker bookkeeping fixes are proven behavior and must remain until a stronger authority replaces them. In particular, current code must continue to preserve:

- `Routine.StatePosition` advancement after custom ownership where required to suppress Gothic's competing timed activation;
- repeated-marker / repeated-contact rearm semantics;
- occurrence/replay protection;
- exact-set RIGHT/LEFT/BOTH/OFF switching;
- interruption/dead-execution rejection so one execution's marker state does not survive into another.

The C1-R1 marked Staff regression proves terminal physical repair can pass through the existing SetCollisionGroup observation path, retire the existing marker-owned source bookkeeping, reject late callbacks from the abandoned execution, and allow the next legitimate marked attack to begin fresh.

The proven C1 generation now creates a legitimate **simplification question**: some old marker state may have existed only to infer execution lifetime before a stronger native-backed execution identity was available.

The simplification audit must classify each check into one of two groups:

```text
A. execution-lifetime inference now genuinely superseded by C1/native execution authority
B. independent marker invariant still required for authored behavior/replay/rearm/native suppression
```

Only group A may be removed. Group B must remain even if the code can technically be shortened.

Before any marker-core consolidation or reimplementation, use this retrieval route:

```text
EVIDENCE_INDEX.md
→ Marker execution lifetime / bookkeeping
→ future marker-core simplification / native execution boundary
→ COLLISION_LIFECYCLE_PLAN.md §9
```

Do not equate `m_pfInstrCallback == sAICombatMoveInstr` alone with exact marked-Hit identity, and do not remove proven marker protections unless the replacement preserves their historical regressions/invariants.

---

## 9. Compatibility

Do not rely on arbitrary DLL load order or assumed same-function hook chaining.

When another mod owns the same engine function/path, choose deliberately among:

- a single shared/downstream intervention;
- integration into one authoritative owner;
- a proven chain-safe mechanism;
- a documented replacement/integration path.

Unmarked/unconfigured attacks must remain compatible with native behavior and should not be made dependent on the research logger.

Compatibility with New Balance and the relevant Jackydima DLL stack is a **required project constraint**.

Two explicit compatibility gates are required:

```text
Gate 1 — mature research collision DLL
marker/source system + lifecycle guard + AttackContinuationProtection
→ test against New Balance / relevant Jackydima DLLs before production migration

Gate 2 — final Script_G3AnimationBehaviors
migrated collision modules + Raise + redesigned speed control
→ retest against New Balance / relevant Jackydima DLLs before stable promotion
```

Passing Gate 1 does not prove the final speed/Raise assembly compatible. Passing Gate 2 is required before release/stable integration.

---

## 10. Target Modular DLL Architecture

The research DLL should first be refactored toward the architecture eventually required by `Script_G3AnimationBehaviors`, without changing behavior.

Conceptual target:

```text
Script_FrameCollisionTest / later Script_G3AnimationBehaviors
│
├─ EngineBridge / EngineHooks
│    sole owner of shared Gothic hooks
│    performs calling-convention-safe transport
│    publishes authoritative engine events/facts
│
├─ CollisionLifecycleGuard
│    C1 generation / execution identity
│    exact per-source offense obligations
│    native-cleanup observation
│    terminal exact 7 -> 5 fail-safe
│
├─ FrameCollisionMarkers
│    exact current-motion marker ownership
│    RIGHT / LEFT / BOTH / OFF semantics
│    authored occurrence/replay/rearm behavior
│    competing native activation suppression
│
├─ CollisionSources
│    EquippedWeaponSourceAdapter
│    later FistSourceAdapter only if proven
│
├─ AttackContinuationProtection [later]
│    held-Use2 destructive-consequence prevention
│    no collision-repair ownership
│
├─ AttackRaise [later production module]
│
├─ AttackSpeed [later production module]
│
├─ Config
│
└─ Diagnostics
     observer only
     research verbosity separable from production behavior
```

Module boundaries do not require one file per box, but responsibilities should be explicit enough that a future change to one feature does not silently redefine another feature's behavior.

The first modular refactor is **structural only**. It must not combine source movement with marker expansion, marker simplification, bad-skip prevention, Raise changes, speed changes, or production migration.

---

## 11. Current Implementation Order

This order is the currently agreed roadmap. It is deliberately course-correctable: source/API/runtime evidence may change a later step, but a later destination does not authorize skipping earlier validation boundaries.

1. **Read-only architecture/code review.** Review all current `prototypes/Script_FrameCollisionTest` source plus the existing `src/Script_G3AnimationBehaviors` structure. Classify production semantics, research diagnostics, hook transport, lifecycle ownership, marker ownership, physical-source handling, potentially redundant marker-lifetime inference, and third-party hook conflicts. No source edit in this phase.
2. **Freeze and perform a semantic-preserving modular refactor of `Script_FrameCollisionTest`.** Central engine bridge remains the sole hook owner; feature modules consume bridge events/facts; diagnostics stay observer-only. Do not add behavior.
3. **Revalidate the collision baseline after structural refactor.** Use compact positive/no-op/marker/source sentinels from `COLLISION_TEST_PLAN.md`; do not rerun the entire R1 research program by default.
4. **Audit marker bookkeeping against C1 execution authority.** Remove only checks proven to duplicate execution-lifetime inference; preserve independent marker ownership, occurrence/replay, StatePosition, exact-set switching, repeated-contact rearm and dead-execution protections.
5. **Expand markers across intended equipped-melee attack mechanisms one at a time.** Keep the existing RIGHT/LEFT/BOTH/OFF vocabulary. For each new family/mechanism, preserve previous marker behavior, native no-marker fallback and lifecycle-guard safety.
6. **Investigate Fist as a separate source adapter.** Only after equipped-melee coverage is stable, prove whether authored Fist timing/rearm is safe. Do not force Fist through weapon-style `Item_Attack` semantics.
7. **Run a complete marker + lifecycle-guard regression.** Establish that the matured marker/source system still preserves the closed C1-R1 contract.
8. **Investigate/implement modular `AttackContinuationProtection`.** Only now pursue the held-Use2 prevention hypothesis as a module separate from `CollisionLifecycleGuard`; preserve timer/native behavior where possible and keep C1-R1 underneath.
9. **Validate guard + markers + continuation protection together.** Include bad-skip prevention, ordinary completion, native reactions, non-attack held-Use2 control and collision cleanup.
10. **Mandatory New Balance/Jackydima compatibility gate on the mature research DLL.** Resolve shared-hook/callback conflicts deliberately; do not rely on load order.
11. **Redesign `src/Script_G3AnimationBehaviors` around the same modular engine-bridge/event architecture and migrate the proven collision modules.** Production migration happens only after the mature research collision system passes compatibility.
12. **Keep Raise and speed as independent production modules.** Generalize Raise only after collision migration is stable. Re-evaluate AttackSpeed's current direct `GetAnimationSpeedModifier` hook against New Balance before final speed implementation; do not carry the v0.1 hook forward merely because it once proved speed control feasible.
13. **Final full production compatibility/regression.** Test the assembled `Script_G3AnimationBehaviors`—collision, continuation protection, Raise, speed and configuration—with New Balance/relevant Jackydima DLLs before stable promotion.

---

## 12. Non-Goals for the Current Iteration

Not immediate implementation targets:

- production migration before the research collision subsystem is mature and compatibility-tested;
- global creature reanimation;
- intended-target/crosshair correction;
- climbing;
- rewriting Gothic 3 input arbitration;
- manually constructing all combat animation filenames;
- inventing universal body/monster collision markers before source semantics are known;
- forcing Fist/body into equipped-weapon collision-group semantics;
- replacing every third-party collision behavior before equivalent ownership/source behavior exists;
- simplifying marker code solely to reduce line count;
- merging bad-skip prevention into the lifecycle guard;
- keeping the current AttackSpeed hook solely because it is already implemented.

---

## 13. Retrieval Routes

| Need | Authority |
|---|---|
| Current task / current branch state | `SESSION_ENTRYPOINT.md` |
| Current roadmap / overall module architecture | this `DESIGN.md` §§10–11 |
| Collision lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| Current collision validation | `COLLISION_TEST_PLAN.md` |
| Exact transient architecture-review handoff | `BETWEEN_CHATS.md` |
| Marker execution lifetime / future marker-core simplification | `EVIDENCE_INDEX.md` Marker execution lifetime → `COLLISION_LIFECYCLE_PLAN.md` §9 |
| Future held-Use2 prevention | `BAD_SKIP_FUTURE_INVESTIGATION.md` |
| Tested native cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| Exact evidence claim / provenance | `EVIDENCE_INDEX.md` → ledgers/raw logs |
| C1-R1 canonical evidence | `EVIDENCE_LEDGER_STEP_D.md` EV-206–EV-207 |
| Animation semantics / UseType / action / pose | `ANIMATION_INDEX.md` → `ANIMATION_RULES.md` |
| Exact asset/family/fixture | `ANIMATION_INDEX.md` → `ANIMATION_CATALOG.md` / animation-name data |
| Hook/source/API/New Balance lookup | `SOURCE_HOOK_GUIDE.md` |
| Historical design/prototype chronology | `RESEARCH_MAP.md` / archived pre-IA documents / raw logs |

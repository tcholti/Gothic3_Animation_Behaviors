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

Future independent behavior domains may include target acquisition, climbing and other animation/gameplay systems.

This file defines the **intended architecture and current implementation order**. It does not preserve experiment chronology. For the exact current bounded rewrite use `SECOND_PASS_REWRITE_CONTRACT.md`; for proof history use `EVIDENCE_INDEX.md` → the evidence ledgers/raw logs; for lifecycle use `COLLISION_LIFECYCLE_PLAN.md`; for staged validation use `COLLISION_TEST_PLAN.md`.

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

Source facts
    identify current physical sources and source metadata

Physical source operations
    translate an already-decided behavior request into source-specific engine operations

Runtime infrastructure
    provides behavior-required neutral services such as monotonic timing

Diagnostics
    observe and record facts in diagnostic builds only
```

Production behavior must remain correct when diagnostics are **not compiled**.

Canonical release/build rule: `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

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

### DP-11 — Diagnostics-free release product

Every released Gothic 3 behavior DLL contains behavior only.

```text
shared behavior architecture
→ diagnostics-free RELEASE build
→ separate instrumented DIAGNOSTIC twin used in place of release during controlled testing
```

The public release must not compile diagnostic source/state/hooks merely because research builds historically used them.

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

Marker-specific callback ownership policy belongs to `FrameCollisionMarkers`, not to the transport-only EngineBridge.

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
- do not create action-specific marker names such as Power/Quick/Whirl RIGHT variants; action-family support belongs in the ownership layer, not the marker vocabulary.

Body/Fist/monster marker vocabulary remains separate and must not be invented before its source model is understood.

### 6.3 Physical source model

Source identity/facts and source mutation are separate layers.

Conceptually:

```text
FrameCollisionMarkers
    ↓ desired source set / authored contact
CollisionSources
    ↓ factual RIGHT/LEFT entity + UseType/source availability
CollisionSourceOperations
    ├─ equipped weapon operations
    │    Item_Attack / Item_Equipped
    │    repeated-contact ClearTriggeredList rearm
    └─ current research Fist operation
         no forced weapon Item_Attack mutation
         preserve existing ClearTriggeredList behavior
```

`CollisionSources` does **not** own marker policy or mutation.

`CollisionSourceOperations` does **not** decide attack family, marker ownership or desired source set.

Fist/body contact is not assumed to use the same physical collision-group mechanism. Controlled Fist evidence shows logical rearm/contact can work while the logical Fist entity remains outside weapon-style `Item_Attack` group handling.

A generalized `FistSourceAdapter` remains a later separately proven responsibility.

### 6.4 Repeated contacts

A weapon/entity visit list can suppress repeated damage to the same target. Repeated authored contacts therefore rearm the selected logical source through `ClearTriggeredList()`.

`BOTH` rearms both selected sources at that authored moment; it is not a substitute for later repeated source markers.

### 6.5 Marker decision caching

Only cache a marker/no-marker decision after the exact current motion is resolved and the frame-effect scan is valid enough to establish a factual result.

Do not permanently cache a transient unresolved-motion failure as a negative marker decision.

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

C1-R1 controlled validation is **closed** through EV-207.

The outstanding `LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED` branch remains fail-closed and is not claimed positively runtime-exercised. Natural NPC combat/Staff marker traffic supports actor-general stability, but no positive NPC destructive-abandonment physical-repair case is claimed.

Current lifecycle authority and constraints:

- `COLLISION_LIFECYCLE_PLAN.md`
- `COLLISION_TEST_PLAN.md`
- `COLLISION_CLEANUP_CALLSITE_MAP.md`
- `EVIDENCE_INDEX.md` → EV-151–EV-207

Do not implement family-specific cleanup matrices, timers, polling, held-Use2 classifiers, arbitrary group-7 adoption, or broad scans merely because native cleanup has several internal paths.

### Known bad-skip root relationship

The known held-Use2 destructive route is a separate future prevention responsibility.

```text
AttackContinuationProtection
= prevent the known destructive route from killing a valid active attack

CollisionLifecycleGuard
= make an exact stale offensive source safe if cleanup is nevertheless lost
```

`AttackContinuationProtection` must not be implemented inside `CollisionLifecycleGuard`. Even if prevention later succeeds, keep C1-R1 as the general lost-cleanup fail-safe.

Authority: `BAD_SKIP_FUTURE_INVESTIGATION.md`.

---

## 8. Marker Bookkeeping Is Not Physical Cleanup

The marker occurrence/duplicate/window state used to survive Gothic frame-effect replay is a different responsibility from physically returning a stale offensive source to a safe state.

A natural/native source reset may retire marker bookkeeping when it proves the old execution ended. Intentional OFF or exact-set source switching must not retire the entire execution.

Existing marker bookkeeping fixes are proven behavior and must remain until a stronger authority replaces them. Preserve:

- `Routine.StatePosition` advancement after custom ownership where required to suppress Gothic's competing timed activation;
- repeated-marker / repeated-contact rearm semantics;
- occurrence/replay protection;
- exact-set RIGHT/LEFT/BOTH/OFF switching;
- interruption/dead-execution rejection so one execution's marker state does not survive into another.

EV-131–EV-133 prove a real interrupted-execution occurrence-budget defect and its natural marker-owned source-retirement correction. EV-167 explicitly separates this marker-bookkeeping retirement from physical cleanup.

The C1 generation creates a legitimate **later simplification question**, but not authority to delete marker execution protections during the frozen structural rewrite.

The later simplification audit must classify each check into:

```text
A. execution-lifetime inference genuinely superseded by C1/native authority
B. independent marker invariant still required
```

Only group A may be removed.

Before any marker-core consolidation/reimplementation:

```text
EVIDENCE_INDEX.md
→ Marker execution lifetime / bookkeeping
→ EV-131–EV-133 / EV-167
→ COLLISION_LIFECYCLE_PLAN.md §9
```

---

## 9. Compatibility

Do not rely on arbitrary DLL load order or assumed same-function hook chaining.

When another mod owns the same engine function/path, choose deliberately among:

- a single shared/downstream intervention;
- integration into one authoritative owner;
- a proven chain-safe mechanism;
- a documented replacement/integration path.

Unmarked/unconfigured attacks must remain compatible with native behavior.

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

The mature research behavior core is the architectural ancestor of the eventual production `Script_G3AnimationBehaviors` DLL.

Conceptual behavior core:

```text
Script_FrameCollisionTest / later Script_G3AnimationBehaviors
│
├─ EngineBridge
│    sole owner of behavior-required shared Gothic hooks
│    calling-convention-safe transport
│    publishes factual native context/events
│    no marker/lifecycle/source policy
│
├─ FrameCollisionMarkers
│    exact current-motion marker ownership
│    current attack-family eligibility / callback ownership
│    RIGHT / LEFT / BOTH / OFF semantics
│    authored occurrence/replay/duplicate bookkeeping
│    competing native activation suppression
│    marker-owned source/window bookkeeping
│
├─ CollisionSources
│    factual current RIGHT/LEFT source identity / UseType / availability
│
├─ CollisionSourceOperations
│    source-specific physical operations already requested by marker behavior
│
├─ CollisionLifecycleGuard
│    C1 generation / durable execution identity
│    P2 temporary pre-Combat correlator
│    exact per-source offense obligations
│    native-cleanup observation
│    terminal exact 7 -> 5 fail-safe
│    no diagnostic dependency
│
├─ RuntimeClock
│    behavior-required monotonic elapsed-time service
│    current same-update duplicate-marker timing support
│
├─ AttackContinuationProtection [later]
│
├─ AttackRaise [later production module]
├─ AttackSpeed [later production module]
├─ Config [later production]
├─ TargetAcquisition [future]
└─ Climbing [future]
```

Research/validation product adds diagnostics around the same behavior core:

```text
CollisionDiagnostics
= compact default proof evidence

CollisionDiagnosticsDeep
= opt-in deep probes / diagnostic-only hooks
```

Public release product:

```text
same mature behavior architecture
+ production config/features
- all diagnostic source/state/hooks/strings
```

The release and instrumented diagnostic twin are mutually exclusive runtime products unless a future architecture explicitly proves coexistence safe.

Canonical release rule: `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

Exact current rewrite contract: `SECOND_PASS_REWRITE_CONTRACT.md`.

---

## 11. Current Implementation Order

This is the current agreed roadmap. A later destination does not authorize skipping an earlier validation boundary.

1. **Unchanged post-EngineBridge runtime baseline — NEXT.** Current source and current logger only. Prove the already-completed EngineBridge extraction using the compact sentinel matrix in `COLLISION_TEST_PLAN.md` / `BETWEEN_CHATS.md`.
2. **If baseline passes, implement the frozen semantic-preserving second-pass rewrite.** Exact authority: `SECOND_PASS_REWRITE_CONTRACT.md`. This includes RuntimeClock rename, FrameCollisionMarkers boundary, CollisionSourceOperations, cache correction, dead lifecycle dispatch removal, diagnostics-independent lifecycle, compact/deep diagnostic separation and a diagnostics-free behavior-only prototype build.
3. **Build/source audit both prototype products.** Diagnostic target + behavior-only target; release-purity architecture must be mechanically enforceable.
4. **Compact diagnostic sufficiency regression.** Default diagnostic output must still prove core marker/source/C1 invariants without deep probes.
5. **Behavior-only smoke/equivalence.** Prove behavior does not depend on diagnostics.
6. **Dedicated marker-bookkeeping audit against C1 authority.** Remove only checks proven to duplicate execution-lifetime inference; preserve independent marker invariants.
7. **Expand markers across intended equipped-melee attack mechanisms one at a time.** Keep RIGHT/LEFT/BOTH/OFF vocabulary and native no-marker fallback.
8. **Investigate Fist as a separate source adapter.** Do not force Fist through weapon-style `Item_Attack` semantics.
9. **Run complete marker + lifecycle regression.** Protect closed C1-R1 behavior after marker/source maturity.
10. **Investigate/implement modular `AttackContinuationProtection`.** Separate from `CollisionLifecycleGuard`; keep C1-R1 underneath.
11. **Validate guard + markers + continuation protection together.** Include bad-skip prevention, ordinary completion, reactions and non-attack held-Use2 control.
12. **Mandatory New Balance/Jackydima compatibility gate on mature research behavior.** Resolve hook/callback conflicts deliberately.
13. **Retain the mature modular foundation and migrate/redesign Raise + speed + config into final `Script_G3AnimationBehaviors`.** Do not pour collision back into the old v0.1 hook/file structure.
14. **Later add independent systems such as target acquisition/climbing under the same central-bridge/module/release-purity architecture.**
15. **Final diagnostics-free production compatibility/regression.** Test assembled public `Script_G3AnimationBehaviors` with New Balance/relevant Jackydima DLLs before stable promotion; retain separate instrumented diagnostic twin for future reproduction.

---

## 12. Non-Goals for the Current Iteration

Not part of the frozen second-pass structural rewrite:

- C1-driven marker bookkeeping simplification;
- new attack-family marker support;
- new marker vocabulary;
- generalized Fist support;
- universal monster/body adapters;
- AttackContinuationProtection;
- Raise/speed changes;
- configuration redesign;
- production migration;
- target acquisition;
- climbing;
- New Balance/Jackydima compatibility fixes;
- rewriting input arbitration;
- simplifying proven marker code solely to reduce line count;
- keeping historical diagnostic hooks in behavior builds merely because they already exist.

---

## 13. Retrieval Routes

| Need | Authority |
|---|---|
| Current exact task / branch state | `SESSION_ENTRYPOINT.md` + `BETWEEN_CHATS.md` |
| Frozen post-baseline rewrite | `SECOND_PASS_REWRITE_CONTRACT.md` |
| Current roadmap / overall architecture | this `DESIGN.md` §§10–11 |
| Release vs diagnostic products | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` |
| Collision lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| Current collision validation | `COLLISION_TEST_PLAN.md` |
| Diagnostic core/deep architecture | `COLLISION_LOGGER_PLAN.md` |
| Marker execution lifetime / later simplification | `EVIDENCE_INDEX.md` Marker execution lifetime → EV-131–EV-133 / EV-167 → `COLLISION_LIFECYCLE_PLAN.md` §9 |
| Future held-Use2 prevention | `BAD_SKIP_FUTURE_INVESTIGATION.md` |
| Tested native cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| Exact evidence claim / provenance | `EVIDENCE_INDEX.md` → ledgers/raw logs |
| C1-R1 canonical evidence | `EVIDENCE_LEDGER_STEP_D.md` EV-206–EV-207 |
| Animation semantics / UseType / action / pose | `ANIMATION_INDEX.md` → `ANIMATION_RULES.md` |
| Exact asset/family/fixture | `ANIMATION_INDEX.md` → `ANIMATION_CATALOG.md` / animation-name data |
| Hook/source/API/New Balance lookup | `SOURCE_HOOK_GUIDE.md` |
| Historical design/prototype chronology | `RESEARCH_MAP.md` / archived pre-IA documents / raw logs |

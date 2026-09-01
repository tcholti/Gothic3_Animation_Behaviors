# Gothic 3 Animation Behaviors — Design

**Status:** Canonical project architecture  
**Updated:** 2026-09-02  
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

`Script_G3AnimationBehaviors` is intended to provide a general animation-behavior layer for Gothic 3 that can support rebuilt animations without forcing them to inherit every legacy timing assumption.

The active behavior domains are:

1. Raise-phase control;
2. attack playback-speed control;
3. authored-frame collision control.

Future independent behavior domains may include target acquisition, climbing and other animation/gameplay systems.

This file defines the **intended architecture and current implementation order**. It does not preserve experiment chronology. The completed second-pass structural rewrite and generation-scoped marker-bookkeeping work are preserved by EV-208–EV-215 plus current source/build state; proof history routes through `EVIDENCE_INDEX.md` → the evidence ledgers/raw logs; lifecycle authority is `COLLISION_LIFECYCLE_PLAN.md`; staged validation authority is `COLLISION_TEST_PLAN.md`; release/build separation is owned by `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

Superseded design/contract wording remains recoverable through Git history rather than a parallel active archive tree.

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

When Gothic already consumes filename fields as part of its serialized animation contract — including destination pose, CombatMove distance/length and other engine-consumed metadata — leave those semantics with Gothic. Behavior code must not parse or reimplement those fields merely because the project authors animations that use them.

A future feature may intervene in one narrow animation-selection dimension only when evidence requires it. Such an intervention should preserve Gothic's normal resolver and the rest of the filename contract rather than replacing animation resolution wholesale.

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

This principle does not require one code implementation per already-understood callback family. When several families share a proven architecture, one bounded implementation may add the shared adapters together while causal confidence is preserved by independent family-by-family validation.

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

### 6.6 Remaining equipped-melee expansion boundary

The shared marker/source/generation core has been reviewed as suitable for broader ordinary equipped-weapon expansion. The remaining required marker families are:

```text
PowerAttack
PierceAttack
SimpleWhirl
HackAttack
```

`GetUpAttack` is optional/nice-to-have and should be included only if source review shows that it fits the established C1/marker architecture without new guessed execution identity or disproportionate lifecycle machinery.

`FinishingAttack` is deliberately excluded. The true downed-enemy Finishing path is an execution mechanic whose observed kill timing is not dependent on ordinary weapon contact; preserve its native behavior and do not require collision markers for it.

Fist/body contact remains a separate source-adapter responsibility after equipped-weapon coverage.

The remaining compatible equipped-melee adapters may be implemented in **one bounded code change** after their family/callback bookkeeping and Hack routing are frozen. Validation remains family-specific: Power, Pierce, SimpleWhirl, Hack and optional GetUp are tested independently before combined regression.

#### HackAttack animation routing

Runtime `gEAction_HackAttack` and `gEAction_FinishingAttack` are distinct behavior/cleanup semantics even though tested 2H Hack currently reuses the serialized `FinishingAttack` asset family.

The preferred architecture is:

```text
runtime HackAttack remains native action 14
→ narrow native-compatible animation-selection/routing change
→ Gothic resolves dedicated HackAttack assets
→ Gothic continues interpreting the normal filename contract itself
→ Hack Hit markers use the ordinary equipped-slot marker system

runtime FinishingAttack remains native action 15
→ existing execution animation/semantics remain native and unmarked
```

Do not make behavior code depend on the authored Hit-distance suffix or hardcode P0/P1 filename fields. The current proposed Hack assets intentionally mirror the existing Finishing naming structure while using the distinct `HackAttack` action token and a P0-preserving 2H stance; exact filenames/authoring notes belong in `ANIMATION_CATALOG.md` / animation data, and their engine-facing field semantics remain governed by `ANIMATION_RULES.md`.

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
- `EVIDENCE_INDEX.md` → EV-151–EV-215

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

Authority: `COLLISION_TEST_PLAN.md` §6, with causal evidence routed through `EVIDENCE_INDEX.md`.

---

## 8. Marker Bookkeeping Is Not Physical Cleanup

The marker occurrence/duplicate/window state used to survive Gothic frame-effect replay is a different responsibility from physically returning a stale offensive source to a safe state.

The accepted execution identity is now:

```text
C1 monotonic generation
= durable marker occurrence/dedupe execution identity
```

Gate 4 removed/consolidated the older marker-local guesses that a new execution began from:

```text
source changes
motion changes
action changes
phase changes
state-time rollback
authored-count changes
controlled-callback rollback inference
```

Natural `RetireMarkerOwnedSource()` handling is narrowed to factual retirement of the exact physical marker-owned source bit/window. It is not whole-execution retirement authority.

Preserve all independent marker invariants:

- `Routine.StatePosition` advancement after custom ownership where required to suppress Gothic's competing timed activation;
- repeated-marker / repeated-contact rearm semantics;
- authored occurrence budgets and replay/duplicate protection;
- exact-set RIGHT/LEFT/BOTH/OFF switching;
- OFF as an intra-Hit inactive gap rather than terminal execution authority;
- interruption/dead-execution rejection;
- supported-family/current-motion/source-preflight ownership;
- physical marker-window/source-bit state;
- native fallback for unmarked/unsupported cases;
- valid-motion-only marker caching.

EV-131–EV-133 establish the historical interrupted-execution occurrence-budget defect. EV-167 separates marker bookkeeping from physical cleanup. EV-213 establishes the generation-scoped replacement, and EV-214 directly closes the literal historical same-motion interruption/restart regression under C1-generation identity. EV-215 completes behavior-only architecture verification.

Before any future marker-core consolidation/reimplementation:

```text
EVIDENCE_INDEX.md
→ Marker execution lifetime / bookkeeping
→ EV-131–EV-133 / EV-167 / EV-213–EV-214
→ COLLISION_LIFECYCLE_PLAN.md §9
```

Do not restore the superseded execution-boundary heuristics merely because a later expansion touches marker code.

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

Required compatibility checkpoints are:

```text
Collision research checkpoint
mature marker/source system + lifecycle guard + AttackContinuationProtection
→ test against New Balance / relevant Jackydima DLLs before production collision migration

Collision production-integration checkpoint
migrated collision modules in diagnostics-free Script_G3AnimationBehaviors
→ verify the collision-only production integration before promoting the completed collision branch to main

Final assembled behavior checkpoint
collision modules + Raise + redesigned speed/config in Script_G3AnimationBehaviors
→ retest against New Balance / relevant Jackydima DLLs before promoting the later Raise/speed branch to main
```

Passing one checkpoint does not prove a later assembled product compatible. Each branch-level stable promotion must be backed by the validation appropriate to the behavior being added in that branch.

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
│    C1-generation-scoped authored occurrence/replay/duplicate bookkeeping
│    competing native activation suppression
│    marker-owned physical source/window bookkeeping
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

Completed structural rewrite proof: EV-208–EV-212 plus current source/build state.

---

## 11. Current Implementation Order

The architecture-verification and project-stabilization phases are complete; they are closed foundations rather than executable roadmap steps.

Closed foundation:

```text
second-pass rewrite / product separation      EV-208–EV-212
Gate-4 generation-scoped marker bookkeeping  EV-213
literal historical regression closure        EV-214
final behavior-only architecture smoke       EV-215
project structural/governance stabilization  COMPLETE
```

Current branch/implementation order:

1. **Finish the remaining equipped-melee source/architecture review on `docs/collision-source-evidence`.** Required marker scope is PowerAttack, PierceAttack, SimpleWhirl and HackAttack. Classify GetUpAttack only as cleanly includable vs defer; true FinishingAttack is deliberately excluded and Fist/body remains separate.
2. **Freeze one shared remaining-equipped-melee adapter architecture.** Preserve RIGHT/LEFT/BOTH/OFF, explicit physical-source semantics, C1-generation marker identity and native no-marker fallback. Use one canonical family/action eligibility policy and explicit per-family callback-bookkeeping policy rather than multiplying marker-core special cases.
3. **For HackAttack, identify the narrow native-compatible action-14 animation-routing change needed to resolve dedicated HackAttack assets while keeping native Hack semantics and Gothic's ordinary filename interpretation.** Do not change true FinishingAttack action-15 execution behavior.
4. **Implement all remaining proven-compatible required equipped-melee adapters in one bounded code change.** At minimum Power + Pierce + SimpleWhirl + Hack; include GetUp only if the architecture review proves it genuinely clean.
5. **Validate every newly supported family independently before combined regression.** Power, Pierce, SimpleWhirl and Hack each get their own controlled test; GetUp is separate if included. Family-by-family testing is the causal isolation mechanism even though implementation is batched.
6. **Investigate Fist as a separate source adapter.** Do not force Fist through weapon-style `Item_Attack` semantics; start from the logical body-contact/rearm and target-gating evidence.
7. **Run complete marker + lifecycle regression.** Protect closed C1-R1/Gate-4 behavior after marker/source maturity.
8. **Investigate/implement modular `AttackContinuationProtection`.** Separate from `CollisionLifecycleGuard`; keep C1-R1 underneath.
9. **Validate guard + markers + continuation protection together.** Include bad-skip prevention, ordinary completion, reactions and non-attack held-Use2 control.
10. **Run the mandatory New Balance/Jackydima compatibility checkpoint on mature research collision behavior.** Resolve hook/callback conflicts deliberately before production migration.
11. **Migrate the mature collision behavior modules into the production-direction `Script_G3AnimationBehaviors` on the same collision branch.** Keep the `Script_G3AnimationBehaviors` name; do not create a collision-named public DLL and do not pour the new architecture back into the old v0.1 hook/file structure. Research diagnostics remain separate.
12. **Validate the diagnostics-free collision integration in `Script_G3AnimationBehaviors`.** Include source/build review, load/functional regression and the compatibility checks appropriate to the collision-only production checkpoint.
13. **Promote the completed collision branch to `main`.** At that boundary `main` becomes the stable Animation Behaviors baseline with mature collision behavior integrated into the production-direction DLL.
14. **Create `feature/raise-attack-speed` from that newly updated `main` only after the collision promotion is complete.** Do not create or develop the branch early.
15. **On `feature/raise-attack-speed`, mature Raise + general/action/profile attack-speed control and redesign/migrate configuration into the shared `Script_G3AnimationBehaviors` architecture.** Preserve feature independence and the closed collision foundation.
16. **Run final diagnostics-free assembled-behavior compatibility/regression before promoting the Raise/speed branch to `main`.** Retain separate diagnostic twins/tools for future reproduction.
17. **Later add independent systems such as target acquisition/climbing under the same central-bridge/module/release-purity architecture.**

---

## 12. Non-Goals for the Current Marker-Expansion Responsibility

Do not combine the current remaining-equipped-melee architecture/implementation step with:

- new marker vocabulary without a separately proven source model;
- true `FinishingAttack` marker ownership or execution redesign;
- generalized Fist/body support;
- universal monster/body adapters;
- forcing `GetUpAttack` into the batch if it requires new execution identity/lifecycle machinery;
- parsing/reimplementing Gothic's destination-pose, movement-distance or other ordinary filename semantics in behavior code;
- AttackContinuationProtection implementation;
- Raise/speed changes;
- configuration redesign;
- production collision migration before collision research maturity;
- creation of `feature/raise-attack-speed` before the completed collision checkpoint is on `main`;
- target acquisition;
- climbing;
- changing closed C1-R1 or Gate-4 behavior without contradicting evidence.

---

## 13. Retrieval Routes

| Need | Authority |
|---|---|
| Current exact task / branch state | `SESSION_ENTRYPOINT.md` + `BETWEEN_CHATS.md` |
| Completed second-pass structural proof | `EVIDENCE_INDEX.md` → EV-208–EV-212 + current source/build state |
| Completed Gate-4 marker bookkeeping proof | `EVIDENCE_INDEX.md` → EV-213–EV-215 |
| Current roadmap / overall architecture | this `DESIGN.md` §§10–11 |
| Release vs diagnostic products | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` |
| Collision lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| Current collision validation posture | `COLLISION_TEST_PLAN.md` |
| Diagnostic core/deep architecture | `COLLISION_LOGGER_PLAN.md` |
| Marker execution lifetime / generation-scoped identity | `EVIDENCE_INDEX.md` Marker execution lifetime → EV-131–EV-133 / EV-167 / EV-213–EV-214 → `COLLISION_LIFECYCLE_PLAN.md` §9 |
| Future held-Use2 prevention | `COLLISION_TEST_PLAN.md` §6 AttackContinuationProtection + `EVIDENCE_INDEX.md` causal route |
| Tested native cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| Exact evidence claim / provenance | `EVIDENCE_INDEX.md` → canonical evidence ledgers / raw/archive evidence |
| C1-R1 canonical evidence | `EVIDENCE_LEDGER_199_ONWARD.md` EV-206–EV-207 |
| Gate 4 + final architecture verification evidence | `EVIDENCE_LEDGER_199_ONWARD.md` EV-213–EV-215 |
| Animation semantics / UseType / action / pose | `ANIMATION_INDEX.md` → `ANIMATION_RULES.md` |
| Exact asset/family/fixture | `ANIMATION_INDEX.md` → `ANIMATION_CATALOG.md` / animation-name data |
| Hook/source/API/New Balance lookup | `SOURCE_HOOK_GUIDE.md` |
| Historical design/prototype chronology | `EVIDENCE_INDEX.md` → exact EV/provenance, then Git history/raw logs when chronology is actually needed |
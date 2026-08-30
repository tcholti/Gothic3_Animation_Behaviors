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

This file defines the **intended architecture**. It does not preserve experiment chronology. For proof history and exact tested claims use `EVIDENCE_INDEX.md` → the evidence ledgers/raw logs. For the current collision-lifecycle research model use `COLLISION_LIFECYCLE_PLAN.md`.

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
Hook / engine bridge
    reports authoritative engine facts

Behavior modules
    own Raise / speed / collision decisions

Diagnostics
    observe and record facts
```

Diagnostics must remain removable without changing production behavior.

### DP-06 — Preserve proven paths while expanding

Change one meaningful subsystem/family responsibility at a time when that improves causal confidence. Do not rewrite a proven path merely because another family is being added.

### DP-07 — Controlled fallback

If a custom rule does not intentionally apply, preserve the original/native path.

### DP-08 — Configuration loaded once

Parse configuration during initialization into normalized in-memory rules. Do not repeatedly parse the INI during attacks.

### DP-09 — Evidence before generalization

Player-only success is not sufficient evidence for an actor-general feature. Use controlled NPC cases when actor scope matters, and use runtime/source evidence for subtle engine behavior.

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
- keep Raise separate from collision lifecycle repair;
- initially generalize Normal and Quick families, then selected full-Whirl paths where evidence/assets justify it.

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
- calibrate final family values from measured native/custom durations rather than freezing provisional authoring guesses.

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
- marker timing is animation-specific, not a universal fixed offset.

Body/Fist/monster marker vocabulary remains separate and must not be invented before its source model is understood.

### 6.3 Physical source model

Equipped weapon sources use the corresponding equipped entity and weapon-style offensive collision operation.

Fist/body contact is **not** assumed to use the same physical collision-group mechanism. Controlled Fist evidence shows logical rearm/contact can work while the logical Fist entity remains outside weapon-style `Item_Attack` group handling.

Treat weapon activation and body/Fist rearm as separate source adapters behind one higher collision-control responsibility.

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

The known held-Use2 destructive route is a separate future root-cause responsibility. C1-R1 deliberately fails closed after ownership has already been destroyed; it does not attempt to resurrect that attack.

Future root investigation should ask whether the destructive FullStop/state-replacement consequence can be suppressed/deferred while a real attack CombatMove is active without changing legitimate reactions or non-attack held-Use2 behavior.

Authority: `BAD_SKIP_FUTURE_INVESTIGATION.md`.

Even if such a root fix later succeeds, keep C1-R1 as the general lost-cleanup fail-safe.

---

## 8. Marker Bookkeeping Is Not Physical Cleanup

The marker occurrence/duplicate/window state used to survive Gothic frame-effect replay is a different responsibility from physically returning a stale offensive source to a safe state.

A natural/native source reset may retire marker bookkeeping when it proves the old execution ended. Intentional intra-Hit OFF/source switching must not retire the entire execution.

Existing marker bookkeeping fixes are proven behavior and must remain until a stronger authority replaces them. In particular, current code must continue to preserve:

- `Routine.StatePosition` advancement after custom ownership where required to suppress Gothic's competing timed activation;
- repeated-marker / repeated-contact rearm semantics;
- occurrence/replay protection;
- exact-set RIGHT/LEFT/BOTH/OFF switching;
- interruption retirement so one execution's marker budget does not survive into the next.

The C1-R1 marked Staff regression proves terminal physical repair can pass through the existing SetCollisionGroup observation path, retire the existing marker-owned source bookkeeping, reject late callbacks from the abandoned execution, and allow the next legitimate marked attack to begin fresh.

A **future simplification possibility** remains: the proven native execution/ScriptFunction/CombatMove lifetime may eventually replace some custom execution inference. That is not a current refactor instruction.

Before any future marker-core consolidation or reimplementation, use this retrieval route:

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

---

## 10. Current Implementation Order

1. Plan and freeze the smallest stable production-integration boundary for the validated C1/P2/R1 collision guard/core and existing marker behavior.
2. Implement/integrate only that frozen collision responsibility, keeping research-only diagnostics separable and preserving every accepted source/lifecycle invariant.
3. Validate the production-integrated collision core against the compact regression matrix frozen after the integration boundary is understood.
4. Before simplifying marker bookkeeping, review the marker-lifetime route in `EVIDENCE_INDEX.md` / `COLLISION_LIFECYCLE_PLAN.md` and remove custom inference only where a stronger proven native boundary replaces it safely.
5. Keep the held-Use2 destructive-skip root investigation separate; pursue it only as a deliberate later responsibility and keep C1-R1 underneath as fail-safe.
6. Generalize Raise for intended Normal/Quick families and selected full-Whirl cases without coupling it to collision repair.
7. Implement profile-aware speed control and calibrate family/action values from logged timing evidence.
8. Broaden actor/source support only where the native source semantics are understood.
9. Preserve useful animation-selection/CombatMove discoveries for later features rather than mixing them into unrelated behavior.

---

## 11. Non-Goals for the Current Iteration

Not immediate implementation targets:

- global creature reanimation;
- intended-target/crosshair correction;
- climbing;
- rewriting Gothic 3 input arbitration;
- manually constructing all combat animation filenames;
- inventing universal body/monster collision markers before source semantics are known;
- replacing every third-party collision behavior before equivalent ownership/source behavior exists.

---

## 12. Retrieval Routes

| Need | Authority |
|---|---|
| Current task / current branch state | `SESSION_ENTRYPOINT.md` |
| Collision lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| Current collision validation | `COLLISION_TEST_PLAN.md` |
| Marker execution lifetime / future marker-core simplification | `EVIDENCE_INDEX.md` Marker execution lifetime → `COLLISION_LIFECYCLE_PLAN.md` §9 |
| Future held-Use2 root investigation | `BAD_SKIP_FUTURE_INVESTIGATION.md` |
| Tested native cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| Exact evidence claim / provenance | `EVIDENCE_INDEX.md` → ledgers/raw logs |
| C1-R1 canonical evidence | `EVIDENCE_LEDGER_STEP_D.md` EV-206–EV-207 |
| Animation semantics / UseType / action / pose | `ANIMATION_INDEX.md` → `ANIMATION_RULES.md` |
| Exact asset/family/fixture | `ANIMATION_INDEX.md` → `ANIMATION_CATALOG.md` / animation-name data |
| Hook/source/API lookup | `SOURCE_HOOK_GUIDE.md` |
| Historical design/prototype chronology | `RESEARCH_MAP.md` / archived pre-IA documents / raw logs |

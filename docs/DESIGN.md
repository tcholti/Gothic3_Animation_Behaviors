# Gothic 3 Animation Behaviors — Design

**Status:** Canonical project architecture  
**Updated:** 2026-08-28  
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
WHEN THE HIT IS OVER:
offensive collision must be clean.
If Gothic already cleaned it -> no-op.
If Gothic failed -> repair using native cleanup semantics.
```

The current preferred lifecycle architecture is an **execution-level native cleanup guard**. It follows one exact real attack-Hit execution that actually requested offensive collision and observes whether Gothic performed legitimate cleanup for that execution.

B6 rejected the earlier replacement-triggered deferred-`ProcessScript()` checkpoint in its present form. B7 now reconstructs Gothic's native CombatMove execution lifetime one layer earlier: `sAICombatMoveInstr` can persist as an SPU instruction callback while the owning ScriptFunction is suspended at a break block; clean attack cleanup is reached only when that continuation resumes, while reaction-control code can explicitly FullStop the current instruction and continue under separate reaction ownership.

The exact finalization boundary is still under research. A generic script boundary, action/phase value, visible successor animation, or persisted instruction callback must never become attack ownership authority by itself.

Current lifecycle authority and constraints:

- `COLLISION_LIFECYCLE_PLAN.md`
- `COLLISION_CLEANUP_CALLSITE_MAP.md`
- `EVIDENCE_LEDGER_STEP_B.md` / `EVIDENCE_INDEX.md`

Do not implement family-specific cleanup matrices, timers, polling, or block-timeout special cases merely because native cleanup has several internal paths.

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

B7 introduces a **future simplification possibility**, not a current refactor instruction: if one exact marked Hit can later be correlated safely with Gothic's persisted CombatMove instruction + ScriptFunction break-block lifetime, some custom execution/occurrence inference may become redundant. If that is proven, simplify custom state at the stronger native boundary.

Before any future marker-core consolidation or reimplementation, use this retrieval route:

```text
EVIDENCE_INDEX.md
→ Marker execution lifetime / bookkeeping
→ future marker-core simplification / native execution boundary
→ COLLISION_LIFECYCLE_PLAN.md §10
```

That route deliberately joins the older marker regressions/fixes with EV-182–EV-184 and later B7 results.

Do not equate `m_pfInstrCallback == sAICombatMoveInstr` alone with exact marked-Hit identity, and do not conflate marker retirement with physical cleanup before one proven native execution boundary can safely own both.

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

1. Finish B7 attack-lifecycle/bookkeeping reconstruction and establish a reliable general collision-finalization boundary.
2. Implement and validate the universal execution-level collision cleanup rule without family/cause-specific repair matrices.
3. Before consolidating the marker core into production, review the marker-lifetime route in `EVIDENCE_INDEX.md` / `COLLISION_LIFECYCLE_PLAN.md` §10 and simplify custom bookkeeping only where a stronger native exact-execution boundary is proven.
4. Integrate the stable collision core into the production `Script_G3AnimationBehaviors` boundary only after lifecycle safety and marker bookkeeping are evidence-backed.
5. Generalize Raise for intended Normal/Quick families and selected full-Whirl cases without coupling it to collision repair.
6. Implement profile-aware speed control and calibrate family/action values from logged timing evidence.
7. Broaden actor/source support only where the native source semantics are understood.
8. Preserve useful animation-selection/CombatMove discoveries for later features rather than mixing them into unrelated behavior.

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
| Marker execution lifetime / future marker-core simplification | `EVIDENCE_INDEX.md` Marker execution lifetime → `COLLISION_LIFECYCLE_PLAN.md` §10 |
| Tested native cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| Exact evidence claim / provenance | `EVIDENCE_INDEX.md` → ledgers/raw logs |
| Animation semantics / UseType / action / pose | `ANIMATION_INDEX.md` → `ANIMATION_RULES.md` |
| Exact asset/family/fixture | `ANIMATION_INDEX.md` → `ANIMATION_CATALOG.md` / animation-name data |
| Hook/source/API lookup | `SOURCE_HOOK_GUIDE.md` |
| Historical design/prototype chronology | `RESEARCH_MAP.md` / archived pre-IA documents / raw logs |
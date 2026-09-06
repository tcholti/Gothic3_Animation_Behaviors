# Gothic 3 Animation Behaviors — Design

**Status:** Canonical project architecture  
**Updated:** 2026-09-06
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

Action/callback/phase identify the attack mechanism. The physical source that can produce a damaging contact is a separate concern.

Possible sources include:

- equipped right weapon;
- equipped left weapon;
- both equipped weapons;
- logical Fist/body-contact source;
- future monster/body/limb/head sources.

Never infer the physical source from a generic `Hit`, final filename `R/L`, or QuickAttackR/L token alone.

Conversely, proving that a physical source is correctly offensive does **not** prove that every Gothic action family applies identical character-hit eligibility, targeting or effect semantics to every actor contacted by that source. Current Pierce and SimpleWhirl evidence requires those layers to remain distinct unless a later controlled result proves a safe uniform rule.

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

The exact-set contract is a **physical source contract**:

```text
marker
→ desired equipped source set
→ Item_Attack / Item_Equipped transitions as required
→ ClearTriggeredList rearm on each authored contact
```

It does not, by itself, promise that every supported `gEAction` applies identical native character-hit eligibility or target/effect semantics to every actor intersected by those physical sources. EV-217 proves SimpleWhirl BOTH can correctly arm both physical weapons; EV-220 nevertheless shows that SimpleWhirl remains substantially more target-directed than true PowerAttack under matched motion content. The framework-level normalization policy is therefore intentionally open until the native cause and safety consequences are understood.

Authoring rules:

- at most one G3AB collision command on one authored frame;
- use BOTH instead of same-frame RIGHT + LEFT;
- keep OFF and a later activation on different frames;
- a repeated source marker later in the same Hit is a new authored contact and rearms that source with `ClearTriggeredList()`;
- marker timing is animation-specific, not a universal fixed offset;
- do not create action-specific marker names such as Power/Quick/Whirl RIGHT variants; action-family support belongs in the ownership layer, not the marker vocabulary;
- until the SimpleWhirl/Pierce native eligibility boundary is resolved into a release contract, do not document BOTH as a universal guarantee that both weapons can damage every character they visibly cross in every action family.

Human Fist uses the separately defined `G3AB_COL_FIST` / `G3AB_COL_FIST_OFF` vocabulary and native body-damage path below. Monster/body vocabulary remains future scope and must not be inferred from the human mechanism.

### 6.3 Shared marker infrastructure; separate native behavior mechanisms

The generic authored-marker layer may share only genuinely mechanism-neutral infrastructure:

- exact animation/frame-effect scanning;
- reserved marker recognition;
- marker occurrence/dedupe bookkeeping;
- C1-generation as factual execution identity;
- exact current animation/action/phase context;
- the decision that a marked execution opts into custom authored timing.

After that generic ownership layer, equipped weapons and human Fist must remain separate conceptual and code paths:

```text
Generic authored-marker infrastructure
        |
        +--> Equipped-weapon collision mechanism
        |       G3AB_COL_RIGHT
        |       G3AB_COL_LEFT
        |       G3AB_COL_BOTH
        |       G3AB_COL_OFF
        |
        |       equipped RIGHT/LEFT source identity
        |       Item_Attack / Item_Equipped
        |       weapon ClearTriggeredList repeated-contact semantics
        |       marker-owned weapon source masks/windows
        |       C1 weapon lifecycle/cleanup
        |
        +--> Human Fist/body-damage mechanism
                G3AB_COL_FIST
                G3AB_COL_FIST_OFF

                exact human gEUseType_Fist / raw 8 semantics
                sAICombatMoveItlLoop native timing/eligibility
                SPU+0x164 factual combat latch
                gCEntity::OnDamage dispatch

                no equipped weapon source-mask semantics
                no Item_Attack ownership assumption
                no weapon marker-owned source window
                no weapon C1 lifecycle obligation
```

Weapon markers and Fist markers must not be mixed in native-mechanism code. Share genuinely generic marker infrastructure only. Equipped-weapon behavior code must not grow Fist special cases merely because both systems use frame-effect markers. Fist/body-damage behavior must not inherit weapon source masks, `Item_Attack` transitions, weapon C1 lifecycle or repeated-contact operations merely for architectural convenience. This is a design-for-separation rule, not a demand for premature module/class restructuring; exact final code organization remains an implementation decision after the native mechanism is understood.

Within each mechanism, source identity/facts and source mutation remain separate layers. `CollisionSources` does not own marker policy or mutation, and physical-source operations do not decide attack family, marker ownership, desired source set or native character-hit eligibility.

#### Equipped-weapon mechanism

```text
FrameCollisionMarkers
    ↓ desired source set / authored contact
CollisionSources
    ↓ factual RIGHT/LEFT entity + UseType/source availability
CollisionSourceOperations
    ↓ Item_Attack / Item_Equipped
    ↓ repeated-contact ClearTriggeredList rearm
marker-owned weapon source windows + C1 lifecycle
```

The closed equipped-weapon RIGHT/LEFT/BOTH/OFF architecture remains unchanged.

#### Human Fist/body-damage mechanism

Exact logical human `gEUseType_Fist` / raw 8 damage has body-contact semantics, not literal right-hand weapon collision. Controlled tests established damaging contact through at least the left hand, right hand, left leg, right leg and head. Current slot/source lookup therefore does not prove that a literal right-hand slot owns physical Fist damage.

The tested native path is:

```text
gCScriptProcessingUnit::sAICombatMoveItlLoop
    native timing / eligibility — unresolved
    -> SPU+0x164 factual combat latch
    -> gCEntity::OnDamage
```

N2D/N2E/N3 establish that latch `1` suppresses the confirmed dispatch, fresh combat-move lifecycle naturally returns it to `0`, and an explicit same-move `1 -> 0` write rearms the dispatch after FIST_OFF for the tested P0 Normal path. N3 does not establish latch zero as a complete authored-frame ON mechanism: the first FIST found `0`, yet the first punch did no damage, while the later FIST reopened the latch after native timing/eligibility had advanced and was followed by native OnDamage.

The exact resolved raw-8 Fist entity has also received native `eCEntity::SetCollisionGroup(eECollisionGroup_Item_Attack / 7)` requests, including observed attack-time requests around StateTime ~0.25, while its observable group remained `BeforeGroup: 0`, `AfterGroup: 0`. `SetCollisionGroup` is void: `AfterGroup: 0` is an observed post-call group, not a return/error code and not proof of formal rejection. The group-7 request is not architectural evidence that human Fist damage should use weapon `Item_Attack` semantics; its exact role remains unresolved.

Current Fist marker ownership can suppress the original Normal `OnAI_Attack` callback. That suppression is causally useful for established weapon marker paths, but it did not suppress the tested native Fist timer/dispatch path. Fist-specific participation in weapon-style `OnAI_Attack` suppression is therefore provisional and is not a proven final Fist ownership mechanism. N4 must test its necessity without changing weapon callback suppression.

The historical Stage-A `G3AB_COL_FIST -> TouchDamage.ClearTriggeredList()` operation was real, but its causal role in the confirmed native combat-loop path remains unproven. `ClearTriggeredList()` is **not** part of the intended final human-Fist marker architecture unless new direct evidence separately proves it necessary. This does not imply that the operation is globally useless or irrelevant to other TouchDamage paths, and its eventual source removal must remain a separate causal change unless a later frozen task explicitly combines it.

The intended final authored-Fist principle is:

```text
attack selects/resolves exact Hit animation
-> inspect its reserved Fist markers

if no Fist markers
    preserve native Fist behavior

if Fist markers exist
    suppress the actual native Fist timing/dispatch mechanism
    not weapon Item_Attack machinery

G3AB_COL_FIST
    create/release the native-equivalent Fist damage opportunity
    at the authored marker

G3AB_COL_FIST_OFF
    suppress further Fist damage opportunity

native unmarked timing must not leak through a marker-owned Fist execution
```

The central unresolved mechanism is the native timing/eligibility logic inside `sAICombatMoveItlLoop` that prevents damage at the first authored FIST marker even though `SPU+0x164` is already zero. Evidence must determine whether the eventual operation mutates a native field, calls a native Fist function, releases eligibility, invokes lower-level damage or uses another mechanism; this design does not decide that prematurely.

This human architecture does not generalize to monsters or `gEUseType_PhysicalFist` / raw 55. User-observed monster armature slot locations are future comparison observations, not proof of engine damage routing or a fallback algorithm.

### 6.4 Repeated contacts

This subsection defines equipped-weapon repeated-contact behavior, not human Fist behavior.

A weapon/entity visit list can suppress repeated damage to the same target. Repeated authored contacts therefore rearm the selected logical source through `ClearTriggeredList()`.

`BOTH` rearms both selected sources at that authored moment; it is not a substitute for later repeated source markers.

Successful rearm is evidence that the selected physical source was made eligible for a new authored contact under the source layer. It does not override a separate native action-family rule that may determine whether a particular actor contact becomes damage/effect.

### 6.5 Marker decision caching

Only cache a marker/no-marker decision after the exact current motion is resolved and the frame-effect scan is valid enough to establish a factual result.

Do not permanently cache a transient unresolved-motion failure as a negative marker decision.

### 6.6 Remaining equipped-melee expansion boundary

The shared marker/source/generation core has been reviewed as suitable for broader ordinary equipped-weapon expansion. The implemented expansion families are:

```text
PowerAttack
PierceAttack
SimpleWhirl
HackAttack
```

Current validation state:

```text
PowerAttack  marker/source validation CLOSED/PASS
PierceAttack marker/source validation CLOSED/PASS
SimpleWhirl  physical marker/source validation PASS; character-hit eligibility semantics OPEN
HackAttack   implementation present; isolated marker/routing validation pending after SimpleWhirl
```

`GetUpAttack` is **not part of the planned development roadmap**. Current review found materially different behavior: legitimate offense can occur before later CombatMove, and its native callback also changes `AniState` to `Stand`. Do not spend further marker-engineering time on GetUp unless a future concrete requirement explicitly reopens it as a separate investigation.

`FinishingAttack` is deliberately excluded. The true downed-enemy Finishing path is an execution mechanic whose observed kill timing is not dependent on ordinary weapon contact; preserve its native behavior and do not require collision markers for it.

Human Fist/body damage remains a separate native behavior-mechanism responsibility after genuinely generic marker ownership; it is not an equipped-weapon source adapter.

The remaining validation is family-specific. Resolve the SimpleWhirl character-hit eligibility boundary enough to define the intended framework guarantee, then validate Hack independently before combined regression.

#### SimpleWhirl native character-hit semantics

Current evidence separates the validated G3AB source layer from an unresolved native eligibility layer:

```text
SimpleWhirl Action 6 / _AI_SimpleWhirl
+ Power-derived Dual motion content
+ authored BOTH -> single -> OFF -> BOTH source program
+ both exact equipped sources physically activated/rearmed
+ StatePosition 1
→ substantially target-directed character-hit behavior

true Dual Power Action 2 / _AI_PowerAttack
+ matched authored motion content/program
+ both exact equipped sources physically activated/rearmed
+ StatePosition 2
→ broad character-hit behavior in the User's comparison
```

Strict “selected target only” is not supported because unselected actors can sometimes be damaged. Conversely, one apparent two-target/two-sword SimpleWhirl observation failed deliberate reproduction and is not a basis for a multi-target guarantee.

The immediate one-variable falsification is temporary SimpleWhirl StatePosition `1 -> 2` while action/callback/motion/marker/source/target setup remains otherwise unchanged. This is diagnostic investigation only; permanent bookkeeping and any normalization policy remain unfrozen until evidence identifies the responsible native semantic.

#### HackAttack optional animation routing

Runtime `gEAction_HackAttack` and `gEAction_FinishingAttack` remain distinct behavior/cleanup semantics even though tested Hack currently reuses the serialized `FinishingAttack` asset family.

Established static/native facts:

```text
gEAction_HackAttack      = 14
gEAction_FinishingAttack = 15

GetAniName = Game +0x16F840

within sAICombatMoveInstr:
    GetAniName call                 = Game +0x16B056
    factual current action          = [SPU + 0x154] immediately afterward
    native motion-resource query    = Game +0x16B10C
```

EV-216 closes the tested callback identity: `Script_Game +0x433D0` uniquely registers as `OnAI_HackAttack`, source `.\Script\AI\AI_Commands\AI_HackAttack.cpp`. This does not yet validate Hack markers or resource routing.

Compatibility facts:

- Jackydima `Script_Animation` can hook `GetAniName` and change the serialized weapon namespace, for example `2H` to `Axe`.
- New Balance performs known CombatMove animation-string work around `Game +0x16B065`.
- G3AB therefore should not unnecessarily own/replace `GetAniName` and should not globally patch action 14's action-string table.

The implemented preferred architecture is:

```text
active native/installed resolver produces the final ordinary resource name
→ CombatMove factual action is read from the existing SPU context
→ at the narrow CombatMove motion-resource query callsite
→ IF factual action == HackAttack (14)
   AND the requested resource contains the exact FinishingAttack action token:
       derive one candidate by replacing only
           _FinishingAttack_ → _HackAttack_

       query the candidate through Gothic's native animation resource system

       candidate exists:
           return/use the candidate resource

       candidate absent:
           query/return the untouched original FinishingAttack resource
→ any non-Hack action, including true FinishingAttack (15):
       untouched native path
```

Dedicated Hack assets are optional overrides. Matching asset existence is the opt-in; no Hero/2H/Staff hardcoded gate is required.

Preserve every namespace, pose, direction, distance and variation field produced by Gothic or another active resolver. Do not parse or reimplement ordinary filename metadata. Do not release the returned candidate resource before returning it when it becomes the actual motion resource.

True `FinishingAttack` remains native and unmarked. Optional Hack routing and Hack marker behavior remain unvalidated until their later runtime tests.

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
- `EVIDENCE_INDEX.md` → EV-151–EV-220

Do not implement family-specific cleanup matrices, timers, polling, held-Use2 classifiers, arbitrary group-7 adoption, or broad scans merely because native cleanup has several internal paths.

### Known bad-skip root relationship

The known held-Use2 destructive route is a separate future prevention responsibility.

```text
AttackContinuationProtection
= prevent the known destructive route from killing a valid active attack

CollisionLifecycleGuard
= make an exact stale offensive source safe if cleanup is nevertheless lost
```

The required `AttackContinuationProtection` outcome is frozen: prevent the known destructive continuation/bad-skip mechanism from terminating or advancing through a legitimately live Hit execution.

The exact mechanism is not frozen. The current preferred investigation may identify and freeze/suppress the responsible timer or continuation trigger while Hit is authoritatively alive, but literal timer-freezing is not the only permitted implementation. Prefer a cleaner native operation if it enforces the same invariant.

Keep `AttackContinuationProtection` separate from `CollisionLifecycleGuard`. Even if prevention later succeeds, retain C1-R1 as the general lost-cleanup fail-safe.

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

EV-220 asks whether StatePosition also participates in SimpleWhirl's native character-hit eligibility. That is a separate causal question and does not weaken the accepted C1-generation execution identity.

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
│    RIGHT / LEFT / BOTH / OFF physical source-set semantics
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

Current accepted sequence:

```text
Power marker/source validation CLOSED
→ Pierce marker/source validation CLOSED
→ SimpleWhirl physical marker/source validation PASS
→ resolve SimpleWhirl native character-hit eligibility enough to define framework guarantee
→ Hack isolated marker/routing validation
→ combined remaining-melee marker/lifecycle regression
→ N4 Fist callback-suppression necessity test
→ bounded removal/retest of obsolete Fist scaffolding when separately frozen
→ identify native Fist timing/eligibility inside sAICombatMoveItlLoop
→ full marker/lifecycle regression
→ AttackContinuationProtection
→ combined collision regression
→ mature New Balance/Jackydima compatibility gate
→ migrate mature collision behavior into Script_G3AnimationBehaviors
→ diagnostics-free integration + compatibility
→ promote collision checkpoint to main
→ create feature/raise-attack-speed from updated main
→ mature Raise + action/profile speed + configuration redesign
→ final assembled compatibility/regression
→ promote mature Raise/speed checkpoint to main
→ FIRST PUBLIC FRAMEWORK RELEASE with 2H animation content
```

### Release 1 boundary

Framework:

```text
general marker/collision framework
+ validated AttackContinuationProtection / bad-skip prevention
+ mature Raise framework
+ general/action/profile attack-speed + configuration framework
+ required compatibility/regression
```

Release 1 animation content is intentionally 2H only. Framework completeness does not require every weapon family to have finished replacement animations.

After Release 1, update remaining weapon-family animation content one family at a time: adapt each family to the new speed possibilities, add or adjust Raise animations, add markers, and release families incrementally.

During that longer content period, climbing may be revisited sporadically or opportunistically; target acquisition remains a separate future system; and other animation-system improvements should be investigated individually when a concrete need appears rather than preplanned as one giant rewrite.

---

## 12. Non-Goals for the Current Marker-Expansion Responsibility

Do not combine the current SimpleWhirl semantic investigation / remaining-equipped-melee validation with:

- new marker vocabulary without a separately proven source model;
- `GetUpAttack`, unless a future concrete requirement separately reopens it;
- `FinishingAttack` marker/execution redesign;
- Fist/body support;
- universal monster/body adapters;
- parsing/reimplementing Gothic's destination-pose, movement-distance or other ordinary filename semantics in behavior code;
- AttackContinuationProtection implementation;
- Raise/speed/configuration work;
- production collision migration;
- creation of `feature/raise-attack-speed` before the completed collision checkpoint is on `main`;
- unrelated systems, including target acquisition and climbing;
- changing closed C1-R1 or Gate-4 behavior without contradicting evidence;
- treating the temporary SimpleWhirl StatePosition-2 falsification as a permanent design decision before runtime evidence.

---

## 13. Retrieval Routes

| Need | Authority |
|---|---|
| Current exact task / branch state | `SESSION_ENTRYPOINT.md` + `BETWEEN_CHATS.md` |
| Completed second-pass structural proof | `EVIDENCE_INDEX.md` → EV-208–EV-212 + current source/build state |
| Completed Gate-4 marker bookkeeping proof | `EVIDENCE_INDEX.md` → EV-213–EV-215 |
| SimpleWhirl physical source / actor-hit semantics | `EVIDENCE_INDEX.md` → EV-217–EV-220 → `research/derived/2026-09-03_simplewhirl_validation_and_target_semantics_checkpoint.md` |
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

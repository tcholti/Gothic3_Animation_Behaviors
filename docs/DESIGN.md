# Gothic 3 Animation Behaviors — Design

**Status:** Canonical project architecture  
**Updated:** 2026-10-04
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

`Script_G3AnimationBehaviors` is the general animation-behavior layer for Gothic 3. Production collision and Speed v2 are CLOSED/PASS. Additive Raise control is the active feature responsibility, initially for Normal, Quick and Whirl. Future independent domains may include target acquisition, attack displacement control, and climbing.

This file owns overall intended architecture and implementation order. Established collision facts are projected in `COLLISION_REFERENCE.md`; collision lifecycle authority is `COLLISION_LIFECYCLE.md`; validation authority is `COLLISION_TEST_PLAN.md`; diagnostics are owned by `COLLISION_DIAGNOSTICS.md`; permanent raw8 behavior is owned by `COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md`; permanent raw55 behavior is owned by `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`; practical source/hook lookup is `SOURCE_HOOK_GUIDE.md`; exact proof routes through `EVIDENCE_INDEX.md`.

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
15. Collision markers author **collision/contact opportunity**, not gameplay damage policy. Marker systems may open, rearm and close native collision opportunities, but Gothic and other behavior systems remain authoritative for target validity, block/parry, immunity, knockdown/get-up vulnerability, reactions, damage amount and whether HP damage occurs at all. A native hit/contact can therefore consume an authored opportunity even when the resulting gameplay damage is zero.

---

## 2. Configuration Identity

The shared Raise/speed profile identity is:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
```

Under ADR-0011, Speed/Raise profile identity follows the **resolved animation set actually requested by Gothic**:

```text
AnimationFamily
+ ResolvedLeftAnimationToken
+ ResolvedRightAnimationToken
```

At the factual Speed request boundary, production resolves `Entity.GetAni(action, phase)` and extracts the left/right animation tokens from Gothic's canonical animation-name structure. This is deliberately different from using raw equipped `gEUseType`. Native Axe that resolves `..._None_2H_...` shares the 2H profile; Axe Separation resolving `..._None_Axe_...` gets an Axe profile; Rapier remains raw 1H but resolves `..._None_Rapier_...` and therefore gets a Rapier profile; Zombie Separation changes `AnimationFamily` to `Zombie`. Shared animations share Speed settings automatically, while genuinely separated animation sets are independently configurable without mod-specific C++ branches.

`G3AnimationBehaviors.ini` is loaded once during DLL startup into a normalized in-memory profile table. Runtime handling performs only an in-memory profile lookup; it does not reread or reparse the INI on each attack. Missing/unconfigured profiles and missing/invalid per-attack settings preserve the live compatible behavior.

Each profile contains independent optional settings for the factual attack families currently supported by Speed:

```text
Normal
Quick
Power
Pierce
Hack
SimpleWhirl
Whirl
```

Speed-supported attacks may contain:

```text
<Attack>_ReferenceHitBaseSpeed
<Attack>_BaseSpeed
```

The initial public additive-Raise surface is deliberately narrower:

```text
Normal_AddRaise
Quick_AddRaise
Whirl_AddRaise
```

Do not infer public AddRaise support for the other Speed attack families merely from the generic internal profile structure.

Quick runtime variants remain factual Action4/Action5 internally but share the user-facing `Quick` settings. Generic Action3 is a selector rather than the proven playback-speed action. Sprint remains factual Action9 in actor state, but its proven shared Power speed route supplies Action2 to the speed owner; under ADR-0009 Sprint therefore inherits the `Power` timing settings and has no separate Speed prefix. EV-401 clarifies that profile inheritance does **not** require equal live Power/Sprint results: in one same-run BlackGoblin control ordinary Power Hit was `1.0` while factual Sprint Hit was `1.5`, despite both passing Action2. The Power profile supplies the authoring base; the live compatible result may still contain Sprint-context effects that C/B composition must preserve.

No P0/P1/P2/P3 pose split belongs in the user-facing profile identity.

Raise/speed feature policy must not grow weapon-specific C++ branches such as `if 1H`, `if 2H`, `if Axe`, or `if Staff` merely to select configured behavior. Weapon/use-type selection belongs to profile data plus normalized runtime facts. A modded item participates through the runtime UseType / animation category and animation family it exposes; adding another configured profile should not require a new C++ weapon branch.

The generic INI schema is now implemented. `<Attack>_AddRaise` is the locked player-facing syntax for attacks where G3AB deliberately adds a missing/unused Raise. The current source still stores the dormant field internally as `RaiseOverride`; implementation may keep generic internal storage if that is cleaner. Missing/Off means G3AB adds nothing and native Gothic behavior is untouched.

Architecture rationale: ADR-0005 + ADR-0006 + ADR-0009.

---

## 3. Raise and Speed

### Raise

A configured custom Raise is intended to prepend the appropriate preparatory CombatMove phase before the untouched original melee state while preserving native Raise where already correct. Keep Raise independent from collision lifecycle and continuation protection.

Custom Raise does **not** hard-code an animation filename. Historical runtime proof also confirms that G3AB must not construct Raise filenames: the old 2H prototype supplied action + `Raise` phase only, and Gothic automatically resolved the correct P0/P1 Raise asset. The intended mechanism remains:

```text
matching configured profile/attack
-> request the corresponding Raise CombatMove phase
-> let Gothic resolve the actual animation from its normal request facts
   (animation family/state/use types/pose/action/phase/direction/etc.)
-> after Raise completes, continue the untouched original attack path
```

The existing 2H Normal prototype proves the basic “ask Gothic for Raise” mechanism; its player + None/2H gate is fixture scope, not final architecture. Speed is now CLOSED/PASS, so Raise is the active feature. Initial production scope is Normal, Quick and Whirl only. `<Attack>_AddRaise=On` means add a Gothic-resolved Raise before Hit; missing/Off adds nothing. G3AB does not expose a user-facing switch for disabling or replacing Raise phases Gothic already uses natively.

The first future Raise-speed question should remain evidence-driven: test whether an inserted Raise naturally follows the configured attack `BaseSpeed` before adding any separate Raise-speed setting or hook.

### Initial Raise production scope

The first implementation/acceptance scope is:

```text
Normal
Quick
Whirl
```

Power, Pierce, Hack, SimpleWhirl, Finishing and Sprint are not part of the first custom-Raise implementation. Do not add public `*_AddRaise` keys for native-Raise attacks merely for symmetry. Broader exposure requires a separate product decision.

Player-facing guidance: Normal and Quick do not normally execute Raise in Gothic 3. Matching Raise files exist for some native sets, but not necessarily every animation set. Enable `AddRaise` only when the correct Raise asset exists for that exact route; otherwise leave it Off.

Release documentation must show real matched Raise naming examples for `Attack`, `QuickAttackR`, `QuickAttackL`, and `WhirlAttack`. Do not tell authors to blindly rename only `Hit` to `Raise`, because native Raise/Hit suffixes can differ in destination pose and movement data.

Historical runtime testing established that the old `PS_Melee_Attack` Raise prepend coexisted successfully with New Balance. The Quick static precheck is now closed: generic Quick / Action3 is the native selector/request identity, and Gothic selects then writes factual `PropertyAction` Action4/QuickAttackR or Action5/QuickAttackL downstream before the proven `Script_Game+0x48677` Quick Hit consumer. G3AB must therefore not choose R/L at `PS_Melee_QuickAttack` entry and must not reproduce Gothic's selector logic.

The first production transport is deliberately split while preserving one generic AddRaise policy:

```text
Normal -> PS_Melee_Attack + PREPEND_BREAK_BLOCK
Whirl  -> PS_Melee_WhirlAttack + PREPEND_BREAK_BLOCK
Quick  -> existing CombatMove transport after Gothic has selected factual Action4/5
```

For Quick, `EngineBridge` remains the sole physical `sAICombatMoveInstr` hook owner and exposes only the smallest transport needed by the permanent Raise owner. The Raise feature may own only the minimal continuation state required to prepend one factual R/L Raise before the untouched factual R/L Hit; it may not add a new physical hook, infer direction, or alter Collision/Speed semantics. Normal has historical coexistence evidence; Quick/Whirl direct runtime coexistence is now PASS through EV-412, including the intended New Balance stack.

EV-412 also confirms the ownership boundary for the known destructive Alternative AI block-skip route: if that external path FullStops and replaces the active attack state, an in-progress Raise continuation may be destroyed. Disabling that block-skip behavior removed the observed Whirl skip in repeated testing. Raise must not add resurrection/recovery logic for this known state-destruction class; prevention remains owned by `AttackContinuationProtection`.

No separate Raise-speed control is authorized. First test whether the inserted Raise naturally reuses/inherits the attack's effective timing through CombatMove.

### Speed

A configured speed authors the **base speed term** for the matching profile/attack; it does not own the final effective playback speed.

The accepted production mechanism is caller-side composition **after** the live `Script_Game+0x42A0 GetAnimationSpeedModifier` owner has calculated the compatible result for the caller, rather than taking over the `+0x42A0` entry.

Reason about the route as:

```text
B = native Gothic reference base for the exact route
C = configured G3AB BaseSpeed
M = combined compatible/contextual multiplier effect already present in the live result

compatibleSpeed = B * M
configuredSpeed = compatibleSpeed * (C / B)
                = C * M
```

`ReferenceHitBaseSpeed` is therefore a **native Gothic calibration fact** for the exact family/loadout/attack route. It is not a New Balance value and normally is not an author-tuning control. `BaseSpeed` is the author-facing speed value.

This downstream algebra is intentionally the small price paid for the safer intervention boundary: Gothic/New Balance retain ownership of their internal speed policy, G3AB calls the live owner exactly once with the original caller action, then substitutes only the known base contribution while preserving compatible relative modifiers already present in the live result.

The production caller-side set currently covers 15 proven Hit call sites across:

```text
Normal
Quick
Power / shared Sprint-Power
Pierce
Hack
SimpleWhirl
Whirl
```

Power Raise at `Script_Game+0x47D51` is currently observation/research evidence only and is not a production Speed hook.

Finishing / `gEAction_FinishingAttack` / Action15 is intentionally outside the current production Speed profile set. EV-398 establishes three distinct native Finishing Hit speed consumers and direct native Action15 observations on Hero 2H and Staff while Hack/Action14 remains separately transported, even though native Gothic may resolve both actions to the same animation asset. EV-399 then closes the practical playback question: configured Hack `BaseSpeed=0.40` slowed Hack while Finishing remained native-timed both when the actions shared the same animation asset and after their assets were separated. Speed authority therefore follows the factual action route, not animation-file identity. The distributed INI contains no Finishing speed entries and default execution timing remains native; any later advanced optional Finishing configuration is a separate product decision, not required for Hack isolation.

EV-399 also observed the existing Hack Raise and Recover portions following the configured slow Hack playback. Preserve that as later Raise evidence only; it does not yet establish whether a future G3AB-inserted custom Raise phase naturally inherits the configured attack speed.


Runtime identity is generic:

```text
AnimationFamily = Animation.GetSkeletonName(...)
+ normalized left/right animation UseType
```

Unknown/missing family/profile/calibration remains fail-closed to the live compatible value.

ADR-0009 freezes factual Sprint/Action9 as an intentional Power timing alias on the proven shared speed route. EV-401 establishes that this is a **profile/authoring alias**, not a promise that the live compatible value equals ordinary Power: Gothic may return a different Sprint-context result through the same passed Action2 route, and the accepted `compatible * (C/B)` composition preserves that difference. EV-402 generalizes this across nonhuman families: Sabertooth and Wolf showed Power Hit `1.0` versus Sprint live Hit `1.5`, while Troll remained `1.0` for both. Therefore G3AB must not copy a universal Sprint multiplier; it preserves the live result. Do not add `Sprint_BaseSpeed`, `Sprint_ReferenceHitBaseSpeed`, or rewrite Action2 to Action9 absent contradictory evidence.

Speed v2 production source, resolved-profile identity, neutral shipping INI and intended-stack runtime acceptance are CLOSED/PASS through EV-410. Broad additional creature calibration remains optional future coverage rather than a Speed closure requirement.

Recover follows the effective Hit speed; no separate user-facing `RecoverSpeed` key is planned.

Raise AddRaise is now the single active feature responsibility. Preserve the closed Speed architecture unless contradictory evidence appears. Architecture/sequencing rationale: ADR-0004 + ADR-0005 + ADR-0006 + ADR-0008 + ADR-0011.

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

`gEUseType_Fist` / raw8 uses a native target-directed body-contact opportunity mechanism. The permanent owner is `Raw8FistCollision`.

Current production architecture after EV-353:

```text
unmarked raw8
-> completely native

marked raw8 C1
-> initial native opportunity CLOSED

accepted FIST
-> one pending authored opportunity OPEN

native miss while pending
-> restore native one-shot eligibility
-> keep authored opportunity pending

first exact native Game+0x16E348 raw8 contact dispatch
-> consume opportunity before gameplay outcome interpretation

later FIST in same C1
-> reopen one opportunity, never stack

same-C1 Action/family/phase transport
-> preserve opportunity

exact C1 finalization/replacement
-> close unused opportunity
```

Gothic remains authoritative for target selection, contact geometry, block/parry, immunity, reactions and HP damage. The API transport happens to be `gCEntity::OnDamage`, but production raw8 uses only exact dispatch entry as the contact-resolution fact and never interprets the result as “damage succeeded.”

The opportunity lifetime is actor/C1/source/SPU scoped. Timing persistence is a separate animation/timing substate and may retire without consuming the logical opportunity. EV-354 directly protects Sprint-origin Action9 -> Action2 continuation inside one C1; in the tested Sabretooth route both action states use the same PowerAttack-named motion rather than separate Sprint/Power animation assets.

Production exclusions remain: no FIST_OFF, no `ClearTriggeredList`, no target/visited list, no collision-group window, no custom/direct damage, no species rules, no polling/timers, and no raw55/equipped mechanism sharing.

Full authority: `COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md`.

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

For equipped markers, permanent `EquippedSprintCollision` support is CLOSED/PASS through EV-329 under ADR-0003. The rule preserves immutable Sprint origin across only the exact same-C1 Action9 -> Action2 continuation; a new true-Power execution never becomes Sprint. Complete-motion required-source validation remains fail-closed and generic RIGHT/LEFT/BOTH/OFF semantics remain owned by `FrameCollisionMarkers`.

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

## 7. Collision Architecture — Production Integrated

The collision architecture was first boundary-refactored in Stage A and later migrated into the production target. Production integration closed/PASS at EV-390.

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

Current production ownership:

```text
Raw8FistCollision
  raw8 Normal+Power+Quick+Sprint FIST family policy
  marked-execution state
  initial latch close + accepted-marker rearm
  threshold/timing permission and exact one-shot decision

PhysicalFistCollision
  raw55 Normal/Quick/Power/Sprint family policy and lifecycle-specific source behavior

AttackMotionRouting
  proven factual Hack optional motion-substitution policy

CollisionLifecycleGuard
  C1 policy/repair decision and result classification

CollisionSourceOperations
  physical equipped source mutations, including terminal 7 -> 5 repair
```

`RunScriptFunctionScope` remains in `EngineBridge` because its lifetime is hook-invocation transport, not feature policy. Current action/phase family resolution remains in `FrameCollisionMarkers` because it is part of marker ownership; no separate family module is planned.

Unknown/new mechanisms follow `FEATURE_DEVELOPMENT_METHOD.md`: dedicated temporary probe first, then the smallest proven permanent owner after research closure.

Current architecture is owned by this file plus `COLLISION_REFERENCE.md`, `COLLISION_LIFECYCLE.md`, `COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md`, `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`, and `COLLISION_DIAGNOSTICS.md`; completed redesign/migration plans are archived provenance.

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

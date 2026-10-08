# Gothic 3 Animation Behaviors — Design

**Status:** Canonical project architecture  
**Updated:** 2026-10-08
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

`Script_G3AnimationBehaviors` is the general animation-behavior layer for Gothic 3. The first-release production set — authored-frame Collision, Speed v2, additive Raise, configurable attack Movement, and the narrow player bad-block protection — is CLOSED/PASS through EV-454 and promoted to stable `main @ 08a0bd8fcf42173088e233e09b706a80da882070` after EV-455/EV-456 review. No feature responsibility is currently active. Future independent domains may include target acquisition, climbing, and other deliberately adopted animation/gameplay behavior modules.

This file owns overall integration, subsystem responsibilities and the current profiles/Speed/Raise/Movement/player-protection contracts. [COLLISION_REFERENCE.md](COLLISION_REFERENCE.md) is the single maintained collision-specific owner for behavior, lifecycle, diagnosis and reopening. [SOURCE_HOOK_GUIDE.md](SOURCE_HOOK_GUIDE.md) owns exact engine facts; release architecture owns product separation; proof routes through [EVIDENCE_INDEX.md](EVIDENCE_INDEX.md).

---

## 1. Governing Principles

1. Prefer Gothic native action/phase/UseType/current-motion semantics over filename heuristics when available.
2. Preserve Gothic's own animation resolution whenever possible.
3. Custom behavior is explicit opt-in: config for Raise/speed/movement, exact reserved markers for collision; the narrow bad-block protection is automatic only on its proven player Action4/5/10 Hit condition.
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

Current shared profile identity (ADR-0011):

```text
normalized skeleton AnimationFamily
+ ResolvedLeftAnimationToken
+ ResolvedRightAnimationToken
```

`BehaviorProfiles::TryBuildRuntimeKey` gets the skeleton family and resolves `Entity.GetAni(action, Hit)` at the request boundary, extracting left/right animation tokens. Raw equipped UseType alone does not select profiles. Native Axe resolving `None_2H` shares 2H settings; Axe Separation resolving `None_Axe`, Rapier resolving `None_Rapier`, and Zombie skeleton family select their resolved identities without weapon/mod-specific C++ branches. Shared resolved animations intentionally share settings. No user-facing pose split.

`BehaviorProfiles::Load` reads `Gothic 3/Ini/G3AnimationBehaviors.ini` once at startup into normalized memory. Duplicate normalized identities become ambiguous and are removed; missing/invalid profiles or per-attack settings preserve compatible behavior. Runtime does no per-attack INI I/O. Actual shipped settings/help are in [the shipping INI](../src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini), which documentation maintenance does not edit.

| Surface | Current configured scope / meaning |
|---|---|
| `<Attack>_ReferenceHitBaseSpeed`, `<Attack>_BaseSpeed` | Normal, Quick, Power, Pierce, Hack, SimpleWhirl, Whirl; positive finite native calibration B and authored C. |
| `<Attack>_AddRaise` | Only Normal, Quick, Whirl; On adds a Gothic-resolved Raise; missing/Off adds nothing. Internal `raiseOverride` is active generic storage, not public scope. |
| `<Attack>_MovementOverride` | Same seven attack settings; Off inactive, finite nonnegative number active, including zero. |

Quick factual R/L Actions4/5 share `Quick` settings; Action3 is a selector, not a proven playback-speed route. Factual Sprint9 inherits Power settings on its proven passed-Action2 route (ADR-0009), without separate Sprint keys. This is profile inheritance, not equal live speed: context can make Power1.0 versus Sprint1.5 (EV-401–402). Family and resolved-token dimensions compose; raw UseType and serialized Fist alone do not choose a collision mechanism.

Proof: EV-406–410; rationale ADR-0005/0006/0009/0011. Historical schema wording in earlier ADRs remains qualified provenance.

---

## 3. Raise, Speed, and Movement

### Raise

`AttackRaise::RunCombatMove` owns opt-in synthetic Raise for Normal1, factual QuickR/L4/5 and full Whirl10. At the already-owned factual Hit CombatMove boundary, store the exact incoming Hit and request the same action/target with phase `Raise` and **the same already-composed Hit AniSpeedScale**. Gothic resolves assets/pose normally; service Raise, then the exact stored Hit. Do not construct filenames, invent Quick R/L selection, query Speed again or disable existing native Raise. The former high-level `PS_Melee_Attack` / `PS_Melee_WhirlAttack` prepend hooks are retired; all three custom routes use CombatMove (EV-415–416).

The minimal SPU continuation survives native asynchronous resumes: null args service the persisted instruction without restarting Raise/Hit. Invocation-held shared state keeps stored arguments alive under reentrancy, while FullStop, AISetState cancellation and mismatched requests prevent resurrection after native replacement. Collision wraps each actual native invocation independently. Raise never repairs destroyed gameplay state or replaces player bad-block/C1 safety.

Normal synthetic Raise and stored Hit would otherwise independently reclassify direction. `PreserveNormalContinuationDirection` captures Gothic's exact first native direction bCString and gEDirection at `Game+0x16B056`, then restores only those facts for the stored Normal Hit at that same GetAniName call. It does not recreate geometry/filename policy or apply to Quick/Whirl/Power/Hack. Direction state retires with the continuation (EV-423–428).

Public scope excludes Power/Pierce/Hack/SimpleWhirl/Finishing/Sprint AddRaise keys. Native Power Raise has separate Speed composition below. Matching Raise assets are required for intended authoring; exact name/pose examples belong to [ANIMATION_RULES §5.1](ANIMATION_RULES.md#51-raise-filename-patterns). Native Raise/Hit suffixes can differ: do not blindly rename Hit to Raise.

Acceptance is representative: EV-411 Off, EV-412 sequencing/compatibility, EV-420–422 phase speed, EV-427 direction, EV-429 Normal/QuickR+L/full-Whirl scope, EV-430 pose-changing and partial Shield+1H Quick asset coverage. Missing matching Raise routes remained functional in EV-430, but the exact fallback mechanism was not instrumented. Not every family/resource is proven. Rationale: ADR-0004/0005/0006/0008/0011; transport facts in hook guide §3.

### Speed

`AttackSpeed::ComposeCompatibleSpeed` substitutes a configured native base contribution while preserving the live compatible result:

```text
B = native Gothic ReferenceHitBaseSpeed for this exact route
C = configured BaseSpeed
compatible = B * M
configured = compatible * (C / B) = C * M
```

B is native calibration, not a New Balance value or tuning control. The live `Script_Game+0x42A0` owner runs exactly once with original caller action; production composes downstream at the 12 Hit caller sites and separate Power Raise caller `+0x47D51` listed in hook guide §§3,3A. It never takes over the entry, rewrites Action2 to Sprint9 or copies New Balance policy. Missing/invalid settings, nonfinite arithmetic and positive underflow preserve compatible speed. Structural changes to a mod's route require evidence, not silently redefining B.

Custom AddRaise inherits incoming composed Hit speed; native Power Raise preserves its live phase base and applies Power C/B, e.g. compatible Raise1.5*M versus Hit1.0*M. No separate RaiseSpeed/ReferenceRaiseBaseSpeed/RecoverSpeed keys. Native Recover follows effective Hit where proven; Pierce already propagates configured speed through visible Raise and gets no additional Raise composition. SimpleWhirl has no added Raise work absent a factual route.

Hack14 is the deliberate route-neutral exception: `TryComposeHackCombatMoveSpeed` composes existing Hit-profile C/B once on Raise/Hit/Recover requests **after** the live compatible owner filled AniSpeedScale. Bridge uses a local request copy between Raise and the collision invocation wrapper. Former native Hack patches `+0x42FF4/+0x431B4/+0x432EB` are removed; no extra speed-owner call, Speed state/cache or AttackCollision DLL hook. Null/resume/FullStop paths pass unchanged. Finishing15 remains excluded even when it shares Hack's animation asset (EV-398–399/417–422).

Native/contextual Sprint results can differ from ordinary Power through the same shared caller; preserve that live difference, never apply a universal Sprint multiplier. Ordinary zero stamina did not materially slow Hack in tested native controls; New Balance alternative no-attack stamina restrictions remain authoritative. Closure: Speed v2 EV-410; native/intended-stack phase/Hack correction EV-420–422. Broad creature calibration is optional, not a reopened release gate. Rationale: ADR-0004/0008/0009/0011.

### Movement

`AttackMovement::Compose` authors an **absolute nominal CombatMove Hit travel distance**, using the same resolved profiles/seven attack settings. Off leaves the compatible vector untouched; numeric0 actively clears it before duration requirements. For positive distance:

```text
native / New Balance final compatible movement vector
-> preserve final direction
-> effective duration T = primary motion maxTime / composed AniSpeedScale
-> replacement magnitude = MovementOverride / T
-> native EnableCombatMovementFromSPU unchanged
```

Bridge inserts after compatible policy at `Game+0x16B8A9`, immediately before `+0x16B8B7`. Unsupported/non-Hit requests, missing profiles and positive-distance invalid timing/zero-or-invalid direction preserve compatible behavior. A configured distance does not manufacture direction: zero-authored-vector Rapier Quick is the accepted limitation. No filename parsing, asset edits or New Balance detection is needed. Native obstacle/ledge/target stopping and interruptions can shorten realized travel; this is not universal root-motion control. Speed changes commanded velocity via duration, not nominal requested distance.

Mechanism/seam proof EV-434–440; source/runtime/name acceptance EV-441–445. Hook guide §3B owns native/New Balance address facts. Broader root-motion or special Jump/Finishing routes require separate scope decisions.

---

## 4. Authored-Frame Collision

[Collision reference §§1–4](COLLISION_REFERENCE.md#1-accepted-scope-and-exclusions) owns the accepted marker/source/family contracts. Shared infrastructure scans exact current motion, recognizes reserved effects and uses C1 occurrence/dedupe/budgets. Equipped, raw8 and raw55 remain distinct production mechanisms selected from factual sources, not serialized animation tokens. General asset authoring stays in ANIMATION_RULES.

Motion routing is separate: `AttackMotionRouting` may select an existing Hack14 asset at the resource query; Finishing15 stays native. Resolved asset changes can affect native movement and marker presence. Configuration changes do not create collision ownership on an unmarked replacement.

## 5. PhysicalFist/raw55 Integration

`PhysicalFistCollision` receives raw55 marker dispatch and narrow native setter/Normal-clear facts through Bridge; it does not own raw8 or generic equipped policy. Exact eligibility, operation tables, native fallback and evidence limits belong only to [reference §4.2](COLLISION_REFERENCE.md#42-raw55--exact-first-opening-second-clear-only). Native cleanup and C1 backup remain independent of contact timing.

## 6. Collision Lifetime and Cleanup

`CollisionLifecycleGuard` supplies monotonic C1 and exact-source obligations; source helpers perform bounded physical operations. Raw8 owns its latch/opportunity retirement separately. [Reference §5](COLLISION_REFERENCE.md#5-c1-lifecycle-and-must-preserve-safety) owns native-first finalization, liveness, generation safeguards and terminal-repair limits. Raise cancellation and player protection must preserve these facts rather than become lifecycle authority.

## 7. Shared Production Integration

`EngineBridge` owns each physical hook once, captures native facts and delegates policy. Startup is RuntimeClock → BehaviorProfiles load → Bridge install. Actual CombatMove order is AttackRaise → Hack Speed adapter → collision invocation scope → native original once. AISetState cancels Raise, lets native state replacement run, then retires/finalizes captured collision generation state. `RunScriptFunctionScope` remains invocation transport, not a permanent execution ID. See [reference §2](COLLISION_REFERENCE.md#2-production-owners-and-native-event-order) and targeted source for entry points.

A Speed change affects duration and marker timing; Raise adds actual invocations; Movement changes compatible contact geometry; bad-block prevents one destructive player branch. None owns collision damage policy. Validate the smallest affected assembled routes after authorized changes. Unknown mechanisms follow FEATURE_DEVELOPMENT_METHOD's isolated-probe boundary.

## 8. Diagnostic / Release Integration

Production is mechanically diagnostics-free under GOTHIC_SCRIPT_RELEASE_ARCHITECTURE. [Collision reference §6](COLLISION_REFERENCE.md#6-diagnose-with-the-smallest-sufficient-facts) owns collision symptom interpretation, evidence limits and targeted escalation; release architecture owns CORE/DEEP policy, dependency direction, runtime exclusivity and generic gates. Historical collision twins omit current profiles/Speed/Raise/Movement/integrated bad-block, so cannot certify the full assembled product. Existing observational production evidence remains legitimate; new instrumentation is conditional on a concrete unresolved question.

---

## 9. AttackContinuationProtection

The first-release player bad-block protection is **production-integrated and closed**. It remains architecturally separate from collision cleanup and does not use a separate gameplay module or persistent timer state.

Production ownership is `EngineBridge::EvaluatePlayerBadBlockDuration` / `PlayerBadBlockDurationAdapter` at the exact player timeout call seam. Installation requires the tested call-byte/IAT target guard (`+0x633BF`, getter slot `+0xE4990`) and a non-null getter; hook guide §6 owns native details:

```text
Script_Game +0x633BF
-> call the native/current DurationPressedMSecs getter exactly once

if raw > 2500
AND receiver-owning actor == player
AND factual action in {QuickAttackR(4), QuickAttackL(5), WhirlAttack(10)}
AND factual phase == Hit
-> return 2500 for this call only

otherwise
-> return raw unchanged
```

This is **stateless branch-local deferral**, not exact pause/resume. Native held-input time continues advancing, so the native timeout may become effective immediately after the protected Hit ends.

The accepted first-release scope deliberately excludes generic selector Action3, Pierce/Action11, Hack/Action14, Finishing/Action15, Normal, Power, SimpleWhirl, Sprint, and the separate NPC parade timeout. No actor/timer map, gameplay token, global getter/IAT mutation, broad `FullStop`/`SetState` suppression, or collision-guardian coupling is permitted by the accepted design.

EV-449–EV-450 provide the causal A/B proof; EV-451–EV-452 support the exclusions; EV-453 accepts the diagnostics-free standalone minimum; EV-454 accepts the same mechanism integrated into production after final release-candidate smoke.

Exact remaining-time pause and the separate NPC timeout remain optional future research only. `CollisionLifecycleGuard`/C1-R1 remains an independent collision fail-safe, not part of this protection mechanism.

---

# Gothic 3 Animation Behaviors — Source & Hook Guide

**Status:** Canonical practical source/hook lookup guide  
**Updated:** 2026-09-29

## Purpose

Use this file for targeted source/API/RVA/hook questions. It is a lookup guide, not chronology or current continuation state.

Current task: `SESSION_ENTRYPOINT.md`.  
Evidence: `EVIDENCE_INDEX.md`.  
Cleanup RVAs/stacks: `COLLISION_CLEANUP_CALLSITE_MAP.md`.

---

## 1. Source Roles / Research Order

Use in this order:

```text
exact runtime question
-> official SDK declaration/API
-> smallest known-good hook/example
-> relevant Jackydima/New Balance reference
-> tested binary reference/static inspection
-> controlled runtime evidence
-> animation asset evidence
-> smallest new diagnostic only if causality remains unresolved
```

Primary sources:

- project repository — current behavior/docs/evidence;
- `thirdparty/gothic3sdk` pinned official SDK — declarations/signatures/enums/wrappers;
- `references/jackydima-gothic3sdk` — practical New Balance/AttackCollision/animation reference, not automatically native truth;
- `tcholti/Gothic3_Binary_Reference` — tested-build disassembly/reference slices.

Prefer converging evidence; addresses below are build-specific.

---

## 2. High-Value Search Terms

### Native semantics

`GameEnum.h`: `gEAction`, `gEPhase`, `gEAniState`, `gEPose`, `gEUseType`, `gEDirection`, `gEHitDirection`.

### Script / CombatMove

Search SDK wrappers for:

```text
gCScriptProcessingUnit
gCScriptRoutine_PS
gScriptRunTimeSingleState
RunScriptFunction
sAICombatMoveInstr
sAICombatMoveStart
sAICombatMoveItlLoop
sAICombatMoveStartRecover
m_StateStack
m_pfInstrCallback
m_pArguments
StateTime
StatePosition
AIFullStop / FullStop
AISetState / SetState
GetPrimaryPoseExt
PropertyAction
```

Durable attack execution identity is the plugin C1 generation, not a raw state-stack or arguments pointer.

### Collision / damage

Search for:

```text
OnAI_Attack
OnAI_QuickAttack
OnAI_PowerAttack
OnAI_PierceAttack
OnAI_SimpleWhirl
OnAI_WhirlAttack
OnAI_HackAttack
SetCollisionGroup
ClearTriggeredList
eCTrigger_PS / TouchDamage
EntitiesVisited / EntitiesVisitedCount
ResetOnUntouch
gESlot_LeftHand / gESlot_RightHand
gCEntity::OnDamage
```

### Frame effects

Search for `UpdateFrameEffects`, `GetFrameEffectList`, `eSFrameEffect`, `StartEffect` and motion-resource/actor accessors.

### Speed / timing

Search for `GetAnimationSpeedModifier`, `AniSpeedScale`, `GetMaxTime`, `GetPlayTime`, `PlayMotion`.

### Movement / displacement

Search around CombatMove reach/vector/movement calls, motion/root translation, actor/world transforms, movement instructions and animation descriptors. Do not assume root motion is the movement owner until static/runtime evidence proves it.

---

## 3. Tested RVA Index

### Animation / CombatMove

| Purpose | Module + RVA | Meaning |
|---|---:|---|
| `GetAnimationSpeedModifier` | `Script_Game +0x42A0` | live native/compatible speed-policy owner; production Speed deliberately does **not** own this entry |
| CombatMove animation-string call | `Game +0x16B065` | narrow substitution point used by New Balance |
| CombatMove reach/vector call | `Game +0x16B8A3` | factual reference surface for future movement/displacement research; exact semantic ownership still open |
| CombatMove movement call | `Game +0x16B8A9` | factual reference surface for future movement/displacement research; exact semantic ownership still open |
| full-Whirl break-block call/test | `Script_Game +0x4DF8C / +0x4DF92` | incomplete CombatMove suspends ScriptFunction |
| full-Whirl ordinary cleanup continuation | `Script_Game +0x4E03C` | resumed path reaches native cleanup |
| GetUp pre-Combat offense | `Script_Game +0x41CA6` | legitimate offense can precede CombatMove |
| GetUp later CombatMove | `Script_Game +0x41D5A` | same outer ScriptFunction reaches CombatMove |
| GetUp ordinary cleanup | `Script_Game +0x41E10` | tested cleanup region |
| `GetAniName` | `Game +0x16F840` | animation-name lookup; fifth argument is the direction bCString serialized into the resource name |
| CombatMove `GetAniName` call | `Game +0x16B056` | production Normal AddRaise direction-preservation boundary: capture Gothic-native direction on synthetic Raise, restore/reuse it for the stored Action1 Hit only; runtime accepted EV-427 |
| CombatMove direction init | `Game +0x16AEDD` | local direction string initializes to exact `Fwd` |
| CombatMove Normal direction dispatch | `Game +0x16AF3C` | Action1 enters Fwd/Left/Right classification |
| CombatMove Right / Left selection | `Game +0x16AF61 / +0x16AF76` | exact `Right` / `Left` bCString selection |
| CombatMove Navigation direction write | `Game +0x16B00E` | writes selected `gEDirection` to current-animation direction before GetAniName |
| `GetAniEx` | `Script +0x15C10` | animation query |
| motion data string | `Game +0xD97D5` | motion resource string |
| cached motion actor | `Game +0xDA344` | animation actor |

### Speed v2 proven Hit consumers

Production Speed leaves live `+0x42A0` ownership untouched. The production caller-side Hit set is the table below. Hack is intentionally absent because EV-418/EV-419 move factual Action14 Raise/Hit/Recover composition to the shared CombatMove request boundary.

| Attack route | Script_Game caller RVA | Factual caller action / note |
|---|---:|---|
| Normal | `+0x383F0` | Action1 / Hit |
| Quick carrier | `+0x38E9D` | factual Action4/5 carrier / Hit |
| Quick carrier | `+0x38F22` | factual Action4/5 carrier / Hit |
| Quick carrier | `+0x3937D` | factual Action4/5 carrier / Hit |
| Quick carrier | `+0x39402` | factual Action4/5 carrier / Hit |
| Quick route | `+0x48677` | PropertyAction after Action3 selector resolves to Action4/5 / Hit |
| Pierce | `+0x47328` | Action11 / Hit |
| Pierce | `+0x4770F` | Action11 / Hit |
| Pierce | `+0x4786F` | Action11 / Hit |
| Power + Sprint-shared transport | `+0x47F6C` | caller hard-passes Action2 / Hit; factual actor may remain Action2 **or Action9 Sprint** |
| SimpleWhirl | `+0x4C6FA` | factual Action6 carrier / Hit |
| Whirl | `+0x4DF1F` | Action10 / Hit |

Raise implication: generic Quick / Action3 is still selector-level before the downstream factual boundary above. For AddRaise, G3AB must consume Gothic's already-selected factual Action4/5 rather than inventing an R/L chooser.

Related Power route:

```text
Script_Game+0x47D51 = factual Power Raise speed consumer
```

It is the production Power Raise composition caller; it is separate from the 12 Hit callers above.

### Motion lifecycle

| Purpose | Module + RVA |
|---|---:|
| high `PlayMotion` | `Engine +0x30860` |
| high `StopMotion` | `Engine +0x30980` |
| high `StopAtLoopEnd` | `Engine +0x309D0` |
| wrapper `PlayMotion` | `Engine +0x476F0` |
| wrapper `StopMotion` | `Engine +0x47910` |
| wrapper `StopAtLoopEnd` | `Engine +0x479C0` |

### CombatMove / state

| Purpose | Module + RVA | Constraint |
|---|---:|---|
| `gCScriptRoutine_PS::AIFullStop` | `Game +0x164430` | invokes current persisted callback with `fullStop=true` |
| `AIStopCombatMove` | `Game +0x1644D0` | full-stops only current CombatMove callback |
| `sAICombatMoveInstr` | `Game +0x1696E0` | persisted async CombatMove instruction |
| `sAICombatMoveStart` | `Game +0x16ABB0` | CombatMove start |
| `sAICombatMoveItlLoop` | `Game +0x16DD00` | iterative loop; also contains proven raw8 Fist path |
| `sAICombatMoveStartRecover` | `Game +0x16E360` | Recover start; not universal weapon cleanup authority |
| `ProcessScript` | `Game +0x16F120` | generic dispatcher, not attack ownership |
| `AISetState` | `Game +0x164320` | destructive state replacement; C1 finalizes after original returns |

### Trigger / TouchDamage

| Purpose | Module + RVA | Meaning |
|---|---:|---|
| `eCTrigger_PS::ClearTriggeredList()` ALL | `Engine +0x7DDA0` | public no-argument clear of trigger visited bookkeeping; factual Normal between-contact reset API in EV-290 |
| `eCTrigger_PS::ClearTriggeredList(eCEntity*)` | `Engine +0x7DDF0` | entity-specific overload; distinct from EV-290 ALL clear |
| `PSTouchDamage::ClearTriggeredList()` wrapper | `Script +0x13720` | tested wrapper tail-jumps to engine trigger clear |
| Normal native ALL-clear caller | `Script_Game +0x386C6` | factual caller RVA for the EV-290 exact RIGHT raw55 between-contact clear |

EV-290 observed the exact current RIGHT TrollFist/raw55 trigger with `PC_Hero` still present/count1 before the native ALL clear and absent/empty afterward. This identifies the reset operation and caller; it does not by itself prove that the clear is causally required for the later second damage opportunity.

### Script dispatch / known bad-skip path

| Purpose | Module + RVA |
|---|---:|
| `RunScriptState` | `Game +0x1603D0` |
| `RunScriptFunction` | `Game +0x1604E0` |
| registered ScriptFunction call | `Game +0x1605E9` |
| first instruction after call | `Game +0x1605EB` |
| completed-frame removal helper | `Game +0x1627B0` |
| tested legitimate-reaction `FullStop` | `Script_Game +0x2D0F2` |
| additional reaction AIFullStop caller | `Script_Game +0x2B8CB` |
| player Use2 helper | `Script_Game +0x62FF0` |
| common higher caller return | `Script_Game +0x61866` |
| tested bad held-Use2 `FullStop` | `Script_Game +0x633F1` |
| immediate destructive `SetState` | `Script_Game +0x63409` |

Tested bad-skip causal class:

```text
attack ScriptFunction suspended at CombatMove break block
-> +0x633F1 FullStop
-> active CombatMove terminated
-> +0x63409 SetState
-> AISetState replacement clears old continuation
-> ordinary attack cleanup continuation cannot resume
```

Held Use2 / ~2500 ms is a test trigger, not collision ownership.

---

## 3A. Speed v2 reusable engine facts

### Caller-side compatibility boundary

The accepted Speed architecture uses the proven Hit caller sites above plus the factual Hack request boundary below.

```text
caller prepares factual action/Hit request
-> G3AB call-site thunk captures caller action
-> thunk calls the live Script_Game+0x42A0 owner exactly once with the original caller action
-> live Gothic/New Balance/compatible owner returns compatibleSpeed
-> G3AB optionally applies configured C/B composition
-> original caller receives the composed result
```

This deliberately leaves `Script_Game+0x42A0` entry ownership to the live compatible stack and avoids copying New Balance policy. EV-418/EV-419 extend the same principle to pinned AttackCollision Hack without hooking the third-party DLL: both native and replacement states first compute the live speed normally, then factual Action14 Raise/Hit/Recover requests are composed once at the existing CombatMove boundary. The former native Hack caller hooks `+0x42FF4/+0x431B4/+0x432EB` are not installed in production.

### Hack route-neutral compatibility boundary

Native Script_Game and pinned AttackCollision both produce factual Action14 CombatMove requests whose `AniSpeedScale` already contains the live compatible result. Production therefore uses:

```text
live native/New Balance Hack speed query
-> factual Action14 Raise / Hit / Recover request
-> AttackRaise pass-through
-> stateless Hack Speed adapter applies existing Hit-profile C/B once
-> unchanged Collision invocation wrapper
-> original CombatMove
```

The adapter uses a local request copy, does not call the speed owner again, and excludes factual Finishing / Action15 before profile lookup. FullStop/null request/null-SPU and null resume paths pass unchanged. Proof: EV-417–EV-419.

### Native reference and algebra

For a configured profile:

```text
B = factual native Gothic Hit base for that exact attack/loadout route
C = configured authored BaseSpeed
compatibleSpeed = B * M
```

where `M` means the combined relative effect already present in the live compatible result at this boundary. G3AB does not need to identify individual modifiers.

Composition:

```text
compatibleSpeed * (C / B)
= (B * M) * (C / B)
= C * M
```

Therefore `ReferenceHitBaseSpeed` is a native Gothic calibration fact required by this safe downstream mechanism. It is not a New Balance value and is not a gameplay tuning value. Third-party changes already present in `compatibleSpeed` remain relative effects if they are multiplicative with respect to the native base.

If a future mod changes the speed path structurally rather than as a compatible relative effect, that route requires evidence; do not silently reinterpret the third-party result as the native reference.

### Evidence-bounded native calibration controls — EV-396

| Exact tested family / loadout | Factual route / phase | Native speed |
|---|---|---:|
| Hero / None+1H | Normal Hit | 0.6 |
| Hero / None+1H | QuickR Hit / QuickL Hit | 1.0 / 1.0 |
| Hero / None+1H | Power Raise / Power Hit | 1.5 / 1.0 |
| Troll / PhysicalFist+PhysicalFist | Normal Hit | 1.0 |
| Troll / PhysicalFist+PhysicalFist | QuickR Hit / QuickL Hit | 1.0 / 1.0 |
| Troll / PhysicalFist+PhysicalFist | Power Hit | 1.0 |
| Troll / PhysicalFist+PhysicalFist | factual Sprint, shared-Power Raise / Hit | 1.0 / 1.0 |

These are evidence-bounded native-only controls, not a complete native catalogue. Do not generalize them to untested families/loadouts. PhysicalFist here is factual raw55, not a source classification inferred from the serialized `Fist` token. `ReferenceHitBaseSpeed` is native Hit base **B**; New Balance/compatible modified live values are not native B. Raise observations are retained for later research, not as `ReferenceHitBaseSpeed` or current Hit-hook scope; Raise remains PAUSED.

Proof: EV-396, retrieved through [EVIDENCE_INDEX.md](EVIDENCE_INDEX.md).

### Power / Sprint shared timing route

Runtime causal evidence on Goblin, Troll and Sabertooth proves:

```text
factual actor current action = Action9 Sprint
caller at Script_Game+0x47F6C = Action2 Power / Hit
current movement = PowerAttack-named animation
actor remains Action9 before and after the live +0x42A0 call
```

Thus Speed authoring intentionally treats Sprint as inheriting the Power timing profile on this proven route. Collision may still distinguish Sprint where collision lifecycle semantics require it.

Native-only Troll control further proves on the tested Troll/Fist Power/Sprint route:

```text
native compatible Hit speed = 1.000000
```

while the New Balance stack previously returned `1.500000` on the same shared route. The native `1.0` is the calibration `B`; the New Balance increase belongs to the live compatible result, not to `ReferenceHitBaseSpeed`.

Evidence route: ADR-0004, ADR-0009, EV-391–EV-395, Sprint shared-Power causal probe/runtime logs.

---

## 3B. Attack movement / displacement mechanism

EV-434 statically closes the principal CombatMove movement path on the tested build.

Native fresh-request path:

```text
selected motion resource
-> parse filename word 13 as D_filename
-> T = primary animation max time / request AniSpeedScale
-> normalize SPU.m_DirectionVec
-> Game+0x16B8A3 scales vector by D_filename / T
-> Game+0x16B8A9 loads CharacterMovement receiver
-> Game+0x16B8B7 calls EnableCombatMovementFromSPU
-> CharacterMovement copies the vector and enables combat movement
-> controlled translation later adds the stored vector to current velocity
```

Important address correction:

| Address | Established meaning |
|---|---|
| `Game+0x16B8A3` | native `bCVector::Scale(float)` using filename distance / nominal animation duration |
| `Game+0x16B8A9` | loads CharacterMovement receiver; project-pinned New Balance inserts `CombatMoveScale` here |
| `Game+0x16B8B7` | actual CombatMove-specific `gCCharacterMovement_PS::EnableCombatMovementFromSPU` call |

Native `Script_Game+0xAA270 GetCombatMoveLength` is **not** the native movement-distance owner on this tested path: the native Hit-side caller discards its return value, and the selected resource filename independently supplies movement distance.

Project-pinned New Balance reference:

`references/jackydima-gothic3sdk @ 316d32406a133f8884e7e302752c35f66b4f54fc`

Its `CombatMoveScale` runs after native filename scaling and before `Game+0x16B8B7`. For factual Hit requests with an eligible callback result it normalizes the existing direction and replaces magnitude using its action/skill distance policy plus `ATTACK_REACH_MULTIPLIER`. A `-1` callback result preserves the native vector; Raise/Recover therefore remain on native movement calculation in this reference.

EV-437 scope clarification: New Balance's replacement covers **every ordinary melee attack action currently represented by G3AB BehaviorProfiles**: Normal, Quick/QuickR/QuickL, Power, SimpleWhirl, Whirl, Pierce and Hack; Sprint is also covered. Special JumpAttack/Action12 and FinishingAttack/Action15 are not in the pinned replacement table and remain separate future-scope questions.

Speed relationship:

```text
T = maxTime / AniSpeedScale
velocity = chosenDistance / T
nominal uninterrupted travel = velocity * T = chosenDistance
```

Thus Speed changes commanded velocity required to cover a chosen nominal distance over the animation duration; it does not inherently multiply nominal distance. Realized entity displacement may still be shortened by target stopping, interruptions, terrain/movement validity or phase timing.

The selected animation's numeric filename distance field is a **causal native movement input**, not descriptive metadata. Motion routing may therefore alter native movement by changing the resolved resource.

EV-438 selects an **absolute-distance** candidate rather than the earlier compatible-vector multiplier:

```text
after New Balance/native compatible vector policy
-> narrow insert immediately before Game+0x16B8B7
-> if Movement Off: leave vector untouched
-> if Movement configured:
     T = current primary max time / already-composed AniSpeedScale
     preserve final direction
     set magnitude = configuredMovement / T
-> untouched native EnableCombatMovementFromSPU call
```

This requires no filename parsing and no New Balance detection. Do not scale at `+0x16B8A3` as the production override seam when New Balance compatibility is required; New Balance may subsequently replace that magnitude.

Author/runtime reconciliation in EV-435 establishes the practical phase behavior needed for this feature: ordinary attack Hit resources carry the nonzero combat-movement value while Raise/Recover are normally zero, and CombatMove translation is applied during the value-carrying phase subject to native ledge/obstacle/target stopping rules. A separate runtime probe is therefore not required merely to re-prove that basic ownership.

Still do **not** claim universal absence of independent animation/root translation for every asset/family. That negative claim is unnecessary for controlling the proven CombatMove movement mechanism, and this feature should not be labeled root-motion control.

Distribution constraint: changing the filename field itself requires animation-resource replacement/repacking under Gothic's archive precedence. Runtime displacement control is intended to avoid that installation burden.

## 4. Production raw-8 Fist Lookup

Raw-8 Fist is a native body-contact / hit-opportunity mechanism, separate from equipped `Item_Attack` collision and from raw55 PhysicalFist. This project does not own gameplay damage policy.

### Generic-human static/runtime path

```text
sAICombatMoveItlLoop                              Game +0x16DD00
SPU+0x164 permission/latch check                  Game +0x16DFB9
GetMaxTime(motion 0) setup/call                   Game +0x16E160..+0x16E164
native threshold multiplier double                Game +0x308308
GetPlayTime(motion 0) exact call site             Game +0x16E180
comparison                                         Game +0x16E18C..+0x16E190
below threshold -> common exit                    Game +0x16E352
native attempt latch write = 1                    Game +0x16E1A3
observed native gCEntity::OnDamage entry boundary   Game +0x16E348

Between `Game+0x16E1A3` and the final call returning at `+0x16E348`, the tested binary performs multiple additional target/contact checks with branches to the common `+0x16E352` exit. Therefore `+0x16E1A3` is attempt/latch consumption, not accepted-contact consumption.

Candidate TouchDamage observation surfaces:
- `gCTouchDamage_PS::CanBeActivatedNow` — `Game+0x692F0`;
- `gCTouchDamage_PS::TriggerTarget` — `Game+0x693B0`.

EV-351 runtime result: the exact current raw8 Fist source produced neither callback on six tested Gargoyle Power invocations, including three close/contact cases that reached the generic `Game+0x16E348` path. Therefore these two virtual boundaries are ruled out as the raw8 contact-consumption boundary on that tested route. Direct inherited `EntitiesVisited` behavior outside those callbacks remains unresolved.
```

Observed generic-human threshold multiplier is approximately `0.6000000238`; with the tested `0.6800000072` max time this produced ~`0.4080000205` seconds.

Special branch warning:

```text
[SPU+0x154] == 0x39
```

has a separate native arm and is **not** covered by the generic-human model above.

### Production hook transport

The production marker mechanism keeps one exact call-site hook at `Game +0x16E180`.

```text
accepted raw8 FIST
-> create or refresh ONE persistent pending opportunity for exact actor/C1/source/SPU
-> call native GetPlayTime at Game+0x16E180; while pending, repeated timing permission
   may return threshold + epsilon only to that matching comparison, for matching
   timing actor/motion while real play time is below that forced value
-> native miss: rearm exact latch 1 -> 0; same authored opportunity remains pending
-> first exact native contact-resolution dispatch, caller-return Game+0x16E348:
   consume pending opportunity before Gothic original
-> later FIST refreshes/reopens one opportunity; opportunities never stack
-> execution replacement/finalization/end may retire an unused opportunity
```

Do not replace this with:

```text
global GetPlayTime hook
global clock mutation
threshold-constant patch
branch patch
direct damage dispatch
```

Timing permission is not consumption. Reaching the forced time or changing timing identity retires only the timing helper; it does not consume the logical opportunity. Native contact geometry, target selection and damage remain Gothic-owned.

Marked-execution start closes `SPU+0x164 = 1`; each accepted FIST rearms `=0`. EV-347 proves the tested native attempt leaves the latch at `1` after the instruction returns whether or not the `Game+0x16E348` boundary is entered, so do not describe `+0x16E1A3` as success-only consumption. EV-349 further shows that entering `+0x16E348` does not imply visible HP damage: Parade/block can still prevent the gameplay damage result. The persistent-opportunity implementation uses only the exact native contact-resolution dispatch at caller-return `+0x16E348` as consumption, not as a damage-success oracle; Gothic original runs once with unchanged arguments.

Permanent owner: [COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md](COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md), §§3–9. Evidence route: EV-221–EV-240 for human production, with later raw8 actor/family controls through EV-263; EV-346–EV-364 for persistent-opportunity evidence, implementation and focused acceptance. Raw8 production semantics must not be generalized to raw55 merely because both serialize through a `Fist` animation category.

---

## 5. PhysicalFist/raw55 Status

`gEUseType_PhysicalFist` / raw55 is now a permanent, distinct collision mechanism. Ordinary semantic lookup starts in `COLLISION_REFERENCE.md`; exact production ownership is `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`.

Stable source/hook facts:

```text
factual tested source       = exact current RIGHT TrollFist / PhysicalFist raw55
resting group               = Item_Equipped(5)
offensive group             = Item_Attack(7)
physical mutation transport = existing SetCollisionGroup hook
native final cleanup        = exact RIGHT 7 -> 5
Normal between-contact clear caller = Script_Game.dll +0x386C6
```

Permanent behavior keeps `EngineBridge` as physical hook/call-site transport owner and `PhysicalFistCollision` as raw55 semantic owner. Historical `PhysicalFistProbe` modules and family-specific causal contracts are archived provenance, not current implementation guidance.

Current proven marked family scope is Normal / Quick / true Power / Sprint-origin. The first authored FIST owns the physical opening; a later same-C1 FIST uses the evidence-backed contact-bookkeeping rearm without another physical opening. Native target/contact/damage and final exact RIGHT cleanup remain Gothic-owned.

Do not:

```text
copy raw8 SPU+0x164 timing/latch policy onto raw55
species-gate production behavior
generalize raw55 to LEFT without evidence
turn the historical probe policy into bridge policy
reconstruct current raw55 semantics from archived probe chronology by default
```

Evidence: EV-262–EV-298. Exact family causal history routes through `EVIDENCE_INDEX.md` only when proof detail is needed.

---

## 6. AttackContinuationProtection Research Route

EV-448 closes the first-release exact-pause research with **NOT CLEAN ENOUGH FOR FIRST RELEASE**.

There is no G3AB-owned block-skip countdown.

### Player timeout — exact tested seam

Tested Script_Game path:

```text
+0x633BF  call PropertyDurationPressedMSecs getter
+0x633C5  cmp eax, 2500
+0x633CA  jbe +0x63586
+0x633F1  PSRoutine::FullStop
+0x63409  PSRoutine::SetState("PS_Melee_Loop")
```

Historical EV-185–EV-191 prove that on vulnerable player attacks this branch can terminate the active CombatMove and discard the suspended attack continuation.

A future **deferral** contract could use one exact call-site adapter at `Script_Game +0x633BF`: call the native getter once, and while the same actor is factually attacking, clamp only this branch-local result to `2500` when it would otherwise exceed the threshold. The native `jbe` then bypasses the whole destructive branch.

This is **not an exact pause**. Native held-input time continues to advance, so expiry may occur immediately after the attack.

Do not:
- hook the shared duration getter/IAT globally;
- mutate generic CharacterControl `DurationPressedMSecs`;
- suppress all `AIFullStop`;
- suppress only `FullStop` or only `SetState`;
- call stateless deferral “pause/resume”.

### NPC parade timeout — separate mechanism

Alternative-AI NPC parade uses a different native timer and branch:

```text
OnAI_Parade
+ non-player
+ StatePosition == 1
+ Routine StateTime > 2.0 s
-> Script_Game +0x46F39 StopAIGoto
-> +0x46F51 SetState("ZS_Attack_Loop")
```

This path does not read `DurationPressedMSecs` and does not share the player's `FullStop` branch. Whether this NPC timeout can overlap a factual active attack in the tested mod stack remains unproven.

If reopened, the smallest justified NPC probe is an observation-only wrapper at `Script_Game +0x46F39`, preserving the original call once and recording actor/SPU, StateTime, factual Action/phase, state and live continuation context.

### Exact pause status

True remaining-time pause would require a new virtual elapsed-clock owner with timer-episode identity, reset detection, excluded attack duration and robust retirement across release/new press, cancellation, chains, death/removal and state changes. Those lifecycle boundaries are not proven.

New Balance compatibility requirement remains:

```text
New Balance/live stack prevents native destructive condition
-> G3AB sees no selected timeout seam
-> G3AB performs no intervention
```

Exact pause remains parked for post-release research.

ADR-0012 changes the **first-release acceptance contract**: exact remaining-time preservation is not required. A bounded stateless deferral that prevents this destructive branch while the bound actor is factually attacking is again a valid v1 candidate. Once the attack is no longer protected, an already-due timeout may fire immediately.

Do not confuse this revised gameplay contract with mathematical pause/resume.

Proof route: EV-448 and `docs/archive/investigations/bad_block_skip_static_research_2026-10-06.md`.

---

## 7. Hook Transport Rules

- Preserve exact calling convention and per-invocation object identity.
- Use the proven explicit-per-invocation `.ThisCall()` transport where shared implicit-this transport was shown recursion-unsafe.
- A call-site hook must be tied to the exact call/argument/context it was designed for; do not turn it into a global API override.
- Shared Gothic functions have one physical owner in `EngineBridge`; feature/probe modules consume bridge facts and own their policy.
- Reverify RVAs against another binary build before reuse.
- A diagnostic hook that identifies or suppresses one factual causal operation does not automatically become production architecture.

---

## 8. Third-Party Compatibility

Jackydima/New Balance source is practical compatibility reference, not native authority.

Do not assume same-function hook chaining is safe. For collisions/continuation/speed, identify whether another mod already owns the relevant path and prefer the narrowest downstream or shared authoritative intervention supported by evidence.

For Speed specifically, third-party changes observed in the live `+0x42A0` result are compatible effects to preserve; they do **not** redefine the native `ReferenceHitBaseSpeed` calibration value.

EV-242 is a bounded Pierce-specific New Balance + Jackydima control only. Mature collision compatibility and Speed compatibility have separate evidence routes; do not infer one subsystem from the other.

# Gothic 3 Animation Behaviors — Source & Hook Guide

**Status:** Canonical practical source/hook lookup guide  
**Updated:** 2026-09-16

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

---

## 3. Tested RVA Index

### Animation / CombatMove

| Purpose | Module + RVA | Meaning |
|---|---:|---|
| `GetAnimationSpeedModifier` | `Script_Game +0x42A0` | proven speed-modifier hook; final compatibility still open |
| CombatMove animation-string call | `Game +0x16B065` | narrow substitution point used by New Balance |
| CombatMove reach/vector call | `Game +0x16B8A3` | reference hook point |
| CombatMove movement call | `Game +0x16B8A9` | reference hook point |
| full-Whirl break-block call/test | `Script_Game +0x4DF8C / +0x4DF92` | incomplete CombatMove suspends ScriptFunction |
| full-Whirl ordinary cleanup continuation | `Script_Game +0x4E03C` | resumed path reaches native cleanup |
| GetUp pre-Combat offense | `Script_Game +0x41CA6` | legitimate offense can precede CombatMove |
| GetUp later CombatMove | `Script_Game +0x41D5A` | same outer ScriptFunction reaches CombatMove |
| GetUp ordinary cleanup | `Script_Game +0x41E10` | tested cleanup region |
| `GetAniName` | `Game +0x16F840` | animation-name lookup |
| `GetAniEx` | `Script +0x15C10` | animation query |
| motion data string | `Game +0xD97D5` | motion resource string |
| cached motion actor | `Game +0xDA344` | animation actor |

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

Their participation in the raw8 combat-loop route is **not yet proven**. Historical N2B runtime had deep diagnostics disabled.
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
accepted FIST below real native threshold
-> arm permission bound to actor/SPU/C1 generation/animation actor/current motion/callsite
-> call native GetPlayTime
-> only that matching comparison receives threshold + epsilon
-> consume once
```

Do not replace this with:

```text
global GetPlayTime hook
global clock mutation
threshold-constant patch
branch patch
direct damage dispatch
```

Marked-execution start closes `SPU+0x164 = 1`; each accepted FIST rearms `=0`. EV-347 proves the tested native attempt leaves the latch at `1` after the instruction returns whether or not the `Game+0x16E348` boundary is entered, so do not describe `+0x16E1A3` as success-only consumption. EV-349 further shows that entering `+0x16E348` does not imply visible HP damage: Parade/block can still prevent the gameplay damage result. Treat `+0x16E348` as an observed native hit/contact-resolution candidate boundary, not as a damage-success oracle.

Evidence route: EV-221–EV-240 for human production, with later raw8 actor/family controls through EV-263. Raw8 production semantics must not be generalized to raw55 merely because both serialize through a `Fist` animation category.

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

Future bad-skip prevention should first locate the **factual native timeout/consumer decision**, not create a parallel timer.

New Balance compatibility requirement:

```text
New Balance prevents native destructive condition
-> our protection sees no condition / performs no intervention
```

If the native destructive condition still becomes due during a real attack, investigate the narrowest point where only the destructive consequence can be suppressed/deferred. Preserve native behavior outside attacks and preserve legitimate reaction FullStop/AISetState paths.

Pausing the timer is only a candidate; consumer-level prevention may be safer.

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

EV-242 is a bounded Pierce-specific New Balance + Jackydima control only. Full mature collision compatibility remains a later gate.

# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-05

## Current bridge — N2B closed Case A; N2C game-entity OnDamage caller trace next

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat / Work must read `docs/SESSION_ENTRYPOINT.md` first, then this file for the exact current continuation.

---

## Closed / protected boundary

```text
collision architecture verification             COMPLETE — EV-206–EV-215
Power marker adapter validation                 CLOSED/PASS
Pierce marker adapter validation                CLOSED/PASS
SimpleWhirl current marker/semantic stage       CLOSED/PASS
Hack isolated routing/source/marker validation  PASS
Fist Stage A dedicated baseline                 CLOSED/PASS — EV-221
Fist Stage B marker-time DamageDisabled probe   CLOSED/FAIL AS CURRENT OFF INTERVENTION
Fist Stage A restoration after Stage B          CLOSED/PASS
Fist N1 native trigger-state observation        CLOSED/PASS AS OBSERVATION — EV-222–EV-223
Fist N2A exact-filtered gate/dispatch timing     CLOSED/INCONCLUSIVE
Fist N2B hook observability discrimination      CLOSED/CASE A FOR BOTH HOOKS
```

Do not reopen those areas without concrete contradictory evidence.

Fist remains a logical human body-contact source adapter inside the closed collision architecture. It is not another RIGHT/LEFT weapon source bit.

---

## N2A / N2B runtime result carried forward

N2A implementation:

```text
888f22fb02b0d6e524847dc28f4bbe3a5d9077a6
Add N2A Fist gate dispatch timing probe
```

N2A used diagnostic-only explicit-this `.ThisCall()` hooks at:

```text
Game + 0x692F0  gCTouchDamage_PS::CanBeActivatedNow
Game + 0x693B0  gCTouchDamage_PS::TriggerTarget
```

Canonical N2A raw:

```text
research/raw/2026-09-05_fist_n2a_gate_dispatch_timing_probe.log
raw evidence commit 7060fc2f94be6d218e3c343225df076bced28cd2
```

A controlled marked human-Fist P0 attack damaged a valid target, but the complete raw contained zero exact-filtered gate/dispatch records.

N2B implementation:

```text
196069ffa47637f57b54a7f7004a7f0fa2dd35b1
Add bounded N2B Fist hook entry trace
```

N2B preserved the same two hooks and added bounded **pre-filter** entry logging before exact-player-Fist identity filtering.

Validated N2B diagnostic:

```text
Script_FrameCollisionTest.dll
SHA256 45A2E6C9A9DFB05F6C50037D400431F19741B6AED8C9B33CCEA427E1CF854BA6
length 434176
```

Built/live SHA256 matched exactly and CORE startup passed.

Canonical N2B raw:

```text
research/raw/2026-09-05_fist_n2b_hook_observability_probe.log
raw evidence commit a23afce5659fb9c87535903573ec80a85f58a04d
length 7220
```

Controlled case:

```text
player PC_Hero
known marked human Fist P0 Normal attack
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
G3AB_COL_FIST at authored frame 3
valid target
User visual damage observation: YES
```

The execution was accepted and damaging. The exact logical Fist source remained raw UseType 8 / collision group 0 and `G3AB_COL_FIST` performed exactly the existing Stage-A triggered-list clear.

The complete N2B raw contained:

```text
zero FIST HOOK ENTRY records for CAN_BE_ACTIVATED
zero FIST HOOK ENTRY records for TRIGGER_TARGET
zero detailed N2A CanBeActivatedNow records
zero detailed N2A TriggerTarget records
```

### N2B conclusion — Case A for both hooks

For this confirmed damaging marked player-Fist run, neither current N2A wrapper entry was observed even before exact-Fist filtering.

Therefore the N2A silence is **not explained by the exact-player-Fist filter rejecting the hooked `this`**.

Do not overstate this result. It does not by itself prove that the tested methods are globally unused, that the RVAs are wrong, that hook installation globally failed, or that every Fist damage path bypasses those methods.

It does establish that another gameplay-control mutation is not justified yet. Continue read-only path reconstruction.

---

## Tested-binary reconstruction after N2B

Authoritative binary reference:

```text
https://github.com/tcholti/Gothic3_Binary_Reference.git
builds/current_tested
```

Tested SDK remains `Georgeto/gothic3sdk`.

### Ordinary eCTrigger activation is not the next probe

Exact tested Engine exports:

```text
Engine + 0x7DA00  eCTrigger_PS::OnTrigger
Engine + 0x7DA70  eCTrigger_PS::OnIntersect
Engine + 0x7DA90  eCTrigger_PS::OnTouch
Engine + 0x7DAD0  eCTrigger_PS::OnDamage
```

Tested disassembly shows all four converge on the same common activation routine at:

```text
Engine + 0x7D0F0
```

with event IDs:

```text
OnTrigger    -> 1
OnTouch      -> 3
OnIntersect  -> 5
OnDamage     -> 6, after ReactToDamage / threshold checks
```

That common activation routine performs a virtual boolean eligibility call through the trigger object's vtable at `+0x168` before continuing. Existing static analysis identifies that eligibility slot as `CanBeActivatedNow`; for `gCTouchDamage_PS` the tested override is `Game + 0x692F0`, which begins by testing `DamageDisabled` at `+0xE9`.

Therefore a normal inherited `eCTrigger_PS` activation on the relevant `gCTouchDamage_PS` would have to pass through the N2B-observed `CanBeActivatedNow` entry before continuing. N2B observed zero such entries during the damaging marked Fist run.

Do **not** add `OnTouch`, `OnIntersect`, `OnTrigger`, or `eCTrigger_PS::OnDamage` hooks as the next experiment merely to restate the same path.

### gCTouchDamage TriggerTarget downstream shape

Tested `gCTouchDamage_PS::TriggerTarget` remains:

```text
Game + 0x693B0
```

Its tested disassembly queries property-set type `0x34` (`DamageReceiver`) from one entity argument and ends with a five-stack-argument virtual call on the receiving game entity. That call shape matches the SDK `gCEntity::OnDamage` signature:

```text
void gCEntity::OnDamage(
    eCEntity *, eCEntity *, GEInt, GEInt, eCContactIterator &)
```

Exact tested Game export:

```text
Game + 0x668D0  gCEntity::OnDamage
```

The tested `gCEntity::OnDamage` implementation then forwards the five-argument damage event into the inherited Engine damage-event path after its game/player guard.

Exact tested Engine export:

```text
Engine + 0x22A8C0  eCDynamicEntity::OnDamage
```

Tested Engine disassembly shows `eCDynamicEntity::OnDamage` iterating the entity's property sets and invoking each property set's five-argument `OnDamage` virtual. This is a factual event fan-out seam.

Separately:

```text
Engine + 0x22A3E0  eCDynamicEntity::DoDamage
```

is only a `ret 0x14` no-op stub in the tested binary. Do not choose it from naming alone.

The game class also exposes a distinct six-argument `gCEntity::DoDamage` at `Game + 0x666D0`, but N2C does **not** need to hook it yet. The closer tested seam to the TouchDamage downstream event shape is `gCEntity::OnDamage`.

### Proven caller-address mechanism

Current diagnostic code already uses `_ReturnAddress()` safely inside explicit-this `.ThisCall()` wrappers for the established `AIFullStop` and `AISetState` diagnostics. Deep diagnostics also already resolve that address to:

```text
CallerAddress
CallerModuleResolved
CallerModule
CallerRVA
```

using `GetModuleHandleExA(...FROM_ADDRESS...)` and `GetModuleFileNameA(...)`.

CORE `CollisionDiagnostics.cpp` already includes `windows.h`. `_ReturnAddress` is currently made available in `EngineBridge.cpp` only under `FRAME_COLLISION_DIAGNOSTICS_DEEP`; N2C may minimally make `<intrin.h>` / `#pragma intrinsic(_ReturnAddress)` available under `FRAME_COLLISION_DIAGNOSTICS` as well. Do not enable the historical deep diagnostic profile merely for caller resolution.

---

## Exact next responsibility — N2C READ-ONLY gCEntity::OnDamage CALLER TRACE

Implement one bounded diagnostic-only hook at exactly:

```text
Game + 0x668D0  gCEntity::OnDamage
```

N2C asks only:

> During the known damaging marked player-Fist execution, is `gCEntity::OnDamage` entered, and if so, what factual caller module/RVA and argument/context values identify the native path that reached it relative to the authored FIST marker?

Do not test another Fist control in N2C.

### Hook transport

The hook must:

- exist only under `FRAME_COLLISION_DIAGNOSTICS`;
- use explicit per-invocation `gCEntity *this` with the already-proven `.ThisCall()` transport;
- use the exact SDK signature/order:

```text
gCEntity *this
eCEntity *EntityArg1
eCEntity *EntityArg2
GEInt IntArg1
GEInt IntArg2
eCContactIterator &ContactIterator
```

- capture `_ReturnAddress()` at hook entry before logging or native forwarding;
- call the native original exactly once with all arguments unchanged and in the same order;
- return normally (`void`);
- perform no entity/property/collision/marker/lifecycle/target mutation.

The behavior-only product must contain neither the N2C hook nor its diagnostics.

### Bounded entry logging

N2C is an observability probe, so do not add a semantic filter that could hide the path before it is understood.

Use one small diagnostic-only ordinal/cap for `gCEntity::OnDamage` entries, sufficient for one controlled attack. A cap of 64 is acceptable and consistent with N2B. Emit one explicit suppression record if the cap is exceeded.

Each logged entry must report at minimum:

```text
Boundary: ENTITY_ON_DAMAGE_ENTRY
ElapsedMs
HookEntryOrdinal
CallerAddress
CallerModuleResolved
CallerModule
CallerRVA
ThisEntityAddress
ThisEntityName
EntityArg1Address
EntityArg1Name
EntityArg2Address
EntityArg2Name
IntArg1
IntArg2
ContactIteratorAddress
PlayerEntityAddress
PlayerAction
PlayerAniPhase
PlayerStateTime
PlayerCurrentMovementAni
ExistingResolverFistSourceAddress (or null)
ExistingResolverFistUseType, if resolved
ExistingResolverFistCollisionGroup, if resolved
ThisIsPlayer: 0/1
EntityArg1IsPlayer: 0/1
EntityArg2IsPlayer: 0/1
ThisIsResolvedFistSource: 0/1
EntityArg1IsResolvedFistSource: 0/1
EntityArg2IsResolvedFistSource: 0/1
```

Use neutral argument names. Do not label `this`, EntityArg1, EntityArg2, IntArg1, or IntArg2 as target, inflictor, damage type, amount, or any other semantic role unless later evidence proves that role.

For Fist correlation, reuse only the existing authority:

```text
CollisionSources::ResolveFistCollisionSource(player)
```

Do not create another Fist classifier.

### Caller resolution

Reuse the already-proven factual caller-address approach in concept:

```text
_ReturnAddress()
-> GetModuleHandleExA(FROM_ADDRESS | UNCHANGED_REFCOUNT)
-> GetModuleFileNameA
-> caller RVA = caller address - module base
```

A tiny CORE-private equivalent helper in `CollisionDiagnostics.cpp` is acceptable. Do not refactor or broaden `CollisionDiagnosticsDeep` merely to share this helper.

### Preserve existing diagnostics and Stage A

Leave the N2A/N2B hooks and logs unchanged unless a compile-only adjustment is strictly necessary. They remain diagnostic-only and their silence is part of the evidence chain.

`G3AB_COL_FIST` must remain exact Stage A:

```text
resolve/validate human gEUseType_Fist / raw 8
-> TouchDamage.ClearTriggeredList()
-> no DamageDisabled behavior
-> no collision-group mutation
-> no weapon source-mask semantics
```

Do not alter callback ownership/suppression, marker occurrence/dedupe, C1 generation, family, StatePosition, source resolution or lifecycle.

### Expected source scope

Expected changed prototype files:

```text
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
```

No CMake/build-product separation change is expected. A minimal include-guard widening for `_ReturnAddress` under `FRAME_COLLISION_DIAGNOSTICS` is within N2C scope.

### N2C interpretation boundary

One controlled damaging marked player-Fist run should answer:

```text
A. gCEntity::OnDamage entry occurs during the marked Fist execution
   -> use caller module/RVA + factual arguments/context to identify the real upstream native path;
      map that caller statically before choosing any control mechanism.

B. visual Fist damage occurs but no gCEntity::OnDamage entry is observed
   -> this seam also did not observe the damaging path in that run;
      do not mutate gameplay behavior; continue static path reconstruction.

C. multiple OnDamage entries occur
   -> correlate only by chronological timing, player action/phase/state time,
      resolved Fist source, neutral entity identities and caller RVA;
      do not guess argument roles.
```

N2C does not select or validate a production `FIST_OFF` mechanism.

---

## N2C explicit non-goals

Do not implement or design:

```text
G3AB_COL_FIST_OFF
any production Fist disable mechanism
any DamageDisabled setter experiment
SetIsEnabled / SetReactToTouch
SetCollisionGroup changes
extra ClearTriggeredList behavior
hooks on eCTrigger_PS::OnTouch / OnIntersect / OnTrigger / OnDamage
hook on eCDynamicEntity::DoDamage
hook on gCEntity::DoDamage
persistent Fist marker-owned lifecycle state
baseline snapshot/restore
terminal/interruption restoration
PhysicalFist / monsters / generalized body collision
per-limb Fist markers
weapon source-mask changes
attack-family or StatePosition redesign
C1 or weapon-lifecycle redesign
RIGHT/LEFT/BOTH/OFF redesign
final mixed regressions
Raise / playback-speed work
```

---

## Frozen continuation

```text
A    — dedicated FIST baseline                    CLOSED/PASS
B    — marker-time DamageDisabled intervention    CLOSED/FAIL AS CURRENT OFF INTERVENTION
R    — exact restoration to Stage A behavior      CLOSED/PASS
N1   — native trigger-state observation           CLOSED/PASS AS OBSERVATION
D    — close N1 / correct docs / procedures       CLOSED
N2A  — exact-filtered gate/TriggerTarget timing   CLOSED/INCONCLUSIVE
N2B  — hook observability/filter discrimination   CLOSED/CASE A FOR BOTH HOOKS
S2   — tested-binary damage-path reconstruction   CLOSED FOR N2C SELECTION
N2C  — gCEntity::OnDamage caller trace            CURRENT/NEXT
C    — production FIST/FIST_OFF lifecycle         BLOCKED until control mechanism is proven
```

---

## Local-state caution carried forward

Earlier local status showed this unrelated untracked file:

```text
research/raw/2026-09-04_hack_2h_dedicated_p0_override_validation.log
```

Do not delete, rename, stage, overwrite, or clean it merely to obtain a clean working tree.

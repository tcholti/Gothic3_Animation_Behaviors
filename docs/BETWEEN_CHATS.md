# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-05

## Current bridge — Fist Stage A CLOSED/PASS; Stage B one-variable probe next

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and use this file only for the exact continuation details below.

---

## Closed / protected boundary

```text
collision architecture verification             COMPLETE — EV-206–EV-215
Power marker adapter validation                 CLOSED/PASS
Pierce marker adapter validation                CLOSED/PASS
SimpleWhirl current marker/semantic stage       CLOSED/PASS
Hack isolated routing/source/marker validation  PASS
Fist Stage A dedicated baseline                 CLOSED/PASS
```

Do not reopen those areas without concrete contradictory evidence.

The previously planned final native-control and New Balance + Script_AttackCollision mixed regressions remain postponed until human Fist collision support is integrated and validated.

Fist is an extension inside the closed collision architecture, not an architecture rewrite.

---

## Frozen Fist architecture

Responsibility split:

```text
attack-family logic
        |
        v
generic marker framework
        |
   +----+----+
   |         |
   v         v
equipped     Fist
source       source
route        route

RIGHT/LEFT/  FIST/FIST_OFF
BOTH/OFF
```

Shared infrastructure:

```text
marker scanning/cache
supported attack-family ownership
current C1 generation identity
generation-scoped occurrence budget
same-update dedupe
existing family-owned StatePosition semantics
```

Source-specific semantics remain separate:

```text
RIGHT / LEFT / BOTH / OFF
-> equipped weapon source path
-> Item_Attack / Item_Equipped responsibilities remain unchanged

FIST / future FIST_OFF
-> logical human Fist/body-contact path
-> no weapon collision-group semantics
```

Fist is **not** another RIGHT/LEFT source bit. Do not add `SourceMask_Fist`.

The human Fist source is factually obtained from the actor's right-hand inventory slot in the proven setup, but that is only an implementation location. Public semantics are the logical Fist/body-contact source, not a right-hand limb marker.

Current runtime scope remains only:

```text
gEUseType_Fist
raw UseType 8
human Fist source
```

Do not generalize current work to `gEUseType_PhysicalFist` / raw 55, monsters, generic body collision, or per-limb collision.

Attack-family selection remains independent from source selection. Do not create a Fist-specific Normal/Power/Quick whitelist or new Quick-selection behavior. If Gothic factually executes an already-supported marker family, the Fist source adapter composes with that family and leaves its existing StatePosition policy intact.

---

## Stage A — CLOSED/PASS

Source implementation:

```text
5984738a41eca895900ae0929c3c930336c8ff53
Add dedicated Fist marker baseline
```

Runtime evidence commit:

```text
91e6d4f81b5f8d549546686a6d308ddff3e3bd9f
Add Fist Stage A baseline runtime evidence
```

Raw artifact:

```text
research/raw/2026-09-05_fist_stagea_human_dedicated_fist_baseline.log
```

Validated diagnostic DLL SHA256:

```text
C9C6474D7A3EE6ABA0D260457DC85A597F5A7B1F614C01AD1A2BA15DDE890033
```

Validated fixture:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
frame 3: G3AB_COL_FIST
```

Observed and logged result:

```text
visual valid-target damage: YES
Family: NORMAL
ContainsReservedSourceMarker: 1
RequiredSourceMask: 0
RequiresFistSource: 1
FistSourceResolved: 1
FistSourceUseType / FistUseType: 8
Fist collision group: 0 -> 0
SuppressNativeCallback: 1
C1GenerationValid: 1
MarkerAction: ACCEPTED
TriggeredListClearCount: 1
FistTriggeredListCleared: 1
MarkerOwnedWeaponMask: 0
ActivatedSourceCount: 0
RetiredSourceCount: 0
DeactivatedSourceCount: 0
finalization: NO_OP_NO_OUTSTANDING
PhysicalCollisionChanged: 0
```

Stage A therefore proves the known-good human Fist contact still damages through the separated dedicated FIST route when the adapter performs only `TouchDamage.ClearTriggeredList()` and does not use weapon Item_Attack / Item_Equipped mutation or DamageDisabled behavior.

---

## Frozen staged implementation / proof sequence

```text
A — dedicated FIST baseline
    CLOSED/PASS

B — DamageDisabled causal probe on the proven FIST route
    CURRENT

C — production FIST / FIST_OFF + exact baseline snapshot/restore lifecycle
    only after B causally proves the mechanism
```

### Stage B contract — next bounded Work responsibility

Change exactly one conceptual variable on the already-proven dedicated FIST path:

```text
same G3AB_COL_FIST route
same human gEUseType_Fist / raw 8 resolution
same ClearTriggeredList behavior
same marker/C1/family bookkeeping
+ DamageDisabled = true
```

No other collision/source/lifecycle behavior is to change.

Runtime question:

> Does the otherwise-identical known-good Stage A contact stop damaging when the dedicated Fist source has `DamageDisabled = true`?

If it does, that is strong causal support for DamageDisabled as the future Fist OFF mechanism.

### Explicit Stage B non-goals

Do **not** implement yet:

```text
G3AB_COL_FIST_OFF
persistent Fist marker-owned state
baseline snapshot/restore
terminal/interruption restoration
PhysicalFist support
monster/general body collision
per-limb Fist markers
weapon source-mask changes
new hooks
attack-family or StatePosition redesign
```

Stage B must remain a temporary causal probe, not a production lifecycle implementation.

---

## Stage C — only after Stage B proves the mechanism

Production-direction contract remains:

```text
G3AB_COL_FIST
-> DamageDisabled = false
-> ClearTriggeredList()

G3AB_COL_FIST_OFF
-> DamageDisabled = true
```

Persistent Fist ownership would then snapshot the exact pre-ownership `DamageDisabled` value once, keep that baseline across `FIST -> FIST_OFF -> FIST`, and restore the captured value at factual execution finalization/interruption so later unmarked/native Fist attacks cannot remain accidentally disabled.

C1 supplies the factual generation/finalization boundary; it does not turn Fist cleanup into weapon `Item_Equipped` repair semantics.

---

## Exact next responsibility

Do not perform another Stage A test.

Freeze and execute one bounded Work B source task implementing only the Stage B one-variable `DamageDisabled = true` probe on the already-proven dedicated FIST route. After Work publishes it, Normal Chat must independently review the diff before local build/runtime validation.

Use the same known-good Stage A fixture/timing for the later Stage B runtime comparison unless a concrete local asset contradiction appears:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
frame 3: G3AB_COL_FIST
```

---

## Local-state caution carried forward

Earlier local status showed this unrelated untracked file:

```text
research/raw/2026-09-04_hack_2h_dedicated_p0_override_validation.log
```

Do not delete, rename, stage, or overwrite it merely to obtain a clean working tree.

---

## Deliberately outside the immediate continuation

```text
production G3AB_COL_FIST_OFF
persistent Fist marker-owned lifecycle state
Fist terminal/interruption restoration
PhysicalFist / monsters / generalized body collision
per-limb Fist markers
new attack actions / Quick-selection logic
attack-family / StatePosition redesign
C1 or weapon-lifecycle redesign
RIGHT/LEFT/BOTH/OFF redesign
Hack / SimpleWhirl redesign
final native mixed regression
final New Balance + Script_AttackCollision mixed regression
Raise
playback-speed redesign
target acquisition
climbing
```

Final mixed collision regressions resume only after the complete human Fist feature reaches Stage C validation.
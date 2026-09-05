# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-05

## Current bridge — Fist Work A source complete; baseline runtime validation next

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

Current runtime scope is only:

```text
gEUseType_Fist
raw UseType 8
human Fist source
```

Do not generalize current work to `gEUseType_PhysicalFist` / raw 55, monsters, generic body collision, or per-limb collision.

Attack-family selection remains independent from source selection. Do not create a Fist-specific Normal/Power/Quick whitelist or new Quick-selection behavior. If Gothic factually executes an already-supported marker family, the Fist source adapter composes with that family and leaves its existing StatePosition policy intact.

---

## Frozen staged implementation / proof sequence

```text
A — dedicated FIST baseline
B — DamageDisabled causal probe on the proven FIST route
C — production FIST / FIST_OFF + exact baseline snapshot/restore lifecycle
```

Only Stage A exists in source now. Stage B and Stage C remain deliberately unimplemented.

### Stage A contract

```text
G3AB_COL_FIST
-> resolve valid logical human Fist source
-> dedicated Fist source operation
-> TouchDamage.ClearTriggeredList()
-> no weapon collision-group mutation
-> no DamageDisabled behavior
```

Runtime question:

> Does the known-good human Fist contact still damage when the marked animation uses the dedicated `G3AB_COL_FIST` route and the Fist adapter performs only `ClearTriggeredList()` while Gothic's native timed collision callback is marker-owned/suppressed?

### Stage B — only after A passes

Change one conceptual variable on the exact proven dedicated FIST path:

```text
same FIST route
+ DamageDisabled = true
```

If otherwise identical known-good contact stops damaging, that is strong causal support that `DamageDisabled` is the Fist OFF mechanism.

### Stage C — only after B proves the mechanism

Production-direction contract:

```text
G3AB_COL_FIST
-> DamageDisabled = false
-> ClearTriggeredList()

G3AB_COL_FIST_OFF
-> DamageDisabled = true
```

Persistent Fist ownership then snapshots the exact pre-ownership `DamageDisabled` value once, keeps that baseline across `FIST -> FIST_OFF -> FIST`, and restores the captured value at factual execution finalization/interruption so later unmarked/native Fist attacks cannot remain accidentally disabled.

C1 supplies the factual generation/finalization boundary; it does not turn Fist cleanup into weapon `Item_Equipped` repair semantics.

---

## Work A published source

Work A is complete and published as:

```text
5984738a41eca895900ae0929c3c930336c8ff53
Add dedicated Fist marker baseline
```

Changed source files:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
prototypes/Script_FrameCollisionTest/CollisionSourceOperations.cpp
prototypes/Script_FrameCollisionTest/CollisionSourceOperations.h
prototypes/Script_FrameCollisionTest/CollisionSources.cpp
prototypes/Script_FrameCollisionTest/CollisionSources.h
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.cpp
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.h
prototypes/Script_FrameCollisionTest/FrameCollisionShared.h
```

No `EngineBridge.cpp` change and no new hook were introduced.

---

## Independent Normal Chat source review — PASS

The Work A diff was independently reviewed against the frozen contract before this handoff.

Confirmed source-level facts:

```text
RIGHT = 0
LEFT  = 1
BOTH  = 2
OFF   = 3
FIST  = 4
Count = 5
```

Also confirmed:

```text
no G3AB_COL_FIST_OFF yet
no SourceMask_Fist
old temporary DamageDisabled=true mutation removed
no Work-A DamageDisabled read/write added
dedicated ResolveFistCollisionSource(actor)
    -> factual right-slot candidate
    -> accepts only gEUseType_Fist
    -> rejects PhysicalFist

dedicated RearmFistSource(source)
    -> validates gEUseType_Fist
    -> records factual group/use type
    -> performs only TouchDamage.ClearTriggeredList()
    -> performs no SetCollisionGroup

FIST presence is represented independently from required weapon SourceMask
valid Fist source is required before native callback suppression
FIST participates in existing C1 generation / occurrence / dedupe bookkeeping
FIST does not create or mutate the equipped-weapon marker-owned source-mask window
existing family-owned StatePosition handling remains downstream and unchanged
old Fist-special branching was removed from the equipped-source operations
actual equipped weapon RIGHT/LEFT/BOTH/OFF semantics remain on the weapon path
CORE diagnostics now advertise RIGHT LEFT BOTH OFF FIST and expose Fist source/useType/group/list-clear facts
```

The source review found no material contradiction requiring redesign.

This is **source review only**. It is not a Gothic runtime result and does not prove the dedicated FIST route damages yet.

---

## Exact next responsibility in the new Chat

Do **not** start Stage B yet.

Complete Stage A on the authoritative home PC:

```text
1. sync branch to current remote HEAD
2. build ONLY Script_FrameCollisionTest
3. deploy only Script_FrameCollisionTest.dll
4. verify Script_FrameCollisionBehaviorTest.dll is absent
5. verify live diagnostic DLL SHA / startup profile
6. author one known-good human Fist Hit with G3AB_COL_FIST at the proven contact timing
7. run one controlled focused/focusable neutral-target contact test
8. preserve the exact diagnostic raw log
9. interpret visual + logger evidence
```

Known historical fixture to reuse unless the local asset setup requires the already-proven equivalent:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
```

Historical Fist tests established frame 3 as a known workable authored marker/contact timing for this fixture. For Stage A, use:

```text
frame 3: G3AB_COL_FIST
```

Do **not** use `G3AB_COL_RIGHT` for Fist. RIGHT belongs to the equipped-source route.

Freeze the exact raw filename immediately before the actual runtime run using the run's real date; do not carry a stale pre-invented filename across days.

Stage A PASS requires both:

```text
visual: known-good Fist contact damages the valid target
logger: FIST accepted on valid C1 generation, resolved human Fist UseType 8,
        factual group remains non-weapon-style (expected historical 0 -> 0),
        ClearTriggeredList occurred, no weapon group request path is used
```

If Stage A passes:

```text
preserve/publish raw evidence
-> interpret and record canonical evidence
-> then freeze Stage B as a separate one-variable Work task
```

If Stage A fails, diagnose the dedicated route before introducing DamageDisabled.

---

## Local-state caution carried forward

Earlier local status showed this untracked file:

```text
research/raw/2026-09-04_hack_2h_dedicated_p0_override_validation.log
```

It is unrelated to Fist Work A. Do not delete, rename, stage, or overwrite it merely to obtain a clean working tree. A normal fast-forward pull can proceed if there are no conflicting tracked local edits.

---

## Deliberately outside the immediate continuation

```text
G3AB_COL_FIST_OFF
DamageDisabled causal mutation until Stage A passes
persistent Fist marker-owned state
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
# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-05

## Current bridge — Human Fist source adapter before final collision regression

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat / Work must read `docs/SESSION_ENTRYPOINT.md` first and follow its bootstrap.

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

The previously planned final native-control and New Balance + Script_AttackCollision mixed regressions are **postponed until human Fist collision support is integrated and validated**. Fist is an extension inside the closed collision architecture, not a reason to redesign it.

---

## Frozen Fist architecture

The intended responsibility split is:

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

FIST / FIST_OFF
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

Do not generalize current Fist work to `gEUseType_PhysicalFist` / raw 55, monsters, generic body collision, or per-limb collision.

Attack-family selection remains independent from source selection. Do not create a Fist-specific Normal/Power/Quick whitelist or new Quick-selection behavior. If Gothic factually executes an already-supported marker family, the Fist source adapter composes with that family and leaves its existing StatePosition policy intact.

---

## Frozen implementation/test sequence

Use three bounded stages so each runtime result stays causal.

```text
A — dedicated FIST baseline
B — DamageDisabled causal probe on the proven FIST route
C — production FIST / FIST_OFF + Fist lifecycle restoration
```

Only **Work A** is authorized now.

### Stage A — dedicated FIST baseline

Goal:

```text
G3AB_COL_FIST
-> resolve valid logical human Fist source
-> dedicated Fist source operation
-> TouchDamage.ClearTriggeredList()
-> no weapon collision-group mutation
```

Runtime question after Work A:

> Does the known-good human Fist contact still damage when the marked animation uses the dedicated `G3AB_COL_FIST` route and the Fist adapter performs only `ClearTriggeredList()` while Gothic's native timed collision callback is marker-owned/suppressed?

### Stage B — later, only after A passes

Using the exact proven dedicated FIST route, change one conceptual variable:

```text
same FIST route
+ DamageDisabled = true
```

If otherwise identical known-good contact stops damaging, that is strong causal support that `DamageDisabled` is the Fist OFF mechanism.

### Stage C — later, only after B proves the mechanism

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

# WORK A — DEDICATED FIST MARKER BASELINE

## Frozen responsibility

Implement **only** first-class marker `G3AB_COL_FIST` and route it through a dedicated human-Fist source adapter whose only engine mutation is `TouchDamage.ClearTriggeredList()`.

The current source branch contains a temporary `DamageDisabled = true` Fist causal probe inside the older mixed source operation. Work A must remove that temporary mutation completely.

There must be **no `DamageDisabled` read/write behavior in Work A**.

## Marker vocabulary

Preserve existing numeric IDs exactly:

```text
RIGHT = 0
LEFT  = 1
BOTH  = 2
OFF   = 3
```

Append:

```text
FIST  = 4
Count = 5
```

Do **not** add `FIST_OFF` yet. Later work will append it as opcode 5.

`FIST` is an ownership/activation marker. It must participate in marker-name recognition, authored marker count, first-frame reporting, marker cache, C1 generation-scoped occurrence budget, same-update dedupe, and supported attack-family marker ownership.

`FIST` must not participate in `SourceMask_Right`, `SourceMask_Left`, or `SourceMask_Both`.

The marker decision/cache must represent dedicated Fist-source requirement independently of the equipped weapon source mask, for example with a narrow factual field such as `requiresFistSource` or an equivalent representation.

## Ownership safety

A motion containing `G3AB_COL_FIST` may suppress the appropriate native timed attack callback only when a valid logical human Fist source resolves before suppression.

A malformed/inappropriate FIST marker with no valid human Fist source must fail ownership safely; it must not suppress native collision and discover the missing source only afterward.

Do not infer Fist from animation filenames.

## Dedicated human Fist resolver

Use a separate Fist-source resolver responsibility, conceptually:

```text
ResolveFistCollisionSource(actor)
```

Required semantics:

```text
obtain factual candidate from proven human Fist slot location
-> candidate exists
-> factual UseType == gEUseType_Fist
-> return logical Fist source
```

Otherwise resolve no Fist source.

Do not accept `gEUseType_PhysicalFist` in Work A.

## Dedicated Fist operation

Use a separate Fist source operation responsibility, conceptually:

```text
ActivateOrRearmFist(source)
```

Its **only** Work A engine action is:

```text
source.TouchDamage.ClearTriggeredList()
```

It must not:

```text
SetCollisionGroup(Item_Attack)
SetCollisionGroup(Item_Equipped)
read or write DamageDisabled
create/use SourceMask_Fist
select a literal limb
```

Record factual source UseType, collision group before/after, and list-clear result for diagnostics as needed, but do not mutate the collision group. Historical evidence expects human Fist group 0 -> 0; do not hard-code group 0 as a behavioral condition.

## Remove old mixed Fist responsibility

The older equipped-source operation contains Fist-aware special handling because Fist previously travelled through RIGHT/LEFT weapon machinery.

Work A moves that responsibility into the dedicated Fist route.

After Work A, conceptual ownership must be:

```text
equipped-source operation
-> equipped weapon mechanics
-> no Fist-specific decision

Fist-source operation
-> logical human Fist mechanics
-> no Item_Attack / Item_Equipped mechanics
```

Remove/narrow only obsolete Fist-specific branches and their direct dead dependents, such as old `IsFistCollisionSource` / `skippedGroupForFist` handling if they are no longer needed.

Do not use this separation as a broad refactor. Preserve actual RIGHT/LEFT/BOTH/OFF weapon behavior exactly.

## Marker processing

When an authored `G3AB_COL_FIST` marker passes the existing factual marker checks:

```text
resolve valid human Fist source
-> dedicated Fist ActivateOrRearm
-> ClearTriggeredList
-> accepted marker
```

Reuse the existing current C1 generation, generation consistency, duplicate suppression, authored occurrence budget, and family-owned StatePosition processing.

FIST must **not** create or modify the existing equipped-weapon `MarkerOwnedCollisionWindow.activeSourceMask`.

Work A creates no persistent Fist marker-owned lifecycle state because `ClearTriggeredList()` requires no restoration. Persistent Fist state belongs only to Stage C after `DamageDisabled` is causally proven.

## Attack-family responsibility

Do not add a Fist-specific action whitelist.

Existing attack-family ownership remains authoritative for:

```text
Normal
Power
Quick
SimpleWhirl
Whirl
Pierce
Hack
```

Examples:

```text
Normal + FIST -> existing Normal semantics -> Fist source operation
Power  + FIST -> existing Power semantics  -> Fist source operation
Quick  + FIST -> existing Quick semantics  -> Fist source operation
```

Do not add attack actions, Quick-selection logic, Power-selection changes, Hack routing changes, or Fist-specific StatePosition values.

## Diagnostics

Update CORE diagnostics only as necessary for Work A.

Startup marker-opcode reporting must include:

```text
RIGHT LEFT BOTH OFF FIST
```

Accepted FIST marker evidence must make it possible to establish at minimum:

```text
MarkerOpcode = FIST
Fist source resolved
factual Fist UseType
collision group before
collision group after
ClearTriggeredList occurred
current C1 generation
normal authored/accepted marker-budget facts
```

Do not add `DamageDisabled` diagnostics in Work A. Do not enable deep diagnostics.

## Explicitly out of scope for Work A

Do not implement or redesign:

```text
G3AB_COL_FIST_OFF
DamageDisabled read/write
original DamageDisabled snapshot
persistent Fist marker-owned window
Fist terminal/interruption restoration
PhysicalFist / monsters / generalized body collision
per-limb Fist markers
Fist RIGHT/LEFT/BOTH semantics
new hooks
new attack actions
Quick-selection logic
attack-family semantics
StatePosition policy
C1 lifecycle architecture
weapon lifecycle architecture
RIGHT/LEFT/BOTH/OFF weapon behavior
Hack behavior
SimpleWhirl behavior
runtime evidence conclusions
documentation/evidence claims based on unrun gameplay
research/raw artifacts
```

## Expected source area

Inspect only the exact dependency chain needed, expected primarily around:

```text
prototypes/Script_FrameCollisionTest/FrameCollisionShared.h
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.cpp
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.h        if required
prototypes/Script_FrameCollisionTest/CollisionSources.cpp
prototypes/Script_FrameCollisionTest/CollisionSources.h
prototypes/Script_FrameCollisionTest/CollisionSourceOperations.cpp
prototypes/Script_FrameCollisionTest/CollisionSourceOperations.h
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
```

`EngineBridge.cpp` should require no new hook or attack-family logic; touch it only if the existing generic reserved-marker dispatch needs the minimum mechanical update for FIST recognition.

## Work A source audit

Before publication verify:

1. Existing opcode values 0-3 are unchanged.
2. FIST is opcode 4; Count is 5.
3. No FIST_OFF exists.
4. No SourceMask_Fist exists.
5. No DamageDisabled read/write remains in Work A runtime code.
6. FIST accepts only `gEUseType_Fist`, not PhysicalFist.
7. FIST uses a dedicated Fist operation that performs `ClearTriggeredList()`.
8. FIST performs no collision-group mutation.
9. Obsolete Fist special handling is removed from the equipped-source operation without changing actual weapon semantics.
10. RIGHT/LEFT/BOTH/OFF behavior is preserved.
11. FIST callback ownership requires a valid logical human Fist source before native suppression.
12. FIST uses existing C1 generation/dedupe/occurrence bookkeeping.
13. FIST creates no equipped-weapon source-mask window.
14. Existing family StatePosition behavior is unchanged.
15. No new hook or attack-selection behavior exists.
16. CORE startup diagnostics list FIST and accepted FIST evidence contains the required factual source operation fields.
17. No unrelated source/evidence files changed.

If the environment can compile the Windows target, build only:

```text
Script_FrameCollisionTest
```

If it cannot actually compile the Windows target, do not claim compilation success.

## Work A publish/handoff

Work is authorized, when launched by the User, to publish only the audited commits for this bounded task to:

```text
Repository: https://github.com/tcholti/Gothic3_Animation_Behaviors.git
Branch: docs/collision-source-evidence
```

Use a narrow message such as:

```text
Add dedicated Fist marker baseline
```

Report only:

```text
final full remote commit SHA
files changed
bounded responsibility implemented
protected behavior preserved
whether compilation was actually performed/succeeded
any material source/API contradiction
```

Do not claim runtime validation.

---

## After Work A publishes

Normal Chat must independently review the Work diff against this contract before local build/runtime authority is claimed.

If the review passes:

```text
sync authoritative home PC
-> build only Script_FrameCollisionTest
-> deploy only diagnostic collision twin
-> verify live SHA/startup
-> author one known-good human Fist Hit with G3AB_COL_FIST at the proven contact timing
-> run controlled focused/focusable neutral-target contact test
-> save exact raw log
-> interpret visual + logger evidence
```

If the dedicated FIST baseline damages as expected, Stage A passes and the next bounded responsibility is Stage B: add only `DamageDisabled=true` to the same proven dedicated FIST operation and repeat the exact causal fixture.

Final mixed native and New Balance + Script_AttackCollision collision regressions remain postponed until the complete Fist feature reaches Stage C validation.

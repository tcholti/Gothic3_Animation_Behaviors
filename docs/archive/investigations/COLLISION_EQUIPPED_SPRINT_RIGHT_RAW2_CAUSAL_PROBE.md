# Equipped Sprint RIGHT/raw2 Causal Probe

**Status:** SUPERSEDED BEFORE RUNTIME TEST
**Type:** Bounded diagnostic-only causal implementation
**Created:** 2026-09-19
**Owner:** Historical/superseded diagnostic contract.

> **Superseded 2026-09-19:** This fixture-narrow RIGHT/raw2 contract was implemented diagnostically in `1ae0731cd501e6d72bbbf6642188a3047d134805` but was **not built or runtime-tested**. A subsequent Normal Chat correction established that Goblin RIGHT/raw2 is only the first evidence fixture; the framework hypothesis must remain generic equipped Sprint using the existing RIGHT/LEFT/BOTH/OFF marker model and generic required-source validation. The replacement active contract is `docs/work/active/COLLISION_EQUIPPED_SPRINT_GENERIC_CAUSAL_PROBE.md`. Do not build/test or promote this superseded narrow contract.

## Purpose

Test one newly discovered scope question from EV-311:

> Can a factual equipped Sprint attack (`Action=9 / Family=SPRINT`) safely use the existing authored equipped collision mechanism for an exact current RIGHT 1H/raw2 source when native early callback timing is suppressed and the authored RIGHT marker becomes the collision authority?

This is **not** production promotion yet. The exact mechanism is not sufficiently proven until runtime shows that callback suppression preserves the Sprint attack and that the existing marker/lifecycle path owns activation, damage opportunity and cleanup correctly.

Phase 4 non-weapon regression is temporarily held while this scope-changing question is resolved.

## Evidence basis

EV-311 provides the exact fixture:

```text
Actor      = Goblin
Action     = 9
Family     = SPRINT
Motion     = Goblin_Stand_None_1H_P0_PowerAttack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
RIGHT      = It_1H_Club_01 / UseType 2
marker     = G3AB_COL_RIGHT
current result = REJECTED_UNSUPPORTED_HIT
```

In the current unmodified path, the native `OnAI_PowerAttack` route opens the exact equipped source `5 -> 7` before the authored marker. The marker is then rejected solely because equipped Sprint is deliberately unsupported.

Current source already establishes:

- factual Sprint identity in `TryGetCurrentAttackHitFamily()`;
- Sprint transport through the existing `OnAI_PowerAttack` hook while factual Action remains 9;
- marker-owned Sprint StatePosition target = 1;
- generic equipped RIGHT activation/rearm/lifecycle machinery;
- raw8 Sprint and raw55 Sprint-origin as separate protected mechanisms.

The unknown is specifically whether skipping the native callback for the exact equipped Sprint fixture is safe and lets the existing equipped marker path become authoritative without breaking attack progression or adjacent mechanisms.

## Frozen causal hypothesis

For the exact eligible probe execution:

```text
factual Action9 / Sprint Hit
+ exact current RIGHT source exists
+ RIGHT source UseType == gEUseType_1H / raw2
+ current motion has authored RIGHT marker(s)
+ OFF may coexist as the ordinary equipped empty-set/deactivation marker
+ no LEFT / BOTH / FIST marker ownership
+ valid current C1 generation
-> suppress original OnAI_PowerAttack callback for this execution
-> permit the authored RIGHT marker to enter the existing generic equipped marker path
-> generic equipped collision code performs RIGHT activation/rearm and lifecycle ownership
-> Gothic still owns target/contact/damage and native cleanup
```

The probe must not invent a parallel collision mechanism.

## Exact probe scope

Probe support is limited to the discovered factual class:

```text
family/action          = Sprint / Action9
equipped source        = exact current RIGHT only
source UseType         = 1H / raw2
authored source marker = RIGHT, with ordinary OFF allowed
FIST                   = excluded from this probe
LEFT/BOTH              = excluded
other UseTypes         = excluded
unmarked Sprint        = native / excluded
```

`OFF` remains part of the established equipped marker vocabulary. In this probe it is allowed only as the ordinary empty-set/deactivation partner to the exact RIGHT/raw2 marker-owned window; it does not broaden source ownership beyond RIGHT. The probe must not invent separate OFF behavior: authorized OFF must enter the existing generic equipped OFF path.

Do not species-gate to Goblin. Eligibility is factual action/source/marker/C1 identity, with the Goblin only serving as the current runtime fixture.

## Required architecture

Follow `FEATURE_DEVELOPMENT_METHOD.md` unknown-mechanism rules.

Create a temporary diagnostic-only module:

```text
prototypes/Script_FrameCollisionTest/EquippedSprintProbe.cpp
prototypes/Script_FrameCollisionTest/EquippedSprintProbe.h
```

The probe owns:

- exact eligibility for this temporary intervention;
- binding callback suppression to actor + current C1 + exact RIGHT source + exact motion;
- authorization for matching RIGHT and ordinary OFF markers on the same bound execution;
- compact probe-specific diagnostic result/state needed to prove the causal question.

`EngineBridge` remains transport-only. It may call the probe at the existing `OnAI_PowerAttack` transport and enact only the probe's returned suppress/delegate decision.

`FrameCollisionMarkers` remains the owner of the established generic equipped marker mechanism. Add only the smallest **diagnostic-build-only permission seam** needed so the probe can authorize the otherwise-rejected Sprint RIGHT/OFF markers. Do not copy equipped activation/deactivation/lifecycle logic into the probe.

The behavior-only twin must remain unchanged in runtime semantics: the probe must compile only into `Script_FrameCollisionTest`, not `Script_FrameCollisionBehaviorTest`.

## Required implementation behavior

### Callback boundary

For an exact probe-eligible marked Sprint execution:

- the probe binds the current actor/C1/source/motion identity;
- `EngineBridge` suppresses the original `OnAI_PowerAttack` callback for that execution;
- existing raw8 ownership update remains untouched;
- existing raw55 `PhysicalFistCollision` behavior remains untouched;
- a non-eligible Sprint execution calls native/original behavior exactly as before.

### Marker boundary

For a matching bound execution:

- only `G3AB_COL_RIGHT` and `G3AB_COL_OFF` may bypass the current generic `Sprint + non-FIST -> REJECTED_UNSUPPORTED_HIT` gate for the same exact bound RIGHT/raw2 execution;
- after that permission, `FrameCollisionMarkers::ProcessMarker()` must use its existing normal equipped RIGHT/OFF paths without duplicated probe-side activation/deactivation logic;
- marker occurrence/dedupe, exact-source operation, C1 offense obligation, rearm, marker-owned window and StatePosition behavior remain generic existing owners.

If actor/C1/source/motion/UseType/marker identity no longer matches the bound execution, deny authorization and preserve the existing unsupported/native behavior. Do not guess or repair stale probe identity.

## Protected behavior

The task must preserve:

- raw8 Sprint FIST behavior and timing permission;
- raw55 Sprint-origin PhysicalFist behavior and immutable origin handling;
- true Power behavior through the same `OnAI_PowerAttack` transport;
- all equipped Normal/Quick/Whirl/Power/Pierce/SimpleWhirl/Hack behavior;
- unmarked Sprint native fallback;
- LEFT/BOTH equipped Sprint unsupported behavior;
- non-raw2 equipped Sprint unsupported behavior;
- C1 lifecycle/repair semantics;
- diagnostic/behavior twin separation;
- one physical hook owner in `EngineBridge`.

Do not modify `Raw8FistCollision` or `PhysicalFistCollision` unless source inspection reveals a direct compile/interface dependency. If such a semantic change appears necessary, STOP and report the contradiction instead of broadening.

## Expected files

Allowed implementation surface:

```text
prototypes/Script_FrameCollisionTest/EquippedSprintProbe.cpp        NEW
prototypes/Script_FrameCollisionTest/EquippedSprintProbe.h          NEW
prototypes/Script_FrameCollisionTest/EngineBridge.cpp               minimal delegation only
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.cpp      diagnostic-only authorization seam only
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.h        only if needed for the narrow seam
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp       compact probe logging only if needed
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h         compact probe logging only if needed
prototypes/Script_FrameCollisionTest/CMakeLists.txt                  diagnostic target inclusion only
```

If another source file requires semantic behavior changes, STOP and report before broadening.

Do not modify production `src/`, evidence ledgers, architecture/reference docs, or runtime artifacts.

## Runtime acceptance question for Normal Chat + User

After independent source review and local build/deploy, the Goblin fixture should prove all of the following in one or more attributable Sprint executions:

```text
callback classified factual Action9 / Sprint
probe eligibility accepted for exact RIGHT raw2 marked execution
native early callback-owned 5 -> 7 does NOT occur before marker
G3AB_COL_RIGHT is ACCEPTED (not REJECTED_UNSUPPORTED_HIT)
RIGHT source is 5 before authored marker
authored RIGHT causes/rearms Item_Attack(7)
if an authored OFF occurs in the fixture, OFF is accepted through the generic equipped path and deactivates the marker-owned source set
native ONDAMAGE to player occurs
native exact-source cleanup returns 7 -> 5
C1 finalizes Outstanding=0
no terminal repair required
no ownership/invariant/divergence error
```

Failure of attack progression, damage, cleanup, or C1 closure falsifies the direct-extension hypothesis and returns the question to architecture/research.

## Sentinel plan after primary Goblin proof

Do not run broad regression before the Goblin causal result is understood.

If Goblin passes, first run small shared-transport sentinels:

1. Sabretooth raw8 Sprint — must remain healthy;
2. Troll/BlackTroll raw55 Sprint-origin — must remain healthy;
3. one equipped true-Power sentinel (Demon or Ogre is sufficient for the causal gate).

If those pass, Normal Chat may freeze permanent promotion. After production promotion and rebuild, a broader confidence pass may include the User's proposed Goblin, Sabretooth, Ogre, Demon, Stalker, Orc and Troll fixtures before resuming Phase 4.

## Static validation

Work may perform source/static checks only.

Required:

- `git diff --check`;
- verify probe files are compiled only into `Script_FrameCollisionTest`;
- verify `Script_FrameCollisionBehaviorTest` has no probe source and no behavior change from pre-probe semantics;
- verify no production `src/` file changed;
- verify raw8/raw55 permanent modules are unchanged;
- verify the generic Sprint rejection remains the default when the diagnostic probe does not explicitly authorize the exact execution;
- inspect final diff against this contract.

Build execution is PROHIBITED.

## Publication

The User authorizes this bounded diagnostic-only causal probe to be committed and pushed directly to:

`docs/collision-source-evidence`

Start from the exact remote HEAD stated by the launcher.

## Required Work report

Report:

- final remote commit SHA;
- changed files;
- exact probe eligibility/binding implemented;
- exact bridge and marker permission seams added;
- confirmation behavior-only twin remains unchanged;
- protected raw8/raw55/true-Power behavior audit result;
- static validation result;
- any material source contradiction;
- `Build: NOT ATTEMPTED — prohibited by task.`

Then STOP.

Do not interpret runtime behavior, promote equipped Sprint to permanent support, create EV evidence, or archive this task. Normal Chat owns those steps after the User's runtime test.

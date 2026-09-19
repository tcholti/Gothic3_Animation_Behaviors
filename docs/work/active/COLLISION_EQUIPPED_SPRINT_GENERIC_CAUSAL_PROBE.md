# Generic Equipped Sprint Causal Probe

**Status:** ACTIVE  
**Type:** Bounded diagnostic-only causal implementation  
**Created:** 2026-09-19  
**Owner:** Work Chat implements; Normal Chat independently reviews and interprets runtime result.

## Purpose

Test the scope question discovered at EV-311 at the correct framework level:

> Can factual equipped Sprint attacks (`Action=9 / Family=SPRINT`) safely use the already-established generic equipped authored-marker mechanism when the native early `OnAI_PowerAttack` timing is suppressed and authored equipped markers become collision authority?

The first runtime fixture remains the exact EV-311 Goblin RIGHT/raw2 execution. That fixture is **evidence**, not the architectural support boundary.

This is **not** production promotion. No equipped Sprint support is established until runtime proves the causal handoff and protected mechanisms remain intact.

Phase 4 non-weapon regression remains temporarily held while this question is resolved.

## Recovery / supersession note

A narrower diagnostic implementation was already published at:

`1ae0731cd501e6d72bbbf6642188a3047d134805`

and the narrow contract was then adjusted at:

`91da15e11a9b1dfabe8b4eb34b825c4d2c329415`.

Neither version was built or runtime-tested.

Those revisions are superseded because they incorrectly turned the first discovered fixture into a framework restriction:

- RIGHT only;
- 1H/raw2 only;
- later RIGHT + OFF only.

Do **not** build or runtime-test the current narrow source before this task replaces those fixture-specific restrictions.

## Evidence and authority basis

EV-311 supplies the first exact fixture:

```text
Actor      = Goblin
Action     = 9
Family     = SPRINT
Motion     = Goblin_Stand_None_1H_P0_PowerAttack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
RIGHT      = It_1H_Club_01 / UseType 2
marker     = G3AB_COL_RIGHT
current result = REJECTED_UNSUPPORTED_HIT
```

The current unmodified/native path opens the exact equipped source before the authored marker; the marker is rejected because equipped Sprint is deliberately unsupported.

The established equipped marker architecture already defines:

```text
RIGHT -> {RIGHT}
LEFT  -> {LEFT}
BOTH  -> {RIGHT, LEFT}
OFF   -> {}
```

and scans the complete current motion into a `requiredSourceMask`. Existing generic source validation requires every source named by that mask to exist before marker ownership is accepted.

FIST remains separate:

```text
equipped markers: RIGHT / LEFT / BOTH / OFF
raw8 Fist:        FIST marker, separate mechanism
raw55 PhysicalFist: FIST marker, separate permanent mechanism
```

The probe must not collapse those mechanisms together.

## Frozen causal hypothesis

For a factual equipped Sprint Hit whose authored motion requests at least one equipped source:

```text
Action = Sprint / 9
+ Hit phase / attack-hit eligible
+ matching current marked motion
+ at least one activating equipped marker: RIGHT and/or LEFT and/or BOTH
+ no FIST markers mixed into the motion
+ requiredSourceMask != NONE
+ every source required by requiredSourceMask exists
+ valid current C1 generation
-> suppress original OnAI_PowerAttack callback for this execution
-> bind the execution identity
-> permit RIGHT / LEFT / BOTH / OFF on that bound execution to pass the Sprint-specific unsupported gate
-> existing FrameCollisionMarkers generic validation and execution remains authoritative
-> Gothic still owns target/contact/damage and native cleanup
```

There is **no Sprint-specific source UseType restriction** in this hypothesis. Goblin raw2 is only the first fixture.

An OFF-only Sprint animation does not claim probe ownership because it requests no activating equipped source. Unmarked Sprint also remains native/excluded.

## Exact diagnostic scope

Probe ownership is factual and generic:

```text
family/action            = Sprint / Action9
phase                    = Hit / attack-hit eligible
marker family            = equipped RIGHT / LEFT / BOTH / OFF
activating requirement   = requiredSourceMask != NONE
source availability      = existing generic HasRequiredCollisionSources(...)
FIST                     = excluded from this probe
UseType restriction      = NONE added by this probe
species restriction      = NONE
unmarked Sprint          = native / excluded
OFF-only Sprint          = native / excluded
FIST-mixed motion        = excluded; existing FIST mechanisms keep ownership
```

The complete-motion `requiredSourceMask` remains authoritative. For example, a motion authored with both RIGHT and LEFT requirements is not partially accepted for an actor that lacks LEFT.

## Required architecture

Retain the temporary diagnostic-only module:

```text
prototypes/Script_FrameCollisionTest/EquippedSprintProbe.cpp
prototypes/Script_FrameCollisionTest/EquippedSprintProbe.h
```

The probe owns only:

- deciding whether the current factual Sprint execution qualifies for this diagnostic handoff;
- binding actor + current C1 generation + current motion + the relevant exact equipped source identity needed to prevent stale reuse;
- authorizing the generic equipped marker path for the same bound execution;
- compact probe-specific diagnostics proving suppress/delegate and authorize/deny decisions.

`EngineBridge` remains transport-only. It may ask the probe whether to suppress/delegate the existing `OnAI_PowerAttack` callback and pass the probe's generic authorization result to `FrameCollisionMarkers`.

`FrameCollisionMarkers` remains owner of:

- authored marker presence/count validation;
- complete-motion `requiredSourceMask`;
- required-source existence checks;
- RIGHT / LEFT / BOTH desired-set semantics;
- OFF deactivation semantics;
- occurrence/dedupe budget;
- exact-source activation/rearm;
- marker-owned window identity;
- C1 offense obligation;
- StatePosition behavior;
- cleanup/lifecycle interaction.

Do **not** duplicate any of those behaviors in `EquippedSprintProbe`.

The behavior-only twin must remain unchanged in runtime semantics. The probe compiles only into `Script_FrameCollisionTest`, never `Script_FrameCollisionBehaviorTest`.

## Required implementation correction from 1ae0731

The current narrow source must be generalized, not layered with more fixture exceptions.

Remove the probe's fixture-specific assumptions:

- `HasExactRightMarkerShape()`;
- `requiredSourceMask == SourceMask_Right`;
- RIGHT-only source binding/authorization;
- `gEUseType_1H / raw2` checks;
- RIGHT-only marker permission;
- log naming/reasons that claim RIGHT/raw2 is the support boundary.

Replace them with the smallest generic execution-level permission consistent with this contract.

At callback time, eligibility should reuse the already-computed `AttackCallbackOwnershipResult` and existing generic source validation rather than reimplementing hand-specific policy.

At marker time, the permission seam may authorize only the equipped marker vocabulary `RIGHT / LEFT / BOTH / OFF` for the same bound execution. After that seam, existing `FrameCollisionMarkers::ProcessMarker()` must perform its normal authored-marker, source, occurrence, activation/deactivation and lifecycle checks.

The probe must not treat OFF as an activating source. OFF is allowed only because the execution was already bound by at least one activating equipped marker in the complete motion.

## Bound-execution safety

Authorization must fail safely when the bound execution is no longer the same factual execution.

At minimum preserve:

- same actor;
- factual Action9 / Sprint Hit;
- same valid C1 generation;
- same current motion identity;
- required equipped source identity still matches the bound execution according to the motion's required source mask.

Do not invent recovery for stale bindings. Deny authorization and preserve existing native/unsupported behavior when identity no longer matches.

## Protected behavior

This task must preserve unchanged:

- raw8 FIST Normal/Power/Quick/Sprint mechanisms;
- permanent raw55 PhysicalFist Normal/Quick/Power/Sprint-origin mechanisms;
- true equipped Power behavior through `OnAI_PowerAttack`;
- all non-Sprint equipped marker behavior;
- unmarked Sprint native behavior;
- unsupported/malformed marker rejection;
- C1-R1 cleanup rules;
- production/behavior-only build semantics.

No species gate. No raw2 gate. No custom damage. No custom target/contact dispatch. No new terminal cleanup system.

## Required diagnostics

Use one compact diagnostic family such as:

```text
CORE EQUIPPED_SPRINT_PROBE
```

It must make the causal result reviewable without broad logging.

At callback boundary record enough to distinguish:

```text
SUPPRESS_NATIVE
DELEGATE_NATIVE
reason
actor
Action / phase / family
C1 generation
motion
requiredSourceMask
current RIGHT / LEFT source identity
```

At marker boundary record enough to distinguish:

```text
AUTHORIZE_GENERIC_EQUIPPED
DENY_GENERIC_EQUIPPED
marker opcode
bound/current identity match
```

Do not add deep logging unless the bounded causal result cannot be interpreted otherwise.

## First runtime fixture and pass criteria

The first runtime test remains EV-311's Goblin Sprint RIGHT/raw2 motion.

For that exact fixture, PASS requires the log and user-observed attack behavior to show:

```text
factual Action9 / SPRINT Hit recognized
probe suppresses native early OnAI_PowerAttack callback
native early callback-owned 5 -> 7 does NOT occur before marker
G3AB_COL_RIGHT is accepted through generic equipped marker processing
RIGHT source is 5 before authored marker
authored RIGHT causes/rearms Item_Attack(7)
native ONDAMAGE to player occurs
native exact-source cleanup returns 7 -> 5
C1 finalizes Outstanding=0
attack progression remains normal
no raw8/raw55/true-Power ownership contradiction
```

The Goblin pass proves the causal handoff for the first fixture. It does **not by itself** prove every marker/source combination.

## Follow-up after first PASS

Only after Normal Chat independently reviews a Goblin PASS:

1. run the existing protected sentinels required to prove no regression:
   - raw8 Sprint;
   - raw55 Sprint-origin;
   - one equipped true-Power route;
2. exercise additional factual equipped Sprint fixtures across other available equipped UseTypes/animation sets where possible (for example Orc/Demon/Ogre/Stalker families already used in regression);
3. if RIGHT/LEFT/BOTH/OFF combinations cannot be exercised by vanilla actors, deliberately authored diagnostic fixtures may be designed later rather than narrowing the framework contract to vanilla limitations;
4. only then decide whether permanent promotion is justified.

Do not create production support, archive this task, or update settled collision reference facts merely because the code compiles.

## Build status

The superseded `1ae0731...` implementation was **NOT BUILT / NOT RUNTIME TESTED**.

Work should report:

- final remote commit SHA;
- changed files;
- concise explanation of how fixture-specific RIGHT/raw2 restrictions were removed;
- confirmation that generic source/marker mechanics remain owned by `FrameCollisionMarkers`;
- build status (normally NOT ATTEMPTED unless the Work launcher explicitly authorizes a build);
- contradictions, if any.

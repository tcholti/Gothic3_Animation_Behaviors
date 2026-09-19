# Generic Equipped Sprint Causal Probe

**Status:** ACTIVE — DIAGNOSTIC CAUSAL CASE ACCEPTED / PRODUCTION-PROMOTION DECISION NEXT  
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

## Current reviewed implementation

Reviewed diagnostic runtime candidate:

`d2c6c8be0d56129ec6725571324a9066b181242c`

Normal Chat independently reviewed the published Work diff against this frozen contract on 2026-09-19. Result: **SOURCE REVIEW PASS** — no material contract violation identified. The implementation was subsequently built/deployed with DLL SHA256 `A42176DC0309662932089324565CAFBEC77DCA51D9CCCF2D3958B31CBD33CFC7`; build, deployment/hash and startup/load gates PASS.

The review specifically confirmed that:

- RIGHT/raw2 fixture restrictions were removed;
- complete-motion `requiredSourceMask` and generic `HasRequiredCollisionSources(...)` govern eligibility;
- required RIGHT/LEFT source identity is bound according to that mask;
- generic permission is limited to RIGHT / LEFT / BOTH / OFF;
- FIST remains outside the generic Sprint permission path;
- `FrameCollisionMarkers` still owns authored-marker validation, occurrence/dedupe, source activation/deactivation/rearm, windows, C1 behavior and StatePosition;
- raw55 marker ownership still runs before the generic marker path;
- true Power and behavior-only runtime semantics remain outside the diagnostic Sprint seam.

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

## First fixture runtime result

EV-315 closes the first Goblin fixture as **CAUSAL PASS**.

Two factual Action9/SPRINT executions independently showed the required sequence:

```text
C1 starts RIGHT group 5
-> diagnostic probe SUPPRESS_NATIVE
-> no Goblin RIGHT 5 -> 7 before authored marker
-> AUTHORIZE_GENERIC_EQUIPPED at RIGHT marker
-> generic FrameCollisionMarkers RIGHT activation 5 -> 7
-> native ONDAMAGE to PC_Hero
-> native exact-source cleanup 7 -> 5
-> C1 final Outstanding=0
```

Later ordinary Action1/NORMAL markers were denied by the Sprint probe and still accepted by ordinary marker processing, providing a useful scoping control.

This proves the causal handoff only for the first Goblin RIGHT/raw2 fixture. It does not promote equipped Sprint support or prove untested marker/source combinations.

## Protected sentinel results

### EV-316 — raw8 Sprint sentinel PASS

Five factual native-Sabretooth Action9/SPRINT generations confirmed the established raw8 mechanism while this diagnostic seam was active:

```text
raw8 ownership confirmed
-> EquippedSprintProbe DELEGATE_NATIVE / FIST_MARKER_PRESENT
-> FIST accepted
-> latch 1 -> 0 confirmed
-> bounded timing permission armed/used
-> native ONDAMAGE to PC_Hero
-> C1 final Outstanding=0
```

A later same-C1 Action2/POWER replay of the same PowerAttack-named motion produced one `REJECTED_C1_GENERATION_INCONSISTENCY` FIST dispatch per sampled Sprint generation. This occurred after the valid Sprint FIST/contact and cleanly failed closed; it was not captured in the older EV-251 sample and is retained as a bounded observation, not a sentinel failure.

Next protected sentinel: raw55 Sprint-origin.

### EV-317 — raw55 Sprint-origin sentinel PASS

Four factual Troll Sprint-origin C1 generations (9, 21, 37, 58) preserved the permanent raw55 mechanism while this diagnostic seam was active:

```text
Action9 / SPRINT origin
-> EquippedSprintProbe DELEGATE_NATIVE / FIST_MARKER_PRESENT
-> permanent raw55 suppresses premature RIGHT 5 -> 7
-> authored FIST at SP1 opens exact RIGHT 5 -> 7
-> native damage to PC_Hero
-> same-C1 Action9 -> Action2 continuation
-> native cleanup 7 -> 5
-> C1 final Outstanding=0
```

Whole-log checks found no contradiction, rejection or lifecycle failure. This is a protected-coexistence sentinel only; it does not broaden permanent raw55 scope or promote equipped Sprint.

Next protected sentinel: one equipped true-Power route.

### EV-318 — equipped true-Power sentinel PASS

Player 2H true Power with RIGHT Flamberge/raw3 remains entirely under the established generic equipped-Power owner:

```text
Action2 / POWER
-> existing ATTACK_OWNERSHIP SuppressNative=1 / ROUTINE
-> EquippedSprintProbe is not reached for PC_Hero
-> RIGHT marker accepted
-> exact Flamberge 5 -> 7
-> native Golem contact where geometry permits
-> native cleanup to group5
-> C1 final Outstanding=0
```

The run contains 25 distinct accepted true-Power marker C1s and 12 native Golem damage contacts, with zero true-Power marker rejection, repair, contradiction or lifecycle failure.

Protected sentinel stage is therefore **COMPLETE/PASS**:

```text
EV-316 raw8 Sprint         PASS
EV-317 raw55 Sprint-origin PASS
EV-318 equipped true Power PASS
```

Next: additional factual equipped-Sprint fixtures across other available equipped UseTypes/animation sets.

### EV-319 — Ogre raw52 broader fixture NOT EXERCISED

The first broader cross-UseType attempt used Ogre / `It_Axe_OgreMorningStar_01` / raw52. The run remained healthy but never entered factual Action9/SPRINT:

```text
Ogre Sprint Action9 count = 0
true Power ownership       = 10
Normal ownership           = 10
Quick ownership            = 6
accepted RIGHT markers     = 28
damage events to PC_Hero   = 26
Ogre final Outstanding!=0  = 0
```

Therefore EV-319 is neither a Sprint PASS nor FAIL. Do not infer raw52 Sprint support from it and do not repeat the identical fixture without a reason to expect factual Action9. Broader fixture selection should prefer routes with evidence that Action9 can actually occur.

### EV-320 — RIGHT -> OFF exposes same-C1 Sprint-origin gap

Controlled RIGHT -> OFF authoring reached the known factual Goblin Sprint route. RIGHT was accepted under Action9/SPRINT and opened the exact club 5 -> 7. Before the later OFF event, Gothic changed the same C1/motion to Action2/POWER. The current probe then denied OFF as NOT_FACTUAL_SPRINT_HIT, and generic marker bookkeeping rejected it as REJECTED_C1_GENERATION_INCONSISTENCY because the marker-owned window/budget identity is action-sensitive.

This is a bounded implementation gap: the execution is still the same C1, motion and exact source, but current action no longer equals the immutable Sprint origin.

Correction authority is frozen separately in:

`docs/archive/investigations/COLLISION_EQUIPPED_SPRINT_ORIGIN_CONTINUATION_CORRECTION.md`

Do not broaden this into generic cross-action identity weakening.

### EV-321 — BOTH with missing LEFT negative PASS

Controlled BOTH authoring produced RequiredMask=RIGHT|LEFT while the Goblin had only RIGHT. The Sprint probe correctly delegated native with REQUIRED_EQUIPPED_SOURCE_MISSING, created no bound Sprint execution, denied BOTH at the marker, and Gothic's native path still opened/damaged/cleaned RIGHT. This closes the missing-required-source negative path.

### EV-322–EV-324 — continuation correction acceptance COMPLETE/PASS

The bounded EV-320 correction was implemented at `c338d9224a4de6b81466ba5b9e2a3e3c8ba67f86`, independently source-reviewed PASS, then runtime-accepted:

- EV-322: RIGHT -> OFF positive continuation PASS. Same bound Sprint C1 survives current Action9 -> Action2; OFF is authorized as `BOUND_SPRINT_ORIGIN_POWER_CONTINUATION`, remains factually logged Action2/POWER, is accepted and closes exact RIGHT 7 -> 5.
- EV-323: BOTH with LEFT absent negative rerun PASS. `RequiredMask=3` still delegates native on missing LEFT, creates no Sprint binding, rejects BOTH and preserves native fallback.
- EV-324: equipped 2H true-Power protected control PASS. Ordinary true Power remains under existing equipped-Power ownership; PC_Hero produces zero Sprint-probe records and zero continuation signatures.

The diagnostic causal case is now accepted. Production equipped-Sprint support remains intentionally unpromoted pending an explicit parent-level promotion decision.

## Follow-up after first PASS

Only after Normal Chat independently reviews a Goblin PASS:

1. complete the existing protected sentinels required to prove no regression:
   - raw8 Sprint = PASS at EV-316;
   - raw55 Sprint-origin = PASS at EV-317;
   - one equipped true-Power route = PASS at EV-318;
2. exercise additional factual equipped Sprint fixtures across other available equipped UseTypes/animation sets where possible (for example Orc/Demon/Ogre/Stalker families already used in regression);
3. deliberately authored fixtures EV-320–EV-321 are now available: missing-LEFT BOTH is PASS, while RIGHT->OFF exposed the same-C1 Action9->Action2 continuation gap;
4. bounded origin-continuation correction is accepted through EV-322–EV-324;
5. next make the explicit production-promotion decision: whether to translate the proven diagnostic seam into behavior-facing architecture, with release-purity and diagnostics-free validation planned separately.

Do not create production support, archive this task, or update settled collision reference facts merely because the code compiles.

## Build status

Reviewed generic implementation `d2c6c8be0d56129ec6725571324a9066b181242c` completed the initial causal/sentinel stages. Continuation correction `c338d9224a4de6b81466ba5b9e2a3e3c8ba67f86` was independently reviewed, locally built/deployed, startup-verified and runtime-accepted through EV-322–EV-324. The exact post-correction DLL SHA256 was not captured in the Normal Chat transcript; do not reuse the earlier `A421...` hash as identity for the corrected build.

The superseded `1ae0731...` implementation was **NOT BUILT / NOT RUNTIME TESTED**.

Work should report:

- final remote commit SHA;
- changed files;
- concise explanation of how fixture-specific RIGHT/raw2 restrictions were removed;
- confirmation that generic source/marker mechanics remain owned by `FrameCollisionMarkers`;
- build status (normally NOT ATTEMPTED unless the Work launcher explicitly authorizes a build);
- contradictions, if any.

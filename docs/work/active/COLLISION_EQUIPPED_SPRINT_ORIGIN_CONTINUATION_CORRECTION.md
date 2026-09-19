# Equipped Sprint Origin-Continuation Correction

**Status:** ACTIVE — EV-322 POSITIVE + EV-323 NEGATIVE PASS / TRUE-POWER CONTROL PENDING  
**Type:** Bounded diagnostic-only correction  
**Created:** 2026-09-19  
**Owner:** Work Chat implements; Normal Chat independently reviews and owns runtime interpretation.

## Purpose

Correct only the execution-identity gap proven by EV-320:

> An already-bound factual equipped Sprint execution can remain the same C1, motion and exact equipped source while Gothic changes current factual action from Action9/SPRINT to Action2/POWER before a later authored equipped marker such as OFF.

The current diagnostic implementation loses ownership at that transition even though the execution identity has not changed.

This task must preserve **immutable Sprint origin** for the already-bound diagnostic execution without weakening generic action identity for unrelated attacks.

## Required base state

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Read first:

1. `README.md`
2. `docs/SESSION_ENTRYPOINT.md`
3. `docs/BETWEEN_CHATS.md`
4. `docs/work/active/COLLISION_EQUIPPED_SPRINT_GENERIC_CAUSAL_PROBE.md`
5. this file
6. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
7. `docs/FEATURE_DEVELOPMENT_METHOD.md`

Evidence authority:
- EV-315 — first factual Goblin Sprint RIGHT handoff PASS.
- EV-316–EV-318 — protected sentinels PASS.
- EV-320 — RIGHT -> OFF exposes Action9 -> Action2 same-C1 continuation gap.
- EV-321 — BOTH with missing LEFT negative PASS.

## Exact causal finding

EV-320 repeatedly shows:

```text
same Goblin
same C1 generation
same PowerAttack-named motion
same requiredSourceMask=RIGHT
same exact RIGHT club identity
Action9 / SPRINT at RIGHT
-> RIGHT authorized
-> exact RIGHT 5 -> 7
-> native contact can occur
-> Gothic changes current action to Action2 / POWER
-> authored OFF arrives
-> probe DENY: NOT_FACTUAL_SPRINT_HIT
-> generic marker result REJECTED_C1_GENERATION_INCONSISTENCY
-> later native cleanup 7 -> 5
```

The generic rejection is expected from current source because marker-owned window and occurrence-budget identity store the factual action. The first marker created those records with Action9; OFF arrives with Action2.

Permanent raw55 already establishes the relevant architecture precedent with an immutable `originFamily` and an allowed Sprint-origin -> current-Power continuation guarded by exact execution identity. Do not couple the modules or reuse raw55 source-specific policy; use only the same architectural principle.

## Frozen responsibility

Implement the smallest diagnostic-only correction that allows an **already-bound equipped Sprint-origin execution** to continue through current Action2/POWER for later generic equipped markers when, and only when, the original execution identity remains exact.

### A. Sprint binding remains origin authority

A binding may still be created only from the already-proven factual callback condition:

```text
Action9 / Family SPRINT
Hit eligible
matching valid marked motion
no FIST mixing
requiredSourceMask != NONE
all required equipped sources exist
valid current C1
```

Do not create a Sprint binding from Action2/POWER.

### B. Allowed continuation is narrow

For a previously bound Sprint execution, current POWER/Action2 may be treated as a continuation only when all durable identity facts still match:

- same actor;
- same C1 generation;
- same motion identity;
- same complete-motion requiredSourceMask;
- all required sources still exist;
- exact required RIGHT/LEFT source identities still match;
- current phase remains attack Hit;
- current family/action is either original Sprint/9 or the exact allowed continuation Power/2.

Any different generation, motion, source identity, required mask, unsupported family/action or malformed marker state must fail closed and invalidate/deny as appropriate.

A new true-Power execution must never inherit a prior Sprint binding.

### C. Callback-side preservation only

If `EquippedSprintProbe::ShouldSuppressNativeCallback()` is reached during the exact same bound Sprint-origin execution after current family becomes POWER, it must **not erase the binding merely because current family is no longer Sprint**.

That continuation path must not claim a new true-Power execution and must not introduce a new native-suppression policy. Preserve/delegate according to the existing callback ownership architecture; the responsibility here is binding continuity, not Power ownership.

### D. Marker authorization

`AuthorizeGenericEquippedMarker()` may authorize RIGHT / LEFT / BOTH / OFF for:
- the original factual Sprint/9 state; or
- the exact same bound Sprint-origin execution while current factual state is Power/2.

Diagnostics must distinguish the continuation case, e.g. a stable reason such as:

`BOUND_SPRINT_ORIGIN_POWER_CONTINUATION`

Do not authorize FIST.

### E. Generic marker execution identity

The current generic marker-owned window and occurrence budget are action-sensitive. Do **not** globally weaken that rule.

For a marker explicitly authorized by the diagnostic equipped-Sprint seam, keep the generic marker execution identity canonical to the bound Sprint origin across the allowed Action9 -> Action2 continuation. The implementation may use a diagnostic-only canonical execution-action/family value or an equivalent narrow mechanism.

The correction must cover the generic state that otherwise rejects EV-320:
- marker-owned window identity;
- authored-marker occurrence/budget identity;
- any duplicate/accepted-marker identity that must remain consistent for the same authored execution.

Factual runtime action must remain observable in diagnostics; do not falsify the logged current action merely to make identity compare equal.

### F. Keep generic semantics owned by FrameCollisionMarkers

After the diagnostic authorization/identity seam:
- RIGHT / LEFT / BOTH desired-set semantics remain unchanged;
- OFF remains the existing deactivation operation;
- source activation/rearm remains unchanged;
- source retirement remains unchanged;
- C1 offense obligations remain unchanged;
- native target/contact/damage remains Gothic-owned;
- native cleanup/repair rules remain unchanged.

Do not reimplement those semantics in `EquippedSprintProbe`.

## Explicit non-responsibilities

Do NOT:
- add production equipped-Sprint support;
- change the behavior-only twin's runtime semantics;
- weaken action identity for ordinary Normal/Quick/Power/Whirl/Pierce/Hack/etc.;
- allow arbitrary cross-action continuation;
- add species or UseType gates;
- add custom damage or target dispatch;
- change raw8 FIST behavior;
- change permanent raw55 behavior;
- modify callback RVAs/calling conventions;
- make BOTH partially activate when a required source is absent;
- reinterpret EV-321 as an error.

## Required files / source boundary

Inspect and modify only what the frozen correction actually requires, expected primarily:

```text
prototypes/Script_FrameCollisionTest/EquippedSprintProbe.cpp
prototypes/Script_FrameCollisionTest/EquippedSprintProbe.h
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.cpp
prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.h
```

`EngineBridge.cpp` may change only if the existing diagnostic seam must carry the minimum additional continuation identity; do not broaden hook ownership.

Behavior-only product semantics must remain unchanged.

## Required runtime acceptance after Normal Chat review

Primary positive fixture: the same EV-320 Goblin RIGHT -> OFF motion.

PASS requires:

```text
Action9 / SPRINT callback binds execution
RIGHT authorized and accepted
RIGHT exact club 5 -> 7
same C1/motion/source later becomes current Action2 / POWER
OFF is authorized as bound Sprint-origin continuation
generic OFF is accepted
OFF closes the marker-owned RIGHT source 7 -> 5 at OFF timing
no REJECTED_C1_GENERATION_INCONSISTENCY for that OFF
C1 final Outstanding=0
```

Required negative control: repeat EV-321 BOTH with LEFT absent.

PASS requires:
- `RequiredMask=3`;
- no Sprint binding;
- `REQUIRED_EQUIPPED_SOURCE_MISSING`;
- BOTH denied/rejected;
- native fallback remains available;
- clean finalization.

Required protected control: equipped true-Power route from EV-318.

PASS requires true Power remain outside Sprint-origin inheritance/authorization.

## Build policy

Work does not build unless the current implementation protocol explicitly authorizes it. User performs local build/deploy/runtime after independent Normal Chat source review.

## Stop condition

Work stops after implementing only this bounded correction, static audit, commit and push.

Report:
- final remote commit SHA;
- changed files;
- concise implementation result;
- confirmation that only bound Sprint-origin Action9 -> Action2 continuation is admitted;
- confirmation that ordinary true Power remains outside the seam;
- build status;
- any material contradiction.


## Independent Normal Chat source review

Reviewed implementation:

`c338d9224a4de6b81466ba5b9e2a3e3c8ba67f86`

Changed files:
- `prototypes/Script_FrameCollisionTest/EquippedSprintProbe.cpp`
- `prototypes/Script_FrameCollisionTest/FrameCollisionMarkers.cpp`

Review result: **PASS**.

Confirmed:
- Sprint bindings are still created only from factual eligible Action9/SPRINT.
- A current Action2/POWER callback can preserve an existing Sprint binding only when C1 generation, motion identity, complete-motion required-source mask, source availability and exact required source identities still match.
- That Power continuation delegates native and introduces no new callback suppression.
- Marker authorization admits Action2/POWER only when the same prior Sprint binding survives those identity checks.
- The continuation is surfaced as `BOUND_SPRINT_ORIGIN_POWER_CONTINUATION`.
- Generic marker bookkeeping uses canonical Action9 identity only for a marker explicitly authorized by the diagnostic Sprint seam; factual `markerAction` remains unchanged for diagnostics.
- Window identity, occurrence budget, duplicate identity and accepted-marker identity all use that same diagnostic-only canonical execution action.
- `FRAME_COLLISION_DIAGNOSTICS` guards the new canonicalization; behavior-only semantics remain unchanged.
- `EquippedSprintProbe` remains diagnostic-product-only in CMake.
- Raw8/raw55 code, callback hook ownership and generic marker desired-set/source-operation semantics were not changed.
- No species/UseType special case was introduced.
- The EV-321 missing-LEFT/BOTH negative policy is structurally preserved.
- The EV-318 true-Power route cannot create Sprint ownership; runtime remains required to confirm no stale-binding inheritance.

Static review cannot replace the required runtime acceptance. Next gate is local build/deploy/startup, then EV-320 positive rerun, EV-321 negative rerun, and EV-318 true-Power protected control.


## EV-322 runtime result

Positive RIGHT -> OFF correction fixture: **PASS**.

Six complete Goblin P0 Sprint-origin executions (C1 24, 34, 45, 84, 92, 101) repeated the required sequence:

```text
Action9 / SPRINT
-> RIGHT authorized + accepted
-> exact club 5 -> 7
-> same C1/motion/source becomes current Action2 / POWER
-> OFF AUTHORIZE_GENERIC_EQUIPPED
   Reason=BOUND_SPRINT_ORIGIN_POWER_CONTINUATION
-> OFF_ACCEPTED while diagnostics still show Action2 / POWER
-> exact club 7 -> 5 at OFF timing
-> C1 final Outstanding=0
```

Zero OFF rejection and zero `REJECTED_C1_GENERATION_INCONSISTENCY` occurred.

EV-322 closes only the positive correction gate. Remaining required controls:
1. EV-321 BOTH with LEFT absent negative rerun.
2. EV-318 equipped true-Power protected control.


## EV-323 runtime result

Missing-LEFT/BOTH negative rerun: **PASS**.

Four factual P0 Sprint executions scanned `RequiredMask=3` with RIGHT club present and LEFT absent. All delegated native with `REQUIRED_EQUIPPED_SOURCE_MISSING`; no Sprint binding was created and no continuation authorization occurred.

Three BOTH markers arrived while still Sprint and were denied `NO_BOUND_EXECUTION` / rejected `REJECTED_UNSUPPORTED_HIT`. One arrived after the same C1 became Power and remained outside Sprint inheritance (`NO_BOUND_SPRINT_ORIGIN`), then generic processing rejected it as `UNSUPPORTED_MISSING_SOURCE`.

All four preserved native RIGHT fallback, native damage, 7 -> 5 cleanup and `Outstanding=0`.

Remaining required control:
- EV-318 equipped 2H true Power must remain outside Sprint-origin inheritance/authorization.

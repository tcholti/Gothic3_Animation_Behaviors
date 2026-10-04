# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-04

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `development`  
Required review base HEAD: `a4b2e5bb5cb4e1780a0f79ff7ac867f0187d1346`  
`main` remains frozen.

## Current state

```text
Collision = CLOSED/PASS through EV-390; NOT a review/redesign target
Speed v2 = CLOSED/PASS through EV-410
Raise sequencing = PASS EV-411–EV-412
Raise phase-speed contradiction = EV-413–EV-414
static causal correction = CLOSED EV-415
production correction source = aab0189f2067f00653f669792b7d267135c745f0
independent Normal Chat source review = PASS EV-416
docs/maintenance head = a4b2e5bb5cb4e1780a0f79ff7ac867f0187d1346
runtime acceptance of corrected source = PENDING
```

Frozen corrected behavior:

```text
custom Normal / factual Quick R/L / Whirl AddRaise
-> inserted Raise copies exact incoming composed Hit AniSpeedScale

native Power Raise
-> preserve live Gothic/New Balance Raise value
-> multiply by Power_BaseSpeed / Power_ReferenceHitBaseSpeed
-> e.g. 1.5*M remains 1.5*M*R, never flattened to Hit

Hack / Pierce
-> already coupled; no additional Raise-specific scale
```

## Current assigned responsibility — independent full Speed + Raise implementation audit

This is a **BOUNDED READ-ONLY FORMAL REVIEW / AUDIT** for Work/Astra.

Do not implement fixes.  
Do not modify source.  
Do not modify documentation.  
Do not build, deploy or run Gothic 3.  
Do not create probes or diagnostics.  
Do not begin runtime acceptance.  
Return findings only.

### Authority / preflight

Apply POP-10 before judging the implementation.

Relevant hierarchy:

```text
CAM
-> docs/README.md project charter
-> DESIGN.md / ADRs / SOURCE_HOOK_GUIDE.md as technical owners
-> WORK_IMPLEMENTATION_PROTOCOL / procedures
-> current source + this transient review handoff
```

The review may challenge the implementation if source contradicts authority/evidence, but it must not redefine project purpose, Collision architecture, or accepted Speed/Raise semantics silently.

### Review scope — whole Speed + Raise implementation

Review the **complete current production Speed and Raise implementation**, not only commit `aab0189...`.

Trace end to end:

1. shipping INI/config surface and startup loading;
2. profile parsing/storage;
3. ADR-0011 resolved animation-set profile identity;
4. per-attack settings lookup;
5. Speed hook/call-site transport;
6. compatible/native result capture;
7. `B*M -> C*M` composition;
8. all supported Speed attack families;
9. Sprint -> Power profile inheritance / contextual live result preservation;
10. Finishing exclusion and Hack/Finishing separation;
11. AddRaise Off/native fallback;
12. custom Normal / factual Quick R/L / Whirl Raise insertion;
13. continuation/cancellation/re-entry behavior;
14. custom Raise effective-speed inheritance;
15. native Power Raise composition and preservation of native/live phase relationship;
16. interaction between Speed and Raise when both are configured;
17. shipping defaults and fail-closed behavior;
18. hook ownership/calling convention/RVA/call-site assumptions;
19. simplicity, modularity, performance and unnecessary-complexity review.

Primary production files include, but are not limited to:

```text
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.h
src/Script_G3AnimationBehaviors/AttackRaise.cpp
src/Script_G3AnimationBehaviors/AttackRaise.h
src/Script_G3AnimationBehaviors/EngineBridge.cpp
Ini/G3AnimationBehaviors.ini
```

Inspect directly connected startup/config/source files when needed to complete the Speed/Raise trace. Do not broaden into unrelated systems.

### Technical authorities to use

Start from current authorities rather than reconstructing the full evidence history:

```text
docs/DESIGN.md — Speed + Raise sections
docs/SOURCE_HOOK_GUIDE.md — relevant Speed/Raise/hook sections
docs/ENGINEERING_GUIDE.md — simplicity/modularity/performance principles
docs/decisions/ADR-0004-speed-control-base-speed-preserves-dynamic-modifiers.md
docs/decisions/ADR-0005-raise-speed-config-profiles.md
docs/decisions/ADR-0008-grouped-loadout-profiles-expanded-attack-scope.md
docs/decisions/ADR-0009-sprint-inherits-power-speed-profile.md
docs/decisions/ADR-0011-resolved-animation-set-speed-profile-identity.md
docs/work/active/RAISE_ADDRAISE_RUNTIME_ACCEPTANCE.md
```

Use `EVIDENCE_INDEX.md` only to route to exact EVs when a premise actually needs proof. Do not load the full archived evidence corpus by default.

### Collision freeze / protected boundary

Collision has been repeatedly reviewed and runtime-validated and is **out of scope**.

Do not review, redesign or propose cleanup to:

```text
FrameCollisionMarkers
CollisionSources
CollisionSourceOperations
CollisionLifecycleGuard
Raw8FistCollision
PhysicalFistCollision
EquippedSprintCollision
collision diagnostics
collision marker semantics
collision cleanup/repair policy
```

In `EngineBridge.cpp`, inspect shared hook/transport code only as needed to answer:

```text
Does Speed/ Raise preserve the existing Collision invocation/lifecycle boundary?
Does Speed/ Raise introduce hook ownership, chaining or ordering that could disturb Collision?
```

The accepted Collision implementation, its hooks, its feature modules, and the universal CollisionLifecycleGuard are protected **as-is**.

If the reviewer believes a Speed/ Raise issue cannot be solved without changing Collision, report that as an architectural conflict/stop condition. Do **not** recommend a Collision edit as an ordinary fix.

### Third-party compatibility — MUST PASS

Compatibility with Jackydima New Balance and AttackCollision is a hard product requirement.

Reference repository:

`Jackydima/gothic3sdk`

Pinned review reference:

`bbe769075bc896085a620a0ceb3491192c5beb61` on `master`

Primary compatibility sources:

```text
scripts/Script_NewBalance/
scripts/Script_AttackCollision/
```

Pay particular attention to:

```text
Script_NewBalance/FunctionHook.cpp
Script_NewBalance/CallHook.cpp
Script_NewBalance/GameScripts.cpp
Script_NewBalance/StateFunctions.cpp
Script_NewBalance/Script_NewBalance.cpp

Script_AttackCollision/Script_AttackCollision.cpp
Script_AttackCollision/config.cpp
```

Also search the rest of `scripts/` only when necessary to identify an exact Speed/ Raise hook/API/state overlap.

Compatibility questions:

1. Does our caller-side Speed composition preserve New Balance's live `GetAnimationSpeedModifier` ownership and contextual modifiers?
2. Does any G3AB call cause New Balance's function or side effects to execute twice?
3. Does the new Power Raise caller composition preserve New Balance's phase-specific Power Raise values such as Hero `1.5*M` and Orc `1.3*M`?
4. Are load order / hook chaining assumptions safe for the actual hook types we and New Balance use?
5. Are there overlapping function hooks/call hooks that can overwrite rather than chain?
6. Can custom AddRaise sequencing interfere with New Balance melee-state/action/state-position assumptions?
7. Can Speed/ Raise change AttackCollision timing/state assumptions in a way likely to create a new conflict?
8. Where G3AB and AttackCollision/New Balance use the same Gothic callback/hook family, does current architecture coexist without relying on undefined hook order?
9. Do any proposed changes threaten compatibility that current runtime evidence has already demonstrated?
10. Are there other scripts under Jackydima `scripts/` with an exact Speed/ Raise overlap that materially changes this conclusion?

Existing runtime evidence says the intended New Balance/AttackCollision stack has worked well with G3AB, including places with shared hook surfaces. Treat that as evidence to preserve, not as proof that static review may skip overlap analysis.

### Required semantic checks

Confirm or challenge each of these:

```text
unconfigured/missing profile -> live native/compatible behavior unchanged

ReferenceHitBaseSpeed B
= native Gothic calibration fact
!= New Balance result

compatible live result
= B*M

configured result
= compatible * (C/B)
= C*M

Speed must not globally hook/replace +0x42A0 ownership

Quick Speed / Raise
= factual Action4/5
!= Action3 selector inference

Sprint
= factual Action9 context may travel shared Action2 Power route
= Power profile authoring alias only
= live contextual difference preserved

custom AddRaise
= Normal / factual Quick R/L / Whirl only
= exact incoming Hit AniSpeedScale reused
= no synthetic second speed-owner call

native Power Raise
= live compatible Raise preserved
* Power_BaseSpeed / Power_ReferenceHitBaseSpeed

Hack / Pierce Raise
= no second Raise-specific scale

Finishing
= outside configured Speed surface

Collision
= unchanged/protected
```

### Engineering-quality review

Evaluate against `ENGINEERING_GUIDE.md`:

- generative simplicity;
- minimum sufficient structure;
- one authoritative physical hook owner;
- clear feature ownership;
- no unnecessary state/cache/timer/hook;
- no duplicated New Balance policy;
- no unnecessary hot-path work;
- no per-frame polling;
- fail-closed unsupported paths;
- maintainability and future profile extensibility without weapon/species C++ branching.

Do not suggest refactoring merely for style. A proposed change must fix a concrete correctness, compatibility, maintainability or material performance problem.

### Findings format

Return findings ordered by severity:

```text
BLOCKER
MAJOR
MINOR
NOTE / CONFIRMATION
```

For every BLOCKER/MAJOR/MINOR finding provide:

- exact file/function/hook/call site;
- factual problem;
- why it matters;
- authority/evidence violated;
- smallest safe Speed/ Raise-owned correction;
- New Balance/AttackCollision compatibility consequence;
- explicit confirmation that Collision can remain unchanged, or flag STOP if not.

Then give separate verdicts:

```text
Correctness:
New Balance compatibility:
AttackCollision compatibility:
Collision non-interference:
Simplicity:
Modularity:
Performance:
Configuration/profile architecture:
Hook architecture:
Runtime-test readiness:
```

End with one overall disposition:

```text
PASS — ready for local build/runtime acceptance
PASS WITH NON-BLOCKING NOTES
FAIL — correction required before build/runtime
```

If no substantive defect is found, say so plainly. Do not manufacture changes to justify the review.

## Stop boundary

This review ends with the report.

No repository writes.
No implementation.
No build.
No runtime test.
No documentation maintenance.

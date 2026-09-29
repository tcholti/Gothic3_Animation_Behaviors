# Speed Expanded Scope — Light Independent Review and Sprint Research

**Status:** ACTIVE  
**Task class:** Bounded independent read-only review + focused static research  
**Branch:** `development`

## Purpose

Perform a lighter independent pre-build review of the already-implemented expanded Speed source, then investigate whether Sprint / `gEAction_SprintAttack` (Action9) has a factual safe Speed transport route that the current implementation missed.

This is **not** a second deep audit of the already-proven Speed v2 design. The compatible-composition architecture has already passed static and runtime proof for Normal/Quick and representative New Balance multiplier preservation. The review should focus on implementation quality, hook correctness, project principles, and Sprint evidence.

## Frozen source under review

Production source commit:

```text
642c88a4e6244ae7377ba835507750af7914e2f5
```

Later commits may contain documentation-only maintenance. Judge production behavior against the exact production source above.

## Read first

Start from the repository, not remembered conversation context.

1. root `README.md` — follow **Start Here**
2. `docs/SESSION_ENTRYPOINT.md`
3. `docs/work/active/SPEED_EXPANDED_ATTACK_SCOPE_AND_GROUPED_PROFILE_IMPLEMENTATION.md`
4. `docs/decisions/ADR-0002-engine-hooks-transport-only.md`
5. `docs/decisions/ADR-0004-speed-control-base-speed-preserves-dynamic-modifiers.md`
6. `docs/decisions/ADR-0008-grouped-loadout-profiles-expanded-attack-scope.md`
7. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
8. apply the project's review/audit preflight from `docs/PROJECT_OPERATING_PROCEDURES.md` (POP-10), but keep the review bounded to this task.

Use repository evidence and the pinned external/static references named by the project when needed. Avoid loading large disassembly files wholesale when targeted search/xref inspection is sufficient.

## Responsibility A — implementation and hook review

Review only the expanded Speed implementation and the code paths necessary to judge it.

Primary production files:

```text
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/EngineBridge.cpp
src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini
```

Check especially:

- grouped loadout identity remains `AnimationFamily + LeftAnimationUseType + RightAnimationUseType`;
- independent attack settings for Normal, Quick, Power, Pierce, Hack, SimpleWhirl and Whirl;
- factual action mapping is correct and no generic selector action is treated as playback fact;
- unsupported/unconfigured/invalid cases fail closed to the live compatible value;
- `AttackSpeed` remains stateless and policy-oriented rather than transport-oriented;
- `EngineBridge` remains the sole low-level hook owner and transport only;
- the common thunk calls the live `Script_Game+0x42A0` compatible owner exactly once per intercepted request;
- the `C/B` composition still preserves the live compatible result rather than replacing it with a hard final speed;
- finite guards and ABI/register/x87 return assumptions remain correct;
- the original six Normal/Quick hooks remain correct;
- the nine newly added Hit callers are the intended factual consumers and use correct EAX action provenance / Hit phase;
- Power Raise `Script_Game+0x47D51` is not accidentally intercepted by this Speed-only change;
- no collision, Raise, Recover, family-source, or current-motion-policy drift was introduced;
- no unnecessary complexity, duplicated policy, special-case family table, or evidence-free fallback was added.

Do not re-audit the entire collision subsystem or repeat yesterday's deep Speed v2 audit unless a concrete dependency requires a narrow check.

## Responsibility B — focused Sprint / Action9 research

Independently investigate whether Sprint Speed can be supported safely without redesigning the architecture.

Current accepted state is:

```text
Sprint / Action9 exists as a factual combat action.
Observed Sprint may reuse Power-named animation assets.
No distinct safe Action9 Hit-speed consumer of Script_Game+0x42A0 has yet been proven.
Therefore Sprint is currently fail-closed/native-compatible.
```

Do not treat animation-name reuse or nearby Action9 checks as proof of a Speed route.

Research requirements:

1. Inspect the pinned Script_Game binary reference / xrefs around all relevant `Script_Game+0x42A0` callers and Action9 occurrences.
2. Trace the factual Sprint request/playback path far enough to identify where its animation speed is actually obtained/applied.
3. Check whether Sprint:
   - has a distinct Action9 `+0x42A0` Hit consumer;
   - flows through an existing dynamic carrier already intercepted by G3AB;
   - intentionally reuses a Power speed consumer while retaining factual Action9 elsewhere;
   - bypasses `+0x42A0` for its effective playback speed;
   - or remains unresolved from static evidence.
4. Cross-check pinned New Balance source only to understand compatible policy/action semantics; do **not** infer Script_Game transport from New Balance policy alone.
5. If a candidate Sprint route is found, prove all of the following before calling it safe:
   - exact caller offset(s);
   - factual Action9 provenance at the call;
   - factual phase / Hit applicability;
   - ABI/register assumptions compatible with the common thunk;
   - whether the live compatible owner is still called exactly once;
   - whether adding the route can reuse the existing grouped `AttackType` + common composition mechanism without special-case policy.

Classify the Sprint result as exactly one of:

```text
PROVEN SAFE ROUTE
PLAUSIBLE BUT UNPROVEN
NO DISTINCT ROUTE FOUND / REMAINS UNPROVEN
```

If `PROVEN SAFE ROUTE`, provide the exact minimal implementation surface that would be justified, but **do not implement it**.

## Severity / output

For implementation findings use:

```text
BLOCKER
MAJOR
MINOR
NOTE
```

Final report should contain:

1. review preflight confirmation;
2. concise implementation verdict: `PASS`, `PASS WITH FINDINGS`, or `BLOCKED`;
3. findings ordered by severity with exact file/offset evidence;
4. explicit confirmation of hook/caller correctness or exact exceptions;
5. separate Sprint research conclusion using the required classification;
6. if Sprint is proven, the smallest evidence-backed next implementation step;
7. if Sprint remains unproven, state what specific missing evidence would be needed rather than proposing speculative hooks.

## Prohibitions

Do **not**:

```text
modify production code
modify documentation
commit or push changes
build or deploy
run Gothic 3
begin Raise implementation
add a Sprint hook
redesign Speed v2
reopen collision absent direct contradictory evidence
```

This task ends with a report only. The normal engineering chat will decide and implement any follow-up.

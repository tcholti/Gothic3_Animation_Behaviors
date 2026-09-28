# Speed v2 Deep Independent Static Audit

**Status:** ACTIVE  
**Task type:** FORMAL BOUNDED READ-ONLY AUDIT  
**Feature:** Speed v2 only  
**Production-code edits:** PROHIBITED  
**Build/deploy/game execution:** PROHIBITED  
**Raise work:** PROHIBITED

## 1. Purpose

Perform a fresh, adversarial, independent static audit of the completed Speed v2 production source before local build/deploy/runtime validation.

This audit exists because the preceding implementation/review sequence was interrupted several times and the User wants one heavy pass that independently reconstructs the relevant engine/SDK facts, checks the final code against them, and evaluates the result against the project's simplicity, modularity, ownership, compatibility and fail-closed principles.

This is **not** a request to confirm the previous conclusion. Existing ADRs, EV-391/EV-392 and the prior source review are evidence/history to compare against, not facts that the auditor must preserve. If independent reconstruction contradicts them, report the contradiction.

The audit must answer four questions:

1. Is the low-level six-call transport technically correct for the tested Gothic 3 build and the pinned SDK ABI?
2. Does the source actually implement the intended compatible composition semantics without bypassing Gothic/New Balance behavior?
3. Is the implementation simple, modular, fail-closed and correctly separated according to project engineering principles?
4. Is there any concrete blocker or unnecessary complexity that should be corrected **before** the User builds and runs it?

## 2. Frozen source and references

Production source under audit:

```text
repository: tcholti/Gothic3_Animation_Behaviors
branch lineage: development
exact source target: 4f9911f57d8d6b36efd35adee41920560c3986e0
```

Current documentation/evidence baseline at task creation:

```text
development: f6f5444b28173c915f576f7fe09d7e8d105493b6
```

All source changes after `4f9911f57d8d6b36efd35adee41920560c3986e0` were documentation-only when this audit was frozen. At audit start, verify that this remains true for the Speed-relevant production source. If relevant source has drifted, STOP the normal audit and report the exact drift before judging a mixed target.

Pinned external/static references:

```text
Gothic 3 SDK:
georgeto/gothic3sdk
90bfd344de4510dda7ac9da7461cc7f1eac911f7

Gothic 3 binary/static-analysis reference:
tcholti/Gothic3_Binary_Reference
c9d12cb5f0dcb4f96af6a82c02138c1c15e981b6
builds/current_tested/

Primary New Balance source reference:
Jackydima/gothic3sdk
316d32406a133f8884e7e302752c35f66b4f54fc
scripts/Script_NewBalance/FunctionHook.cpp
```

Do not silently replace these pins with current upstream HEADs.

## 3. Authority/preflight — mandatory before evaluating source

This is a formal review/audit. Apply the repository's formal-review preflight before judging the implementation.

Start from the repository front door and reconstruct only the authority needed for this audit. At minimum establish the relationship:

```text
CAM
-> project charter / authority topology
-> engineering + feature-development principles
-> project operating/review procedure
-> Speed architecture ADRs
-> evidence
-> completed implementation contract
-> this audit task
```

Read/spot-read the current authoritative route, including as needed:

```text
README.md
docs/README.md
docs/SESSION_ENTRYPOINT.md
docs/BETWEEN_CHATS.md
docs/PROJECT_OPERATING_PROCEDURES.md          # formal audit/preflight + relevant procedure rules
docs/FEATURE_DEVELOPMENT_METHOD.md
docs/ENGINEERING_GUIDE.md
docs/WORK_IMPLEMENTATION_PROTOCOL.md
docs/PROJECT_PIPELINE.md
docs/decisions/ADR-0004-*.md
docs/decisions/ADR-0005-raise-speed-config-profiles.md
docs/decisions/ADR-0007-shared-ini-profile-schema.md
docs/EVIDENCE_LEDGER_389_ONWARD.md            # EV-391 and EV-392
docs/archive/investigations/SPEED_V2_CALLER_SIDE_COMPOSITION_IMPLEMENTATION.md
```

Resolve exact ADR-0004 filename from the repository rather than guessing it.

Before evaluating code, write a compact internal audit map distinguishing:

- architecture / intended behavior;
- proven engine/SDK facts;
- historical evidence and prior interpretation;
- implementation responsibility;
- this task's review constraints.

Do not use evidence history as architecture, or architecture as proof that engine behavior exists.

## 4. Hard audit behavior

### 4.1 Independent reconstruction first

For the critical ABI/call-site mechanism, independently inspect the pinned SDK and binary/static-analysis reference before relying on EV-391/EV-392's conclusion.

Use EV-391/EV-392 afterward as a cross-check:

```text
independently re-derived fact
vs
existing evidence claim
```

Classify important conclusions as one of:

```text
INDEPENDENTLY RE-DERIVED
CORROBORATED ONLY
NOT PROVABLE STATICALLY / RUNTIME GATE
CONTRADICTED
```

### 4.2 No repair while reviewing

Do not modify production source, ADRs, evidence ledgers, architecture, CMake, INI, SDK/reference repositories, or runtime files.

If a defect is found:

```text
identify exact defect
-> establish causal impact
-> state smallest repair direction
-> continue only where the finding does not invalidate downstream reasoning
-> final verdict may be BLOCKED
```

Do not implement the fix in this task.

### 4.3 No aesthetic refactor findings

Do not recommend a refactor merely because another structure is prettier.

A simplification/modularity finding must establish concrete value such as:

- removing duplicate ownership;
- eliminating stale conflicting behavior;
- reducing ABI/hook risk;
- making fail-closed behavior clearer;
- removing an unnecessary dependency;
- preventing future misconfiguration;
- removing evidence-free complexity.

Prefer the smaller working design when both designs satisfy the proven responsibility.

## 5. Production source scope

Audit these production surfaces at exact source target `4f9911f...`:

```text
src/Script_G3AnimationBehaviors/EngineBridge.cpp
src/Script_G3AnimationBehaviors/EngineBridge.h
src/Script_G3AnimationBehaviors/AttackSpeed.cpp
src/Script_G3AnimationBehaviors/AttackSpeed.h
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp
src/Script_G3AnimationBehaviors/BehaviorProfiles.h
src/Script_G3AnimationBehaviors/Script_G3AnimationBehaviors.cpp
src/Script_G3AnimationBehaviors/CMakeLists.txt
src/Script_G3AnimationBehaviors/Ini/                  # relevant shipped profile/INI material
src/Script_G3AnimationBehaviors/SharedConfig.cpp
src/Script_G3AnimationBehaviors/SharedConfig.h
```

Inspect `AttackRaise.*` only enough to confirm shared-profile separation and that Speed did not accidentally assume Raise responsibility. **Do not audit or design Raise itself.**

Inspect collision modules only to the minimum needed to establish:

- `EngineBridge` remains the sole low-level hook owner;
- Speed hook addresses do not conflict with existing project hooks;
- the Speed correction did not modify collision behavior;
- Speed has not gained hidden collision dependencies.

Do not reopen collision architecture absent a concrete contradiction.

Also compare:

```text
pre-final Speed lineage
-> 4f9911f final correction
-> current development
```

Confirm the final correction was bounded to the frozen transport responsibility and that later source drift is absent.

## 6. SDK / x86 ABI audit — mandatory

At pinned SDK `georgeto/gothic3sdk@90bfd344...`, inspect the implementation, not only declarations, of the hook/caller machinery used by Speed. Include relevant portions of:

```text
util/RtPatch/include/g3sdk/util/Hook.h
util/RtPatch/src/Hook.cpp
relevant Script/Entity/type definitions and calling-convention macros
```

Verify the actual semantics of:

```text
mCCallHook
Prepare / Hook
AddRegArg
argument insertion order
register save/restore behavior
stack cleanup behavior
mCCaller
mCCaller::GetCallerParams
SetImmEax / EAX setup
GetFunction
GE_STDCALL / project x86 calling convention
```

Then prove or disprove the production thunk ABI end-to-end.

The audit must explicitly answer:

1. At each hooked original CALL site, is factual `gEAction` really in EAX at the hook boundary?
2. Does `.AddRegArg(mERegisterType_Eax)` pass that value as the thunk's explicit first parameter without corrupting the original stack arguments?
3. Are `Entity` and `gEPhase` received by the thunk in the correct positions/types?
4. Does `Call_GetAnimationSpeedModifier.SetImmEax(a_Action)` restore the exact action convention expected by live `Script_Game+0x42A0`?
5. Does the `mCCaller` invocation call the live target exactly once with correct stack cleanup/calling convention?
6. Is the returned `GEFloat` transported correctly through the x86 floating-point ABI and back to the original caller path?
7. Are required registers/stack state preserved for the downstream code?
8. Is there any recursion/re-entry hazard created by calling the live `+0x42A0` from a caller hook?
9. Is one shared caller/thunk safe for all six sites?

Do not infer these answers from comments in G3AB source. Derive them from SDK implementation + tested-build call-site structure.

Use SDK examples such as existing `mCCaller` usage only as corroboration, not as a substitute for the actual implementation.

## 7. Gothic 3 binary/static-analysis audit — mandatory

Use the pinned `tcholti/Gothic3_Binary_Reference@c9d12cb...` current-tested build.

The repository exposes module-specific surfaces including `Engine`, `Game`, `Gothic3`, `Script`, and `Script_Game`. Begin with `builds/current_tested/BUILD_INFO.md` and use the exact relevant artifacts beneath the module directories. Do not assume filenames; discover the available disassembly/decompiler/import/xref surfaces.

Primary module is `Script_Game`. Inspect other modules only when needed to settle a concrete ABI/wrapper/cross-module question.

### 7.1 Re-derive the speed target

Independently inspect `Script_Game+0x42A0` and establish the relevant input/output contract for this audit:

```text
action transport
phase/entity inputs
returned speed value
relevant base behavior/constants where statically visible
```

### 7.2 Re-derive the caller set

Independently enumerate the relevant xrefs/callers of `+0x42A0` and prove or disprove the frozen production set:

```text
+0x383F0
+0x38E9D
+0x38F22
+0x3937D
+0x39402
+0x48677
```

For **each** accepted site record:

- exact module + offset;
- whether the instruction is a direct CALL suitable for the selected `mCCallHook` mechanism;
- action provenance into EAX;
- phase/entity argument provenance;
- what happens to the returned float immediately afterward;
- whether the site can carry one of the supported Normal/Quick factual actions;
- whether redirecting only that CALL preserves the surrounding path.

### 7.3 Negative caller proof

Explicitly inspect and explain the excluded:

```text
Script_Game+0x38A8B
```

Re-derive whether its apparent scalar/action-like value is actually StateTime/non-action provenance.

Also inspect the xref family far enough to establish that:

- no relevant supported Normal/Quick consumer is omitted from the six-site set;
- no production hook targets an unrelated action consumer;
- other known consumers such as the Action6 / Action27/28 routes remain outside this bounded Speed responsibility when the static facts support that exclusion.

If exhaustive xref proof is impossible from the available static artifact, say exactly what remains unproven; do not convert incomplete enumeration into certainty.

## 8. New Balance compatibility audit — mandatory

Inspect pinned `Jackydima/gothic3sdk@316d324...`, especially the live speed-hook logic in `scripts/Script_NewBalance/FunctionHook.cpp` and only the additional code needed to understand that ownership.

Independently establish:

1. how New Balance takes part in `Script_Game+0x42A0` behavior;
2. whether G3AB's `mCCaller` to the **live** `+0x42A0` address preserves the installed compatible owner rather than bypassing it;
3. whether any hook ordering/trampoline behavior can cause recursion, double application or bypass;
4. whether G3AB copies any New Balance multiplier policy instead of composing with the live result;
5. whether the algebra is actually preserved:

```text
compatible result = B * M
G3AB factor       = C / B
final result      = C * M
```

Check the initial factual bases against independent source/static evidence:

```text
Normal:
None+1H / Shield+1H / Torch+1H / 1H+1H = 0.6
None+2H / None+Axe / None+Staff / None+Halberd = 0.7

Quick Action4/5 = 1.0
```

Normal Fist/PhysicalFist is deliberately unsupported in this first contract; verify that the reason and fail-closed behavior remain sound rather than broadening support.

If another primary runtime component such as `Script_AttackCollision.dll` has an accessible project/pinned source surface relevant to these exact addresses, check for direct hook/address ownership conflict. Do **not** broaden into a general third-party compatibility audit when no concrete overlap exists.

## 9. BehaviorProfiles audit — mandatory

Audit the profile layer as generic shared infrastructure, not merely as something that makes the sample INI work.

Verify:

- runtime INI path and load timing;
- one-time loading assumptions;
- exact-key matching semantics;
- normalization rules;
- duplicate-key ambiguity handling;
- `BaseSpeed` parsing as positive finite data;
- missing/invalid `BaseSpeed` fail-closed behavior;
- `Raise` data remains separate from Speed responsibility;
- runtime `AnimationFamily` identity source and whether expected Hero identity can match `hero` correctly;
- left/right slot acquisition including empty slots;
- raw `gEUseType` -> normalized animation token mappings;
- intentional canonicalization such as Axe/Pickaxe -> `2h` token and tool/staff families;
- preservation of **raw** use types separately for technical `B` lookup where normalized tokens alone are insufficient;
- unknown use types fail closed;
- profile missing/unconfigured route returns compatible speed unchanged;
- exact Normal/Quick action mapping;
- Action3 generic Quick is not incorrectly treated as a factual playback action when the proven route resolves to Action4/5;
- non-Hero families remain fail-closed;
- numerical guards are adequate without adding speculative complexity.

Pay particular attention to the distinction:

```text
user/profile identity = normalized animation/use-type identity
technical reference B = exact evidence-bounded raw runtime facts
```

The two must not be accidentally conflated.

## 10. Simplicity / modularity / ownership audit — mandatory

Evaluate the implementation explicitly against project principles.

Expected responsibility shape:

```text
EngineBridge
= low-level transport/hook ownership only

AttackSpeed
= Speed policy + C/B compatible composition only

BehaviorProfiles
= generic shared INI/profile identity infrastructure

Gothic / compatible owner
= original/base/contextual speed policy
```

Check for:

- one low-level owner per hook/address;
- no hook of the `Script_Game+0x42A0` entry itself;
- exactly the required bounded caller hooks, no global playback-speed override;
- no hidden third-party-policy duplication;
- no final-result hard replacement that destroys contextual modifiers;
- no player-only or NPC-only restriction that is not part of the intended generic responsibility;
- clean dependency direction;
- no collision dependency introduced by Speed;
- no diagnostics dependency in production;
- no evidence-free special case;
- no premature abstraction;
- no unnecessary state/cache/lifecycle machinery;
- native/compatible fallback for unconfigured or unsupported routes.

### 10.1 Legacy/dead-code check

Explicitly search for stale Speed ownership or configuration machinery, including:

```text
InstallAttackSpeedHook
old global +0x42A0 hook code
legacy speed constants
SharedConfig speed fields
old direct final-speed replacement
duplicate profile/config readers
```

Determine whether `SharedConfig.cpp/.h` or any other legacy surface is:

```text
still required
harmless dead code
confusing duplicate authority
or an actual conflicting behavior
```

Do not demand deletion merely because code is unused; classify concrete maintenance/risk impact.

## 11. Required static invariants / negative controls

The audit must explicitly prove or disprove each item:

```text
[ ] exactly six Speed caller hooks exist
[ ] the six hook RVAs are the frozen tested-build sites
[ ] +0x38A8B is NOT hooked
[ ] Script_Game+0x42A0 entry is NOT hooked/owned by G3AB
[ ] no legacy InstallAttackSpeedHook path remains active
[ ] every selected path calls the live compatible owner exactly once before G3AB composition
[ ] unsupported phase returns compatible result unchanged
[ ] unsupported action returns compatible result unchanged
[ ] missing/invalid/unconfigured profile returns compatible result unchanged
[ ] unsupported family/raw-use-type route returns compatible result unchanged
[ ] technical reference B is evidence-bounded and not user configurable
[ ] configured path computes compatibleSpeed * (C/B), not a hard replacement
[ ] final Speed correction did not modify collision behavior
[ ] production CMake contains all required Speed/profile modules
[ ] production code does not require diagnostic macros/components
[ ] no later production-source drift exists after reviewed source 4f9911f...
```

## 12. Findings standard

Use these severities:

```text
BLOCKER
= wrong ABI/call site/action provenance; crash/corruption risk; bypass/double-call of compatible owner; wrong technical base; mechanism cannot satisfy responsibility

MAJOR
= concrete architecture/fail-closed/compatibility violation likely to produce wrong supported behavior or material maintenance risk

MINOR
= concrete simplicity/modularity/clarity/dead-code issue without current correctness failure

NOTE
= validated design point, bounded limitation, or runtime-only uncertainty
```

Every BLOCKER/MAJOR/MINOR finding must include:

- exact source file + function/location, or module + RVA/static artifact;
- evidence/provenance;
- causal chain from fact -> defect/risk -> effect;
- smallest repair direction;
- whether runtime validation is still required afterward.

Do not create speculative findings without a concrete causal chain.

## 13. Required final report

Return one structured audit report containing:

### A. Audit identity

```text
source SHA audited
current documentation/task SHA observed
SDK pin
binary-reference pin
New Balance pin
source-drift check result
```

### B. Authority map

A compact statement of which documents defined intended architecture, which evidence was historical proof, and which facts were independently re-derived.

### C. Findings first

List BLOCKER -> MAJOR -> MINOR findings first. If none exist, say explicitly:

```text
No BLOCKER/MAJOR/MINOR findings.
```

### D. ABI/call-site proof table

For the six accepted sites plus `+0x38A8B`, include factual action provenance, hook suitability, return handling and audit status.

### E. Compatible composition proof

Show the actual live-owner flow and algebra, including New Balance interaction and any hook-order limitation.

### F. Profile/fail-closed matrix

Cover configured supported, unconfigured, invalid profile, unsupported action/phase/family/use-type and Fist/PhysicalFist behavior.

### G. Simplicity/modularity assessment

Assess `EngineBridge`, `AttackSpeed`, `BehaviorProfiles`, legacy surfaces and dependency direction. Distinguish genuine simplification opportunities from aesthetic alternatives.

### H. Independent-evidence reconciliation

For the important EV-391/EV-392 claims, state:

```text
independently re-derived and matches
corroborated only
contradicted
not statically provable
```

### I. Runtime-only unknowns

State exactly what static audit cannot prove and belongs to the later local gate.

### J. Verdict

Use exactly one:

```text
PASS
PASS WITH NON-BLOCKING FINDINGS
BLOCKED
```

Interpretation:

- `PASS`: no source correction required before local build/runtime gate.
- `PASS WITH NON-BLOCKING FINDINGS`: implementation may proceed to runtime; findings do not justify changing the tested source before runtime unless Normal Chat deliberately freezes a separate cleanup task.
- `BLOCKED`: do not build/test as candidate; freeze the smallest bounded correction first.

Even on PASS, **do not close Speed**. Runtime acceptance remains required.

## 14. Out of scope / prohibitions

Do NOT:

- edit production code;
- implement a fix;
- build the DLL;
- deploy to Gothic 3;
- run Gothic 3;
- create new runtime probes/loggers;
- start Raise implementation/design;
- redesign collision behavior;
- broaden support to unproven actions/families/use types;
- change ADRs/evidence to make the implementation appear correct;
- promote to `main`;
- perform general unrelated engine reverse engineering.

If the available static material is insufficient for one sub-question, record the exact limitation and continue the portions that remain independently auditable.

## 15. Stop condition

Stop after delivering the full audit report.

Normal Chat will decide whether to:

```text
PASS -> local build/deploy/startup/New Balance runtime matrix
or
BLOCKED -> freeze a separate smallest correction task
```

No repository maintenance or implementation is part of this Work audit unless Normal Chat later creates a separate responsibility.
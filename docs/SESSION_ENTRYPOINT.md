# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-30

`docs/collision-source-evidence` contains the newest collision research/prototype state. `main` is the stable integration baseline.

Document roles / Hot-Warm-Cold retrieval: `docs/README.md`  
Transient exact handoff: `docs/BETWEEN_CHATS.md`  
Stable conventions: `docs/PROJECT_PIPELINE.md`  
Recurring local procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`  
Project-wide release/build rule: `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`

---

## Mandatory Gothic 3 Release-Purity Rule

> **Every released Gothic 3 behavior DLL must contain behavior only. Research diagnostics are a separate build product and must not be compiled into the release binary.**

This is a project-wide rule for all present and future systems, not a collision-only preference.

It applies to:

```text
frame-controlled collision
collision lifecycle repair
AttackContinuationProtection
Raise
playback speed
target acquisition
climbing
future animation/gameplay behavior modules
```

For the eventual public `Script_G3AnimationBehaviors.dll`:

```text
NO CollisionDiagnostics implementation
NO research logger/log strings
NO stack-capture/RVA research machinery
NO diagnostic-only state
NO diagnostic-only hooks
NO runtime switch that merely hides compiled-in research diagnostics
NO production behavior dependency on diagnostic code
```

Preferred long-term model:

```text
one shared behavior architecture
→ diagnostics-free RELEASE build
→ separately built instrumented DIAGNOSTIC twin used in place of the release DLL for controlled testing
```

Do not load release and diagnostic twins together unless a future architecture explicitly proves safe coexistence. Preserve one physical hook owner per built DLL.

Canonical authority: `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

---

### Collaboration operating intent

Normal Chat owns evidence interpretation, architecture, semantic design, task freezing and knowledge maintenance. Work is used for bounded implementation when its execution environment materially helps. Put the detailed frozen implementation contract in `BETWEEN_CHATS.md`; keep the Work launcher small. Full project rule: `COLLABORATION_RULES.md` §6.

Project-local improvements stay at the lowest owning project layer during ordinary Gothic 3 work. Comparing a lesson with CAM does not authorize editing CAM.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Treat the **Mandatory Gothic 3 Release-Purity Rule** above as a standing architectural constraint before proposing any new script/DLL system.
3. Read `docs/BETWEEN_CHATS.md` when continuing the current/recent responsibility.
4. If the active subsystem is not already oriented in the current Chat, perform the one-time Subsystem Orientation Pass from `docs/README.md`.
5. If substantial reasoning will reinterpret evidence or propose a new fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md`.
6. Read `docs/PROJECT_OPERATING_PROCEDURES.md` once when entering a local Git/build/deploy/runtime-artifact sequence.
7. Before changing gate/test IDs, evidence/procedure IDs, artifact naming, prototype/build labels, branch meanings, or validation-flow conventions, retrieve the relevant `docs/PROJECT_PIPELINE.md` section.
8. Do not scan the whole repository or reconstruct the project from old chat history.
9. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.

### If the previous Chat ended unexpectedly

```text
Open `tcholti/Gothic3_Animation_Behaviors` on branch `docs/collision-source-evidence`.

Read `docs/SESSION_ENTRYPOINT.md` and follow its Fresh Normal Chat Bootstrap before claiming readiness.

Use repository documentation as authority. Do not reconstruct the project from old chat history and do not scan the whole repository. Retrieve only the exact deeper authority/evidence required by the current responsibility.

When bootstrap is complete, tell me briefly what the current technical gate is and what responsibility comes next. Do not begin a new implementation step until then.
```

---

## Active Subsystem

**Frame-controlled melee collision lifecycle and modular collision architecture.**

Preferred lifecycle invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if cleanup was observed, do nothing; if not, repair only that execution's remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. End-of-execution safety is one shared execution-level responsibility for marked and native attacks.

Architecture authorities:

```text
docs/DESIGN.md §§10–11                  overall modular target / agreed roadmap
docs/COLLISION_LIFECYCLE_PLAN.md        lifecycle safety contract
docs/COLLISION_LOGGER_PLAN.md           research-diagnostic architecture
docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md release/diagnostic product separation
docs/COLLISION_TEST_PLAN.md             staged validation sequence
```

---

## Validated Collision-Safety Model — CLOSED THROUGH C1-R1

Compact established model:

- normal attack ScriptFunctions suspend around CombatMove and later resume into native cleanup;
- legitimate reactions can terminate CombatMove and still receive separate cleanup ownership;
- the known destructive held-Use2 path can terminate CombatMove and discard the suspended attack continuation before cleanup, leaving offensive collision stale;
- stale collision can persist and can be inherited by a later legitimate execution as `7 -> 7`;
- C1 tracks successful offensive requests as exact per-source obligations and observes a successful later transition away from `Item_Attack` as fulfillment;
- GetUpAttack can request offense before CombatMove, so C1-O2-P2 uses a live ScriptFunction frame only as a temporary pre-Combat correlator;
- matching CombatMove consumes that temporary binding before wrapper return while C1's monotonic generation remains the durable execution identity;
- C1-R1 repairs only the exact outstanding source that remains live/current-equipped and physically `Item_Attack(7)` after native AISetState had its cleanup opportunity;
- terminal repair is exactly one `SetCollisionGroup(Item_Equipped)` request, verified as exact group 5, with **no `ClearTriggeredList()`**;
- R1-E closed Dual source specificity, marked-source terminal repair/late-callback rejection, broad player/NPC stability, Fist/body separation and unsupported-source negatives.

Canonical evidence:

```text
EV-199–EV-205  C1 transport / P1 / P2
EV-206–EV-207  controlled C1-R1 physical repair
```

Validated C1-R1 implementation:

```text
93e5a2f2d4839ec908a8940927294217dd961c7a
```

Validated DLL:

```text
Script_FrameCollisionTest.dll
Length: 466432
SHA256: 449AC6BECB38B8627CAFAEA6311F4CC0697B91328A15D63B3446DA4766D3EAB5
```

Two qualifications remain explicit and do not reopen C1-R1:

```text
1. No positive runtime exercise of an outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED branch.
2. No positive NPC destructive-abandonment / C1 physical-repair case is claimed.
```

---

## Directly Relevant Tested Hook Substrate

```text
RunScriptFunction
= explicit-this recursion-safe .ThisCall()
= stack-local/TLS lightweight current scope
= P1/P2 tested stable

AISetState
= explicit-this recursion-safe .ThisCall()
= PASS tested extended stability

AIFullStop
= explicit-this recursion-safe .ThisCall()
= PASS tested extended stability

SetCollisionGroup
= explicit-this recursion-safe .ThisCall()
= PASS tested extended stability

FinalizeAfterAISetState
= post-native-AISetState exact-generation finalizer
= remembered source dereference gated by exact current equipped identity
= C1-R1 repair uses the normal SetCollisionGroup path
```

Preserve proven pre/original/post ordering and reentrancy contracts unless new evidence requires a bounded change.

---

## Structural Modularization — CLOSED / BUILD PASS

Completed seams:

```text
CollisionSources extraction
43fa1e719b5af716c54e17430c101251bbc36ff8

EngineBridge extraction transaction
source range d0132b69df3add63641bc5d5fd5779f1037eaa99
→ 32ff447c9a678ba18c8234310564ff2475ba7dfb
```

`EngineBridge.cpp` is now the sole physical hook owner for the research DLL. `Script_FrameCollisionTest.cpp` is the composition root.

Local Release build after EngineBridge extraction: **PASS**.

No post-EngineBridge runtime collision baseline has yet been run.

---

## First Per-CPP Architecture Review — CLOSED

Every `.cpp` in `prototypes/Script_FrameCollisionTest/` now has an explicit first-pass disposition.

```text
Script_FrameCollisionTest.cpp — ACCEPTED
EngineBridge.cpp              — core accepted; second-pass boundaries queued
CollisionSources.cpp          — ACCEPTED
HookBridgeRuntime.cpp         — ACCEPTED
CollisionLifecycleGuard.cpp   — core C1/P2/R1 accepted; dead historical baggage queued
CollisionControl.cpp          — proven marker core accepted; architectural synthesis queued
CollisionDiagnostics.cpp      — core evidence accepted; default logger/hook architecture requires redesign
```

Important preserved behavior:

```text
C1 monotonic execution generation
exact per-source offense/cleanup obligations
P2 temporary pre-Combat correlator
native cleanup precedence
exact post-AISetState liveness gate
exact 7 -> 5 terminal repair
RIGHT / LEFT / BOTH / OFF exact-set marker semantics
repeated-contact ClearTriggeredList rearm
same-update duplicate protection
authored marker occurrence budgets
Quick / full-Whirl StatePosition suppression
Fist not forced through weapon Item_Attack semantics
```

---

## Current Technical Gate — SECOND-PASS ARCHITECTURE SYNTHESIS

The first review pass is complete. **Do not implement the deferred cleanup yet.**

Current responsibility:

```text
review all deferred/correction findings together
→ decide which baggage/boundaries should be resolved now
→ freeze one coherent bounded architecture rewrite
```

Second-pass queue includes:

```text
EngineBridge
- move marker-specific ownership policy to the marker module
- separate production-required hook surface from diagnostic-only hook surface

CollisionLifecycleGuard
- remove dormant rejected eager ScriptFunction dispatch stack/API
- move diagnostic formatting out without moving C1 decisions

CollisionControl / future FrameCollisionMarkers
- investigate unsafe permanent negative marker caching
- classify old execution-lifetime inference against stronger C1 authority
- preserve independent duplicate/budget/replay/rearm/exact-set invariants
- define a cleaner physical-source operation/adapter boundary
- remove transitional CollisionSources aliases

CollisionDiagnostics
- compact authoritative default research evidence
- retain useful historical probes as opt-in deep diagnostics
- remove obsolete proof-era startup/noise
- ensure diagnostic state never feeds behavior correctness

Release architecture
- keep diagnostics in the research/diagnostic product only
- final release target must exclude diagnostic sources/hooks/state entirely
```

The mature research DLL is increasingly the architectural ancestor of the final `Script_G3AnimationBehaviors`; do not pour the mature collision system back into the old v0.1 hook/file layout.

---

## Required Sequence From Here

Preserve causal attribution:

```text
second-pass architecture synthesis
→ freeze exact rewrite contract
→ run CURRENT post-EngineBridge runtime baseline with the existing rich logger
→ if baseline PASS
→ implement the frozen architecture cleanup
→ build/source audit
→ validate compact diagnostic sufficiency
→ marker-bookkeeping simplification/expansion work
→ separate Fist source-adapter decision
→ AttackContinuationProtection
→ mature research DLL compatibility gate with New Balance / relevant Jackydima DLLs
→ retain mature modular foundation and migrate/redesign Raise + speed + config
→ add later systems such as target acquisition/climbing under the same modular/release-purity rules
→ final diagnostics-free release DLL compatibility/regression
```

If the second-pass rewrite is broad enough to benefit from Work/High, Normal Chat owns the architecture and writes the exact frozen contract into `BETWEEN_CHATS.md`; Work executes that contract without redesigning it.

---

## Production Migration Direction

The final production architecture should evolve from the mature modular research foundation:

```text
mature research behavior core
+ validated collision/marker/lifecycle/continuation responsibilities
+ redesigned Raise
+ redesigned compatible speed
+ configuration
+ future independent modules such as target acquisition/climbing
→ final Script_G3AnimationBehaviors behavior architecture
```

The public release build then compiles **behavior only**.

A separate instrumented diagnostic twin may compile the same behavior core plus diagnostics for controlled reproduction and future research. It is not the public release and should normally be used **instead of**, not beside, the release DLL.

---

## Relevant Tested Native Points

```text
Game +0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
Game +0x164320 = gCScriptRoutine_PS::AISetState(bCString const&)
Game +0x164430 = gCScriptRoutine_PS::AIFullStop()
Game +0x1696E0 = gCScriptProcessingUnit::sAICombatMoveInstr(...)
Game +0x16F120 = gCScriptProcessingUnit::ProcessScript()
Engine +0x225660 = tested SetCollisionGroup hook target
```

GetUp boundary evidence:

```text
Script_Game +0x41CA6  pre-CombatMove Item_Attack request region
Script_Game +0x41D5A  later CombatMove call
Script_Game +0x41E10  ordinary cleanup
```

All addresses are tested-build-specific.

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| current exact gate / deferred second-pass queue | `BETWEEN_CHATS.md` |
| mandatory diagnostics-free release architecture | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` |
| modular target / agreed implementation order | `DESIGN.md` §§10–11 |
| research diagnostic architecture | `COLLISION_LOGGER_PLAN.md` |
| staged validation / closed R1 acceptance | `COLLISION_TEST_PLAN.md` |
| active causal reconstruction | `EVIDENCE_INDEX.md` Active-Problem Reconstruction |
| canonical C1/P2 continuation evidence | `EVIDENCE_LEDGER_STEP_C.md` EV-199–EV-205 |
| canonical C1-R1 physical-repair evidence | `EVIDENCE_LEDGER_STEP_D.md` EV-206–EV-207 |
| lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| future held-Use2 prevention | `BAD_SKIP_FUTURE_INVESTIGATION.md` |
| native cleanup semantics/RVAs | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| source/API/New Balance/hook transport lookup | `SOURCE_HOOK_GUIDE.md` + pinned SDK/reference material as needed |
| recurring local operations | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded Work implementation rules | `WORK_IMPLEMENTATION_PROTOCOL.md` |
| naming/gate conventions | `PROJECT_PIPELINE.md` |

Do not load the whole documentation corpus by default.

---

## Broad Priority Order

1. complete second-pass architecture synthesis and preserve a clean post-EngineBridge baseline boundary;
2. mature and modularize collision/marker/continuation in the research/diagnostic build;
3. prove New Balance/Jackydima compatibility on the mature research DLL;
4. retain that modular foundation while redesigning/migrating Raise, speed and config into `Script_G3AnimationBehaviors`;
5. add future independent systems such as target acquisition and climbing only through the same central-hook/modular architecture;
6. build and validate a **diagnostics-free** public `Script_G3AnimationBehaviors.dll`;
7. retain a separate instrumented diagnostic twin for future controlled reproduction and research.

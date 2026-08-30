# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-30

`docs/collision-source-evidence` contains the newest collision research/prototype state. `main` is the stable integration baseline.

Document roles / Hot-Warm-Cold retrieval: `docs/README.md`  
Transient Chat ↔ Work handoff when relevant: `docs/BETWEEN_CHATS.md`  
Stable conventions: `docs/PROJECT_PIPELINE.md`  
Recurring Git/build/deploy/test/log procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`

### Collaboration operating intent

Normal Chat is the primary evidence-interpretation / architecture / semantic-design / task-freezing environment. Work is used for bounded implementation when its execution environment materially helps. Keep detailed frozen implementation contracts in `BETWEEN_CHATS.md` and Work launchers short. This preserves accumulated User + Normal Chat understanding and uses the User's limited Work budget where it buys real execution capability. Full project rule: `COLLABORATION_RULES.md` §6.

Project-local collaboration improvements stay at the lowest owning project layer during ordinary Gothic 3 work. Comparing a lesson with CAM does not authorize editing CAM; upward promotion is a separate dedicated CAM-evolution responsibility.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` when continuing the current/recent responsibility.
3. If the active subsystem is not already oriented in the current Chat, perform the one-time Subsystem Orientation Pass from `docs/README.md`.
4. If substantial reasoning will reinterpret evidence or propose a new fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md`.
5. Read `docs/PROJECT_OPERATING_PROCEDURES.md` once when entering a local Git/build/deploy/runtime-artifact sequence.
6. Before changing gate/test IDs, evidence/procedure IDs, artifact naming, prototype/build labels, branch meanings, or validation-flow conventions, retrieve the relevant `docs/PROJECT_PIPELINE.md` section.
7. Do not scan the whole repository or reconstruct the project from old chat history.
8. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.

### If the previous Chat ended unexpectedly

```text
Open `tcholti/Gothic3_Animation_Behaviors` on branch `docs/collision-source-evidence`.

Read `docs/SESSION_ENTRYPOINT.md` and follow its Fresh Normal Chat Bootstrap before claiming readiness.

Use repository documentation as authority. Do not reconstruct the project from old chat history and do not scan the whole repository. Retrieve only the exact deeper authority/evidence required by the current responsibility.

When bootstrap is complete, tell me briefly what the current technical gate is and what responsibility comes next. Do not begin a new implementation step until then.
```

---

## Active Subsystem

**Frame-controlled melee collision lifecycle.**

Preferred invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if cleanup was observed, do nothing; if not, repair only that execution's remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. End-of-execution safety is one shared execution-level responsibility for marked and native attacks.

Architecture authority: `docs/COLLISION_LIFECYCLE_PLAN.md`.

Production physical repair is still **disabled**.

---

## Active Problem — Native Stale Melee Collision

Use `EVIDENCE_INDEX.md` Active-Problem Reconstruction when the causal model is not fresh. Compact model:

- normal attack ScriptFunctions suspend around CombatMove and later resume into native cleanup;
- legitimate reactions can terminate CombatMove and still receive separate cleanup ownership;
- the known held-Use2 destructive path can terminate CombatMove and discard the suspended attack continuation before cleanup, leaving offensive collision stale;
- stale collision can persist through later idle/movement and can be inherited by a later legitimate execution as `7 -> 7`;
- C1 tracks successful offensive requests as exact per-source obligations, observes native cleanup, and classifies outstanding obligations at destructive AISetState finalization;
- GetUpAttack can request offense before CombatMove, so CombatMove alone is too late as a universal execution-acquisition boundary;
- C1-O1/P1 established that a live ScriptFunction frame is a valid temporary correlator for the pre-Combat GetUp gap but not a durable execution identity;
- C1-O2-P2 proved that a real pre-Combat offense can acquire the monotonic C1 generation, matching CombatMove can reuse that same generation and consume the temporary native-frame binding before wrapper return, and later timer offense/native cleanup continue on the durable generation;
- C1's monotonic generation remains the durable plugin execution identity.

Canonical evidence route: EV-151–EV-205 plus dedicated P2 shutdown-closure evidence commit `4946d382041e9ec86400291395e5acbad77b1de6`.

---

## C1 Shadow Guard — Current Proven State

C1 remains shadow-only; physical repair is disabled.

Core evidence:

- EV-192–EV-193 — shadow execution/source obligation model;
- EV-194 — GetUp pre-CombatMove acquisition gap;
- EV-195–EV-196 — outer ScriptFunction lifetime and C1-O1 correlation/pointer-reuse qualification;
- EV-199–EV-203 — hook-transport/finalizer stabilization;
- EV-204 — P1 lightweight live-scope bridge;
- EV-205 — P2 lazy pre-Combat generation acquisition + bridge consumption, isolated/targeted/broad runtime validation;
- dedicated P2 shutdown closure — same validated P2 binary loaded a save, returned to menu and ended with `Script_FrameCollisionTest unloading.`.

### Directly relevant tested substrate

```text
RunScriptFunction
= recursion-safe explicit-this .ThisCall()
= stack-local/TLS lightweight current scope
= P1 source/isolated/targeted PASS
= P2 lazy acquisition + bridge-consumption source/isolated/targeted/broad gameplay PASS

AISetState
= explicit-this recursion-safe .ThisCall()
= PASS for tested extended stability

AIFullStop
= explicit-this recursion-safe .ThisCall()
= PASS for tested extended stability

SetCollisionGroup
= explicit-this recursion-safe .ThisCall()
= PASS for tested extended stability

FinalizeAfterAISetState
= remembered-source liveness gated by current equipped identity before source observation
= PASS for tested isolated + extended stability
```

Important qualification: EV-203 did not positively exercise an outstanding `LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED` finalization branch. Do not claim runtime proof of that exact branch.

---

## C1-O2-P2 — Closed for Tested Outer-Acquisition / Binding Model

Behavior implementation:

```text
cc51c67c19425be4e4d6a4838803ed3e66b2a071
```

Startup identity correction:

```text
8b6a5873b8caa27b469ae831d25bf155a6c7f189
```

Validated DLL:

```text
Script_FrameCollisionTest.dll
Length: 465408
SHA256: 1081B287912DB9A368164DDE13542A7EC2D6E5DBB0AA29B04C19BD7932D92C7C
```

Validation:

```text
P2-A independent source audit = PASS
P2-B isolated load/unload = PASS
P2-C targeted GetUp meaning = PASS
P2-D broad gameplay ownership/stability = PASS
P2-D broad-run raw itself did not capture shutdown
P2-D dedicated clean shutdown closure = PASS
```

P2-C produced five clean GetUp bridge generations `20/33/45/54/64` with no unowned or binding invariant.

P2-D canonical raw:

```text
research/archive/2026-08-30_c1o2p2_broader_combat_interruption_stability.log
SHA256: 50AE4944C23DB30C78CE0373E241DDAAC32C252C2D8563584871F098C96BB041
Bytes: 12123937
Lines: 398143
```

Derived package:

```text
research/derived/2026-08-30_c1o2p2_broader_combat_interruption_stability_large_log/
```

P2-D contained 13 successful pre-Combat bridges, generations:

```text
200 298 314 364 384 473 622 658 660 671 726 857 868
```

All tested positive bridges followed:

```text
real exact-source early offense
→ PRECOMBAT_ACQUIRED
→ matching CombatMove reuses same generation
→ PRECOMBAT_BRIDGE_CONSUMED before RunScriptFunction return
→ durable generation/source obligation continues independently
```

Whole-run failure-signal result was zero for C1 invariant warnings, unowned offense, unconsumed bridge, error/exception, failure, mismatch/divergence, stale, unresolved/orphan and unsafe/bad-skip classes.

The broad run recorded 29 actual shadow `WOULD_REPAIR` source outcomes with physical repair still disabled. Representative 2H, Staff, 1H/Torch and Dual cases remained exact-source/consequence based. Dual included source-specific RIGHT and LEFT outcomes.

A consistency check over the observed run gives:

```text
306 offense-request events
- 13 second GetUp requests belonging to the same early-acquired obligations
= 293 observed offensive source obligations

264 native cleanup fulfillments
+ 29 shadow WOULD_REPAIR outcomes
= 293
```

Two observed Staff GetUpParade action-31 cases traversed `Hit`/Recover resources without C1 offense, reinforcing that filename grammar is engine-significant but collision ownership is still established from actual collision consequence/source evidence rather than a generic `Hit` token alone.

The original broad-run raw ended during continued gameplay and therefore cannot itself prove shutdown. A separate closure run using the same validated P2 DLL loaded a save, idled briefly, returned to the main menu and exited normally; its final log line is `Script_FrameCollisionTest unloading.`. Raw commit:

```text
4946d382041e9ec86400291395e5acbad77b1de6
research/archive/2026-08-30_c1o2p2d_clean_shutdown_closure.log
```

The User subjectively reported that P2 felt smoother than several previous research builds. No controlled performance comparison was performed; do not claim causal performance improvement.

---

## Current Immediate Responsibility — Normal Chat Physical-Repair Gate Design

C1-O2 is closed for the tested outer binding/acquisition model.

**Do not send a Work implementation task yet.**

Normal Chat must now retrieve only the exact current lifecycle/finalizer source and architecture needed to answer:

> **What is the smallest controlled native-equivalent physical repair that can replace the already-proven shadow `WOULD_REPAIR` outcome while preserving exact-source ownership, source liveness, native-cleanup precedence, legitimate reaction behavior, inherited `7 -> 7` attribution and all current no-op cases?**

Preserved constraints:

```text
repair is consequence/source-obligation based, not family/action/input/cause/time based
only the exact outstanding source may be repaired
current equipped identity/liveness must be established before dereference/mutation
observed native cleanup always wins → no repair
no arbitrary adoption of unrelated group-7 state
no polling / timer / world scan
no FullStop-as-cleanup-authority rule
no marker-core refactor
no restoration of rejected C1-O2 dispatch machinery
```

Physical repair remains **OFF** until Normal Chat freezes one bounded implementation gate plus its runtime falsification matrix.

---

## Relevant Tested Native Points

```text
Game +0x1604E0 = gCScriptAdmin::RunScriptFunction(...)
Game +0x1605E9 = indirect registered ScriptFunction call
Game +0x1605EB = first instruction after that call
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
| current exact continuation / transient handoff | `BETWEEN_CHATS.md` |
| participant/tool responsibility allocation | `COLLABORATION_RULES.md` §6 |
| active stale-collision causal reconstruction | `EVIDENCE_INDEX.md` Active-Problem Reconstruction |
| C1-O2 / hook/finalizer continuation evidence | `EVIDENCE_LEDGER_STEP_C.md` EV-199–EV-205 |
| outer lifetime / cleanup architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| current staged validation | `COLLISION_TEST_PLAN.md` |
| native cleanup RVAs/stacks | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| SPU / ScriptFunction / CombatMove / hook lookup | `SOURCE_HOOK_GUIDE.md` + pinned SDK/static reference as needed |
| diagnostic architecture | `COLLISION_LOGGER_PLAN.md` |
| naming/numbering/version/test/artifact conventions | `PROJECT_PIPELINE.md` relevant section only |
| recurring Git/build/deploy/test/log procedure | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded implementation protocol | `WORK_IMPLEMENTATION_PROTOCOL.md` |
| general architecture/review principles | `ENGINEERING_GUIDE.md` |
| marker execution lifetime / future simplification | `EVIDENCE_INDEX.md` Marker execution lifetime → `COLLISION_LIFECYCLE_PLAN.md` |
| animation semantics/assets | `ANIMATION_INDEX.md` |
| overall Raise/speed/collision architecture | `DESIGN.md` |
| older chronology | `RESEARCH_MAP.md` / archive only when specifically needed |

Do not load the whole documentation corpus by default.

---

## After Collision

Broad priority order remains:

1. finish collision lifecycle safety and integrate stable collision behavior;
2. generalize Raise for intended Normal/Quick and selected full-Whirl families;
3. implement/calibrate profile-aware playback speed;
4. later investigate broader animation-selection/gameplay systems such as jumping, wading and climbing.

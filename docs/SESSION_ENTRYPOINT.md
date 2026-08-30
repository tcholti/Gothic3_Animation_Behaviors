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

### Collaboration operating intent

Normal Chat owns evidence interpretation, architecture, semantic design, task freezing and knowledge maintenance. Work is used for bounded implementation when its execution environment materially helps. Put the detailed frozen implementation contract in `BETWEEN_CHATS.md`; keep the Work launcher small. Full project rule: `COLLABORATION_RULES.md` §6.

Project-local improvements stay at the lowest owning project layer during ordinary Gothic 3 work. Comparing a lesson with CAM does not authorize editing CAM.

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

---

## Active Problem — Native Stale Melee Collision

Compact established model:

- normal attack ScriptFunctions suspend around CombatMove and later resume into native cleanup;
- legitimate reactions can terminate CombatMove and still receive separate cleanup ownership;
- the known destructive held-Use2 path can terminate CombatMove and discard the suspended attack continuation before cleanup, leaving offensive collision stale;
- stale collision can persist through idle/movement and can be inherited by a later legitimate execution as `7 -> 7`;
- C1 tracks successful offensive requests as exact per-source obligations and observes successful transition away from `Item_Attack` as fulfillment;
- GetUpAttack can request offense before CombatMove, so CombatMove alone is too late as a universal acquisition boundary;
- C1-O1/P1 established a live ScriptFunction frame as a temporary correlator for that pre-Combat gap;
- C1-O2-P2 proved the early offense can acquire the monotonic C1 generation, matching CombatMove can reuse it and consume the native-frame bridge before wrapper return, and later timer offense/native cleanup continue on the durable generation;
- C1's monotonic generation remains the durable plugin execution identity.

Canonical evidence route: EV-151–EV-205 plus dedicated P2 shutdown-closure evidence commit `4946d382041e9ec86400291395e5acbad77b1de6`.

---

## C1-O2-P2 — CLOSED

Implementation:

```text
cc51c67c19425be4e4d6a4838803ed3e66b2a071
```

Validated P2 DLL:

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
P2-D dedicated clean shutdown closure = PASS
```

P2-D broad run:

```text
research/archive/2026-08-30_c1o2p2_broader_combat_interruption_stability.log
SHA256: 50AE4944C23DB30C78CE0373E241DDAAC32C252C2D8563584871F098C96BB041
Bytes: 12123937
Lines: 398143
```

Observed whole-run accounting:

```text
306 offense-request events
- 13 second GetUp requests belonging to the same early-acquired obligations
= 293 observed offensive source obligations

264 observed cleanup fulfillments
+ 29 shadow WOULD_REPAIR outcomes
= 293
```

No C1/P2 binding/invariant failure signal was present. Physical mutation was still disabled in P2.

---

## Directly Relevant Tested Substrate

```text
RunScriptFunction
= explicit-this recursion-safe .ThisCall()
= stack-local/TLS lightweight current scope
= P1/P2 tested stable for current responsibilities

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
= shadow classification passed extended stability
```

EV-203 did not positively exercise an outstanding `LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED` branch. Do not claim runtime proof of that exact branch.

---

## Current Immediate Responsibility — C1-R1 Controlled Native-Equivalent Physical Repair

Normal Chat source/API inspection is complete and the first physical-repair gate is now frozen as **C1-R1**.

Detailed implementation authority: `docs/BETWEEN_CHATS.md`.

C1-R1 asks:

> **Can the existing proven `WOULD_REPAIR` branch perform exactly the same narrow weapon-source reset Gothic 3 uses for legitimate cleanup — `Item_Attack(7) -> Item_Equipped(5)` on the exact live/equipped outstanding source — without changing any execution that already cleaned itself, never requested offense, is no longer safely live, or belongs to the other Dual source?**

Source/API conclusion supporting the gate:

- tested ordinary weapon cleanup paths across the established melee action matrix reset the physical source `7 -> 5`;
- the tested legitimate reaction cleanup route uses the same physical weapon reset semantics;
- current marker OFF/source-deactivation uses `SetCollisionGroup(Item_Equipped)` without `ClearTriggeredList()`;
- `ClearTriggeredList()` is activation/rearm behavior and is not part of the proven cleanup mutation.

Therefore the C1-R1 physical mutation is exactly:

```text
existing finalizer has exact outstanding source
+ exact current equipped identity establishes liveness
+ actual source group is Item_Attack(7)
→ SetCollisionGroup(Item_Equipped) exactly once on that source
→ no ClearTriggeredList()
→ verify exact resulting group 5
```

All existing no-op branches remain no-op.

### Important diagnostic-order requirement

The repair call will pass through the already-hooked SetCollisionGroup path and emit nested diagnostics. Therefore `FinalizeAfterAISetState()` must not begin printing its finalization block and then call the setter mid-block.

C1-R1 uses a minimal two-phase finalizer:

```text
classify / repair into fixed stack-local per-source results (max 2)
→ then emit one complete C1 FINALIZATION block
```

No heap allocation, new global state, new hook or new ownership mechanism is authorized.

### Frozen non-responsibilities

Do not change:

```text
execution acquisition / generation ownership
P1/P2 bridge behavior
CombatMove behavior
AISetState/AIFullStop/SetCollisionGroup hook transport
finalization trigger
marker activation or RIGHT/LEFT/BOTH/OFF semantics
family/action/input/state-name classification
held-Use2 / 2500-ms external behavior
Fist/body-source semantics
rejected eager dispatch machinery
```

The guard remains actor/source-general; do not add Hero-only production semantics.

---

## C1-R1 Validation Order

```text
R1-A independent Normal Chat source audit
→ R1-B build / exact DLL identity / isolated load
→ R1-C targeted destructive positive repair + later ordinary 5 -> 7 control
→ R1-D clean/reaction/pre-activation/GetUp/GetUpParade no-op controls
→ R1-E Dual source-specific + compact marker interaction + broader player/NPC/negative stability as evidence requires
```

A targeted positive repair should prove:

```text
real offense obligation
→ no native cleanup
→ destructive finalization
→ exact live/equipped source still Item_Attack(7)
→ one repair request to Item_Equipped(5)
→ result exactly 5
→ REPAIRED_TO_ITEM_EQUIPPED
```

A later legitimate attack should normally begin from `5 -> 7`, demonstrating that stale `7` was physically removed rather than inherited.

Physical repair is not production-integrated merely because the first positive case passes.

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
| current exact implementation handoff | `BETWEEN_CHATS.md` |
| current staged validation | `COLLISION_TEST_PLAN.md` |
| active causal reconstruction | `EVIDENCE_INDEX.md` Active-Problem Reconstruction |
| canonical C1/P2 continuation evidence | `EVIDENCE_LEDGER_STEP_C.md` EV-199–EV-205 |
| lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| native cleanup semantics/RVAs | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| source/API lookup | `SOURCE_HOOK_GUIDE.md` + pinned SDK/static reference as needed |
| recurring local operations | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded Work implementation rules | `WORK_IMPLEMENTATION_PROTOCOL.md` |
| naming/gate conventions | `PROJECT_PIPELINE.md` |

Do not load the whole documentation corpus by default.

---

## After Collision

Broad priority order remains:

1. finish collision lifecycle safety and integrate stable collision behavior;
2. generalize Raise for intended Normal/Quick and selected full-Whirl families;
3. implement/calibrate profile-aware playback speed;
4. later investigate broader animation-selection/gameplay systems such as jumping, wading and climbing.

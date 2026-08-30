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

**Frame-controlled melee collision lifecycle and modular collision architecture.**

Preferred invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if cleanup was observed, do nothing; if not, repair only that execution's remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. End-of-execution safety is one shared execution-level responsibility for marked and native attacks.

Architecture authorities:

```text
docs/DESIGN.md §§10–11                  overall modular target / agreed roadmap
docs/COLLISION_LIFECYCLE_PLAN.md        lifecycle safety contract
docs/COLLISION_TEST_PLAN.md             staged validation sequence
```

---

## Established Problem and Validated Collision-Safety Model

Compact established model:

- normal attack ScriptFunctions suspend around CombatMove and later resume into native cleanup;
- legitimate reactions can terminate CombatMove and still receive separate cleanup ownership;
- the known destructive held-Use2 path can terminate CombatMove and discard the suspended attack continuation before cleanup, leaving offensive collision stale;
- stale collision can persist through idle/movement and can be inherited by a later legitimate execution as `7 -> 7`;
- C1 tracks successful offensive requests as exact per-source obligations and observes successful transition away from `Item_Attack` as fulfillment;
- GetUpAttack can request offense before CombatMove, so CombatMove alone is too late as a universal acquisition boundary;
- C1-O1/P1 established a live ScriptFunction frame as a temporary correlator for that pre-Combat gap;
- C1-O2-P2 proved the early offense can acquire the monotonic C1 generation, matching CombatMove can reuse it and consume the native-frame bridge before wrapper return, and later offense/native cleanup continue on the durable generation;
- C1's monotonic generation remains the durable plugin execution identity;
- C1-R1 performs the proven native-equivalent `Item_Attack(7) -> Item_Equipped(5)` repair only for the exact outstanding source that remains live/equipped and physically offensive after native AISetState has had its cleanup opportunity;
- R1-E closed source-specific Dual, marked-source, broad player/NPC stability and unsupported-source negative coverage without requiring family/action/input/cause-specific cleanup rules.

Canonical evidence route: EV-151–EV-207 plus dedicated P2 shutdown-closure evidence commit `4946d382041e9ec86400291395e5acbad77b1de6`.

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
= C1-R1 controlled repair uses this same finalizer
```

EV-203/EV-206/EV-207 do not positively exercise an outstanding `LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED` branch. Preserve the fail-closed behavior and do not claim runtime proof of that exact branch.

---

## C1-R1 Controlled Native-Equivalent Physical Repair — CLOSED

Implementation:

```text
93e5a2f2d4839ec908a8940927294217dd961c7a
```

Validated C1-R1 DLL:

```text
Script_FrameCollisionTest.dll
Length: 466432
SHA256: 449AC6BECB38B8627CAFAEA6311F4CC0697B91328A15D63B3446DA4766D3EAB5
```

Canonical physical-repair evidence: **EV-206–EV-207** in `docs/EVIDENCE_LEDGER_STEP_D.md`.

Validation:

```text
R1-A independent source audit = PASS
R1-B build / exact DLL identity / isolated load-unload = PASS
R1-C targeted positive repair = PASS
R1-D no-op / reaction / GetUp controls = PASS
R1-E Dual source-specific repair = PASS
R1-E compact marked-Staff regression = PASS
R1-E broad mixed exercised player/NPC/negative coverage = PASS
R1-E focused unarmed/crossbow negative closure = PASS
C1-R1 controlled validation = CLOSED
```

Accepted repair rule:

```text
existing finalizer has exact outstanding source
+ exact current equipped identity establishes liveness
+ actual source group is Item_Attack(7)
→ SetCollisionGroup(Item_Equipped) exactly once on that source
→ no ClearTriggeredList()
→ verify exact resulting group 5
```

Everything outside that predicate remains no-op/unresolved and non-mutating. Native cleanup retains precedence. Repair passes through the existing SetCollisionGroup path and keeps marker retirement/source observation on the established path.

R1-E proved exact Dual source independence, marked-source terminal repair and late-callback rejection, broad mixed player/NPC stability, Fist/body separation and crossbow unsupported-source fallback. Supplemental bow and magic regression traffic also remained outside inappropriate weapon-style C1 repair ownership.

Two qualifications remain explicit:

```text
- no positive runtime exercise of an outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED case;
- no positive NPC destructive-abandonment / C1 physical-repair case is claimed.
```

Neither qualification reopens R1. Do not invent another broad matrix solely to force them.

---

## Current Immediate Responsibility — Read-Only Architecture / Code Review

Do **not** migrate C1-R1 directly into `src/Script_G3AnimationBehaviors` and do not begin a refactor yet.

Normal Chat should now perform a bounded but complete read-only architecture review of:

```text
prototypes/Script_FrameCollisionTest/
src/Script_G3AnimationBehaviors/
```

The current source already shows useful separation (`CollisionControl`, `CollisionLifecycleGuard`, `CollisionDiagnostics`, `HookBridgeRuntime`) and a main research file that owns the physical hooks. The review must determine whether those boundaries are clean enough for future modular growth and where research instrumentation is still entangled with behavior.

Required review classification:

```text
1. shared engine hooks / calling-convention-safe transport
2. validated CollisionLifecycleGuard production semantics
3. frame-marker ownership/control semantics
4. physical source adapters / equipped weapon vs Fist separation
5. research-only diagnostics/probes and hooks that production does not need
6. historical marker execution/window checks that may be redundant under C1 execution identity
7. marker invariants that remain independently necessary
8. existing Script_G3AnimationBehaviors module/config/hook structure
9. New Balance / Jackydima shared-hook compatibility risks, especially current AttackSpeed
```

No source edit is authorized by this phase. The output should be a specific proposed module boundary and the **smallest behavior-preserving research-DLL refactor** to freeze next.

Target architecture rule:

> **One DLL may contain multiple independent behavior modules, but one central engine-bridge layer owns each shared Gothic hook. Feature modules consume authoritative engine events/facts; they do not compete with one another for the same physical hook.**

Detailed roadmap: `docs/DESIGN.md` §§10–11.  
Exact transient handoff: `docs/BETWEEN_CHATS.md`.

---

## Agreed Forward Direction After Review

Do not treat this as authorization to skip directly to a later step. Each phase is frozen separately and may be course-corrected by source/runtime evidence.

```text
read-only full architecture/code review
→ semantic-preserving modular refactor of Script_FrameCollisionTest
→ compact collision-baseline revalidation
→ marker-bookkeeping simplification audit against C1 authority
→ equipped-melee marker expansion one mechanism at a time
→ separate Fist source-adapter investigation/decision
→ full marker + lifecycle regression
→ modular AttackContinuationProtection investigation/implementation
→ guard + markers + continuation regression
→ mandatory New Balance/Jackydima compatibility on mature research DLL
→ redesign/migrate collision modules into modular Script_G3AnimationBehaviors
→ independent Raise + redesigned speed work
→ final full Script_G3AnimationBehaviors + New Balance/Jackydima compatibility regression
```

The future held-Use2 prevention module remains separate from `CollisionLifecycleGuard`: `docs/BAD_SKIP_FUTURE_INVESTIGATION.md`.

The existing `AttackSpeed.cpp` direct `GetAnimationSpeedModifier` hook is proof-of-concept only; its production strategy must be re-evaluated for New Balance compatibility before final speed integration.

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
| current exact architecture-review handoff | `BETWEEN_CHATS.md` |
| modular target / agreed implementation order | `DESIGN.md` §§10–11 |
| staged validation / closed R1 acceptance | `COLLISION_TEST_PLAN.md` |
| active causal reconstruction | `EVIDENCE_INDEX.md` Active-Problem Reconstruction |
| canonical C1/P2 continuation evidence | `EVIDENCE_LEDGER_STEP_C.md` EV-199–EV-205 |
| canonical C1-R1 physical-repair evidence | `EVIDENCE_LEDGER_STEP_D.md` EV-206–EV-207 |
| lifecycle architecture | `COLLISION_LIFECYCLE_PLAN.md` |
| future held-Use2 prevention | `BAD_SKIP_FUTURE_INVESTIGATION.md` |
| native cleanup semantics/RVAs | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| source/API/New Balance lookup | `SOURCE_HOOK_GUIDE.md` + pinned SDK/reference material as needed |
| recurring local operations | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded Work implementation rules | `WORK_IMPLEMENTATION_PROTOCOL.md` |
| naming/gate conventions | `PROJECT_PIPELINE.md` |

Do not load the whole documentation corpus by default.

---

## Broad Priority Order

1. mature and modularize the collision/marker/continuation system in the research DLL and prove New Balance/Jackydima compatibility;
2. redesign/migrate that proven collision architecture into `Script_G3AnimationBehaviors` while preserving modularity;
3. generalize Raise for intended Normal/Quick and selected full-Whirl families;
4. redesign/implement compatible profile-aware playback speed;
5. run final production DLL compatibility/regression before stable promotion;
6. later investigate broader animation-selection/gameplay systems such as jumping, wading and climbing.

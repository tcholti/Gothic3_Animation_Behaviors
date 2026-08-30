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
- GetUpAttack can request offense before CombatMove, so CombatMove alone is too late as a universal acquisition boundary;
- C1-O1 proved the live outer ScriptFunction frame can correlate pre-CombatMove offense → CombatMove → cleanup, while raw frame/argument addresses are lifetime-bound correlators only and may be reused after retirement;
- C1-O2-P1 proved that the missing GetUp pre-Combat offense occurs inside a safe lightweight live `RunScriptFunction` scope and that matching CombatMove begins before that wrapper returns/suspends;
- C1-O2-P2 now implements the smaller bridge model: a real pre-Combat offense may acquire the monotonic C1 generation, matching CombatMove may reuse that generation and consume the temporary native-frame binding before wrapper return;
- C1's monotonic generation remains the durable plugin execution identity.

Evidence route: EV-151–EV-204. P2 source implementation is not runtime evidence yet.

---

## Agreed Strategic Direction — Universal Guard First

```text
preserve proven marker behavior
→ finish stable shadow execution/source ownership
→ prove controlled native-equivalent physical repair
→ preserve the known destructive abandonment as a stress case
→ preserve ordinary / legitimate reaction / pre-activation / inherited-state controls
→ broad marked/unmarked/player/NPC/negative regression
→ stable production integration
→ only later consider marker-bookkeeping simplification
```

The held-Use2 / 2500-ms path is a **test case**, not production classification authority.

The universal guard owns collision safety only. It should not rewrite unrelated external/native movement, state, balance or interruption behavior when collision integrity can be guaranteed independently.

---

## C1 Shadow Guard — Current Stable / Validation State

C1 remains shadow-only; production physical repair is disabled.

Core model and acquisition evidence:

- EV-192–EV-193 — shadow execution/source obligation model;
- EV-194 — GetUp pre-CombatMove acquisition gap;
- EV-195–EV-196 — outer ScriptFunction lifetime and C1-O1 correlation/pointer-reuse qualification;
- EV-204 — P1 lightweight dispatch bridge source/isolated/targeted validation.

### Directly relevant tested substrate

```text
RunScriptFunction
= recursion-safe explicit-this .ThisCall()
= stack-local/TLS lightweight current scope
= P1 PASS source audit + isolated load + targeted meaning validation
= no separate P1 extended-stability claim

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

Important qualification: the corrected EV-203 run did **not** positively exercise an outstanding `LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED` finalization branch. Do not claim runtime proof of that exact branch.

---

## C1-O2-P1 — Closed Meaning Gate

P1 implemented only a zero-allocation, nesting-safe, stack-local current `RunScriptFunction` scope around the already-correct explicit-this hook transport. The generic wrapper performs no state-stack, actor, C1, allocation or logging work before native execution.

Validated corrected P1 DLL SHA256:

```text
44C15C068D34F82BDCB03EEBEC76C3C0A93094D64662B032954BFF637D51E05D
```

P1-B isolated main-menu load/unload passed.

P1-C targeted gameplay produced four deliberate GetUpAttack acquisition-gap reproductions. In all four initial GetUp `5 -> 7` events the live scope matched the player SPU/state stack and `_AI_GetUpAttack`; matching CombatMove began in that same live invocation before `RunScriptFunction` returned `GEFalse` / suspended. Later timer `7 -> 7` offense occurred with no live wrapper scope while `_AI_GetUpAttack` remained suspended on the SPU.

Ordinary Normal/Quick timer offense likewise often occurs with no live P1 scope; a live P1 scope is **not** a universal requirement for offense ownership and is used only as the proven pre-Combat bridge.

P1-D was not run as a separate long-duration gate.

---

## C1-O2-P2 — Implemented, Source-Audited, Runtime Unverified

Implementation commit:

```text
cc51c67c19425be4e4d6a4838803ed3e66b2a071
```

Independent Normal Chat P2-A source review: **PASS**.

Source review confirms:

- the generic `RunScriptFunction` pre-native path remains stack-local/TLS bookkeeping only;
- the rejected `g_ScriptFunctionDispatchStack` / old Begin-End machinery was not reconnected;
- live-frame/actor/source/C1 acquisition work is lazy at a real successful offense event;
- the exact live SPU/runtime-stack/ScriptFunction/non-null-arguments/equipped-source checks remain the acquisition boundary;
- matching CombatMove reuses the same pre-acquired generation and consumes/retires the temporary native-frame binding immediately;
- an unconsumed bridge is diagnostic and is retired before wrapper return without dropping the real source obligation;
- ordinary CombatMove-created generation behavior, cleanup/finalization semantics, marker behavior, hook transport and physical collision behavior were not deliberately changed.

One source-review omission remains mechanical rather than architectural: the startup log still identifies only the P1 bridge. Before P2-B load validation, add an explicit P2 startup banner so the tested binary can be identified unambiguously.

---

## Current Immediate Responsibility — C1-O2-P2-B Build / Isolated Load

The next responsibility is **not another architecture/Work task**.

After the P2 startup-banner identity correction is committed, Normal Chat hands the branch to the User for the normal local sequence:

```text
sync exact branch
→ build Script_FrameCollisionTest
→ deploy exact DLL
→ verify one live DLL + built/live SHA256 match
→ isolated main-menu load/unload
→ require exact P2 startup banner
→ preserve raw isolated-load evidence
```

P2-C targeted 2H GetUp correlation is authorized only after P2-B passes.

P2-C is expected to test the intended meaning:

```text
initial legitimate GetUp offense
→ pre-Combat generation acquired
→ C1 source obligation belongs to that generation
→ matching CombatMove reuses same generation
→ PRECOMBAT_BRIDGE_CONSUMED
→ no unconsumed-bridge invariant
→ later timer offense remains attributed to durable generation
→ native cleanup fulfills same generation
→ physical repair remains OFF
```

Representative ordinary Normal attacks remain a control; they do not require a live `RunScriptFunction` scope at timer offense.

Exact runtime filenames and commands are frozen by Normal Chat at the relevant local stage, following `PROJECT_PIPELINE.md` and `PROJECT_OPERATING_PROCEDURES.md`.

---

## Qualified Runtime Observations To Preserve

These are useful future test hypotheses, not established causal mechanisms:

- a reaction/knockdown sequence appeared to restore a stale source to the equipped collision state before a later GetUpAttack reactivated it; the exact cleanup owner was not isolated;
- holster/draw appeared to restore stale collision; do not attribute this specifically to bone detachment or equip mechanics without a targeted sequence.

Route to EV-203 before using either observation architecturally.

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
| C1-O2 / hook/finalizer continuation evidence | `EVIDENCE_LEDGER_STEP_C.md` EV-199–EV-204 |
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

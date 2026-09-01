# Gothic 3 Animation Behaviors — Research Topic & History Map

**Status:** Cold/reference research router  
**Updated:** 2026-09-01

## Purpose

Recover **where a line of research happened, what durable result came from it, and where to retrieve the exact evidence now**.

This document is **not current continuation state** and must never declare a live technical gate.

Current state:

```text
docs/SESSION_ENTRYPOINT.md
docs/BETWEEN_CHATS.md
```

Exact evidence:

```text
docs/EVIDENCE_INDEX.md
→ docs/EVIDENCE_LEDGER*.md
```

The full pre-information-architecture research map—including old “current prototype” and “next” sections—is preserved at:

`docs/archive/technical_2026-08-27/RESEARCH_MAP_pre_ia.md`

Use this active file as a topic/history router, not as a document to read end-to-end for ordinary continuation.

---

## 1. Evidence Vocabulary

Canonical statuses used by the ledgers include:

- **CONFIRMED**
- **STRONGLY SUPPORTED**
- **WORKING HYPOTHESIS**
- **UNKNOWN**
- **DESIGN DECISION**

This map summarizes topics; it does not promote or downgrade evidence. Open the exact EV entry when status/qualification matters.

Current ledger storage split:

```text
EV-001–EV-157   EVIDENCE_LEDGER.md
EV-158–EV-198   EVIDENCE_LEDGER_STEP_B.md
EV-199–EV-205   EVIDENCE_LEDGER_STEP_C.md
EV-206–EV-214   EVIDENCE_LEDGER_STEP_D.md
EV-215 onward   EVIDENCE_LEDGER_STEP_E.md
```

---

## 2. Project Research Lines

| Research line | Durable result / current relevance | Primary retrieval route |
|---|---|---|
| CombatMove phase/speed | measured native family/phase speeds; `AniSpeedScale` is real duration authority; upstream speed hook proven but compatibility constrained | EV-001–EV-011; `DESIGN.md` playback speed; `SOURCE_HOOK_GUIDE.md` |
| Raise insertion | `PREPEND_BREAK_BLOCK` can prepend custom Raise while preserving original melee state/Hit continuation | EV-006–EV-007; `DESIGN.md` Raise |
| Frame-effect channel | authored `.xmot` frame effects reach `UpdateFrameEffects`/`StartEffect`; exact motion can be scanned before dispatch | EV-012–EV-018; source guide |
| Marker timing / playback speed | marker timing follows authored animation time and scales with playback; tested latency negligible | EV-020–EV-023; `ANIMATION_RULES.md` |
| Native weapon collision reset | ordinary tested weapon cleanup is `Item_Attack(7) -> Item_Equipped(5)`; later work proved cleanup can be lost on destructive abandonment | EV-019, EV-151–EV-207 |
| Quick callback/bookkeeping | `OnAI_QuickAttack` + StatePosition handling enabled marker-controlled Quick without post-reset native reactivation | EV-026–EV-028, EV-066–EV-075 |
| Fist/body contact | logical Fist contacts can damage through several body contacts without weapon-style group activation; general source adapter remains separate | EV-029–EV-032, EV-080–EV-085, EV-207, EV-211 |
| Dual physical source mapping | Normal/Quick/Pierce/Power source behavior mapped; R/L attack-direction metadata is not collision-hand authority | EV-047–EV-059, EV-090–EV-094 |
| Multi-target / repeated-contact rearm | one window can hit multiple targets; repeated same-target authored contacts require source rearm | EV-106–EV-116 |
| Exact-set markers | RIGHT/LEFT/BOTH/OFF complete desired-set semantics validated and vocabulary frozen | EV-112–EV-116, EV-143–EV-144 |
| Marker execution lifetime | interruption exposed occurrence-budget leakage across executions; marker bookkeeping is distinct from physical cleanup | EV-131–EV-133, EV-167 |
| Generation-scoped marker identity | durable C1 generation replaced older marker-local guesses about execution boundaries while independent marker invariants remained | EV-213; `MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md` |
| Literal historical marker regression closure | restored two-contact 2H Normal proved interrupted execution budget does not leak into next same-motion generation; Dual all-marker exact-set preservation also exercised | EV-214 |
| Whirl family separation | Dual SimpleWhirl/action 6 and full 2H/Staff Whirl/action 10 are separate runtime families | EV-145–EV-153 |
| New Balance / AttackCollision compatibility | tested marked Whirl configurations can coexist, but arbitrary same-function hook chaining/load order is not proven | EV-035, EV-148–EV-150 |
| Staff/block-skip stale collision | native and marked tests proved stale offense can survive bad teardown and later damage while moving | EV-151–EV-156, EV-180–EV-181 |
| Actual PrimaryFirst lifetime | PlayMotion type0 gives replacement evidence; action/phase can drift while physical Hit remains; replacement precedes cleanup | EV-157–EV-160, EV-174–EV-180 |
| Recover lifecycle | Recover asset playback is not required for native cleanup/bookkeeping; StartRecover is not universal cleanup authority | EV-154, EV-160–EV-162 |
| Native cleanup call sites | ordinary cleanup is action-specific; legitimate reaction interruption has a separate cleanup route | EV-163–EV-166; cleanup callsite map |
| Generic script parents | `RunScriptFunction` / `RunScriptState` converge in generic processing; neither is unconditional combat cleanup authority | EV-169–EV-171, EV-195 |
| State-stack abandonment | held-Use2 bad route terminates CombatMove and destroys suspended attack continuation while legitimate reactions have separate cleanup ownership | EV-182–EV-191 |
| C1 execution/source guard | monotonic generation + exact source obligations distinguish successful offense, cleanup and terminal outstanding state | EV-192–EV-193 |
| GetUp pre-Combat acquisition | legitimate offense can occur before CombatMove, requiring the lightweight outer ScriptFunction bridge | EV-194–EV-196 |
| Hook/finalizer transport stabilization | explicit-this transport corrections and source-liveness hardening stabilized behavior-critical hooks/finalization | EV-199–EV-203 |
| C1-O2 outer bridge closure | pre-Combat exact offense can lazily acquire C1 and matching CombatMove consumes the temporary native bridge | EV-204–EV-205 |
| C1-R1 physical repair | exact live/equipped outstanding weapon source gets one native-equivalent `7 -> 5` repair; clean/reaction/source-negative paths remain non-mutating | EV-206–EV-207 |
| Second-pass modular architecture | central EngineBridge, behavior modules, source operations, diagnostics-independent lifecycle and diagnostics-free behavior target implemented | EV-208; `SECOND_PASS_REWRITE_CONTRACT.md` |
| CORE diagnostic sufficiency | compact diagnostic twin proved required lifecycle/marker/source sentinels after one diagnostics-only context correction | EV-209–EV-211 |
| Diagnostics-free behavior product | behavior-only target functions without diagnostic sources/state/hooks | EV-212 and final EV-215 |
| Architecture verification completion | Gate 4 + literal historical regression + final behavior-only smoke completed the new collision architecture verification | EV-213–EV-215 |
| Animation-name semantics | actor family, UseType normalization, poses, action/phase serialization, overlays, distance and direction metadata | `ANIMATION_INDEX.md` → `ANIMATION_RULES.md` |
| Animation family/asset inventory | exact human melee assets, Raise availability, possible unused files, stumbles and controlled fixtures | `ANIMATION_INDEX.md` → `ANIMATION_CATALOG.md` / data lists |
| Future animation selection / disabled variants | CombatMove animation-string interception at `Game +0x16B065` is reusable engine knowledge; jump/wade/climb remain later work | `SOURCE_HOOK_GUIDE.md` third-party/reference patterns |

---

## 3. Milestone Timeline — Retrieval, Not Current Authority

### Foundation — EV-001–EV-025

- Win32/CMake/Gothic SDK build path established.
- CombatMove logger established phase/speed baseline.
- Raise prepend proof established.
- Frame-effect marker channel reverse-engineered and proven.

### Normal / Quick marker ownership — EV-026–EV-075

- Normal exact-motion marker ownership proven.
- Quick callback and StatePosition behavior isolated/fixed.
- Player + controlled human NPC Quick validation completed.

### Fist/source causality and Dual map — EV-080–EV-094

- Fist weapon-style group request shown unnecessary for tested contacts while list rearm remained.
- Dual Normal/Quick/Pierce/Power physical source map logged.

### Repeated-contact / exact-set / replay protection — EV-106–EV-144

- multi-target single window confirmed;
- same-target second contact isolated to later `ClearTriggeredList()` rearm;
- OFF window closure validated;
- repeated frame-effect replay discovered;
- same-update duplicate + authored-occurrence budget architecture validated;
- LEFT/BOTH/mixed exact-set behavior and final marker vocabulary validated;
- interruption exposed the historical occurrence-budget execution-lifetime defect.

### Full Whirl and native cleanup defect — EV-145–EV-167

- full Whirl/action 10 separated from Dual SimpleWhirl/action 6;
- 2H/Staff marked Whirl contact behavior validated;
- rare Staff cleanup failure reproduced;
- no-Recover Quick and native Staff/Dual cases broadened the defect;
- stale collision proved physically harmful/native;
- native cleanup callsites and marker-bookkeeping/physical-cleanup distinction established.

### Step B lifecycle causal search — EV-158–EV-191

- B1 replacement proved too early for repair;
- callback and StartRecover boundaries rejected;
- missing Recover asset rejected as root cause;
- action-specific + reaction cleanup map built;
- generic script parents identified;
- replacement-time post-script candidate rejected;
- FullStop/SetState causal chain established;
- held-Use2 abandonment generalized across tested families;
- AISetState ordering established native cleanup precedence and bad-path no-cleanup condition.

### C1 identity and source obligation — EV-192–EV-205

- C1 monotonic generation/source-obligation model implemented in shadow form;
- core bad/clean/reaction/pre-activation/inherited-stale controls passed;
- GetUp exposed legitimate pre-Combat offense;
- outer ScriptFunction lifetime/correlation proved;
- transport/finalizer substrate stabilized;
- lightweight pre-Combat bridge closed the acquisition gap without durable raw-frame identity.

### C1-R1 physical repair closure — EV-206–EV-207

- exact outstanding live/equipped weapon source `7 -> 5` repair validated;
- ordinary/reaction/GetUp/no-offense controls remained non-mutating;
- Dual exact-source independence, marker interaction, Fist/crossbow negatives and broad player/NPC hook stability closed the controlled gate.

### Second-pass architecture and product separation — EV-208–EV-212

- structural rewrite separated EngineBridge, marker policy, source facts/operations, lifecycle and diagnostics;
- behavior-only target mechanically excluded diagnostics;
- CORE diagnostic matrix passed after bounded diagnostic-context restoration;
- behavior-only target loaded and functioned without diagnostic dependency.

### Generation-scoped marker bookkeeping and final verification — EV-213–EV-215

- C1 generation became durable marker occurrence/dedupe execution identity;
- older source/motion/action/phase/state-time and controlled-callback rollback execution guesses were removed/consolidated;
- exact physical marker-owned source-bit/window retirement remained separate;
- literal historical EV-131 same-motion interruption/restart defect was directly closed with restored two-contact 2H Normal;
- final diagnostics-free restored-fixture/mixed-combat smoke passed;
- **new collision architecture verification completed**.

This timeline records history only. It does not authorize another diagnostic matrix or define what the project should do next.

---

## 4. Topic Search Keywords

Use exact terms rather than reading broad documents:

```text
AniSpeedScale
PREPEND_BREAK_BLOCK
UpdateFrameEffects
StartEffect
G3AB_COL_RIGHT
G3AB_COL_LEFT
G3AB_COL_BOTH
G3AB_COL_OFF
ClearTriggeredList
MarkerExecutionBudget
C1Generation
ExecutionBudgetReset
RetireMarkerOwnedSource
Item_Attack
Item_Equipped
SetCollisionGroup
RunScriptFunction
AISetState
AIFullStop
FullStop
AttackContinuationProtection
LivenessEstablished
REPAIRED_TO_ITEM_EQUIPPED
NewBalance
Jackydima
```

Use `EVIDENCE_INDEX.md` to route the term to exact evidence.

---

## Core Rule

> **History explains how the project learned something; current authorities define what is true now. Use this map to find history, never to override `SESSION_ENTRYPOINT.md`, `DESIGN.md`, subsystem authorities or the canonical evidence ledger.**

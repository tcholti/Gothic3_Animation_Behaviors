# Gothic 3 Animation Behaviors — Research Topic & History Map

**Status:** Cold/reference research router  
**Updated:** 2026-08-27

## Purpose

This document helps recover **where a line of research happened, what durable result came from it, and where to retrieve the exact evidence now**.

It is **not** the current continuation state.

Current state and next responsibility live in:

`docs/SESSION_ENTRYPOINT.md`

Exact evidence status/provenance lives in:

`docs/EVIDENCE_INDEX.md` → `EVIDENCE_LEDGER.md` / `EVIDENCE_LEDGER_STEP_B.md`

The full pre-information-architecture research map—including old “current prototype” and “next” sections—is preserved at:

`docs/archive/technical_2026-08-27/RESEARCH_MAP_pre_ia.md`

Use this active file as a topic/history router, not as a document to read end-to-end for ordinary continuation.

---

## 1. Evidence Vocabulary

Canonical statuses used by the ledgers:

- **CONFIRMED**
- **STRONGLY SUPPORTED**
- **WORKING HYPOTHESIS**
- **UNKNOWN**
- **DESIGN DECISION**

This map summarizes topics; it does not promote or downgrade evidence. When status matters, open the exact evidence entry.

---

## 2. Project Research Lines

| Research line | Durable result / current relevance | Primary retrieval route |
|---|---|---|
| CombatMove phase/speed | measured native family/phase speeds; `AniSpeedScale` is real duration authority; upstream speed hook proven but compatibility constrained | EV-001–EV-011; `DESIGN.md` §5; `SOURCE_HOOK_GUIDE.md` Speed |
| Raise insertion | `PREPEND_BREAK_BLOCK` can prepend custom Raise while preserving original melee state/Hit continuation | EV-006–EV-007; `DESIGN.md` §4 |
| Frame-effect channel | authored `.xmot` frame effects reach `UpdateFrameEffects`/`StartEffect`; exact motion can be scanned before dispatch | EV-012–EV-018; source guide Frame effects |
| Marker timing / playback speed | marker timing follows authored animation time and scales with playback; tested latency negligible | EV-020–EV-023; `ANIMATION_RULES.md` §20 |
| Native weapon collision reset | ordinary tested weapon path cleans `Item_Attack(7) -> Item_Equipped(5)`; later work proved this is not guaranteed across every ending | EV-019, EV-151–EV-156, EV-163–EV-168 |
| Quick callback/bookkeeping | `OnAI_QuickAttack` + StatePosition handling enabled marker-controlled Quick without post-reset native reactivation | EV-026–EV-028, EV-066–EV-075 |
| Fist/body contact | tested logical Fist contacts can damage via several limbs/head without weapon-style collision-group activation; body-source generalization remains bounded | EV-029–EV-032, EV-080–EV-085; `ANIMATION_CATALOG.md` Fist fixture |
| Dual physical source mapping | runtime mapped Normal/Quick/Pierce/Power source behavior and proved R/L attack-direction metadata is not collision-hand authority | EV-047–EV-059, EV-090–EV-094; `ANIMATION_CATALOG.md` source sections |
| Multi-target / repeated-contact rearm | one weapon window can hit multiple distinct targets; repeated same-target contact needs source rearm; Gothic frame-effect replay requires duplicate/occurrence guards | EV-106–EV-116 and later marker-core evidence |
| Exact-set markers | RIGHT/LEFT/BOTH/OFF desired-set semantics validated and final equipped-slot spellings frozen | EV-112–EV-116, EV-143–EV-144; `DESIGN.md` §6 |
| Marker execution lifetime | interruptions exposed stale occurrence-budget ownership even when physical collision had already cleaned; marker bookkeeping is distinct from physical cleanup | EV-131–EV-133, EV-167 |
| Whirl family separation | Dual SimpleWhirl/action 6 and full 2H/Staff Whirl/action 10 are separate runtime families despite shared serialized filename wording | EV-145–EV-153; `ANIMATION_RULES.md` §8.1 |
| NewBalance / AttackCollision compatibility | tested configurations can coexist for marked 2H Whirl, but arbitrary same-function hook chaining/load order is not proven | EV-035, EV-148–EV-150; source guide Same-Function Hook Caution |
| Staff/block-skip stale collision | native and marked tests proved real stale offensive collision can survive bad teardown and cause later running/contact damage | EV-151–EV-156 |
| Actual PrimaryFirst lifetime | PlayMotion type0 gives immediate replacement evidence; action/phase can drift while physical Hit remains; replacement itself precedes cleanup | EV-157–EV-160 |
| Recover lifecycle | Recover asset playback is not required for native cleanup/bookkeeping; StartRecover is not universal or post-cleanup | EV-154, EV-160–EV-162 |
| Native cleanup call sites | ordinary cleanup is action-specific; legitimate damage/reaction interruption has a separate tested route | EV-163–EV-166; `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| Generic script parents | B5 parents identified as `RunScriptFunction` / `RunScriptState`; both converge higher in generic `ProcessScript()`; CombatMove instruction completion is too early | EV-169–EV-171; cleanup map / source guide |
| Deferred finalization candidate | exact replacement may mark pending finalization, then a tightly gated post-script timing opportunity may verify/repair after Gothic's native chance | EV-172; `COLLISION_LIFECYCLE_PLAN.md` §8–§9; B6 pending runtime |
| Animation-name semantics | actor family, UseType normalization, poses, action/phase serialization, overlay/non-overlay, distance, direction metadata | `ANIMATION_INDEX.md` → `ANIMATION_RULES.md` |
| Animation family/asset inventory | exact human melee assets, Raise availability, possible unused files, stumbles, test fixtures | `ANIMATION_INDEX.md` → `ANIMATION_CATALOG.md` / data lists |
| Future animation selection / disabled variants | practical CombatMove animation-string interception at `Game + 0x16B065` is reusable engine knowledge; jump/wade/climb questions remain later research | `SOURCE_HOOK_GUIDE.md` Third-Party Reference Patterns |

---

## 3. Milestone Timeline — Retrieval, Not Current Authority

### Foundation

- Win32/CMake/Gothic SDK build path established.
- CombatMove logger established phase/speed baseline.
- Raise prepend proof established.
- frame-effect marker channel reverse-engineered and proven.

Evidence: EV-001–EV-025.

### Normal / Quick marker ownership

- Normal exact-motion marker ownership proven.
- Quick callback and StatePosition behavior isolated/fixed.
- player + controlled human NPC Quick validation completed.

Evidence: EV-026–EV-075.

### Fist/source causality and Dual map

- Fist weapon-style group request shown unnecessary for tested contacts while list rearm remained.
- Dual Normal/Quick/Pierce/Power physical source map logged.

Evidence: EV-080–EV-094.

### Repeated-contact / OFF / replay protection

- multi-target single window confirmed;
- same-target second contact isolated to later `ClearTriggeredList()` rearm;
- OFF physical window closure validated;
- repeated frame-effect replay discovered;
- same-update duplicate + authored-occurrence budget architecture validated.

Evidence: EV-106 onward through the marker-core sequence; exact fixture history remains in the evidence ledger, catalog, raw logs, and archived pre-IA docs.

### Multi-source exact-set and final vocabulary

- LEFT, BOTH, mixed exact-set transitions, interruption handling, NPC overlapping battle stress and missing-slot fallback validated;
- final `G3AB_COL_RIGHT/LEFT/BOTH/OFF` spelling validated.

Key evidence: EV-131–EV-144.

### Full Whirl and native cleanup defect

- full Whirl/action 10 separated from Dual SimpleWhirl/action 6;
- 2H/Staff marked Whirl contact behavior validated;
- rare Staff final cleanup failure reproduced;
- no-Recover Quick and native Staff/Dual cases showed the defect is broader than one asset/family;
- stale collision proven physically harmful and native in origin.

Evidence: EV-145–EV-162.

### Step B lifecycle causal search

- B1 PlayMotion: immediate replacement, too early for repair;
- B2 callback boundary rejected;
- B3 StartRecover boundary rejected;
- B3b missing Recover asset rejected as root cause;
- B4/B4b action-specific + interruption cleanup map;
- B5 parent stacks;
- static identification of generic script runners / `ProcessScript()`.

Evidence: EV-158–EV-172.

### Current B6 boundary experiment

Source-only diagnostic is implemented and independently reviewed; runtime validation remains pending.

Current authority: `SESSION_ENTRYPOINT.md`, `COLLISION_LIFECYCLE_PLAN.md`, `COLLISION_TEST_PLAN.md`.

Do not treat the older chronological map as a newer next-step instruction.

---

## 4. Topic Search Keywords

Use these exact terms when searching the repository rather than reading broad documents:

### Collision / marker

`G3AB_COL_RIGHT`  
`G3AB_COL_LEFT`  
`G3AB_COL_BOTH`  
`G3AB_COL_OFF`  
`ClearTriggeredList`  
`SetCollisionGroup`  
`Item_Attack`  
`Item_Equipped`  
`MarkerExecutionBudget`  
`MarkerOwnedCollisionWindow`  
`RetireMarkerOwnedSource`

### CombatMove / script

`PlayMotion`  
`StopMotion`  
`sAICombatMoveInstr`  
`sAICombatMoveStart`  
`sAICombatMoveItlLoop`  
`sAICombatMoveStartRecover`  
`RunScriptFunction`  
`RunScriptState`  
`ProcessScript`

### Actions

`gEAction_Attack`  
`PowerAttack`  
`QuickAttackR` / `QuickAttackL`  
`SimpleWhirl`  
`WhirlAttack`  
`PierceAttack`  
`HackAttack`  
`FinishingAttack`  
`GetUpAttack`

### Animation semantics

`gEUseType`  
`gEPhase`  
`gEPose`  
`HitDirection`  
`QuickStumble`  
`LightStumble`  
`CombatMove distance`  
`frame indexing`

---

## 5. Raw Evidence Routing

### Current causal/lifecycle raw logs

`research/raw/`

Notable Step-B names include:

- `researchraw2026-08-26_framecollision_stepB1_primaryfirst_event_probe.log`
- `2026-08-26_stepB2_causal_extract.log`
- `2026-08-26_stepB3_native_startrecover_probe.log`
- `2026-08-26_stepB3b_native_block_skip_comparison.log`
- `2026-08-26_stepB4_native_cleanup_callsite_probe.log`
- `2026-08-26_stepB4b_native_manyattacks_cleanup_callsite.log`
- `2026-08-26_stepB4b_native_finishing_blow_cleanup_callsite.log`
- `2026-08-26_stepB4b_native_interruption_cleanup_callsite.log`
- `2026-08-26_stepB5_cleanup_parent_stack_probe.log`

### Processed historical runtime logs

`research/archive/`

Names encode date, prototype version, actor/family, and experiment. Prefer evidence IDs first; open raw logs when verifying a claim or extracting a fact not represented in the ledger.

### Long source/history intake

`research/archive/2026-08_pre_github_animation_behaviors_chat_log.txt`

Useful for provenance/history, not current authority.

---

## 6. Open / Deferred Research Backlog

These are **not automatically next**. Retrieve them only when the project reaches the relevant responsibility.

### Collision lifecycle

- B6 runtime comparison of clean/reaction/bad replacement stacks;
- post-native-opportunity checkpoint if B6 supports it;
- final attack-wide vs source-aware repair decision;
- negative Fist/ranged/magic regression if generic script timing is used;
- defensive block/parade collision semantics before release if cleanup operation could disturb them.

### Raise / speed

- broaden Raise from proven Normal path to intended Normal/Quick/full-Whirl assets;
- calibrate final profile speeds from measured durations;
- choose speed intervention that avoids unsafe same-function compatibility.

### Animation selection / broader mechanics

- investigate disabled/unused weapon jump selection;
- investigate Wade animation selection;
- later simple climbing feasibility;
- explore CombatMove animation-string substitution only when a feature actually needs it.

### Actor/source generalization

- body/Fist marker vocabulary beyond tested logical Fist scope;
- PhysicalFist and monster-specific body/limb/head source models;
- broader creature family support.

---

## 7. Historical Retrieval Rule

When an older decision or implementation detail matters:

```text
current question
→ EVIDENCE_INDEX / topic row here
→ exact evidence ID
→ raw log / source commit if needed
→ archived pre-IA document only when chronology or omitted implementation rationale matters
```

Do not reconstruct current project state from an old v0.x narrative when current authorities already exist.

---

## 8. Authority Rule

If this file conflicts with a newer current-state statement:

1. `SESSION_ENTRYPOINT.md` owns current continuation;
2. current source/commits own implementation truth;
3. evidence ledgers own evidence status/provenance;
4. current design/lifecycle documents own architecture;
5. this map owns historical/topic routing only.

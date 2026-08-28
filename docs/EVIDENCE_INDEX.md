# Gothic 3 Animation Behaviors — Evidence Index

**Status:** Cold/reference routing index  
**Updated:** 2026-08-28

## Purpose

Route a technical question to the smallest relevant evidence range without loading the complete evidence ledgers.

Canonical evidence remains:

- `EVIDENCE_LEDGER.md` — EV-001 through EV-157;
- `EVIDENCE_LEDGER_STEP_B.md` — EV-158 onward.

This index **does not restate or change evidence status**. Search/open the exact EV entry when wording, qualification, provenance, build scope, or engineering consequence matters.

Raw logs are verification/provenance, not routine reading.

---

## 1. Fast Topic Routing

| Topic / search intent | Start with | Then broaden if needed |
|---|---|---|
| CombatMove fields, native phase/speed baselines | EV-001–EV-011 | `SOURCE_HOOK_GUIDE.md` Speed / CombatMove symbols |
| Raise prepend proof / engine animation resolution | EV-006–EV-007 | `DESIGN.md` §4 |
| frame effects / marker channel / frame-effect layout | EV-012–EV-018 | source guide Frame effects |
| ordinary natural weapon reset / marker timing | EV-019–EV-023 | later lifecycle evidence if asking about abnormal endings |
| Staff + NPC actor-general marker proof | EV-024–EV-028 | Quick implementation evidence EV-066+ |
| Fist/body-contact source semantics | EV-029–EV-032, EV-080–EV-085 | `ANIMATION_CATALOG.md` Fist fixture |
| repeated-hit rearm / triggered lists | EV-033, EV-106–EV-116 | marker-core later evidence / catalog fixtures |
| Hero family / poses / UseType / R-L semantics | EV-036–EV-065 | `ANIMATION_INDEX.md` |
| Quick marker ownership / StatePosition | EV-066–EV-075 | EV-182–EV-184 for native lifecycle/bookkeeping context |
| Dual native source map | EV-090–EV-094 | `ANIMATION_CATALOG.md` §6–§7 |
| multi-target, OFF, duplicate/replay/occurrence guard | EV-106–EV-116 | archived v0.10–v0.13 fixture logs |
| marker execution retirement after interruption | EV-131–EV-133 | EV-167, EV-182–EV-184 for later lifecycle interpretation |
| final RIGHT/LEFT/BOTH/OFF vocabulary | EV-143–EV-144 | `DESIGN.md` §6 / `ANIMATION_RULES.md` §20 |
| Whirl callback/action/source separation | EV-145–EV-147 | `ANIMATION_RULES.md` §8.1 / cleanup map |
| NewBalance / AttackCollision Whirl compatibility | EV-035, EV-148–EV-150 | `SOURCE_HOOK_GUIDE.md` same-function caution |
| Staff full-Whirl cleanup anomaly | EV-151–EV-153 | EV-155–EV-156, EV-180–EV-184 for bad-skip lifecycle |
| Recover asset vs lifecycle cleanup | EV-154, EV-160–EV-162 | `COLLISION_LIFECYCLE_PLAN.md` Step-B constraints |
| marked block-timeout failure | EV-155 | native control EV-156 |
| native stale collision / running damage | EV-156, EV-181 | archived 2026-08-25 native logs / latest B6-D raw |
| v0.20 PrimaryFirst lifetime sampling | EV-157 | B1 EV-158 |
| PlayMotion actual replacement timing | EV-158 | B6 EV-174–EV-180 |
| later original callback is not completion | EV-159 | EV-171 static callback ordering |
| StartRecover not post-cleanup / not guaranteed | EV-160 | EV-176 / EV-180 clean-vs-bad comparison |
| no-Recover and Dual Quick broad defect | EV-161–EV-162 | archived B3b log |
| action-specific native cleanup matrix | EV-163 | `COLLISION_CLEANUP_CALLSITE_MAP.md` §2 |
| same serialized asset, different runtime action | EV-164 | cleanup map §3 |
| legitimate reaction interruption cleanup/successor | EV-165, EV-177–EV-179, EV-184 | cleanup map §4 / `COLLISION_TEST_PLAN.md` B6-C/B7 |
| B5 parent stack | EV-166 | EV-169–EV-170 static identification |
| marker bookkeeping vs physical cleanup | EV-167, EV-182–EV-184 | `COLLISION_LIFECYCLE_PLAN.md` §10 |
| future marker-core simplification / native execution boundary | EV-066–EV-075, EV-131–EV-133, EV-167, EV-182–EV-184 | **Read `COLLISION_LIFECYCLE_PLAN.md` §10 before changing marker bookkeeping** |
| ordinary / reaction / bad-skip three-path model | EV-168, EV-179–EV-184 | lifecycle plan §§9–12 |
| `RunScriptState` / `RunScriptFunction` identification | EV-169 | cleanup map §§5–6 |
| `ProcessScript()` common generic dispatcher | EV-170, EV-176 | EV-180 for failed universal replacement-time validation |
| callback processing after main script dispatch | EV-171 | cleanup map §8 |
| deferred pending-finalization/post-script candidate | EV-172 | **superseded by EV-180**; lifecycle plan §8 |
| live `scripts` backup-DLL contamination | EV-173 | `SOURCE_HOOK_GUIDE.md` build/runtime reference |
| B6 clean path disappearance + ProcessScript stack | EV-174–EV-176 | `COLLISION_TEST_PLAN.md` B6-B |
| B6 reaction successor context | EV-177–EV-179 | `COLLISION_TEST_PLAN.md` B6-C |
| B6 bad skip context / no useful ScriptAdmin replacement stack | EV-180 | `COLLISION_TEST_PLAN.md` B6-D |
| long-lived stale group 7 through idle / later inherited 7->7 | EV-181 | `COLLISION_LIFECYCLE_PLAN.md` §§1–2 / B7 rationale |
| persisted CombatMove instruction / FullStop semantics | EV-182 | `COLLISION_LIFECYCLE_PLAN.md` §9 / `SOURCE_HOOK_GUIDE.md` CombatMove symbols |
| full-Whirl break-block continuation to native cleanup | EV-183 | `COLLISION_LIFECYCLE_PLAN.md` §§9–11 |
| reaction-side FullStop before separate reaction ownership | EV-184 | `COLLISION_LIFECYCLE_PLAN.md` §§9–11 |
| current attack-lifecycle/bookkeeping reconstruction | EV-066–EV-075, EV-131–EV-133, EV-167, EV-179–EV-184 | `COLLISION_TEST_PLAN.md` B7 / `COLLISION_LIFECYCLE_PLAN.md` §§9–10 |

---

## 2. Evidence by Engineering Domain

### A. Raise and playback speed

Search terms:

`AniSpeedScale`, `GetAnimationSpeedModifier`, `PREPEND_BREAK_BLOCK`, `Raise`, `RecoverSpeed`

Evidence anchors:

- EV-001–EV-011.

Architecture:

- `DESIGN.md` §4–§5.

### B. Animation-authored frame effects

Search terms:

`UpdateFrameEffects`, `StartEffect`, `eSFrameEffect`, marker frame, playback synchronization

Evidence anchors:

- EV-012–EV-023.

Reference:

- `SOURCE_HOOK_GUIDE.md` Frame effects;
- `ANIMATION_RULES.md` §19–§20.

### C. Physical source selection

Search terms:

`RIGHT`, `LEFT`, `BOTH`, `Fist`, `Torch`, `Dual`, `Pierce`, `Power`, `QuickAttackR`, `QuickAttackL`

Evidence anchors:

- EV-029–EV-032;
- EV-047–EV-059;
- EV-080–EV-085;
- EV-090–EV-094;
- EV-145–EV-147.

Asset-level routing:

- `ANIMATION_INDEX.md`.

### D. Triggered-list rearm / multi-contact

Search terms:

`ClearTriggeredList`, `EntitiesVisited`, multi-target, same-target, duplicate dispatch, occurrence budget, OFF

Evidence anchors:

- EV-033;
- EV-106–EV-116;
- EV-143–EV-144.

Historical fixture details:

- `ANIMATION_CATALOG.md` §12;
- `research/archive/2026-08-22_framecollision_v0.10_*`;
- `research/archive/2026-08-23_framecollision_v0.11_*` through v0.18 fixture logs.

### E. Marker execution lifetime / bookkeeping

Search terms:

`MarkerExecutionBudget`, `RetireMarkerOwnedSource`, `StatePosition`, interruption, stale budget, exact-set switching, `m_pfInstrCallback`, `sAICombatMoveInstr`, `FullStop`, break block, CombatMove completion

Evidence anchors:

- EV-066–EV-075;
- EV-131–EV-133;
- EV-167;
- EV-181–EV-184.

Architecture:

- `COLLISION_LIFECYCLE_PLAN.md` §§9–10;
- `COLLISION_TEST_PLAN.md` B7.

**Marker reimplementation/review rule:** before consolidating or optimizing the marker core, read this evidence set and `COLLISION_LIFECYCLE_PLAN.md` §10. The native persisted CombatMove/break-block lifecycle may eventually replace some custom execution/occurrence inference, but that is not yet proven safe. Preserve the existing `StatePosition` advancement, occurrence/replay protection, OFF/exact-set switching, repeated-contact rearm and interruption-retirement guarantees until a native exact-execution boundary is demonstrated.

### F. Native collision cleanup lifecycle

Search terms:

`Item_Attack`, `Item_Equipped`, `SetCollisionGroup`, cleanup, block skip, StartRecover, PlayMotion, StopMotion, ProcessScript, StateTime, StatePosition, `m_pfInstrCallback`, `FullStop`

Evidence anchors:

- EV-151–EV-184.

Exact native RVAs/stacks:

- `COLLISION_CLEANUP_CALLSITE_MAP.md`.

Current architecture/test:

- `COLLISION_LIFECYCLE_PLAN.md`;
- `COLLISION_TEST_PLAN.md`.

### G. Animation semantics and naming

Search terms:

`gEUseType`, `gEAction`, `gEPhase`, `gEPose`, `HitDirection`, destination pose, R/L, overlay, CombatMove distance

Evidence anchors:

- EV-036–EV-065.

Main routing:

- `ANIMATION_INDEX.md`.

### H. Compatibility / hook ownership

Search terms:

`NewBalance`, `Script_AttackCollision`, same-function hook, load order, ResetOnUntouch, backup DLL

Evidence anchors:

- EV-035;
- EV-045;
- EV-148–EV-150;
- EV-173.

Practical source route:

- `SOURCE_HOOK_GUIDE.md` §8–§11.

---

## 3. Step-B Evidence Quick Map

| Step | Evidence | Answer obtained |
|---|---|---|
| B1 | EV-158 | `PlayMotion(type 0)` is immediate actual-motion replacement evidence, but clean replacement precedes native cleanup |
| B2 | EV-159, EV-171 | later original callbacks are downstream/repeating, not one-shot completion |
| B3 | EV-160 | `sAICombatMoveStartRecover` is too early and can be bypassed |
| B3b | EV-161–EV-162 | missing Recover asset is not root cause; defect reproduces beyond Staff/Whirl |
| B4/B4b | EV-163–EV-165 | ordinary cleanup is action-specific; tested reaction interruption has separate route |
| B5 | EV-166 | ordinary/reaction successful paths reached adjacent but distinct Game parents |
| B5 static follow-up | EV-169–EV-171 | parents are generic script runners, common higher dispatcher is generic `ProcessScript()` |
| B6 environment | EV-173 | backup `Script_*.dll.bak` in live scripts can participate in runtime hooks; isolate test directory |
| B6 clean control | EV-174–EV-176 | clean completion exposes `sAICombatMoveInstr -> ProcessScript()` at StartRecover |
| B6 reaction comparison | EV-177–EV-179 | reaction cleanup and actual Stumble/KnockDown successor stacks are captured inside reaction Script_Game/ScriptAdmin context |
| B6 bad replacement | EV-180–EV-181 | armed Whirl can disappear to Ambient without StartRecover/cleanup; observed successor stack exposes no useful ScriptAdmin/SPU context and stale group 7 can persist through idle into a later attack |
| B6 design result | EV-172, EV-180 | replacement-triggered deferred-`ProcessScript()` candidate is superseded/rejected in its present form; execution-level invariant remains |
| B7 static reconstruction | EV-182–EV-184 | CombatMove persists as an SPU instruction; clean Whirl cleanup is a later Script_Game break-block continuation; reaction-control code can explicitly FullStop the current instruction |
| B7 current runtime gate | EV-182–EV-184 | determine whether bad block-skip invokes `sAICombatMoveInstr(..., fullStop=true)` or loses the instruction by another route |

---

## 4. Processed Step-B Log Routing

Processed logs are moved to `research/archive/` as their conclusions become canonical. Raw logs may remain temporarily in `research/raw/` while the current lifecycle comparison set is still active.

Key active comparative artifacts:

- `research/raw/2026-08-28_b6b_player_2h_normal_clean_completion_startrecover_stack.log`
- `research/raw/2026-08-28_b6c_player_2h_normal_legitimate_reaction_replacement_stack.log`
- `research/raw/2026-08-28_b6c2_player_2h_normal_legitimate_reaction_empty_primary_playmotion_stack.log`
- `research/raw/2026-08-28_b6c3_b6d_player_2h_clean_skip_and_reaction_successor_stacks.log`

Open archived/raw logs only when verifying ledger wording, reinterpreting a result, or extracting a new fact.

`research/raw/` is reserved for active/unprocessed or still-comparative evidence and current diagnostic output.

---

## 5. Historical Runtime Log Naming

Processed logs under `research/archive/` follow names such as:

```text
YYYY-MM-DD_framecollision_vX.Y_actor_family_experiment.log
```

Useful search tokens include:

- `staff_whirl`
- `block_timeout`
- `native_block_skip`
- `dual_normal`
- `quick`
- `fist`
- `multi_target`
- `duplicate_guard`
- `occurrence_guard`
- `final_markers`

Prefer the EV entry first because it records the qualification and engineering consequence already extracted from the raw session.

---

## 6. Evidence Maintenance Rule

When a new durable result is established:

1. add/modify the canonical EV entry with explicit status/provenance;
2. preserve the raw/source artifact when needed for verification;
3. update this index only if the result creates a new retrieval route or materially changes an existing topic range;
4. update current design/state documents only when their responsibility actually changes.

Do not copy the full experiment narrative into every design/reference document.
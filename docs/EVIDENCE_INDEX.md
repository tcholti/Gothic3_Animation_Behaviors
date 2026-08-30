# Gothic 3 Animation Behaviors — Evidence Index

**Status:** Cold/reference routing index  
**Updated:** 2026-08-30

## Purpose

Route a technical question to the smallest relevant evidence range without loading the complete evidence ledgers.

Canonical evidence remains:

- `EVIDENCE_LEDGER.md` — EV-001 through EV-157;
- `EVIDENCE_LEDGER_STEP_B.md` — EV-158 through EV-198;
- `EVIDENCE_LEDGER_STEP_C.md` — EV-199 through EV-205;
- `EVIDENCE_LEDGER_STEP_D.md` — EV-206 onward.

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
| Staff + NPC actor-general marker proof | EV-024–EV-028 | Quick implementation evidence EV-066+; R1-E NPC Staff stability EV-207 |
| Fist/body-contact source semantics | EV-029–EV-032, EV-080–EV-085, EV-207 | `ANIMATION_CATALOG.md` Fist fixture |
| repeated-hit rearm / triggered lists | EV-033, EV-106–EV-116 | marker-core later evidence / catalog fixtures |
| Hero family / poses / UseType / R-L semantics | EV-036–EV-065 | `ANIMATION_INDEX.md` |
| Quick marker ownership / StatePosition | EV-066–EV-075 | EV-182–EV-196 for native lifecycle/bookkeeping context |
| Dual native source map | EV-090–EV-094 | EV-207 for C1-R1 exact-source repair validation |
| multi-target, OFF, duplicate/replay/occurrence guard | EV-106–EV-116 | archived v0.10–v0.13 fixture logs |
| marker execution retirement after interruption | EV-131–EV-133 | EV-167, EV-182–EV-196, EV-207 for later lifecycle/terminal-repair interpretation |
| final RIGHT/LEFT/BOTH/OFF vocabulary | EV-143–EV-144 | `DESIGN.md` §6 / `ANIMATION_RULES.md` §20 |
| Whirl callback/action/source separation | EV-145–EV-147 | `ANIMATION_RULES.md` §8.1 / cleanup map |
| NewBalance / AttackCollision Whirl compatibility | EV-035, EV-148–EV-150 | `SOURCE_HOOK_GUIDE.md` same-function caution |
| Staff full-Whirl cleanup anomaly | EV-151–EV-153 | EV-155–EV-156, EV-180–EV-191, EV-206–EV-207 for validated guard outcome |
| Recover asset vs lifecycle cleanup | EV-154, EV-160–EV-162 | `COLLISION_LIFECYCLE_PLAN.md` constraints |
| marked block-timeout failure | EV-155 | native control EV-156; validated terminal repair EV-206–EV-207 |
| native stale collision / running consequence | EV-156, EV-181, EV-187, EV-190, EV-197–EV-198, EV-202–EV-203, EV-206 | active-problem reconstruction route below |
| v0.20 PrimaryFirst lifetime sampling | EV-157 | B1 EV-158 |
| PlayMotion actual replacement timing | EV-158 | B6 EV-174–EV-180 |
| later original callback is not completion | EV-159 | EV-171 static callback ordering |
| StartRecover not post-cleanup / not guaranteed | EV-160 | EV-176 / EV-180 clean-vs-bad comparison |
| no-Recover and Dual Quick broad defect | EV-161–EV-162 | EV-190 for held-Use2 state-stack-abandonment generality |
| action-specific native cleanup matrix | EV-163 | `COLLISION_CLEANUP_CALLSITE_MAP.md` §2 |
| same serialized asset, different runtime action | EV-164 | cleanup map §3 |
| legitimate reaction interruption cleanup/successor | EV-165, EV-177–EV-179, EV-184, EV-186, EV-188, EV-191, EV-203, EV-206 | cleanup map / lifecycle plan §3 |
| B5 parent stack | EV-166 | EV-169–EV-170 static identification |
| marker bookkeeping vs physical cleanup | EV-167, EV-182–EV-196, EV-206–EV-207 | `COLLISION_LIFECYCLE_PLAN.md` §9 |
| future marker-core simplification / native execution boundary | EV-066–EV-075, EV-131–EV-133, EV-167, EV-182–EV-196, EV-207 | **Read `COLLISION_LIFECYCLE_PLAN.md` §9 before changing marker bookkeeping** |
| ordinary / reaction / bad-skip ending model | EV-168, EV-179–EV-191 | lifecycle plan §§3–8 |
| `RunScriptState` / `RunScriptFunction` identification | EV-169, EV-195, EV-199 | cleanup map §§5–6 / source guide Script administration |
| `ProcessScript()` common generic dispatcher | EV-170, EV-176 | EV-180 for failed universal replacement-time validation |
| callback processing after main script dispatch | EV-171 | cleanup map §8 |
| deferred pending-finalization/post-script candidate | EV-172 | **superseded by EV-180**; lifecycle plan §7 |
| live `scripts` backup-DLL contamination | EV-173 | `SOURCE_HOOK_GUIDE.md` build/runtime reference |
| B6 clean path disappearance + ProcessScript stack | EV-174–EV-176 | historical lifecycle evidence |
| B6 reaction successor context | EV-177–EV-179 | historical lifecycle evidence |
| B6 bad skip context / no useful ScriptAdmin replacement stack | EV-180 | B6-D raw |
| long-lived stale group 7 / later inherited 7->7 | EV-181, EV-193, EV-203 | C1 core confirms new-generation attribution for inherited stale state |
| persisted CombatMove instruction / FullStop semantics | EV-182, EV-185–EV-191 | lifecycle plan §§3–4 / source guide CombatMove symbols |
| full-Whirl break-block continuation to native cleanup | EV-183, EV-189 | lifecycle plan §§3–4 |
| reaction-side FullStop before separate cleanup ownership | EV-184, EV-186, EV-188, EV-191, EV-203, EV-206 | lifecycle plan §3 |
| bad full-Whirl exact held-Use2 FullStop caller | EV-187 | `SOURCE_HOOK_GUIDE.md` §5 |
| exact tested Normal/Quick reaction FullStop caller | EV-188 | EV-191 adds another legitimate reaction caller; do not universalize one RVA |
| `FullStop -> SetState` state-stack abandonment causal chain | EV-189–EV-191 | B8 generality + B9 ordering close the tested known stale class |
| B8 cross-family held-Use2 state-stack abandonment | EV-190 | C1 design follows from the general execution-level failure class |
| B9 AISetState cleanup/finalization ordering | EV-191 | AISetState is a gated post-opportunity checkpoint, not unconditional cleanup |
| Alternative AI 2.5-second parade/held-Use2 trigger | EV-187, EV-197 | historical trigger plus tested-binary threshold; not production cleanup authority |
| Raise reproduction boundary | EV-153, EV-191, EV-198 | observed boundary only; mechanism and general immunity unproven |
| C1 shadow execution/source obligation model | EV-192–EV-193 | `SESSION_ENTRYPOINT.md` C1 core result |
| GetUp pre-CombatMove acquisition gap | EV-194 | outer ScriptFunction lifetime EV-195–EV-196 |
| outer ScriptFunction stack / `RunScriptFunction` persistence | EV-195 | pinned SDK + tested Game binary; runner is generic context only |
| C1-O1 live-frame correlation / pointer reuse | EV-196 | native frame is lifetime-bound correlator; C1 generation remains durable identity |
| C1-O2 original direct dispatch-capture crash / pure-pass-through baseline | EV-199 | do not infer later substrate stability solved the original capture crash |
| AISetState / AIFullStop explicit-this transport stability | EV-199–EV-200 | tested substrate prerequisite |
| SetCollisionGroup explicit-this transport / interrupted crash / corrected rerun | EV-201–EV-203 | EV-202 supersedes EV-201 root-cause interpretation; EV-203 is tested PASS |
| C1 finalizer remembered-source liveness crash and correction | EV-202–EV-203 | correction is stable; exact liveness-negative outstanding branch lacks positive runtime coverage |
| C1-O2 lightweight dispatch bridge / outer acquisition closure | EV-204–EV-205 | P1 establishes synchronous scope; P2 closes tested pre-Combat offense→CombatMove bridge model |
| C1-R1 controlled native-equivalent physical repair | EV-206–EV-207 | exact live/equipped outstanding weapon-source `7 -> 5` repair plus Dual/marker/broad/Fist/crossbow closure; controlled validation CLOSED |
| crossbow / bow / magic C1 negative regression | EV-207 | crossbow independently remains outside exact tracked C1 weapon-source ownership; bow/magic provide supplemental negative coverage |
| C1-R1 closure / next integration boundary | EV-207 | do not invent another R1 matrix; `SESSION_ENTRYPOINT.md` owns production-integration planning state |

---

## Active-Problem Reconstruction — Native Stale Melee Collision

When this stale-collision problem is the active engineering responsibility, a fresh Normal Chat should reconstruct this ordered causal route once before proposing a new fix or architecture. Do not load every raw log; retrieve exact raw evidence only when verifying or reinterpreting a specific fact.

1. **Historical trigger / manual reproduction context:** EV-187, EV-197, EV-198.
2. **Native stale physical consequence / persistence:** EV-156, EV-162, EV-181, EV-193, EV-202–EV-203, EV-206.
3. **Normal attack/CombatMove continuation and ordinary cleanup:** EV-163, EV-182–EV-183.
4. **Legitimate reaction interruption and separate cleanup ownership:** EV-165, EV-184, EV-186, EV-188, EV-191, EV-203, EV-206.
5. **Bad held-Use2 abandonment causal chain:** EV-185, EV-187, EV-189–EV-191.
6. **Cross-family generality:** EV-162, EV-190.
7. **Rejected Recover/StartRecover/replacement/callback explanations:** EV-154, EV-159–EV-162, EV-168, EV-174–EV-181.
8. **Raise reproduction boundary:** EV-153, EV-191, EV-198.
9. **C1 execution/source-obligation invariant and lifetime work:** EV-192–EV-196 → `COLLISION_LIFECYCLE_PLAN.md`.
10. **C1 hook/finalizer substrate stabilization:** EV-199–EV-203.
11. **C1-O2 outer acquisition/binding closure:** EV-204–EV-205.
12. **Controlled native-equivalent physical repair and closure:** EV-206–EV-207 → `COLLISION_LIFECYCLE_PLAN.md` / `COLLISION_TEST_PLAN.md`; `SESSION_ENTRYPOINT.md` owns the next production-integration responsibility.

---

## 2. Evidence by Engineering Domain

### A. Raise and playback speed

Search terms: `AniSpeedScale`, `GetAnimationSpeedModifier`, `PREPEND_BREAK_BLOCK`, `Raise`, `RecoverSpeed`

Evidence anchors: EV-001–EV-011.  
Architecture: `DESIGN.md` §4–§5.

### B. Animation-authored frame effects

Search terms: `UpdateFrameEffects`, `StartEffect`, `eSFrameEffect`, marker frame, playback synchronization

Evidence anchors: EV-012–EV-023.  
Reference: `SOURCE_HOOK_GUIDE.md` Frame effects; `ANIMATION_RULES.md` §19–§20.

### C. Physical source selection

Search terms: `RIGHT`, `LEFT`, `BOTH`, `Fist`, `Torch`, `Dual`, `Pierce`, `Power`, `QuickAttackR`, `QuickAttackL`, `Crossbow`

Evidence anchors:

- EV-029–EV-032;
- EV-047–EV-059;
- EV-080–EV-085;
- EV-090–EV-094;
- EV-145–EV-147;
- EV-192–EV-194 for C1 exact equipped-source obligation/acquisition behavior;
- EV-206 for exact-source physical-repair semantics and controlled no-op coverage;
- EV-207 for Dual repair independence plus Fist/crossbow source-scope closure.

Asset-level routing: `ANIMATION_INDEX.md`.

### D. Triggered-list rearm / multi-contact

Search terms: `ClearTriggeredList`, `EntitiesVisited`, multi-target, same-target, duplicate dispatch, occurrence budget, OFF

Evidence anchors: EV-033, EV-106–EV-116, EV-143–EV-144.

Historical fixture details: `ANIMATION_CATALOG.md` §12 and archived v0.10–v0.18 fixture logs.

### E. Marker execution lifetime / bookkeeping

Search terms: `MarkerExecutionBudget`, `RetireMarkerOwnedSource`, `StatePosition`, interruption, stale budget, exact-set switching, `m_pfInstrCallback`, `sAICombatMoveInstr`, `FullStop`, `SetState`, state stack, break block, `RunScriptFunction`, `m_pArguments`

Evidence anchors:

- EV-066–EV-075;
- EV-131–EV-133;
- EV-167;
- EV-181–EV-196;
- EV-206–EV-207 for controlled terminal repair and marked-source regression.

Architecture: `COLLISION_LIFECYCLE_PLAN.md` §§3–9.

**Marker reimplementation/review rule:** before consolidating or optimizing the marker core, read this evidence set and `COLLISION_LIFECYCLE_PLAN.md` §9. Native CombatMove/state-stack/outer-ScriptFunction lifetime may eventually replace some custom execution inference, but only if the stronger boundary generalizes safely. Preserve StatePosition advancement, occurrence/replay protection, OFF/exact-set switching, repeated-contact rearm and interruption-retirement guarantees meanwhile.

### F. Native collision cleanup lifecycle

Search terms: `Item_Attack`, `Item_Equipped`, `SetCollisionGroup`, cleanup, block skip, StartRecover, PlayMotion, StopMotion, ProcessScript, StateTime, StatePosition, `m_pfInstrCallback`, `FullStop`, `SetState`, `RunScriptFunction`, `m_StateStack`, `m_pArguments`, `FinalizeAfterAISetState`, `LivenessEstablished`, `REPAIRED_TO_ITEM_EQUIPPED`

Evidence anchors: EV-151–EV-207.

Exact native RVAs/stacks: `COLLISION_CLEANUP_CALLSITE_MAP.md`.  
Current architecture/test: `COLLISION_LIFECYCLE_PLAN.md`; `COLLISION_TEST_PLAN.md`; current integration responsibility in `SESSION_ENTRYPOINT.md`.

### G. Animation semantics and naming

Search terms: `gEUseType`, `gEAction`, `gEPhase`, `gEPose`, `HitDirection`, destination pose, R/L, overlay, CombatMove distance

Evidence anchors: EV-036–EV-065.  
Main routing: `ANIMATION_INDEX.md`.

### H. Compatibility / hook ownership

Search terms: `NewBalance`, `Script_AttackCollision`, same-function hook, load order, ResetOnUntouch, backup DLL

Evidence anchors: EV-035, EV-045, EV-148–EV-150, EV-173.  
Practical source route: `SOURCE_HOOK_GUIDE.md` §8–§11.

---

## 3. Lifecycle Evidence Quick Map

| Step | Evidence | Answer obtained |
|---|---|---|
| B1 | EV-158 | `PlayMotion(type 0)` is immediate actual-motion replacement evidence, but clean replacement precedes native cleanup |
| B2 | EV-159, EV-171 | later original callbacks are downstream/repeating, not one-shot completion |
| B3 | EV-160 | `sAICombatMoveStartRecover` is too early and can be bypassed |
| B3b | EV-161–EV-162 | missing Recover asset is not root cause; defect reproduces beyond Staff/Whirl |
| B4/B4b | EV-163–EV-165 | ordinary cleanup is action-specific; tested reaction interruption has separate route |
| B5 | EV-166 | ordinary/reaction successful paths reached adjacent but distinct Game parents |
| B5 static follow-up | EV-169–EV-171 | parents are generic script runners; common higher dispatcher is generic `ProcessScript()` |
| B6 environment | EV-173 | backup `Script_*.dll.bak` in live scripts can participate in runtime hooks |
| B6 clean control | EV-174–EV-176 | clean completion exposes `sAICombatMoveInstr -> ProcessScript()` at StartRecover |
| B6 reaction comparison | EV-177–EV-179 | reaction cleanup and actual Stumble/KnockDown successors are captured in reaction Script_Game/ScriptAdmin context |
| B6 bad replacement | EV-180–EV-181 | armed Whirl can disappear to Ambient without StartRecover/cleanup and stale group 7 can persist through idle into a later attack |
| B6 design result | EV-172, EV-180 | replacement-triggered deferred-`ProcessScript()` candidate is superseded/rejected in its present form |
| B7 static reconstruction | EV-182–EV-184 | CombatMove persists as an SPU instruction; clean Whirl cleanup is a later break-block continuation; reaction control can FullStop the instruction |
| B7 runtime | EV-185–EV-186 | bad Whirl and legitimate reaction both explicitly FullStop CombatMove, but only reaction receives later cleanup ownership |
| B7b exact caller | EV-187–EV-188 | bad Whirl uses exact held-Use2 FullStop `+0x633F1`; tested Normal/Quick reaction uses distinct FullStop `+0x2D0F2` |
| B7b causal reconstruction | EV-189 | bad FullStop is immediately followed by SetState, which clears the SPU state stack/break block and discards the suspended Whirl cleanup continuation |
| B8 generality | EV-190 | the same held-Use2 stale class reproduces in tested Quick configurations beyond full Whirl |
| B9 finalization ordering | EV-191 | bad abandonment reaches AISetState before cleanup; clean/reaction paths fulfill cleanup first; AISetState is a gated checkpoint only |
| C1 shadow core | EV-192–EV-193 | per-source consequence-based obligation model passes the tested main matrix, including inherited stale `7 -> 7` |
| C1 acquisition gap | EV-194 | GetUp can arm before CombatMove, so CombatMove is too late as universal execution acquisition |
| C1 outer static lifetime | EV-195 | ScriptFunction frame persists across false return/asynchronous work and has explicit SPU/actor context |
| C1-O1 outer identity probe | EV-196 | same live frame bridges GetUp offense→CombatMove→cleanup; raw pointers can be reused only after retirement |
| C1-O2 first integration / isolation | EV-199 | direct dispatch capture crashed in registered-ScriptFunction paths; pure-pass-through baseline isolated it |
| directly relevant hook hardening | EV-199–EV-201 | AISetState, AIFullStop and SetCollisionGroup were converted in bounded transport-only steps |
| SetCollisionGroup crash reassessment | EV-201–EV-202 | exact crashed-DLL disassembly localized failure to post-AISetState finalizer observation, not SetCollisionGroup transport |
| finalizer liveness correction + rerun | EV-203 | corrected finalizer and SetCollisionGroup transport pass tested extended stability; liveness-negative outstanding branch remains unexercised |
| C1-O2-P1 lightweight bridge | EV-204 | tiny synchronous RunScriptFunction scope exposes the missing pre-Combat acquisition context without eager generic dispatch work |
| C1-O2-P2 ownership integration | EV-205 | early exact offense acquires the monotonic generation and matching CombatMove consumes the native bridge before wrapper return; tested model closes |
| C1-R1 controlled physical repair | EV-206 | exact live/equipped outstanding weapon source is repaired `7 -> 5`; clean/reaction/pre-activation/GetUp/GetUpParade controls remain non-mutating |
| C1-R1-E source/marker/broad closure | EV-207 | Dual exact-source independence, marked terminal repair, broad player/NPC stability, Fist/body separation and crossbow negative behavior close the controlled R1 gate |

---

## 4. Processed / Active Lifecycle Log Routing

Processed logs move to `research/archive/` as their conclusions become canonical. Raw logs may remain temporarily in `research/raw/` while a comparison set or current causal gate remains active.

Key Step-B comparative artifacts include:

- `research/raw/2026-08-28_b6b_player_2h_normal_clean_completion_startrecover_stack.log`
- `research/raw/2026-08-28_b6c3_b6d_player_2h_clean_skip_and_reaction_successor_stacks.log`
- `research/raw/2026-08-28_b7_player_combatmove_fullstop_clean_reaction_blockskip.log`
- `research/raw/2026-08-28_b7b_player_aifullstop_exact_caller_clean_reaction_blockskip.log`
- `research/raw/2026-08-28_b8_player_dual_quick_state_stack_abandonment.log`
- `research/raw/2026-08-28_b9_player_aisetstate_cleanup_ordering.log`

Current C1 evidence includes:

- `research/raw/2026-08-28_c1_shadow_core_lifecycle_matrix.log`
- `research/archive/2026-08-28_c1_shadow_core_lifecycle_matrix_connector_extract.txt`
- `research/raw/2026-08-29_c1o1_outer_scriptfunction_identity_probe.log`
- `research/archive/2026-08-29_c1o1_outer_scriptfunction_identity_probe_connector_extract.txt`
- `research/archive/2026-08-30_c1o2p2_broader_combat_interruption_stability.log`
- `research/archive/2026-08-30_c1r1_isolated_load.log`
- `research/archive/2026-08-30_c1r1c_player_2h_targeted_physical_repair.log`
- `research/archive/2026-08-30_c1r1d_player_2h_reaction_getup_noop_controls.log`
- `research/raw/2026-08-30_c1r1e_dual_source_specific_physical_repair.log`
- `research/raw/2026-08-30_c1r1e_marked_staff_terminal_repair_regression.log`
- `research/raw/2026-08-30_c1r1e_broad_player_npc_negative_stability.log`
- `research/derived/2026-08-30_c1r1e_broad_player_npc_negative_stability_large_log/`
- `research/raw/2026-08-30_c1r1e_unarmed_crossbow_negative_closure.log`

Open archived/raw logs only when verifying ledger wording, reinterpreting a result, or extracting a new fact.

`research/raw/` is reserved for active/unprocessed or still-comparative evidence and current diagnostic output. A raw artifact may remain there while it is still serving the current causal comparison even after its main result has been canonically recorded.

---

## 5. Historical Runtime Log Naming

Processed older logs under `research/archive/` may follow historical names such as:

```text
YYYY-MM-DD_framecollision_vX.Y_actor_family_experiment.log
```

Current gate-based naming is owned by `PROJECT_PIPELINE.md`; do not rename historical evidence merely to normalize older styles.

Prefer the EV entry first because it records the qualification and engineering consequence already extracted from the raw session.

---

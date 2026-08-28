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
| Quick marker ownership / StatePosition | EV-066–EV-075 | EV-182–EV-189 for native lifecycle/bookkeeping context |
| Dual native source map | EV-090–EV-094 | `ANIMATION_CATALOG.md` §6–§7 |
| multi-target, OFF, duplicate/replay/occurrence guard | EV-106–EV-116 | archived v0.10–v0.13 fixture logs |
| marker execution retirement after interruption | EV-131–EV-133 | EV-167, EV-182–EV-189 for later lifecycle interpretation |
| final RIGHT/LEFT/BOTH/OFF vocabulary | EV-143–EV-144 | `DESIGN.md` §6 / `ANIMATION_RULES.md` §20 |
| Whirl callback/action/source separation | EV-145–EV-147 | `ANIMATION_RULES.md` §8.1 / cleanup map |
| NewBalance / AttackCollision Whirl compatibility | EV-035, EV-148–EV-150 | `SOURCE_HOOK_GUIDE.md` same-function caution |
| Staff full-Whirl cleanup anomaly | EV-151–EV-153 | EV-155–EV-156, EV-180–EV-189 for resolved tested Whirl lifecycle |
| Recover asset vs lifecycle cleanup | EV-154, EV-160–EV-162 | `COLLISION_LIFECYCLE_PLAN.md` constraints |
| marked block-timeout failure | EV-155 | native control EV-156 |
| native stale collision / running damage | EV-156, EV-181, EV-187 | B6-D/B7b raw for persistence through idle/movement |
| v0.20 PrimaryFirst lifetime sampling | EV-157 | B1 EV-158 |
| PlayMotion actual replacement timing | EV-158 | B6 EV-174–EV-180 |
| later original callback is not completion | EV-159 | EV-171 static callback ordering |
| StartRecover not post-cleanup / not guaranteed | EV-160 | EV-176 / EV-180 clean-vs-bad comparison |
| no-Recover and Dual Quick broad defect | EV-161–EV-162 | B3b raw; current cross-family gate |
| action-specific native cleanup matrix | EV-163 | `COLLISION_CLEANUP_CALLSITE_MAP.md` §2 |
| same serialized asset, different runtime action | EV-164 | cleanup map §3 |
| legitimate reaction interruption cleanup/successor | EV-165, EV-177–EV-179, EV-184, EV-186, EV-188 | cleanup map / lifecycle plan §3 |
| B5 parent stack | EV-166 | EV-169–EV-170 static identification |
| marker bookkeeping vs physical cleanup | EV-167, EV-182–EV-189 | `COLLISION_LIFECYCLE_PLAN.md` §9 |
| future marker-core simplification / native execution boundary | EV-066–EV-075, EV-131–EV-133, EV-167, EV-182–EV-189 | **Read `COLLISION_LIFECYCLE_PLAN.md` §9 before changing marker bookkeeping** |
| ordinary / reaction / bad-skip ending model | EV-168, EV-179–EV-189 | lifecycle plan §§3–8 |
| `RunScriptState` / `RunScriptFunction` identification | EV-169 | cleanup map §§5–6 |
| `ProcessScript()` common generic dispatcher | EV-170, EV-176 | EV-180 for failed universal replacement-time validation |
| callback processing after main script dispatch | EV-171 | cleanup map §8 |
| deferred pending-finalization/post-script candidate | EV-172 | **superseded by EV-180**; lifecycle plan §7 |
| live `scripts` backup-DLL contamination | EV-173 | `SOURCE_HOOK_GUIDE.md` build/runtime reference |
| B6 clean path disappearance + ProcessScript stack | EV-174–EV-176 | `COLLISION_TEST_PLAN.md` B6-B |
| B6 reaction successor context | EV-177–EV-179 | `COLLISION_TEST_PLAN.md` B6-C |
| B6 bad skip context / no useful ScriptAdmin replacement stack | EV-180 | B6-D raw |
| long-lived stale group 7 / later inherited 7->7 | EV-181 | `COLLISION_LIFECYCLE_PLAN.md` §§1–2 |
| persisted CombatMove instruction / FullStop semantics | EV-182, EV-185–EV-189 | lifecycle plan §§3–4 / source guide CombatMove symbols |
| full-Whirl break-block continuation to native cleanup | EV-183, EV-189 | lifecycle plan §§3–4 |
| reaction-side FullStop before separate cleanup ownership | EV-184, EV-186, EV-188 | lifecycle plan §3 |
| bad full-Whirl exact held-Use2 FullStop caller | EV-187 | `SOURCE_HOOK_GUIDE.md` §5 |
| exact tested Normal/Quick reaction FullStop caller | EV-188 | `SOURCE_HOOK_GUIDE.md` §5 |
| `FullStop -> SetState` state-stack abandonment causal chain | EV-189 | `COLLISION_LIFECYCLE_PLAN.md` §§3–4 |
| current attack-lifecycle / cross-family generality question | EV-162, EV-182–EV-189 | `COLLISION_LIFECYCLE_PLAN.md` §8 / `BETWEEN_CHATS.md` |

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

Search terms: `RIGHT`, `LEFT`, `BOTH`, `Fist`, `Torch`, `Dual`, `Pierce`, `Power`, `QuickAttackR`, `QuickAttackL`

Evidence anchors:

- EV-029–EV-032;
- EV-047–EV-059;
- EV-080–EV-085;
- EV-090–EV-094;
- EV-145–EV-147.

Asset-level routing: `ANIMATION_INDEX.md`.

### D. Triggered-list rearm / multi-contact

Search terms: `ClearTriggeredList`, `EntitiesVisited`, multi-target, same-target, duplicate dispatch, occurrence budget, OFF

Evidence anchors: EV-033, EV-106–EV-116, EV-143–EV-144.

Historical fixture details: `ANIMATION_CATALOG.md` §12 and archived v0.10–v0.18 fixture logs.

### E. Marker execution lifetime / bookkeeping

Search terms: `MarkerExecutionBudget`, `RetireMarkerOwnedSource`, `StatePosition`, interruption, stale budget, exact-set switching, `m_pfInstrCallback`, `sAICombatMoveInstr`, `FullStop`, `SetState`, state stack, break block

Evidence anchors:

- EV-066–EV-075;
- EV-131–EV-133;
- EV-167;
- EV-181–EV-189.

Architecture: `COLLISION_LIFECYCLE_PLAN.md` §§3–9.

**Marker reimplementation/review rule:** before consolidating or optimizing the marker core, read this evidence set and `COLLISION_LIFECYCLE_PLAN.md` §9. Native CombatMove/state-stack lifetime may eventually replace some custom execution inference, but only if the stronger boundary generalizes safely. Preserve StatePosition advancement, occurrence/replay protection, OFF/exact-set switching, repeated-contact rearm and interruption-retirement guarantees meanwhile.

### F. Native collision cleanup lifecycle

Search terms: `Item_Attack`, `Item_Equipped`, `SetCollisionGroup`, cleanup, block skip, StartRecover, PlayMotion, StopMotion, ProcessScript, StateTime, StatePosition, `m_pfInstrCallback`, `FullStop`, `SetState`

Evidence anchors: EV-151–EV-189.

Exact native RVAs/stacks: `COLLISION_CLEANUP_CALLSITE_MAP.md`.  
Current architecture/test: `COLLISION_LIFECYCLE_PLAN.md`; `COLLISION_TEST_PLAN.md`.

### G. Animation semantics and naming

Search terms: `gEUseType`, `gEAction`, `gEPhase`, `gEPose`, `HitDirection`, destination pose, R/L, overlay, CombatMove distance

Evidence anchors: EV-036–EV-065.  
Main routing: `ANIMATION_INDEX.md`.

### H. Compatibility / hook ownership

Search terms: `NewBalance`, `Script_AttackCollision`, same-function hook, load order, ResetOnUntouch, backup DLL

Evidence anchors: EV-035, EV-045, EV-148–EV-150, EV-173.  
Practical source route: `SOURCE_HOOK_GUIDE.md` §8–§11.

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
| Current gate | EV-162, EV-187–EV-189 | test whether known Dual Quick stale failure uses the same state-stack-abandonment class; existing B7b diagnostic is sufficient for first check |

---

## 4. Processed / Active Step-B Log Routing

Processed logs move to `research/archive/` as their conclusions become canonical. Raw logs may remain temporarily in `research/raw/` while the lifecycle comparison set is active.

Key current comparative artifacts:

- `research/raw/2026-08-28_b6b_player_2h_normal_clean_completion_startrecover_stack.log`
- `research/raw/2026-08-28_b6c3_b6d_player_2h_clean_skip_and_reaction_successor_stacks.log`
- `research/raw/2026-08-28_b7_player_combatmove_fullstop_clean_reaction_blockskip.log`
- `research/raw/2026-08-28_b7b_player_aifullstop_exact_caller_clean_reaction_blockskip.log`

Open archived/raw logs only when verifying ledger wording, reinterpreting a result, or extracting a new fact.

`research/raw/` is reserved for active/unprocessed or still-comparative evidence and current diagnostic output.

---

## 5. Historical Runtime Log Naming

Processed logs under `research/archive/` follow names such as:

```text
YYYY-MM-DD_framecollision_vX.Y_actor_family_experiment.log
```

Useful search tokens include `staff_whirl`, `block_timeout`, `native_block_skip`, `dual_normal`, `quick`, `fist`, `multi_target`, `duplicate_guard`, `occurrence_guard`, `final_markers`.

Prefer the EV entry first because it records the qualification and engineering consequence already extracted from the raw session.

---

## 6. Evidence Maintenance Rule

When a new durable result is established:

1. add/modify the canonical EV entry with explicit status/provenance;
2. preserve the raw/source artifact when needed for verification;
3. update this index only if the result creates a new retrieval route or materially changes an existing topic range;
4. update current design/state documents only when their responsibility actually changes.

Do not copy the full experiment narrative into every design/reference document.

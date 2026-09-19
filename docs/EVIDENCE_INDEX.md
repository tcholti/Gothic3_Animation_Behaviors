# Gothic 3 Animation Behaviors — Evidence Index

**Status:** Cold/reference routing index  
**Updated:** 2026-09-18

## Purpose

Route a technical question to the smallest relevant evidence range without loading the complete evidence ledgers.

Canonical evidence remains one global monotonic namespace split only for storage/retrieval:

```text
EVIDENCE_LEDGER.md                  EV-001–EV-157
EVIDENCE_LEDGER_STEP_B.md           EV-158–EV-198
EVIDENCE_LEDGER_199_ONWARD.md       EV-199–EV-231
EVIDENCE_LEDGER_232_ONWARD.md       EV-232–EV-249
EVIDENCE_LEDGER_250_ONWARD.md       EV-250–EV-264
EVIDENCE_LEDGER_265_ONWARD.md       EV-265–EV-273
EVIDENCE_LEDGER_274_ONWARD.md       EV-274–EV-279
EVIDENCE_LEDGER_280_ONWARD.md       EV-280–EV-282
EVIDENCE_LEDGER_283_ONWARD.md       EV-283–EV-285
EVIDENCE_LEDGER_286_ONWARD.md       EV-286–EV-290
EVIDENCE_LEDGER_291_ONWARD.md       EV-291 onward
```

The ledger splits are storage-only; numbering remains one global monotonic namespace.

This index does not restate or change evidence status. Open the exact EV entry when wording, qualification, provenance, build scope or engineering consequence matters.

Processed September 2–16 runtime artifacts are moved unchanged from `research/raw/` to `research/archive/` after evidence closure. Historical rows written before an archive move may still spell the former raw intake path; `EVIDENCE_PATH_MIGRATIONS.md` records those path migrations where needed. Raw/archive logs are verification/provenance, not routine reading. For large logs, prefer the committed `research/derived/` package for routine retrieval and return to the archived source only for an exact unresolved fact.

Current project responsibility is never owned by this historical index. Use `SESSION_ENTRYPOINT.md` / `BETWEEN_CHATS.md` for current state.

---

## 1. Fast Topic Routing

| Topic / search intent | Start with | Then broaden if needed |
|---|---|---|
| CombatMove fields, native phase/speed baselines | EV-001–EV-011 | `SOURCE_HOOK_GUIDE.md` speed / CombatMove symbols |
| Raise prepend proof / engine animation resolution | EV-006–EV-007 | `DESIGN.md` Raise architecture |
| frame effects / marker channel / frame-effect layout | EV-012–EV-018 | source guide Frame effects |
| ordinary natural weapon reset / marker timing | EV-019–EV-023 | lifecycle evidence for abnormal endings |
| Staff + NPC actor-general marker proof | EV-024–EV-028 | Quick evidence EV-066+; R1-E stability EV-207 |
| raw-8 Fist/body contact — production + cross-family marker route | EV-029–EV-032, EV-080–EV-085, EV-207, EV-211, EV-221–EV-240, EV-247, EV-250–EV-251, EV-257, EV-263, EV-297, EV-304–EV-305, EV-307 | `DESIGN.md` raw-8 Fist architecture; EV-304 native fallback; EV-305 human two-FIST rearm; EV-307 Sabretooth actor-general two-FIST confirmation |
| PhysicalFist/raw55 factual source + permanent validation | EV-245–EV-246, EV-262–EV-298 | §3K below; family causal closure through EV-294; focused sentinels EV-295–EV-297; aggregate permanent-acceptance closure EV-298 |
| standalone collision regression campaign | EV-299 onward | `COLLISION_TEST_PLAN.md` §8; Golem/setup coverage through EV-306 plus Sabretooth raw8 corroboration EV-307 |
| repeated-hit rearm / triggered lists | EV-033, EV-106–EV-116, EV-266–EV-273, EV-283–EV-292, EV-305, EV-307 | equipped exact-set/replay evidence; raw8 same-C1 FIST rearm human EV-305 + Sabretooth EV-307; raw55 family/timing-specific rearm remains separate |
| Hero family / poses / UseType / R-L semantics | EV-036–EV-065 | `ANIMATION_INDEX.md` |
| Quick marker ownership / StatePosition | EV-066–EV-075, EV-263–EV-273 | EV-182–EV-196 lifecycle context; EV-264–EV-273 raw55 Quick ownership/separability/activation/rearm/pre-state closure |
| Dual native source map / source-explicit marker review | EV-090–EV-094 | EV-207, EV-211, EV-214 |
| multi-target, OFF, duplicate/replay/occurrence guard | EV-106–EV-116 | EV-131–EV-144; archived fixture logs |
| historical marker occurrence-budget leak | EV-131–EV-133 | EV-167; EV-213–EV-214 for generation replacement/closure |
| final equipped RIGHT/LEFT/BOTH/OFF vocabulary | EV-143–EV-144 | `DESIGN.md` / `ANIMATION_RULES.md` |
| Whirl callback/action/source separation | EV-145–EV-147 | `ANIMATION_RULES.md` / cleanup map |
| Hack callback identity | EV-216 | `SOURCE_HOOK_GUIDE.md`; actual runtime adapter behavior is EV-244 |
| Power marker/source/lifecycle expansion | EV-241 | `research/derived/2026-09-03_power_pierce_marker_validation_checkpoint.md` |
| Pierce marker/source/lifecycle expansion + bounded NB/Jackydima control | EV-242 | same Power/Pierce checkpoint; compatibility qualification in exact EV |
| SimpleWhirl physical source / target semantics / StatePosition closure | EV-217–EV-220, EV-243 | `research/derived/2026-09-04_simplewhirl_stateposition_and_target_semantics_closure.md` |
| Hack equipped routing/source/marker validation | EV-244 | EV-216 for callback identity only; archived September 4 Hack evidence |
| New Balance / AttackCollision Whirl compatibility | EV-035, EV-148–EV-150 | source-guide same-function caution |
| Staff full-Whirl cleanup anomaly | EV-151–EV-156 | EV-180–EV-191, EV-206–EV-207 |
| Recover asset vs lifecycle cleanup | EV-154, EV-160–EV-162 | `COLLISION_LIFECYCLE_PLAN.md` |
| native stale collision / running consequence | EV-156, EV-181, EV-187, EV-190, EV-197–EV-198, EV-202–EV-203, EV-206 | stale-collision reconstruction below |
| PlayMotion / PrimaryFirst replacement timing | EV-157–EV-160 | EV-174–EV-180 |
| action-specific native cleanup matrix | EV-163–EV-166 | `COLLISION_CLEANUP_CALLSITE_MAP.md` |
| marker bookkeeping vs physical cleanup | EV-167 | EV-182–EV-196, EV-206–EV-207, EV-213–EV-214 |
| generic script parents / ProcessScript | EV-169–EV-171, EV-195 | cleanup map / source guide |
| rejected deferred replacement finalization | EV-172, EV-180 | historical only |
| live `scripts` backup-DLL contamination | EV-173, EV-218 | POP-03 / source-guide cautions |
| CombatMove FullStop / SetState continuation loss | EV-182–EV-191 | `COLLISION_LIFECYCLE_PLAN.md` |
| Alternative-AI held-Use2 trigger | EV-187, EV-197 | test trigger only, not production classifier |
| C1 shadow execution/source obligation | EV-192–EV-193 | lifecycle plan |
| GetUp pre-CombatMove acquisition gap | EV-194 | EV-195–EV-196 |
| outer ScriptFunction lifetime / pointer reuse | EV-195–EV-196 | lifecycle plan execution identity |
| hook transport stabilization / recursion-safe explicit-this | EV-199–EV-203 | `SOURCE_HOOK_GUIDE.md` |
| C1-O2 pre-Combat bridge closure | EV-204–EV-205 | lifecycle plan |
| C1-R1 physical repair closure | EV-206–EV-207 | exact-source `7 -> 5`; controlled validation closed |
| second-pass source/build separation | EV-208 | `DESIGN.md` modular architecture / release architecture |
| second-pass CORE diagnostic sufficiency | EV-209–EV-211 | `COLLISION_TEST_PLAN.md` |
| first behavior-only architecture smoke | EV-212 | release architecture |
| Gate 4 C1-generation marker bookkeeping | EV-213 | `COLLISION_LIFECYCLE_PLAN.md` / `DESIGN.md` marker identity |
| literal EV-131 same-motion interruption/restart closure | EV-214 | restored fixture / Gate-4 route |
| final diagnostics-free architecture verification | EV-215 | new architecture verification complete |
| Fist callback suppression / ClearTriggeredList removal | EV-232–EV-233 | final raw-8 Fist architecture |
| Fist native timing threshold | EV-234 | `SOURCE_HOOK_GUIDE.md` generic human-proven static path |
| Fist exact one-shot timing permission | EV-235 | production FIST timing transport |
| authored FIST_OFF removal | EV-236 | final FIST-only author vocabulary |
| Fist Normal/Power interruption safety | EV-237 | generation-scoped timing permission |
| late-first-marker native leak / initial-close requirement | EV-238 | pre-production frame-12 controls |
| production Fist implementation / build smoke | EV-239 | commits `dba34c6...` / `17491d53...` |
| final human Normal + Power FIST acceptance | EV-240 | archived acceptance log / commit `5de195c6...` |
| transformed/native Sabretooth raw8 compatibility + Quick control | EV-247, EV-250–EV-251, EV-263 | use EV-263 for the accepted-marker StatePosition interpretation boundary |

---

## 2. Native Stale Melee Collision — Causal Reconstruction Route

Use this ordered route only when stale collision/lifecycle safety is again the active engineering responsibility. Do not reread all raw logs.

1. Trigger/reproduction context: EV-187, EV-197–EV-198.
2. Physical stale consequence/persistence: EV-156, EV-162, EV-181, EV-193, EV-202–EV-203, EV-206.
3. Ordinary attack continuation/cleanup: EV-163, EV-182–EV-183.
4. Legitimate reaction interruption + separate cleanup ownership: EV-165, EV-184, EV-186, EV-188, EV-191, EV-203, EV-206, EV-210.
5. Bad held-Use2 abandonment chain: EV-185, EV-187, EV-189–EV-191.
6. Cross-family generality: EV-162, EV-190.
7. Rejected Recover/StartRecover/replacement/callback explanations: EV-154, EV-159–EV-162, EV-168, EV-174–EV-181.
8. C1 execution/source-obligation model: EV-192–EV-196.
9. Hook/finalizer stabilization: EV-199–EV-203.
10. Outer pre-Combat acquisition closure: EV-204–EV-205.
11. Controlled native-equivalent physical repair: EV-206–EV-207.
12. Post-rewrite regression/architecture verification: EV-208–EV-215.

Current architecture: `COLLISION_LIFECYCLE_PLAN.md`.  
Current validation posture: `COLLISION_TEST_PLAN.md`.

---

## 3. Evidence by Engineering Domain

### A. Raise and playback speed

Search terms: `AniSpeedScale`, `GetAnimationSpeedModifier`, `PREPEND_BREAK_BLOCK`, `Raise`, `RecoverSpeed`.

Evidence: EV-001–EV-011.  
Architecture: `DESIGN.md` Raise / Playback-Speed sections.

### B. Animation-authored frame effects

Search terms: `UpdateFrameEffects`, `StartEffect`, `eSFrameEffect`, marker frame, playback synchronization.

Evidence: EV-012–EV-023.  
Reference: `SOURCE_HOOK_GUIDE.md`; `ANIMATION_RULES.md`.

### C. Physical source selection and action-specific character-hit eligibility

Evidence anchors:

```text
EV-029–EV-032
EV-047–EV-059
EV-080–EV-085
EV-090–EV-094
EV-145–EV-147
EV-192–EV-194
EV-206–EV-207
EV-211
EV-214
EV-217–EV-290
```

Power, Pierce, SimpleWhirl and Hack equipped expansion conclusions are canonically closed in EV-241–EV-244. EV-216 remains Hack callback identity only. EV-245–EV-246 record the initial bounded raw55 survey that had not yet found a factual source. Later Troll/BlackTroll evidence reopened the question: EV-262 confirms factual raw55; EV-264–EV-294 close the four supported family causal routes including repeated-contact behavior; EV-295–EV-297 validate diagnostic/equipped, unmarked-native and raw8 coexistence sentinels; EV-298 closes focused permanent raw55 acceptance. EV-263 remains the focused historical raw8 Quick comparison boundary.

SimpleWhirl current distinction:

```text
G3AB exact-set markers
= physical equipped-source activation/rearm semantics

native SimpleWhirl character-hit eligibility
= substantially target-directed, but not strictly selected-target-only
```

EV-217 validates the physical marker/source layer. EV-219 rejects a strict selected-target-only model. EV-220 supports a SimpleWhirl-vs-Power action-specific character-hit difference under matched motion content. EV-243 records the September 4 causal closure: StatePosition `2` did not make SimpleWhirl Power-like, the temporary change was reverted, and final StatePosition `1` regression preserved healthy marker behavior.

Closed checkpoint:
`research/derived/2026-09-04_simplewhirl_stateposition_and_target_semantics_closure.md`

Archived raw controls:

```text
research/archive/2026-09-04_simplewhirl_stateposition2_causal_probe.log
research/archive/2026-09-04_simplewhirl_native_stateposition1_final_regression.log
```

### D. Triggered-list rearm / multi-contact / exact-set markers

Evidence:

```text
EV-033
EV-106–EV-116
EV-131–EV-144
EV-213–EV-214
EV-217
EV-220
EV-241–EV-244
EV-266–EV-273
EV-276
EV-279
EV-282
EV-283–EV-290
```

`ClearTriggeredList()` is established for equipped repeated-contact semantics, but raw55 family behavior is not uniform. Raw-8 Fist explicitly does not require it in final production architecture; see EV-233. Raw55 Quick is a proven special case: EV-266 shows delayed authored group opening alone can remain contact-insufficient, EV-267 restores Quick damage with one exact triggered-list clear, and EV-268–EV-273 close the timing/pre-state behavior and repeated-contact path.

The earlier first-contact checkpoints for true Power EV-276, Normal EV-279 and Sprint EV-282 each show damage after authored raw55 opening with `ClearTriggeredList=0` in those tested native timing states. Do not generalize that result to every marker timing. EV-286–EV-287 later prove that an earlier Normal marker at SP0 can physically open raw55 yet fail to create early contact until one exact marker-owned `ClearTriggeredList()` is performed. EV-288 rejects the later native `7 -> 7` setter as the second-contact owner. EV-289 proves the player visit bookkeeping is naturally cleared during the native SP0 -> 1 callback transition before marker2, and EV-290 identifies the exact public native ALL `eCTrigger_PS::ClearTriggeredList()` call from `Script_Game.dll + 0x386C6` that performs that reset. EV-290 identifies the operation; EV-291 proves its causal necessity and EV-292 closes Normal authored marker2 replacement-clear ownership.

### E. Marker execution lifetime / bookkeeping

Mandatory causal route before changing marker execution identity:

```text
EV-066–EV-075
EV-108–EV-117
EV-128–EV-133
EV-143–EV-147
EV-155–EV-156
EV-167
EV-182–EV-196
EV-206–EV-207
EV-209–EV-214
COLLISION_LIFECYCLE_PLAN.md
DESIGN.md marker identity
```

Accepted result:

```text
C1 monotonic generation = durable marker occurrence/dedupe execution identity
```

Fist timing permission also uses this factual generation identity; EV-237 confirms interruption-safe retirement in tested Normal/Power cases.

### F. Native collision cleanup lifecycle

Evidence: EV-151–EV-215 plus equipped expansion cleanup evidence EV-217, EV-220 and EV-241–EV-244, raw55 authored-FIST cleanup evidence EV-266–EV-282, and the Normal repeated-contact/reset-source evidence EV-283–EV-290.  
Exact native RVAs/stacks: `COLLISION_CLEANUP_CALLSITE_MAP.md`.  
Architecture: `COLLISION_LIFECYCLE_PLAN.md`.

Raw-8 Fist is not an equipped-source cleanup client; it creates no weapon C1 physical repair obligation. Raw55 authored opening creates a real C1 offense obligation when the source actually becomes group7. Quick, true Power, Normal and Sprint all have positive native exact RIGHT `7 -> 5` cleanup evidence after their proven authored-opening paths. The EV-286–EV-290 Normal probes also preserve native exact RIGHT `7 -> 5` cleanup while isolating contact bookkeeping. Suppressed `5 -> 7` requests that never physically open do not fabricate an offense obligation; Sprint EV-281 provides a particularly direct control.

### G. Animation semantics and naming

Evidence: EV-036–EV-065, plus EV-245–EV-290 for the distinction between serialized `Fist`, factual raw source UseType, actual marker-mechanism support, factual engine family/action and timing/contact behavior.  
Main routing: `ANIMATION_INDEX.md`.

Sprint EV-280–EV-282 is an explicit caution: the PowerAttack-named motion can be factual Action9/Sprint and later become factual Action2/Power. Animation filename is not family authority.

### H. Compatibility / hook ownership

Evidence: EV-035, EV-045, EV-148–EV-150, EV-173, EV-218, plus the bounded Pierce-specific New Balance + Jackydima control in EV-242.  
Practical route: `SOURCE_HOOK_GUIDE.md`; deployment rule: POP-03.

Do not promote EV-242 into blanket compatibility certification; the mature subsystem compatibility gate remains separate.

### I. Architecture rewrite / diagnostics-free product separation

```text
EV-208 source/build separation
EV-209–EV-211 CORE diagnostic sufficiency
EV-212 behavior-only smoke
EV-213 Gate-4 generation bookkeeping
EV-214 literal historical regression closure
EV-215 final behavior-only functional/release-purity smoke
```

Authorities: `DESIGN.md`, `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`, `COLLISION_LIFECYCLE_PLAN.md`, `COLLISION_TEST_PLAN.md`.

### J. Production raw-8 Fist/body-damage mechanism

Use this route instead of reconstructing N1–N6 chronology from raw logs:

```text
EV-221–EV-231  historical baseline/path/latch/N3 progression
EV-232         weapon-style callback suppression unnecessary
EV-233         Fist ClearTriggeredList unnecessary
EV-234         native timing threshold identified
EV-235         exact one-shot timing comparison permission causal
EV-236         authored FIST_OFF unnecessary
EV-237         Normal/Power interruption and multiple-opportunity safety
EV-238         late-first-marker native leak -> initial ownership close
EV-239         production implementation + compile/load smoke
EV-240         final human 3x Normal + 3x Power frame-12 acceptance
EV-247         transformed Sabretooth Normal/Power marker PASS at that checkpoint
EV-250–EV-251  broader native/transformed raw8 family controls including Quick/Sprint
EV-257         Orc raw8 native control
EV-263         focused healthy raw8 Quick ownership-direction control + StatePosition interpretation boundary
```

Current architecture for a supported/proven raw8 family:

```text
unmarked raw-8 Fist -> native

marked execution
    -> once per factual C1 generation close SPU+0x164 to 1

accepted FIST
    -> latch 0
    -> below threshold: one exact Game+0x16E180 timing permission
    -> at/above threshold: native timing unchanged

native Gothic
    -> target/contact/damage
    -> successful opportunity self-closes latch to 1
```

No authored FIST_OFF, no Fist triggered-list clear, no Fist-specific weapon callback suppression, no custom damage and no raw55 generalization. Marker applicability is not species- or animation-family-name-gated. Later native/transformed controls extend the shared raw8 mechanism without changing its ownership model.

Human final acceptance artifact:
`research/archive/2026-09-07_fist_production_frame12_normal_power_acceptance.log`.

Raw8 Quick comparison provenance used during the raw55 investigation is now archived:
`research/archive/2026.09.12_sabertooth_marked_quick.log`.

### K. PhysicalFist/raw55 complete causal route

Initial discovery boundary:

```text
EV-245 transformed Wolf/Sabretooth proxy rejected: both factual raw8
EV-246 bounded native-NPC survey: no factual raw55 observed in that survey
EV-262 Troll/BlackTroll factual TrollFist/raw55 confirmed; whole marked-callback suppression is not a uniform solution
EV-263 healthy raw8 Quick control retained as mechanism boundary
```

Quick closure:

```text
EV-264 same original Quick callback owns native StatePosition progression + premature RIGHT raw55 opening
EV-265 selective exact RIGHT early 5 -> 7 suppression preserves Quick StatePosition progression
EV-266 authored FIST opens exact RIGHT raw55 and native cleanup succeeds, but activation alone does not restore Quick damage
EV-267 one exact post-opening triggered-list clear restores Quick damage on contact
EV-268 timing controls prove frame-1 FIST can arrive pre-StatePosition
EV-269–EV-273 close the pre-state/repeat-contact Quick path and its bounded behavior
```

True Power first-contact closure:

```text
EV-274 compound native callback ownership
EV-275 selective exact RIGHT early-group suppression preserves native progression
EV-276 authored FIST exact RIGHT activation with ClearTriggeredList=0 restores native damage and native cleanup
```

Normal first-contact closure:

```text
EV-277 compound native callback ownership
EV-278 selective exact RIGHT early-group suppression preserves native progression
EV-279 authored FIST exact RIGHT activation with ClearTriggeredList=0 restores native damage and native cleanup at the tested SP1 marker timing
```

Sprint first-contact closure:

```text
EV-280 factual Action9/Sprint compound ownership inside existing _AI_PowerAttack transport; whole-callback suppression rejected
EV-281 selective exact RIGHT Action9 early-group suppression preserves native StatePosition 0 -> 1 and holds RIGHT group5 through FIST
EV-282 authored FIST at factual Action9/SP1 opens exact RIGHT raw55 5 -> 7 with ClearTriggeredList=0; native damage + native 7 -> 5 cleanup repeat across C1=16/57/81
```

Cross-family repeated-FIST checkpoint:

```text
EV-283 two authored FIST occurrences are transported in Quick, Power, Normal and Sprint fixtures; repeated-contact behavior is not uniform across families
EV-284–EV-285 narrow the Normal repeated-FIST question and prepare the pre-state route
```

Normal repeated-contact causal route:

```text
EV-286 frame-1/SP0 FIST is accepted and physically opens exact RIGHT raw55 5 -> 7; with ClearTriggeredList=0 no early first-swing damage occurs
EV-287 one exact marker-owned ClearTriggeredList after verified SP0 opening creates first damage before native SP0 -> 1; second same-C1 damage also occurs later without marker2 intervention
EV-288 suppressing the native exact RIGHT 7 -> 7 setter preserves SP0 -> 1 and both damages, rejecting that setter as the second-contact owner
EV-289 read-only trigger state proves PC_Hero is visited after hit1, then removed during the same native SP0 -> 1 callback transition before marker2
EV-290 exact public eCTrigger_PS::ClearTriggeredList() ALL from Script_Game.dll +0x386C6 is the operation that empties the visited arrays; hit2 later re-inserts PC_Hero
```

Current engineering status:

```text
factual raw55 source                  = CONFIRMED for Troll/BlackTroll TrollFist
raw55 Quick                           = CLOSED/PASS through EV-273
raw55 Normal                          = CLOSED/PASS repeated-contact route through EV-292
raw55 true Power                      = CLOSED/PASS repeated-contact route through EV-293
raw55 Sprint-origin                   = CLOSED/PASS repeated-contact route through EV-294
permanent raw55 implementation        = SOURCE/CORE BEHAVIOR ACCEPTED
diagnostic ownership correction       = RUNTIME PASS — EV-295
equipped authored-marker sentinel     = PASS inside EV-295 control
unmarked raw55 native fallback        = PASS — EV-296
raw8 FIST sentinel                    = PASS — EV-297
focused permanent raw55 acceptance   = CLOSED/PASS — EV-298
```

The source-reviewed current diagnostic suppresses exactly once the EV-290 native ALL clear from `Engine + 0x7DDA0`, caller `Script_Game.dll + 0x386C6`, only when the factual Normal actor/C1/current RIGHT raw55/contact gates match and PC_Hero is still visited after hit1. Marker1 remains unchanged, marker2 remains observational, the EV-288 `7 -> 7` suppression remains, and native cleanup is not modified.

Current probe authority:
`COLLISION_RAW55_NORMAL_NATIVE_TRIGGER_CLEAR_SUPPRESSION_PROBE.md`.

Current diagnostic implementation:
`2839c8c271fa240b81ce5ccd203c34058870a5bb` — source review PASS; build not yet attempted at the EV-290 maintenance boundary.

Preferred EV-290 runtime retrieval:
`research/derived/2026.09.16_troll_raw55_normal_native_trigger_clear_observation_large_log/`.

Canonical full source provenance:
`research/archive/2026.09.16_troll_raw55_normal_native_trigger_clear_observation.log`.

Do not substitute raw8 semantics for raw55, do not species-gate production policy, and do not infer exact whole-limb/body damage geometry from the `TrollFist` name or current OnDamage logger.

---

## 4. Closed Architecture Boundary

```text
C1-R1 lifecycle repair                      CLOSED — EV-206–EV-207
second-pass source/build separation         CLOSED — EV-208
CORE diagnostic sufficiency                 CLOSED — EV-209–EV-211
behavior-only product smoke                 CLOSED — EV-212
C1-generation marker bookkeeping            CLOSED — EV-213
literal EV-131 regression                   CLOSED — EV-214
final behavior-only architecture smoke      CLOSED — EV-215
Power equipped marker expansion             CLOSED/PASS — EV-241
Pierce equipped marker expansion            CLOSED/PASS — EV-242
SimpleWhirl current semantic checkpoint     CLOSED for current scope — EV-217–EV-220, EV-243
Hack equipped marker/source validation      CLOSED/PASS for tested 2H/Staff scope — EV-216, EV-244
human/raw8 Fist production mechanism        CLOSED/PASS; broadened controls through EV-263
initial PhysicalFist/raw55 bounded survey   CLOSED at EV-245–EV-246; REOPENED by factual EV-262 evidence
raw55 factual source boundary               CONFIRMED — EV-262
raw55 Quick causal mechanism                CLOSED/PASS through EV-273
raw55 true Power first-contact mechanism    CLOSED/PASS through EV-276
raw55 Normal first-contact mechanism        CLOSED/PASS through EV-279
raw55 Sprint first-contact mechanism        CLOSED/PASS through EV-282
raw55 two-FIST transport checkpoint         CONFIRMED — EV-283
Normal SP0 opening/first-contact rearm       CLOSED/PASS — EV-286–EV-287
Normal native 7 -> 7 second-rearm hypothesis REJECTED — EV-288
Normal between-contact bookkeeping reset    CONFIRMED — EV-289
Normal exact native ALL-clear reset source  IDENTIFIED — EV-290
Normal repeated-contact causal closure       CLOSED/PASS — EV-291–EV-292
true Power repeated-FIST closure             CLOSED/PASS — EV-293
Sprint-origin repeated-FIST closure          CLOSED/PASS — EV-294
permanent raw55 diagnostic control           PASS — EV-295
equipped authored-marker sentinel            PASS — EV-295
unmarked raw55 native-fallback sentinel       PASS — EV-296
raw8 FIST coexistence sentinel                 PASS — EV-297
focused permanent raw55 acceptance            CLOSED/PASS — EV-298
```

```text
NEW COLLISION ARCHITECTURE VERIFICATION = COMPLETE
RAW8 FIST SHARED MECHANISM = CLOSED/PASS FOR THE EVIDENCE-BACKED FAMILIES/CONTROLS
EQUIPPED POWER / PIERCE / SIMPLEWHIRL / HACK EXPANSION CHECKPOINTS = CANONICALLY PROMOTED
RAW55 FACTUAL SOURCE = CONFIRMED FOR TROLL/BLACKTROLL
RAW55 QUICK = CLOSED/PASS WITH PROVEN QUICK-SPECIFIC REARM/PRE-STATE BEHAVIOR
RAW55 QUICK / NORMAL / TRUE POWER / SPRINT-ORIGIN REPEATED-CONTACT ROUTES = CLOSED/PASS THROUGH EV-294
PERMANENT RAW55 IMPLEMENTATION + FOUR-FAMILY CORE ACCEPTANCE = PASS
POST-AUDIT DIAGNOSTIC CORRECTIONS CONTROL = PASS — EV-295
EQUIPPED AUTHORED-MARKER SENTINEL = PASS — EV-295
UNMARKED RAW55 NATIVE FALLBACK = PASS — EV-296
RAW8 FIST COEXISTENCE SENTINEL = PASS — EV-297
FOCUSED PERMANENT RAW55 ACCEPTANCE = CLOSED/PASS — EV-298
```

Do not route current work back into raw55 causal probing or focused acceptance without concrete contradictory evidence. EV-298 closes that responsibility; current work proceeds to standalone collision regression.

---

## 5. Future-Responsibility Cross-Routes

### PhysicalFist/raw55 repeated-contact closure route

Current causal route is:

```text
EV-245–EV-246  initial bounded survey / raw8-vs-raw55 distinction
EV-262–EV-263  factual raw55 discovery + raw8 comparison boundary
EV-264–EV-273  complete Quick causal closure
EV-274–EV-276  true Power first-contact closure
EV-277–EV-290  Normal first-contact + repeated-contact narrowing
EV-291–EV-292  Normal native-clear necessity + authored marker2 replacement-clear closure
EV-293         true Power repeated-FIST closure
EV-294         Sprint-origin repeated-FIST closure across Action9 -> Action2
EV-295         permanent post-audit diagnostic-corrections control + equipped-marker sentinel
EV-296         unmarked raw55 native-fallback sentinel
EV-297         raw8 FIST coexistence sentinel across native/transformed ownership
EV-298         aggregate focused permanent raw55 acceptance closure
COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md
COLLISION_TEST_PLAN.md
SESSION_ENTRYPOINT.md / BETWEEN_CHATS.md
```

The family-specific causal route is closed through EV-294. EV-295 supplies the post-audit diagnostic/equipped sentinel, EV-296 closes unmarked raw55 fallback, EV-297 closes raw8 coexistence, and EV-298 closes focused permanent raw55 acceptance. Do not route current work back into causal raw55 probing without contradictory evidence; current execution details remain owned by `SESSION_ENTRYPOINT.md` / `BETWEEN_CHATS.md`.

### Standalone collision regression campaign

Focused permanent raw55 acceptance is closed at EV-298. The prepared standalone campaign is now active under `COLLISION_TEST_PLAN.md` §8.

Current canonical regression sequence:

```text
Phase 1 — Golem player equipped/setup matrix
  EV-299  1H PASS
  EV-300  1H + torch PASS
  EV-301  dual 1H PASS
  EV-302  2H PASS
  EV-303  Staff PASS
  EV-304  human raw8 Fist single-marker + unmarked Power-P1 fallback PASS
  EV-305  human raw8 Fist double-marker repeated-contact PASS
  EV-306  1H + shield PASS
  -> remaining prepared Golem setups, if any

Supplemental raw8 actor-general control:
  EV-307  Sabretooth double-FIST repeated-contact PASS

Phase 2 — Orc 2H / Staff / raw8 Fist
Phase 3 — other weapon-using actors
Phase 4 — non-weapon creatures in chunks
Phase 5 — 2H vs Axe separation-mod compatibility
Phase 6 — 1H vs Rapier separation-mod compatibility
Phase 7 — stress regression
```

The Golem batches provide positive C1-R1 bad-skip repair coverage in 1H, 1H+torch, dual-1H, 2H and 1H+shield; Staff supplies the complementary cleanup-completes-before-repair control. EV-306 additionally proves the tracked LEFT shield remains non-offensive while only the exact stale RIGHT sword is repaired. EV-304/EV-305 add human raw8 fallback/two-marker coverage, and EV-307 independently confirms the same raw8 double-FIST mechanism on Sabretooth.

This campaign is regression confirmation, not source/lifecycle redesign. Current execution details belong to `SESSION_ENTRYPOINT.md` / `BETWEEN_CHATS.md`.

### AttackContinuationProtection

```text
EV-182–EV-191
EV-197–EV-198
COLLISION_TEST_PLAN.md
COLLISION_LIFECYCLE_PLAN.md
```

Prevention remains separate from lifecycle repair and from the raw8/raw55 marker mechanisms.

### New Balance / Jackydima compatibility

```text
EV-035
EV-148–EV-150
EV-242 bounded Pierce-specific control
SOURCE_HOOK_GUIDE.md same-function caution
DESIGN.md compatibility section
```

Compatibility is required on the mature collision behavior at the architecture-defined gate and again on later assembled production behavior. EV-242 does not replace that gate.

### Production collision migration / Raise / speed

Start from current architecture authorities and only the exact proof route required by the subsystem being migrated. Do not reconstruct collision chronology wholesale.

---

## Core Retrieval Rule

> **Use the index to find the smallest authority/evidence route, then open the exact EV or authority. Do not treat historical route text as current project state, and do not load whole ledgers merely to regain context.**

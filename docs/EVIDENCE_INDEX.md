# Gothic 3 Animation Behaviors — Evidence Index

**Status:** Cold/reference routing index  
**Updated:** 2026-09-08

## Purpose

Route a technical question to the smallest relevant evidence range without loading the complete evidence ledgers.

Canonical evidence remains one global monotonic namespace split only for storage/retrieval:

```text
EVIDENCE_LEDGER.md                  EV-001–EV-157
EVIDENCE_LEDGER_STEP_B.md           EV-158–EV-198
EVIDENCE_LEDGER_199_ONWARD.md       EV-199–EV-231
EVIDENCE_LEDGER_232_ONWARD.md       EV-232 onward
```

The EV-232 split is storage-only at the stable human-Fist checkpoint; numbering remains one global monotonic namespace.

This index does not restate or change evidence status. Open the exact EV entry when wording, qualification, provenance, build scope or engineering consequence matters.

Processed September 2–8 runtime artifacts are moved unchanged from `research/raw/` to `research/archive/` after evidence closure. Historical rows written before an archive move may still spell the former raw intake path; `EVIDENCE_PATH_MIGRATIONS.md` records those path migrations where needed. Raw/archive logs are verification/provenance, not routine reading.

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
| human Fist/body contact — final production route | EV-029–EV-032, EV-080–EV-085, EV-207, EV-211, EV-221–EV-240 | `DESIGN.md` human-Fist architecture; `SOURCE_HOOK_GUIDE.md` human-Fist path |
| PhysicalFist/raw55 bounded survey / creature native source classification | EV-245–EV-246 | `COLLISION_TEST_PLAN.md` §4; `SOURCE_HOOK_GUIDE.md` §5 |
| repeated-hit rearm / triggered lists | EV-033, EV-106–EV-116 | equipped marker exact-set/replay evidence |
| Hero family / poses / UseType / R-L semantics | EV-036–EV-065 | `ANIMATION_INDEX.md` |
| Quick marker ownership / StatePosition | EV-066–EV-075 | EV-182–EV-196 for lifecycle context |
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
| Fist callback suppression / ClearTriggeredList removal | EV-232–EV-233 | final human-Fist architecture |
| Fist native timing threshold | EV-234 | `SOURCE_HOOK_GUIDE.md` generic human-Fist static path |
| Fist exact one-shot timing permission | EV-235 | production FIST timing transport |
| authored FIST_OFF removal | EV-236 | final FIST-only author vocabulary |
| Fist Normal/Power interruption safety | EV-237 | generation-scoped timing permission |
| late-first-marker native leak / initial-close requirement | EV-238 | pre-production frame-12 controls |
| production Fist implementation / build smoke | EV-239 | commits `dba34c6...` / `17491d53...` |
| final production Normal + Power FIST acceptance | EV-240 | archived acceptance log / commit `5de195c6...` |

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
EV-217–EV-246
```

Power, Pierce, SimpleWhirl and Hack equipped expansion conclusions are canonically closed in EV-241–EV-244. EV-216 remains Hack callback identity only. EV-245–EV-246 close the current bounded raw55 discovery as unobserved/deferred while recording that several non-human body attacks factually use raw8.

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
```

`ClearTriggeredList()` here belongs to equipped repeated-contact semantics. Human Fist explicitly does not use it in final production architecture; see EV-233.

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

Evidence: EV-151–EV-215 plus equipped expansion cleanup evidence EV-217, EV-220 and EV-241–EV-244.  
Exact native RVAs/stacks: `COLLISION_CLEANUP_CALLSITE_MAP.md`.  
Architecture: `COLLISION_LIFECYCLE_PLAN.md`.

Human Fist is not an equipped-source cleanup client; it creates no weapon C1 physical repair obligation.

### G. Animation semantics and naming

Evidence: EV-036–EV-065, plus EV-245–EV-246 for the runtime distinction between serialized `Fist` and factual raw source UseType.  
Main routing: `ANIMATION_INDEX.md`.

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

### J. Production human Fist/body-damage mechanism

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
EV-240         final 3x Normal + 3x Power frame-12 acceptance
```

Final architecture:

```text
unmarked human raw-8 Fist -> native

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

No authored FIST_OFF, no Fist triggered-list clear, no Fist-specific weapon callback suppression, no custom damage, no raw55/monster authoring generalization.

Final acceptance artifact:
`research/archive/2026-09-07_fist_production_frame12_normal_power_acceptance.log`.

### K. PhysicalFist/raw55 bounded survey

```text
EV-245 transformed Wolf/Sabertooth proxy rejected: both factual raw8
EV-246 native-NPC source survey: no factual raw55 observed
```

Observed native body attackers Boar/Wolf/Sabertooth/Bloodfly/Golem/Snapper/Minecrawler/Bison resolved `Fist` / raw8 / group0 and damaged through `Game +0x16E348`. Weapon controls resolved 2H/1H/Axe factual UseTypes; the Dragon capture recorded Cast/raw15 fireball only and left Dragon physical attack inconclusive.

Engineering status:

```text
raw55 = unobserved in bounded survey
support = deferred / unsupported for current scope
reopen = only on concrete factual runtime UseType 55 evidence
```

Do not infer complete human timing/latch equivalence for creature raw8 and do not extend `G3AB_COL_FIST` authoring to monsters from this survey.

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
human raw-8 Fist production                 CLOSED/PASS — EV-221–EV-240
PhysicalFist/raw55 bounded discovery        CLOSED/DEFERRED — EV-245–EV-246
```

```text
NEW COLLISION ARCHITECTURE VERIFICATION = COMPLETE
CURRENT HUMAN FIST NORMAL + POWER PRODUCTION SCOPE = COMPLETE
EQUIPPED POWER / PIERCE / SIMPLEWHIRL / HACK EXPANSION CHECKPOINTS = CANONICALLY PROMOTED
RAW55 BOUNDED DISCOVERY = COMPLETE / UNOBSERVED / DEFERRED
```

Do not route fresh work into N4/N5/N6, another human raw-8 Fist causal probe, or another raw55 search absent contradicting factual evidence.

---

## 5. Future-Responsibility Cross-Routes

### PhysicalFist/raw55 deferred boundary

Current bounded evidence is EV-245–EV-246. It found no factual raw55 source and therefore justifies no raw55 implementation.

If future runtime evidence establishes a relevant source `UseType == 55`, reopen from:

```text
EV-245–EV-246     current bounded raw55 disposition
ANIMATION_RULES.md raw UseType -> serialized Fist distinction
SOURCE_HOOK_GUIDE.md PhysicalFist/raw55 status
DESIGN.md + COLLISION_TEST_PLAN.md deferred boundary
```

Then classify the actual observed native mechanism before changing production behavior. Do not use human raw8 or creature raw8 as a semantic substitute for factual raw55.

### Final native mixed collision regression

Start from:

```text
DESIGN.md collision architecture
COLLISION_TEST_PLAN.md current closure gate
EV-206–EV-215 lifecycle/architecture proof
EV-216–EV-220 equipped expansion history
EV-221–EV-240 final human-Fist production proof
EV-241–EV-244 canonical equipped expansion closures
EV-245–EV-246 raw55 deferred boundary / native-source survey
```

This is the next immediate collision responsibility. It is regression confirmation, not source/lifecycle/Fist redesign.

### AttackContinuationProtection

```text
EV-182–EV-191
EV-197–EV-198
COLLISION_TEST_PLAN.md
COLLISION_LIFECYCLE_PLAN.md
```

Prevention remains separate from lifecycle repair and from the closed Fist production mechanism.

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

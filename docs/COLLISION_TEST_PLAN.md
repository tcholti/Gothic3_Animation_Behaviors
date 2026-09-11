# Collision Validation Plan

**Status:** Current collision validation authority — architecture foundation COMPLETE through EV-215; equipped marker families CLOSED/PASS through EV-244; raw55 bounded discovery CLOSED/DEFERRED through EV-246; raw8 Normal/Power/Quick CLOSED/PASS through EV-249; architecture/diagnostic refactor sentinel CLOSED/PASS through EV-250; raw8 Sprint FIST production support CLOSED/PASS through EV-251; remaining broad matrix resumes at native equipped-NPC controls  
**Updated:** 2026-09-11

## Purpose

Define the standing validation rules and remaining collision-validation gates. This file owns **how future collision behavior is validated**, not implementation architecture, current transient state, or experiment chronology.

Current state: `SESSION_ENTRYPOINT.md`.  
Transient continuation: `BETWEEN_CHATS.md`.  
Current redesign authority: `COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`.  
Overall architecture/order: `DESIGN.md`.  
Lifecycle architecture: `COLLISION_LIFECYCLE_PLAN.md`.  
Diagnostic architecture: `COLLISION_LOGGER_PLAN.md`.  
Exact proof: `EVIDENCE_INDEX.md` -> canonical evidence ledgers.

---

## 1. Standing Validation Rules

- Do not reopen closed C1-R1, Gate-4, equipped-family, raw8 Normal/Power/Quick/Sprint, or bounded raw55 conclusions without concrete contradictory evidence.
- Native cleanup gets first opportunity.
- Equipped RIGHT / LEFT / BOTH / OFF control the desired **physical equipped-source set**; they do not prove uniform native target/contact/effect eligibility across action families.
- Raw-8 `FIST` is a separate native body-damage opportunity mechanism, not an equipped source/window.
- Do not gate marker applicability by actor species or animation-family name when factual source/mechanism evidence supports a broader scope.
- Native action identity outranks animation filename. A PowerAttack-named motion does not make `gEAction_SprintAttack` a PowerAttack.
- The C1 monotonic generation remains the durable execution identity for marker occurrence/dedupe and equipped-source obligations.
- Terminal repair may mutate only an exact owned outstanding equipped source after native cleanup opportunity and current-equipped liveness are established.
- Keep diagnostics independent from behavior correctness; release behavior must not compile research diagnostics.
- Never deploy diagnostic and behavior-only collision twins together.
- Freeze one falsifiable question and minimum positive/negative controls before each new runtime investigation.
- Preserve/publish/interpret/promote/archive runtime evidence under POP-05/POP-06 before advancing to a new causal question.
- Do not grow a matrix after a gate closes unless a new responsibility or contradiction requires it.
- Large regression/compatibility runs should use compact CORE diagnostics. Unknown/unsupported/anomalous events must automatically retain richer classification detail.

Authoritative research products remain:

```text
Script_FrameCollisionTest
= instrumented diagnostic twin

Script_FrameCollisionBehaviorTest
= diagnostics-free behavior twin
```

---

## 2. Closed Foundation

```text
C1-R1 exact-source lifecycle safety          CLOSED — EV-206–EV-207
source/build separation                      CLOSED/PASS — EV-208
CORE diagnostic sufficiency foundation       CLOSED/PASS — EV-209–EV-211
behavior-only smoke                          CLOSED/PASS — EV-212
C1-generation marker bookkeeping             CLOSED/PASS — EV-213
literal EV-131 regression                    CLOSED/PASS — EV-214
final behavior-only architecture smoke       CLOSED/PASS — EV-215
```

Accepted terminal equipped-source repair remains exactly:

```text
outstanding exact source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual group == Item_Attack(7)
-> SetCollisionGroup(Item_Equipped) exactly once
-> no ClearTriggeredList()
-> verify Item_Equipped(5)
```

Retained evidence limits do not reopen the gate:

```text
no positive outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED runtime case
no positive NPC destructive-abandonment / physical-repair case claimed
```

---

## 3. Closed Supported Collision Scope

Current proven equipped-family state:

```text
Normal / Quick / full Whirl foundation       CLOSED/PASS
PowerAttack                                  CLOSED/PASS — EV-241
PierceAttack                                 CLOSED/PASS — EV-242
SimpleWhirl                                  CLOSED/PASS — EV-217–EV-220, EV-243
HackAttack tested 2H/Staff scope             CLOSED/PASS — EV-216, EV-244
```

Important family qualifications:

- Power physical source control is closed; native Power contact/target sensitivity remains native behavior.
- Pierce physical marker-source timing is separate from native Pierce target/reaction semantics.
- SimpleWhirl StatePosition `2` was tested and rejected as sufficient normalization. Final StatePosition remains `1`; native character-hit eligibility remains action-specific.
- Hack callback identity is EV-216; actual 2H/Staff routing/source/marker validation is EV-244.

### Production raw-8 Fist

Current supported/proven raw8 FIST family scope for the tested fixtures is:

```text
Normal + Power + Quick + Sprint
```

Evidence progression:

```text
human Normal/Power production                   EV-221–EV-240
transformed Sabretooth Normal/Power             EV-247
native Sabretooth + Quick mechanism proof       EV-248
bounded Quick extension + two-direction PASS    EV-249
Sprint transport/source/mechanism classification + production validation
                                                 EV-250–EV-251
```

Validated contract for a supported/proven raw-8 Fist family:

```text
unmarked raw-8 Fist
-> completely native

marked raw-8 Fist execution
-> initial SPU+0x164 close to 1 once per factual C1 generation

accepted FIST
-> latch 1 -> 0
-> if real motion-0 time is below native threshold,
   arm one exact bounded Game+0x16E180 timing permission
-> otherwise use native timing directly

native Gothic path
-> owns target/contact/damage
-> successful opportunity self-closes latch to 1
```

Sprint qualification:

```text
factual gEAction_SprintAttack / Action 9
-> first-class AttackFamily_Sprint
-> existing OnAI_PowerAttack physical transport
-> actor routine Action 9 is semantic identity
-> FIST/raw8 only in current proven scope
-> marker-owned StatePosition 1
-> equipped Sprint RIGHT/LEFT/BOTH/OFF remains unsupported
```

Production exclusions remain:

```text
NO authored FIST_OFF
NO Fist ClearTriggeredList
NO Fist-specific weapon callback suppression
NO equipped Item_Attack/Item_Equipped window for Fist
NO weapon C1 physical-cleanup obligation for Fist
NO direct/custom Fist damage
NO global animation-clock mutation
NO raw55 generalization
NO species/name-specific marker rule
NO unproven attack-family extension merely because source is Fist
NO Sprint -> Power semantic alias
NO Sprint equipped-marker support without factual equipped Sprint evidence
```

---

## 4. PhysicalFist/raw55 Bounded Discovery — CLOSED/DEFERRED

The bounded discovery completed through EV-245–EV-246 without observing raw55.

Observed:

```text
Hero Wolf transformation       -> factual Fist / raw8
Hero Sabretooth transformation -> factual Fist / raw8
Boar/Wolf/Sabretooth/Bloodfly/Golem/Snapper/Minecrawler/Bison
  -> factual Fist / raw8 / group0 / Game+0x16E348 body-damage route
Demon  -> 2H/raw3
Goblin -> 1H/raw2
Ogre   -> Axe/raw52
Dragon capture -> Cast/raw15 fireball; physical attack inconclusive
raw55 -> not observed
```

Raw55 remains unsupported/unobserved, not globally disproven. Do not create raw55 behavior or new discovery probes unless factual `UseType == 55` appears.

---

## 5. Architecture/Diagnostic Refactor Gate — CLOSED/PASS

The parity-preserving architecture/diagnostic refactor and compact equivalence sentinel are complete through EV-250.

Closed requirements included:

```text
raw8 FIST:
  Sabretooth Normal + Quick + Power

equipped marker:
  ordinary marked weapon attack

marker lifecycle:
  established multi-marker / OFF / rearm fixture

C1 safety:
  established destructive bad-skip -> exact terminal repair
```

The sentinel preserved accepted marker semantics, factual source identities and physical transitions, raw8 latch/timing/native-damage contract, C1 generation/cleanup/repair behavior, and compact CORE sufficiency with no new invariant/repair divergence.

Do not reopen Stage A/B merely for routine variation.

---

## 6. SprintAttack Discovery / Support Gate — CLOSED/PASS

Sprint was discovered as factual `gEAction_SprintAttack = 9` with a PowerAttack-named motion and raw8 Fist source. Transport research established that tested Sprint enters through the existing physical `OnAI_PowerAttack` hook while actor routine Action 9 is already factual at callback entry; SPU action 2 and the animation filename are transport/motion facts, not Sprint semantic identity.

Production implementation uses first-class `AttackFamily_Sprint`, the existing Power callback transport, the proven raw8 FIST mechanism, and marker-owned StatePosition `1`.

Focused EV-251 validation repeatedly confirmed:

```text
Action=9 Family=SPRINT Phase=1
Raw8Fist=Fist Raw8UseType=8
InitialClose=0->1
Marker=FIST Result=ACCEPTED
StatePosition=1
Latch=1->0 LatchConfirmed=1
OwnershipMatched=1
bounded early timing permission armed/used when required
clean C1 finalization with no equipped obligation
```

Whole-log targeted checks found no `REJECTED_UNSUPPORTED_HIT`, no `LIFECYCLE_ISSUE`, no surviving temporary `SPRINT_TRANSPORT` records, and clean unload.

Current evidence-backed Sprint limit remains:

```text
raw8 FIST supported
native Sabretooth fixture positively validated
equipped Sprint RIGHT/LEFT/BOTH/OFF unevidenced and unsupported
AI/distance selection rule intentionally unresolved because it is not needed for marker behavior
```

EV-251 did not independently add a positive `ONDAMAGE` sample with native Sabretooth Sprint as attacker; it added no contradictory damage-path evidence. Native target/contact/damage ownership remains outside the authored marker mechanism.

Focused Sprint closure permits the broad compatibility matrix to resume.

---

## 7. Diagnostic Requirements for Remaining Large Tests

Default large tests should use compact CORE diagnostics under `COLLISION_LOGGER_PLAN.md`.

CORE governing rule:

```text
known healthy path -> compact
unknown/unsupported family or source -> detailed
unexpected rejection/failure -> detailed
C1 anomaly/repair/divergence -> detailed
DEEP explicitly enabled -> full research detail
```

Unknown-family records must retain enough to classify numeric/resolved action, phase, StatePosition, current motion, marker, source/UseType/group, side association, rejection reason, and damage correlation when relevant.

This rule is intended to discover any new unplanned family/source during larger tests without returning to huge research-era logs for every known execution.

---

## 8. Pre-Regression Cross-Actor / Family Compatibility Gates

Architecture sentinel and focused Sprint disposition are now closed. Resume here.

### 8.1 Native equipped-NPC marker controls — NEXT

Separate logs:

```text
Goblin -> factual 1H / raw2
Demon  -> factual 2H / raw3
Ogre   -> factual Axe / raw52
```

Purpose:

```text
confirm equipped marker ownership follows factual equipped source/action semantics
for NPC attackers as well as already-proven player-side cases
```

Keep each actor as separate evidence so failures remain attributable.

### 8.2 Additional prepared native/modded actor-family controls

Use one actor/family per log where practical. Grow only when a concrete compatibility question remains open.

### 8.3 Separated 2H vs Axe mod compatibility

With the mod that separates 2H from Axe animation families:

- mark at least one new 2H attack;
- mark at least one new Axe attack;
- include marker-free/native controls where practical.

The question is whether collision follows factual source/action semantics after the animation-family split.

### 8.4 Separated 1H vs Rapier mod compatibility

With the mod that separates ordinary 1H from Rapiers:

- mark at least one ordinary 1H attack;
- mark at least one Rapier attack;
- include marker-free/native controls where practical.

Again, factual source/action semantics outrank animation-family naming.

Only after these bounded gates are dispositioned should final mixed regression begin.

---

## 9. Final Native Mixed / Stress Collision Regression

Run one native/no-third-party mixed regression over the supported scope after the pre-regression gates close.

Protect at minimum:

```text
equipped RIGHT / LEFT / BOTH / OFF exact-set behavior
repeated-contact ClearTriggeredList semantics
Power / Pierce / SimpleWhirl / Hack behavior
supported Sprint behavior
C1 generation-scoped occurrence/dedupe
C1-R1 exact-source terminal repair
supported raw8 FIST behavior
unmarked/native fallback
one-live-collision-twin deployment invariant
compact CORE anomaly discovery
```

There is no accepted raw55 behavior to add unless future factual evidence reopens it.

Do not broaden this gate into Raise, speed, target acquisition, or a new source redesign.

---

## 10. AttackContinuationProtection — Separate Later Responsibility

`AttackContinuationProtection` remains separate from `CollisionLifecycleGuard`/C1-R1.

Intended boundary:

```text
AttackContinuationProtection.cpp
= prevent the known destructive bad-skip route when its factual native timeout/decision becomes due during a real attack

CollisionLifecycleGuard / C1-R1
= exact-source fail-safe if collision cleanup is nevertheless lost
```

New Balance compatibility is a hard constraint. If New Balance prevents the relevant native destructive condition, our module should naturally remain inactive.

Do not begin with an independent timer, polling loop, permanent watchdog, unconditional attack-state override, or resurrection after teardown.

Before implementation prove:

1. exact timeout/decision path leading to destructive FullStop/state replacement;
2. whether the destructive consequence has legitimate responsibility while a real attack CombatMove is active;
3. whether preventing/defering only that consequence lets the attack finish normally;
4. outside-attack timeout remains native;
5. legitimate reaction/interruption remains native;
6. New Balance-covered attacks naturally produce no intervention;
7. C1-R1 remains independent underlying fail-safe.

Minimum validation: known bad-skip case, outside-attack control, legitimate reaction control, and New Balance-enabled controls where the route is already prevented.

---

## 11. Compatibility Gates

### Compatibility Gate 1 — mature collision research assembly

After AttackContinuationProtection and combined regression, validate:

```text
New Balance
+ relevant Jackydima collision DLLs, including Script_AttackCollision where applicable
```

Do not assume arbitrary same-function hook chaining or load-order safety.

EV-242 is Pierce-specific compatibility evidence only.

### Compatibility Gate 2 — final Script_G3AnimationBehaviors

After collision migration plus Raise and redesigned speed/configuration work, repeat compatibility/regression on the final production assembly before stable/release promotion.

---

## 12. Evidence / Artifact Boundary

Runtime evidence lifecycle:

```text
freeze test + raw filename
-> User runs locally
-> publish unchanged raw artifact
-> Normal Chat interprets
-> promote reusable conclusion to canonical EV
-> explicitly disposition every artifact
-> archive when fully processed and no active comparison remains
-> only then advance
```

`research/raw/` is active intake. `research/archive/` is processed provenance. `research/derived/` is a retrieval aid, not canonical evidence.

EV-251 is the current raw8 Sprint closure checkpoint. Its processed validation raw is archived as `research/archive/2026.09.11_sprint_raw8_production_validation.log`.

---

## 13. Current Collision Validation Sequence

```text
production raw8 Normal/Power                         CLOSED/PASS
Power/Pierce/SimpleWhirl/Hack expansion              CLOSED/PASS for tested scope
PhysicalFist/raw55 bounded discovery                 CLOSED/DEFERRED
Sabretooth raw8 + Quick mechanism                    PASS/CLASSIFIED — EV-247–EV-248
raw8 Quick extension + two-direction validation      CLOSED/PASS — EV-249
architecture + diagnostic refactor/sentinel          CLOSED/PASS — EV-250
raw8 Sprint source/transport/production support      CLOSED/PASS — EV-251
-> native equipped-NPC markers: Goblin 1H / Demon 2H / Ogre Axe
-> additional native/modded family controls
-> separated 2H-vs-Axe compatibility
-> separated 1H-vs-Rapier compatibility
-> final native mixed/stress regression
-> separate AttackContinuationProtection
-> combined marker + lifecycle + continuation regression
-> mature New Balance + relevant Jackydima compatibility
-> production collision migration
-> diagnostics-free production integration validation
-> integrate Raise + Speed + Config
```

Exact immediate task remains owned by `SESSION_ENTRYPOINT.md` / `BETWEEN_CHATS.md`.
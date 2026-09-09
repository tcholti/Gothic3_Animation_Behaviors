# Collision Validation Plan

**Status:** Current collision validation authority — architecture foundation COMPLETE through EV-215; equipped marker families CLOSED/PASS through EV-244; raw55 bounded discovery CLOSED/DEFERRED through EV-246; raw8 Sabretooth/Quick progression CLOSED/PASS through EV-249; architecture/diagnostic refactor and SprintAttack investigation precede the remaining broad matrix  
**Updated:** 2026-09-09

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

- Do not reopen closed C1-R1, Gate-4, equipped-family, raw8 Normal/Power/Quick, or bounded raw55 conclusions without concrete contradictory evidence.
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
Normal + Power + Quick
```

Evidence progression:

```text
human Normal/Power production                   EV-221–EV-240
transformed Sabretooth Normal/Power             EV-247
native Sabretooth + Quick mechanism proof       EV-248
bounded Quick extension + two-direction PASS    EV-249
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

## 5. Architecture/Diagnostic Refactor Gate — NEXT BEFORE BROAD TESTING

The remaining broad compatibility tests must certify the architecture intended for production. Therefore no Goblin/Demon/Ogre or large mixed matrix is run before the planned parity-preserving architecture/diagnostic refactor.

Normal Chat first completes the audit/design defined in `COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`, then Work performs bounded mechanical changes.

The refactor itself must not intentionally change proven marker/source/lifecycle/raw8 semantics.

### 5.1 Required post-refactor equivalence sentinel

Use one compact test package covering the structural seams that may have moved:

```text
raw8 FIST:
  Sabretooth Normal + Quick + Power

equipped marker:
  one ordinary marked weapon attack

marker lifecycle:
  one established multi-marker / OFF / rearm fixture

C1 safety:
  one established destructive bad-skip -> exact terminal repair
```

Require:

- same accepted marker semantics as pre-refactor;
- same factual source identities and physical transitions;
- same raw8 latch/timing/native-damage contract;
- same C1 generation/cleanup/repair contract;
- no new invariant/repair divergence;
- compact CORE output remains sufficient to prove the result.

If this sentinel fails, stop and correct the refactor before Sprint research or any broad matrix.

---

## 6. SprintAttack Discovery / Support Gate — AFTER REFACTOR SENTINEL

EV-249's Sabretooth fight exposed repeated:

```text
Action: 9 = gEAction_SprintAttack
motion: ...PowerAttack_Hit...
source: Fist/raw8
G3AB_COL_FIST: REJECTED_UNSUPPORTED_HIT
```

Current framework has no `AttackFamily_Sprint` and no Sprint family adapter/hook plumbing.

The observed PowerAttack filename does not make this a PowerAttack. Sprint is a factual missing family.

### 6.1 Current evidence limit

Only native Sabretooth/raw8 Sprint is currently observed in this project. Earlier tests did not surface SprintAttack.

Do not assume:

```text
Sprint is Fist-only
Sprint is creature-only
Sprint is equivalent to Power
Sprint has equipped marker semantics
```

### 6.2 Sprint discovery questions

After the refactor sentinel passes, determine with compact CORE first and smallest missing DEEP probes only when required:

1. Which actors execute `gEAction_SprintAttack`?
2. Which factual source UseTypes occur?
3. What native callback/hook transport owns SprintAttack?
4. What StatePosition does Sprint use?
5. Does practical equipped Sprint traffic exist?
6. Does raw8 Sprint traverse the same relevant `SPU+0x164`, `Game+0x16E180`, `+0x16E1A3`, `+0x16E348` path?
7. If equipped Sprint is observed, does it use the established equipped source mechanism or require distinct semantics?

### 6.3 Implementation rule

If evidence supports implementation, prefer:

```text
first-class AttackFamily_Sprint
```

Do not implement a Sabretooth exception or Power filename alias.

Freeze the exact source/mechanism scope before Work edits code.

### 6.4 Focused Sprint validation

After any Sprint implementation, validate only the evidence-backed scope first. Require:

```text
factual action = SprintAttack
factual source identity matches intended adapter
marker accepted where supported
StatePosition/native callback semantics preserved
native target/contact/damage ownership preserved
unmarked/native fallback preserved
no cross-family regression
```

Only after focused Sprint closure resume the broad compatibility matrix.

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

This rule is specifically intended to discover Sprint or another unplanned family during larger tests without returning to huge research-era logs for every known execution.

---

## 8. Pre-Regression Cross-Actor / Family Compatibility Gates

Only after architecture sentinel and Sprint disposition:

### 8.1 Native equipped-NPC marker controls

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
supported Sprint behavior if implemented
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

EV-249 is the current raw8 Quick closure checkpoint. The Action-9/Sprint observation is now part of the durable redesign/validation plan and should be promoted/refined in canonical evidence maintenance when the Sprint investigation begins.

---

## 13. Current Collision Validation Sequence

```text
production raw8 Normal/Power                         CLOSED/PASS
Power/Pierce/SimpleWhirl/Hack expansion              CLOSED/PASS for tested scope
PhysicalFist/raw55 bounded discovery                 CLOSED/DEFERRED
Sabretooth raw8 + Quick mechanism                    PASS/CLASSIFIED — EV-247–EV-248
raw8 Quick extension + two-direction validation      CLOSED/PASS — EV-249
SprintAttack missing-family discovery                IDENTIFIED
-> complete architecture + diagnostic-volume audit
-> bounded parity-preserving refactor
-> compact post-refactor equivalence sentinel
-> Sprint source/transport/mechanism investigation
-> bounded Sprint implementation if evidence supports it
-> focused Sprint validation
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

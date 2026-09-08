# Collision Validation Plan

**Status:** Current collision validation authority — architecture verification COMPLETE through EV-215; equipped marker expansion and production human raw-8 Fist CLOSED/PASS through EV-244; bounded raw55 discovery CLOSED/DEFERRED through EV-246; transformed Sabretooth raw-8 Normal/Power marker compatibility PASS through EV-247  
**Updated:** 2026-09-08

## Purpose

Define the standing validation rules and the remaining collision-validation gates. This file owns **how future collision behavior is validated**, not implementation architecture, current transient state, or experiment chronology.

Current state: `SESSION_ENTRYPOINT.md`.  
Transient continuation: `BETWEEN_CHATS.md` when needed.  
Overall architecture/order: `DESIGN.md`.  
Lifecycle architecture: `COLLISION_LIFECYCLE_PLAN.md`.  
Diagnostic architecture: `COLLISION_LOGGER_PLAN.md`.  
Exact proof: `EVIDENCE_INDEX.md` -> canonical evidence ledgers.

---

## 1. Standing Validation Rules

- Do not reopen closed C1-R1, Gate-4, equipped-family, human raw-8 Normal/Power production, or bounded raw55 conclusions without concrete contradictory evidence.
- Native cleanup gets first opportunity.
- Equipped RIGHT / LEFT / BOTH / OFF control the desired **physical equipped-source set**; they do not prove uniform native target/contact/effect eligibility across action families.
- Raw-8 `FIST` is a separate native body-damage opportunity mechanism, not an equipped source/window.
- Do not gate marker applicability by actor species or animation-family name when factual source/mechanism evidence supports a broader scope.
- The C1 monotonic generation remains the durable execution identity for marker occurrence/dedupe and equipped-source obligations.
- Terminal repair may mutate only an exact owned outstanding equipped source after native cleanup opportunity and current-equipped liveness are established.
- Keep diagnostics independent from behavior correctness; release behavior must not compile research diagnostics.
- Never deploy the diagnostic and behavior-only collision twins together.
- Freeze one falsifiable question and the minimum positive/negative controls before each new runtime investigation.
- Preserve/publish/interpret/promote/archive runtime evidence under POP-05/POP-06 before advancing to a new causal question.
- Do not grow a matrix after a gate closes unless a new responsibility or contradiction requires it.

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
CORE diagnostic sufficiency                  CLOSED/PASS — EV-209–EV-211
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
- SimpleWhirl StatePosition `2` was tested and rejected as a sufficient explanation/normalization. Final StatePosition remains `1`; its native character-hit eligibility is substantially selected-target-centered but not strictly selected-target-only.
- Hack callback identity is EV-216; actual 2H/Staff routing/source/marker validation is EV-244.

No old SimpleWhirl StatePosition probe remains pending.

### Production raw-8 Fist

Human `gEUseType_Fist` / raw 8 Normal + Power production scope is CLOSED/PASS through EV-221–EV-240.

Validated production contract for a supported/proven raw-8 Fist attack family:

```text
unmarked raw-8 Fist
-> completely native

marked raw-8 Fist execution
-> initial SPU+0x164 close to 1 once per factual C1 generation

accepted FIST
-> latch 1 -> 0
-> if real motion-0 time is below the proven native threshold,
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
NO generalization to gEUseType_PhysicalFist / raw55
NO species/name-specific marker rule
NO unproven attack-family extension merely because the serialized token is Fist
```

EV-247 adds direct positive evidence that transformed Sabretooth Normal + Power can use the existing raw-8 FIST mechanism. The same log shows transformed Quick-left/right remains **explicitly unsupported** by current code: each FIST marker is `REJECTED_UNSUPPORTED_HIT`, while physical damage still occurs natively through `Game +0x16E348`.

This means the architecture is not human-animation-family-only, but native-NPC actor equivalence and raw-8 Quick mechanism equivalence remain separate open validation questions.

---

## 4. PhysicalFist/raw55 Bounded Discovery — CLOSED/DEFERRED

`gEUseType_PhysicalFist` / raw 55 is not covered merely because animation-name normalization maps it and raw-8 `Fist` to the serialized `Fist` token.

The bounded discovery stage completed through EV-245–EV-246 without observing raw55.

### What the survey established

```text
Hero Wolf transformation      -> factual Fist / raw 8
Hero Sabretooth transformation -> factual Fist / raw 8

native body attackers observed:
Boar / Wolf / Sabretooth / Bloodfly / Golem / Snapper / Minecrawler / Bison
-> factual Fist / raw 8 / group 0
-> damaging gCEntity::OnDamage caller Game +0x16E348

native equipped controls:
Demon  -> 2H / raw 3
Goblin -> 1H / raw 2
Ogre   -> Axe / raw 52
-> ordinary equipped/TouchDamage-style path including Game +0x69484 damage calls

Dragon capture:
Mis_Fireball / Cast raw 15 observed
physical Dragon attack not captured
```

No raw55 occurred in the twelve native-NPC logs. The transformed fixtures were themselves raw8, so they were invalid as raw55 proxies.

### Accepted boundary

This result means:

```text
raw55 = UNOBSERVED in the bounded survey
raw55 support = DEFERRED / currently unsupported
```

It does **not** mean raw55 is proven globally unused in Gothic 3.

Do not create a raw55 implementation, new monster/body marker vocabulary, or additional raw55 diagnostic unless future runtime evidence first establishes a relevant factual source `UseType == 55`.

EV-247 does not change the raw55 conclusion. It establishes transformed-actor raw8 Normal/Power marker compatibility only.

---

## 5. Pre-Regression Cross-Actor / Family Compatibility Gates — NEXT

These are bounded compatibility/coverage gates before the final mixed regression. They are not permission to redesign source ownership or create actor-specific marker vocabularies.

### 5.1 Native Sabretooth NPC -> player Normal/Power marker control

Use the same marked Sabretooth Normal/Power animations that passed under `Transform_Sabertooth_Potion`, but let a genuine native Sabretooth NPC attack the player.

Purpose:

```text
determine whether the existing raw8 Normal/Power FIST mechanism
also works when the attacker is a native NPC actor
rather than the transformed Hero
```

Require:

- factual raw8 `Fist` source;
- marker ownership decision with `HasFistMarkers=1`;
- accepted FIST opportunities for Normal/Power;
- no native pre-marker leak for the marked executions;
- damage, when contact occurs, after the authored opportunity through the native body-damage route;
- no actor/species-specific code change before this control.

`research/raw/2026.09.08_sabertooth_marked_attacks.log` is **ACTIVE COMPARISON — KEEP RAW** until this native-NPC comparison is closed.

### 5.2 Raw-8 Quick mechanism classification

EV-247 establishes:

```text
Quick-left/right source = factual raw8 Fist
Quick physical damage   = native Game +0x16E348
FIST marker             = currently REJECTED_UNSUPPORTED_HIT
```

The current rejection is an explicit implementation boundary because FIST was previously proven only for Normal + Power; humans did not provide a testable Quick-Fist fixture.

Before any code change, determine whether raw-8 Quick traverses the same relevant latch/timing opportunity mechanism sufficiently to support the existing FIST contract.

If proven:

```text
make the smallest bounded Quick-family extension
-> rebuild/deploy normally
-> validate marked Quick-left/right against the same native route
```

If not proven, keep Quick native/unsupported and do not invent a second marker mechanism without evidence.

### 5.3 Native equipped-NPC marker controls

Use separate logs for each actor:

```text
Goblin -> factual 1H / raw2
Demon  -> factual 2H / raw3
Ogre   -> factual Axe / raw52
```

Put ordinary equipped-source markers on selected native NPC attack animations and let each NPC attack the player.

Purpose:

```text
confirm equipped marker ownership follows factual equipped source/action semantics
for NPC attackers as well as the already-proven player-side cases
```

Keep each NPC as a separate evidence artifact so failures/qualifications remain attributable.

### 5.4 Separated 2H vs Axe mod compatibility

With the mod that separates 2H from Axe animation families:

- mark at least one new 2H attack;
- mark at least one new Axe attack;
- include marker-free/native controls where practical.

The question is whether collision behavior follows factual equipped source/action semantics after the animation-family split, not whether vanilla filename grouping is preserved.

### 5.5 Separated 1H vs Rapier mod compatibility

With the mod that separates ordinary 1H from Rapiers:

- mark at least one ordinary 1H attack;
- mark at least one Rapier attack;
- include marker-free/native controls where practical.

Again, factual source/action semantics outrank animation-family naming.

Only after these bounded gates are dispositioned should the final mixed regression begin.

---

## 6. Final Native Mixed Collision Regression

Run one native/no-third-party mixed regression over the **supported current scope after the pre-regression compatibility gates above are closed**.

The purpose is coexistence/regression confirmation, not source redesign.

Protect at minimum:

```text
equipped RIGHT / LEFT / BOTH / OFF exact-set behavior
repeated-contact ClearTriggeredList semantics
Power / Pierce / SimpleWhirl / Hack current behavior
C1 generation-scoped occurrence/dedupe identity
C1-R1 exact-source terminal repair
supported raw-8 FIST behavior
unmarked/native fallback
one-live-collision-twin deployment invariant
```

There is no accepted PhysicalFist behavior to add to this gate from EV-245–EV-246.

Do not broaden this gate into raw55 discovery, Raise, speed, target acquisition, or a fresh family/source redesign.

---

## 7. AttackContinuationProtection — Separate Later Responsibility

`AttackContinuationProtection` is prevention for the known held-Use2 destructive continuation-loss route. It remains separate from `CollisionLifecycleGuard`/C1-R1.

Intended module boundary:

```text
AttackContinuationProtection.cpp
= prevent the known destructive bad-skip route when its factual native timeout/decision becomes due during a real attack

CollisionLifecycleGuard / C1-R1
= exact-source fail-safe if collision cleanup is nevertheless lost
```

### New Balance compatibility constraint

The User normally plays with New Balance, which already prevents the bad skip on most melee blocks but appears not to cover every case (known concern: left-held Staff; hand-to-hand/other forms not yet established).

Therefore the future protection must be **event/condition-gated**, not continuously active:

```text
native bad-skip timeout/consumer does not become due
-> module does nothing

native destructive timeout/consumer becomes due
+ no genuine attack CombatMove would be destroyed
-> native behavior unchanged

native destructive timeout/consumer becomes due
+ genuine attack CombatMove would be destroyed
-> suppress/defer only that destructive consequence
```

If New Balance has already prevented the native bad-skip route from reaching that factual condition, our module should naturally remain inactive.

Do not begin by adding an independent timer, polling loop, permanent watchdog, or unconditional attack-state override.

The preferred investigation is the smallest native decision boundary. Pausing/freezing the underlying timer remains only one possible implementation; if blocking/defering the destructive consumer is cleaner, prefer that. Evidence decides the exact intervention point.

Before implementation prove:

1. the exact timeout/decision path leading to destructive FullStop/state replacement;
2. whether the destructive consequence has any legitimate responsibility while the real attack CombatMove is active;
3. whether preventing/defering only that consequence lets the attack finish normally;
4. whether outside-attack timeout behavior remains native;
5. whether legitimate reaction/interruption FullStop/AISetState behavior remains untouched;
6. whether New Balance-covered attacks naturally produce no intervention;
7. whether C1-R1 remains an independent underlying fail-safe.

Minimum causal validation should include a known bad-skip case, an outside-attack control, a legitimate reaction control, and New Balance-enabled controls where the route is already prevented.

---

## 8. Compatibility Gates

### Compatibility Gate 1 — mature collision research assembly

After AttackContinuationProtection and the required combined regression, validate the mature marker/source/lifecycle/continuation assembly against:

```text
New Balance
+ relevant Jackydima collision DLLs, including Script_AttackCollision where applicable
```

Do not assume arbitrary same-function hook chaining or load-order safety.

EV-242 contains a bounded Pierce-specific compatibility control only; it is not blanket certification of the mature subsystem.

### Compatibility Gate 2 — final Script_G3AnimationBehaviors

After collision migration plus Raise and redesigned speed/configuration work, repeat compatibility/regression on the final production assembly before stable/release promotion.

---

## 9. Evidence / Artifact Boundary

Runtime evidence lifecycle is owned operationally by POP-05/POP-06:

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

The September 2–8 processed collision/Fist/raw55-survey artifacts are archived; `research/raw/2026.09.08_sabertooth_marked_attacks.log` intentionally remains raw as an active comparison input for the planned native-Sabretooth control.

---

## 10. Current Collision Validation Sequence

```text
production human raw-8 Fist                         CLOSED/PASS
Power/Pierce/SimpleWhirl/Hack expansion             CLOSED/PASS for tested scope
PhysicalFist/raw55 bounded discovery                CLOSED/DEFERRED — no raw55 observed
transformed Sabretooth Normal/Power raw8 marker     PASS — EV-247
-> native Sabretooth NPC Normal/Power marker control
-> raw8 Quick mechanism classification / bounded extension only if proven
-> native equipped-NPC markers: Goblin 1H / Demon 2H / Ogre Axe
-> separated 2H-vs-Axe mod marker compatibility
-> separated 1H-vs-Rapier mod marker compatibility
-> final native mixed collision regression over supported scope
-> separate AttackContinuationProtection research/implementation
-> combined marker + lifecycle + continuation regression
-> mature New Balance + relevant Jackydima compatibility gate
-> production collision migration
-> diagnostics-free collision integration validation
```

Exact immediate task remains owned by `SESSION_ENTRYPOINT.md` / `BETWEEN_CHATS.md`.

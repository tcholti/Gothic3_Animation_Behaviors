# Collision Validation Plan

**Status:** Current collision validation authority  
**Updated:** 2026-09-20

## Purpose

Define the standing validation rules and the remaining collision-validation campaign.

This file owns **what must still be tested and what counts as acceptance**. It does not own implementation architecture, settled collision facts, probe chronology, or exact evidence proof.

Current state: `SESSION_ENTRYPOINT.md`.  
Established facts: `COLLISION_REFERENCE.md`.  
Architecture: `DESIGN.md` / `COLLISION_LIFECYCLE.md` / `COLLISION_DIAGNOSTICS.md`.  
Permanent raw55: `COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`.  
Proof: `EVIDENCE_INDEX.md`.

The pre-compression validation history is preserved under `docs/archive/investigations/`.

---

## 1. Standing validation rules

- Do not reopen a closed causal gate without concrete contradictory evidence or a deliberate scope extension.
- Factual native action/source/UseType identity outranks filename inference.
- Native cleanup gets first opportunity.
- Equipped RIGHT / LEFT / BOTH / OFF control the desired physical equipped-source set; they do not guarantee uniform native target/contact/damage eligibility.
- Raw8 FIST and raw55 PhysicalFist are separate mechanisms.
- C1 monotonic generation remains the durable execution identity for marker occurrence/dedupe and equipped-source obligations.
- C1-R1 may repair only an exact owned outstanding source after native cleanup opportunity and current-equipped liveness are established.
- Diagnostics must not be required for behavior correctness.
- Diagnostic and behavior-only collision twins are mutually exclusive at runtime.
- Freeze one falsifiable question and minimum controls before a new causal investigation.
- Large regression runs use compact CORE diagnostics; unknown/anomalous events must retain richer classification.
- Every uploaded runtime batch closes fully under POP-06 before the next batch.
- New reusable results are promoted to current reference before a temporary investigation is archived.

Current research products:

```text
Script_FrameCollisionTest
  instrumented diagnostic twin

Script_FrameCollisionBehaviorTest
  diagnostics-free behavior twin
```

---

## 2. Closed gates — do not reconstruct routinely

The following are already closed for their tested/evidence-bounded scope:

| Area | Closure |
|---|---|
| C1-R1 exact-source lifecycle safety | EV-206–EV-207 |
| behavior/diagnostic source separation | EV-208–EV-215 |
| equipped Normal/Quick/full Whirl foundation | closed before EV-241 |
| Power | EV-241 |
| Pierce | EV-242 |
| SimpleWhirl | EV-217–EV-220, EV-243 |
| tested 2H/Staff Hack | EV-216, EV-244 |
| raw8 Normal/Power | EV-221–EV-240 |
| raw8 Quick | EV-247–EV-249 |
| raw8 Sprint | EV-250–EV-251 |
| raw55 factual discovery + four-family causal route | EV-262–EV-294 |
| permanent raw55 focused acceptance | EV-295–EV-298 |

Current semantics for these gates belong in `COLLISION_REFERENCE.md` and owning architecture. Use `EVIDENCE_INDEX.md` only when proof detail matters.

---

## 3. Standalone collision regression campaign — ACTIVE

The broader collision campaign validates the mature feature across actors, sources, authoring patterns, separation mods and stress conditions.

Publication rule:

```text
one complete runtime log per setup where attribution matters
-> User may upload small batches
-> Normal Chat closes every uploaded batch under POP-06
-> next batch only after evidence/reference/archive/current-state maintenance is complete
```

<a id="phase-1-golem"></a>

### 3.1 Phase 1 — Human marker attack matrix — CLOSED/PASS

Purpose: validate the prepared **human attack routes with authored markers**. Golem was used as the consistent target fixture across these runs; the phase was not a Golem-behavior test.

Closed progress:

```text
1H                         PASS — EV-299
1H+torch                   PASS — EV-300
dual 1H                    PASS — EV-301
2H                         PASS — EV-302
Staff                      PASS — EV-303
human raw8 single FIST     PASS — EV-304
human raw8 double FIST     PASS — EV-305
1H+shield                  PASS — EV-306

supplemental controls:
Sabretooth marked/raw8 single-marker compatibility + Quick closure — EV-247–EV-249
Sabretooth raw8 double FIST                                         PASS — EV-307
shield-bash LEFT/raw9                                               NEGATIVE CONTROL / DEFERRED — EV-308
```

The human marker matrix is complete. Sabretooth has also covered marked single-marker behavior and the later two-marker same-C1 control.

The shield-bash negative control does not represent a regression failure: LEFT/raw9 physical activation/cleanup worked, but Gothic supplied no native damage route in the tested fixture. Shield-bash damage is deferred.

### 3.2 Phase 2 — Orc attack matrix — CLOSED/PASS

Closed coverage:

```text
Staff animation set
  factual source = It_Halberd_Orc_01 / UseType 51
  Hack / Whirl / Quick L+R / Power / Normal = PASS — EV-309

Fist/raw8
  factual source = Fist / UseType 8
  Normal / Power = PASS — EV-309

2H animation set
  factual source = It_Axe_Orc_01 / UseType 52
  Quick L+R / Normal / Power / Hack / Whirl = PASS — EV-310
```

Across both logs, all tested Orc attack types damaged the player at least once, accepted marker routes remained attributable, native cleanup/finalization stayed clean, and no ownership/invariant/rejection/repair contradiction appeared.

Phase 2 is complete.

### 3.3 Phase 3 — Other weapon-using creatures/NPCs — CLOSED/PASS

Current-DLL/post-raw55 regression coverage:

```text
Goblin  -> factual 1H/raw2                 PASS — EV-311
Demon   -> factual 2H/raw3                 PASS — EV-312
Ogre    -> factual Axe/raw52               PASS — EV-313
Stalker -> factual Axe/raw52               PASS — EV-314
```

Goblin, Demon and Ogre were deliberately repeated after permanent raw55 integration even though earlier controls existed at EV-252–EV-254. Their established supported routes remain healthy, providing bounded regression evidence that the raw55 work did not disturb those equipped-NPC paths. Stalker extends the current coverage with another Axe/raw52 actor/source fixture.

Before Phase 4, EV-332–EV-336 add a mixed player/enemy cross-source pass on the accepted current build: player dual-1H vs Ogre/raw52, 1H vs Orc Raider/raw52, 1H+shield vs Demon/raw3, 2H vs Stalker/raw52, and raw8 Fist vs Goblin/raw2. The batch also re-confirms dual-slot desired-set semantics, shield source isolation, 2H Whirl/Hack, raw8 timing, and permanent equipped Sprint under ordinary combat.

EV-311 exposed the factual equipped Sprint/right/raw2 Goblin route that was subsequently researched and promoted. Permanent `EquippedSprintCollision` acceptance is now CLOSED/PASS through EV-329; Phase 3 remains closed and that scope no longer blocks Phase 4.

### 3.4 Phase 4 — Non-weapon creatures — PAUSED AT RAW8 AUTHORING-SEMANTICS GATE

Exercise multiple prepared creature/body-contact routes.

Current Phase-4 progress:

```text
Sabretooth raw8 double-FIST, native + transformed player    PASS — EV-337
Sabretooth raw8 single-FIST, native + transformed player    PASS — EV-338
Wolf marked raw8, native + transformed player               PASS — EV-339
Wolf unmarked raw8 native-fallback control, both forms       PASS — EV-340
Troll raw55 mixed single/double FIST + player Staff          PASS — EV-341
Minecrawler raw8 Normal/Power/Quick + player 1H-family       PASS — EV-342
Bloodfly raw8 Normal/Power/Sprint + player 1H                PASS — EV-343
Boar raw8 Normal + player 1H+shield                          PASS — EV-344
Bison raw8 Normal + player 2H                                PASS — EV-345
Gargoyle raw8 Power timing sweep                            DESIGN DISCOVERY — EV-346
Gargoyle post-attempt latch hit/miss observation             CAUSAL PASS — EV-347
```

The Sabretooth/Troll reruns above were deliberate differentiated fixtures rather than duplication: they added transformed-player symmetry, single-vs-double marker comparison, and mixed current-build coexistence. EV-342–EV-345 then broaden factual Fist/raw8 coverage to Minecrawler, Bloodfly, Boar and Bison. EV-342 is an ordinary PASS: some correctly processed Minecrawler executions did not physically contact, which is normal runtime attack variance rather than a collision-system qualification.

EV-346 is a material design discovery, not a creature-specific failure. Gargoyle factual raw8 Power showed that the current early-FIST mechanism is one-shot: frame-1 0/4, approximate frame-3 5/10, frame-6 8/8 and native 7/7 under a stationary-player fixture, while ownership/markers/finalization remained healthy. EV-347 then proved that the native latch closes to 1 after the attempt whether that exact synthetic invocation hits or misses. User + Normal Chat have chosen persistent opportunity-window semantics; broad Phase-4 certification remains paused while the smallest causal rearm mechanism is researched.

Preserve factual runtime source/UseType. Do not infer raw8/raw55 from creature name or animation token.

Permanent raw55 behavior applies only to its frozen factual contract. Ordinary raw8 behavior remains governed by the separate raw8 mechanism. EV-339–EV-340 provide a paired Wolf control: factual Fist/UseType8 with markers enters raw8 authored timing; the same factual source without markers stays completely native. Permanent equipped Sprint behavior is governed separately by `EquippedSprintCollision`; do not infer applicability from creature name or Power-named animation text.

### 3.5 Phase 5 — 2H vs Axe separation-mod compatibility

Under the prepared Axe-separation mod, verify both:

```text
ordinary 2H route
Axe-defined separated route
```

Protect authored markers, factual equipped source/UseType, native cleanup/finalization and ownership diagnostics.

### 3.6 Phase 6 — 1H vs Rapier separation-mod compatibility

Under the Rapier-separation mod, verify ordinary 1H and separated Rapier routes.

The objective is to prove collision follows factual runtime source/action semantics rather than old animation-family grouping assumptions.

### 3.7 Phase 7 — Stress regression

After structured phases pass, intentionally mix already-supported routes to expose:

```text
ownership/anomaly misclassification
occurrence/dedupe leakage across C1 generations
lost native cleanup
unexpected terminal repair
source replacement/liveness contradictions
repeated-contact regressions
raw8/raw55/equipped interference
mixed actor/target sequencing problems
```

A stress failure must first be reduced to the smallest factual route before source changes are considered.

---

## 4. Regression acceptance invariants

Across the complete campaign protect at minimum:

```text
equipped RIGHT / LEFT / BOTH / OFF exact-set behavior
repeated-contact ClearTriggeredList semantics
Power / Pierce / SimpleWhirl / Hack behavior
supported raw8 Normal / Power / Quick / Sprint
supported permanent raw55 Normal / Quick / Power / Sprint-origin
supported permanent equipped Sprint RIGHT / LEFT / BOTH / OFF policy
unmarked raw55 native fallback
raw8/raw55 coexistence
C1 generation-scoped occurrence/dedupe
C1-R1 exact-source terminal repair
native cleanup + outstanding-zero finalization
one-live-collision-twin deployment invariant
compact CORE anomaly discovery
Axe-separation compatibility
Rapier-separation compatibility
```

The standalone campaign is complete only when all seven phases have an explicit disposition and every published runtime artifact is closed under POP-06.

---

## 5. Diagnostic requirements

Default regression uses compact CORE diagnostics under `COLLISION_DIAGNOSTICS.md`.

```text
known healthy path
-> compact

unknown / unsupported source or family
-> richer classification

unexpected rejection / failure
-> richer classification

C1 anomaly / repair / divergence
-> richer classification

DEEP explicitly enabled
-> bounded research detail
```

Unknown-family records must preserve enough factual data to classify action, phase, StatePosition, motion, marker, source/UseType/group, side association, rejection reason and relevant damage correlation.

Do not return to full research-era verbosity for every known successful execution.

---

## 6. Evidence / artifact boundary

For each runtime run:

```text
freeze test + filename
-> User runs locally
-> publish unchanged raw artifact
-> Normal Chat interprets
-> concise canonical EV
-> promote changed reusable fact to current reference/architecture
-> archive processed runtime artifact when no active comparison remains
-> archive closed temporary investigation contract when applicable
-> run POP-12 validation
-> only then next batch
```

`research/raw/` is active intake, not a history store.

---

## 7. New Balance exact distributed-bundle regression — after standalone

After all seven standalone phases pass, test the exact New Balance 0.7 distributed bundle with relevant Jackydima collision components including `Script_AttackCollision` where applicable.

Source-level preflight evidence is not sufficient final compatibility certification.

Do not assume arbitrary same-function hook chaining or DLL load-order safety.

---

## 8. Production collision migration — after compatibility gate

After standalone + New Balance compatibility pass:

```text
mature collision behavior
-> migrate into src/Script_G3AnimationBehaviors
-> diagnostics remain separate
-> release-purity/integration validation
```

Do not migrate during the current standalone campaign.

---

## 9. AttackContinuationProtection — separate later responsibility

`AttackContinuationProtection` remains separate from collision cleanup.

Intended boundary:

```text
AttackContinuationProtection
= prevent/defer the proven destructive bad-skip consequence at its factual native decision point

CollisionLifecycleGuard / C1-R1
= exact-source fail-safe if collision cleanup is nevertheless lost
```

Before implementation, prove the exact native timeout/consumer path and validate at least:

1. known bad-skip case;
2. outside-attack control;
3. legitimate reaction control;
4. New Balance-enabled controls where New Balance already prevents the route.

Do not start with an independent timer, polling loop, unconditional attack-state override or teardown resurrection.

This work remains paused until deliberately reopened.

---

## 10. Current sequence

```text
standalone collision regression          CURRENT
-> New Balance exact bundle regression
-> production collision migration
-> diagnostics-free integration validation
-> later Raise + Speed + Config

AttackContinuationProtection remains separate unless deliberately reopened
```

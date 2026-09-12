# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-12

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

> **MAX-CONTEXT / FAILED-CHAT RULE:** If the previous Normal Chat reached its context limit, became unusable, or ended before evidence closure, immediately use `docs/PROJECT_OPERATING_PROCEDURES.md` **§13 POP-11 — Normal Chat Continuity and Interrupted-Context Recovery**. Enter **Recovery Lock** before starting any new implementation, runtime experiment, or Work task. Oversized runtime logs are handled by **§9 POP-07**.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Operating procedures / failed-Chat recovery: `docs/PROJECT_OPERATING_PROCEDURES.md` §13 POP-11  
Large runtime-log procedure: `docs/PROJECT_OPERATING_PROCEDURES.md` §9 POP-07  
Project-wide feature-development methodology: `docs/FEATURE_DEVELOPMENT_METHOD.md`  
Raw55 causal-probe authority: `docs/COLLISION_RAW55_CALLBACK_SUPPRESSION_PROBE.md`  
Bounded Work execution: `docs/WORK_IMPLEMENTATION_PROTOCOL.md`  
Architecture/redesign authority: `docs/COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`  
Overall architecture: `docs/DESIGN.md`  
Validation: `docs/COLLISION_TEST_PLAN.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`; latest continuation: `docs/EVIDENCE_LEDGER_250_ONWARD.md`

---

## Closed Collision Boundary

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
collision architecture verification        CLOSED/PASS — EV-208–EV-215
Power                                      CLOSED/PASS — EV-241
Pierce                                     CLOSED/PASS — EV-242
SimpleWhirl                                CLOSED/PASS — EV-217–EV-220, EV-243
Hack tested 2H/Staff scope                 CLOSED/PASS — EV-216, EV-244
raw8 FIST Normal + Power + Quick scope     CLOSED/PASS — EV-221–EV-249
Stage A/B compact equivalence sentinel     CLOSED/PASS — EV-250
raw8 FIST Sprint production support        CLOSED/PASS — EV-251
native NPC 1H/raw2 control                 CLOSED/PASS — EV-252
native NPC 2H/raw3 control                 CLOSED/PASS — EV-253
native NPC Axe/raw52 control               CLOSED/PASS — EV-254
Orc broad raw52 native control             CLOSED/PASS — EV-255
Orc Staff/raw51 native control             CLOSED/PASS — EV-256
Orc raw8 Fist Normal/Power control         CLOSED/PASS — EV-257
Orc Hack vs FinishingAttack separation     CLOSED/PASS — EV-258
```

Raw8 FIST remains one shared native mechanism across the proven Normal, Power, Quick and Sprint family scope. Marker applicability is not species-gated. No authored FIST_OFF, Fist ClearTriggeredList, equipped Fist window/C1 weapon obligation, direct/custom damage, or species branch.

Sprint production implementation remains `270d98f59fd7f83ab332d7cfbfc07d243273e0ca`.

---

## Raw55 / PhysicalFist Discovery and Probe State

The earlier Troll/BlackTroll baseline established factual `gEUseType_PhysicalFist / raw55`:

`research/raw/2026.09.12_troll_collision_test.log`

Baseline facts already frozen by the probe contract:

```text
Troll / BlackTroll
right source: TrollFist / raw55 / group5
left source:  TrollFist / raw55 / group5
native tested offense request: RIGHT source 5 -> 7
native cleanup: 7 -> 5
native damage caller observed: Game.dll +0x00069484
raw8 resolver: <none>
current authored G3AB_COL_FIST: unsupported for raw55 by production design
```

Do not infer damaging limb from RIGHT and do not infer physical source side from animation-name `L/R`.

The frozen diagnostic callback-suppression probe was implemented at:

`b1cea4904ca2ecb14d26c1e0d23cdab6e0a07e25` — `Add raw55 callback suppression diagnostic probe`

The probe remains temporary diagnostic-only `PhysicalFistProbe.cpp/.h`; `EngineBridge` remains hook owner; production `Raw8FistCollision` is unchanged.

A deployment/load log was committed at:

`70334d2642148c6d17f9683d800ab2bbe8cea492`

The current runtime artifact was then committed at:

`caaaa2ea00eae3954aa92f0ce567c5ea140a8b64`

Artifact:

`research/raw/2026.09.12_troll_and_other_marker_test.log`  
blob `6f8c58f5049382ef6d6c595c16b3ecb32a835b6e`  
size `2,410,630` bytes

User visual/runtime observation from that run:

```text
marked Troll attacks: could not hit/damage Player
marked BlackTroll attacks: could not hit/damage Player
marked Sabretooth control after Trolls: worked as before
marked Golem control after Trolls: worked as before
```

**Important epistemic status:** this observation plus the committed raw artifact is highly encouraging for the causal hypothesis, but the oversized log has **not yet completed POP-07 targeted analysis and canonical Evidence Ledger promotion**. Therefore do not yet label the raw55 suppression probe formally CLOSED/PASS in canonical evidence.

---

## CURRENT IMMEDIATE RESPONSIBILITY — RECOVERY LOCK + LARGE-LOG INTERPRETATION

Because the previous Chat reached its context limit during the first pass over the 2.4 MB runtime artifact, the next fresh Normal Chat must begin under POP-11 Recovery Lock.

Do **not** start another implementation, Work task, or creature test first.

Read in this order:

```text
1. SESSION_ENTRYPOINT.md
2. BETWEEN_CHATS.md
3. PROJECT_OPERATING_PROCEDURES.md §13 POP-11
4. PROJECT_OPERATING_PROCEDURES.md §9 POP-07
5. COLLISION_RAW55_CALLBACK_SUPPRESSION_PROBE.md
6. only the exact raw/derived evidence needed for the targeted analysis
```

First responsibility:

```text
analyze research/raw/2026.09.12_troll_and_other_marker_test.log by POP-07
-> correlate probe suppression records with Troll/BlackTroll generations
-> verify absence/presence of raw55 5 -> 7 activation and raw55 damage in suppressed marked executions
-> verify FIST frame still occurs with expected current raw55 unsupported result
-> verify attack/recover/next-generation progression remains healthy
-> verify Sabretooth/raw8 and Golem marked controls stayed unchanged
-> check C1/lifecycle anomaly signals
-> decide exact causal disposition
-> promote reusable result to canonical Evidence Ledger if supported
-> archive or retain artifacts according to POP-06
```

Only after that evidence transaction is closed may Normal Chat decide whether to freeze a permanent `PhysicalFistCollision` production contract. A passing probe still does **not** authorize production implementation by itself; production remains a separate frozen Work task and must remove the temporary probe.

The broader native-creature certification remains paused until raw55 is either explicitly deferred/rejected or implemented and focused-valid.

---

## Other September 12 Evidence-Maintenance Debt to Check During Recovery Lock

These artifacts were already interpreted in the prior Normal Chat, but the fresh Chat must verify whether their canonical EV promotion/archive transaction was completed before starting new causal work:

```text
research/raw/2026.09.12_stalker_native_markers_test.log
  interpreted result: native Stalker factual Axe/raw52, marked Normal + Power healthy

research/raw/2026.09.12_fall_down_damage.log
  interpreted result: no unresolved Fist/PhysicalFist source classification exposed

research/raw/2026.09.12_blunt_arrow_bolt_test.log
  interpreted result: BluntArrow = UseType4; BluntBolt = UseType7; neither raw55
```

If `EVIDENCE_LEDGER_250_ONWARD.md` still ends at EV-258, treat these as an outstanding POP-06 maintenance closure, not as permission to redo the tests.

---

## Later Validation / Compatibility Work

After raw55 disposition and evidence closure:

```text
resume prepared native Fist creature sweep

Axe animation-separation mod:
  quick attributable validation logs for Hero/humans, Orc, Demon, Ogre, Stalker

Rapier animation-separation mod:
  Hero/human family only

Zombie animation mod:
  modded Zombie-specific animation family
```

For Axe separation, the five-family pass is intentional compatibility coverage. It does not imply actor-specific collision rules.

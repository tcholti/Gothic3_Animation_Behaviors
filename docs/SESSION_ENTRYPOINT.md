# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-12

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe, not accumulated in `EngineBridge` or another stable module. Proven behavior is promoted into the permanent module that actually owns the responsibility. Hooks remain transport-only, temporary probe scaffolding is removed, and broad/final validation waits until known scope-changing design decisions are resolved. Full authority: `docs/FEATURE_DEVELOPMENT_METHOD.md`.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Project-wide feature-development methodology: `docs/FEATURE_DEVELOPMENT_METHOD.md`  
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

Validated diagnostic built/live SHA256 remains:
`1A58C6CF4D98B02873A114A7AF6F1AA372B8A937B1EC60DDA3A221F52879F74F`.

---

## New factual discovery — PhysicalFist/raw55 REOPENED

The prior EV-245–EV-246 raw55 status was **deferred because no factual runtime UseType55 had been observed**. That prerequisite is now satisfied by the active Troll/BlackTroll runtime log:

`research/raw/2026.09.12_troll_collision_test.log`

Observed facts:

```text
Troll / BlackTroll
right source: TrollFist / gEUseType_PhysicalFist / raw55 / group5
left source:  TrollFist / gEUseType_PhysicalFist / raw55 / group5
native tested offense request: RIGHT source 5 -> 7
native cleanup: 7 -> 5
native damage caller: Game.dll +0x00069484
raw8 resolver: <none>
current authored G3AB_COL_FIST: unsupported for raw55 by design
```

The physical RIGHT source is a bookkeeping/source fact only. **Do not infer damaging limb from RIGHT**, and do not infer source side from animation-name `L/R`; prior Fist experiments show body contact can involve multiple limbs and prior weapon research did not establish attack-name `L/R` as physical source identity.

Troll `...PowerAttack...` motion also factually executes as `gEAction_SprintAttack / Action 9 / Family SPRINT`, strengthening the existing rule that native action identity outranks animation filename.

No `Troll_Stand_None_Fist...` motion occurred in the tested Troll/BlackTroll run. Treat those assets as unexercised; do not invent behavior for them.

---

## Current Immediate Responsibility — RAW55 DESIGN / PROBE GATE

**Pause the broader native-creature validation sequence here.** The Troll discovery changes the intended product scope enough that continuing final-style validation before raw55 disposition would weaken the later certification.

Current question:

> Can factual `PhysicalFist/raw55` support the existing author-facing `G3AB_COL_FIST` cleanly and safely, while preserving native TouchDamage/target/damage semantics and keeping raw8 behavior untouched?

Current architectural direction, not yet production authority:

```text
same author-facing marker: G3AB_COL_FIST

raw8 Fist
-> existing Raw8FistCollision mechanism

raw55 PhysicalFist
-> separate physical-source mechanism if proven
-> likely group5/group7 ownership using existing physical lifecycle infrastructure
-> NOT raw8 latch/timing logic
```

The main unresolved causal question is pre-marker native activation. In the Troll log, native raw55 can open its group7 collision window before a later authored FIST marker. Therefore a production implementation cannot simply activate raw55 at the marker; it must first prove that marked raw55 can safely take callback/timing ownership without breaking native attack progression.

### Required research method

Follow `FEATURE_DEVELOPMENT_METHOD.md`:

```text
create isolated diagnostic-only PhysicalFist probe module
-> EngineBridge remains hook transport/delegation only
-> do not put raw55 experiments into Raw8FistCollision
-> do not accumulate experiment state/policy in EngineBridge
-> test one causal variable at a time
-> if mechanism is proven, freeze production contract
-> implement permanent PhysicalFistCollision (or equivalent owner)
-> remove probe scaffolding
-> validate focused production candidate
-> only then resume broad creature/final validation
```

First intended causal probe:

```text
exact marked factual raw55 execution
-> suppress its native attack-callback activation only
-> do NOT yet provide replacement marker activation

Question:
does pre-marker 5->7/native damage disappear while attack animation/state/recover/next attacks remain healthy?
```

No code task is frozen yet; Normal Chat should finish source/design review and freeze the bounded probe responsibility before Work implementation.

---

## Recent bounded observations already completed

```text
Stalker native baseline:
  factual It_Axe_SpikedClub_01 / raw52
  marked Normal + Power healthy 5 -> 7 -> 5
  useful future Axe-separation baseline

fall damage:
  did not expose the unresolved Fist/PhysicalFist source classification

special blunt projectile test:
  BluntArrow = UseType4
  BluntBolt  = UseType7
  neither identifies raw55
```

The previously planned two bounded unresolved-Fist checks are therefore complete. Do not expand them further.

---

## Later validation / compatibility work

After raw55 is either explicitly deferred/rejected or implemented and focused-valid:

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

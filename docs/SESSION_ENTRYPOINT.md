# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-11

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Sprint transport probe contract: `docs/COLLISION_SPRINT_TRANSPORT_PROBE.md`  
Architecture/redesign authority: `docs/COLLISION_ARCHITECTURE_REDESIGN_PLAN.md`  
Overall architecture: `docs/DESIGN.md`  
Diagnostics: `docs/COLLISION_LOGGER_PLAN.md`  
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
PhysicalFist/raw55 bounded discovery       CLOSED/DEFERRED — EV-245–EV-246
raw8 FIST Normal + Power + Quick scope     CLOSED/PASS — EV-221–EV-249
Stage A architecture build/load gate       CLOSED/PASS — 2026-09-10
Stage B diagnostic build/load gate         CLOSED/PASS — 2026-09-10
Stage A/B compact equivalence sentinel     CLOSED/PASS — EV-250
```

Raw-8 FIST remains one shared native mechanism. No authored FIST_OFF, Fist ClearTriggeredList, equipped Fist window/C1 weapon obligation, direct/custom damage, species branch, or raw55 generalization.

Stage A behavior architecture implementation: `7c5874932cd6eafa5af3414c65a4442b3d74bb73`.  
Stage B diagnostic implementation: `5737db32e5eda76810989ddfb5659f8405c0c458`.  
Validated Stage-B diagnostic SHA256: `081CDF413EC623079B8E4F1934EA7F1C27A7FFC7307B3BA0B19EA000BDA108BD`.

---

## SprintAttack Static Research — CURRENT BOUNDARY

Sprint remains deliberately unsupported.

EV-250 repeatedly establishes the tested runtime facts:

```text
actor = native Sabretooth
action = 9 = gEAction_SprintAttack
phase = 1
StatePosition = 1
motion = Sabretooth ... PowerAttack_Hit ...
marker = G3AB_COL_FIST
result = REJECTED_UNSUPPORTED_HIT
C1 generation = valid
RIGHT source = Fist / UseType 8 / raw8 / group0
C1 script transport binding = _AI_PowerAttack
```

The PowerAttack-named motion is not family authority. Factual action identity remains authoritative.

Remote source/API/binary review on 2026-09-11 narrows the five Sprint questions as follows:

```text
1. transport:
   _AI_PowerAttack is the observed script transport binding;
   pinned SDK search exposes no dedicated OnAI_Sprint callback;
   unresolved fact = whether Action 9 is already factual at physical OnAI_PowerAttack ENTRY
                     or becomes factual during/after the original callback.

2. bounded source scope:
   factual observed Sprint source = Fist/raw8/group0 only.
   Existing Demon 2H/raw3, Goblin 1H/raw2 and Ogre Axe/raw52 controls contain no Action 9.
   Therefore equipped Sprint is not evidenced, but is not proven impossible.

3. tested action/phase contract:
   native Sabretooth Action 9 uses phase 1 and StatePosition 1.
   Do not generalize beyond tested scope yet.

4. raw8 native mechanism:
   tested Game static control flow strongly supports the same generic latch/timing route:
   SPU+0x164 gate -> Game+0x16E160..190 timing comparison -> +0x16E1A3 latch close
   -> later native Fist damage path +0x16E348.
   Nearby special action branch is 0x39, not Action 9.
   Runtime Sprint transport timing still needs the bounded probe before implementation.

5. equipped Sprint:
   no current runtime evidence.
```

Current architecture also explains why Sprint is not accidentally treated as Power: `EvaluateAttackCallbackOwnership()` requires the factual action to match the supplied family. Action 9 therefore fails `AttackFamily_Power` eligibility by design. Stage-B callback logging suppresses non-eligible ownership records, so the existing runtime log cannot reveal the callback-entry action.

---

## Current Immediate Responsibility — FROZEN SPRINT TRANSPORT PROBE

Exact authority:

```text
docs/COLLISION_SPRINT_TRANSPORT_PROBE.md
```

The probe is diagnostic-only and read-only:

```text
existing OnAI_PowerAttack physical hook only
CORE SPRINT_TRANSPORT at ENTRY and AFTER_ORIGINAL
log SPU+0x154 factual action + actor factual action + phase + motion
no AttackFamily_Sprint
no marker acceptance
no raw8 latch/timing behavior change
no new hook/RVA/calling convention
no species filter
```

Work may implement only that frozen probe. Work build execution remains prohibited.

After independent source review, the remote-only phase stops. The next required step is the User's local build/deploy/run of the diagnostic DLL and one native-Sabretooth fixture that captures Action 9.

Do not implement Sprint behavior, alias Sprint to Power, or begin Goblin/Demon/Ogre matrix testing before that runtime transport result is interpreted in Normal Chat.

Active Sprint evidence:

```text
research/raw/2026.09.10_sabertooth_npc_pc_marked_attacks_new.log
```

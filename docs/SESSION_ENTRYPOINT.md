# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper authorities only when the active responsibility requires them.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-11

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Current Sprint implementation contract: `docs/COLLISION_SPRINT_RAW8_IMPLEMENTATION.md`  
Completed Sprint transport probe contract: `docs/COLLISION_SPRINT_TRANSPORT_PROBE.md`  
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
Sprint transport observability probe       CLOSED/PASS — 2026-09-11
```

Raw-8 FIST remains one shared native mechanism. No authored FIST_OFF, Fist ClearTriggeredList, equipped Fist window/C1 weapon obligation, direct/custom damage, species branch, or raw55 generalization.

Stage A behavior architecture implementation: `7c5874932cd6eafa5af3414c65a4442b3d74bb73`.  
Stage B diagnostic implementation: `5737db32e5eda76810989ddfb5659f8405c0c458`.  
Validated Stage-B diagnostic SHA256: `081CDF413EC623079B8E4F1934EA7F1C27A7FFC7307B3BA0B19EA000BDA108BD`.

---

## SprintAttack Evidence — CURRENT BOUNDARY

Sprint is still unsupported in production code at this entry point, but the implementation boundary is now frozen.

The completed transport probe plus `research/raw/2026.09.11_sprint_transport_probe_4.log` establish the tested runtime facts:

```text
actor = native Sabretooth
factual actor action = 9 = gEAction_SprintAttack
physical callback transport = existing OnAI_PowerAttack
SPU+0x154 action at callback ENTRY = 2
actor routine action at callback ENTRY = 9
actor routine action AFTER_ORIGINAL = 9
phase = 1
StatePosition = 1
motion = Sabretooth ... PowerAttack_Hit ...
marker = G3AB_COL_FIST
current result = REJECTED_UNSUPPORTED_HIT
C1 generation = valid
source = Fist / gEUseType_Fist / raw8 / group0
RequiredSourceMask = 0
left source = none
```

Therefore:

- no new Sprint physical hook is required;
- Sprint must remain a first-class semantic family rather than being aliased to Power;
- the existing `OnAI_PowerAttack` wrapper is early enough to route Sprint from factual actor routine Action 9;
- SPU+0x154 Action 2 is transport identity, not Sprint semantic identity;
- current Sprint evidence is raw8 FIST only;
- equipped RIGHT/LEFT/BOTH/OFF Sprint remains unevidenced and must stay unsupported;
- the exact AI/distance rule that causes SprintAttack is not required for marker implementation.

A practical validation fixture is sufficiently repeatable:

```text
god mode
-> transform player to Sabretooth
-> spawn native Sabretooth
-> fight it, including Power attacks from range
```

---

## Current Immediate Responsibility — FROZEN RAW8 SPRINT FIST IMPLEMENTATION

Exact authority:

```text
docs/COLLISION_SPRINT_RAW8_IMPLEMENTATION.md
```

The bounded production responsibility is:

```text
add AttackFamily_Sprint
map factual gEAction_SprintAttack -> Sprint
reuse existing OnAI_PowerAttack physical hook
select Sprint from factual actor routine Action 9 at callback entry
admit Sprint into existing raw8 FIST mechanism
Sprint marker-owned StatePosition = 1
keep equipped Sprint explicitly unsupported
retire temporary SPRINT_TRANSPORT diagnostic records
preserve native damage, C1, equipped collision and all unrelated families
```

Work may implement only that frozen responsibility. Work build execution remains prohibited.

After Work publishes, Normal Chat must independently review the exact source diff before the User builds locally.

Do not broaden into Sprint AI-selection research, equipped Sprint behavior, raw55, new hooks, or unrelated collision work.

Active Sprint evidence:

```text
research/raw/2026.09.11_sprint_transport_probe_4.log
```

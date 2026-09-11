# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-11

## Current Bridge — SPRINT TRANSPORT CLOSED; RAW8 SPRINT FIST IMPLEMENTATION FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat orientation:

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_SPRINT_RAW8_IMPLEMENTATION.md
4. WORK_IMPLEMENTATION_PROTOCOL.md
5. EVIDENCE_LEDGER_250_ONWARD.md only when promoting evidence
```

---

## Closed Starting Point

```text
Stage A architecture refactor                 CLOSED/PASS
Stage B diagnostic refactor                   CLOSED/PASS
Stage A/B compact equivalence sentinel        CLOSED/PASS — EV-250
Sprint transport observability probe          CLOSED/PASS — 2026-09-11
```

Stage A implementation:
`7c5874932cd6eafa5af3414c65a4442b3d74bb73`

Stage B implementation:
`5737db32e5eda76810989ddfb5659f8405c0c458`

Sprint transport probe implementation:
`2d30eeb3242e9391e384d08c54b14bcd825a3b12`

Probe DLL deployed with matching built/live SHA256:
`42EDF5E01748ACF016BBB58B83CBFB71EC97DE6343A344CEEF2214F1B82207B6`

Decisive raw Sprint fixture:

```text
research/raw/2026.09.11_sprint_transport_probe_4.log
```

---

## Sprint transport result

The probe is decisive for the tested native-Sabretooth Sprint case:

```text
physical callback = existing OnAI_PowerAttack
ENTRY:          SPUAction=2  ActorAction=9  Phase=1
AFTER_ORIGINAL: SPUAction=2  ActorAction=9  Phase=1
motion = Sabretooth ... PowerAttack_Hit ...
```

Therefore the existing Power callback transport is early enough to route Sprint without another hook.

Do not interpret SPUAction 2 or the PowerAttack-named motion as Power-family semantics. Factual actor routine Action 9 is the Sprint identity.

---

## Sprint marker/source result

The same run contains many consistent Sprint marker discovery executions:

```text
action = 9 = gEAction_SprintAttack
phase = 1
StatePosition = 1
marker = G3AB_COL_FIST
C1 generation = valid
source = Fist / raw8 / group0
RequiredSourceMask = 0
left source = none
result = REJECTED_UNSUPPORTED_HIT
```

The rejection occurs because Sprint is not yet admitted as a supported first-class family/raw8 family.

Current runtime evidence is raw8 FIST only. Equipped Sprint RIGHT/LEFT/BOTH/OFF remains unevidenced and must stay unsupported.

The exact AI/distance selection rule for SprintAttack is not required. The practical validation fixture is sufficiently repeatable:

```text
god mode
-> transform player to Sabretooth
-> spawn native Sabretooth
-> fight it, including Power attacks from range
```

---

## Frozen next Work responsibility

Authority:

```text
docs/COLLISION_SPRINT_RAW8_IMPLEMENTATION.md
```

Implement only:

```text
AttackFamily_Sprint
gEAction_SprintAttack -> Sprint family
existing OnAI_PowerAttack callback selects Sprint from factual actor Action 9
Sprint admitted to the existing raw8 FIST mechanism
Sprint marker-owned StatePosition = 1
diagnostics name Sprint as SPRINT
Sprint remains FIST/raw8-only; equipped Sprint stays unsupported
temporary SPRINT_TRANSPORT probe logging retired
```

Hard prohibitions:

```text
NO new hook/callback/RVA/calling convention
NO Sprint -> Power semantic alias
NO SPU+0x154 semantic classification
NO equipped Sprint marker support
NO marker vocabulary change
NO raw8 resolver/timing redesign
NO C1/equipped cleanup/Hack-routing changes
NO raw55/custom damage/species special case
NO AI-selection/distance research encoded into behavior
NO unrelated refactor
NO Work build execution or build-tool probing
```

After Work publishes, Normal Chat independently reviews the source diff. If PASS, the User builds both Release twins locally, deploys the diagnostic DLL, and repeats the established Sprint fixture.

Expected marked Sprint validation pattern:

```text
Family=SPRINT
RAW8_FIST_OWNERSHIP initial close once per C1
G3AB_COL_FIST Result=ACCEPTED
Action=9 Phase=1 StatePosition=1
Latch=1->0
existing timing permission when required
native damage remains Game.dll+0x16E348
no equipped Sprint behavior or lifecycle regression
```

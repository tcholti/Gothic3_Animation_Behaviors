# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-04

Immediate transient handoff: `docs/BETWEEN_CHATS.md`  
Project charter / highest Gothic-specific authority: `docs/README.md`  
Project collaboration/CAM operationalization: `docs/COLLABORATION_RULES.md`  
Stable conventions: `docs/PROJECT_PIPELINE.md`  
Recurring procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`  
Knowledge ownership: `docs/KNOWLEDGE_MAINTENANCE.md` / `docs/KNOWLEDGE_REGISTRY.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`

Local workstation/build/runtime paths: `docs/LOCAL_WORKSTATION_PATHS.md` (retrieve only when deployment paths matter)

---

## Authority Boundary

CAM is the constitutional collaboration layer above this project. `docs/README.md` is the highest project-specific authority immediately beneath CAM.

```text
CAM
-> Gothic project charter
-> specialist Gothic authorities
-> procedures / bounded protocols
-> exact task execution
```

Do not modify the Collaborative-Agency-Model repository from Gothic 3 project work.

---

## Mandatory Release-Purity Rule

> **Every released Gothic 3 behavior DLL contains behavior only. Research diagnostics are a separate build product and are not compiled into the release binary.**

Never normally load behavior-only and diagnostic collision twins together.

Release/product details: `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` for the exact active responsibility.
3. Treat CAM -> project charter -> specialist authority and release purity as standing constraints.
4. Reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md` plus the owning subsystem authority when substantial reasoning requires it.
5. Retrieve `PROJECT_PIPELINE.md` before changing branch/test/evidence/procedure/version/artifact conventions.
6. Do not scan the whole repository or reconstruct the project from old chat history.
7. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.
8. If the previous Normal Chat failed or hit maximum context, apply POP-11 before trusting stale current-state wording.

After bootstrap, report briefly:

```text
current responsibility
closed boundary relevant to it
exact immediate next step
what remains deliberately outside current responsibility
```

---

## Closed Collision Architecture Boundary

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
Gate 1 source/build separation             CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency         CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke                 CLOSED/PASS — EV-212
Gate 4 generation-scoped bookkeeping       CLOSED/PASS — EV-213
literal historical EV-131 regression       CLOSED/PASS — EV-214
final behavior-only architecture smoke     CLOSED/PASS — EV-215
NEW COLLISION ARCHITECTURE VERIFICATION    COMPLETE
```

Do not reopen this architecture without concrete contradicting evidence.

---

## Repository Boundary

```text
main
= stable integration + reusable stable Gothic 3 knowledge baseline

docs/collision-source-evidence
= sole active collision development/research branch through completed collision behavior,
  production collision migration and collision validation
```

Accepted phase transition:

```text
complete collision on docs/collision-source-evidence
-> migrate mature collision behavior into Script_G3AnimationBehaviors
-> validate diagnostics-free collision integration
-> promote completed collision checkpoint to main
-> create feature/raise-attack-speed from updated main
```

Do not create `feature/raise-attack-speed` early.

---

## Current Equipped-Melee Expansion State

Remaining-melee implementation baseline:

`f0d929c90fbe086f44f66f91a2523904d06c3903`

Generic before/after-marker StatePosition diagnostics:

`7c31784c5ef86bc79b54d573144b8e40f33e5e6b`

Current family status:

```text
PowerAttack   CLOSED/PASS for current marker-expansion stage
PierceAttack  CLOSED/PASS for current marker-expansion stage
SimpleWhirl   CLOSED/PASS for current marker-expansion stage
HackAttack    implementation present; callback identity CLOSED; isolated validation NEXT
```

`GetUpAttack` is not part of the planned marker roadmap. True `FinishingAttack` action 15 remains deliberately native/unmarked. Fist/body remains a separate later source-adapter responsibility.

---

## SimpleWhirl Closure

Closed retrieval checkpoint:

`research/derived/2026-09-04_simplewhirl_stateposition_and_target_semantics_closure.md`

Established result:

```text
Action 6 / _AI_SimpleWhirl ownership works
RIGHT / LEFT / BOTH / OFF physical source mechanics work
BOTH activates/rearms both exact Dual equipped weapon sources
both swords can connect against the selected target
native cleanup / C1 generation / occurrence protection remain healthy
```

Matched-motion testing showed SimpleWhirl remains substantially more target-directed than true PowerAttack even when the physical source program succeeds.

A temporary one-variable causal probe changed only:

```text
SimpleWhirl StatePosition 1 -> 2
```

Implementation:

`a48449fcd9e2514a6d1c1f9943eb04004a5778f3`

Runtime result:

`research/raw/2026-09-04_simplewhirl_stateposition2_causal_probe.log`  
commit `ed40a6d901efc4bb30800e170bc850857d8f6dda`

The logger confirmed StatePosition 2 was active, but gameplay remained substantially target-directed. Therefore StatePosition 2 is rejected as a sufficient explanation/normalization for the SimpleWhirl-vs-Power actor-hit difference.

The temporary probe was reverted at:

`9120ca32466b257722a4fe553f64063f331249b4`

Final accepted bookkeeping:

```text
SimpleWhirl -> StatePosition 1
```

Final native regression:

`research/raw/2026-09-04_simplewhirl_native_stateposition1_final_regression.log`  
commit `003c4c5c4baaa72401f6743c408f14db476b8887`

The User again confirmed both swords could connect against the selected target. Non-selected actors could also sometimes be damaged. The repeated observation was that those secondary actors were roughly beside/in front of the selected target or between Hero and the selected target. This is preserved only as a qualified spatial observation; no exact cone/corridor/native rule is claimed.

Current framework decision:

```text
G3AB SimpleWhirl markers
= authored physical source timing/set/rearm

Gothic SimpleWhirl semantics
= preserve the native substantially target-directed actor-hit eligibility
```

The cost/reward decision is to stop deeper Action-6 eligibility reverse engineering in the current collision scope. Future deliberate target-acquisition/action-specific-hit-semantics work may reopen the question from the closure checkpoint without reopening the proven physical marker/source layer.

---

## Current Responsibility — HackAttack Isolated Marker / Optional Routing Validation

EV-216 closes the callback identity for the tested runtime build:

```text
Script_Game +0x433D0
= OnAI_HackAttack
= .\Script\AI\AI_Commands\AI_HackAttack.cpp
```

Hack bookkeeping currently implemented:

```text
Hack -> StatePosition 1
```

Optional Hack animation routing is already implemented and must now be validated rather than redesigned.

Accepted routing contract:

```text
runtime action == HackAttack (14)
-> preserve the resource name/namespace produced by the active resolver
-> at the narrow CombatMove motion-resource query, derive only
   _FinishingAttack_ -> _HackAttack_
-> matching Hack asset exists: use it
-> matching Hack asset absent: preserve untouched original FinishingAttack resource/path

runtime action == FinishingAttack (15)
-> untouched native path
```

Preserve namespaces produced by native Gothic or compatible resolvers such as Jackydima `Script_Animation`; do not normalize Axe/other namespaces into G3AB guesses.

Exact current Hack test continuation: `docs/BETWEEN_CHATS.md`.

---

## Exact Immediate Next Step

Run only the isolated Hack validation defined in `docs/BETWEEN_CHATS.md`:

```text
fallback control
-> dedicated Hack positive with one simple marked fixture
-> true FinishingAttack negative
```

The positive must establish:

```text
runtime Action 14 / OnAI_HackAttack remains Hack
matching dedicated Hack resource is selected
Family HACK owns the reserved marker in the exact Hit
accepted source marker leaves StatePosition 1
exact equipped source activation/rearm/cleanup remains healthy
```

Do not broaden into every weapon type or compatibility stack before this isolated result.

After Hack closes:

```text
combined remaining-melee marker/lifecycle regression
```

Do not reopen Power, Pierce, SimpleWhirl, C1 lifecycle architecture or Gate-4 execution identity during Hack validation.

---

## Later Separate Responsibilities

Remain outside current Hack validation:

- Fist/body source adapter;
- full marker/lifecycle regression after remaining equipped-melee closure;
- AttackContinuationProtection / bad-skip prevention;
- mature collision compatibility gate;
- production collision migration into `Script_G3AnimationBehaviors`;
- Raise / speed / configuration work on the later branch;
- target acquisition;
- climbing.

First public release still requires the mature diagnostics-free framework with collision + AttackContinuationProtection + Raise + redesigned speed/config + required compatibility/regression. Release 1 animation content remains intentionally 2H only.

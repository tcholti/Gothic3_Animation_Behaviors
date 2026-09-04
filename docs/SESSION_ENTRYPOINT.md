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

## Authority / Release Boundary

CAM is the constitutional collaboration layer above this project. `docs/README.md` is the highest project-specific authority immediately beneath CAM.

> **Every released Gothic 3 behavior DLL contains behavior only. Research diagnostics are a separate build product and are not compiled into the release binary.**

Never normally load behavior-only and diagnostic collision twins together.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` for the exact active responsibility.
3. Treat CAM -> project charter -> specialist authority and release purity as standing constraints.
4. Reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md` plus the owning subsystem authority when substantial reasoning requires it.
5. Retrieve `PROJECT_PIPELINE.md` before changing branch/test/evidence/procedure/version/artifact conventions.
6. Do not scan the whole repository or reconstruct the project from old chat history.
7. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.

After bootstrap, report briefly: current responsibility, relevant closed boundary, exact next step, and what remains deliberately outside scope.

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

## Repository / Phase Boundary

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

```text
PowerAttack   CLOSED/PASS for current marker-expansion stage
PierceAttack  CLOSED/PASS for current marker-expansion stage
SimpleWhirl   CLOSED/PASS for current marker-expansion stage
HackAttack    isolated routing/source/marker validation PASS; final compatibility regression remains
```

`GetUpAttack` is not part of the planned marker roadmap. True `FinishingAttack` action 15 remains deliberately native/unmarked. Fist/body remains a separate later source-adapter responsibility.

SimpleWhirl target-semantics closure remains at:

`research/derived/2026-09-04_simplewhirl_stateposition_and_target_semantics_closure.md`

Do not reopen its proven physical source layer during final regression.

---

## HackAttack Accepted State

Latest Hack runtime evidence is committed through:

`ec36039df8cafa5f17658d4307fa1c109d82cce0` — `Record Hack Staff and marker validation`

Established current behavior:

```text
Action 14 / _AI_HackAttack callback identity           PASS
2H missing Hack asset -> FinishingAttack fallback      PASS
Staff missing Hack asset -> FinishingAttack fallback   PASS
2H dedicated Hack asset override                       PASS
Staff dedicated Hack asset override                    PASS
2H authored distance override                          PASS
Hack marker StatePosition                              1
RIGHT                                                   PASS
OFF                                                     PASS
RIGHT -> OFF -> RIGHT                                   PASS
OFF before first RIGHT -> delayed RIGHT                PASS
single RIGHT -> natural terminal cleanup               PASS
2H right equipped source                               PASS
Staff right equipped source                            PASS
```

The routing implementation is intentionally action-gated and weapon-family agnostic. It preserves the animation namespace produced by the active Gothic/installed resolver and changes only the Hack-vs-Finishing action token at the narrow CombatMove motion-resource query. Do not add Hero/2H/Staff/Axe gates.

Jackydima `Script_Animation` is an important reference for this contract: its `GetAniName` reconstruction builds the lookup identity only through the `_00_` prefix and can provide custom namespaces such as `Axe`; destination pose, distance and later suffix data belong to the resolved animation resource. The documentation/retrieval route for this fact must be repaired during final collision knowledge maintenance; do not redesign working Hack code because the older handoff wording was incomplete.

### 2H Hack pose-chain caveat

The tested complete 2H Hack sequence is:

```text
Hero_Parade_None_2H_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_2H_P0_HackAttack_Hit_N_Fwd_00_%_00_P1_100.xmot
Hero_Parade_None_2H_P1_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot
```

The numeric Hit distance is author-controlled: a `...P0_200.xmot` dedicated Hack Hit was selected successfully. However, changing the 2H Hit destination from native-like `P1` to `P0` prevented the expected Recover continuation; restoring `P1` and the matching P1-source Recover restored the full sequence, including with New Balance present. Exact native reason is unknown and deliberately out of scope. Preserve the native 2H pose progression rather than creating a new engine-behavior responsibility.

The tested Staff Hack sequence remains the native-like all-P0 family:

```text
Hero_Parade_None_Staff_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_Staff_P0_HackAttack_Hit_N_Fwd_00_%_00_P0_100.xmot
Hero_Parade_None_Staff_P0_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot
```

---

## Current Responsibility — Final Collision Regression / Compatibility Closure

Run **two final strong mixed regressions**, not new architecture research.

### A. Native-control mixed regression

Environment:

```text
current G3AB diagnostic collision DLL
+ current authored test fixtures
+ no New Balance
+ no Script_AttackCollision
```

Exercise a practical mixture of:

- different supported melee weapon families;
- marked and unmarked attacks;
- repeated attacks and ordinary transitions;
- interruption attempts;
- Hack dedicated override and Hack fallback where practical;
- true FinishingAttack Action 15 if convenient as a negative/unmarked control.

Goal: no crash, no stuck weapon collision, expected contacts, unmarked/native paths untouched, marker source/lifecycle behavior remains healthy.

### B. New Balance + Script_AttackCollision compatibility regression

Repeat a similarly strong mixed run with:

```text
current G3AB diagnostic collision DLL
+ New Balance
+ Script_AttackCollision
```

This is the final collision compatibility checkpoint. New Balance compatibility is an explicit project criterion. Existing earlier compatibility evidence remains relevant, but this final run should exercise the mature current collision implementation strongly enough that later Raise/speed work can treat collision compatibility as a closed baseline unless contradictory evidence appears.

Do not confuse this with playback-speed compatibility: the current upstream speed-control hook is already known to conflict with New Balance and must be redesigned later on the Raise/speed branch.

---

## After Both Final Runs Pass

Perform one bounded collision knowledge-maintenance/closure transaction:

```text
interpret both final logs
-> record canonical evidence
-> repair Hack animation/fallback lookup ownership routes in docs/indexes
-> update current design/test status
-> archive fully processed Power/Pierce/SimpleWhirl/Hack raw evidence with paths updated
-> close equipped-weapon collision implementation
```

Then continue the existing phase transition toward production `Script_G3AnimationBehaviors` collision integration. Raise and playback-speed implementation remain later work after the collision checkpoint is mature/promoted as planned.

---

## Deliberately Outside the Next Two Tests

- new collision architecture changes without contradictory evidence;
- deeper 2H Hack pose-chain reverse engineering;
- Fist/body source adapter;
- AttackContinuationProtection unless the final regression exposes a concrete contradiction;
- Raise implementation;
- speed-hook redesign;
- target acquisition;
- climbing.

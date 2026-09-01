# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-02

Immediate transient handoff when needed: `docs/BETWEEN_CHATS.md`  
Project charter / highest Gothic-specific authority / retrieval map: `docs/README.md`  
Project collaboration/CAM operationalization: `docs/COLLABORATION_RULES.md`  
Stable conventions: `docs/PROJECT_PIPELINE.md`  
Recurring local + formal review/audit procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`  
Knowledge maintenance/ownership: `docs/KNOWLEDGE_MAINTENANCE.md` / `docs/KNOWLEDGE_REGISTRY.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`

---

## Authority Boundary

CAM is the constitutional collaboration layer above this project. `docs/README.md` is the **highest project-specific authority immediately beneath CAM** for the project's purpose, long-term direction, scope and authority topology. `COLLABORATION_RULES.md` owns how CAM/project principles are operationalized for participant allocation and collaboration inside Gothic 3.

```text
CAM constitutional collaboration principles
→ Gothic project charter (`docs/README.md`)
→ specialist Gothic authorities within delegated domains
→ procedures / bounded protocols
→ exact task execution
```

Specialist authorities are not all linearly ranked; each owns its delegated domain beneath the charter.

Ordinary Gothic engineering should use the lowest relevant Gothic authority rather than rereading CAM or the full charter by default.

A **formal project review/audit** must instead apply POP-10: establish the charter hierarchy and each target's intended responsibility before judging content, contradiction, duplication or cleanup.

> **Do not modify the Collaborative-Agency-Model repository from Gothic 3 project work.** Any CAM evolution requires a separate User-authorized CAM-focused responsibility; adopted CAM changes are then deliberately operationalized back into this project.

---

## Mandatory Release-Purity Rule

> **Every released Gothic 3 behavior DLL contains behavior only. Research diagnostics are a separate build product and are not compiled into the release binary.**

Never normally load behavior-only and diagnostic twins together.

Release/product details live in `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` only when it contains an active transient responsibility.
3. Treat the CAM → project charter → specialist authority hierarchy and the release-purity rule above as standing constraints.
4. If the current responsibility is a **formal review/audit**, apply POP-10 in `docs/PROJECT_OPERATING_PROCEDURES.md` before evaluating the target. Read/confirm `docs/README.md` §0 and each target's intended Purpose/Scope/owner first. The review has not started until that preflight is satisfied.
5. If the active technical subsystem is not already oriented, use the one-time Subsystem Orientation Pass from `docs/README.md`.
6. If substantial reasoning will reinterpret evidence or propose a new fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md` plus the owning subsystem authority.
7. Read other `docs/PROJECT_OPERATING_PROCEDURES.md` sections only when entering their relevant local Git/build/deploy/runtime-artifact sequences.
8. Retrieve the relevant `docs/PROJECT_PIPELINE.md` section before changing gate/test/evidence/procedure IDs, artifact naming, build labels, branch meanings or validation-flow conventions.
9. Do not scan the whole repository or reconstruct the project from old chat history.
10. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.
11. Do not modify CAM from this project responsibility.

After bootstrap, report briefly:

```text
current responsibility
closed boundary relevant to it
exact immediate next step
what remains deliberately deferred
```

For a formal review/audit, also state the compact POP-10 preflight hierarchy and intended use of the major targets before findings.

---

## Closed Collision Architecture Boundary

```text
C1-R1 lifecycle safety                     CLOSED — EV-206–EV-207
Gate 1 source/build separation             CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency         CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke                 CLOSED/PASS — EV-212
Gate 4 generation-scoped bookkeeping       CLOSED/PASS — EV-213
Literal historical EV-131 regression       CLOSED/PASS — EV-214
Final behavior-only architecture smoke     CLOSED/PASS — EV-215
NEW COLLISION ARCHITECTURE VERIFICATION    COMPLETE
```

Do not reopen this architecture without concrete contradicting evidence. Technical semantics live in `DESIGN.md` and the collision authorities; proof lives behind `EVIDENCE_INDEX.md`.

---

## Repository Boundary

```text
main
= stable integration + reusable stable Gothic 3 knowledge baseline

docs/collision-source-evidence
= active collision development/research
= remains the sole active feature branch through completed collision behavior,
  production collision migration and collision validation
```

The stabilized governance/planning checkpoint is kept aligned with protected `main` before new collision implementation resumes. After that checkpoint, collision development may advance on `docs/collision-source-evidence` while `main` remains the stable baseline until the completed collision responsibility is deliberately promoted.

Accepted phase transition:

```text
complete collision on docs/collision-source-evidence
→ migrate mature collision behavior into Script_G3AnimationBehaviors
→ validate diagnostics-free collision integration
→ promote completed collision checkpoint to main
→ create feature/raise-attack-speed from that newly updated main
```

Do **not** create `feature/raise-attack-speed` early.

Known unrelated local file remains outside project maintenance and must stay untouched:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Project Stabilization — COMPLETE

```text
Pass 1 structural document/tool simplification   PASS
Pass 2 Gothic rules/procedures consistency       PASS
Pass 3 build/product/repository-shape audit      PASS
Pass 4 final fresh-context/readiness check       PASS
stable main promotion                            PASS
```

Stable product/tool model:

```text
Script_G3AnimationBehaviors
= production-direction behavior DLL; current Raise/speed implementation

Script_FrameCollisionBehaviorTest
= diagnostics-free collision behavior research twin

Script_FrameCollisionTest
= same collision behavior + diagnostic instrumentation

Script_CombatMoveLogger
= independent generic CombatMove / playback-speed diagnostic tool

tools/log_evidence
= offline deterministic large-log processor
```

The cleanup found no remaining structural ambiguity that should delay engineering. Do not start another documentation cleanup merely for stylistic uniformity.

---

## CURRENT RESPONSIBILITY — Finalize Remaining Equipped-Melee Marker Architecture

Return to engineering, but **do not modify behavior code yet**.

Required marker expansion is now:

```text
PowerAttack
PierceAttack
SimpleWhirl
HackAttack
```

`GetUpAttack` is now **deferred** rather than part of the immediate batch: it can perform legitimate offense before later CombatMove and its native callback also changes `AniState` to `Stand`, so suppressing it would cross into non-collision semantics.

`FinishingAttack` remains deliberately excluded and native. Fist/body remains a separate later source-adapter investigation.

Accepted implementation/validation strategy:

```text
finish the last two narrow Hack facts
→ freeze exact shared adapter architecture with User
→ implement Power + Pierce + SimpleWhirl + Hack in one bounded code change
→ validate Power independently
→ validate Pierce independently
→ validate SimpleWhirl independently
→ validate Hack independently
→ run combined marker/lifecycle regression afterward
```

Required planning boundaries:

```text
preserve closed C1 lifecycle/generation architecture
preserve RIGHT / LEFT / BOTH / OFF semantics
preserve native fallback for unmarked/unsupported cases
separate physical source selection from action/family identity
use one canonical family/action eligibility policy rather than multiplying marker-core special cases
complete only the native callback bookkeeping needed to prevent competing timed activation
keep Fist/body source adaptation separate
keep AttackContinuationProtection separate
```

### Current callback/bookkeeping classification

```text
Pierce
→ one-stage native collision callback
→ StatePosition 1

SimpleWhirl
→ one-stage native collision callback
→ StatePosition 1

Hack
→ native callback-shaped routine at Script_Game +0x433D0 performs Item_Attack(7), triggered-list clearing and StatePosition 1
→ exact registered callback name/entry still needs confirmation

Power
→ native two-stage collision callback
→ ordinary/non-Dual marker-owned completion at StatePosition 1
→ Dual 1H+1H marker-owned completion at StatePosition 2 so all competing native collision/rearm timing is consumed
```

Repeated Power contacts remain authored through the existing marker vocabulary and `ClearTriggeredList()` rearm; do not rebuild Power as a separate marker engine.

### HackAttack optional animation routing

Known runtime/static facts:

```text
gEAction_HackAttack       = 14
gEAction_FinishingAttack  = 15

gCScriptProcessingUnit::GetAniName
= Game +0x16F840
= receives native gEAction

Game +0x16FA16
→ indexes action-string table at Game +0x3F75C0
→ serializes the action token used in the animation name
```

This explains why simply adding `_HackAttack_` files did not make the tested game select them: runtime Hack currently serializes the shared `FinishingAttack` action family.

Preferred Hack fixture names remain:

```text
Hero_Parade_None_2H_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_2H_P0_HackAttack_Hit_N_Fwd_00_%_00_P0_100.xmot
Hero_Parade_None_2H_P0_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot

Hero_Parade_None_Staff_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_Staff_P0_HackAttack_Hit_N_Fwd_00_%_00_P0_100.xmot
Hero_Parade_None_Staff_P0_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot
```

`100` remains animation-author metadata, not a DLL constant. Gothic keeps ownership of destination pose, movement distance and the rest of its filename contract.

The accepted feature behavior is now **optional override with fallback**:

```text
runtime action == HackAttack
+ active/native animation resolver produces the ordinary serialized name
→ derive only the corresponding HackAttack action-token variant
→ if matching HackAttack asset exists: use it
→ if it does not exist: preserve the original FinishingAttack name/path unchanged
```

Therefore G3AB must work normally with **no custom Hack assets**. Dedicated Hack assets are optional content discovered/used only when present.

### Jackydima Script_Animation compatibility requirement

`Jackydima/Script_Animation` is now a relevant compatibility reference.

It hooks `GetAniName` at `Game +0x16F840`, rebuilds animation names, and globally changes the UseType→string table at `Game +0x2BAC98` so normally shared weapon types can acquire namespaces such as `Axe`. It uses the same action-string table at `Game +0x3F75C0` identified independently by this project.

G3AB must not assume exclusive ownership of that hook or undo the resulting animation namespace.

Required compatibility behavior:

```text
preserve whatever serialized actor/weapon/pose/phase/direction/etc. name the active resolver already produced
→ modify only the exact FinishingAttack→HackAttack action token for factual runtime Hack
→ only when the matching optional Hack asset is valid/present
```

Do not globally patch action 14's action-string-table entry: the stock inventory has no native HackAttack assets, while FinishingAttack assets exist across multiple Hero/Orc weapon families, so a global replacement would be too broad.

Do not choose the New Balance `Game +0x16B065` interception merely because it is known; New Balance compatibility also remains required.

### Exact immediate next step

Only two narrow factual questions remain before Work:

```text
1. Resolve the registered AI-callback identity/name corresponding to Script_Game +0x433D0.

2. Find the narrowest safe result-level/post-name-construction Hack override path plus exact-animation existence/preflight mechanism that:
   - does not require exclusive ownership of GetAniName,
   - preserves namespaces produced by native Gothic or Script_Animation,
   - falls back to the untouched FinishingAttack name when no matching Hack asset exists.
```

After those are answered:

```text
freeze exact multi-family implementation architecture with User
→ only then create the bounded Work responsibility
```

---

## Forward Order

```text
remaining equipped-melee architecture review
→ one bounded Power/Pierce/SimpleWhirl/Hack implementation
→ family-by-family validation
→ separate Fist source-adapter investigation
→ full marker/lifecycle regression
→ AttackContinuationProtection
→ combined collision regression
→ mature research-collision compatibility gate
→ migrate mature collision behavior into Script_G3AnimationBehaviors on the collision branch
→ diagnostics-free collision integration + compatibility validation
→ promote completed collision checkpoint to main
→ create feature/raise-attack-speed from updated main
→ Raise + general/action/profile attack-speed + config redesign/migration
→ final assembled-behavior compatibility/regression
→ promote mature Raise/speed checkpoint to main
→ later target acquisition/climbing
→ retain separate diagnostic twins/tools
```
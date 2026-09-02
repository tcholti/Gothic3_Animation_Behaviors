# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-02

Immediate transient handoff: `docs/BETWEEN_CHATS.md`  
Project charter / highest Gothic-specific authority: `docs/README.md`  
Project collaboration/CAM operationalization: `docs/COLLABORATION_RULES.md`  
Stable conventions: `docs/PROJECT_PIPELINE.md`  
Recurring procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`  
Knowledge ownership: `docs/KNOWLEDGE_MAINTENANCE.md` / `docs/KNOWLEDGE_REGISTRY.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`

---

## Authority Boundary

CAM is the constitutional collaboration layer above this project. `docs/README.md` is the **highest project-specific authority immediately beneath CAM**.

```text
CAM
→ Gothic project charter (`docs/README.md`)
→ specialist Gothic authorities within delegated domains
→ procedures / bounded protocols
→ exact task execution
```

Specialist authorities are not all linearly ranked; each owns its delegated domain beneath the charter.

A formal project review/audit must apply POP-10 before judging content, contradiction, duplication or cleanup.

> **Do not modify the Collaborative-Agency-Model repository from Gothic 3 project work.**

---

## Mandatory Release-Purity Rule

> **Every released Gothic 3 behavior DLL contains behavior only. Research diagnostics are a separate build product and are not compiled into the release binary.**

Never normally load behavior-only and diagnostic twins together.

Release/product details live in `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` when it contains an active transient responsibility.
3. Treat CAM → project charter → specialist authority and release purity as standing constraints.
4. For a formal review/audit, apply POP-10 before evaluating targets.
5. If the active technical subsystem is not already oriented, use the one-time Subsystem Orientation Pass from `docs/README.md`.
6. Reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md` plus the owning subsystem authority when substantial reasoning requires it.
7. Retrieve `PROJECT_PIPELINE.md` before changing branch/test/evidence/procedure/version/artifact conventions.
8. Do not scan the whole repository or reconstruct the project from old chat history.
9. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.
10. Do not modify CAM from this project responsibility.

After bootstrap, report briefly:

```text
current responsibility
closed boundary relevant to it
exact immediate next step
what remains deliberately outside the current responsibility
```

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
→ migrate mature collision behavior into Script_G3AnimationBehaviors
→ validate diagnostics-free collision integration
→ promote completed collision checkpoint to main
→ create feature/raise-attack-speed from that updated main
```

Do **not** create `feature/raise-attack-speed` early.

Known unrelated local file remains outside project maintenance and must stay untouched:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## CURRENT RESPONSIBILITY — Finalize Remaining Equipped-Melee Marker Architecture

Do not modify behavior code until the exact bounded implementation responsibility is frozen.

Required marker expansion:

```text
PowerAttack
PierceAttack
SimpleWhirl
HackAttack
```

`GetUpAttack` is **not part of the planned development roadmap**. Current review found materially different behavior: legitimate offense can occur before later CombatMove and its native callback also changes `AniState` to `Stand`. Do not spend further marker-engineering time on it absent a future concrete requirement.

`FinishingAttack` remains deliberately excluded/native. Fist/body remains a separate source-adapter responsibility.

Accepted implementation/validation strategy:

```text
finish exact Hack facts
→ freeze shared adapter architecture with User
→ implement Power + Pierce + SimpleWhirl + Hack in one bounded code change
→ validate each family independently
→ combined marker/lifecycle regression
```

Current bookkeeping classification:

```text
Pierce       → StatePosition 1
SimpleWhirl  → StatePosition 1
Hack         → callback-shaped routine at Script_Game +0x433D0 ends at StatePosition 1
Power normal → StatePosition 1
Power Dual   → StatePosition 2
```

One Hack collision fact still needs exact proof: the registered AI callback identity/name corresponding to `Script_Game +0x433D0`.

---

## HackAttack Optional Animation Routing

Dedicated Hack animations are **optional overrides**, not a dependency.

Required behavior:

```text
runtime action == HackAttack
→ preserve the serialized name/namespace produced by the active resolver
→ derive only the matching HackAttack action-token variant
→ matching Hack asset exists: use it
→ matching Hack asset absent: preserve original FinishingAttack resource/path unchanged
```

True runtime `FinishingAttack` action 15 stays native/unmarked.

Preferred authored 2H/Staff Hack names are recorded in `BETWEEN_CHATS.md`. Their pose/distance suffixes remain animation-author/engine metadata; the DLL must not recreate those semantics.

Static review now identifies the current preferred compatibility direction:

```text
GetAniName builds the final name
→ New Balance may modify the CombatMove animation string around Game +0x16B065
→ CombatMove queries the motion resource at Game +0x16B10C
```

Gothic's normal loader uses `IsAnimationMissed`, `QueryMotionDataEntity` and `AddMissingAnimation`, then uses the returned resource's filename and installs the returned resource through `SetMotion`. The SDK hook substrate supports callsite interposition.

Therefore prefer a **narrow CombatMove resource-query adapter** over exclusive ownership of `GetAniName` or a global action-string-table patch. Preserve namespaces created by native Gothic or Jackydima `Script_Animation` (for example `Axe`) and change only the action token when the exact optional Hack asset resolves. This remains to be implemented/runtime-validated.

---

## AttackContinuationProtection Goal

```text
prevent the known destructive continuation/bad-skip mechanism
from terminating or advancing through a legitimately live Hit execution
```

The required outcome is frozen; the exact mechanism is not. Current preferred research direction is to identify and, if appropriate, freeze/suppress the responsible timer/continuation trigger while Hit remains authoritatively alive. Prefer a cleaner native operation if research exposes one.

Keep this responsibility separate from `CollisionLifecycleGuard`; retain C1-R1 underneath as the general lost-cleanup fail-safe.

---

## First Public Release Boundary

The first public Animation Behaviors release is planned after the diagnostics-free framework contains and validates:

```text
general marker/collision framework
+ AttackContinuationProtection / bad-skip prevention
+ Raise framework
+ general/action/profile attack-speed + configuration framework
+ required assembled compatibility/regression
```

**Release 1 animation content is intentionally 2H only.** The framework does not wait for every weapon family to have finished replacement animations.

The 2H set is the first complete reference implementation. Release communication/video should explain how other animators/modders can use markers, Raise assets and speed configuration.

After Release 1, animation content is updated and released weapon family by weapon family. During that longer authoring period, climbing may be revisited sporadically; target-acquisition changes remain independent future work. Other animation-system fixes (for example enabling more specific jump animations when valid assets exist) should be investigated one at a time as concrete useful cases appear.

---

## Exact Immediate Next Step

Without the Gothic PC, static planning/source work can continue. The first fact likely requiring the game installation is the exact registered callback identity for `Script_Game +0x433D0`.

Then:

```text
freeze exact Power/Pierce/SimpleWhirl/Hack adapter + Hack optional-routing architecture with User
→ create one bounded Work implementation responsibility
→ build/deploy/test when the Gothic PC is available
```

Detailed current reasoning, the Sprint fallback observation, Hack fixture names and compatibility notes are in `docs/BETWEEN_CHATS.md`.

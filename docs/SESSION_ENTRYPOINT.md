# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-03

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

CAM is the constitutional collaboration layer above this project. `docs/README.md` is the **highest project-specific authority immediately beneath CAM**.

```text
CAM
→ Gothic project charter (`docs/README.md`)
→ specialist Gothic authorities within delegated domains
→ procedures / bounded protocols
→ exact task execution
```

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
2. Read `docs/BETWEEN_CHATS.md` for the active transient responsibility.
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

### If the previous Normal Chat failed or hit maximum context

Do **not** assume the current `NEXT` text below is still accurate merely because this file was the last maintained front door. Apply POP-11 interrupted-context recovery first.

Emergency starter:

```text
RECOVERY START
Read SESSION_ENTRYPOINT first, but treat its current responsibility as potentially stale.
Apply PROJECT_OPERATING_PROCEDURES POP-11.
Compare only the recent durability gap against the newest branch commits/raw evidence and any supplied previous-chat transcript.
Complete any missed KNOWLEDGE_MAINTENANCE transaction and correct SESSION_ENTRYPOINT/BETWEEN_CHATS before resuming technical work.
Do not scan the whole repository.
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

---

## CURRENT RESPONSIBILITY — Complete Remaining Equipped-Melee Marker Validation

Implemented batch baseline:

```text
f0d929c90fbe086f44f66f91a2523904d06c3903
```

Generic before/after-marker StatePosition diagnostics:

```text
7c31784c5ef86bc79b54d573144b8e40f33e5e6b
```

Required marker expansion:

```text
PowerAttack
PierceAttack
SimpleWhirl
HackAttack
```

Current status:

```text
PowerAttack   CLOSED/PASS for current marker-expansion stage
PierceAttack  CLOSED/PASS for current marker-expansion stage
SimpleWhirl   NEXT — isolated runtime validation
HackAttack    implementation complete; isolated marker/routing validation pending
combined marker/lifecycle regression pending afterward
```

Compact Power/Pierce evidence retrieval checkpoint:

`research/derived/2026-09-03_power_pierce_marker_validation_checkpoint.md`

Current bookkeeping classification:

```text
Pierce       → StatePosition 1
SimpleWhirl  → StatePosition 1
Hack         → OnAI_HackAttack → StatePosition 1
Power normal → StatePosition 1
Power Dual   → StatePosition 2
```

EV-216 closes the Hack callback identity for the tested runtime build: `Script_Game +0x433D0` has one unique registration-table match, `OnAI_HackAttack`, from `.\Script\AI\AI_Commands\AI_HackAttack.cpp`.

`GetUpAttack` is not part of the planned marker roadmap. `FinishingAttack` remains deliberately excluded/native. Fist/body remains a separate source-adapter responsibility.

---

## Pierce Closure Note

Pierce validation established that marker-authored RIGHT / LEFT / BOTH / OFF source behavior can be changed independently of stock Pierce motion content while runtime action remains Pierce and bookkeeping remains `StatePosition 1`.

User runtime observation additionally indicates that Pierce retains native focused-target/reaction semantics: copied Power motion content still produced the distinctive humanoid Pierce stumble on successful selected-target contacts, while nearby non-selected targets were not hit by the same Pierce swings in the observed multi-target test.

A repeated diagnostic cadence where a fresh `MARKER OWNERSHIP DECISION` appears once per distinct Pierce motion rather than once per execution remains unexplained. It also persists with New Balance bad-skip prevention active while all execution generations, marker budgets, physical source transitions and cleanup remain correct. Do not investigate further absent a concrete behavioral contradiction. A relationship to native Pierce target/effect semantics is plausible but unproven.

The tested Pierce configuration also passed with New Balance + Jackydima `Script_AttackCollision` active across 1H, Torch+1H, Shield+1H and both Dual Pierce sides. This is Pierce-specific compatibility evidence, not blanket certification of every AttackCollision callback family.

---

## HackAttack Optional Animation Routing

Dedicated Hack animations are optional overrides, not a dependency.

Implemented behavior:

```text
runtime action == HackAttack (14)
→ preserve the serialized name/namespace produced by the active resolver
→ at the narrow CombatMove motion-resource query callsite, derive only the matching _HackAttack_ token variant
→ matching Hack asset exists: use it
→ matching Hack asset absent: preserve original FinishingAttack resource/path unchanged
```

True runtime `FinishingAttack` action 15 stays native/unmarked.

Preserve namespaces created by native Gothic or compatible resolvers such as Jackydima `Script_Animation`; do not normalize Axe/other namespaces into G3AB guesses.

Exact preferred authored fixtures and routing notes remain in `docs/BETWEEN_CHATS.md`.

---

## AttackContinuationProtection Goal

```text
prevent the known destructive continuation/bad-skip mechanism
from terminating or advancing through a legitimately live Hit execution
```

The required outcome is frozen; the exact mechanism is not. Keep this responsibility separate from `CollisionLifecycleGuard`; retain C1-R1 underneath as the general lost-cleanup fail-safe.

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

After Release 1, animation content is updated and released weapon family by weapon family. Climbing may be revisited sporadically during that longer authoring period; target-acquisition changes remain independent future work.

---

## Exact Immediate Next Step

```text
NEXT SESSION:
inspect only the exact existing SimpleWhirl fixture/source evidence needed
→ freeze the isolated SimpleWhirl runtime test
→ validate SimpleWhirl
→ validate Hack
→ combined marker/lifecycle regression
```

Do not reopen Power or Pierce merely to broaden already-passing evidence or investigate benign diagnostic cadence.

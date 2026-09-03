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

## CURRENT RESPONSIBILITY — Resolve SimpleWhirl Character-Hit Semantics

Implemented remaining-melee batch baseline:

```text
f0d929c90fbe086f44f66f91a2523904d06c3903
```

Generic before/after-marker StatePosition diagnostics:

```text
7c31784c5ef86bc79b54d573144b8e40f33e5e6b
```

Current family status:

```text
PowerAttack   CLOSED/PASS for current marker-expansion stage
PierceAttack  CLOSED/PASS for current marker-expansion stage
SimpleWhirl   physical marker/source mechanics PASS
SimpleWhirl   native character-hit eligibility semantics OPEN
HackAttack    implementation complete; isolated marker/routing validation pending AFTER SimpleWhirl
combined marker/lifecycle regression pending afterward
```

Compact retrieval checkpoints:

```text
research/derived/2026-09-03_power_pierce_marker_validation_checkpoint.md
research/derived/2026-09-03_simplewhirl_validation_and_target_semantics_checkpoint.md
```

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

## SimpleWhirl Current Result

The current runtime evidence establishes the G3AB physical marker/source layer for SimpleWhirl:

```text
Action 6 / _AI_SimpleWhirl ownership works
accepted native-slot marker -> exact source activation/rearm
accepted BOTH -> both exact Dual sources 5 -> 7
StatePosition 0 -> 1 and remains 1 through later markers
BOTH -> single -> OFF -> BOTH exact-set behavior works
natural exact-source cleanup returns live sources 7 -> 5
no C1 terminal repair is required in healthy completion
```

However, User observation under matched animation content shows that SimpleWhirl does **not** have the same character-hit eligibility as true PowerAttack:

```text
same Power-derived Dual motion content
same authored physical source program

true PowerAttack -> broad actor contacts can damage actors touched by the swords
SimpleWhirl      -> substantially more target-directed, though not strictly selected-target-only
```

Therefore the current architecture distinction is:

```text
G3AB markers
= WHEN collision is offensive
+ WHICH equipped physical source set is offensive/rearmed

native/action-specific character-hit semantics
= which actor contacts are eligible to become character damage/effects
```

Do not claim `G3AB_COL_BOTH` currently guarantees uniform two-weapon character-hit eligibility across every action family. It guarantees the authored physical equipped-source set; the final framework-level actor-hit guarantee remains open.

The initial swapped-motion observation that appeared to show two swords damaging two separate actors in one SimpleWhirl execution was not reproduced on deliberate repetition and is **not confirmed evidence**.

The earlier SimpleWhirl crash is not the current causal gate. The crashing configuration had multiple collision twins/modules live; verified single-twin deployment did not reproduce it in the control run. Treat accidental co-loading as the strongest identified crash cause, but not a universally proven sole cause. Reopen only if a comparable crash recurs under verified single-twin deployment.

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

Temporary diagnostic causal control only:

```text
keep Action 6 / SimpleWhirl
keep OnAI_SimpleWhirl
keep the same Power-derived Dual motion fixture
keep the same BOTH -> single -> OFF -> BOTH markers
keep the same source activation/rearm behavior
keep the same target/group setup

change only accepted SimpleWhirl marker bookkeeping:
StatePosition 1 -> 2
```

Compare character-hit behavior against the already-observed true Dual Power / StatePosition-2 control.

```text
SimpleWhirl becomes Power-like
→ StatePosition participates in deeper native actor-hit eligibility
→ investigate the legitimate semantic rule from evidence

SimpleWhirl stays substantially target-directed
→ StatePosition is likely bookkeeping/suppression only
→ revert temporary change
→ trace Action 6 / SimpleWhirl-specific native eligibility instead
```

This is a falsification probe, **not** permission to redefine the permanent SimpleWhirl bookkeeping yet.

Do not proceed to Hack isolated runtime validation until this SimpleWhirl causal question is resolved enough to define the intended framework guarantee. Do not reopen Power or Pierce.

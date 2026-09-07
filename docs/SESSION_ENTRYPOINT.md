# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-07

> **WORK BUILD RULE:** Unless the current frozen task explicitly says that Work is authorized to build, Work must not invoke or probe build tooling/environment at all. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat.

Immediate transient handoff: `docs/BETWEEN_CHATS.md`  
Project charter / highest Gothic-specific authority: `docs/README.md`  
Project collaboration/CAM operationalization: `docs/COLLABORATION_RULES.md`  
Stable conventions: `docs/PROJECT_PIPELINE.md`  
Recurring procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`  
Knowledge ownership: `docs/KNOWLEDGE_MAINTENANCE.md` / `docs/KNOWLEDGE_REGISTRY.md`  
Evidence routing: `docs/EVIDENCE_INDEX.md`

Local workstation/build/runtime paths: `docs/LOCAL_WORKSTATION_PATHS.md` (retrieve only when deployment paths matter).

---

## Authority / Release Boundary

CAM is the constitutional collaboration layer above this project. `docs/README.md` is the highest project-specific authority immediately beneath CAM.

> **Every released Gothic 3 behavior DLL contains behavior only. Research diagnostics are a separate build product and are not compiled into the release binary.**

Never normally load behavior-only and diagnostic collision twins together.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Read `docs/BETWEEN_CHATS.md` for the exact active continuation.
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

Current equipped-melee expansion state:

```text
PowerAttack   CLOSED/PASS
PierceAttack  CLOSED/PASS
SimpleWhirl   CLOSED/PASS for current marker/semantic scope
HackAttack    CLOSED/PASS for isolated routing/source/marker scope
```

Human Fist shares only genuinely mechanism-neutral authored-marker infrastructure. It is **not** an equipped-weapon source adapter.

---

## Human raw-8 Fist — PRODUCTION CLOSED/PASS

Production implementation:

```text
dba34c6fbf36b6354186d1884faee5501ee4f261  Add production human Fist marker mechanism
17491d53d8a4209690fc2fa49a7b5c4c04b5b0cf  compile-only duplicate-local correction
```

Canonical production acceptance:

```text
research/raw/2026-09-07_fist_production_frame12_normal_power_acceptance.log
5de195c6c4571237fef5d841a7a8fe1b75c9cf78  evidence commit
```

Validated scope:

```text
exact human gEUseType_Fist / raw 8
Normal P0 marked Hit
Power P0 marked Hit
unmarked Fist remains native
multiple authored FIST opportunities
below-threshold authored timing permission
generation-scoped interruption safety
```

Current production semantics:

```text
UNMARKED HUMAN FIST
    -> completely native

MARKED HUMAN FIST EXECUTION
    -> exact marked execution becomes authored-Fist-owned
    -> once per factual C1 generation, SPU+0x164 is closed to 1
       before the first authored FIST opportunity

EACH ACCEPTED FIST
    -> SPU+0x164 = 0
    -> if real motion-0 play time is below the native threshold,
       arm one exact bounded Game+0x16E180 timing permission
    -> otherwise use real native timing

NATIVE GOTHIC PATH
    -> downstream target/contact/damage remains native
    -> successful opportunity writes SPU+0x164 = 1
    -> observed damage dispatch remains Game+0x16E348
```

The final frame-12 acceptance repeated three Power and three Normal executions. In all six, marker ownership confirmed latch `0 -> 1`; frame-12 `FIST` confirmed `1 -> 0`; real play time was already above the native threshold so no synthetic timing permission was armed; exactly six Hero raw-8 Fist `Game+0x16E348` damage events occurred, each after its corresponding authored marker and none before it. User visual result was 6/6: first swing NO damage, second swing YES damage.

Production human-Fist exclusions are now explicit:

```text
no authored FIST_OFF semantic
no Fist ClearTriggeredList operation
no Fist-specific weapon-style OnAI_Attack suppression
no equipped Item_Attack/Item_Equipped source window
no weapon C1 cleanup obligation
no custom Fist damage dispatch
no actual animation-clock mutation
no monster/raw55 PhysicalFist generalization
no dedicated Fist interruption repair
no speculative current-H2H bad-skip fix
```

Historical N1/N2/N3/N4/N5/N6/FIST_OFF experiments remain evidence, not current architecture. Route through `EVIDENCE_INDEX.md` rather than treating their old next-step wording as active.

---

## Current Responsibility

Human Fist research/production for the currently defined Normal + Power raw-8 scope is complete.

The next collision responsibility is:

> **Freeze and run the final native mixed collision regression against the mature current research behavior before the separate third-party compatibility gate.**

The purpose is regression confirmation, not reopening closed source/lifecycle/Fist mechanisms.

Protected during that regression:

```text
weapon RIGHT / LEFT / BOTH / OFF semantics
weapon repeated-contact ClearTriggeredList behavior
C1 generation-scoped marker identity
C1-R1 exact-source terminal repair
Power / Pierce / SimpleWhirl / Hack current closed behavior
human raw-8 FIST production semantics above
unmarked/native fallback
one-live-collision-twin deployment invariant
```

After the native mixed regression, the accepted branch sequence remains:

```text
final native mixed collision regression
-> final New Balance + Script_AttackCollision / relevant Jackydima mixed compatibility regression
-> collision knowledge/evidence closure
-> migrate mature collision behavior into Script_G3AnimationBehaviors
-> validate diagnostics-free collision integration
-> promote completed collision checkpoint to main
-> create feature/raise-attack-speed from updated main
```

Do not create `feature/raise-attack-speed` early.

---

## Deliberately Outside the Current Responsibility

- another human-Fist causal probe without contradicting evidence;
- authored `FIST_OFF` resurrection;
- human-Fist `ClearTriggeredList()` or weapon callback suppression;
- `gEUseType_PhysicalFist` / raw 55, monsters, generalized body collision or per-limb markers;
- a theoretical Fist bad-skip repair for moves the current H2H set cannot exercise;
- changing Power's native contact sensitivity merely because some native Power executions miss;
- equipped-weapon source/lifecycle redesign;
- C1-R1 or Gate-4 redesign;
- AttackContinuationProtection until its separate later responsibility becomes active;
- Raise/playback-speed implementation before collision branch completion;
- target acquisition;
- climbing.

Current exact continuation belongs in `docs/BETWEEN_CHATS.md`; exact proof belongs in `EVIDENCE_INDEX.md` and the canonical ledgers.

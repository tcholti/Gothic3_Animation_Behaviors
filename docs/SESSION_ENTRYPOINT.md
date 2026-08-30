# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work. Read this first; retrieve deeper knowledge only when the current responsibility requires it.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-08-30

`docs/collision-source-evidence` contains the newest research/prototype state. `main` is the stable integration baseline.

Immediate current handoff: `docs/BETWEEN_CHATS.md`  
Frozen architecture rewrite: `docs/SECOND_PASS_REWRITE_CONTRACT.md`  
Project-wide release/build rule: `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`  
Document routing: `docs/README.md`  
Stable workflow conventions: `docs/PROJECT_PIPELINE.md`  
Recurring local procedures: `docs/PROJECT_OPERATING_PROCEDURES.md`

---

## Mandatory Gothic 3 Release-Purity Rule

> **Every released Gothic 3 behavior DLL must contain behavior only. Research diagnostics are a separate build product and must not be compiled into the release binary.**

This is a project-wide architectural constraint for all present and future systems, including:

```text
frame-controlled collision
collision lifecycle repair
AttackContinuationProtection
Raise
playback speed
target acquisition
climbing
future animation/gameplay behavior modules
```

For the eventual public `Script_G3AnimationBehaviors.dll`:

```text
NO research diagnostic implementation
NO research logger/log strings
NO stack/RVA capture machinery used only for research
NO diagnostic-only state
NO diagnostic-only hooks
NO hidden runtime diagnostic mode compiled into release
NO production behavior dependency on diagnostics
```

Preferred long-term model:

```text
one shared behavior architecture
→ diagnostics-free RELEASE build
→ separate instrumented DIAGNOSTIC twin used in place of release for controlled testing
```

Do not load release and diagnostic twins together unless a future architecture explicitly proves safe coexistence.

Canonical authority: `docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.

---

## Fresh Normal Chat Bootstrap

1. Read this file first.
2. Treat the release-purity rule above as a standing constraint before proposing any Gothic 3 script/DLL architecture.
3. Read `docs/BETWEEN_CHATS.md` for the exact current responsibility and latest accepted boundary.
4. If the active subsystem is not already oriented in the current Chat, perform the one-time Subsystem Orientation Pass from `docs/README.md`.
5. If substantial reasoning will reinterpret evidence or propose a new fix, reconstruct only the active causal route from `docs/EVIDENCE_INDEX.md`.
6. Read `docs/PROJECT_OPERATING_PROCEDURES.md` once when entering a local Git/build/deploy/runtime-artifact sequence.
7. Before changing gate/test IDs, evidence/procedure IDs, artifact naming, prototype/build labels, branch meanings, or validation-flow conventions, retrieve the relevant `docs/PROJECT_PIPELINE.md` section.
8. Do not scan the whole repository or reconstruct the project from old chat history.
9. Within one continuing subsystem context, do not repeatedly reread unchanged authorities.

### If the previous Chat ended unexpectedly

```text
Open `tcholti/Gothic3_Animation_Behaviors` on branch `docs/collision-source-evidence`.

Read `docs/SESSION_ENTRYPOINT.md` first and follow its Fresh Normal Chat Bootstrap.
Then read the current `docs/BETWEEN_CHATS.md`.

Use repository documentation as authority. Do not reconstruct the project from old chat history and do not scan the whole repository.

When bootstrap is complete, tell me briefly:
- the current technical gate;
- the exact frozen responsibility;
- the key behavior invariants that must not change.

Do not redesign outside the frozen responsibility.
```

---

## Active Subsystem

**Frame-controlled melee collision lifecycle and modular collision architecture.**

Governing invariant:

> **For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact execution ends or is destructively abandoned, if cleanup was observed, do nothing; if not, repair only that execution's remaining offensive collision using native cleanup semantics.**

Markers control collision **inside a live Hit**. Terminal source safety is a separate execution-level responsibility.

Architecture authorities:

```text
docs/SECOND_PASS_REWRITE_CONTRACT.md      current frozen rewrite
docs/DESIGN.md §§10–11                    general modular direction
docs/COLLISION_LIFECYCLE_PLAN.md          lifecycle safety contract
docs/COLLISION_LOGGER_PLAN.md             diagnostic architecture
docs/COLLISION_TEST_PLAN.md               staged validation
docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md release/diagnostic separation
```

---

## Closed Collision-Safety Model

C1-R1 controlled validation is **CLOSED through EV-206–EV-207**.

Accepted execution/source model:

```text
live ScriptFunction frame
= temporary native correlator only where early acquisition needs it

C1 monotonic generation
= durable plugin execution identity

successful exact-source Item_Attack request
= exact source cleanup obligation

successful later transition away from Item_Attack
= obligation fulfilled
```

Accepted terminal repair:

```text
exact outstanding source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual source group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList()
→ verify exact Item_Equipped(5)
```

Everything outside that predicate remains no-op/unresolved and non-mutating. Native cleanup retains precedence.

Explicit qualifications that do not reopen R1:

```text
- no positive runtime exercise of an outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED case;
- no positive NPC destructive-abandonment / C1 physical-repair case is claimed.
```

Do not invent another broad R1 matrix solely to force those branches.

---

## Proven Marker Invariants

Preserve until a dedicated later simplification gate proves a stronger replacement:

```text
exact current-motion marker ownership
RIGHT / LEFT / BOTH / OFF exact-set semantics
authored occurrence budgets
same-update duplicate/replay protection
repeated-contact ClearTriggeredList rearm
Quick/full-Whirl StatePosition suppression
marker-owned source/window state
natural SetCollisionGroup retirement
OFF as an intra-Hit gap, not terminal cleanup
interruption/dead-execution rejection
unmarked/unsupported native fallback
current research Fist behavior without forcing weapon Item_Attack semantics
```

EV-131–EV-133 and EV-167 are especially important before changing marker execution bookkeeping.

---

## Structural Architecture State

Closed extractions/reviews:

```text
CollisionSources extraction
43fa1e719b5af716c54e17430c101251bbc36ff8

EngineBridge extraction
32ff447c9a678ba18c8234310564ff2475ba7dfb

first per-CPP review = CLOSED
second-pass architecture synthesis = CLOSED
unchanged post-EngineBridge runtime baseline = CLOSED/PASS
```

The post-EngineBridge runtime closure is recorded in `BETWEEN_CHATS.md`. Primary compact evidence is commit `5a33e5c134b027c440e40e6155cdf233aea049eb`, its deterministic retrieval package is commit `fb2644d2952923f5a9a3d41ba881a342ef0d8ff2`, and the supplemental focused Fist negative closure is commit `269faad334ef918ca16f6401751d47693e48520f`.

Current EngineBridge is the sole physical hook owner for the research DLL. Proven explicit-this transport remains on behavior-critical `RunScriptFunction`, `AISetState` and `SetCollisionGroup`; AIFullStop explicit-this remains a tested diagnostic/future transport point.

Second-pass correction:

```text
HookBridgeRuntime is behavior infrastructure,
not diagnostics,
because marker duplicate acceptance uses its elapsed-ms clock.
```

Frozen rewrite rename:

```text
HookBridgeRuntime → RuntimeClock
```

---

## Current Technical Gate — IMPLEMENT FROZEN SECOND-PASS REWRITE

The unchanged post-EngineBridge runtime baseline has passed. The exact next responsibility is now the semantic-preserving implementation contract in:

```text
docs/SECOND_PASS_REWRITE_CONTRACT.md
```

High-level frozen rewrite:

```text
HookBridgeRuntime → RuntimeClock
CollisionControl → FrameCollisionMarkers
new CollisionSourceOperations seam
fix unresolved-motion negative marker caching
move marker callback-ownership policy out of EngineBridge
remove rejected dormant eager lifecycle dispatch stack/API
make CollisionLifecycleGuard diagnostics-independent
compact default diagnostic layer + separate deep diagnostic layer
remove diagnostic-only hooks from behavior-only build
add a mechanically diagnostics-free behavior-only prototype target
preserve all existing collision/marker/C1 semantics
```

Do not combine with:

```text
C1-driven marker simplification
new marker-family support
new Fist semantics
AttackContinuationProtection
Raise
speed
config redesign
New Balance/Jackydima compatibility fixes
production migration
target acquisition
climbing
```

If a concrete source/API/calling-convention contradiction appears during implementation, **STOP and report it rather than improvising**.

Required post-rewrite source/build gate:

```text
git diff --check
bounded contract audit
build Script_FrameCollisionTest
build Script_FrameCollisionBehaviorTest
verify behavior-only target excludes diagnostic sources/hooks
```

---

## Production Migration Direction

The mature modular research DLL is the architectural ancestor of the eventual production `Script_G3AnimationBehaviors` DLL.

Do **not** pour the mature collision system back into the old v0.1 source/hook layout.

Later:

```text
retain mature central EngineBridge + behavior modules
→ migrate/redesign Raise + speed + config into that foundation
→ add independent systems such as target acquisition/climbing under the same rules
→ build public diagnostics-free Script_G3AnimationBehaviors
→ retain a separate instrumented diagnostic twin
```

---

## Retrieval — Only What the Question Needs

| Need | Open |
|---|---|
| exact current gate / handoff | `BETWEEN_CHATS.md` |
| frozen rewrite | `SECOND_PASS_REWRITE_CONTRACT.md` |
| release/diagnostic separation | `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md` |
| lifecycle C1/P2/R1 contract | `COLLISION_LIFECYCLE_PLAN.md` |
| diagnostic core/deep principles | `COLLISION_LOGGER_PLAN.md` |
| staged validation | `COLLISION_TEST_PLAN.md` |
| evidence routing | `EVIDENCE_INDEX.md` |
| C1-R1 exact evidence | `EVIDENCE_LEDGER_STEP_D.md` EV-206–EV-207 |
| marker bookkeeping history | `EVIDENCE_INDEX.md` marker execution route, especially EV-131–EV-133 / EV-167 |
| source/API/hook transport | `SOURCE_HOOK_GUIDE.md` |
| local build/deploy/log procedure | `PROJECT_OPERATING_PROCEDURES.md` |
| bounded Work execution rules | `WORK_IMPLEMENTATION_PROTOCOL.md` |
| future held-Use2 prevention | `BAD_SKIP_FUTURE_INVESTIGATION.md` |

Do not load the whole documentation corpus by default.

---

## Forward Order

```text
implement frozen SECOND_PASS_REWRITE_CONTRACT — NEXT
→ diagnostic + behavior-only build/source audit
→ compact diagnostic sufficiency regression
→ behavior-only smoke/equivalence
→ dedicated C1-vs-marker bookkeeping simplification audit
→ equipped-melee marker expansion
→ separate Fist source-adapter investigation
→ full marker + lifecycle regression
→ AttackContinuationProtection
→ mature research New Balance/Jackydima compatibility gate
→ migrate/redesign Raise + speed + config into mature foundation
→ later target acquisition/climbing and other independent systems
→ final diagnostics-free Script_G3AnimationBehaviors
→ final New Balance/Jackydima regression
→ retain separate diagnostic twin
```

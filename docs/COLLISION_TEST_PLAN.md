# Collision Lifecycle Test Plan

**Status:** Current staged validation plan  
**Updated:** 2026-08-30

## Purpose

Validate the collision system through small falsifiable stages while preserving the already-closed lifecycle-safety contract. Historical gate detail is preserved through `EVIDENCE_INDEX.md`, the canonical evidence ledgers and raw/archive artifacts; this file owns the **current and forward validation sequence**.

Current state: `SESSION_ENTRYPOINT.md`.  
Exact transient continuation: `BETWEEN_CHATS.md`.  
Lifecycle architecture: `COLLISION_LIFECYCLE_PLAN.md`.  
Overall modular architecture / implementation order: `DESIGN.md`.

---

## 1. Current Rules

- Compare one conceptual variable at a time where practical.
- Do not reopen closed C1-R1 semantics merely because code structure or marker coverage changes.
- Do not add family/action/input/state-name-specific cleanup branches.
- Do not treat `RunScriptFunction`, FullStop or AISetState as unconditional cleanup authority.
- Preserve native behavior for executions that already clean themselves.
- Successful offensive request creates an exact physical-source obligation; successful transition away from `Item_Attack` fulfills it.
- Repair may act only on an already-owned exact outstanding source after its legitimate cleanup opportunity has passed.
- Current equipped identity must establish source liveness before dereference/mutation.
- Keep structural refactors behavior-preserving and test them before adding new marker/source semantics.
- Expand one attack mechanism/source responsibility at a time.
- Preserve raw runtime logs exactly as produced.
- Follow `PROJECT_PIPELINE.md` for gate/artifact identity and `PROJECT_OPERATING_PROCEDURES.md` for build/deploy/test/log operations.

Authoritative research DLL remains:

```text
Script_FrameCollisionTest
```

until the explicit later production-migration phase is reached.

---

## 2. Closed Gates — Retrieve, Do Not Rerun by Default

```text
B6 replacement/deferred ProcessScript candidate      EV-174–EV-181
B7/B7b termination / continuation loss               EV-182–EV-189
B8 cross-family abandonment generality               EV-190
B9 cleanup/finalization ordering                      EV-191
C1 shadow execution/source obligation core           EV-192–EV-193
C1 pre-Combat acquisition gap                        EV-194
C1-O1 outer ScriptFunction lifetime/correlation      EV-195–EV-196
hook/finalizer substrate stabilization               EV-199–EV-203
C1-O2-P1 lightweight dispatch bridge                 EV-204
C1-O2-P2 lazy pre-Combat acquisition/consumption     EV-205
C1-R1 controlled native-equivalent physical repair   EV-206–EV-207
```

C1-R1 validation is closed.

Validated R1 sequence:

```text
R1-A independent source audit = PASS
R1-B build / identity / isolated load-unload = PASS
R1-C targeted positive repair = PASS
R1-D no-op / reaction / GetUp controls = PASS
R1-E Dual source-specific repair = PASS
R1-E compact marked-Staff regression = PASS
R1-E broad mixed exercised coverage = PASS
R1-E focused unarmed/crossbow negative closure = PASS
```

Do not rerun or expand this matrix merely because the research DLL is being reviewed/refactored. Retrieve EV-206–EV-207 when exact proof meaning is needed.

---

## 3. Accepted Collision-Safety Contract

Accepted identity/obligation model:

```text
live ScriptFunction frame
= temporary correlator only where early acquisition needs it

C1 monotonic generation
= durable plugin execution identity

successful Item_Attack request
= exact source obligation

successful transition away from Item_Attack
= obligation fulfilled

destructive AISetState + obligation still outstanding
= terminal repair checkpoint
```

Accepted repair predicate:

```text
source obligation is outstanding
+ exact current equipped RIGHT/LEFT pointer establishes liveness
+ actual current source group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList()
→ verify exact Item_Equipped(5)
```

Everything outside that predicate remains no-op/unresolved and non-mutating.

The validated regression envelope includes:

```text
ordinary clean completion
legitimate reaction cleanup
pre-activation/no-offense
P2 GetUpAttack acquisition + native cleanup
GetUpParade/defensive no-offense
inherited 7 -> 7 attribution
Dual exact RIGHT/LEFT independence
marked RIGHT/LEFT/BOTH/OFF interaction
Fist/body separation
crossbow unsupported-source fallback
supplemental bow/magic negative regression
mixed player/NPC hook stability
```

Two explicit limits remain:

```text
- no positive runtime exercise of an outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED branch;
- no positive NPC destructive-abandonment / C1 physical-repair case is claimed.
```

These are qualifications, not reasons to invent another R1 test matrix.

---

## 4. Current Phase — Read-Only Architecture Review

Before another source change, Normal Chat reviews:

```text
prototypes/Script_FrameCollisionTest/
src/Script_G3AnimationBehaviors/
```

The review should classify code into:

```text
shared engine hook/transport ownership
CollisionLifecycleGuard production semantics
frame-marker ownership/control semantics
physical source adapters
research-only diagnostics/probes
potentially redundant historical marker-lifetime inference
production-DLL Raise/speed modules and shared-hook compatibility risks
```

This phase has no runtime test because it authorizes no source change. Its output is a frozen, behavior-preserving modular-refactor responsibility.

Do not assign a new test/gate identifier until that exact implementation responsibility is frozen under `PROJECT_PIPELINE.md` conventions.

---

## 5. Forward Validation Sequence

The roadmap is provisional and may be course-corrected by source/runtime contradiction. Each implementation stage must be frozen before execution and gets the smallest regression that can falsify its claimed meaning.

### Phase A — semantic-preserving research-DLL modularization

Goal:

```text
central EngineHooks/bridge owns shared Gothic hooks
→ feature modules consume authoritative bridge events
→ CollisionLifecycleGuard remains collision-safety owner only
→ marker/source behavior remains unchanged
→ diagnostics remain observer-only/removable
```

No feature expansion in the same step.

Minimum post-refactor validation should include startup/load identity plus compact sentinels for:

```text
known positive stale-source repair
ordinary native cleanup no-op
legitimate reaction cleanup no-op
Dual source independence
one marked-source regression
Fist/unarmed negative
crossbow negative
normal shutdown
```

### Phase B — marker-bookkeeping simplification audit

First compare each existing marker guard/check against the proven C1 execution authority.

Remove only machinery proven to duplicate execution-lifetime inference. Preserve independent marker invariants, including:

```text
exact current-motion marker ownership
authored occurrence budgets
same-update duplicate/replay protection
repeated-contact ClearTriggeredList rearm
RIGHT/LEFT/BOTH/OFF exact-set behavior
StatePosition behavior required to suppress competing native activation
interruption/dead-execution rejection
```

Any simplification gets targeted historical marker regressions before expansion continues.

### Phase C — equipped-melee marker expansion

Expand the unchanged marker vocabulary one native attack mechanism at a time. Do not invent action-specific marker names.

For each expansion, minimum validation should protect:

```text
new family/mechanism positive marker behavior
one previously supported marker family
one unmarked/native fallback case
one lifecycle-guard positive or no-op sentinel as appropriate
```

### Phase D — Fist source-adapter decision

Only after equipped-melee marker coverage is stable, investigate whether Fist can safely support authored timing.

Do not route Fist through weapon-style `Item_Attack` group mutation. Prove the Fist-specific activation/rearm semantics independently before declaring support.

### Phase E — complete marker + lifecycle regression

After marker/source expansion, run a broader but purposeful regression confirming that marker changes did not weaken the closed C1-R1 safety contract.

### Phase F — modular attack-continuation protection

Investigate and, only if source evidence supports it, implement `AttackContinuationProtection` as a module separate from `CollisionLifecycleGuard`.

Its responsibility is to suppress/defer the known held-Use2 destructive consequence while a real attack is active, not to repair collision.

Validate:

```text
known bad skip prevented inside active attack
normal marker/native continuation completes
normal cleanup occurs
held-Use2 behavior outside attack remains native
legitimate reaction FullStop/AISetState remains native
C1-R1 remains available underneath as fail-safe
```

Authority: `BAD_SKIP_FUTURE_INVESTIGATION.md`.

### Phase G — New Balance / Jackydima compatibility on mature research DLL

Compatibility is mandatory before production migration.

Test the mature research DLL with New Balance and the relevant Jackydima DLL stack, focusing especially on shared hook ownership, attack callbacks, collision behavior and state/CombatMove paths. Do not rely on arbitrary DLL load order or assumed hook chaining.

### Phase H — production-DLL redesign and collision migration

Only after the mature research collision system passes compatibility should `src/Script_G3AnimationBehaviors` be redesigned around the same central engine-bridge + independent-module architecture and receive the proven collision modules.

Migration itself gets a compact equivalence regression before Raise/speed work is added.

### Phase I — Raise / speed modules and final compatibility

Raise and speed remain independent modules.

The existing direct `GetAnimationSpeedModifier` AttackSpeed hook is proof-of-concept, not frozen production architecture; re-evaluate the hook/intervention point against New Balance compatibility before implementing final speed control.

After all production modules are assembled, perform a second full `Script_G3AnimationBehaviors` + New Balance/Jackydima compatibility regression before stable promotion.

---

## 6. Non-Combination Rules

Unless an explicitly frozen phase says otherwise, do not combine:

```text
structural modular refactor + feature expansion
marker simplification + new attack-family support
Fist support + equipped-weapon source changes
AttackContinuationProtection + CollisionLifecycleGuard redesign
production migration + bad-skip investigation
production migration + Raise/speed redesign
New Balance compatibility fixes + unrelated behavior changes
```

If a source/API/calling-convention contradiction requires crossing one of these boundaries, stop and reassess in Normal Chat rather than broadening implementation opportunistically.

---

## 7. Evidence Handling

For future implementation/runtime stages:

```text
freeze exact question/matrix/raw filename
→ preserve raw unchanged
→ publish raw
→ use deterministic large-log reduction only when retrieval requires it
→ interpret in Normal Chat
→ update canonical evidence/current authorities only when meaning changes
```

Do not ask the User to paste large successful logs into Chat. Use `PROJECT_OPERATING_PROCEDURES.md` POP-05 through POP-07.

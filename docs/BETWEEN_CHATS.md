# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-08-31

## Current bridge — Gate 4 audit CLOSED/PASS; bounded implementation FROZEN

Repository:

```text
tcholti/Gothic3_Animation_Behaviors
```

Branch:

```text
docs/collision-source-evidence
```

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and follow its Fresh Normal Chat Bootstrap, then read this file.

Frozen Gate 4 implementation authority:

```text
docs/MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md
```

Do not reconstruct the project from old chat history and do not scan the whole repository.

---

## Closed foundations — do not reopen

### C1-R1 lifecycle safety

Closed through EV-206–EV-207.

```text
successful exact-source Item_Attack request
→ exact source obligation

successful transition away from Item_Attack
→ obligation fulfilled

post-native-AISetState finalization
+ exact obligation still outstanding
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList
→ verify exact group 5
```

Native cleanup always gets first opportunity.

### Marker invariants protected through Gate 4

```text
exact current-motion ownership
Normal / Quick / full-Whirl predicates
RIGHT / LEFT / BOTH / OFF exact-set semantics
authored occurrence budgets
same-update duplicate/replay suppression
repeated-contact ClearTriggeredList rearm
Quick/full-Whirl StatePosition suppression
marker-owned source/window state
natural retirement of exact physical source bits
OFF as intra-Hit gap
late/dead/unsupported marker rejection
current research Fist semantics
unmarked/unsupported native fallback
```

Gate 4 does not authorize weakening any of these.

---

## Product / validation state

Implementation architecture commit:

```text
4eeb701725e8b77d8850116d408155653ff4ad36
```

Products:

```text
Script_FrameCollisionTest
= CORE diagnostic research target

Script_FrameCollisionBehaviorTest
= behavior-only prototype target
= no diagnostic sources/defines/hooks
```

```text
Gate 1 source/build separation       CLOSED/PASS — EV-208
Gate 2 CORE diagnostic sufficiency   CLOSED/PASS — EV-209–EV-211
Gate 3 behavior-only smoke            CLOSED/PASS — EV-212
Gate 4 bookkeeping audit              CLOSED/PASS
Gate 4 bounded implementation         FROZEN / NEXT
```

Behavior-only Gate 3 DLL:

```text
Length: 380416
SHA256: 2802FD584F84BBAA0F7D9E1AAD502BDB2CE91D994EE303CF880CA82AC2737EB4
```

The behavior-only DLL may still be present in the live Gothic 3 scripts directory. Preserve the one-product-at-a-time rule before any later diagnostic run.

---

## Gate 4 audit result

The audit classified the current marker state into three conceptual responsibilities:

```text
1. duplicate/replay + authored occurrence protection
2. marker-owned physical source/window state
3. marker-local execution-boundary inference
```

Only responsibility 3 is superseded.

### Superseded execution-lifetime inference

Remove/consolidate only the marker-local guesses that a fresh execution began because of:

```text
source pointer change
motion filename change
action change
phase change
state-time rollback
authored-count change
controlled-callback key/state-time retirement
MarkerWindowStillMatchesActorExecution lifetime inference
```

The stronger authority is the already-proven monotonic C1 generation.

### Preserved independent marker behavior

Keep:

```text
exact current motion
family/action/Hit eligibility
required source preflight
RIGHT/LEFT/BOTH/OFF
occurrence budgets
duplicate suppression
ClearTriggeredList rearm
source-set switching
marker-owned active mask/window
StatePosition suppression
Fist behavior
native fallback
late/dead rejection
```

Natural `SetCollisionGroup` retirement must still remove the exact physical source bit from marker-owned state, but it must no longer guess that the entire occurrence/dedupe execution ended.

---

## Exact next responsibility — bounded Work implementation

Implement **only** `docs/MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md`.

Core rule:

```text
existing valid C1 generation
= durable marker-execution identity
```

Add one read-only factual `CollisionLifecycleGuard` query for the actor's current generation. It must not create, replace, finalize or repair anything.

Scope marker occurrence/dedupe state to that generation.

Different valid C1 generation:

```text
→ fresh marker execution budget/dedupe record
```

Same valid C1 generation:

```text
→ never silently reset occurrence history because action/phase/motion/source/state-time changed
→ preserve independent ownership checks
→ fail closed/reject on unexplained internal inconsistency
```

`FrameCollisionMarkers` must not become owner of C1 generation creation/finalization.

If a marker point requiring generation-scoped bookkeeping has no valid C1 generation, or source/API/calling-convention evidence contradicts the contract, **STOP and report rather than inventing a fallback execution-ID scheme**.

Expected bounded source scope:

```text
CollisionLifecycleGuard.h/.cpp
FrameCollisionMarkers.h/.cpp
FrameCollisionShared.h only if required for factual transport
EngineBridge.cpp only if required for factual generation transport
CollisionDiagnostics.cpp/.h only if compact validation observability requires it
```

No new hooks. No new attack family. No marker semantic change. No C1 repair change.

Before publishing implementation:

```text
source audit
git diff --check
commit/push
STOP
```

Do not build or run Gothic 3 inside the bounded Work implementation.

---

## Validation after implementation

After independent Normal Chat source review, the frozen CORE diagnostic regression will prove:

```text
same-motion two-contact genuine markers remain accepted
replay callbacks remain rejected
interrupted attack -> immediate same-motion new attack gets fresh C1 generation/budget
OFF/exact-set switching stays within one generation
natural cleanup retires physical source/window bit without inventing a new generation
full-Whirl destructive bad skip still rejects dead/late reopening and preserves C1 repair
no invariant/divergence/unresolved/failure signal
clean shutdown
```

Only after diagnostic regression passes should behavior-only smoke be repeated.

---

## Separate later item

The tested Dual P1 Quick asset currently carries `G3AB_COL_RIGHT` although older native-source evidence maps tested Dual P1 Quick to LEFT.

This remains a later equipped-melee marker-authoring/source-map review item. Do not mix it into Gate 4 implementation.

---

## Local/branch handoff note

Assistant-side documentation has advanced the remote branch beyond the User's previous local source head.

Before the next local source/build/commit window, synchronize per POP-01 and preserve unrelated local work.

Known unrelated local file to leave untouched if still present:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Authorities

```text
SESSION_ENTRYPOINT.md                          current front door
BETWEEN_CHATS.md                               this exact continuation
MARKER_BOOKKEEPING_SIMPLIFICATION_CONTRACT.md  frozen Gate 4 implementation
COLLISION_TEST_PLAN.md                         staged validation
COLLISION_LIFECYCLE_PLAN.md §9                 marker/C1 separation
EVIDENCE_INDEX.md                              evidence routing
EVIDENCE_LEDGER_STEP_D.md                      current collision evidence
SECOND_PASS_REWRITE_CONTRACT.md                architecture/invariants
GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md          release-purity rule
PROJECT_OPERATING_PROCEDURES.md                local build/deploy/test workflow
WORK_IMPLEMENTATION_PROTOCOL.md                bounded source implementation rules
```

---

## Forward order

```text
Gate 4 bounded implementation — NEXT
→ independent source review
→ frozen CORE marker-generation regression
→ behavior-only smoke if diagnostic regression passes
→ equipped-melee marker expansion
→ separate Fist source-adapter investigation
→ full marker/lifecycle regression
→ AttackContinuationProtection
→ mature research New Balance/Jackydima compatibility gate
→ migrate/redesign Raise + speed + config
→ later target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain diagnostic twin
```

# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-08-31

## Current bridge — Gate 2 CORE diagnostic sufficiency OPEN; build validation NEXT

Repository:

```text
tcholti/Gothic3_Animation_Behaviors
```

Branch:

```text
docs/collision-source-evidence
```

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and follow its Fresh Normal Chat Bootstrap, then read this file.

Do not reconstruct the project from old chat history and do not scan the whole repository.

---

## Closed foundations — do not reopen

### C1-R1 lifecycle safety

Closed through EV-206–EV-207.

Invariant:

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

Do not add action/input/state-specific cleanup branches or redesign C1.

### Marker invariants

Preserve:

```text
exact current-motion ownership
Normal / Quick / full-Whirl predicates
RIGHT / LEFT / BOTH / OFF exact-set semantics
authored occurrence budgets
same-update duplicate/replay suppression
repeated-contact ClearTriggeredList rearm
Quick/full-Whirl StatePosition suppression
marker-owned source/window retirement
OFF as intra-Hit gap
late/dead-execution rejection
current research Fist semantics
unmarked/unsupported native fallback
```

Do not simplify marker bookkeeping during the current responsibility.

---

## Second-pass rewrite — IMPLEMENTED / GATE 1 PASS

Frozen contract:

```text
docs/SECOND_PASS_REWRITE_CONTRACT.md
```

Implementation commit:

```text
4eeb701725e8b77d8850116d408155653ff4ad36
```

Build products:

```text
Script_FrameCollisionTest
= CORE diagnostic research target

Script_FrameCollisionBehaviorTest
= behavior-only prototype target
= no diagnostic sources/defines/hooks
```

Gate 1 source/build validation and initial post-rewrite CORE startup/load-unload are closed/PASS. Evidence EV-208.

---

## Gate 2 progress — already PASS

Mixed runtime artifact:

```text
research/raw/2026-08-30_second_pass_core_mixed_melee_bad_skip_attempts.log
commit a7995225310789c78a85cbce9940c86d41de74b0
```

The run contains eight exact positive `REPAIRED_TO_ITEM_EQUIPPED` outcomes across 2H Whirl and 1H Quick, plus ordinary native cleanup/no-op and marked Normal/Quick/Whirl coverage.

Gate 2 currently stands at:

```text
PASS  known positive stale-source repair
PASS  ordinary native cleanup no-op
PASS  marked-source regression
PASS  clean shutdown

OPEN  legitimate reaction cleanup no-op
OPEN  Dual source independence
OPEN  Fist/unarmed negative
OPEN  crossbow negative
```

Evidence EV-209.

Do not rerun already-PASS sentinels unless a later behavior/source change actually requires it.

---

## Reaction diagnostic-sufficiency gap

Focused reaction artifact:

```text
research/raw/2026-08-30_second_pass_core_legitimate_reaction_cleanup_noop.log
commit 86d41d4772ebfc320d67ca063e51b28523fcfb9e
```

User observation:

```text
visually things looked correct
```

CORE log showed healthy exact-source `7 -> 5` cleanup followed by `NO_OP_NO_OUTSTANDING`, but the reduced `ENGINE SetCollisionGroup` record lacked player action/phase/state/motion. Therefore the old compact run could not distinguish ordinary Hit→Recover cleanup from legitimate reaction cleanup.

Classification:

```text
CORE DIAGNOSTIC SUFFICIENCY GAP
NOT a demonstrated collision-behavior failure
```

---

## CORE SetCollisionGroup context restoration — IMPLEMENTED / REVIEW PASS

Frozen one-file correction was published at:

```text
5b92b79a5af63c38e66a7ec8deecd0876c2cf141
Restore Gate 2 SetCollisionGroup context
```

Parent:

```text
56b75d7d6801ac7015a59254733c9ef84258267f
```

Changed file only:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
```

Function:

```text
CollisionDiagnostics::LogSetCollisionGroup
```

Restored fields:

```text
PlayerAction
PlayerAniPhase
PlayerStateTime
PlayerCurrentMovementAni
```

Implementation uses already-established current-player/routine/animation APIs in the diagnostic source.

Independent Normal Chat source review: **PASS**.

Verified from the published diff:

```text
only CollisionDiagnostics.cpp changed
all four required fields are emitted
no deep diagnostic dependency added
no hook change
no lifecycle/C1 change
no marker/source-operation change
no RuntimeClock change
no CMake/behavior-only target change
```

This correction is diagnostic-only. It does not itself establish runtime success.

The Work handoff pasted into Normal Chat after publication was stale and incorrectly described historical C1-R1 commit `93e5a2f2...`; ignore that text. The actual remote branch/source commit is `5b92b79a...` and was independently verified from GitHub.

---

## EXACT NEXT RESPONSIBILITY — authoritative Windows build

The current source is ready for local validation. **Do not assign another behavior/source coding task before this build/runtime boundary is crossed.**

When the User is on the authoritative Windows/game PC:

### 1. Synchronize local checkout

The local checkout predates the latest remote source/documentation state. Preserve the unrelated untracked file below and synchronize normally per POP-01.

Unrelated local file to preserve exactly in place:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

Do not delete, move, stage or commit it as part of this gate.

### 2. Build only diagnostic target

```text
Script_FrameCollisionTest Release
```

Because the source change is confined to diagnostic-only `CollisionDiagnostics.cpp`, `Script_FrameCollisionBehaviorTest` does not need a repeat build unless a later diff crosses that boundary.

### 3. Deploy / identity

```text
deploy Script_FrameCollisionTest.dll only
verify exactly one intended live collision DLL
verify built/live SHA equality
```

Never deploy diagnostic and behavior-only prototype DLLs together.

### 4. Startup/load verification

Require the normal CORE identity:

```text
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
Hooks installed.
```

### 5. Focused runtime rerun only

Rerun the legitimate reaction cleanup/no-op sentinel. Freeze a new exact raw filename in the same message that requests the rerun; the old reaction raw remains canonical and unchanged.

Expected proof:

```text
attack collision armed
→ exact source Item_Attack(7)
→ ENGINE SetCollisionGroup cleanup 7 -> 5
→ restored compact PlayerAction / PlayerAniPhase / PlayerStateTime / PlayerCurrentMovementAni establish legitimate reaction context
→ C1 cleanup fulfilled
→ finalization NO_OP_NO_OUTSTANDING
→ RepairAttempted: 0
→ PhysicalCollisionChanged: 0
```

If proved:

```text
reaction sentinel PASS
→ continue Dual source independence
→ Fist/unarmed negative
→ crossbow negative
```

If still ambiguous, stop and reassess the smallest compact evidence addition before enabling deep diagnostics.

---

## Current environment boundary

The User is presently on a computer without the local Gothic 3 repository/build/game environment.

Allowed now:

```text
Normal Chat planning/review
GitHub source/document inspection
bounded future-task planning
```

Blocked until authoritative PC:

```text
local sync/build
DLL deployment
binary identity verification
Gothic 3 runtime testing
raw runtime capture
```

Planning may continue, but the technical gate must not be claimed beyond the Windows build/runtime boundary.

---

## Explicit non-goals before Gate 2 closes

Do not start:

```text
new hooks/deep stack probes
C1 redesign
marker simplification
new attack-family marker support
new/generalized Fist semantics
AttackContinuationProtection
Raise
speed/config redesign
New Balance / Jackydima compatibility fixes
production migration
target acquisition
climbing
```

---

## Authorities

```text
SESSION_ENTRYPOINT.md                 current gate/front door
BETWEEN_CHATS.md                      this exact continuation
COLLISION_TEST_PLAN.md                Gate 2 validation state
EVIDENCE_LEDGER_STEP_D.md             EV-206–EV-209
SECOND_PASS_REWRITE_CONTRACT.md       frozen architecture/invariants
GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md release-purity rule
PROJECT_OPERATING_PROCEDURES.md       local build/deploy/test/raw workflow
WORK_IMPLEMENTATION_PROTOCOL.md       bounded source implementation rules
```

---

## Forward order

```text
Windows build/deploy of 5b92b79... — NEXT
→ focused reaction CORE rerun
→ finish Gate 2 Dual/Fist/crossbow
→ Gate 2 CLOSED/PASS
→ behavior-only smoke/equivalence
→ dedicated marker-bookkeeping simplification audit
→ equipped-melee marker expansion
→ separate Fist source-adapter investigation
→ full marker/lifecycle regression
→ AttackContinuationProtection
→ mature research compatibility gate
→ migrate/redesign Raise + speed + config
→ later target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain diagnostic twin
```

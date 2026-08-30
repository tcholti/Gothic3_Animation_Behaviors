# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-08-31

## Current bridge — Gate 2 CORE diagnostic sufficiency OPEN

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

Implemented modules:

```text
EngineBridge
FrameCollisionMarkers
CollisionSources
CollisionSourceOperations
CollisionLifecycleGuard
RuntimeClock
CollisionDiagnostics          diagnostic target only
CollisionDiagnosticsDeep      diagnostic/deep capability only
```

Build products:

```text
Script_FrameCollisionTest
= CORE diagnostic research target

Script_FrameCollisionBehaviorTest
= behavior-only prototype target
= no diagnostic sources/defines/hooks
```

Gate 1:

```text
source audit PASS
git diff --check PASS
diagnostic build PASS
behavior-only build PASS
behavior-only mechanical diagnostic exclusion PASS
```

Validated deployed diagnostic DLL before Gate 2:

```text
SHA256 25980C09DC0AB3ECAF69397F0AE3CA8D5566FF816B1210F44182D4508B292109
Length 417792
```

Startup/load-unload sentinel:

```text
research/raw/2026-08-30_second_pass_core_diagnostic_startup_load_unload.log
commit 6bf59e6c08aebf6097566192b239092f0f734ea5
```

Contains:

```text
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
Hooks installed.
Script_FrameCollisionTest unloading cleanly.
```

Gate 1 / startup = CLOSED/PASS. Evidence EV-208.

---

## Gate 2 progress — already closed in CORE diagnostics

Mixed runtime artifact:

```text
research/raw/2026-08-30_second_pass_core_mixed_melee_bad_skip_attempts.log
commit a7995225310789c78a85cbce9940c86d41de74b0
```

The User performed 2H Normal, repeated 2H Whirl bad-skip attempts, repeated 1H Quick bad-skip attempts and a couple of 1H Normal attacks. Manual timing was intentionally not treated as authoritative; the log classified what actually happened.

The run contains eight exact positive repairs:

```text
2H Whirl generations: 5, 9, 10, 13
1H Quick generations: 14, 15, 17, 22
```

Each positive case established:

```text
OutstandingBeforeFinalization: 1
CleanupObservedBeforeFinalization: 0
ActualGroupBeforeRepair: 7
RepairAttempted: 1
RepairRequestedGroup: 5
ActualGroupAfterRepair: 5
PhysicalCollisionChanged: 1
Outcome: REPAIRED_TO_ITEM_EQUIPPED
```

The same run also contains ordinary native `7 -> 5` cleanup with `NO_OP_NO_OUTSTANDING`, marked Normal/Quick/Whirl ownership, Whirl OFF/occurrence/dead-marker handling, no searched invariant/divergence/unresolved/failure signal, and clean unload.

Therefore Gate 2 currently has:

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

Do not rerun the already-PASS sentinels unless a later source change actually touches their behavior/evidence.

---

## Current blocker — CORE reaction evidence is ambiguous

Focused reaction artifact:

```text
research/raw/2026-08-30_second_pass_core_legitimate_reaction_cleanup_noop.log
commit 86d41d4772ebfc320d67ca063e51b28523fcfb9e
```

User observation:

```text
visually things looked correct
```

CORE log:

```text
healthy exact source 7 -> 5 cleanup exists
finalization NO_OP_NO_OUTSTANDING
no repair indicated
```

But current compact `ENGINE SetCollisionGroup` records only:

```text
Source
SourceAddress
SlotAssociation
RequestedGroup
BeforeGroup
AfterGroup
RetiredMarkerExecutionCount
```

It no longer records player action/phase/state/motion around the transition. Therefore Normal Chat cannot prove whether a specific cleanup was:

```text
ordinary Hit -> Recover
or
legitimate damage-reaction cleanup
```

Gate-2 rule:

> If compact diagnostics make a required fact ambiguous, the diagnostic reduction is too aggressive.

Classification:

```text
CORE DIAGNOSTIC SUFFICIENCY GAP
NOT a demonstrated collision-behavior failure
```

Stop the remaining Gate-2 runtime matrix until this is corrected.

---

## FROZEN NEXT RESPONSIBILITY — diagnostics-only one-file correction

Immediate target:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
```

Function:

```text
CollisionDiagnostics::LogSetCollisionGroup
```

Restore these current-player context fields on relevant compact `ENGINE SetCollisionGroup` records:

```text
PlayerAction
PlayerAniPhase
PlayerStateTime
PlayerCurrentMovementAni
```

Use the already-established `Entity::GetPlayer`, routine/action, ani-phase, state-time and current-movement-animation APIs already used in the diagnostic source.

This is a compact logger correction only.

Do NOT:

```text
restore deep stack/callsite probes
add hooks
change EngineBridge hook targets/calling conventions/order
change CollisionLifecycleGuard
change C1 generation/obligation/finalization/repair semantics
change FrameCollisionMarkers or marker bookkeeping
change CollisionSources or CollisionSourceOperations
change RuntimeClock or duplicate timing
change CMake product separation
change Script_FrameCollisionBehaviorTest
turn deep diagnostics on by default
expand attack families
change/generalize Fist semantics
implement AttackContinuationProtection
change Raise/speed/config
start New Balance/Jackydima compatibility work
start production migration
touch target acquisition/climbing
```

If source inspection exposes a concrete API/calling-convention contradiction to this exact responsibility, STOP and report it rather than improvising.

---

## Validation after the one-file correction

Do one stage at a time.

Source stage:

```text
bounded diff audit
git diff --check for editable source
confirm only intended compact diagnostics changed
confirm behavior-only target remains mechanically unaffected
```

Build stage:

```text
build Script_FrameCollisionTest Release
```

Because the intended file is diagnostic-only and is excluded from `Script_FrameCollisionBehaviorTest`, the behavior-only build is not automatically required again unless the actual diff crosses that boundary.

Deployment stage:

```text
deploy Script_FrameCollisionTest.dll only
verify exactly one intended live collision DLL
verify built/live SHA equality
```

Startup stage:

```text
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
expected hook-install banner
```

Runtime stage:

```text
rerun only focused legitimate-reaction cleanup/no-op sentinel
```

Freeze a new exact raw filename in the same message that requests the rerun. The prior reaction raw remains canonical and unchanged.

Expected proof after correction:

```text
attack collision armed
→ exact source Item_Attack(7)
→ cleanup 7 -> 5 occurs while compact action/phase/state/motion establishes reaction context
→ C1 cleanup fulfilled
→ finalization NO_OP_NO_OUTSTANDING
→ RepairAttempted: 0
→ PhysicalCollisionChanged: 0
```

If proved, mark reaction sentinel PASS and continue:

```text
Dual source independence
Fist/unarmed negative
crossbow negative
```

If still ambiguous, stop and reassess the smallest compact evidence addition before enabling deep diagnostics.

---

## Local / branch handoff state

The User's last local evidence push before this documentation close was:

```text
86d41d4772ebfc320d67ca063e51b28523fcfb9e
```

After that push, Normal Chat performed documentation-only remote maintenance. Therefore at the start of the next local writer window the User must synchronize from the latest remote `docs/collision-source-evidence` before editing/building.

Preserve the existing unrelated untracked local file exactly in place:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

It is legitimate derived research context from the earlier AISetState stability work. Do not delete, move, stage or commit it as part of the Gate-2 logger correction.

One branch writer window at a time per POP-01.

---

## Authorities for the next Chat

```text
SESSION_ENTRYPOINT.md                current gate/front door
BETWEEN_CHATS.md                     this exact continuation
COLLISION_TEST_PLAN.md               Gate 2 validation state
EVIDENCE_LEDGER_STEP_D.md            EV-206–EV-209
SECOND_PASS_REWRITE_CONTRACT.md      frozen rewrite/invariants
GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md release-purity rule
PROJECT_OPERATING_PROCEDURES.md      local build/deploy/test/raw workflow
WORK_IMPLEMENTATION_PROTOCOL.md      bounded source implementation if Work is used
```

Do not load other documents unless a concrete question requires them.

---

## Forward order

```text
CORE SetCollisionGroup context restoration — NEXT
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
→ migrate/redesign Raise + speed + config into mature modular foundation
→ later target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final compatibility regression
→ retain diagnostic twin
```

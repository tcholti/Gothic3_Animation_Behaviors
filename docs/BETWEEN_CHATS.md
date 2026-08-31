# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-08-31

## Current bridge — Gate 3 CLOSED/PASS; Gate 4 audit NEXT

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

### Marker invariants still protected during Gate 4 audit

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

Gate 4 may only classify whether some execution-lifetime inference is superseded. It must not silently collapse independent marker invariants.

---

## Product separation

Implementation:

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

Gate 1 source/build separation is CLOSED/PASS. EV-208.

Gate 2 CORE diagnostic sufficiency is CLOSED/PASS. EV-209–EV-211.

---

## Gate 3 — behavior-only smoke/equivalence CLOSED/PASS

The User synchronized local source to:

```text
2fb28e5a27333eb6da902dc5c1d46a11fbe0d809
```

`Script_FrameCollisionBehaviorTest` Release then built successfully.

Built behavior-only DLL:

```text
Script_FrameCollisionBehaviorTest.dll
Length: 380416
SHA256: 2802FD584F84BBAA0F7D9E1AAD502BDB2CE91D994EE303CF880CA82AC2737EB4
```

Deployment isolation:

```text
Script_FrameCollisionTest.dll removed from live scripts
Script_FrameCollisionBehaviorTest.dll deployed alone
built/live SHA exact match
live enumeration showed only Script_FrameCollisionBehaviorTest.dll
```

Runtime:

```text
main menu reached normally
main-menu exit normal
User then performed many different functional tests under the frozen Gate-3 exercise and reported everything working as intended
```

This closes the intended behavior-only functional smoke/equivalence gate. Because the behavior-only DLL intentionally contains no diagnostics, do not turn this into an internal-event claim and do not reintroduce diagnostics merely to manufacture a Gate-3 log.

The behavior-only DLL may still be present in the live Gothic 3 scripts directory after the successful test. Before any future diagnostic run, preserve the one-product-at-a-time rule and remove/swap it deliberately.

---

## Exact next responsibility — Gate 4 marker-bookkeeping simplification audit

**No source edit is authorized yet.**

The audit question is:

```text
for each current FrameCollisionMarkers execution/bookkeeping guard:
A. is it execution-lifetime inference now genuinely superseded by stronger native/C1 authority?
or
B. is it an independent marker invariant that must remain?
```

Before proposing removal or consolidation, reconstruct only this evidence route:

```text
EV-066–EV-075
EV-131–EV-133
EV-167
EV-182–EV-196
EV-206–EV-207
EV-209–EV-211
COLLISION_LIFECYCLE_PLAN.md §9
```

Then inspect only the current marker source necessary to map each relevant guard/check to that evidence.

Mandatory preserve-unless-disproved set:

```text
exact current-motion marker ownership
authored occurrence budgets
same-update duplicate/replay protection
repeated-contact ClearTriggeredList rearm
RIGHT/LEFT/BOTH/OFF exact-set behavior
StatePosition native-activation suppression
interruption/dead-execution rejection
```

The Gate-2 Dual P1 Quick authoring/source-map mismatch is a later equipped-melee marker-expansion item. Do not mix it into the bookkeeping audit unless it directly bears on a guard's correctness.

---

## Local/branch handoff note

The assistant-side documentation maintenance after the User's Gate-3 runtime test advances the remote branch beyond local source head `2fb28e5...`.

Do not require a local sync merely for Normal Chat evidence/source review. Before the next local build, local source edit, or local commit window, synchronize per POP-01 and preserve unrelated local work.

Known unrelated local file to leave untouched if still present:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

---

## Explicit non-goals during the audit

Do not start:

```text
source changes before classification is frozen
new hooks/deep probes
C1 redesign
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
COLLISION_TEST_PLAN.md                Gate 4 audit state
EVIDENCE_LEDGER_STEP_D.md             current collision evidence
SECOND_PASS_REWRITE_CONTRACT.md       frozen architecture/invariants
COLLISION_LIFECYCLE_PLAN.md §9        marker simplification constraints
GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md release-purity rule
PROJECT_OPERATING_PROCEDURES.md       local build/deploy/test workflow
WORK_IMPLEMENTATION_PROTOCOL.md       bounded source implementation rules
```

---

## Forward order

```text
Gate 4 marker-bookkeeping simplification audit — NEXT
→ freeze only evidence-supported bounded simplification, if any
→ implement/review/test that bounded simplification
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

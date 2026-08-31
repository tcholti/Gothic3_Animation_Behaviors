# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-08-31

## Current bridge — Gate 2 CLOSED/PASS; Gate 3 behavior-only smoke NEXT

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

Do not simplify marker bookkeeping during Gate 3.

---

## Second-pass rewrite / product separation

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

---

## Gate 2 — CLOSED/PASS

The diagnostic-only context restoration was published at:

```text
5b92b79a5af63c38e66a7ec8deecd0876c2cf141
Restore Gate 2 SetCollisionGroup context
```

Validated rebuilt diagnostic DLL:

```text
Length: 418304
SHA256: 635B2AD1E7DD4B037317CA6BD5FC3477A427E5EBF1772623D7A41DBC728CB0F3
DiagnosticProfile: CORE
DeepDiagnostics: DISABLED
```

Gate-2 sentinel state:

```text
PASS  known positive stale-source repair
PASS  ordinary native cleanup no-op
PASS  legitimate reaction cleanup no-op
PASS  Dual source independence
PASS  marked-source regression
PASS  Fist/unarmed negative
PASS  crossbow negative
PASS  clean shutdown
```

Relevant final artifacts:

```text
reaction:
research/raw/2026-08-31_second_pass_core_legitimate_reaction_cleanup_noop_context_restored.log
commit 2ca3f76aeb1b832d5be22985e3f6fd58ef8d4191

Dual:
research/raw/2026-08-31_second_pass_core_dual_source_independence.log
commit c5d833c6d749636f238879b46d196e7865248ac8

Fist/unarmed:
research/raw/2026-08-31_second_pass_core_fist_unarmed_negative.log
commit b914f7660a424f502b21f85ee668b694760dbbae

crossbow:
research/raw/2026-08-31_second_pass_core_crossbow_negative.log
commit 0b23be7a22c3b96e817db2fc9522d854b4739d2f
```

Evidence:

```text
EV-209  mixed CORE pass + reaction ambiguity
EV-210  restored compact context + reaction sentinel closure
EV-211  Dual/Fist/crossbow closure + Gate 2 CLOSED/PASS
```

### Important later marker-expansion note

The tested Dual P1 Quick assets in the Gate-2 fixture carry `G3AB_COL_RIGHT`, so the marker system correctly activates RIGHT. Older native-source evidence maps tested Dual P1 Quick to LEFT. Preserve this as a later marker-authoring/source-map review item; it is not a Gate-2 source-independence failure. See EV-211.

---

## EXACT NEXT RESPONSIBILITY — Gate 3 behavior-only smoke/equivalence

No source change is authorized before this gate.

### Local handoff

The assistant-side documentation/evidence transaction advances the remote branch after the User's last local evidence push. Before building, synchronize the local checkout per POP-01 while preserving unrelated local work.

Known unrelated untracked file to preserve exactly in place if still present:

```text
research/archive/2026-08-29_c1_aisetstate_recursion_safe_extended_gameplay_stability_would_repair_context.txt
```

Do not delete, move, stage or commit it as part of Gate 3.

### Build/deploy sequence

```text
sync local branch
→ build Script_FrameCollisionBehaviorTest Release
→ identify/hash built behavior-only DLL
→ remove Script_FrameCollisionTest diagnostic DLL from live scripts
→ deploy Script_FrameCollisionBehaviorTest.dll alone
→ verify exactly one intended collision prototype DLL is live
→ verify built/live SHA equality
→ main-menu load/exit smoke
→ run frozen Gate-3 functional matrix
```

Never deploy diagnostic and behavior-only prototypes together.

### Frozen Gate 3 matrix

```text
A. marked 2H Normal positive
   - 2–3 marked 2H Normal attacks against a target
   - intended damage/contact must occur

B. stale-source repair functional smoke
   - 3 established vulnerable 2H full-Whirl held-Use2 bad-skip attempts
   - each attempt should already have made offensive contact before the destructive skip
   - after returning to Ambient/running, contact the target without attacking
   - no passive stale-weapon damage may occur
   - a following ordinary attack must still damage normally

C. unsupported/native-fallback smoke
   - 3 normal crossbow shot cycles against a target
   - aim/shoot/reload flow remains normal
   - no visible melee-marker/repair interference

D. exit Gothic 3 normally
```

Acceptance:

```text
no load/runtime crash
marked melee behavior functional
no stale passive weapon damage after bad skip
later ordinary melee attack functional
crossbow/native fallback functional
normal exit
```

No diagnostic raw log is expected because the behavior-only target intentionally contains no diagnostics. Do not co-load or reintroduce diagnostic code just to create a Gate-3 log.

---

## Explicit non-goals during Gate 3

Do not start:

```text
new hooks/deep probes
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
COLLISION_TEST_PLAN.md                Gate 3 frozen validation state
EVIDENCE_LEDGER_STEP_D.md             EV-206–EV-211
SECOND_PASS_REWRITE_CONTRACT.md       frozen architecture/invariants
GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md release-purity rule
PROJECT_OPERATING_PROCEDURES.md       local build/deploy/test workflow
WORK_IMPLEMENTATION_PROTOCOL.md       bounded source implementation rules
```

---

## Forward order

```text
Gate 3 behavior-only build/deploy/functional smoke — NEXT
→ Gate 3 CLOSED/PASS if clean
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

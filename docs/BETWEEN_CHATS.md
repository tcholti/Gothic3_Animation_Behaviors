# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-14

## Current Bridge — EV-282 CLOSED; RAW55 ARCHITECTURE SYNTHESIS NEXT; FINAL VALIDATION SEQUENCE SAVED

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical runtime evidence is through **EV-282**.

No permanent raw55 implementation is authorized yet.  
No new Work/source task is currently frozen.

The current responsibility returns to **Normal Chat architecture synthesis**: convert only the proven raw55 family responsibilities into a clean permanent design before any production implementation task is authorized.

Important stopping-point addition from the User: raw55 must **not** be considered finally concluded after the first permanent/candidate implementation alone. A final one-marker cross-family validation must come first, followed by a dedicated two-marker/double-contact validation across Quick, Normal, Power and Sprint.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. EVIDENCE_LEDGER_274_ONWARD.md — EV-274 through EV-279
4. EVIDENCE_LEDGER_280_ONWARD.md — EV-280 through EV-282
5. prior Quick raw55 evidence EV-264 through EV-273 only as needed
6. FEATURE_DEVELOPMENT_METHOD.md when permanent module boundaries are being designed
```

Historical Sprint probe authority remains:

```text
docs/COLLISION_RAW55_SPRINT_FIST_ACTIVATION_PROBE.md
```

It is closed evidence/provenance, not an active Work responsibility.

---

## Closed Raw55 Family Results

### Quick — CLOSED/PASS through EV-273

Proven shape:

```text
preserve original native Quick callback/state progression
suppress premature exact RIGHT PhysicalFist/raw55 group5 -> group7
support authored FIST activation at the factual marker boundary
Quick contact requires triggered-list clearing/rearm
later authored FIST can rearm repeated contact in the same C1
pre-StatePosition marker ordering is a real Quick-specific boundary
native cleanup returns exact RIGHT 7 -> 5
```

Do not generalize Quick's `ClearTriggeredList` requirement onto other families.

### True Power — CLOSED/PASS through EV-276

```text
factual Action2 / Family POWER
preserve original _AI_PowerAttack
suppress premature exact RIGHT raw55 5 -> 7
native StatePosition 0 -> 1 survives
FIST at StatePosition1 opens exact RIGHT 5 -> 7
ClearTriggeredList=0
native damage
native cleanup 7 -> 5
```

### Normal — CLOSED/PASS through EV-279

```text
factual Action1 / Family NORMAL
preserve original _AI_Attack
suppress premature exact RIGHT raw55 5 -> 7
native StatePosition 0 -> 1 survives
FIST at StatePosition1 opens exact RIGHT 5 -> 7
ClearTriggeredList=0
native damage
native cleanup 7 -> 5
```

### Sprint — CLOSED/PASS through EV-282

EV-280 proves factual Sprint is `Action=9 / Family=SPRINT` inside the existing `_AI_PowerAttack` transport and that the same original callback owns native `StatePosition 0 -> 1` plus the premature exact RIGHT raw55 `5 -> 7`. Whole-callback suppression is rejected.

EV-281 proves the exact Action9 nested RIGHT raw55 opening can be suppressed while native callback/state progression survives and RIGHT remains group5 through authored FIST.

EV-282 proves authored Sprint FIST activation itself is sufficient. Three independent Sprint C1s — 16, 57 and 81 — repeat:

```text
Action9/SP0 exact RIGHT raw55 5 -> 7 suppressed
native StatePosition 0 -> 1 survives
RIGHT remains group5

authored G3AB_COL_FIST at factual Action9 / SPRINT / SP1
exact RIGHT TrollFist/raw55 group5 -> group7
ClearTriggeredList=0
native ONDAMAGE Target=PC_Hero
native exact RIGHT cleanup 7 -> 5
C1 CLEANUP FULFILLED
C1_FINAL Outstanding=0 Cleanup=1 PhysicalChanged=0
```

Later callbacks in the same PowerAttack-named motion may become factual Action2 after contact. That later factual transition is separate and does not change the Action9 activation proof. Animation filename remains non-authoritative.

Canonical runtime:

```text
research/raw/2026.09.14_troll_raw55_sprint_fist_activation_2.log
SHA256 5CB3DCF52A68669C24C44279B69DC84ED404E78C61029DF76499B79088B0361C
```

Derived retrieval package:

```text
research/derived/2026.09.14_troll_raw55_sprint_fist_activation_2_large_log/
```

Implementation under test:

```text
545863c0c522b2cd2d2748f6823a23662bf0ffbf
```

User-local diagnostic DLL identity:

```text
SHA256 783747CC5E6627A1AC0092BB05C7F110813C940B940B208A835C0B2D28A5C597
```

User observation: the exercised Power-looking Troll attacks damaged the player; provoking factual Sprint required attacking the Troll, suggesting a counter-like trigger in this fixture.

---

## Current Architecture-Synthesis Boundary

The permanent design must express proven responsibilities, not transplant diagnostic scaffolding.

Common proven Power/Normal/Sprint shape:

```text
preserve native callback/state progression
selectively suppress only the premature exact RIGHT PhysicalFist/raw55 5 -> 7
at authored FIST, open the exact current RIGHT PhysicalFist/raw55 5 -> 7
no ClearTriggeredList for first contact
let Gothic own contact/damage
let native cleanup own 7 -> 5
```

Quick is the proven special case:

```text
same general delayed authored-opening goal
but marker ordering may be pre-StatePosition
and triggered-list clear/rearm is required for contact/repeated contact
```

Architecture constraints that remain standing:

```text
EngineBridge remains hook/transport-only
FrameCollisionMarkers stable semantics remain separate
CollisionLifecycleGuard remains lifecycle/repair owner
raw8 FIST remains a separate proven mechanism
PhysicalFistProbe remains diagnostic research code
permanent raw55 policy/state belongs in an appropriate permanent responsibility-owned module
no species/name/motion-filename policy
no timer/polling/per-frame workaround
```

Do not freeze Work until Normal Chat and User agree on the permanent module/responsibility shape.

---

## Planned Final Raw55 Validation Sequence

This is a **future validation gate**, not an active implementation task yet.

After Normal Chat and User agree on the permanent raw55 architecture and the bounded implementation has been completed/reviewed, validate in this order:

### Gate 1 — one authored FIST marker across all four raw55 families

Use Troll test animations/fixtures for:

```text
Quick
Normal
Power
Sprint
```

Each should use the ordinary single authored FIST path first. Confirm the final implementation preserves the already-proven family behavior: authored activation occurs at the intended marker, native damage/contact remains Gothic-owned, and native cleanup/finalization stays healthy.

Do not move to the two-marker test until this single-marker cross-family regression passes.

### Gate 2 — two authored FIST markers / two possible player contacts

Then use Troll animations deliberately authored so **two distinct hits on the player are physically possible** in the same attack execution, for:

```text
Quick
Normal
Power
Sprint
```

Author/use two FIST marker opportunities corresponding to the two intended contacts and determine whether a second authored activation/contact can occur correctly in each family.

Purpose:

```text
verify repeated authored activation/contact semantics rather than assuming Quick's proven rearm behavior is universal
confirm whether Normal, Power and Sprint also support two authored hit opportunities correctly
compare those results against Quick's already-proven repeated-contact/rearm specialization
verify both contacts still leave ordinary native cleanup and clean C1 finalization
```

The exact two-marker implementation/test contract must be frozen only after Gate 1 passes and after Normal Chat inspects the permanent implementation shape. Do not pre-assign `ClearTriggeredList` behavior to Normal/Power/Sprint; let this test establish what repeated-contact semantics actually require.

Raw55 is **not finally concluded** until these two validation gates are complete or explicitly deferred by User + Normal Chat.

---

## Still Paused

```text
NO automatic copy/promotion of PhysicalFistProbe
NO new raw55 family probe before architecture synthesis
NO broad native-creature certification continuation
NO Axe-separation compatibility sequence
NO Rapier/Zombie compatibility sequence
NO AttackContinuationProtection work
```

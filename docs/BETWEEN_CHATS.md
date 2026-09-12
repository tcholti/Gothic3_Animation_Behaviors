# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-12

## Current Bridge — RAW55 QUICK AUTHORED-FIST CONTACT-REARM WORK TASK

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock remains **CLOSED**. Canonical evidence now reaches **EV-266**.

No permanent raw55 implementation is authorized.

---

## Read Order

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_RAW55_QUICK_FIST_REARM_PROBE.md
4. EVIDENCE_LEDGER_265_ONWARD.md EV-265–EV-266
5. FEATURE_DEVELOPMENT_METHOD.md
6. WORK_IMPLEMENTATION_PROTOCOL.md
7. only exact source/API files required for this bounded implementation
```

Prior raw55 probe contracts are closed causal context. Preserve their behavior where this task depends on it.

---

## Closed Raw55 Evidence

### EV-265 — early Quick activation and state progression are separable

```text
exact early RIGHT raw55 5 -> 7 request suppressed
original _AI_QuickAttack still runs
StatePosition 0 -> 1 preserved
RIGHT remains group5
```

### EV-266 — authored FIST group activation works, damage does not

Runtime artifacts:

```text
research/raw/2026.09.12_troll_raw55_quick_fist_activation.log
research/raw/2026.09.12_black_troll_raw55_quick_fist_activation.log
```

Across 12 Troll + 9 BlackTroll Quick executions:

```text
early EV-265 5 -> 7 suppression remains
StatePosition 0 -> 1 remains
FIST arrives at StatePosition 1 around StateTime ~0.48–0.49
exact RIGHT raw55 5 -> 7 request succeeds
real C1 offense obligation is created
source remains group7 through late Quick window
native cleanup returns 7 -> 5
C1 cleanup fulfilled; no terminal repair
NO Troll/BlackTroll OnDamage to PC_Hero
```

The BlackTroll log contains three `CORE ONDAMAGE` records, all from `PC_Hero` Flamberge counterattacks targeting `BlackTroll`; they are controls, not raw55 damage.

Therefore group activation and cleanup are proven for this Quick path, but group opening alone is insufficient to restore contact/damage.

The EV-266 logs remain **ACTIVE COMPARISON** for the next one-variable rearm probe.

---

## Frozen Work Responsibility

Authority:

```text
docs/COLLISION_RAW55_QUICK_FIST_REARM_PROBE.md
```

Implement **only** the temporary diagnostics-only Quick authored-FIST triggered-list causal probe frozen there.

Single question:

> Keeping EV-265 early suppression and EV-266 authored-FIST `5 -> 7` activation unchanged, is one exact `TouchDamage.ClearTriggeredList()` on the same RIGHT raw55 source immediately after verified successful FIST-time activation sufficient to restore native contact/damage while preserving native cleanup?

### Required behavior

Preserve unchanged:

```text
marked raw55 Quick original callback executes exactly once
exact early RIGHT raw55 5 -> 7 request is suppressed
native StatePosition 0 -> 1 remains
same actor/source/C1 early-suppression proof is required
stable raw55 FIST result remains UNSUPPORTED_MISSING_SOURCE
FIST-time exact RIGHT raw55 5 -> 7 request remains one-shot
```

At the eligible FIST event:

```text
mark FIST intervention used
request exact RIGHT raw55 -> Item_Attack/group7 through ordinary setter
read groupAfter

ONLY if groupAfter == 7:
    rightSource.TouchDamage.ClearTriggeredList()
    exactly once
```

Do not use `CollisionSourceOperations::ActivateOrRearm()`; the causal delta from EV-266 must be only the direct triggered-list clear after the already-proven group request.

Add compact diagnostic:

```text
CORE RAW55_QUICK_FIST_REARM_PROBE
```

with actor/C1/action/StatePosition/StateTime/right identity/use type/group before/requested/after and `ClearTriggeredList=1|0`.

---

## Stable Boundaries

Do not change:

```text
FrameCollisionMarkers semantics or acceptance
Raw8FistCollision
CollisionLifecycleGuard semantics
CollisionSources
CollisionSourceOperations
CMake target/source separation
hook RVAs/ownership
raw8 behavior
equipped RIGHT/LEFT/BOTH/OFF behavior
native cleanup
Normal/Sprint raw55 behavior
```

Do not add:

```text
custom/direct damage
manual TriggerTarget / OnDamage
StatePosition write
SPU+0x164 write
manual 7 -> 5 cleanup
second group7 request
species/name policy
new hook/RVA/timer/polling/per-frame scan
permanent PhysicalFistCollision
```

EV-233 remains authoritative for raw8: this raw55 probe must not be generalized back onto raw8 Fist.

---

## Expected Changed Files

Normally only:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp
```

`PhysicalFistProbe.h` or the smallest existing diagnostics-only bridge seam may change only if directly necessary. No stable behavior module or CMake change is expected.

If the frozen task cannot be implemented within these boundaries because of a real source/API contradiction, stop and report rather than broadening scope.

---

## Work Stop / Report

Follow `WORK_IMPLEMENTATION_PROTOCOL.md`:

```text
read frozen authorities
-> inspect only necessary source/API
-> implement bounded diagnostic probe
-> static/source audit
-> commit + push to docs/collision-source-evidence
-> report final remote SHA, changed files, concise result,
   build status, material contradiction if any
-> STOP
```

**Build execution is NOT authorized.**

Normal Chat reviews source first. Only after review passes does User + Normal Chat build/deploy/test locally.

---

## Expected Runtime Classification

### A — rearm sufficient

```text
early 5 -> 7 suppressed
StatePosition 0 -> 1 preserved
FIST 5 -> 7 succeeds
one exact ClearTriggeredList executes
native OnDamage to PC_Hero appears after authored FIST/rearm when contact occurs
native cleanup 7 -> 5
C1 closes without repair
```

### B — rearm insufficient

```text
group7 + one exact clear
but still no raw55 OnDamage to PC_Hero
```

Return to Normal Chat and isolate the next native TouchDamage/contact fact. Do not add another intervention in the same Work task.

### C — lifecycle divergence

If damage returns but cleanup becomes abnormal, isolate that consequence before any production design.

Broader raw55 family design remains paused until this Quick-only contact/rearm question closes.

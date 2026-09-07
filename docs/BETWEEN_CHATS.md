# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-07

## Current bridge — production human Fist CLOSED/PASS; final native mixed collision regression NEXT

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat / Work must read `docs/SESSION_ENTRYPOINT.md` first, then this file, then `docs/WORK_IMPLEMENTATION_PROTOCOL.md` when a bounded Work implementation is actually frozen.

No Work implementation task is currently frozen.

---

## Closed / protected boundary

```text
collision architecture verification                 COMPLETE — EV-206–EV-215
Power equipped marker/source validation             CLOSED/PASS
Pierce equipped marker/source validation            CLOSED/PASS
SimpleWhirl current marker/semantic scope           CLOSED/PASS
Hack isolated routing/source/marker scope           CLOSED/PASS
human Fist Stage A/B/N1/N2/N3 research              HISTORICAL / SUPERSEDED AS CURRENT
human Fist N4 callback-suppression necessity        CLOSED/PASS — unnecessary
human Fist N5 ClearTriggeredList necessity           CLOSED/PASS — unnecessary
human Fist N6 native timing gate                     CLOSED/PASS — causal mechanism identified
human Fist authored FIST_OFF                         CLOSED — unnecessary for final vocabulary
human Fist interruption handling                     CLOSED/PASS for tested Normal/Power cases
production human raw-8 FIST                          CLOSED/PASS
```

Do not reopen these findings without concrete contradictory evidence.

---

## Production human raw-8 Fist checkpoint

Production source:

```text
dba34c6fbf36b6354186d1884faee5501ee4f261
    Add production human Fist marker mechanism

17491d53d8a4209690fc2fa49a7b5c4c04b5b0cf
    Fix duplicate human Fist actor identity declaration
```

The compile correction is one-line only and does not change behavior.

Authoritative acceptance evidence:

```text
research/raw/2026-09-07_fist_production_frame12_normal_power_acceptance.log
5de195c6c4571237fef5d841a7a8fe1b75c9cf78
```

User runtime matrix:

```text
3 x P0 Normal frame-12-only FIST
3 x P0 Power frame-12-only FIST
same controlled Golem contact setup

visual result, all six:
    first swing  = NO damage
    second swing = YES damage
```

Engine-side result, all six marked executions:

```text
marked execution ownership
    latch 0 -> 1, confirmed

frame-12 FIST
    latch 1 -> 0, confirmed

real motion-0 play time
    above native threshold in every case
    TimingPermissionArmed = 0

native damage
    exactly one Hero raw-8 Fist -> Golem Game+0x16E348 event per execution
    every event occurs after the FIST marker
    zero pre-marker Game+0x16E348 events
```

This closes the late-first-marker leak exposed by the earlier frame-12 Normal/Power tests.

---

## Frozen production FIST semantics

```text
UNMARKED HUMAN FIST
    completely native

MARKED HUMAN FIST EXECUTION
    exact current Hit contains one or more authored FIST markers
    + exact human raw-8 Fist identity established
        -> once per factual C1 generation, close SPU+0x164 to 1
           before first authored FIST

EACH ACCEPTED FIST
    -> SPU+0x164 = 0
    -> inspect real motion-0 timing

    if real play time < native threshold
        -> arm one exact bounded Game+0x16E180 timing permission
        -> matching call sees threshold + epsilon only for that comparison
        -> actual animation clock remains unchanged
        -> permission consumed once

    if real play time >= native threshold
        -> no synthetic timing permission

GOTHIC NATIVE PATH
    -> downstream target/contact/damage remains native
    -> successful opportunity self-closes through native SPU+0x164 = 1
    -> observed damage dispatch Game+0x16E348
```

Timing permission remains bound to the factual actor/SPU/C1 generation/animation-actor/motion/callsite identity and retires on factual identity/generation change.

---

## Explicit production exclusions

```text
NO authored G3AB_COL_FIST_OFF semantic
NO Fist TouchDamage.ClearTriggeredList operation
NO Fist-specific weapon-style OnAI_Attack suppression
NO equipped RIGHT/LEFT source-mask/window semantics for Fist
NO Item_Attack / Item_Equipped Fist ownership
NO weapon C1 physical-cleanup obligation for Fist
NO custom/direct Fist damage dispatch
NO global animation-clock mutation
NO global timing-constant/branch patch
NO monster gEUseType_PhysicalFist / raw55 generalization
NO dedicated Fist interruption repair from current evidence
NO theoretical bad-skip correction for current H2H moves that cannot reproduce it
```

Equipped-weapon RIGHT / LEFT / BOTH / OFF behavior and weapon repeated-contact `ClearTriggeredList()` remain protected and unchanged.

---

## Current exact next responsibility

> Freeze and run the final native mixed collision regression against the mature current research behavior.

This is a regression/closure matrix, not a new architecture investigation.

It should exercise the mature native/no-third-party collision stack broadly enough to confirm that the accumulated current behavior still coexists correctly across the supported equipped families plus human Fist before entering the separate compatibility gate.

Protect during the test:

```text
weapon RIGHT / LEFT / BOTH / OFF
Power / Pierce / SimpleWhirl / Hack current behavior
C1 generation-scoped occurrence/dedupe identity
C1-R1 exact-source terminal repair
human raw-8 FIST production semantics
unmarked/native fallback
one live collision twin only
```

Do not broaden this regression into:

```text
new Fist research
monster/raw55 work
AttackContinuationProtection implementation
Raise/speed work
new marker vocabulary
source/lifecycle redesign
```

After native mixed regression:

```text
final New Balance + Script_AttackCollision / relevant Jackydima mixed compatibility regression
-> collision knowledge/evidence closure
-> migrate mature collision behavior into Script_G3AnimationBehaviors
-> diagnostics-free collision integration validation
-> promote collision checkpoint to main
-> create feature/raise-attack-speed from updated main
```

---

## Evidence / archive maintenance state

The September collision/Fist raw artifacts have now reached a stable-subsystem checkpoint. During the current maintenance pass, processed canonical artifacts should be moved unchanged from `research/raw/` to `research/archive/` and their active references repointed accordingly.

Leave genuinely unprocessed or unidentified artifacts in `research/raw/`.

The established evidence-publish workflow remains POP-05/POP-06:

```text
freeze test + exact raw filename
-> User runs locally
-> copy complete unchanged log into research/raw
-> stage only intended artifact
-> commit/push active branch
-> report SHA
-> Normal Chat reads committed artifact from GitHub
-> interpret/promote evidence
-> archive after processing
```

Do not substitute Chat attachment for this repository evidence workflow unless a Chat attachment is explicitly requested for a separate reason.

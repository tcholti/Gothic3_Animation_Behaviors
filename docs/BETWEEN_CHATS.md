# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — C1-R1 closed; read-only architecture review next

C1-O2-P2 is closed for the tested outer-acquisition/binding model. Canonical result: **EV-205**.

C1-R1 implementation:

```text
93e5a2f2d4839ec908a8940927294217dd961c7a
```

Validated C1-R1 DLL:

```text
Script_FrameCollisionTest.dll
Length: 466432
SHA256: 449AC6BECB38B8627CAFAEA6311F4CC0697B91328A15D63B3446DA4766D3EAB5
Built/live match: True
```

Canonical C1-R1 evidence: **EV-206–EV-207** in `docs/EVIDENCE_LEDGER_STEP_D.md`.

Validation state:

```text
R1-A independent source audit = PASS
R1-B build / identity / isolated load-unload = PASS
R1-C targeted positive repair = PASS
R1-D no-op / reaction / GetUp controls = PASS
R1-E Dual source-specific repair = PASS
R1-E compact marker regression = PASS
R1-E broad mixed exercised coverage = PASS
R1-E focused unarmed/crossbow negative closure = PASS
C1-R1 CONTROLLED VALIDATION = CLOSED
```

Accepted repair rule remains:

```text
exact outstanding source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList()
→ verify exact resulting group Item_Equipped(5)
```

Everything outside that predicate remains no-op/unresolved and non-mutating. Native cleanup retains precedence. Dual sources remain independent. Marker timing/ownership remains separate from terminal collision safety. Fist/body semantics remain separate from weapon-style Item_Attack cleanup.

Two qualifications remain explicit but do not reopen C1-R1:

```text
1. An outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED case has not been positively runtime exercised.
2. Natural NPC combat and marked Staff traffic support actor-general stability, but no positive NPC destructive-abandonment / C1 physical-repair case is claimed.
```

Do not invent another broad R1 matrix solely to force either case.

---

## Current immediate responsibility — read-only architecture/code review

Do **not** migrate C1-R1 directly into `src/Script_G3AnimationBehaviors`.

Normal Chat should first review the current source structure of:

```text
prototypes/Script_FrameCollisionTest/
src/Script_G3AnimationBehaviors/
```

The review is read-only. Its purpose is to classify the existing code by responsibility and define a semantic-preserving modular boundary before any refactor is frozen.

Review questions:

```text
- which code is required production behavior?
- which code is research diagnostics only?
- which code owns physical Gothic hooks / transport?
- which code belongs to CollisionLifecycleGuard?
- which code belongs to frame-marker ownership/control?
- which code belongs to physical source adapters?
- which marker bookkeeping is still independently required?
- which marker-lifetime inference may now be redundant because C1 provides a proven execution identity?
- which shared hook paths create compatibility constraints with New Balance / Jackydima DLLs?
- what should the eventual one-DLL module/event boundaries be?
```

No source edit is authorized by this review. After the review, Normal Chat should freeze the smallest **behavior-preserving modular refactor** of the research DLL and only then hand a bounded implementation to Work/local execution if appropriate.

---

## Agreed forward roadmap

This order is provisional architecture guidance and may be course-corrected by source/runtime evidence. Do not skip phases merely because a later destination is already known.

```text
1. Full read-only Script_FrameCollisionTest + existing production-DLL architecture/code review.
2. Semantic-preserving modular refactor of Script_FrameCollisionTest; central engine bridge remains sole hook owner.
3. Revalidate the existing collision baseline after structural refactor.
4. Audit marker bookkeeping against the proven C1 execution authority; remove only checks proven redundant while preserving independent marker invariants.
5. Expand the existing RIGHT/LEFT/BOTH/OFF marker system one supported equipped-melee attack mechanism at a time, with compact regressions.
6. Investigate/prove a separate Fist source adapter only after equipped-melee marker coverage is stable; do not force Fist into weapon-style Item_Attack semantics.
7. Run a full marker + lifecycle-guard regression after marker/source expansion.
8. Add a separate modular AttackContinuationProtection responsibility for the held-Use2 bad skip only after the marker system is mature; keep CollisionLifecycleGuard unchanged underneath as fail-safe.
9. Validate guard + markers + continuation protection together, including native reaction/non-attack controls.
10. Test the mature research DLL against New Balance and the relevant Jackydima DLL stack; compatibility is mandatory.
11. Only then redesign `Script_G3AnimationBehaviors` around the same modular engine-bridge/event architecture and migrate the proven collision modules.
12. Keep Raise and playback-speed control as independent modules. Re-evaluate the current AttackSpeed hook strategy because the existing direct `GetAnimationSpeedModifier` hook has a New Balance compatibility concern.
13. Perform a final full `Script_G3AnimationBehaviors` + New Balance/Jackydima compatibility regression before stable promotion.
```

Target architectural rule:

> **One DLL may contain multiple independent behavior modules, but one central engine-bridge layer owns each shared Gothic hook. Feature modules consume authoritative engine events; they do not compete with one another for the same physical hook.**

Diagnostics remain observers and must be removable/reducible without changing production behavior.

Future held-Use2 investigation remains separately documented in `docs/BAD_SKIP_FUTURE_INVESTIGATION.md`.

# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — C1-R1 validation closed; production integration planning next

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

The final focused negative run is:

```text
research/raw/2026-08-30_c1r1e_unarmed_crossbow_negative_closure.log
commit: 8ce64abe4718b5ae42a79f793aea063874010649
bytes: 5692140
```

It independently exercised genuine unarmed/Fist and crossbow gameplay, with supplemental bow, magic, NPC Staff-marker and broad NPC/weapon traffic. The whole run contains zero `REPAIRED_TO_ITEM_EQUIPPED`, zero `REPAIR_DIVERGED_FROM_ITEM_EQUIPPED`, zero `UNRESOLVED_NOT_EQUIPPED` and zero `C1 INVARIANT WARNING`. Exact Fist executions remained group 0 with zero weapon-style offense/outstanding obligation and no-op finalization; the crossbow item never became an exact tracked C1 collision source.

Two qualifications remain explicit:

```text
1. An outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED case has not been positively runtime exercised.
   Preserve the fail-closed branch; do not claim direct runtime proof of it.

2. Natural NPC combat and marked Staff traffic support actor-general hook/marker stability,
   but no positive NPC destructive-abandonment / C1 physical-repair case is claimed.
```

Neither qualification reopens C1-R1. Do not invent another broad validation matrix solely to force either case.

---

## Current responsibility — plan/freeze stable production integration

C1-R1 is validated only in the research prototype. It is **not yet production-integrated** into the stable `Script_G3AnimationBehaviors` collision core.

Normal Chat should now determine the smallest production-integration boundary that preserves the validated architecture and existing marker behavior. Do not implement merely because R1 closed; freeze the integration responsibility first.

Production integration must preserve:

```text
C1 monotonic generation as durable execution identity
P1/P2 lightweight pre-Combat acquisition/bridge behavior
exact per-source offensive obligations
native cleanup always gets first opportunity
post-native-AISetState finalization
exact current-equipped liveness gate before source dereference/mutation
exact source-specific Item_Attack(7) -> Item_Equipped(5) repair
no ClearTriggeredList() in terminal repair
Dual source independence
marker RIGHT/LEFT/BOTH/OFF semantics and existing marker bookkeeping
Fist/body separation
unsupported-source fallback
no family/action/input/cause cleanup matrix
no polling/timer/world scan
```

Do not automatically combine production integration with:

```text
held-Use2 / Alternative-AI root behavior changes
marker-core simplification
Raise work
playback-speed work
new source-family expansion
```

Future held-Use2 root investigation remains separate in `docs/BAD_SKIP_FUTURE_INVESTIGATION.md`; even if pursued later, it does not replace the validated C1-R1 fail-safe.

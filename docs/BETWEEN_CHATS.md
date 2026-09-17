# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-17

## Current Bridge — PERMANENT RAW55 CORE BEHAVIOR PASS; DIAGNOSTIC FALSE-POSITIVE CORRECTION FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Canonical family-specific causal evidence remains closed through **EV-294**.

Permanent raw55 contract:

`docs/COLLISION_RAW55_PRODUCTION_ARCHITECTURE.md`

Permanent implementation:

```text
21853392f146febbc2d1aad4e501baa741fd65b2
```

Normal Chat independent source review: **PASS**.

## Local product validation already PASS

```text
Script_FrameCollisionBehaviorTest Release build PASS
Script_FrameCollisionTest Release build PASS
behavior-only isolated deployment / functional smoke PASS
diagnostic deployment / startup / clean unload PASS
```

Behavior-only SHA256:
`0EB935FCBFD5B7A2D2D56683971641EA42B9F7FF074D5B7F2EC2FD353594833A`

Diagnostic candidate SHA256:
`4A402FD2300C95344657719895BCEF49F07AD417AAFCF1287F5421F641311FCA`

## First permanent raw55 diagnostic acceptance — BEHAVIOR CORE PASS

Evidence upload commit:

```text
6ae7dcc315e0859ab8ff061f1576d52206d21008
```

Source:

```text
research/raw/2026.09.17_troll_raw55_permanent_acceptance.log
SHA256 AA866E70BF2DB42CF7CE73607040443A9F8725F05CCFDDB01116E582956DA6A7
Git blob 8ae8cd8da6e958f6b7f0b139a17467fcc7dd3c6b
150110 bytes
1011 lines
```

Derived:

`research/derived/2026.09.17_troll_raw55_permanent_acceptance_large_log/`

User observed all exercised two-swing attacks damage twice; Sprint knocked the player down. The second run contains all required factual raw55 families.

Representative factual routes:

```text
Quick C1=3
marker1 SP0 5->7 + clear
-> first OnDamage
marker2 SP1 group7 clear-only / no group request
-> second OnDamage
-> native 7->5
-> outstanding zero / NO_OP_NO_OUTSTANDING

true Power C1=6
early native 5->7 suppressed
marker1 Action2/SP1 5->7, no clear
-> first OnDamage
marker2 group7 clear-only / no group request
-> second OnDamage
-> native 7->5
-> outstanding zero / NO_OP_NO_OUTSTANDING

Normal C1=33
marker1 SP0 5->7 + clear
-> first OnDamage
exact Script_Game.dll+0x386C6 ALL clear suppressed
marker2 SP1 group7 clear-only / no group request
-> second OnDamage
-> native 7->5
-> outstanding zero / NO_OP_NO_OUTSTANDING

Sprint-origin C1=42
early native 5->7 suppressed
marker1 Origin=SPRINT Current=SPRINT Action9/SP1 5->7, no clear
-> first OnDamage
same C1/right transitions to Action2
marker2 Origin=SPRINT Current=POWER Action2/SP1 group7 clear-only
-> second OnDamage while PC_Hero is LieKnockDown_Begin
-> native 7->5
-> outstanding zero / NO_OP_NO_OUTSTANDING
```

No `C1 INVARIANT WARNING` was found in the three full-source parts. The representative raw55 routes require no terminal repair and finalize cleanly.

## Diagnostic-only acceptance gap

The older generic `CollisionDiagnostics::LogAttackCallbackOwnership()` still treats every FIST-bearing execution whose raw8 resolver is not `gEUseType_Fist` as a contradiction:

```cpp
result.decision.hasFistMarkers
&& fistUseType != static_cast<GEInt>(gEUseType_Fist)
```

Permanent raw55 legitimately has:

```text
FIST marker
raw8 resolver absent
requiredSourceMask none
current RIGHT source PhysicalFist / UseType55
```

Therefore the run contains 19 false `CORE ATTACK OWNERSHIP ANOMALY` blocks even though the dedicated permanent raw55 records prove correct behavior.

This is a CORE diagnostic classification defect, not a behavior failure.

Frozen correction:

`docs/COLLISION_RAW55_CORE_DIAGNOSTIC_CLASSIFICATION_CORRECTION.md`

## Current responsibility — BOUNDED WORK DIAGNOSTIC CORRECTION

Work may modify only:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
```

Correct only the stale compact CORE contradiction predicate so the already-supported factual raw55 source shape is routine rather than anomalous. Do not call into `PhysicalFistCollision` and do not duplicate its full eligibility state machine.

Preserve all behavior/core modules unchanged.

**WORK BUILD EXECUTION IS PROHIBITED.**

After Work returns:

```text
Normal Chat independent diff review
-> rebuild Script_FrameCollisionTest only
-> diagnostic deploy/startup
-> small marked raw55 control proving legitimate raw55 Classification=ROUTINE and no ownership-anomaly block
-> continue remaining focused sentinels:
   unmarked raw55 native fallback
   raw8 FIST
   one equipped authored-marker route
```

Do not rerun the full four-family Troll acceptance unless the diagnostic-only correction unexpectedly changes behavior-facing source.

## Still paused

```text
NO broad standalone collision regression yet
NO New Balance final regression yet
NO collision migration into src/Script_G3AnimationBehaviors yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

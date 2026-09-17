# Session Entry Point

**Purpose:** Minimal durable front door for current Gothic 3 Animation Behaviors work.

**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-17

> **WORK BUILD RULE:** Unless a frozen task explicitly authorizes Work to build, Work must not invoke or probe build tooling. Source/static audit -> publish -> STOP. Local build belongs to User + Normal Chat after independent source review.

> **MANDATORY FEATURE-DEVELOPMENT RULE:** Unknown behavior is researched in an isolated probe. Proven behavior is promoted into the permanent module that owns it. Hooks remain transport-only; temporary probe scaffolding is removed rather than promoted wholesale.

> **RELEASE-PURITY RULE:** `Script_FrameCollisionTest` is diagnostic research only. The eventual shipped plugin remains `Script_G3AnimationBehaviors`; `PhysicalFistProbe` is not production architecture.

> **LARGE-LOG RULE:** Do not orient by scanning raw/archive logs. Use canonical EV first and the committed derived package for large-log retrieval. Processed source evidence moves unchanged to `research/archive/`.

Immediate handoff: `docs/BETWEEN_CHATS.md`  
Latest canonical evidence: **EV-292** in `docs/EVIDENCE_LEDGER_291_ONWARD.md`

## Current checkpoint

```text
raw55 Quick       CLOSED/PASS through EV-273
raw55 true Power  first-contact CLOSED/PASS through EV-276
raw55 Normal      repeated-FIST contact rearm CLOSED/PASS — EV-292
raw55 Sprint      first-contact CLOSED/PASS through EV-282
raw55 two-FIST cross-family runtime CLOSED — EV-283
raw55 Normal native 7->7 setter as second-rearm source REJECTED — EV-288
raw55 Normal native trigger-bookkeeping reset before marker2 CONFIRMED — EV-289
raw55 Normal exact native public ALL-clear reset operation IDENTIFIED — EV-290
raw55 Normal native ALL-clear causal necessity CLOSED/PASS — EV-291
raw55 Normal authored marker2 replacement-clear sufficiency CLOSED/PASS — EV-292
```

## EV-292 factual result

Diagnostic implementation:

```text
f2ae82991bc1c1675c6e56c45b6f1bd267f093ee
```

Local build/deploy/startup PASS:

```text
Built SHA256 = 98878AA9DE76CA04C9EEFFA07A9FD44C190E6711825231D2688FE1B75864B6E3
Live  SHA256 = 98878AA9DE76CA04C9EEFFA07A9FD44C190E6711825231D2688FE1B75864B6E3
```

Representative factual Normal C1=3:

```text
marker1 at SP0
-> exact RIGHT raw55 5 -> 7
-> marker-owned ClearTriggeredList
-> hit1
-> PC_Hero visited/count1

native Normal transition
-> EV-288 exact native 7 -> 7 setter suppressed
-> EV-291 exact Script_Game +0x386C6 ALL clear suppressed
-> PC_Hero remains visited/count1
-> original _AI_Attack completes SP0 -> 1

marker2 at SP1
-> same C1 / same exact RIGHT raw55 group7
-> PRE PC_Hero visited/count1
-> one authored replacement ClearTriggeredList
-> actual clear observed from Script_FrameCollisionTest.dll
-> POST PC_Hero absent / aligned arrays
-> later hit2 returns

native exact RIGHT 7 -> 5 cleanup
-> outstanding = 0
-> clean C1 finalization
```

User visual result: **both swings connected/damaged**.

Conclusion:

> Authored Normal marker2 `ClearTriggeredList()` is sufficient to replace Gothic's suppressed native between-contact clear and causally owns the second same-C1 contact rearm in the tested route.

## Immediate next responsibility — NORMAL CHAT DESIGN/FREEZE ONLY

Do not launch another Work task automatically.

Normal repeated-FIST contact-rearm causality is closed for the tested raw55 route. The next planned family is **Power repeated-FIST rearm**.

Before any Work implementation, Normal Chat must reconstruct only the already-proven Power first-contact/two-FIST route and freeze the smallest one-variable repeated-contact probe. Do not copy Normal's SP0/SP1 assumptions into Power without evidence.

## Evidence retrieval discipline

Do not scan `research/raw/` or `research/archive/` during orientation.

Use in this order:

1. this file;
2. `BETWEEN_CHATS.md`;
3. EV-292 in `EVIDENCE_LEDGER_291_ONWARD.md`;
4. the EV-292 derived package only for exact runtime verification;
5. prior Power canonical evidence only when designing the next probe.

EV-292 derived package:

```text
research/derived/2026.09.17_troll_raw55_normal_marker2_replacement_clear_large_log/
```

Source SHA256:

```text
4AE9700C2944FC2940AB194E018478B88EF00A90157BC8DC3AC1FDB48BEDD91D
```

## Still paused

```text
NO permanent PhysicalFistCollision
NO promotion/copy of PhysicalFistProbe scaffolding
NO Power/Sprint repeated-FIST intervention until separately frozen
NO permanent raw55 architecture until Power + Sprint repeated-contact work closes
NO New Balance final regression yet
NO Raise/speed work yet
NO AttackContinuationProtection work
```

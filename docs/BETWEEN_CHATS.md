# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — C1-O2-P2-D broader stability

C1-O2-P2 behavior implementation:

```text
cc51c67c19425be4e4d6a4838803ed3e66b2a071
```

P2 build-identity banner correction:

```text
8b6a5873b8caa27b469ae831d25bf155a6c7f189
```

Independent Normal Chat P2-A source audit: **PASS**.

Validated P2 built/live DLL:

```text
Script_FrameCollisionTest.dll
Length: 465408
SHA256: 1081B287912DB9A368164DDE13542A7EC2D6E5DBB0AA29B04C19BD7932D92C7C
Built/live match: True
```

P2-B isolated main-menu load/unload: **PASS**.

P2-C targeted player 2H Normal + GetUpAttack meaning test: **PASS**.

P2-C raw:

```text
research/raw/2026-08-30_c1o2p2_player_2h_normal_getup_bridge_consumption.log
```

P2-C evidence commit:

```text
0697437cf9b3036367e9bdba2ec85576f86ddbe3
```

The User performed three ordinary clean 2H Normal controls followed by five GetUpAttack executions. Some GetUpAttack inputs were attempted promptly after knockdown/sit-up and some after remaining seated longer. The runtime log does not directly label the User's input-timing category, so do not invent a classifier from that variation; all five positive acquisition events converged on the same `_AI_GetUpAttack` / `OnAI_GetUpAttack` path with native `gEAction_GetUpAttack` (`30`) at the acquisition point.

The five pre-Combat generations were:

```text
20
33
45
54
64
```

For each one, the log shows:

```text
PRECOMBAT_ACQUIRED
→ first C1 OFFENSE REQUEST while OUTER_BOUND
→ PRECOMBAT_BRIDGE_CONSUMED on the SAME generation
→ later timer C1 OFFENSE REQUEST while PERSISTED
→ C1 CLEANUP FULFILLED on the SAME generation/source
→ AISetState finalization = NO_OP_NO_OUTSTANDING
```

Whole-run failure signals:

```text
UNOWNED_PLAYER_OFFENSE_REQUEST = 0
PRECOMBAT_BRIDGE_UNCONSUMED_AT_DISPATCH_RETURN = 0
C1 INVARIANT WARNING = 0
```

The three initial ordinary Normal controls remained on the ordinary CombatMove-created `_AI_Attack` generation path and cleaned normally.

Physical repair remained disabled.

---

## Current responsibility — P2-D

P2-C has proved the bounded positive meaning. The next gate is broader stability/integration coverage before C1-O2 can be called complete.

Do **not** change implementation before P2-D unless the broader run exposes a contradiction.

P2-D should cover the existing C1 runtime matrix rather than inventing new classification rules:

```text
ordinary clean attacks / multiple relevant weapon families
legitimate reaction interruptions
pre-activation interruption/no-offense cases
known armed destructive abandonment as a positive shadow WOULD_REPAIR stress case
later legitimate attack after stale 7 -> 7 when naturally produced
repeated GetUpAttack opportunities when they occur
normal traversal / draw-holster / state churn around combat
```

Expected model:

```text
pre-Combat GetUp offense
→ temporary live-frame bridge only until matching CombatMove
→ durable monotonic generation thereafter

ordinary attacks
→ unchanged CombatMove-created generation path

successful native cleanup
→ exact source obligation fulfilled

destructive AISetState with outstanding exact live/equipped source
→ existing shadow WOULD_REPAIR only
```

Specifically inspect for:

```text
UNOWNED_PLAYER_OFFENSE_REQUEST
PRECOMBAT_BRIDGE_UNCONSUMED_AT_DISPATCH_RETURN
live-frame/binding mismatch or overlap invariants
generation replacement where reuse was expected
NULL_ARGUMENTS / unresolved binding failures
unexpected physical collision change
crash / abnormal unload
```

Physical repair remains **OFF**.

Do not freeze physical-repair implementation until P2-D broader stability is interpreted by Normal Chat.

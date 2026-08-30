# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — C1-O2-P2 closed; physical-repair gate design next

C1-O2-P2 behavior implementation:

```text
cc51c67c19425be4e4d6a4838803ed3e66b2a071
```

P2 build-identity banner correction:

```text
8b6a5873b8caa27b469ae831d25bf155a6c7f189
```

Validated P2 built/live DLL:

```text
Script_FrameCollisionTest.dll
Length: 465408
SHA256: 1081B287912DB9A368164DDE13542A7EC2D6E5DBB0AA29B04C19BD7932D92C7C
Built/live match: True
```

Canonical promoted evidence:

```text
EV-205
```

P2 validation result:

```text
P2-A independent source audit = PASS
P2-B isolated load/unload = PASS
P2-C targeted GetUp meaning = PASS
P2-D broader gameplay ownership/stability = PASS
P2-D broad-run raw itself did not capture shutdown
P2-D dedicated clean shutdown closure = PASS
```

P2-D canonical broad-run raw identity:

```text
research/archive/2026-08-30_c1o2p2_broader_combat_interruption_stability.log
SHA256: 50AE4944C23DB30C78CE0373E241DDAAC32C252C2D8563584871F098C96BB041
Bytes: 12123937
Lines: 398143
```

Derived package:

```text
research/derived/2026-08-30_c1o2p2_broader_combat_interruption_stability_large_log/
package commit: 680d5068a16034e122aeff2ef5528e9cc16477bf
```

Whole-run P2-D facts:

```text
Event blocks = 15387
C1 OFFENSE REQUEST = 306
C1 CLEANUP FULFILLED = 264
C1 FINALIZATION = 436
C1-O2 OUTER BINDING = 536
COMBATMOVE FULLSTOP STACK = 157
AISETSTATE CALLSITE = 1112
ENGINE SetCollisionGroup = 844
```

Exactly 13 pre-Combat GetUp bridges were observed. Generations:

```text
200 298 314 364 384 473 622 658 660 671 726 857 868
```

For all tested positive bridges:

```text
PRECOMBAT_ACQUIRED
→ first exact-source offense on same OUTER_BOUND generation
→ matching CombatMove
→ PRECOMBAT_BRIDGE_CONSUMED on SAME generation
→ temporary native binding gone before RunScriptFunction return
→ later timer offense remains on durable PERSISTED generation
→ native cleanup fulfills that same generation/source when cleanup occurs
```

Failure-signal result:

```text
C1 INVARIANT WARNING = 0
UNOWNED_PLAYER_OFFENSE_REQUEST = 0
unconsumed bridge invariant = 0
error/exception signal = 0
failure signal = 0
mismatch/divergence signal = 0
stale signal = 0
unresolved/orphan signal = 0
unsafe/bad skip signal = 0
```

There were 29 actual shadow `WOULD_REPAIR` finalization outcomes. Representative 2H, Staff, 1H/Torch and Dual contexts show exact live/equipped sources with real outstanding offense and no observed native cleanup at destructive AISetState. Physical collision remained unchanged by the guard.

A whole-run consistency check gives:

```text
306 offense-request events
- 13 second GetUp requests belonging to the same 13 early-acquired obligations
= 293 observed offensive source obligations

264 native cleanup fulfillments
+ 29 shadow WOULD_REPAIR outcomes
= 293
```

Two observed Staff `GetUpParade` action-31 sequences traversed their `Hit`/Recover resources without a C1 offense request. This supports consequence-based collision ownership; the filename's `Hit` token alone does not imply an offensive source obligation.

The original P2-D broad-run raw file ended during continued gameplay and therefore did not itself contain `Script_FrameCollisionTest unloading.`. A dedicated clean shutdown-closure run was then performed with the same validated P2 DLL: launch Gothic 3 → load a save → brief idle → return to menu → normal Exit. That raw log ends with `Script_FrameCollisionTest unloading.` and therefore closes the shutdown qualification for the exact tested P2 binary. Evidence commit:

```text
4946d382041e9ec86400291395e5acbad77b1de6
research/archive/2026-08-30_c1o2p2d_clean_shutdown_closure.log
```

The User also reported that P2 subjectively felt smoother than several previous research builds. Preserve only as an uncontrolled observation; no causal performance improvement is established.

---

## Current responsibility — Normal Chat physical-repair gate design

C1-O2 is closed for the tested outer-acquisition/binding model.

Do **not** send a Work implementation task yet.

Normal Chat must now retrieve only the exact current lifecycle/finalizer source and architecture needed to answer:

> What is the smallest controlled native-equivalent physical repair that can replace the already-proven shadow `WOULD_REPAIR` outcome while preserving exact-source ownership, source liveness, native-cleanup precedence, legitimate reaction behavior, inherited `7 -> 7` attribution and all current no-op cases?

Preserved design constraints:

```text
repair is consequence/source-obligation based, not family/action/input/cause/time based
only the exact outstanding source may be repaired
current equipped identity/liveness must be established before dereference/mutation
observed native cleanup always wins → no repair
no arbitrary adoption of unrelated group-7 state
no polling / timer / world scan
no FullStop-as-cleanup-authority rule
no marker-core refactor
no restoration of rejected C1-O2 dispatch machinery
```

Physical repair remains **OFF** until Normal Chat freezes a new bounded gate and its runtime falsification plan.

# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — C1-R1 controlled physical repair

C1-O2-P2 is closed for the tested outer-acquisition/binding model. Canonical result: **EV-205** plus the dedicated shutdown-closure evidence commit `4946d382041e9ec86400291395e5acbad77b1de6`.

Validated P2/shadow baseline DLL:

```text
Script_FrameCollisionTest.dll
Length: 465408
SHA256: 1081B287912DB9A368164DDE13542A7EC2D6E5DBB0AA29B04C19BD7932D92C7C
```

Accepted ownership model:

```text
live ScriptFunction frame
= temporary pre-Combat offense -> CombatMove correlator only

C1 monotonic generation
= durable plugin execution identity

successful Item_Attack request
= exact physical-source cleanup obligation

successful transition away from Item_Attack
= obligation fulfilled

destructive AISetState with exact obligation still outstanding
= terminal repair checkpoint
```

P2-D broad evidence closed 293 observed offensive source obligations exactly as:

```text
264 observed cleanup fulfillments
+ 29 shadow WOULD_REPAIR outcomes
= 293
```

No C1/P2 binding/invariant failure signal was present in the broad run.

---

## Frozen gate — C1-R1 Controlled Native-Equivalent Physical Repair

### Question

> Can the existing proven `WOULD_REPAIR` branch perform exactly the same narrow weapon-source reset Gothic 3 uses for legitimate cleanup — `Item_Attack(7) -> Item_Equipped(5)` on the exact live/equipped outstanding source — without changing any execution that already cleaned itself, never requested offense, is no longer safely live, or belongs to the other Dual source?

### Why this is the minimum sufficient mutation

Tested ordinary weapon cleanup across Normal, Power, Quick, SimpleWhirl, full Whirl, Pierce, Hack, Finishing and GetUpAttack uses an exact collision-group reset from `Item_Attack(7)` to `Item_Equipped(5)`. The tested legitimate reaction cleanup route uses the same weapon reset semantics.

The existing marker OFF/source-deactivation path also uses `SetCollisionGroup(Item_Equipped)` and deliberately does **not** call `ClearTriggeredList()`. Trigger-list clearing belongs to offensive activation/rearm, not cleanup.

Therefore C1-R1 adds no second cleanup action, no animation/state change and no family/cause logic.

---

## Frozen implementation responsibility

Make **only** the existing `CollisionLifecycleGuard::FinalizeAfterAISetState()` shadow `WOULD_REPAIR` branch physically perform the proven exact-source `7 -> 5` reset.

Expected source changes:

```text
prototypes/Script_FrameCollisionTest/CollisionLifecycleGuard.cpp
prototypes/Script_FrameCollisionTest/Script_FrameCollisionTest.cpp   # startup identity only
```

No public/header change is expected. If a concrete compile/API contradiction requires another source file, STOP and report it rather than broadening architecture.

### Preserve finalization timing exactly

Existing AISetState order remains:

```text
CaptureFinalizationToken(owner)
→ native AISetState exactly once
→ invalidate transient dispatch state
→ FinalizeAfterAISetState(token)
```

Do not move repair before native AISetState. Native cleanup occurring during the original call must continue to win automatically and make finalization a no-op.

### Exact per-source decision

After native AISetState, for each tracked source:

```text
outstandingCleanup == false
→ NO_OP_NO_OUTSTANDING
→ no mutation

outstandingCleanup == true
+ source is NOT one of the actor's exact current equipped RIGHT/LEFT source pointers
→ UNRESOLVED_NOT_EQUIPPED
→ do not dereference remembered source
→ no mutation

outstandingCleanup == true
+ exact current equipped identity establishes source liveness
+ actual collision group != Item_Attack
→ NO_OP_PHYSICALLY_CLEAN_RECONCILED
→ no mutation

outstandingCleanup == true
+ exact current equipped identity establishes source liveness
+ actual collision group == Item_Attack
→ call SetCollisionGroup(Item_Equipped) exactly once on THAT source only
→ do NOT call ClearTriggeredList()
→ re-read resulting collision group
```

A repair is successful only when the resulting group is exactly `Item_Equipped(5)`.

Do not mutate the other tracked source merely because the same generation contains two sources. Dual remains exact-source/per-obligation.

### Use the existing SetCollisionGroup path

The repair should use the normal existing entity/Entity `SetCollisionGroup(Item_Equipped)` API path. Do not bypass or duplicate the existing SetCollisionGroup hook.

This intentionally lets the already-tested SetCollisionGroup observation path see the reset, retire marker-owned source bookkeeping through its existing logic, and observe the source transition away from `Item_Attack`.

Do not add a new hook, timer, poller, world scan, source table or repair dispatcher.

### Finalization logging must not be interleaved

Important implementation constraint:

`FinalizeAfterAISetState()` currently starts printing the `C1 FINALIZATION` block before iterating sources. A physical `SetCollisionGroup()` call will re-enter the existing SetCollisionGroup hook and emit its own complete diagnostics. If repair is called while the finalization block is half-written, those nested logs will splice into and corrupt that event block.

Therefore restructure only the finalizer's diagnostics into two phases:

```text
phase 1
classify / perform any exact repair
→ store per-source finalization result in fixed stack-local storage
  (maximum source count is already 2)

phase 2
emit one complete C1 FINALIZATION block from those stored results
```

No heap allocation or new persistent/global state is needed for this.

Preserve enough per-source diagnostics to prove at least:

```text
Outcome
LivenessEstablished / StillEquipped / CurrentSideMask
OutstandingBeforeFinalization
CleanupObservedBeforeFinalization
ActualGroupBeforeRepair
RepairAttempted
RepairRequestedGroup when attempted
ActualGroupAfterRepair when attempted
PhysicalCollisionChanged for that source
```

Recommended positive outcome name:

```text
REPAIRED_TO_ITEM_EQUIPPED
```

If the setter does not end at exact group 5, emit a high-signal repair-failure/divergence outcome. Do not retry, poll or invent a fallback mutation in C1-R1.

The generation record is still retired once after finalization, as before.

### Startup identity

Replace the P2-only startup identity with one exact C1-R1 line that makes physical mutation unmistakable. Recommended text:

```text
STEP C1-R1 PHYSICAL REPAIR: exact live/equipped outstanding Item_Attack source resets to Item_Equipped at destructive AISetState finalization; native cleanup/no-op paths unchanged; no ClearTriggeredList.
```

Do not claim broader production completion in the banner.

---

## Explicit non-responsibilities

C1-R1 must NOT change:

```text
execution acquisition
generation ownership
P1/P2 RunScriptFunction bridge behavior
CombatMove behavior
AISetState/AIFullStop/SetCollisionGroup hook transport
finalization trigger/authority
marker activation timing
marker RIGHT/LEFT/BOTH/OFF semantics
ClearTriggeredList activation/rearm behavior
family/action/input/state-name classification
held-Use2 / 2500-ms external behavior
native/modded block or interruption policy
Fist/body-source semantics
```

Do not add player-only production semantics. The guard remains actor/source-general; runtime validation will expand deliberately.

Do not reconnect rejected `g_ScriptFunctionDispatchStack` / `BeginScriptFunctionDispatch()` / `EndScriptFunctionDispatch()` machinery.

---

## C1-R1 validation sequence

### R1-A — independent Normal Chat source audit

Before build, verify the implementation matches this frozen responsibility exactly.

### R1-B — build / isolated load

Build, exact DLL identity, main-menu load/unload with the C1-R1 banner. No combat.

### R1-C — targeted positive repair

Reproduce a known armed destructive abandonment on a controlled player weapon source.

Expected:

```text
real offense obligation
→ no native cleanup
→ destructive AISetState
→ exact source still live/equipped at Item_Attack(7)
→ one C1-R1 repair request to Item_Equipped(5)
→ resulting group exactly 5
→ REPAIRED_TO_ITEM_EQUIPPED
```

Then perform a later legitimate attack with that source. Because the stale state was physically removed, its new offense should normally begin `5 -> 7`, not inherit the old stale `7 -> 7`.

### R1-D — no-op controls

Verify zero repair mutation for:

```text
ordinary clean completion
legitimate reaction/knockdown cleanup
pre-activation interruption/no offense
clean GetUpAttack with P2 acquisition + native cleanup
GetUpParade / defensive no-offense case
```

### R1-E — source-specific / marker / broader stability

Only after targeted positive/no-op meaning passes:

```text
Dual RIGHT/LEFT source-specific repair control
compact marked-source regression if repair interacts with marker-owned state
broader mixed player/NPC/negative stability as appropriate
```

Physical repair is not considered production-integrated merely because R1-C succeeds.

---

## Work execution rule

Work receives this frozen responsibility through the small launcher only. It should:

```text
read SESSION_ENTRYPOINT.md
read this BETWEEN_CHATS.md
follow WORK_IMPLEMENTATION_PROTOCOL.md
inspect only source/API material necessary for C1-R1
implement exactly C1-R1
source audit
git diff --check for editable source
commit/publish
STOP
```

Do not build or run Gothic 3 in Work.

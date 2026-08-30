# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — second-pass architecture CLOSED; rewrite contract FROZEN; unchanged runtime baseline NEXT

C1-R1 controlled validation remains closed through **EV-206–EV-207**.

The complete first per-CPP review and second-pass architecture synthesis are now closed.

Frozen bounded rewrite contract:

```text
docs/SECOND_PASS_REWRITE_CONTRACT.md
```

Contract creation commit:

```text
50f0874fb51853eee910ef63c45914bc935fca88
```

**Do not implement that rewrite yet.** First run the compact runtime baseline on the current unchanged post-EngineBridge source/logger so the EngineBridge extraction is causally isolated from every later architectural/logging change.

---

## Mandatory project-wide release rule

Canonical authority:

```text
docs/GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md
```

> **The public Gothic 3 behavior DLL contains behavior only. Research diagnostics are a separate build product and are not compiled into the release binary.**

This applies to collision, lifecycle repair, Raise, speed, AttackContinuationProtection, target acquisition, climbing and all future Gothic 3 behavior modules.

Long-term model:

```text
shared behavior architecture
→ diagnostics-free RELEASE build
→ separate instrumented DIAGNOSTIC twin used in place of release during controlled testing
```

Never plan to deploy release and diagnostic twins together unless a future architecture explicitly proves safe coexistence.

---

## Closed structural work already compiler-validated

### CollisionSources extraction

```text
43fa1e719b5af716c54e17430c101251bbc36ff8
```

### EngineBridge extraction

Frozen base:

```text
d0132b69df3add63641bc5d5fd5779f1037eaa99
```

Implementation head before later documentation-only commits:

```text
32ff447c9a678ba18c8234310564ff2475ba7dfb
```

Local validation already confirmed:

```text
git diff --check = PASS
CMake Release build Script_FrameCollisionTest = PASS
```

No runtime baseline has yet been run after EngineBridge extraction.

---

## Proven behavior that must remain unchanged

### C1 lifecycle / repair

```text
real attack execution
→ monotonic C1 generation
→ successful exact-source Item_Attack request creates/refreshes obligation
→ successful later transition away from Item_Attack fulfills obligation
→ destructive post-native-AISetState finalization checks only remaining obligations
```

Terminal repair remains exactly:

```text
exact outstanding source
+ exact current equipped RIGHT/LEFT identity establishes liveness
+ actual group == Item_Attack(7)
→ exactly one SetCollisionGroup(Item_Equipped)
→ no ClearTriggeredList()
→ verify exact resulting group Item_Equipped(5)
```

Native cleanup retains first opportunity. C1's monotonic generation remains durable identity. The proven P2 live ScriptFunction frame is temporary pre-Combat correlation only.

Two qualifications remain explicit but do not reopen R1:

```text
1. No positive runtime exercise of an outstanding LivenessEstablished=0 / UNRESOLVED_NOT_EQUIPPED branch.
2. No positive NPC destructive-abandonment / C1 physical-repair case is claimed.
```

### Marker behavior

Preserve:

```text
exact current-motion marker ownership
current Normal / Quick / full-Whirl support
RIGHT / LEFT / BOTH / OFF exact-set semantics
authored occurrence budgets
same-update duplicate/replay protection
repeated-contact ClearTriggeredList rearm
Quick/full-Whirl StatePosition suppression
marker-owned source/window retirement
OFF as intra-Hit gap, not terminal cleanup
late/dead execution rejection
current Fist research behavior
unmarked/unsupported native fallback
```

Do not simplify marker bookkeeping during the frozen rewrite. EV-131–EV-133 and EV-167 remain the key evidence that occurrence/execution retirement has independent proven meaning.

---

## Second-pass conclusions now frozen

### 1. `HookBridgeRuntime` classification corrected

It is **behavior infrastructure**, not diagnostics, because the marker duplicate predicate uses the elapsed-millisecond clock as part of acceptance.

Frozen rewrite rename:

```text
HookBridgeRuntime.h/.cpp
→ RuntimeClock.h/.cpp
```

Do not redesign the proven 5 ms duplicate rule in the structural rewrite.

### 2. Marker module boundary

Frozen rewrite rename after operation extraction:

```text
CollisionControl.h/.cpp
→ FrameCollisionMarkers.h/.cpp
```

Marker-specific callback ownership/suppression policy moves out of EngineBridge into the marker module.

### 3. New physical operation seam

Create:

```text
CollisionSourceOperations.h/.cpp
```

It performs already-decided source-specific physical operations while `CollisionSources` remains factual query/resolution only.

Preserve current weapon and current research Fist operations exactly; do not generalize Fist.

### 4. Marker-cache correction

Do not permanently cache a negative marker decision when the exact current motion or valid frame-effect scan was not resolved.

Cache only factual resolved marker/no-marker decisions.

### 5. Lifecycle cleanup

Remove the rejected dormant eager ScriptFunction dispatch machinery:

```text
ScriptFunctionDispatchToken
BeginScriptFunctionDispatch / EndScriptFunctionDispatch
g_ScriptFunctionDispatchStack
InvalidateScriptFunctionDispatchAfterAISetState
its now-no-op EngineBridge call
unused <vector> afterward
```

Do **not** remove the live P2 correlator structures/functions with similar names.

`CollisionLifecycleGuard` becomes diagnostics-independent and returns compact factual results. Keep the fixed max-two-source finalizer classify/repair phase before any diagnostic formatting.

### 6. Diagnostics split

Diagnostic product:

```text
CollisionDiagnostics
= compact default proof evidence

CollisionDiagnosticsDeep
= opt-in historical/deep probes
```

Deep candidates include PlayMotion/StopMotion motion snapshots, StartRecover, AIFullStop, broad AISetState/outer-frame stacks, native-cleanup stacks/RVAs and OnTick marker lifetime tracking.

Normal diagnostic output removes stale B1–B9/O1/P1 chronology and repetitive proof-era constants.

### 7. Hook surface

Behavior-required current collision hooks:

```text
OnAI_Attack
OnAI_QuickAttack
OnAI_WhirlAttack
StartEffect
SetCollisionGroup
AICombatMoveInstr
AISetState
RunScriptFunction
```

Current diagnostic-only candidates:

```text
PlayMotion
StopMotion
AICombatMoveStartRecover
OnTick
AIFullStop
```

`AIFullStop` remains a proven explicit-this transport point and may become behavior-required later for `AttackContinuationProtection`, but current collision behavior does not require it.

### 8. Mechanical diagnostics-free prototype build

Frozen rewrite adds a behavior-only prototype target, provisionally:

```text
Script_FrameCollisionBehaviorTest
```

Existing `Script_FrameCollisionTest` remains the diagnostic research target unless a concrete build-system contradiction requires otherwise.

The behavior-only target must not compile/link diagnostic source/state/hooks.

Never deploy both targets together into Gothic 3's live `scripts` directory.

---

## Current exact gate — unchanged post-EngineBridge runtime baseline

Before any rewrite source edit:

```text
1. pull current branch
2. git diff --check
3. build current Script_FrameCollisionTest Release target
4. deploy only the intended current DLL
5. run the compact baseline below with the current unchanged logger
6. exit Gothic 3 cleanly
7. place the raw log unchanged in research/raw/
8. report completion; do not paste the large log into Chat
```

Baseline meaning must cover, in one compact session where practical:

```text
A. ordinary melee completion with native cleanup/no repair
B. one known destructive stale-source case that produces exact C1-R1 repair
C. one legitimate reaction interruption with native cleanup/no repair
D. one marked Staff RIGHT/OFF/RIGHT regression
E. one Dual source-specific case
F. one Fist/unarmed negative
G. one crossbow negative
H. clean shutdown
```

Exact raw filename for this baseline:

```text
research/raw/2026-08-30_post_enginebridge_unchanged_compact_collision_baseline.log
```

This is **not** a reopened R1 validation matrix. It is a compact structural sentinel proving the already-completed EngineBridge extraction before the frozen rewrite changes architecture/observation.

If a concrete runtime contradiction appears, STOP and diagnose it before rewrite implementation.

---

## After baseline PASS

Normal Chat records baseline meaning/evidence first.

Then the frozen rewrite in `docs/SECOND_PASS_REWRITE_CONTRACT.md` may be implemented as one bounded semantic-preserving transaction.

If Work/High is used:

```text
Normal Chat owns the architecture and frozen contract.
Work executes only that contract.
Work must not redesign marker/lifecycle/source semantics or expand features.
```

Required post-rewrite source/build gate:

```text
git diff --check
bounded contract audit
build Script_FrameCollisionTest
build Script_FrameCollisionBehaviorTest
verify behavior-only target excludes diagnostic sources/hooks
```

Then run compact diagnostic sufficiency regression. Only after that passes, run a small behavior-only smoke/equivalence test. Only after both pass may the separate C1-vs-marker simplification audit begin.

---

## Explicit rewrite non-goals

Do not combine the frozen rewrite with:

```text
C1-driven marker simplification
new attack-family marker support
new marker vocabulary
new Fist semantics / generalized Fist support
monster/body adapters
AttackContinuationProtection
Raise
speed
config redesign
New Balance / Jackydima compatibility fixes
production DLL migration
target acquisition
climbing
unrelated hook transport rewrites
```

---

## Forward order

```text
unchanged post-EngineBridge runtime baseline — NEXT
→ freeze/publish baseline evidence meaning
→ implement SECOND_PASS_REWRITE_CONTRACT
→ diagnostic + behavior-only build/source audit
→ compact diagnostic sufficiency regression
→ behavior-only smoke/equivalence
→ dedicated C1-vs-marker bookkeeping simplification audit
→ equipped-melee marker expansion one mechanism at a time
→ separate Fist source-adapter investigation
→ full marker + lifecycle regression
→ AttackContinuationProtection
→ guard + markers + continuation regression
→ mature research New Balance/Jackydima compatibility gate
→ retain mature modular foundation and migrate/redesign Raise + speed + config
→ later independent systems such as target acquisition/climbing
→ final diagnostics-free Script_G3AnimationBehaviors
→ final New Balance/Jackydima regression
→ retain separate diagnostic twin for future controlled reproduction
```

Architecture/rewrite authority: `SECOND_PASS_REWRITE_CONTRACT.md`.  
Release/build separation authority: `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`.  
Lifecycle authority: `COLLISION_LIFECYCLE_PLAN.md`.  
Diagnostic authority: `COLLISION_LOGGER_PLAN.md`.  
Validation authority: `COLLISION_TEST_PLAN.md`.  
Future held-Use2 prevention: `BAD_SKIP_FUTURE_INVESTIGATION.md`.

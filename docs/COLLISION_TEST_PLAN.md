# Collision Lifecycle Test Plan

**Status:** Current staged validation plan  
**Updated:** 2026-08-30

## Purpose

Validate one general execution-level collision-cleanup model with the smallest tests that can falsify it. Historical gate detail is preserved through `EVIDENCE_INDEX.md`, the canonical evidence ledgers and raw/archive artifacts; this file owns the **current and forward validation sequence**.

Current state: `SESSION_ENTRYPOINT.md`.  
Exact transient implementation contract: `BETWEEN_CHATS.md`.  
Lifecycle architecture: `COLLISION_LIFECYCLE_PLAN.md`.

---

## 1. Current Rules

- Compare one conceptual variable at a time where practical.
- Do not add family/action/input/state-name-specific ownership or repair branches.
- Do not treat `RunScriptFunction`, FullStop or AISetState as unconditional cleanup authority.
- Preserve native behavior for executions that already clean themselves.
- Successful offensive request creates an exact physical-source obligation; successful transition away from `Item_Attack` fulfills it.
- Repair may act only on an already-owned exact outstanding source after its legitimate cleanup opportunity has passed.
- Current equipped identity must establish source liveness before dereference/mutation.
- Preserve raw runtime logs exactly as produced.
- Follow `PROJECT_PIPELINE.md` for gate/artifact identity and `PROJECT_OPERATING_PROCEDURES.md` for build/deploy/test/log operations.

Authoritative research DLL remains:

```text
Script_FrameCollisionTest
```

---

## 2. Closed Gates — Retrieve, Do Not Rerun by Default

```text
B6 replacement/deferred ProcessScript candidate      EV-174–EV-181
B7/B7b termination / continuation loss               EV-182–EV-189
B8 cross-family abandonment generality               EV-190
B9 cleanup/finalization ordering                      EV-191
C1 shadow execution/source obligation core           EV-192–EV-193
C1 pre-Combat acquisition gap                        EV-194
C1-O1 outer ScriptFunction lifetime/correlation      EV-195–EV-196
hook/finalizer substrate stabilization               EV-199–EV-203
C1-O2-P1 lightweight dispatch bridge                 EV-204
C1-O2-P2 lazy pre-Combat acquisition/consumption     EV-205
```

C1-O2-P2 is closed for the tested outer-acquisition/binding model, including a dedicated clean shutdown closure for the same validated binary.

Accepted identity model:

```text
live ScriptFunction frame
= temporary correlator only where early acquisition needs it

C1 monotonic generation
= durable plugin execution identity

successful Item_Attack request
= exact source obligation

successful transition away from Item_Attack
= obligation fulfilled

destructive AISetState + obligation still outstanding
= terminal repair checkpoint
```

---

## 3. Current Gate — C1-R1 Controlled Native-Equivalent Physical Repair

C1-R1 asks:

> **Can the existing proven `WOULD_REPAIR` branch perform exactly the same narrow weapon-source reset Gothic 3 uses for legitimate cleanup — `Item_Attack(7) -> Item_Equipped(5)` on the exact live/equipped outstanding source — without changing any execution that already cleaned itself, never requested offense, is no longer safely live, or belongs to the other Dual source?**

### Source/API basis

Tested ordinary weapon cleanup across the established action matrix uses `7 -> 5` collision-group reset semantics. The tested legitimate reaction route also resets the exact weapon source away from `Item_Attack` to `Item_Equipped`.

Existing marker OFF/source-deactivation code already uses:

```text
SetCollisionGroup(Item_Equipped)
```

without `ClearTriggeredList()`.

Therefore C1-R1 must not add another cleanup action. Trigger-list clearing remains activation/rearm behavior.

### Exact positive predicate

```text
source obligation is outstanding
+ exact current equipped RIGHT/LEFT pointer establishes liveness
+ actual current source group == Item_Attack(7)
→ repair exactly that source to Item_Equipped(5)
```

Anything outside that predicate is no-op/diagnostic only.

### Required no-op branches

```text
NO_OP_NO_OUTSTANDING
UNRESOLVED_NOT_EQUIPPED
NO_OP_PHYSICALLY_CLEAN_RECONCILED
```

No unrelated group-7 adoption, no player-input classifier, no timeout, no polling and no broad scan.

### Diagnostic ordering

The repair setter intentionally passes through the existing SetCollisionGroup hook. Because that hook emits its own complete diagnostics, the finalizer must first classify/repair into fixed stack-local per-source results and only afterward emit the complete `C1 FINALIZATION` block.

Do not allow nested SetCollisionGroup diagnostics to splice into a half-written finalization block.

No heap allocation or new persistent/global state is required; the lifecycle already tracks at most two physical sources.

Recommended successful outcome:

```text
REPAIRED_TO_ITEM_EQUIPPED
```

Any resulting group other than exact `Item_Equipped(5)` is a gate failure/divergence. Do not retry or add fallback mutation.

---

## 4. C1-R1 Validation Sequence

### R1-A — independent source audit

Confirm before build:

1. existing AISetState capture/original/finalize ordering is unchanged;
2. existing ownership/acquisition/generation logic is unchanged;
3. only the former `WOULD_REPAIR` predicate may mutate;
4. exact equipped identity gates source dereference and mutation;
5. only the exact outstanding source is reset;
6. target is exactly `Item_Equipped(5)`;
7. `ClearTriggeredList()` is not called by repair;
8. no SetCollisionGroup-hook bypass/new hook/global repair machinery is added;
9. finalization diagnostics are emitted only after nested repair setter diagnostics complete;
10. record retirement remains once after finalization.

### R1-B — build / isolated load

```text
sync exact implementation
→ build Script_FrameCollisionTest
→ deploy one exact DLL
→ built/live SHA match
→ main-menu load/unload
→ exact C1-R1 startup identity
→ no combat
```

### R1-C — targeted positive repair

Reproduce one known armed destructive abandonment on a controlled player weapon source.

Expected:

```text
real offense obligation
→ no native cleanup
→ destructive AISetState
→ exact source still live/equipped and Item_Attack(7)
→ one repair SetCollisionGroup(Item_Equipped)
→ result exactly Item_Equipped(5)
→ REPAIRED_TO_ITEM_EQUIPPED
```

Then perform a later legitimate attack with the same source.

Expected consequence:

```text
new offense normally begins 5 -> 7
```

rather than inheriting the previous stale `7 -> 7`.

### R1-D — no-op controls

Verify **zero repair mutation** for:

```text
ordinary clean completion
legitimate reaction/knockdown cleanup
pre-activation interruption / no offense
clean GetUpAttack with P2 acquisition + native cleanup
GetUpParade / defensive no-offense case
```

Native cleanup must continue to win before finalization.

### R1-E — source-specific / marker / broader stability

Only after R1-C/R1-D meaning passes:

```text
Dual RIGHT/LEFT source-specific destructive repair
compact marked-source terminal-repair regression where relevant
broader mixed player/NPC/negative stability
```

The guard remains actor/source-general; do not add Hero-only production semantics merely to simplify the first test.

---

## 5. Acceptance / Failure Meaning

C1-R1 passes its controlled meaning gate only if:

```text
proven outstanding exact live/equipped source at group 7
→ one exact reset to group 5
→ physical stale collision removed
```

while all native-clean and no-obligation controls remain mutation-free.

A later attack beginning `5 -> 7` after a repaired stale case is strong consequence evidence that the previous stale offensive state was actually removed rather than merely reclassified.

C1-R1 fails at this boundary if safe repair requires:

```text
family/action/input/cause classification
null/liveness fallback
polling/timer/world scan
repair of unrelated equipped sources
SetCollisionGroup-hook bypass
ClearTriggeredList cleanup behavior
new terminal owner beyond the proven exact obligation/finalization model
```

Do not broaden the implementation in the same gate to hide such a result.

---

## 6. Explicit Regression Requirements

Protect throughout R1 and later integration:

- source-specific Dual RIGHT/LEFT behavior;
- inherited `7 -> 7` attribution for legitimate later requests;
- clean ordinary and reaction-side native cleanup precedence;
- pre-activation no-obligation behavior;
- P2 GetUp pre-Combat generation acquisition/bridge consumption;
- GetUpParade/defensive no-offense behavior;
- marker RIGHT/LEFT/BOTH/OFF semantics and marker bookkeeping retirement;
- Fist/body-source separation;
- bow, crossbow and magic negatives when broader regression is reached.

Do not reintroduce rejected C1-O2 dispatch machinery.

---

## 7. After C1-R1

Only after controlled physical repair passes should the project expand toward:

```text
broader physical-repair stability
→ marked/unmarked/player/NPC/negative regression
→ stable production integration
→ only later reconsider marker-bookkeeping simplification
```

Root-cause repair of the held-Use2 / Alternative-AI interruption remains unnecessary unless evidence proves the general collision guard cannot preserve collision integrity independently.

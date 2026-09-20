# Gothic 3 — Raw8 FIST Post-Attempt Latch Observation Probe

**Status:** ACTIVE — BOUNDED DIAGNOSTIC-ONLY IMPLEMENTATION TASK  
**Opened:** 2026-09-20  
**Owner after implementation:** Normal Chat runtime/evidence interpretation  
**Production behavior change:** PROHIBITED  
**Work build execution:** PROHIBITED

## Repository

`https://github.com/tcholti/Gothic3_Animation_Behaviors.git`

Branch:

`docs/collision-source-evidence`

## Read first

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. this document
4. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
5. `docs/FEATURE_DEVELOPMENT_METHOD.md`
6. `docs/work/active/COLLISION_RAW8_FIST_AUTHORING_SEMANTICS_REVIEW.md`
7. `docs/SOURCE_HOOK_GUIDE.md`

Then inspect only the exact source required by this frozen observation contract.

## Agreed design target — context only

The desired author-facing raw8 semantic is now frozen:

```text
FIST
-> body-contact damage opportunity becomes available from this authored point

unsuccessful native contact
-> opportunity should remain available

successful native contact
-> opportunity consumed

later FIST
-> opportunity rearmed

C1 / Hit termination
-> unused opportunity closed
```

There is no authored raw8 FIST_OFF in the chosen design absent future contradictory evidence.

This task does **not** implement that design.

## Evidence trigger

EV-346 Gargoyle factual `Action=2 / POWER`, RIGHT `Fist` / UseType8:

```text
native/no marker        7/7 damage
approx frame-3 FIST     5/10 damage
frame-1 FIST            0/4 damage
frame-6 FIST            8/8 damage
```

Every marked execution had correct ownership/marker/finalization behavior.

Current production behavior:
- marked C1 start closes `SPU+0x164 = 1`;
- accepted FIST writes `0`;
- when marker time is below the native ~60% motion threshold, one exact `Game+0x16E180` comparison receives synthetic threshold+epsilon;
- the synthetic permission is consumed once.

Historical EV-231 already proves that an explicit same-C1 write `SPU+0x164: 1 -> 0` can rearm the confirmed native raw8 damage path later in the move.

What remains unproven is the factual latch/result sequence after the **early synthetic native attempt itself**.

## Single causal question

> After an exact marked raw8 FIST consumes the current synthetic early timing permission, what is `SPU+0x164` after Gothic returns from that native CombatMove instruction, and how does that post-attempt state correlate with native raw8 damage occurring or not occurring?

The target distinction is:

```text
synthetic early opportunity
+ no native damage/contact result
-> post-attempt latch ?

synthetic early opportunity
+ native damage/contact result
-> post-attempt latch ?
```

This task is observation-only. Do not rearm, suppress, extend, preserve, or otherwise alter the native opportunity.

## Preferred existing observation boundary

Current `EngineBridge` already wraps `AICombatMoveInstr` at `Game +0x1696E0` and regains control immediately after the original instruction returns.

Source inspection should first determine whether this existing wrapper can faithfully provide the required post-native observation for the exact invocation in which `Raw8FistCollision::ApplyTimingPermission()` consumed a synthetic permission.

Preferred shape if source facts support it:

```text
before original AICombatMoveInstr
-> establish exact invocation correlation only

inside existing Game+0x16E180 timing transport
-> existing synthetic permission consumption occurs unchanged
-> observation state notes that this exact invocation consumed synthetic raw8 permission

original AICombatMoveInstr returns
-> read same exact actor/SPU/C1 raw8 latch
-> emit one compact diagnostic observation

existing EntityOnDamage diagnostic
-> remains observation only
-> runtime correlation determines whether damage occurred
```

Do not add a new engine hook if the existing wrapper can answer the question faithfully.

## Allowed implementation responsibility

Implement only the minimum diagnostics needed to correlate:

- exact actor identity;
- exact SPU identity;
- exact C1 generation;
- exact factual raw8 Fist source identity / UseType8;
- factual action/family/current animation identity as already available;
- whether the current AICombatMoveInstr invocation consumed a raw8 timing permission;
- whether that consumption used `SyntheticApplied=1` or native timing;
- latch value immediately before returning from the bridge's post-original observation point;
- enough exact identity to correlate the existing native `gCEntity::OnDamage` diagnostic entry with the same C1.

A compact line such as a dedicated `CORE RAW8_FIST_POST_ATTEMPT` record is appropriate if it preserves the project's CORE diagnostic conventions.

Diagnostic state must be exact-invocation/C1 scoped and mechanically absent from the behavior-only product.

## Allowed files / modules

Prefer the smallest set among:

- `prototypes/Script_FrameCollisionTest/Raw8FistCollision.cpp/.h`
- `prototypes/Script_FrameCollisionTest/EngineBridge.cpp`
- `prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp/.h`

CMake changes are not expected because this is observation-only inside existing diagnostic infrastructure.

Do not edit production integration under `src/Script_G3AnimationBehaviors`.

Do not change `PhysicalFistCollision`, `EquippedSprintCollision`, generic equipped marker semantics, collision lifecycle repair policy, or raw55 behavior.

## Protected behavior

Must remain byte-semantically equivalent in behavior:

```text
current raw8 latch writes
current raw8 synthetic timing decision
current one-shot timing-permission consumption
unmarked raw8 native fallback
raw55 behavior
equipped weapon behavior
equipped Sprint behavior
target/contact/damage dispatch
C1 lifecycle/finalization
```

The probe must not:
- write `SPU+0x164` at any new point;
- alter returned play time beyond the already-existing production behavior;
- suppress any callback/hook/native call;
- call damage directly;
- clear triggered lists;
- mutate collision groups;
- add polling;
- add a timer;
- add species/animation-name policy.

## Stop condition

If the existing `AICombatMoveInstr` wrapper cannot faithfully identify the exact post-attempt state, do **not** invent a new hook or choose a new native boundary inside this task.

Instead report:

```text
expected observation
vs.
why existing transport is insufficient
vs.
the narrow native boundary/hook question Normal Chat must decide next
```

and STOP.

Likewise, if source inspection contradicts the assumption that a synthetic timing consumption can be correlated to one exact current `AICombatMoveInstr` invocation without behavior change, stop and report the contradiction.

## Build / publication

Work build execution is **PROHIBITED**.

The User explicitly authorizes publication of this bounded diagnostics-only implementation to:

- repository: `tcholti/Gothic3_Animation_Behaviors`
- branch: `docs/collision-source-evidence`

Perform source/static review only, including exact diff/scope inspection and `git diff --check` or equivalent if available without build execution.

## Required report

Report:
- final remote commit SHA;
- changed files;
- concise description of the observation added;
- protected behavior confirmation;
- source/static checks;
- `Build: NOT ATTEMPTED — Work build execution was not authorized for this task.`;
- any material contradiction.

Then STOP.
# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-05

## Current bridge — N2C identified direct combat-loop Fist damage dispatch; N2D latch intervention next

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat / Work must read `docs/SESSION_ENTRYPOINT.md` first, then this file for the exact current continuation.

---

## Closed / protected boundary

```text
collision architecture verification             COMPLETE — EV-206–EV-215
Power marker adapter validation                 CLOSED/PASS
Pierce marker adapter validation                CLOSED/PASS
SimpleWhirl current marker/semantic stage       CLOSED/PASS
Hack isolated routing/source/marker validation  PASS
Fist Stage A dedicated baseline                 CLOSED/PASS — EV-221
Fist Stage B marker-time DamageDisabled probe   CLOSED/FAIL AS CURRENT OFF INTERVENTION
Fist Stage A restoration after Stage B          CLOSED/PASS
Fist N1 native trigger-state observation        CLOSED/PASS AS OBSERVATION — EV-222–EV-223
Fist N2A gate/TriggerTarget timing               CLOSED/INCONCLUSIVE
Fist N2B hook observability discrimination      CLOSED/CASE A FOR BOTH HOOKS
Fist N2C gCEntity::OnDamage caller trace         CLOSED/PASS AS PATH IDENTIFICATION
```

Do not reopen those areas without concrete contradictory evidence.

Fist remains a logical human body-contact source adapter inside the closed collision architecture. It is not another RIGHT/LEFT weapon source bit.

---

## N2C implementation / runtime evidence

N2C implementation:

```text
3679d0dba0a049ad0a28bbe3755d09a500fbcd92
Add N2C Fist OnDamage caller trace
```

Diagnostic-only hook:

```text
Game + 0x668D0  gCEntity::OnDamage
```

Transport:

```text
explicit gCEntity *this
.ThisCall()
_ReturnAddress() captured at entry
native original exactly once, unchanged arguments/order
64-entry diagnostic cap
no behavior-only hook
```

Local diagnostic build: PASS.

Validated deployed diagnostic:

```text
Script_FrameCollisionTest.dll
SHA256 62C90DBD08763866FA6057431C2C7488ED41ABD2849068219E36C127374D94D9
length 438272
```

Built/live SHA256 matched exactly. CORE startup PASS.

Canonical N2C raw:

```text
research/raw/2026-09-05_fist_n2c_ondamage_caller_trace.log
raw evidence commit 30cb0aaba8b121d05ad7f2793cf27acea1e18bba
length 9507
```

Controlled case:

```text
player PC_Hero
known marked human Fist P0 Normal attack
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
G3AB_COL_FIST at authored frame 3
valid target Golem
User visual damage observation: YES
```

The intended marker executed:

```text
FIST RECEIVED
ElapsedMs: 39352.632
Action: 1
AniPhase: 1
StateTime: 0.123945
MarkerAction: ACCEPTED
FistSourceAddress: E6AA5E10
FistUseType: 8
FistGroupBefore: 0
FistGroupAfter: 0
FistTriggeredListCleared: 1
```

The complete raw contains exactly one `ENTITY_ON_DAMAGE_ENTRY`, during the same attack:

```text
ElapsedMs: 39439.144
HookEntryOrdinal: 1
CallerModule: Game.dll
CallerRVA: 0x0016E348
ThisEntityName: Golem
EntityArg1Name: Fist
EntityArg1Address: E6AA5E10
EntityArg2Name: PC_Hero
EntityArg2IsPlayer: 1
EntityArg1IsResolvedFistSource: 1
IntArg1: 21
IntArg2: 2
PlayerAction: 1
PlayerAniPhase: 1
PlayerStateTime: 0.198956
```

Marker-to-OnDamage delta in this run:

```text
39439.144 - 39352.632 = 86.512 ms
```

Use neutral argument semantics. N2C proves factual identity/correlation, not semantic names for IntArg1/IntArg2.

---

## Tested-binary path identification after N2C

Authoritative binary reference:

```text
https://github.com/tcholti/Gothic3_Binary_Reference.git
builds/current_tested
```

Exact tested export:

```text
Game + 0x16DD00  gCScriptProcessingUnit::sAICombatMoveItlLoop
```

N2C's caller return address:

```text
Game + 0x16E348
```

lands immediately after the indirect call at:

```text
Game + 0x16E346
```

inside `sAICombatMoveItlLoop`.

The surrounding tested instructions construct the five-argument `gCEntity::OnDamage` call and invoke it on the receiving game entity. Therefore the damaging N2C Fist event was dispatched directly by the native combat-move loop.

This resolves the N2A/N2B silence:

```text
confirmed damaging human-Fist path
-> gCScriptProcessingUnit::sAICombatMoveItlLoop
-> gCEntity::OnDamage
```

The tested path did not need to enter the two hooked `gCTouchDamage_PS` methods:

```text
CanBeActivatedNow
TriggerTarget
```

Do not infer that those methods are globally unused. The conclusion is specific to the confirmed N2C damaging run/path.

---

## Native combat-move latch candidate

Within the normal combat-move loop branch that leads to the observed damage dispatch, tested disassembly shows an internal byte at:

```text
gCScriptProcessingUnit + 0x164
```

At the top of the relevant normal branch:

```text
Game + 0x16DFB9  cmp byte ptr [SPU+0x164], 0
Game + 0x16DFC0  jne Game+0x16E352
```

A nonzero value therefore exits the loop branch before the later hit-time threshold, DamageReceiver resolution and `gCEntity::OnDamage` dispatch.

After the hit-time threshold is satisfied, but before the damage path is constructed, the same loop commits:

```text
Game + 0x16E1A3  mov byte ptr [SPU+0x164], 1
```

Only afterward does it continue through actor-side NPC / Inventory lookup and eventually call `gCEntity::OnDamage` at `Game + 0x16E346`.

Tested property-set IDs encountered after the latch write include:

```text
0x1E = NPC
0x1F = Inventory
```

The current SDK does not expose a named public member/accessor for `SPU+0x164`; the tail of `gCScriptProcessingUnit` remains partially unimplemented in the SDK. Treat this as an internal native combat-move latch candidate, not a named SDK property.

Important qualification:

- do not call it a proven production `FIST_OFF` mechanism yet;
- do not assume its full meaning outside the tested combat path;
- do not create persistent marker-owned state around it yet;
- do not modify the production behavior-only product yet.

The static ordering is sufficient to justify exactly one causal marker-time intervention test.

---

## Exact next responsibility — N2D TEMPORARY MARKER-TIME COMBAT-LATCH INTERVENTION

N2D asks only:

> On the same known marked human-Fist P0 Normal attack, if the accepted existing `G3AB_COL_FIST` marker temporarily writes the current player's exact combat SPU byte at `+0x164` to `1` after preserving the existing Stage-A FIST operation, does the later native `sAICombatMoveItlLoop -> gCEntity::OnDamage` Fist damage dispatch disappear?

This is a one-variable causal probe of the newly identified native latch candidate.

It is **not** production `FIST_OFF` implementation.

### Preserve Stage A, add exactly one temporary intervention

The accepted existing FIST marker must continue to do its current Stage-A operation unchanged:

```text
resolve/validate exact human gEUseType_Fist raw 8
-> TouchDamage.ClearTriggeredList()
-> group remains 0
-> no DamageDisabled mutation
-> no weapon source-mask semantics
```

Then, for this N2D diagnostic experiment only, additionally:

```text
resolve the current player's gCScriptProcessingUnit from the player's gCScriptRoutine_PS
read byte at SPU + 0x164
write that exact byte to 1
read it back
```

Do not write any other SPU field.

Do not add a `G3AB_COL_FIST_OFF` opcode yet.

Do not move the intervention to another marker or another timing boundary.

### Scope the temporary mutation tightly

The temporary write must be restricted to the diagnostic test path:

```text
FRAME_COLLISION_DIAGNOSTICS build only
accepted existing G3AB_COL_FIST marker only
actor is the current player
existing exact human Fist source validation succeeds
```

The behavior-only product must remain exact Stage A and must not contain an active N2D latch mutation.

Do not create persistent diagnostic/gameplay bookkeeping to remember the write.

Do not add restore/terminal/interruption logic in N2D.

### Required N2D logging

At the accepted FIST marker, record enough factual data to prove the exact intervention:

```text
Boundary: FIST_COMBAT_LATCH_INTERVENTION
ElapsedMs
Actor / ActorAddress
Action
AniPhase
StateTime
CurrentMovementAni
C1Generation if already available
SPUAddress
LatchOffset: 0x164
LatchBefore
LatchAfter
WriteAttempted: 0/1
WriteConfirmed: 0/1
FistSourceAddress
FistUseType
FistCollisionGroup
```

The existing N2C `gCEntity::OnDamage` hook must remain installed and unchanged so the same run independently reports whether a Fist-correlated damage dispatch still occurs.

Keep the older N2A/N2B diagnostic hooks unchanged unless a compile-only adjustment is unavoidable.

### Transport / implementation cautions

Use the established factual route to the player's routine/SPU; do not invent a second player or Fist classifier.

Use byte-wise access only for the exact tested offset:

```text
reinterpret_cast<GEU8 *>(spu) + 0x164
```

or an equivalent minimal helper.

Do not reinterpret the byte as a named SDK field in code/comments/docs.

Do not hook or patch `sAICombatMoveItlLoop` itself in N2D.

Do not skip/replace `gCEntity::OnDamage` in the hook.

### N2D controlled runtime case

Use exactly the same fixture and target class as N2C if practical:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
G3AB_COL_FIST at frame 3
one complete P0 Normal/Fist attack
valid target
no additional attack afterward
User records visual damage YES/NO
```

Freeze the raw log after the single run.

### N2D interpretation

```text
A. LatchBefore = 0, LatchAfter = 1, visual damage NO,
   and no Fist-correlated ENTITY_ON_DAMAGE_ENTRY
   -> PASS as causal suppression evidence for this tested path.
      The native combat latch is a viable production FIST_OFF candidate.
      Restore the temporary N2D setter to Stage A before production design.

B. LatchBefore = 0, LatchAfter = 1, but visual damage YES and/or
   Fist-correlated ENTITY_ON_DAMAGE_ENTRY still occurs
   -> FAIL as marker-time suppression mechanism in this form.
      Investigate whether native code resets the latch after the marker or
      another damage path exists. Do not add production FIST_OFF.

C. LatchBefore is already nonzero at the accepted marker
   -> material contradiction with the assumed timing state for this run.
      Do not interpret suppression; inspect lifecycle/timing before another mutation.

D. write cannot be confirmed or exact SPU cannot be resolved
   -> implementation/observability failure only.
      Fix that bounded defect before causal interpretation.
```

Do not infer full lifecycle/reset behavior from N2D even if suppression passes. Natural reset across a later combat move is a separate question to prove before production implementation.

---

## N2D explicit non-goals

Do not implement or design:

```text
G3AB_COL_FIST_OFF
production FIST/FIST_OFF lifecycle
production raw SPU mutation
persistent Fist marker-owned latch state
manual latch restoration
terminal/interruption restoration
DamageDisabled setter experiment
SetIsEnabled / SetReactToTouch
SetCollisionGroup changes
extra ClearTriggeredList behavior beyond existing Stage A
hook/patch sAICombatMoveItlLoop
skip/replace gCEntity::OnDamage
PhysicalFist / monsters / generalized body collision
per-limb Fist markers
weapon source-mask changes
attack-family or StatePosition redesign
C1 or weapon-lifecycle redesign
RIGHT/LEFT/BOTH/OFF redesign
final mixed regressions
Raise / playback-speed work
```

---

## Frozen continuation

```text
A    — dedicated FIST baseline                    CLOSED/PASS
B    — marker-time DamageDisabled intervention    CLOSED/FAIL AS CURRENT OFF INTERVENTION
R    — exact restoration to Stage A behavior      CLOSED/PASS
N1   — native trigger-state observation           CLOSED/PASS AS OBSERVATION
N2A  — gate/TriggerTarget timing                  CLOSED/INCONCLUSIVE
N2B  — hook observability discrimination          CLOSED/CASE A FOR BOTH HOOKS
N2C  — gCEntity::OnDamage caller trace            CLOSED/PASS AS PATH IDENTIFICATION
S3   — combat-loop static reconstruction          CLOSED FOR N2D SELECTION
N2D  — temporary SPU+0x164 marker-time probe      CURRENT/NEXT
C    — production FIST/FIST_OFF lifecycle         BLOCKED until suppression + reset are proven
```

---

## Local-state caution carried forward

Earlier local status showed this unrelated untracked file:

```text
research/raw/2026-09-04_hack_2h_dedicated_p0_override_validation.log
```

Do not delete, rename, stage, overwrite, or clean it merely to obtain a clean working tree.

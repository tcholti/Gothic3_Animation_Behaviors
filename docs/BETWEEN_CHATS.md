# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-06

## Current bridge — N2D causal suppression PASS; N2E same-process native reset proof next

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
Fist N2D SPU+0x164 causal suppression probe      CLOSED/PASS — CASE A
```

Do not reopen those areas without concrete contradictory evidence.

Fist remains a logical human body-contact source adapter inside the closed collision architecture. It is not another RIGHT/LEFT weapon source bit.

---

## N2C path fact carried forward

Authoritative tested binary reference:

```text
https://github.com/tcholti/Gothic3_Binary_Reference.git
builds/current_tested
```

N2C proved the damaging marked human-Fist path:

```text
gCScriptProcessingUnit::sAICombatMoveItlLoop
Game + 0x16DD00
    -> indirect gCEntity::OnDamage call at Game + 0x16E346
    -> return address observed as Game + 0x16E348
```

Canonical N2C raw:

```text
research/raw/2026-09-05_fist_n2c_ondamage_caller_trace.log
raw evidence commit 30cb0aaba8b121d05ad7f2793cf27acea1e18bba
```

The correlated event was:

```text
ThisEntityName: Golem
EntityArg1Name: Fist
EntityArg1IsResolvedFistSource: 1
EntityArg2Name: PC_Hero
EntityArg2IsPlayer: 1
CallerModule: Game.dll
CallerRVA: 0x0016E348
```

This explains the earlier N2A/N2B silence for the tested run: that confirmed damaging path did not need to enter the hooked `gCTouchDamage_PS::CanBeActivatedNow` / `TriggerTarget` entries.

---

## Native combat latch fact

Within the tested normal combat-loop branch:

```text
Game + 0x16DFB9  cmp byte ptr [SPU+0x164], 0
Game + 0x16DFC0  jne Game+0x16E352
```

A nonzero latch exits before the later Fist damage dispatch.

Once native hit timing is reached, the same loop commits:

```text
Game + 0x16E1A3  mov byte ptr [SPU+0x164], 1
```

before continuing to the eventual `gCEntity::OnDamage` call.

The SDK does not expose a named public member/accessor for this byte. Continue to call it only the factual/internal `SPU+0x164` combat latch.

Tested binary also contains native writes of `0` to this same byte elsewhere in the combat/instruction machinery. Those static writes justify a reset test but do not by themselves prove the exact fresh-combat-move reset lifecycle.

---

## N2D implementation / runtime closure

N2D implementation:

```text
33a55615315d7c90fd507cac86ff1205029785d0
Add N2D Fist combat latch intervention
```

Validated diagnostic DLL:

```text
SHA256 3EE9B27C5BEB72643436D6289632E38A71B562106FDA0B2E974ECF9E5488BF39
length 439296
```

Built/live SHA256 matched exactly. CORE startup PASS.

Canonical N2D raw:

```text
research/raw/2026-09-06_fist_n2d_combat_latch_intervention.log
raw evidence commit c0ac9429674a590705aa660a8a20c446afe63e8a
length 6890
SHA256 C153D05D4B6218C3E6972C7062EA20353BD41AFC42F265A6AB774C05994790E3
```

Controlled case:

```text
player PC_Hero
known marked human Fist P0 Normal attack
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
G3AB_COL_FIST at authored frame 3
valid target
User visual damage observation: NO
```

The accepted marker retained exact Stage-A behavior:

```text
MarkerAction: ACCEPTED
FistUseType: 8
FistGroupBefore: 0
FistGroupAfter: 0
FistTriggeredListCleared: 1
```

The diagnostic intervention immediately after marker processing reported:

```text
Boundary: FIST_COMBAT_LATCH_INTERVENTION
Action: 1
AniPhase: 1
StateTime: 0.124997
LatchOffset: 0x164
LatchBefore: 0
LatchAfter: 1
WriteAttempted: 1
WriteConfirmed: 1
FistUseType: 8
FistCollisionGroup: 0
```

The complete N2D raw contains **zero** `ENTITY_ON_DAMAGE_ENTRY` records.

### N2D conclusion — CASE A / CAUSAL SUPPRESSION PASS

For this tested marked human-Fist P0 Normal attack:

```text
accepted FIST marker
-> exact current-player SPU+0x164 observed 0
-> diagnostic write 1 confirmed
-> later sAICombatMoveItlLoop -> gCEntity::OnDamage Fist dispatch absent
-> User observed visual damage NO
```

Therefore setting the native combat latch to `1` at the authored marker causally suppresses the confirmed native Fist damage path in this tested execution.

This makes `SPU+0x164 = 1` a viable production `FIST_OFF` candidate, but production is still blocked until native rearming/reset across a later combat move is proven.

Do not infer from N2D alone:

- the complete semantic meaning of `SPU+0x164` outside this path;
- interruption/terminal reset behavior;
- that manual restoration is required;
- that production `G3AB_COL_FIST_OFF` can be implemented yet;
- how repeated ON/OFF windows inside one combat move should behave.

---

## Exact next responsibility — N2E SAME-PROCESS NATIVE LATCH RESET PROOF

N2E asks only:

> After one marked human-Fist attack is suppressed by the proven `SPU+0x164 = 1` intervention, does Gothic 3 naturally return that same current-player latch to `0` for the next fresh marked human-Fist combat move in the same game process, such that the second attack can damage normally without any manual latch restoration?

This is a diagnostic lifecycle proof only. It is **not** production `FIST_OFF` implementation.

### Required diagnostic sequence

Preserve exact Stage-A FIST marker behavior for every accepted marker:

```text
resolve/validate exact human gEUseType_Fist raw 8
-> TouchDamage.ClearTriggeredList()
-> no collision-group mutation
-> no DamageDisabled mutation
-> no weapon source-mask semantics
```

Replace the current N2D every-FIST diagnostic setter with one bounded process-local diagnostic sequence for accepted current-player exact-human-Fist markers:

```text
AcceptedFistSequenceOrdinal = 1
    read current SPU+0x164
    write exactly 1
    volatile readback
    no manual restore later

AcceptedFistSequenceOrdinal = 2
    read current SPU+0x164 only
    DO NOT write the latch

AcceptedFistSequenceOrdinal > 2
    no latch mutation
    bounded diagnostic indication only if needed
```

The process-local ordinal exists only to distinguish the two controlled N2E test attacks. It must not become gameplay/marker lifecycle state.

Do not reset the ordinal from animation/action/phase/state-time guesses.

### Required logging

For both accepted sequence entries report at minimum:

```text
Boundary: FIST_COMBAT_LATCH_RESET_PROBE
AcceptedFistSequenceOrdinal
ProbeMode: SUPPRESS_FIRST or OBSERVE_SECOND
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

For ordinal 2:

```text
WriteAttempted: 0
LatchAfter = same read-only observed value as LatchBefore, or otherwise clearly indicate no write
```

Do not add a manual clear to `0` anywhere in N2E.

Keep the existing N2C `gCEntity::OnDamage` caller hook unchanged so the same run independently reports whether damage dispatch resumes on attack 2.

### Scope

Diagnostic-only:

```text
FRAME_COLLISION_DIAGNOSTICS
current player only
accepted existing G3AB_COL_FIST marker only
existing exact human Fist validation succeeds
```

Behavior-only product must remain exact Stage A.

Do not add `G3AB_COL_FIST_OFF` yet.

### Controlled runtime case

Run **two and only two** complete marked P0 Normal/Fist attacks in the same game process, preferably against the same valid target class:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
G3AB_COL_FIST at frame 3
```

Attack 1:

```text
expected diagnostic suppression
User records visual damage YES/NO
```

Allow the first attack to finish naturally and return to a state from which a fresh attack can be started. Do not reload the game, change DLL, manually restore the latch, or perform another intervening attack.

Attack 2:

```text
read-only latch observation
User records visual damage YES/NO
```

Exit normally after attack 2 and freeze the single full raw log.

### N2E interpretation

```text
A. Attack 1: ordinal1 latch 0 -> 1, write confirmed, damage NO,
   no Fist-correlated OnDamage;
   Attack 2: ordinal2 LatchBefore = 0 with no write, damage YES,
   Fist-correlated OnDamage resumes from Game.dll + 0x16E348
   -> PASS: native combat lifecycle naturally rearms the latch for a fresh move
      after the authored suppression. Production FIST_OFF design may proceed.

B. Attack 2 marker occurs but LatchBefore remains 1
   -> native reset not established before the second authored marker.
      Do not implement production FIST_OFF; map reset timing/lifecycle.

C. Attack 2 LatchBefore = 0 but normal Fist damage/OnDamage does not resume
   -> latch reset alone is insufficient to explain rearming; investigate before production.

D. Attack 1 no longer reproduces N2D suppression
   -> contradiction/regression; stop and inspect before interpreting reset.

E. second accepted FIST marker cannot be reached in the same process after the first suppression
   -> lifecycle contradiction; do not add manual restore as a shortcut.
```

### Explicit non-goals

Do not implement or design:

```text
G3AB_COL_FIST_OFF
production FIST/FIST_OFF lifecycle
behavior-only SPU mutation
manual SPU+0x164 restoration
terminal/interruption restoration
persistent marker-owned latch state
DamageDisabled / IsEnabled / ReactToTouch / collision-group experiments
extra ClearTriggeredList beyond existing Stage A
hook/patch sAICombatMoveItlLoop
skip/replace gCEntity::OnDamage
PhysicalFist / monsters / generalized body collision
per-limb Fist markers
weapon source-mask changes
family / StatePosition / C1 redesign
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
N2D  — SPU+0x164 marker-time intervention         CLOSED/PASS — CASE A
N2E  — same-process native latch reset proof      CURRENT/NEXT
C    — production FIST/FIST_OFF lifecycle         BLOCKED until N2E passes
```

---

## Local-state caution carried forward

Earlier local status showed this unrelated untracked file:

```text
research/raw/2026-09-04_hack_2h_dedicated_p0_override_validation.log
```

Do not delete, rename, stage, overwrite, or clean it merely to obtain a clean working tree.

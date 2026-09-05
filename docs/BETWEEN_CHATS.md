# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-06

## Current bridge — N2E implemented, audited, and built; runtime reset proof next

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

Fist remains a logical human body-contact source adapter. It is not a RIGHT/LEFT weapon source bit.

---

## Proven Fist damage path carried forward

N2C proved the damaging marked human-Fist path:

```text
gCScriptProcessingUnit::sAICombatMoveItlLoop
Game + 0x16DD00
    -> indirect gCEntity::OnDamage call at Game + 0x16E346
    -> observed return address Game + 0x16E348
```

Canonical N2C raw:

```text
research/raw/2026-09-05_fist_n2c_ondamage_caller_trace.log
raw evidence commit 30cb0aaba8b121d05ad7f2793cf27acea1e18bba
```

Correlated runtime event:

```text
ThisEntityName: Golem
EntityArg1Name: Fist
EntityArg1IsResolvedFistSource: 1
EntityArg2Name: PC_Hero
EntityArg2IsPlayer: 1
CallerModule: Game.dll
CallerRVA: 0x0016E348
```

This explains N2A/N2B silence for the tested run: the confirmed damage path did not need the hooked `gCTouchDamage_PS::CanBeActivatedNow` / `TriggerTarget` entries.

---

## Native combat latch fact

Within the tested normal combat-loop branch:

```text
Game + 0x16DFB9  cmp byte ptr [SPU+0x164], 0
Game + 0x16DFC0  jne Game+0x16E352
```

A nonzero byte exits before later Fist damage dispatch.

Once native hit timing is reached, the same loop commits:

```text
Game + 0x16E1A3  mov byte ptr [SPU+0x164], 1
```

before continuing toward `gCEntity::OnDamage`.

The SDK does not expose a named public member/accessor for this byte. Continue to call it only the factual/internal `SPU+0x164` combat latch.

Tested binary also contains native writes of `0` to this same byte elsewhere in combat/instruction machinery. Those writes justify N2E but do not by themselves prove the exact fresh-move reset lifecycle.

---

## N2D closure — causal suppression PASS

N2D implementation:

```text
33a55615315d7c90fd507cac86ff1205029785d0
Add N2D Fist combat latch intervention
```

Validated N2D DLL:

```text
SHA256 3EE9B27C5BEB72643436D6289632E38A71B562106FDA0B2E974ECF9E5488BF39
length 439296
```

Canonical N2D raw:

```text
research/raw/2026-09-06_fist_n2d_combat_latch_intervention.log
raw evidence commit c0ac9429674a590705aa660a8a20c446afe63e8a
length 6890
SHA256 C153D05D4B6218C3E6972C7062EA20353BD41AFC42F265A6AB774C05994790E3
```

Controlled result:

```text
accepted G3AB_COL_FIST
LatchBefore: 0
LatchAfter: 1
WriteAttempted: 1
WriteConfirmed: 1
complete raw: zero ENTITY_ON_DAMAGE_ENTRY records
User visual damage observation: NO
```

Conclusion:

```text
SPU+0x164 = 1 at the authored FIST marker
-> suppresses the confirmed sAICombatMoveItlLoop -> gCEntity::OnDamage path
-> no observed target damage
```

This is causal suppression evidence for the tested human-Fist P0 Normal execution. Production `FIST_OFF` remains blocked until native rearming/reset is proven.

---

## N2E implementation status

Frozen N2E handoff commit:

```text
6f61fd596cd7e4fbef62cdc4422ca81391e634e6
```

N2E implementation:

```text
0034e4eeaf807904ab0ad3e96e64049197981f7c
Add N2E Fist latch reset probe
```

Source audit: PASS.

Changed files:

```text
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.cpp
prototypes/Script_FrameCollisionTest/CollisionDiagnostics.h
prototypes/Script_FrameCollisionTest/EngineBridge.cpp
```

Implemented diagnostic sequence:

```text
AcceptedFistSequenceOrdinal = 1
    ProbeMode: SUPPRESS_FIRST
    read SPU+0x164
    write exactly 1
    volatile readback

AcceptedFistSequenceOrdinal = 2
    ProbeMode: OBSERVE_SECOND
    read SPU+0x164 only
    no write
    LatchAfter mirrors observed LatchBefore

AcceptedFistSequenceOrdinal > 2
    no latch mutation
```

Preserved:

```text
Stage-A FIST behavior unchanged
existing N2C gCEntity::OnDamage hook unchanged
no manual latch reset
no production FIST_OFF
no gameplay lifecycle state
no action/phase/state-time ordinal reset guesses
behavior-only product unchanged
```

Local build on 2026-09-06: PASS.

```text
Script_FrameCollisionTest.dll
SHA256 2382A50D0265BCF8743E9B7E40E32398341CCE23088CEA9F33790469FD881F96
length 439808
```

The DLL has been built but N2E deployment/startup/runtime validation has **not** yet been performed.

---

## Exact next action — resume here

Do **not** rebuild or redesign first unless the local built DLL is missing or differs from the recorded hash.

Next sequence:

```text
1. Deploy exact N2E diagnostic DLL.
2. Verify built/live SHA256 match:
   2382A50D0265BCF8743E9B7E40E32398341CCE23088CEA9F33790469FD881F96
3. Launch only far enough to verify CORE startup, then exit.
4. If startup passes, run the controlled N2E two-attack test in ONE game process.
```

Controlled fixture:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
G3AB_COL_FIST at frame 3
prefer same valid target class as N2C/N2D (Golem) if practical
```

Attack 1:

```text
expected AcceptedFistSequenceOrdinal: 1
expected ProbeMode: SUPPRESS_FIRST
expected LatchBefore: 0
expected LatchAfter: 1
expected WriteConfirmed: 1
User records visual damage YES/NO
```

Allow attack 1 to finish naturally. Do not reload, change DLL, manually restore the latch, or perform an intervening attack.

Attack 2 in the same process:

```text
expected AcceptedFistSequenceOrdinal: 2
expected ProbeMode: OBSERVE_SECOND
must have WriteAttempted: 0
observe LatchBefore read-only
User records visual damage YES/NO
```

Exit normally immediately after attack 2 and freeze one full raw log.

### N2E interpretation

```text
A. attack1: 0 -> 1, write confirmed, damage NO, no Fist OnDamage
   attack2: LatchBefore = 0, no write, damage YES,
            Fist OnDamage resumes from Game.dll + 0x16E348
   -> PASS: native combat lifecycle naturally rearms for fresh move.
      Production FIST_OFF design may proceed.

B. attack2 marker occurs but LatchBefore remains 1
   -> native reset not established before second marker.
      Do not implement production FIST_OFF; map reset timing/lifecycle.

C. attack2 LatchBefore = 0 but damage / Fist OnDamage does not resume
   -> latch reset alone is insufficient; investigate before production.

D. attack1 no longer reproduces N2D suppression
   -> contradiction/regression; stop before interpreting reset.

E. second accepted FIST marker cannot be reached in same process
   -> lifecycle contradiction; do not add manual restore as shortcut.
```

---

## Current frozen continuation

```text
A    — dedicated FIST baseline                    CLOSED/PASS
B    — marker-time DamageDisabled intervention    CLOSED/FAIL AS CURRENT OFF INTERVENTION
R    — exact restoration to Stage A behavior      CLOSED/PASS
N1   — native trigger-state observation           CLOSED/PASS AS OBSERVATION
N2A  — gate/TriggerTarget timing                  CLOSED/INCONCLUSIVE
N2B  — hook observability discrimination          CLOSED/CASE A FOR BOTH HOOKS
N2C  — gCEntity::OnDamage caller trace            CLOSED/PASS AS PATH IDENTIFICATION
N2D  — SPU+0x164 marker-time intervention         CLOSED/PASS — CASE A
N2E  — same-process native latch reset proof      IMPLEMENTED + BUILT; RUNTIME NEXT
C    — production FIST/FIST_OFF lifecycle         BLOCKED until N2E passes
```

---

## Explicit N2E non-goals still in force

Do not implement or design before N2E runtime closure:

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

## Local-state caution carried forward

Earlier local status showed this unrelated untracked file:

```text
research/raw/2026-09-04_hack_2h_dedicated_p0_override_validation.log
```

Do not delete, rename, stage, overwrite, or clean it merely to obtain a clean working tree.

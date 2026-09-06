# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-06

## Current bridge — N2E native rearm PASS; production FIST_OFF minimal integration next

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
Fist N2E same-process native latch reset proof   CLOSED/PASS — CASE A
```

Do not reopen those areas without concrete contradictory evidence.

Fist remains a logical human body-contact source adapter. It is not a RIGHT/LEFT weapon source bit.

---

## Proven native Fist path and latch

N2C proved the damaging marked human-Fist path:

```text
gCScriptProcessingUnit::sAICombatMoveItlLoop
Game + 0x16DD00
    -> indirect gCEntity::OnDamage call at Game + 0x16E346
    -> observed return address Game + 0x16E348
```

Within the tested normal combat-loop branch:

```text
Game + 0x16DFB9  cmp byte ptr [SPU+0x164], 0
Game + 0x16DFC0  jne Game+0x16E352
```

A nonzero byte exits before later Fist damage dispatch.

Once native hit timing is reached, the loop itself commits:

```text
Game + 0x16E1A3  mov byte ptr [SPU+0x164], 1
```

before continuing toward `gCEntity::OnDamage`.

The SDK does not expose a named public member/accessor for this byte. Continue to call it only the factual/internal `SPU+0x164` combat latch.

---

## N2D closure — causal suppression PASS

N2D implementation:

```text
33a55615315d7c90fd507cac86ff1205029785d0
Add N2D Fist combat latch intervention
```

Canonical N2D raw:

```text
research/raw/2026-09-06_fist_n2d_combat_latch_intervention.log
raw evidence commit c0ac9429674a590705aa660a8a20c446afe63e8a
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
SPU+0x164 = 1 before native hit dispatch
-> suppresses the confirmed sAICombatMoveItlLoop -> gCEntity::OnDamage Fist path
-> no observed target damage
```

---

## N2E closure — native fresh-move rearm PASS

N2E implementation:

```text
0034e4eeaf807904ab0ad3e96e64049197981f7c
Add N2E Fist latch reset probe
```

Validated N2E diagnostic DLL:

```text
SHA256 2382A50D0265BCF8743E9B7E40E32398341CCE23088CEA9F33790469FD881F96
length 439808
```

Canonical N2E raw:

```text
research/raw/2026-09-06_fist_n2e_same_process_native_latch_reset.log
raw evidence commit 7e635bc26a3ac8f9d79d84ed57d230278b2b2be1
length 15677
SHA256 6801DBD78CEA4436186F43CFC1462A1951806644EF96CC95B97E0EBE44715865
```

Two marked P0 Normal/Fist attacks ran in the same game process with no reload, DLL change, manual latch restoration, or intervening attack.

Attack 1:

```text
AcceptedFistSequenceOrdinal: 1
ProbeMode: SUPPRESS_FIRST
C1Generation: 1
SPUAddress: EBB67074
LatchBefore: 0
LatchAfter: 1
WriteAttempted: 1
WriteConfirmed: 1
User visual damage: NO
no ENTITY_ON_DAMAGE_ENTRY before attack 2
```

Attack 2:

```text
AcceptedFistSequenceOrdinal: 2
ProbeMode: OBSERVE_SECOND
C1Generation: 2
same SPUAddress: EBB67074
LatchBefore: 0
LatchAfter: 0
WriteAttempted: 0
WriteConfirmed: 0
User visual damage: YES
```

The complete N2E raw contains exactly one `ENTITY_ON_DAMAGE_ENTRY`, after attack 2:

```text
CallerModule: Game.dll
CallerRVA: 0x0016E348
ThisEntityName: Golem
EntityArg1Name: Fist
EntityArg1IsResolvedFistSource: 1
EntityArg2Name: PC_Hero
EntityArg2IsPlayer: 1
```

### N2E conclusion — CASE A / NATIVE REARM PASS

For the tested human-Fist P0 Normal path:

```text
attack 1 authored intervention sets SPU+0x164 = 1
-> current combat move damage dispatch suppressed
-> native lifecycle later creates a fresh combat move
-> same SPU+0x164 is naturally 0 again before attack 2 marker
-> no manual restoration was performed
-> normal Fist gCEntity::OnDamage dispatch and visual damage resume
```

Therefore production Fist OFF does **not** need marker-owned/manual restoration merely to permit the next fresh combat move. The native combat lifecycle provides the required fresh-move rearm in this tested path.

Do not overstate N2E. It does not prove the complete semantic meaning of the byte for all combat types, PhysicalFist, monsters, or repeated OFF->ON windows inside one combat move.

---

## Exact next responsibility — STAGE C PRODUCTION FIST_OFF MINIMAL LATCH INTEGRATION

Implement the first production human-Fist OFF mechanism using only the behavior now proven by N2D/N2E.

### Production semantics

Existing `G3AB_COL_FIST` remains exact Stage A:

```text
resolve/validate human gEUseType_Fist raw 8
-> TouchDamage.ClearTriggeredList()
-> no collision-group mutation
-> no DamageDisabled mutation
-> no weapon source-mask semantics
```

Add a distinct production marker opcode/token:

```text
G3AB_COL_FIST_OFF
```

For an accepted exact-human-Fist `FIST_OFF` marker:

```text
resolve the current actor's established gCScriptRoutine_PS / gCScriptProcessingUnit
read exact byte SPU+0x164
write exact byte SPU+0x164 = 1
optional diagnostic readback/logging
no other SPU mutation
no TouchDamage property mutation
no collision-group mutation
no ClearTriggeredList on FIST_OFF
no manual restoration
no persistent Fist latch ownership/state
```

`FIST_OFF` means:

> suppress native Fist damage dispatch for the remainder of the current combat move; native fresh-move lifecycle rearms the latch for the next combat move.

### Important same-move boundary

Do **not** implement same-combat-move re-enable after `FIST_OFF` in this stage.

A later `G3AB_COL_FIST` after `G3AB_COL_FIST_OFF` within the same combat move is not a proven rearm mechanism because Stage-A FIST only clears the TouchDamage triggered list and does not clear `SPU+0x164`.

Therefore Stage C supports one terminal Fist OFF for the remainder of the current combat move. Any future requirement for OFF->FIST re-enable inside one combat move is a separate evidence/design task.

Do not add a manual `SPU+0x164 = 0` operation as a shortcut.

### Marker/parser/ownership requirements

- add `MarkerOpcode_FistOff` without changing RIGHT/LEFT/BOTH/OFF/FIST meanings;
- recognize exact `G3AB_COL_FIST_OFF` distinctly from `G3AB_COL_FIST` (avoid prefix ambiguity);
- include FIST_OFF in the existing exact marker scan/occurrence/dedupe machinery rather than creating a parallel parser or lifecycle tracker;
- FIST_OFF is a logical Fist marker, not a weapon source-mask bit;
- an animation containing FIST and/or FIST_OFF continues to use the existing exact human-Fist source requirement/validation;
- preserve existing callback ownership/suppression architecture and C1 generation identity;
- do not infer behavior from filename alone.

### Remove temporary N2E behavior

Delete the process-local N2E `AcceptedFistSequenceOrdinal` probe and its SUPPRESS_FIRST/OBSERVE_SECOND behavior. Production behavior must not depend on process-local test ordinals.

The N2C/N2A/N2B diagnostic hooks may remain diagnostic-only if they are still useful, but they must not drive production semantics.

### Actor scope

Implement through the current marker actor's established routine/SPU path, not a hard-coded player singleton. Production logic is for exact human `gEUseType_Fist` actors that satisfy the existing Fist source resolution/validation.

Do not broaden to:

```text
gEUseType_PhysicalFist raw 55
monsters/general body collision
per-limb markers
```

### Diagnostics

Under `FRAME_COLLISION_DIAGNOSTICS`, log a bounded factual FIST_OFF record sufficient to validate:

```text
Boundary: FIST_OFF_COMBAT_LATCH
Actor / ActorAddress
Action
AniPhase
StateTime
CurrentMovementAni
C1Generation if available
SPUAddress
LatchOffset: 0x164
LatchBefore
LatchAfter
WriteAttempted
WriteConfirmed
FistSourceAddress
FistUseType
FistCollisionGroup
```

Behavior-only build must perform the production FIST_OFF latch operation without requiring diagnostic code.

### Preserve

Do not change:

```text
RIGHT / LEFT / BOTH / OFF semantics
weapon source masks
C1 repair/lifecycle safety
marker generation/occurrence/dedupe identity
attack-family recognition
StatePosition behavior
Power/Pierce/SimpleWhirl/Hack adapters
native callback ownership rules except the minimal FistOff marker recognition needed by existing ownership logic
```

### Explicit non-goals

Do not implement or design in Stage C:

```text
manual latch restoration
persistent Fist lifecycle state
terminal/interruption restoration
same-move FIST_OFF -> FIST re-enable
DamageDisabled / IsEnabled / ReactToTouch changes
collision-group changes for Fist
extra ClearTriggeredList on FIST_OFF
hook/patch sAICombatMoveItlLoop
skip/replace gCEntity::OnDamage
PhysicalFist / monsters / generalized body collision
per-limb Fist markers
weapon source-mask redesign
family / StatePosition / C1 redesign
final mixed regressions
Raise / playback-speed work
```

### Expected implementation scope

Inspect only the exact marker/parser/source-operation files needed. Reuse the existing marker opcode, marker scan, result, diagnostics, and actor routine/SPU patterns. Do not add a new subsystem.

After implementation, stop before runtime validation. Report final remote commit SHA, changed files, build status, and any material contradiction.

---

## Frozen continuation

```text
A      — dedicated FIST baseline                    CLOSED/PASS
B      — marker-time DamageDisabled intervention    CLOSED/FAIL AS CURRENT OFF INTERVENTION
R      — exact restoration to Stage A behavior      CLOSED/PASS
N1     — native trigger-state observation           CLOSED/PASS AS OBSERVATION
N2A    — gate/TriggerTarget timing                  CLOSED/INCONCLUSIVE
N2B    — hook observability discrimination          CLOSED/CASE A FOR BOTH HOOKS
N2C    — gCEntity::OnDamage caller trace            CLOSED/PASS AS PATH IDENTIFICATION
N2D    — SPU+0x164 marker-time intervention         CLOSED/PASS — CASE A
N2E    — same-process native latch reset proof      CLOSED/PASS — CASE A
Stage C — production FIST_OFF minimal integration   CURRENT/NEXT
```

---

## Local-state caution carried forward

Earlier local status showed this unrelated untracked file:

```text
research/raw/2026-09-04_hack_2h_dedicated_p0_override_validation.log
```

Do not delete, rename, stage, overwrite, or clean it merely to obtain a clean working tree.

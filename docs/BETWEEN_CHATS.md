# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-06

## Current bridge — N3 same-move Fist latch-zero rearm probe frozen

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
Fist body-contact source semantics              CLOSED/PASS — EV-029, EV-080–EV-084
Fist Stage A marker/source plumbing             CLOSED/PASS — EV-221, reinterpreted by EV-224
Fist Stage B marker-time DamageDisabled probe   CLOSED/FAIL AS CURRENT OFF INTERVENTION — EV-223
Fist N1 native trigger-state observation        CLOSED/PASS AS OBSERVATION — EV-222–EV-223
Fist N2A gate/TriggerTarget timing               CLOSED/INCONCLUSIVE
Fist N2B hook observability discrimination      CLOSED/CASE A FOR BOTH HOOKS
Fist N2C gCEntity::OnDamage caller trace         CLOSED/PASS AS PATH IDENTIFICATION — EV-224
Fist N2D SPU+0x164 causal suppression probe      CLOSED/PASS — EV-225
Fist N2E same-process native latch reset proof   CLOSED/PASS — EV-226
Stage C production FIST_OFF validation          CLOSED/PASS — EV-227
same-move FIST/FIST_OFF timing observation       RECORDED — EV-228–EV-229
N3 same-move latch-zero rearm probe              CURRENT/NEXT — FROZEN DIAGNOSTIC
```

Do not reopen these findings without concrete contradictory evidence.

---

## Physical source fact — closed

Logical human `gEUseType_Fist` / raw 8 is a body-contact source, not a literal right-hand attack source.

Controlled tests established damaging contact through at least:

```text
left hand
right hand
left leg
right leg
head
```

Do not reopen limb-side semantics. This evidence does not generalize to `gEUseType_PhysicalFist` / raw 55, monsters, or every possible body part.

---

## Stage A causal reinterpretation

The old positive Stage-A runs established this factual sequence:

```text
accepted G3AB_COL_FIST
-> exact human gEUseType_Fist / raw 8 resolved
-> TouchDamage.ClearTriggeredList() executed
-> Fist collision group remained 0
-> later target damage was observed
```

N2C later proved that the tested damaging path was:

```text
gCScriptProcessingUnit::sAICombatMoveItlLoop
Game + 0x16DD00
    -> indirect gCEntity::OnDamage call at Game + 0x16E346
    -> observed return address Game.dll + 0x16E348
```

Therefore the Stage-A temporal sequence does **not** causally prove that `ClearTriggeredList()` enabled or created the native Fist damage. Stage A remains valid marker-recognition, exact-source resolution, group-0 preservation and operation-plumbing evidence; it is not a proven native Fist ON mechanism.

The older claim that triggered-list clearing is the critical Fist rearm operation is superseded for this confirmed native human-Fist combat-loop path. The causal role of `ClearTriggeredList()` on that path is currently unproven. Do not infer that list clearing is globally useless: it may matter on other TouchDamage paths.

---

## Proven native Fist path and latch

Within the tested Normal/Fist combat-loop branch:

```text
Game + 0x16DFB9  cmp byte ptr [SPU+0x164], 0
Game + 0x16DFC0  jne Game+0x16E352
```

A nonzero byte exits before the later Fist damage dispatch. Once native hit timing is reached, the loop itself commits:

```text
Game + 0x16E1A3  mov byte ptr [SPU+0x164], 1
```

before continuing toward `gCEntity::OnDamage`.

N2D causally established:

```text
SPU+0x164 = 1 before native hit dispatch
-> confirmed Fist gCEntity::OnDamage path suppressed
-> no observed visual target damage
```

N2E causally established in one process, without reload or manual restoration:

```text
attack 1 intervention: same SPU+0x164 0 -> 1
-> no OnDamage entry; visual damage NO

fresh attack 2 marker: same SPU+0x164 already 0
-> no marker-owned write
-> confirmed OnDamage entry; visual damage YES
```

Thus fresh combat-move lifecycle naturally returns the tested latch to 0. The SDK exposes no named public member/accessor for this byte; call it only the factual/internal `SPU+0x164` combat latch. Do not generalize its meaning outside the tested human-Fist path.

---

## Stage C production FIST_OFF — causally validated

Implementation:

```text
9266c2fe7c2ff628440a3602caff3fe48e6b46b0
Add production Fist OFF latch marker
```

Canonical validation evidence:

```text
research/raw/2026-09-06_fist_stagec_production_fist_off_validation.log
evidence commit f0a53d12bb3ab8b811c71cce14b1d26bc59c3e76
SHA256 F2A98F5936C1E29BAB716285E4055254B0AB0F8050BC3AEB26B9E1A7B84651EF
```

Validated sequence:

```text
accepted G3AB_COL_FIST
accepted G3AB_COL_FIST_OFF
FIST_OFF latch 0 -> 1
WriteAttempted: 1
WriteConfirmed: 1
FIST_OFF TriggeredListClearCount: 0
FIST_OFF collision-group mutation: none
complete run Fist-correlated ENTITY_ON_DAMAGE_ENTRY: none
User visual damage observation: NO
```

Conclusion: production `G3AB_COL_FIST_OFF` is causally validated as OFF/suppression for the tested human-Fist P0 Normal native path.

---

## Same-move timing evidence

### FIST -> FIST

Canonical raw:

```text
research/raw/2026-09-06_fist_on_on_test.log
evidence commit fe43f8d24e4d582455f24b4a1b37a686bbf5cb1d
SHA256 EDDDC17994B7B171AE3EB885C9901F16BACBC876B6469862948AC0FD40C2C79D
```

Observed order:

```text
first FIST accepted:  StateTime 0.127985
Fist OnDamage entry: PlayerStateTime 0.414992
second FIST accepted: StateTime 0.487977
User observation: first punch missed, second punch hit
```

The native damage event occurred **before** the second FIST marker. The second FIST did not cause that observed hit. This run is not proof of same-move FIST rearm.

### FIST -> FIST_OFF -> FIST

Canonical raw:

```text
research/raw/2026-09-06_fist_on_off_on_test.log
evidence commit fe43f8d24e4d582455f24b4a1b37a686bbf5cb1d
SHA256 3EDA3D55325D2F03E1F595E6FDE81EEDEDED6992D88EE3EE85065A87F58714197
```

Observed across the committed executions:

```text
first FIST accepted: around StateTime 0.13
FIST_OFF accepted: around StateTime 0.365–0.369
FIST_OFF latch: 0 -> 1, write confirmed
second FIST accepted: around StateTime 0.485
second FIST operation: ClearTriggeredList only; no SPU+0x164 clear
Fist-correlated ENTITY_ON_DAMAGE_ENTRY after OFF: none
User observation for the controlled test: both punches missed
```

The current second FIST does not reverse FIST_OFF inside the same combat move. This does not decide whether an explicit latch-0 FIST operation would rearm native damage.

---

## Frozen current semantic model

```text
Native fresh-move state
    SPU+0x164 = 0
    confirmed native damage path armed

Current production G3AB_COL_FIST
    exact human gEUseType_Fist / raw 8 validation
    + TouchDamage.ClearTriggeredList()
    does not clear SPU+0x164
    NOT YET causally proven to arm/rearm the confirmed native damage path

Production G3AB_COL_FIST_OFF
    exact human gEUseType_Fist / raw 8 validation
    + SPU+0x164 = 1
    no ClearTriggeredList()
    no collision-group mutation
    causally proven to suppress the confirmed native damage path
```

## Exact next responsibility — N3 FIST same-move latch-zero rearm probe

### Frozen diagnostic question

During the existing two-punch human-Fist P0 Normal combat move, after production `G3AB_COL_FIST_OFF` has written `SPU+0x164` from 0 to 1, does a later accepted `G3AB_COL_FIST` writing that same byte from 1 back to 0 causally rearm the confirmed native `sAICombatMoveItlLoop -> gCEntity::OnDamage` damage path in the same combat move?

This is a diagnostic causal probe only. It does not authorize production FIST latch-zero semantics.

### Frozen diagnostic intervention

For every accepted exact-human-Fist `G3AB_COL_FIST` in the diagnostic build only:

1. Preserve the existing Stage-A FIST operation unchanged:
   - resolve/validate exact human `gEUseType_Fist` / raw 8;
   - call `TouchDamage.ClearTriggeredList()`;
   - perform no collision-group mutation.
2. Then:
   - resolve the current marker actor's existing `gCScriptRoutine_PS` / SPU;
   - read the exact byte `SPU+0x164`;
   - write the exact byte `SPU+0x164 = 0`;
   - perform volatile readback;
   - log the factual before/after/write-confirmation result.

Apply this intervention to every accepted exact-human-Fist FIST marker. Do not condition it on remembered marker history and do not add persistent state.

The latch-zero write must exist only under `FRAME_COLLISION_DIAGNOSTICS` for N3. Behavior-only production `G3AB_COL_FIST` must remain exact current Stage A: exact raw-8 validation plus `ClearTriggeredList()`, with no latch-zero write.

Production `G3AB_COL_FIST_OFF` must remain unchanged.

Keep the existing N2C `gCEntity::OnDamage` diagnostic hook unchanged.

### Controlled fixture

Exact animation:

```text
Hero_Stand_None_Fist_P0_Attack_Hit_N_Fwd_00_%_00_P1_100_R.xmot
```

Authored markers:

```text
frame 3:  G3AB_COL_FIST
frame 9:  G3AB_COL_FIST_OFF
frame 12: G3AB_COL_FIST
```

Expected factual intervention sequence if prior evidence reproduces:

```text
first FIST
    latch 0 -> 0

FIST_OFF
    latch 0 -> 1

second FIST
    latch 1 -> 0
```

### Required N3 diagnostic logging

For each accepted `G3AB_COL_FIST`, log:

```text
Boundary: FIST_COMBAT_LATCH_REARM_PROBE
ElapsedMs
Actor
ActorAddress
Action
AniPhase
StateTime
CurrentMovementAni
C1Generation
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

### Frozen runtime classification

#### CASE A — SAME-MOVE REARM PASS

Required observations:

```text
first FIST latch 0 -> 0 confirmed
FIST_OFF latch 0 -> 1 confirmed
second FIST latch 1 -> 0 confirmed
Fist-correlated ENTITY_ON_DAMAGE_ENTRY occurs after second FIST
CallerModule: Game.dll
CallerRVA: 0x0016E348
User second-strike damage observation: YES
```

Conclusion: explicit latch-zero FIST causally rearms the confirmed native damage path in the same combat move.

#### CASE B — OFF STATE NOT PRESENT

Condition:

```text
second FIST LatchBefore is not 1
```

Stop. Prior OFF persistence did not reproduce; do not interpret rearm.

#### CASE C — LATCH ZERO INSUFFICIENT

Required observations:

```text
second FIST latch 1 -> 0 write confirmed
no later Fist-correlated ENTITY_ON_DAMAGE_ENTRY
User second-strike damage observation: NO
```

Conclusion: latch zero alone is insufficient to rearm after OFF at this same-move timing.

#### CASE D — NATIVE PATH RESUMES BUT VISUAL DAMAGE DOES NOT

Required observations:

```text
second FIST latch 1 -> 0 confirmed
Fist-correlated ENTITY_ON_DAMAGE_ENTRY resumes after second FIST
CallerModule: Game.dll
CallerRVA: 0x0016E348
User second-strike damage observation: NO
```

Conclusion: native dispatch rearm is proven, but authored gameplay/contact timing remains unresolved.

#### CASE E — EARLY NATIVE DAMAGE REGRESSION

Condition:

```text
Fist-correlated OnDamage occurs before FIST_OFF in the controlled fixture
```

Stop and treat this as a contradiction/regression of the established timing fixture.

### Promotion boundary

The N3 freeze alone does not authorize production FIST latch-zero semantics. Production promotion requires runtime CASE A, or separate interpretation if runtime produces CASE D.

### N3 implementation non-goals

Do not add or change:

- manual end-of-move restoration;
- persistent Fist lifecycle state;
- previous-marker tracking;
- new marker opcodes;
- collision-group behavior;
- `DamageDisabled`, `IsEnabled`, or `ReactToTouch`;
- hooks or patches to `sAICombatMoveItlLoop`;
- `gCEntity::OnDamage` skipping or replacement;
- `gEUseType_PhysicalFist` / raw 55;
- monsters or generalized body collision;
- per-limb semantics;
- weapon source masks;
- C1, StatePosition, or attack-family behavior.

---

## Explicitly unresolved / out of scope

- `gEUseType_PhysicalFist` / raw 55;
- monsters or generalized body collision;
- the global meaning of `SPU+0x164` outside the tested human-Fist path;
- whether `ClearTriggeredList()` matters on other TouchDamage paths;
- manual latch restoration;
- persistent marker-owned Fist lifecycle state;
- production same-move OFF -> FIST re-enable semantics before N3 evidence permits promotion;
- RIGHT/LEFT/BOTH/OFF weapon semantics, C1 lifecycle, attack-family/StatePosition redesign, Raise, playback-speed work, target acquisition, or climbing.

Evidence authority: EV-224–EV-230 in `docs/EVIDENCE_LEDGER_199_ONWARD.md`.

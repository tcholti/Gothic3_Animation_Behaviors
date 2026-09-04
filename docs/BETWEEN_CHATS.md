# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-04

## Current bridge — Final collision mixed regression / compatibility closure

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat must read `docs/SESSION_ENTRYPOINT.md` first and follow its bootstrap.

---

## Closed / protected boundary

```text
collision architecture verification             COMPLETE — EV-206–EV-215
Power marker adapter validation                 CLOSED/PASS
Pierce marker adapter validation                CLOSED/PASS
SimpleWhirl current marker/semantic stage       CLOSED/PASS
Hack isolated routing/source/marker validation  PASS
```

Do not reopen these without concrete contradictory evidence.

Latest Hack evidence commit:

`ec36039df8cafa5f17658d4307fa1c109d82cce0`

Earlier Hack evidence commits used in the current conclusion:

```text
2c283befecefdbf9d170210865d2c29b7cd6d81d  Hack 2H FinishingAttack fallback control
4a6cae2a3bd880c88d48cf8f8b52d78e9bb6a890  Hack distance + Recover pose validation
ec36039df8cafa5f17658d4307fa1c109d82cce0  Hack Staff + marker validation
```

---

## Hack result to preserve

Routing/source behavior:

```text
Action 14 remains HackAttack
missing dedicated Hack asset -> original FinishingAttack fallback remains usable
dedicated Hack asset present -> Hack resource is selected
2H and Staff both pass
routing has no Hero/2H/Staff family gate
active resolver namespace is preserved
Hack marker bookkeeping remains StatePosition 1
```

Marker behavior proven across 2H + Staff:

```text
RIGHT
RIGHT -> OFF -> RIGHT
single RIGHT -> natural terminal cleanup
OFF before first RIGHT -> delayed RIGHT
```

All tested marker operations used the exact right equipped source, with valid C1 generations and no observed `RepairAttempted: 1` / outstanding-generation failure in the reviewed runs. User visually confirmed attacks worked and connected with targets; interruption attempts were made during target tests, but exact interruption timing was not visually proven and need not be chased absent contradictory log evidence.

### Animation-resolution / authored suffix fact

Do not infer the resolver requires the final logged `.xmot` filename literally.

Jackydima `Script_Animation` `GetAniName` reconstructs only through:

```text
Actor_State_LeftUse_RightUse_SourcePose_Action_Phase_N/O_Direction_00_
```

and can provide custom namespaces such as `Axe`. Destination pose, movement distance and later suffix fields belong to the resolved resource. This is why a dedicated Hack resource may carry its own destination/distance metadata while the current G3AB adapter only changes the action identity in the lookup prefix.

This retrieval ownership was underrepresented in the older Hack handoff and must be repaired in `ANIMATION_INDEX.md` / `SOURCE_HOOK_GUIDE.md` / current design/evidence routing during final closure. **Do not redesign the currently working Hack code because of the stale wording.**

### 2H pose-chain qualification

Known complete 2H Hack sequence:

```text
Hero_Parade_None_2H_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_2H_P0_HackAttack_Hit_N_Fwd_00_%_00_P1_100.xmot
Hero_Parade_None_2H_P1_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot
```

Changing the Hit destination `P1 -> P0` prevented expected Recover; restoring the native-like P1 progression restored it. New Balance did not change that result. Exact native cause remains unknown and is not worth further current-scope research.

The numeric distance is not fixed by G3AB; a `...P0_200.xmot` dedicated Hack Hit was selected successfully.

Known Staff Hack sequence:

```text
Hero_Parade_None_Staff_P0_HackAttack_Raise_N_Fwd_00_%_00_P0_0.xmot
Hero_Parade_None_Staff_P0_HackAttack_Hit_N_Fwd_00_%_00_P0_100.xmot
Hero_Parade_None_Staff_P0_HackAttack_Recover_N_Fwd_00_%_00_P0_0.xmot
```

---

## Exact next responsibility

Two final strong collision regression runs remain.

### Run A — native-control mixed regression

Use the current G3AB diagnostic collision DLL and current authored fixtures with **New Balance and Script_AttackCollision absent**.

Exercise a strong practical mixture of:

```text
marked + unmarked attacks
different supported melee weapon families
repeated attacks / ordinary transitions
interruption attempts
Hack dedicated override + fallback where practical
true FinishingAttack Action 15 if convenient
```

Pass criteria:

```text
no crash
no visible stuck collision
expected hit/contact behavior
unmarked/native attacks remain native
marker-owned source/lifecycle behavior remains healthy
no new C1/generation/repair anomaly
```

### Run B — New Balance + Script_AttackCollision compatibility regression

Repeat a similarly strong mixed regression with both compatibility mods present:

```text
current G3AB diagnostic collision DLL
+ New Balance
+ Script_AttackCollision
```

This is deliberately stronger than earlier compatibility spot checks and is the final mature-collision compatibility checkpoint.

New Balance compatibility is an explicit project criterion. This test is for **collision** compatibility only. Playback-speed compatibility remains separately unresolved because the current speed-control hook is already known to conflict with New Balance and must use a different intervention design later.

Freeze exact raw filenames immediately before each run according to the actual run date; do not invent stale dates in advance.

---

## After both runs pass

Perform one bounded collision closure/knowledge-maintenance transaction:

```text
interpret final native + compatibility logs
-> append canonical evidence
-> update EVIDENCE_INDEX
-> repair Hack fallback/GetAniName/Script_Animation/Axe retrieval ownership
-> update DESIGN + COLLISION_TEST_PLAN current status
-> archive fully processed Power/Pierce/SimpleWhirl/Hack raw evidence with canonical paths updated
-> close equipped-weapon collision implementation
```

Then continue the already-planned production collision migration/diagnostics-free integration before branching to Raise + playback-speed work.

Fist/body source adaptation, AttackContinuationProtection, deeper Hack pose semantics, Raise, speed redesign, target acquisition and climbing remain separate responsibilities unless new evidence forces reconsideration.

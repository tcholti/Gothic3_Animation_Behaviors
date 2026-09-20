# Raw8 FIST Authoring Semantics Review

**Status:** ACTIVE — DESIGN AGREED / RESEARCH GATE  
**Opened:** 2026-09-20  
**Evidence trigger:** EV-346

## Agreed author-facing semantic

User + Normal Chat agreed on 2026-09-20 that marked factual `gEUseType_Fist` / raw8 should use a persistent authored opportunity model:

```text
marked C1 starts
-> raw8 authored opportunity CLOSED

accepted FIST
-> authored body-contact damage opportunity OPEN

while OPEN
-> Gothic owns target/contact/damage
-> unsuccessful native contact attempt does not consume authored opportunity

first successful native contact
-> authored opportunity CONSUMED/CLOSED

later accepted FIST
-> authored opportunity OPEN again

C1 / Hit termination, interruption or factual replacement
-> any unused authored opportunity CLOSED
```

The marker defines the beginning of eligibility, not one exact frame on which contact must already exist.

No arbitrary timeout is part of the desired semantic. The natural upper lifetime boundary is the factual attack/C1 lifetime.

### FIST_OFF decision

Do **not** add authored FIST_OFF for raw8 unless future evidence demonstrates a concrete unwanted-contact problem requiring it.

The weapon OFF marker exists because a physically active weapon can damage unintended nearby actors during visually inactive frames. Existing raw8 evidence, including EV-082 and the User's allied-NPC control observation, instead supports target/focus-directed eligibility: unarmed attacks did not damage an allied NPC that could not be selected with weapons drawn, while weapon contact did.

This supports the present design decision that raw8 does not need an OFF marker merely to mirror weapon vocabulary.

### Raw55 follow-up

The same author-facing FIST meaning should later be checked against permanent raw55/PhysicalFist behavior. Do not copy raw8 mechanics into raw55. The desired abstraction may be shared while the native mechanisms remain separate.

The immediate research responsibility is raw8 only.

## Historical question

For marked factual `gEUseType_Fist` / raw8 attacks, what should an authored `G3AB_COL_FIST` mean?

Current production meaning:

```text
FIST
-> rearm SPU+0x164 once
-> if before native timing threshold, grant one exact synthetic timing comparison
-> Gothic performs one native contact opportunity at that authored moment
-> native latch closes the opportunity
```

Alternative authoring meaning under review:

```text
FIST
-> open/rearm a logical body-contact opportunity from this authored point
-> Gothic remains responsible for target/contact/damage
-> if the actor has not reached a valid target yet, eligibility remains available
-> successful contact consumes the authored opportunity
-> another FIST rearms another opportunity
-> end of Hit / factual C1 replacement closes any remaining opportunity
```

The second model is conceptually closer to equipped marker authoring: activation defines an eligibility window rather than requiring the animator to place the marker on the exact frame where geometry already overlaps.

## Why this gate reopened

EV-346 Gargoyle factual raw8 Power produced:

```text
native/no marker        7/7 damage
FIST around frame 3     5/10 damage
FIST at frame 1         0/4 damage
FIST at frame 6         8/8 damage
```

All marked cases had correct raw8 ownership, accepted markers and clean finalization. Frame-1 and frame-3 failures therefore expose the consequence of the current one-shot timing design rather than a marker-recognition/lifecycle defect.

Frame 6 arrived at approximately Gothic's native contact timing and used `SyntheticApplied=0 / NATIVE_TIMING`, restoring native-like 8/8 contact.

## Historical reason for current one-shot design

EV-234–EV-235 established the native timing gate and proved that one exact synthetic `GetPlayTime` comparison can advance the native raw8 opportunity without mutating the global animation clock or dispatching custom damage.

EV-238 established the opposite late-marker problem: if a marked execution does not close native permission at C1 start, Gothic can damage before a late authored FIST. EV-239 therefore froze the conservative production contract:

```text
marked C1 start -> close native latch
each FIST       -> one native opportunity
unmarked        -> fully native
```

That contract solved marker authority and native preservation. It did not prove that one-shot pulse semantics are the best author-facing abstraction.

## Non-negotiable invariants for either decision

```text
unmarked raw8 remains completely native
factual source/UseType governs applicability; no species rules
Gothic retains target/contact/damage authority
no direct/custom damage
marked attack cannot damage before its first FIST
C1/animation/source identity remains exact and generation-scoped
interruption cannot leak an old opportunity into a later move
Normal / Power / Quick / Sprint separation remains factual
raw55 stays separate
equipped marker behavior stays unchanged
diagnostics are not required for release behavior
```

## Option A — retain one-shot FIST pulse

Meaning:

```text
each FIST = perform one native raw8 opportunity now
```

Advantages:
- already proven and production-stable;
- very small intervention surface;
- preserves the native raw8 one-shot mechanism closely;
- repeated FIST already has an exact meaning.

Costs:
- animator must place FIST at a frame where target/body geometry is already capable of contact;
- early markers can permanently miss even though the actor reaches the target later in the same Hit;
- author-facing semantics differ materially from equipped collision markers.

If retained, this difference must be explicit in author documentation: raw8 FIST is a damage/contact pulse, not an ON window.

## Option B — persistent authored opportunity window

Intended semantic target:

```text
first FIST
-> contact becomes eligible from here onward

failed early native contact attempt
-> authored opportunity remains eligible

first successful native contact
-> consume this authored opportunity

later FIST
-> rearm another authored opportunity

end Hit / interruption
-> close remaining opportunity
```

Advantages:
- closer to the general marker mental model;
- robust to moving body attacks such as Gargoyle;
- marker identifies the beginning of damage eligibility instead of requiring exact overlap timing.

Costs / unknowns:
- Gothic's native raw8 latch is itself one-shot; merely leaving timing permission armed is not sufficient if Gothic writes the latch closed on an unsuccessful attempt;
- we need a factual success/failure signal that can exist in production without turning diagnostic `OnDamage` observation into custom damage ownership;
- repeated/multi-target/contact semantics must be proven rather than assumed;
- an explicit FIST_OFF may or may not become justified if authored inactive gaps are desired.

## Required research before production implementation

Current status:

1. **CLOSED — EV-347:** the tested native path closes `SPU+0x164` after both unsuccessful and successful early synthetic attempts.
2. **CLOSED FOR THE TESTED ROUTE — EV-347:** the existing post-original `AICombatMoveInstr` boundary plus exact same-invocation `Game+0x16E348` / source / actor identity distinguishes hit from miss without a new hook.
3. **CLOSED FOR TESTED POWER ROUTE — EV-348:** one exact post-miss latch-only rearm can restore a later native opportunity without custom target/damage logic; 7/9 rearmed misses later produced exact native raw8 damage, while successful early hits remained consumed.
4. Existing bridge transport was sufficient; no new hook was required.
5. **REFINED BY EV-349:** timing is not the only remaining question. A future persistent opportunity must distinguish genuine no-contact from legitimate Gothic target-state rejection (for example knocked-down/get-up protection); visible health damage is not a valid success oracle.
6. **LIFECYCLE REQUIREMENT CONFIRMED BY EV-349:** an unused rearmed latch can survive Hit-C1 replacement into Recover under the temporary probe. Final behavior must close any unused authored opportunity at the exact C1/Hit replacement/interruption boundary.
7. **NEXT RESEARCH QUESTION:** find the smallest native factual boundary that distinguishes geometric/no-contact from target-state rejection while keeping Gothic in ownership of target/vulnerability/damage. Only after that boundary is understood should continuous-timing policy be finalized.
8. FIST_OFF is **not part of the agreed raw8 design** absent future contradictory evidence.

## Gate

The author-facing semantic is decided. Production redesign remains prohibited until the native mechanism is established causally.

EV-347 closed the first bounded observation question: both hit and miss synthetic attempts return with `SPU+0x164 = 1`.

EV-348 closes the post-miss latch-rearm causal question. Latch-only recovery is causally sufficient to restore a later native opportunity on the tested Power route.

EV-349 adds two constraints before any production design:
- target-state rejection such as knockdown/get-up protection must not be mistaken for a collision miss merely because no visible damage occurs;
- unused authored opportunity must be closed at exact C1/Hit termination because the temporary rearm can otherwise remain live into Recover.

No new Work implementation task is active. The next step is to identify the smallest factual native distinction between genuine no-contact and legitimate target-state rejection, **after POP-12 knowledge-state validation passes**.

Phase-4 broad regression remains paused until this research chain either proves a safe persistent-window mechanism or forces a design revision.

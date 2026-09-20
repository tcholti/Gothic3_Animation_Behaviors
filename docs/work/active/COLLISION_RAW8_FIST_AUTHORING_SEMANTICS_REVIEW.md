# Raw8 FIST Authoring Semantics Review

**Status:** ACTIVE — DESIGN / RESEARCH GATE  
**Opened:** 2026-09-20  
**Evidence trigger:** EV-346

## Question

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

## Required research before Option B can be implemented

Do not modify production behavior yet. The next causal work, if Option B is chosen in principle, must first determine:

1. whether the native `SPU+0x164 = 1` close occurs on every eligible attempt or only on a successful contact path;
2. where the smallest factual post-attempt boundary exists that distinguishes an unsuccessful contact opportunity from a successful one;
3. whether rearming only after a failed attempt can preserve one damage per authored opportunity without custom target/damage logic;
4. whether existing bridge transports can expose that fact or a new narrow transport seam is required;
5. how repeated FIST and interruption behave under the candidate window model;
6. whether FIST_OFF is actually required for authoring or can remain absent.

## Gate

No Work implementation task is active.

Phase-4 broad regression is paused at this design gate. Normal Chat + User must first choose the intended author-facing semantic. If persistent-window semantics are preferred, freeze one diagnostic causal question at a time under `FEATURE_DEVELOPMENT_METHOD.md` before any production redesign.

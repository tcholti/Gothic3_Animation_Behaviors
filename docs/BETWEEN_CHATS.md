# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-04

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `development`  
Stable branch: `main` — frozen.

## Current state

```text
collision production integration = CLOSED/PASS through EV-390
Speed v2 / resolved profile identity = CLOSED/PASS through EV-410
neutral release Speed INI = LOCKED/PASS
Speed shipping catalogue = 27 tested profiles / 97 tested attack settings
BaseSpeed = ReferenceHitBaseSpeed for every shipped Speed setting
installation alone does not intentionally retime attacks

Raise AddRaise = ACTIVE NEXT FEATURE
Raise design = LOCKED
public first-scope keys:
  Normal_AddRaise
  Quick_AddRaise
  Whirl_AddRaise
shipping default for every AddRaise key = Off
```

## Continue here

Read in this order:

1. root `README.md` -> Start Here
2. `docs/SESSION_ENTRYPOINT.md`
3. this file
4. `docs/work/active/RAISE_ADDRAISE_IMPLEMENTATION_PRECHECK.md`
5. `docs/DESIGN.md` Raise section
6. `docs/WORK_IMPLEMENTATION_PROTOCOL.md` and `docs/FEATURE_DEVELOPMENT_METHOD.md` before assigning implementation

Do not reopen Speed or collision absent contradictory evidence.

## Locked Raise product design

```text
feature = additive Raise only

Off / missing
-> G3AB adds nothing
-> native Gothic behavior stays untouched

On
-> G3AB asks Gothic to execute the matching Raise phase
-> Gothic resolves the concrete Raise animation itself
-> after Raise completes, original attack path continues
```

Do not expose user-facing controls for disabling/replacing native Raise merely for symmetry.

First production scope only:

```text
Normal
Quick
Whirl
```

Do not initially add custom AddRaise support for:

```text
Power
Pierce
Hack
SimpleWhirl
Finishing
Sprint
```

No separate user-facing Raise speed setting.

## Profile architecture

Reuse the accepted resolved animation-set profile identity:

```text
AnimationFamily
+ ResolvedLeftAnimationToken
+ ResolvedRightAnimationToken
```

No weapon-specific C++ branches such as 1H / 2H / Axe / Rapier.

The implementation must be generic from the start. Hero None+2H is only the first runtime fixture because the User already has ready Raise assets for:
- Normal;
- Quick;
- full Whirl.

After 2H acceptance, 1H is a cross-profile/generalization test and should require no new feature branch.

## Historical Raise proof

Historical source:
`18844a35379992def7c9b112b0e70fdaa5fe082e` / `AttackRaise.cpp`.

Proven old sequence:

```text
PS_Melee_Attack
-> PREPEND_BREAK_BLOCK
-> sAICombatMoveInstr(same factual action, "Raise", 1.0)
-> wait for Raise
-> untouched original state
-> original Hit / continuation
```

Historical runtime observations:
- Gothic automatically resolved the correct 2H P0/P1 Raise resource; G3AB did not build a filename.
- the old 2H Normal Raise implementation coexisted successfully with New Balance.
- old Speed/New Balance incompatibility was a separate mechanism problem and is already solved by Speed v2.

Preferred first production transport:

```text
Normal -> PS_Melee_Attack state prepend
Quick  -> PS_Melee_QuickAttack state prepend candidate
Whirl  -> PS_Melee_WhirlAttack state prepend
```

Existing lower-level `sAICombatMoveInstr` interception is fallback only if a state route proves insufficient.

## One remaining pre-implementation question

Quick is the only unresolved transport fact.

Existing evidence proves Gothic eventually converts generic Quick/Action3 into factual:
- QuickAttackR / Action4;
- QuickAttackL / Action5.

Before freezing production implementation, statically determine:

```text
At PS_Melee_QuickAttack entry intended for PREPEND_BREAK_BLOCK,
is PropertyAction already factual Action4/5?

YES
-> use factual R/L directly for Quick Raise
-> freeze generic Normal/Quick/Whirl production implementation

NO / still Action3
-> find the smallest existing factual-selection boundary in the same Quick route
-> do not invent R/L selection logic in G3AB
-> if necessary use the lower-level CombatMove boundary narrowly for Quick
```

Do not repeat broad Raise architecture research.

## First runtime acceptance sequence

After independent source review and local build/deployment identity:

```text
A. AddRaise Off control
   2H Normal / Quick / Whirl stay native

B. Native stack, Hero None+2H
   enable Normal_AddRaise
   enable Quick_AddRaise
   enable Whirl_AddRaise
   verify Raise -> Hit -> normal continuation
   verify no duplicate/repeated Raise
   exercise both Quick R/L where gameplay reaches them

C. Intended New Balance stack
   repeat 2H Normal / Quick / Whirl
   reconfirm Normal coexistence
   establish Quick + NB and Whirl + NB coexistence

D. Speed-coupling contrast
   after neutral-speed AddRaise passes,
   deliberately change tested BaseSpeed values
   observe whether added Raise naturally follows the same relative timing
   only if not, return to design for the smallest generic solution
   do not add a RaiseSpeed key

E. Cross-profile generalization
   create/provide matching 1H Raise assets
   enable AddRaise on 1H profile(s)
   expect zero new C++ weapon/profile branches
```

## Raise animation naming rule

G3AB does not construct Raise filenames.

```text
G3AB requests factual action + Raise phase
-> Gothic resolves pose/use-type/direction/etc.
-> Gothic requests the concrete serialized Raise resource
-> animator provides the asset Gothic expects
```

Release README must explain Gothic's filename fields/rules with matched real examples for:
- `Attack_Hit` / `Attack_Raise`;
- `QuickAttackR_Hit` / `QuickAttackR_Raise`;
- `QuickAttackL_Hit` / `QuickAttackL_Raise`;
- `WhirlAttack_Hit` / `WhirlAttack_Raise`.

Do not tell authors to blindly replace only `Hit` with `Raise`; destination pose and movement/reach suffixes may differ.

## Protected boundaries

```text
NO Speed redesign
NO collision redesign
NO Finishing changes
NO weapon-specific AddRaise policy
NO manual Raise filename construction in C++
NO New Balance policy copying
NO separate RaiseSpeed setting without contradictory runtime evidence
NO broader AddRaise family scope before Normal/Quick/Whirl acceptance
NO main promotion yet
```

## Exact next responsibility

Close the single Quick factual-action static question.

Then freeze and hand off one bounded production implementation task for generic profile-driven Normal/Quick/Whirl AddRaise, with all shipping INI AddRaise values Off by default.

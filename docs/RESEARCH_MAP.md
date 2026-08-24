# Gothic 3 Animation Behaviors — Research Map

**Status:** Canonical engineering-state map  
**Date:** 2026-08-24
**Supersedes:** the "current/next" state in the older v0.2 Research & Implementation Map and v0.1 handoff.

## 1. Purpose

This document records the current engineering state of the Gothic 3 Animation Behaviors project.

It separates confirmed facts, strongly supported findings, working hypotheses, unresolved questions, design decisions, completed milestones, and the immediate implementation sequence.

Historical documents remain useful source material, but this file is the current continuation map.

## 2. Evidence Vocabulary

- **CONFIRMED** — SDK/source verification, controlled runtime logging, or controlled behavior-changing test.
- **STRONGLY SUPPORTED** — repeated empirical animation-modding evidence and/or multiple converging observations.
- **WORKING HYPOTHESIS** — plausible explanation still requiring isolation.
- **UNKNOWN** — not sufficiently investigated.
- **DESIGN DECISION** — intended project behavior, not a claim about native engine behavior.

## 3. Current Project Priorities

### Priority A — Frame-controlled melee collision

Complete the generalized authored-frame collision mechanism while preserving correct source selection and native reset behavior.

### Priority B — Raise control

Move the proven Raise mechanism into the unified production system and generalize it carefully across intended human melee families.

### Priority C — Playback-speed control

Implement profile-aware speed authority that is compatible with existing mods and supports a consistent animation-timing standard.

### Later

- intended-target/crosshair enforcement;
- Recover interruptibility consistency if still needed;
- climbing and broader Gothic 3 scripting research.

## 4. Completed Milestones

### 4.1 Development and diagnostic foundation — COMPLETE

- Visual Studio 2022 / CMake / Win32 toolchain established.
- SDK/examples build path proven.
- CombatMove logger created and used successfully.
- multiple dedicated prototype DLLs created and tested.

### 4.2 CombatMove phase/speed baseline — COMPLETE

Confirmed tested values include:

- 1H Attack Hit `0.600`
- 2H Attack Hit `0.700`
- QuickAttack Hit `1.000`
- PowerAttack Raise `1.500`
- PowerAttack Hit `1.000`

Ordinary Recover visibly plays without appearing as a normal separate external CombatMove request in the original logger.

### 4.3 Raise proof of concept — COMPLETE

A previously unused 2H normal-Attack Raise was successfully prepended with `PREPEND_BREAK_BLOCK`.

The engine resolved the correct P0/P1 Raise automatically.

Original Hit, target propagation, collision, pose alternation, and Recover remained intact.

This proof currently covers the Normal path. The v0.13 2H Quick collision
regression played no Raise because Quick Raise insertion has not yet been
generalized or enabled; existing 2H/Staff Quick Raise assets remain future
integration targets rather than current behavior.

### 4.4 Initial speed override — COMPLETE AS PROOF

`Script_G3AnimationBehaviors v0.1` proved a Raise toggle for normal 2H, configurable normal 2H Hit speed, and that the stock 2H Hit modifier could be observed at `0.700` and overridden to `1.000`.

Compatibility with another mod using the same upstream speed hook is not solved.

### 4.5 Frame-effect reverse engineering — COMPLETE

Confirmed pipeline:

`custom authored frame effect in Blender -> exported .xmot -> eCVisualAnimation_PS::UpdateFrameEffects -> gCEffectSystem::StartEffect -> DLL marker recognition -> custom code at the authored frame`

### 4.6 Marker-driven collision proof — COMPLETE

Confirmed:

- exact current Hit motion can be inspected before marker fires;
- marker presence can declare custom ownership;
- native timed `OnAI_Attack` activation can be suppressed for that execution;
- marker can activate collision and clear the triggered list;
- marker ownership follows the marked exact animation rather than a hard-coded P0/P1 rule.

### 4.7 Natural weapon collision reset — COMPLETE

A hook on `eCEntity::SetCollisionGroup` confirmed the ordinary weapon path resets:

`5 -> 7` at activation, then `7 -> 5` at Hit -> Recover.

A mandatory end marker is not needed for ordinary single-hit attacks.

### 4.8 Playback-speed synchronization of marker — COMPLETE

For a tested 2H normal Hit authored from frame 0 through frame 12 inclusive (13 sampled frames):

- marker frame stayed tied to the authored animation frame when playback speed changed;
- marker timing shifted in real time as expected with speed;
- marker-to-collision call delay was approximately `0.02–0.03 ms`.

### 4.9 Staff player test — COMPLETE

`Script_FrameCollisionTest v0.6` successfully controlled a Staff normal attack using the actor's actual right-hand Staff/Halberd item.

Natural reset also worked.

### 4.10 NPC Staff test — COMPLETE

A non-player human NPC using Hero-family Staff animations successfully used marker-controlled collision on its own equipped halberd.

This confirms the system is not inherently player-specific.

### 4.11 QuickAttack diagnostic — COMPLETE

Staff QuickAttack markers fire correctly.

Native action values observed include QuickAttackR and QuickAttackL.

`v0.6` still rejects those executions because its eligibility path is tied to the literal `_Attack_Hit_` Normal-attack naming assumption, so native collision occurs before the marker.

This is an implementation limitation, not a frame-marker limitation.

### 4.12 Fist/body-contact observation — COMPLETE

With marked Fist tests and native timed activation suppressed:

- left leg damage worked;
- right leg damage worked;
- right hand damage worked;
- left hand damage worked.

The same logical right-slot `Fist` entity was used, remained collision group `0`, and `SetCollisionGroup(Item_Attack)` did not visibly change that stored group.

## 5. Current Prototype State

### Script_G3AnimationBehaviors

Current known integrated proof version: `v0.1`.

Proven concepts:

- Raise configuration;
- speed configuration;
- game loads correctly alongside the separate frame-collision prototype.

### Script_FrameCollisionTest

Current validated prototype: `v0.8` at commit `f4d2946`.

Retained proven behavior:

- exact-motion marker ownership;
- marked Normal attack path;
- generalized player/NPC eligibility;
- Staff Normal;
- natural weapon collision reset;
- separate Quick/QuickR/QuickL callback/action/Hit eligibility;
- right-hand prototype source meaning;
- no Staff/UseType/Pose gate.

v0.7 runtime result:

- QuickR/action 4 and QuickL/action 5 first activated at marker frame 6;
- no pre-marker native activation occurred;
- after every natural 7 -> 5 reset, an unmarked 5 -> 7 reactivation occurred;
- v0.7 failed runtime validation.

v0.8 player runtime result:

- standalone Win32 Release build succeeded;
- installed DLL matched the build at SHA-256 `18DDE8B770400C76709063FA0888EFEF888F41C2FE03B3449508BC43DA120858`;
- QuickAttackR/action 4 and QuickAttackL/action 5 each activated only at marker frame 6;
- each accepted Quick marker changed `Routine.PropertyStatePosition` 0 -> 1;
- both executions naturally reset collision 7 -> 5 without the v0.7 post-reset reactivation;
- one marked Normal/action 1 regression retained marker-frame-5 activation and natural reset;
- no per-actor ownership state was introduced.

Player and human-NPC Staff QuickR/L validation are complete. In the NPC test, `OutNovice_01` produced two QuickAttackR/action 4 and five QuickAttackL/action 5 executions using its own `It_Halberd_01`; all seven passed marker, bookkeeping, and reset checks.

Current causal source candidate: `v0.9` at commit `11f2a1b`.

- identifies only raw `gEUseType_Fist` and `gEUseType_PhysicalFist`;
- skips `SetCollisionGroup(Item_Attack)` only for those resolved sources;
- keeps `ClearTriggeredList` unconditional;
- preserves Normal/Quick ownership and Quick StatePosition bookkeeping;
- logs the raw source UseType and whether the group request was skipped;
- leaves every non-Fist activation path unchanged.

Build `89f36d8` failed because the script-layer `Entity` wrapper has no `GetUseType()` member. Build `9b4a73c` then failed because the base `eCEntity` returned by `GetInstance()` also has no member `GetUseType()`. Commit `11f2a1b` uses the SDK-declared game-layer static resolver `gCEntity::GetUseType(eCEntity*)` and compiled successfully. The installed v0.9 DLL matches the successful build at SHA-256 `16B2F35DBA817F344F24BADED3ABEA7ED5A237ACDCED631008CEAF675A9F3140`; the validated v0.8 rollback copy remains preserved. Runtime contact validation is complete: the native left hand and custom right hand, left leg, right leg, and head all passed. The right-leg fixture's collision effect was accidentally authored on frame 2 and its whoosh on frame 3; this does not change the Fist source conclusion.

Current diagnostic candidate: `v0.10` at commit `6914039`.

- marked Normal/Quick ownership and activation behavior remain v0.9;
- the global `SetCollisionGroup` observer now compares the changed entity pointer with the player's exact left- and right-slot entity pointers;
- every transition involving `Item_Attack` is labelled `LEFT`, `RIGHT`, `BOTH`, `NONE`, or `NO_PLAYER` and includes current player action, phase, primary pose, state time/position, animation, and both slot snapshots;
- no Pierce, Power, SimpleWhirl, or Whirl callback is newly intercepted for behavior;
- Win32 Release compilation passed on 2026-08-22 with only the pre-existing Windows SDK C5105 warning;
- installed/build SHA-256 matches at `647B8C36C0FEA9D16C898F069894028DE0769FF7C4D7A30A84DDE2F0422B0C6D`;
- validated v0.9 rollback SHA-256 is `16B2F35DBA817F344F24BADED3ABEA7ED5A237ACDCED631008CEAF675A9F3140`;
- controlled unmarked player Dual runtime passed: exact slot labels produced the complete Normal/Quick/Pierce/Power source map and paired activation/reset records.

Validated duplicate-dispatch prototype: `v0.11` at commit `0bbc377`.

- preserves v0.10 ownership, source selection, Fist handling, Quick
  bookkeeping, and diagnostics;
- records the last accepted marker per actor;
- ignores only the same actor + source + motion + marker + action + phase +
  state-time tuple repeated within 5 ms;
- performs no collision-group request and no triggered-list clear for the
  ignored duplicate;
- leaves a genuine later marker at a different state time eligible to activate
  and rearm normally;
- Win32 Release build/install passed at SHA-256
  `F47EAD5B403DA701F32CCD23B2A2A429BDB16491DDE0864E0CF10CF76C78D154`;
  the v0.10 rollback is preserved at SHA-256
  `647B8C36C0FEA9D16C898F069894028DE0769FF7C4D7A30A84DDE2F0422B0C6D`;
- the exact two-marker regression passed across six executions: 12 genuine
  accepts/clears, six ignored same-update duplicates, and six natural resets;
- ignored callbacks had zero state-time delta, arrived 0.0574–0.1162 ms after
  the accepted late callback, and performed no collision/list mutation;
- two-contact damage remained observable against two targets.

Tested explicit-OFF prototype: `v0.12` at commit `685bbb7`.

- recognizes provisional `G3AB_COL_OFF_TEST` only inside a Normal/Quick Hit
  whose exact motion is already owned by `G3AB_COL_TEST`;
- records a weapon-style ON window by actor, resolved source, exact motion,
  action, and phase;
- OFF requests `Item_Equipped` only while that matching marker-owned source is
  still in `Item_Attack`;
- OFF never clears the triggered list;
- OFF before ON, after natural reset, or for Fist/body is consumed as a logged
  no-op rather than changing unrelated collision state;
- natural engine reset and accepted OFF both retire marker ownership;
- v0.11 same-update deduplication applies independently to ON and OFF names;
- Win32 Release build/install passed at SHA-256
  `F268FEDB96B1FDED304443FE34A62BA19A02BE214D6084C1B9A014FBD159758B`;
  the v0.11 rollback is preserved at SHA-256
  `F47EAD5B403DA701F32CCD23B2A2A429BDB16491DDE0864E0CF10CF76C78D154`.

Physical OFF passed in the horizontal 2H sweep. Three ON-only executions each
logged one activation/clear and one natural reset and could damage all three
wolves. Seven ON-f7/OFF-f9 executions each logged one 5 -> 7 and one 7 -> 5;
they usually hit one wolf and sometimes two when tightly grouped. Ten
ON-f7/OFF-f8 executions produced the same clean state sequence and never hit
more than one wolf. OFF performed no list clear in all 17 executions.

Later ON also restores collision physically, but the double fixture exposed a
new replay defect. Each of four single-target and three multi-target executions
visually retained both swings, while the late state-time batch was `ON, OFF,
ON`. The single-target log therefore contains 12 ON accepts/clears and eight
OFF accepts; the multi-target log contains nine and six. Each attack performs
three 5 -> 7 operations, two explicit 7 -> 5 OFF operations, and one natural
7 -> 5 cleanup instead of the authored two ON and one OFF.

The v0.11 last-accepted guard is insufficient when marker names interleave.
Validated v0.13 at commit `7a0f1b7` retains that guard as the first layer and
adds a second per-execution authored-occurrence budget. Retaining both is
necessary:
same-update identical suppression prevents an early duplicate from consuming
the budget intended for a later genuine contact, while the occurrence budget
rejects replay with interleaved marker names.

- exact-motion ON/OFF counts are scanned once and cached by animation name;
- accepted counts are actor + source + motion + action + phase specific;
- state-time rollback starts a new execution;
- natural collision cleanup outside the owning Hit retires the execution;
- the tested motion budgets two ON and one OFF;
- runtime lookup/checking occurs only when a reserved marker fires; there is no
  per-frame actor/world scan;
- the test DLL's verbose logging is diagnostic overhead, not intended release
  behavior.

Win32 Release build/install passed at SHA-256
`0E4A50AD5ED6F7D641FD23503298011F4CE7943628AC09AC3D257F075FC1D692`;
the v0.12 rollback is preserved at SHA-256
`F268FEDB96B1FDED304443FE34A62BA19A02BE214D6084C1B9A014FBD159758B`.

All seven double-fixture executions matched the contract independently: two ON
accepts/clears, one OFF accept/no-clear, one replayed OFF rejected by the
budget, one final ON rejected as an exact same-update duplicate, and one
natural cleanup. Every first ON logged execution-budget reset; every rejected
callback requested neither collision mutation nor list clearing. Both intended
swings visibly damaged each of two separately tested targets on their first
attack. Large-battle performance is not yet profiled; the event-driven/cached
cost model is confirmed by source structure, not by this functional test.

The family-specific Quick regression is also complete. Four 2H executions—
three QuickAttackR/action 4 and one QuickAttackL/action 5—each reproduced the
same exact budget result: two accepted ON/clears, one accepted OFF/no-clear,
one budget-rejected replayed OFF, one duplicate-rejected final ON, and one
natural cleanup. Each first ON changed Quick StatePosition 0 -> 1 and each
second genuine ON preserved 1 -> 1. The targeted QuickAttackL visibly damaged
the opponent at both intended contacts. Actual Whirl remains unsupported until
its named callback/action/phase adapter is added separately.

Current validated prototype: v0.17 at source commit `931cc32`. Its Win32
Release build/install SHA-256 is
`F1E141BF33BE1821DDC6D17C8EBB63751FEFE092AB7193A60EA4ACFD8E25AB5A`.
The v0.16 interruption-boundary correction remains intact, and the first
isolated BOTH gate passed. Sixteen P0 Dual Normal executions each accepted one
BOTH occurrence, activated and cleared RIGHT plus LEFT independently, and
published exact mask 3. The single-marker right -> left -> right fixture visibly produced two contacts
because the first weapon was not later rearmed. A subsequent repeated-BOTH
session contained 17 complete P0 BOTH -> BOTH -> BOTH executions, each with six
source requests and six list clears; all three same-target contacts were
observed. Four P0 interruptions after the second BOTH reset both sources, and
all later executions began fresh. Eleven complete P1 alternating-source
controls plus one interrupted P1 retained expected behavior. The separate
missing-left test delivered ten BOTH markers with required mask 3 but no LEFT
source; every marker was consumed without custom mutation while the untouched
native callback activated/reset RIGHT ten times. Basic BOTH activation, rearm,
interruption cleanup, and incomplete-source fallback now pass. Mixed exact-set
control also passed: 28 complete controlled player schedules plus four
interrupted prefixes preserved BOTH/LEFT-or-RIGHT/OFF/BOTH ordering, all three
visual contacts, occurrence/dedupe protection, and no-clear OFF behavior. The
multi-target follow-up retained damage across opponents.

A larger overlapping battle produced 39 fresh marked executions across
PC_Hero, AssWarrior_07, and Silvio: 19 complete and 20 valid interrupted
prefixes, using distinct source addresses with no observed cross-actor
contamination. Sixty-six markers received in actual Power motions were rejected
at the Normal/Quick gate. This proves tested functional stability, not low
release overhead; verbose logging remained enabled and frame time was not
measured. Next run a compact Dual Quick mixed-set regression, then consider the
source vocabulary freeze. Power and Whirl remain separate callback adapters.

### Prototype marker

`G3AB_COL_TEST`

Status: proven research marker, not finalized production vocabulary.

## 6. v0.8 Implementation — PLAYER AND NPC RUNTIME PASSED

v0.8 keeps the v0.7 callback/action/phase/marker ownership model and completes
the Quick callback's one-shot bookkeeping only at accepted marker time.

The implementation remains intentionally narrow:

1. resolve Normal versus Quick marker context;
2. retain all ownership and source checks;
3. activate the right-hand prototype source and clear its triggered list;
4. for Quick only, set `PropertyStatePosition = 1`;
5. log Quick state position before and after;
6. leave Normal behavior unchanged.

The controlled player test confirms the predicted correction: both Quick markers
observed state position 0 and changed it to 1; neither natural 7 -> 5 reset was
followed by the v0.7 delayed 5 -> 7 reactivation. A controlled human-NPC test
then reproduced the corrected sequence seven times on the NPC's own equipped
Halberd. This promotes the fix's tested player/NPC behavior to **CONFIRMED**,
while the exact unobserved native callback internals behind the original defect
remain **STRONGLY SUPPORTED**.

The current `G3AB_COL_TEST` marker still means the actor's right-hand equipped
item. Do not mark Dual or Torch+1H Quick animations until explicit source
handling exists.

## 7. v0.8 Test Matrix

### Player Staff Quick — PASSED

Confirmed for QuickAttackR/action 4 and QuickAttackL/action 5:

- marker frame 6 performed the only 5 -> 7 activation;
- Quick StatePosition changed 0 -> 1;
- natural 7 -> 5 reset remained;
- no immediate post-reset 5 -> 7 occurred;
- the following attack began from collision group 5.

### Player Staff Normal regression — PASSED

One marked Normal/action 1 activated at marker frame 5 and naturally reset
7 -> 5. The separate Normal adapter remained compatible with the shared
activation/reset core.

### NPC Staff Quick — PASSED

For `OutNovice_01` using its own `It_Halberd_01`:

- QuickAttackR/action 4 occurred twice;
- QuickAttackL/action 5 occurred five times;
- all seven marker events changed StatePosition 0 -> 1;
- all seven activated 5 -> 7 and naturally reset 7 -> 5;
- no immediate post-reset reactivation occurred.

Other later unmarked collision cycles were separated native NPC attacks, not the
v0.7 same-execution reactivation.

Generic Quick/action 3 remains untested. Neither controlled player nor NPC
session selected it.

## 8. Fist Causal Test — COMPLETE AND PASSED

Question answered: `SetCollisionGroup(Item_Attack)` is unnecessary for the
five tested player Fist body contacts when the logical Fist source is rearmed by
clearing its triggered-damage list.

Validated v0.9 branch:

- raw Fist/PhysicalFist detection uses static
  `gCEntity::GetUseType(eCEntity*)`;
- Fist/PhysicalFist skips the weapon-style group request;
- `ClearTriggeredList` remains active;
- all non-Fist marker paths remain unchanged.

Passed contact motions:

1. native left hand — marker frame 3;
2. custom right hand — marker frame 3;
3. custom left leg — marker frame 3;
4. custom right leg — marker frame 2;
5. custom head — marker frame 3.

All five visibly damaged a focused target while the accepted marker resolved
UseType 8, kept group 0 -> 0, skipped the group request, and cleared the list.
The right-leg frame-2 marker is a controlled-fixture deviation, but a positive
result still proves that the omitted group request was not required for that
contact.

Production consequence:

- distinguish weapon activation from Fist/body rearming in the collision helper;
- a Fist marker should rearm the logical Fist source without requesting
  `Item_Attack`;
- keep claims limited to the tested player Fist contacts;
- separately validate PhysicalFist 55 and monster-specific body sources when
  those families are implemented.

Limitations retained:

- the four focused-neutral custom-motion sessions may have ended before Recover
  completed, so they are not Recover/reset tests;
- unfocused allied humans are invalid Fist targets;
- accepted-marker counts exceeded fresh ownership decisions in repeated
  unfocused input, whose callback/action-state cause remains open.

No inverse isolation is required unless later evidence contradicts the positive
matrix.

## 9. Source-Resolver Work After Quick + Fist

The production collision API must separate callback/action family, authored source choice, and physical body-contact mechanism.

Controlled v0.10 player Dual runtime source map:

- P0 Normal: left weapon.
- P1 Normal: right weapon.
- P0 QuickAttackR and QuickAttackL: right weapon.
- P1 QuickAttackR and QuickAttackL: left weapon.
- P0 Pierce: right weapon.
- P1 Pierce: left weapon.
- P0 and P1 Power: both weapons.
- all 17 activation records had paired 7 -> 5 resets in phase 3.

The Power group result contradicts the earlier P0-left-only recollection and
converges with Jackydima's initial BOTH activation. It does not prove all three
visual contacts can damage: P0 is right -> left -> right and P1 is left -> right
-> left, while native behavior is reported to damage only twice. The first
weapon must be rearmed for its second contact. Jackydima later clears both lists
again; v0.10 did not observe that operation.

Other source evidence to preserve:

- Dual P3 Quick file: should be left visually; whether the game currently uses it is unconfirmed.
- Dual has SimpleWhirl only; its files use the `WhirlAttack` name token and its exact source/contact intent remains to be tested.
- Jackydima's SimpleWhirl code uses left in Dual P1 and right otherwise.
- Human 2H/Staff have the separate full Whirl; Jackydima activates right and enables `PropertyResetOnUntouch`.
- ordinary human 1H families have no Whirl; hand-to-hand coverage remains unknown.
- Torch+1H P1 and P3 Quick: left torch.
- Some Torch+1H P0 Normal attacks natively use the left torch incorrectly; Jackydima's correction sends regular Torch+1H Normal collision to the right weapon.
- One Dual finishing animation may visually use both weapons; exact native source remains unconfirmed and one damaging source is acceptable for that animation.

Needed future validation still includes:

- 1H;
- Torch + 1H;
- Shield + 1H;
- 2H;
- Staff;
- Fist beyond the completed player UseType-8 matrix;
- Dual SimpleWhirl source/contact intent and Dual Power third-contact rearm;
- separate 2H/Staff full-Whirl recontact/`ResetOnUntouch` behavior;
- later monster-specific cases.

## 10. Dual Normal/Quick/Pierce/Power Source Discovery — COMPLETE

The controlled targetless player session used unmarked Dual animations, two
distinct equipped 1H entity instances, seven Normal attacks for stance changes,
both Quick variants in P0 and P1, two Block prerequisites, both Pierce poses,
and both Power poses.

| Tested execution | Logged source |
|---|---|
| P0 Normal | LEFT |
| P1 Normal | RIGHT |
| P0 QuickAttackR | RIGHT |
| P0 QuickAttackL | RIGHT |
| P1 QuickAttackR | LEFT |
| P1 QuickAttackL | LEFT |
| P0 Pierce | RIGHT |
| P1 Pierce | LEFT |
| P0 Power | RIGHT + LEFT |
| P1 Power | RIGHT + LEFT |

Every activation had a paired 7 -> 5 reset in phase 3. Pierce collision and
cleanup passed; Pierce Recover is known-good and is not a project issue or
follow-up target.

Next Dual work is SimpleWhirl plus Power multi-contact rearming. Dual does not
have the separate full Whirl used by 2H/Staff. The diagnostic must observe
`ClearTriggeredList`, because first group activation alone cannot distinguish
native two-hit Power from the intended three-contact sequence. Marked v0.10 2H
Normal testing without NewBalance or `Script_AttackCollision` established that
one marker activation/list clear can damage multiple distinct opponents: four
attacks logged one frame-7 activation and one natural reset each, while one
observed swing hit three wolves and at least two hit two wolves. Target-identity
logging remains useful for future automatic evidence, but the project marker
path is no longer blocked on basic multi-target capability. Pinned NewBalance
independently clears both Dual weapon lists through `FixDualOneHanded`, so the
rearm fix is not exclusive to `Script_AttackCollision`. Separate later 2H/Staff
Whirl work should observe `ResetOnUntouch` and OFF-gap needs.

## 11. Production Marker Vocabulary — EQUIPPED-SLOT API FROZEN

The equipped-slot API is now frozen and shared across attack callback families:

- `G3AB_COL_RIGHT` publishes/rearms the exact RIGHT slot set;
- `G3AB_COL_LEFT` publishes/rearms the exact LEFT slot set;
- `G3AB_COL_BOTH` publishes/rearms both equipped slot entities;
- `G3AB_COL_OFF` closes the marker-owned set without clearing lists.

RIGHT/LEFT are equipped-slot identities, not filename direction letters. New
animations must use only these final names; v0.18 deliberately provides no
`*_TEST` aliases. Body/unarmed/Fist/monster naming remains a separate open
design problem.

Historical implementation staging made this contract concrete before the names
were frozen. The v0.14 candidate keeps `G3AB_COL_TEST` as RIGHT for
regression compatibility and adds `G3AB_COL_LEFT_TEST`. RIGHT and LEFT replace
the exact active source set owned by the current marked execution; selecting
LEFT after RIGHT therefore retires only marker-owned RIGHT. OFF retires the
whole set. The actor record is two equipped-source pointers plus a two-bit mask,
and the cached occurrence budget has separate RIGHT/LEFT/OFF counters. BOTH is
not recognized yet, but the fixed source-set representation is intentionally
ready for it after LEFT and RIGHT validation.

LEFT runtime validation is now complete for the tested player Dual Normal
family. The mixed P0-only log preserves unmarked native P1 behavior, while the
stronger P0/P1 replacement log contains six P0 and five P1 marked executions.
Those 11 contacts produced 11 left activations/clears and 11 left resets with
no player right activation. Because native P1 normally uses RIGHT, the P1
result directly proves source replacement rather than additive activation.
The preserved RIGHT regression has also passed. Four 2H Normal
RIGHT-f4/OFF-f10/RIGHT-f15 executions retained exactly the accepted/rejected
marker pattern and physical collision sequence proven in v0.13, with no LEFT
activation. The alternating exact-set gate passed for 29 complete Dual Normal
executions: P0 accepted RIGHT -> LEFT -> RIGHT and P1 accepted the mirror, with
source retirement/rearm at each change and three visible same-target contacts.
One accidental unmarked side Normal remained native.

Two marked attacks were interrupted. The important case changed to action 59
after the first source naturally reset, yet a later RIGHT marker was accepted
because Normal marker-time eligibility used the still-current `_Attack_Hit_`
filename without checking action/phase. The immediate next gate is therefore a
small Normal safety correction: require `gEAction_Attack` and `gEPhase_Hit` at
marker time, then reproduce an interruption. BOTH remains disabled until that
regression passes.

The v0.15 implementation applies the same exact Normal predicate at
`OnAI_Attack` callback entry and global reserved-marker dispatch:
`gEAction_Attack` + `gEPhase_Hit` + current `_Attack_Hit_` motion. It changes no
source-set or timing behavior and adds no per-frame work. It built and installed
successfully. Two interruption sessions preserved 21 complete Dual alternating
executions and repeated 2H Normal/Quick behavior. Damage reactions stopped
later marker delivery, so no invalid-action marker mutation occurred, but the
exact action-59 late-marker rejection branch was not directly reproduced.

Those sessions exposed a different boundary problem in the v0.13 occurrence
record. One 2H Normal ended after its first RIGHT. Natural 7 -> 5 cleanup
occurred at state time 0 while stale action/phase/motion still matched, so the
budget was retained. The next attack's first RIGHT was accepted as occurrence
2/2 without reset and its genuine second RIGHT was rejected. A new-execution
signal must therefore be recognized at natural marker-owned retirement (or by
an equivalent generation mechanism), without treating explicit OFF or
same-execution source switching as a new attack. This correction precedes BOTH.

Real Dual Power is still deliberately outside callback ownership. In two probe
logs every Power-context RIGHT/LEFT marker was rejected before mutation, while
native Power activated and reset both weapons. The user's three-contact visual
observations are therefore native evidence only. Reuse the motion under Normal
filenames for marker tests; add `OnAI_PowerAttack` ownership separately later.

There is no separate generic ON marker. "ON" is only shorthand for the
activation behavior already carried by RIGHT/LEFT/BOTH. A multi-contact file
can therefore author RIGHT at the first contact, OFF after that swing, and
RIGHT again at the next contact; each RIGHT opens a fresh right-source window.

The same-target causal test is complete. One identical 2H double-contact motion
was tested under the proven Normal callback with no marker, first-contact marker
only, and first-plus-second-contact markers. Native and one-marker variants hit
the target once; the two-marker variant hit at both intended contacts. This
confirms that a repeated source marker rearms the same weapon against the same
target without requiring OFF.

The later authored marker dispatched twice at identical `StateTime` in all four
two-marker attacks, yielding three accepted clears per attack. Only two damage
contacts occurred. v0.11 validates the narrow same-update guard described
above: six repeated executions each retained the early and late marker while
ignoring exactly one duplicate late callback.
Current v0.10 also logs the first matching authored frame for every dispatch, so
accepted-marker count and `StateTime` remain the authoritative diagnostic.
Actual Whirl is still a separate callback-ownership test and is unsupported by
the v0.10 marker handler.

This separation is important for custom 2H/Staff double attacks: explicit OFF
can prevent a nearby target from being struck by the second weapon motion before
its intended acceleration, while the next source marker opens a clean second
contact window.

The compact Dual Quick mixed-set checkpoint is complete. Forty-seven fresh
executions covered all four tested P0/P1 QuickAttackR/L variants; 45 completed
the full P0 BOTH -> LEFT -> OFF -> BOTH or P1
BOTH -> RIGHT -> OFF -> BOTH schedule and two stopped safely after OFF. Every
first BOTH performed Quick StatePosition 0 -> 1 and every later source marker
preserved 1 -> 1. No malformed sequence or delayed native reactivation was
found. The shared marker-source core is therefore validated across the tested
Normal and Quick families.

v0.18 is validated. Its Win32 Release build/install matched at SHA-256
`427A7CF4EB72BF76DBA573768BCCE5C45151994C6D36B99EA23D7A5869AACBCC`.
Twenty-four complete final-name executions covered P0/P1 Normal and all four
tested P0/P1 QuickAttackR/L variants. Every execution accepted the exact
BOTH -> side -> OFF -> BOTH schedule, began with a fresh budget, rejected only
the expected replay callbacks, and naturally cleaned up both sources. Quick
StatePosition bookkeeping remained correct, no delayed native player
activation appeared, and all three intended contacts were visually confirmed.
This closes the equipped-slot vocabulary plus shared Normal/Quick marker core
for the current stage.

Whirl ownership is now mapped. Native logging plus official/pinned source
evidence establishes two separate paths:

- full 2H/Staff Whirl: `OnAI_WhirlAttack`, action 10, Hit phase, RIGHT;
- Dual SimpleWhirl: `OnAI_SimpleWhirl`, action 6, Hit phase, with LEFT for
  the logged P0 filename/runtime pose 2 case and RIGHT for the logged P1
  filename/runtime pose 1 case.

The v0.19 source candidate at `a78f231` adds only the full-Whirl adapter. It
reuses the closed v0.18 source-set/rearm/OFF core, sets StatePosition to 1 on
accepted source markers, leaves SimpleWhirl native, and does not enable
`ResetOnUntouch`. Build/runtime validation is next: test 2H and Staff
RIGHT -> OFF -> RIGHT separately, including two same-target contacts, the OFF
gap, cleanup, bookkeeping, and absence of delayed native activation. Then add
SimpleWhirl independently. Power remains a later separate adapter. A quiet
prototype-disabled/enabled battle comparison remains required before claiming
negligible release overhead. Visible target stumble is not a reliable damage
proxy during rapid repeated hits; a damage/health logger extension remains
optional diagnostic work.

## 12. Raise Generalization — After Collision Core Stabilizes

Known starting point: 2H Normal works.

Likely controlled expansion:

1. 2H normal integrated into unified module;
2. Staff normal;
3. 2H/Staff Quick where Raise assets exist;
4. 1H family;
5. Torch + 1H;
6. Shield + 1H;
7. Dual;
8. selected Whirl/SimpleWhirl only where desired.

At each step verify resolved Raise, source/destination pose, Hit, Recover, speed, collision, and player/NPC behavior where relevant.

## 13. Speed-System Continuation

Current design goal:

- configure by animation family + normalized left/right animation UseTypes + action profile;
- preserve native behavior for missing profiles;
- apply custom speed only to matching profiles;
- avoid unsafe conflict with NewBalance's upstream speed hook.

Open implementation question:

What is the safest final point for production speed authority?

A downstream CombatMove `AniSpeedScale` intervention remains a leading option.

## 14. Recover Policy

Confirmed engine behavior:

ordinary Recover can start internally without appearing as a separate external CombatMove request.

Project design decision:

controlled Recover should follow the effective Hit speed and should not expose a separate user tuning key.

Separate issue:

Recover interruptibility has shown inconsistencies among attack variants and may later need a dedicated diagnostic.

## 15. Important Current Unknowns

1. Final body/unarmed/Fist/monster collision marker terminology.
2. General primary/secondary/all source resolver.
3. Exact Fist activation/rearm causality.
4. Safe compatibility strategy when multiple DLLs hook the same callback/function.
5. Final production speed-hook location.
6. Exact final INI syntax after current code is migrated.
7. Which Whirl/SimpleWhirl attacks should opt into Raise.
8. Multi-hit source/rearm semantics across all supported weapon families.
9. Monster-specific physical damage-source resolution.
10. Exact relationship among action R/L, final filename R/L, `Routine.HitDirection`, and victim reaction selection; no current implementation depends on it.

## 16. Superseded Earlier Continuation Points

The following old "next tasks" are historical, not current:

- first Recover-speed search;
- first collision ON/OFF comparison;
- first player-only 2H collision proof;
- Staff marker feasibility;
- NPC marker feasibility;
- whether marker timing remains synchronized when speed changes.

Those questions produced later results and should not be restarted unless a new regression specifically requires them.

## 17. Later Research

### Optional logical hit-direction diagnostic

CombatMoveLogger v0.4 does not currently log `Routine.HitDirection`. No current collision, Raise, or speed plan requires it.

If a later feature depends on reaction-side selection, extend the consolidated logger rather than creating a separate temporary DLL. The useful record should pair attacker action/pose/current motion and `HitDirection` with the victim's selected reaction action/current motion at the damage event. A controlled follow-up may force only HitDirection Left versus Right while preserving attack frames and collision.

### Intended target

Still relevant but outside the current immediate animation-behavior core.

Distinct concepts remain FocusEntity, CurrentTarget, AlternativeTarget, AlignmentTarget, action target, CombatMove TargetEntity, and SPU context entities.

### Climbing

Long-term separate Gothic 3 scripting investigation. Not part of the current combat implementation.

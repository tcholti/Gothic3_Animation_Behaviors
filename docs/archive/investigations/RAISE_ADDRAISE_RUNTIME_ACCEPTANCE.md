# Raise — AddRaise Runtime Acceptance

**Status:** CLOSED/PASS — archived after EV-422 final runtime acceptance  
**Branch:** `development`  
**Current source candidate:** `41ed80c6420e5236d13fc037cb5923b946cb8ccc`  
**Prior sequencing baseline:** `bc46dcf7d22305c4d9d4f99fc5f5a1075ef726bd`  
**Source review:** PASS — EV-416 + EV-419  
**Scope:** AddRaise + EV-415 phase-speed correction + EV-418 native/AttackCollision Hack Speed compatibility correction

## Purpose

Validate the reviewed production candidate in the real Gothic 3 runtime before documentation/release closure.

Collision and Speed remain CLOSED/PASS unless this fixture produces contradictory evidence.

Hero None+2H is the first fixture because matching authored Raise assets are already available for:

```text
Normal
QuickAttackR
QuickAttackL
full Whirl
```

## Gate 0 — initial sequencing-baseline build and deployment — HISTORICAL PASS

User-local release build succeeded.

Verified deployment identity:

```text
Built DLL SHA256 = 921B840471450CFE9BE4970C8268228FE06F443958DB3899D4897985F952F705
Live  DLL SHA256 = 921B840471450CFE9BE4970C8268228FE06F443958DB3899D4897985F952F705

Source INI SHA256 = AE328120EE34EA4F016D7BBAA9A511EE518F14CCBA71EB84040AF5A644ECB6F2
Live   INI SHA256 = AE328120EE34EA4F016D7BBAA9A511EE518F14CCBA71EB84040AF5A644ECB6F2

live selected project product:
Script_G3AnimationBehaviors.dll
length = 463360 bytes
```

POP-03 selected-product/hash gate: **PASS**.

This checkpoint proves exact deployment of the earlier `bc46dcf...` sequencing baseline only. It does **not** deploy the current `41ed80c...` candidate.

Historical procedure text for this completed gate follows:

Use the normal User-local workflow:

```text
sync development
-> build release Script_G3AnimationBehaviors target
-> deploy exact built DLL
-> verify built/live SHA256 match
-> verify only the intended release/third-party DLL set is present
```

Do not build a diagnostic prototype as a substitute for the release product.

If build fails, stop at the build error. Do not begin runtime testing.

## Gate 0B — current correction build and deployment — PASS (EV-420)

Current source candidate:

`41ed80c6420e5236d13fc037cb5923b946cb8ccc`

This candidate includes the accepted AddRaise phase-speed correction plus the EV-418 Hack compatibility transport and EV-417 arithmetic fail-closed guard.

Before any new runtime acceptance:

```text
sync development
-> build Release Script_G3AnimationBehaviors
-> deploy exact built Script_G3AnimationBehaviors.dll under POP-03
-> verify built/live SHA256 match
-> verify the intended project DLL set
-> only then launch Gothic 3
```

Verified current deployment:

```text
Built SHA256 = 3E7BCDBE1EBFC92B6E5FCFD7507A1E6A36C9DB8849847C29AD15288C01C2928D
Live  SHA256 = 3E7BCDBE1EBFC92B6E5FCFD7507A1E6A36C9DB8849847C29AD15288C01C2928D
selected project product = Script_G3AnimationBehaviors.dll
length = 462336 bytes
```

The prior DLL/hash in Gate 0 is historical and must not be reused as proof for this candidate. Source commit `aab0189...` is also superseded as the build target by `41ed80c...`.

## Gate A — AddRaise Off control — PASS (EV-411)

The User exercised 1H, dual-wield, 2H and Staff routes with the shipping AddRaise values unchanged.

Observed:

```text
Normal = PASS
Quick  = PASS
Whirl  = PASS on applicable tested routes
added Raise while Off = NONE
visible regression/stuck/skipped attack = NONE
```

This closes the disabled-state fail-closed control and exceeds the minimum Hero None+2H fixture.

Historical fixture text follows:

Start with the shipping INI unchanged:

```ini
Normal_AddRaise=Off
Quick_AddRaise=Off
Whirl_AddRaise=Off
```

With Hero None+2H, verify ordinary:

```text
Normal
Quick
full Whirl
```

still behave as before with no added Raise.

This is the fail-closed control.

## Gate B — native stack / AddRaise On — PASS (EV-412)

The User tested Hero None+2H Normal, factual Quick R/L and full Whirl with AddRaise On and the intended compatibility stack absent.

Observed sequence and continuation behavior: PASS.

Interruption/hit/out-of-combat controls did not produce a persistent Raise skip or continuation leak.

Historical fixture text follows:

Physically remove New Balance / AttackCollision DLLs required to be absent by the fixture; renaming them in the scripts folder is not sufficient.

For `[Profile.Hero_None_2H]`, locally set:

```ini
Normal_AddRaise=On
Quick_AddRaise=On
Whirl_AddRaise=On
```

Do not commit this test configuration.

Test separately:

```text
B1 Normal
B2 QuickAttackR
B3 QuickAttackL
B4 full Whirl
```

Acceptance for each:

- exactly one authored Raise occurs before Hit;
- Raise completes before Hit begins;
- no repeated Raise loop;
- no skipped Hit;
- no stuck/suspended attack;
- Quick uses Gothic's factual R/L choice — no wrong-side substitution;
- normal target/damage/collision behavior remains plausible in play.

For Quick, perform enough attacks to observe both R and L factual variants. G3AB must follow the variant Gothic chose; do not force alternation for the test.

If any item fails, stop the sequence and report the exact attack/observation before broad testing.

## Gate C — intended New Balance stack — PASS (EV-412)

The same Hero None+2H AddRaise-On routes were repeated with the intended New Balance stack restored.

Normal, factual Quick R/L and Whirl all passed the intended-stack acceptance.

One Whirl skip class was isolated to the already-known Alternative AI destructive block-skip behavior: with that option enabled Whirl could occasionally lose the in-progress Raise continuation; disabling the block-skip behavior removed the symptom in repeated retesting. This remains owned by future `AttackContinuationProtection`, not Raise.

Historical fixture text follows:

Restore the intended compatibility DLL set, including the project's normal New Balance / AttackCollision components.

Keep the same Hero None+2H AddRaise-On test configuration.

Repeat:

```text
C1 Normal
C2 Quick R/L
C3 full Whirl
```

Acceptance is the same as Gate B, plus no New Balance-specific hang, skipped attack, duplicated Raise, wrong Quick side, or obvious timing/continuation regression.

## Gate D — Raise timing coupling question — CONTRADICTION / ESCALATED (EV-413–EV-414)

The factual observation is closed, but the feature requirement is **not accepted**.

Observed:

```text
Normal custom AddRaise -> Raise does not follow BaseSpeed
Quick custom AddRaise  -> Raise does not follow BaseSpeed
Whirl custom AddRaise  -> Raise does not follow BaseSpeed
Power native Raise     -> Raise does not follow BaseSpeed
Hack native Raise      -> Raise follows BaseSpeed
Pierce native Raise    -> Raise follows BaseSpeed
```

Extreme `BaseSpeed=0.1` controls made the split clear. Hit/visible Recover followed authored speed while the non-coupled Raise phases retained their prior timing.

The approximately 0–10-frame custom Raise assets were intentionally made **longer** than the earlier approximately 0–3-frame Raise assets to make timing differences easier to observe.

EV-413 remains the factual first non-coupling observation. EV-414 supersedes only its earlier product-closure interpretation.

ADR-0004 and ADR-0008 require a coherent one-`BaseSpeed` authoring model. Therefore this result is an integration contradiction that must be corrected, not a reason to accept native Raise timing.

Static causal research is CLOSED/PASS at EV-415 and archived under `docs/archive/investigations/RAISE_SPEED_PHASE_CONSISTENCY_RESEARCH.md`.

Active correction owner:

`docs/work/active/RAISE_SPEED_PHASE_CONSISTENCY_IMPLEMENTATION.md`

Frozen correction:

```text
custom Normal / factual Quick R/L / Whirl AddRaise
-> inserted Raise copies the exact already-composed incoming Hit AniSpeedScale

native Power Raise
-> preserve the live Gothic/New Balance Raise result
-> apply the configured Power authoring ratio on top
```

For the established ordinary Hero Power example:

```text
native/live Raise = 1.5 * M
Power ratio       = Power_BaseSpeed / Power_ReferenceHitBaseSpeed
configured Raise  = (1.5 * M) * Power ratio
```

The `1.5` relationship is therefore preserved rather than replaced by Hit speed. The same rule preserves any other factual live Power Raise result (for example an Orc-specific compatible value) and its contextual modifier chain.

Do not add `RaiseSpeed`, flatten native Power Raise to Hit, or double-scale Hack/Pierce.

Historical Gate-D question:

> Does the inserted Raise naturally follow the configured attack BaseSpeed, or does only Hit change?

Answer: **not consistently; EV-415 established the correction and EV-416 accepts its production source.**

### Gate D correction source — PASS (EV-416; integrated current source PASS EV-419)

Raise correction originally implemented at `aab0189f...`; current integrated candidate:

`41ed80c6420e5236d13fc037cb5923b946cb8ccc`

Static result:

```text
custom Normal / factual Quick R/L / Whirl Raise
-> exact incoming composed Hit AniSpeedScale

native Power Raise
-> compatible live Raise result
   * (Power_BaseSpeed / Power_ReferenceHitBaseSpeed)

Hack / Pierce
-> no additional Raise-specific scaling
```

Power explicitly preserves the native/live phase relationship. For the established ordinary Hero route:

```text
compatible Raise = 1.5 * M
compatible Hit   = 1.0 * M
R                = configured Power BaseSpeed / native Power Hit reference

configured Raise = (1.5 * M) * R
configured Hit   = (1.0 * M) * R
```

### Gate D runtime correction acceptance — PASS NATIVE + INTENDED STACK (EV-420–EV-421)

EV-420 native-only runtime result:

```text
2H Normal = PASS at BaseSpeed 0.1 and 1.0
2H Quick  = PASS at BaseSpeed 0.1 and 1.0
2H Whirl  = PASS at BaseSpeed 0.1 and 1.0
2H Power  = phase-speed coupling PASS at 0.1 and 1.0
1H Power  = phase-speed coupling PASS at 0.1 and 1.0
1H Pierce = positive whole-attack control PASS at 0.1 and 1.0
```

The User observed Raise following the authored speed together with Hit in every tested case. This closes the native coupling contradiction exposed by EV-413/EV-414 for the tested routes.

Power caveat: this visual batch proves Raise responds to the authored Power speed; it does not independently quantify the established native/live Raise-vs-Hit relative ratio. Static architecture continues to preserve that ratio by composing the live Raise value rather than replacing it with Hit speed.

EV-421 clarifies that the User already repeated the same 0.1-versus-1.0 matrix with New Balance + AttackCollision enabled and observed the same positive result. The tested Raise phase-speed correction therefore passes both native and intended-stack fixtures.


## Gate D2 — native + AttackCollision Hack compatibility — PASS (EV-420–EV-421)

EV-417 found that pinned AttackCollision replaces `_AI_HackAttack` and bypassed the former three native Hack caller hooks. EV-418 froze, and EV-419 source-accepted, the route-neutral Action14 CombatMove adapter.

Use an established Hero None+2H Hack profile with native `ReferenceHitBaseSpeed=1.0`. A strong visible control is:

```ini
Hack_BaseSpeed=0.40
```

Do not commit the test value.

Run both exact routes:

1. **Native route — PASS EV-420:** with compatibility DLLs absent, 2H Hack was tested at authored speeds 0.1 and 1.0; Raise followed authored speed together with Hit. No ignored authoring or obvious double-slowdown was reported.
2. **Intended compatibility route — PASS EV-421:** the User ran the same 2H Hack 0.1-versus-1.0 control with New Balance + AttackCollision enabled and reported the same positive result as native. AttackCollision no longer bypasses configured Hack speed on the tested fixture, and no obvious double-slowdown was reported.
3. Under the intended stack, exercise one already-understood New Balance slowdown/context condition and verify its relative effect still survives the configured Hack authoring.
4. Verify factual Finishing remains native-timed, including a shared Hack/Finishing asset fixture if convenient.
5. Include one interrupted Hack followed by another attack and one AddRaise-enabled Normal/Quick/Whirl -> Hack transition. No stale continuation or repeated scaling may appear.
6. If the New Balance direct/static-block Hack Recover path is readily reproducible, verify its compatible Recover scale is authored once rather than ignored or squared.

Expected algebra:

```text
incoming live compatible Hack scale = B*M
configured request scale            = B*M * (C/B) = C*M
```

Failure indicators:

```text
configured Hack ignored under AttackCollision
~0.16-style double scaling for C=0.40
Finishing slowed by Hack profile
New Balance relative slowdown disappears
Raise/Hit/Recover disagree unexpectedly
stuck/repeated continuation
Collision contradiction
```

No diagnostic probe is required if the visible timing result is clear.

## Gate E — later cross-profile generalization

Deferred until the Hero None+2H gates above pass.

A later fixture may use matching authored 1H Raise assets to verify the generic profile architecture requires no new C++ branch.

Do not create those assets or broaden the runtime matrix merely to complete this first acceptance.

## Evidence / reporting

For each gate, User visual/gameplay observation is valid primary evidence for sequence correctness.

If behavior looks correct, report the concise per-attack result; a large diagnostic log is not required merely to prove visible Raise sequencing.

If there is a failure involving collision, continuation, wrong Quick side, or an unclear engine transition, preserve the smallest useful log/evidence before changing the candidate.

Normal Chat owns evidence/document maintenance after each completed uploaded/result batch.

## Stop conditions

Stop before advancing if any of these occur:

```text
build/deploy hash mismatch
DLL load-set uncertainty
crash
Raise repeats
Hit is skipped
attack remains stuck
Quick wrong-side Raise
state leaks into a later attack
collision/damage behavior contradicts the closed subsystem
New Balance-only regression
```

Do not redesign from the symptom. Preserve the exact fixture first.

## Protected

Do not:

- reopen Speed or Collision absent contradictory evidence;
- add Action3 Quick direction logic;
- add a new hook;
- add RaiseSpeed yet;
- broaden public AddRaise beyond Normal/Quick/Whirl;
- promote to `main` before runtime acceptance and maintenance closure.


## Next-session closure batch

**Session stop:** 2026-10-04 after EV-421. No unrecorded runtime evidence remains from the completed batch.

Current production DLL/source is unchanged. If the next session begins from this same source state, a rebuild is not required merely because documentation advanced; first synchronize `development`, verify the live production DLL remains the EV-420 hash, and keep the intended New Balance + AttackCollision fixture when running the remaining checks.

Only these small sanity controls remain before final acceptance closure:

1. **Configured Hack + New Balance contextual modifier:** with the intended stack active and a normal configured Hack base, compare an understood full/available-stamina case with the corresponding depleted-stamina/context case. The relative New Balance slowdown must remain visible.
2. **Factual Finishing isolation:** use an obvious slow Hack control (for example `Hack_BaseSpeed=0.1`) and verify factual Action15 Finishing remains native-timed even if it shares an animation asset with Hack.
3. **Interruption/transition sanity:** interrupt or leave a Hack, then perform another attack; if convenient also perform one AddRaise-enabled Normal/Quick/Whirl followed by Hack. No stale Raise, speed carry-over, stuck continuation, repeated phase, or collision contradiction may appear.

These are sanity/closure checks, not a new design phase. No new diagnostic log or Work task is required unless a contradiction appears.


## Final closure — EV-422

Final sanity controls completed:

```text
ordinary zero-stamina Hack:
  little/no visible slowdown
  same result with G3AB removed
  same conclusion with and without New Balance
  -> not a G3AB modifier-loss defect

New Balance alternative stamina mechanics:
  zero stamina blocks attacks
  Hack with G3AB installed obeyed the same restriction as other attacks
  -> compatible gameplay policy preserved

Hack/Finishing isolation:
  unique Hack asset: Hack 0.1 slow / Finishing native-fast
  shared Finishing asset: Hack 0.1 slow / Finishing native-fast
  -> factual Action14/Action15 isolation PASS independent of asset sharing

interruption stress:
  repeated Hack and other-attack interruptions
  no stuck attack / stale Raise / speed carry-over / continuation leak
```

Final disposition:

**PASS — first public AddRaise, phase-speed consistency, Speed compatibility, route-neutral AttackCollision Hack correction, Finishing exclusion and focused interruption behavior are accepted on the tested production source.**

No additional Raise/Speed implementation is authorized absent contradictory evidence.

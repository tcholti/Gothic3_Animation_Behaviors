# Raise — AddRaise Runtime Acceptance

**Status:** ACTIVE — USER-LOCAL BUILD / DEPLOY / FOCUSED RUNTIME ACCEPTANCE  
**Branch:** `development`  
**Accepted source candidate:** `bc46dcf7d22305c4d9d4f99fc5f5a1075ef726bd`  
**Scope:** first public AddRaise behavior only — Normal / Quick / Whirl

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

## Gate 0 — build and deployment

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

## Gate A — AddRaise Off control

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

## Gate B — native stack / AddRaise On

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

## Gate C — intended New Balance stack

Restore the intended compatibility DLL set, including the project's normal New Balance / AttackCollision components.

Keep the same Hero None+2H AddRaise-On test configuration.

Repeat:

```text
C1 Normal
C2 Quick R/L
C3 full Whirl
```

Acceptance is the same as Gate B, plus no New Balance-specific hang, skipped attack, duplicated Raise, wrong Quick side, or obvious timing/continuation regression.

## Gate D — Raise timing coupling question

Only after B and C pass.

Change one attack BaseSpeed at a time enough to create an obvious contrast while leaving its AddRaise On. Observe Raise and Hit separately.

Question:

> Does the inserted Raise naturally follow the configured attack BaseSpeed, or does only Hit change?

Do not implement or request a `RaiseSpeed` key during this test. Record the factual result first.

Return BaseSpeed to the accepted shipping value after each contrast.

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

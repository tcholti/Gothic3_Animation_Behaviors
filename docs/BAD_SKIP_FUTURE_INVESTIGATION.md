# Bad-Skip Future Investigation Direction

**Status:** Future modular investigation only. C1-R1 validation is closed; do not begin this responsibility until the marker/source system has been reviewed, modularized, expanded and regressed as planned in `DESIGN.md` / `BETWEEN_CHATS.md`.

## Why this exists

The held-Use2 destructive bad-skip route can terminate a real attack execution in the middle of its animation. The consequence depends on timing relative to collision activation:

```text
bad skip before collision activation
→ native attack ownership is destroyed before offense exists
→ later markers from the abandoned motion are rejected
→ that one attack can miss

bad skip after collision activation
→ native attack ownership is destroyed while the exact source is offensive
→ ordinary cleanup can be lost
→ C1-R1 fails closed by repairing the exact outstanding source 7 -> 5
→ any remaining visual portion of the abandoned attack may no longer deal weapon damage
```

C1-R1 intentionally addresses only the lost-cleanup consequence. It is a separately validated safety guard and must remain intact beneath any future prevention layer.

## Module boundary

The future prevention behavior must **not** be implemented inside `CollisionLifecycleGuard`.

Working module name:

```text
AttackContinuationProtection
```

Its responsibility is different:

```text
CollisionLifecycleGuard
= after ownership/cleanup fails, make an exact stale offensive source safe

AttackContinuationProtection
= prevent the known held-Use2 destructive consequence from killing a legitimate active attack in the first place
```

Both modules may consume facts from the shared engine bridge, but they must remain independently understandable and testable. The continuation module must not become a second collision-repair owner.

## Preferred future root-fix hypothesis

Do **not** begin by trying to resurrect or reconstruct an attack after the destructive skip has already killed it.

First investigate whether the cleaner root fix is to prevent the held-Use2 timeout's destructive consequence from firing while a real attack CombatMove execution is active.

Conceptually:

```text
held-Use2 timer continues to count normally

when the timeout consumer becomes due:
    if it would destructively FullStop / replace state
    while a real attack CombatMove execution is active
        suppress or defer only that destructive timeout consequence
    else
        preserve native timeout behavior
```

The important distinction is **not necessarily to disable or reset the timer itself**. Resetting/freezing the timer could alter post-attack input semantics. Prefer preserving the timer and changing only the inappropriate destructive action if source/API evidence supports that model.

## Preferred ownership signal

Avoid a new family-specific matrix such as Normal/Quick/Whirl/Power/Pierce unless engine evidence proves it necessary.

Prefer a native execution fact if available:

> Is there currently a real active attack CombatMove execution that this timeout action would destroy?

If yes, that execution should be the first candidate boundary for suppressing/defering the timeout consequence.

The module may reuse authoritative execution facts exposed by the shared engine bridge/lifecycle architecture, but it must not mutate or redefine the C1 cleanup obligation model merely to obtain that signal.

## Prerequisites before implementation

Do not begin this investigation until:

```text
- Script_FrameCollisionTest has received the agreed read-only architecture review;
- the research DLL has been modularized without semantic change and revalidated;
- marker bookkeeping has been audited against C1 execution authority;
- equipped-melee marker coverage has been expanded to the intended supported domain;
- the Fist adapter question has been separately decided from evidence;
- the resulting marker + lifecycle-guard system has passed regression.
```

This order matters because the bad-skip prevention layer should be tested against the marker/source architecture we actually intend to keep, not against an intermediate marker prototype that will immediately change underneath it.

## Required investigation before implementation

Do not assume the timeout is universally invalid during attacks. First prove:

1. the exact held-Use2 timeout decision/call path that leads to the destructive AIFullStop/state replacement;
2. whether that timeout has any legitimate responsibility while an attack CombatMove is active;
3. whether suppressing/defering only that destructive decision lets the attack complete through its ordinary lifecycle;
4. whether the same timeout still behaves natively outside attacks;
5. whether legitimate reaction/interruption FullStop and AISetState behavior remains untouched;
6. whether the prevention layer can consume shared bridge/execution facts without coupling itself to collision repair internals.

If source/API/calling-convention evidence contradicts this model, stop and redesign from evidence rather than forcing this hypothesis.

## Smallest future falsification test

If the source audit supports the hypothesis, the first runtime test should be narrow:

```text
marked full Whirl or another attack with observable collision windows
→ hold Use2 so the known timeout threshold crosses while attack CombatMove is active
→ destructive bad skip must NOT occur
→ attack must continue through its normal marker/native lifecycle
→ collision ON/OFF/ON sequence must remain normal
→ normal native cleanup must occur
→ C1-R1 should remain available underneath but should not need to repair this prevented case

control outside attack:
→ same held-Use2 timeout still performs its native behavior

reaction control:
→ legitimate attack interruption/reaction cleanup and FullStop behavior still works
```

Do not broaden implementation until those controls pass.

## Compatibility boundary

After this module and the mature marker/guard system pass their own regression, test the research DLL against New Balance and the relevant Jackydima DLL stack before migrating the collision system into `Script_G3AnimationBehaviors`.

Compatibility is a required gate, not an optional release polish step.

## Relationship to C1-R1

Even if this future prevention layer succeeds, **keep C1-R1**.

```text
AttackContinuationProtection
= prevent this known bad-skip route from destroying a legitimate attack

C1-R1
= general fail-safe if an exact offensive source nevertheless loses its cleanup opportunity
```

A prevention layer should reduce how often C1-R1 needs to act; it must not replace or weaken the validated guard.

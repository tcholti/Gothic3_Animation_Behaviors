# Bad-Skip Future Investigation Direction

**Status:** Future investigation only. Do not change current C1-R1 work to pursue this while C1-R1 validation is still open.

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
→ C1-R1 now fails closed by repairing the exact outstanding source 7 -> 5
→ any remaining visual portion of the abandoned attack may no longer deal weapon damage
```

C1-R1 intentionally addresses only the lost-cleanup consequence. It must remain a separate validated safety guard.

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

## Required investigation before implementation

Do not assume the timeout is universally invalid during attacks. First prove:

1. the exact held-Use2 timeout decision/call path that leads to the destructive AIFullStop/state replacement;
2. whether that timeout has any legitimate responsibility while an attack CombatMove is active;
3. whether suppressing/defering only that destructive decision lets the attack complete through its ordinary lifecycle;
4. whether the same timeout still behaves natively outside attacks;
5. whether legitimate reaction/interruption FullStop and AISetState behavior remains untouched.

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

control outside attack:
→ same held-Use2 timeout still performs its native behavior

reaction control:
→ legitimate attack interruption/reaction cleanup and FullStop behavior still works
```

Do not broaden implementation until those controls pass.

## Relationship to C1-R1

Even if this future root fix succeeds, **keep C1-R1**.

```text
future root fix
= prevent this known bad-skip route from destroying a legitimate attack

C1-R1
= general fail-safe if an exact offensive source nevertheless loses its cleanup opportunity
```

A root fix should reduce how often C1-R1 needs to act; it should not replace or weaken the validated guard.

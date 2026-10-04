# ADR-0006 — General Development Branch and Sequential Speed → Raise Development

**Status:** Accepted  
**Date:** 2026-09-27  
**Related:** ADR-0004, ADR-0005, `docs/DESIGN.md`, `docs/PROJECT_PIPELINE.md`

**Current qualification — partial supersession:** The development-branch model and Speed-before-Raise sequencing remain valid. Speed is now CLOSED/PASS through EV-410 and Raise is the active feature. Historical Normal/Quick/profile-scope wording is qualified by the grouped/expanded schema in [ADR-0008](ADR-0008-grouped-loadout-profiles-expanded-attack-scope.md), resolved profile identity in [ADR-0011](ADR-0011-resolved-animation-set-speed-profile-identity.md), and the current Raise owner under `docs/work/active/`.

The historical decision body below is preserved.

## Context

The collision subsystem benefited from sustained single-focus development: one mechanism was researched, implemented, tested, corrected and closed before unrelated feature work resumed. That reduced cross-feature confusion and made evidence/causality easier to preserve.

The previous branch model was collision-specific (`docs/collision-source-evidence`) and assumed collision would be promoted to `main` before a separate Raise/speed feature branch was created. The project has now reached a broader integrated-product phase: the mature collision core has been migrated into `src/Script_G3AnimationBehaviors`, and the same production DLL will later gain Speed, Raise, targeting, climbing and other deliberately adopted behavior modules.

The User also explicitly prefers finishing one feature responsibility before opening the next rather than alternating between unresolved Speed and Raise problems.

## Decision

### 1. Branch model

`main` is the last deliberately promoted **stable integration branch**. It is not advanced merely because active development has progressed.

The general active branch is:

```text
development
```

It owns current integration/research/implementation across animation-behavior subsystems. Its name is intentionally subsystem-neutral so later work such as targeting or climbing does not require another branch rename merely because the active feature changes.

The historical branch:

```text
docs/collision-source-evidence
```

remains historical/legacy unless deliberately removed later. Ordinary new project work does not continue there.

Promotion is deliberate:

```text
development
-> complete/validate the intended integrated feature checkpoint
-> promote to main
```

During the current cycle, `main` remains frozen until the collision production integration, Speed, Raise, and their assembled regression reach the agreed stable checkpoint.

### 2. Finish the current collision integration first

The source migration of the EV-389 collision core into `Script_G3AnimationBehaviors` is complete and independently source-reviewed. Before starting Speed implementation/research that changes the production DLL, perform the bounded local production-integration check for the newly named/located production DLL.

This is closure of the existing migration responsibility, not a new feature campaign and not a rerun of the full collision diagnostic history.

### 3. One shared configuration architecture from the start

Speed and Raise share the generic profile identity frozen by ADR-0005:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile
```

with user-facing action profiles:

```text
Normal
Quick
```

The exact `G3AnimationBehaviors.ini` schema is designed once as a generic profile/configuration surface capable of carrying both Speed and Raise settings.

Configuration is loaded once at startup into normalized in-memory profile rules. Runtime behavior performs only bounded in-memory lookup.

The shared schema may be implemented while Speed is the active feature because Speed requires configuration. However, **Raise behavior must not be implemented early merely because its future field/schema is already represented.** A field may exist or be reserved in the shared profile model while its consumer remains inactive until the Raise phase begins.

Exact INI syntax is not frozen by this ADR. It must be chosen after inspecting the actual Gothic config API capabilities and must preserve the generic profile identity rather than encode a growing set of weapon-specific C++ branches.

### 4. Feature order is deliberately sequential

After collision production integration closes:

```text
A. freeze/implement the shared profile/config foundation needed by Speed and future Raise
B. Speed v2 research/design/implementation/validation ONLY
C. close Speed completely
D. Raise research/design/implementation/validation ONLY
E. close Raise completely
F. run assembled collision + Speed + Raise regression/compatibility validation
G. deliberately promote development -> main
```

Do not alternate between unresolved Speed and Raise questions merely because both use the same INI/profile data.

If Speed research proves that the generic profile/config representation itself must change, make that generic correction while Speed is current and stabilize it before Speed closes. Raise later consumes that stabilized shared configuration architecture rather than reopening Speed design by default.

### 5. Speed remains the first feature responsibility

Speed v2 remains governed by ADR-0004 and ADR-0005:

```text
configured value = base-speed authority
not final effective-speed authority
```

The exact compatible intervention mechanism must be researched before implementation is frozen. Applicable native/New Balance contextual multipliers must remain composable. No final-speed replacement, copied New Balance multiplier table, or same-hook load-order dependency is accepted merely to make progress.

### 6. Raise remains paused until Speed closes

Raise retains the architecture already frozen by ADR-0005:

```text
configured Normal/Quick profile
-> request Raise through Gothic CombatMove semantics
-> Gothic resolves the actual animation through its own naming/request rules
-> continue the untouched attack path
```

But no Raise implementation or new Raise causal work begins while Speed is still open, except maintaining the shared schema so it remains structurally capable of representing Raise later.

## Consequences

- Future Chats must not revert to `docs/collision-source-evidence` as the active branch or invent a subsystem-named feature branch for the current cycle.
- Future Chats must not advance `main` after ordinary development commits; `main` is a stable checkpoint until deliberate promotion.
- Future Chats must not interpret the shared INI as permission to develop Speed and Raise concurrently.
- Speed is the sole active feature after collision integration closure; Raise follows only after Speed is closed.
- The exact INI syntax remains an explicit near-term design question rather than being silently inherited from the old 2H-only prototype.
- Later targeting/climbing/etc. may continue on `development` under the same deliberate stable-promotion model unless a future branch strategy decision supersedes this ADR.

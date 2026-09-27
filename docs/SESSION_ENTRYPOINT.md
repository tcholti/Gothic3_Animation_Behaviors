# Session Entry Point

**Purpose:** Minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `development`  
**Stable integration branch:** `main`  
**Updated:** 2026-09-27

> **INTERRUPTED-CHAT ENTRY RULE:** after an abrupt/max-context/unusable Chat, return to root `README.md` and enter Recovery Lock. This file is then a clue, not unquestioned truth, until POP-11 reconciliation.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
latest closed collision evidence = EV-389
current evidence ledger = EVIDENCE_LEDGER_389_ONWARD.md

collision diagnostic phase = CLOSED/PASS EV-386–EV-388
behavior-only release-purity collision gate = CLOSED/PASS EV-389
production collision source migration implementation = 9da92dc559d8897a675d575f8d88b3631470ed7d
independent production-migration source review = PASS
production migration task = CLOSED / archived

CURRENT = bounded local production-integration validation of Script_G3AnimationBehaviors.dll
NEXT AFTER PASS = shared INI/profile foundation + Speed v2 only
RAISE = PAUSED until Speed is completely closed
```

## Branch model

ADR-0006 owns the current deliberate branch/sequencing decision:

```text
main
= last deliberately promoted stable integration checkpoint
= DO NOT advance during ordinary current feature development

development
= sole active general development/research/integration branch
= collision integration -> Speed -> Raise -> assembled regression

docs/collision-source-evidence
= historical collision branch; no ordinary new work
```

Current cycle promotion rule:

```text
development
-> close collision production integration
-> shared generic INI/profile schema
-> finish Speed v2 completely
-> finish Raise completely
-> assembled collision + Speed + Raise regression
-> deliberate promotion to main
```

Later targeting/climbing/other adopted behavior may continue on the general `development` branch unless a future deliberate branch decision supersedes ADR-0006.

## Product architecture decisions frozen

```text
final release DLL = Script_G3AnimationBehaviors.dll
validated collision core = production architectural foundation
EngineBridge = sole physical hook owner inside the DLL
release build = behavior only; diagnostics remain separate

Raise/speed profile identity:
  AnimationFamily
  + LeftAnimationUseType
  + RightAnimationUseType
  + ActionProfile

user-facing Raise/speed ActionProfile scope = Normal + Quick
INI parsed once at startup into normalized in-memory rules
runtime = bounded in-memory profile lookup
unconfigured profile = native behavior
no weapon-specific C++ policy branches merely for configuration selection
```

### Speed — first feature after collision integration

```text
unconfigured effective speed = B(profile, action, phase) * M(context)
configured effective speed   = C(profile, action, phase) * M(context)
```

`C` is the configured base-speed authority; applicable Gothic/New Balance contextual modifiers `M` must remain effective. The exact Speed v2 intervention point/mechanism remains a focused research question under ADR-0004. Final-speed replacement, copying New Balance's multiplier table, or same-hook load-order dependency are not accepted architecture.

### Raise — deliberately later

Raise remains governed by ADR-0005 but is not active work yet:

```text
matching configured Normal/Quick profile
-> request Raise through Gothic CombatMove semantics
-> Gothic resolves the actual animation from its normal naming/request facts
-> continue the untouched attack path
```

The shared INI/profile schema is designed to support both Speed and future Raise from the start, but Raise behavior/research does not begin until Speed is closed.

## Immediate route

```text
1. User syncs/checks out development
2. build Script_G3AnimationBehaviors.dll locally
3. deploy it as the sole G3AB production collision DLL
4. startup smoke
5. focused collision production-integration sanity:
   - one marker-dependent equipped positive control (Hack or ON/OFF/ON)
   - raw8 double-FIST contact control
   - raw55 double-FIST contact control
   - observe no stuck/persistent collision
6. PASS -> record production integration closure
7. inspect Gothic config API and freeze one shared Speed+Raise INI/profile schema
8. begin Speed v2 only
```

This is a focused migration check, not a rerun of the closed EV-386–EV-389 campaigns. No diagnostic log is expected unless contradictory behavior appears.

## Read next by question

- exact continuation -> `BETWEEN_CHATS.md`
- branch + sequential Speed→Raise decision -> `decisions/ADR-0006-development-branch-and-sequential-speed-raise.md`
- Raise/speed profile architecture -> `DESIGN.md` §§2–3 + `decisions/ADR-0004-speed-control-base-speed-preserves-dynamic-modifiers.md` + `decisions/ADR-0005-raise-speed-config-profiles.md`
- third-party source -> `../references/README.md`
- collision facts -> `COLLISION_REFERENCE.md`
- release/diagnostic separation -> `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`
- archived production migration contract -> `archive/investigations/PRODUCTION_COLLISION_CORE_MIGRATION.md`

## Runtime-log retrieval rule

`PROJECT_OPERATING_PROCEDURES.md` POP-06 requires bounded retrieval for **all** runtime logs regardless of size: identity/metadata -> exact searches/counts -> bounded event windows -> representative route/whole-run-class checks -> conclusions + provenance. POP-07 is the large-log specialization.

## Still paused

```text
NO Speed implementation before collision production integration closes
NO Raise implementation/research while Speed is open
NO AttackContinuationProtection work
NO targeting/climbing work
NO promotion of development to main before the agreed integrated checkpoint
NO load-order compensation experiment absent contradictory evidence
```
# Session Entry Point

**Purpose:** Minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `docs/collision-source-evidence`  
**Stable branch:** `main`  
**Updated:** 2026-09-27

> **INTERRUPTED-CHAT ENTRY RULE:** after an abrupt/max-context/unusable Chat, return to root `README.md` and enter Recovery Lock. This file is then a clue, not unquestioned truth, until POP-11 reconciliation.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
standalone frozen collision baseline = f1f5d2aad3edc3564a9a8b40541840b94f8fa903
first raw55 SP2 correction = 6eb3e3ca96da55e89127c24d5f656e05610d315f
Sprint-first SP2 correction = ce59e5a2bad564652eaba970e959bdef0b479d82
Sprint-second SP2 correction = 4c85193f4efd31e789bc07d7e3c71d31a9b5326e
Normal-second SP0 correction = a31c66b97e45c27d0739b7df51252d33f490e7e1
standalone Sprint-second SP1 final candidate = 1c45e5ec3de1194e43b2f2200a28fe7846bd5ce0
latest runtime/observational evidence = EV-389
current ledger = EVIDENCE_LEDGER_389_ONWARD.md

standalone final-source regression = CLOSED/PASS EV-299–EV-374
Zombie+Axe asset-gap remedy = PASS EV-375
focused raw55 New Balance compatibility = CLOSED/PASS EV-376–EV-382
dual-1H four-marker / three-window authoring = PASS EV-383
New Balance full intended-stack compatibility = CLOSED/PASS EV-384
EV-385 standalone Sprint/SP1 defect = CLOSED by EV-386
corrected marked standalone raw55 matrix = PASS EV-386
unmarked raw55 native fallback = PASS EV-387
final-candidate New Balance/raw55 focused diagnostic regression = PASS EV-388
DIAGNOSTIC PHASE = CLOSED/PASS EV-386–EV-388
behavior-only deployment identity = PASS EV-389
behavior-only startup smoke = PASS EV-389
behavior-only functional release-purity validation = PASS EV-389

CURRENT = bounded source-only production collision-core migration
TASK = docs/work/active/PRODUCTION_COLLISION_CORE_MIGRATION.md
```

## Product architecture decisions now frozen

```text
final release DLL = Script_G3AnimationBehaviors.dll
validated collision behavior core = production architectural foundation
EngineBridge = sole physical hook owner inside the DLL
release build = behavior only; no collision diagnostic implementation
prototype/diagnostic twins remain separate reference/research products

Raise/speed profile architecture:
  startup-loaded normalized INI profiles
  AnimationFamily + LeftAnimationUseType + RightAnimationUseType + ActionProfile
  user-facing Raise/speed families = Normal + Quick
  no weapon-specific C++ policy branches merely for configuration selection
  Raise preserves Gothic animation resolution
  Speed v2 authors the base term while preserving applicable contextual modifiers
  exact Speed v2 intervention remains future focused research
```

Raise/speed rationale: ADR-0004 + ADR-0005. Current Jackydima/New Balance source is pinned under `references/jackydima-gothic3sdk`; routing is `references/README.md`.

## EV-389 behavior-only release-purity closure

The final diagnostics-free observational gate deliberately used behavior that native Gothic collision timing could not explain:

```text
Run 1:
  long-developed/released authored animations across weapon types
  collision timing observed at authored marker locations
  Hack attacks successfully produce authored offensive collision

Run 2:
  2H ON -> OFF -> ON produces separate offensive windows
  opponent entering weapon during authored OFF does not get hit
  1H1H/dual BOTH -> single-side -> OFF -> BOTH produces intended multi-window contacts
  extra authored swings beyond native attack structure collide with opponents
  human Fist double markers can hit twice
  Sabretooth raw8 double markers can hit twice
  Troll raw55 double markers can hit twice
  one-on-one and group combat show no observed stuck/persistent collision regression
```

User disposition: very confident the DLL works as intended.

Therefore:

```text
BEHAVIOR-ONLY RELEASE-PURITY COLLISION GATE = CLOSED/PASS EV-389
MATURE COLLISION SUBSYSTEM = APPROVED FOR PRODUCTION MIGRATION
```

## Exact next route

```text
1. execute only docs/work/active/PRODUCTION_COLLISION_CORE_MIGRATION.md
2. exact-copy the accepted collision behavior modules into src/Script_G3AnimationBehaviors
3. adapt only production entry point + CMake target as authorized
4. exclude old AttackRaise / AttackSpeed / SharedConfig from the production build but leave their files untouched
5. do not modify the prototype/diagnostic twins
6. Work/source-only session MUST NOT build or run Gothic 3
7. Normal Chat independently reviews the implementation diff against the frozen contract
8. User builds Script_G3AnimationBehaviors.dll locally at home
9. focused production integration validation
10. migration PASS -> archive task and advance to Raise/config before Speed v2 research
```

Do not rerun closed diagnostic or behavior-only campaigns absent contradictory evidence.

## Runtime-log retrieval rule

`PROJECT_OPERATING_PROCEDURES.md` POP-06 requires bounded retrieval for **all** runtime logs regardless of size: identity/metadata -> exact searches/counts -> bounded event windows -> representative route/whole-run-class checks -> conclusions + provenance. POP-07 is the large-log specialization.

## Read next by question

- exact implementation task -> `work/active/PRODUCTION_COLLISION_CORE_MIGRATION.md`
- exact continuation -> `BETWEEN_CHATS.md`
- overall architecture -> `DESIGN.md`
- release/diagnostic separation -> `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`
- current facts -> `COLLISION_REFERENCE.md`
- Raise/speed decisions -> `decisions/ADR-0004-speed-control-base-speed-preserves-dynamic-modifiers.md` + `decisions/ADR-0005-raise-speed-config-profiles.md`
- third-party source -> `../references/README.md`
- proof -> `EVIDENCE_INDEX.md` -> EV-385–EV-389

## Still paused

```text
NO collision behavior redesign during migration without contradictory evidence
NO Raise implementation in the collision migration task
NO Speed v1/v2 implementation in the collision migration task
NO AttackContinuationProtection work
NO load-order compensation experiment
```
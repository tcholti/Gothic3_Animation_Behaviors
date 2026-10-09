# Architecture Decision Records

**Purpose:** Preserve the rationale for significant project decisions without turning current architecture/reference documents into chronological history.

Decision records are short and immutable in spirit. A later decision does not rewrite an old accepted record; it creates a new record that supersedes or qualifies it.

Use an ADR only when a future contributor could reasonably ask **why** a significant architectural/project-structure choice was made. Routine implementation details, experiment chronology, evidence observations and temporary task contracts do not need ADRs.

Statuses:

```text
Proposed
Accepted
Superseded by ADR-xxxx
Rejected
```

Current architecture/reference documents state what applies now. ADRs preserve why a non-obvious choice was made.

## Find a decision

This index is a navigation/status aid. **Accepted with later qualifications** means the core rationale remains accepted while later decisions, completed implementation or current configuration qualify historical details; it does not rewrite the record's status/body. For current behavior use [DESIGN](../DESIGN.md), [COLLISION_REFERENCE](../COLLISION_REFERENCE.md) and [shipping settings](../../src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini). Historical sequencing and proposed schemas are not current work instructions.

| Decision / topic | Effective status | Current qualification / reading cue |
|---|---|---|
| [ADR-0001 — Current knowledge versus historical proof](ADR-0001-knowledge-lifecycle.md) | Accepted | Current-reference-first retrieval; promote reusable conclusions before archival. |
| [ADR-0002 — One transport owner for engine hooks](ADR-0002-engine-hooks-transport-only.md) | Accepted | Feature policy and removable probes remain in their own source modules. |
| [ADR-0003 — Permanent equipped Sprint behavior](ADR-0003-promote-equipped-sprint-as-permanent-behavior.md) | Accepted | Promotion and later production integration are complete; historical twin/migration sequencing is not pending work. |
| [ADR-0004 — Author base speed, preserve dynamic modifiers](ADR-0004-speed-control-base-speed-preserves-dynamic-modifiers.md) | Accepted with later qualifications | Composition invariant remains current; early research gates and nominal tuning examples are historical. DESIGN and the shipping INI govern the implemented mechanism/defaults. |
| [ADR-0005 — Startup-loaded generic Raise/Speed profiles](ADR-0005-raise-speed-config-profiles.md) | Accepted with later qualifications / partial historical supersession | Original Normal/Quick-era scope/schema is qualified by ADR-0008 grouped scope, ADR-0009 inheritance and ADR-0011 identity. |
| [ADR-0006 — Development branch and sequential feature work](ADR-0006-development-branch-and-sequential-speed-raise.md) | Accepted with later qualifications / partial historical supersession | Stable/working branch model remains; first-release sequencing is completed, with profile details qualified by ADR-0008/0011. |
| [ADR-0007 — Shared INI profile foundation](ADR-0007-shared-ini-profile-schema.md) | Accepted with later qualifications / partial historical supersession | ADR-0008 replaces per-action sections and ReferenceRaiseBaseSpeed; ADR-0009 owns inheritance; ADR-0011 owns resolved tokens. |
| [ADR-0008 — Grouped loadouts and expanded attack settings](ADR-0008-grouped-loadout-profiles-expanded-attack-scope.md) | Accepted with later qualifications / partial historical supersession | Public AddRaise keys replace dormant RaiseOverride; ADR-0009 replaces Sprint deferral; ADR-0011 supplies current profile identity. |
| [ADR-0009 — Sprint inherits Power speed settings](ADR-0009-sprint-inherits-power-speed-profile.md) | Accepted with later qualifications | Proven Power inheritance remains; it does not guarantee equal live speed in every context. Raise-paused sequencing is historical. |
| [ADR-0010 — Raw UseType profile identity](ADR-0010-raw-use-type-speed-profile-identity.md) | Superseded by [ADR-0011](ADR-0011-resolved-animation-set-speed-profile-identity.md) | Preserve as rationale history; raw equipped UseType is not the current profile selector. |
| [ADR-0011 — Resolved animation-set profile identity](ADR-0011-resolved-animation-set-speed-profile-identity.md) | Accepted | Request-time animation family/tokens select the shared profile; supersedes ADR-0010. |
| [ADR-0012 — Protect attacks from player bad-block teardown](ADR-0012-bad-block-skip-attack-protection-contract.md) | Accepted with later qualifications | First-release stateless player protection is integrated/closed under DESIGN §9; packaging candidates are historical. Exact timer pause and NPC timeout remain separate future questions. |

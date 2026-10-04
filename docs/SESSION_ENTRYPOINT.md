# Session Entry Point

**Purpose:** minimal durable current-state pointer. Repository startup begins at root `README.md` **Start Here**.  
**Active development branch:** `development`  
**Stable integration branch:** `main`  
**Updated:** 2026-10-04

> After abrupt/max-context recovery, return to root `README.md` and apply POP-11 before trusting this pointer.

<!-- KNOWLEDGE_LIFECYCLE_ROUTE: docs/KNOWLEDGE_MAINTENANCE.md -->

## Current gate

```text
collision production integration = CLOSED/PASS through EV-390
configured Speed + New Balance multiplier preservation = PASS EV-395
Speed v2 / ADR-0011 = CLOSED/PASS through EV-410; neutral shipping INI locked
Sprint Speed authoring = inherits Power profile on proven shared route (ADR-0009)
repository health/authority audit = CLOSED / NORMAL CHAT REVIEW PASS
reviewed maintenance = commit 4090298a409172dcee2bc5e6dc1d267b1e22f75e / knowledge-state CI PASS
Speed calibration probe = native control PASS EV-396; broad Hero/loadout calibration PASS EV-397; Finishing Action15 gate PASS EV-398
Hack/Finishing action-route Speed isolation = PASS EV-399 on shared + separated assets
extended 18-Hit calibration probe identity/startup = PASS EV-400 / SHA256 F63EB6D169778079D6E60B62DF7E00F586B1987E05F4557BC61AF3D45071C05B
representative Hero/Orc/Goblin NPC calibration = PASS EV-400
Goblin same-run Power/Sprint context control = PASS EV-401
representative nonhuman native Batch 1 = PASS EV-402
initial release calibration sufficiency = PASS EV-403–EV-404
late Boar/Batch2/tool calibration = PASS EV-404
raw UseType-only profile identity = SUPERSEDED EV-406 / ADR-0011
separation profile identity = PASS EV-406; resolved animation-set identity selected
human bare Fist Speed calibration = Normal B=1.0 / Power B=1.0; native Quick does not exist and is intentionally omitted
ADR-0011 implementation candidate = ba3e76549eff5c7fdfc2d165ec976e640ef9c24c / four-file boundary PASS
CURRENT = Raise AddRaise design locked; one Quick factual-action static precheck remains before bounded implementation
Raise behavior = ACTIVE — additive Normal_AddRaise / Quick_AddRaise / Whirl_AddRaise; shipping defaults Off
main = FROZEN
```

Completed Speed task is archived at:

```text
docs/archive/investigations/SPEED_EXPANDED_ATTACK_SCOPE_AND_GROUPED_PROFILE_IMPLEMENTATION.md
```

The completed ADR-0011 bounded source task is archived under `docs/archive/investigations/SPEED_RESOLVED_PROFILE_IMPLEMENTATION.md`. The completed native calibration probe task is archived under `docs/archive/investigations/SPEED_NATIVE_CALIBRATION_PROBE.md`; neither is a current blocking responsibility.

Canonical reusable engine lookup:

`docs/SOURCE_HOOK_GUIDE.md`

The completed preservation-biased repository audit and Work result are archived under `docs/archive/investigations/`. Its accepted RH-01–RH-13 maintenance is represented in the durable owners; RH-14–RH-17 were KEEP/no-action. The three previously retained Sprint-probe logs were positively reconciled during EV-397/EV-398 maintenance and archived byte-identically; path migration is recorded in `EVIDENCE_PATH_MIGRATIONS.md`.

## Immediate continuation — Raise

Use `docs/work/active/RAISE_ADDRAISE_IMPLEMENTATION_PRECHECK.md` as the owning current contract.

```text
Speed = CLOSED/PASS
Raise design = LOCKED
preferred transport = high-level PS_Melee_* PREPEND_BREAK_BLOCK state prepend
historical 2H Normal + New Balance coexistence = observed PASS
only pre-implementation question = factual Quick R/L availability at PS_Melee_QuickAttack entry
-> close that static question
-> freeze bounded generic Normal/Quick/Whirl AddRaise implementation
-> first runtime fixture = Hero None+2H (assets already ready)
```

EV-406 closes the separation identity probe. Shared resolved assets intentionally share Speed profiles; separated request-time animation tokens select independent profiles. Rapier proves raw UseType alone is insufficient, while Zombie+Axe proves family and animation-token dimensions compose.

Historical original 15-Hit-caller probe SHA256:

`4140867626119632929D2286A173E97B3A4ACE6EDBCA4E2DBFE30AC28FE28E82`

Pre-separation 18-Hit-caller probe SHA256 used through EV-404:

`F63EB6D169778079D6E60B62DF7E00F586B1987E05F4557BC61AF3D45071C05B`

Current resolved-request identity probe built/live SHA256 used by EV-406:

`76B65B57ACFB536E7B044751B3576B912ECE741F8C73480BFAA6680DDBEA7702`

The EV-406 probe retains the same 18 Hit callers + Power Raise observation caller and adds request-time identity diagnostics only.

EV-396 native controls establish, within their exact tested fixtures:

```text
Hero None+1H Normal Hit = 0.6
Hero None+1H Quick R/L Hit = 1.0
Hero Power Raise = 1.5
Hero Power Hit = 1.0
Troll PhysicalFist Normal/Quick/Power Hit = 1.0
Troll factual Sprint Raise/Hit through passed Power = 1.0
```

`ReferenceHitBaseSpeed` remains native Gothic `B`; compatible live modifiers remain in the live result and production composes:

```text
compatible = B * M
configured = compatible * (C / B) = C * M
```

## Runtime fixture rule

Each frozen runtime fixture owns its allowed third-party DLL set. POP-03 owns project-product exclusion/deployment verification.

Any DLL excluded from a fixture must be physically moved/removed completely outside Gothic 3's `scripts` folder before launch. Renaming a DLL in place is **not** a disable method.

## Still frozen

```text
NO +0x42A0 entry hook
NO rewrite of live compatible-owner EAX
NO New Balance result used as native ReferenceHitBaseSpeed
NO Sprint-specific Speed keys absent contradictory evidence
Raise implementation requires a frozen bounded task after the single Quick factual-action precheck
NO collision redesign absent contradictory evidence
NO attack-displacement/climbing implementation yet
NO promotion to main before agreed integrated checkpoint
```

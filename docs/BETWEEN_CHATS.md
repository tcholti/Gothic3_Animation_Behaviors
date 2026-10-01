# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-01

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active: `development`  
Stable: `main` — frozen.

## Current state

```text
collision production integration = CLOSED/PASS EV-390
configured Speed + New Balance multiplier preservation = PASS EV-395
expanded Speed production source = implemented / static-review PASS / local Release build PASS
Sprint Speed = inherits Power profile on proven shared route (ADR-0009)
repository health/authority audit = CLOSED / reviewed maintenance PASS at 4090298a409172dcee2bc5e6dc1d267b1e22f75e
Speed calibration = native control PASS EV-396; broad Hero/loadout checkpoint PASS EV-397; Finishing Action15 observation PASS EV-398
Hack/Finishing action-route Speed isolation = PASS EV-399 on shared + separated assets
extended 18-Hit probe identity/startup = PASS EV-400 / F63EB6D169778079D6E60B62DF7E00F586B1987E05F4557BC61AF3D45071C05B
representative Hero/Orc/Goblin NPC calibration = PASS EV-400
Goblin same-run ordinary-Power/Sprint context control = PASS EV-401
representative nonhuman native Batch 1 = PASS EV-402
initial release calibration sufficiency = PASS EV-403–EV-404
late calibration logs = PASS EV-404
raw UseType profile identity = ACCEPTED EV-405 / ADR-0010
CURRENT = implement ADR-0010 + full active raw-UseType Speed INI
Raise = paused until Speed closes
```

## Continue here

Read:

`docs/work/active/SPEED_NATIVE_CALIBRATION_PROBE.md`

Historical original 15-Hit-caller probe SHA256:

`4140867626119632929D2286A173E97B3A4ACE6EDBCA4E2DBFE30AC28FE28E82`

Current extended 18-Hit-caller probe built/live SHA256:

`F63EB6D169778079D6E60B62DF7E00F586B1987E05F4557BC61AF3D45071C05B`

EV-400 verified that current hash with one sole live project DLL and a clean 18-hook startup/unload gate. It does not retroactively identify the EV-398 binary.

Immediate sequence:

```text
use SPEED_EXPANDED_ATTACK_SCOPE_AND_GROUPED_PROFILE_IMPLEMENTATION.md
-> implement ADR-0010 raw UseType profile identity
-> populate full calibrated INI with separate 2H/Axe and Staff/Halberd sections
-> review/build/deploy
-> Axe Separation + intended-stack runtime acceptance
-> close Speed
-> Raise afterward
```

EV-404 closes Boar Power B and records Batch-2/tool-use observations. EV-405 corrects configuration identity: raw UseType, not serialized animation token, owns the Speed profile. Shared vanilla animations may use identical values; separation mods can tune the raw profile independently.

`ReferenceHitBaseSpeed` is native Gothic `B`, never a New Balance-modified live value.

Runtime fixture rule: excluded Gothic script DLLs must be physically moved/removed outside `scripts`; renaming in place does not reliably disable them. POP-03 owns project-product exclusion; each frozen fixture decides whether New Balance/AttackCollision/other third-party DLLs are present.

The completed repository audit task/result are archived under `docs/archive/investigations/`. The three formerly retained Sprint-probe logs are now positively reconciled and archived byte-identically; see `docs/EVIDENCE_PATH_MIGRATIONS.md`.

Do not begin Raise, attack displacement, climbing, collision redesign, or `main` promotion before the current gates close.

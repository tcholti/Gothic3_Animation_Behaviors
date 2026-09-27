# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-27

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `development`  
Stable branch: `main`

## Current state

```text
EV-389 behavior-only collision release-purity = CLOSED/PASS
production collision migration = PASS
EV-390 production Script_G3AnimationBehaviors.dll integration = CLOSED/PASS
CURRENT = freeze shared generic INI/profile foundation
NEXT = Speed v2 ONLY until completely closed
RAISE = PAUSED until Speed closes
```

EV-390 production proof:

```text
Script_G3AnimationBehaviors.dll
built/live SHA256 = 12FA5819FEEB5033B2D747A9B57CA1591E588EAAC0BAC9CC386307B77C367A55
sole live G3AB/collision product = PASS
2H double / three markers = works
1H1H triple / four markers = works
human Fist double / two markers = works
Sabretooth raw8 double / two markers = works
Troll raw55 double / two markers = works
```

These impossible-native controls confirm active migrated production marker behavior. Collision migration is closed; do not reopen historical collision campaigns absent contradictory evidence.

## Branch / sequencing decision

ADR-0006 owns:

```text
main        = last stable integration checkpoint; leave unchanged
development = active general development/research/integration branch
docs/collision-source-evidence = historical collision branch
```

Current cycle:

```text
shared INI/profile schema
-> Speed v2 completely
-> Raise completely
-> assembled collision + Speed + Raise safety regression
-> deliberate development -> main promotion
```

The assembled regression is only a final safety check that later modules did not break already-accepted collision/Speed behavior; it is not another Raise research phase.

## Frozen Raise / Speed architecture

Profile identity:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile
```

User-facing ActionProfile scope = `Normal` + `Quick` only.

```text
G3AnimationBehaviors.ini
-> parse once at startup
-> normalized in-memory profile rules
-> bounded runtime lookup
-> missing profile = native fallback
```

No P0/P1/P2/P3 user-facing split. No 1H/2H/Axe/Staff/etc. feature-policy branches merely to select config; UseType/profile identity comes from runtime facts/data so modded profiles can participate generically.

### Speed — next and exclusive feature

```text
unconfigured = B * M
configured   = C * M
```

`C` is the configured base term; applicable Gothic/New Balance contextual modifiers `M` must remain effective. Exact intervention mechanism remains research under ADR-0004. Do not use final-result replacement, copied New Balance multiplier tables, or arbitrary same-hook load-order dependency.

### Raise — paused

ADR-0005 design remains:

```text
configured Normal/Quick profile
-> request Raise through Gothic CombatMove
-> Gothic resolves the actual animation through normal naming/request rules
```

The shared INI schema supports future Raise from the start, but no Raise behavior/research begins until Speed closes.

## Exact next route

```text
1. inspect Gothic/eCConfigFile config API + old G3AB config only as reference
2. freeze exact generic INI syntax for shared Speed + future Raise profiles
3. implement shared parsing/normalization/profile lookup foundation
4. research/design/implement/test Speed v2 ONLY until completely closed
5. only then begin Raise
```

Authorities: `DESIGN.md`, ADR-0004, ADR-0005, ADR-0006, `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`, `references/README.md`.  
Current evidence ledger: `EVIDENCE_LEDGER_389_ONWARD.md`.

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
production collision migration implementation = 9da92dc559d8897a675d575f8d88b3631470ed7d
independent source review = PASS
migration Work contract = CLOSED / archived
CURRENT = local production-integration validation of Script_G3AnimationBehaviors.dll
```

The production target now contains the accepted collision core under the final DLL name. The 21 migrated behavior files match the accepted prototype Git blobs; only production CMake/bootstrap differ as authorized. Old `AttackRaise`, `AttackSpeed`, `SharedConfig`, and old INI files remain physically present but are excluded from the production target.

## Branch decision

ADR-0006 supersedes the previous collision-specific branch progression:

```text
main
= last stable integration checkpoint
= leave unchanged during current feature development

development
= active general branch for current and future animation-behavior work

docs/collision-source-evidence
= historical collision branch
```

Do not create or switch to `feature/raise-attack-speed` for this cycle. Do not promote intermediate Speed work to `main`.

## Frozen Raise / Speed architecture

Shared profile identity:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile
```

User-facing ActionProfile scope:

```text
Normal
Quick
```

Shared config rule:

```text
G3AnimationBehaviors.ini
-> parse once at startup
-> normalize into in-memory profile rules
-> bounded runtime lookup only
-> missing profile = native fallback
```

No P0/P1/P2/P3 user-facing split. No feature-policy C++ branches for 1H/2H/Axe/Staff/etc. merely to select config; UseType/profile identity comes from data/runtime facts so modded profiles can participate generically.

### Speed — next and exclusive feature

Speed v2 must author the configured **base** term while preserving applicable contextual modifiers:

```text
unconfigured = B * M
configured   = C * M
```

Current New Balance source is pinned at `references/jackydima-gothic3sdk` and shows why final-result replacement is wrong: its speed function combines base terms with stamina/arena/disease/etc. logic. Exact intervention mechanism is still research under ADR-0004.

### Raise — paused until Speed closes

Raise keeps the ADR-0005 design:

```text
configured Normal/Quick profile
-> request Raise through Gothic CombatMove
-> Gothic resolves actual animation through normal naming/request rules
```

The shared INI schema should support a future Raise setting from the beginning, but no Raise behavior/research begins while Speed remains open.

## Exact next route

```text
1. User builds/deploys development production target locally
2. startup smoke
3. focused collision integration sanity:
   marker-dependent equipped attack
   raw8 double FIST
   raw55 double FIST
   no stuck/persistent collision
4. PASS -> record production integration closure
5. inspect eCConfigFile/config API and freeze exact generic INI syntax
6. implement shared profile/config foundation needed by Speed and later Raise
7. research/design/implement/test Speed v2 ONLY until completely closed
8. only then begin Raise
9. after Raise closes, run assembled collision + Speed + Raise regression
10. deliberate development -> main promotion
```

This focused collision check does not reopen the closed EV-386–EV-389 diagnostic campaigns. No diagnostic log is expected unless behavior contradicts the accepted system.

Authorities:

```text
DESIGN.md
ADR-0004
ADR-0005
ADR-0006
GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md
references/README.md
```

Current evidence ledger: `EVIDENCE_LEDGER_389_ONWARD.md`.  
POP-06 remains mandatory for future diagnostic runtime logs.
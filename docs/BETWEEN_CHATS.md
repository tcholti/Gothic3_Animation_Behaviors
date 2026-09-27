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
independent migration source review = PASS
EV-390 production Script_G3AnimationBehaviors.dll collision integration = CLOSED/PASS
CURRENT = freeze shared generic INI/profile foundation
NEXT = Speed v2 ONLY until completely closed
RAISE = PAUSED until Speed closes
```

EV-390 production identity:

```text
Script_G3AnimationBehaviors.dll
built/live SHA256 = 12FA5819FEEB5033B2D747A9B57CA1591E588EAAC0BAC9CC386307B77C367A55
sole live G3AB/collision product = PASS
```

Focused production gameplay reproduced the deliberately impossible-native marker controls from EV-389:

```text
2H double attack / three markers = works
1H1H triple attack / four markers = works
human Fist double / two markers = works
Sabretooth raw8 double / two markers = works
Troll raw55 double / two markers = works
```

Therefore collision migration into the final production DLL is closed. Do not reopen historical collision campaigns absent contradictory evidence.

## Branch decision

ADR-0006 owns the active model:

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

Current New Balance source is pinned at `references/jackydima-gothic3sdk` and shows why final-result replacement is wrong: its speed function combines base terms with stamina/arena/disease/etc. logic. Exact intervention mechanism remains research under ADR-0004.

### Raise — paused until Speed closes

Raise keeps the ADR-0005 design:

```text
configured Normal/Quick profile
-> request Raise through Gothic CombatMove
-> Gothic resolves actual animation through normal naming/request rules
```

The shared INI schema must support future Raise from the beginning, but no Raise behavior/research begins while Speed remains open.

## Exact next route

```text
1. inspect Gothic/eCConfigFile config API plus old G3AB config only as reference
2. freeze exact generic INI syntax for shared Speed + future Raise profiles
3. implement shared parsing/normalization/profile lookup foundation
4. research/design/implement/test Speed v2 ONLY until completely closed
5. only then begin Raise
6. after Raise closes, run one assembled regression of collision + Speed + Raise
7. deliberate development -> main promotion
```

"assembled regression" means a final safety test after Raise is integrated: verify the completed DLL still preserves already-accepted collision and Speed behavior while Raise works. It is not a separate Raise research mechanism.

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

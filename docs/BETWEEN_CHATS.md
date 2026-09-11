# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-11

## Current Bridge — EV-250 CLOSED/PASS; SPRINT TRANSPORT PROBE FROZEN

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Fresh Chat orientation:

```text
1. SESSION_ENTRYPOINT.md
2. this file
3. COLLISION_SPRINT_TRANSPORT_PROBE.md
4. EVIDENCE_LEDGER_250_ONWARD.md
5. COLLISION_TEST_PLAN.md only when planning the runtime fixture
```

Do not begin Sprint behavior implementation or the Goblin/Demon/Ogre matrix yet.

---

## Closed Starting Point

```text
Stage A architecture refactor                 CLOSED/PASS
Stage B diagnostic refactor                   CLOSED/PASS
Stage A/B compact equivalence sentinel        CLOSED/PASS — EV-250
```

Stage A implementation:
`7c5874932cd6eafa5af3414c65a4442b3d74bb73`

Stage B implementation:
`5737db32e5eda76810989ddfb5659f8405c0c458`

Validated Stage-B diagnostic DLL SHA256:
`081CDF413EC623079B8E4F1934EA7F1C27A7FFC7307B3BA0B19EA000BDA108BD`

Active Sprint raw:

```text
research/raw/2026.09.10_sabertooth_npc_pc_marked_attacks_new.log
```

---

## Sprint static research result — 2026-09-11

Known factual tested boundary:

```text
gEAction_SprintAttack = 9
actor = native Sabretooth
source = Fist/raw8/group0
phase = 1
StatePosition = 1
motion filename = PowerAttack-named
marker = FIST
current marker result = REJECTED_UNSUPPORTED_HIT
C1 binding = _AI_PowerAttack
```

Do not infer Power family semantics from the script/motion transport names.

### Transport

Pinned SDK search exposes the Action-9 enum but no dedicated `OnAI_Sprint...` callback symbol. Runtime C1 binds the tested Action-9 executions to `_AI_PowerAttack`.

Current `OnAI_PowerAttack` wrapper evaluates `AttackFamily_Power`. `EvaluateAttackCallbackOwnership()` requires factual family/action agreement, so factual Action 9 is not eligible as Power. This is intentional and explains why current Sprint does not receive raw8 ownership/initial-close.

Stage-B `LogAttackCallbackOwnership()` does not emit for non-eligible callbacks. Therefore current logs do not reveal whether Action 9 is already present at physical `OnAI_PowerAttack` entry.

That is the only remaining transport fact requiring a probe.

### Source scope

Current observed Sprint source scope is raw8 only:

```text
Fist / gEUseType_Fist / 8 / group0
```

Existing archived native weapon controls contain no Action 9:

```text
Demon   -> 2H/raw3       no Action 9 observed
Goblin  -> 1H/raw2       no Action 9 observed
Ogre    -> Axe/raw52     no Action 9 observed
```

This means equipped Sprint is currently unevidenced, not impossible.

### Native raw8 mechanism

Tested Game static control flow strongly supports Action 9 using the existing generic raw8 native route:

```text
SPU+0x164 gate at Game+0x16DFB9
GetMaxTime(0) at +0x16E160
GetPlayTime(0) at +0x16E180
threshold comparison through +0x16E190
native latch close SPU+0x164=1 at +0x16E1A3
later native Fist damage path returning at +0x16E348
```

The nearby action-specific special branch is action `0x39`, not Action 9.

Do not yet promote this static mechanism result into Sprint production behavior until callback-entry transport is proven.

---

## Frozen next Work responsibility

Authority:

```text
docs/COLLISION_SPRINT_TRANSPORT_PROBE.md
```

Work implements only a diagnostic CORE record in the already-existing physical `OnAI_PowerAttack` wrapper:

```text
ENTRY
AFTER_ORIGINAL
```

Each record captures:

```text
elapsed time
actor
SPU+0x154 factual action
actor routine action
phase
current movement animation
```

AFTER_ORIGINAL also captures native return.

Hard prohibitions:

```text
NO new hook
NO Sprint family implementation
NO marker acceptance
NO SPU latch/timing mutation
NO behavior/RVA/calling-convention change
NO species/name special case
NO broad refactor
NO Work build execution or build-tool probing
```

After Work publishes, Normal Chat independently reviews the source. Then STOP remote work at the local build/runtime gate.

---

## Runtime decision after local build

One native-Sabretooth Action-9 occurrence is sufficient if transport records are clear:

```text
ENTRY already Action 9
    -> existing OnAI_PowerAttack physical hook is early enough for first-class Sprint routing

ENTRY Power/other, AFTER_ORIGINAL Action 9
    -> callback entry is too early to identify Sprint; find next factual boundary before implementation

SPU action vs actor action materially disagree
    -> investigate disagreement before implementation

no Action 9 captured
    -> repeat same bounded fixture only
```

No Sprint behavior Work task exists yet.

# Collision Lifecycle Plan

**Status:** Working design / research target, not yet production implementation  
**Updated:** 2026-08-26

## Goal

Replace accumulated cleanup/interruption contingencies with the smallest authoritative lifecycle rule supported by the engine evidence.

> For every real attack-Hit execution that requests offensive collision, Gothic 3 gets its legitimate cleanup opportunity. When that exact Hit genuinely ends or is replaced, if proper cleanup already occurred, do nothing; if not, repair the remaining offensive collision using the native cleanup semantics.

How the Hit ends is intentionally irrelevant to the production invariant. Normal completion, block timeout, damage interruption, terrain interruption, skipped Recover bookkeeping, or another genuine replacement should become test cases for one rule rather than separate production cleanup branches.

## Preferred System — Execution-Level Native Cleanup Guard

**System 1 remains preferred.**

```text
REAL ATTACK-HIT EXECUTION X BEGINS
        ↓
Acquire using native action/callback/phase semantics
        ↓
Capture exact actual Hit motion execution
        ↓
Marked motion?
   ├─ YES → suppress native collision timing;
   │        markers own collision timing inside Hit
   └─ NO  → leave native collision activation untouched
        ↓
Did execution X request offensive collision?
   ├─ NO  → no cleanup obligation
   └─ YES → remember cleanup obligation
        ↓
Follow exact actual Hit execution
        ↓
Hit genuinely ends / is replaced / interrupted
        ↓
Allow Gothic 3 its legitimate cleanup opportunity
        ↓
Was proper cleanup observed for X?
   ├─ YES → do nothing
   └─ NO  → repair stale offensive collision
        ↓
Retire execution-level marker/lifecycle bookkeeping
```

A request counts even when the source was already `Item_Attack` (`7 -> 7`). The relevant fact is that execution X requested offensive collision, not whether the numerical group changed.

Preferred minimal execution state, if later research permits:

```text
Execution X
    exact actual Hit execution
    collisionRequested
    nativeCleanupObserved
```

Production should remain event-driven. The old Script `OnTick` comparison is diagnostic only.

## Fallback System — Source-Aware Cleanup Guard

Use source-aware ownership only if evidence proves an attack-wide cleanup obligation is insufficient, for example if one source can legitimately clean while another independently remains offensive.

The fallback keeps the same invariant but records which physical sources were requested by execution X and checks those sources individually at the authoritative Hit end.

Do **not** adopt per-source bookkeeping merely because the current prototype already has RIGHT/LEFT masks.

## Marker Rule While Hit Is Alive

Marker control is separate from final lifecycle cleanup.

```text
RIGHT = desired offensive set {RIGHT}
LEFT  = desired offensive set {LEFT}
BOTH  = desired offensive set {RIGHT, LEFT}
OFF   = desired offensive set {}
```

Each marker defines the complete desired offensive collision set at that moment.

Examples:

```text
RIGHT -> LEFT
{RIGHT} -> {LEFT}
```

```text
BOTH -> RIGHT
{RIGHT, LEFT} -> {RIGHT}
```

```text
OFF
{}
```

`G3AB_COL_OFF` is optional authored early shutoff inside a still-live Hit. It is not mandatory terminal safety and must not substitute for the execution-level cleanup invariant.

Repeated source markers remain responsible for explicit rearm via `ClearTriggeredList()` at later authored contacts.

## Two Governing Rules

```text
WHILE THE HIT IS ALIVE:
Markers define the desired offensive collision set.
```

```text
WHEN THE HIT IS OVER:
Offensive collision must be clean.
If Gothic 3 already cleaned it -> nothing.
If Gothic 3 failed -> repair.
```

## Native Cleanup Paths Are Opportunities, Not Guarantees

Step B4/B4b proved that successful Gothic cleanup is not one universal action function.

Ordinary successful completion uses action-specific `Script_Game.dll` cleanup sites for tested Normal, Power, Quick, SimpleWhirl, full Whirl, Pierce, Hack, Finishing, and GetUpAttack paths.

Legitimate damage/reaction interruption uses a separate tested path beginning with:

```text
Script_Game + 0x24AFF
```

The production guard should therefore **observe success**, not depend on one particular cleanup function always running.

This distinction also applies to marked attacks. Earlier marked interruption tests often cleaned successfully, but later marked Staff/block-skip cases proved natural cleanup is not guaranteed across every ending. The universal guard is therefore still required even though legitimate native interruption cleanup exists.

## Step-B Evidence That Constrains the Model

### B1 — actual motion replacement is earlier than cleanup

`eCVisualAnimation_PS::PlayMotion(type 0)` is an immediate PrimaryFirst acquisition/replacement signal in controlled tests.

However, clean successor Recover PlayMotion occurs **before** native `7 -> 5` cleanup. Therefore replacement detection itself is too early for immediate repair.

The old Script `OnTick` comparator sees replacement later and is too indirect/coarse for production.

### B2 — original attack callbacks are not completion events

On clean Quick paths, native cleanup occurs before the later original callback starts; that callback then repeats during Recover. Callback return is not one-shot Hit completion.

### B3 — StartRecover is not post-cleanup and is not guaranteed

`gCScriptProcessingUnit::sAICombatMoveStartRecover` starts/attempts the Recover transition and returns while the weapon is still group 7. Cleanup follows later.

Broken 2H/Staff Whirls can bypass StartRecover entirely and replace the Hit directly without cleanup.

### B3b — missing Recover asset is not the cause

Native 1H/Shield+1H Quick attacks with no Recover animation asset can still run the engine's Recover lifecycle/bookkeeping and clean correctly while the Hit motion remains Primary.

The same no-Recover attack can also take the broken path and remain stale.

Therefore Recover **asset playback** and Recover **lifecycle bookkeeping** are distinct.

Native Dual Quick reproduced the same structural stale path, proving the defect is not Staff/Whirl-specific.

### B4/B4b — successful cleanup is action-specific

Detailed build-specific map:

`docs/COLLISION_CLEANUP_CALLSITE_MAP.md`

The same serialized `FinishingAttack` asset can be processed under different runtime actions and cleanup functions. Native action semantics, not filename identity, are the behavioral authority.

A separate legitimate interruption cleanup site exists at `Script_Game + 0x24AFF`.

### B5 — ordinary and interruption success reach adjacent sibling Game paths

For ordinary successful completion, different action-specific Script_Game cleanup calls converged in the B5 stack to:

```text
Game + 0x1605EB
```

inside a Game helper beginning at approximately:

```text
Game + 0x1604E0
```

The tested legitimate interruption path instead returned through:

```text
Script_Game + 0x24AFF
→ another Script_Game frame
→ Game + 0x1604D3
```

Binary inspection shows `+0x1604D3` belongs to the immediately preceding sibling Game function, whose return ends at approximately `+0x1604D5`; the ordinary sibling begins at `+0x1604E0`.

Thus B5 did **not** find one identical captured parent for both successful paths. Do not hook both sibling helpers merely because they are adjacent. First inspect who calls/selects them and whether a narrower post-opportunity event exists above them.

## Marker Bookkeeping vs Physical Cleanup

Physical collision cleanup and marker-execution retirement are different responsibilities.

The earlier v0.15/v0.16 interruption defect was:

```text
first marker accepted
→ attack interrupted before later authored marker
→ Gothic physically resets weapon 7 -> 5
→ old marker occurrence/execution record can remain stale
→ next attack inherits old marker budget
```

`RetireMarkerOwnedSource()` was added to react to an **already-performed** source reset and retire marker bookkeeping when that reset represented execution end. It is not a physical fallback cleanup operation.

Intentional intra-Hit `OFF` or exact-set source switching must not retire the entire execution.

A future authoritative exact-Hit lifetime boundary may simplify both:

1. final physical cleanup verification;
2. marker occurrence/budget/window retirement.

Do not assume this simplification until the boundary is proven.

## Current Three-Path Model

### A. Normal completion

```text
Hit
→ action-specific Script_Game completion cleanup
→ shared ordinary Game sibling path
→ collision clean
```

### B. Legitimate damage/reaction interruption

```text
Hit
→ Script_Game interruption cleanup (+0x24AFF)
→ interruption Game sibling path
→ Stumble/KnockDown/etc.
→ collision clean
```

### C. Bad block skip / abnormal teardown

```text
Hit
→ some CombatMove/gameplay ownership is abandoned
→ proper completion cleanup not guaranteed
→ proper interruption cleanup not guaranteed
→ physical Hit can continue or later replace
→ stale collision possible
```

This model explains why adding one special block-timeout cleanup branch would be the wrong abstraction.

## Separate Deeper Block-Skip Hypothesis

Current evidence supports a broader native CombatMove teardown defect distinct from the universal collision safety guard.

Working hypothesis:

> During the vulnerable block-timeout/skip, Gothic 3 may abandon some action/CombatMove ownership or bookkeeping while the physical PrimaryFirst Hit motion continues playing. A skip during an active Hit is potentially harmful regardless of whether offensive collision has activated yet.

Possible timing-dependent consequences:

1. **Before collision activation:** remaining native movement and/or collision timing may be abandoned while the visual Hit continues. Missed activation from this exact mechanism remains plausible but not directly logger-confirmed.
2. **After collision activation:** later cleanup can be lost. This is runtime-confirmed and can leave the weapon offensive during Ambient/running state and into later attacks.

The user also visually observed attack-driven forward movement apparently stopping at the bad skip while animation continued. This remains a useful later research lead rather than a current collision-guard dependency.

Raise is not a cleanup or block-skip fix. A pre-Hit Raise may only move the vulnerable skip before an offensive Hit begins; if a fresh Hit starts afterward, normal gameplay ownership may be reacquired.

## Research Order

1. Finish the universal execution-level collision safety rule.
2. Validate it against native and marked normal completion plus several abnormal endings.
3. Only later decide whether to repair the deeper block-skip/CombatMove teardown itself to preserve movement, collision activation/timing, and other gameplay behavior.

A deeper block-skip fix does not make the universal guard redundant.

## Current Next Research Target

Do **not** implement production cleanup yet.

Next question:

> What calls/selects the two adjacent Game sibling paths around `Game + 0x1604D3` and `Game + 0x1604E0..0x1605EB`, and is there a narrow event-driven boundary after either legitimate completion/interruption path has had its cleanup opportunity?

Preferred next activity is static binary/source inspection of those sibling functions and their callers/dispatch conditions before another runtime hook is added.

Only if that inspection identifies a plausible narrow parent/event should another bounded runtime probe be created.

Do not default to:

- one cleanup hook per action family;
- hooking both siblings just because they are adjacent;
- broad `sAICombatMoveItlLoop` polling;
- timers or wall-clock delays;
- block-timeout/Staff/Quick/Whirl-specific production cleanup rules.

## Working Hypotheses

1. Offensive collision belongs to a physical attack-Hit execution and should not intentionally survive into the next independent Hit.
2. Actual PrimaryFirst Hit execution is a better lifetime authority than continuing action/phase after acquisition.
3. Native and marked attacks can share one end-of-Hit cleanup invariant even though their activation policy differs.
4. A usable event-driven post-opportunity boundary probably exists above or around the adjacent Game sibling helpers, but this is not yet proven.
5. Defensive block/parade collision semantics must be measured before any broad "clean every collision state" implementation.
6. The block-skip defect is likely broader than collision cleanup and should remain separate research.

## v0.20 Scaffolding to Revisit Later

Useful prototype mechanisms that are **not presumed production architecture**:

1. `MarkerOwnedCollisionWindow` as lifetime owner.
2. strict source + animation + action + phase matching after acquisition.
3. state-time/action/phase inference for execution lifetime.
4. `RetireMarkerOwnedSource(...)` as lifetime inference from natural source reset.
5. action/phase as continuing marker veto after exact Hit ownership is acquired.
6. any accumulated special cleanup contingency.

Keep unless separate evidence says otherwise:

- final marker vocabulary RIGHT/LEFT/BOTH/OFF;
- desired-set switching;
- repeated source markers + `ClearTriggeredList()` rearm;
- optional OFF;
- same-update duplicate suppression;
- authored occurrence budgets for Gothic frame-effect replay/interleaving;
- exact marked-motion preflight and native fallback when required sources are unavailable.

## Research DLL / Diagnostics Rule

Keep behavior and lifecycle diagnostics in one research DLL while they share Gothic hooks.

```text
Main / Hook Bridge
    owns each Gothic hook once
        ├── Collision Control
        └── Collision Diagnostics
```

Diagnostics must never be required for production behavior.

`Script_CombatMoveLogger v0.4` remains a separate proven combat-move/speed tool and should not automatically absorb collision-lifecycle diagnostics.

## Implementation Gate

Production cleanup implementation remains blocked until the post-native-cleanup opportunity is identified strongly enough to avoid family-specific repair rules or polling.

If implementation research reveals a conceptual contradiction, return to design/research rather than stacking compensating branches.

## Preference Order

1. **Preferred:** execution-level guard that observes/reuses Gothic's native cleanup semantics.
2. **Fallback:** source-aware guard only if independent source cleanup evidence requires it.
3. Avoid interruption-specific production branches unless a real case is proven unable to fit either general model.

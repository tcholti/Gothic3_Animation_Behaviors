# Stage B — Collision Diagnostic Refactor Contract

**Status:** FROZEN Work responsibility  
**Updated:** 2026-09-10  
**Project:** `Gothic3_Animation_Behaviors`

## Purpose

Refactor the research diagnostic product after Stage A architecture build/load PASS so larger collision tests produce compact, readable logs without losing evidence needed for failures, unknown families, or SprintAttack discovery.

This is a **DIAGNOSTIC-ONLY PARITY REFACTOR**. It must not change collision behavior.

Read with:

```text
SESSION_ENTRYPOINT.md
BETWEEN_CHATS.md
COLLISION_ARCHITECTURE_REDESIGN_PLAN.md
COLLISION_LOGGER_PLAN.md
WORK_IMPLEMENTATION_PROTOCOL.md
```

Stage A implementation source base is `7c5874932cd6eafa5af3414c65a4442b3d74bb73`; documentation commits follow it on the same branch. Work must start from the current remote branch HEAD required by the handoff prompt.

---

## 1. Governing Rule

> **Known successful behavior logs compactly. Unknown, unsupported, contradictory, repair, or invariant behavior logs richly.**

Product separation remains:

```text
behavior-only / future production
  diagnostics not compiled

CORE diagnostic build
  compact ordinary regression evidence
  rich anomaly/unknown evidence

DEEP diagnostic build
  retained low-level reverse-engineering probes
```

Do not delete reusable research capability merely to reduce output. Move it to DEEP where appropriate.

---

## 2. CORE Startup Metadata

Keep the short startup/lifetime banner.

Correct the stale `BehaviorCore:` line so it includes the implemented Stage A modules:

```text
EngineBridge
FrameCollisionMarkers
CollisionSources
CollisionSourceOperations
CollisionLifecycleGuard
Raw8FistCollision
AttackMotionRouting
RuntimeClock
```

Keep:

```text
DiagnosticProfile: CORE
DeepDiagnostics: ENABLED/DISABLED
C1 repair policy summary
supported MarkerFamilies
MarkerOpcodes
clean unload line
Hack callback identity probe
```

Do not add Sprint to `MarkerFamilies`; Sprint remains unsupported.

---

## 3. Move Historical Fist Gate Probes to DEEP

These are no longer ordinary CORE requirements:

```text
FistCanBeActivatedNow hook/logging
FistTriggerTarget hook/logging
bounded FIST hook-entry identity/cap logging
routine FIST trigger-state snapshot logging
```

### Physical hook ownership

`EngineBridge` remains the sole physical hook owner.

Move installation and wrapper compilation for:

```text
Game +0x692F0 FistCanBeActivatedNow
Game +0x693B0 FistTriggerTarget
```

from `FRAME_COLLISION_DIAGNOSTICS` to `FRAME_COLLISION_DIAGNOSTICS_DEEP`.

Do not change their RVAs, calling convention, wrapper semantics, native calls, argument handling, or research output when DEEP is enabled.

Move the supporting detailed Fist gate/hook-entry logging API/implementation to DEEP ownership, or compile/call it only under DEEP if that is the smaller clean implementation. CORE with DEEP disabled must install neither physical hook and produce none of those records.

### Routine trigger snapshots

The before/after `LogFistTriggerStateSnapshot` calls around ordinary native attack and `AISetState` paths must not execute in CORE.

Retain equivalent capability under DEEP only. Do not change the underlying native attack/AISetState calls.

---

## 4. Keep OnDamage in CORE, Compact Its Normal Output

The `gCEntity::OnDamage` diagnostic hook remains installed in CORE because it is required for native damage correlation and future Sprint discovery.

Do not change:

```text
physical hook RVA
calling convention
original/native call
argument forwarding
```

Replace the routine large multi-line entity/contact dump with one compact factual CORE event per logged entry containing enough to preserve:

```text
elapsed time / ordinal
target/this entity name
entity argument names
caller module + RVA when resolvable
current player action/phase/current motion context
resolved player Fist/raw8 identity when present
```

Exact raw pointer/contact-iterator/integer argument detail belongs in DEEP.

Retain the existing bounded-entry/cap protection or an equivalent bounded protection so CORE cannot grow without limit from the OnDamage hook.

When DEEP is enabled, preserve access to the previous detailed OnDamage caller/entity/contact evidence in addition to or instead of the compact CORE line, whichever is architecturally cleanest without duplicate ambiguity.

---

## 5. Marker Logging — One Post-Result CORE Event

CORE must stop producing separate large `MARKER RECEIVED` context + large `MARKER RESULT` blocks for every normal marker.

Prefer one post-`ProcessMarker` diagnostic call/event that can inspect:

```text
Entity actor
MarkerProcessResult result
```

Do not change `ProcessMarker` behavior or its order.

### Known successful/expected marker event

For routine accepted/expected traffic, log one compact event containing enough to establish:

```text
actor
action
resolved family when known
phase
current motion
marker opcode
result code
C1 generation when available
StatePosition result where behaviorally relevant
meaningful desired/previous/retired/owned source mask
physical activation/deactivation/rearm counts
source UseType/side when a physical equipped source participated
```

Do not dump every cached marker count/frame/source address for every healthy event.

### Unsupported / anomaly marker event

`MarkerResult_RejectedUnsupportedHit`, generation inconsistency, missing source, incomplete activation, unexpected motion ownership failure, repair-related contradiction, or other non-routine rejection must be rich enough to classify later.

For unsupported/unknown action traffic, including current SprintAttack, automatically log at minimum:

```text
actor name
numeric action
phase
StatePosition
current movement animation
marker name/opcode
result/rejection reason
C1 generation if available
right equipped source: name / UseType / collision group / slot association
left equipped source: name / UseType / collision group / slot association
resolved Fist source: name / UseType / collision group when present
```

This detail may be gathered diagnostically from `actor` even when `ProcessMarker` rejected before filling later result fields. Do not change behavior processing merely to populate diagnostics.

This is the primary CORE discovery path for unsupported Sprint.

### Duplicate/budget traffic

Expected duplicate-same-update or authored-occurrence-budget suppression should be compact, not a full anomaly dump, unless identity/generation inconsistency is involved.

---

## 6. Attack Callback Ownership Logging

Keep callback ownership observation in CORE but compact routine successful/known output.

A routine record should establish only the useful facts:

```text
actor
family
numeric action
phase
current movement animation
reserved-marker presence
required equipped source mask
FIST-marker presence / factual Fist source when relevant
native callback suppressed yes/no
```

Do not repeatedly dump all authored marker counts/first-frame tables and every source address for healthy known motion ownership.

Preserve richer detail for an unexpected ownership/source contradiction.

Existing once-per-motion dedupe may remain if still useful; do not redesign behavior around diagnostic dedupe.

---

## 7. Raw8 FIST CORE Logging

Rename Stage A's stale diagnostic-facing `HumanFist...` concepts to factual `Raw8Fist...` naming where the diagnostic refactor naturally touches them.

Do not rename or change behavior semantics merely for aesthetics beyond the diagnostic interface/calls.

For healthy known raw8 Normal/Power/Quick traffic, replace large ownership/opportunity/timing blocks with compact events.

CORE must preserve:

```text
actor
family/action when available
C1 generation
factual raw8 Fist identity
initial marked-execution latch close result
accepted FIST latch rearm result
ownership/identity match
timing classification:
  NATIVE_TIMING
  EARLY_PERMISSION_ARMED
  EARLY_PERMISSION_USED
  TIMING_UNAVAILABLE / IDENTITY_MISMATCH or equivalent anomaly
```

Full SPU addresses, animation-actor addresses, threshold arithmetic, exact real/max/returned play times, and detailed permission-retirement state belong in DEEP for ordinary known traffic.

If raw8 ownership/latch/timing identity fails unexpectedly, CORE must emit a richer anomaly record rather than hiding the failure behind a compact success format.

Do not change:

```text
Normal + Power + Quick supported set
SPU+0x164 writes
threshold constant/read
threshold calculation
epsilon
permission arming/retirement/identity/consumption
native fallback
```

---

## 8. SetCollisionGroup CORE Logging

Keep meaningful physical attack-source transitions observable, but replace large blocks with compact events.

CORE must preserve meaningful cases including:

```text
Item_Equipped -> Item_Attack
Item_Attack -> Item_Attack when behaviorally meaningful rearm/offense request
Item_Attack -> Item_Equipped/other cleanup
marker-owned source-bit retirement
```

Do not emit large context blocks for routine calls.

Suppress records that are genuinely unrelated to attack-source behavior or produce no relevant information under the existing attack filter.

Do **not** suppress `7 -> 7` merely because the numerical group is unchanged; repeated authored rearm/offense can make that event meaningful.

Remove the current player-only contextual assumption from the compact source event. Prefer facts about the actual changed source and its factual slot association to the owning actor when that association is available; do not invent an owner if it cannot be established.

Do not change the SetCollisionGroup behavior hook or lifecycle observation order.

---

## 9. C1 Lifecycle CORE Logging

Remove the current player-only output filtering where it would hide relevant NPC lifecycle evidence.

Routine healthy chronology should become compact one-line/event records rather than large blocks:

```text
C1 generation start/bind/status when useful
C1 offense obligation
C1 cleanup fulfillment
C1 healthy finalization outcome
```

The minimum healthy facts are:

```text
actor
generation
source / side when relevant
outstanding obligation state
cleanup fulfilled or finalization outcome
```

The full START -> BINDING -> STATUS chronology may be omitted or condensed for ordinary healthy paths.

### Rich CORE cases

Keep/produce rich detail for:

```text
any LifecycleIssue / C1 INVARIANT WARNING
unresolved-not-equipped finalization
terminal repair attempted
repair divergence
unexpected generation/binding overlap
```

For C1-R1 repair, preserve exact:

```text
actor
generation
source
original/current side
outstanding state
liveness
actual group before
requested repair group
actual group after
outcome
```

Do not change any C1 state, criteria, generation, binding, cleanup, or repair behavior.

Routine `RunScriptFunctionScopeReturn` diagnostic chronology should move to DEEP unless needed to explain a CORE anomaly.

---

## 10. DEEP Retention

DEEP must continue to provide reusable detailed research capability, including existing:

```text
PlayMotion / StopMotion snapshots and stacks
StartRecover stacks/boundaries
AIFullStop / FullStop context
AISetState caller/stack context
outer-frame/state-stack detail
native cleanup stack/caller detail
OnTick marker lifetime tracking
```

Stage B also places the removed CORE detail here:

```text
Fist gate/trigger hooks and state snapshots
full raw8 timing arithmetic/addresses
full OnDamage addresses/contact/integer arguments
full healthy ownership tables when needed
full routine C1 dispatch chronology when needed
```

Do not add new reverse-engineering hooks for Sprint in Stage B.

---

## 11. Behavior-Only Warning Cleanup Allowed

Stage A exposed non-fatal Release warnings because some locals/parameters in shared behavior files are only consumed by diagnostic calls when diagnostics are compiled.

Stage B may remove these warnings only by mechanically conditionalizing or explicitly marking **diagnostic-only values** unused in behavior-only builds.

Allowed examples:

```text
`reason` used only by diagnostic retirement logging
diagnostic-only copies of latch-before/timing arithmetic values
`EngineBridge` helpers/locals used only under diagnostic/deep gates
```

Hard rule: do not remove, reorder, or skip any behavior-required read/write/call merely to silence a warning.

---

## 12. Hard Boundaries

Stage B MUST NOT:

```text
implement SprintAttack or AttackFamily_Sprint
add a Sprint callback/hook
add any new gameplay hook
change any behavior hook RVA/calling convention
change marker vocabulary
change supported attack-family semantics
change StatePosition behavior
change raw8 source/latch/timing behavior
change equipped RIGHT/LEFT/BOTH/OFF behavior
change ClearTriggeredList behavior
change C1 generation/ownership/repair criteria
change Hack motion routing
implement AttackContinuationProtection
implement Raise / Speed / Config
implement raw55/PhysicalFist behavior
perform unrelated source cleanup
```

Moving existing diagnostic-only physical hooks from CORE to the already-existing DEEP compile gate is explicitly authorized; changing those hooks is not.

If a material contradiction requires behavior changes beyond this diagnostic contract, STOP and report it.

---

## 13. Build / Publication Rule

Work BUILD EXECUTION OR BUILD-TOOLING PROBING IS PROHIBITED.

Work must perform source/static audit and `git diff --check`, then commit/push the bounded Stage B implementation to `docs/collision-source-evidence`.

Required report:

```text
final remote commit SHA
changed files
concise CORE reductions / DEEP-retained capability summary
static-audit result
git diff --check result
build status: NOT RUN / PROHIBITED
material contradiction, if any
```

Then STOP.

---

## 14. After Work

Normal Chat independently reviews the exact diff.

Then User + Normal Chat locally:

```text
build both Release twins
deploy diagnostic DLL
verify built/live SHA256 equality
load/unload smoke
```

Only after that passes run the compact equivalence sentinel:

```text
raw8 FIST: Sabretooth Normal + Quick + Power
equipped: one ordinary marked weapon attack
marker lifecycle: one established multi-marker / OFF / rearm fixture
C1 safety: one established destructive bad-skip -> exact terminal repair
```

Only after sentinel PASS begin SprintAttack factual source/transport/mechanism investigation.

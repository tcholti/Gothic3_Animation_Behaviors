# Gothic 3 Script Release Architecture

**Status:** Canonical project-wide release/build rule  
**Updated:** 2026-08-30  
**Scope:** All present and future Gothic 3 script/DLL systems in this project

## 1. Governing Rule

> **Released Gothic 3 behavior DLLs must contain behavior only. Research diagnostics are a separate build product and must not be compiled into the release binary.**

This is a project-wide architectural constraint, not a collision-specific preference.

It applies to existing and future systems including, but not limited to:

```text
frame-controlled collision
collision lifecycle repair
AttackContinuationProtection
Raise control
playback-speed control
target acquisition
climbing
future animation-selection or gameplay behavior modules
```

A behavior module is not production-ready if its correctness depends on diagnostic code, diagnostic state, diagnostic hooks, log files, stack capture, or a diagnostic runtime mode.

---

## 2. Two Mutually Exclusive Build Products

The intended long-term model is one shared behavior codebase with two separately built products.

```text
SHARED BEHAVIOR CORE
EngineBridge
behavior modules
source adapters
configuration
        |
        +-----------------------+
        |                       |
        v                       v
RELEASE BUILD              DIAGNOSTIC BUILD
behavior only              same behavior core
no diagnostics             + CollisionDiagnostics
no diagnostic strings      + compact core evidence
no stack capture           + opt-in deep probes
no diagnostic state        + diagnostic-only hooks when needed
```

### Release product

The released `Script_G3AnimationBehaviors.dll` must not contain:

```text
CollisionDiagnostics implementation
research logger code
research log strings/banners
CaptureStackBackTrace or equivalent research stack capture
module/RVA-resolution code used only for diagnostics
primary-motion lifetime probes used only for research
OnTick polling used only for diagnostics
diagnostic-only PlayMotion / StopMotion / StartRecover hooks
diagnostic state maps/caches
runtime switches whose only purpose is to enable hidden research diagnostics
```

If a hook or state object is required for behavior correctness, it belongs to the behavior architecture and is not diagnostic merely because diagnostics also observe it.

### Diagnostic product

The diagnostic/research product contains the same behavior core plus instrumentation needed for controlled validation and future investigations.

It may provide:

```text
compact default collision/behavior evidence
opt-in deep probes
call stacks and caller/RVA context
motion-lifetime snapshots
additional diagnostic-only hooks
research-only state needed to correlate observations
```

Diagnostic instrumentation must remain observational. Disabling/removing it must not change intended behavior.

---

## 3. Do Not Load Release and Diagnostic Twins Together

Do not solve diagnostic separation by installing two copies that independently hook the same Gothic functions.

Preferred packaging:

```text
normal package:
Script_G3AnimationBehaviors.dll

controlled diagnostic package/build:
instrumented twin used IN PLACE OF the release DLL
```

Build targets/output directories may have distinct internal names, for example:

```text
Script_G3AnimationBehaviors_RELEASE
Script_G3AnimationBehaviors_DIAGNOSTIC
```

but they should be treated as mutually exclusive runtime products unless a future architecture explicitly proves safe coexistence.

This preserves the one-hook-owner rule and avoids accidental same-function hook competition.

---

## 4. Why a Separate Generic Logger Is Not Always Enough

A separate general logger DLL is appropriate for facts that can be observed independently from Gothic 3, such as generic combat-move or animation-speed research.

The existing `tools/Script_CombatMoveLogger` remains useful for that role.

However, some diagnostics need internal behavior state such as:

```text
C1 monotonic generation
exact outstanding source obligation
pre-Combat bridge acquisition/consumption
marker occurrence budget
marker-owned source window
repair classification/result
```

A completely separate logger DLL cannot observe those internal facts without either:

1. forcing the release DLL to expose diagnostic instrumentation interfaces; or
2. duplicating hooks and reconstructing private behavior state independently.

Both approaches weaken the release-purity and one-hook-owner rules.

Therefore the preferred solution for internal behavior diagnostics is an instrumented build of the same architecture, not a companion DLL loaded beside the release DLL.

---

## 5. Dependency Rule

Production dependencies must point away from diagnostics.

Correct conceptual direction:

```text
EngineBridge / behavior modules / source adapters
        |
        +--> factual result/state
                 |
                 v
          CollisionDiagnostics   [diagnostic build only]
```

Forbidden architecture:

```text
behavior correctness
    -> requires CollisionDiagnostics
    -> requires log to be open
    -> requires diagnostic state/cache
    -> requires diagnostic-only hook
```

Behavior modules may produce compact factual result structures that diagnostic builds observe. They must remain correct when no diagnostic consumer exists.

---

## 6. Hook Rule

The central EngineBridge remains the sole physical hook owner inside each built DLL.

For release builds:

```text
install only hooks required by production behavior
```

For diagnostic builds:

```text
install all production-required hooks
+ diagnostic-only hooks only when the selected diagnostic profile requires them
```

A diagnostic-only hook must never silently become a production prerequisite merely because the research DLL historically installed it.

---

## 7. Development Rule for Every New System

Every new Gothic 3 behavior responsibility must be designed from the beginning in three layers:

```text
1. behavior authority
   what the feature decides and changes

2. engine transport / shared hook facts
   how authoritative native events reach the feature

3. diagnostics
   how we observe/prove the feature during development
```

The third layer must remain removable from the first two.

This rule applies when adding future systems such as target acquisition, climbing, or other gameplay/animation behaviors to `Script_G3AnimationBehaviors`.

Do not first build feature logic around a logger and plan to peel the logger out later.

---

## 8. Promotion / Release Gate

Before a stable public release, verify explicitly that:

```text
release target does not compile diagnostic source files
release target does not install diagnostic-only hooks
release target does not contain research log output paths/banners
release behavior does not depend on diagnostic state
release behavior passes its required runtime/compatibility tests
instrumented diagnostic twin remains available separately for controlled reproduction
```

For `Script_G3AnimationBehaviors`, the final release compatibility gate still includes New Balance and relevant Jackydima DLL regression.

---

## 9. Current Project Consequence

The mature `Script_FrameCollisionTest` research architecture is becoming the architectural ancestor of the final `Script_G3AnimationBehaviors` behavior core.

During research, retain useful diagnostics and deep probes where they answer concrete questions.

During production extraction:

```text
keep proven behavior architecture
keep behavior-required shared hooks
keep behavior state/invariants
remove diagnostics from the RELEASE target entirely
retain a separate instrumented diagnostic build for future controlled work
```

The final public DLL may therefore contain collision, Raise, speed, target acquisition, climbing, and other future behavior modules while still containing **zero research-diagnostic implementation**.

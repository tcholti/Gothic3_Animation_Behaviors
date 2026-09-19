# ADR-0003 — Promote Equipped Sprint as Permanent Behavior, Not a Diagnostic Probe

**Status:** Accepted  
**Date:** 2026-09-19  
**Evidence basis:** EV-311, EV-315–EV-324

## Context

Equipped Sprint was discovered as factual `Action9 / SPRINT` traffic arriving through the existing physical `OnAI_PowerAttack` callback. A diagnostic-only `EquippedSprintProbe` was used to answer the causal question without prematurely changing production behavior.

The accepted evidence now shows:
- eligible marked Sprint can hand collision timing to the generic equipped marker mechanism;
- exact same-C1 Sprint origin may continue through factual Action9 -> Action2 without becoming a new true-Power execution;
- missing required equipped sources fail closed and preserve native fallback;
- raw8, raw55 and ordinary equipped true Power remain isolated;
- generic marker semantics remain owned by `FrameCollisionMarkers`.

Leaving the behavior behind `FRAME_COLLISION_DIAGNOSTICS` would make proven behavior depend on research-product configuration. Compiling the temporary probe into production would preserve the wrong ownership model.

## Decision

Promote the proven mechanism into a permanent behavior module:

`EquippedSprintCollision`

The permanent module owns Sprint-specific eligibility, bound origin identity, exact continuation validation and authorization into the existing generic equipped marker mechanism.

`EngineBridge` remains physical hook transport only.

`FrameCollisionMarkers` remains owner of generic RIGHT/LEFT/BOTH/OFF semantics, occurrence/dedupe, marker-owned windows and generic source operations.

The temporary `EquippedSprintProbe` is research scaffolding and must be removed from active source after extraction.

Behavior-only and diagnostic twins must compile the same permanent Sprint behavior. Diagnostics may observe it but cannot own or enable it.

## Consequences

- Equipped Sprint can become production behavior without diagnostic dependency.
- Action9 remains the immutable origin; exact same-C1 Action2 is only a bounded continuation.
- New ordinary true-Power executions cannot inherit Sprint ownership.
- Missing-source BOTH cannot partially activate RIGHT.
- No species or UseType-specific support boundary is introduced.
- Release-purity remains mechanically testable because the permanent behavior module is independent of `CollisionDiagnostics`.
- The later migration into `Script_G3AnimationBehaviors` remains separate from this standalone promotion.

## Current authorities

- `DESIGN.md`
- `GOTHIC_SCRIPT_RELEASE_ARCHITECTURE.md`
- `COLLISION_REFERENCE.md`
- `docs/work/active/COLLISION_EQUIPPED_SPRINT_PRODUCTION_PROMOTION.md`

This ADR records why promotion uses a permanent behavior owner rather than retaining the successful diagnostic probe.

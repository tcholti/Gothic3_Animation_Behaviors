# Speed v2 Deep Independent Static Audit — Result

**Status:** CLOSED  
**Audit date:** 2026-09-28  
**Audited production source:** `4f9911f57d8d6b36efd35adee41920560c3986e0`  
**Audit task/documentation HEAD:** `19eff2b8cab0f3d0db46f7f90f86fd8e4b1d8d18`  
**Verdict:** **PASS WITH NON-BLOCKING FINDINGS**

## Purpose

Durable closure record for the heavy read-only Work audit requested after interrupted source/review sessions. The audit was instructed to independently reconstruct the critical Speed v2 mechanism from pinned SDK, binary-reference and New Balance sources before reconciling EV-391/EV-392.

The full audit report was returned to Normal Chat as a 210-line text artifact on 2026-09-28. The original active audit contract remains available in Git history at `19eff2b8cab0f3d0db46f7f90f86fd8e4b1d8d18`.

## Independent conclusions

The audit found **no BLOCKER and no MAJOR finding**.

It independently re-derived and accepted:

- all six frozen Speed call sites: `+0x383F0`, `+0x38E9D`, `+0x38F22`, `+0x3937D`, `+0x39402`, `+0x48677`;
- exclusion of `+0x38A8B` because its apparent action scalar is integerized `PSRoutine::GetStateTime()`, not factual action identity;
- exhaustive classification of the tested `Script_Game+0x42A0` direct callers, with no additional supported Normal/Quick caller found;
- `mCCallHook` EAX capture, thunk stack layout, `mCCaller` EAX restoration, stdcall cleanup and x87 return compatibility;
- live-address invocation of `Script_Game+0x42A0`, preserving whichever compatible owner is installed there, including New Balance;
- exactly-once compatible-owner invocation before G3AB composition;
- New Balance Normal/Quick base/multiplier form needed for `B*M -> (C/B) -> C*M`;
- EngineBridge as low-level transport owner, AttackSpeed as stateless policy/composition, and BehaviorProfiles as generic startup configuration;
- fail-closed behavior for unsupported actions/phases/families/raw UseTypes/profiles;
- no Speed dependency or source change in the collision subsystem;
- no later Speed-relevant production-source drift between the audited source and the audit-task HEAD.

The audit also confirmed that `SharedConfig` / `AttackRaise` are historical dead source excluded from the production target and therefore do not constitute conflicting runtime authority.

## MINOR S-01

One numerical edge was found in `AttackSpeed::ComposeCompatibleSpeed()`:

- `BaseSpeed` deliberately accepts every positive finite float;
- the pre-correction code validated finite inputs but returned `compatibleSpeed * (BaseSpeed / referenceBase)` without validating the result;
- an extreme but finite configured value could therefore overflow to a non-finite result.

The audit classified this as MINOR because ordinary configured values, the shipped neutral INI, the six-site ABI mechanism and the evidence-bounded base table are unaffected.

Smallest correction direction: compute the composed result and return the live `compatibleSpeed` unchanged if the result is non-finite. Do not add an arbitrary parser upper bound.

## Runtime-only unknowns retained

Static audit does not prove build/link success, hook installation against the User's installed binaries, deployed module fingerprints, live INI loading, factual runtime family strings, New Balance contextual-modifier preservation in gameplay, absence of indirect script re-entry, third-party caller-site patch compatibility, or visual/gameplay acceptance.

Those remain the local build/deploy/startup/runtime gate.

## Disposition

- **PASS WITH NON-BLOCKING FINDINGS.**
- The six-call Speed v2 architecture and transport are independently supported.
- S-01 was deliberately selected for a separate smallest bounded correction before first build.
- Speed remains open until local runtime acceptance.
- Raise remains paused.

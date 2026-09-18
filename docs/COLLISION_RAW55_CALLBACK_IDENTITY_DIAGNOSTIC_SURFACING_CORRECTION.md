# Gothic 3 — raw55 Callback Identity Diagnostic Surfacing Correction

**Status:** FROZEN bounded diagnostics-only correction  
**Date:** 2026-09-18

## Purpose

Close one diagnostics-only contract omission found by the independent permanent-raw55 source audit.

Permanent raw55 behavior is already accepted for the four proven families. This task does **not** change raw55 behavior.

## Required base

Use the current branch state containing:

```text
314f284dbaaf05c5f185811aab107e84f1d434ce
```

and the later documentation-only maintenance commits.

## Problem

`PhysicalFistCollision::ResolveExecution()` can correctly identify an identity/origin contradiction for the same factual C1.

At marker dispatch, that contradiction becomes:

```text
MarkerResult_RejectedGenerationInconsistency
```

and is therefore visible in diagnostics.

At native callback entry, however, `BeginNativeCallbackScope()` currently does:

```cpp
PhysicalFistExecution *const execution = ResolveExecution(
    facts, created, identityContradiction);
if (execution == nullptr || identityContradiction)
    return;
```

so the correct behavior decision — no intervention — is preserved, but the contradiction can be diagnostically silent.

The frozen production architecture §5 requires:

```text
Any other same-C1 origin contradiction performs no new raw55 intervention
and is surfaced by diagnostics.
```

## Exact responsibility

Modify only the permanent raw55 feature's **diagnostic reporting** so a callback-entry identity/origin contradiction is surfaced as one compact stable CORE diagnostic fact.

The diagnostic must make clear at minimum:

```text
actor
current C1 generation
stored origin family
current callback family
exact RIGHT source identity
contradiction/rejection fact
```

Use the existing `FRAME_COLLISION_DIAGNOSTICS` boundary.

The behavior-only target must remain mechanically free of the log operation after preprocessing.

## Allowed source

Expected changed source:

```text
prototypes/Script_FrameCollisionTest/PhysicalFistCollision.cpp
```

No header change is expected unless compilation proves one is mechanically required.

## Protected behavior

Do not change:

- `ResolveExecution()` identity rules;
- execution creation/replacement;
- immutable origin;
- Sprint Action9 -> Action2 continuation;
- raw55 eligibility;
- callback scope activation decisions;
- premature 5 -> 7 suppression;
- marker first/repeated-FIST semantics;
- Normal native-clear suppression;
- raw8 behavior;
- equipped marker behavior;
- EngineBridge;
- lifecycle;
- hooks;
- CMake.

The contradictory callback must still perform **no new raw55 intervention**.

## Forbidden

Do not:

- add runtime state;
- add a new behavior branch;
- change return values;
- call into generic `CollisionDiagnostics::LogAttackCallbackOwnership()` with invented feature state;
- move raw55 identity policy into generic diagnostics;
- duplicate `ResolveExecution()`;
- generalize F1 / nested marker-callback risk into this task;
- implement speculative feature-owned activation scope;
- modify any release behavior.

## Suggested shape

A small feature-local diagnostic helper under:

```cpp
#ifdef FRAME_COLLISION_DIAGNOSTICS
...
#endif
```

called only when the already-computed `identityContradiction` is true at callback entry.

Prefer one single-line stable CORE record such as:

```text
CORE RAW55_PHYSICAL_FIST_IDENTITY_CONTRADICTION ...
```

Exact spelling is implementation-local provided the fact is compact and unambiguous.

## Validation

Work:

- source/static audit;
- `git diff --check`;
- publish;
- **do not build**.

Normal Chat + User after independent review:

```text
build Script_FrameCollisionTest Release
-> deploy
-> startup
-> small raw55 control
```

No special runtime reproduction of an identity contradiction is required for this correction before focused acceptance continues. The source contract is sufficient; ordinary controls must show no regression.

## Work build rule

**WORK BUILD EXECUTION IS PROHIBITED.**

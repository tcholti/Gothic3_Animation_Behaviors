# External Source References

**Purpose:** Durable routing for third-party Gothic 3 implementation/compatibility source used by this project.

Third-party source is a practical reference, not automatically native-engine authority. For native declarations prefer the pinned official SDK; for tested native behavior use project evidence/binary references as required by `docs/SOURCE_HOOK_GUIDE.md`.

## Jackydima Gothic 3 SDK / New Balance source

Upstream repository:

`https://github.com/Jackydima/gothic3sdk`

Local pinned reference:

`references/jackydima-gothic3sdk`

High-value source routes:

```text
scripts/Script_NewBalance/
    full New Balance DLL source
    speed behavior: FunctionHook.cpp -> GetAnimationSpeedModifier

scripts/Script_AttackCollision/
    full Script_AttackCollision DLL source

scripts/
    source for the other Jackydima-produced Gothic 3 script DLLs in the repository
```

Current reference pin recorded 2026-09-27:

`316d32406a133f8884e7e302752c35f66b4f54fc`

When a compatibility question depends on the current New Balance/Jackydima implementation, compare the pinned submodule revision with upstream `master` before drawing a current-source conclusion. Advance the pin deliberately when needed; do not silently assume the local reference and upstream `master` are identical.

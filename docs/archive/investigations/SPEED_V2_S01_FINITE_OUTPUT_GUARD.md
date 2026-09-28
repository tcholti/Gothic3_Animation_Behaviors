# Speed v2 S-01 Finite Output Guard — Closure

**Status:** CLOSED / SOURCE-REVIEW PASS  
**Opened:** 2026-09-28  
**Base HEAD:** `19eff2b8cab0f3d0db46f7f90f86fd8e4b1d8d18`  
**Implementation commit:** `db7b24f1a0c19beaaf4e720cd69d19c331854340`

## Responsibility

Correct only the MINOR S-01 finding from the deep independent Speed v2 static audit: a positive finite configured `BaseSpeed` could be large enough for the composed arithmetic result to become non-finite.

## Implemented correction

Only `src/Script_G3AnimationBehaviors/AttackSpeed.cpp` changed.

The existing expression is now materialized into `composedSpeed`; if `std::isfinite(composedSpeed)` is false, `ComposeCompatibleSpeed()` returns the already-computed live `compatibleSpeed` unchanged. Otherwise it returns `composedSpeed`.

No parser cap or arbitrary maximum was introduced.

## Focused source review

PASS.

Comparison from the audit-task HEAD to the implementation commit showed only:

- this bounded task document; and
- the one `AttackSpeed.cpp` arithmetic guard.

The implementation commit itself changed 6 lines added / 1 line removed in `AttackSpeed.cpp` and no other file.

Review conclusions:

- ordinary finite composition remains exactly `compatibleSpeed * (C / B)`;
- non-finite composition now fails closed to `compatibleSpeed`;
- the technical B facts are unchanged;
- profile parsing/schema/identity are unchanged;
- the six `EngineBridge` caller hooks are unchanged;
- the live `Script_Game+0x42A0` ownership/compatibility model is unchanged;
- collision source is unchanged;
- no diagnostics, state, caches or lifecycle machinery were added;
- no Raise behavior was added.

## Build/runtime status

Not attempted in this source-only correction.

## Disposition

- **S-01 CLOSED / SOURCE-REVIEW PASS.**
- Corrected Speed v2 source candidate: `db7b24f1a0c19beaaf4e720cd69d19c331854340`.
- Next gate: local production build -> deploy/hash -> startup/load -> New Balance runtime matrix -> native-only sanity/fallback.
- Speed remains open until runtime acceptance.
- Raise remains paused.

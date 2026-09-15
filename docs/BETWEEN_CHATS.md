# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.

**Updated:** 2026-09-15

## Current Bridge — EV-286 CLOSED; RAW55 NORMAL PRE-STATE CONTACT-REARM IMPLEMENTED + REVIEWED

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active branch: `docs/collision-source-evidence`  
Stable branch: `main`

Recovery Lock is **CLOSED**. Canonical evidence is through **EV-286**. No permanent raw55 implementation is authorized.

Current diagnostic authority:

`docs/COLLISION_RAW55_NORMAL_PRESTATE_REARM_PROBE.md`

Diagnostic implementation under validation:

`50db909b414eb821b536cd68baa75efbf5589c1b`

Normal Chat independently reviewed the implementation against required base `ecc05f29edbc2be36b4cbcd2402342b44cf4e534` and marked **SOURCE REVIEW PASS**.

Exactly one source file changed:

`prototypes/Script_FrameCollisionTest/PhysicalFistProbe.cpp`

The implementation preserves the EV-286 Normal SP0 path and changes exactly one causal variable: after the exact current RIGHT PhysicalFist/raw55 source is requested from group5 to group7 and `groupAfter == Item_Attack/group7` is verified, it calls `rightSource.TouchDamage.ClearTriggeredList()` once. The existing actor + C1 generation + exact RIGHT source intervention identity is recorded before the group request/rearm operation, so the same SP0 occurrence cannot re-enter and clear twice.

Logging truthfully reports `ClearTriggeredList` and `PRESTATE_REARM`. No later Normal marker rearm, StatePosition write, damage call, cleanup intervention, hook/RVA change, EngineBridge change, or CMake change was added.

## EV-286 — Previous runtime result

Canonical runtime:

`research/raw/2026.09.15_troll_raw55_normal_prestate_fist.log`

SHA256:

`5E081A79BCB39280A738C5FBA97E6C4FF4E5DCFB22479FA8D8C16407AA7EC349`

Upload commit:

`1f336c04173983428e5e95a348207040c2fe9a14`

Representative factual Normal C1s 19, 21 and 23 all repeat:

```text
frame-1 FIST at Action1 / NORMAL / StatePosition=0
RIGHT TrollFist/raw55 group5
-> exact RIGHT 5 -> 7
-> ClearTriggeredList=0
-> original _AI_Attack continues

around StateTime ~= 0.25:
    Gothic native 7 -> 7
    StatePosition 0 -> 1

frame-15 FIST later at SP1 while RIGHT remains group7
    no Normal repeat intervention

one later native ONDAMAGE
native 7 -> 5 cleanup
clean C1 finalization
```

Therefore frame-1 marker transport and physical opening pass; the remaining first-contact unknown is whether triggered-list rearm is sufficient for an early damaging opportunity.

## Local validation sequence

1. User syncs branch through GitHub Desktop and confirms Changes empty.
2. Build only `Script_FrameCollisionTest` Release.
3. Stop on build result.
4. If build passes, perform POP-03 deployment hash/twin verification.
5. Perform POP-04 startup banner check.
6. Run the same Troll two-FIST fixture and preserve the untouched raw log.

Preferred raw artifact:

`research/raw/2026.09.15_troll_raw55_normal_prestate_rearm.log`

Decisive interpretation:

- early `ONDAMAGE` before native `7 -> 7 / SP0 -> 1` => triggered-list rearm is the missing early-contact primitive;
- still no early damage until after native transition => another native Normal timing/state eligibility gate remains;
- any callback/lifecycle/cleanup divergence => stop and analyze, do not compensate.

The later frame-15 Normal FIST remains observational only in this probe.

## Remaining collision order

After this evidence transaction closes:

1. finish Normal early-contact eligibility if another native gate exists;
2. non-Quick repeated-FIST semantics;
3. Sprint same-C1 Action9 -> Action2 continuity within repeated-marker design;
4. permanent raw55 architecture and implementation;
5. standalone final collision regression;
6. New Balance 0.7 final bundle regression exactly as distributed, bundled AttackCollision active;
7. close collision module;
8. begin Raise / speed-control work.

New Balance 0.7 is not a current blocker. Existing combined runtime evidence remains EV-035/EV-150/EV-242, with corrected compatibility interpretation EV-285.

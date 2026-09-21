# Between Chats

**Purpose:** Short-lived exact continuation pointer. Replace, do not accumulate.  
**Updated:** 2026-09-21

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

## Frozen source

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Frozen collision source:
`f1f5d2aad3edc3564a9a8b40541840b94f8fa903`

Final diagnostic DLL SHA256:
`5AD5B33A8826DB5E78F4AECADC3FF48546E1C54ADA3BE9ED2BE9A54E6190E313`

Final behavior DLL SHA256:
`A806EC6523116286335A659735067B1AA6C581837B3E0D604E6271AC98079340`

No source change is authorized absent newly demonstrated contradictory evidence.

## Focused raw8 acceptance — after EV-359

Authority: `docs/COLLISION_RAW8_PRODUCTION_ARCHITECTURE.md` §14.

```text
1. Gargoyle close/delayed/no-contact    PARTIAL — close + delayed PASS EV-359; far/no-contact open
2. Human Normal + true Power            PASS — EV-359
3. Later FIST same C1 reopen            PASS — EV-359
4. Ordinary no-contact finalization     PASS — EV-359
5. Reaction/generation replacement      OPEN
6. Replacement -> unmarked fallback     OPEN
7. Unmarked human target-directed       OPEN on frozen source
8. Sprint Action9 -> Action2 transport  OPEN on frozen source
9. raw55 + equipped coexistence         PASS — EV-357
10. Diagnostic/behavior parity          PASS — EV-357 + EV-358
```

EV-359 key facts:
- Gargoyle: 7 POWER opportunities -> 7 contacts; delayed examples survived ~203 ms / 25 rearms and ~246 ms / 32 rearms.
- Human NORMAL: 23 opens -> 18 contacts + 5 C1 closes.
- Human POWER: 53 opens -> 29 contacts + 15 C1 closes + 9 first opportunities superseded by later FIST.
- 20 Power C1s had two FIST opens; 11 showed OPEN -> CONTACT -> later OPEN -> CONTACT.
- all 20 unused closes were C1_FINALIZED with latch 0->1 confirmed.
- zero contradiction/rejection/invariant/generation inconsistency/repair divergence/error.

## Next proof batch — diagnostic twin

Run POP-12 first. Keep the frozen diagnostic DLL deployed alone.

Freeze these filenames exactly:

### 1. Gargoyle true far/no-contact

`research/raw/2026-09-21_raw8_final_acceptance_gargoyle_frame3_far_no_contact.log`

Use the established frame-3 marked Power fixture.

Goal:
- allow FIST to open;
- remain or keep moving far enough away that the Gargoyle never reaches contact during that attack;
- let the whole attack/C1 finish naturally;
- repeat until at least several opportunities end by lifecycle close rather than contact.

This closes the missing portion of item 1.

### 2. Marked human reaction/replacement

`research/raw/2026-09-21_raw8_final_acceptance_human_reaction_replacement.log`

Reuse the EV-353 marked human group-combat style fixture.

Goal:
- open a marked raw8 FIST opportunity;
- while it is still pending, allow an opponent to interrupt/stumble/knock down/react the player so the attack generation is replaced;
- repeat enough times to obtain factual replacement closures;
- after replacement, watch for any old-opportunity contact before a new FIST. There should be none.

This targets item 5.

If the currently installed fixture provides a **known unmarked raw8 attack on the same player in the same session**, use that unmarked attack after a successful marked replacement and let it contact normally. That can also close item 6.

If no same-session unmarked human raw8 route exists, do not manufacture evidence in this run; item 6 remains open for one dedicated asset/control test after analysis.

### 3. Native unmarked human target-directed control

`research/raw/2026-09-21_raw8_final_acceptance_human_unmarked_target_control.log`

Reuse the established native/unmarked group-combat control from EV-352/EV-353:
- several opponents nearby/behind/between player and target;
- deliberately lock/switch between intended targets;
- no FIST marker ownership/opportunity records should appear;
- native raw8 contacts should remain limited to the intended/locked target route.

This closes item 7 on the frozen source and may provide the unmarked half of item 6 if a same-player replacement sequence can be arranged.

### 4. Sabretooth Sprint-origin transport

`research/raw/2026-09-21_raw8_final_acceptance_sabretooth_sprint_transport.log`

Use the established single-FIST marked native Sabretooth fixture.

Goal:
- run enough attacks to obtain factual Action9/SPRINT openings;
- decisive sample: the same opportunity ordinal/C1 remains live and is later consumed under Action2/POWER on the same PowerAttack-named motion;
- misses/rearms before the transition are welcome but not required.

This closes item 8 on the frozen source.

Multiple tests/logs may be uploaded together.

## Comprehensive release validation after focused acceptance

The User explicitly wants another systematic final-source campaign because prior broad passes repeatedly exposed missing routes/interactions. This is now part of the release-validation strategy, not optional extra testing.

After §14 closes, follow `COLLISION_TEST_PLAN.md` §3.8:

```text
A. animals/body-contact
   -> many fixtures, several logs per batch
   -> vary player weapons across animal tests

B. equipped coverage
   -> player + NPC/creature weapon matrices

C. modded/custom animations
   -> Axe/Rapier separation + fast/multi-contact authored animations

D. stress
   -> mixed actors, targets, weapons, families, C1 churn

E. New Balance + AttackCollision
   -> several exact-bundle compatibility tests, not one smoke
```

A broad failure must first be reduced to its smallest factual route before any source change is considered.

`research/raw/` should contain only `Keep.txt` before the next captures.

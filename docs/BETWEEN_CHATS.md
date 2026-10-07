# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-10-07 — ADR-0012 bad-block attack protection / Work delegation rule

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`

Stable release branch:
`main @ e899f37092706a9846312b93d6b52b34e715b53d`

Active branch:
`development`

## Stable baseline

Collision + Speed + Raise + Movement remain accepted.  
EV-447 stable promotion remains the release fallback.

## EV-448 remains valid, but its contract was too strong for the gameplay need

EV-448 proved:
- exact mathematical remaining-time pause is stateful and not clean enough for first release;
- player timeout seam is `Script_Game +0x633BF`;
- NPC Alternative-AI timeout is a separate `StateTime > 2.0` branch at `+0x46F39`.

Today the User clarified the actual gameplay requirement.

ADR-0012 accepted:

```text
Do not let block-timeout teardown destroy a live attack.

Exact remaining-time preservation is NOT required.

The native timer may continue advancing.
If it is already due, block skip may fire immediately after the attack has safely ended.
```

Reason:
the visible attack animation can continue after destructive bad skip while engine-side continuation has been lost. Collision guard correctly repairs stale collision, but the result can be a visually connected weapon with no normal hit/damage outcome.

## Active responsibility

`docs/work/active/BAD_BLOCK_SKIP_ATTACK_PROTECTION_OPTIONS.md`

Compare:
1. integrated player stateless deferral;
2. separate optional bad-block-skip patch DLL;
3. NPC-specific protection only if overlap is proven;
4. no-change fallback.

No implementation is frozen yet.

## Work delegation improvement

Project collaboration procedures were strengthened on 2026-10-07:

- bounded Work research is advisory unless decision closure is explicitly delegated;
- Work must distinguish impossible/contradicted from risky/imperfect;
- if the ideal contract fails but viable alternatives exist, preserve and compare them;
- a recommendation is not authority to abandon/defer a feature;
- task preflight should state acceptance criteria, acceptable approximations, optimization priority, decision authority and options required if the ideal fails.

This project-local lesson is a candidate for later promotion into CAM so other projects, including General-Animation-Helpers, can inherit it through a dedicated CAM maintenance pass.


## Research vehicle

User + Normal Chat selected a separate experimental DLL for all bad-block research:

```text
Script_G3AnimationBehaviors.dll
= protected production candidate
= no bad-block experimental hooks/state

Script_G3AB_BadBlockResearch.dll
= isolated research target
= tools/Script_G3AB_BadBlockResearch/
```

Current research DLL behavior:
- startup/unload log only;
- no hooks yet;
- removable without changing production behavior.

Initial runtime fixture when User returns to the authoritative build PC:

```text
Gothic 3 / CP + Alternative AI
+ Script_G3AB_BadBlockResearch.dll
- Script_G3AnimationBehaviors.dll
- Script_NewBalance.dll
```

Later compatibility fixtures add G3AB first, then New Balance.

Final product placement remains undecided:
- integrate proven minimum into G3AB;
- ship a cleaned optional bad-block DLL;
- discard research DLL.

# Between Chats

**Purpose:** Exact short-lived continuation bridge. Replace rather than accumulate chronology.  
**Updated:** 2026-09-20

> After an abrupt/max-context/unusable Chat, start at root `README.md`; this bridge is only a clue until POP-11 recovery verifies it.

## Current bridge

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Branch: `docs/collision-source-evidence`

Phase 4 remains paused at raw8 FIST authoring-semantics research. Latest completed evidence: **EV-350**. No active Work task.

Agreed author-facing target:

```text
FIST opens one target-directed native body-contact / hit opportunity
-> until native hit/contact resolution occurs, opportunity remains available
-> first native hit/contact resolution consumes it for that target
-> block / parry / immunity / reactions / HP damage remain Gothic/behavior-owned
-> later FIST rearms it
-> C1 / Hit replacement or interruption closes any unused opportunity
```

Terminology discipline:
- **opportunity** = the authored logical OPEN/CLOSED/rearmed state;
- **collision/contact** = actual native physical/contact resolution;
- **native hit/contact-resolution boundary** = factual Gothic boundary under research;
- **damage** = reserve for literal Gothic API names/log labels or gameplay HP result, not collision ownership.

## EV-347–EV-350

- EV-347: native raw8 one-shot attempt closes the latch on both hit and miss.
- EV-348: temporary post-miss latch rearm restored later native opportunity.
- EV-349: Parade showed native contact-path resolution may occur with zero visible damage; temporary rearm also exposed cross-C1 lifetime leakage.
- Collision-vs-damage audit: permanent collision behavior remained policy-neutral; drift was confined to research terminology / closed diagnostic probes.
- EV-350: retired `Raw8FistWindowProbe` + EV-347 post-attempt OnDamage-counting instrumentation. Both twins built. Diagnostic deployment/startup PASS. Optional five-attack frame-3 Gargoyle control returned to one-shot baseline:
  - C1 22 + 29 -> immediate `Game+0x16E348` native contact-path entries;
  - C1 7 + 13 + 17 -> no later contact-path entry;
  - no retired probe records;
  - generic `CORE ONDAMAGE` observer retained.

Current diagnostic DLL SHA256:
`C33046D1AE139B5D905CF5E1004F725F07A5FE8CAC3A9705F11691497D7CD17D`.

Latest canonical log:
`research/archive/2026-09-20_observation_gargoyle_marker_frame_3_test_4.log`  
Git blob `06d1e22353f017f536d1c8c2d039e5fe34fd1e0b`.

## Current stop gate

Run:

```text
python tools/knowledge/validate_knowledge_state.py
```

Require:

```text
Knowledge-state validation PASS
```

Do not freeze or launch the next causal task before that PASS.

After PASS, Normal Chat should reason from the neutral baseline and freeze only the smallest next question:

> What is the smallest factual native hit/contact-resolution boundary that can consume an authored raw8 opportunity independently of block/immunity/reaction/HP-damage policy, while any unused opportunity is forcibly bounded to the exact Hit/C1 lifetime?

`research/raw/` should contain only `Keep.txt`.

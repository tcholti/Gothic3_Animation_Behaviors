# Between Chats

**Purpose:** exact continuation pointer; replace, do not accumulate.  
**Updated:** 2026-09-27

> After abrupt/max-context recovery, start at root `README.md` and apply POP-11 before trusting this bridge.

Repository: `tcholti/Gothic3_Animation_Behaviors`  
Active: `development`  
Stable: `main` — keep frozen until Speed + Raise + assembled regression close.

## State

```text
EV-390 collision production integration = CLOSED/PASS
ADR-0007 shared Speed/Raise schema = ACCEPTED
BehaviorProfiles foundation = PASS
implementation = 81d4964201579c9f7a989404426c3d9dc9ab4834
EV-391 Speed v2 caller-side composition static evidence = RECORDED
CURRENT = Speed v2 mechanism research/design ONLY
RAISE = PAUSED until Speed closes
```

`docs/work/active/` is clean.

## Speed v2 handoff

Required invariant:

```text
unconfigured = B * M
configured   = C * M
```

`C` is configured authored base; legitimate Gothic/New Balance modifiers `M` must remain effective. Configured Normal/Quick uses `1.0` as the intended neutral authored reference; native/NB `0.6`/`0.7` Normal values are technical base facts, not desired G3AB defaults.

EV-391 statically proves a narrower post-policy/pre-playback composition class outside competing `+0x42A0` ownership:

```text
exact target caller
-> invoke LIVE Script_Game+0x42A0       # NB computes B*M
-> exact configured profile: * (C/B)
-> C*M
-> existing downstream path
```

Direct Hit-consumer proof:

```text
Script_Game+0x383F0  Action1 / Attack / Normal
Script_Game+0x48677  PropertyAction after explicit Action4/5 / Quick R/L
```

Nearby dynamic Hit callers (`+0x38A8B`, `+0x38E9D`, `+0x38F22`, `+0x3937D`, `+0x39402`) preserve action context and support the same intervention class. Prefer targeted caller-side thunk/call redirection; do not hook all `StartPlayAni*` calls and do not compete for `+0x42A0` ownership.

Existing evidence plus pinned New Balance source already supplies the first intended base groups (`0.6`, `0.7`, `1.0`), so **do not request another native-speed logger run now**.

Open static gap: ADR-0007 Quick includes Action3/4/5. Action4/5 provenance is proven; generic `gEAction_QuickAttack` / Action3 is not yet closed. The production call-site list is therefore not frozen.

Primary runtime compatibility stack remains:

```text
Script_G3AnimationBehaviors.dll
Script_NewBalance.dll
Script_AttackCollision.dll
```

## Next route

```text
1. trace generic QuickAttack / Action3 into the dynamic combat consumer family
2. close exact Normal+Quick Hit consumer-callsite set
3. verify entity + exact action/profile identity survives at each selected site
4. if static proof fails, freeze only the smallest diagnostics-only probe
5. then freeze bounded Speed v2 implementation
6. validate New Balance composition first; native-only sanity later
7. close Speed before any Raise work
```

Authorities: ADR-0004, ADR-0007, `SESSION_ENTRYPOINT.md`, EV-391, `DESIGN.md` §§2–3, `SOURCE_HOOK_GUIDE.md`.

Hard exclusions: final-result replacement; same-hook load-order dependency; copied NB multiplier policy; global speed override; stamina bypass; Raise work; collision redesign.

# Gothic 3 Animation Behaviors — Speed Control Architecture

**Status:** Current design constraints / research baseline — implementation redesign pending  
**Updated:** 2026-09-26  
**Owner:** future attack playback-speed control

## Purpose

Define the current non-negotiable behavior semantics and research baseline for the future speed-control redesign.

This document does **not** freeze a hook, implementation formula, INI syntax, or current-New-Balance binary interpretation. Collision remains the active engineering gate; speed work is paused until deliberately reopened.

Decision rationale: `decisions/ADR-0004-speed-control-base-speed-preserves-dynamic-modifiers.md`.  
Practical hook lookup: `SOURCE_HOOK_GUIDE.md`.

---

## 1. Established runtime baseline

The earlier standalone speed-control investigation directly observed native Gothic playback-speed values on the tested human attack routes:

```text
1H Normal / Action1 Hit        = 0.600
QuickAttackL / Action5 Hit     = 1.000
PowerAttack / Action2 Raise    = 1.500
PowerAttack / Action2 Hit      = 1.000
2H Normal Raise                = 1.000
2H Normal Hit                  = 0.700
```

These specific values are runtime observations, not guesses derived from New Balance source.

Do not generalize this table to every weapon/action/phase until directly measured. In particular, matching values later seen in third-party source are useful corroboration but do not automatically prove every listed family has the same native value.

---

## 2. Known flaw in the current prototype

The current/first G3AB speed-control approach can replace the effective animation speed too late in the calculation.

Observed gameplay consequence:

```text
native attack + depleted stamina
-> Gothic slows the attack

G3AB-configured attack + depleted stamina
-> configured attack can keep the configured speed
-> native stamina slowdown is bypassed
```

Therefore a configured speed must **not** mean "force this final playback speed regardless of later game state".

This is a correctness issue even without New Balance.

---

## 3. Required future semantics

A G3AB speed definition is a **base-speed authority**, not final effective-speed authority.

Conceptually:

```text
native/action/phase base
        ↓
G3AB configured base choice or base adjustment
        ↓
applicable native + mod dynamic modifiers
        ↓
effective playback speed
```

The exact mathematical order and intervention point are deliberately **not frozen yet**. Research must first establish where Gothic and New Balance apply their dynamic modifiers.

Required invariant:

> If the same contextual multiplier would affect an otherwise equivalent unconfigured attack, it must also affect a G3AB-configured attack unless a future explicit feature deliberately owns that multiplier.

Examples that must remain composable where applicable include:

```text
Gothic stamina / exhaustion slowdown
New Balance arena/NPC modifiers
New Balance species/action modifiers such as Troll/ Sprint behavior
New Balance perk/skill-related speed modifiers
other proven contextual multipliers discovered during research
```

The user-configured value must not silently erase these systems.

---

## 4. New Balance compatibility implication

New Balance publicly hooks the same general animation-speed domain used by the first G3AB prototype. Several base values visible in that source correspond to values already measured natively by our earlier runtime investigation, including tested 1H Normal `0.6`, Quick `1.0`, Power phase values, and 2H Normal Hit `0.7`.

This supports treating those values as base/action-speed inputs rather than describing them as arbitrary global slowdowns.

What remains open:

```text
exact current distributed New Balance binary behavior
exact ordering of its base selection vs dynamic multipliers
whether a safe compositional hook can run before/after its calculation
whether another lower-level or higher-level native surface is preferable
```

Do not solve compatibility through arbitrary DLL load order, competing same-function hooks, or a New-Balance-version special case unless evidence leaves no cleaner native composition point.

---

## 5. Recover rule

Recover follows the **effective Hit speed**. No separate user-facing `RecoverSpeed` key is currently planned.

The future implementation must preserve that rule without converting Recover into an independent final-speed override.

---

## 6. Research required before redesign

Before freezing speed-control v2 architecture, collect at minimum:

```text
A. standalone Gothic
   - representative 1H / 2H / Staff/Axe families
   - relevant Raise / Hit / Recover observations
   - full-stamina vs depleted-stamina comparisons

B. current intended New Balance stack
   - same representative attacks
   - exact effective/base values at the candidate hook surfaces
   - Troll/Sprint and other known New Balance modifiers
   - arena/skill/perk modifiers where practical

C. composition tests
   - configured attack at full stamina
   - same configured attack at depleted stamina
   - configured attack under New Balance modifier conditions
   - unconfigured native controls
```

The causal question is not merely "can G3AB set a speed?" It is:

> **Where can G3AB author the intended base speed while leaving the game's and compatible mods' legitimate dynamic multiplier chain intact?**

---

## 7. Hard exclusions before evidence

Do not freeze or implement yet:

```text
final-speed replacement as the intended architecture
same-hook load-order dependency
New Balance DLL/version detection as the primary design
hard-coded copies of every New Balance multiplier
global animation-speed override
stamina bypass
unverified per-family constants
```

Speed work remains paused until the current collision compatibility gate closes and the User deliberately reopens this responsibility.

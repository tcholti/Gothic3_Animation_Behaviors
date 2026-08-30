# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — C1-O2-P2-C targeted meaning test

C1-O2-P2 behavior implementation:

```text
cc51c67c19425be4e4d6a4838803ed3e66b2a071
```

P2 build-identity banner correction:

```text
8b6a5873b8caa27b469ae831d25bf155a6c7f189
```

Independent Normal Chat P2-A source audit: **PASS**.

Validated P2 built/live DLL:

```text
Script_FrameCollisionTest.dll
Length: 465408
SHA256: 1081B287912DB9A368164DDE13542A7EC2D6E5DBB0AA29B04C19BD7932D92C7C
Built/live match: True
```

P2-B isolated main-menu load/unload: **PASS**.

Canonical active raw:

```text
research/raw/2026-08-30_c1o2p2_lazy_precombat_bridge_isolated_load.log
```

The committed log contains the exact P2 startup identity, `Installing hooks...`, `Hooks installed.`, and normal `Script_FrameCollisionTest unloading.`

Older processed collision logs were moved byte-for-byte from `research/raw/` to `research/archive/` at:

```text
20302dbf97cb59d52824a8496bc548122d040f1b
```

`research/raw/` now contains only `Keep.txt` and the active P2 evidence.

---

## Current responsibility — P2-C

Run only the targeted player 2H Normal + GetUpAttack meaning test.

Purpose:

> Prove or falsify that the legitimate early GetUp offense now acquires one C1 generation, the matching CombatMove reuses that same generation and consumes the temporary native-frame bridge before wrapper return, while later offense/cleanup remain owned by the durable generation and physical repair stays disabled.

Test sequence:

1. synchronize the current active branch before adding the new raw artifact;
2. keep the currently validated P2 DLL deployed unless source/DLL identity changes;
3. enter gameplay with the player using 2H;
4. perform several ordinary clean 2H Normal attacks as controls;
5. deliberately reproduce the player 2H GetUpAttack path several times, using the same controlled GetUpAttack method used for P1-C;
6. do not deliberately add the held-Use2 stale-collision stress, marker-window tests, or broad mixed-gameplay coverage in this gate;
7. exit Gothic 3 normally;
8. preserve the complete runtime log byte-faithfully as:

```text
research/raw/2026-08-30_c1o2p2_player_2h_normal_getup_bridge_consumption.log
```

### P2-C expected positive meaning

For each legitimate initial GetUp offense:

```text
PRECOMBAT_ACQUIRED
→ C1 OFFENSE REQUEST on that generation
→ matching CombatMove uses SAME generation
→ PRECOMBAT_BRIDGE_CONSUMED
→ no PRECOMBAT_BRIDGE_UNCONSUMED_AT_DISPATCH_RETURN for that positive path
→ no UNOWNED_PLAYER_OFFENSE_REQUEST for that initial GetUp offense
→ later timer offense remains attributed to the durable generation
→ native cleanup fulfills the same generation/source obligation
```

Representative ordinary 2H Normal controls must remain on the ordinary CombatMove-created generation path; they do not require a live RunScriptFunction scope at timer offense.

Physical repair remains disabled throughout.

STOP interpretation and return to Normal Chat if the run crashes, a positive GetUp bridge reaches wrapper return unconsumed, matching CombatMove creates/replaces a different generation, or another new invariant appears.

Do not authorize extended P2 stability testing until P2-C establishes the intended meaning.
# Between Chats

**Purpose:** Small transient bridge between Normal Chat and Work/local execution. Replace rather than accumulate chronology.

## Current bridge — C1-O2-P2-B build / isolated load

C1-O2-P2 implementation is published at:

```text
cc51c67c19425be4e4d6a4838803ed3e66b2a071
```

Independent Normal Chat P2-A source audit: **PASS**.

The implementation:

```text
real successful equipped-source pre-Combat offense inside the proven P1 live scope
→ lazily validate live SPU/runtime-stack/ScriptFunction frame
→ acquire the existing monotonic C1 generation
→ record the real source obligation
→ matching CombatMove in the same live frame reuses that generation
→ consume/retire temporary native-frame binding immediately
→ durable C1 generation/source ownership continues
```

If a temporary bridge reaches `RunScriptFunction` return unconsumed, P2 logs the invariant and retires the native binding without dropping the real source obligation. The old dispatch-vector / Begin-End machinery remains disconnected. Physical repair remains OFF.

### Source-review qualification

The P2 behavior source passed review, but the implementation commit retained only the P1 startup banner. Normal Chat identified this as a mechanical build-identity omission, not an architectural contradiction.

Before local P2-B validation, the source must contain an explicit P2 startup line:

```text
STEP C1-O2-P2 LAZY PRE-COMBAT BRIDGE: event-driven pre-Combat generation acquisition; matching CombatMove consumes temporary binding; shadow-only; no physical repair.
```

The final banner-correction commit, rather than `cc51...` alone, is the source identity to build for P2-B.

---

## P2-B responsibility

After the banner correction is committed:

```text
sync active branch
→ build Script_FrameCollisionTest
→ deploy exact built DLL
→ verify exactly one intended live DLL and built/live SHA256 equality
→ launch only far enough for normal script load/main menu
→ exit normally
→ require the exact P2 startup banner
→ preserve the complete produced log under the frozen raw filename
```

No combat is required for P2-B.

Do not begin P2-C until P2-B passes.

### P2-C after P2-B

The next targeted meaning test will use ordinary 2H attacks as controls plus deliberate GetUpAttack reproductions. It will check that the first legitimate GetUp offense is no longer unowned, that `PRECOMBAT_ACQUIRED` and `PRECOMBAT_BRIDGE_CONSUMED` use the same C1 generation, that no unconsumed-bridge invariant occurs for the positive path, and that later timer offense/native cleanup remain attributed to the durable generation.

Physical repair remains disabled throughout.

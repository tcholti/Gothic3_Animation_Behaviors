# Shared Profile Configuration Foundation

**Status:** CLOSED / IMPLEMENTED / ARCHIVED  
**Implementation:** `81d4964201579c9f7a989404426c3d9dc9ab4834`  
**Independent Normal Chat source review:** PASS  
**Original task class:** Bounded production implementation / source-only  
**Repository:** `tcholti/Gothic3_Animation_Behaviors`  
**Branch:** `development`  
**Build/run in Work:** PROHIBITED

> Archived after successful bounded implementation and independent source review. The frozen responsibility below is preserved as the implementation contract.

## 1. Responsibility

Implement only the shared startup-loaded configuration/profile foundation frozen by ADR-0007 so later Speed and Raise modules can consume one normalized in-memory profile table.

This task does **not** implement Speed behavior and does **not** implement Raise behavior.

The production collision subsystem accepted through EV-390 is protected and must remain behaviorally untouched.

## 2. Read first

1. `docs/SESSION_ENTRYPOINT.md`
2. `docs/BETWEEN_CHATS.md`
3. this file
4. `docs/WORK_IMPLEMENTATION_PROTOCOL.md`
5. `docs/decisions/ADR-0007-shared-ini-profile-schema.md`
6. `docs/decisions/ADR-0005-raise-speed-config-profiles.md`
7. `docs/ANIMATION_RULES.md` §§2–5 only as profile-token semantics
8. `src/Script_G3AnimationBehaviors/CMakeLists.txt`
9. `src/Script_G3AnimationBehaviors/Script_G3AnimationBehaviors.cpp`
10. legacy `src/Script_G3AnimationBehaviors/SharedConfig.cpp/.h` and `Ini/G3AnimationBehaviors.ini` only as historical prototype reference
11. pinned SDK declaration `thirdparty/gothic3sdk/g3/Engine/include/g3sdk/Engine/io/file/ge_configfile.h`
12. pinned SDK section/key declarations only if required to implement enumeration

Do not broaden into Speed hook research, New Balance speed logic, Raise hooks, collision evidence, or unrelated architecture.

## 3. Frozen configuration contract

Profile sections are discovered generically by section-name prefix:

```text
Profile.
```

The suffix is a unique author label only and must not be parsed as runtime identity.

Mandatory identity keys:

```text
AnimationFamily
LeftAnimationUseType
RightAnimationUseType
ActionProfile
```

Profile identity:

```text
AnimationFamily
+ LeftAnimationUseType
+ RightAnimationUseType
+ ActionProfile
```

`ActionProfile` accepts only:

```text
Normal
Quick
```

Optional feature keys:

```text
BaseSpeed=<positive finite float>
Raise=Native|On
```

Semantics:

```text
BaseSpeed absent -> no Speed override
BaseSpeed=1.00 -> explicit configured value, not absence
Raise absent or Native -> native/no G3AB Raise override
Raise=On -> future Raise request stored only; NO Raise behavior in this task
```

No `Raise=Off` behavior is authorized.

## 4. Required production module

Create a small general production module under:

```text
src/Script_G3AnimationBehaviors/
```

Preferred responsibility/name:

```text
BehaviorProfiles.cpp
BehaviorProfiles.h
```

The module owns:

```text
profile data types
startup INI loading
generic Profile.* section enumeration
identity-field parsing
stable string normalization for profile matching
Normal/Quick ActionProfile parsing
optional BaseSpeed presence/value
future Raise mode storage only
duplicate-identity ambiguity handling
immutable/read-only lookup surface after startup
```

It owns no Gothic hooks and no feature behavior.

### 4.1 Suggested public shape

Exact private implementation is flexible, but public responsibility should remain equivalent to:

```cpp
namespace G3AB::BehaviorProfiles
{
enum class ActionProfile
{
    Normal,
    Quick
};

enum class RaiseMode
{
    Native,
    On
};

struct ProfileKey
{
    std::string animationFamily;
    std::string leftAnimationUseType;
    std::string rightAnimationUseType;
    ActionProfile actionProfile;
};

struct Profile
{
    ProfileKey key;
    bool hasBaseSpeed;
    float baseSpeed;
    RaiseMode raiseMode;
};

void Load();
Profile const *Find(ProfileKey const &key);
}
```

Names may vary only where a concrete SDK/C++ reason improves clarity. Do not add feature-specific subclasses or weapon-specific structures.

## 5. String normalization boundary

This task must make profile-key string comparison stable and independent of author capitalization/outer whitespace.

At minimum, identity strings used in the in-memory key should be:

```text
trimmed
case-normalized for comparison
```

Preserve the semantic distinction among different tokens; do not infer weapon aliases from names in this task.

Important boundary:

- ADR-0007 says config UseType values are normalized animation-token semantics.
- This task does **not** yet know the final Speed runtime intervention point and therefore must not invent a raw-`gEUseType` runtime mapping or hook-dependent extractor.
- Later Speed work supplies factual runtime family/left/right/action values to the same key-normalization API.
- A non-empty author token that never corresponds to a factual runtime-normalized token simply cannot match and therefore cannot broaden behavior.

Do not create 1H/2H/Axe/Staff behavior branches.

## 6. Duplicate and malformed handling

### Mandatory identity

A `Profile.*` section with any missing/empty mandatory identity field or unsupported `ActionProfile` is not inserted into the active table.

### Duplicate normalized identity

If more than one `Profile.*` section normalizes to the same exact `ProfileKey`:

```text
mark that identity ambiguous
remove/do not activate any override for that identity
never use first-wins or last-wins behavior
```

INI order must not control runtime behavior.

### BaseSpeed

```text
key absent -> hasBaseSpeed=false
valid positive finite float -> hasBaseSpeed=true, preserve exact configured float
invalid / zero / negative / non-finite -> hasBaseSpeed=false
```

Do not use `1.0` as a missing-value sentinel.

### Raise

```text
key absent -> Native
Native -> Native
On -> On
anything else -> Native
```

Parsing/storing `On` does not authorize any Raise hook or intervention.

### Unknown keys

Ignore unknown non-owned keys for forward compatibility.

No research/diagnostic logging framework is added by this task. A tiny production-safe startup warning mechanism is optional only if already available without new hooks/files; otherwise omit warnings rather than broadening.

## 7. Startup loading

Use the already proven Gothic config surface:

```text
eCConfigFile
ReadFile
GetSections / section enumeration
Contains / GetString / GetFloat or equivalent safe value retrieval
```

Expected INI path remains:

```text
GetGothic3Path() + "Ini\\G3AnimationBehaviors.ini"
```

Production `ScriptInit` must load profiles exactly once before future feature consumers could use them and before hook installation completes.

Preferred startup order:

```text
RuntimeClock::InitializeClock()
BehaviorProfiles::Load()
EngineBridge::InstallHooks()
return script init
```

A missing/unreadable INI must result in an empty profile table and must not prevent collision hooks or DLL startup.

## 8. Default INI template

Replace the obsolete active 2H prototype settings in:

```text
src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini
```

with a concise commented ADR-0007 template.

The shipped/default file must be behavior-neutral: no active `BaseSpeed` or `Raise=On` profile should alter gameplay merely because the file is installed.

Show commented examples for at least:

```text
Hero + None + 1H + Normal
Hero + None + 1H + Quick
Hero + Torch + 1H + Normal
```

Use `BaseSpeed` and future `Raise=Native|On` terminology exactly.

## 9. Build integration

Update only the production CMake target as required to compile the new shared module.

Do not re-add:

```text
AttackSpeed.cpp
AttackRaise.cpp
SharedConfig.cpp
```

The legacy files remain physically untouched unless the obsolete INI template itself is being replaced as authorized above.

Do not modify prototype collision targets.

## 10. Protected collision boundary

Do not modify any accepted collision behavior source:

```text
AttackMotionRouting.*
CollisionLifecycleGuard.*
CollisionSourceOperations.*
CollisionSources.*
EngineBridge.*
EquippedSprintCollision.*
FrameCollisionMarkers.*
FrameCollisionShared.h
PhysicalFistCollision.*
Raw8FistCollision.*
RuntimeClock.*
```

Exception: `Script_G3AnimationBehaviors.cpp` may add only the one startup call required to load profiles. `RuntimeClock` implementation itself remains untouched.

No hook address, marker semantic, raw8/raw55 behavior, C1 behavior, Hack routing, Sprint behavior or collision lifecycle logic may change.

## 11. Explicit exclusions

Do NOT:

```text
implement or hook Speed
research/modify GetAnimationSpeedModifier
copy New Balance speed logic
implement Raise behavior
install PS_Melee_Attack Raise hooks
modify EngineBridge
add weapon-specific policy
add P0/P1/P2/P3 config dimensions
add Power/Pierce/Hack/etc. user-facing Speed/Raise profiles
add reload/hot-reload/polling
add config reads per attack
add diagnostic logging infrastructure
add AttackContinuationProtection
touch targeting/climbing
modify main
```

## 12. Allowed files

Implementation edits are limited to:

```text
src/Script_G3AnimationBehaviors/BehaviorProfiles.cpp      [new]
src/Script_G3AnimationBehaviors/BehaviorProfiles.h        [new]
src/Script_G3AnimationBehaviors/CMakeLists.txt
src/Script_G3AnimationBehaviors/Script_G3AnimationBehaviors.cpp
src/Script_G3AnimationBehaviors/Ini/G3AnimationBehaviors.ini
```

If a concrete compile dependency requires another file, STOP and report rather than broadening.

## 13. Required static audit

Before publication verify:

1. Only §12 files changed/added.
2. No collision behavior file changed.
3. No Speed or Raise hook/behavior was added.
4. `BehaviorProfiles` has no physical hook ownership.
5. INI is read only by startup `Load()`, not by runtime lookup.
6. Missing INI naturally leaves an empty table.
7. `BaseSpeed=1.0` remains distinguishable from absence.
8. duplicate normalized profile identity cannot become order-dependent first/last-wins.
9. only Normal/Quick ActionProfile parses as valid.
10. production CMake contains the new module and still excludes legacy `AttackSpeed`, `AttackRaise`, `SharedConfig`.
11. default INI is behavior-neutral.
12. `git diff --check` PASS.

Do not build or run.

## 14. Stop conditions

STOP if:

- implementation requires a new engine hook;
- runtime UseType/family extraction must be decided to make the config table compile;
- exact SDK API differs materially from the frozen contract;
- config loading requires modifying collision modules;
- Speed or Raise behavior becomes necessary;
- files outside §12 must change;
- malformed/duplicate handling cannot be implemented without a new architectural choice.

## 15. Publication and handoff

Publication was authorized to `development`. Work reported completion at implementation SHA `81d4964201579c9f7a989404426c3d9dc9ab4834`; Normal Chat independently reviewed and accepted the implementation before archival.
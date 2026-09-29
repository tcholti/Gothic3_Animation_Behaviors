#pragma once

#include <g3sdk/Script.h>

#include <string>

namespace G3AB::BehaviorProfiles
{
enum class AttackType
{
    Normal,
    Quick,
    Power,
    Pierce,
    Hack,
    SimpleWhirl,
    Whirl
};

enum class RaiseOverride
{
    Off,
    On
};

struct ProfileKey
{
    std::string animationFamily;
    std::string leftAnimationUseType;
    std::string rightAnimationUseType;
};

struct AttackSettings
{
    bool hasReferenceHitBaseSpeed;
    float referenceHitBaseSpeed;
    bool hasBaseSpeed;
    float baseSpeed;
    RaiseOverride raiseOverride;
};

struct Profile
{
    ProfileKey key;
    AttackSettings normal;
    AttackSettings quick;
    AttackSettings power;
    AttackSettings pierce;
    AttackSettings hack;
    AttackSettings simpleWhirl;
    AttackSettings whirl;
};

void Load();
Profile const *Find(ProfileKey const &key);
AttackSettings const *GetAttackSettings(Profile const &profile, AttackType attackType);
bool TryBuildRuntimeKey(Entity const &entity, ProfileKey &key);
}

#pragma once

#include <g3sdk/Script.h>

#include <string>

namespace G3AB::BehaviorProfiles
{
enum class ActionProfile
{
    Normal,
    Quick
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
    ActionProfile actionProfile;
};

struct Profile
{
    ProfileKey key;
    bool hasReferenceHitBaseSpeed;
    float referenceHitBaseSpeed;
    bool hasBaseSpeed;
    float baseSpeed;
    bool hasReferenceRaiseBaseSpeed;
    float referenceRaiseBaseSpeed;
    RaiseOverride raiseOverride;
};

void Load();
Profile const *Find(ProfileKey const &key);
bool TryBuildRuntimeKey(
    Entity const &entity,
    ActionProfile actionProfile,
    ProfileKey &key,
    gEUseType &rawLeftUseType,
    gEUseType &rawRightUseType);
}

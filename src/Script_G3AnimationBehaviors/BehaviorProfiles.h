#pragma once

#include <string>

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

#include "BehaviorProfiles.h"

#include <g3sdk/Engine/io/file/ge_configfile.h>

#include <windows.h>

#include <cmath>
#include <cstdlib>
#include <map>
#include <set>
#include <string>
#include <tuple>

namespace G3AB::BehaviorProfiles
{
namespace
{
struct ProfileKeyLess
{
    bool operator()(ProfileKey const &left, ProfileKey const &right) const
    {
        return std::tie(
                   left.animationFamily,
                   left.leftAnimationUseType,
                   left.rightAnimationUseType,
                   left.actionProfile)
            < std::tie(
                   right.animationFamily,
                   right.leftAnimationUseType,
                   right.rightAnimationUseType,
                   right.actionProfile);
    }
};

using ProfileMap = std::map<ProfileKey, Profile, ProfileKeyLess>;
using AmbiguousKeySet = std::set<ProfileKey, ProfileKeyLess>;

ProfileMap g_Profiles;
AmbiguousKeySet g_AmbiguousKeys;
bool g_LoadAttempted = false;

bool IsOuterWhitespace(char value)
{
    return value == ' ' || value == '\t' || value == '\r'
        || value == '\n' || value == '\f' || value == '\v';
}

std::string NormalizeIdentityString(char const *text)
{
    std::string result = text != nullptr ? text : "";
    std::string::size_type begin = 0;
    while (begin < result.size() && IsOuterWhitespace(result[begin]))
        ++begin;

    std::string::size_type end = result.size();
    while (end > begin && IsOuterWhitespace(result[end - 1]))
        --end;

    result = result.substr(begin, end - begin);
    for (char &value : result)
    {
        if (value >= 'A' && value <= 'Z')
            value = static_cast<char>(value + ('a' - 'A'));
    }
    return result;
}

ProfileKey NormalizeKey(ProfileKey const &key)
{
    ProfileKey normalized = key;
    normalized.animationFamily =
        NormalizeIdentityString(key.animationFamily.c_str());
    normalized.leftAnimationUseType =
        NormalizeIdentityString(key.leftAnimationUseType.c_str());
    normalized.rightAnimationUseType =
        NormalizeIdentityString(key.rightAnimationUseType.c_str());
    return normalized;
}

std::string GetGothic3Path()
{
    char path[MAX_PATH] = {};
    DWORD const length = ::GetModuleFileNameA(nullptr, path, MAX_PATH);
    if (length == 0 || length >= MAX_PATH)
        return std::string();

    std::string result(path, length);
    std::string::size_type const separator = result.find_last_of("\\/");
    if (separator == std::string::npos)
        return std::string();

    result.resize(separator + 1);
    return result;
}

bool ReadIdentityString(
    eCConfigFile const &config,
    bCString const &section,
    char const *key,
    std::string &result)
{
    bCString const keyName(key);
    if (!config.Contains(section, keyName))
        return false;

    result = NormalizeIdentityString(config.GetString(section, keyName).GetText());
    return !result.empty();
}

bool ParseActionProfile(std::string const &value, ActionProfile &result)
{
    if (value == "normal")
    {
        result = ActionProfile::Normal;
        return true;
    }
    if (value == "quick")
    {
        result = ActionProfile::Quick;
        return true;
    }
    return false;
}

bool ParsePositiveFiniteFloat(char const *text, float &result)
{
    std::string const value = NormalizeIdentityString(text);
    if (value.empty())
        return false;

    char *end = nullptr;
    float const parsed = std::strtof(value.c_str(), &end);
    if (end == value.c_str() || *end != '\0')
        return false;
    if (!(parsed > 0.0f) || !std::isfinite(parsed))
        return false;

    result = parsed;
    return true;
}

Profile ParseOptionalValues(
    eCConfigFile const &config,
    bCString const &section,
    ProfileKey const &key)
{
    Profile profile = {key, false, 0.0f, RaiseMode::Native};

    bCString const baseSpeedKey("BaseSpeed");
    if (config.Contains(section, baseSpeedKey))
    {
        float baseSpeed = 0.0f;
        if (ParsePositiveFiniteFloat(
                config.GetString(section, baseSpeedKey).GetText(),
                baseSpeed))
        {
            profile.hasBaseSpeed = true;
            profile.baseSpeed = baseSpeed;
        }
    }

    bCString const raiseKey("Raise");
    if (config.Contains(section, raiseKey))
    {
        std::string const raise = NormalizeIdentityString(
            config.GetString(section, raiseKey).GetText());
        if (raise == "on")
            profile.raiseMode = RaiseMode::On;
    }

    return profile;
}

bool ParseProfileKey(
    eCConfigFile const &config,
    bCString const &section,
    ProfileKey &result)
{
    std::string actionProfile;
    if (!ReadIdentityString(
            config,
            section,
            "AnimationFamily",
            result.animationFamily)
        || !ReadIdentityString(
            config,
            section,
            "LeftAnimationUseType",
            result.leftAnimationUseType)
        || !ReadIdentityString(
            config,
            section,
            "RightAnimationUseType",
            result.rightAnimationUseType)
        || !ReadIdentityString(
            config,
            section,
            "ActionProfile",
            actionProfile))
    {
        return false;
    }

    return ParseActionProfile(actionProfile, result.actionProfile);
}

void InsertProfile(Profile const &profile)
{
    if (g_AmbiguousKeys.find(profile.key) != g_AmbiguousKeys.end())
        return;

    auto const inserted = g_Profiles.emplace(profile.key, profile);
    if (inserted.second)
        return;

    g_Profiles.erase(inserted.first);
    g_AmbiguousKeys.insert(profile.key);
}
}

void Load()
{
    if (g_LoadAttempted)
        return;
    g_LoadAttempted = true;

    g_Profiles.clear();
    g_AmbiguousKeys.clear();

    std::string const gothic3Path = GetGothic3Path();
    if (gothic3Path.empty())
        return;

    std::string const iniPath =
        gothic3Path + "Ini\\G3AnimationBehaviors.ini";
    eCConfigFile config;
    if (!config.ReadFile(bCString(iniPath.c_str())))
        return;

    bTObjArray<bCString> sections;
    if (!config.GetSections(sections))
        return;

    for (GEInt index = 0; index < sections.GetCount(); ++index)
    {
        bCString const &section = sections[index];
        char const *sectionText = section.GetText();
        if (sectionText == nullptr)
            continue;

        std::string const sectionName(sectionText);
        if (sectionName.compare(0, 8, "Profile.") != 0)
            continue;

        ProfileKey key;
        if (!ParseProfileKey(config, section, key))
            continue;

        InsertProfile(ParseOptionalValues(config, section, key));
    }
}

Profile const *Find(ProfileKey const &key)
{
    ProfileMap::const_iterator const profile = g_Profiles.find(NormalizeKey(key));
    return profile != g_Profiles.end() ? &profile->second : nullptr;
}
}

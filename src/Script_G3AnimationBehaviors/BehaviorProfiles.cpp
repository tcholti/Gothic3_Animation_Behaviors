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
                   left.rightAnimationUseType)
            < std::tie(
                   right.animationFamily,
                   right.leftAnimationUseType,
                   right.rightAnimationUseType);
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

bool TryGetAnimationUseTypeToken(gEUseType useType, std::string &token)
{
    switch (useType)
    {
        case gEUseType_None:         token = "none"; return true;
        case gEUseType_1H:           token = "1h"; return true;
        case gEUseType_2H:           token = "2h"; return true;
        case gEUseType_Fist:         token = "fist"; return true;
        case gEUseType_Shield:       token = "shield"; return true;
        case gEUseType_Staff:        token = "staff"; return true;
        case gEUseType_Torch:        token = "torch"; return true;
        case gEUseType_Broom:        token = "staff"; return true;
        case gEUseType_Rake:         token = "staff"; return true;
        case gEUseType_Shovel:       token = "staff"; return true;
        case gEUseType_Fan:          token = "staff"; return true;
        case gEUseType_Pickaxe:      token = "2h"; return true;
        case gEUseType_Axe:          token = "2h"; return true;
        case gEUseType_Halberd:      token = "staff"; return true;
        case gEUseType_PhysicalFist: token = "fist"; return true;
        default:                     return false;
    }
}

gEUseType GetHandUseType(Entity const &entity, gESlot slot)
{
    Entity item = entity.Inventory.GetItemFromSlot(slot);
    return item == None ? gEUseType_None : item.Interaction.GetUseType();
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

AttackSettings ParseAttackSettings(
    eCConfigFile const &config,
    bCString const &section,
    char const *prefix)
{
    AttackSettings settings = {
        false, 0.0f,
        false, 0.0f,
        RaiseOverride::Off};

    std::string const prefixText(prefix);

    std::string const referenceName =
        prefixText + "_ReferenceHitBaseSpeed";
    bCString const referenceKey(referenceName.c_str());
    if (config.Contains(section, referenceKey))
    {
        float value = 0.0f;
        if (ParsePositiveFiniteFloat(
                config.GetString(section, referenceKey).GetText(), value))
        {
            settings.hasReferenceHitBaseSpeed = true;
            settings.referenceHitBaseSpeed = value;
        }
    }

    std::string const baseName = prefixText + "_BaseSpeed";
    bCString const baseKey(baseName.c_str());
    if (config.Contains(section, baseKey))
    {
        float value = 0.0f;
        if (ParsePositiveFiniteFloat(
                config.GetString(section, baseKey).GetText(), value))
        {
            settings.hasBaseSpeed = true;
            settings.baseSpeed = value;
        }
    }

    std::string const raiseName = prefixText + "_RaiseOverride";
    bCString const raiseKey(raiseName.c_str());
    if (config.Contains(section, raiseKey))
    {
        std::string const value = NormalizeIdentityString(
            config.GetString(section, raiseKey).GetText());
        if (value == "on")
            settings.raiseOverride = RaiseOverride::On;
    }

    return settings;
}

bool ParseProfileKey(
    eCConfigFile const &config,
    bCString const &section,
    ProfileKey &result)
{
    return ReadIdentityString(
               config, section, "AnimationFamily", result.animationFamily)
        && ReadIdentityString(
               config, section, "LeftAnimationUseType",
               result.leftAnimationUseType)
        && ReadIdentityString(
               config, section, "RightAnimationUseType",
               result.rightAnimationUseType);
}

Profile ParseProfile(
    eCConfigFile const &config,
    bCString const &section,
    ProfileKey const &key)
{
    Profile profile = {
        key,
        ParseAttackSettings(config, section, "Normal"),
        ParseAttackSettings(config, section, "Quick"),
        ParseAttackSettings(config, section, "Power"),
        ParseAttackSettings(config, section, "Pierce"),
        ParseAttackSettings(config, section, "Hack"),
        ParseAttackSettings(config, section, "SimpleWhirl"),
        ParseAttackSettings(config, section, "Whirl")};
    return profile;
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

        key = NormalizeKey(key);
        InsertProfile(ParseProfile(config, section, key));
    }
}

Profile const *Find(ProfileKey const &key)
{
    ProfileMap::const_iterator const profile =
        g_Profiles.find(NormalizeKey(key));
    return profile != g_Profiles.end() ? &profile->second : nullptr;
}

AttackSettings const *GetAttackSettings(
    Profile const &profile, AttackType attackType)
{
    switch (attackType)
    {
        case AttackType::Normal:      return &profile.normal;
        case AttackType::Quick:       return &profile.quick;
        case AttackType::Power:       return &profile.power;
        case AttackType::Pierce:      return &profile.pierce;
        case AttackType::Hack:        return &profile.hack;
        case AttackType::SimpleWhirl: return &profile.simpleWhirl;
        case AttackType::Whirl:       return &profile.whirl;
        default:                      return nullptr;
    }
}

bool TryBuildRuntimeKey(Entity const &entity, ProfileKey &key)
{
    if (entity == None)
        return false;

    bCString skeletonName;
    if (!entity.Animation.GetSkeletonName(skeletonName))
        return false;

    key.animationFamily = NormalizeIdentityString(skeletonName.GetText());
    if (key.animationFamily.empty())
        return false;

    gEUseType const rawLeftUseType =
        GetHandUseType(entity, gESlot_LeftHand);
    gEUseType const rawRightUseType =
        GetHandUseType(entity, gESlot_RightHand);
    if (!TryGetAnimationUseTypeToken(
            rawLeftUseType, key.leftAnimationUseType)
        || !TryGetAnimationUseTypeToken(
            rawRightUseType, key.rightAnimationUseType))
    {
        return false;
    }

    key = NormalizeKey(key);
    return true;
}
}

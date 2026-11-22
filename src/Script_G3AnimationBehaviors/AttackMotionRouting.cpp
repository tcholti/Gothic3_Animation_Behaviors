#include "AttackMotionRouting.h"

#include <g3sdk/Engine/ge_moduleadmin.h>

#include <cstring>
#include <string>

namespace FrameCollision::AttackMotionRouting
{
eCResourceDataEntity *QueryOptionalSubstitution(
    gEAction factualAction, eCAnimationAdmin *animationAdmin,
    bCString const &resourceName,
    eEResourceCacheBehavior cacheBehavior)
{
    char const *const resourceNameText = resourceName.GetText();
    if (factualAction != gEAction_HackAttack
        || resourceNameText == nullptr)
    {
        return nullptr;
    }

    static char const FinishingToken[] = "_FinishingAttack_";
    static char const HackToken[] = "_HackAttack_";
    std::string candidate(resourceNameText);
    std::string::size_type const actionToken =
        candidate.find(FinishingToken);
    if (actionToken == std::string::npos)
        return nullptr;

    candidate.replace(actionToken, sizeof(FinishingToken) - 1, HackToken);
    bCString const candidateName(candidate.c_str());
    return animationAdmin->QueryMotionDataEntity(
        candidateName, cacheBehavior);
}

bool HasMatchingHackRecoverForFinishingMotion(bCString const &motionFilename)
{
    char const *const motionName = motionFilename.GetText();
    if (motionName == nullptr)
        return false;

    // The first native playback is a Finishing Recover .xmot descriptor.
    // Derive the actual .fxm resource request using Gothic's serialized
    // "_%_" variant separator; preserve the trailing underscore.
    static char const FinishingRecover[] = "_FinishingAttack_Recover_";
    static char const Variation[] = "_%_";
    static char const Extension[] = ".xmot";
    size_t const length = std::strlen(motionName);
    if (length < sizeof(Extension) - 1
        || std::strcmp(motionName + length - (sizeof(Extension) - 1),
                       Extension) != 0
        || std::strstr(motionName, FinishingRecover) == nullptr)
        return false;

    char const *const variation = std::strstr(motionName, Variation);
    if (variation == nullptr
        || std::strstr(variation + sizeof(Variation) - 1, Variation) != nullptr)
        return false;

    std::string resourceName(motionName, variation - motionName + 1);
    resourceName += ".fxm";

    // Look up the live engine owner at this exact transition. Never retain
    // an animation-admin pointer from an earlier attack phase.
    eCEngineComponentBase *const module =
        eCModuleAdmin::GetInstance().FindModule(bCString("eCAnimationAdmin"));
    eCAnimationAdmin *const animationAdmin =
        dynamic_cast<eCAnimationAdmin *>(module);
    if (animationAdmin == nullptr)
        return false;

    return QueryOptionalSubstitution(
               gEAction_HackAttack, animationAdmin,
               bCString(resourceName.c_str()),
               eEResourceCacheBehavior_Immediate) != nullptr;
}
}

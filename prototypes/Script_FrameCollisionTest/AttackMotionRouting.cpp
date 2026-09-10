#include "AttackMotionRouting.h"

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
}

#pragma once

#include <g3sdk/Engine/animation/ge_animationadmin.h>
#include <g3sdk/Script.h>

namespace FrameCollision::AttackMotionRouting
{
eCResourceDataEntity *QueryOptionalSubstitution(
    gEAction factualAction, eCAnimationAdmin *animationAdmin,
    bCString const &resourceName,
    eEResourceCacheBehavior cacheBehavior);

// Only answer whether the first native Finishing Recover may be skipped.
// Unsupported names, missing module and absent Hack Recover all fail native.
bool HasMatchingHackRecoverForFinishingMotion(bCString const &motionFilename);
}

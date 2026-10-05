#include "AttackMovement.h"

#include "BehaviorProfiles.h"

#include <g3sdk/Engine/animation/ge_visualanimation_ps.h>

#include <cmath>
#include <limits>

namespace G3AB::AttackMovement
{
namespace
{
bool TryGetAttackType(
    gEAction action,
    BehaviorProfiles::AttackType &attackType)
{
    switch (action)
    {
        case gEAction_Attack:
            attackType = BehaviorProfiles::AttackType::Normal;
            return true;
        case gEAction_QuickAttackR:
        case gEAction_QuickAttackL:
            attackType = BehaviorProfiles::AttackType::Quick;
            return true;
        case gEAction_PowerAttack:
            attackType = BehaviorProfiles::AttackType::Power;
            return true;
        case gEAction_PierceAttack:
            attackType = BehaviorProfiles::AttackType::Pierce;
            return true;
        case gEAction_HackAttack:
            attackType = BehaviorProfiles::AttackType::Hack;
            return true;
        case gEAction_SimpleWhirl:
            attackType = BehaviorProfiles::AttackType::SimpleWhirl;
            return true;
        case gEAction_WhirlAttack:
            attackType = BehaviorProfiles::AttackType::Whirl;
            return true;
        default:
            return false;
    }
}
}

void Compose(
    gCScriptProcessingUnit::sAICombatMoveInstr_Args const *request,
    gCScriptProcessingUnit *spu,
    bCVector &movement)
{
    if (request == nullptr || spu == nullptr || request->SelfEntity == nullptr
        || request->PhaseName != bCString("Hit"))
    {
        return;
    }

    Entity actor(request->SelfEntity);
    if (actor == None)
        return;

    BehaviorProfiles::AttackType attackType;
    if (!TryGetAttackType(request->Action, attackType))
        return;

    BehaviorProfiles::ProfileKey key;
    if (!BehaviorProfiles::TryBuildRuntimeKey(
            actor, request->Action, gEPhase_Hit, key))
    {
        return;
    }

    BehaviorProfiles::Profile const *profile = BehaviorProfiles::Find(key);
    if (profile == nullptr)
        return;

    BehaviorProfiles::AttackSettings const *settings =
        BehaviorProfiles::GetAttackSettings(*profile, attackType);
    if (settings == nullptr || !settings->hasMovement
        || !(settings->movement >= 0.0f)
        || !std::isfinite(settings->movement))
    {
        return;
    }

    // Numeric zero is active and needs neither timing nor a direction.
    if (settings->movement == 0.0f)
    {
        movement.Clear();
        return;
    }

    if (!(request->AniSpeedScale > 0.0f)
        || !std::isfinite(request->AniSpeedScale)
        || !actor.Animation.IsValid())
    {
        return;
    }

    eCVisualAnimation_PS *animationPS = static_cast<eCVisualAnimation_PS *>(
        actor.Animation.m_pEngineEntityPropertySet);
    if (animationPS == nullptr || !animationPS->HasActor())
        return;

    eCWrapper_emfx2Actor *animationActor = animationPS->GetActor();
    if (animationActor == nullptr)
        return;

    // Primary-first is motion 0 in the pinned SDK/native timing surface.
    auto const primaryMotion =
        static_cast<eCWrapper_emfx2Actor::eEMotionType>(0);
    if (!animationActor->HasMotionInstance(primaryMotion))
        return;

    GEDouble const maxTime = animationActor->GetMaxTime(primaryMotion);
    if (!(maxTime > 0.0) || !std::isfinite(maxTime))
        return;

    GEDouble const duration = maxTime / request->AniSpeedScale;
    if (!(duration > 0.0) || !std::isfinite(duration))
        return;

    GEDouble const velocityMagnitude = settings->movement / duration;
    if (!(velocityMagnitude > 0.0) || !std::isfinite(velocityMagnitude)
        || velocityMagnitude > (std::numeric_limits<GEFloat>::max)())
    {
        return;
    }

    GEDouble const x = movement.m_fX;
    GEDouble const y = movement.m_fY;
    GEDouble const z = movement.m_fZ;
    if (!std::isfinite(x) || !std::isfinite(y) || !std::isfinite(z))
        return;

    GEDouble const directionMagnitude = std::sqrt(x * x + y * y + z * z);
    if (!(directionMagnitude > 0.0) || !std::isfinite(directionMagnitude))
        return;

    // Normalize and scale locally; the compatible vector stays intact on failure.
    bCVector const replacement(
        static_cast<GEFloat>((x / directionMagnitude) * velocityMagnitude),
        static_cast<GEFloat>((y / directionMagnitude) * velocityMagnitude),
        static_cast<GEFloat>((z / directionMagnitude) * velocityMagnitude));
    if (!std::isfinite(replacement.m_fX)
        || !std::isfinite(replacement.m_fY)
        || !std::isfinite(replacement.m_fZ)
        || (replacement.m_fX == 0.0f
            && replacement.m_fY == 0.0f
            && replacement.m_fZ == 0.0f))
    {
        return;
    }

    movement = replacement;
}
}

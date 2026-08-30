#pragma once

#include <g3sdk/Script.h>

#include <string>

namespace FrameCollision
{
char const *const CollisionRightMarker = "G3AB_COL_RIGHT";
char const *const CollisionLeftMarker = "G3AB_COL_LEFT";
char const *const CollisionBothMarker = "G3AB_COL_BOTH";
char const *const CollisionOffMarker = "G3AB_COL_OFF";

enum MarkerOpcode
{
    MarkerOpcode_Right = 0,
    MarkerOpcode_Left = 1,
    MarkerOpcode_Both = 2,
    MarkerOpcode_Off = 3,
    MarkerOpcode_Count = 4,
    MarkerOpcode_Invalid = -1
};

enum AttackFamily
{
    AttackFamily_Normal,
    AttackFamily_Quick,
    AttackFamily_Whirl
};

unsigned int const SourceMask_None = 0;
unsigned int const SourceMask_Right = 1u << 0;
unsigned int const SourceMask_Left = 1u << 1;
unsigned int const SourceMask_Both = SourceMask_Right | SourceMask_Left;

struct EquippedCollisionSources
{
    eCEntity *rightInstance;
    eCEntity *leftInstance;
};

struct CurrentMotionMarkerResult
{
    bool foundMatchingMotion;
    bool scanValid;
    bool markerPresent;
    GEInt frameEffectCount;
    GEInt firstMarkerFrames[MarkerOpcode_Count];
    GEInt markerCounts[MarkerOpcode_Count];
    unsigned int requiredSourceMask;
};

struct ControlledCallbackObservation
{
    bool executionRetired;
    bCString currentAnimation;
    GEInt currentAction;
    GEInt currentPhase;
    GEFloat currentStateTime;
    GEFloat previousStateTime;
    bool keyChanged;
    bool stateTimeRolledBack;
};

enum MarkerResultCode
{
    MarkerResult_RejectedUnsupportedHit,
    MarkerResult_RejectedMotionOwnership,
    MarkerResult_UnsupportedMissingSource,
    MarkerResult_DuplicateIgnored,
    MarkerResult_BudgetIgnored,
    MarkerResult_OffAccepted,
    MarkerResult_OffNoWindow,
    MarkerResult_RejectedEmptySourceSet,
    MarkerResult_RejectedIncompleteActivation,
    MarkerResult_Accepted
};

struct MarkerProcessResult
{
    MarkerResultCode code;
    MarkerOpcode opcode;
    CurrentMotionMarkerResult decision;
    EquippedCollisionSources sources;
    std::string markerName;
    std::string currentAnimation;
    GEInt markerAction;
    GEInt markerPhase;
    GEFloat markerStateTime;
    double markerElapsedMs;
    GEFloat duplicateStateTimeDelta;
    double duplicateElapsedMsDelta;
    GEInt authoredMarkerCount;
    GEInt acceptedMarkerCountBefore;
    GEInt acceptedMarkerCountAfter;
    bool executionBudgetReset;
    unsigned int ownedMask;
    bool markerOwnedWindowRemoved;
    GEInt deactivatedSourceCount;
    unsigned int missingSourceMask;
    unsigned int previousSourceMask;
    unsigned int desiredSourceMask;
    unsigned int retiredSourceMask;
    GEInt retiredSourceCount;
    GEInt sourceGroupBefore[2];
    GEInt sourceGroupAfter[2];
    GEInt sourceUseTypes[2];
    bool sourceSkippedGroupForFist[2];
    bool sourceGroupRequested[2];
    bool sourceListCleared[2];
    GEInt activatedSourceCount;
    GEInt collisionGroupRequestCount;
    GEInt fistSourceCount;
    GEInt triggeredListClearCount;
    unsigned int markerOwnedWeaponMask;
    GEInt quickStatePositionBeforeMarker;
    GEInt quickStatePositionAfterMarker;
    GEInt whirlStatePositionBeforeMarker;
    GEInt whirlStatePositionAfterMarker;
};

struct MarkerOwnedWindowView
{
    unsigned int activeSourceMask;
    std::string animationName;
    GEInt action;
    GEInt phase;
};
}

cmake_minimum_required(VERSION 3.16...3.24)

project(
    Gothic3_Animation_Behaviors
    DESCRIPTION "Gothic 3 animation behavior scripts and diagnostics"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(G3AB_BUILD_PROTOTYPES "Build experimental animation-behavior prototypes" ON)
option(G3AB_BUILD_TOOLS "Build project diagnostic tools" ON)

add_subdirectory(thirdparty/gothic3sdk)
include(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/gothic3sdk/cmake/Setup.cmake)

add_subdirectory(src/Script_G3AnimationBehaviors)

if(G3AB_BUILD_PROTOTYPES)
    add_subdirectory(prototypes/Script_FrameCollisionTest)
    add_subdirectory(prototypes/Script_FrameEffectLogger)
endif()

if(G3AB_BUILD_TOOLS)
    add_subdirectory(tools/Script_CombatMoveLogger)
endif()

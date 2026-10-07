#pragma once

#include <g3sdk/Script.h>

#include <cstdio>

namespace BadBlockResearch
{
// Temporary experiment policy. The adapter has already called the native getter.
GEU32 DeferPlayerHitTimeout(
    GEU32 rawDuration,
    PSCharacterControl const *receiver,
    FILE *log);
}

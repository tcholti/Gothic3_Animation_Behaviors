#pragma once

#include <g3sdk/Script.h>

#include <cstdio>

namespace BadBlockResearch
{
// Temporary experiment policy. The adapter has already called the native getter.
// protectionEnabled=false observes the exact same qualifying seam but preserves raw.
GEU32 EvaluatePlayerHitTimeout(
    GEU32 rawDuration,
    PSCharacterControl const *receiver,
    FILE *log,
    bool protectionEnabled);

// Observation-only exclusion probe. Always returns native raw unchanged.
GEU32 ObservePierceHackHitTimeout(
    GEU32 rawDuration,
    PSCharacterControl const *receiver,
    FILE *log);
}

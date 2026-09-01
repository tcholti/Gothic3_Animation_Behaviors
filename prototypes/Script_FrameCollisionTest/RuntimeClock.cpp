#include "RuntimeClock.h"

#include <windows.h>

namespace FrameCollision::RuntimeClock
{
static LARGE_INTEGER g_StartCounter = {};
static LARGE_INTEGER g_Frequency = {};

void InitializeClock()
{
    ::QueryPerformanceFrequency(&g_Frequency);
    ::QueryPerformanceCounter(&g_StartCounter);
}

double GetElapsedMilliseconds()
{
    LARGE_INTEGER now = {};
    ::QueryPerformanceCounter(&now);
    if (g_Frequency.QuadPart == 0)
        return 0.0;
    return (static_cast<double>(now.QuadPart - g_StartCounter.QuadPart) * 1000.0)
         / static_cast<double>(g_Frequency.QuadPart);
}
}

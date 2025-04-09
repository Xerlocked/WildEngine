#include "Timer.h"

#include <algorithm>
#include "Class.h"

Timer::Timer()
{
    uint64_t CountsPerSecond = 0;
    QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&CountsPerSecond));
    SecondsPerCount = 1.0f / static_cast<float>(CountsPerSecond);

    Reset();
}

void Timer::Start()
{
    uint64_t StartTime = 0;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&StartTime));

    if (bStopped)
    {
        PausedTime += StartTime - StopTime;
        PreviousTime = StartTime;
        StopTime = 0;
        bStopped = false;
    }
}

void Timer::Stop()
{
    if (bStopped)
    {
        uint64_t CurrentTime = 0;
        QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentTime));

        StopTime = CurrentTime;
        bStopped = true;
    }
}

void Timer::Reset()
{
    uint64_t CurrentTime = 0;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentTime));

    BaseTime = CurrentTime;
    PreviousTime = CurrentTime;
    StopTime = 0;
    bStopped = false;

    Tick();
}

void Timer::Tick()
{
    if (bStopped)
    {
        DeltaTime = 0.0f;
        return;
    }

    uint64_t TickCurrentTime = 0;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&TickCurrentTime));

    CurrentTime = TickCurrentTime;

    DeltaTime = (CurrentTime - PreviousTime) * SecondsPerCount;

    PreviousTime = CurrentTime;

    DeltaTime = std::max(DeltaTime, 0.0f);
}

float Timer::GetDeltaTime() const
{
    return DeltaTime;
}

float Timer::GetTotalTime() const
{
    if (bStopped)
    {
        return (StopTime - PausedTime - BaseTime) * SecondsPerCount;
    }
    
    return (CurrentTime - PausedTime - BaseTime) * SecondsPerCount;
}

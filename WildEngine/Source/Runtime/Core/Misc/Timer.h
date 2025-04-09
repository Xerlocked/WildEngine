#pragma once
#include <cstdint>

class Timer
{
public:
    Timer();
    ~Timer() = default;

    void Start();

    void Stop();

    void Reset();

    void Tick();

    float GetDeltaTime() const;

    float GetTotalTime() const;

private:
    float SecondsPerCount = 0.0f;
    float DeltaTime = 0.0f;

    int64_t BaseTime = 0;
    int64_t PausedTime = 0;
    int64_t StopTime = 0;
    int64_t PreviousTime = 0;
    int64_t CurrentTime = 0;

    bool bStopped = false;
};

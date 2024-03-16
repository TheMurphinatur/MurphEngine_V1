#pragma once
#include <chrono>

namespace MurphEngine
{
    

class TimeManager
{
    using HighResolutionClock = std::chrono::high_resolution_clock;
    using TimePoint = HighResolutionClock::time_point;

    TimePoint m_startTime;
public:
    void StartTimer();
    double GetDeltaFromStart() const;
};

}
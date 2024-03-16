#include "pch.h"
#include "TimeManager.h"

void MurphEngine::TimeManager::StartTimer()
{
    m_startTime = HighResolutionClock::now();
}

double MurphEngine::TimeManager::GetDeltaFromStart() const
{
    using namespace std::chrono;

    const TimePoint endTime = HighResolutionClock::now();
    duration<double> timeSpan = duration_cast<duration <double>>(endTime - m_startTime);
    return timeSpan.count() * 1000; // converts to miliseconds.
}

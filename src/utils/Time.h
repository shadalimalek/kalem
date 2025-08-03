#pragma once

#include <chrono>
#include <string>

/**
 * @brief Time utilities for the Kalem animation engine
 * 
 * Provides timing functions and time-related utilities
 * for animations and performance measurement.
 */
namespace Time {
    
    // Time measurement
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;
    using Duration = std::chrono::duration<float>;
    
    // Time utilities
    TimePoint now();
    float elapsed(const TimePoint& start);
    float elapsedSeconds(const TimePoint& start);
    float elapsedMilliseconds(const TimePoint& start);
    
    // Animation timing
    float getDeltaTime();
    void setDeltaTime(float dt);
    float getTimeScale();
    void setTimeScale(float scale);
    
    // Performance measurement
    class Timer {
    public:
        Timer();
        void start();
        void stop();
        float getElapsed() const;
        void reset();
        
    private:
        TimePoint m_startTime;
        TimePoint m_endTime;
        bool m_isRunning;
    };
    
    // Time formatting
    std::string formatTime(float seconds);
    std::string formatDuration(float seconds);
    
} // namespace Time 
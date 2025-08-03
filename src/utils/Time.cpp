#include "Time.h"
#include <sstream>
#include <iomanip>

namespace Time {
    
    // Global timing state
    static float g_deltaTime = 0.016f;  // Default 60 FPS
    static float g_timeScale = 1.0f;
    
    TimePoint now() {
        return Clock::now();
    }
    
    float elapsed(const TimePoint& start) {
        auto now = Clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start);
        return duration.count() / 1000000.0f;
    }
    
    float elapsedSeconds(const TimePoint& start) {
        return elapsed(start);
    }
    
    float elapsedMilliseconds(const TimePoint& start) {
        auto now = Clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
        return duration.count();
    }
    
    float getDeltaTime() {
        return g_deltaTime * g_timeScale;
    }
    
    void setDeltaTime(float dt) {
        g_deltaTime = dt;
    }
    
    float getTimeScale() {
        return g_timeScale;
    }
    
    void setTimeScale(float scale) {
        g_timeScale = scale;
    }
    
    // Timer implementation
    Timer::Timer() : m_isRunning(false) {
    }
    
    void Timer::start() {
        m_startTime = Clock::now();
        m_isRunning = true;
    }
    
    void Timer::stop() {
        if (m_isRunning) {
            m_endTime = Clock::now();
            m_isRunning = false;
        }
    }
    
    float Timer::getElapsed() const {
        if (m_isRunning) {
            return elapsed(m_startTime);
        } else {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(m_endTime - m_startTime);
            return duration.count() / 1000000.0f;
        }
    }
    
    void Timer::reset() {
        m_isRunning = false;
    }
    
    std::string formatTime(float seconds) {
        int hours = static_cast<int>(seconds) / 3600;
        int minutes = (static_cast<int>(seconds) % 3600) / 60;
        int secs = static_cast<int>(seconds) % 60;
        int ms = static_cast<int>((seconds - static_cast<int>(seconds)) * 1000);
        
        std::ostringstream oss;
        if (hours > 0) {
            oss << std::setfill('0') << std::setw(2) << hours << ":";
        }
        oss << std::setfill('0') << std::setw(2) << minutes << ":"
            << std::setfill('0') << std::setw(2) << secs << "."
            << std::setfill('0') << std::setw(3) << ms;
        
        return oss.str();
    }
    
    std::string formatDuration(float seconds) {
        if (seconds < 1.0f) {
            return std::to_string(static_cast<int>(seconds * 1000)) + "ms";
        } else if (seconds < 60.0f) {
            return std::to_string(static_cast<int>(seconds)) + "s";
        } else if (seconds < 3600.0f) {
            int minutes = static_cast<int>(seconds) / 60;
            int secs = static_cast<int>(seconds) % 60;
            return std::to_string(minutes) + "m " + std::to_string(secs) + "s";
        } else {
            int hours = static_cast<int>(seconds) / 3600;
            int minutes = (static_cast<int>(seconds) % 3600) / 60;
            return std::to_string(hours) + "h " + std::to_string(minutes) + "m";
        }
    }
    
} // namespace Time 
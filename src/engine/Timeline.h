#pragma once

#include <vector>
#include <functional>
#include <string>

/**
 * @brief Timeline class for managing animation timing and playback
 * 
 * The timeline controls the overall timing of animations, including
 * play/pause/reset functionality and time scaling.
 */
class Timeline {
public:
    Timeline();
    ~Timeline();

    // Timeline control
    void play();
    void pause();
    void reset();
    void stop();
    
    // Time control
    void setTimeScale(float scale);
    float getTimeScale() const;
    
    void setCurrentTime(float time);
    float getCurrentTime() const;
    
    void setDuration(float duration);
    float getDuration() const;
    
    // Timeline state
    bool isPlaying() const;
    bool isPaused() const;
    bool isStopped() const;
    
    // Update
    void update(float deltaTime);
    
    // Timeline markers
    void addMarker(float time, const std::string& name);
    void removeMarker(const std::string& name);
    void jumpToMarker(const std::string& name);
    
    // Timeline events
    using TimelineCallback = std::function<void(float)>;
    void addTimeCallback(float time, TimelineCallback callback);
    void removeTimeCallback(float time);

private:
    bool m_isPlaying;
    bool m_isPaused;
    float m_currentTime;
    float m_duration;
    float m_timeScale;
    
    struct Marker {
        float time;
        std::string name;
    };
    
    struct TimeCallback {
        float time;
        TimelineCallback callback;
    };
    
    std::vector<Marker> m_markers;
    std::vector<TimeCallback> m_callbacks;
    
    // Helper methods
    void checkCallbacks();
    void sortMarkers();
}; 
#include "Timeline.h"
#include <algorithm>
#include <iostream>

Timeline::Timeline()
    : m_isPlaying(false)
    , m_isPaused(false)
    , m_currentTime(0.0f)
    , m_duration(0.0f)
    , m_timeScale(1.0f) {
}

Timeline::~Timeline() {
}

void Timeline::play() {
    m_isPlaying = true;
    m_isPaused = false;
}

void Timeline::pause() {
    m_isPaused = true;
    m_isPlaying = false;
}

void Timeline::reset() {
    m_currentTime = 0.0f;
    m_isPlaying = false;
    m_isPaused = false;
}

void Timeline::stop() {
    m_isPlaying = false;
    m_isPaused = false;
    m_currentTime = 0.0f;
}

void Timeline::setTimeScale(float scale) {
    m_timeScale = scale;
}

float Timeline::getTimeScale() const {
    return m_timeScale;
}

void Timeline::setCurrentTime(float time) {
    m_currentTime = std::max(0.0f, std::min(time, m_duration));
}

float Timeline::getCurrentTime() const {
    return m_currentTime;
}

void Timeline::setDuration(float duration) {
    m_duration = std::max(0.0f, duration);
    if (m_currentTime > m_duration) {
        m_currentTime = m_duration;
    }
}

float Timeline::getDuration() const {
    return m_duration;
}

bool Timeline::isPlaying() const {
    return m_isPlaying && !m_isPaused;
}

bool Timeline::isPaused() const {
    return m_isPaused;
}

bool Timeline::isStopped() const {
    return !m_isPlaying && !m_isPaused;
}

void Timeline::update(float deltaTime) {
    if (m_isPlaying && !m_isPaused) {
        m_currentTime += deltaTime * m_timeScale;
        
        // Check if we've reached the end
        if (m_currentTime >= m_duration && m_duration > 0.0f) {
            m_currentTime = m_duration;
            m_isPlaying = false;
        }
        
        // Check for callbacks
        checkCallbacks();
    }
}

void Timeline::addMarker(float time, const std::string& name) {
    Marker marker;
    marker.time = time;
    marker.name = name;
    m_markers.push_back(marker);
    sortMarkers();
}

void Timeline::removeMarker(const std::string& name) {
    m_markers.erase(
        std::remove_if(m_markers.begin(), m_markers.end(),
            [&name](const Marker& marker) {
                return marker.name == name;
            }),
        m_markers.end()
    );
}

void Timeline::jumpToMarker(const std::string& name) {
    for (const auto& marker : m_markers) {
        if (marker.name == name) {
            setCurrentTime(marker.time);
            return;
        }
    }
}

void Timeline::addTimeCallback(float time, TimelineCallback callback) {
    TimeCallback timeCallback;
    timeCallback.time = time;
    timeCallback.callback = callback;
    m_callbacks.push_back(timeCallback);
}

void Timeline::removeTimeCallback(float time) {
    m_callbacks.erase(
        std::remove_if(m_callbacks.begin(), m_callbacks.end(),
            [time](const TimeCallback& callback) {
                return callback.time == time;
            }),
        m_callbacks.end()
    );
}

void Timeline::checkCallbacks() {
    for (auto& callback : m_callbacks) {
        if (m_currentTime >= callback.time && callback.callback) {
            callback.callback(m_currentTime);
        }
    }
}

void Timeline::sortMarkers() {
    std::sort(m_markers.begin(), m_markers.end(),
        [](const Marker& a, const Marker& b) {
            return a.time < b.time;
        });
} 
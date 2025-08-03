#include "Math.h"
#include <cmath>

namespace Math {
    
    // Interpolation functions
    float lerp(float a, float b, float t) {
        return a + (b - a) * t;
    }
    
    glm::vec3 lerp(const glm::vec3& a, const glm::vec3& b, float t) {
        return a + (b - a) * t;
    }
    
    glm::vec4 lerp(const glm::vec4& a, const glm::vec4& b, float t) {
        return a + (b - a) * t;
    }
    
    // Easing functions
    float easeInQuad(float t) {
        return t * t;
    }
    
    float easeOutQuad(float t) {
        return t * (2.0f - t);
    }
    
    float easeInOutQuad(float t) {
        return t < 0.5f ? 2.0f * t * t : -1.0f + (4.0f - 2.0f * t) * t;
    }
    
    float easeInCubic(float t) {
        return t * t * t;
    }
    
    float easeOutCubic(float t) {
        return 1.0f - (1.0f - t) * (1.0f - t) * (1.0f - t);
    }
    
    float easeInOutCubic(float t) {
        return t < 0.5f ? 4.0f * t * t * t : 1.0f - 4.0f * (1.0f - t) * (1.0f - t) * (1.0f - t);
    }
    
    // Trigonometric utilities
    float toRadians(float degrees) {
        return degrees * M_PI / 180.0f;
    }
    
    float toDegrees(float radians) {
        return radians * 180.0f / M_PI;
    }
    
    // Vector utilities
    float distance(const glm::vec3& a, const glm::vec3& b) {
        return glm::length(a - b);
    }
    
    float distance2D(const glm::vec3& a, const glm::vec3& b) {
        glm::vec2 diff(a.x - b.x, a.y - b.y);
        return glm::length(diff);
    }
    
    glm::vec3 normalize(const glm::vec3& v) {
        return glm::normalize(v);
    }
    
    // Random utilities
    float random(float min, float max) {
        float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        return min + random * (max - min);
    }
    
    glm::vec3 randomDirection() {
        float theta = random(0.0f, 2.0f * M_PI);
        float phi = random(0.0f, M_PI);
        
        float x = sin(phi) * cos(theta);
        float y = sin(phi) * sin(theta);
        float z = cos(phi);
        
        return glm::vec3(x, y, z);
    }
    
    // Clamping and wrapping
    float clamp(float value, float min, float max) {
        return std::max(min, std::min(max, value));
    }
    
    float wrap(float value, float min, float max) {
        float range = max - min;
        if (range == 0.0f) return min;
        
        float wrapped = fmod(value - min, range);
        if (wrapped < 0.0f) wrapped += range;
        return wrapped + min;
    }
    
    // Animation utilities
    float smoothStep(float edge0, float edge1, float x) {
        x = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
        return x * x * (3.0f - 2.0f * x);
    }
    
    float smootherStep(float edge0, float edge1, float x) {
        x = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
        return x * x * x * (x * (x * 6.0f - 15.0f) + 10.0f);
    }
    
} // namespace Math 
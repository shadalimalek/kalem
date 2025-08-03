#pragma once

#include <glm/glm.hpp>

/**
 * @brief Mathematical utilities for the Kalem animation engine
 * 
 * Provides interpolation, easing, and other mathematical functions
 * commonly used in animations.
 */
namespace Math {
    
    // Interpolation functions
    float lerp(float a, float b, float t);
    glm::vec3 lerp(const glm::vec3& a, const glm::vec3& b, float t);
    glm::vec4 lerp(const glm::vec4& a, const glm::vec4& b, float t);
    
    // Easing functions
    float easeInQuad(float t);
    float easeOutQuad(float t);
    float easeInOutQuad(float t);
    float easeInCubic(float t);
    float easeOutCubic(float t);
    float easeInOutCubic(float t);
    
    // Trigonometric utilities
    float toRadians(float degrees);
    float toDegrees(float radians);
    
    // Vector utilities
    float distance(const glm::vec3& a, const glm::vec3& b);
    float distance2D(const glm::vec3& a, const glm::vec3& b);
    glm::vec3 normalize(const glm::vec3& v);
    
    // Random utilities
    float random(float min, float max);
    glm::vec3 randomDirection();
    
    // Clamping and wrapping
    float clamp(float value, float min, float max);
    float wrap(float value, float min, float max);
    
    // Animation utilities
    float smoothStep(float edge0, float edge1, float x);
    float smootherStep(float edge0, float edge1, float x);
    
} // namespace Math 
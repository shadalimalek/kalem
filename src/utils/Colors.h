#pragma once

#include <glm/glm.hpp>
#include <string>

/**
 * @brief Color utilities for the Kalem animation engine
 * 
 * Provides predefined colors and color manipulation functions
 * commonly used in educational animations.
 */
namespace Colors {
    
    // Predefined colors (RGBA format)
    extern const glm::vec4 RED;
    extern const glm::vec4 GREEN;
    extern const glm::vec4 BLUE;
    extern const glm::vec4 YELLOW;
    extern const glm::vec4 CYAN;
    extern const glm::vec4 MAGENTA;
    extern const glm::vec4 WHITE;
    extern const glm::vec4 BLACK;
    extern const glm::vec4 GRAY;
    extern const glm::vec4 ORANGE;
    extern const glm::vec4 PURPLE;
    extern const glm::vec4 PINK;
    extern const glm::vec4 BROWN;
    
    // Color manipulation functions
    glm::vec4 fromRGB(float r, float g, float b, float a = 1.0f);
    glm::vec4 fromHSV(float h, float s, float v, float a = 1.0f);
    glm::vec4 blend(const glm::vec4& a, const glm::vec4& b, float t);
    glm::vec4 darken(const glm::vec4& color, float factor);
    glm::vec4 lighten(const glm::vec4& color, float factor);
    glm::vec4 setAlpha(const glm::vec4& color, float alpha);
    
    // Color conversion functions
    void RGBtoHSV(float r, float g, float b, float& h, float& s, float& v);
    void HSVtoRGB(float h, float s, float v, float& r, float& g, float& b);
    
    // Utility functions
    float getLuminance(const glm::vec4& color);
    bool isDark(const glm::vec4& color);
    glm::vec4 getContrastColor(const glm::vec4& color);
    
} // namespace Colors 
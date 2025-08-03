#include "Colors.h"
#include <algorithm>
#include <cmath>

namespace Colors {
    
    // Predefined colors
    const glm::vec4 RED(1.0f, 0.0f, 0.0f, 1.0f);
    const glm::vec4 GREEN(0.0f, 1.0f, 0.0f, 1.0f);
    const glm::vec4 BLUE(0.0f, 0.0f, 1.0f, 1.0f);
    const glm::vec4 YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
    const glm::vec4 CYAN(0.0f, 1.0f, 1.0f, 1.0f);
    const glm::vec4 MAGENTA(1.0f, 0.0f, 1.0f, 1.0f);
    const glm::vec4 WHITE(1.0f, 1.0f, 1.0f, 1.0f);
    const glm::vec4 BLACK(0.0f, 0.0f, 0.0f, 1.0f);
    const glm::vec4 GRAY(0.5f, 0.5f, 0.5f, 1.0f);
    const glm::vec4 ORANGE(1.0f, 0.5f, 0.0f, 1.0f);
    const glm::vec4 PURPLE(0.5f, 0.0f, 0.5f, 1.0f);
    const glm::vec4 PINK(1.0f, 0.75f, 0.8f, 1.0f);
    const glm::vec4 BROWN(0.6f, 0.4f, 0.2f, 1.0f);
    
    glm::vec4 fromRGB(float r, float g, float b, float a) {
        return glm::vec4(r, g, b, a);
    }
    
    glm::vec4 fromHSV(float h, float s, float v, float a) {
        float r, g, b;
        HSVtoRGB(h, s, v, r, g, b);
        return glm::vec4(r, g, b, a);
    }
    
    glm::vec4 blend(const glm::vec4& a, const glm::vec4& b, float t) {
        return a + (b - a) * t;
    }
    
    glm::vec4 darken(const glm::vec4& color, float factor) {
        return glm::vec4(color.rgb() * (1.0f - factor), color.a);
    }
    
    glm::vec4 lighten(const glm::vec4& color, float factor) {
        return glm::vec4(color.rgb() + (glm::vec3(1.0f) - color.rgb()) * factor, color.a);
    }
    
    glm::vec4 setAlpha(const glm::vec4& color, float alpha) {
        return glm::vec4(color.rgb(), alpha);
    }
    
    void RGBtoHSV(float r, float g, float b, float& h, float& s, float& v) {
        float max = std::max({r, g, b});
        float min = std::min({r, g, b});
        float delta = max - min;
        
        v = max;
        
        if (max == 0.0f) {
            s = 0.0f;
            h = 0.0f;
            return;
        }
        
        s = delta / max;
        
        if (delta == 0.0f) {
            h = 0.0f;
        } else if (max == r) {
            h = fmod((g - b) / delta, 6.0f);
        } else if (max == g) {
            h = (b - r) / delta + 2.0f;
        } else {
            h = (r - g) / delta + 4.0f;
        }
        
        h *= 60.0f;
        if (h < 0.0f) h += 360.0f;
    }
    
    void HSVtoRGB(float h, float s, float v, float& r, float& g, float& b) {
        if (s == 0.0f) {
            r = g = b = v;
            return;
        }
        
        h /= 60.0f;
        int i = static_cast<int>(h);
        float f = h - i;
        float p = v * (1.0f - s);
        float q = v * (1.0f - s * f);
        float t = v * (1.0f - s * (1.0f - f));
        
        switch (i) {
            case 0: r = v; g = t; b = p; break;
            case 1: r = q; g = v; b = p; break;
            case 2: r = p; g = v; b = t; break;
            case 3: r = p; g = q; b = v; break;
            case 4: r = t; g = p; b = v; break;
            default: r = v; g = p; b = q; break;
        }
    }
    
    float getLuminance(const glm::vec4& color) {
        return 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
    }
    
    bool isDark(const glm::vec4& color) {
        return getLuminance(color) < 0.5f;
    }
    
    glm::vec4 getContrastColor(const glm::vec4& color) {
        return isDark(color) ? WHITE : BLACK;
    }
    
} // namespace Colors 
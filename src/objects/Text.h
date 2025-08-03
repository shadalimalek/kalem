#pragma once

#include "AnimationObject.h"
#include <string>

/**
 * @brief Text object for rendering text and labels
 * 
 * Provides text rendering capabilities with customizable
 * font, size, color, and positioning.
 */
class TextObject : public AnimationObject {
public:
    TextObject(float x, float y, const std::string& text);
    virtual ~TextObject();

    // Text properties
    void setText(const std::string& text);
    std::string getText() const;
    
    void setFontSize(float size);
    float getFontSize() const;
    
    void setFontFamily(const std::string& family);
    std::string getFontFamily() const;
    
    void setBold(bool bold);
    bool isBold() const;
    
    void setItalic(bool italic);
    bool isItalic() const;
    
    // Text alignment
    enum class Alignment {
        Left,
        Center,
        Right
    };
    
    void setAlignment(Alignment alignment);
    Alignment getAlignment() const;
    
    // Rendering
    void render() override;
    
    // Collision detection
    bool intersects(const AnimationObject* other) const override;
    glm::vec3 getCollisionNormal(const AnimationObject* other) const override;
    
    // Bounding box
    glm::vec3 getMinBounds() const override;
    glm::vec3 getMaxBounds() const override;
    
    // Cloning
    std::shared_ptr<AnimationObject> clone() const override;
    
    // Type information
    std::string getTypeName() const override;

private:
    std::string m_text;
    float m_fontSize;
    std::string m_fontFamily;
    bool m_bold;
    bool m_italic;
    Alignment m_alignment;
    
    // Helper methods
    void updateTextBounds();
    void renderText();
}; 
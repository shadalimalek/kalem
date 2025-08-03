#include "Text.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

TextObject::TextObject(float x, float y, const std::string& text)
    : AnimationObject("Text")
    , m_text(text)
    , m_fontSize(16.0f)
    , m_fontFamily("Arial")
    , m_bold(false)
    , m_italic(false)
    , m_alignment(Alignment::Left) {
    setPosition(x, y, 0.0f);
    updateTextBounds();
}

TextObject::~TextObject() {
}

void TextObject::setText(const std::string& text) {
    m_text = text;
    updateTextBounds();
}

std::string TextObject::getText() const {
    return m_text;
}

void TextObject::setFontSize(float size) {
    m_fontSize = size;
    updateTextBounds();
}

float TextObject::getFontSize() const {
    return m_fontSize;
}

void TextObject::setFontFamily(const std::string& family) {
    m_fontFamily = family;
}

std::string TextObject::getFontFamily() const {
    return m_fontFamily;
}

void TextObject::setBold(bool bold) {
    m_bold = bold;
}

bool TextObject::isBold() const {
    return m_bold;
}

void TextObject::setItalic(bool italic) {
    m_italic = italic;
}

bool TextObject::isItalic() const {
    return m_italic;
}

void TextObject::setAlignment(Alignment alignment) {
    m_alignment = alignment;
}

TextObject::Alignment TextObject::getAlignment() const {
    return m_alignment;
}

void TextObject::render() {
    if (!isVisible() || m_text.empty()) return;
    
    // For now, we'll use a simple approach with OpenGL immediate mode
    // In a real implementation, you'd use a proper text rendering library like FreeType
    
    glPushMatrix();
    
    // Apply transformations
    glm::mat4 transform = getTransformMatrix();
    glLoadMatrixf(&transform[0][0]);
    
    // Set color
    glm::vec4 color = getColor();
    glColor4f(color.r, color.g, color.b, color.a * getOpacity());
    
    // Simple text rendering using GLUT bitmap characters
    // This is a basic implementation - in production you'd use proper text rendering
    renderText();
    
    glPopMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  // Reset color
}

bool TextObject::intersects(const AnimationObject* other) const {
    if (!other) return false;
    
    // Simple bounding box intersection for text
    glm::vec3 min1 = getMinBounds();
    glm::vec3 max1 = getMaxBounds();
    glm::vec3 min2 = other->getMinBounds();
    glm::vec3 max2 = other->getMaxBounds();
    
    return (min1.x <= max2.x && max1.x >= min2.x &&
            min1.y <= max2.y && max1.y >= min2.y);
}

glm::vec3 TextObject::getCollisionNormal(const AnimationObject* other) const {
    if (!other) return glm::vec3(0.0f);
    
    glm::vec3 pos1 = getPosition();
    glm::vec3 pos2 = other->getPosition();
    
    return glm::normalize(pos1 - pos2);
}

glm::vec3 TextObject::getMinBounds() const {
    glm::vec3 pos = getPosition();
    float width = m_text.length() * m_fontSize * 0.6f;  // Approximate character width
    float height = m_fontSize;
    
    // Adjust for alignment
    float offsetX = 0.0f;
    switch (m_alignment) {
        case Alignment::Center:
            offsetX = -width * 0.5f;
            break;
        case Alignment::Right:
            offsetX = -width;
            break;
        default:
            break;
    }
    
    return pos + glm::vec3(offsetX, -height * 0.5f, 0.0f);
}

glm::vec3 TextObject::getMaxBounds() const {
    glm::vec3 pos = getPosition();
    float width = m_text.length() * m_fontSize * 0.6f;  // Approximate character width
    float height = m_fontSize;
    
    // Adjust for alignment
    float offsetX = 0.0f;
    switch (m_alignment) {
        case Alignment::Center:
            offsetX = width * 0.5f;
            break;
        case Alignment::Right:
            offsetX = 0.0f;
            break;
        default:
            offsetX = width;
            break;
    }
    
    return pos + glm::vec3(offsetX, height * 0.5f, 0.0f);
}

std::shared_ptr<AnimationObject> TextObject::clone() const {
    auto text = std::make_shared<TextObject>(getPosition().x, getPosition().y, m_text);
    text->setColor(getColor());
    text->setScale(getScale());
    text->setRotation(getRotation());
    text->setVisible(isVisible());
    text->setOpacity(getOpacity());
    text->setFontSize(m_fontSize);
    text->setFontFamily(m_fontFamily);
    text->setBold(m_bold);
    text->setItalic(m_italic);
    text->setAlignment(m_alignment);
    return text;
}

std::string TextObject::getTypeName() const {
    return "Text";
}

void TextObject::updateTextBounds() {
    // Update the object's scale based on text size
    float width = m_text.length() * m_fontSize * 0.6f;  // Approximate character width
    float height = m_fontSize;
    setScale(width, height, 1.0f);
}

void TextObject::renderText() {
    // Simple text rendering using OpenGL immediate mode
    // This is a placeholder - in a real implementation you'd use proper text rendering
    
    // For now, we'll just draw a rectangle to represent the text
    // In production, you'd use FreeType or similar for proper text rendering
    
    float width = m_text.length() * m_fontSize * 0.6f;
    float height = m_fontSize;
    
    // Adjust position based on alignment
    float offsetX = 0.0f;
    switch (m_alignment) {
        case Alignment::Center:
            offsetX = -width * 0.5f;
            break;
        case Alignment::Right:
            offsetX = -width;
            break;
        default:
            break;
    }
    
    // Draw a simple rectangle to represent the text area
    glBegin(GL_QUADS);
    glVertex2f(offsetX, -height * 0.5f);
    glVertex2f(offsetX + width, -height * 0.5f);
    glVertex2f(offsetX + width, height * 0.5f);
    glVertex2f(offsetX, height * 0.5f);
    glEnd();
    
    // In a real implementation, you would:
    // 1. Load a font using FreeType
    // 2. Generate texture atlas for characters
    // 3. Render each character as a textured quad
    // 4. Handle different font styles, sizes, and alignments
} 
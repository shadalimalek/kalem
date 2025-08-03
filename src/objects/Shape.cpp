#include "Shape.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

// ============================================================================
// SHAPE BASE CLASS
// ============================================================================

Shape::Shape(const std::string& name)
    : AnimationObject(name)
    , m_size(1.0f, 1.0f) {
}

Shape::~Shape() {
}

void Shape::setSize(float width, float height) {
    m_size = glm::vec2(width, height);
    updateBounds();
}

glm::vec2 Shape::getSize() const {
    return m_size;
}

bool Shape::intersects(const AnimationObject* other) const {
    if (!other) return false;
    
    // Check if other is a shape
    const Shape* otherShape = dynamic_cast<const Shape*>(other);
    if (!otherShape) return false;
    
    // Get bounding boxes
    glm::vec3 min1 = getMinBounds();
    glm::vec3 max1 = getMaxBounds();
    glm::vec3 min2 = otherShape->getMinBounds();
    glm::vec3 max2 = otherShape->getMaxBounds();
    
    // Check for overlap
    return (min1.x <= max2.x && max1.x >= min2.x &&
            min1.y <= max2.y && max1.y >= min2.y);
}

glm::vec3 Shape::getCollisionNormal(const AnimationObject* other) const {
    if (!other) return glm::vec3(0.0f);
    
    glm::vec3 pos1 = getPosition();
    glm::vec3 pos2 = other->getPosition();
    
    return glm::normalize(pos1 - pos2);
}

glm::vec3 Shape::getMinBounds() const {
    glm::vec3 pos = getPosition();
    glm::vec3 scale = getScale();
    return pos - glm::vec3(m_size.x * scale.x * 0.5f, m_size.y * scale.y * 0.5f, 0.0f);
}

glm::vec3 Shape::getMaxBounds() const {
    glm::vec3 pos = getPosition();
    glm::vec3 scale = getScale();
    return pos + glm::vec3(m_size.x * scale.x * 0.5f, m_size.y * scale.y * 0.5f, 0.0f);
}

void Shape::updateBounds() {
    // Update scale based on size
    setScale(m_size.x, m_size.y, 1.0f);
}

// ============================================================================
// CIRCLE CLASS
// ============================================================================

Circle::Circle(float x, float y, float radius)
    : Shape("Circle")
    , m_radius(radius) {
    setPosition(x, y, 0.0f);
    setSize(radius * 2.0f, radius * 2.0f);
}

Circle::~Circle() {
}

void Circle::setRadius(float radius) {
    m_radius = radius;
    setSize(radius * 2.0f, radius * 2.0f);
}

float Circle::getRadius() const {
    return m_radius;
}

void Circle::setSize(float width, float height) {
    float radius = std::min(width, height) * 0.5f;
    m_radius = radius;
    Shape::setSize(radius * 2.0f, radius * 2.0f);
}

glm::vec2 Circle::getSize() const {
    return glm::vec2(m_radius * 2.0f, m_radius * 2.0f);
}

void Circle::render() {
    if (!isVisible()) return;
    
    // Simple OpenGL immediate mode rendering for now
    // In a real implementation, you'd use vertex buffers and shaders
    
    glPushMatrix();
    
    // Apply transformations
    glm::mat4 transform = getTransformMatrix();
    glLoadMatrixf(&transform[0][0]);
    
    // Set color
    glm::vec4 color = getColor();
    glColor4f(color.r, color.g, color.b, color.a * getOpacity());
    
    // Draw circle using triangle fan
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);  // Center
    
    const int segments = 32;
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float x = cos(angle);
        float y = sin(angle);
        glVertex2f(x, y);
    }
    
    glEnd();
    
    glPopMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  // Reset color
}

bool Circle::intersects(const AnimationObject* other) const {
    if (!other) return false;
    
    // Circle-circle intersection
    const Circle* otherCircle = dynamic_cast<const Circle*>(other);
    if (otherCircle) {
        glm::vec3 pos1 = getPosition();
        glm::vec3 pos2 = otherCircle->getPosition();
        float distance = glm::length(pos1 - pos2);
        float radius1 = m_radius * getScale().x;
        float radius2 = otherCircle->getRadius() * otherCircle->getScale().x;
        return distance < (radius1 + radius2);
    }
    
    // Fall back to base class implementation
    return Shape::intersects(other);
}

glm::vec3 Circle::getCollisionNormal(const AnimationObject* other) const {
    if (!other) return glm::vec3(0.0f);
    
    glm::vec3 pos1 = getPosition();
    glm::vec3 pos2 = other->getPosition();
    
    return glm::normalize(pos1 - pos2);
}

glm::vec3 Circle::getMinBounds() const {
    glm::vec3 pos = getPosition();
    float radius = m_radius * getScale().x;
    return pos - glm::vec3(radius, radius, 0.0f);
}

glm::vec3 Circle::getMaxBounds() const {
    glm::vec3 pos = getPosition();
    float radius = m_radius * getScale().x;
    return pos + glm::vec3(radius, radius, 0.0f);
}

std::shared_ptr<AnimationObject> Circle::clone() const {
    auto circle = std::make_shared<Circle>(getPosition().x, getPosition().y, m_radius);
    circle->setColor(getColor());
    circle->setScale(getScale());
    circle->setRotation(getRotation());
    circle->setVisible(isVisible());
    circle->setOpacity(getOpacity());
    return circle;
}

std::string Circle::getTypeName() const {
    return "Circle";
}

bool Circle::pointInside(float x, float y) const {
    glm::vec3 pos = getPosition();
    float dx = x - pos.x;
    float dy = y - pos.y;
    float radius = m_radius * getScale().x;
    return (dx * dx + dy * dy) <= (radius * radius);
}

// ============================================================================
// RECTANGLE CLASS
// ============================================================================

Rectangle::Rectangle(float x, float y, float width, float height)
    : Shape("Rectangle") {
    setPosition(x, y, 0.0f);
    setSize(width, height);
}

Rectangle::~Rectangle() {
}

void Rectangle::setWidth(float width) {
    m_size.x = width;
    updateBounds();
}

void Rectangle::setHeight(float height) {
    m_size.y = height;
    updateBounds();
}

float Rectangle::getWidth() const {
    return m_size.x;
}

float Rectangle::getHeight() const {
    return m_size.y;
}

void Rectangle::setSize(float width, float height) {
    Shape::setSize(width, height);
}

glm::vec2 Rectangle::getSize() const {
    return Shape::getSize();
}

void Rectangle::render() {
    if (!isVisible()) return;
    
    glPushMatrix();
    
    // Apply transformations
    glm::mat4 transform = getTransformMatrix();
    glLoadMatrixf(&transform[0][0]);
    
    // Set color
    glm::vec4 color = getColor();
    glColor4f(color.r, color.g, color.b, color.a * getOpacity());
    
    // Draw rectangle
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f( 0.5f, -0.5f);
    glVertex2f( 0.5f,  0.5f);
    glVertex2f(-0.5f,  0.5f);
    glEnd();
    
    glPopMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  // Reset color
}

bool Rectangle::intersects(const AnimationObject* other) const {
    if (!other) return false;
    
    // Rectangle-rectangle intersection
    const Rectangle* otherRect = dynamic_cast<const Rectangle*>(other);
    if (otherRect) {
        glm::vec3 min1 = getMinBounds();
        glm::vec3 max1 = getMaxBounds();
        glm::vec3 min2 = otherRect->getMinBounds();
        glm::vec3 max2 = otherRect->getMaxBounds();
        
        return (min1.x <= max2.x && max1.x >= min2.x &&
                min1.y <= max2.y && max1.y >= min2.y);
    }
    
    // Fall back to base class implementation
    return Shape::intersects(other);
}

glm::vec3 Rectangle::getCollisionNormal(const AnimationObject* other) const {
    if (!other) return glm::vec3(0.0f);
    
    glm::vec3 pos1 = getPosition();
    glm::vec3 pos2 = other->getPosition();
    
    return glm::normalize(pos1 - pos2);
}

glm::vec3 Rectangle::getMinBounds() const {
    return Shape::getMinBounds();
}

glm::vec3 Rectangle::getMaxBounds() const {
    return Shape::getMaxBounds();
}

std::shared_ptr<AnimationObject> Rectangle::clone() const {
    auto rect = std::make_shared<Rectangle>(getPosition().x, getPosition().y, m_size.x, m_size.y);
    rect->setColor(getColor());
    rect->setScale(getScale());
    rect->setRotation(getRotation());
    rect->setVisible(isVisible());
    rect->setOpacity(getOpacity());
    return rect;
}

std::string Rectangle::getTypeName() const {
    return "Rectangle";
}

bool Rectangle::pointInside(float x, float y) const {
    glm::vec3 pos = getPosition();
    glm::vec3 scale = getScale();
    float halfWidth = m_size.x * scale.x * 0.5f;
    float halfHeight = m_size.y * scale.y * 0.5f;
    
    return (x >= pos.x - halfWidth && x <= pos.x + halfWidth &&
            y >= pos.y - halfHeight && y <= pos.y + halfHeight);
}

// ============================================================================
// LINE CLASS
// ============================================================================

Line::Line(float x1, float y1, float x2, float y2)
    : Shape("Line")
    , m_startPoint(x1, y1)
    , m_endPoint(x2, y2)
    , m_thickness(1.0f) {
    
    // Calculate center position
    float centerX = (x1 + x2) * 0.5f;
    float centerY = (y1 + y2) * 0.5f;
    setPosition(centerX, centerY, 0.0f);
    
    // Calculate size
    float width = abs(x2 - x1);
    float height = abs(y2 - y1);
    setSize(width, height);
}

Line::~Line() {
}

void Line::setStartPoint(float x, float y) {
    m_startPoint = glm::vec2(x, y);
    updateLine();
}

void Line::setEndPoint(float x, float y) {
    m_endPoint = glm::vec2(x, y);
    updateLine();
}

glm::vec2 Line::getStartPoint() const {
    return m_startPoint;
}

glm::vec2 Line::getEndPoint() const {
    return m_endPoint;
}

void Line::setThickness(float thickness) {
    m_thickness = thickness;
}

float Line::getThickness() const {
    return m_thickness;
}

void Line::setSize(float width, float height) {
    Shape::setSize(width, height);
}

glm::vec2 Line::getSize() const {
    return Shape::getSize();
}

void Line::render() {
    if (!isVisible()) return;
    
    // Set color
    glm::vec4 color = getColor();
    glColor4f(color.r, color.g, color.b, color.a * getOpacity());
    
    // Set line width
    glLineWidth(m_thickness);
    
    // Draw line
    glBegin(GL_LINES);
    glVertex2f(m_startPoint.x, m_startPoint.y);
    glVertex2f(m_endPoint.x, m_endPoint.y);
    glEnd();
    
    glLineWidth(1.0f);  // Reset line width
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  // Reset color
}

bool Line::intersects(const AnimationObject* other) const {
    if (!other) return false;
    
    // Line-circle intersection
    const Circle* circle = dynamic_cast<const Circle*>(other);
    if (circle) {
        glm::vec3 circlePos = circle->getPosition();
        float circleRadius = circle->getRadius() * circle->getScale().x;
        
        // Calculate distance from line to circle center
        float distance = distanceToLine(circlePos.x, circlePos.y);
        return distance <= circleRadius;
    }
    
    // Fall back to base class implementation
    return Shape::intersects(other);
}

glm::vec3 Line::getCollisionNormal(const AnimationObject* other) const {
    if (!other) return glm::vec3(0.0f);
    
    glm::vec3 pos1 = getPosition();
    glm::vec3 pos2 = other->getPosition();
    
    return glm::normalize(pos1 - pos2);
}

glm::vec3 Line::getMinBounds() const {
    float minX = std::min(m_startPoint.x, m_endPoint.x);
    float minY = std::min(m_startPoint.y, m_endPoint.y);
    return glm::vec3(minX, minY, 0.0f);
}

glm::vec3 Line::getMaxBounds() const {
    float maxX = std::max(m_startPoint.x, m_endPoint.x);
    float maxY = std::max(m_startPoint.y, m_endPoint.y);
    return glm::vec3(maxX, maxY, 0.0f);
}

std::shared_ptr<AnimationObject> Line::clone() const {
    auto line = std::make_shared<Line>(m_startPoint.x, m_startPoint.y, m_endPoint.x, m_endPoint.y);
    line->setColor(getColor());
    line->setScale(getScale());
    line->setRotation(getRotation());
    line->setVisible(isVisible());
    line->setOpacity(getOpacity());
    line->setThickness(m_thickness);
    return line;
}

std::string Line::getTypeName() const {
    return "Line";
}

bool Line::pointInside(float x, float y) const {
    // Check if point is close to the line
    float distance = distanceToLine(x, y);
    return distance <= m_thickness * 0.5f;
}

void Line::updateLine() {
    // Update center position
    float centerX = (m_startPoint.x + m_endPoint.x) * 0.5f;
    float centerY = (m_startPoint.y + m_endPoint.y) * 0.5f;
    setPosition(centerX, centerY, 0.0f);
    
    // Update size
    float width = abs(m_endPoint.x - m_startPoint.x);
    float height = abs(m_endPoint.y - m_startPoint.y);
    setSize(width, height);
}

float Line::distanceToLine(float x, float y) const {
    // Calculate distance from point to line segment
    float A = x - m_startPoint.x;
    float B = y - m_startPoint.y;
    float C = m_endPoint.x - m_startPoint.x;
    float D = m_endPoint.y - m_startPoint.y;
    
    float dot = A * C + B * D;
    float lenSq = C * C + D * D;
    
    if (lenSq == 0) {
        // Line is a point
        return sqrt(A * A + B * B);
    }
    
    float param = dot / lenSq;
    
    float xx, yy;
    if (param < 0) {
        xx = m_startPoint.x;
        yy = m_startPoint.y;
    } else if (param > 1) {
        xx = m_endPoint.x;
        yy = m_endPoint.y;
    } else {
        xx = m_startPoint.x + param * C;
        yy = m_startPoint.y + param * D;
    }
    
    float dx = x - xx;
    float dy = y - yy;
    return sqrt(dx * dx + dy * dy);
} 
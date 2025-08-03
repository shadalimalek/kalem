#include "AnimationObject.h"
#include <iostream>
#include <cmath>

AnimationObject::AnimationObject(const std::string& name)
    : m_name(name)
    , m_position(0.0f, 0.0f, 0.0f)
    , m_scale(1.0f, 1.0f, 1.0f)
    , m_rotation(0.0f, 0.0f, 0.0f)
    , m_color(1.0f, 1.0f, 1.0f, 1.0f)
    , m_visible(true)
    , m_opacity(1.0f)
    , m_animationProgress(0.0f)
    , m_mass(1.0f)
    , m_velocity(0.0f, 0.0f, 0.0f)
    , m_acceleration(0.0f, 0.0f, 0.0f)
    , m_bounce(0.0f)
    , m_friction(0.1f)
    , m_isStatic(false)
    , m_gravityAffected(false)
    , m_renderOrder(0)
    , m_layer(0)
    , m_scene(nullptr) {
}

AnimationObject::~AnimationObject() {
}

// ============================================================================
// PROPERTIES
// ============================================================================

void AnimationObject::setPosition(float x, float y, float z) {
    m_position = glm::vec3(x, y, z);
    notifyPositionChanged();
}

void AnimationObject::setPosition(const glm::vec3& position) {
    m_position = position;
    notifyPositionChanged();
}

glm::vec3 AnimationObject::getPosition() const {
    return m_position;
}

void AnimationObject::setScale(float x, float y, float z) {
    m_scale = glm::vec3(x, y, z);
}

void AnimationObject::setScale(const glm::vec3& scale) {
    m_scale = scale;
}

glm::vec3 AnimationObject::getScale() const {
    return m_scale;
}

void AnimationObject::setRotation(float x, float y, float z) {
    m_rotation = glm::vec3(x, y, z);
}

void AnimationObject::setRotation(const glm::vec3& rotation) {
    m_rotation = rotation;
}

glm::vec3 AnimationObject::getRotation() const {
    return m_rotation;
}

void AnimationObject::setColor(float r, float g, float b, float a) {
    m_color = glm::vec4(r, g, b, a);
    notifyColorChanged();
}

void AnimationObject::setColor(const glm::vec4& color) {
    m_color = color;
    notifyColorChanged();
}

glm::vec4 AnimationObject::getColor() const {
    return m_color;
}

void AnimationObject::setVisible(bool visible) {
    m_visible = visible;
}

bool AnimationObject::isVisible() const {
    return m_visible;
}

void AnimationObject::setOpacity(float opacity) {
    m_opacity = std::max(0.0f, std::min(1.0f, opacity));
}

float AnimationObject::getOpacity() const {
    return m_opacity;
}

void AnimationObject::setName(const std::string& name) {
    m_name = name;
}

std::string AnimationObject::getName() const {
    return m_name;
}

// ============================================================================
// TRANSFORMATIONS
// ============================================================================

glm::mat4 AnimationObject::getTransformMatrix() const {
    glm::mat4 transform = glm::mat4(1.0f);
    
    // Apply transformations in order: scale, rotate, translate
    transform = glm::translate(transform, m_position);
    transform = glm::rotate(transform, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::rotate(transform, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::scale(transform, m_scale);
    
    return transform;
}

void AnimationObject::translate(float x, float y, float z) {
    m_position += glm::vec3(x, y, z);
    notifyPositionChanged();
}

void AnimationObject::rotate(float x, float y, float z) {
    m_rotation += glm::vec3(x, y, z);
}

void AnimationObject::scale(float x, float y, float z) {
    m_scale *= glm::vec3(x, y, z);
}

// ============================================================================
// ANIMATION
// ============================================================================

void AnimationObject::setAnimationProgress(float progress) {
    m_animationProgress = std::max(0.0f, std::min(1.0f, progress));
}

float AnimationObject::getAnimationProgress() const {
    return m_animationProgress;
}

void AnimationObject::setAnimationCallback(std::function<void(float)> callback) {
    m_animationCallback = callback;
}

void AnimationObject::clearAnimationCallback() {
    m_animationCallback = nullptr;
}

// ============================================================================
// EVENTS
// ============================================================================

void AnimationObject::addEventListener(EventType type, EventCallback callback) {
    m_eventCallbacks.push_back(std::make_pair(type, callback));
}

void AnimationObject::removeEventListener(EventType type, EventCallback callback) {
    m_eventCallbacks.erase(
        std::remove_if(m_eventCallbacks.begin(), m_eventCallbacks.end(),
            [type, &callback](const std::pair<EventType, EventCallback>& pair) {
                return pair.first == type && pair.second.target_type() == callback.target_type();
            }),
        m_eventCallbacks.end()
    );
}

void AnimationObject::triggerEvent(EventType type) {
    for (const auto& pair : m_eventCallbacks) {
        if (pair.first == type && pair.second) {
            pair.second(this, type);
        }
    }
}

// ============================================================================
// PHYSICS
// ============================================================================

void AnimationObject::setMass(float mass) {
    m_mass = std::max(0.001f, mass);
}

float AnimationObject::getMass() const {
    return m_mass;
}

void AnimationObject::setVelocity(float x, float y, float z) {
    m_velocity = glm::vec3(x, y, z);
}

void AnimationObject::setVelocity(const glm::vec3& velocity) {
    m_velocity = velocity;
}

glm::vec3 AnimationObject::getVelocity() const {
    return m_velocity;
}

void AnimationObject::setAcceleration(float x, float y, float z) {
    m_acceleration = glm::vec3(x, y, z);
}

void AnimationObject::setAcceleration(const glm::vec3& acceleration) {
    m_acceleration = acceleration;
}

glm::vec3 AnimationObject::getAcceleration() const {
    return m_acceleration;
}

void AnimationObject::setBounce(float bounce) {
    m_bounce = std::max(0.0f, std::min(1.0f, bounce));
}

float AnimationObject::getBounce() const {
    return m_bounce;
}

void AnimationObject::setFriction(float friction) {
    m_friction = std::max(0.0f, std::min(1.0f, friction));
}

float AnimationObject::getFriction() const {
    return m_friction;
}

void AnimationObject::setStatic(bool isStatic) {
    m_isStatic = isStatic;
}

bool AnimationObject::isStatic() const {
    return m_isStatic;
}

void AnimationObject::setGravityAffected(bool affected) {
    m_gravityAffected = affected;
}

bool AnimationObject::isGravityAffected() const {
    return m_gravityAffected;
}

// ============================================================================
// COLLISION
// ============================================================================

bool AnimationObject::intersects(const AnimationObject* other) const {
    if (!other) return false;
    
    // Simple circle-circle intersection for now
    glm::vec3 pos1 = getPosition();
    glm::vec3 pos2 = other->getPosition();
    
    float distance = glm::length(pos1 - pos2);
    float radius1 = getScale().x;
    float radius2 = other->getScale().x;
    
    return distance < (radius1 + radius2);
}

glm::vec3 AnimationObject::getCollisionNormal(const AnimationObject* other) const {
    if (!other) return glm::vec3(0.0f);
    
    glm::vec3 pos1 = getPosition();
    glm::vec3 pos2 = other->getPosition();
    
    return glm::normalize(pos1 - pos2);
}

glm::vec3 AnimationObject::getMinBounds() const {
    glm::vec3 pos = getPosition();
    glm::vec3 scale = getScale();
    return pos - scale * 0.5f;
}

glm::vec3 AnimationObject::getMaxBounds() const {
    glm::vec3 pos = getPosition();
    glm::vec3 scale = getScale();
    return pos + scale * 0.5f;
}

// ============================================================================
// RENDERING
// ============================================================================

void AnimationObject::update(float deltaTime) {
    internalUpdate(deltaTime);
    
    // Call animation callback if set
    if (m_animationCallback) {
        m_animationCallback(m_animationProgress);
    }
}

void AnimationObject::setRenderOrder(int order) {
    m_renderOrder = order;
}

int AnimationObject::getRenderOrder() const {
    return m_renderOrder;
}

void AnimationObject::setLayer(int layer) {
    m_layer = layer;
}

int AnimationObject::getLayer() const {
    return m_layer;
}

// ============================================================================
// SERIALIZATION
// ============================================================================

void AnimationObject::serialize(std::ostream& stream) const {
    // Basic serialization - can be extended
    stream << "Object: " << m_name << std::endl;
    stream << "Position: " << m_position.x << ", " << m_position.y << ", " << m_position.z << std::endl;
    stream << "Scale: " << m_scale.x << ", " << m_scale.y << ", " << m_scale.z << std::endl;
    stream << "Color: " << m_color.r << ", " << m_color.g << ", " << m_color.b << ", " << m_color.a << std::endl;
}

void AnimationObject::deserialize(std::istream& stream) {
    // Basic deserialization - can be extended
    // Implementation would parse the stream and set properties
}

std::string AnimationObject::toJSON() const {
    // Basic JSON representation
    return "{\"name\":\"" + m_name + "\",\"type\":\"" + getTypeName() + "\"}";
}

void AnimationObject::fromJSON(const std::string& json) {
    // Basic JSON parsing - can be extended
    // Implementation would parse JSON and set properties
}

// ============================================================================
// UTILITY
// ============================================================================

float AnimationObject::distanceTo(const AnimationObject* other) const {
    if (!other) return 0.0f;
    
    glm::vec3 pos1 = getPosition();
    glm::vec3 pos2 = other->getPosition();
    
    return glm::length(pos1 - pos2);
}

glm::vec3 AnimationObject::directionTo(const AnimationObject* other) const {
    if (!other) return glm::vec3(0.0f);
    
    glm::vec3 pos1 = getPosition();
    glm::vec3 pos2 = other->getPosition();
    
    return glm::normalize(pos2 - pos1);
}

std::string AnimationObject::getDebugInfo() const {
    std::string info = "Object: " + m_name + " (" + getTypeName() + ")\n";
    info += "Position: (" + std::to_string(m_position.x) + ", " + std::to_string(m_position.y) + ", " + std::to_string(m_position.z) + ")\n";
    info += "Scale: (" + std::to_string(m_scale.x) + ", " + std::to_string(m_scale.y) + ", " + std::to_string(m_scale.z) + ")\n";
    info += "Visible: " + std::string(m_visible ? "true" : "false") + "\n";
    info += "Mass: " + std::to_string(m_mass) + "\n";
    return info;
}

// ============================================================================
// PROTECTED METHODS
// ============================================================================

void AnimationObject::notifyPositionChanged() {
    triggerEvent(EventType::PositionChanged);
}

void AnimationObject::notifyColorChanged() {
    triggerEvent(EventType::ColorChanged);
}

void AnimationObject::notifyAnimationStarted() {
    triggerEvent(EventType::AnimationStarted);
}

void AnimationObject::notifyAnimationFinished() {
    triggerEvent(EventType::AnimationFinished);
}

void AnimationObject::internalUpdate(float deltaTime) {
    // Base implementation - can be overridden by derived classes
    // Update animation progress if needed
    if (m_animationProgress < 1.0f) {
        m_animationProgress += deltaTime * 0.5f; // Simple progress update
        if (m_animationProgress >= 1.0f) {
            m_animationProgress = 1.0f;
            notifyAnimationFinished();
        }
    }
} 
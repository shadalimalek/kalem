#pragma once

#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Forward declarations
class Scene;
class AnimationEngine;

/**
 * @brief Base class for all animation objects
 * 
 * This is the foundation of the Kalem animation system. All objects
 * (shapes, particles, text, etc.) inherit from this class.
 */
class AnimationObject {
public:
    // ============================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // ============================================================================
    
    AnimationObject(const std::string& name = "Object");
    virtual ~AnimationObject();
    
    // ============================================================================
    // PROPERTIES
    // ============================================================================
    
    // Position
    void setPosition(float x, float y, float z = 0.0f);
    void setPosition(const glm::vec3& position);
    glm::vec3 getPosition() const;
    
    // Scale
    void setScale(float x, float y, float z = 1.0f);
    void setScale(const glm::vec3& scale);
    glm::vec3 getScale() const;
    
    // Rotation
    void setRotation(float x, float y, float z);
    void setRotation(const glm::vec3& rotation);
    glm::vec3 getRotation() const;
    
    // Color
    void setColor(float r, float g, float b, float a = 1.0f);
    void setColor(const glm::vec4& color);
    glm::vec4 getColor() const;
    
    // Visibility
    void setVisible(bool visible);
    bool isVisible() const;
    
    // Opacity
    void setOpacity(float opacity);
    float getOpacity() const;
    
    // Name
    void setName(const std::string& name);
    std::string getName() const;
    
    // ============================================================================
    // TRANSFORMATIONS
    // ============================================================================
    
    // Transform matrix
    glm::mat4 getTransformMatrix() const;
    
    // Local transformations
    void translate(float x, float y, float z = 0.0f);
    void rotate(float x, float y, float z);
    void scale(float x, float y, float z = 1.0f);
    
    // ============================================================================
    // ANIMATION
    // ============================================================================
    
    // Animation state
    void setAnimationProgress(float progress);
    float getAnimationProgress() const;
    
    // Animation callbacks
    void setAnimationCallback(std::function<void(float)> callback);
    void clearAnimationCallback();
    
    // ============================================================================
    // EVENTS
    // ============================================================================
    
    // Event types
    enum class EventType {
        Created,
        Destroyed,
        PositionChanged,
        ColorChanged,
        AnimationStarted,
        AnimationFinished,
        Clicked,
        Hovered
    };
    
    // Event callback
    using EventCallback = std::function<void(AnimationObject*, EventType)>;
    
    void addEventListener(EventType type, EventCallback callback);
    void removeEventListener(EventType type, EventCallback callback);
    void triggerEvent(EventType type);
    
    // ============================================================================
    // PHYSICS
    // ============================================================================
    
    // Physics properties
    void setMass(float mass);
    float getMass() const;
    
    void setVelocity(float x, float y, float z = 0.0f);
    void setVelocity(const glm::vec3& velocity);
    glm::vec3 getVelocity() const;
    
    void setAcceleration(float x, float y, float z = 0.0f);
    void setAcceleration(const glm::vec3& acceleration);
    glm::vec3 getAcceleration() const;
    
    void setBounce(float bounce);
    float getBounce() const;
    
    void setFriction(float friction);
    float getFriction() const;
    
    // Physics flags
    void setStatic(bool isStatic);
    bool isStatic() const;
    
    void setGravityAffected(bool affected);
    bool isGravityAffected() const;
    
    // ============================================================================
    // COLLISION
    // ============================================================================
    
    // Collision detection
    virtual bool intersects(const AnimationObject* other) const;
    virtual glm::vec3 getCollisionNormal(const AnimationObject* other) const;
    
    // Bounding box
    virtual glm::vec3 getMinBounds() const;
    virtual glm::vec3 getMaxBounds() const;
    
    // ============================================================================
    // RENDERING
    // ============================================================================
    
    // Render methods
    virtual void render() = 0;
    virtual void update(float deltaTime);
    
    // Render properties
    void setRenderOrder(int order);
    int getRenderOrder() const;
    
    void setLayer(int layer);
    int getLayer() const;
    
    // ============================================================================
    // SERIALIZATION
    // ============================================================================
    
    // Save/Load
    virtual void serialize(std::ostream& stream) const;
    virtual void deserialize(std::istream& stream);
    
    // JSON support
    virtual std::string toJSON() const;
    virtual void fromJSON(const std::string& json);
    
    // ============================================================================
    // UTILITY
    // ============================================================================
    
    // Distance to another object
    float distanceTo(const AnimationObject* other) const;
    
    // Direction to another object
    glm::vec3 directionTo(const AnimationObject* other) const;
    
    // Clone object
    virtual std::shared_ptr<AnimationObject> clone() const = 0;
    
    // Type information
    virtual std::string getTypeName() const = 0;
    
    // Debug info
    virtual std::string getDebugInfo() const;

protected:
    // ============================================================================
    // PROTECTED MEMBERS
    // ============================================================================
    
    std::string m_name;
    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::vec3 m_rotation;
    glm::vec4 m_color;
    
    bool m_visible;
    float m_opacity;
    float m_animationProgress;
    
    // Physics
    float m_mass;
    glm::vec3 m_velocity;
    glm::vec3 m_acceleration;
    float m_bounce;
    float m_friction;
    bool m_isStatic;
    bool m_gravityAffected;
    
    // Rendering
    int m_renderOrder;
    int m_layer;
    
    // Events
    std::vector<std::pair<EventType, EventCallback>> m_eventCallbacks;
    
    // Animation
    std::function<void(float)> m_animationCallback;
    
    // Scene reference
    Scene* m_scene;
    
    // Helper methods
    void notifyPositionChanged();
    void notifyColorChanged();
    void notifyAnimationStarted();
    void notifyAnimationFinished();
    
    // Internal update
    virtual void internalUpdate(float deltaTime);
};

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

// Object factory
std::shared_ptr<AnimationObject> createObject(const std::string& type, const std::string& name = "");

// Object registry
void registerObjectType(const std::string& type, std::function<std::shared_ptr<AnimationObject>(const std::string&)> factory);

// Object management
std::vector<std::shared_ptr<AnimationObject>> findObjectsByType(const std::string& type);
std::shared_ptr<AnimationObject> findObjectByName(const std::string& name); 
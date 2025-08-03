#pragma once

#include "AnimationObject.h"
#include <glm/glm.hpp>

/**
 * @brief Particle class for physics simulations
 * 
 * Represents a physics-based particle with mass, velocity,
 * acceleration, and other physical properties.
 */
class Particle : public AnimationObject {
public:
    Particle(float x, float y, float mass = 1.0f);
    virtual ~Particle();

    // Particle properties
    void setRadius(float radius);
    float getRadius() const;
    
    void setLifetime(float lifetime);
    float getLifetime() const;
    
    void setAge(float age);
    float getAge() const;
    
    // Physics properties (inherited from AnimationObject)
    // - mass, velocity, acceleration, bounce, friction
    
    // Particle-specific physics
    void setDrag(float drag);
    float getDrag() const;
    
    void setAngularVelocity(float angularVelocity);
    float getAngularVelocity() const;
    
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
    
    // Update
    void update(float deltaTime) override;

private:
    float m_radius;
    float m_lifetime;
    float m_age;
    float m_drag;
    float m_angularVelocity;
    
    // Helper methods
    void updatePhysics(float deltaTime);
    void updateLifetime(float deltaTime);
}; 
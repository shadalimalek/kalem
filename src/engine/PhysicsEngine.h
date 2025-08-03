#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

// Forward declarations
class AnimationObject;

/**
 * @brief PhysicsEngine class for real-time physics simulation
 * 
 * Handles gravity, forces, collisions, and physics-based animations
 * for all objects in the scene.
 */
class PhysicsEngine {
public:
    PhysicsEngine();
    ~PhysicsEngine();

    // Physics control
    void setEnabled(bool enabled);
    bool isEnabled() const;
    
    // Physics properties
    void setGravity(const glm::vec3& gravity);
    glm::vec3 getGravity() const;
    
    void setAirResistance(float resistance);
    float getAirResistance() const;
    
    void setTimeStep(float timeStep);
    float getTimeStep() const;
    
    // Object management
    void addObject(std::shared_ptr<AnimationObject> obj);
    void removeObject(std::shared_ptr<AnimationObject> obj);
    void clearObjects();
    
    // Physics simulation
    void update(float deltaTime);
    void step(float deltaTime);
    
    // Collision detection
    void enableCollisionDetection(bool enable);
    bool isCollisionDetectionEnabled() const;
    
    void updateCollisions();
    void resolveCollisions();
    
    // Forces
    void applyForce(std::shared_ptr<AnimationObject> obj, const glm::vec3& force);
    void applyImpulse(std::shared_ptr<AnimationObject> obj, const glm::vec3& impulse);
    
    // Constraints
    void addGroundConstraint(float y = 0.0f);
    void addWallConstraint(float x, float y, float width, float height);
    
    // Physics queries
    std::vector<std::shared_ptr<AnimationObject>> getObjectsInArea(const glm::vec3& center, float radius);
    std::vector<std::shared_ptr<AnimationObject>> getObjectsInBox(const glm::vec3& min, const glm::vec3& max);

private:
    bool m_enabled;
    bool m_collisionDetectionEnabled;
    
    glm::vec3 m_gravity;
    float m_airResistance;
    float m_timeStep;
    
    std::vector<std::shared_ptr<AnimationObject>> m_physicsObjects;
    
    // Ground constraint
    bool m_groundConstraintEnabled;
    float m_groundY;
    
    // Wall constraints
    struct WallConstraint {
        float x, y, width, height;
    };
    std::vector<WallConstraint> m_wallConstraints;
    
    // Helper methods
    void updateObjectPhysics(std::shared_ptr<AnimationObject> obj, float deltaTime);
    void applyConstraints(std::shared_ptr<AnimationObject> obj);
    bool checkCollision(std::shared_ptr<AnimationObject> obj1, std::shared_ptr<AnimationObject> obj2);
    void resolveCollision(std::shared_ptr<AnimationObject> obj1, std::shared_ptr<AnimationObject> obj2);
    glm::vec3 calculateCollisionNormal(std::shared_ptr<AnimationObject> obj1, std::shared_ptr<AnimationObject> obj2);
}; 
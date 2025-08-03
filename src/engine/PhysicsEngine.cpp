#include "PhysicsEngine.h"
#include "../objects/AnimationObject.h"
#include <algorithm>
#include <iostream>

PhysicsEngine::PhysicsEngine()
    : m_enabled(false)
    , m_collisionDetectionEnabled(true)
    , m_gravity(0.0f, -9.81f, 0.0f)
    , m_airResistance(0.1f)
    , m_timeStep(1.0f / 60.0f)
    , m_groundConstraintEnabled(false)
    , m_groundY(0.0f) {
}

PhysicsEngine::~PhysicsEngine() {
    clearObjects();
}

void PhysicsEngine::setEnabled(bool enabled) {
    m_enabled = enabled;
}

bool PhysicsEngine::isEnabled() const {
    return m_enabled;
}

void PhysicsEngine::setGravity(const glm::vec3& gravity) {
    m_gravity = gravity;
}

glm::vec3 PhysicsEngine::getGravity() const {
    return m_gravity;
}

void PhysicsEngine::setAirResistance(float resistance) {
    m_airResistance = std::max(0.0f, std::min(1.0f, resistance));
}

float PhysicsEngine::getAirResistance() const {
    return m_airResistance;
}

void PhysicsEngine::setTimeStep(float timeStep) {
    m_timeStep = std::max(0.001f, timeStep);
}

float PhysicsEngine::getTimeStep() const {
    return m_timeStep;
}

void PhysicsEngine::addObject(std::shared_ptr<AnimationObject> obj) {
    if (obj) {
        m_physicsObjects.push_back(obj);
    }
}

void PhysicsEngine::removeObject(std::shared_ptr<AnimationObject> obj) {
    if (obj) {
        m_physicsObjects.erase(
            std::remove(m_physicsObjects.begin(), m_physicsObjects.end(), obj),
            m_physicsObjects.end()
        );
    }
}

void PhysicsEngine::clearObjects() {
    m_physicsObjects.clear();
}

void PhysicsEngine::update(float deltaTime) {
    if (!m_enabled) return;
    
    // Use fixed time step for physics
    float remainingTime = deltaTime;
    while (remainingTime >= m_timeStep) {
        step(m_timeStep);
        remainingTime -= m_timeStep;
    }
    
    // Handle remaining time
    if (remainingTime > 0.0f) {
        step(remainingTime);
    }
}

void PhysicsEngine::step(float deltaTime) {
    // Update physics for all objects
    for (auto& obj : m_physicsObjects) {
        if (obj && !obj->isStatic()) {
            updateObjectPhysics(obj, deltaTime);
        }
    }
    
    // Handle collisions
    if (m_collisionDetectionEnabled) {
        updateCollisions();
    }
    
    // Apply constraints
    for (auto& obj : m_physicsObjects) {
        if (obj) {
            applyConstraints(obj);
        }
    }
}

void PhysicsEngine::enableCollisionDetection(bool enable) {
    m_collisionDetectionEnabled = enable;
}

bool PhysicsEngine::isCollisionDetectionEnabled() const {
    return m_collisionDetectionEnabled;
}

void PhysicsEngine::updateCollisions() {
    // Simple collision detection between all objects
    for (size_t i = 0; i < m_physicsObjects.size(); ++i) {
        for (size_t j = i + 1; j < m_physicsObjects.size(); ++j) {
            auto obj1 = m_physicsObjects[i];
            auto obj2 = m_physicsObjects[j];
            
            if (obj1 && obj2 && checkCollision(obj1, obj2)) {
                resolveCollision(obj1, obj2);
            }
        }
    }
}

void PhysicsEngine::resolveCollisions() {
    // This is handled in updateCollisions()
}

void PhysicsEngine::applyForce(std::shared_ptr<AnimationObject> obj, const glm::vec3& force) {
    if (obj && !obj->isStatic()) {
        glm::vec3 currentAccel = obj->getAcceleration();
        obj->setAcceleration(currentAccel + force / obj->getMass());
    }
}

void PhysicsEngine::applyImpulse(std::shared_ptr<AnimationObject> obj, const glm::vec3& impulse) {
    if (obj && !obj->isStatic()) {
        glm::vec3 currentVel = obj->getVelocity();
        obj->setVelocity(currentVel + impulse / obj->getMass());
    }
}

void PhysicsEngine::addGroundConstraint(float y) {
    m_groundConstraintEnabled = true;
    m_groundY = y;
}

void PhysicsEngine::addWallConstraint(float x, float y, float width, float height) {
    WallConstraint wall;
    wall.x = x;
    wall.y = y;
    wall.width = width;
    wall.height = height;
    m_wallConstraints.push_back(wall);
}

std::vector<std::shared_ptr<AnimationObject>> PhysicsEngine::getObjectsInArea(const glm::vec3& center, float radius) {
    std::vector<std::shared_ptr<AnimationObject>> result;
    
    for (auto& obj : m_physicsObjects) {
        if (obj) {
            glm::vec3 pos = obj->getPosition();
            float distance = glm::length(pos - center);
            if (distance <= radius) {
                result.push_back(obj);
            }
        }
    }
    
    return result;
}

std::vector<std::shared_ptr<AnimationObject>> PhysicsEngine::getObjectsInBox(const glm::vec3& min, const glm::vec3& max) {
    std::vector<std::shared_ptr<AnimationObject>> result;
    
    for (auto& obj : m_physicsObjects) {
        if (obj) {
            glm::vec3 pos = obj->getPosition();
            if (pos.x >= min.x && pos.x <= max.x &&
                pos.y >= min.y && pos.y <= max.y &&
                pos.z >= min.z && pos.z <= max.z) {
                result.push_back(obj);
            }
        }
    }
    
    return result;
}

void PhysicsEngine::updateObjectPhysics(std::shared_ptr<AnimationObject> obj, float deltaTime) {
    if (!obj || obj->isStatic()) return;
    
    // Apply gravity
    if (obj->isGravityAffected()) {
        glm::vec3 currentAccel = obj->getAcceleration();
        obj->setAcceleration(currentAccel + m_gravity);
    }
    
    // Update velocity
    glm::vec3 currentVel = obj->getVelocity();
    glm::vec3 currentAccel = obj->getAcceleration();
    glm::vec3 newVel = currentVel + currentAccel * deltaTime;
    
    // Apply air resistance
    newVel *= (1.0f - m_airResistance * deltaTime);
    
    obj->setVelocity(newVel);
    
    // Update position
    glm::vec3 currentPos = obj->getPosition();
    glm::vec3 newPos = currentPos + newVel * deltaTime;
    obj->setPosition(newPos);
    
    // Reset acceleration (forces are applied per frame)
    obj->setAcceleration(glm::vec3(0.0f));
}

void PhysicsEngine::applyConstraints(std::shared_ptr<AnimationObject> obj) {
    if (!obj) return;
    
    glm::vec3 pos = obj->getPosition();
    glm::vec3 vel = obj->getVelocity();
    bool modified = false;
    
    // Ground constraint
    if (m_groundConstraintEnabled && pos.y < m_groundY) {
        pos.y = m_groundY;
        if (vel.y < 0.0f) {
            vel.y = -vel.y * obj->getBounce();
        }
        modified = true;
    }
    
    // Wall constraints
    for (const auto& wall : m_wallConstraints) {
        if (pos.x < wall.x) {
            pos.x = wall.x;
            if (vel.x < 0.0f) vel.x = -vel.x * obj->getBounce();
            modified = true;
        }
        if (pos.x > wall.x + wall.width) {
            pos.x = wall.x + wall.width;
            if (vel.x > 0.0f) vel.x = -vel.x * obj->getBounce();
            modified = true;
        }
        if (pos.y < wall.y) {
            pos.y = wall.y;
            if (vel.y < 0.0f) vel.y = -vel.y * obj->getBounce();
            modified = true;
        }
        if (pos.y > wall.y + wall.height) {
            pos.y = wall.y + wall.height;
            if (vel.y > 0.0f) vel.y = -vel.y * obj->getBounce();
            modified = true;
        }
    }
    
    if (modified) {
        obj->setPosition(pos);
        obj->setVelocity(vel);
    }
}

bool PhysicsEngine::checkCollision(std::shared_ptr<AnimationObject> obj1, std::shared_ptr<AnimationObject> obj2) {
    if (!obj1 || !obj2) return false;
    
    // Simple circle-circle collision for now
    glm::vec3 pos1 = obj1->getPosition();
    glm::vec3 pos2 = obj2->getPosition();
    
    float distance = glm::length(pos1 - pos2);
    float radius1 = obj1->getScale().x;  // Assuming uniform scale
    float radius2 = obj2->getScale().x;
    
    return distance < (radius1 + radius2);
}

void PhysicsEngine::resolveCollision(std::shared_ptr<AnimationObject> obj1, std::shared_ptr<AnimationObject> obj2) {
    if (!obj1 || !obj2) return;
    
    // Simple elastic collision resolution
    glm::vec3 pos1 = obj1->getPosition();
    glm::vec3 pos2 = obj2->getPosition();
    glm::vec3 vel1 = obj1->getVelocity();
    glm::vec3 vel2 = obj2->getVelocity();
    
    glm::vec3 normal = glm::normalize(pos1 - pos2);
    
    // Separate objects
    float overlap = glm::length(pos1 - pos2) - (obj1->getScale().x + obj2->getScale().x);
    if (overlap < 0) {
        glm::vec3 separation = normal * (-overlap * 0.5f);
        obj1->setPosition(pos1 + separation);
        obj2->setPosition(pos2 - separation);
    }
    
    // Calculate collision response
    float mass1 = obj1->getMass();
    float mass2 = obj2->getMass();
    
    float relativeVel = glm::dot(vel1 - vel2, normal);
    
    if (relativeVel > 0) return;  // Objects are moving apart
    
    float restitution = std::min(obj1->getBounce(), obj2->getBounce());
    float impulse = -(1.0f + restitution) * relativeVel / (1.0f / mass1 + 1.0f / mass2);
    
    glm::vec3 impulseVec = impulse * normal;
    
    if (!obj1->isStatic()) {
        obj1->setVelocity(vel1 + impulseVec / mass1);
    }
    if (!obj2->isStatic()) {
        obj2->setVelocity(vel2 - impulseVec / mass2);
    }
}

glm::vec3 PhysicsEngine::calculateCollisionNormal(std::shared_ptr<AnimationObject> obj1, std::shared_ptr<AnimationObject> obj2) {
    if (!obj1 || !obj2) return glm::vec3(0.0f);
    
    glm::vec3 pos1 = obj1->getPosition();
    glm::vec3 pos2 = obj2->getPosition();
    
    return glm::normalize(pos1 - pos2);
} 
#include "Particle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

Particle::Particle(float x, float y, float mass)
    : AnimationObject("Particle")
    , m_radius(5.0f)
    , m_lifetime(-1.0f)  // -1 means infinite lifetime
    , m_age(0.0f)
    , m_drag(0.1f)
    , m_angularVelocity(0.0f) {
    setPosition(x, y, 0.0f);
    setMass(mass);
    setScale(m_radius, m_radius, 1.0f);
}

Particle::~Particle() {
}

void Particle::setRadius(float radius) {
    m_radius = radius;
    setScale(radius, radius, 1.0f);
}

float Particle::getRadius() const {
    return m_radius;
}

void Particle::setLifetime(float lifetime) {
    m_lifetime = lifetime;
}

float Particle::getLifetime() const {
    return m_lifetime;
}

void Particle::setAge(float age) {
    m_age = age;
}

float Particle::getAge() const {
    return m_age;
}

void Particle::setDrag(float drag) {
    m_drag = std::max(0.0f, std::min(1.0f, drag));
}

float Particle::getDrag() const {
    return m_drag;
}

void Particle::setAngularVelocity(float angularVelocity) {
    m_angularVelocity = angularVelocity;
}

float Particle::getAngularVelocity() const {
    return m_angularVelocity;
}

void Particle::render() {
    if (!isVisible()) return;
    
    glPushMatrix();
    
    // Apply transformations
    glm::mat4 transform = getTransformMatrix();
    glLoadMatrixf(&transform[0][0]);
    
    // Set color with lifetime fade
    glm::vec4 color = getColor();
    float alpha = color.a * getOpacity();
    
    // Fade out based on lifetime
    if (m_lifetime > 0.0f) {
        float lifeProgress = m_age / m_lifetime;
        alpha *= (1.0f - lifeProgress);
    }
    
    glColor4f(color.r, color.g, color.b, alpha);
    
    // Draw particle as a circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);  // Center
    
    const int segments = 16;
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

bool Particle::intersects(const AnimationObject* other) const {
    if (!other) return false;
    
    // Particle-circle intersection
    const Particle* otherParticle = dynamic_cast<const Particle*>(other);
    if (otherParticle) {
        glm::vec3 pos1 = getPosition();
        glm::vec3 pos2 = otherParticle->getPosition();
        float distance = glm::length(pos1 - pos2);
        float radius1 = m_radius * getScale().x;
        float radius2 = otherParticle->getRadius() * otherParticle->getScale().x;
        return distance < (radius1 + radius2);
    }
    
    // Fall back to base class implementation
    return AnimationObject::intersects(other);
}

glm::vec3 Particle::getCollisionNormal(const AnimationObject* other) const {
    if (!other) return glm::vec3(0.0f);
    
    glm::vec3 pos1 = getPosition();
    glm::vec3 pos2 = other->getPosition();
    
    return glm::normalize(pos1 - pos2);
}

glm::vec3 Particle::getMinBounds() const {
    glm::vec3 pos = getPosition();
    float radius = m_radius * getScale().x;
    return pos - glm::vec3(radius, radius, 0.0f);
}

glm::vec3 Particle::getMaxBounds() const {
    glm::vec3 pos = getPosition();
    float radius = m_radius * getScale().x;
    return pos + glm::vec3(radius, radius, 0.0f);
}

std::shared_ptr<AnimationObject> Particle::clone() const {
    auto particle = std::make_shared<Particle>(getPosition().x, getPosition().y, getMass());
    particle->setColor(getColor());
    particle->setScale(getScale());
    particle->setRotation(getRotation());
    particle->setVisible(isVisible());
    particle->setOpacity(getOpacity());
    particle->setRadius(m_radius);
    particle->setLifetime(m_lifetime);
    particle->setAge(m_age);
    particle->setDrag(m_drag);
    particle->setAngularVelocity(m_angularVelocity);
    return particle;
}

std::string Particle::getTypeName() const {
    return "Particle";
}

void Particle::update(float deltaTime) {
    // Update physics
    updatePhysics(deltaTime);
    
    // Update lifetime
    updateLifetime(deltaTime);
    
    // Call base class update
    AnimationObject::update(deltaTime);
}

void Particle::updatePhysics(float deltaTime) {
    if (isStatic()) return;
    
    // Apply drag
    glm::vec3 velocity = getVelocity();
    velocity *= (1.0f - m_drag * deltaTime);
    setVelocity(velocity);
    
    // Update angular rotation
    if (m_angularVelocity != 0.0f) {
        glm::vec3 rotation = getRotation();
        rotation.z += m_angularVelocity * deltaTime;
        setRotation(rotation);
    }
}

void Particle::updateLifetime(float deltaTime) {
    if (m_lifetime > 0.0f) {
        m_age += deltaTime;
        
        // Check if particle should be destroyed
        if (m_age >= m_lifetime) {
            setVisible(false);
            // Could trigger a destruction event here
        }
    }
} 
#pragma once

#include "AnimationObject.h"
#include <glm/glm.hpp>

/**
 * @brief Base class for geometric shapes
 * 
 * Provides common functionality for all geometric shapes
 * including rendering, collision detection, and transformations.
 */
class Shape : public AnimationObject {
public:
    Shape(const std::string& name = "Shape");
    virtual ~Shape();

    // Shape properties
    virtual void setSize(float width, float height);
    virtual glm::vec2 getSize() const;
    
    // Rendering
    virtual void render() override = 0;
    
    // Collision detection
    virtual bool intersects(const AnimationObject* other) const override;
    virtual glm::vec3 getCollisionNormal(const AnimationObject* other) const override;
    
    // Bounding box
    virtual glm::vec3 getMinBounds() const override;
    virtual glm::vec3 getMaxBounds() const override;
    
    // Cloning
    virtual std::shared_ptr<AnimationObject> clone() const override = 0;
    
    // Type information
    virtual std::string getTypeName() const override = 0;

protected:
    glm::vec2 m_size;
    
    // Helper methods for derived classes
    virtual void updateBounds();
    virtual bool pointInside(float x, float y) const = 0;
};

/**
 * @brief Circle shape
 */
class Circle : public Shape {
public:
    Circle(float x, float y, float radius);
    virtual ~Circle();

    // Circle properties
    void setRadius(float radius);
    float getRadius() const;
    
    // Override shape methods
    void setSize(float width, float height) override;
    glm::vec2 getSize() const override;
    
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

protected:
    bool pointInside(float x, float y) const override;
    
private:
    float m_radius;
};

/**
 * @brief Rectangle shape
 */
class Rectangle : public Shape {
public:
    Rectangle(float x, float y, float width, float height);
    virtual ~Rectangle();

    // Rectangle properties
    void setWidth(float width);
    void setHeight(float height);
    float getWidth() const;
    float getHeight() const;
    
    // Override shape methods
    void setSize(float width, float height) override;
    glm::vec2 getSize() const override;
    
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

protected:
    bool pointInside(float x, float y) const override;
};

/**
 * @brief Line shape
 */
class Line : public Shape {
public:
    Line(float x1, float y1, float x2, float y2);
    virtual ~Line();

    // Line properties
    void setStartPoint(float x, float y);
    void setEndPoint(float x, float y);
    glm::vec2 getStartPoint() const;
    glm::vec2 getEndPoint() const;
    
    void setThickness(float thickness);
    float getThickness() const;
    
    // Override shape methods
    void setSize(float width, float height) override;
    glm::vec2 getSize() const override;
    
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

protected:
    bool pointInside(float x, float y) const override;
    
private:
    glm::vec2 m_startPoint;
    glm::vec2 m_endPoint;
    float m_thickness;
}; 
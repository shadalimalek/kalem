#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

// Forward declarations
class AnimationObject;
class Renderer;

/**
 * @brief Scene class for managing collections of animation objects
 * 
 * A scene is a container for animation objects and provides
 * scene-level operations like rendering, updating, and object management.
 */
class Scene {
public:
    Scene(const std::string& name);
    ~Scene();

    // Object management
    void addObject(std::shared_ptr<AnimationObject> obj);
    void removeObject(const std::string& name);
    void removeObject(std::shared_ptr<AnimationObject> obj);
    std::shared_ptr<AnimationObject> getObject(const std::string& name);
    std::vector<std::shared_ptr<AnimationObject>> getAllObjects() const;
    
    // Scene operations
    void update(float deltaTime);
    void render(Renderer* renderer);
    void reset();
    void clear();
    
    // Input handling
    void handleInput();
    
    // Scene properties
    void setName(const std::string& name);
    std::string getName() const;
    
    // Object queries
    std::vector<std::shared_ptr<AnimationObject>> findObjectsByType(const std::string& type);
    std::vector<std::shared_ptr<AnimationObject>> findObjectsInArea(float x, float y, float radius);

private:
    std::string m_name;
    std::vector<std::shared_ptr<AnimationObject>> m_objects;
    std::unordered_map<std::string, std::shared_ptr<AnimationObject>> m_objectMap;
    
    // Helper methods
    void updateObjectMap();
}; 
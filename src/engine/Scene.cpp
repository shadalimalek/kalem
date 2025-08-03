#include "Scene.h"
#include "../objects/AnimationObject.h"
#include "../rendering/Renderer.h"
#include <algorithm>
#include <iostream>

Scene::Scene(const std::string& name) 
    : m_name(name) {
}

Scene::~Scene() {
    clear();
}

void Scene::addObject(std::shared_ptr<AnimationObject> obj) {
    if (obj) {
        m_objects.push_back(obj);
        updateObjectMap();
        std::cout << "Added object '" << obj->getName() << "' to scene '" << m_name << "'" << std::endl;
    }
}

void Scene::removeObject(const std::string& name) {
    auto it = std::find_if(m_objects.begin(), m_objects.end(),
        [&name](const std::shared_ptr<AnimationObject>& obj) {
            return obj->getName() == name;
        });
    
    if (it != m_objects.end()) {
        m_objects.erase(it);
        updateObjectMap();
        std::cout << "Removed object '" << name << "' from scene '" << m_name << "'" << std::endl;
    }
}

void Scene::removeObject(std::shared_ptr<AnimationObject> obj) {
    if (obj) {
        removeObject(obj->getName());
    }
}

std::shared_ptr<AnimationObject> Scene::getObject(const std::string& name) {
    auto it = m_objectMap.find(name);
    if (it != m_objectMap.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<std::shared_ptr<AnimationObject>> Scene::getAllObjects() const {
    return m_objects;
}

void Scene::update(float deltaTime) {
    for (auto& obj : m_objects) {
        if (obj && obj->isVisible()) {
            obj->update(deltaTime);
        }
    }
}

void Scene::render(Renderer* renderer) {
    if (!renderer) return;
    
    // Sort objects by render order
    std::vector<std::shared_ptr<AnimationObject>> sortedObjects = m_objects;
    std::sort(sortedObjects.begin(), sortedObjects.end(),
        [](const std::shared_ptr<AnimationObject>& a, const std::shared_ptr<AnimationObject>& b) {
            return a->getRenderOrder() < b->getRenderOrder();
        });
    
    // Render all visible objects
    for (auto& obj : sortedObjects) {
        if (obj && obj->isVisible()) {
            obj->render();
        }
    }
}

void Scene::reset() {
    for (auto& obj : m_objects) {
        if (obj) {
            // Reset object to initial state
            obj->setAnimationProgress(0.0f);
        }
    }
}

void Scene::clear() {
    m_objects.clear();
    m_objectMap.clear();
}

void Scene::handleInput() {
    // Scene-level input handling can be implemented here
    // For now, individual objects handle their own input
}

void Scene::setName(const std::string& name) {
    m_name = name;
}

std::string Scene::getName() const {
    return m_name;
}

std::vector<std::shared_ptr<AnimationObject>> Scene::findObjectsByType(const std::string& type) {
    std::vector<std::shared_ptr<AnimationObject>> result;
    
    for (auto& obj : m_objects) {
        if (obj && obj->getTypeName() == type) {
            result.push_back(obj);
        }
    }
    
    return result;
}

std::vector<std::shared_ptr<AnimationObject>> Scene::findObjectsInArea(float x, float y, float radius) {
    std::vector<std::shared_ptr<AnimationObject>> result;
    
    for (auto& obj : m_objects) {
        if (obj) {
            glm::vec3 pos = obj->getPosition();
            float distance = sqrt((pos.x - x) * (pos.x - x) + (pos.y - y) * (pos.y - y));
            
            if (distance <= radius) {
                result.push_back(obj);
            }
        }
    }
    
    return result;
}

void Scene::updateObjectMap() {
    m_objectMap.clear();
    for (auto& obj : m_objects) {
        if (obj) {
            m_objectMap[obj->getName()] = obj;
        }
    }
} 
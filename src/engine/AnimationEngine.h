#pragma once

#include <memory>
#include <vector>
#include <string>
#include <functional>

// Forward declarations
class Scene;
class AnimationObject;
class Timeline;
class PhysicsEngine;
class Renderer;

/**
 * @brief Main animation engine class
 * 
 * This is the core class that manages all animations, scenes, and rendering.
 * It provides a simple interface for creating and running animations.
 */
class AnimationEngine {
public:
    AnimationEngine();
    ~AnimationEngine();

    // Scene management
    Scene* createScene(const std::string& name);
    Scene* getCurrentScene();
    void setCurrentScene(Scene* scene);
    
    // Animation control
    void play();
    void pause();
    void reset();
    void setTimeScale(float scale);
    float getTimeScale() const;
    
    // Object management
    void addObject(std::shared_ptr<AnimationObject> obj);
    void removeObject(const std::string& name);
    std::shared_ptr<AnimationObject> getObject(const std::string& name);
    
    // Physics
    void enablePhysics(bool enable);
    void setGravity(float gx, float gy);
    void setAirResistance(float resistance);
    
    // Rendering
    void render();
    void setBackground(float r, float g, float b);
    
    // Input handling
    void handleInput();
    void handleKeyPress(int key);
    void handleMouseClick(float x, float y);
    void onKeyPress(int key, std::function<void()> callback);
    void onMouseClick(std::function<void(float, float)> callback);
    
    // Export
    void exportVideo(const std::string& filename, int fps = 30);
    void exportGif(const std::string& filename, int fps = 15);
    void exportCode(const std::string& filename);
    
    // Utility
    bool isRunning() const;
    float getCurrentTime() const;
    void update(float dt);

private:
    std::unique_ptr<Scene> m_currentScene;
    std::unique_ptr<PhysicsEngine> m_physicsEngine;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Timeline> m_timeline;
    
    bool m_isRunning;
    float m_timeScale;
    std::vector<std::function<void()>> m_keyCallbacks;
    std::vector<std::function<void(float, float)>> m_mouseCallbacks;
};

// Global engine instance
extern AnimationEngine* g_engine;

// Easy access functions
AnimationEngine* getEngine();
void initEngine();
void shutdownEngine(); 
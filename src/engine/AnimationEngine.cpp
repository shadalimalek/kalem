#include "AnimationEngine.h"
#include "Scene.h"
#include "Timeline.h"
#include "PhysicsEngine.h"
#include "../rendering/Renderer.h"
#include "../objects/AnimationObject.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <algorithm>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

// Global engine instance
AnimationEngine* g_engine = nullptr;

AnimationEngine::AnimationEngine() 
    : m_isRunning(false)
    , m_timeScale(1.0f) {
    
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }
    
    // Create window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(1200, 800, "Kalem - Educational Animation Engine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(window);
    
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }
    
    // Initialize components
    m_currentScene = std::make_unique<Scene>("MainScene");
    m_physicsEngine = std::make_unique<PhysicsEngine>();
    m_renderer = std::make_unique<Renderer>(window);
    m_timeline = std::make_unique<Timeline>();
    
    // Minimal input handling for basic controls (ESC to exit)
    glfwSetWindowUserPointer(window, this);
    
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    });
    
    // Set background color
    m_renderer->setBackground(0.1f, 0.1f, 0.1f);
    
    std::cout << "AnimationEngine initialized successfully!" << std::endl;
}

AnimationEngine::~AnimationEngine() {
    glfwTerminate();
}

Scene* AnimationEngine::createScene(const std::string& name) {
    m_currentScene = std::make_unique<Scene>(name);
    return m_currentScene.get();
}

Scene* AnimationEngine::getCurrentScene() {
    return m_currentScene.get();
}

void AnimationEngine::setCurrentScene(Scene* scene) {
    if (scene) {
        m_currentScene.reset(scene);
    }
}

void AnimationEngine::play() {
    m_isRunning = true;
    m_timeline->play();
}

void AnimationEngine::pause() {
    m_isRunning = false;
    m_timeline->pause();
}

void AnimationEngine::reset() {
    m_timeline->reset();
    if (m_currentScene) {
        m_currentScene->reset();
    }
}

void AnimationEngine::setTimeScale(float scale) {
    m_timeScale = scale;
    m_timeline->setTimeScale(scale);
}

float AnimationEngine::getTimeScale() const {
    return m_timeScale;
}

void AnimationEngine::addObject(std::shared_ptr<AnimationObject> obj) {
    if (m_currentScene) {
        m_currentScene->addObject(obj);
    }
}

void AnimationEngine::removeObject(const std::string& name) {
    if (m_currentScene) {
        m_currentScene->removeObject(name);
    }
}

std::shared_ptr<AnimationObject> AnimationEngine::getObject(const std::string& name) {
    if (m_currentScene) {
        return m_currentScene->getObject(name);
    }
    return nullptr;
}

void AnimationEngine::enablePhysics(bool enable) {
    if (m_physicsEngine) {
        m_physicsEngine->setEnabled(enable);
    }
}

void AnimationEngine::setGravity(float gx, float gy) {
    if (m_physicsEngine) {
        m_physicsEngine->setGravity(glm::vec3(gx, gy, 0.0f));
    }
}

void AnimationEngine::setAirResistance(float resistance) {
    if (m_physicsEngine) {
        m_physicsEngine->setAirResistance(resistance);
    }
}

void AnimationEngine::render() {
    if (m_renderer && m_currentScene) {
        m_renderer->beginFrame();
        m_currentScene->render(m_renderer.get());
        m_renderer->endFrame();
    }
}

void AnimationEngine::setBackground(float r, float g, float b) {
    if (m_renderer) {
        m_renderer->setBackground(r, g, b);
    }
}

void AnimationEngine::handleInput() {
    if (m_currentScene) {
        m_currentScene->handleInput();
    }
}

void AnimationEngine::onKeyPress(int key, std::function<void()> callback) {
    // Minimal key handling - only for essential controls
    // Most animation control should be programmatic
    m_keyCallbacks.push_back(callback);
}

void AnimationEngine::onMouseClick(std::function<void(float, float)> callback) {
    // Minimal mouse handling - only for essential controls
    // Most animation control should be programmatic
    m_mouseCallbacks.push_back(callback);
}

void AnimationEngine::exportVideo(const std::string& filename, int fps) {
    // TODO: Implement video export
    std::cout << "Video export to " << filename << " (not yet implemented)" << std::endl;
}

void AnimationEngine::exportGif(const std::string& filename, int fps) {
    // TODO: Implement GIF export
    std::cout << "GIF export to " << filename << " (not yet implemented)" << std::endl;
}

void AnimationEngine::exportCode(const std::string& filename) {
    // TODO: Implement code export
    std::cout << "Code export to " << filename << " (not yet implemented)" << std::endl;
}

bool AnimationEngine::isRunning() const {
    return m_isRunning && !glfwWindowShouldClose(glfwGetCurrentContext());
}

float AnimationEngine::getCurrentTime() const {
    return m_timeline->getCurrentTime();
}

void AnimationEngine::update(float dt) {
    // Update timeline
    m_timeline->update(dt * m_timeScale);
    
    // Update physics
    if (m_physicsEngine && m_physicsEngine->isEnabled()) {
        m_physicsEngine->update(dt);
    }
    
    // Update scene
    if (m_currentScene) {
        m_currentScene->update(dt);
    }
    
    // Render
    render();
    
    // Handle input
    handleInput();
    
    // Poll events
    glfwPollEvents();
}

void AnimationEngine::handleKeyPress(int key) {
    // Minimal key handling - only for essential controls
    // Most animation control should be programmatic
    for (auto& callback : m_keyCallbacks) {
        callback();
    }
}

void AnimationEngine::handleMouseClick(float x, float y) {
    // Minimal mouse handling - only for essential controls
    // Most animation control should be programmatic
    // Convert screen coordinates to world coordinates
    float worldX = (x - 600.0f) * 2.0f / 1200.0f;  // Convert to [-1, 1] range
    float worldY = (400.0f - y) * 2.0f / 800.0f;   // Convert to [-1, 1] range
    
    for (auto& callback : m_mouseCallbacks) {
        callback(worldX * 500.0f, worldY * 400.0f);  // Scale to world coordinates
    }
} 
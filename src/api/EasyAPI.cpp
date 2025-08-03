#include "EasyAPI.h"
#include "engine/AnimationEngine.h"
#include "objects/AnimationObject.h"
#include "objects/Particle.h"
#include "objects/Shape.h"
#include "objects/Text.h"
#include <iostream>

// ============================================================================
// GLOBAL ENGINE INSTANCE
// ============================================================================

static AnimationEngine* g_engine = nullptr;

// ============================================================================
// COLOR DEFINITIONS
// ============================================================================

const Color RED(1.0f, 0.0f, 0.0f);
const Color GREEN(0.0f, 1.0f, 0.0f);
const Color BLUE(0.0f, 0.0f, 1.0f);
const Color YELLOW(1.0f, 1.0f, 0.0f);
const Color CYAN(0.0f, 1.0f, 1.0f);
const Color MAGENTA(1.0f, 0.0f, 1.0f);
const Color WHITE(1.0f, 1.0f, 1.0f);
const Color BLACK(0.0f, 0.0f, 0.0f);
const Color GRAY(0.5f, 0.5f, 0.5f);

// ============================================================================
// ENGINE INITIALIZATION
// ============================================================================

void initEngine() {
    if (!g_engine) {
        g_engine = new AnimationEngine();
        std::cout << "Kalem Animation Engine initialized successfully!" << std::endl;
    }
}

void shutdownEngine() {
    if (g_engine) {
        delete g_engine;
        g_engine = nullptr;
        std::cout << "Kalem Animation Engine shutdown." << std::endl;
    }
}

AnimationEngine* getEngine() {
    if (!g_engine) {
        initEngine();
    }
    return g_engine;
}

// ============================================================================
// OBJECT CREATION FUNCTIONS
// ============================================================================

std::shared_ptr<AnimationObject> create_circle(float x, float y, float radius, const Color& color) {
    auto engine = getEngine();
    auto circle = std::make_shared<Circle>(x, y, radius);
    circle->setColor(color.r, color.g, color.b, 1.0f);
    engine->addObject(circle);
    return circle;
}

std::shared_ptr<AnimationObject> create_rectangle(float x, float y, float width, float height, const Color& color) {
    auto engine = getEngine();
    auto rect = std::make_shared<Rectangle>(x, y, width, height);
    rect->setColor(color.r, color.g, color.b, 1.0f);
    engine->addObject(rect);
    return rect;
}

std::shared_ptr<AnimationObject> create_line(float x1, float y1, float x2, float y2, const Color& color) {
    auto engine = getEngine();
    auto line = std::make_shared<Line>(x1, y1, x2, y2);
    line->setColor(color.r, color.g, color.b, 1.0f);
    engine->addObject(line);
    return line;
}

std::shared_ptr<AnimationObject> create_text(float x, float y, const std::string& text, const Color& color) {
    auto engine = getEngine();
    auto textObj = std::make_shared<TextObject>(x, y, text);
    textObj->setColor(color.r, color.g, color.b, 1.0f);
    engine->addObject(textObj);
    return textObj;
}

std::shared_ptr<AnimationObject> create_particle(float x, float y, float mass) {
    auto engine = getEngine();
    auto particle = std::make_shared<Particle>(x, y, mass);
    engine->addObject(particle);
    return particle;
}

// ============================================================================
// ANIMATION FUNCTIONS
// ============================================================================

std::function<void(AnimationObject*, float)> move_to(float x, float y) {
    return [x, y](AnimationObject* obj, float progress) {
        if (obj) {
            // Simple linear interpolation
            glm::vec3 startPos = obj->getPosition();
            glm::vec3 endPos(x, y, startPos.z);
            glm::vec3 newPos = startPos + (endPos - startPos) * progress;
            obj->setPosition(newPos);
        }
    };
}

std::function<void(AnimationObject*, float)> move_by(float dx, float dy) {
    return [dx, dy](AnimationObject* obj, float progress) {
        if (obj) {
            glm::vec3 pos = obj->getPosition();
            obj->setPosition(pos.x + dx * progress, pos.y + dy * progress, pos.z);
        }
    };
}

std::function<void(AnimationObject*, float)> rotate_to(float angle) {
    return [angle](AnimationObject* obj, float progress) {
        if (obj) {
            glm::vec3 rotation = obj->getRotation();
            float startAngle = rotation.z;
            float endAngle = angle;
            float newAngle = startAngle + (endAngle - startAngle) * progress;
            obj->setRotation(rotation.x, rotation.y, newAngle);
        }
    };
}

std::function<void(AnimationObject*, float)> scale_to(float factor) {
    return [factor](AnimationObject* obj, float progress) {
        if (obj) {
            glm::vec3 scale = obj->getScale();
            glm::vec3 startScale = scale;
            glm::vec3 endScale(factor, factor, factor);
            glm::vec3 newScale = startScale + (endScale - startScale) * progress;
            obj->setScale(newScale);
        }
    };
}

void animate(std::shared_ptr<AnimationObject> obj, 
             std::function<void(AnimationObject*, float)> animation, 
             const Time& duration) {
    if (obj && animation) {
        // Store animation data in the object
        obj->setAnimationCallback([animation, duration](float progress) {
            // This will be called by the engine during animation updates
            if (animation) {
                animation(nullptr, progress);
            }
        });
        
        // Start the animation
        auto engine = getEngine();
        engine->play();
    }
}

// ============================================================================
// PHYSICS FUNCTIONS
// ============================================================================

void apply_force(std::shared_ptr<AnimationObject> obj, float fx, float fy) {
    if (obj) {
        glm::vec3 currentAccel = obj->getAcceleration();
        obj->setAcceleration(currentAccel.x + fx, currentAccel.y + fy, currentAccel.z);
    }
}

void apply_gravity(std::shared_ptr<AnimationObject> obj) {
    if (obj) {
        obj->setGravityAffected(true);
        auto engine = getEngine();
        engine->setGravity(0.0f, -9.81f, 0.0f);
    }
}

void set_bounce(std::shared_ptr<AnimationObject> obj, bool bounce) {
    if (obj) {
        obj->setBounce(bounce ? 0.8f : 0.0f);
    }
}

void run_simulation(const Time& duration) {
    auto engine = getEngine();
    engine->enablePhysics(true);
    engine->play();
    
    // Run for the specified duration
    float elapsed = 0.0f;
    while (elapsed < duration.seconds) {
        engine->update(1.0f / 60.0f); // 60 FPS
        elapsed += 1.0f / 60.0f;
    }
}

// ============================================================================
// COMPLEX ANIMATIONS
// ============================================================================

std::function<void(AnimationObject*, float)> sequence(
    std::vector<std::function<void(AnimationObject*, float)>> animations) {
    
    return [animations](AnimationObject* obj, float progress) {
        if (animations.empty()) return;
        
        float segmentSize = 1.0f / animations.size();
        int currentSegment = static_cast<int>(progress / segmentSize);
        float segmentProgress = (progress - currentSegment * segmentSize) / segmentSize;
        
        if (currentSegment < animations.size()) {
            animations[currentSegment](obj, segmentProgress);
        }
    };
}

void parallel(std::vector<std::shared_ptr<AnimationObject>> objects,
             std::vector<std::function<void(AnimationObject*, float)>> animations,
             const Time& duration) {
    
    if (objects.size() != animations.size()) return;
    
    for (size_t i = 0; i < objects.size(); ++i) {
        animate(objects[i], animations[i], duration);
    }
}

// ============================================================================
// CONTROL FUNCTIONS
// ============================================================================

void run_animation() {
    auto engine = getEngine();
    engine->play();
    
    // Main animation loop
    while (engine->isRunning()) {
        engine->update(1.0f / 60.0f);
        engine->render();
        
        // Handle input
        engine->handleInput();
    }
}

void pause_animation() {
    auto engine = getEngine();
    engine->pause();
}

void resume_animation() {
    auto engine = getEngine();
    engine->play();
}

void reset_animation() {
    auto engine = getEngine();
    engine->reset();
}

void set_speed(float scale) {
    auto engine = getEngine();
    engine->setTimeScale(scale);
}

// ============================================================================
// STYLING FUNCTIONS
// ============================================================================

void set_color(std::shared_ptr<AnimationObject> obj, const Color& color) {
    if (obj) {
        obj->setColor(color.r, color.g, color.b, 1.0f);
    }
}

void set_opacity(std::shared_ptr<AnimationObject> obj, float opacity) {
    if (obj) {
        obj->setOpacity(opacity);
    }
}

void set_visible(std::shared_ptr<AnimationObject> obj, bool visible) {
    if (obj) {
        obj->setVisible(visible);
    }
}

// ============================================================================
// EXPORT FUNCTIONS
// ============================================================================

void export_video(const std::string& filename, int fps) {
    auto engine = getEngine();
    engine->exportVideo(filename, fps);
}

void export_gif(const std::string& filename, int fps) {
    auto engine = getEngine();
    engine->exportGif(filename, fps);
}

void export_code(const std::string& filename) {
    auto engine = getEngine();
    engine->exportCode(filename);
}

// ============================================================================
// INTERACTIVE FUNCTIONS
// ============================================================================

void on_key_press(int key, std::function<void()> callback) {
    auto engine = getEngine();
    engine->onKeyPress(key, callback);
}

void on_mouse_click(std::function<void(float, float)> callback) {
    auto engine = getEngine();
    engine->onMouseClick(callback);
}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

float get_current_time() {
    auto engine = getEngine();
    return engine->getCurrentTime();
}

bool is_playing() {
    auto engine = getEngine();
    return engine->isRunning();
}

std::shared_ptr<AnimationObject> findObjectByName(const std::string& name) {
    auto engine = getEngine();
    return engine->getObject(name);
}

void wait(const Time& duration) {
    // Simple wait implementation
    float elapsed = 0.0f;
    while (elapsed < duration.value) {
        elapsed += 1.0f / 60.0f;
        // Could add actual sleep here for better performance
    }
} 